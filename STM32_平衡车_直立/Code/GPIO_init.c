#include "stm32f10x.h" 
#include "GPIO_init.h"
//GPIO��ʼ���������������������ģʽ�ڳ�ʼ������
void GPIO_Config(void)
{
		GPIO_InitTypeDef GPIOB_Init;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      //�����ⲿʱ��
		GPIOB_Init.GPIO_Pin=0xFFFF;
		/****GPIO_Pin��GPIO_InitTypeDef �ṹ����ռ16λ���ʿ�����������ѡ����Ҫ��ʼ�������λ**********/
		GPIOB_Init.GPIO_Mode=GPIO_Mode_Out_PP;        //��©���
		GPIOB_Init.GPIO_Speed=GPIO_Speed_50MHz;       //�ⲿ����50MHZ
		GPIO_Init(GPIOB,&GPIOB_Init);          //GPIOB��ʼ��
}

