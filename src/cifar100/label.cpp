#include "cifar100/label.h"
#include "common/file.h"

namespace vision {

CifarLabel::CifarLabel(const std::string &filename) {
  File file(filename);
  const size_t file_size = file.size();
  const size_t buffer_size = 256;
  std::unique_ptr<uint8_t[]> buffer(new uint8_t[file_size]{});
  file.read(buffer.get(), file_size);
  file.close();
  size_t idx_begin = 0, idx_end = 0;
  while (idx_end++ < file_size) {
    char ch = *(buffer.get() + idx_end);
    if (ch == split_char_) {
      char label[buffer_size]{};
      std::memcpy(label, buffer.get() + idx_begin, idx_end - idx_begin);
      label_list_.emplace_back(label);
      idx_begin = idx_end + 1;
    }
  }
}

const std::vector<std::string> &CifarLabel::get_label_list() const {
  return label_list_;
}

size_t CifarLabel::get_label_count() const { return label_list_.size(); }

} // namespace vision