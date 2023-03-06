#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#define EPS 10E-9

#include <cmath>
#include <iostream>

using namespace std;

class S21Matrix {
 private:
  mutable int rows_, cols_;
  mutable double** matrix_;
  // static int nCount;

 public:
  S21Matrix();

  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(const S21Matrix&& other);

  // OPERTATORS:
  double& operator()(int i, int j);
  void operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double& num);
  bool operator==(const S21Matrix& other) const;
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);

  // OPERATIONS
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix Minor(int i, int j);
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  double Determinant();
  // S21Matrix InverseMatrix();

  // ADDITIONAL FUNCTIONS:
  void alocMatrix(double*** matrix, int& rows, int& cols);
  void delMatrix(double** matrix);
  int getRows() const;
  int getCols() const;
  // void mainLoop(int& rows, int& cols, void (*func)(int, int, S21Matrix));
  // void cpy(int i, int j, S21Matrix& other) {
  //   matrix_[i][j] = other.matrix_[i][j];
  // }
  // static int getCount() { return nCount; }
  double** getMatrix() const;

  void setRows(int rows);
  void setCols(int cols);
  void checkIndexes(int i, int j);

  ~S21Matrix();
};

// void print(S21Matrix& other, string comment);

#endif