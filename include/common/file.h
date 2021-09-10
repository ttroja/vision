#ifndef FILE_H
#define FILE_H

#include <cstdio>
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

} // namespace vision

#endif // FILE_H