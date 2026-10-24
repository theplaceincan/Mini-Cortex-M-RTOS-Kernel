# Mini ARM Cortex-M RTOS Kernel using QEMU

Rework in progress...

---

## Development of the ARM Cortex-M Mini-RTOS

*Development Log*

---

### Software Installation - 10/26/2026

```bash
pacman -S mingw-w64-ucrt-x86_64-arm-none-eabi-gcc mingw-w64-ucrt-x86_64-qemu
```

1. Installed `arm-none-eabi-gcc`
   1. This is the ARM compiler. It also includes helper tools, such as `objdump` and `readelf`.
   2. This turns my C and assembly code into instructions that an ARM chip can understand. A normal compiler would turn the code to Intel instructions, which ARM can't run.
2. Installed QEMU (`qemu-system-arm`)
   1. This is a program that pretends to be an ARM chip, specifically an TI board called `lm3s6965evb`. The RTOS code will run purely on this program.

We already have `gdb-multiarch`, which is our debugger. This lets us pause the fake QEMU chip and run the program one line at a time, while letting us view the registers and memory as the program progresses.

### Github Setup - 10/21/2026

1. Set aside exiting code as "attempt-1", created a new branch called "rework"

---

## Progression of development

### 1. Knowing what the chip does when powered on

The first thing that the CPU does after/at a reset is read the word stored at `0x00000000`. The processor takes this value and loads it into the main stack pointer (MSP, register R13). After that, the CPU reads the word stored at `0x00000004` and loads it into the program counter (PC, register R15). Both `0x00000000` and `0x00000004` are on flash.

The word at `0x00000004`, which gets loaded into the PC, is the reset vector, which is the address of `Reset_Handler`. Since this is an address that the CPU will jump to for running code, its bit 0 needs to be 1 when it is stored (an old requirement to differentiate between ARM and Thumb instructions for executing code. This specific CPU only uses Thumb instructions, but this requirement is still held for compatibility reasons). After the CPU reads the address of the `Reset_Handler`, it takes that word's bit 0 and copies it into the T-bit switch. The rest of the word is copied into PC. Afterwards, for each instruction ever run on the CPU, the CPU will check this T-bit switch to know whether to run the instruction in Thumb or ARM mode (this specific CPU cannot do ARM, so the T-bit being 0 will create a fault).

**Source:** Page 17, *The Cortex-M3 Processor*

#### Some additional notes

The reason why the stack pointer is the first thing ever done on the CPU is because if there happens to be an error, exception, or whatever, between the start of the CPU and the CPU being able to run the first program, which causes the CPU to save registers onto the stack as part of an interruption, there needs to be a properly-set stack that can handle the interruption, otherwise the CPU may cause another fault on top of the first one by writing to an invalid address.

The T-bit is a single bit in the xPSR register. The xPSR register is a special-purpose register alongside R0-15, and it is the status register for CPU's current state. The T-bit is at bit 24 in that register, where 0 = ARM and 1 = Thumb.

It is common convention to define the location of the SP to be at the top of the RAM in order to use the most space. The SP-4 will be the beginning of the stack since the stack will grow downward from there (each `push` subtracts before writing). There is no automatically defined end to the stack, so it's our responsibility to define it in order to prevent stack overflows, since otherwise it will just write over variables stored in RAM. Also, there are two stack pointers: MSP and PSP. "SP" just refers to whichever one is being used. It is convention that MSP is used for the kernel and interrupts and PSP is used for tasks.

### 2. GDB walkthrough

