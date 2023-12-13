#include "CollisionSystem.h"
#include <PositionSystem.h>

void CollisionSystem::add(long unsigned id, int xoffs, int yoffs, int width, int height, bool barrier)
{
    SDL_Rect rect{0, 0, width, height};
    // Search for id in PositionSystem
    auto pospod = PositionSystem::instance().get(id);
    if(pospod)
    {
        rect.x = pospod->pos.x - xoffs;
        rect.y = pospod->pos.y - yoffs;
    }
    cntr.add(id, xoffs, yoffs, rect, barrier);
}

void CollisionSystem::add(long unsigned id, int xoffs, int yoffs, SDL_Rect rect, bool barrier)
{
    cntr.add(id, xoffs, yoffs, rect, barrier);
}

CollisionSystem::CollisionPOD *CollisionSystem::get(long unsigned id)
{
    return cntr.get(id);
}

void CollisionSystem::remove(long unsigned id)
{
    cntr.remove(id);
}

bool CollisionSystem::update(long unsigned id, Vec position)
{
    auto collpod = cntr.get(id);
    if(!collpod) return true;
    SDL_Rect newrect{(int)position.x - collpod->xoffs, (int)position.y - collpod->yoffs, collpod->rect.w, collpod->rect.h};
    if(collpod->barrier)
    {
        for(auto& pod : cntr)
        {
            if(pod.id == id || !pod.barrier) continue;
            if(SDL_HasIntersection(&newrect, &pod.rect)) return false;
        }
    }
    collpod->rect.x = newrect.x;
    collpod->rect.y = newrect.y;
    return true;
}
