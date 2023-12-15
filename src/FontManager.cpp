#include "FontManager.h"
#include <iostream>

bool FontManager::init()
{
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << "\n";
        return false;
    }
    font[FontType::Regular] = TTF_OpenFont("font/Orbitron-Regular.ttf", 24);
    if (!font[FontType::Regular]) {
        std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
        return false;
    }
    font[FontType::Medium] = TTF_OpenFont("font/Orbitron-Bold.ttf", 24);
    if (!font[FontType::Medium]) {
        std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
        return false;
    }
    font[FontType::Bold] = TTF_OpenFont("font/Orbitron-Black.ttf", 24);
    if (!font[FontType::Bold]) {
        std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
        return false;
    }
    return true;
}

void FontManager::render_text(const char *text, int x, int y, SDL_Color color, FontType type)
{
    if(!RenderSystem::renderer) return;
    SDL_Surface* text_surface = TTF_RenderText_Solid(font[type], text, color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(RenderSystem::renderer, text_surface);
    SDL_Rect textRect = { x, y, text_surface->w, text_surface->h };
    SDL_RenderCopy(RenderSystem::renderer, text_texture, NULL, &textRect);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void FontManager::clean()
{
    for(int i = 0; i < FontType::count; ++i)
    {
        TTF_CloseFont(font[i]);
    }
    TTF_Quit();
}
