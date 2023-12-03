#include <gtest/gtest.h>
#include "Vec.h"
#include "Vecmath.h"

TEST(CalculatorTest, Add) {
    Vec a(1,1);
    Vec res_a(3,3);
    double mul = 3;
    auto result = Vecmath::multiply(a, mul);
    EXPECT_EQ(result, res_a);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}