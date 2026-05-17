ENTRY(reset_handler)
MEMORY {
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512k
  SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128k
}
_estack = ORIGIN(SRAM) + LENGTH(SRAM);
SECTIONS {
  .isr_vector : ALIGN(4) {
     KEEP(*(.isr_vector))
  } >FLASH

  .text : ALIGN(4) {
    *(.text*)
  } >FLASH

  .rodata : ALIGN(4) {
    *(.rodata*)
  } >FLASH

  .data : ALIGN(4) {
    _sdata = .;
    *(.data SORT(.data.*))
    _edata = .;
  } >SRAM AT >FLASH
  _sidata = LOADADDR(.data);

  .bss : {
    _sbss = .;
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;
  } >SRAM
}


