#include "PositionSystem.h"
#include <RenderSystem.h>

void PositionSystem::add(long unsigned id, Vec &&vec)
{
    ctnr.add(id, vec);
}

PositionSystem::PositionPOD *PositionSystem::get(long unsigned id)
{
    return ctnr.get(id);
}

void PositionSystem::remove(long unsigned id)
{
    ctnr.remove(id);
}

void PositionSystem::set_position(long unsigned id, Vec position)
{
    auto pospod = ctnr.get(id);
    pospod->pos.set_position(position);
    RenderSystem::instance().set_position(id, position.x, position.y, pospod->level);
}

void PositionSystem::set_position(long unsigned id, Vec position, int &level)
{
    ctnr.get(id)->pos.set_position(position);
    ctnr.get(id)->level = level;
    RenderSystem::instance().set_position(id, position.x, position.y, level);
}