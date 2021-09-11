#include <cstdint>
#include <memory>

#include "common.h"
#include "gtest/gtest.h"

using namespace vision;

TEST(classifier, make) {
  auto classifier = Classifier<float>::make(3, 2, ClassifierType::LINEAR);
  EXPECT_TRUE(classifier != nullptr);
}

TEST(classifier, set_weight) {
  auto classifier = Classifier<float>::make(3, 2, ClassifierType::LINEAR);
  EXPECT_TRUE(classifier != nullptr);

  Matrix<float> mat1 = {{1.1, 2.1}, {1.3, 4.1}, {2.1, 1.0}};

  classifier->set_weight(mat1);

  auto mat2 = classifier->get_weight();

  EXPECT_TRUE(mat1 == mat2);
}

TEST(classifier, set_bias) {
  auto classifier = Classifier<float>::make(3, 2, ClassifierType::LINEAR);
  EXPECT_TRUE(classifier != nullptr);

  Matrix<float> mat1 = {{1.1, 2.1, 3}};
  classifier->set_bias(mat1.dispose());

  auto mat2 = classifier->get_bias().dispose();

  EXPECT_TRUE(mat1 == mat2);
}

TEST(classifier, get_score) {
  auto classifier = Classifier<float>::make(3, 3, ClassifierType::LINEAR);
  EXPECT_TRUE(classifier != nullptr);

  Matrix<float> weight = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}, {1.1, 2.1, 0.3}};
  Matrix<float> bias = {{1.1, 2.1, 3}};

  Matrix<uint8_t> sample = {{1, 2, 3}};

  classifier->set_weight(weight);
  classifier->set_bias(bias.dispose());

  auto score = classifier->get_score(sample.dispose());
  score.print();
}