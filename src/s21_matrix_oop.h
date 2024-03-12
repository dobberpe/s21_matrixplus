#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

#include <cstdlib>
#include <cmath>

#define S21_EPS 1E-7

using namespace std;

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;

        S21Matrix Minor(int row, int col) const;

    public:
        S21Matrix();
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix();

        int get_rows() const;
        int get_cols() const;
        void edit_rows(int rows);
        void edit_cols(int cols);

        bool EqMatrix(const S21Matrix& other) const;
        void SumMatrix(const S21Matrix& other);
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other);
        S21Matrix Transpose() const;
        S21Matrix CalcComplements() const;
        double Determinant() const;
        S21Matrix InverseMatrix() const;

        S21Matrix operator+(const S21Matrix& other) const;
        S21Matrix operator-(const S21Matrix& other) const;
        S21Matrix operator*(const S21Matrix& other) const;
        S21Matrix operator*(const double num) const;
        bool operator==(const S21Matrix& other) const;
        void operator=(const S21Matrix& other);
        void operator+=(const S21Matrix& other);
        void operator-=(const S21Matrix& other);
        void operator*=(const S21Matrix& other);
        void operator*=(const double num);
        double* operator[](int i) const;
};

#endif