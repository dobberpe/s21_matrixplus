#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Minor(int row, int col) const {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_ - 1; ++i) for (int j = 0; j < cols_ - 1; ++j) minor[i][j] = matrix_[i < row ? i : i + 1][j < col ? j : j + 1];
}

bool S21Matrix::IsTriangle() const {
    bool res = true;
    for (int i = 0; i < rows_ && res; ++i) for (int j = 0; j < i && res; ++j) res = matrix_[i][j] != 0;
    return res;
}

int S21Matrix::GaussianMethod() {
    int swap_counter = 0;

    for (int j = 0; j < cols_; ++j) {
        int i = j + 1;
        while (i < rows_) {
            if (matrix_[j][j]) {
                double factor = matrix_[i][j] / matrix_[j][j];
                for (int k = j; k < cols_; ++k) matrix_[i][k] -= factor * matrix_[j][k];
                ++i;
            } else if (SwapRows(j)) ++swap_counter;
            else i = rows_; // j = cols_; ?
        }
    }
    return swap_counter;
}

bool S21Matrix::SwapRows(int j) {
    int swap_row = j;

    for (int i = j + 1; i < rows_ && swap_row == j; ++i) swap_row = matrix_[i][j] != 0 ? i : j;

    bool res = swap_row != j;

    for (int i = 0; i < cols_ && res; ++i) {
        double tmp = matrix_[j][i];
        matrix_[j][i] = matrix_[swap_row][i];
        matrix_[swap_row][i] = tmp;
    }

    return res;
}

S21Matrix::S21Matrix() { S21Matrix(1, 1); }

S21Matrix::S21Matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        S21Matrix();
        throw exception;
    }

    rows_ = rows;
    cols_ = cols;

    matrix_ = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; ++i) matrix_[i] = (double*)calloc(cols, sizeof(double));
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    if (!other.get_rows()) throw exception;

    S21Matrix(other.get_rows(), other.get_cols());
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] = other[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    if (!other.get_rows()) throw exception;

    S21Matrix(&other);
    other.~S21Matrix();
}

S21Matrix::~S21Matrix() {
    if (!rows_) throw exception;

    for (int i = 0; i < rows_; ++i) free(matrix_[i]);
    free(matrix_);
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
}

int S21Matrix::get_rows() const { return rows_; }

int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::edit_rows(int rows) {
    if (rows <= 0) throw exception;

    matrix_ = (double**)realloc(matrix_, rows * sizeof(double*));
    if (rows > rows_) for (int i = rows_; i < rows; ++i) matrix_[i] = (double*)calloc(cols_, sizeof(double));
}

void S21Matrix::edit_cols(int cols) {
    if (cols <= 0) throw exception;

    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = (double*)realloc(matrix_, cols * sizeof(double));
        if (cols > cols_) for (int j = cols_; j < cols; ++j) matrix_[i][j] = 0;
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
    if (!rows_ || !other.get_rows() || rows_ != other.get_rows() || cols_ != other.get_cols()) throw exception;
    bool res = true;

    for (int i = 0; i < rows_ && res; ++i) for (int j = 0; j < cols_ && res; ++j) res = fabs(matrix_[i][j] - other[i][j]) < S21_EPS;

    return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (!rows_ || !other.get_rows() || rows_ != other.get_rows() || cols_ != other.get_cols()) throw exception;

    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] += other[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (!rows_ || !other.get_rows() || rows_ != other.get_rows() || cols_ != other.get_cols()) throw exception;

    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other[i][j];
}

void S21Matrix::MulNumber(const double num) {
    if (!rows_) throw exception;

    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (!rows_ || !other.get_rows() || cols_ != other.get_rows()) throw exception;

    S21Matrix tmp(*this);
    edit_cols(other.get_cols());
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < other.get_cols(); ++j) {
        matrix_[i][j] = 0;
        for (int k = 0; k < cols_; ++k) matrix_[i][j] += tmp[i][k] * other[k][j];
    }
}

S21Matrix S21Matrix::Transpose() const {
    if (!rows_) throw exception;

    S21Matrix transposed(cols_, rows_);
    for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) transposed[j][i] = matrix_[i][j];
}

S21Matrix S21Matrix::CalcComplements() const {
    if (!rows_ || rows_ != cols_) throw exception;

    S21Matrix complement_matrix(rows_, cols_);
    if (rows_ == 1) complement_matrix[0][0] = 1;
    else {
        complement_matrix.edit_rows(rows_);
        complement_matrix.edit_cols(cols_);
        for (int i = 0; i < rows_; ++i) for (int j = 0; j < cols_; ++j) {
                S21Matrix minor = Minor(i, j);
                complement_matrix[i][j] = minor.Determinant() * pow(-1, i + j);
//            minor.~S21Matrix();
            }
    }
    return complement_matrix;
}

double S21Matrix::Determinant() const {
    if (!rows_ || rows_ != cols_) throw exception;

    S21Matrix tmp(*this);
    double result = 1;
    if (!tmp.IsTriangle()) result = pow(-1, tmp.GaussianMethod());
    for (int i = 0; i < rows_; ++i) result *= tmp[i][i];

    return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
    double det;
    if (!rows || rows_ != cols_ || !(det = Determinant())) throw exception;

    S21Matrix complement_matrix = CalcComplements();
    S21Matrix result = complement_matrix.Transpose();
    result *= 1 / det;
    return result;
}

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
    if (!other.get_rows()) throw exception;

    ~S21Matrix();
    S21Matrix(&other);
}

void S21Matrix::operator=(const S21Matrix&& other) {
    if (!other.get_rows()) throw exception;

    ~S21Matrix();
    S21Matrix(&&other);
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double* S21Matrix::operator[](int i) const {
    if (!rows_) throw exception;

    return matrix_[i];
}