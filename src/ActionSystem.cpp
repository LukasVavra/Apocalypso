#include "ActionSystem.h"
#include <PositionSystem.h>
#include <algorithm>

bool ActionSystem::assign_op(long unsigned id, OperationId op, bool actor)
{
    ActionPOD* pod = cntr.get(id);
    if(!pod) return false;
    if(actor)
    {
        pod->actor_op.push_back(op);
    }
    else
    {
        pod->reactor_op.push_back(op);
    }
    return true;
}

bool ActionSystem::unassign_op(long unsigned id, OperationId op, bool actor)
{
    ActionPOD* pod = cntr.get(id);
    if(!pod) return false;
    auto& vec = actor ? pod->actor_op : pod->reactor_op;
    vec.erase(std::remove(vec.begin(), vec.end(), op), vec.end());
    return true;
}

bool ActionSystem::trigger_action(long unsigned id, OperationId op)
{
    ActionPOD* actor = cntr.get(id);
    if(!actor || !has_op(*actor, op, true)) return false;
    if(cache.count(id) > 0)
    {
        auto reactor = cache[id];
        if(SDL_HasIntersection(&actor->area, &reactor->area))
        {
            return OperationManager::instance().run_op(id, reactor->id, op);
        }
        // cache entry is not valid, remove it
        cache.erase(id);
    }
    // id entry not in cache, search for action
    auto reactor = find_action(*actor, op);
    if(!reactor) return false;
    cache[id] = reactor;
    return OperationManager::instance().run_op(id, reactor->id, op);
}

void ActionSystem::add(long unsigned id, int xoffs, int yoffs, int width, int height, std::vector<OperationId>& actor_op, std::vector<OperationId>& reactor_op)
{
    SDL_Rect area {0, 0, width, height};
    // Search for id in PositionSystem
    auto pospod = PositionSystem::instance().get(id);
    if(pospod)
    {
        area.x = pospod->pos.x - xoffs;
        area.y = pospod->pos.y - yoffs;
    }
    cntr.add(id, xoffs, yoffs, area, actor_op, reactor_op);
}

ActionSystem::ActionPOD *ActionSystem::get(long unsigned id)
{
    return cntr.get(id);
}

void ActionSystem::remove(long unsigned id)
{
    cntr.remove(id);
}

void ActionSystem::update(long unsigned id, Vec point)
{
    ActionPOD* pod = cntr.get(id);
    if(!pod) return;
    pod->area.x = point.x - pod->xoffs;
    pod->area.y = point.y - pod->yoffs;
}

ActionSystem::ActionPOD *ActionSystem::find_action(ActionPOD& actor, OperationId op)
{
    for(auto& reactor : cntr)
    {
        if(actor.id == reactor.id) continue;
        if(SDL_HasIntersection(&actor.area, &reactor.area) && has_op(reactor, op, false))
        {
            return &reactor;
        }
    }
    return nullptr;
}

bool ActionSystem::has_op(ActionPOD& pod, OperationId op, bool actor)
{
    if(actor)
    {
        for(const auto& o : pod.actor_op)
        {
            if(o == op) return true;
        }
    }
    else
    {
        for(const auto& o : pod.reactor_op)
        {
            if(o == op) return true;
        }
    }
    return false;
}
