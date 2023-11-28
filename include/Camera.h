/*
 * Camera.h
 *
 *  Created on: 27. 11. 2022
 *      Author: lucco
 */

#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

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
	void update();

private:
	Vec point;
	SDL_Rect _view;
	int mw, mh;
	long unsigned id_eye = 0;
};


#endif /* INC_CAMERA_H_ */
