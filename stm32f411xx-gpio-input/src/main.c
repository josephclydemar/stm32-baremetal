/* STM32F411xx */
#include "rcc.h"
#include "gpio.h"

void main(void)
{
  rcc_gpio_enable((rcc_t *)RCC_START, RCC_GPIOA_MASK); /* RCC_AHB1ENR |= 0x1 : Turn on the clock for GPIOA */

  /* Set PA0 to output mode */
  gpio_set_mode((gpio_t *)GPIOA, GPIO_OUTPUT_MODE, GPIO_PIN_5, GPIO_AF_0);
  gpio_set_mode((gpio_t *)GPIOA, GPIO_INPUT_MODE, GPIO_PIN_6, GPIO_AF_0);

  volatile uint32_t inpt = 0;
  while (1) {
    inpt = gpio_read_pin((gpio_t *)GPIOA, GPIO_PIN_6);
    if (inpt == GPIO_PIN_HIGH) {
      // gpio_write_pin((gpio_t *)GPIOA, GPIO_PIN_5, GPIO_PIN_HIGH);
      /* PA5 slow blink */
      for (int idx = 0; idx < 4; ++idx) {
        gpio_write_pin((gpio_t *)GPIOA, GPIO_PIN_5, GPIO_PIN_HIGH);
        for (volatile uint32_t i = 0; i < 200000; i++);
        gpio_write_pin((gpio_t *)GPIOA, GPIO_PIN_5, GPIO_PIN_LOW);
        for (volatile uint32_t i = 0; i < 200000; i++);
      }

      /* PA5 fast blink */
      for (uint32_t idx = 0; idx < 16; ++idx) {
        gpio_write_pin((gpio_t *)GPIOA, GPIO_PIN_5, GPIO_PIN_HIGH);
        for (volatile uint32_t i = 0; i < 50000; i++);
        gpio_write_pin((gpio_t *)GPIOA, GPIO_PIN_5, GPIO_PIN_LOW);
        for (volatile uint32_t i = 0; i < 50000; i++);
      }
    } else {
      gpio_write_pin((gpio_t *)GPIOA, GPIO_PIN_5, GPIO_PIN_LOW);
    }
  }
}


