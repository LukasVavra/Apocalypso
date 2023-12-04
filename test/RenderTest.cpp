#include <gtest/gtest.h>

#include <RenderSystem.h>

TEST(RenderTest, RendererPointer)
{
    EXPECT_TRUE(RenderSystem::renderer == nullptr);
}