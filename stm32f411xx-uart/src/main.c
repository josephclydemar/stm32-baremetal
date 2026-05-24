/* STM32F411xx */
#include "stm32f411xx.h"
#include "systick.h"
#include "rcc.h"
#include "gpio.h"
#include "usart.h"
#include "util.h"

extern volatile uint32_t s_ticks;

int main(void)
{
  rcc_pll_config();
  stk_init((stk_t *)STK_START, 100000);
  rcc_periph_enable(RCC_GPIOA);
  rcc_periph_enable(RCC_USART2);

  gpio_init(PA2, (gpio_cfg_t){
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF7,
    .speed = GPIO_OSPEED_HIGH,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PA3, (gpio_cfg_t){
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF7,
    .speed = GPIO_OSPEED_HIGH,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .pupd = GPIO_PUPD_NONE,
  });

  uint32_t now, num = 0;
  char num_buf[10], next_line_buf[2] = {'\r', '\n'};
  // baud rate 115200
  usart_init(USART2, (usart_brr_t){ .mantissa = 13, .fraction = 9 });
  while (1) {
    now = s_ticks;
    num_buf[0] = '0';
    num_buf[1] = 'x';
    u32word2hex_rev_encode(num, num_buf + 2);
    usart_send(USART2, num_buf, 10);
    usart_send(USART2, next_line_buf, 2);
    ++num;
    while (s_ticks - now < 500);
  }
}

