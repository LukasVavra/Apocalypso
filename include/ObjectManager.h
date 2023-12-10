#pragma once
#include <ArduinoJson-v6.19.4.h>
#include <Singleton.h>

class ObjectManager : public Singleton<ObjectManager>
{
    public:
        inline static unsigned long get_unique_id()
        {
            static int unique_id_counter;
            return ++unique_id_counter;
        }
        void loadObjects(const char* filepath);
};