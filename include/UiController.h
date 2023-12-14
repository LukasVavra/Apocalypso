#pragma once

#include <ControllerSystem.h>
#include <KeypadManager.h>
#include <MouseManager.h>
#include <RenderSystem.h>
#include <Camera.h>

class UiController : public ControllerInterface, public KeypadObserver, public MouseObserver
{
public:
    UiController(Camera* camera);
    virtual void update(long unsigned id) override;
    virtual void key_down(SDL_Keysym& key) override;
    virtual void key_up(SDL_Keysym& key) override;
    virtual void left_btn(int& x, int& y) override;
    virtual void right_btn(int& x, int& y) override;
private:
    long unsigned controlled_id;
    Camera* camera;
};