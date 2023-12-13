#pragma once

#include <OperationManager.h>
#include <Singleton.h>
#include <PODContainer.h>
#include <Vec.h>
#include <SDL2/SDL.h>
#include <map>

class ActionSystem : public Singleton<ActionSystem>
{
public:
    static constexpr uint8_t OP_SIZE = 8;
    struct ActionPOD
    {
        long unsigned id;
        int xoffs, yoffs;
        SDL_Rect area;
        OperationId actor_op[OP_SIZE];
        OperationId reactor_op[OP_SIZE];
    };
    using Cache = std::map<long unsigned, ActionPOD*>;
    bool assign_op(long unsigned id, OperationId op, bool actor);
    bool unassign_op(long unsigned id, OperationId op, bool actor);
    bool trigger_action(long unsigned id, OperationId op);
    void update(long unsigned id, Vec point);
    
private:
    ActionPOD* find_action(ActionPOD& actor, OperationId op);
    bool has_op(ActionPOD& pod, OperationId op, bool actor);
    PODContainer<ActionPOD, 1024> cntr;
    Cache cache;
};