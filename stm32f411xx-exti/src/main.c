/* STM32F411xx */
#include "stm32f411xx.h"
#include "rcc.h"
#include "gpio.h"
#include "timer.h"

int main(void)
{
  tim_stk_init((stk_t *)STK_START, 16000);
  rcc_periph_enable(RCC_GPIOA);
  rcc_periph_enable(RCC_GPIOB);
  rcc_periph_enable(RCC_SYSCFG);

  gpio_init(PA7, (gpio_cfg_t){
    .mode = GPIO_OUTPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PB6, (gpio_cfg_t){
    .mode = GPIO_OUTPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_NONE,
  });

  gpio_init(PB4, (gpio_cfg_t){
    .mode = GPIO_INPUT_MODE,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_PUDN,
    .altf = GPIO_ALTF0,
  });

  syscfg_t *syscfg = (syscfg_t *)SYSCFG_START;
  syscfg->exticr[1] &= ~(0xf);
  syscfg->exticr[1] |= 1; // set to PBx

  exti_t *exti = (exti_t *)EXTI_START;
  exti->imr |= (1 << 4);
  exti->rtsr &= ~(1 << 4); // rising edge trigger
  exti->ftsr |= (1 << 4); // falling edge trigger

  nvic_t *nvic = (nvic_t *)NVIC_START;
  nvic->ipr[2] &= ~(0xff << (2 * 8));
  nvic->ipr[2] |= (0x20 << (2 * 8));
  
  nvic->iser[0] |= (1 << 10);

  while (1);
}

// IPR
// 0:  [ 0][ 1][ 2][ 3]
// 1:  [ 4][ 5][ 6][ 7]
// 2:  [ 8][ 9][10][11]
// 3:  [12][13][14][15]
// 4:  [16][17][18][19]
// 5:  [20][21][22][23]
