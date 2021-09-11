#include <cstdint>
#include <memory>

#include "common.h"
#include "gtest/gtest.h"

using namespace vision;

TEST(matrix, constructor1) {
  Matrix<float> mat = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  EXPECT_EQ(mat.rows(), 2);
  EXPECT_EQ(mat.cols(), 3);
  EXPECT_TRUE(mat.data() != nullptr);
  EXPECT_FLOAT_EQ(mat(0, 1), 2.1);
}

TEST(matrix, constructor2) {
  Matrix<float> mat = {{1.1, 2.1}, {1.3, 4.1}, {2.3, -0.09}};
  EXPECT_EQ(mat.rows(), 3);
  EXPECT_EQ(mat.cols(), 2);
  EXPECT_TRUE(mat.data() != nullptr);
  EXPECT_FLOAT_EQ(mat(1, 1), 4.1);
}

TEST(matrix, constructor3) {
  Matrix<float> mat(3, 2, 1.5);
  EXPECT_EQ(mat.rows(), 3);
  EXPECT_EQ(mat.cols(), 2);
  EXPECT_TRUE(mat.data() != nullptr);
  EXPECT_FLOAT_EQ(mat(1, 1), 1.5);
}

TEST(matrix_DeathTest, constructor_mismatch_dimension) {
  Matrix<float> mat{};
  GTEST_FLAG_SET(death_test_style, "threadsafe");
  EXPECT_DEATH((mat = {{1.1, 2.1}, {1.3, 4.1, 5.5}, {2.3, -0.09}}), "");
}

TEST(matrix, copy_constructor) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  auto mat2(mat1);
  EXPECT_EQ(mat1.rows(), mat2.rows());
  EXPECT_EQ(mat1.cols(), mat2.cols());
}

TEST(matrix, assign) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  auto mat2 = mat1;
  EXPECT_EQ(mat1.rows(), mat2.rows());
  EXPECT_EQ(mat1.cols(), mat2.cols());
}

TEST(matrix_DeathTest, plus_invalid_dimentsion) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.1}, {1.3, 4.1}};
  EXPECT_DEATH((mat1 + mat2), "");
}

TEST(matrix, plus) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.1, 1.2}, {1.3, -4.1, -5.1}};
  auto mat3 = mat1 + mat2;
  Matrix<float> mat4 = {{2.2, 4.2, 4.2}, {2.6, 0, 0}};
  EXPECT_TRUE(mat3 == mat4);
}

TEST(matrix, plus_diff_data_type) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<int> mat2 = {{1, 3, 2}, {4, -4, -5}};
  auto mat3 = mat1 + mat2;
  Matrix<float> mat4 = {{2.1, 5.1, 5}, {5.3, 0.1, 0.1}};
  EXPECT_TRUE(mat3 == mat4);
}

TEST(matrix_DeathTest, minus_invalid_dimentsion) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.1}, {1.3, 4.1}};
  EXPECT_DEATH((mat1 - mat2), "");
}

TEST(matrix, minus) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.1, 1.2}, {1.3, -4.1, -5.1}};
  auto mat3 = mat1 - mat2;
  Matrix<float> mat4 = {{0, 0, 1.8}, {0, 8.2, 10.2}};
  EXPECT_TRUE(mat3 == mat4);
}

TEST(matrix, minus_diff_data_type) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<int> mat2 = {{1, 2, 3}, {3, -5, -5}};
  auto mat3 = mat1 - mat2;
  Matrix<float> mat4 = {{0.1, 0.1, 0}, {-1.7, 9.1, 10.1}};
  EXPECT_TRUE(mat3 == mat4);
}

TEST(matrix_DeathTest, multiply_invalid_dimentsion) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.1}, {1.3, 4.1}};
  EXPECT_DEATH((mat1 * mat2), "");
}

TEST(matrix, multiply) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.1}, {1.3, -4.1}, {1, 1.2}};
  auto mat3 = mat1 * mat2;
  Matrix<float> mat4 = {{6.94, -2.7}, {11.86, -7.96}};
  EXPECT_TRUE(mat3 == mat4);
}

TEST(matrix, multiply_diff_data_type) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1, 2}, {1, -4}, {1, 1}};
  auto mat3 = mat1 * mat2;
  Matrix<float> mat4 = {{6.2, -3.2}, {10.5, -8.7}};
  EXPECT_TRUE(mat3 == mat4);
  mat3.print();
  mat4.print();
}

TEST(matrix, equal1) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  auto mat2 = mat1;
  EXPECT_TRUE(mat1 == mat2);
}

TEST(matrix, equal2) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat2 = {{1.1, 2.101, 3}, {1.3, 4.1, 5.1}};
  Matrix<float> mat3 = {{1.1, 2.1}, {1.3, 4.1}};
  EXPECT_FALSE(mat1 == mat2);
  EXPECT_FALSE(mat1 == mat3);
}

TEST(matrix, dispose) {
  Matrix<float> mat1 = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  auto mat2 = mat1.dispose();
  Matrix<float> mat3 = {{1.1, 1.3}, {2.1, 4.1}, {3, 5.1}};
  EXPECT_EQ(mat1.rows(), mat2.cols());
  EXPECT_EQ(mat1.cols(), mat2.rows());
  EXPECT_TRUE(mat2 == mat3);
}

TEST(matrix, at) {
  Matrix<float> mat = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  EXPECT_FLOAT_EQ(mat(0, 0), 1.1);
  EXPECT_FLOAT_EQ(mat(0, 1), 2.1);
  EXPECT_FLOAT_EQ(mat(0, 2), 3);
  EXPECT_FLOAT_EQ(mat(1, 0), 1.3);
  EXPECT_FLOAT_EQ(mat(1, 1), 4.1);
  EXPECT_FLOAT_EQ(mat(1, 2), 5.1);

  mat(1, 1) = 15.2;
  EXPECT_FLOAT_EQ(mat(1, 1), 15.2);
}

TEST(matrix, row) {
  Matrix<float> mat = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  auto row = mat.row(0);
  EXPECT_EQ(row.rows(), 1);
  EXPECT_EQ(row.cols(), 3);
  EXPECT_TRUE(row.data() != nullptr);
  EXPECT_FLOAT_EQ(row(0, 0), 1.1);
  EXPECT_FLOAT_EQ(row(0, 1), 2.1);
  EXPECT_FLOAT_EQ(row(0, 2), 3);
}

TEST(matrix, col) {
  Matrix<float> mat = {{1.1, 2.1, 3}, {1.3, 4.1, 5.1}};
  auto col = mat.col(1);
  EXPECT_EQ(col.rows(), 2);
  EXPECT_EQ(col.cols(), 1);
  EXPECT_TRUE(col.data() != nullptr);
  EXPECT_FLOAT_EQ(col(0, 0), 2.1);
  EXPECT_FLOAT_EQ(col(1, 0), 4.1);
}