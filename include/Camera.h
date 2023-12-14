#pragma once

#include <PositionSystem.h>
#include <Vec.h>
#include <SDL2/SDL.h>
#include <KeypadManager.h>

class Camera : public KeypadObserver
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
	virtual void key_down(SDL_Keysym &key) override;
	virtual void key_up(SDL_Keysym &key) override;
	
private:
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	SDL_Rect _view;
	int mw, mh;
	PositionSystem::PositionPOD* pospod_eye;
	int move_step = 10;
};