#include <CameraController.h>
#include <RenderSystem.h>

CameraController::CameraController(): camera(nullptr)
{
    KeypadManager::instance().add_observer(this);
    MouseManager::instance().add_observer(this);
}

void CameraController::set_camera(Camera *camera)
{
	this->camera = camera;
}

void CameraController::key_down(SDL_Keysym &key)
{
    if(!camera) return;
    camera->unwatch();
	switch(key.sym)
	{
		case SDLK_UP:
			camera->move_up();
		break;

		case SDLK_DOWN:
			camera->move_down();
		break;

		case SDLK_LEFT:
			camera->move_left();
		break;

		case SDLK_RIGHT:
			camera->move_right();
		break;
		default:
		break;
	}
}

void CameraController::key_up(SDL_Keysym &key)
{
}

void CameraController::left_btn(int &x, int &y)
{
	if(!camera) return;
    auto id = RenderSystem::instance().get_clicked_id(x, y);
    controlled_id = id;
    camera->watch_id(id);
}

void CameraController::right_btn(int &x, int &y)
{
	if(!camera) return;
    if(controlled_id)
    {
        MotionSystem::instance().set_target(controlled_id, camera->convert_position(x, y));
    }
}