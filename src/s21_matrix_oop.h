#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

class S21Matrix {
 private:
  mutable int rows_, cols_;
  mutable double** matrix_;

 public:
  S21Matrix();

  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(const S21Matrix&& other);

  // OPERTATORS:
  double& operator()(int i, int j);

  // OPERATIONS
  bool EqMatrix(const S21Matrix& other) const;

  // ADDITIONAL FUNCTIONS:
  void alocMatrix(int& rows, int& cols);
  int getRows() const;
  int getCols() const;
  double** getMatrix() const;

  int setRows(int& rows) const;
  int setCols(int& cols) const;

  ~S21Matrix();
};

#endif