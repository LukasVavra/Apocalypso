#include <gtest/gtest.h>
#include <KeypadManager.h>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

static int down_counter = 0;
static int up_counter = 0;


SDL_Keysym key;

class KeypadTest : public testing::Test 
{
public:
    class TestObserver : public KeypadObserver
    {
    public:
        virtual void key_down(SDL_Keysym& key) override
        {
            cout << "TestObserver: key down called\n";
            ++down_counter;
        }
        virtual void key_up(SDL_Keysym& key) override
        {
            cout << "TestObserver: key up called\n";
            ++up_counter;
        }
        virtual ~TestObserver() = default;
    };
protected:
    void SetUp() override
    {
        key.sym = 100;
    }
};

static KeypadTest::TestObserver keyobserver;


TEST(KeypadTest, TestInitialization)
{
    KeypadManager::instance().key_down(key);
    KeypadManager::instance().key_up(key);
    EXPECT_EQ(down_counter, 0);
    EXPECT_EQ(up_counter, 0);
}

TEST(KeypadTest, KeyDownTest)
{
    KeypadManager::instance().add_observer(&keyobserver);
    KeypadManager::instance().key_down(key);
    EXPECT_EQ(down_counter, 1);
    EXPECT_EQ(up_counter, 0);
}

TEST(KeypadTest, KeyUpTest)
{
    KeypadManager::instance().key_up(key);
    EXPECT_EQ(down_counter, 1);
    EXPECT_EQ(up_counter, 1);
}