CC = arm-none-eabi-gcc
CFLAGS = -std=c99 -Wno-main -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -mcpu=cortex-m4 -mthumb -g
LFLAGS = -nostdlib -T linker.ld
INCLUDES = -I include

SOURCE_FILES = $(wildcard src/*.c)
OBJECT_FILES = $(patsubst src/%.c,build/%.o,$(SOURCE_FILES))
TARGET_ELF = build/stm32f411xx-firmware.elf
TARGET_BIN = build/stm32f411xx-firmware.bin
TARGET_IHEX = build/stm32f411xx-firmware.hex
ST = st-flash
FLASH_START_ADDR = 0x8000000


all: $(TARGET_BIN) $(TARGET_IHEX)

clean:
	$(RM) $(wildcard build/*)

probe:
	st-info --probe

flash:
	@echo -n $$(($$(cat ../.flashcount) - 1)) > ../.flashcount
	$(ST) --reset write $(TARGET_BIN) $(FLASH_START_ADDR)

erase:
	$(ST) erase

debug:
	gdb-multiarch $(TARGET_ELF)

openocd:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

.PHONY: all clean probe flash erase debug openocd

build/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET_ELF): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LFLAGS) -o $@

$(TARGET_BIN): $(TARGET_ELF)
	arm-none-eabi-objcopy -O binary $< $@

$(TARGET_IHEX): $(TARGET_ELF)
	arm-none-eabi-objcopy -O ihex $< $@

