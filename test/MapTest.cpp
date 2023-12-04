#include <gtest/gtest.h>
#include <MapManager.h>
#include <Camera.h>

TEST(MapTest, Camera)
{
    EXPECT_TRUE(MapManager::instance().get_camera() == nullptr);
    Camera camera;
    MapManager::instance().set_camera(&camera);
    EXPECT_TRUE(MapManager::instance().get_camera() == &camera);
}

TEST(MapTest, UpdateRenderBounds)
{
    MapManager::instance().set_camera(nullptr);
    EXPECT_TRUE(MapManager::instance().get_camera() == nullptr);

    int a = 0, b = 0, c = 0, d = 0;
    EXPECT_TRUE(a == 0 && b == 0 && c == 0 && d == 0);

    Camera camera;
    camera.set_map_size(1000, 1000);
    camera.resize(100, 200);
    Vec viewpoint{300,200};
    camera.update_viewpoint(&viewpoint);
    MapManager::instance().set_camera(&camera);
    EXPECT_TRUE(MapManager::instance().get_camera() == &camera);

    MapManager::instance().update_render_bounds(a, b, c, d);
    EXPECT_EQ(a, 3);
    EXPECT_EQ(b, 1);
    EXPECT_EQ(c, 6);
    EXPECT_EQ(d, 5);
}