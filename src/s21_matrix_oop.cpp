#include "s21_matrix_oop.h"

#include <cstring>
#include <iostream>

using namespace std;

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  cout << "Constructor 1" << endl;
  aloc_matrix(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  cout << "Constructor 2" << endl;
  aloc_matrix(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  cout << "COPY" << endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix&& other)
    : S21Matrix(other.rows_, other.cols_) {
  cout << "MOVE" << endl;
  null_matrix(other);
}

S21Matrix::~S21Matrix() {
  cout << "Destructor RUN" << endl;
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

void S21Matrix::aloc_matrix(int rows, int cols) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::null_matrix(S21Matrix other) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

double& S21Matrix::operator()(int i, int j) { return matrix_[i][j]; }

int main(void) {
  int rows = 2;
  int cols = 2;
  // S21Matrix other(4, 4);
  // S21Matrix basic(rows, cols);
  S21Matrix basic;
  // S21Matrix other(4, 4);

  basic(0, 0) = 10.11;
  basic(0, 1) = 22.02;
  basic(1, 0) = 333.3;
  basic(1, 1) = 444.4;

  S21Matrix other(move(basic));

  // S21Matrix *ptr_basic = &basic;
  // ptr_basic->S21Matrix();
  cout << "OTHER:" << endl;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << other(i, j) << " ";
    }
    cout << endl;
  }

  cout << "BASIC:" << endl;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << basic(i, j) << " ";
    }
    cout << endl;
  }

  return 0;
}
