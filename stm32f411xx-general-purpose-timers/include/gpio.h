#ifndef GPIO_H_
#define GPIO_H_
#include "stm32f411xx.h"

#define PA5 (volatile gpio_pin_t){ .port = ((volatile gpio_t *)GPIOA_START), .pin = 5 }
#define PA6 (volatile gpio_pin_t){ .port = ((volatile gpio_t *)GPIOA_START), .pin = 6 }
#define PA7 (volatile gpio_pin_t){ .port = ((volatile gpio_t *)GPIOA_START), .pin = 7 }
#define PB3 (volatile gpio_pin_t){ .port = ((volatile gpio_t *)GPIOB_START), .pin = 3 }
#define PB5 (volatile gpio_pin_t){ .port = ((volatile gpio_t *)GPIOB_START), .pin = 5 }
#define PB6 (volatile gpio_pin_t){ .port = ((volatile gpio_t *)GPIOB_START), .pin = 6 }

#define GPIO_OUTPUT_LOW_SPEED        0x0
#define GPIO_OUTPUT_MEDIUM_SPEED     0x1
#define GPIO_OUTPUT_HIGH_SPEED       0x2
#define GPIO_OUTPUT_VERY_HIGH_SPEED  0x3

typedef enum {
  GPIO_INPUT_MODE  = 0x0,
  GPIO_OUTPUT_MODE = 0x1,
  GPIO_ALTF_MODE   = 0x2,
  GPIO_ANALOG_MODE = 0x3,
} gpio_mode_t;

typedef enum {
  GPIO_ALTF0  = 0x0,
  GPIO_ALTF1  = 0x1,
  GPIO_ALTF2  = 0x2,
  GPIO_ALTF3  = 0x3,
  GPIO_ALTF4  = 0x4,
  GPIO_ALTF5  = 0x5,
  GPIO_ALTF6  = 0x6,
  GPIO_ALTF7  = 0x7,
  GPIO_ALTF8  = 0x8,
  GPIO_ALTF9  = 0x9,
  GPIO_ALTF10 = 0xa,
  GPIO_ALTF11 = 0xb,
  GPIO_ALTF12 = 0xc,
  GPIO_ALTF13 = 0xd,
  GPIO_ALTF14 = 0xe,
  GPIO_ALTF15 = 0xf,
} gpio_altf_t;

typedef enum {
  GPIO_PIN_LOW  = 0x0,
  GPIO_PIN_HIGH = 0x1,
} gpio_level_t;

typedef enum {
  GPIO_OTYPE_PUSH_PULL  = 0x0,
  GPIO_OTYPE_OPEN_DRAIN = 0x1,
} gpio_otype_t;

typedef enum {
  GPIO_OSPEED_LOW    = 0x0,
  GPIO_OSPEED_MEDIUM = 0x1,
  GPIO_OSPEED_FAST   = 0x2,
  GPIO_OSPEED_HIGH   = 0x3,
} gpio_ospeed_t;

typedef enum {
  GPIO_PUPD_NONE = 0x0,
  GPIO_PUPD_PUUP = 0x1,
  GPIO_PUPD_PUDN = 0x2,
  GPIO_PUPD_RSRV = 0x3,
} gpio_pupd_t;

typedef struct {
  volatile gpio_t *port;
  volatile uint8_t pin;
} gpio_pin_t;

typedef struct {
  volatile gpio_mode_t mode;
  volatile gpio_altf_t altf;
  volatile gpio_otype_t otype;
  volatile gpio_ospeed_t speed;
  volatile gpio_pupd_t pupd;
} gpio_cfg_t;

void gpio_init(gpio_pin_t p, gpio_cfg_t cfg);
void gpio_write(gpio_pin_t p, gpio_level_t level);
gpio_level_t gpio_read(gpio_pin_t p);

#endif // GPIO_H_

