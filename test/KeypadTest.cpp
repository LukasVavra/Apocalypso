#include <gtest/gtest.h>
#include <KeypadManager.h>
#include <SDL2/SDL.h>

TEST(KeypadTest, RegisterAction)
{
    int counter = 0;
    SDL_Keysym key;
    key.sym = 100;
    KeypadManager::instance().register_action(100, [&counter](){counter++;});
    EXPECT_EQ(counter, 0);
    KeypadManager::instance().key_down(key);
    EXPECT_EQ(counter, 1);
    KeypadManager::instance().key_down(key);
    EXPECT_EQ(counter, 2);
}