#include "s21_matrix_oop_test.h"

TEST(EqMatrixTest, HandlesEqCase) {
S21Matrix B(2, 4);
for (int i = 0; i < B.get_rows(); ++i) for (int j = 0; j < B.get_cols(); ++j) B[i][j] = i + j;
S21Matrix A(B);
ASSERT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrixTest, HandlesUneqCase) {
S21Matrix B(2, 4);
S21Matrix A(B);
for (int i = 0; i < B.get_rows(); ++i) for (int j = 0; j < B.get_cols(); ++j) B[i][j] = i + j;
ASSERT_FALSE(A.EqMatrix(B));
}

TEST(EqMatrixTest, HandlesDifferentSizes) {
S21Matrix B(2, 4);
S21Matrix A(2, 2);
ASSERT_THROW(A.EqMatrix(B), exception);
}