#include <TextureManager.h>

SDL_Texture* TextureManager::load_texture(const char *path, SDL_Renderer *renderer)
{
	auto tm = TextureManager::instance();
	if(tm.textures.count(path))
	{
		return tm.textures[path];
	}
	SDL_Surface* temp = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	tm.textures[path] = tex;
	return tex;
}

SDL_Texture* TextureManager::load_texture_add_text(const char *path, SDL_Renderer *renderer, const char *text, TTF_Font * font, SDL_Color color)
{
	SDL_Surface* temp = IMG_Load(path);
	// TODO: draw text in middle of loaded image
	SDL_Surface* txt = TTF_RenderText_Solid(font, text, color);
	SDL_BlitSurface(txt, NULL, temp, NULL);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(txt);
	SDL_FreeSurface(temp);
	return tex;
}

void TextureManager::clean()
{
	for(auto it = textures.begin(); it != textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	textures.clear();
}

TextureManager::TextureManager()
{
}
