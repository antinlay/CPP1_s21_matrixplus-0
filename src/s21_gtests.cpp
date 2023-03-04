#include <cstdarg>

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(Matrix, Constructors) {
  S21Matrix left;
  left(0, 0) = 11.11;
  left(0, 1) = 12.12;
  left(1, 0) = 21.21;
  left(1, 1) = 31.31;
  // const S21Matrix *pt_left = &left;
  S21Matrix right(2, 2);
  left(0, 0) = 11.11;
  left(0, 1) = 12.12;
  left(1, 0) = 21.21;
  left(1, 1) = 31.31;
  // const S21Matrix *pt_right = &right;
  EXPECT_EQ(left, right);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // ::testing::Matrix(&argc, argv);
  return RUN_ALL_TESTS();
}
