#pragma once

#include <KeypadManager.h>
#include <MouseManager.h>
#include <Camera.h>

class CameraController : public KeypadObserver, public MouseObserver
{
public:
    CameraController();
    void set_camera(Camera* camera);
    virtual void key_down(SDL_Keysym& key) override;
    virtual void key_up(SDL_Keysym& key) override;
    virtual void left_btn(int& x, int& y) override;
    virtual void right_btn(int& x, int& y) override;
private:
    long unsigned controlled_id;
    Camera* camera;
};