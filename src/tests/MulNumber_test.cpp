#include "s21_matrix_oop_test.h"

TEST(MulNumberTest, MulNumberCorrect) {
  S21Matrix A(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  double num = 2;

  A.MulNumber(num);

  ASSERT_EQ(A[0][0], 2);
  ASSERT_EQ(A[0][1], 4);
  ASSERT_EQ(A[1][0], 6);
  ASSERT_EQ(A[1][1], 8);
}

TEST(MulNumberTest, MulNumberZero) {
  S21Matrix A(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  double num = 0;

  A.MulNumber(num);

  ASSERT_EQ(A[0][0], 0);
  ASSERT_EQ(A[0][1], 0);
  ASSERT_EQ(A[1][0], 0);
  ASSERT_EQ(A[1][1], 0);
}