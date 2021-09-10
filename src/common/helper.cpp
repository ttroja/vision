#include "common/helper.h"
#include "common/exception.h"

namespace vision {

File::File(std::string const &filename) {
  fp_ = fopen(filename.c_str(), "rb");
  CHECK_THROW(fp_ != nullptr, ErrorCode::INVALID_FILE,
              "Fail to open file '%s'.", filename.c_str());
  fseek(fp_, 0, SEEK_END);
  size_ = ftell(fp_);
  fseek(fp_, 0, SEEK_SET);
  pos_ = 0;
};

size_t File::read(void *buf, size_t size) {
  auto ret = fread(buf, 1, size, fp_);
  pos_ += ret;
  return ret;
}

bool File::seek(long int offset, PosOrigin origin) {
  auto ret = fseek(fp_, offset, static_cast<int>(origin)) == 0;
  pos_ = ftell(fp_);
  return ret;
}

size_t File::tell() const { return pos_; }

size_t File::size() const { return size_; }

void File::close() {
  if (fp_)
    fclose(fp_);
  fp_ = nullptr;
}

bool File::ok() const { return (fp_ != nullptr); }

bool File::eof() const { return pos_ >= size_; }

CifarBin::CifarBin(const std::string &filename) {
  File file(filename);
  file_size_ = file.size();
  ASSERT(file_size_ % (HEIGHT * WIDTH * CHANNEL + COARSE_FINE_BYTE) == 0);
  file_count_ = file_size_ / (HEIGHT * WIDTH * CHANNEL + COARSE_FINE_BYTE);

  buffer_.reset(new uint8_t[file_size_]{});
  file.read(buffer_.get(), file_size_);
  file.close();
}

Matrix<uint8_t> CifarBin::get_image_origin(size_t index) const {
  ASSERT(index < file_count_);
  constexpr size_t file_size = HEIGHT * WIDTH * CHANNEL;
  size_t pos = index * (file_size + COARSE_FINE_BYTE) + COARSE_FINE_BYTE;
  Matrix<uint8_t> matrix(HEIGHT * WIDTH * CHANNEL, 1);
  memcpy(matrix.data(), buffer_.get() + pos, file_size);
  return std::move(matrix);
}

std::pair<size_t, size_t> CifarBin::get_image_label(size_t index) const {
  ASSERT(index < file_count_);
  constexpr size_t file_size = HEIGHT * WIDTH * CHANNEL;
  size_t pos = index * (file_size + COARSE_FINE_BYTE);

  return std::make_pair(*(buffer_.get() + pos), *(buffer_.get() + pos + 1));
}

Matrix<uint8_t> CifarBin::get_image_opencv(size_t index) const {
  ASSERT(index < file_count_);
  constexpr size_t file_size = HEIGHT * WIDTH * CHANNEL;
  size_t pos = index * (file_size + COARSE_FINE_BYTE) + COARSE_FINE_BYTE;
  Matrix<uint8_t> matrix(HEIGHT * WIDTH * CHANNEL, 1);

  constexpr size_t patch_size = HEIGHT * WIDTH;

  // copy b
  uint8_t *dst_ptr = matrix.data();
  uint8_t *src_ptr = buffer_.get() + pos + 2 * patch_size;
  for (auto i = 0; i < patch_size; i++) {
    *(dst_ptr) = *(src_ptr);
    dst_ptr += CHANNEL;
    src_ptr++;
  }
  // copy g
  dst_ptr = matrix.data() + 1;
  src_ptr = buffer_.get() + pos + 1 * patch_size;
  for (auto i = 0; i < patch_size; i++) {
    *(dst_ptr) = *(src_ptr);
    dst_ptr += CHANNEL;
    src_ptr++;
  }
  // copy r
  dst_ptr = matrix.data() + 2;
  src_ptr = buffer_.get() + pos;
  for (auto i = 0; i < patch_size; i++) {
    *(dst_ptr) = *(src_ptr);
    dst_ptr += CHANNEL;
    src_ptr++;
  }
  return std::move(matrix);
}

Matrix<uint8_t> CifarBin::get_image_r(size_t index) const {
  ASSERT(index < file_count_);
  constexpr size_t file_size = HEIGHT * WIDTH * CHANNEL;
  size_t pos = index * (file_size + COARSE_FINE_BYTE) + COARSE_FINE_BYTE;
  Matrix<uint8_t> matrix(HEIGHT * WIDTH, 1);

  constexpr size_t patch_size = HEIGHT * WIDTH;
  memcpy(matrix.data(), buffer_.get() + pos, patch_size);
  return std::move(matrix);
}

Matrix<uint8_t> CifarBin::get_image_g(size_t index) const {
  ASSERT(index < file_count_);
  constexpr size_t file_size = HEIGHT * WIDTH * CHANNEL;
  size_t pos = index * (file_size + COARSE_FINE_BYTE) + COARSE_FINE_BYTE;
  Matrix<uint8_t> matrix(HEIGHT * WIDTH, 1);

  constexpr size_t patch_size = HEIGHT * WIDTH;
  memcpy(matrix.data(), buffer_.get() + pos + 1 * patch_size, patch_size);
  return std::move(matrix);
}

Matrix<uint8_t> CifarBin::get_image_b(size_t index) const {
  ASSERT(index < file_count_);
  constexpr size_t file_size = HEIGHT * WIDTH * CHANNEL;
  size_t pos = index * (file_size + COARSE_FINE_BYTE) + COARSE_FINE_BYTE;
  Matrix<uint8_t> matrix(HEIGHT * WIDTH, 1);

  constexpr size_t patch_size = HEIGHT * WIDTH;
  memcpy(matrix.data(), buffer_.get() + pos + 2 * patch_size, patch_size);
  return std::move(matrix);
}

size_t CifarBin::get_file_count() const { return file_count_; }

size_t CifarBin::get_file_size() const { return file_size_; }

} // namespace vision