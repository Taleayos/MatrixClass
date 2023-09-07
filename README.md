# MatrixLib - C++

## Implementation of the matrix_oop.h library on C++ language.

In this project, the matrix library with using the object-oriented approach realized. 

## Matrix operations

There is a brief description of the matrix operations below that is implemented in the developing library.

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const MyMatrix& other)` | Checks matrices for equality with each other |  |
| `void SumMatrix(const MyMatrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void SubMatrix(const MyMatrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number |  |
| `void MulMatrix(const Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `S21Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `S21Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double Determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `MyMatrix InverseMatrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |

- Full coverage of library functions code with unit-tests using the GTest library prepared
- A Makefile for building the library and tests (with targets all, clean, test, s21_matrix_oop.a) provided

