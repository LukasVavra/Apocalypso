#include "ControllerSystem.h"

void ControllerSystem::update()
{
    for(const auto& pod : cntr)
    {
        pod.controller->update(pod.id);
    }
}

void ControllerSystem::add(long unsigned controlled_id, std::shared_ptr<ControllerInterface> controller)
{
    cntr.add(controlled_id, controller);
}

ControllerSystem::ControlPOD *ControllerSystem::get(long unsigned controlled_id)
{
    return cntr.get(controlled_id);
}

void ControllerSystem::remove(long unsigned controlled_id)
{
    cntr.remove(controlled_id);
}