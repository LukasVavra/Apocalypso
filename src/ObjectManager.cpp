#include "ObjectManager.h"
#include <fstream>
#include <iostream>
#include <PositionSystem.h>
#include <MotionSystem.h>
#include <RenderSystem.h>
#include <CollisionSystem.h>
#include <TextureManager.h>
#include <SDL2/SDL.h>
#include <JsonReader.h>

using namespace std;

void ObjectManager::loadObjects(const char *filepath)
{
    StaticJsonDocument<2048> json;    
    if(!load_json(json, filepath)) return;
    if(json.is<JsonArray>())
    {
        for (JsonVariant obj : json.as<JsonArray>())
        {
            unsigned long id = ObjectManager::get_unique_id();
            auto name = obj["name"].as<const char*>();
            cout << "New object " << name << " with id " << id <<"\n";
            if(obj.containsKey("position"))
            {
                auto pos = obj["position"];
                PositionSystem::instance().add(id, Vec(pos["x"], pos["y"]));
            }
            if(obj.containsKey("movable"))
            {
                auto movable = obj["movable"].as<bool>();
                if(movable)
                {
                    MotionSystem::instance().set_movable(id);
                }
            }
            if(obj.containsKey("render"))
            {
                auto ren = obj["render"];
                const char* path = ren["texture"];
                auto tex = TextureManager::load_texture(path);
                if(!tex)
                {
                    cout << "Texture " << path << " not found! \n";
                }
                auto rect = ren["src"];
                SDL_Rect src{rect["x"], rect["y"], rect["w"], rect["h"]};
                RenderSystem::instance().add(id, src, src, tex);
                auto pos_pod = PositionSystem::instance().get(id);
                if(!pos_pod)
                {
                    cout << "There is no Position POD for id " << id << "\n";
                    return;
                }
                RenderSystem::instance().set_position(id, pos_pod->pos.x, pos_pod->pos.y, pos_pod->level);
            }
            if(obj.containsKey("collision"))
            {
                auto coll = obj["collision"];
                CollisionSystem::instance().add(id, coll["xoffs"], coll["yoffs"], coll["width"], coll["height"], coll["barrier"]);
            }
        }
    }
    else
    {
        cout << "Json not array!\n";
    }
}