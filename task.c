#include <stdint.h>

#define NTASK 10
#define SSIZE 256

enum STATE {
  UNUSED,
  WAITING,
  RUNNING,
  READY,
};

struct Task {
  uint32_t tid;
  enum STATE state;
  
  // For context switching, the context of the task (r4-r11) 
  // is saved in the task's stack, then that task's stack pointer 
  // is stored in the task record
  uint32_t* sp;
};

struct Task TASKLIST[NTASK];
uint32_t TASKSTACKS[NTASK][SSIZE];

// Creates new task, adds to empty slot in TASKLIST and TASKSTACKS
int create_task(struct Task t) {

  // Search for the next UNUSED task, replace with READY task
  for (int i = 0; i < NTASK; i++) {
    if (TASKLIST[i].state == UNUSED) {
      t.state = READY;
      TASKLIST[i] = t;
      TASKLIST[i].sp = &TASKSTACKS[i][SSIZE];
      return 0;
    }
  }

  // If unable to create new task
  return -1;
}