#include "ResourceManager.h"
#include <iostream>

bool ResourceManager::init()
{
    DynamicJsonDocument doc(65535);
    if(!load_json(doc, "json/resources.json")) return false;
    if(doc.is<JsonArray>())
    {
        for(const auto& obj : doc.as<JsonArray>())
        {
            resources.push_back({obj["name"].as<const char*>(), obj["liquid_temp"].as<int>(), obj["gas_temp"].as<int>(), 0});
        }
        return true;
    }
    return false;
}

ResourceManager::Resource& ResourceManager::get(int type)
{
    return resources.at(type);
}
