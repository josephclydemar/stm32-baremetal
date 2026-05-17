#include "gpio.h"

void gpio_set_mode(gpio_t *gpio, uint32_t mode, uint8_t pin, uint32_t alt_value)
{
  mode &= 0x3ul;
  pin &= 0xful;
  alt_value &= 0xful;
  switch (mode) {
    case GPIO_OUTPUT_MODE:
      gpio->moder &= ~(0x3ul << (pin * 0x2));
      gpio->moder |= (mode << (pin * 0x2));
      /* set to output push-pull */
      gpio->otyper &= ~(0x1ul << pin);
      /* set to low speed */
      gpio->ospeedr &= ~(0x3ul << (pin * 0x2));
      // gpio->ospeedr |= (output_speed << (pin * 0x2));
      /* set to no pull-up, no pull-down */
      gpio->pupdr &= ~(0x3ul << (pin * 0x2));
      break;

    case GPIO_INPUT_MODE:
      gpio->moder &= ~(0x3ul << (pin * 0x2));
      /* set to pull-down */
      gpio->pupdr &= ~(0x3ul << (pin * 0x2));
      gpio->pupdr |= (0x2ul << (pin * 0x2));
      break;

    case GPIO_ALT_MODE:
      gpio->moder &= ~(0x3ul << (pin * 0x2));
      gpio->moder |= (mode << (pin * 0x2));
      gpio->ospeedr |= (0x3ul << (pin * 0x2));
      if (pin < 8) {
        /* alt low */
        gpio->afrl &= ~(0xful << (pin * 0x4));
        gpio->afrl |= (alt_value << (pin * 0x4));
      } else {
        /* alt high */
        gpio->afrh &= ~(0xful << ((pin - 8) * 0x4));
        gpio->afrh |= (alt_value << ((pin - 8) * 0x4));
      }
      break;

    case GPIO_ANALOG_MODE:
      break;
  }
}

void gpio_write_pin(gpio_t *gpio, uint8_t pin, uint8_t value)
{
  pin &= 0xful;
  value &= 0x1ul;
  switch (value) {
    case GPIO_PIN_LOW:
      gpio->bsrr = (0x1ul << (pin + 0x10));
      break;
    case GPIO_PIN_HIGH:
      gpio->bsrr = (0x1ul << pin);
      break;
  }
}

uint32_t gpio_read_pin(gpio_t *gpio, uint8_t pin)
{
  pin &= 0xful;
  return ((uint32_t)((gpio->idr & (0x1ul << pin)) >> pin));
}

