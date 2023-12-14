#include <gtest/gtest.h>
#include <MouseManager.h>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

static int l_counter = 0;
static int r_counter = 0;

class TestObserver : public MouseObserver
{
public:
    virtual void left_btn(int& x, int& y) override
    {
        cout << "TestObserver: left button called\n";
        ++l_counter;
    }
    virtual void right_btn(int& x, int& y) override
    {
        cout << "TestObserver: right button called\n";
        ++r_counter;
    }
    virtual ~TestObserver() = default;
};

TestObserver o;

class MouseManagerTest : public testing::Test 
{
protected:
    int x, y;
    void SetUp() override
    {
        x = 0;
        y = 0;
    }
};

TEST_F(MouseManagerTest, TestInitialization)
{
    MouseManager::instance().left_btn(x, y);
    MouseManager::instance().right_btn(x, y);
    EXPECT_EQ(l_counter, 0);
    EXPECT_EQ(r_counter, 0);
}

TEST_F(MouseManagerTest, TestLeftClick)
{
    MouseManager::instance().add_observer(&o);
    MouseManager::instance().left_btn(x, y);
    EXPECT_EQ(l_counter, 1);
    EXPECT_EQ(r_counter, 0);
}

TEST_F(MouseManagerTest, TestRightClick)
{
    MouseManager::instance().right_btn(x, y);
    EXPECT_EQ(l_counter, 1);
    EXPECT_EQ(r_counter, 1);
}
