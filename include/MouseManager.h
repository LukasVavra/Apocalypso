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
    void invoke(int& x, int& y);

private:
    MouseManager();
    long unsigned controlled_id;
    Vec click_point;
    Camera * camera;
};