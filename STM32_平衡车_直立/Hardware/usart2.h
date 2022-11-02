#ifndef __USART2_H
#define __USART2_H	
#include "stm32f10x.h"
#include "sys.h"

void uart2_init(u32 bound);
void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data);
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str);

int  Get_6050Data(void);


#endif 
