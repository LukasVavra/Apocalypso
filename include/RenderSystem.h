#pragma once

#include <Camera.h>
#include <PODContainer.h>
#include <SDL2/SDL.h>

class RenderSystem
{
public:
    struct RenderPOD
    {
        long unsigned id;
        SDL_Rect src;
        SDL_Rect des;
        SDL_Texture *tex;
    };

    void add(long unsigned id, SDL_Rect src, SDL_Rect des, SDL_Texture *tex);
    RenderPOD *get(long unsigned id);
    void sort();
    void remove(long unsigned id);
    void render(SDL_Renderer *renderer);
    void set_position(long unsigned id, double& x, double& y, int& level);
    void set_camera(Camera *camera);

    static RenderSystem &instance()
    {
        static RenderSystem system;
        return system;
    }

private:
    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;
    PODContainer<RenderPOD, 128> ctnr;
    Camera *camera = nullptr;
};