#ifndef USART_H_
#define USART_H_
#include "stm32f411xx.h"

#define USART2          (usart_t *)USART2_START

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
  uint32_t mantissa;
  uint32_t fraction;
} usart_brr_t;

void usart_init(usart_t *usart, usart_brr_t brr_cfg);
void usart_send(usart_t *usart, char *buff, uint32_t buff_len);

#endif // USART_H_

