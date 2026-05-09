#include <stdint.h>

void Reset_Handler(void);
int main(void);

extern uint32_t _estack; // end of stack, top of RAM
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

// for test purposes
volatile uint32_t initialized_global = 123;
volatile uint32_t zero_global;

__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {
  (uint32_t)&_estack, // set initial stack poionter to addr called _estack
  (uint32_t)Reset_Handler, // after reset, start executing at Reset_Handler
};

volatile uint32_t reached_main = 0;

int main(void) {
  reached_main = 1;
  while (1) {
  }
}

// Copies .data initial values to RAM
// Zero .bss
// Call main
void Reset_Handler(void) {
  uint32_t *src = &_sidata; // src points to initial data value in FLASH
  uint32_t *dst = &_sdata; // dst points to start of .data in RAM

  while (dst < &_edata) { // while less than end of .data
    *dst = *src;
    dst++;
    src++;
  }

  dst = &_sbss;

  while (dst < &_ebss) { // while less than end of .bss
    *dst = 0;
    dst++;
  }

  main();
  while (1) {
  }
}