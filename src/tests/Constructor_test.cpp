#include "s21_matrix_oop_test.h"

TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix A;
  ASSERT_EQ(1, A.get_rows());
  ASSERT_EQ(1, A.get_cols());
  ASSERT_EQ(0, A[0][0]);
}

TEST(ConstructorTest, ParameterizedConstructor1) {
  S21Matrix A(1, 1);
  ASSERT_EQ(1, A.get_rows());
  ASSERT_EQ(1, A.get_cols());
  ASSERT_EQ(0, A[0][0]);
}

TEST(ConstructorTest, ParameterizedConstructor2) {
  S21Matrix A(2, 4);
  ASSERT_EQ(2, A.get_rows());
  ASSERT_EQ(4, A.get_cols());
  ASSERT_EQ(0, A[0][0]);
  ASSERT_EQ(0, A[0][1]);
  ASSERT_EQ(0, A[0][2]);
  ASSERT_EQ(0, A[0][3]);
  ASSERT_EQ(0, A[1][0]);
  ASSERT_EQ(0, A[1][1]);
  ASSERT_EQ(0, A[1][2]);
  ASSERT_EQ(0, A[1][3]);
}

TEST(ConstructorTest, ParameterizedConstructorInvalid) {
  ASSERT_THROW(S21Matrix A(0, 4), exception);
}

TEST(ConstructorTest, CopyConstructor) {
  S21Matrix B(2, 4);
  for (int i = 0; i < B.get_rows(); ++i)
    for (int j = 0; j < B.get_cols(); ++j) B[i][j] = i + j;
  S21Matrix A(B);
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(ConstructorTest, MoveConstructor) {
  S21Matrix B(2, 4);
  for (int i = 0; i < B.get_rows(); ++i)
    for (int j = 0; j < B.get_cols(); ++j) B[i][j] = i + j;
  S21Matrix A(move(B));
  ASSERT_EQ(2, A.get_rows());
  ASSERT_EQ(4, A.get_cols());
  ASSERT_EQ(0, A[0][0]);
  ASSERT_EQ(1, A[0][1]);
  ASSERT_EQ(2, A[0][2]);
  ASSERT_EQ(3, A[0][3]);
  ASSERT_EQ(1, A[1][0]);
  ASSERT_EQ(2, A[1][1]);
  ASSERT_EQ(3, A[1][2]);
  ASSERT_EQ(4, A[1][3]);
  ASSERT_THROW(B[0], exception);
}