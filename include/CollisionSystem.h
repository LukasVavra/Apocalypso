#pragma once
#include <Singleton.h>
#include <Vec.h>
#include <PODContainer.h>
#include <SDL2/SDL.h>

class CollisionSystem : public Singleton<CollisionSystem>
{
    public:
        struct CollisionPOD
        {
            long unsigned id;
            int xoffs;
            int yoffs;
            SDL_Rect rect;
            bool barrier;
        };
        void add(long unsigned id, int xoffs, int yoffs, int width, int height, bool barrier);
        CollisionPOD* get(long unsigned id);
        void remove(long unsigned id);
        bool update(long unsigned id, Vec position);

    private:
        PODContainer<CollisionPOD, 128> cntr;
};