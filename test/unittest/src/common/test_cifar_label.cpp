#include <cstdint>
#include <memory>

#include "common.h"
#include "gtest/gtest.h"

using namespace vision;

TEST(cifar_label, constructor_coarse) {
  std::string file_path = "../resource/cifar-100-binary/coarse_label_names.txt";
  auto cifar_label = CifarLabel(file_path);

  EXPECT_EQ(cifar_label.get_label_count(), 20);
  EXPECT_EQ(cifar_label.get_label_list().size(), cifar_label.get_label_count());
}

TEST(cifar_label, constructor_fine) {
  std::string file_path = "../resource/cifar-100-binary/fine_label_names.txt";
  auto cifar_label = CifarLabel(file_path);

  EXPECT_EQ(cifar_label.get_label_count(), 100);
  EXPECT_EQ(cifar_label.get_label_list().size(), cifar_label.get_label_count());
}

TEST(cifar_label, get_label_list_coarse) {
  std::string file_path = "../resource/cifar-100-binary/coarse_label_names.txt";
  auto cifar_label = CifarLabel(file_path);

  auto label_list = cifar_label.get_label_list();
  for (const auto &label : label_list) {
    printf("%s\n", label.c_str());
  }
}

TEST(cifar_label, get_label_list_fine) {
  std::string file_path = "../resource/cifar-100-binary/fine_label_names.txt";
  auto cifar_label = CifarLabel(file_path);

  auto label_list = cifar_label.get_label_list();
  for (const auto &label : label_list) {
    printf("%s\n", label.c_str());
  }
}