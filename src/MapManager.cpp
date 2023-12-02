#include "MapManager.h"
#include <TextureManager.h>
#include <RenderSystem.h>

void MapManager::init()
{
    auto tex = TextureManager::instance().load_texture("texture/map-tiles.png");
    tile[0] = {tex, {0, 0, 64, 64}};
    tile[1] = {tex, {0, 64, 64, 64}};
    tile[2] = {tex, {0, 128, 64, 64}};
}

void MapManager::render()
{
    for(int i = 0; i < 16; ++i)
        for(int j = 0; j < 16; ++j)
        {
            SDL_Rect dest{i * 64, j * 64, 64, 64};
            if(camera) camera->update_render(dest);
            SDL_RenderCopy(RenderSystem::renderer, tile[map[i][j]].tex, &tile[map[i][j]].src, &dest);
        }
}

void MapManager::set_camera(Camera *camera)
{
    this->camera = camera;
}
