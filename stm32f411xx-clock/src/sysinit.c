#include "stm32f411xx.h"
#include "systick.h"
#include "rcc.h"
#include "gpio.h"

void sysinit(void)
{
  rcc_pll_config();
  rcc_periph_enable(RCC_GPIOA);
  gpio_init(PA5, (gpio_cfg_t){
    .mode = GPIO_OUTPUT_MODE,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_HIGH,
    .pupd = GPIO_PUPD_NONE,
    .altf = GPIO_ALTF0,
  });
  stk_init((stk_t *)STK_START, 8000000);
}
