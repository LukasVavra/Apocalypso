#include <CameraController.h>
#include <RenderSystem.h>
#include <MotionSystem.h>
#include <EventSystem.h>

CameraController::CameraController(): camera(nullptr)
{
	EventSystem::instance().subscribe(EventId::KEY_DOWN, s_key_down);
	EventSystem::instance().subscribe(EventId::KEY_UP, s_key_up);
	EventSystem::instance().subscribe(EventId::MOUSE_LEFT, s_left_btn);
	EventSystem::instance().subscribe(EventId::MOUSE_RIGHT, s_right_btn);
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

void CameraController::s_key_down(void *data)
{
	auto key = static_cast<SDL_Keysym*>(data);
	CameraController::instance().key_down(*key);
}

void CameraController::s_key_up(void *data)
{
	auto key = static_cast<SDL_Keysym*>(data);
	CameraController::instance().key_up(*key);
}

void CameraController::s_left_btn(void *data)
{
	struct pos {int x,y;};
	auto p = static_cast<pos*>(data);
	CameraController::instance().left_btn(p->x, p->y);
}

void CameraController::s_right_btn(void *data)
{
	struct pos {int x,y;};
	auto p = static_cast<pos*>(data);
	CameraController::instance().right_btn(p->x, p->y);
}
