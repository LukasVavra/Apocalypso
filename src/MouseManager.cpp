#include "MouseManager.h"
#include <RenderSystem.h>
#include <iostream>
#include <algorithm>

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
    for(auto& observer : observers)
    {
        observer->left_btn(x, y);
    }
    auto id = RenderSystem::instance().get_clicked_id(x, y);
    set_controlled_id(id);
    if(camera) camera->watch_id(id);
}

void MouseManager::right_btn(int &x, int &y)
{
    for(auto& observer : observers)
    {
        observer->right_btn(x, y);
    }
    if(controlled_id)
    {
        MotionSystem::instance().set_target(controlled_id, get_map_position(x,y));
    }
}

Vec MouseManager::get_map_position(int &x, int &y)
{
    if(camera)
    {
        int cx = x + camera->view().x;
        int cy = y + camera->view().y;
        return Vec(cx, cy);
    }
    return Vec();
}

void MouseManager::add_observer(MouseObserver *observer)
{
    if(std::find(observers.begin(), observers.end(), observer) == observers.end())
    {
        observers.push_back(observer);
    }
}

void MouseManager::remove_observer(MouseObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
