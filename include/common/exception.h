#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "assertion.h"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace vision {

enum ErrorCode {
  OK = 0,
  FAILURE = -1,
  INVALID_FILE = -2,
  INVALID_ARGUMENT = -3,
};

class Exception {
public:
  Exception(int status) : error_(status){};
  int get_status() { return error_; };

private:
  int error_ = ErrorCode::FAILURE;
};

inline void log(const char *fmt, ...) {
  va_list lst;
  va_start(lst, fmt);
  vfprintf(stderr, fmt, lst);
  va_end(lst);
}

#define LOG(...) log(__VA_ARGS__)

#if defined(ENABLE_EXCEPTION)
#define THROW(e) throw(e)
#else
#define THROW(e) std::abort()
#endif

#define CHECK_THROW(_cond, _fail, ...)                                         \
  do {                                                                         \
    if (UNLIKELY(!(_cond))) {                                                  \
      LOG(__VA_ARGS__);                                                        \
      THROW(Exception{_fail});                                                 \
    }                                                                          \
  } while (0)

} // namespace vision

#endif // EXCEPTION_H
