/*
 * Camera.cpp
 *
 *  Created on: 27. 11. 2022
 *      Author: lucco
 */

#include <Camera.h>

#include <PositionSystem.h>

Camera::Camera() :
		point(0, 0), mw(0), mh(0)
{
	_view.x = 0;
	_view.y = 0;
	_view.w = 0;
	_view.h = 0;
}

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
	id_eye = id;
}

void Camera::update()
{
	if(id_eye)
	{
		update_viewpoint(&PositionSystem::instance().get(id_eye)->pos);
	}
}
