#pragma once
#include <Camera.h>
#include <Singleton.h>
#include <SDL2/SDL.h>
#include <cstdint>

class MapManager : public Singleton<MapManager>
{
    public:
        ~MapManager();
        void init();
        void render();
        void set_camera(Camera *camera);
        Camera* get_camera();
        void update_render_bounds(int& imin, int& jmin, int& imax, int&jmax);

        static int MAP_WIDTH;
        static int MAP_HEIGHT;
    private:
        bool load_map_tiles();
        bool load_map();
        uint8_t** map;
        struct CollisionRect
        {
            int xoffs, yoffs;
            int width, height;
            bool barrier;
        };
        struct MapTile
        {
            SDL_Texture* tex;
            SDL_Rect src;
            CollisionRect coll;
        };
        MapTile tile[64];
        Camera* camera = nullptr;
};