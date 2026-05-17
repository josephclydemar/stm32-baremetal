CC = arm-none-eabi-gcc
CFLAGS = -std=c11 -Wno-main -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g
LFLAGS = -nostdlib -T linker.ld
INCLUDES = -I include

SOURCE_FILES = $(wildcard src/*.c)
OBJECT_FILES = $(patsubst src/%.c,build/%.o,$(SOURCE_FILES))
TARGET_ELF = build/stm32f411xx-firmware.elf
TARGET_BIN = build/stm32f411xx-firmware.bin
TARGET_IHEX = build/stm32f411xx-firmware.hex
FLASHER = st-flash
FLASH_FLASHERART_ADDR = 0x8000000


all: $(TARGET_BIN) $(TARGET_IHEX)

clean:
	$(RM) $(wildcard build/*)

iprobe:
	st-info --probe

iflash:
	st-info --flash

isram:
	st-info --sram

flash:
	$(FLASHER) --reset write $(TARGET_BIN) $(FLASH_FLASHERART_ADDR)

erase:
	$(FLASHER) erase

debug:
	gdb-multiarch $(TARGET_ELF)

openocd:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

.PHONY: all clean iprobe iflash isram flash erase debug openocd

build/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET_ELF): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LFLAGS) -o $@

$(TARGET_BIN): $(TARGET_ELF)
	arm-none-eabi-objcopy -O binary $< $@

$(TARGET_IHEX): $(TARGET_ELF)
	arm-none-eabi-objcopy -O ihex $< $@

