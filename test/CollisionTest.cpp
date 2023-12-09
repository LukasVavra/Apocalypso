#include <gtest/gtest.h>

#include <PositionSystem.h>
#include <CollisionSystem.h>

class CollisionTest : public testing::Test 
{
    protected:
        void SetUp() override
        {
            // prepare positions
            PositionSystem::instance().add(1, Vec(128, 128));
            PositionSystem::instance().add(2, Vec(1000, 1000));
            // prepare collisions
            CollisionSystem::instance().add(1, 32, 32, 64, 64, true);
            CollisionSystem::instance().add(2, 32, 32, 64, 64, true);
        }
        Vec nextpos{0, 0};
};

TEST_F(CollisionTest, TestInitialization)
{
    EXPECT_FALSE(CollisionSystem::instance().get(1) == nullptr);
    EXPECT_FALSE(CollisionSystem::instance().get(2) == nullptr);
}

TEST_F(CollisionTest, NorthProximity)
{
    nextpos.set_xy(128, 64);
    EXPECT_TRUE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, SouthProximity)
{
    nextpos.set_xy(128, 192);
    EXPECT_TRUE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, WestProximity)
{
    nextpos.set_xy(64, 128);
    EXPECT_TRUE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, EastProximity)
{
    nextpos.set_xy(192, 128);
    EXPECT_TRUE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, NorthCollision)
{
    nextpos.set_xy(128, 65);
    EXPECT_FALSE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, SouthCollision)
{
    nextpos.set_xy(128, 191);
    EXPECT_FALSE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, WestCollision)
{
    nextpos.set_xy(65, 128);
    EXPECT_FALSE(CollisionSystem::instance().update(2, nextpos));
}

TEST_F(CollisionTest, EastCollision)
{
    nextpos.set_xy(191, 128);
    EXPECT_FALSE(CollisionSystem::instance().update(2, nextpos));
}