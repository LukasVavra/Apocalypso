#pragma once

#include <Vec.h>
#include <PODContainer.h>
#include <SDL2/SDL.h>
#include <Singleton.h>

class PositionSystem : public Singleton<PositionSystem>
{
public:
    struct PositionPOD
    {
        long unsigned id;
        Vec pos;
        int level;
    };

    void add(long unsigned id, Vec &&vec);
    PositionPOD *get(long unsigned id);
    void remove(long unsigned id);
    void set_position(long unsigned id, Vec position);
    void set_position(long unsigned id, Vec position, int& level);

private:
    PODContainer<PositionPOD, 128> ctnr;
};