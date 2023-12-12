#include "ActionSystem.h"

bool ActionSystem::add_op(long unsigned id, ActionId op)
{
    ActionPOD* pod = cntr.get(id);
    if(!pod) return false;
    for(int i = 0; i < OP_SIZE; ++i)
    {
        if(pod->op[i] == 0)
        {
            pod->op[i] = op;
            return true;
        }
    }
    return false;
}

bool ActionSystem::remove_op(long unsigned id, ActionId op)
{
    ActionPOD* pod = cntr.get(id);
    if(!pod) return false;
    for(int i = 0; i < OP_SIZE; ++i)
    {
        if(pod->op[i] == op)
        {
            pod->op[i] = 0;
            return true;
        }
    }
    return false;
}

bool ActionSystem::trigger_action(long unsigned id, ActionId op)
{
    ActionPOD* actor = cntr.get(id);
    if(!actor || !has_op(*actor, op)) return false;
    if(cache.count(id) > 0)
    {
        auto reactor = cache[id];
        if(SDL_HasIntersection(&actor->area, &reactor->area))
        {
            //return call_op (actor, reactor, op);
            return true;
        }
        // cache entry is not valid, remove it
        cache.erase(id);
    }
    // id entry not in cache, search for action
    auto reactor = find_action(*actor, op);
    if(!reactor) return false;
    //return call_op (actor, reactor, op);
    return true;
}

void ActionSystem::update(long unsigned id, Vec point)
{
    ActionPOD* pod = cntr.get(id);
    if(!pod) return;
    pod->area.x = point.x - pod->xoffs;
    pod->area.y = point.y - pod->yoffs;
}

ActionSystem::ActionPOD *ActionSystem::find_action(ActionPOD& actor, ActionId op)
{
    for(auto& reactor : cntr)
    {
        if(SDL_HasIntersection(&actor.area, &reactor.area) && has_op(reactor, op))
        {
            return &reactor;
        }
    }
    return nullptr;
}

bool ActionSystem::has_op(ActionPOD& pod, ActionId op)
{
    for(int i = 0; i < 8; ++i)
    {
        if(pod.op[i] == op) return true;
    }
    return false;
}
