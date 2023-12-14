#pragma once
#include <Singleton.h>
#include <SDL2/SDL.h>
#include <vector>

class KeypadObserver
{
public:
    virtual void key_down(SDL_Keysym& key) = 0;
    virtual void key_up(SDL_Keysym& key) = 0;
    virtual ~KeypadObserver() = default;
};

class KeypadManager : public Singleton<KeypadManager>
{
public:
    void key_down(SDL_Keysym& key);
    void key_up(SDL_Keysym& key);
    void add_observer(KeypadObserver* observer);
    void remove_observer(KeypadObserver* observer);

private:
    std::vector<KeypadObserver*> observers;
};