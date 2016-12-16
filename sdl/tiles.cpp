/*
2D tile-based game world, made for programmable AIs to compete.

https://en.wikipedia.org/wiki/Tile-based_video_game

TODO:

-   when hold is pressed, only take input at end of tick. Otherwise, any click leads to double move.
-   implement one type of score
-   display mode that only shows the line of sight of on chosen object
-   redo previous human action
-   pause
-   use protobuf serialization for full world state, controller world view, and controller actions
-   put players in separate processes, and control resources:
    - time
    - RAM
    - disk: loopback + seccomp should suffice
    But hopefully allow for access to:
    - threading
    - GPU (TODO how to enforce fair resource sharing of GPU shaders?)
    Should we use raw seccomp, or a more full blown docker?
-   draw grids to screen
-   display line of sight of objects on screen
-   toroidal world, or world with closed barriers (invisible walls are a hard mechanic for AI to grasp!)
-   use quadtree (same as B-tree width width 4?) for searches.
    Boost geometry has some classes: http://www.boost.org/doc/libs/1_58_0/libs/geometry/doc/html/geometry/spatial_indexes/introduction.html
    R-tree is even more efficient as it is not restricted to halves only.
*/

#include "common.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

const unsigned int COLOR_MAX = 255;
const unsigned int N_COLOR_CHANNELS = 4;

class Actor;
class DrawableObject;
class World;

class Action {
    public:
        enum class MoveX {
            NONE,
            LEFT,
            RIGHT
        };
        enum class MoveY {
            NONE,
            DOWN,
            UP
        };
        Action() { this->reset(); }
        Action(MoveX moveX, MoveY moveY) :
            moveX(moveX), moveY(moveY) {}
        MoveX getMoveX() const { return this->moveX; }
        MoveY getMoveY() const { return this->moveY; }
        void reset() {
            this->moveX = MoveX::NONE;
            this->moveY = MoveY::NONE;
        };
        void setMoveX(MoveX x) { this->moveX = x; }
        void setMoveY(MoveY y) { this->moveY = y; }
    private:
        MoveX moveX;
        MoveY moveY;
};

class Object {
    public:
        enum class Type {
            DO_NOTHING,
            MOVE_UP,
            MOVE_DOWN,
            RANDOM,
            FOLLOW_HUMAN,
            FLEE_HUMAN,
            HUMAN
        };
        Object();
        virtual ~Object();
        Object(
            unsigned int x,
            unsigned int y,
            Type type,
            std::unique_ptr<Actor> actor,
            unsigned int fov,
            std::unique_ptr<DrawableObject> drawableObject
        );
        void draw(const World& world, int cameraX = 0, int cameraY = 0) const;
        Actor& getActor() const;
        unsigned int getFov() const;
        unsigned int getX() const;
        unsigned int getY() const;
        Type getType() const;
        void setX(unsigned int x);
        void setY(unsigned int y);
    protected:
        unsigned int x;
        unsigned int y;
        unsigned int fov;
        std::unique_ptr<Actor> actor;
        Type type;
        std::unique_ptr<DrawableObject> drawableObject;
};

class DrawableObject {
    public:
        virtual ~DrawableObject(){}
        // cameraX / Y: lower left corner of the camera.
        // Signed as it might go out of the scenario if player goes to world corner.
        virtual void draw(
            const World& world,
            const Object& object,
            int cameraX = 0,
            int cameraY = 0
        ) const = 0;
};

/// Placeholder for when we don't have any display.
class DoNothingDrawableObject : public DrawableObject {
    public:
        DoNothingDrawableObject(){}
        virtual void draw(const World& world, const Object& object, int cameraX = 0, int cameraY = 0) const {}
};

/// The properties of an object that actors can see.
/// E.g., actors may not know the line of sight of other objects.
class ObjectView {
    public:
        ObjectView(int x, int y, Object::Type type)
            : x(x), y(y), type(type) {}
        int getX() const { return this->x; }
        int getY() const { return this->y; }
        Object::Type getType() const { return this->type; }
    private:
        int x;
        int y;
        Object::Type type;
};

std::ostream& operator<<(std::ostream& os, const ObjectView& o) {
    return os << "ObjectView, x = " << o.getX() << ", y = " << o.getY();
}

/// The portion of the world that actors can see.
/// E.g.: actors cannot see what lies beyond their line of sight.
class WorldView {
    public:
        WorldView(unsigned int width, unsigned int height, std::unique_ptr<std::vector<std::unique_ptr<ObjectView>>> objectViews) :
            width(width), height(height), objectViews(std::move(objectViews)) {}
        unsigned int getHeight() const { return this->height; }
        const std::vector<std::unique_ptr<ObjectView>>& getObjectViews() const { return *this->objectViews; }
        unsigned int getWidth() const { return this->width; }
    private:
        unsigned int width;
        unsigned int height;
        std::unique_ptr<std::vector<std::unique_ptr<ObjectView>>> objectViews;
};

class World {
    public:
        World(
            unsigned int width,
            unsigned int height,
            bool display,
            unsigned int windowWidthPix,
            unsigned int windowHeightPix,
            int showFovId
        );
        ~World();
        void draw() const;
        void destroyTextures();
        /// Collect desired actions from all objects, and resolve them
        unsigned int getHeight() const;
        unsigned int getNHumanActions() const;
        const std::vector<std::unique_ptr<Object>>& getObjects() const;
        SDL_Renderer * getRenderer() const;
        unsigned int getTileWidthPix() const;
        unsigned int getTileHeightPix() const;
        unsigned int getWidth() const;
        unsigned int getViewHeight() const;
        void init();
        void reset();
        /// to the next world state. E.g.: what happens if two objects
        /// want to move to the same place next tick? Or if an object
        /// wants to move into a wall?
        void update(const std::vector<std::unique_ptr<Action>> &humanActions);
    private:
        int showFovId;
        unsigned int height;
        unsigned int nHumanActions;
        unsigned int tileHeightPix;
        unsigned int tileWidthPix;
        unsigned int width;
        unsigned int windowHeightPix;
        unsigned int windowWidthPix;
        unsigned int viewHeight;
        bool display;
        SDL_Renderer *renderer;
        SDL_Window *window;
        std::vector<std::unique_ptr<Object>> objects;
        std::vector<SDL_Texture *> textures;

        // Private methods.
        /// Should we only show the FOV for a single object on screen? Or show every object?
        bool showFov() const;
        SDL_Texture * createSolidTexture(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
        /// Advance iterator until the next object in the FOV of object, including it itself.
        /// Return true if such object exists, false if there are no more.
        /// The caller is responsible for incrementing the pointer to ask for the next object.
        bool findNextObjectInFov(std::vector<std::unique_ptr<Object>>::const_iterator& it, const Object& object, int& dx, int& dy) const;
        std::unique_ptr<WorldView> createWorldView(const Object &object) const;
        void createSingleTextureObject(
            unsigned int x,
            unsigned int y,
            Object::Type type,
            std::unique_ptr<Actor> actor,
            unsigned int fov,
            size_t textureId
        );
};

Object::Object() : drawableObject(new DoNothingDrawableObject()) {}
Object::Object(
    unsigned int x,
    unsigned int y,
    Type type,
    std::unique_ptr<Actor> actor,
    unsigned int fov,
    std::unique_ptr<DrawableObject> drawableObject
) :
    x(x),
    y(y),
    type(type),
    actor(std::move(actor)),
    fov(fov),
    drawableObject(std::move(drawableObject))
{}
Object::~Object() {}
void Object::draw(const World& world, int cameraX, int cameraY) const {
    this->drawableObject->draw(world, *this, cameraX, cameraY);
}
Actor& Object::getActor() const { return *this->actor; }
Object::Type Object::getType() const { return this->type; }
unsigned int Object::getFov() const { return this->fov; }
unsigned int Object::getX() const { return this->x; }
unsigned int Object::getY() const { return this->y; }
void Object::setX(unsigned int x) { this->x = x; }
void Object::setY(unsigned int y) { this->y = y; }

std::ostream& operator<<(std::ostream& os, const Object& o) {
    return os << "Object, x = " << o.getX() << ", y = " << o.getY();
}

class Actor {
    public:
        /// Perceive one step of the world.
        /// Update internal mental state.
        /// Return an action for this current world step.
        virtual Action act(const WorldView &worldView) = 0;
        virtual bool takesHumanAction() const { return false; }
};

class DoNothingActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            return Action();
        };
};

class MoveUpActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            return Action(Action::MoveX::NONE, Action::MoveY::UP);
        };
};

class MoveDownActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            return Action(Action::MoveX::NONE, Action::MoveY::DOWN);
        };
};

class RandomActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            Action::MoveX x;
            Action::MoveY y;
            switch (rand() % 3) {
                case 0:
                    x = Action::MoveX::LEFT;
                break;
                case 1:
                    x = Action::MoveX::NONE;
                break;
                case 2:
                    x = Action::MoveX::RIGHT;
                break;
            }
            switch (rand() % 3) {
                case 0:
                    y = Action::MoveY::DOWN;
                break;
                case 1:
                    y = Action::MoveY::NONE;
                break;
                case 2:
                    y = Action::MoveY::UP;
                break;
            }
            return Action(x, y);
        };
};

class HumanActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            return Action();
        };
        virtual bool takesHumanAction() const { return true; }
};

/// Follow the first human it sees. TODO: closest.
/// Dumb: no understanding of walls.
class FollowHumanActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            Action a;
            for (auto const& objectView : worldView.getObjectViews()) {
                if (objectView->getType() == Object::Type::HUMAN) {
                    if (objectView->getX() > 0) {
                        a.setMoveX(Action::MoveX::RIGHT);
                    } else if (objectView->getX() < 0) {
                        a.setMoveX(Action::MoveX::LEFT);
                    }
                    if (0 < objectView->getY()) {
                        a.setMoveY(Action::MoveY::UP);
                    } else if (0 > objectView->getY()) {
                        a.setMoveY(Action::MoveY::DOWN);
                    }
                    break;
                }
            }
            return a;
        };
};

/// Follow the first human it sees. TODO: closest.
/// Dumb: no understanding of walls.
class FleeHumanActor : public Actor {
    public:
        virtual Action act(const WorldView &worldView) {
            Action a;
            for (auto const& objectView : worldView.getObjectViews()) {
                if (objectView->getType() == Object::Type::HUMAN) {
                    if (objectView->getX() < 0) {
                        a.setMoveX(Action::MoveX::RIGHT);
                    } else {
                        a.setMoveX(Action::MoveX::LEFT);
                    }
                    if (objectView->getY() > 0) {
                        a.setMoveY(Action::MoveY::DOWN);
                    } else {
                        a.setMoveY(Action::MoveY::UP);
                    }
                    break;
                }
            }
            return a;
        };
};

class SingleTextureDrawableObject : public DrawableObject {
    public:
        SingleTextureDrawableObject(SDL_Texture *texture) :
            texture(texture) {}
        virtual void draw(
            const World& world,
            const Object& object,
            int cameraX,
            int cameraY
        ) const {
            SDL_Rect rect;
            rect.x = (object.getX() - cameraX) * world.getTileWidthPix();
            rect.y = ((world.getViewHeight() - 1) - (object.getY() - cameraY)) * world.getTileHeightPix();
            rect.w = world.getTileWidthPix();
            rect.h = world.getTileHeightPix();
            SDL_RenderCopy(world.getRenderer(), this->texture, NULL, &rect);
        }
    private:
        /// Pointer to texture shared across all objects that look the same.
        SDL_Texture * texture;
};

World::World(
    unsigned int width,
    unsigned int height,
    bool display,
    unsigned int windowWidthPix,
    unsigned int windowHeightPix,
    int showFovId
) :
    width(width),
    height(height),
    display(display),
    windowWidthPix(windowWidthPix),
    windowHeightPix(windowHeightPix),
    showFovId(showFovId)
{
    this->window = NULL;
    this->renderer = NULL;
    if (this->display) {
        // Window setup.
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(this->windowWidthPix, this->windowHeightPix, 0, &this->window, &this->renderer);
        SDL_SetWindowTitle(window, __FILE__);
    }
    this->init();
}

World::~World() {
    if (this->display) {
        this->destroyTextures();
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }
}

void World::draw() const {
    int dx, dy;
    if (this->display) {
        Uint8 *base;
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
        SDL_RenderClear(this->renderer);
        auto it = this->objects.begin();
        int dx, dy;
        if (this->showFov()) {
            auto const& object = *(this->objects[this->showFovId]);
            auto cameraX = object.getX() - (object.getFov() / 2);
            auto cameraY = object.getY() - (object.getFov() / 2);
            while (this->findNextObjectInFov(it, object, dx, dy)) {
                auto const& otherObject = **it;
                otherObject.draw(*this, cameraX, cameraY);
                it++;
            }
        } else {
            for (auto const& object : this->objects) {
                object->draw(*this);
            }
        }
        SDL_RenderPresent(this->renderer);
    }
}

void World::destroyTextures() {
    for (auto& texture : this->textures) {
        SDL_DestroyTexture(texture);
    }
    this->textures.clear();
}

void World::init() {
    this->nHumanActions = 0;
    unsigned int fov = std::min(this->getWidth(), this->getHeight()) / 2;

    // Setup textures. Depends on fov if we are watching an object.
    if (this->display) {
        unsigned int fovWidth = 0;
        unsigned int fovHeight = 0;
        if (this->showFov()) {
            fovWidth = fov;
            fovHeight = fovWidth;
            this->viewHeight = fovHeight;
        } else {
            fovWidth = this->width;
            fovHeight = this->height;
            this->viewHeight = this->height;
        }
        this->tileWidthPix = windowWidthPix / fovWidth;
        this->tileHeightPix = windowHeightPix / fovHeight;
        createSolidTexture(COLOR_MAX, 0, 0, 0);
        createSolidTexture(0, COLOR_MAX, 0, 0);
        createSolidTexture(0, 0, COLOR_MAX, 0);
        createSolidTexture(COLOR_MAX, COLOR_MAX, 0, 0);
        createSolidTexture(COLOR_MAX, 0, COLOR_MAX, 0);
        createSolidTexture(0, COLOR_MAX, COLOR_MAX, 0);
        createSolidTexture(COLOR_MAX, COLOR_MAX, COLOR_MAX, 0);
        createSolidTexture(COLOR_MAX / 2, COLOR_MAX / 2, COLOR_MAX / 2, 0);
        createSolidTexture(0, COLOR_MAX / 2, COLOR_MAX, 0);
    }

    // Place objects.
    this->createSingleTextureObject(
        this->getWidth() / 2,
        this->getHeight() / 2,
        Object::Type::HUMAN,
        std::make_unique<HumanActor>(),
        fov,
        0
    );
    //this->createSingleTextureObject(
        //(this->getWidth() / 2) + 1,
        //(this->getHeight() / 2) + 1,
        //Object::Type::HUMAN,
        //std::make_unique<HumanActor>(),
        //fov,
        //1
    //);
    this->createSingleTextureObject(
        this->getWidth() / 4,
        this->getHeight() / 4,
        Object::Type::RANDOM,
        std::make_unique<RandomActor>(),
        fov,
        2
    );
    this->createSingleTextureObject(
        3 * this->getWidth() / 4,
        this->getHeight() / 4,
        Object::Type::FOLLOW_HUMAN,
        std::make_unique<FollowHumanActor>(),
        fov,
        3
    );
    this->createSingleTextureObject(
        3 * this->getWidth() / 4,
        3 * this->getHeight() / 4,
        Object::Type::FLEE_HUMAN,
        std::make_unique<FleeHumanActor>(),
        fov,
        4
    );
    this->createSingleTextureObject(
        this->getWidth() / 4,
        3 * this->getHeight() / 4,
        Object::Type::DO_NOTHING,
        std::make_unique<DoNothingActor>(),
        fov,
        5
    );
    for (unsigned int y = 0; y < this->height; ++y) {
        for (unsigned int x = 0; x < this->width; ++x) {
            unsigned int sum = x + y;
            if (sum % 5 == 0) {
                this->createSingleTextureObject(x, y, Object::Type::MOVE_UP, std::make_unique<MoveUpActor>(), fov, 6);
            } else if (sum % 7 == 0) {
                this->createSingleTextureObject(x, y, Object::Type::MOVE_DOWN, std::make_unique<MoveDownActor>(), fov, 7);
            }
        }
    }
}

// Reset to initial state.
// Resets everything, except the main window which stays open.
void World::reset() {
    this->objects.clear();
    this->destroyTextures();
    this->init();
}

void World::update(const std::vector<std::unique_ptr<Action>>& humanActions) {
    auto humanActionsIt = humanActions.begin();
    for (auto &object : this->objects) {
        Action action;
        auto& actor = object->getActor();
        if (actor.takesHumanAction()) {
            action = **humanActionsIt;
            humanActionsIt++;
        } else {
            action = actor.act(*createWorldView(*object));
        }

        // X
        if (action.getMoveX() == Action::MoveX::LEFT) {
            auto x = object->getX();
            if (x > 0) {
                object->setX(x - 1);
            }
        } else if (action.getMoveX() == Action::MoveX::RIGHT) {
            auto x = object->getX();
            if (x < this->getWidth() - 1) {
                object->setX(x + 1);
            }
        }

        // Y
        if (action.getMoveY() == Action::MoveY::UP) {
            auto y = object->getY();
            if (y < this->getHeight() - 1) {
                object->setY(y + 1);
            }
        } else if (action.getMoveY() == Action::MoveY::DOWN) {
            auto y = object->getY();
            if (y > 0) {
                object->setY(y - 1);
            }
        }
    }
}

unsigned int World::getHeight() const { return this->height; }
unsigned int World::getNHumanActions() const { return this->nHumanActions; }

const std::vector<std::unique_ptr<Object>>& World::getObjects() const { return this->objects; }
SDL_Renderer * World::getRenderer() const { return this->renderer; }
unsigned int World::getTileHeightPix() const { return this->tileHeightPix; }
unsigned int World::getTileWidthPix() const { return this->tileWidthPix; }
unsigned int World::getWidth() const { return this->width; }
unsigned int World::getViewHeight() const { return this->viewHeight; }

bool World::showFov() const { return this->showFovId >= 0; }

SDL_Texture * World::createSolidTexture(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    int pitch = 0;
    void *pixels = NULL;
    SDL_Texture *texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, this->tileWidthPix, this->tileHeightPix);
    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    unsigned long TILE_AREA = this->tileHeightPix * this->tileWidthPix;
    for (unsigned long idx = 0; idx < TILE_AREA; ++idx) {
        Uint8 *base = &((Uint8 *)pixels)[idx * N_COLOR_CHANNELS];
        *(base + 0) = b;
        *(base + 1) = g;
        *(base + 2) = r;
        *(base + 3) = a;
    }
    SDL_UnlockTexture(texture);
    textures.push_back(texture);
    return texture;
}

bool World::findNextObjectInFov(std::vector<std::unique_ptr<Object>>::const_iterator& it, const Object& object, int& dx, int& dy) const {
    // TODO: use quadtree
    auto const end = this->objects.end();
    while (it != end) {
        auto const& otherObject = **it;
        dx = (int)otherObject.getX() - (int)object.getX();
        dy = (int)otherObject.getY() - (int)object.getY();
        int fov = object.getFov();
        if (std::abs(dx) < fov && std::abs(dy) < fov) {
            return true;
        }
        it++;
    }
    return false;
}

std::unique_ptr<WorldView> World::createWorldView(const Object &object) const {
    auto objectViews = std::make_unique<std::vector<std::unique_ptr<ObjectView>>>();
    auto it = this->objects.begin();
    int dx, dy;
    while (this->findNextObjectInFov(it, object, dx, dy)) {
        auto const& otherObject = **it;
        objectViews->push_back(std::make_unique<ObjectView>(
            dx, dy, otherObject.getType()
        ));
        it++;
    }
    return std::make_unique<WorldView>(object.getFov(), object.getFov(), std::move(objectViews));
}

void World::createSingleTextureObject(
    unsigned int x,
    unsigned int y,
    Object::Type type,
    std::unique_ptr<Actor> actor,
    unsigned int fov,
    size_t textureId
) {
    std::unique_ptr<DrawableObject> drawableObject;
    if (this->display) {
        drawableObject = std::make_unique<SingleTextureDrawableObject>(this->textures[textureId]);
    } else {
        drawableObject = std::make_unique<DoNothingDrawableObject>();
    }
    if (actor->takesHumanAction()) {
        this->nHumanActions++;
    }
    auto object = std::make_unique<Object>(x, y, type, std::move(actor), fov, std::move(drawableObject));
    this->objects.push_back(std::move(object));
}

void printHelp() {
    std::cerr <<
        "# CLI Options\n"
        "\n"
        "- `-b`:          (Block) don't block on player input.\n"
        "\n"
        "                 If given, if he player does not give any input until\n"
        "                 before the current frame is over, and empty input is used,\n"
        "                 and the simulation progresses.\n"
        "\n"
        "                 Not setting this option makes the game more Rogue-like.\n"
        "\n"
        "- `-d`:          (Display) turn display off. Might make simulation faster\n"
        "                 or runnable in device without display.\n"
        "\n"
        "                 User input is only available with display.\n"
        "\n"
        "- `-f <double>`: (Fps) limit FPS to <double> FPS.\n"
        "\n"
        "                 If not present, simulation runs as faster as possible.\n"
        "\n"
        "                 Helps humans visualize non-interactive simulations\n"
        "                 that are too fast. E.g. `-f 2.0` limits simulation to 2 FPS.\n"
        "\n"
        "                 You likely don't want this for interactive simulations that\n"
        "                 block on user input (Rogue-like), as this becomes lag.\n"
        "\n"
        "- `-F`:          (Fps) don't print FPS to stdout.\n"
        "\n"
        "- `-h`:          (help) show this help\n"
        "\n"
        "- `-H`:          (Hold key) actions are taken not only when the player clicks\n"
        "                 keys during a frame, but also when keys are being held during\n"
        "                 a frame from the previous frame.\n"
        "\n"
        "                 Makes the game more interactive, and controls less precise.\n"
        "\n"
        "- `-i`:          immediate mode. Progress simulation immediately after any user\n"
        "                 control is given, without waiting for `SPACE`.\n"
        "\n"
        "                 Makes game more interactive, and less precisely controllable.\n"
        "\n"
        "- `-r`:          (Random) set a fixed random seed.\n"
        "\n"
        "                 If given, it is always used across restarts. Otherwise, a new\n"
        "                 seed is chosen for every restart.\n"
        "\n"
        "                 This is the only source of randomness in the whole engine.\n"
        "                 Fixing it to a given value gives reproducible games.\n"
        "\n"
        "- `-v <int>`:    Only show what the int-th player is seeing on screen,\n"
        "                 limited by its field of view.\n"
        "\n"
        "                 You are forced to use this if the world is so large that\n"
        "                 each tile would be less than one pixel wide.\n"
        "\n"
        "                 If the field of view is so large that the tiles are less than\n"
        "                 one pixel wide, then your game simply cannot be visualized.\n"
        "\n"
        "- `-w <int>`:    world width in tiles\n"
        "\n"
        "- `-W <int>`:    window width in pixels. Square windows only for now.\n"
        "                 Must be divisible by the width of the world.\n"
        "\n"
        "# Controls\n"
        "\n"
        "- `q`: quit\n"
        "- `r`: restart from initial state\n"
        "- `UP` / `DOWN` / `LEFT` / `RIGHT` arrow keys: move\n"
        "- `SPACE`: step simulation\n"
        "\n"
        "# Examples\n"
        "\n"
        "## Rogue-like TAS mode\n"
        "\n"
        "    ./prog\n"
        "\n"
        "If a player controller is present,\n"
        "then the world blocks until player makes a move (`SPACE`).\n"
        "\n"
        "By TAS, we mean that each input can be carefully constructed,\n"
        "by parts, and the world only advances when `SPACE` is pressed.\n"
        "in similar fashion to how Tool Assisted Speedruns are developed\n"
        "\n"
        "This mode may be too slow to be fun, but it allows for precise controls.\n"
        "\n"
        "E.g., to move diagonally right up, you do:\n"
        "\n"
        "- `RIGHT` (horizontal direction)\n"
        "- `UP` (vertical direction)\n"
        "- `SPACE`\n"
        "\n"
        "The default for each type of direction is to do nothing.\n"
        "E.g., to just move up:\n"
        "\n"
        "- `UP` (vertical direction)\n"
        "- `SPACE`\n"
        "\n"
        "Since there was no horizontal input, the default of not\n"
        "moving horizontally is used.\n"
        "\n"
        "You can fix some controls half-way. E.g. the following will move up:\n"
        ""
        "\n"
        "- `DOWN`\n"
        "- `UP`, overrides the previous `DOWN`\n"
        "- `SPACE`\n"
        "\n"
        "## Rogue mode\n"
        "\n"
        "    ./prog -i\n"
        "\n"
        "When the player clicks any key, the world updates.\n"
        "\n"
        "## Crypt of the NecroDancer mode\n"
        "\n"
        "   ./prog -H -b -f 2.0 -i\n"
        "\n"
        "World updates even if user does nothing, but only at 2FPS.\n"
        "\n"
        "TODO currently the first input is taken, but that feels sluggish.\n"
        "This is to allow haveing multiple players with the same controls in TAS mode,\n"
        "where the second input starts as soon as the first one is done.\n"
        "\n"
        "## Continuous action game\n"
        "\n"
        "   ./prog -H -b -f 20.0 -i -w 100\n"
        "\n"
        "Same as Crypt of the NecroDancer, but with wide screen, and faster FPS.\n"
        "\n"
        "Most engines will implement this mode with floating point positions.\n"
        "\n"
    ;
}

bool activatetKey(
    SDL_Scancode scancode,
    const Uint8 *keyboardState,
    Uint8 *lastKeyboardState,
    bool holdKey
) {
    return
        keyboardState[scancode] &&
        (
            holdKey
            || !lastKeyboardState[scancode]
        );
}

int main(int argc, char **argv) {
    SDL_Event event;
    std::unique_ptr<World> world;
    bool
        blockOnPlayer = true,
        display = true,
        fixedRandomSeed = false,
        holdKey = false,
        immediateAction = false,
        limitFps = false,
        printFps = true
    ;
    double
        targetFps = 1.0,
        last_time;
    ;
    int showFovId = -1;
    unsigned int
        randomSeed,
        ticks = 0,
        width = 100,
        windowWidthPix = 500
    ;

    // Treat CLI arguments.
    for (decltype(argc) i = 0; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (std::strcmp(argv[i], "-b") == 0) {
                blockOnPlayer = !blockOnPlayer;
            } else if (std::strcmp(argv[i], "-d") == 0) {
                display = !display;
            } else if (std::strcmp(argv[i], "-F") == 0) {
                printFps = !printFps;
            } else if (std::strcmp(argv[i], "-f") == 0) {
                limitFps = !limitFps;
                targetFps = std::strtod(argv[i + 1], NULL);
            } else if (std::strcmp(argv[i], "-h") == 0) {
                printHelp();
                std::exit(EXIT_SUCCESS);
            } else if (std::strcmp(argv[i], "-H") == 0) {
                holdKey = !holdKey;
            } else if (std::strcmp(argv[i], "-i") == 0) {
                immediateAction = !immediateAction;
            } else if (std::strcmp(argv[i], "-r") == 0) {
                randomSeed = std::strtol(argv[i + 1], NULL, 10);
                fixedRandomSeed = true;
            } else if (std::strcmp(argv[i], "-v") == 0) {
                showFovId = std::strtol(argv[i + 1], NULL, 10);
            } else if (std::strcmp(argv[i], "-w") == 0) {
                width = std::strtol(argv[i + 1], NULL, 10);
            } else if (std::strcmp(argv[i], "-W") == 0) {
                windowWidthPix = std::strtol(argv[i + 1], NULL, 10);
            } else {
                printHelp();
                std::exit(EXIT_FAILURE);
            }
        }
    }
    auto windowHeightPix = windowWidthPix;
    auto targetSpf = 1.0 / targetFps;
    auto height = width;

    world = std::make_unique<World>(
        width,
        height,
        display,
        windowWidthPix,
        windowHeightPix,
        showFovId
    );
main_loop:
    if (printFps) {
        common_fps_init();
    }
    last_time = common_get_secs();

    // Keyboard state.
    int numkeys;
    const Uint8 * keyboardState = SDL_GetKeyboardState(&numkeys);
    size_t keyboardStateSize = numkeys * sizeof(*keyboardState);
    auto lastKeyboardState = std::make_unique<Uint8[]>(keyboardStateSize);

    // Human actions.
    std::vector<std::unique_ptr<Action>> humanActions;
    for (decltype(world->getNHumanActions()) i = 0; i < world->getNHumanActions(); ++i) {
        humanActions.push_back(std::make_unique<Action>());
    }

    // Randomness.
    if (!fixedRandomSeed) {
        randomSeed = std::time(NULL);
    }
    std::srand(randomSeed);

    while (1) {
        world->draw();
        double slack;
        double nextTarget = last_time + targetSpf;
        decltype(humanActions.size()) humanActionIdx = 0;
        bool needMoreHumanActions = humanActionIdx < world->getNHumanActions();
        for (auto &action : humanActions) {
            action->reset();
        }
        do {
            if (display) {
                do {
                    std::memcpy(lastKeyboardState.get(), keyboardState, keyboardStateSize);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            goto quit;
                        }
                    }
                    // Global controls.
                    if (activatetKey(SDL_SCANCODE_Q, keyboardState, lastKeyboardState.get(), holdKey)) {
                        goto quit;
                    }
                    if (activatetKey(SDL_SCANCODE_R, keyboardState, lastKeyboardState.get(), holdKey)) {
                        world->reset();
                        goto main_loop;
                    }

                    // Player controls.
                    if (needMoreHumanActions) {
                        bool addHumanAction = false;
                        if (activatetKey(SDL_SCANCODE_LEFT, keyboardState, lastKeyboardState.get(), holdKey)) {
                            humanActions[humanActionIdx]->setMoveX(Action::MoveX::LEFT);
                            if (immediateAction) {
                                addHumanAction = true;
                            }
                        }
                        if (activatetKey(SDL_SCANCODE_RIGHT, keyboardState, lastKeyboardState.get(), holdKey)) {
                            humanActions[humanActionIdx]->setMoveX(Action::MoveX::RIGHT);
                            if (immediateAction) {
                                addHumanAction = true;
                            }
                        }
                        if (activatetKey(SDL_SCANCODE_UP, keyboardState, lastKeyboardState.get(), holdKey)) {
                            humanActions[humanActionIdx]->setMoveY(Action::MoveY::UP);
                            if (immediateAction) {
                                addHumanAction = true;
                            }
                        }
                        if (activatetKey(SDL_SCANCODE_DOWN, keyboardState, lastKeyboardState.get(), holdKey)) {
                            humanActions[humanActionIdx]->setMoveY(Action::MoveY::DOWN);
                            if (immediateAction) {
                                addHumanAction = true;
                            }
                        }
                        if (activatetKey(SDL_SCANCODE_SPACE, keyboardState, lastKeyboardState.get(), holdKey)) {
                            addHumanAction = true;
                        }
                        if (addHumanAction) {
                            humanActionIdx++;
                            needMoreHumanActions = humanActionIdx < world->getNHumanActions();
                        }
                    }
                } while (blockOnPlayer && needMoreHumanActions);
            }
            slack = nextTarget - common_get_secs();
        } while (limitFps && slack > 0.0);
        last_time = common_get_secs();
        world->update(humanActions);
        ticks++;
        if (printFps) {
            common_fps_update_and_print();
        }
    }
quit:
    return EXIT_SUCCESS;
}
