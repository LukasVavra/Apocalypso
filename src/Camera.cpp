#include <Camera.h>
#include <KeypadManager.h>

Camera::Camera() : _view{0, 0, 0, 0}, mw(0), mh(0), pospod_eye(nullptr)
{}

void Camera::update_viewpoint(Vec* point)
{
	if (point->x < _view.w / 2)
	{
		_view.x = 0;
	}
	else if (point->x > mw - (_view.w / 2))
	{
		_view.x = mw - _view.w;
		_view.x = _view.x < 0 ? 0 : _view.x;
	}
	else
	{
		_view.x = point->x - _view.w / 2;
	}

	if (point->y < _view.h / 2)
	{
		_view.y = 0;
	}
	else if (point->y > mh - (_view.h / 2))
	{
		_view.y = mh - _view.h;
		_view.y = _view.y < 0 ? 0 : _view.y;
	}
	else
	{
		_view.y = point->y - _view.h / 2;
	}
}

void Camera::resize(int w, int h)
{
	_view.w = w;
	_view.h = h;
}

void Camera::set_map_size(int w, int h)
{
	mw = w;
	mh = h;
}

SDL_Rect& Camera::view()
{
	return _view;
}

void Camera::update_render(SDL_Rect &des)
{
	des.x -= _view.x;
	des.y -= _view.y;
}

void Camera::watch_id(long unsigned id)
{
	pospod_eye = PositionSystem::instance().get(id);
}

void Camera::unwatch()
{
	if(pospod_eye)
	{
		pospod_eye = nullptr;
	}
}

void Camera::update()
{
	if(pospod_eye)
	{
		update_viewpoint(&pospod_eye->pos);
	}
}

void Camera::move_up()
{
	unwatch();
	_view.y = _view.y < move_step ? 0 : _view.y - move_step;
}

void Camera::move_down()
{
	unwatch();
	_view.y = (mh - (_view.y + _view.h)) < move_step ? (mh - _view.h) : _view.y + move_step;
}

void Camera::move_left()
{
	unwatch();
	_view.x = _view.x < move_step ? 0 : _view.x - move_step;
}

void Camera::move_right()
{
	unwatch();
	_view.x = (mw - (_view.x + _view.w)) < move_step ? (mw - _view.w) : _view.x + move_step;
}