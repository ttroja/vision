#ifndef BIN_H
#define BIN_H

#include "common/matrix.h"
#include "common/struct.h"
#include <cstring>
#include <memory>
#include <string>

namespace vision {
class CifarBin {
public:
  explicit CifarBin(const std::string &filename);

  // get <rr...r><gg...g><bb...b> panel data
  Matrix<uint8_t> get_image_origin(size_t index) const;

  // get <bgr><bgr><bgr> data (opencv style)
  Matrix<uint8_t> get_image_opencv(size_t index) const;

  // get <coarse, fine> label
  std::pair<size_t, size_t> get_image_label(size_t index) const;

  Matrix<uint8_t> get_image_r(size_t index) const;
  Matrix<uint8_t> get_image_g(size_t index) const;
  Matrix<uint8_t> get_image_b(size_t index) const;

  size_t get_image_count() const;
  size_t get_file_size() const;
  Shape get_image_shape() const;

private:
  std::unique_ptr<uint8_t[]> buffer_{};

  size_t image_count_{0};
  size_t file_size_{0};

  static constexpr size_t COARSE_FINE_BYTE = 2;
  static constexpr size_t HEIGHT = 32;
  static constexpr size_t WIDTH = 32;
  static constexpr size_t CHANNEL = 3;
};

} // namespace vision

#endif // BIN_H