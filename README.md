# QEMU Mini Cortex-M RTOS Kernel

QEMU : lm3s6965evb

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