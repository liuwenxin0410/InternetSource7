#include "Tim3.h"
#include "Led.h"	 
#include "usart2.h"
#include "usart.h"
#include "delay.h"
#include "Pid.h"
#include "encoder.h"

u8 count1;
extern char usart2_buff[30]; //6050��������
extern char USART2_Flag;       //6050����״̬���	
extern float volatile a[3],w[3],angle[3],T;
extern int Moto1,Moto2;//PWM����
extern int Encoder_Left,Encoder_Right; //���ұ��������������
extern int Blance_Pwm;   //ֱ����PID����
extern int Velocity_Pwm; //�ٶȻ�PID����

/*
 * ��������TIM3_Int_Init
 * ����  ��ͨ�ö�ʱ��3�жϳ�ʼ��������ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
 * ����  ��arr���Զ���װֵ��
					 psc��ʱ��Ԥ��Ƶ��
 * ���  ����
 */	 
void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}

/*
 * ��������TIM3_IRQHandler
 * ����  ����ʱ��3�жϷ������
 * ����  ����
 * ���  ����
 */	
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־
    	
//					printf("left%d\r\n",Read_Encoder(2));
//		printf("right%d\r\n",Read_Encoder(4));
		
		Encoder_Left=Read_Encoder(2);//===��ȡ��������ֵ����Ϊ�����������ת��180�ȵģ����Զ�����һ��ȡ������֤�������һ��
		Encoder_Right=Read_Encoder(4);//===��ȡ��������ֵ

		Blance_Pwm=balance(angle[0],w[0]);  
		Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);
		Moto1=Blance_Pwm+Velocity_Pwm;
		Moto2=Blance_Pwm+Velocity_Pwm;

		Set_Pwm(Moto1,Moto2);
	}
}
