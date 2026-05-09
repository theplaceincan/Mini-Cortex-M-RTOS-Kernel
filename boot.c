#include <stdint.h>

volatile uint32_t reached_main = 0;

int main(void) {

  reached_main = 1;

  while (1) {

  }

}