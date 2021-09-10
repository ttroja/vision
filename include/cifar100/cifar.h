#ifndef CIFAR_H
#define CIFAR_H

#include "bin.h"
#include "common/classifier.h"
#include "common/exception.h"
#include "common/struct.h"
#include "label.h"
#include <memory>
#include <string>

namespace vision {
class Cifar {
public:
  explicit Cifar(const std::string &path, const CifarConfig &config);

  template <typename T> void classify();

  size_t get_image_count() const { return image_count_; }
  size_t get_image_shpae() const { return image_shape_; }
  size_t get_label_count() const { return label_count_; }

private:
  // template <typename T>
  // void classify_once(std::shared_ptr<Classifier<T>> classifier);

  size_t image_count_{};
  size_t image_shape_{};
  size_t label_count_{};

  std::string path_{};
  std::shared_ptr<CifarBin> cifar_bin_{};
  std::shared_ptr<CifarLabel> cifar_fine_label_{};
  std::shared_ptr<CifarLabel> cifar_coarse_label_{};

  const std::string TEST_BIN = "test.bin";
  const std::string TRAIN_BIN = "train.bin";
  const std::string FINE_LABEL = "fine_label_names.txt";
  const std::string COARSE_LABEL = "coarse_label_names.txt";
};

template <typename T> void Cifar::classify() {
  auto classifier =
      Classifier<T>::make(label_count_, image_shape_, ClassifierType::LINEAR);
  CHECK_THROW(classifier != nullptr, ErrorCode::FAILURE,
              "make classifier failed.");
  // weight
  Matrix<T> weight(label_count_, image_shape_);
  Matrix<T> bias(label_count_, 1);
  classifier->set_weight(weight);
  classifier->set_bias(bias);

  auto result = classifier->get_score(cifar_bin_->get_image_origin(0));

  result.print();
  // for(auto i=0; i<image_count; i++){
  //   classifier->get_score();
  // }
}

} // namespace vision

#endif // CIFAR_H