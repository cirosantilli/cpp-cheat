/*
2D tile-based game world, made for programmable AIs to compete.

https://en.wikipedia.org/wiki/Tile-based_video_game

TODO:

-   separate objects from controllers. Give controllers observed state instead of full world.
-   hold mode: no need to press keys, if you hold them input is taken for every frame
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

#include <cstring>
#include <iostream>
#include <memory>
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
        Action() : directionX(X_NONE), directionY(Y_NONE) {}
        Action(DirectionX directionX, DirectionY directionY) :
            directionX(directionX), directionY(directionY) {}
        DirectionX getDirectionX() const { return this->directionX; }
        DirectionY getDirectionY() const { return this->directionY; }
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

class HumanPlayerObject : public Object {
    public:
        HumanPlayerObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual Action act(World *world) {
            return Action();
        };
        virtual bool takesHumanAction() const { return true; }
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
        createSolidTexture(COLOR_MAX, 0, COLOR_MAX, 0);
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
	{
		//auto object = std::unique_ptr<Object>(new HumanPlayerObject(this->getWidth() / 2, this->getHeight() / 2 + 1));
		//if (display) {
			//drawableObjects.push_back(std::unique_ptr<DrawableObject>(
				//new SingleTextureDrawableObject(object.get(), this->textures[3])
			//));
		//}
		//this->addObject(std::move(object));
	}
}

void World::resetPhysics() {
    this->objects.clear();
    this->drawableObjects.clear();
    this->initPhysics();
}

void World::update(const std::vector<std::unique_ptr<Action>> &humanActions) {
    auto humanActionsIt = humanActions.begin();
    for (auto& object : this->objects) {
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

void printHelp() {
    std::cerr <<
        "# CLI Options\n"
        "\n"
        "- `-b`:          don't block on player input.\n"
        "\n"
        "                 If given, if he player does not give any input until\n"
        "                 before the current frame is over, and empty input is used,\n"
        "                 and the simulation progresses.\n"
        "\n"
        "                 Not setting this option makes the game more Rogue-like.\n"
        "\n"
        "- `-d`:          turn display off. Might make simulation faster\n"
        "                 or runnable in device without display.\n"
        "\n"
        "                 User input is only available with display.\n"
        "\n"
        "- `-f <double>`: limit FPS to <double> FPS.\n"
        "\n"
        "                 If not present, simulation runs as faster as possible.\n"
        "\n"
        "                 Helps humans visualize non-interactive simulations\n"
        "                 that are too fast. E.g. `-f 2.0` limits simulation to 2 FPS.\n"
        "\n"
        "                 You likely don't want this for interactive simulations that\n"
        "                 block on user input (Rogue-like), as this becomes lag.\n"
        "\n"
        "- `-h`:          show this help\n"
        "\n"
        "- `-i`:          immediate mode. Progress simulation immediately after any user\n"
        "                 control is given, without waiting for `SPACE`.\n"
        "\n"
        "                 Makes game more interactive, and less precisely controllable.\n"
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
        "## Rogue mode TODO\n"
        "\n"
        "## Crypt of the NecroDancer mode TODO\n"
        "\n"
    ;
}

int main(int argc, char **argv) {
    SDL_Event event;
    std::unique_ptr<World> world;
    bool
        display = true,
        limitFps = false,
        blockOnPlayer = true,
        immediateAction = false
    ;
    double
        targetFps = 1.0,
        last_time;
    ;
    unsigned int
        width = 100,
        ticks = 0,
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
            } else if (std::strcmp(argv[i], "-i") == 0) {
                immediateAction = !immediateAction;
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
    auto action = std::unique_ptr<Action>(new Action());
    while (1) {
        world->draw();
        double slack;
        double nextTarget = last_time + targetSpf;
        std::vector<std::unique_ptr<Action>> humanActions;
        do {
            if (display) {
                do {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            goto quit;
                        } else if (event.type == SDL_KEYDOWN) {
                            bool addHumanAction = false;
                            switch(event.key.keysym.sym) {
                                // Global controls.
                                case SDLK_ESCAPE:
                                    goto quit;
                                break;
                                case SDLK_r:
                                    world->resetPhysics();
                                    goto main_loop;
                                break;

                                // Player controls.
                                case SDLK_LEFT:
                                    action->setDirectionX(Action::DirectionX::X_LEFT);
                                    if (immediateAction)
                                        addHumanAction = true;
                                break;
                                case SDLK_RIGHT:
                                    action->setDirectionX(Action::DirectionX::X_RIGHT);
                                    if (immediateAction)
                                        addHumanAction = true;
                                break;
                                case SDLK_DOWN:
                                    action->setDirectionY(Action::DirectionY::Y_DOWN);
                                    if (immediateAction)
                                        addHumanAction = true;
                                break;
                                case SDLK_UP:
                                    action->setDirectionY(Action::DirectionY::Y_UP);
                                    if (immediateAction)
                                        addHumanAction = true;
                                break;
                                case SDLK_SPACE:
                                    addHumanAction = true;
                                break;

                            }
                            if (addHumanAction && humanActions.size() < world->getNHumanActions()) {
                                humanActions.push_back(std::move(action));
                                action = std::unique_ptr<Action>(new Action());
                            }
                        }
                    }
                } while (blockOnPlayer && humanActions.size() < world->getNHumanActions());
            }
            slack = nextTarget - common_get_secs();
        } while (limitFps && slack > 0.0);
        last_time = common_get_secs();
        // Fill in dummy missing actions that player didn't
        // enter in time in non-blocking mode.
        for (
            decltype(world->getNHumanActions()) nHumanActions = 0;
            nHumanActions < world->getNHumanActions();
            ++nHumanActions
        ) {
            humanActions.push_back(std::unique_ptr<Action>(new Action()));
        }
        world->update(humanActions);
        ticks++;
        common_fps_update_and_print();
    }
quit:
    return EXIT_SUCCESS;
}
