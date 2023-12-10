#include "JsonReader.h"
#include <fstream>
#include <iostream>

bool load_json(JsonDocument &doc, const char *path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "Error opening" << path << "\n";
        return false;
    }
    DeserializationError err = deserializeJson(doc, file);
    if(err)
    {
        std::cout << "Error parsing json: " << err.c_str() << "\n";
        return false;
    }
    file.close();
    return true;
}