#pragma once

#include <PositionSystem.h>
#include <Vec.h>
#include <SDL2/SDL.h>

class Camera
{
public:
	Camera();
	void set_map_size(int w, int h);
	void update_viewpoint(Vec* point);
	void resize(int w, int h);
	SDL_Rect& view();
	void update_render(SDL_Rect& des);
	void watch_id(long unsigned id);
	void unwatch();
	void update();
	Vec convert_position(int &x, int &y);
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	
private:
    SDL_Rect _view;
    int mw, mh;
	PositionSystem::PositionPOD* pospod_eye;
	int move_step = 10;
};