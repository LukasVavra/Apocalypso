#pragma once

#include <Singleton.h>
#include <vector>
#include <SDL2/SDL.h>

class GuiManager : public Singleton<GuiManager>
{
public:
    GuiManager();
    virtual ~GuiManager();
    bool init(SDL_Window* window, SDL_Renderer* renderer);
    void handle_event(SDL_Event* event);
    void update();
    void render();
    void clean();
    
private:    
    SDL_Window* _window; 
    SDL_Renderer* _renderer;
};