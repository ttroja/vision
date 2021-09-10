#include "common/file.h"
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

} // namespace vision