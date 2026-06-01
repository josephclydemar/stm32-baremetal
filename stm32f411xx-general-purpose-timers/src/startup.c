/* STM32F411xx */
#include "startup.h"
#include "timer.h"
#include "usart.h"
#include "util.h"

void nmi_handler(void)            __attribute__((weak, alias("default_handler")));
void hardfault_handler(void)      __attribute__((weak, alias("default_handler")));
void memmanage_handler(void)      __attribute__((weak, alias("default_handler")));
void busfault_handler(void)       __attribute__((weak, alias("default_handler")));
void usagefault_handler(void)     __attribute__((weak, alias("default_handler")));
void svc_handler(void)            __attribute__((weak, alias("default_handler")));
void debugmon_handler(void)       __attribute__((weak, alias("default_handler")));
void pendsv_handler(void)         __attribute__((weak, alias("default_handler")));
void tim4_handler(void)           __attribute__((weak, alias("default_handler")));
void usart2_handler(void)         __attribute__((weak, alias("default_handler")));


void default_handler(void)
{
  while (1);
}

__attribute__((naked, noreturn))
void reset_handler(void)
{
  /* copy initialized data from FLASH to SRAM */
  __asm volatile (
    "mov r0, %0\n"
    "mov r1, %1\n"
    "mov r2, %2\n"
    "_data_sec_l1:\n"
    "cmp r1, r2\n"
    "bcs _data_sec_l2\n"
    "ldr r3, [r0]\n"
    "str r3, [r1]\n"
    "add r0, #4\n"
    "add r1, #4\n"
    "b _data_sec_l1\n"
    "_data_sec_l2:\n"
    :
    : "r"(_sidata), "r"(_sdata), "r"(_edata)
    : "r0", "r1", "r2", "r3", "memory"
  );

  /* zero the .bss section */
  __asm volatile (
    "mov r0, %0\n"
    "mov r1, %1\n"
    "mov r2, #0\n"
    "_bss_sec_l1:\n"
    "cmp r0, r1\n"
    "bcs _bss_sec_l2\n"
    "str r2, [r0]\n"
    "add r0, #4\n"
    "b _bss_sec_l1\n"
    "_bss_sec_l2:\n"
    :
    : "r"(_sbss), "r"(_ebss)
    : "r0", "r1", "r2", "memory"
  );

  __asm volatile (
    "bl sysinit\n"
    "b main\n"
    "reset_loop:\n"
    "b reset_loop\n"
  );
}

void stk_handler(void)
{
  ++stk_ticks;
}

void tim3_handler(void)
{
  gptim_t *t = (gptim_t *)TIM3_ADDR;
  if (t->sr & (1ul << 4)) {
    uint32_t hehe = t->ccr[3];
    uint8_t num_buf[12];
    num_buf[0] = '-';
    num_buf[1] = '>';
    num_buf[10] = '\r';
    num_buf[11] = '\n';

    u32word2hex_rev_encode(hehe, num_buf + 2);
    usart_send(USART2, num_buf, 12);
    t->sr &= ~(1ul << 4);
    // t->sr &= ~(1ul << 12);
  }
}

