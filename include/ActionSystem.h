#pragma once

#include <OperationManager.h>
#include <Singleton.h>
#include <PODContainer.h>
#include <Vec.h>
#include <SDL2/SDL.h>
#include <map>
#include <vector>

class ActionSystem : public Singleton<ActionSystem>
{
public:
    struct ActionPOD
    {
        long unsigned id;
        int xoffs, yoffs;
        SDL_Rect area;
        std::vector<OperationId> actor_op;
        std::vector<OperationId> reactor_op;
    };
    using Cache = std::map<long unsigned, ActionPOD*>;
    bool assign_op(long unsigned id, OperationId op, bool actor);
    bool unassign_op(long unsigned id, OperationId op, bool actor);
    bool trigger_action(long unsigned id, OperationId op);
    void add(long unsigned id, int xoffs, int yoffs, int width, int height, std::vector<OperationId>& actor_op, std::vector<OperationId>& reactor_op);
    ActionPOD* get(long unsigned id);
    void remove(long unsigned id);
    void update(long unsigned id, Vec point);
    
private:
    ActionPOD* find_action(ActionPOD& actor, OperationId op);
    bool has_op(ActionPOD& pod, OperationId op, bool actor);
    PODContainer<ActionPOD, 1024> cntr;
    Cache cache;
};