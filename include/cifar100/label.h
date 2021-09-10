#ifndef LABEL_H
#define LABEL_H

#include <cstring>
#include <memory>
#include <vector>

namespace vision {

class CifarLabel {
public:
  explicit CifarLabel(const std::string &filename);

  const std::vector<std::string> &get_label_list() const;

  size_t get_label_count() const;

private:
  std::vector<std::string> label_list_{};
  static constexpr char split_char_{0x0A};
};

} // namespace vision

#endif // LABEL_H