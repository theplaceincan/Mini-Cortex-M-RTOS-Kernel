#include <stdint.h>

extern uint32_t _estack; // end of stack, top of RAM
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

// interrupt initialization addresses
volatile uint32_t* SYST_RVR_PTR = (uint32_t *)(0xE000E014);
volatile uint32_t* SYST_CVR_PTR = (uint32_t *)(0xE000E018);
volatile uint32_t* SYST_CSR_PTR = (uint32_t *)(0xE000E010);

// for test purposes
volatile uint32_t initialized_global = 123;
volatile uint32_t zero_global;

void Reset_Handler(void);
int main(void);
void SysTick_Handler(void);
void Default_Handler(void);
// void MNI_Handler(void);
// void HardFault_Handler(void);
// void BusFault_Handler(void);
// void UsageFault_Handler(void);
// void MemManage_Handler(void);

__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {
  (uint32_t)&_estack, // set initial stack poionter to addr called _estack
  (uint32_t)Reset_Handler, // after reset, start executing at Reset_Handler
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)0,
  (uint32_t)0,
  (uint32_t)0,
  (uint32_t)0,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)0,
  (uint32_t)Default_Handler,
  (uint32_t)SysTick_Handler,
};

// Debug variables
volatile uint32_t reached_main = 0;
volatile uint32_t tick_count = 0;

int main(void) {
  reached_main = 1;

  // Tell SysTick to load 12499 (QEMU 12.5 MHz)
  *SYST_RVR_PTR = 12499;

  // clear  SysTick current count
  *SYST_CVR_PTR = 0;

  // enable SysTick with value 7
  *SYST_CSR_PTR = 7;

  while (1) {
  }
}

void Default_Handler(void) {
  while(1) {

  }
}

// Runs everytime SysTick fires
void SysTick_Handler(void) {
  tick_count++;
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