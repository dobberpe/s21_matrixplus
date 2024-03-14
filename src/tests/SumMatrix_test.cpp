#include "s21_matrix_oop_test.h"

TEST(SumMatrixTest, SumMatrixCorrect) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A.SumMatrix(B);

  ASSERT_EQ(A[0][0], 6.0);
  ASSERT_EQ(A[0][1], 8.0);
  ASSERT_EQ(A[1][0], 10.0);
  ASSERT_EQ(A[1][1], 12.0);
}

TEST(SumMatrixTest, SumMatrixDifferentSizes) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);

  ASSERT_THROW(A.SumMatrix(B), exception);
}