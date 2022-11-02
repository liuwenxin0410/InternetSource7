#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
#include "sys.h"	 

#define PWMA   TIM1->CCR1  //PA8
#define PWMB   TIM1->CCR3  //PA11

#define AIN2   PBout(0)
#define AIN1   PBout(1)
#define BIN1   PBout(2)
#define BIN2   PBout(3)

void PWM_Init(u16 arr,u16 psc);
void Motor_Init(void);

#endif
