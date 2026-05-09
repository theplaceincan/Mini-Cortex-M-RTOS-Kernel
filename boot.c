#include <stdint.h>


void Reset_Handler(void);
int main(void);

extern uint32_t _estack; // end of stack, top of RAM

__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {
  (uint32_t)&_estack, // set initial stack poionter to addr called e_stack
  (uint32_t)Reset_Handler, // after reset, start executing at Reset_Handler
};

volatile uint32_t reached_main = 0;

int main(void) {
  reached_main = 1;
  while (1) {
  }
}

void Reset_Handler(void) {
  main();
  while (1) {
  }
}