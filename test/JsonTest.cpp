#include <gtest/gtest.h>

#include <JsonReader.h>

TEST(JsonTest, LoadJson)
{
    DynamicJsonDocument json(65535);
    EXPECT_TRUE(load_json(json ,"json/objects.json"));
    json.clear();
    EXPECT_TRUE(load_json(json ,"json/maptiles.json"));
    json.clear();
    EXPECT_TRUE(load_json(json ,"json/map.json"));
    json.clear();
}