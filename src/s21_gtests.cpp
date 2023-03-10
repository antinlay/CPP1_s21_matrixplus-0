#include <cstdarg>

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

void printq(S21Matrix& other, string comment) {
  cout << comment << endl;
  cout << "rows: " << other.GetRows() << " cols: " << other.GetCols() << endl;
  if (other.GetMatrix()) {
    for (int i = 0; i < other.GetRows(); i++) {
      for (int j = 0; j < other.GetCols(); j++) {
        cout << other(i, j) << " ";
      }
      cout << endl;
    }
  }
}

void fillMatrix(double* seq, S21Matrix& other) {
  int n = 0;
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetCols(); j++) {
      other(i, j) = seq[n++];
    }
  }
}

TEST(Matrix, Constructors) {
  S21Matrix left;
  left(0, 0) = 11.11;
  S21Matrix Right(1, 1);
  Right(0, 0) = 11.11;
  EXPECT_EQ(left, Right);
}

TEST(Matrix, Copy) {
  S21Matrix Basic(2, 2);
  double seq[] = {11.11, 12.12, 21.21, 31.31};
  fillMatrix(seq, Basic);
  printq(Basic, "Basic MATRIX: ");
  S21Matrix copy(Basic);
  EXPECT_EQ(Basic, copy);
}

TEST(Matrix, Move) {
  S21Matrix Basic(2, 2);
  double seq[] = {11.11, 12.12, 21.21, 31.31};
  fillMatrix(seq, Basic);
  S21Matrix copy(Basic);
  S21Matrix Move(move(Basic));
  printq(Basic, "Basic MATRIX: ");
  printq(Move, "Move MATRIX: ");
  EXPECT_EQ(Move, copy);
  EXPECT_FALSE(Move == Basic);
}

TEST(Matrix, SetterGetter) {
  S21Matrix Right(123, 911);
  EXPECT_EQ(Right.GetCols(), 911);
  EXPECT_EQ(Right.GetRows(), 123);
  Right.SetRows(2);
  EXPECT_EQ(Right.GetRows(), 2);
  Right.SetCols(20);
  EXPECT_EQ(Right.GetCols(), 20);
}

TEST(Matrix, Operations) {
  S21Matrix Basic(3, 3);
  double seq[] = {1, 2, 4, 3, 3, 5, 2, 4, 4};
  fillMatrix(seq, Basic);
  S21Matrix One(3, 3);
  double seq_one[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  fillMatrix(seq_one, One);
  S21Matrix Calc(3, 3);
  Calc = Basic.InverseMatrix();
  EXPECT_TRUE(Calc == Basic.InverseMatrix());
  Calc.MulMatrix(Basic);
  printq(Calc, "Calc MATRIX: ");
  printq(One, "One MATRIX: ");
  EXPECT_EQ(One, Calc);
}

TEST(Matrix, Determinant) {
  S21Matrix Det = S21Matrix();
  Det(0, 0) = 214214321.4325452;
  EXPECT_EQ(Det.Determinant(), Det(0, 0));
  Det.SetCols(4);
  Det.SetRows(4);
  double seq[] = {1, 2, 3, 5, 6, 1, 12, 3, 0, 11, 2, 33, 7, 68, 9, 71};
  fillMatrix(seq, Det);
  double det = -6984.0;
  EXPECT_EQ(Det.Determinant(), det);
  Det.SetCols(80);
  Det.SetRows(80);
  EXPECT_EQ(Det.Determinant(), 0.0);
  for (int i = 0; i < Det.GetRows(); i++) {
    for (int j = 0; j < Det.GetCols(); j++) {
      Det(i, j) = (random() % 1000) * 0.01;
    }
  }
  cout << "DETERMINANT " + to_string(Det.Determinant()) << endl;
  det = Det.Determinant();
  EXPECT_EQ(det, Det.Determinant());
  // printq(Det, "Det MATRIX: ");
}

TEST(Matrix, Operators) {
  S21Matrix Basic(3, 3);
  double seq[] = {11.01, 22.02, 33.03, 44.04, 55.05,
                  66.06, 77.07, 88.08, 99.09};
  fillMatrix(seq, Basic);
  S21Matrix Sum(3, 3);
  Sum = Basic + Basic;
  Basic * 2.0;
  EXPECT_EQ(Sum, Basic);
  for (int i = 0; i < 3; i++) {
    Sum += Basic;
    Sum *= 2.0;
    EXPECT_FALSE(Sum == Basic);
    Sum *= 0.5;
    Sum -= Basic;
  }
  EXPECT_EQ(Sum, Basic);
  Sum = Sum * Sum;
  Basic = Basic * Basic;
  //   printq(Sum, "Sum AFTER MULT: ");
  //   printq(Basic, "Basic AFTER MULT: ");
  EXPECT_EQ(Basic, Sum);
  Basic = Basic - Sum;
  Sum = Sum - Basic;
  //   printq(Sum, "Sum AFTER SUB: ");
  //   printq(Basic, "Basic AFTER SUB: ");
  EXPECT_FALSE(Basic == Sum);
}

TEST(Matrix, Errors) {
  EXPECT_THROW(S21Matrix errors(-123, 0), invalid_argument);
  EXPECT_THROW(S21Matrix errors(1, 0), invalid_argument);
  S21Matrix error_sub_l(1, 55);
  S21Matrix error_sub_r(2, 55);
  EXPECT_THROW(error_sub_l -= error_sub_r, invalid_argument);
  EXPECT_THROW(error_sub_l += error_sub_r, invalid_argument);
  EXPECT_THROW(error_sub_l *= error_sub_r, invalid_argument);
  S21Matrix Basic(4, 4);
  EXPECT_THROW(error_sub_l.Determinant(), runtime_error);
  EXPECT_THROW(error_sub_l.CalcComplements(), runtime_error);
  EXPECT_THROW(Basic.InverseMatrix(), runtime_error);
  EXPECT_THROW(Basic(-12, 1) = 1, out_of_range);
  EXPECT_THROW(Basic(1, 123) = 14, out_of_range);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
