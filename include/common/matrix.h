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
  Matrix(size_t rows, size_t cols, T default_value);
  Matrix(size_t rows, size_t cols, const T *data = nullptr);
  Matrix(const Matrix<T> &b);
  Matrix<T> &operator=(const Matrix<T> &b);
  Matrix(std::initializer_list<std::initializer_list<T>>);

  T *data() { return reinterpret_cast<T *>(data_.data()); }
  const size_t rows() const { return rows_; }
  const size_t cols() const { return cols_; }

  const Matrix<T> row(size_t index) const;
  const Matrix<T> col(size_t index) const;

  const void print() const;

  const Matrix<T> dispose() const;
  // const Matrix<T> inverse() const;

  template <typename J, typename K>
  friend Matrix<J> operator+(const Matrix<J> &a, const Matrix<K> &b);

  template <typename J, typename K>
  friend Matrix<J> operator-(const Matrix<J> &a, const Matrix<K> &b);

  template <typename J, typename K>
  friend Matrix<J> operator*(const Matrix<J> &a, const Matrix<K> &b);

  bool operator==(const Matrix<T> &b);

  T &operator()(size_t row, size_t col);

private:
  std::vector<T> data_{}; // row first
  size_t rows_{};
  size_t cols_{};
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T default_value)
    : rows_(rows), cols_(cols) {
  data_.resize(rows_ * cols_, default_value);
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T *data)
    : rows_(rows), cols_(cols) {
  data_.resize(rows_ * cols_);
  if (data) {
    std::memcpy(
        data_.data(), data,
        rows_ * cols_ *
            sizeof(T)); // use data directly without copy will more efficient
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

template <typename T> const Matrix<T> Matrix<T>::row(size_t index) const {
  ASSERT(index < rows_);
  Matrix<T> matrix(1, cols_);
  std::memcpy(matrix.data_.data(), data_.data() + index * cols_,
              cols_ * sizeof(T));
  return std::move(matrix);
}

template <typename T> const Matrix<T> Matrix<T>::col(size_t index) const {
  ASSERT(index < cols_);
  Matrix<T> matrix(rows_, 1);
  for (auto i = 0; i < rows_; i++) {
    matrix.data_[i] = data_[i * cols_ + index];
  }
  return std::move(matrix);
}

template <typename J, typename K>
Matrix<J> operator+(const Matrix<J> &a, const Matrix<K> &b) {
  ASSERT(a.rows_ > 0 && b.cols_ > 0);
  ASSERT(a.rows_ == b.rows_);
  ASSERT(a.cols_ == b.cols_);
  Matrix<J> matrix(a.rows_, a.cols_);
  for (auto i = 0; i < a.rows_; i++) {
    for (auto j = 0; j < a.cols_; j++) {
      matrix.data_[i * a.cols_ + j] =
          a.data_[i * a.cols_ + j] + b.data_[i * a.cols_ + j];
    }
  }
  return std::move(matrix);
}

template <typename J, typename K>
Matrix<J> operator-(const Matrix<J> &a, const Matrix<K> &b) {
  ASSERT(a.rows_ > 0 && a.cols_ > 0);
  ASSERT(a.rows_ == b.rows_);
  ASSERT(a.cols_ == b.cols_);
  Matrix<J> matrix(a.rows_, a.cols_);
  for (auto i = 0; i < a.rows_; i++) {
    for (auto j = 0; j < a.cols_; j++) {
      matrix.data_[i * a.cols_ + j] =
          a.data_[i * a.cols_ + j] - b.data_[i * a.cols_ + j];
    }
  }
  return std::move(matrix);
}

template <typename J, typename K>
Matrix<J> operator*(const Matrix<J> &a, const Matrix<K> &b) {
  ASSERT(a.rows_ > 0 && a.cols_ > 0);
  ASSERT(a.cols_ == b.rows_);
  auto rows = a.rows_;
  auto cols = b.cols_;
  auto cal_cols = a.cols_;
  Matrix<J> matrix(rows, cols);
  for (auto i = 0; i < rows; i++) {
    for (auto j = 0; j < cols; j++) {
      for (auto k = 0; k < cal_cols; k++) {
        matrix.data_[i * cols + j] +=
            a.data_[i * a.cols_ + k] * b.data_[k * cols + j];
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

template <typename T> T &Matrix<T>::operator()(size_t row, size_t col) {
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
    format_str = "%f";
  } else if (typeid(T).hash_code() == typeid(int).hash_code()) {
    format_str = "%d";
  } else if (typeid(T).hash_code() == typeid(uint8_t).hash_code()) {
    format_str = "%d";
  } else {
    fprintf(stderr, "unsupport data type.\n");
    exit(0);
  }

  printf("[\n");
  size_t num = 0;
  for (const auto &val : data_) {
    if (num % cols_ == 0) {
      if (num > 0) {
        printf("}\n");
      }
      printf(("  {" + format_str).c_str(), val);
    } else {
      printf((", " + format_str).c_str(), val);
    }
    num++;
  }
  printf("}\n]\n");
}

} // namespace vision

#endif // MATRIX_H