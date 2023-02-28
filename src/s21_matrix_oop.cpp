#include "s21_matrix_oop.h"

#include <cstring>
#include <functional>
#include <iostream>

using namespace std;

S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  cout << "Constructor 1 address: " << this << endl;
  alocMatrix(&matrix_, rows_, cols_);
  // nCount++;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  cout << "Constructor 2 address: " << this << endl;
  alocMatrix(&matrix_, rows_, cols_);
  cout << " NEW MATRIX WITH rows: " << rows_ << " cols: " << cols_ << endl;

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

// void S21Matrix::mainLoop(int& rows, int& cols,
//                          void (*func)(int, int, S21Matrix)) {
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       func(i, j, S21Matrix&);
//     }
//   }
// }

void S21Matrix::alocMatrix(double*** matrix, int& rows, int& cols) {
  if (rows < 1) {
    throw invalid_argument("Invalid number of rows" + to_string(rows));
  }
  if (cols < 1) {
    throw invalid_argument("Invalid number of cols" + to_string(cols));
  }
  *matrix = new double*[rows];
  for (int i = 0; i < rows; i++) {
    (*matrix)[i] = new double[cols]();
  }
}

int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
double** S21Matrix::getMatrix() const { return matrix_; }

void S21Matrix::setRows(int& rows) const { rows_ = rows; }

void S21Matrix::setCols(int& cols) const { cols_ = cols; }

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
  if (other.rows_ != cols_) {
    throw invalid_argument(
        "Invalid argument the number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      double sum = 0;
      for (int k = 0; k < cols_; k++) {
        sum += matrix_[i][k] * other.matrix_[k][j];
      }
      res.matrix_[i][j] = sum;
    }
  }
  *this = res;
}

double& S21Matrix::operator()(int i, int j) { return matrix_[i][j]; }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  alocMatrix(&matrix_, rows_, cols_);
  cout << "  WHAT THE MATRIX rows: " << rows_ << " cols: " << cols_ << endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

void print(S21Matrix& other, string comment) {
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

int main(void) {
  int rows = 2;
  int cols = 4;
  const double num = 100.001;
  // S21Matrix other(4, 4);
  // S21Matrix basic(rows, cols);
  S21Matrix basic(rows, cols);
  // S21Matrix other(4, 4);

  basic(0, 0) = 10.01;
  basic(0, 1) = 20.02;
  basic(0, 2) = 30.03;
  basic(0, 3) = 40.04;
  basic(1, 0) = 50.05;
  basic(1, 1) = 60.06;
  basic(1, 2) = 70.07;
  basic(1, 3) = 80.08;

  int row_o = 3, col_o = 2;
  S21Matrix other(row_o, col_o);
  other(0, 0) = 1.01;
  other(0, 1) = 10.88;
  other(1, 0) = 24;
  other(1, 1) = 31;
  other(2, 0) = 12;
  other(2, 1) = 2.123;

  print(basic, "BASIC BEFORE MULT");

  other.MulMatrix(basic);
  // S21Matrix* ptr_other = &other;
  S21Matrix copy(basic);
  copy.SumMatrix(basic);
  other = copy - basic;
  // S21Matrix *ptr_basic = &basic;
  // ptr_basic->S21Matrix();

  print(other, "OTHER:");

  // basic.SubMatrix(other);
  // basic.MulNumber(num);

  print(basic, "BASIC AFTER MULT");

  cout << "EQUAL:" << endl;
  if (basic.EqMatrix(other)) {
    cout << "TRUE" << endl;
  } else {
    cout << "FALSE" << endl;
  }
  // cout << basic.getCount() << endl;
  return 0;
}
