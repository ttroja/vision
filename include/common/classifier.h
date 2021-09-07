#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "matrix.h"
#include <memory>

namespace vision {
enum class ClassifierType { LINEAR, ALL_CONNET };

template <typename T> class Classifier {
public:
  virtual ~Classifier(){};

  virtual void set_weight(const Matrix<T> &weight) = 0;
  virtual const Matrix<T> get_weight() = 0;

  virtual void set_bias(const Matrix<T> &bias) = 0;
  virtual const Matrix<T> get_bias() = 0;

  virtual const Matrix<T> get_score(const Matrix<T> &x) = 0;

  static std::shared_ptr<Classifier<T>> make(int rows, int cols,
                                             ClassifierType type);
};

template <typename T> class LinearClassifier : public Classifier<T> {
public:
  LinearClassifier() = default;
  // rows means the number of the classifier, cols means the dimension of the
  // sample
  explicit LinearClassifier(int rows, int cols) : rows_(rows), cols_(cols) {}

  virtual void set_weight(const Matrix<T> &weight) override;
  virtual const Matrix<T> get_weight() override { return w_; }

  virtual void set_bias(const Matrix<T> &bias) override;
  virtual const Matrix<T> get_bias() override { return b_; }

  virtual const Matrix<T> get_score(const Matrix<T> &x) override;

private:
  Matrix<T> w_{};
  Matrix<T> b_{};
  float lambda_{};
  int rows_{};
  int cols_{};
};

template <typename T>
void LinearClassifier<T>::set_weight(const Matrix<T> &weight) {
  ASSERT(weight.rows() == rows_);
  ASSERT(weight.cols() == cols_);
  w_ = weight;
}

template <typename T>
void LinearClassifier<T>::set_bias(const Matrix<T> &bias) {
  ASSERT(bias.rows() == rows_);
  ASSERT(bias.cols() == 1);
  b_ = bias;
}

template <typename T>
const Matrix<T> LinearClassifier<T>::get_score(
    const Matrix<T> &x) { // this will return a matrix, not a value
  return w_ * x + b_;
}

template <typename T>
std::shared_ptr<Classifier<T>> Classifier<T>::make(int rows, int cols,
                                                   ClassifierType type) {
  return std::make_shared<LinearClassifier<T>>(rows, cols);
}

} // namespace vision

#endif // CLASSIFIER_H