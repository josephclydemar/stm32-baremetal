#include "gpio.h"

void gpio_init(gpio_pin_t p, gpio_cfg_t cfg)
{
  uint32_t pin = p.pin;
  volatile gpio_t *g = p.port;

  /* mode */
  g->moder &= ~(3ul << (pin * 2));
  g->moder |= ((uint32_t)cfg.mode << (pin * 2));

  /* output type */
  g->otyper &= ~(1ul << pin);
  g->otyper |= ((uint32_t)cfg.otype << pin);

  /* speed */
  g->ospeedr &= ~(3ul << (pin * 2));
  g->ospeedr |= ((uint32_t)cfg.speed << (pin * 2));

  /* pull-up/pull-down */
  g->pupdr &= ~(3ul << (pin * 2));
  g->pupdr |= ((uint32_t)cfg.pupd << (pin * 2));

  /* alternate function */
  if (cfg.mode == GPIO_ALTF_MODE) {
    if (pin < 8ul) {
      g->afr[0] &= ~(0xFul << (pin * 4));
      g->afr[0] |= ((uint32_t)cfg.altf << (pin * 4));
    } else {
      g->afr[1] &= ~(0xFul << ((pin - 8) * 4));
      g->afr[1] |= ((uint32_t)cfg.altf << ((pin - 8) * 4));
    }
  }
}

void gpio_write(gpio_pin_t p, gpio_level_t level)
{
  uint32_t pin = p.pin;
  volatile gpio_t *g = p.port;
  if (level == GPIO_PIN_HIGH) g->bsrr = (1u << p.pin);
  else g->bsrr = (1ul << (pin + 16));
}

gpio_level_t gpio_read(gpio_pin_t p)
{
  uint32_t pin = p.pin, read_level;
  volatile gpio_t *g = p.port;
  read_level = (g->idr & (1ul << pin)) >> pin;
  if (read_level == 1ul) return GPIO_PIN_HIGH;
  else return GPIO_PIN_LOW;
}

