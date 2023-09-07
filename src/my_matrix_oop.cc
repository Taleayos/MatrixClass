#include "my_matrix_oop.h"

MyMatrix::MyMatrix() : rows_(10), cols_(10) { _Create(); }

MyMatrix::MyMatrix(int rows_value, int col_value)
    : rows_(rows_value), cols_(col_value) {
  _Create();
}
void MyMatrix::_Create() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range(
        "ERROR! Incorrect input. Rows and colomns must be greater than 0");
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

MyMatrix::MyMatrix(const MyMatrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  _Create();
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

MyMatrix::MyMatrix(MyMatrix &&other) noexcept {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int MyMatrix::GetRows() { return rows_; }
int MyMatrix::GetCols() { return cols_; }

void MyMatrix::SetRowsCols(int r_value, int c_value) {
  if (r_value < 1 || c_value < 1) {
    throw std::out_of_range(
        "ERROR! Incorrect input. Rows and colomns must be greater than 0");
  }
  if (r_value != rows_ || c_value != cols_) {
    int prev_rows = rows_;
    int prev_cols = cols_;
    MyMatrix temp(*this);
    _Clear();
    MyMatrix dest(r_value, c_value);
    for (int i = 0; i < (prev_rows < r_value ? prev_rows : r_value); ++i) {
      for (int j = 0; j < (prev_cols < c_value ? prev_cols : c_value); ++j) {
        dest.matrix_[i][j] = temp.matrix_[i][j];
      }
    }
    *this = std::move(dest);
  }
}

bool MyMatrix::EqMatrix(const MyMatrix &other) const noexcept {
  int res = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-07) {
          res = false;
        }
      }
    }
  } else {
    res = false;
  }
  return res;
}

void MyMatrix::SumMatrix(const MyMatrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("ERROR! Rows and colomns of matrix must be equal");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void MyMatrix::SubMatrix(const MyMatrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("ERROR! Rows and colomns of matrix must be equal");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void MyMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void MyMatrix::MulMatrix(const MyMatrix &other) {
  MyMatrix temp(rows_, other.cols_);
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "ERROR! Amount of rows of the first matrix must be "
        "equal to the amount of colomns of the second one");
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < other.cols_; ++j) {
        for (int k = 0; k < other.rows_; ++k) {
          temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  }
  *this = std::move(temp);
}

MyMatrix MyMatrix::Transpose() {
  MyMatrix res(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; ++j) {
      res.matrix_[i][j] = matrix_[j][i];
    }
  }
  return res;
}

double MyMatrix::_Minor(int row, int col) {
  double result = 0;
  MyMatrix temp(rows_ - 1, cols_ - 1);
  for (int x = 0, i = 0; i < rows_; ++i) {
    if (i != row) {
      for (int y = 0, j = 0; j < cols_; ++j)
        if (j != col) temp.matrix_[x][y++] = matrix_[i][j];
      x++;
    }
  }
  result = temp.Determinant();
  return result;
}

MyMatrix MyMatrix::CalcComplements() {
  MyMatrix res(*this), minor(*this);
  double det_res = 0;
  if (res.rows_ != res.cols_ || res.rows_ < 2) {
    throw std::out_of_range("ERROR! Incorrect Matrix");
  }
  for (int i = 0; i < res.rows_; ++i) {
    for (int j = 0; j < res.cols_; ++j) {
      det_res = minor._Minor(i, j);
      res.matrix_[i][j] = det_res * pow(-1, i + j);
    }
  }
  return res;
}

void MyMatrix::_CheckDiagonal() {
  int p = 1;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i == j && abs(matrix_[i][j]) <= 1e-7) {
        if (i > 0) p = i - 1;
        for (int k = 0; k < cols_; ++k) {
          matrix_[i][k] += matrix_[p][k];
        }
      }
    }
  }
}

double MyMatrix::Determinant() {
  MyMatrix copy(*this);
  double det_matrix = 1, eps = 1e-07, temp = 0;
  int start = 0;
  if (copy.rows_ != copy.cols_) {
    throw std::out_of_range("ERROR! Matrix must be square");
  }
  if (copy.rows_ == 1) {
    det_matrix = copy.matrix_[0][0];
  } else {
    copy._CheckDiagonal();
    for (int i = 1; i < copy.rows_; ++i) {
      start = 0;
      for (int j = 0; j < copy.cols_ && j < i; ++j) {
        if (abs(copy.matrix_[i][j]) >= eps) {
          double del = (-1) * (copy.matrix_[i][j] / copy.matrix_[start][j]);
          for (int k = 0; k < copy.cols_; ++k) {
            temp = copy.matrix_[start][k] * del;
            copy.matrix_[i][k] += temp;
            if (fabs(copy.matrix_[i][k]) <= eps) copy.matrix_[i][k] = 0;
          }
        }
        ++start;
      }
    }
    for (int i = 0; i < copy.rows_; ++i) {
      for (int j = 0; j < copy.cols_; ++j) {
        if (i == j) {
          det_matrix *= copy.matrix_[i][j];
        }
      }
    }
  }
  return det_matrix;
}

MyMatrix MyMatrix::InverseMatrix() {
  MyMatrix res(*this);
  if (res.rows_ != res.cols_) {
    throw std::out_of_range("ERROR! Matrix must be square");
  }
  double determinant = res.Determinant();
  if (determinant == 0) {
    throw std::out_of_range("ERROR! Determinant is zero");
  }
  if (res.rows_ == 1 && res.cols_ == 1) {
    res.matrix_[0][0] = pow(res.matrix_[0][0], -1);
  } else {
    res = res.CalcComplements().Transpose() * (1 / determinant);
  }
  return res;
}

MyMatrix &MyMatrix::operator=(MyMatrix &&other) {
  if (this != &other) {
    _Clear();
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

MyMatrix &MyMatrix::operator=(const MyMatrix &other) {
  _Clear();
  rows_ = other.rows_;
  cols_ = other.cols_;
  _Create();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

bool MyMatrix::operator==(const MyMatrix &other) const noexcept {
  return (EqMatrix(other));
}

MyMatrix MyMatrix::operator+(const MyMatrix &other) {
  MyMatrix res(*this);
  res.SumMatrix(other);
  return res;
}

MyMatrix &MyMatrix::operator+=(const MyMatrix &other) {
  SumMatrix(other);
  return *this;
}

MyMatrix MyMatrix::operator-(const MyMatrix &other) {
  MyMatrix res(*this);
  res.SubMatrix(other);
  return res;
}

MyMatrix &MyMatrix::operator-=(const MyMatrix &other) {
  SubMatrix(other);
  return *this;
}

MyMatrix operator*(const double number, const MyMatrix &other) {
  MyMatrix res = other;
  res.MulNumber(number);
  return res;
}

MyMatrix operator*(const MyMatrix &other, const double number) {
  MyMatrix res = other;
  res.MulNumber(number);
  return res;
}

MyMatrix MyMatrix::operator*(const MyMatrix &other) {
  MyMatrix res(*this);
  res.MulMatrix(other);
  return res;
}

MyMatrix &MyMatrix::operator*=(const MyMatrix &other) {
  MulMatrix(other);
  return *this;
}

MyMatrix &MyMatrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

double &MyMatrix::operator()(const int i, const int j) const {
  if (i < 0 || j < 0 || i > rows_ || j > cols_) {
    throw std::out_of_range("ERROR! Index is out of range");
  }
  return matrix_[i][j];
}

double &MyMatrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i > rows_ || j > cols_) {
    throw std::out_of_range("ERROR! Index is out of range");
  }
  return matrix_[i][j];
}

MyMatrix::~MyMatrix() { _Clear(); }

double RandomNum() {
  return sqrt((double)rand() /
              RAND_MAX);  // for generating random points between 0 to 1
}

void SetMatrixLine(MyMatrix *a, double *mass) {
  int k = 0;
  for (int i = 0; i < a->rows_; ++i) {
    for (int j = 0; j < a->cols_; ++j) {
      a->matrix_[i][j] = mass[k++];
    }
  }
}

void SetMatrixRandom(MyMatrix *a) {
  for (int i = 0; i < a->rows_; ++i) {
    for (int j = 0; j < a->cols_; ++j) {
      a->matrix_[i][j] = RandomNum();
    }
  }
}

void MyMatrix::_Clear() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}
