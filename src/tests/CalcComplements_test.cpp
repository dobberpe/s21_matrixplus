#include "s21_matrix_oop_test.h"

TEST(CalcComplementsTest, Square1x1) {
  S21Matrix A(1, 1);
  A[0][0] = 2;

  S21Matrix complement = A.CalcComplements();

  ASSERT_EQ(complement.get_rows(), 1);
  ASSERT_EQ(complement.get_cols(), 1);

  ASSERT_EQ(complement[0][0], 1);
}

TEST(CalcComplementsTest, NonSquare) {
  S21Matrix A(2, 3);

  ASSERT_THROW(A.CalcComplements(), std::exception);
}

TEST(CalcComplementsTest, Square2x2) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix complement = A.CalcComplements();

  ASSERT_EQ(complement.get_rows(), 2);
  ASSERT_EQ(complement.get_cols(), 2);

  ASSERT_EQ(complement[0][0], 4);
  ASSERT_EQ(complement[0][1], -3);
  ASSERT_EQ(complement[1][0], -2);
  ASSERT_EQ(complement[1][1], 1);
}