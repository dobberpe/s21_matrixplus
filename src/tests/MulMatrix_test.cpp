#include "s21_matrix_oop_test.h"

TEST(MulMatrixTest, MulMatrixCorrect) {
  S21Matrix A(2, 4);
  S21Matrix B(4, 1);

  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[0][3] = 4;
  A[1][0] = 5;
  A[1][1] = 6;
  A[1][2] = 7;
  A[1][3] = 8;

  B[0][0] = 9;
  B[1][0] = 10;
  B[2][0] = 11;
  B[3][0] = 12;

  A.MulMatrix(B);

  ASSERT_EQ(A[0][0], 110.0);
  ASSERT_EQ(A[1][0], 278.0);
}

TEST(MulMatrixTest, MulMatrixIncorrectSizes) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);

  ASSERT_THROW(A.MulMatrix(B), std::exception);
}