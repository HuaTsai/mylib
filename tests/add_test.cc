#include <myadd.h>
#include <gtest/gtest.h>

TEST(AddTest, Add1) { EXPECT_EQ(3, add(1, 2)); }

TEST(AddTest, Add2) { EXPECT_EQ(7, add(3, 4)); }
