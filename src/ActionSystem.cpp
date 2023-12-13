#include "ActionSystem.h"

bool ActionSystem::assign_op(long unsigned id, OperationId op)
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

bool ActionSystem::unassign_op(long unsigned id, OperationId op)
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

bool ActionSystem::trigger_action(long unsigned id, OperationId op)
{
    ActionPOD* actor = cntr.get(id);
    if(!actor || !has_op(*actor, op)) return false;
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
    return OperationManager::instance().run_op(id, reactor->id, op);
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
        if(SDL_HasIntersection(&actor.area, &reactor.area) && has_op(reactor, op))
        {
            return &reactor;
        }
    }
    return nullptr;
}

bool ActionSystem::has_op(ActionPOD& pod, OperationId op)
{
    for(int i = 0; i < OP_SIZE; ++i)
    {
        if(pod.op[i] == op) return true;
    }
    return false;
}
