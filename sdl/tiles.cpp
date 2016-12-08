/*
2D tile-based game world, made for programmable AIs to compete.

https://en.wikipedia.org/wiki/Tile-based_video_game
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
        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        Action(Direction direction) : direction(direction) {}
        Direction getDirection() { return this->direction; }
    private:
        Direction direction;
};

class Object {
    public:
        Object();
        virtual ~Object();
        Object(unsigned int x, unsigned int y);
        virtual Action act(World *world) = 0;
        unsigned int getX() const;
        unsigned int getY() const;
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
        void draw() const;
        /// Collect desired actions from all objects, and resolve them
        unsigned int getHeight() const;
        SDL_Renderer * getRenderer() const;
        unsigned int getTileWidthPix() const;
        unsigned int getTileHeightPix() const;
        unsigned int getWidth() const;
        void initPhysics();
        void resetPhysics();
        /// to the next world state. E.g.: what happens if two objects
        /// want to move to the same place next tick? Or if an object
        /// wants to move into a wall?
        void update();
    private:
        unsigned int width;
        unsigned int height;
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
void Object::setX(unsigned int x) { this->x = x; }
void Object::setY(unsigned int y) { this->y = y; }

class MoveUpObject : public Object {
    public:
        MoveUpObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual ~MoveUpObject(){}
        virtual Action act(World *world) {
            return Action(Action::Direction::UP);
        };
};

class MoveDownObject : public Object {
    public:
        MoveDownObject(unsigned int x, unsigned int y) : Object(x, y) {}
        virtual ~MoveDownObject(){}
        virtual Action act(World *world) {
            return Action(Action::Direction::DOWN);
        };
};

class SingleTextureDrawableObject : public DrawableObject {
    public:
        SingleTextureDrawableObject(Object *object, SDL_Texture *texture) :
            DrawableObject(object), texture(texture) {}
        virtual void draw(const World * world) const {
            SDL_Rect rect;
            rect.x = this->object->getX() * world->getTileWidthPix();
            rect.y = this->object->getY() * world->getTileHeightPix();
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
        createSolidTexture(0, 0, COLOR_MAX, 0);
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

void World::initPhysics() {
    for (unsigned int y = 0; y < this->height; ++y) {
        for (unsigned int x = 0; x < this->width; ++x) {
            unsigned int sum = x + y;
            if (sum & 1) {
                auto object = std::unique_ptr<Object>(new MoveUpObject(x, y));
                if (display) {
                    drawableObjects.push_back(std::unique_ptr<DrawableObject>(
                        new SingleTextureDrawableObject(object.get(), this->textures[0])
                    ));
                }
                objects.push_back(std::move(object));
            } else if (sum % 3 == 0) {
                auto object = std::unique_ptr<Object>(new MoveDownObject(x, y));
                if (display) {
                    drawableObjects.push_back(std::unique_ptr<DrawableObject>(
                        new SingleTextureDrawableObject(object.get(), this->textures[1])
                    ));
                }
                objects.push_back(std::move(object));
            }
        }
    }
}

void World::resetPhysics() {
    this->objects.clear();
    this->drawableObjects.clear();
    this->initPhysics();
}

void World::update() {
    for (auto& object : this->objects) {
        Action a = object->act(this);
        if (a.getDirection() == Action::Direction::UP) {
            auto y = object->getY();
            if (y < this->getHeight() - 1) {
                object->setY(y + 1);
            }
        } else if (a.getDirection() == Action::Direction::DOWN) {
            auto y = object->getY();
            if (y > 0) {
                object->setY(y - 1);
            }
        }
    }
}

unsigned int World::getHeight() const { return this->height; }
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

int main(int argc, char **argv) {
    SDL_Event event;
    std::unique_ptr<World> world;
    bool
        display = true,
        limitFps = false
    ;
    double
        targetFps = 1.0,
        last_time;
    ;
    unsigned int
        width = 100,
        height = width,
        ticks = 0,
        tileWidthPix = 5,
        tileHeightPix = tileWidthPix,
        windowWidthPix = width * tileWidthPix,
        windowHeightPix = height * tileHeightPix
    ;

    // Treat CLI arguments.
    while (argc > 1) {
        argc--;
        if (argv[argc][0] == '-') {
            if (std::strcmp(argv[argc], "-d") == 0) {
                display = !display;
            } else if (std::strcmp(argv[argc], "-f") == 0) {
                limitFps = !limitFps;
                targetFps = std::strtod(argv[argc + 1], NULL);
            } else if (std::strcmp(argv[argc], "-h") == 0) {
                std::cerr <<
                    "# CLI Options\n"
                    "\n"
                    "- `-d`:          turn display off. Might make simulation faster\n"
                    "                 or runnable in device without display.\n"
                    "\n"
                    "- `-f <double>`: limit FPS to <double> FPS. Helps humans visualize\n"
                    "                 what is going on if simulation is too fast. E.g.\n"
                    "                 `-f 2.0` limits simulation to 2 FPS.\n"
                    "\n"
                    "# Controls\n"
                    "\n"
                    "- `ESC`: quit\n"
                    "- `r`:   restart from initial state\n"
                ;
                std::exit(EXIT_SUCCESS);
            }
        }
    }
    auto targetSpf = 1.0 / targetFps;

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
    while (1) {
        world->draw();
        double slack;
        double nextTarget = last_time + targetSpf;
        do {
            if (display) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        goto quit;
                    } else if (event.type == SDL_KEYDOWN) {
                        switch(event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                goto quit;
                            break;
                            case SDLK_r:
                                world->resetPhysics();
                                goto main_loop;
                            break;
                        }
                    }
                }
            }
            slack = nextTarget - common_get_secs();
        } while (limitFps && slack > 0.0);
        last_time = common_get_secs();
        world->update();
        ticks++;
        common_fps_update_and_print();
    }
quit:
    return EXIT_SUCCESS;
}
