#include <RenderSystem.h>

#include <iostream>

void RenderSystem::add(long unsigned id, SDL_Rect src, SDL_Rect des, SDL_Texture *tex)
{
    instance().ctnr.add(id, src, des, tex);
}

RenderSystem::RenderPOD *RenderSystem::get(long unsigned id)
{
    return instance().ctnr.get(id);
}

void RenderSystem::sort()
{
    auto sort_f = [](const RenderPOD &a, const RenderPOD &b)
    {
        return (a.des.y + a.des.h) < (b.des.y + b.des.h);
    };
    instance().ctnr.sort(sort_f);
}

void RenderSystem::remove(long unsigned id)
{
    instance().ctnr.remove(id);
}

void RenderSystem::render(SDL_Renderer *renderer)
{
    for (auto &pod : instance().ctnr)
    {
        SDL_Rect dest(pod.des);
        if(camera) camera->update_render(dest);
        SDL_RenderCopy(renderer, pod.tex, &pod.src, &dest);
    }
}

void RenderSystem::set_position(long unsigned id, double &x, double &y, int &level)
{
    auto pod = instance().ctnr.get(id);
    if(pod)
    {
        pod->des.x = (x - pod->des.w / 2) - (level * 32);
        pod->des.y = y - pod->des.h / 2;
    }
    else
    {
        std::cout << "RenderSystem::set_position: POD id:" << id << " not found!\n";
    }
}

void RenderSystem::set_camera(Camera *camera)
{
    this->camera = camera;
}

RenderSystem::RenderSystem() : camera(nullptr)
{
}
