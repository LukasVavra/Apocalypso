#pragma once

#include <MotionSystem.h>
#include <Camera.h>

#include <Vec.h>

class MouseManager
{
public:
    static MouseManager &instance()
    {
        static MouseManager control;
        return control;
    }

    void set_controlled_id(long unsigned id);
    void set_camera(Camera* camera);
    void left_btn(int& x, int& y);
    void right_btn(int& x, int& y);

private:
    MouseManager();
    MouseManager(const MouseManager&) = delete;
    MouseManager& operator=(const MouseManager&) = delete;
    long unsigned controlled_id;
    Vec cpoint;
    Camera * camera;
};