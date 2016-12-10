/*
2D tile-based game world, made for programmable AIs to compete.

https://en.wikipedia.org/wiki/Tile-based_video_game

TODO:

-   separate objects from controllers. Give controllers observed state instead of full world.
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
*/

#include "common.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

const unsigned int COLOR_MAX = 255;
const unsigned int N_COLOR_CHANNELS = 4;

class World;

class Action {
    public:
        enum DirectionX {
            X_NONE,
            X_LEFT,
            X_RIGHT
        };
        enum DirectionY {
            Y_NONE,
            Y_DOWN,
            Y_UP
        };
        Action() { this->reset(); }
        Action(DirectionX directionX, DirectionY directionY) :
            directionX(directionX), directionY(directionY) {}
        DirectionX getDirectionX() const { return this->directionX; }
        DirectionY getDirectionY() const { return this->directionY; }
        void reset() {
            this->directionX = X_NONE;
            this->directionY = Y_NONE;
        };
        void setDirectionX(DirectionX x) { this->directionX = x; }
        void setDirectionY(DirectionY y) { this->directionY = y; }
    private:
        DirectionX directionX;
        DirectionY directionY;
};

class Object {
    public:
        Object();
        virtual ~Object();
        Object(unsigned int x, unsigned int y);
        virtual Action act(World *world) = 0;
        unsigned int getX() const;
        unsigned int getY() const;
        virtual bool takesHumanAction() const;
        void setX(unsigned int x);
        void setY(unsigned int y);
    protected:
        unsigned int x;
        unsigned int y;
};

class DrawableObject {
    public:
        DrawableObject(Object *object) : object(object){}
        virtual ~DrawableObject(){}
        virtual void draw(const World * world) const = 0;
    protected:
        Object *object;
};

class WorldView {
    public:
        WorldView(unsigned int width, unsigned int height, std::unique_ptr<std::vector<std::unique_ptr<Object>>> objects) :
            width(width), height(height), objects(std::move(objects)) {}
        unsigned int getHeight() const { return this->height; }
        unsigned int getWidth() const { return this->width; }
    private:
        unsigned int width;
        unsigned int height;
        std::unique_ptr<std::vector<std::unique_ptr<Object>>> objects;
};

class World {
    public:
        World(
            unsigned int width,
            unsigned int height,
            bool display,
            unsigned int windowWidthPix,
            unsigned int windowHeightPix,
            unsigned int tileWidthPix,
            unsigned int tileHeightPix
        );
        ~World();
        void addObject(std::unique_ptr<Object> object);
        void draw() const;
        /// Collect desired actions from all objects, and resolve them
        unsigned int getHeight() const;
        unsigned int getNHumanActions() const;
        const std::vector<std::unique_ptr<Object>>& getObjects() const;
        SDL_Renderer * getRenderer() const;
        unsigned int getTileWidthPix() const;
        unsigned int getTileHeightPix() const;
        unsigned int getWidth() const;
        void initPhysics();
        void resetPhysics();
        /// to the next world state. E.g.: what happens if two objects
        /// want to move to the same place next tick? Or if an object
        /// wants to move into a wall?
        void update(const std::vector<std::unique_ptr<Action>> &humanActions);
    private:
        unsigned int width;
        unsigned int height;
        unsigned int nHumanActions;
        unsigned int windowWidthPix;
        unsigned int windowHeightPix;
        unsigned int tileWidthPix;
        unsigned int tileHeightPix;
        bool display;
        SDL_Renderer *renderer;
        SDL_Window *window;
        std::vector<std::unique_ptr<Object>> objects;
        std::vector<std::unique_ptr<DrawableObject>> drawableObjects;
        std::vector<SDL_Texture *> textures;

        SDL_Texture * createSolidTexture(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
        std::unique_ptr<WorldView> createWorldView(const std::unique_ptr<Object> &object) const;
};

Object::Object(){}
Object::~Object(){}
Object::Object(unsigned int x, unsigned int y) : x(x), y(y) {}
unsigned int Object::getX() const { return this->x; }
unsigned int Object::getY() const { return this->y; }
bool Object::takesHumanAction() const { return false; }
void Object::setX(unsigned int x) { this->x = x; }
void Object::setY(unsigned int y) { this->y = y; }

class MoveUpObject : public Object {
    public:
        MoveUpObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            return Action(Action::DirectionX::X_NONE, Action::DirectionY::Y_UP);
        };
};

class MoveDownObject : public Object {
    public:
        MoveDownObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            return Action(Action::DirectionX::X_NONE, Action::DirectionY::Y_DOWN);
        };
};

class MoveRandomObject : public Object {
    public:
        MoveRandomObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            Action::DirectionX x;
            Action::DirectionY y;
            switch (rand() % 3) {
                case 0:
                    x = Action::DirectionX::X_LEFT;
                break;
                case 1:
                    x = Action::DirectionX::X_NONE;
                break;
                case 2:
                    x = Action::DirectionX::X_RIGHT;
                break;
            }
            switch (rand() % 3) {
                case 0:
                    y = Action::DirectionY::Y_DOWN;
                break;
                case 1:
                    y = Action::DirectionY::Y_NONE;
                break;
                case 2:
                    y = Action::DirectionY::Y_UP;
                break;
            }
            return Action(x, y);
        };
};

class HumanPlayerObject : public Object {
    public:
        HumanPlayerObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            return Action();
        };
        virtual bool takesHumanAction() const { return true; }
};

/// Dumb: no understanding of walls.
class FollowPlayerObject : public Object {
    public:
        FollowPlayerObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            Action a;
            for (auto const& object : world->getObjects()) {
                if (typeid(*object) == typeid(HumanPlayerObject)) {
                    if (this->getX() < object->getX()) {
                        a.setDirectionX(Action::DirectionX::X_RIGHT);
                    } else if (this->getX() > object->getX()) {
                        a.setDirectionX(Action::DirectionX::X_LEFT);
                    }
                    if (this->getY() < object->getY()) {
                        a.setDirectionY(Action::DirectionY::Y_UP);
                    } else if (this->getY() > object->getY()) {
                        a.setDirectionY(Action::DirectionY::Y_DOWN);
                    }
                    break;
                }
            }
            return a;
        };
};

/// Dumb: no understanding of walls.
class FleePlayerObject : public Object {
    public:
        FleePlayerObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            Action a;
            for (auto const& object : world->getObjects()) {
                if (typeid(*object) == typeid(HumanPlayerObject)) {
                    if (this->getX() < object->getX()) {
                        a.setDirectionX(Action::DirectionX::X_LEFT);
                    } else {
                        a.setDirectionX(Action::DirectionX::X_RIGHT);
                    }
                    if (this->getY() < object->getY()) {
                        a.setDirectionY(Action::DirectionY::Y_DOWN);
                    } else {
                        a.setDirectionY(Action::DirectionY::Y_UP);
                    }
                    break;
                }
            }
            return a;
        };
};

class SingleTextureDrawableObject : public DrawableObject {
    public:
        SingleTextureDrawableObject(Object *object, SDL_Texture *texture) :
            DrawableObject(object), texture(texture) {}
        virtual void draw(const World * world) const {
            SDL_Rect rect;
            rect.x = this->object->getX() * world->getTileWidthPix();
            rect.y = (world->getHeight() - this->object->getY() - 1) * world->getTileHeightPix();
            rect.w = world->getTileWidthPix();
            rect.h = world->getTileHeightPix();
            SDL_RenderCopy(world->getRenderer(), this->texture, NULL, &rect);
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
    unsigned int tileWidthPix,
    unsigned int tileHeightPix
) :
    width(width),
    height(height),
    display(display),
    windowWidthPix(windowWidthPix),
    windowHeightPix(windowHeightPix),
    tileWidthPix(tileWidthPix),
    tileHeightPix(tileHeightPix)
{
    this->window = NULL;
    this->renderer = NULL;
    if (this->display) {
        // Window setup.
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(this->windowWidthPix, this->windowHeightPix, 0, &this->window, &this->renderer);
        SDL_SetWindowTitle(window, __FILE__);
        createSolidTexture(COLOR_MAX, 0, 0, 0);
        createSolidTexture(0, COLOR_MAX, 0, 0);
        createSolidTexture(0, 0, COLOR_MAX, 0);
        createSolidTexture(COLOR_MAX, COLOR_MAX, 0, 0);
        createSolidTexture(COLOR_MAX, 0, COLOR_MAX, 0);
        createSolidTexture(0, COLOR_MAX, COLOR_MAX, 0);
        createSolidTexture(COLOR_MAX, COLOR_MAX, COLOR_MAX, 0);
        createSolidTexture(COLOR_MAX / 2, COLOR_MAX / 2, COLOR_MAX / 2, 0);
    }
    this->initPhysics();
}

World::~World() {
    if (this->display) {
        for (auto& texture : this->textures) {
            SDL_DestroyTexture(texture);
        }
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }
}

void World::draw() const {
    if (this->display) {
        Uint8 *base;
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
        SDL_RenderClear(this->renderer);
        for (auto const& object : this->drawableObjects) {
            object->draw(this);
        }
        SDL_RenderPresent(this->renderer);
    }
}

void World::addObject(std::unique_ptr<Object> object) {
    if (object->takesHumanAction()) {
        this->nHumanActions++;
    }
    this->objects.push_back(std::move(object));
}

void World::initPhysics() {
    this->nHumanActions = 0;
    for (unsigned int y = 0; y < this->height; ++y) {
        for (unsigned int x = 0; x < this->width; ++x) {
            unsigned int sum = x + y;
            if (sum & 1) {
                auto object = std::unique_ptr<Object>(new MoveUpObject(x, y));
                if (display) {
                    this->drawableObjects.push_back(std::unique_ptr<DrawableObject>(
                        new SingleTextureDrawableObject(object.get(), this->textures[0])
                    ));
                }
                this->addObject(std::move(object));
            } else if (sum % 3 == 0) {
                auto object = std::unique_ptr<Object>(new MoveDownObject(x, y));
                if (display) {
                    this->drawableObjects.push_back(std::unique_ptr<DrawableObject>(
                        new SingleTextureDrawableObject(object.get(), this->textures[1])
                    ));
                }
                this->addObject(std::move(object));
            }
        }
    }
	{
		auto object = std::unique_ptr<Object>(new HumanPlayerObject(this->getWidth() / 2, this->getHeight() / 2));
		if (display) {
			drawableObjects.push_back(std::unique_ptr<DrawableObject>(
				new SingleTextureDrawableObject(object.get(), this->textures[2])
			));
		}
		this->addObject(std::move(object));
	}
	// Player 2.
	//{
        //auto object = std::unique_ptr<Object>(new HumanPlayerObject(this->getWidth() / 2, this->getHeight() / 2 + 1));
        //if (display) {
            //drawableObjects.push_back(std::unique_ptr<DrawableObject>(
                //new SingleTextureDrawableObject(object.get(), this->textures[3])
            //));
        //}
        //this->addObject(std::move(object));
	//}
	{
		auto object = std::unique_ptr<Object>(new MoveRandomObject(this->getWidth() / 4, this->getHeight() / 4));
		if (display) {
			drawableObjects.push_back(std::unique_ptr<DrawableObject>(
				new SingleTextureDrawableObject(object.get(), this->textures[4])
			));
		}
		this->addObject(std::move(object));
	}
	{
		auto object = std::unique_ptr<Object>(new FollowPlayerObject(3 * this->getWidth() / 4, 3 * this->getHeight() / 4));
		if (display) {
			drawableObjects.push_back(std::unique_ptr<DrawableObject>(
				new SingleTextureDrawableObject(object.get(), this->textures[5])
			));
		}
		this->addObject(std::move(object));
	}
	{
		auto object = std::unique_ptr<Object>(new FleePlayerObject(this->getWidth() / 4, 3 * this->getHeight() / 4));
		if (display) {
			drawableObjects.push_back(std::unique_ptr<DrawableObject>(
				new SingleTextureDrawableObject(object.get(), this->textures[6])
			));
		}
		this->addObject(std::move(object));
	}

}

void World::resetPhysics() {
    this->objects.clear();
    this->drawableObjects.clear();
    this->initPhysics();
}

void World::update(const std::vector<std::unique_ptr<Action>> &humanActions) {
    auto humanActionsIt = humanActions.begin();
    for (auto &object : this->objects) {
        auto worldView = createWorldView(object);

        Action a;
        if (object->takesHumanAction()) {
            a = **humanActionsIt;
            humanActionsIt++;
        } else {
            a = object->act(this);
        }

        // X
        if (a.getDirectionX() == Action::DirectionX::X_LEFT) {
            auto x = object->getX();
            if (x > 0) {
                object->setX(x - 1);
            }
        } else if (a.getDirectionX() == Action::DirectionX::X_RIGHT) {
            auto x = object->getX();
            if (x < this->getWidth() - 1) {
                object->setX(x + 1);
            }
        }

        // Y
        if (a.getDirectionY() == Action::DirectionY::Y_UP) {
            auto y = object->getY();
            if (y < this->getHeight() - 1) {
                object->setY(y + 1);
            }
        } else if (a.getDirectionY() == Action::DirectionY::Y_DOWN) {
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

// TODO.
std::unique_ptr<WorldView> World::createWorldView(const std::unique_ptr<Object> &object) const {
    auto objects = std::unique_ptr<std::vector<std::unique_ptr<Object>>>();
    return std::unique_ptr<WorldView>(new WorldView(1, 2, std::move(objects)));
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
        "- `-w <int>`:    world width in tiles\n"
        "\n"
        "- `-W <int>`:    window width in pixels. Square windows only for now.\n"
        "                 Must be divisible by the width of the world.\n"
        "\n"
        "# Controls\n"
        "\n"
        "- `ESC`: quit\n"
        "- `r`:   restart from initial state\n"
        "- `Y_UP` / `Y_DOWN` / `LEFT` / `RIGHT` arrow keys: move\n"
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
        holdKey = false,
        immediateAction = false,
        limitFps = false,
        fixedRandomSeed = false
    ;
    double
        targetFps = 1.0,
        last_time;
    ;
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
    auto tileWidthPix = windowWidthPix / width;
    auto tileHeightPix = windowHeightPix / height;

    world = std::unique_ptr<World>(new World(
        width,
        height,
        display,
        windowWidthPix,
        windowHeightPix,
        tileWidthPix,
        tileHeightPix
    ));
main_loop:

    common_fps_init();
    last_time = common_get_secs();

    // Keyboard state.
    int numkeys;
    const Uint8 * keyboardState = SDL_GetKeyboardState(&numkeys);
    size_t keyboardStateSize = numkeys * sizeof(*keyboardState);
    auto lastKeyboardState = std::unique_ptr<Uint8[]>(new Uint8[keyboardStateSize]);

    // Human actions.
    std::vector<std::unique_ptr<Action>> humanActions;
    for (decltype(world->getNHumanActions()) i = 0; i < world->getNHumanActions(); ++i) {
        humanActions.push_back(std::unique_ptr<Action>(new Action()));
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
                    bool addHumanAction = false;
                    // Global controls.
                    if (activatetKey(SDL_SCANCODE_ESCAPE, keyboardState, lastKeyboardState.get(), holdKey)) {
                        goto quit;
                    }
                    if (activatetKey(SDL_SCANCODE_R, keyboardState, lastKeyboardState.get(), holdKey)) {
                        world->resetPhysics();
                        goto main_loop;
                    }

                    // Player controls.
                    if (activatetKey(SDL_SCANCODE_LEFT, keyboardState, lastKeyboardState.get(), holdKey)) {
                        humanActions[humanActionIdx]->setDirectionX(Action::DirectionX::X_LEFT);
                        if (immediateAction) {
                            addHumanAction = true;
                        }
                    }
                    if (activatetKey(SDL_SCANCODE_RIGHT, keyboardState, lastKeyboardState.get(), holdKey)) {
                        humanActions[humanActionIdx]->setDirectionX(Action::DirectionX::X_RIGHT);
                        if (immediateAction) {
                            addHumanAction = true;
                        }
                    }
                    if (activatetKey(SDL_SCANCODE_UP, keyboardState, lastKeyboardState.get(), holdKey)) {
                        humanActions[humanActionIdx]->setDirectionY(Action::DirectionY::Y_UP);
                        if (immediateAction) {
                            addHumanAction = true;
                        }
                    }
                    if (activatetKey(SDL_SCANCODE_DOWN, keyboardState, lastKeyboardState.get(), holdKey)) {
                        humanActions[humanActionIdx]->setDirectionY(Action::DirectionY::Y_DOWN);
                        if (immediateAction) {
                            addHumanAction = true;
                        }
                    }
                    if (activatetKey(SDL_SCANCODE_SPACE, keyboardState, lastKeyboardState.get(), holdKey)) {
                        addHumanAction = true;
                    }

                    if (addHumanAction) {
                        humanActionIdx++;
                    }
                } while (blockOnPlayer && humanActionIdx < world->getNHumanActions());
            }
            slack = nextTarget - common_get_secs();
        } while (limitFps && slack > 0.0);
        last_time = common_get_secs();
        world->update(humanActions);
        ticks++;
        common_fps_update_and_print();
    }
quit:
    return EXIT_SUCCESS;
}
