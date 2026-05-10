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
  uint32_t func_addr;
  
  // For context switching, the context of the task (r4-r11) 
  // is saved in the task's stack, then that task's stack pointer 
  // is stored in the task record
  uint32_t* sp;
};

struct Task TASKLIST[NTASK];
uint32_t TASKSTACKS[NTASK][SSIZE];

// When a task finishes running
void task_exit(void) {
  while(1) {
  }
}

// Creates NEW task, adds to empty slot in TASKLIST and TASKSTACKS
int create_task(struct Task t) {

  // Search for the next UNUSED task, replace with READY task
  for (int i = 0; i < NTASK; i++) {
    if (TASKLIST[i].state == UNUSED) {
      t.state = READY;
      TASKLIST[i] = t;
      
      // xPSR
      TASKSTACKS[i][SSIZE-1] = 0x01000000; // Thumb mode

      // PC
      TASKSTACKS[i][SSIZE-2] = t.func_addr; // address of task function

      // LR
      TASKSTACKS[i][SSIZE-3] = (uint32_t)task_exit;

      // R12
      TASKSTACKS[i][SSIZE-4] = 0;

      // R3
      TASKSTACKS[i][SSIZE-5] = 0;

      // R2
      TASKSTACKS[i][SSIZE-6] = 0;

      // R1
      TASKSTACKS[i][SSIZE-7] = 0;

      // R0
      TASKSTACKS[i][SSIZE-8] = 0; // 0 or task argument
      
      // R11-R4
      TASKSTACKS[i][SSIZE-9] = 0; // 11
      TASKSTACKS[i][SSIZE-10] = 0; // 10
      TASKSTACKS[i][SSIZE-11] = 0; // 9
      TASKSTACKS[i][SSIZE-12] = 0; // 8
      TASKSTACKS[i][SSIZE-13] = 0; // 7
      TASKSTACKS[i][SSIZE-14] = 0; // 6 
      TASKSTACKS[i][SSIZE-15] = 0; // 5
      TASKSTACKS[i][SSIZE-16] = 0; // 4

      // SP points to R4 after interrupt
      TASKLIST[i].sp = &TASKSTACKS[i][SSIZE-16];

      return 0;
    }
  }

  // If unable to create new task
  return -1;
}