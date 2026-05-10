#include <stdint.h>

#define NTASK 10
#define SSIZE 256

enum STATE {
  WAITING,
  RUNNING,
};

struct Task {
  uint32_t tid;
  enum STATE state;
  
  // For context switching, the context of the task (r4-r11) is saved in the task's stack,
  // then that task stack pointer is stored in the task record
  uint32_t* sp;
};

struct Task TASKLIST[NTASK];
uint32_t TASKSTACKS[NTASK][SSIZE];