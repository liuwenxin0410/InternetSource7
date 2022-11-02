#include "stm32f10x.h" 
#include "GPIO_init.h"
//GPIO初始化函数，设置输出，输入模式口初始化函数
void GPIO_Config(void)
{
		GPIO_InitTypeDef GPIOB_Init;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      //开启外部时钟
		GPIOB_Init.GPIO_Pin=0xFFFF;
		/****GPIO_Pin在GPIO_InitTypeDef 结构体中占16位，故可以用与运算选择需要初始化的相关位**********/
		GPIOB_Init.GPIO_Mode=GPIO_Mode_Out_PP;        //开漏输出
		GPIOB_Init.GPIO_Speed=GPIO_Speed_50MHz;       //外部晶振50MHZ
		GPIO_Init(GPIOB,&GPIOB_Init);          //GPIOB初始化
}

