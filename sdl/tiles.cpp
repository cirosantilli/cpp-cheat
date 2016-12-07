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
        Object(){}
        Object(World *world, unsigned int x, unsigned int y);
        virtual void draw(SDL_Renderer *renderer) const = 0;
        virtual Action act() = 0;
        unsigned int getX() const;
        unsigned int getY() const;
        void setX(unsigned int x);
        void setY(unsigned int y);
    protected:
        unsigned int x;
        unsigned int y;
        World *world;
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
        /// to the next world state. E.g.: what happens if two objects
        /// want to move to the same place next tick? Or if an object
        /// wants to move into a wall?
        void update();
        unsigned int getHeight() const;
        unsigned int getWidth() const;
        unsigned int getTileWidthPix() const;
        unsigned int getTileHeightPix() const;
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
        std::vector<SDL_Texture *> textures;
        SDL_Texture * createSolidTexture(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
};

Object::Object(World *world, unsigned int x, unsigned int y) :
        world(world), x(x), y(y) {}

unsigned int Object::getX() const { return this->x; }
unsigned int Object::getY() const { return this->y; }
void Object::setX(unsigned int x) { this->x = x; }
void Object::setY(unsigned int y) { this->y = y; }

class SingleTextureDrawableObject : public virtual Object {
    public:
        SingleTextureDrawableObject(SDL_Texture *texture) :
            texture(texture) {
        }
        virtual void draw(SDL_Renderer *renderer) const {
            SDL_Rect rect;
            rect.x = this->x * this->world->getTileWidthPix();
            rect.y = this->y * this->world->getTileHeightPix();
            rect.w = this->world->getTileWidthPix();
            rect.h = this->world->getTileHeightPix();
            SDL_RenderCopy(renderer, this->texture, NULL, &rect);
        }
    private:
        /// Pointer to texture shared across all objects that look the same.
        SDL_Texture * const texture;
};

class MoveUpActableObject : public virtual Object {
    public:
        MoveUpActableObject(){}
        virtual Action act() {
            return Action(Action::Direction::UP);
        };
};

class MoveDownActableObject : public virtual Object {
    public:
        MoveDownActableObject(){}
        virtual Action act() {
            return Action(Action::Direction::DOWN);
        };
};

class SingleTextureMoveUpObject : public SingleTextureDrawableObject, public MoveUpActableObject {
    public:
        SingleTextureMoveUpObject(World *world, unsigned int x, unsigned int y, SDL_Texture *texture) :
            Object(world, x, y),
            SingleTextureDrawableObject(texture)
        {}
};

class SingleTextureMoveDownObject : public SingleTextureDrawableObject, public MoveDownActableObject {
    public:
        SingleTextureMoveDownObject(World *world, unsigned int x, unsigned int y, SDL_Texture *texture) :
            Object(world, x, y),
            SingleTextureDrawableObject(texture)
        {}
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
    SDL_Texture
        *redTexture = NULL,
        *blueTexture = NULL
    ;
    if (this->display) {
        // Window setup.
        SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(this->windowWidthPix, this->windowHeightPix, 0, &this->window, &this->renderer);
        SDL_SetWindowTitle(window, __FILE__);

        // Initialize textures to be reused across objects..
        redTexture = createSolidTexture(COLOR_MAX, 0, 0, 0);
        blueTexture = createSolidTexture(0, 0, COLOR_MAX, 0);
    }

    // Initialize objects in world. TODO also load serialization.
    for (unsigned int y = 0; y < this->height; ++y) {
        for (unsigned int x = 0; x < this->width; ++x) {
            unsigned int sum = x + y;
            if (sum & 1) {
                objects.push_back(std::unique_ptr<Object>(new SingleTextureMoveUpObject(this, x, y, redTexture)));
            } else if (sum % 3 == 0) {
                objects.push_back(std::unique_ptr<Object>(new SingleTextureMoveDownObject(this, x, y, blueTexture)));
            }
        }
    }
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
        for (auto const& object : this->objects) {
            object->draw(this->renderer);
        }
        SDL_RenderPresent(this->renderer);
    }
}

void World::update() {
    for (auto& object : this->objects) {
        Action a = object->act();
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
    World *world;
    bool
        display = true,
        limitFps = false
    ;
    double
        targetFps = 1.0,
        last_time;
    ;
    unsigned int
        width = 10,
        height = width,
        ticks = 0,
        tileWidthPix = 50,
        tileHeightPix = tileWidthPix,
        windowWidthPix = width * tileWidthPix,
        windowHeightPix = height * tileHeightPix
    ;

    // Treat CLI arguments.
    while (argc > 1) {
        argc--;
        if (argv[argc][0] == '-') {
            // -d: turn display off. Might make simulation faster
            //     or runnable in device without display.
            if (std::strcmp(argv[argc], "-d") == 0) {
                display = !display;
            // -f 1.5: limit FPS to 1.5 fps. Helps humans visualize
            //         what is going on if simulation is too fast.
            } else if (std::strcmp(argv[argc], "-f") == 0) {
                limitFps = !limitFps;
                targetFps = std::strtod(argv[argc + 1], NULL);
            }
        }
    }
    auto targetSpf = 1.0 / targetFps;

main_loop:
    world = new World(
        width,
        height,
        display,
        windowWidthPix,
        windowHeightPix,
        tileWidthPix,
        tileHeightPix
    );
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
                                goto main_loop;
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
