#include "UiController.h"

UiController::UiController(Camera* camera): camera(camera)
{
    KeypadManager::instance().add_observer(this);
    MouseManager::instance().add_observer(this);
}

void UiController::update(long unsigned id)
{
}

void UiController::key_down(SDL_Keysym &key)
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

void UiController::key_up(SDL_Keysym &key)
{
}

void UiController::left_btn(int &x, int &y)
{
    auto id = RenderSystem::instance().get_clicked_id(x, y);
    controlled_id = id;
    if(camera) camera->watch_id(id);
}

void UiController::right_btn(int &x, int &y)
{
    if(controlled_id && camera)
    {
        MotionSystem::instance().set_target(controlled_id, camera->get_map_position(x, y));
    }
}