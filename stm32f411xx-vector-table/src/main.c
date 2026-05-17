#include "common.h"

int main(void);

extern unsigned long _estack; /* defined in linker.ld */
__attribute__((noreturn))
void reset_handler(void) /* startup */
{
  extern long _sbss, _ebss, _sdata, _edata, _sidata;
  for (long *dst = &_sbss; dst < &_ebss; dst++) {
    *dst = 0;
  }
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) {
    *dst++ = *src++;
  }

  (void)main();

  while(1);
}

/* vector table */
__attribute__((section(".isr_vector"))) void (*const vector_table[])(void) = {
  (void *)&_estack,
  reset_handler,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


int main(void)
{
  uint32_t count = 0, half_count;
  while (1) {
    uint32_t t = 50;

    count += 2;
    half_count = count / 2;
    ++half_count;

    while(t--);
  }
}
