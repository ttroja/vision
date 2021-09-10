#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>

namespace vision {

enum class BinType { TEST, TRAIN };
enum class LabelType { COARSE, FINE };

struct Shape {
  size_t channel;
  size_t width;
  size_t height;
};

struct CifarConfig {
  size_t thread_num;
  size_t stride;
  BinType bin_type;
  LabelType label_type;
};

} // namespace vision

#endif // STRUCT_H