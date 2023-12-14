#pragma once

#include <MotionSystem.h>
#include <Camera.h>
#include <Vec.h>
#include <Singleton.h>
#include <vector>

class MouseObserver
{
public:
    virtual void left_btn(int& x, int& y) = 0;
    virtual void right_btn(int& x, int& y) = 0;
    virtual ~MouseObserver() = default;
};

class MouseManager : public Singleton<MouseManager>
{
public:
    void set_controlled_id(long unsigned id);
    void set_camera(Camera* camera);
    void left_btn(int& x, int& y);
    void right_btn(int& x, int& y);
    Vec get_map_position(int& x, int& y);
    void add_observer(MouseObserver* observer);
    void remove_observer(MouseObserver* observer);

private:
    long unsigned controlled_id;
    Vec cpoint;
    Camera * camera = nullptr;
    std::vector<MouseObserver*> observers;
};