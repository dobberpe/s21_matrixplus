#include "s21_matrix_oop_test.h"

TEST(TransposeTest, TransposeCorrect) {
  S21Matrix A(2, 3);

  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 4;
  A[1][1] = 5;
  A[1][2] = 6;

  S21Matrix B = A.Transpose();

  ASSERT_EQ(B.get_rows(), 3);
  ASSERT_EQ(B.get_cols(), 2);

  ASSERT_EQ(B[0][0], 1);
  ASSERT_EQ(B[0][1], 4);
  ASSERT_EQ(B[1][0], 2);
  ASSERT_EQ(B[1][1], 5);
  ASSERT_EQ(B[2][0], 3);
  ASSERT_EQ(B[2][1], 6);
}
