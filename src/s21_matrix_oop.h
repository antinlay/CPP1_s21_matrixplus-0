#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#define EPS 10E-9

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();

  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  // OPERTATORS:
  double& operator()(int i, int j);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double& num);
  bool operator==(const S21Matrix& other) const;
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double& num);

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

  // ADDITIONAL FUNCTIONS:
  void AlocMatrix(double*** matrix, int& rows, int& cols);
  void DelMatrix(double** matrix);
  void CheckIndexes(int i, int j);
  void SwapMaxRows(double** matrix, int maxrow, int j);
  double GaussDet();
  int CheckZero();
  // Setters and getters
  int GetRows() const;
  int GetCols() const;
  double** GetMatrix() const;

  void SetRows(int rows);
  void SetCols(int cols);

  ~S21Matrix();
};

#endif