#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"

/* GPIOA address boundary (0x4002 0000 - 0x4002 03FF) : AHB1 */
#define GPIOA            0x40020000

#define GPIO_PIN_0        0x0
#define GPIO_PIN_1        0x1
#define GPIO_PIN_2        0x2
#define GPIO_PIN_3        0x3
#define GPIO_PIN_4        0x4
#define GPIO_PIN_5        0x5
#define GPIO_PIN_6        0x6
#define GPIO_PIN_7        0x7
#define GPIO_PIN_8        0x8
#define GPIO_PIN_9        0x9
#define GPIO_PIN_10       0xa
#define GPIO_PIN_11       0xb
#define GPIO_PIN_12       0xc
#define GPIO_PIN_13       0xd
#define GPIO_PIN_14       0xe
#define GPIO_PIN_15       0xf

#define GPIO_OUTPUT_LOW_SPEED             0x0
#define GPIO_OUTPUT_MEDIUM_SPEED          0x1
#define GPIO_OUTPUT_HIGH_SPEED            0x2
#define GPIO_OUTPUT_VERY_HIGH_SPEED       0x3

#define GPIO_INPUT_MODE        0x0
#define GPIO_OUTPUT_MODE       0x1
#define GPIO_ALT_MODE          0x2
#define GPIO_ANALOG_MODE       0x3

#define GPIO_PIN_LOW       0x0
#define GPIO_PIN_HIGH      0x1

#define GPIO_AF_0       0x0
#define GPIO_AF_1       0x1
#define GPIO_AF_2       0x2
#define GPIO_AF_3       0x3
#define GPIO_AF_4       0x4
#define GPIO_AF_5       0x5
#define GPIO_AF_6       0x6
#define GPIO_AF_7       0x7
#define GPIO_AF_8       0x8
#define GPIO_AF_9       0x9
#define GPIO_AF_A       0xa
#define GPIO_AF_B       0xb
#define GPIO_AF_C       0xc
#define GPIO_AF_D       0xd
#define GPIO_AF_E       0xe
#define GPIO_AF_F       0xf


/* GPIO registers */
typedef struct {
  volatile uint32_t moder;
  volatile uint32_t otyper;
  volatile uint32_t ospeedr;
  volatile uint32_t pupdr;
  volatile uint32_t idr;
  volatile uint32_t odr;
  volatile uint32_t bsrr;
  volatile uint32_t lckr;
  volatile uint32_t afrl;
  volatile uint32_t afrh;
} gpio_t;

void gpio_set_mode(gpio_t *gpio, uint32_t mode, uint8_t pin, uint32_t alt_value);
void gpio_write_pin(gpio_t *gpio, uint8_t pin, uint8_t value);
uint32_t gpio_read_pin(gpio_t *gpio, uint8_t pin);

#endif // GPIO_H_

