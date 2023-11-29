#pragma once
#include <ArduinoJson-v6.19.4.h>

class ObjectManager
{
    public:
        static ObjectManager &instance()
        {
            static ObjectManager manager;
            return manager;
        }
        inline static unsigned long get_unique_id()
        {
            static int unique_id_counter;
            return ++unique_id_counter;
        }
        static bool loadJson(const char* filepath);
        void loadObjects(const char* filepath);

    private:
        ObjectManager() = default;
        ObjectManager(const ObjectManager&) = delete;
        ObjectManager& operator=(const ObjectManager&) = delete;
        inline static StaticJsonDocument<2048> json;    
};