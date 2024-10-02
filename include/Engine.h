#pragma once

#include <Singleton.h>
#include <SDL2/SDL.h>

class Engine : public Singleton<Engine>
{
public:
    Engine();
    virtual ~Engine();
    void run();
private:
    void init();
    void clean();
    void handle_events();
    void update();
    void render();

    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
};