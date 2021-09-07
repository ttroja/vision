#ifndef ASSERTION_H
#define ASSERTION_H

#include <cstdio>
#include <cstdlib>

namespace vision {

#if defined(_MSC_VER)
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#else
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

#if defined(ENABLE_ASSERTION)
#define __ASSERT_FMT(fmt, file, line, e, msg)                                  \
  do {                                                                         \
    std::fprintf(stderr, fmt, file, line, e, msg);                             \
    std::abort();                                                              \
  } while (false)

#define ASSERT(e)                                                              \
  if (UNLIKELY(!(e)))                                                          \
  __ASSERT_FMT("%s:%u: failed assertion '%s'%s\n", __FILE__, __LINE__, #e, "")

#else
#define ASSERT(e)
#endif
} // namespace vision

#endif // ASSERTION_H