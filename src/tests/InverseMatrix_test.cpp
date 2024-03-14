#include "s21_matrix_oop_test.h"

TEST(InverseMatrixTest, Square1x1) {
  S21Matrix A(1, 1);
  A[0][0] = 2;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.get_rows(), 1);
  ASSERT_EQ(result.get_cols(), 1);
  ASSERT_NEAR(result[0][0], 0.5, 1e-7);
}

TEST(InverseMatrixTest, Square2x2) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.get_rows(), 2);
  ASSERT_EQ(result.get_cols(), 2);
  ASSERT_NEAR(result[0][0], -2, 1e-7);
  ASSERT_NEAR(result[0][1], 1, 1e-7);
  ASSERT_NEAR(result[1][0], 1.5, 1e-7);
  ASSERT_NEAR(result[1][1], -0.5, 1e-7);
}

TEST(InverseMatrixTest, Square3x3Eq) {
  S21Matrix A(3, 3);
  A[0][0] = 1;
  A[0][1] = 0;
  A[0][2] = 0;
  A[1][0] = 0;
  A[1][1] = 1;
  A[1][2] = 0;
  A[2][0] = 0;
  A[2][1] = 0;
  A[2][2] = 1;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.get_rows(), 3);
  ASSERT_EQ(result.get_cols(), 3);
  ASSERT_NEAR(result[0][0], 1, 1e-7);
  ASSERT_NEAR(result[0][1], 0, 1e-7);
  ASSERT_NEAR(result[0][2], 0, 1e-7);
  ASSERT_NEAR(result[1][0], 0, 1e-7);
  ASSERT_NEAR(result[1][1], 1, 1e-7);
  ASSERT_NEAR(result[1][2], 0, 1e-7);
  ASSERT_NEAR(result[2][0], 0, 1e-7);
  ASSERT_NEAR(result[2][1], 0, 1e-7);
  ASSERT_NEAR(result[2][2], 1, 1e-7);
}

TEST(InverseMatrixTest, SingularMatrix) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 2;
  A[1][1] = 4;

  ASSERT_THROW(A.InverseMatrix(), std::exception);
}

TEST(InverseMatrixTest, NonSquareMatrix) {
  S21Matrix A(2, 3);
  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 4;
  A[1][1] = 5;
  A[1][2] = 6;

  ASSERT_THROW(A.InverseMatrix(), std::exception);
}

TEST(InverseMatrixTest, Square3x3) {
  S21Matrix A(3, 3);
  A[0][0] = 2;
  A[0][1] = 4;
  A[0][2] = -1;
  A[1][0] = 7;
  A[1][1] = 3;
  A[1][2] = 1;
  A[2][0] = -3;
  A[2][1] = 5;
  A[2][2] = 6;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.get_rows(), 3);
  ASSERT_EQ(result.get_cols(), 3);
  ASSERT_NEAR(result[0][0], -13.0 / 198, 1e-7);
  ASSERT_NEAR(result[0][1], 29.0 / 198, 1e-7);
  ASSERT_NEAR(result[0][2], -7.0 / 198, 1e-7);
  ASSERT_NEAR(result[1][0], 5.0 / 22, 1e-7);
  ASSERT_NEAR(result[1][1], -1.0 / 22, 1e-7);
  ASSERT_NEAR(result[1][2], 1.0 / 22, 1e-7);
  ASSERT_NEAR(result[2][0], -2.0 / 9, 1e-7);
  ASSERT_NEAR(result[2][1], 1.0 / 9, 1e-7);
  ASSERT_NEAR(result[2][2], 1.0 / 9, 1e-7);
}