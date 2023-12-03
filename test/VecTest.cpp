#include <gtest/gtest.h>

#include <Vec.h>
#include <Vecmath.h>

TEST(VecTest, Mul) {
    Vec a(1,1);
    Vec res_a(3,3);
    double mul = 3;
    auto result = Vecmath::multiply(a, mul);
    EXPECT_EQ(result, res_a);
}