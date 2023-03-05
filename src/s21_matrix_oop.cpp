#include "s21_matrix_oop.h"

#include <iostream>

using namespace std;

S21Matrix::S21Matrix() : rows_(1), cols_(1) {
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
    throw invalid_argument("Invalid number of rows " + to_string(rows));
  }
  if (cols < 1) {
    throw invalid_argument("Invalid number of cols " + to_string(cols));
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

S21Matrix S21Matrix::Transpose() {
  S21Matrix other(cols_, rows_);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      other.matrix_[i][j] = matrix_[j][i];
    }
  }
  return other;
}

S21Matrix S21Matrix::Minor(int i, int j) {
  checkIndexes(i, j);
  int rows = rows_ - 1, cols = cols_ - 1;
  if (rows_ == 1) rows = 1;
  if (cols_ == 1) cols = 1;
  S21Matrix minor(rows, cols);
  int k = 0, l;
  for (int m = 0; m < rows_; m++) {
    if (i == m && rows_ != 1) continue;
    l = 0;
    for (int r = 0; r < cols_; r++) {
      if (j == r && cols_ != 1) continue;
      minor(k, l) = (*this)(m, r);
      if (cols_ != 1) l++;
    }
    if (rows_ != 1) k++;
  }
  return minor;
}

double S21Matrix::Determinant() {
  // int s21_determinant(matrix_t *A, double result) {
  int err = 0, ok = 0;
  double quotient = 0, sign = 1, result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix tmp(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    for (int i = 0; i < tmp.rows_; i++) {
      if (tmp.matrix_[i][i] == 0) {
        ok = swap_rows(&tmp, i);
        sign = -sign;
      }
      if (!ok) {
        for (int j = i + 1; j < tmp.rows_; j++) {
          quotient = tmp.matrix_[j][i] / tmp.matrix_[i][i];
          for (int x = i; x < tmp.cols_; x++) {
            tmp.matrix_[j][x] =
                tmp.matrix_[j][x] - quotient * tmp.matrix_[i][x];
          }
        }
        result *= tmp.matrix_[i][i];
      } else {
        result = 0;
        break;
      }
    }
    if (!ok) result *= sign;
  }
  return result;
}

// S21Matrix S21Matrix::CalcComplements() {}

double& S21Matrix::operator()(int i, int j) {
  checkIndexes(i, j);
  return matrix_[i][j];
}

void S21Matrix::operator=(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  alocMatrix(&matrix_, rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  cout << "  WHAT THE MATRIX rows: " << rows_ << " cols: " << cols_ << endl;
  // return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double& num) {
  S21Matrix res(*this);
  MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

void S21Matrix::checkIndexes(int i, int j) {
  if (i < 0 || i > rows_ - 1) {
    throw invalid_argument(
        "Invalid argument i - number of rows must be grater or equal 0");
  }
  if (j < 0 || j > cols_ - 1) {
    throw invalid_argument(
        "Invalid argument j - number of cols must be grater or equal 0");
  }
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
  int rows = 3;
  int cols = 3;
  const double num = 100.001;
  // S21Matrix other(4, 4);
  // S21Matrix basic(rows, cols);
  S21Matrix basic(rows, cols);
  // S21Matrix other(4, 4);

  basic(0, 0) = 1.01;
  basic(0, 1) = 2.02;
  basic(0, 2) = 3.03;
  basic(1, 0) = 4.04;
  basic(1, 1) = 5.05;
  basic(1, 2) = 6.06;
  basic(2, 0) = 7.07;
  basic(2, 1) = 8.08;
  basic(2, 2) = 9.09;

  // S21Matrix basic2(rows, cols);
  // // S21Matrix other(4, 4);

  // basic2(0, 0) = 11.01;
  // basic2(0, 1) = 22.02;
  // basic2(0, 2) = 33.03;
  // basic2(0, 3) = 44.04;
  // basic2(1, 0) = 55.05;
  // basic2(1, 1) = 66.06;
  // basic2(1, 2) = 77.07;
  // basic2(1, 3) = 88.08;

  // S21Matrix sum(rows, cols);
  // print(sum, "SUM BEFORE SUMM");
  // print(basic2, "BASIC2 BEFORE SUMM:");
  // // S21Matrix copy(basic * num);
  // sum = basic2 + basic;
  // // sum = basic2;
  // for (int i = 0; i < 3; i++) {
  //   sum += basic;
  // }
  // print(sum, "SUM BETWEEN += AND -=:");
  // for (int i = 0; i < 3; i++) {
  //   sum -= basic;
  // }
  // print(basic2, "BASIC2 AFTER SUMM:");
  // print(sum, "SUM AFTER SUMM:");

  int row_o = 3, col_o = 3;
  S21Matrix other(row_o, col_o);
  other(0, 0) = 1.01;
  other(0, 1) = 1.88;
  other(0, 2) = 1.98;
  other(1, 0) = 2.4;
  other(1, 1) = 3.1;
  other(1, 2) = 3.2;
  other(2, 0) = 1.2;
  other(2, 1) = 2.123;
  other(2, 2) = 2.223;

  print(other, "OTHER BEFORE TRANSP");
  // S21Matrix copy(basic * num);
  // for (int i = 0; i < 3; i++) {
  //   other *= basic;
  // }
  S21Matrix transp = other.Transpose();
  S21Matrix minor = transp.Minor(1, 0);
  print(transp, "OTHER AFTER TRANSP:");
  print(minor, "MINOR OF TRANSP:");
  // (basic * num);
  // other.MulMatrix(basic);
  // S21Matrix* ptr_other = &other;
  S21Matrix copy(basic);
  copy.SumMatrix(basic);
  // other = copy;
  // S21Matrix *ptr_basic = &basic;
  // ptr_basic->S21Matrix();

  // print(other, "OTHER AFTER EQ:");

  // basic.SubMatrix(other);
  // basic.MulNumber(num);

  print(basic, "BASIC AFTER MULT:");

  cout << "EQUAL:" << endl;
  if (copy == other) {
    cout << "TRUE" << endl;
  } else {
    cout << "FALSE" << endl;
  }
  // cout << basic.getCount() << endl;
  return 0;
}
