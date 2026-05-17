/* STM32F411xx */
#include "stm32f411xx.h"
#include "rcc.h"
#include "gpio.h"
#include "timer.h"

#define ARR         1024ul
#define PSC         1ul

int main(void)
{
  rcc_periph_enable(RCC_GPIOA);
  rcc_periph_enable(RCC_GPIOB);
  rcc_periph_enable(RCC_TIM3);
  rcc_periph_enable(RCC_TIM4);

  /* Output */
  gpio_init(PA5, (gpio_cfg_t){
      .mode = GPIO_OUTPUT_MODE,
      .altf = GPIO_ALTF0,
      .otype = GPIO_OTYPE_PUSH_PULL,
      .speed = GPIO_OSPEED_LOW,
      .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PB5, (gpio_cfg_t){
      .mode = GPIO_OUTPUT_MODE,
      .altf = GPIO_ALTF0,
      .otype = GPIO_OTYPE_PUSH_PULL,
      .speed = GPIO_OSPEED_LOW,
      .pupd = GPIO_PUPD_NONE,
  });
  /* Input */
  gpio_init(PA6, (gpio_cfg_t){
      .mode = GPIO_INPUT_MODE,
      .altf = GPIO_ALTF0,
      .otype = GPIO_OTYPE_PUSH_PULL,
      .speed = GPIO_OSPEED_LOW,
      .pupd = GPIO_PUPD_PUDN,
  });

  /* PWM */
  gpio_init(PA7, (gpio_cfg_t){
      .mode = GPIO_ALTF_MODE,
      .altf = GPIO_ALTF2,
      .otype = GPIO_OTYPE_PUSH_PULL,
      .speed = GPIO_OSPEED_HIGH,
      .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PB6, (gpio_cfg_t){
      .mode = GPIO_ALTF_MODE,
      .altf = GPIO_ALTF2,
      .otype = GPIO_OTYPE_PUSH_PULL,
      .speed = GPIO_OSPEED_HIGH,
      .pupd = GPIO_PUPD_NONE,
  });

  tim_pwm_init(TIM3, (tim_pwm_cfg_t){
    .psc = PSC - 1ul,
    .arr = ARR - 1ul,
    .ccr = 100ul,
    .ch = TIMER_CH2,
  });
  tim_pwm_init(TIM4, (tim_pwm_cfg_t){
    .psc = PSC - 1ul,
    .arr = ARR - 1ul,
    .ccr = 100ul,
    .ch = TIMER_CH1,
  });

  int32_t iter = 1;
  uint32_t dc = 0x64, count = 0;
  uint32_t icount = 0;
  gpio_level_t pa5_state = GPIO_PIN_HIGH, pb5_state = GPIO_PIN_HIGH, pa6_input_state = GPIO_PIN_HIGH;
  while (1) {
    ++count;
    if (dc == 0x1 || dc == ARR) {
      iter *= -1;
    }
    if (count % 0x2ful == 0) {
      tim_pwm_write(TIM3, TIMER_CH2, dc);
      tim_pwm_write(TIM4, TIMER_CH1, ARR - dc);
      dc += iter;
    }

    pa6_input_state = gpio_read(PA6);
    if (pa6_input_state == GPIO_PIN_HIGH) {
      icount = 0x4f;
    }

    if (icount > 0 && count % 0xffful == 0) {
      gpio_write(PA5, pa5_state);
      switch (pa5_state) {
        case GPIO_PIN_HIGH:
          pa5_state = GPIO_PIN_LOW;
          break;
        case GPIO_PIN_LOW:
          pa5_state = GPIO_PIN_HIGH;
          break;
      }
      --icount;
      if (icount == 0) gpio_write(PA5, GPIO_PIN_LOW);
    }

    if (count % 0x2ffful == 0) {
      gpio_write(PB5, pb5_state);
      switch (pb5_state) {
        case GPIO_PIN_HIGH:
          pb5_state = GPIO_PIN_LOW;
          break;
        case GPIO_PIN_LOW:
          pb5_state = GPIO_PIN_HIGH;
          break;
      }
    }
  }
}

