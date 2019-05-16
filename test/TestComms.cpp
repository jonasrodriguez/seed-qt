#include <gtest/gtest.h>

TEST(TestComms, Test1) {
  int x = 1;
  int y = 2;
  ASSERT_EQ(x + x, y);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
