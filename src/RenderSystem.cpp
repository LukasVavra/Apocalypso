#include <RenderSystem.h>

#include <iostream>

void RenderSystem::add(long unsigned id, SDL_Rect src, SDL_Rect des, SDL_Texture *tex)
{
    ctnr.add(id, src, des, tex);
}

RenderSystem::RenderPOD *RenderSystem::get(long unsigned id)
{
    return ctnr.get(id);
}

void RenderSystem::sort()
{
    auto sort_f = [](const RenderPOD &a, const RenderPOD &b)
    {
        return (a.des.y + a.des.h) < (b.des.y + b.des.h);
    };
    ctnr.sort(sort_f);
}

void RenderSystem::remove(long unsigned id)
{
    ctnr.remove(id);
}

void RenderSystem::render(SDL_Renderer *renderer)
{
    for (auto &pod : ctnr)
    {
        SDL_Rect dest(pod.des);
        if(camera) camera->update_render(dest);
        SDL_RenderCopy(renderer, pod.tex, &pod.src, &dest);
    }
}

void RenderSystem::set_position(long unsigned id, double &x, double &y, int &level)
{
    auto pod = ctnr.get(id);
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

long unsigned RenderSystem::get_clicked_id(int &x, int &y)
{
    SDL_Point point{x, y};
    for (auto &pod : ctnr)
    {
        SDL_Rect area(pod.des);
        if(camera) camera->update_render(area);
        if(SDL_PointInRect(&point, &area)) return pod.id;
    }
    return 0;
}
