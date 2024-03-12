#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Minor(int row, int col) const {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_ - 1; ++i) for (int j = 0; j < cols_ - 1; ++j) minor[i][j] = matrix_[i < row ? i : i + 1][j < col ? j : j + 1];
}

S21Matrix::S21Matrix() { S21Matrix(1, 1); }

S21Matrix::S21Matrix(int rows, int cols) {
    matrix_ = nullptr;
    if (rows > 0 && cols > 0) {
        rows_ = rows;
        cols_ = cols;

        matrix_ = (double**)malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; ++i) matrix_[i] = (double*)calloc(cols, sizeof(double));
    }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    S21Matrix(other.get_rows(), other.get_cols());
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] = other[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    S21Matrix(*other);
    other.~S21Matrix();
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows_; ++i) free(matrix_[i]);
    free(matrix_);
}

int S21Matrix::get_rows() const { return rows_; }

int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::edit_rows(int rows) {
    if (rows > 0) {
        matrix_ = (double**)realloc(matrix_, rows * sizeof(double*));
        if (rows > rows_) for (int i = rows_; i < rows; ++i) matrix_[i] = (double*)calloc(cols_, sizeof(double));
    }
}

void S21Matrix::edit_cols(int cols) {
    if (cols > 0) {
        for (int i = 0; i < rows_; ++i) {
            matrix_[i] = (double*)realloc(matrix_, cols * sizeof(double));
            if (cols > cols_) for (int j = cols_; j < cols; ++j) matrix_[i][j] = 0;
        }
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
    bool res = rows_ == other.get_rows() && cols_ == other.get_cols();

    for (int i = 0; i < rows_ && res; ++i) for (int j = 0; j < cols_ && res; ++j) res = fabs(matrix_[i][j] - other[i][j]) < S21_EPS;

    return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (rows_ == other.get_rows() && cols_ == other.get_cols()) for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] += other[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (rows_ == other.get_rows() && cols_ == other.get_cols()) for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other[i][j];
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (cols_ == other.get_rows()) for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other[i][j];
}

S21Matrix S21Matrix::Transpose() const {
    S21Matrix transposed(cols_, rows_);
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) transposed[j][i] = matrix_[i][j];
}

S21Matrix S21Matrix::CalcComplements() const {
    S21Matrix complement_matrix(0, 0);
    if (rows_ == cols_) {
        if (rows_ == 1) {
            complement_matrix.edit_rows(1);
            complement_matrix.edit_cols(1);
            complement_matrix[0][0] = 1;
        } else {
            complement_matrix.edit_rows(rows_);
            complement_matrix.edit_cols(cols_);
            for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) {
                S21Matrix minor = Minor(i, j);
                complement_matrix[i][j] = minor.Determinant() * pow(-1, i + j);
                minor.~S21Matrix();
            }
        }
    }
    return complement_matrix;
}

double S21Matrix::Determinant() const {}

S21Matrix S21Matrix::InverseMatrix() const {}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
    S21Matrix result(*this);
    result += other;
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
    S21Matrix result(*this);
    result -= other;
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
    S21Matrix result(*this);
    result *= other;
    return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
    S21Matrix result(*this);
    result *= num;
    return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const { return EqMatrix(other); }

void S21Matrix::operator=(const S21Matrix& other) {
    this->~S21Matrix();
    S21Matrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double* S21Matrix::operator[](int i) const { return matrix_[i]; }