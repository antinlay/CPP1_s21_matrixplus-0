#include "s21_matrix_oop.h"

#include <string.h>

#include <iostream>

using namespace std;

S21Matrix::S21Matrix() {
  rows_ = 2;
  cols_ = 2;
  aloc_matrix(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  aloc_matrix(rows_, cols_);
}

void S21Matrix::aloc_matrix(int rows, int cols) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    memset(matrix_[i], 0, sizeof(double) * cols_);
  }
}

double& S21Matrix::operator()(int i, int j) { return matrix_[i][j]; }

int main(void) {
  int rows = 2;
  int cols = 2;
  // S21Matrix basic(rows, cols);
  S21Matrix basic;

  // basic(0, 0) = 1.0;
  // basic(0, 1) = 22.0;
  // basic(1, 0) = 333.0;
  // basic(1, 1) = 444.0;

  // S21Matrix *ptr_basic = &basic;
  // ptr_basic->S21Matrix();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << basic(i, j) << " ";
    }
    cout << endl;
  }

  return 0;
}
