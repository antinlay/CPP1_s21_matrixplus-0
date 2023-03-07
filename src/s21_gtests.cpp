#include <cstdarg>

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

void printq(S21Matrix& other, string comment) {
  cout << comment << endl;
  cout << "rows: " << other.getRows() << " cols: " << other.getCols() << endl;
  if (other.getMatrix()) {
    for (int i = 0; i < other.getRows(); i++) {
      for (int j = 0; j < other.getCols(); j++) {
        cout << other(i, j) << " ";
      }
      cout << endl;
    }
  }
}
TEST(Matrix, Constructors) {
  S21Matrix left;
  left(0, 0) = 11.11;
  S21Matrix right(1, 1);
  right(0, 0) = 11.11;
  EXPECT_EQ(left, right);
}

TEST(Matrix, Copy) {
  S21Matrix basic(2, 2);
  basic(0, 0) = 11.11;
  basic(0, 1) = 12.12;
  basic(1, 0) = 21.21;
  basic(1, 1) = 31.31;
  S21Matrix copy(basic);
  EXPECT_EQ(basic, copy);
}

TEST(Matrix, Move) {
  S21Matrix basic(2, 2);
  basic(0, 0) = 11.11;
  basic(0, 1) = 12.12;
  basic(1, 0) = 21.21;
  basic(1, 1) = 31.31;
  S21Matrix copy(basic);
  S21Matrix mv(move(basic));
  EXPECT_EQ(mv, copy);
  EXPECT_FALSE(mv == basic);
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

TEST(Matrix, Operations) {
  S21Matrix basic(3, 3);
  basic(0, 0) = 1;
  basic(0, 1) = 2;
  basic(0, 2) = 4;
  basic(1, 0) = 3;
  basic(1, 1) = 3;
  basic(1, 2) = 5;
  basic(2, 0) = 2;
  basic(2, 1) = 4;
  basic(2, 2) = 4;

  S21Matrix one(3, 3);
  one(0, 0) = 1.0;
  one(0, 1) = 0.0;
  one(0, 2) = 0.0;
  one(1, 0) = 0.0;
  one(1, 1) = 1.0;
  one(1, 2) = 0.0;
  one(2, 0) = 0.0;
  one(2, 1) = 0.0;
  one(2, 2) = 1.0;

  S21Matrix calc(3, 3);
  calc = basic.InverseMatrix();
  EXPECT_TRUE(calc == basic.InverseMatrix());
  calc.MulMatrix(basic);
  for (auto i = 0; i < calc.getRows(); i++) {
    for (auto j = 0; j < calc.getCols(); j++) {
      EXPECT_EQ(round(calc.getMatrix()[i][j]), one.getMatrix()[i][j]);
    }
  }
  // printq(calc, "CALC MATRIX: ");
  // printq(one, "ONE MATRIX: ");
  // EXPECT_EQ(one.getMatrix(), calc.getMatrix());
  S21Matrix det(5, 5);
  EXPECT_EQ(round(det.Determinant()), 0.0);
}

TEST(Matrix, Operators) {
  S21Matrix basic(3, 3);
  basic(0, 0) = 11.01;
  basic(0, 1) = 22.02;
  basic(0, 2) = 33.03;
  basic(1, 0) = 44.04;
  basic(1, 1) = 55.05;
  basic(1, 2) = 66.06;
  basic(2, 0) = 77.07;
  basic(2, 1) = 88.08;
  basic(2, 2) = 99.09;

  S21Matrix sum(3, 3);
  sum = basic + basic;
  basic * 2.0;
  EXPECT_EQ(sum, basic);
  for (int i = 0; i < 3; i++) {
    sum += basic;
    sum *= 2.0;
    EXPECT_FALSE(sum == basic);
    sum *= 0.5;
    sum -= basic;
  }
  EXPECT_EQ(sum, basic);
  sum = sum * sum;
  basic = basic * basic;
  //   printq(sum, "SUM AFTER MULT: ");
  //   printq(basic, "basic AFTER MULT: ");
  EXPECT_EQ(basic, sum);
  basic = basic - sum;
  sum = sum - basic;
  //   printq(sum, "SUM AFTER SUB: ");
  //   printq(basic, "basic AFTER SUB: ");
  EXPECT_FALSE(basic == sum);
}

TEST(Matrix, Errors) {
  EXPECT_THROW(S21Matrix errors(-123, 0), invalid_argument);
  EXPECT_THROW(S21Matrix errors(1, 0), invalid_argument);
  S21Matrix error_sub_l(1, 55);
  S21Matrix error_sub_r(2, 55);
  EXPECT_THROW(error_sub_l -= error_sub_r, invalid_argument);
  EXPECT_THROW(error_sub_l += error_sub_r, invalid_argument);
  EXPECT_THROW(error_sub_l *= error_sub_r, invalid_argument);
  S21Matrix basic(4, 4);
  EXPECT_THROW(error_sub_l.Determinant(), runtime_error);
  EXPECT_THROW(error_sub_l.CalcComplements(), runtime_error);
  EXPECT_THROW(basic.InverseMatrix(), runtime_error);
  EXPECT_THROW(basic(-12, 1) = 1, out_of_range);
  EXPECT_THROW(basic(1, 123) = 14, out_of_range);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
