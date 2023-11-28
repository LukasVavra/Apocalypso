#include "MouseManager.h"
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
    click_point.set_xy(x + camera->view().x, y + camera->view().y);
    std::cout << "MouseManager: invoke x:" << click_point.x << " y:" << click_point.y <<"\n";
    MotionSystem::instance().set_target(controlled_id, click_point);
}