#include "s21_matrix_oop.h"

#include <cstring>
#include <iostream>

using namespace std;

S21Matrix::S21Matrix() {
  cout << "Constructor 1" << endl;
  int row_col = 2;
  setRows(row_col);
  setCols(row_col);
  alocMatrix(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  cout << "Constructor 2" << endl;
  if (setRows(rows)) {
    throw invalid_argument("Invalid number of rows" + to_string(rows));
  }
  if (setCols(cols)) {
    throw invalid_argument("Invalid number of cols" + to_string(cols));
  }
  alocMatrix(rows_, cols_);
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

S21Matrix::S21Matrix(const S21Matrix&& other) {
  cout << "MOVE" << endl;
  if (setRows(other.rows_)) {
    throw invalid_argument("Invalid number of rows" + to_string(other.rows_));
  }
  if (setCols(other.cols_)) {
    throw invalid_argument("Invalid number of cols" + to_string(other.cols_));
  }
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

S21Matrix::~S21Matrix() {
  cout << "Destructor RUN" << endl;
  if (this->matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void S21Matrix::alocMatrix(int& rows, int& cols) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
double** S21Matrix::getMatrix() const { return matrix_; }

int S21Matrix::setRows(int& rows) const {
  int err = 0;
  if (rows <= 0) {
    return err = 1;
  }
  if (rows == rows_) {
    return err = 1;
  }
  rows_ = rows;
  return err;
}

int S21Matrix::setCols(int& cols) const {
  int err = 0;
  if (cols <= 0) {
    return err = 1;
  }
  if (cols == cols_) {
    return err = 1;
  }
  cols_ = cols;
  return err;
}

bool EqMatrix(const S21Matrix& other) {
  if (getMatrix() == other.getMatrix()) return 1;
  return 0;
}

double& S21Matrix::operator()(int i, int j) { return matrix_[i][j]; }

int main(void) {
  int rows = 7;
  int cols = 11;
  // S21Matrix other(4, 4);
  // S21Matrix basic(rows, cols);
  S21Matrix basic(rows, cols);
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

  if (basic.getMatrix()) {
    cout << "BASIC:" << endl;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << basic(i, j) << " ";
      }
      cout << endl;
    }
  }
  return 0;
}
