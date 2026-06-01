#ifndef USART_H_
#define USART_H_
#include "stm32f411xx.h"

#define USART2          (usart_dev_t){ .usart = (usart_t *)USART2_ADDR, .irq_pos = 38, .irq_priority = 45 }
#define USART1          (usart_dev_t){ .usart = (usart_t *)USART1_ADDR, .irq_pos = 37, .irq_priority = 44 }
#define USART6          (usart_dev_t){ .usart = (usart_t *)USART6_ADDR, .irq_pos = 71, .irq_priority = 78 }

/* status register */
#define USART_SR_RXNE        (1ul << 5)
#define USART_SR_TC          (1ul << 6)
#define USART_SR_TXE         (1ul << 7)

/* control register 1 */
#define USART_CR1_RE         (1ul << 2)
#define USART_CR1_TE         (1ul << 3)
#define USART_CR1_IDLEIE     (1ul << 4)
#define USART_CR1_RXNEIE     (1ul << 5)
#define USART_CR1_TCIE       (1ul << 6)
#define USART_CR1_TXEIE      (1ul << 7)
#define USART_CR1_M          (1ul << 12)
#define USART_CR1_UE         (1ul << 13)
#define USART_CR1_OVER8      (1ul << 15)


typedef struct {
  usart_t *usart;
  uint32_t irq_pos;
  uint8_t irq_priority;
} usart_dev_t;

typedef struct {
  uint32_t mantissa;
  uint32_t fraction;
} usart_brr_t;

void usart_init(usart_dev_t usart_dev, usart_brr_t brr_cfg);
void usart_send(usart_dev_t usart_dev, uint8_t *buff, uint32_t buff_len);

#endif // USART_H_

