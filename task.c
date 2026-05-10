#include <stdint.h>

struct Task {
  uint32_t tid;
  uint32_t* sp;
};