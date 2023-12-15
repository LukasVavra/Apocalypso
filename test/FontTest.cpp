#include <gtest/gtest.h>

#include <FontManager.h>

TEST(FontTest, TestInit)
{
    EXPECT_TRUE(FontManager::instance().init());
}