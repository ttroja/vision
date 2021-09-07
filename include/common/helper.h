#ifndef HELPER_H
#define HELPER_H

#include "matrix.h"
#include <cstdio>
#include <memory>
#include <string>

namespace vision {
enum class PosOrigin {
  SET = SEEK_SET,
  CURRENT = SEEK_CUR,
  END = SEEK_END,
};

class File {
public:
  explicit File(const std::string &filename);
  ~File() { close(); }

  size_t read(void *buf, size_t size);
  bool seek(long int offset, PosOrigin origin);
  size_t tell() const;
  void close();
  bool ok() const;
  bool eof() const;
  size_t size() const;

private:
  FILE *fp_{};
  std::string filename_{};
  size_t size_{};
  size_t pos_{};
};

class CifarBin {
public:
  explicit CifarBin(const std::string &filename);

  // get <rr...r><gg...g><bb...b> panel data
  Matrix<uint8_t> get_image_origin(size_t index) const;

  // get <bgr><bgr><bgr> data (opencv style)
  Matrix<uint8_t> get_image_opencv(size_t index) const;

  Matrix<uint8_t> get_image_r(size_t index) const;
  Matrix<uint8_t> get_image_g(size_t index) const;
  Matrix<uint8_t> get_image_b(size_t index) const;

  size_t get_file_count() const;
  size_t get_file_size() const;

private:
  std::unique_ptr<uint8_t[]> buffer_{};

  size_t file_count_{0};
  size_t file_size_{0};

  static constexpr size_t COARSE_FINE_BYTE = 2;
  static constexpr size_t HEIGHT = 32;
  static constexpr size_t WIDTH = 32;
  static constexpr size_t CHANNEL = 3;
};

} // namespace vision

#endif // HELPER_H