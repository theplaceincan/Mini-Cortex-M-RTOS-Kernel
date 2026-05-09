# QEMU Mini Cortex-M RTOS Kernel

QEMU : lm3s6965evb

## The steps of this kernel

## 1. Bootload Step

The bootloading step works like this: afer the processor resets, the first thing it will do is look for is the vector table. The vector table includes the address of the initial stack pointer located at the end of the stack (the top of RAM) and the address to Reset_Handler. Reset_Handler will run, which initializes the memory before calling main() by copying initialized FLASH values to RAM and zeroing .bss values. At main() it will run forever, thus finishing the boot process.

You can prove that this steps works by using a debugger to read the `initialized_global` and `zero_global` values, then running `reached_main` before and after reaching `main()`. It should look like this:

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

