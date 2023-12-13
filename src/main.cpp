#include <RenderSystem.h>
#include <PositionSystem.h>
#include <TextureManager.h>
#include <Camera.h>
#include <MouseManager.h>
#include <ObjectManager.h>
#include <MapManager.h>
#include <KeypadManager.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include <iostream>

/**
 * SDL system
 */
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

/**
 * Apocalypso system
 */
Camera camera;
#define rendersys   RenderSystem::instance()
#define positionsys PositionSystem::instance()
#define motionsys   MotionSystem::instance()
#define mouseman    MouseManager::instance()
#define mapman      MapManager::instance()
#define objman      ObjectManager::instance()
#define keyman      KeypadManager::instance()

static bool running;

/**
 * Frame rate management
 */
const int FPS = 60;
const int FRAME_DELAY = (1000 / 60) + 1;
uint32_t frame_begin_time;
int frame_time;

void handle_events()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            keyman.key_down(event.key.keysym);
        }
        else if (event.type == SDL_KEYUP)
        {
            keyman.key_up(event.key.keysym);
        }
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            camera.resize(SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                mouseman.left_btn(x, y);
            }
            else 
            {
                mouseman.right_btn(x, y);
            }
        }
    }
}

void init()
{
    /*
     * Initialize SDL Library
     */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR: " << SDL_GetError() << std::endl;
        assert(false && "SDL INIT");
    }

    /*
     * Create SDL Window
     */
    window = SDL_CreateWindow("Apocalypso v.1", 0, 0, 800, 600, SDL_WINDOW_RESIZABLE); // SDL_WINDOW_FULLSCREEN);
    assert(window && "WINDOW INIT");

    /*
     * Create SDL Renderer
     */
    renderer = SDL_CreateRenderer(window, -1, 0);
    RenderSystem::renderer = renderer;
    assert(renderer && RenderSystem::renderer && "RENDERER INIT");

    /*
     * Create map
     */
    mapman.init();

    /*
     * Set camera
     */
    camera.resize(SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h);
    camera.set_map_size(MapManager::MAP_WIDTH * MapManager::TILE_WIDTH, MapManager::MAP_HEIGHT * MapManager::TILE_HEIGHT);
   	keyman.register_action(SDLK_UP, [](){camera.move_up();});
	keyman.register_action(SDLK_DOWN, [](){camera.move_down();});
    keyman.register_action(SDLK_LEFT, [](){camera.move_left();});
    keyman.register_action(SDLK_RIGHT, [](){camera.move_right();});

    rendersys.set_camera(&camera);
    mouseman.set_camera(&camera);
    mapman.set_camera(&camera);

    /*
     * Load objects
     */
    objman.loadObjects("json/objects.json");

    /*
     * Start loop
     */
    running = true;
}

void update()
{
    motionsys.update();
    camera.update();
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    rendersys.render();
    SDL_RenderPresent(renderer);
}

void clean()
{
    TextureManager::instance().clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main()
{
    init();
    while (running)
    {
        frame_begin_time = SDL_GetTicks();

        handle_events();
        update();
        render();

        frame_time = SDL_GetTicks() - frame_begin_time;
        if (frame_time < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }
    clean();
    return 0;
}