#ifndef MATRIX_H
#define MATRIX_H

#include "assertion.h"
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <math.h>
#include <vector>

namespace vision {
template <typename T> class Matrix {
public:
  ~Matrix() {}
  Matrix(size_t rows, size_t cols, const T *data = nullptr);
  Matrix(const Matrix<T> &b);
  Matrix<T> &operator=(const Matrix<T> &b);
  Matrix(std::initializer_list<std::initializer_list<T>>);

  T *data() { return reinterpret_cast<T *>(data_.data()); }
  const size_t rows() const { return rows_; }
  const size_t cols() const { return cols_; }

  const void print() const;

  const Matrix<T> dispose() const;
  // const Matrix<T> inverse() const;

  Matrix<T> operator+(const Matrix<T> &b);
  Matrix<T> operator-(const Matrix<T> &b);
  Matrix<T> operator*(const Matrix<T> &b);
  bool operator==(const Matrix<T> &b);

  T operator()(size_t row, size_t col);

private:
  std::vector<T> data_{}; // row first
  size_t rows_{};
  size_t cols_{};
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T *data)
    : rows_(rows), cols_(cols) {
  data_.resize(rows_ * cols_);
  if (data) {
    std::memcpy(data_.data(), data, rows_ * cols_ * sizeof(T));
  }
}

template <typename T> Matrix<T>::Matrix(const Matrix<T> &b) {
  rows_ = b.rows();
  cols_ = b.cols();
  data_.resize(rows_ * cols_);
  std::memcpy(data_.data(), b.data_.data(), rows_ * cols_ * sizeof(T));
}

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &b) {
  rows_ = b.rows();
  cols_ = b.cols();
  data_.resize(rows_ * cols_);
  if (this != &b) {
    std::memcpy(data_.data(), b.data_.data(), rows_ * cols_ * sizeof(T));
  }
  return *this;
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> lst)
    : rows_(lst.size()), cols_(0) {
  for (const auto &row : lst) { // row first
    if (cols_ == 0) {
      cols_ = row.size();
    }
    ASSERT(row.size() == cols_);
    data_.insert(data_.end(), row.begin(), row.end());
  }
}

template <typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T> &b) {
  ASSERT(rows_ > 0 && cols_ > 0);
  ASSERT(rows_ == b.rows());
  ASSERT(cols_ == b.cols());
  Matrix<T> matrix(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix.data_[i * cols_ + j] =
          data_[i * cols_ + j] + b.data_[i * cols_ + j];
    }
  }
  return std::move(matrix);
}

template <typename T> Matrix<T> Matrix<T>::operator-(const Matrix<T> &b) {
  ASSERT(rows_ > 0 && cols_ > 0);
  ASSERT(rows_ == b.rows());
  ASSERT(cols_ == b.cols());
  Matrix<T> matrix(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix.data_[i * cols_ + j] =
          data_[i * cols_ + j] - b.data_[i * cols_ + j];
    }
  }
  return std::move(matrix);
}

template <typename T> Matrix<T> Matrix<T>::operator*(const Matrix<T> &b) {
  ASSERT(rows_ > 0 && cols_ > 0);
  ASSERT(cols_ == b.rows());
  auto rows = rows_;
  auto cols = b.cols();
  auto cal_cols = cols_;
  Matrix<T> matrix(rows, cols);
  for (auto i = 0; i < rows; i++) {
    for (auto j = 0; j < cols; j++) {
      for (auto k = 0; k < cal_cols; k++) {
        matrix.data_[i * cols + j] +=
            data_[i * cols_ + k] * b.data_[k * cols + j];
      }
    }
  }
  return std::move(matrix);
}

template <typename T> bool Matrix<T>::operator==(const Matrix<T> &b) {
  const float PRECISION = 0.000001f;
  if (this->rows() != b.rows() || this->cols() != b.cols()) {
    return false;
  }
  auto size = this->data_.size();
  for (auto i = 0; i < size; i++) {
    if (fabs(this->data_[i] - b.data_[i]) > PRECISION) {
      return false;
    }
  }
  return true;
}

template <typename T> T Matrix<T>::operator()(size_t row, size_t col) {
  ASSERT(row < rows_ && col < cols_);
  return data_[row * cols_ + col];
}

template <typename T> const Matrix<T> Matrix<T>::dispose() const {
  Matrix<T> matrix(cols_, rows_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix.data_[j * rows_ + i] = data_[i * cols_ + j];
    }
  }
  return std::move(matrix);
}

template <typename T> const void Matrix<T>::print() const {
  std::string format_str = "";
  if (typeid(T).hash_code() == typeid(float).hash_code()) {
    format_str = "%f, ";
  } else if (typeid(T).hash_code() == typeid(int).hash_code()) {
    format_str = "%d, ";
  } else if (typeid(T).hash_code() == typeid(uint8_t).hash_code()) {
    format_str = "%d, ";
  } else {
    fprintf(stderr, "unsupport data type.\n");
    exit(0);
  }

  printf("[\n");
  size_t num = 0;
  bool new_line = false;
  for (const auto &val : data_) {
    if (num % cols_ == 0) {
      if (num > 0) {
        printf("}\n");
      }
      printf("{");
      new_line = true;
    } else {
      new_line = false;
    }
    printf(format_str.c_str(), val);
    num++;
  }
  printf("}\n]\n");
}

} // namespace vision

#endif // MATRIX_H