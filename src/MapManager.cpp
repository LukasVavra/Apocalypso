#include "MapManager.h"
#include <TextureManager.h>
#include <RenderSystem.h>

void MapManager::init()
{
    //  create map tiles
    auto tex = TextureManager::instance().load_texture("texture/map-tiles.png");
    tile[0] = {tex, {0, 0, 64, 64}};
    tile[1] = {tex, {0, 64, 64, 64}};
    tile[2] = {tex, {0, 128, 64, 64}};
}

void MapManager::render()
{
    int x = 0;
    int y = 0;
    int xmax = 16;
    int ymax = 16;
    update_render_bounds(x, y, xmax,  ymax); // render only visible tiles
    for(int i = x; i < xmax; ++i)
        for(int j = y; j < ymax; ++j)
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

Camera *MapManager::get_camera()
{
    return this->camera;
}

void MapManager::update_render_bounds(int &imin, int &jmin, int &imax, int &jmax)
{
    if(!camera) return;
    imin = camera->view().x / 64;
    jmin = camera->view().y / 64;
    imax = ((camera->view().x + camera->view().w) / 64) + 1;
    jmax = ((camera->view().y + camera->view().h) / 64) + 1;
}
