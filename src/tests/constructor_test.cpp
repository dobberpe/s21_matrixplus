#include "s21_matrix_oop_test.h"

TEST(ConstructorTest, DefaultConstructor) {
    S21Matrix A;
    EXPECT_EQ(1, A.get_rows());
    EXPECT_EQ(1, A.get_cols());
    EXPECT_EQ(0, A[0][0]);
}

TEST(ConstructorTest, ParameterizedConstructor1) {
    S21Matrix A(1, 1);
    EXPECT_EQ(1, A.get_rows());
    EXPECT_EQ(1, A.get_cols());
    EXPECT_EQ(0, A[0][0]);
}

TEST(ConstructorTest, ParameterizedConstructor2) {
S21Matrix A(2, 4);
EXPECT_EQ(2, A.get_rows());
EXPECT_EQ(4, A.get_cols());
EXPECT_EQ(0, A[0][0]);
EXPECT_EQ(0, A[0][1]);
EXPECT_EQ(0, A[0][2]);
EXPECT_EQ(0, A[0][3]);
EXPECT_EQ(0, A[1][0]);
EXPECT_EQ(0, A[1][1]);
EXPECT_EQ(0, A[1][2]);
EXPECT_EQ(0, A[1][3]);
}

TEST(ConstructorTest, ParameterizedConstructorInvalid) {
    try {
        S21Matrix A(0, 4);
    } catch (const exception& err) {
        EXPECT_EQ("Invalid parameters.", err.what());
    }
}

TEST(ConstructorTest, CopyConstructor) {
S21Matrix B(2, 4);
for (int i = 0; i < B.get_rows(); ++i) for (int j = 0; j < B.get_cols(); ++j) B[i][j] = i + j;
S21Matrix A(B);
EXPECT_EQ(2, A.get_rows());
EXPECT_EQ(4, A.get_cols());
EXPECT_EQ(0, A[0][0]);
EXPECT_EQ(1, A[0][1]);
EXPECT_EQ(2, A[0][2]);
EXPECT_EQ(3, A[0][3]);
EXPECT_EQ(1, A[1][0]);
EXPECT_EQ(2, A[1][1]);
EXPECT_EQ(3, A[1][2]);
EXPECT_EQ(4, A[1][3]);
}

TEST(ConstructorTest, MoveConstructor) {
S21Matrix B(2, 4);
for (int i = 0; i < B.get_rows(); ++i) for (int j = 0; j < B.get_cols(); ++j) B[i][j] = i + j;
S21Matrix A(&&B);
EXPECT_EQ(2, A.get_rows());
EXPECT_EQ(4, A.get_cols());
EXPECT_EQ(0, A[0][0]);
EXPECT_EQ(1, A[0][1]);
EXPECT_EQ(2, A[0][2]);
EXPECT_EQ(3, A[0][3]);
EXPECT_EQ(1, A[1][0]);
EXPECT_EQ(2, A[1][1]);
EXPECT_EQ(3, A[1][2]);
EXPECT_EQ(4, A[1][3]);
}