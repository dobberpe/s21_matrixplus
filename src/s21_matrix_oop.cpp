#include "s21_matrix_oop.h"

void S21Matrix::AllocateMatrix() {
  matrix_ = (double**)malloc(rows_ * sizeof(double*));
  for (int i = 0; i < rows_; ++i)
    matrix_[i] = (double*)calloc(cols_, sizeof(double));
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other[i][j];
}

S21Matrix S21Matrix::Minor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int i = 0; i < rows_ - 1; ++i)
    for (int j = 0; j < cols_ - 1; ++j)
      minor[i][j] = matrix_[i < row ? i : i + 1][j < col ? j : j + 1];

  return minor;
}

bool S21Matrix::IsTriangle() const {
  bool res = true;
  for (int i = 0; i < rows_ && res; ++i)
    for (int j = 0; j < i && res; ++j) res = matrix_[i][j] == 0;
  return res;
}

int S21Matrix::GaussianMethod() {
  int swap_counter = 0;

  //    printf("\nGauss\n");

  for (int j = 0; j < cols_; ++j) {
    int i = j + 1;
    while (i < rows_) {
      if (matrix_[j][j]) {
        double factor = matrix_[i][j] / matrix_[j][j];
        for (int k = j; k < cols_; ++k) matrix_[i][k] -= factor * matrix_[j][k];
        ++i;
        //        printf("\n[%d] - %f * [%d]\n", i, factor, j);
        //          for (int i = 0; i < rows_; ++i) {
        //              for (int j = 0; j < cols_; ++j) printf("%f ",
        //              matrix_[i][j]); printf("\n");
        //          }
      } else if (SwapRows(j))
        ++swap_counter;
      else
        i = rows_;  // j = cols_; ?
    }
  }
  return swap_counter;
}

bool S21Matrix::SwapRows(int j) {
  int swap_row = j;

  for (int i = j + 1; i < rows_ && swap_row == j; ++i)
    swap_row = matrix_[i][j] != 0 ? i : j;

  bool res = swap_row != j;

  for (int i = 0; i < cols_ && res; ++i) {
    double tmp = matrix_[j][i];
    matrix_[j][i] = matrix_[swap_row][i];
    matrix_[swap_row][i] = tmp;
  }

  //  if (res) {
  //      printf("\n[%d] ~ [%d]\n", j, swap_row);
  //      for (int i = 0; i < rows_; ++i) {
  //          for (int j = 0; j < cols_; ++j) printf("%f ", matrix_[i][j]);
  //          printf("\n");
  //      }
  //  }

  return res;
}

S21Matrix::S21Matrix() : rows_(1), cols_(1) { AllocateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) throw runtime_error("Invalid parameters.");

  AllocateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (!other.get_rows()) throw runtime_error("Empty matrix.");

  AllocateMatrix();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  if (!other.get_rows()) throw runtime_error("Empty matrix.");

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) free(matrix_[i]);
    free(matrix_);
  }

  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

int S21Matrix::get_rows() const { return rows_; }

int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::edit_rows(int rows) {
  if (rows <= 0) throw runtime_error("Invalid number of rows.");

  matrix_ = (double**)realloc(matrix_, rows * sizeof(double*));
  if (rows > rows_)
    for (int i = rows_; i < rows; ++i)
      matrix_[i] = (double*)calloc(cols_, sizeof(double));
  rows_ = rows;
}

void S21Matrix::edit_cols(int cols) {
  if (cols <= 0) throw runtime_error("Invalid number of columns.");

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = (double*)realloc(matrix_, cols * sizeof(double));
    if (cols > cols_)
      for (int j = cols_; j < cols; ++j) matrix_[i][j] = 0;
  }
  cols_ = cols;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (!rows_ || !other.get_rows()) throw runtime_error("Empty matrix.");
  if (rows_ != other.get_rows() || cols_ != other.get_cols())
    throw runtime_error("Different sizes of matrices.");

  bool res = true;

  for (int i = 0; i < rows_ && res; ++i)
    for (int j = 0; j < cols_ && res; ++j)
      res = fabs(matrix_[i][j] - other[i][j]) < S21_EPS;

  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!rows_ || !other.get_rows()) throw runtime_error("Empty matrix.");
  if (rows_ != other.get_rows() || cols_ != other.get_cols())
    throw runtime_error("Different sizes of matrices.");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!rows_ || !other.get_rows()) throw runtime_error("Empty matrix.");
  if (rows_ != other.get_rows() || cols_ != other.get_cols())
    throw runtime_error("Different sizes of matrices.");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other[i][j];
}

void S21Matrix::MulNumber(const double num) {
  if (!rows_) throw runtime_error("Empty matrix.");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!rows_ || !other.get_rows()) throw runtime_error("Empty matrix.");
  if (cols_ != other.get_rows()) throw runtime_error("Invalid matrices sizes.");

  S21Matrix tmp(*this);
  edit_cols(other.get_cols());
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      double value = 0;
      for (int k = 0; k < tmp.get_cols(); ++k) value += tmp[i][k] * other[k][j];
      matrix_[i][j] = value;
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  if (!rows_) throw runtime_error("Empty matrix.");

  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) transposed[j][i] = matrix_[i][j];

  return transposed;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (!rows_) throw runtime_error("Empty matrix.");
  if (rows_ != cols_) throw runtime_error("The matrix isn't square.");

  S21Matrix complement_matrix(rows_, cols_);
  if (rows_ == 1)
    complement_matrix[0][0] = 1;
  else {
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor = Minor(i, j);
        complement_matrix[i][j] = minor.Determinant() * pow(-1, i + j);
      }
  }
  return complement_matrix;
}

double S21Matrix::Determinant() const {
  if (!rows_) throw runtime_error("Empty matrix.");
  if (rows_ != cols_) throw runtime_error("The matrix isn't square.");

  S21Matrix tmp(*this);
  //  printf("\nStart det\n");
  //  for (int i = 0; i < rows_; ++i) {
  //      for (int j = 0; j < cols_; ++j) printf("%f ", tmp[i][j]);
  //      printf("\n");
  //  }
  double result = 1;
  if (!tmp.IsTriangle()) result = pow(-1, tmp.GaussianMethod());
  for (int i = 0; i < rows_; ++i) result *= tmp[i][i];

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (!rows_) throw runtime_error("Empty matrix.");
  if (rows_ != cols_) throw runtime_error("The matrix isn't square.");
  double det;
  if (!(det = Determinant())) throw runtime_error("Singular matrix.");

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

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

void S21Matrix::operator=(const S21Matrix& other) {
  if (!other.get_rows()) throw runtime_error("Empty matrix.");

  edit_rows(other.get_rows());
  edit_cols(other.get_cols());
  CopyMatrix(other);
}

void S21Matrix::operator=(S21Matrix&& other) {
  if (!other.get_rows()) throw runtime_error("Empty matrix.");

  edit_rows(other.get_rows());
  edit_cols(other.get_cols());
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double* S21Matrix::operator[](int i) const {
  if (i < 0 || i >= rows_) throw runtime_error("Invalid index.");

  return matrix_[i];
}