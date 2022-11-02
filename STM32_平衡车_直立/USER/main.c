#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "Led.h" //LEDϵͳ����ָʾ��
#include "usart2.h"//���ڶ� ��ȡ6050����
#include "encoder.h"//������ TIM2��TIM4
#include "Tim3.h" //��ʱ����  �жϺ�������
#include "pwm.h"  //TIM1   A8��A11
#include "Pid.h"  //�㷨   PDƽ��


/******���ж����ȫ�ֱ����ڴ˴�������*******/
extern char usart2_buff[30];   //6050��������
extern char USART2_Flag;       //6050����״̬���	
extern int Moto1,Moto2;				//���PWM����
extern int Encoder_Left,Encoder_Right; //���ұ��������������
extern int Blance_Pwm;   //ֱ����PID����
extern int Velocity_Pwm; //�ٶȻ�PID����

extern volatile float a[3],w[3],angle[3],T;
/*****************************************************************
aΪ���ٶȣ�a[0]x����ٶ�,a[1]y����ٶ�,a[2]z����ٶ�
wΪ�Ǽ��ٶȣ�w[0]x��Ǽ��ٶ�,w[1]y��Ǽ��ٶ�,w[2]z��Ǽ��ٶ�,
angleΪ�Ƕȣ�angle[0]Ϊx��Ƕ�,angle[1]Ϊy��Ƕ�,angle[2]z��Ƕ�,
TΪ�¶�
******************************************************************/

void JTAG_Set(u8 mode);


int main(void)
{
	delay_init();
	NVIC_Configuration();
	uart_init(115200);
	
	LED_Init();
	Encoder_Init_TIM2();  //=====������1
	Encoder_Init_TIM4();  //=====������2
	Motor_Init();
  PWM_Init(7199,0);     //10k��PWM��
	uart2_init(115200);	
	TIM3_Init(9999,71);
	printf("ok");	
	while(1)
	{
		while(Get_6050Data());
//		printf("angel%f\r\n",angle[0]);
//		delay_ms(10);
	}
}

