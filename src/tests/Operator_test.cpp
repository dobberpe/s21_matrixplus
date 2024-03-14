#include "s21_matrix_oop_test.h"

TEST(MatrixOperatorTest, Addition) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  S21Matrix result = A + B;

  ASSERT_EQ(result.get_rows(), 2);
  ASSERT_EQ(result.get_cols(), 2);

  ASSERT_EQ(result[0][0], 6);
  ASSERT_EQ(result[0][1], 8);
  ASSERT_EQ(result[1][0], 10);
  ASSERT_EQ(result[1][1], 12);
}

TEST(MatrixOperatorTest, Subtraction) {
  S21Matrix A(2, 2);
  A[0][0] = 5;
  A[0][1] = 6;
  A[1][0] = 7;
  A[1][1] = 8;

  S21Matrix B(2, 2);
  B[0][0] = 1;
  B[0][1] = 2;
  B[1][0] = 3;
  B[1][1] = 4;

  S21Matrix result = A - B;

  ASSERT_EQ(result.get_rows(), 2);
  ASSERT_EQ(result.get_cols(), 2);

  ASSERT_EQ(result[0][0], 4);
  ASSERT_EQ(result[0][1], 4);
  ASSERT_EQ(result[1][0], 4);
  ASSERT_EQ(result[1][1], 4);
}

TEST(MatrixOperatorTest, Multiplication) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  S21Matrix result = A * B;

  ASSERT_EQ(result.get_rows(), 2);
  ASSERT_EQ(result.get_cols(), 2);

  ASSERT_EQ(result[0][0], 19);
  ASSERT_EQ(result[0][1], 22);
  ASSERT_EQ(result[1][0], 43);
  ASSERT_EQ(result[1][1], 50);
}

TEST(MatrixOperatorTest, MultiplicationByNumber) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  double num = 2;

  S21Matrix result = A * num;

  ASSERT_EQ(result.get_rows(), 2);
  ASSERT_EQ(result.get_cols(), 2);

  ASSERT_EQ(result[0][0], 2);
  ASSERT_EQ(result[0][1], 4);
  ASSERT_EQ(result[1][0], 6);
  ASSERT_EQ(result[1][1], 8);
}

TEST(MatrixOperatorTest, Equality) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 1;
  B[0][1] = 2;
  B[1][0] = 3;
  B[1][1] = 4;

  ASSERT_TRUE(A == B);
}

TEST(MatrixOperatorTest, Assignment) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A = B;

  ASSERT_EQ(A[0][0], B[0][0]);
  ASSERT_EQ(A[0][1], B[0][1]);
  ASSERT_EQ(A[1][0], B[1][0]);
  ASSERT_EQ(A[1][1], B[1][1]);
}

TEST(MatrixOperatorTest, MoveAssignment) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A = move(B);

  ASSERT_EQ(A[0][0], 5);
  ASSERT_EQ(A[0][1], 6);
  ASSERT_EQ(A[1][0], 7);
  ASSERT_EQ(A[1][1], 8);
  ASSERT_THROW(B[0], exception);
}

TEST(MatrixOperatorTest, AdditionAssignment) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A += B;

  ASSERT_EQ(A[0][0], 6);
  ASSERT_EQ(A[0][1], 8);
  ASSERT_EQ(A[1][0], 10);
  ASSERT_EQ(A[1][1], 12);
}

TEST(MatrixOperatorTest, SubtractionAssignment) {
  S21Matrix A(2, 2);
  A[0][0] = 5;
  A[0][1] = 6;
  A[1][0] = 7;
  A[1][1] = 8;

  S21Matrix B(2, 2);
  B[0][0] = 1;
  B[0][1] = 2;
  B[1][0] = 3;
  B[1][1] = 4;

  A -= B;

  ASSERT_EQ(A[0][0], 4);
  ASSERT_EQ(A[0][1], 4);
  ASSERT_EQ(A[1][0], 4);
  ASSERT_EQ(A[1][1], 4);
}

TEST(MatrixOperatorTest, MultiplicationAssignment) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix B(2, 2);
  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A *= B;

  ASSERT_EQ(A[0][0], 19);
  ASSERT_EQ(A[0][1], 22);
  ASSERT_EQ(A[1][0], 43);
  ASSERT_EQ(A[1][1], 50);
}

TEST(MatrixOperatorTest, NumMultiplicationAssignment) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  A *= 2;

  ASSERT_EQ(A[0][0], 2);
  ASSERT_EQ(A[0][1], 4);
  ASSERT_EQ(A[1][0], 6);
  ASSERT_EQ(A[1][1], 8);
}