#pragma
#include <Singleton.h>
#include <SDL2/SDL.h>
#include <map>
#include <functional>

using callback = std::function<void()>;

class KeypadManager : public Singleton<KeypadManager>
{
    public:
        void key_down(SDL_Keysym& key);
        void key_up(SDL_Keysym& key);
        void register_action(int32_t keysym, callback f);

    private:
        std::map<int32_t, callback> action;
};