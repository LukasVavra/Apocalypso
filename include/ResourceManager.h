#pragma once

#include <Singleton.h>
#include <JsonReader.h>
#include <vector>

class ResourceManager : public Singleton<ResourceManager>
{
public:
    struct Resource
    {
        const char* name;
        int liquid_temp;
        int gas_temp;
        int temperature;
    };
    bool init();
    Resource& get(int type);
private:
    std::vector<Resource> resources;
};