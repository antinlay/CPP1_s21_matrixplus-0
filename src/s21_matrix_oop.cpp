#include "s21_matrix_oop.hpp"

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
    (*matrix)[i] = new double[cols];
  }
}

void S21Matrix::delMatrix(double** matrix) {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
double** S21Matrix::getMatrix() const { return matrix_; }

void S21Matrix::setRows(int rows) {
  if (rows == rows_) return;
  // rows_ = rows;
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
    throw invalid_argument(
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
    throw invalid_argument(
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
  double det = Determinant();
  if (fabs(det) < EPS) {
    throw runtime_error("Error: matrix determinant is 0");
  }
  S21Matrix inverse(cols_, rows_);
  inverse = CalcComplements().Transpose();
  inverse.MulNumber(1 / det);
  return inverse;
}

double& S21Matrix::operator()(int i, int j) {
  checkIndexes(i, j);
  matrix_[i][j] =
      fabs(matrix_[i][j]) < EPS ? 0 : round(matrix_[i][j] / EPS) * EPS;
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
    throw out_of_range("Invalid argument i - number of rows out of range [0:" +
                       to_string(rows_ - 1) + "]");
  }
  if (j < 0 || j > cols_ - 1) {
    throw invalid_argument(
        "Invalid argument j - number of cols out of range [0:" +
        to_string(cols_ - 1) + "]");
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

// int main(void) {
//   int rows = 3;
//   int cols = 3;
//   const double num = 100.001;
//   double det = round(0.000000001 / EPS) * EPS;
//   // S21Matrix other(4, 4);
//   // S21Matrix basic(rows, cols);
//   S21Matrix basic(rows, cols);
//   // S21Matrix other(4, 4);

//   basic(0, 0) = 1;
//   basic(0, 1) = 2;
//   basic(0, 2) = 4;
//   basic(1, 0) = 3;
//   basic(1, 1) = 3;
//   basic(1, 2) = 5;
//   basic(2, 0) = 2;
//   basic(2, 1) = 4;
//   basic(2, 2) = 4;

//   det = basic.Determinant();
//   cout << det << endl;
//   S21Matrix calc(3, 3);
//   // calc = basic.CalcComplements();
//   // calc = calc.Transpose();
//   calc = basic.InverseMatrix();

//   calc.MulMatrix(basic);
//   calc.setRows(10);
//   calc.setCols(10);

//   print(calc, "CALC MATRIX: ");

//   // S21Matrix basic2(rows, cols);
//   // // S21Matrix other(4, 4);

//   // basic2(0, 0) = 11.01;
//   // basic2(0, 1) = 22.02;
//   // basic2(0, 2) = 33.03;
//   // basic2(0, 3) = 44.04;
//   // basic2(1, 0) = 55.05;
//   // basic2(1, 1) = 66.06;
//   // basic2(1, 2) = 77.07;
//   // basic2(1, 3) = 88.08;

//   // S21Matrix sum(rows, cols);
//   // print(sum, "SUM BEFORE SUMM");
//   // print(basic2, "BASIC2 BEFORE SUMM:");
//   // // S21Matrix copy(basic * num);
//   // sum = basic2 + basic;
//   // // sum = basic2;
//   // for (int i = 0; i < 3; i++) {
//   //   sum += basic;
//   // }
//   // print(sum, "SUM BETWEEN += AND -=:");
//   // for (int i = 0; i < 3; i++) {
//   //   sum -= basic;
//   // }
//   // print(basic2, "BASIC2 AFTER SUMM:");
//   // print(sum, "SUM AFTER SUMM:");

//   int row_o = 3, col_o = 3;
//   S21Matrix other(row_o, col_o);
//   other(0, 0) = 1;
//   other(0, 1) = 2;
//   other(0, 2) = 3;
//   other(1, 0) = 4;
//   other(1, 1) = 5;
//   other(1, 2) = 6;
//   other(2, 0) = 7;
//   other(2, 1) = 8;
//   other(2, 2) = 10;

//   print(other, "OTHER BEFORE TRANSP");
//   // S21Matrix copy(basic * num);
//   // for (int i = 0; i < 3; i++) {
//   //   other *= basic;
//   // }
//   S21Matrix transp = other.Transpose();
//   S21Matrix minor = transp.Minor(1, 0);
//   print(transp, "OTHER AFTER TRANSP:");
//   print(minor, "MINOR OF TRANSP:");
//   // (basic * num);
//   // other.MulMatrix(basic);
//   // S21Matrix* ptr_other = &other;
//   S21Matrix copy(basic);
//   copy.SumMatrix(basic);
//   // other = copy;
//   // S21Matrix *ptr_basic = &basic;
//   // ptr_basic->S21Matrix();

//   // print(other, "OTHER AFTER EQ:");

//   // basic.SubMatrix(other);
//   // basic.MulNumber(num);

//   print(basic, "BASIC AFTER MULT:");

//   cout << "EQUAL:" << endl;
//   if (copy == other) {
//     cout << "TRUE" << endl;
//   } else {
//     cout << "FALSE" << endl;
//   }
//   // cout << basic.getCount() << endl;
//   return 0;
// }
