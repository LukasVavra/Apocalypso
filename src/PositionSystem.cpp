#include "PositionSystem.h"
#include <RenderSystem.h>

void PositionSystem::add(long unsigned id, Vec &&vec)
{
    instance().ctnr.add(id, vec);
}

PositionSystem::PositionPOD *PositionSystem::get(long unsigned id)
{
    return instance().ctnr.get(id);
}

void PositionSystem::remove(long unsigned id)
{
    instance().ctnr.remove(id);
}

void PositionSystem::set_position(long unsigned id, Vec position)
{
    auto pospod = instance().ctnr.get(id);
    pospod->pos.set_position(position);
    RenderSystem::instance().set_position(id, position.x, position.y, pospod->level);
}

void PositionSystem::set_position(long unsigned id, Vec position, int &level)
{
    instance().ctnr.get(id)->pos.set_position(position);
    instance().ctnr.get(id)->level = level;
    RenderSystem::instance().set_position(id, position.x, position.y, level);
}

PositionSystem::PositionSystem()
{
}
