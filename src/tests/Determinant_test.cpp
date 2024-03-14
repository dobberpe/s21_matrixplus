#include "s21_matrix_oop_test.h"

TEST(DeterminantTest, Square1x1) {
S21Matrix A(1, 1);
A[0][0] = 2;
double determinant = A.Determinant();
ASSERT_EQ(determinant, 2);
}

TEST(DeterminantTest, NonSquare) {
S21Matrix A(2, 3);
ASSERT_THROW(A.Determinant(), std::exception);
}

TEST(DeterminantTest, Square2x2) {
S21Matrix A(2, 2);
A[0][0] = 1;
A[0][1] = 2;
A[1][0] = 3;
A[1][1] = 4;
double determinant = A.Determinant();
ASSERT_NEAR(-2, determinant, S21_EPS);
}

TEST(DeterminantTest, Square3x3) {
S21Matrix A(3, 3);
A[0][0] = 1;
A[0][1] = 2;
A[0][2] = 3;
A[1][0] = 4;
A[1][1] = 5;
A[1][2] = 6;
A[2][0] = 7;
A[2][1] = 8;
A[2][2] = 9;
double determinant = A.Determinant();
ASSERT_EQ(determinant, 0);
}

TEST(DeterminantTest, Square3x3NotNull) {
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
double determinant = A.Determinant();
ASSERT_NEAR(-198, determinant, S21_EPS);
}

TEST(DeterminantTest, Square3x3Swap) {
S21Matrix A(3, 3);
A[0][0] = 0;
A[0][1] = 4;
A[0][2] = -1;
A[1][0] = 7;
A[1][1] = 3;
A[1][2] = 1;
A[2][0] = -3;
A[2][1] = 5;
A[2][2] = 6;
double determinant = A.Determinant();
ASSERT_NEAR(-10, determinant, S21_EPS);
}

TEST(DeterminantTest, Square3x3Swap2) {
S21Matrix A(3, 3);
A[0][0] = 2;
A[0][1] = 4;
A[0][2] = -1;
A[1][0] = 7;
A[1][1] = 14;
A[1][2] = 1;
A[2][0] = -3;
A[2][1] = 5;
A[2][2] = 6;
double determinant = A.Determinant();
ASSERT_NEAR(536, determinant, S21_EPS);
}

TEST(DeterminantTest, Square3x3SwapNull) {
S21Matrix A(3, 3);
A[0][0] = 2;
A[0][1] = 4;
A[0][2] = -1;
A[1][0] = 7;
A[1][1] = 14;
A[1][2] = 1;
A[2][0] = -3;
A[2][1] = -6;
A[2][2] = 6;
double determinant = A.Determinant();
ASSERT_EQ(0, determinant);
}