#include "MouseManager.h"
#include <RenderSystem.h>
#include <iostream>

MouseManager::MouseManager() : camera(nullptr)
{
}

void MouseManager::set_controlled_id(long unsigned id)
{
    controlled_id = id;
}

void MouseManager::set_camera(Camera *camera)
{
    this->camera = camera;
}

void MouseManager::left_btn(int &x, int &y)
{
    int cx = x + camera->view().x;
    int cy = y + camera->view().y;
    auto id = RenderSystem::instance().get_clicked_id(x, y);
    set_controlled_id(id);
    camera->watch_id(id);
}

void MouseManager::right_btn(int &x, int &y)
{
    int cx = x + camera->view().x;
    int cy = y + camera->view().y;
    if(controlled_id)
    {
        MotionSystem::instance().set_target(controlled_id, Vec(cx,cy));
    }
}
