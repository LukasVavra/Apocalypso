#include "MouseManager.h"
#include <RenderSystem.h>
#include <iostream>

MouseManager::MouseManager() : camera(nullptr)
{
}

void MouseManager::set_controlled_id(long unsigned id)
{
    std::cout << "MouseManager: set id to " << id << "\n";
    controlled_id = id;
}

void MouseManager::set_camera(Camera *camera)
{
    this->camera = camera;
}

void MouseManager::invoke(int &x, int &y)
{
    int cx = x + camera->view().x;
    int cy = y + camera->view().y;
    std::cout << "MouseManager: invoke x:" << cx << " y:" << cy <<"\n";
    auto id = RenderSystem::instance().get_clicked_id(cx, cy);
    if(id) 
    {
        set_controlled_id(id);
        camera->watch_id(id);
    }
    else if(controlled_id)
    {
        MotionSystem::instance().set_target(controlled_id, Vec(cx,cy));
    }
}