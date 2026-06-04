/* STM32F411xx */
#include "stm32f411xx.h"
#include "rcc.h"
#include "gpio.h"
#include "usart.h"
#include "util.h"

// extern volatile uint32_t s_ticks;

int main(void)
{
  rcc_pll_config();
  // stk_init((stk_t *)STK_START, 100000);
  rcc_periph_enable(RCC_GPIOA);
  rcc_periph_enable(RCC_GPIOB);
  rcc_periph_enable(RCC_USART6);

  gpio_init(PA11, (gpio_cfg_t){
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF8,
    .speed = GPIO_OSPEED_HIGH,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PA12, (gpio_cfg_t){
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF8,
    .speed = GPIO_OSPEED_HIGH,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PB6, (gpio_cfg_t){
    .mode = GPIO_INPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_PUDN,
  });

  uint32_t now;
  uint32_t num = 0;
  uint8_t num_buf[12], next_line_buf[2] = {'\r', '\n'};
  num_buf[0] = '-';
  num_buf[1] = '>';
  num_buf[2] = '0';
  num_buf[3] = 'x';
  
  gpio_level_t pa6_input_state = GPIO_PIN_LOW;
  // usart_init(USART2, (usart_brr_t){ .mantissa = 13, .fraction = 9 });  // baud rate 115200 for APB1 25MHz clock
  usart_init(USART6, (usart_brr_t){ .mantissa = 6, .fraction = 13 });  // baud rate 115200 for APB2 12.5MHz clock
  while (1) {
    // now = s_ticks;

    pa6_input_state = gpio_read(PB6);
    if (pa6_input_state == GPIO_PIN_HIGH) {
      u32word2hex_rev_encode(num, num_buf + 4);
      usart_send(USART6, num_buf, 12);
      usart_send(USART6, next_line_buf, 2);
      ++num;
      for (now = 0; now < 0x4fffff; ++now);
    }
    // // while (s_ticks - now < 200);
  }
}

