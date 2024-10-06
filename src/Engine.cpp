#include <Engine.h>
#include <EventSystem.h>
#include <RenderSystem.h>
#include <PositionSystem.h>
#include <MotionSystem.h>
#include <ControllerSystem.h>
#include <CameraController.h>
#include <TextureManager.h>
#include <Camera.h>
#include <ObjectManager.h>
#include <MapManager.h>
#include <FontManager.h>
#include <GuiManager.h>
#include <assert.h>
#include <iostream>

/**
 * Apocalypso system
 */
Camera camera;
#define camctrl     CameraController::instance()
#define eventsys    EventSystem::instance()
#define rendersys   RenderSystem::instance()
#define positionsys PositionSystem::instance()
#define motionsys   MotionSystem::instance()
#define mapman      MapManager::instance()
#define objman      ObjectManager::instance()
#define fontman     FontManager::instance()
#define ctrlsys     ControllerSystem::instance()
#define guiman      GuiManager::instance()

Engine::Engine()
{
    init();
}

Engine::~Engine()
{
    clean();
}

void Engine::init()
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    RenderSystem::renderer = renderer;
    assert(renderer && RenderSystem::renderer && "RENDERER INIT");

    /*
     * Init GUI manager
     */
    guiman.init(window, renderer);

    /*
     * Init font manager
     */
    fontman.init();

    /*
     * Create map
     */
    mapman.init();

    /*
     * Set camera
     */
    camera.resize(SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h);
    camera.set_map_size(MapManager::MAP_WIDTH * MapManager::TILE_WIDTH, MapManager::MAP_HEIGHT * MapManager::TILE_HEIGHT);
    camctrl.set_camera(&camera);
    rendersys.set_camera(&camera);
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

void Engine::run()
{
    while (running)
    {
        handle_events();
        update();
        render();
    }
}

void Engine::clean()
{
    guiman.clean();
    fontman.clean();
    TextureManager::instance().clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::handle_events()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        guiman.handle_event(&event);
        if (event.type == SDL_QUIT)
        {
            eventsys.emit(EventId::QUIT);
            running = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            eventsys.emit(EventId::KEY_DOWN, (void*) &event.key.keysym);
        }
        else if (event.type == SDL_KEYUP)
        {
            eventsys.emit(EventId::KEY_UP, (void*) &event.key.keysym);
        }
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            struct {int w,h;} d;
            d.w = SDL_GetWindowSurface(window)->w;
            d.h = SDL_GetWindowSurface(window)->h;
            eventsys.emit(EventId::WINDOW_RESIZED, (void*) &d);
            camera.resize(d.w, d.h);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            struct {int x,y;} p;
            SDL_GetMouseState(&p.x, &p.y);
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                eventsys.emit(EventId::MOUSE_LEFT, (void*)&p);
            }
            else 
            {
                eventsys.emit(EventId::MOUSE_RIGHT, (void*)&p);
            }
        }
    }
}

void Engine::update()
{
    ctrlsys.update();
    motionsys.update();
    camera.update();
    guiman.update();
}

void Engine::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    rendersys.render();
    guiman.render();
    SDL_RenderPresent(renderer);
}
