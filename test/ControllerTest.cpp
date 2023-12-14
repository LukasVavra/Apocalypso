#include <gtest/gtest.h>
#include <ControllerSystem.h>
#include <iostream>

class TestController : public ControllerInterface
{
public:
    TestController(int v) : value(v)
    {
        std::cout << "TestController created, value: " << value << "\n";
    }
    virtual ~TestController() {std::cout << "TestController destroyed\n";}
    virtual void update(long unsigned id) override {std::cout << "TestController updated with id: " << id << "\n"; value++;}
    int value;
private:
};

class ControllerTest : public testing::Test 
{
protected:
    std::shared_ptr<ControllerInterface> controller;
    void SetUp() override
    {
        controller = ControllerSystem::instance().create_controller<TestController>(10);
    }
};

TEST_F(ControllerTest, CreateController)
{
    EXPECT_NE(controller, nullptr);
}

TEST_F(ControllerTest, UpdateTest)
{
    EXPECT_EQ(std::static_pointer_cast<TestController>(controller)->value, 10);
    ControllerSystem::instance().add(1, controller);
    EXPECT_NE(ControllerSystem::instance().get(1), nullptr);
    ControllerSystem::instance().update();
    EXPECT_EQ(std::static_pointer_cast<TestController>(controller)->value, 11);
}
