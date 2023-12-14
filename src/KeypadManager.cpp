#include "KeypadManager.h"
#include <algorithm>

void KeypadManager::key_down(SDL_Keysym &key)
{
    for(auto& observer : observers)
    {
        observer->key_down(key);
    }    
}

void KeypadManager::key_up(SDL_Keysym &key)
{
    for(auto& observer : observers)
    {
        observer->key_up(key);
    }
}

void KeypadManager::add_observer(KeypadObserver *observer)
{
    if(std::find(observers.begin(), observers.end(), observer) == observers.end())
    {
        observers.push_back(observer);
    }
}

void KeypadManager::remove_observer(KeypadObserver *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}