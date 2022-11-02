#ifndef __TIM3_H
#define __TIM3_H
#include "sys.h"	 

void TIM3_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);   //TIM3ÖÐ¶Ï
#endif
