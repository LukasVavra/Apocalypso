#pragma once

#include <Singleton.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>

class TextureManager : public Singleton<TextureManager>
{
public:
	/*
	 * Static
	 */
	static SDL_Texture *load_texture(const char *path);
	static SDL_Texture *load_texture_add_text(const char *path, const char *text, TTF_Font *font, SDL_Color color);
	/*
	 * Instance
	 */
	void clean();
private:
	std::map<const char *, SDL_Texture *> textures;
};