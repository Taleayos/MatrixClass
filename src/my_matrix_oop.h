#ifndef CPP_My_MATRIXPLUS_2_SRC_MY_MATRIX_OOP_H_
#define CPP_My_MATRIXPLUS_2_SRC_MY_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <random>

class MyMatrix;
double RandomNum();
void SetMatrixLine(MyMatrix *a, double *mass);
void SetMatrixRandom(MyMatrix *a);
void PrintMatrix(MyMatrix a);
MyMatrix operator*(const double number, const MyMatrix &other);
MyMatrix operator*(const MyMatrix &other, const double number);

class MyMatrix {
  friend void SetMatrixLine(MyMatrix *a, double *mass);
  friend void SetMatrixRandom(MyMatrix *a);
  friend MyMatrix operator*(const double number, const MyMatrix &other);
  friend MyMatrix operator*(const MyMatrix &other, const double number);

 public:
  MyMatrix();
  MyMatrix(int rows_value, int col_value);
  MyMatrix(const MyMatrix &other);
  MyMatrix(MyMatrix &&other) noexcept;
  ~MyMatrix();

  int GetRows();
  int GetCols();
  void SetRowsCols(int r_value, int c_value);

  //МЕТОДЫ
  bool EqMatrix(const MyMatrix &other) const noexcept;
  void SumMatrix(const MyMatrix &other);
  void SubMatrix(const MyMatrix &other);
  void MulNumber(const double num);
  void MulMatrix(const MyMatrix &other);
  MyMatrix Transpose();
  MyMatrix CalcComplements();
  double Determinant();
  MyMatrix InverseMatrix();

  //ОПЕРАТОРЫ
  MyMatrix &operator=(MyMatrix &&other);
  MyMatrix &operator=(const MyMatrix &other);
  bool operator==(const MyMatrix &other) const noexcept;
  MyMatrix operator+(const MyMatrix &other);
  MyMatrix &operator+=(const MyMatrix &other);
  MyMatrix operator-(const MyMatrix &other);
  MyMatrix &operator-=(const MyMatrix &other);
  MyMatrix operator*(const MyMatrix &other);
  MyMatrix &operator*=(const MyMatrix &other);
  MyMatrix &operator*=(const double number);
  double &operator()(const int i, const int j) const;
  double &operator()(int i, int j);

 private:
  int rows_, cols_;
  double **matrix_;

  double _Minor(int row, int col);
  void _Clear();
  void _Create();
  void _CheckDiagonal();
};

#endif  // CPP_My_MATRIXPLUS_2_SRC_MY_MATRIX_OOP_H_
