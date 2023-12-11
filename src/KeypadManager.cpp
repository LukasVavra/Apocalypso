#include "KeypadManager.h"
#include <iostream>

void KeypadManager::key_down(SDL_Keysym &key)
{
    if(action.count(key.sym) > 0) action[key.sym]();
}

void KeypadManager::key_up(SDL_Keysym &key)
{

}

void KeypadManager::register_action(int32_t keysym, callback f)
{
    action[keysym] = f;
}
