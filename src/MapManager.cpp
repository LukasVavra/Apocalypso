#include "MapManager.h"
#include <TextureManager.h>
#include <RenderSystem.h>
#include <CollisionSystem.h>
#include <ObjectManager.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ArduinoJson-v6.19.4.h>
#include <JsonReader.h>

int MapManager::MAP_WIDTH = 16;
int MapManager::MAP_HEIGHT = 16;
int MapManager::TILE_WIDTH = 64;
int MapManager::TILE_HEIGHT = 64;

void MapManager::init()
{
    load_map_tiles();
    load_map();
    // create collision areas
    for(int i = 0; i < MapManager::MAP_HEIGHT; ++i)
        for(int j = 0; j < MapManager::MAP_WIDTH; ++j)
        if(tile[map[i][j]].coll.barrier)
            {//          left up   mid   offs
                int x = (j * TILE_WIDTH) + (TILE_WIDTH / 2) - tile[map[i][j]].coll.xoffs;
                int y = (i * TILE_HEIGHT) + (TILE_HEIGHT / 2) - tile[map[i][j]].coll.yoffs;
                int width = tile[map[i][j]].coll.width;
                int height = tile[map[i][j]].coll.height;
                SDL_Rect collrect{x, y, width, height};
                auto id = ObjectManager::get_unique_id();
                CollisionSystem::instance().add(id, tile[map[i][j]].coll.xoffs, tile[map[i][j]].coll.yoffs, collrect, true);
            }
}

void MapManager::render()
{
    int x = 0;
    int y = 0;
    int xmax = 16;
    int ymax = 16;
    update_render_bounds(x, y, xmax,  ymax); // render only visible tiles
    for(int h = y; h < ymax; ++h)
        for(int w = x; w < xmax; ++w)
        {
            SDL_Rect dest{w * TILE_WIDTH, h * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
            if(camera) camera->update_render(dest);
            SDL_RenderCopy(RenderSystem::renderer, tile[map[h][w]].tex, &tile[map[h][w]].src, &dest);
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
    imin = camera->view().x / TILE_WIDTH;
    jmin = camera->view().y / TILE_HEIGHT;
    imax = std::min(((camera->view().x + camera->view().w) / TILE_WIDTH) + 1, MapManager::MAP_WIDTH);
    jmax = std::min(((camera->view().y + camera->view().h) / TILE_HEIGHT) + 1, MapManager::MAP_HEIGHT);
}

bool MapManager::load_map_tiles()
{   
    StaticJsonDocument<2048> json;
    if(!load_json(json, "json/maptiles.json")) return false;

    if(json.is<JsonArray>())
    {
        int index = 0;
        for (JsonVariant obj : json.as<JsonArray>())
        {
            auto tex = TextureManager::instance().load_texture(obj["texture"].as<const char*>());
            auto jsrc = obj["src"];
            SDL_Rect src{jsrc["x"].as<int>(), jsrc["y"].as<int>(), jsrc["w"].as<int>(), jsrc["h"].as<int>()};
            auto jcoll = obj["collision"];
            CollisionRect coll{jcoll["xoffs"].as<int>(), jcoll["yoffs"].as<int>(), jcoll["width"].as<int>(), jcoll["height"].as<int>(), jcoll["barrier"].as<bool>()};
            tile[index++] = {tex, src, coll};
        }
    }
    else
    {
        std::cout << "maptiles.json does not contains json array\n";
        return false;
    }
    std::cout << "maptiles.json loaded successfully\n";
    return true;
}

bool MapManager::load_map()
{
    // read json
    DynamicJsonDocument json(65535);
    if(!load_json(json, "json/map.json")) return false;
    
    // get map layer
    auto layer = json["layers"][0];
    MapManager::MAP_WIDTH = layer["width"].as<int>();
    MapManager::MAP_HEIGHT = layer["height"].as<int>();
    
    // allocate map
    map = new uint8_t*[MapManager::MAP_HEIGHT];
    for(int i = 0; i < MapManager::MAP_HEIGHT; ++i)
    {
        map[i] = new uint8_t[MapManager::MAP_WIDTH];
    }

    // fill map
    auto data = layer["data"].as<JsonArray>();
    int index = 0;
    for(int i = 0; i < MapManager::MAP_HEIGHT; ++i)
        for(int j = 0; j < MapManager::MAP_WIDTH; ++j)
        {
            map[i][j] = (data[index++].as<int>()) - 1;
        }

    std::cout << "map width: " << MapManager::MAP_WIDTH << ", map height: " << MapManager::MAP_HEIGHT << "\n";
    std::cout << "map.json loaded successfully\n";
    return true;
}

MapManager::~MapManager() 
{
    if(map) 
    {
        for(int i = 0; i < MapManager::MAP_HEIGHT; ++i)
        {
            delete[] map[i];
        }   
        delete[] map;
    }
}
