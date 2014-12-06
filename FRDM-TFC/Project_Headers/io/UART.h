#ifndef TFC_UART_H_
#define TFC_UART_H_

#include <stdint.h>
#include "io/RingBuffer.h"

void     UART0_Init();
void     UART0_ConfigureDataRate(int sysclk, int baud);
void     UART0_ArmIRQ();
void     UART0_DisarmIRQ();
void     UART0_ArmDMA();
int8_t   UART0_Send(uint8_t * msg, uint16_t size);

extern RingBuffer RxBuffer;
extern RingBuffer TxBuffer;

#endif /* TFC_UART_H_ */
