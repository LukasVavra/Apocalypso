#include <gtest/gtest.h>
#include <EventSystem.h>

#define eventsys EventSystem::instance()

struct test_data
{
    int id;
    const char* text;
};

void test_callback(void* data)
{
    auto d = (test_data*) data;
    EXPECT_EQ(d->id, 10);
    EXPECT_EQ(d->text, "hello");
}

TEST(EventTest, SubscribeMaxCallbacks) {
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_TRUE(eventsys.subscribe(EventId::QUIT, test_callback));
    EXPECT_FALSE(eventsys.subscribe(EventId::QUIT, test_callback));
}

TEST(EventTest, Emit) {
    test_data data;
    data.id = 10;
    data.text = "hello";
    eventsys.emit(EventId::QUIT, &data);
}