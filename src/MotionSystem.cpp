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
    if(!movable[id]) return;
    auto pos = PositionSystem::instance().get(id);
    if(!pos) return;
    auto step = target - pos->pos;
    Vecmath::normalize(step);
    if (ctnr.count(id))
    {
        step = Vecmath::multiply(step, ctnr[id].speed);
        ctnr[id].target = target;
        ctnr[id].step = step;
    }
    else
    {
        MotionPOD pod = {id, target, 1.0, Vec()};
        step = Vecmath::multiply(step, pod.speed);
        pod.step = step;
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
        // Check end of motion
        if (distance < 1)
        {
            ctnr.erase(p.first);
            break;
        }
        else
        {
            PositionSystem::instance().set_position(pod.id, pos->pos + pod.step, pos->level);
        }
    }
}

void MotionSystem::set_movable(long unsigned id)
{
    movable.insert(std::pair<long unsigned, bool>(id, true));
}
