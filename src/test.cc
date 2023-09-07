#include <gtest/gtest.h>

#include <iostream>

#include "my_matrix_oop.h"

TEST(Constructor, NoArgs) {
  MyMatrix a;
  EXPECT_EQ(10, a.GetRows());
  EXPECT_EQ(10, a.GetCols());
  for (int i = 0; i < 1; ++i) {
    for (int j = 0; j < 1; ++j) {
      EXPECT_EQ(0, a(i, j));
    }
  }
}

TEST(Constructor, Copy) {
  MyMatrix a(2, 2);
  SetMatrixRandom(&a);
  MyMatrix b(a);
  EXPECT_EQ(2, b.GetCols());
  EXPECT_EQ(2, b.GetRows());
  EXPECT_EQ(true, b.EqMatrix(a));
}

TEST(Constructor, Move) {
  MyMatrix a(2, 8);
  SetMatrixRandom(&a);
  MyMatrix b(std::move(a));
  EXPECT_EQ(2, b.GetRows());
  EXPECT_EQ(8, b.GetCols());
  EXPECT_EQ(0, a.GetRows());
  EXPECT_EQ(0, a.GetCols());
}

TEST(Setter, SetRCF) {
  MyMatrix a(4, 4), b(3, 3);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  double mass1[] = {1, 2, 3, 5, 6, 7, 9, 10, 11};
  SetMatrixLine(&a, mass);
  a.SetRowsCols(3, 3);
  SetMatrixLine(&b, mass1);
  EXPECT_EQ(3, a.GetRows());
  EXPECT_EQ(3, a.GetCols());
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(b(i, j), a(i, j));
    }
  }
}

TEST(Setter, SetRCS) {
  MyMatrix a;
  a.SetRowsCols(11, 11);
  EXPECT_EQ(11, a.GetRows());
  EXPECT_EQ(11, a.GetCols());
  for (int i = 10; i < 11; ++i) {
    for (int j = 10; j < 11; ++j) {
      EXPECT_EQ(0, a(i, j));
    }
  }
}

TEST(EqMatrix, Equal) {
  MyMatrix a(3, 3), b(3, 3);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass);
  EXPECT_EQ(true, a.EqMatrix(b));
}

TEST(EqMatrix, NotEqualF) {
  MyMatrix a(4, 4), b(4, 4);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  SetMatrixLine(&a, mass);
  SetMatrixRandom(&b);
  EXPECT_EQ(false, a.EqMatrix(b));
}

TEST(EqMatrix, NotEqualS) {
  MyMatrix a(4, 4), b(3, 4);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  SetMatrixLine(&a, mass);
  SetMatrixRandom(&b);
  EXPECT_EQ(false, a.EqMatrix(b));
}

TEST(SumMatrix, First) {
  MyMatrix a(3, 3), b(3, 3), c(3, 3);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double mass1[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  double mass2[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  SetMatrixLine(&c, mass2);
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass1);
  a.SumMatrix(b);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(c(i, j), a(i, j));
    }
  }
}

TEST(SubMatrix, Second) {
  MyMatrix a(3, 3), b(3, 3), c(3, 3);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double mass1[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  double mass2[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  SetMatrixLine(&a, mass2);
  SetMatrixLine(&b, mass1);
  SetMatrixLine(&c, mass);
  a.SubMatrix(b);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(c(i, j), a(i, j));
    }
  }
}

TEST(MulNumber, First) {
  MyMatrix a(3, 3), b(3, 3);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double mass1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
  SetMatrixLine(&a, mass);
  double x = 1.1;
  a.MulNumber(x);
  SetMatrixLine(&b, mass1);
  EXPECT_EQ(true, a.EqMatrix(b));
}

TEST(MulMatrix, Second) {
  MyMatrix a(10, 10), b;
  SetMatrixRandom(&a);
  a.MulMatrix(b);
  EXPECT_EQ(true, a.EqMatrix(b));
}

TEST(Transpose, First) {
  MyMatrix a(2, 4), b(4, 2);
  double mass[] = {0.12, -4.5, 0, 0.87654537, 6.12, -11, 2.0001, -0.758316};
  double mass1[] = {0.12, 6.12, -4.5, -11, 0, 2.0001, 0.876545, -0.758316};
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass1);
  a = a.Transpose();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_NEAR(b(i, j), a(i, j), 1e-6);
    }
  }
}

TEST(Determinant, First) {
  MyMatrix a(3, 3);
  double mass[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  SetMatrixLine(&a, mass);
  double x = a.Determinant();
  EXPECT_EQ(0, x);
}

TEST(Determinant, Second) {
  MyMatrix a(4, 4);
  double mass[] = {0.00279756, 0.362681, 0.869256, 0.677237, 0.729909, 0.467931,
                   0.216898,   0.823932, 0.824194, 0.966795, 0.619275, 0.720705,
                   0.911573,   0.185936, 0.231218, 0.727805};
  SetMatrixLine(&a, mass);
  double x = a.Determinant();
  EXPECT_NEAR(-0.1696, x, 1e-6);
}

TEST(CalcComplements, Second) {
  MyMatrix a(5, 5), b(5, 5);
  double mass[] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                   14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
  SetMatrixLine(&a, mass);
  b = a.CalcComplements();
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      EXPECT_EQ(0, b(i, j));
    }
  }
}

TEST(CalcComplements, Third) {
  MyMatrix a(3, 3), b(3, 3), c(3, 3);
  double mass[] = {0.00279756, 0.362681, 0.869256, 0.677237, 0.729909,
                   0.467931,   0.216898, 0.823932, 0.824194};
  SetMatrixLine(&a, mass);
  b = a.CalcComplements();
  double mass1[] = {0.216044,  -0.456682, 0.399682, 0.417288, -0.186234,
                    0.0763598, -0.464768, 0.587383, -0.243579};
  SetMatrixLine(&c, mass1);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_NEAR(c(i, j), b(i, j), 1e-6);
    }
  }
}

TEST(InverseMatrix, Third) {
  MyMatrix a(4, 4), b(4, 4), c(4, 4);
  double mass[] = {0.00279756, 0.362681, 0.869256, 0.677237, 0.729909, 0.467931,
                   0.216898,   0.823932, 0.824194, 0.966795, 0.619275, 0.720705,
                   0.911573,   0.185936, 0.231218, 0.727805};
  SetMatrixLine(&a, mass);
  b = a.InverseMatrix();
  double mass1[] = {-0.581862, -1.87925, 0.759125, 1.91717,  -0.521051, 1.19576,
                    1.01063,   -1.86962, 0.927829, -2.77569, 0.688139,  1.59751,
                    0.567131,  2.93008,  -1.42761, -1.05713};
  SetMatrixLine(&c, mass1);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_NEAR(c(i, j), b(i, j), 1e-5);
    }
  }
}

TEST(InverseMatrix, Fourth) {
  MyMatrix a(1, 1), b(1, 1);
  a(0, 0) = 2;
  b = a.InverseMatrix();
  EXPECT_DOUBLE_EQ(0.5, b(0, 0));
}

TEST(Operators, Order) {
  MyMatrix a(3, 5), b(3, 5);
  double mass[] = {0.00279756, 0.362681, 0.869256, 0.677237, 0.729909,
                   0.467931,   0.216898, 0.823932, 0.824194, 0.966795,
                   0.619275,   0.720705, 0.911573, 0.185936, 0.231218};
  SetMatrixLine(&a, mass);
  MyMatrix c(a);
  b = a;
  EXPECT_EQ(true, b.EqMatrix(c));
}

TEST(Operators, EquelF) {
  MyMatrix a, b;
  EXPECT_EQ(true, a == b);
}

TEST(Operators, EquelS) {
  MyMatrix a(3, 3), b(3, 3);
  SetMatrixRandom(&a);
  SetMatrixRandom(&b);
  EXPECT_EQ(false, a == b);
}

TEST(Operators, SumMatrixF) {
  MyMatrix a(2, 2), b(2, 2), c(2, 2);
  double mass[] = {1, 2, 3, 4};
  double mass1[] = {0.1, 0.2, 0.3, 0.4};
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass1);
  c = a + b;
  double x = 1.1;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(x, c(i, j));
      x += 1.1;
    }
  }
}

TEST(Operators, SumMatrixS) {
  MyMatrix a(3, 4), b(3, 4), c(3, 4);
  double mass[] = {0.002, 0.362, 0.869, 0.677, 0.729, 0.467,
                   0.216, 0.823, 0.824, 0.966, 0.619, 0.720};
  SetMatrixLine(&a, mass);
  double mass1[] = {0.911, 0.185, 0.231, 0.727, 0.819, 0.087,
                    0.619, 0.258, 0.646, 0.828, 0.767, 0.964};
  SetMatrixLine(&b, mass1);
  double mass2[] = {0.913, 0.547, 1.100, 1.405, 1.548, 0.554,
                    0.835, 1.082, 1.470, 1.794, 1.386, 1.685};
  a += b;
  SetMatrixLine(&c, mass2);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_NEAR(c(i, j), a(i, j), 1e-6);
    }
  }
}

TEST(Operators, SubMatrixF) {
  MyMatrix a(2, 3), b(2, 3), c(2, 3);
  double mass[] = {1, 2, 3, 4, 5, 6};
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass);
  c = a - b;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(0, c(i, j));
    }
  }
}

TEST(Operators, SubMatrixS) {
  MyMatrix a(4, 4), b(4, 4), c(4, 4);
  double mass[] = {0.00279756, 0.362681, 0.869256, 0.677237, 0.729909, 0.467931,
                   0.216898,   0.823932, 0.824194, 0.966795, 0.619275, 0.720705,
                   0.911573,   0.185936, 0.231218, 0.727805};
  SetMatrixLine(&a, mass);
  double mass1[] = {0.819237, 0.0877393, 0.619206, 0.258539, 0.646132, 0.828718,
                    0.767448, 0.964591,  0.919873, 0.725899, 0.303257, 0.808653,
                    0.64498,  0.837371,  0.954107, 0.87304};
  SetMatrixLine(&b, mass1);
  double mass2[] = {-0.81644,   0.274942,  0.25005,   0.418698,
                    0.0837775,  -0.360787, -0.55055,  -0.140659,
                    -0.0956789, 0.240896,  0.316018,  -0.0879471,
                    0.266593,   -0.651435, -0.722889, -0.145235};
  SetMatrixLine(&c, mass2);
  a -= b;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_NEAR(mass2[i + (i * 3) + j], a(i, j), 1e-6);
    }
  }
}

TEST(Operators, MulNumberF) {
  MyMatrix a(2, 4), b(2, 4);
  double mass[] = {1, 2, 3, 4, 5, 6, 7, 8};
  SetMatrixLine(&a, mass);
  double x = 1.1;
  b = a * x;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      EXPECT_NEAR(x, b(i, j), 1e-6);
      x += 1.1;
    }
  }
}

TEST(Operators, MulNumberS) {
  MyMatrix a, b;
  double x = -13.925000123;
  b = a * x;
  EXPECT_EQ(true, b.EqMatrix(a));
}

TEST(Operators, MulNumberY) {
  MyMatrix a, b;
  double x = -13.925000123;
  b = x * a;
  EXPECT_EQ(true, b.EqMatrix(a));
}

TEST(Operators, MulMatrixF) {
  MyMatrix a(3, 3), b(3, 3), c(3, 3);
  double mass[] = {0.12, -9.0873, 3, -0.4215, 11, 1e-3, 2.12, 1.00002, 6};
  double mass1[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
  double mass2[] = {-0.59673, -0.59673, -0.59673, 1.05795, 1.05795,
                    1.05795,  0.912002, 0.912002, 0.912002};
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass1);
  c = a * b;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(mass2[i + (i * 2) + j], c(i, j));
    }
  }
}

TEST(Operators, MulMatrixT) {
  MyMatrix a, b;
  MyMatrix c = a * b;
  EXPECT_EQ(true, c.EqMatrix(a));
}

TEST(Operators, MulMatrixS) {
  MyMatrix a(3, 3), b(3, 3), c(3, 3);
  double mass[] = {0.12, -9.0873, 3, -0.4215, 11, 1e-3, 2.12, 1.00002, 6};
  double mass1[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
  double mass2[] = {-0.59673, -0.59673, -0.59673, 1.05795, 1.05795,
                    1.05795,  0.912002, 0.912002, 0.912002};
  SetMatrixLine(&a, mass);
  SetMatrixLine(&b, mass1);
  a *= b;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_DOUBLE_EQ(mass2[i + (i * 2) + j], a(i, j));
    }
  }
}

TEST(Operators, MulNumberT) {
  MyMatrix a;
  a *= 1e-7;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      EXPECT_EQ(0, a(i, j));
    }
  }
}

TEST(Operators, MulNumberG) {
  MyMatrix a(2, 2);
  double mass[] = {0.1672, -12.9011, 56.098, 2.000001};
  SetMatrixLine(&a, mass);
  a *= 0.13;
  double mass1[] = {0.021736, -1.677143, 7.29274, 0.26000013};
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(mass1[i + (i * 1) + j], a(i, j));
    }
  }
}

TEST(Operators, BracketsF) {
  MyMatrix a(2, 2);
  double mass[4] = {1};
  SetMatrixLine(&a, mass);
  EXPECT_EQ(1, a(0, 0));
}

TEST(Operators, BracketsS) {
  const MyMatrix a;
  int i = 2, j = 1;
  EXPECT_EQ(0, a(i, j));
}

// Exceptions

TEST(InverseMatrix, Fifth) {
  MyMatrix a(2, 3);
  double mass[] = {0.12, 12, 7, 0.763, 1.15, 6.3452};
  SetMatrixLine(&a, mass);
  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(SumMatrix, Second) {
  MyMatrix a(3, 4), b(3, 3);
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(SubMatrix, First) {
  MyMatrix a(4, 2), b(3, 5);
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(MulMatrix, First) {
  MyMatrix a(2, 2), b(3, 4);
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(Determinant, Err) {
  MyMatrix a(2, 3);
  EXPECT_ANY_THROW(a.Determinant());
}

TEST(CalcComplements, First) {
  MyMatrix a(3, 5);
  EXPECT_ANY_THROW(a.CalcComplements());
}

TEST(InverseMatrix, First) {
  MyMatrix a(2, 4);
  SetMatrixRandom(&a);
  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(InverseMatrix, Second) {
  MyMatrix a(3, 3);
  double mass[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  SetMatrixLine(&a, mass);
  EXPECT_ANY_THROW(a.InverseMatrix());
}

TEST(Setter, SetRCT) {
  MyMatrix a;
  EXPECT_ANY_THROW(a.SetRowsCols(-1, 0));
}

TEST(Operators, Brackets) {
  MyMatrix a(3, 3);
  EXPECT_ANY_THROW(a(4, 4));
}

TEST(Operators, BracketsConst) {
  const MyMatrix a(3, 3);
  EXPECT_ANY_THROW(a(4, 4));
}

TEST(Errors, First) { EXPECT_ANY_THROW(MyMatrix a(-1, -1)); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
