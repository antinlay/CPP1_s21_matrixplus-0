#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();

  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(const S21Matrix&& other);

  // ADDITIONAL FUNCTIONS:
  void aloc_matrix(int rows, int cols);
  void null_matrix(S21Matrix other);
  // OPERTATORS:
  double& operator()(int i, int j);

  ~S21Matrix();
};

// S21Matrix ::S21Matrix(/* args */) {}

// S21Matrix ::~S21Matrix() {}

#endif