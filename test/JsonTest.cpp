#include <gtest/gtest.h>

#include <ObjectManager.h>

TEST(JsonTest, LoadJson)
{
    EXPECT_TRUE(ObjectManager::loadJson("json/objects.json"));
}