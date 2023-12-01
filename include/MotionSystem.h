#pragma once

#include <Vec.h>
#include <map>
#include <SDL2/SDL.h>
#include <Singleton.h>

class MotionSystem : public Singleton<MotionSystem>
{
public:
    struct MotionPOD
    {
        long unsigned id;
        Vec target;
        double speed;
        Vec step;
    };

    void set_target(long unsigned id, Vec target);
    void update();
    void set_movable(long unsigned id);

private:
    std::map<long unsigned, MotionPOD> ctnr;
    std::map<long unsigned, bool> movable;
};