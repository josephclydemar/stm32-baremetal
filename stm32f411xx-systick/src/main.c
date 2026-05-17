/* STM32F411xx */
#include "gpio.h"
#include "stm32f411xx.h"
#include "rcc.h"
#include "timer.h"

#define ARR         1024ul
#define PSC         1ul

extern volatile uint32_t s_ticks;
void delay_ms(uint32_t ms);


int main(void)
{
  tim_stk_init((stk_t *)STK_START, 16000);
  rcc_periph_enable(RCC_GPIOA);
  gpio_init(PA5, (gpio_cfg_t){
    .mode = GPIO_OUTPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_NONE,
  });
  while (1) {
    gpio_write(PA5, GPIO_PIN_HIGH);
    delay_ms(500);
    gpio_write(PA5, GPIO_PIN_LOW);
    delay_ms(500);
  }
}

void delay_ms(uint32_t ms)
{
  uint32_t start = s_ticks;
  while ((s_ticks - start) < ms);
}

