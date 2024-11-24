#include <myminus.h>
#include <gtest/gtest.h>

TEST(MinusTest, Minus1) { EXPECT_EQ(1, minus(2, 1)); }

TEST(MinusTest, Minus2) { EXPECT_EQ(-1, minus(3, 4)); }
