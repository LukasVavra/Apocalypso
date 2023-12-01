#pragma once

#include <MotionSystem.h>
#include <Camera.h>
#include <Vec.h>
#include <Singleton.h>

class MouseManager : public Singleton<MouseManager>
{
public:
    void set_controlled_id(long unsigned id);
    void set_camera(Camera* camera);
    void left_btn(int& x, int& y);
    void right_btn(int& x, int& y);

private:
    long unsigned controlled_id;
    Vec cpoint;
    Camera * camera = nullptr;
};