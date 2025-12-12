#include "math_utils.h"
#include <gtest/gtest.h>

// Test add() function
TEST(MathUtilsTest, AddPositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(MathUtilsTest, AddNegativeNumbers) {
    EXPECT_EQ(add(-1, -5), -6);
}

TEST(MathUtilsTest, AddMixedNumbers) {
    EXPECT_EQ(add(-2, 3), 1);
}

// Test multiply() function
TEST(MathUtilsTest, MultiplyPositiveNumbers) {
    EXPECT_EQ(multiply(2, 3), 6);
}

TEST(MathUtilsTest, MultiplyWithZero) {
    EXPECT_EQ(multiply(0, 10), 0);
}

TEST(MathUtilsTest, MultiplyNegativeNumbers) {
    EXPECT_EQ(multiply(-2, -3), 6);
}

TEST(MathUtilsTest, MultiplyMixedNumbers) {
    EXPECT_EQ(multiply(-2, 3), -6);
}

// Optional: check add and multiply together
TEST(MathUtilsTest, CombinedOperations) {
    int a = 3, b = 4;
    EXPECT_EQ(add(a, b), 7);
    EXPECT_EQ(multiply(a, b), 12);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
