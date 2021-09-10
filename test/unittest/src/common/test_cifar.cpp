#include <cstdint>
#include <memory>

#include "common.h"
#include "gtest/gtest.h"

using namespace vision;

TEST(cifar, constructor) {
  std::string file_path = "../resource/cifar-100-binary";
  CifarConfig config{.bin_type = BinType::TEST,
                     .label_type = LabelType::COARSE};
  auto cifar = Cifar(file_path, config);

  EXPECT_EQ(cifar.get_image_count(), 10000);
  EXPECT_EQ(cifar.get_image_shpae(), 3072);
  EXPECT_EQ(cifar.get_label_count(), 20);
}

TEST(cifar, classify) {
  std::string file_path = "../resource/cifar-100-binary";
  CifarConfig config{.bin_type = BinType::TEST,
                     .label_type = LabelType::COARSE};
  auto cifar = Cifar(file_path, config);

  cifar.classify<float>();
}