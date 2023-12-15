#pragma once

#include <Singleton.h>
#include <RenderSystem.h>
#include <SDL2/SDL_ttf.h>

class FontManager : public Singleton<FontManager>
{
public:
    enum FontType
    {
        Regular,
        Medium,
        Bold,
        count
    };
    bool init();
    void render_text(const char* text, int x, int y, SDL_Color color, FontType type);
    void clean();

private:
    TTF_Font* font[FontType::count];
};