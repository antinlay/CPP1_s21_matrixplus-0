#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1) {
  cout << "Constructor 1 address: " << this << endl;
  AlocMatrix(&matrix_, rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  cout << "Constructor 2 address: " << this << endl;
  AlocMatrix(&matrix_, rows_, cols_);
  cout << " NEW MATRIX WITH rows: " << rows_ << " cols: " << cols_ << endl;
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

S21Matrix::S21Matrix(S21Matrix&& other) {
  cout << "MOVE address: " << this << endl;
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

S21Matrix::~S21Matrix() {
  cout << "Destructor RUN address: " << this << endl;
  if (matrix_) {
    DelMatrix(matrix_);
  }
}
// Additional functions
void S21Matrix::AlocMatrix(double*** matrix, int& rows, int& cols) {
  if (rows < 1) {
    throw invalid_argument("Invalid number of rows " + to_string(rows));
  }
  if (cols < 1) {
    throw invalid_argument("Invalid number of cols " + to_string(cols));
  }
  *matrix = new double*[rows]();
  for (int i = 0; i < rows; i++) {
    (*matrix)[i] = new double[cols]();
  }
}

void S21Matrix::DelMatrix(double** matrix) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void S21Matrix::CheckIndexes(int i, int j) {
  if (i < 0 || i > rows_ - 1) {
    throw out_of_range("Invalid argument i - number of rows out of range [0:" +
                       to_string(rows_ - 1) + "]");
  }
  if (j < 0 || j > cols_ - 1) {
    throw out_of_range("Invalid argument j - number of cols out of range [0:" +
                       to_string(cols_ - 1) + "]");
  }
  double check = fabs(matrix_[i][j]) - floor(fabs(matrix_[i][j]));
  if (check < EPS) {
    if (fabs(matrix_[i][j]) < EPS) {
      matrix_[i][j] = 0.0;
    } else {
      matrix_[i][j] = floor(matrix_[i][j]);
    }
  }
}

double** S21Matrix::GetMatrix() const { return matrix_; }

// Accessor and mutator (Getters setters)
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows == rows_) return;
  double** new_matrix;
  AlocMatrix(&new_matrix, rows, cols_);
  for (int i = 0; i < rows && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix[i][j] = (*this)(i, j);
    }
  }
  DelMatrix(matrix_);
  rows_ = rows;
  matrix_ = new_matrix;
}

void S21Matrix::SetCols(int cols) {
  if (cols == cols_) return;
  double** new_matrix;
  AlocMatrix(&new_matrix, rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols && j < cols_; j++) {
      new_matrix[i][j] = (*this)(i, j);
    }
  }
  DelMatrix(matrix_);
  cols_ = cols;
  matrix_ = new_matrix;
}
// Ariphmetic operations
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(other.matrix_[i][j] - matrix_[i][j]) > EPS) return false;
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
      matrix_[i][j] = (*this)(i, j) * num;
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
        sum += (*this)(i, k) * other.matrix_[k][j];
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

S21Matrix S21Matrix::Minor(int i_row, int j_col) {
  CheckIndexes(i_row, j_col);
  int rows = rows_ - 1, cols = cols_ - 1;
  if (rows_ == 1) rows = 1;
  if (cols_ == 1) cols = 1;
  S21Matrix Minor(rows, cols);
  int k = 0, l;
  for (int r = 0; r < rows_; r++) {
    if (i_row == r && rows_ != 1) continue;
    l = 0;
    for (int c = 0; c < cols_; c++) {
      if (j_col == c && cols_ != 1) continue;
      Minor.matrix_[k][l] = (*this)(r, c);
      if (cols_ != 1) l++;
    }
    if (rows_ != 1) k++;
  }
  return Minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw runtime_error(
        "Invalid argument of rows or cols the matrix is not square");
  }
  double result = 0;
  if (CheckZero() == 1) {
    return 0.0;
  } else if (rows_ == 1) {
    result = (*this)(0, 0);
  } else if (rows_ == 2) {
    result = (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  } else if (rows_ < 5) {
    for (int j = 0; j < cols_; j++) {
      result += (*this)(0, j) * Minor(0, j).Determinant() * pow(-1, j);
    }
  } else {
    result = GaussDet();
  }
  return result;
}
// Swap rows
void S21Matrix::SwapMaxRows(double** matrix, int maxrow, int j) {
  for (int c = 0; c < cols_; c++) {
    double temp = matrix[j][c];
    matrix[j][c] = matrix[maxrow][c];
    matrix[maxrow][c] = temp;
  }
}
// Check rows or cols with only zero's
int S21Matrix::CheckZero() {
  int zero = 0;
  for (int i = 0; i < rows_; i++) {
    if ((*this)(i, 0) == 0) {
      for (int j = 1; j < cols_; j++) {
        for (int k = 1; k < cols_; k++) {
          if ((*this)(k, i) != 0) break;
          if ((k + 1) == cols_) zero = 1;
        }
        if ((*this)(i, j) != 0) break;
        if ((j + 1) == cols_) zero = 1;
      }
    }
  }
  return zero;
}
// Determinant
double S21Matrix::GaussDet() {
  S21Matrix Det(*this);
  int n = rows_;
  double res = 1.0;

  for (int i = 0; i < n; i++) {
    // Find max element in col(i)
    int maxrow = i;
    for (int j = i + 1; j < n; j++) {
      if (fabs(Det(j, i)) > fabs(Det(maxrow, i))) {
        maxrow = j;
      }
    }

    // Change of place rows i and maxrow
    if (i != maxrow) {
      SwapMaxRows(Det.matrix_, maxrow, i);
      res *= -1.0;
    }

    // Zero's all elements down main diagonal
    for (int j = i + 1; j < n; j++) {
      double factor = Det(j, i) / Det(i, i);
      for (int k = i + 1; k < n; k++) {
        Det.matrix_[j][k] -= factor * Det(i, k);
      }
      Det.matrix_[j][i] = 0.0;
    }

    // Calculate GaussDet
    res *= Det(i, i);
  }

  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw runtime_error(
        "Invalid argument of rows or cols the matrix is not square");
  }
  S21Matrix Calc(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      Calc.matrix_[i][j] = Minor(i, j).Determinant() * pow(-1, i + j);
    }
  }
  return Calc;
}

S21Matrix S21Matrix::InverseMatrix() {
  const double det = Determinant();
  if (fabs(det) < EPS) {
    throw runtime_error("Error: matrix GaussDet is 0");
  }
  S21Matrix Inverse(cols_, rows_);
  Inverse = CalcComplements().Transpose();
  Inverse.MulNumber(1 / det);
  return Inverse;
}
// Operators + - * = == *= -= +=
double& S21Matrix::operator()(int i, int j) {
  CheckIndexes(i, j);

  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  cout << "  WHAT THE MATRIX rows: " << rows_ << " cols: " << cols_ << endl;
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double& num) {
  S21Matrix res = *this;
  MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }
void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }
void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }
void S21Matrix::operator*=(const double& num) { MulNumber(num); }
