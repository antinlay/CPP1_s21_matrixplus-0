#include <cstdarg>

#include "gtest/gtest.h"
#include "s21_matrix_oop.hpp"

TEST(Matrix, Constructors) {
  S21Matrix left;
  left(0, 0) = 11.11;
  S21Matrix right(1, 1);
  right(0, 0) = 11.11;
  EXPECT_EQ(left, right);
  left.setRows(2);
  left.setCols(2);
  left(1, 0) = 12.12;
  left(1, 0) = 21.21;
  left(1, 1) = 31.31;
  // const S21Matrix *pt_left = &left;
  S21Matrix copy(right);
  EXPECT_EQ(right, copy);
  S21Matrix mv(move(copy));
  EXPECT_EQ(mv, right);
}

TEST(Matrix, SetterGetter) {
  S21Matrix right(123, 911);
  EXPECT_EQ(right.getCols(), 911);
  EXPECT_EQ(right.getRows(), 123);
  right.setRows(2);
  EXPECT_EQ(right.getRows(), 2);
  right.setCols(20);
  EXPECT_EQ(right.getCols(), 20);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // ::testing::Matrix(&argc, argv);
  return RUN_ALL_TESTS();
}
