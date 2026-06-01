/* STM32F411xx */
#include "rcc.h"
#include "gpio.h"
#include "timer.h"
#include "usart.h"

#define ARR         0xFFFFul
#define PSC         2ul


extern volatile uint32_t stk_ticks;
int main(void)
{
  rcc_periph_enable(RCC_GPIOA);
  rcc_periph_enable(RCC_GPIOB);
  rcc_periph_enable(RCC_TIM3);
  rcc_periph_enable(RCC_USART2);

  gpio_init(PA2, (gpio_cfg_t){ /* USART2 TX */
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF7,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PA3, (gpio_cfg_t){ /* USART2 RX */
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF7,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_HIGH,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PA5, (gpio_cfg_t){ /* GPIO output */
    .mode = GPIO_OUTPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PA6, (gpio_cfg_t){ /* PWM output */
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF2,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_HIGH,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PA7, (gpio_cfg_t){ /* PWM output */
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF2,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_HIGH,
    .pupd = GPIO_PUPD_NONE,
  });

  gpio_init(PB1, (gpio_cfg_t){ /* input capture */
    .mode = GPIO_ALTF_MODE,
    .altf = GPIO_ALTF2,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_HIGH,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PB5, (gpio_cfg_t){ /* GPIO output */
    .mode = GPIO_OUTPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_NONE,
  });
  gpio_init(PB6, (gpio_cfg_t){ /* GPIO input */
    .mode = GPIO_INPUT_MODE,
    .altf = GPIO_ALTF0,
    .otype = GPIO_OTYPE_PUSH_PULL,
    .speed = GPIO_OSPEED_LOW,
    .pupd = GPIO_PUPD_PUDN,
  });


  // gpio_init(PA11, (gpio_cfg_t){
  //   .mode = GPIO_ALTF_MODE,
  //   .altf = GPIO_ALTF8,
  //   .speed = GPIO_OSPEED_HIGH,
  //   .otype = GPIO_OTYPE_PUSH_PULL,
  //   .pupd = GPIO_PUPD_NONE,
  // });
  // gpio_init(PA12, (gpio_cfg_t){
  //   .mode = GPIO_ALTF_MODE,
  //   .altf = GPIO_ALTF8,
  //   .speed = GPIO_OSPEED_HIGH,
  //   .otype = GPIO_OTYPE_PUSH_PULL,
  //   .pupd = GPIO_PUPD_NONE,
  // });



  timer_init(TIM3, (tim_base_cfg_t){ .psc = PSC - 1ul, .arr = ARR - 1ul });
  timer_pwm_channel_init(TIM3, (tim_pwm_ch_cfg_t){ .ch = TIMER_CH1, .ccr = 100ul });
  timer_pwm_channel_init(TIM3, (tim_pwm_ch_cfg_t){ .ch = TIMER_CH2, .ccr = 100ul });
  timer_input_capture_channel_init(TIM3, TIMER_CH4);
  timer_start(TIM3);
  usart_init(USART2, (usart_brr_t){ .mantissa = 13, .fraction = 9 });

  int32_t iter = 1;
  uint32_t dc = 0x64, icount = 0, count = 0;
  gpio_level_t pa5_state = GPIO_PIN_HIGH;
  gpio_level_t pb5_state = GPIO_PIN_HIGH;
  gpio_level_t pb6_input_state = GPIO_PIN_HIGH;
  uint32_t now1 = stk_ticks, now2 = stk_ticks;
  uint8_t buff[7] = {'H', 'e', 'l', 'l', 'o', '\r', '\n'};
  while (1) {
    ++count;
    if (dc == 1 || dc == ARR) iter *= -1;
    if (count % 0x2ful == 0) {
      timer_pwm_write(TIM3, TIMER_CH1, dc);
      timer_pwm_write(TIM3, TIMER_CH2, ARR - dc);
      dc += iter;
    }

    pb6_input_state = gpio_read(PB6);
    if (pb6_input_state == GPIO_PIN_HIGH) icount = 100;
    if (icount > 0 && stk_ticks - now1 > 100) {
      now1 = stk_ticks;
      gpio_write(PB5, pb5_state);
      pb5_state = !pb5_state;
      --icount;
      if (icount == 0) {
        gpio_write(PB5, GPIO_PIN_LOW);
        usart_send(USART2, buff, 7);
      }
    }

    if (stk_ticks - now2 > 2000) {
      now2 = stk_ticks;
      gpio_write(PA5, pa5_state);
      pa5_state = !pa5_state;
    }
  }
}

