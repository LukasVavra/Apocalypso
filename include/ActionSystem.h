#pragma once

#include <Singleton.h>
#include <PODContainer.h>
#include <Vec.h>
#include <SDL2/SDL.h>
#include <map>

using ActionId = uint16_t;

class ActionSystem : public Singleton<ActionSystem>
{
public:
    static constexpr uint8_t OP_SIZE = 8;
    struct ActionPOD
    {
        long unsigned id;
        int xoffs, yoffs;
        SDL_Rect area;
        ActionId op[OP_SIZE];
    };
    using Cache = std::map<long unsigned, ActionPOD*>;
    bool add_op(long unsigned id, ActionId op);
    bool remove_op(long unsigned id, ActionId op);
    bool trigger_action(long unsigned id, ActionId op);
    void update(long unsigned id, Vec point);
    
private:
    ActionPOD* find_action(ActionPOD& actor, ActionId op);
    bool has_op(ActionPOD& pod, ActionId op);
    PODContainer<ActionPOD, 1024> cntr;
    Cache cache;
};