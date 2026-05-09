# QEMU Mini Cortex-M RTOS Kernel

QEMU : lm3s6965evb

## The steps of this kernel

## 1. Bootload Step

The bootloading step works like this: afer the processor resets, the first thing it will do is look for is the vector table. The vector table includes the address of the initial stack pointer located at the end of the stack (the top of RAM) and the address to Reset_Handler. Reset_Handler will run, which initializes the memory before calling main() by copying initialized FLASH values to RAM and zeroing .bss values. At main() it will run forever, thus finishing the boot process.


---

## Build

```bash
export PATH=/ucrt64/bin:$PATH
make
```

## Run In QEMU

```bash
export PATH=/ucrt64/bin:$PATH
qemu-system-arm -M lm3s6965evb -cpu cortex-m3 -kernel firmware.elf -nographic
```


## Debug

```bash
export PATH=/ucrt64/bin:$PATH
gdb-multiarch firmware.elf
```

