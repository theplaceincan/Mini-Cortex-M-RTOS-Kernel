#include <stdint.h>

// For debug purposes, to see if we've reached main (1 = yes)
volatile uint32_t reached_main = 0;

int main(void) {

  reached_main = 1;

  while (1) {

  }

}