CC = arm-none-eabi-gcc

CFLAGS = -mcpu=cortex-m3 -mthumb -ffreestanding -nostdlib -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

TARGET = firmware.elf
SRCS = boot.c

all: $(TARGET)

$(TARGET): $(SRCS) linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
