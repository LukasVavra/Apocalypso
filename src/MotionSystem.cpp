#include <MotionSystem.h>
#include <PositionSystem.h>
#include <RenderSystem.h>
#include <Vecmath.h>

#include <iostream>

MotionSystem::MotionSystem()
{
}

void MotionSystem::set_target(long unsigned id, Vec target)
{
    if (ctnr.count(id))
    {
        ctnr[id].target = target;
    }
    else
    {
        MotionPOD pod = {id, target, 1.0};
        ctnr[id] = pod;
    }
}

void MotionSystem::update()
{
    for (const auto &p : ctnr)
    {
        
        auto pod = p.second;
        auto pos = PositionSystem::instance().get(pod.id);
        auto dir = pod.target - pos->pos;
        auto distance = Vecmath::size(dir);
        if (distance < 1)
        {
            ctnr.erase(p.first);
            break;
        }
        Vecmath::normalize(dir);
        Vecmath::multiply(dir, pod.speed);
        PositionSystem::instance().set_position(pod.id, pos->pos + dir, pos->level);
    }
}