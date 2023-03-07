#include "s21_matrix_oop.h"

// Constructors and destructor
S21Matrix::S21Matrix() : rows_(1), cols_(1) {
  cout << "Constructor 1 address: " << this << endl;
  alocMatrix(&matrix_, rows_, cols_);
  // nCount++;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  cout << "Constructor 2 address: " << this << endl;
  alocMatrix(&matrix_, rows_, cols_);
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
    delMatrix(matrix_);
  }
}
// Additional functions
void S21Matrix::alocMatrix(double*** matrix, int& rows, int& cols) {
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

void S21Matrix::delMatrix(double** matrix) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

void S21Matrix::checkIndexes(int i, int j) {
  if (i < 0 || i > rows_ - 1) {
    throw out_of_range("Invalid argument i - number of rows out of range [0:" +
                       to_string(rows_ - 1) + "]");
  }
  if (j < 0 || j > cols_ - 1) {
    throw out_of_range("Invalid argument j - number of cols out of range [0:" +
                       to_string(cols_ - 1) + "]");
  }
}

double** S21Matrix::getMatrix() const { return matrix_; }

// Accessor and mutator (Getters setters)
int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows == rows_) return;
  double** new_matrix;
  alocMatrix(&new_matrix, rows, cols_);
  for (int i = 0; i < rows && i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix[i][j] = (*this)(i, j);
    }
  }
  delMatrix(matrix_);
  rows_ = rows;
  matrix_ = new_matrix;
}

void S21Matrix::setCols(int cols) {
  if (cols == cols_) return;
  double** new_matrix;
  alocMatrix(&new_matrix, rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols && j < cols_; j++) {
      new_matrix[i][j] = (*this)(i, j);
    }
  }
  delMatrix(matrix_);
  cols_ = cols;
  matrix_ = new_matrix;
}
// Ariphmetic operations
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
      matrix_[i][j] = matrix_[i][j] * num;
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

S21Matrix S21Matrix::Minor(int i_row, int j_col) {
  checkIndexes(i_row, j_col);
  int rows = rows_ - 1, cols = cols_ - 1;
  if (rows_ == 1) rows = 1;
  if (cols_ == 1) cols = 1;
  S21Matrix minor(rows, cols);
  int k = 0, l;
  for (int r = 0; r < rows_; r++) {
    if (i_row == r && rows_ != 1) continue;
    l = 0;
    for (int c = 0; c < cols_; c++) {
      if (j_col == c && cols_ != 1) continue;
      minor(k, l) = (*this)(r, c);
      if (cols_ != 1) l++;
    }
    if (rows_ != 1) k++;
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw runtime_error(
        "Invalid argument of rows or cols the matrix is not square");
  }
  double result = 0;
  if (rows_ == 1) {
    result = (*this)(0, 0);
  } else {
    for (int j = 0; j < cols_; j++) {
      result += (*this)(0, j) * Minor(0, j).Determinant() * pow(-1, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw runtime_error(
        "Invalid argument of rows or cols the matrix is not square");
  }
  S21Matrix calc_compl(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      calc_compl(i, j) = Minor(i, j).Determinant() * pow(-1, i + j);
    }
  }
  return calc_compl;
}

S21Matrix S21Matrix::InverseMatrix() {
  const double det = Determinant();
  if (fabs(det) < EPS) {
    throw runtime_error("Error: matrix determinant is 0");
  }
  S21Matrix inverse(cols_, rows_);
  inverse = CalcComplements().Transpose();
  inverse.MulNumber(1 / det);
  return inverse;
}
// Operators + - * = == *= -= +=
double& S21Matrix::operator()(int i, int j) {
  checkIndexes(i, j);
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
