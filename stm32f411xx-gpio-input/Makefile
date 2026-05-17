CC = arm-none-eabi-gcc
CFLAGS = -std=c11 -ffreestanding \
				 -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
				 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
LFLAGS = -nostdlib -T linker.ld
INCLUDES = -I include

SOURCE_FILES = $(wildcard src/*.c)
OBJECT_FILES = $(patsubst src/%.c,build/%.o,$(SOURCE_FILES))
TARGET_ELF = build/stm32f411xx-firmware.elf
TARGET_BIN = build/stm32f411xx-firmware.bin
TARGET_IHEX = build/stm32f411xx-firmware.hex
FLASHER = st-flash
FLASH_FLASHERART_ADDR = 0x8000000


all: debug

debug: CFLAGS += -O0 -g
debug: $(TARGET_BIN) $(TARGET_IHEX)

release: CFLAGS += -O3
release: LFLAGS += -s
release: $(TARGET_BIN) $(TARGET_IHEX)

clean:
	$(RM) $(wildcard build/*)

probe:
	st-info --probe

flash:
	$(FLASHER) --reset write $(TARGET_BIN) $(FLASH_FLASHERART_ADDR)

erase:
	$(FLASHER) erase

gdb:
	gdb-multiarch $(TARGET_ELF)

openocd:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

.PHONY: all debug release clean probe flash erase gdb openocd


build/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET_ELF): $(OBJECT_FILES)
	$(CC) $^ $(LFLAGS) -o $@

$(TARGET_BIN): $(TARGET_ELF)
	arm-none-eabi-objcopy -O binary $< $@

$(TARGET_IHEX): $(TARGET_ELF)
	arm-none-eabi-objcopy -O ihex $< $@

