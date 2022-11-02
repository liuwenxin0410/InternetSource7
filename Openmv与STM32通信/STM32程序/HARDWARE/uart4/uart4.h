#ifndef UART4_H
#define UART4_H
#include "sys.h"

void uart4_Init(void);
void uart4_SendByte(unsigned char *DataToSend ,u8 data_num);

#endif

