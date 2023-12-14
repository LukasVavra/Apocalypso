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
    if(observers.size())
    {
        for(auto& observer : observers)
        {
            observer->left_btn(x, y);
        }
    }
    int cx = x + camera->view().x;
    int cy = y + camera->view().y;
    auto id = RenderSystem::instance().get_clicked_id(x, y);
    set_controlled_id(id);
    camera->watch_id(id);
}

void MouseManager::right_btn(int &x, int &y)
{
    if(observers.size())
    {
        for(auto& observer : observers)
        {
            observer->right_btn(x, y);
        }
    }
    if(controlled_id)
    {
        // calculate map position
        int cx = x + camera->view().x;
        int cy = y + camera->view().y;
        MotionSystem::instance().set_target(controlled_id, Vec(cx,cy));
    }
}

void MouseManager::add_observer(MouseObserver *observer)
{
    observers.push_back(observer);
}

void MouseManager::remove_observer(MouseObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
