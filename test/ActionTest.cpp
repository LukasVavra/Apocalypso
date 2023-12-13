#include <gtest/gtest.h>

#include <PositionSystem.h>
#include <ActionSystem.h>
#include <OperationManager.h>
#include <vector>

long unsigned id1 = 10, id2 = 11;

static int counter = 0;

class TestOp : public OperationInterface
    {
    public:
        virtual bool run(long unsigned actor_id, long unsigned reactor_id) override
        {
            counter++;
            return true;
        }
    };

    TestOp op;

class ActionTest : public testing::Test 
{
protected:
    Vec nextpos{0, 0};

    void SetUp() override
    {
        // prepare positions
        PositionSystem::instance().add(id1, Vec(100, 100));
        PositionSystem::instance().add(id2, Vec(200, 100));
        // prepare actions
        std::vector<OperationId> actor, reactor;
        actor.push_back(1);
        reactor.push_back(1);
        ActionSystem::instance().add(id1, 25, 25, 50, 50, actor, reactor);
        ActionSystem::instance().add(id2, 25, 25, 50, 50, actor, reactor);
        OperationManager::instance().add(&op);
    }
};

TEST_F(ActionTest, TestInitialization)
{
    EXPECT_FALSE(ActionSystem::instance().get(id1) == nullptr);
    EXPECT_FALSE(ActionSystem::instance().get(id2) == nullptr);
    EXPECT_EQ(ActionSystem::instance().get(id1)->actor_op.size(), 1);
    EXPECT_EQ(ActionSystem::instance().get(id1)->reactor_op.size(), 1);
    EXPECT_EQ(ActionSystem::instance().get(id2)->actor_op.size(), 1);
    EXPECT_EQ(ActionSystem::instance().get(id2)->reactor_op.size(), 1);
}

TEST_F(ActionTest, AssignOp)
{
    ActionSystem::instance().assign_op(id1,2, true);
    ActionSystem::instance().assign_op(id1,3, true);
    ActionSystem::instance().assign_op(id2,2, true);
    ActionSystem::instance().assign_op(id1,2, false);
    ActionSystem::instance().assign_op(id1,3, false);
    ActionSystem::instance().assign_op(id2,2, false);
    EXPECT_EQ(ActionSystem::instance().get(id1)->actor_op.size(), 3);
    EXPECT_EQ(ActionSystem::instance().get(id1)->reactor_op.size(), 3);
    EXPECT_EQ(ActionSystem::instance().get(id2)->actor_op.size(), 2);
    EXPECT_EQ(ActionSystem::instance().get(id2)->reactor_op.size(), 2);
}

TEST_F(ActionTest, UnassignOp)
{
    ActionSystem::instance().unassign_op(id1,2, true);
    ActionSystem::instance().unassign_op(id1,3, true);
    ActionSystem::instance().unassign_op(id2,2, true);
    ActionSystem::instance().unassign_op(id1,2, false);
    ActionSystem::instance().unassign_op(id1,3, false);
    ActionSystem::instance().unassign_op(id2,2, false);
    EXPECT_EQ(ActionSystem::instance().get(id1)->actor_op.size(), 1);
    EXPECT_EQ(ActionSystem::instance().get(id1)->reactor_op.size(), 1);
    EXPECT_EQ(ActionSystem::instance().get(id2)->actor_op.size(), 1);
    EXPECT_EQ(ActionSystem::instance().get(id2)->reactor_op.size(), 1);
}

TEST_F(ActionTest, TriggerNegative)
{
    EXPECT_FALSE(ActionSystem::instance().trigger_action(id1, 1));
    EXPECT_EQ(counter, 0);
}

TEST_F(ActionTest, TriggerPositive)
{
    ActionSystem::instance().get(id1)->area.x = 149;
    EXPECT_TRUE(ActionSystem::instance().trigger_action(id1, 1));
    EXPECT_EQ(counter, 1);
}