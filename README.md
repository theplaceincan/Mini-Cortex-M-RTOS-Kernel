# QEMU Mini Cortex-M RTOS Kernel

QEMU : lm3s6965evb

## The steps of this kernel

## 1. Boot Step

The booting step works like this: after the processor resets, the first thing it will do is read the vector table. The vector table includes the address of the initial stack pointer located at the end of the stack (the top of RAM) and the address of the Reset_Handler. Reset_Handler will run, which initializes the memory before calling main() by copying initialized FLASH values to RAM and zeroing .bss values. At main() it will run forever, thus finishing the boot process.

You can prove that this steps works by using a debugger to read the `initialized_global` and `zero_global` values, then running `reached_main` after reaching `main()`. It should look like this:

```
main () at boot.c:27
27        while (1) {
(gdb) break main
Breakpoint 1 at 0xc: file boot.c, line 26.
(gdb) print reached_main
$1 = 1
(gdb) print zero_global
$2 = 0
(gdb) print initialized_global
$3 = 123
(gdb) 
```


## 2. Interrupts

This operating system uses SysTick, which gives us a simple first interrupt source/tool because the hardware of the ARM Cortex-M does most of the work. After the booting step, the next step is setting the values in specified memory addresses to initialize the systick, which is a counter that helps the OS know if time passed.

For this QEMU board, the system clock is approximately 12.5 MHz. For SysTick, there are three values we need to set: 1) the `Control and Status Register`, 2) the `Reload Value Register`, and 3) the `Current Value Register`, where:

Control and Status Register (SYST_RVR) == # of clock cycles between ticks
Reload Value Register (SYST_CVR) == clears/restarts the current countdown
Current Value Register (SYST_CSR) == enables SysTick, enables interrupts, and chooses clock source

For 12.5 MHz, to calculate how long SysTick should wait before firing an interrupt, 
12,500,000 Hz (# of ticks sent) / 1000 Hz (# of interrupts per sec) = 12,500 cycles per millisecond
reload = 12,500 - 1 = 12,499

So SysTick should count 12,500 ticks before sending an interrupt.

---

## Build

```bash
export PATH=/ucrt64/bin:$PATH
make
```

## Run In QEMU

```bash
export PATH=/ucrt64/bin:$PATH
# qemu-system-arm -M lm3s6965evb -cpu cortex-m3 -kernel firmware.elf -nographic
qemu-system-arm -M lm3s6965evb -cpu cortex-m3 -kernel firmware.elf -nographic -S -s
```


## Debug

```bash
export PATH=/ucrt64/bin:$PATH
gdb-multiarch firmware.elf
```

