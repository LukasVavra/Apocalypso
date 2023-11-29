#include <RenderSystem.h>
#include <PositionSystem.h>
#include <TextureManager.h>
#include <Camera.h>
#include <MouseManager.h>
#include <ObjectManager.h>
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

static bool running;

/**
 * Frame rate management
 */
const int FPS = 60;
const int FRAME_DELAY = 1000 / 60;
uint32_t frame_begin_time;
int frame_time;


void init_objects()
{
    int id = 5;
    auto tex = TextureManager::load_texture("texture/crystals.png", renderer);
    SDL_Rect src = {0, 0, 64, 64};
    SDL_Rect des = {0, 0, 64, 64};
    rendersys.add(id, src, des, tex);
    positionsys.add(id, Vec());
    positionsys.set_position(id, Vec(100, 100));
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
    camera.resize(SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h);
    camera.set_map_size(1000, 1000);
    rendersys.set_camera(&camera);
    mouseman.set_camera(&camera);

    /*
     * Create SDL Renderer
     */
    renderer = SDL_CreateRenderer(window, -1, 0);
    RenderSystem::renderer = renderer;
    assert(renderer && "RENDERER INIT");

    init_objects();

    /*
     * Start loop
     */
    running = true;
}

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
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                break;
            default:
                break;
            }
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
    ObjectManager::instance().loadObjects("json/objects.json");
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