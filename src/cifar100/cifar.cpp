#include "cifar100/cifar.h"

namespace vision {

Cifar::Cifar(const std::string &path, const CifarConfig &config) : path_(path) {
  auto path_fine_label = path_ + "/" + FINE_LABEL;
  auto path_coarse_label = path_ + "/" + COARSE_LABEL;
  cifar_fine_label_ = std::make_shared<CifarLabel>(path_fine_label);
  cifar_coarse_label_ = std::make_shared<CifarLabel>(path_coarse_label);

  if (config.bin_type == BinType::TEST) {
    auto path_test_bin = path_ + "/" + TEST_BIN;
    cifar_bin_ = std::make_shared<CifarBin>(path_test_bin);
  } else {
    auto path_train_bin = path_ + "/" + TRAIN_BIN;
    cifar_bin_ = std::make_shared<CifarBin>(path_train_bin);
  }

  image_count_ = cifar_bin_->get_image_count();
  auto shape = cifar_bin_->get_image_shape();
  image_shape_ = shape.channel * shape.width * shape.height;

  if (config.label_type == LabelType::COARSE) {
    label_count_ = cifar_coarse_label_->get_label_count();
  } else {
    label_count_ = cifar_fine_label_->get_label_count();
  }
}

} // namespace vision