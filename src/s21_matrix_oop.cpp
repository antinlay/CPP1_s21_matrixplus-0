#include "s21_matrix_oop.h"

#include <cstring>
#include <iostream>

using namespace std;

S21Matrix::S21Matrix() {
  cout << "Constructor 1 address: " << this << endl;
  int row_col = 2;
  setRows(row_col);
  setCols(row_col);
  alocMatrix(rows_, cols_);
  // nCount++;
}

S21Matrix::S21Matrix(int rows, int cols) {
  cout << "Constructor 2 address: " << this << endl;
  if (setRows(rows)) {
    throw invalid_argument("Invalid number of rows" + to_string(rows));
  }
  if (setCols(cols)) {
    throw invalid_argument("Invalid number of cols" + to_string(cols));
  }
  alocMatrix(rows_, cols_);
  // nCount++;
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  cout << "COPY address: " << this << endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix&& other) {
  cout << "MOVE address: " << this << endl;
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
  cout << "Destructor RUN address: " << this << endl;
  if (matrix_) {
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
    return err = 0;
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

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Invalid argument different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw invalid_argument("Invalid argument different matrix dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw invalid_argument(
        "Invalid argument the number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

double& S21Matrix::operator()(int i, int j) { return matrix_[i][j]; }

int main(void) {
  int rows = 2;
  int cols = 4;
  const double num = 100.001;
  // S21Matrix other(4, 4);
  // S21Matrix basic(rows, cols);
  S21Matrix basic(rows, cols);
  // S21Matrix other(4, 4);

  basic(0, 0) = 10.11;
  basic(0, 1) = 22.02;
  basic(0, 2) = 10.11;
  basic(0, 3) = 22.02;
  basic(1, 0) = 333.3;
  basic(1, 1) = 444.4;
  basic(1, 2) = 333.3;
  basic(1, 3) = 444.4;

  S21Matrix other((basic));
  other.SumMatrix(basic);

  // S21Matrix *ptr_basic = &basic;
  // ptr_basic->S21Matrix();
  cout << "OTHER:" << endl;
  if (other.getMatrix()) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << other(i, j) << " ";
      }
      cout << endl;
    }
  }
  basic.SubMatrix(other);
  basic.MulNumber(num);
  if (basic.getMatrix()) {
    cout << "BASIC SUB & MULT:" << endl;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << basic(i, j) << " ";
      }
      cout << endl;
    }
  }
  cout << "EQUAL:" << endl;
  if (basic.EqMatrix(other)) {
    cout << "TRUE" << endl;
  } else {
    cout << "FALSE" << endl;
  }
  // cout << basic.getCount() << endl;
  return 0;
}
