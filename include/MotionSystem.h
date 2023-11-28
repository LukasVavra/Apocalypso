#pragma once

#include <Vec.h>
#include <map>
#include <SDL2/SDL.h>

class MotionSystem
{
public:
    struct MotionPOD
    {
        long unsigned id;
        Vec target;
        double speed;
    };

    static MotionSystem &instance()
    {
        static MotionSystem system;
        return system;
    }

    void set_target(long unsigned id, Vec target);
    void update();

private:
    MotionSystem();
    std::map<long unsigned, MotionPOD> ctnr;
};