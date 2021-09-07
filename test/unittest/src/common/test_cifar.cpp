#include <cstdint>
#include <memory>

#include <fstream>

#include "common.h"
#include "opencv2/opencv.hpp"
#include "gtest/gtest.h"

using namespace vision;

TEST(cifar, constructor) {
  std::string file_path = "../resource/cifar-100-binary/test.bin";
  auto cifar = CifarBin(file_path);
  EXPECT_TRUE(cifar.get_file_count() == 10000);
  EXPECT_TRUE(cifar.get_file_size() > 0);
}

TEST(cifar, get_image_origin) {
  std::string file_path = "../resource/cifar-100-binary/test.bin";
  auto cifar = CifarBin(file_path);

  auto matrix = cifar.get_image_origin(0);
  EXPECT_EQ(matrix.rows(), 3072);
  EXPECT_EQ(matrix.cols(), 1);

  cv::Mat img(32, 32, CV_8UC3, matrix.data());
  std::string result_path = "image_origin.png";
  cv::imwrite(result_path, img);
}

TEST(cifar, get_image_opencv) {
  std::string file_path = "../resource/cifar-100-binary/test.bin";
  auto cifar = CifarBin(file_path);

  auto matrix = cifar.get_image_opencv(0);
  EXPECT_EQ(matrix.rows(), 3072);
  EXPECT_EQ(matrix.cols(), 1);

  cv::Mat img(32, 32, CV_8UC3, matrix.data());
  std::string result_path = "image_opencv.png";
  cv::imwrite(result_path, img);
}

TEST(cifar, get_image_r) {
  std::string file_path = "../resource/cifar-100-binary/test.bin";
  auto cifar = CifarBin(file_path);

  auto matrix = cifar.get_image_r(1);
  EXPECT_EQ(matrix.rows(), 32 * 32);
  EXPECT_EQ(matrix.cols(), 1);

  cv::Mat img(32, 32, CV_8UC1, matrix.data());
  std::string result_path = "test_r.png";
  cv::imwrite(result_path, img);
}

TEST(cifar, get_image_g) {
  std::string file_path = "../resource/cifar-100-binary/test.bin";
  auto cifar = CifarBin(file_path);

  auto matrix = cifar.get_image_g(3);
  EXPECT_EQ(matrix.rows(), 32 * 32);
  EXPECT_EQ(matrix.cols(), 1);

  cv::Mat img(32, 32, CV_8UC1, matrix.data());
  std::string result_path = "test_g.png";
  cv::imwrite(result_path, img);
}

TEST(cifar, get_image_b) {
  std::string file_path = "../resource/cifar-100-binary/test.bin";
  auto cifar = CifarBin(file_path);

  auto matrix = cifar.get_image_b(11);
  EXPECT_EQ(matrix.rows(), 32 * 32);
  EXPECT_EQ(matrix.cols(), 1);

  cv::Mat img(32, 32, CV_8UC1, matrix.data());
  std::string result_path = "test_b.png";
  cv::imwrite(result_path, img);
}