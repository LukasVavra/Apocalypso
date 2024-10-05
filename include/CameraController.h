#pragma once

#include <Singleton.h>
#include <Camera.h>

class CameraController : public Singleton<CameraController>
{
public:
    CameraController();
    void set_camera(Camera* camera);
    void key_down(SDL_Keysym& key);
    void key_up(SDL_Keysym& key);
    void left_btn(int& x, int& y);
    void right_btn(int& x, int& y);
private:
    static void s_key_down(void* data);
    static void s_key_up(void* data);
    static void s_left_btn(void* data);
    static void s_right_btn(void* data);
    long unsigned controlled_id;
    Camera* camera;
};