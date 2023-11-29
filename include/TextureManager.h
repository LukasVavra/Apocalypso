#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <map>

class TextureManager
{
public:
	/*
	 * Static
	 */
	static SDL_Texture *load_texture(const char *path, SDL_Renderer *renderer);
	static SDL_Texture *load_texture_add_text(const char *path, SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color);
	static TextureManager &instance()
	{
		static TextureManager manager;
		return manager;
	}
	/*
	 * Instance
	 */
	void clean();
private:
	TextureManager();
	TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
	std::map<const char *, SDL_Texture *> textures;
};