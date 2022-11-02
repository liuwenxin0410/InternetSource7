#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "Led.h" //LED系统运行指示灯
#include "usart2.h"//串口二 读取6050数据
#include "encoder.h"//编码器 TIM2，TIM4
#include "Tim3.h" //定时器三  中断函数调节
#include "pwm.h"  //TIM1   A8和A11
#include "Pid.h"  //算法   PD平衡


/******所有定义的全局变量在此处有声明*******/
extern char usart2_buff[30];   //6050缓存数组
extern char USART2_Flag;       //6050接收状态标记	
extern int Moto1,Moto2;				//电机PWM变量
extern int Encoder_Left,Encoder_Right; //左右编码器的脉冲计数
extern int Blance_Pwm;   //直立环PID计算
extern int Velocity_Pwm; //速度环PID计算

extern volatile float a[3],w[3],angle[3],T;
/*****************************************************************
a为加速度：a[0]x轴加速度,a[1]y轴加速度,a[2]z轴加速度
w为角加速度：w[0]x轴角加速度,w[1]y轴角加速度,w[2]z轴角加速度,
angle为角度：angle[0]为x轴角度,angle[1]为y轴角度,angle[2]z轴角度,
T为温度
******************************************************************/

void JTAG_Set(u8 mode);


int main(void)
{
	delay_init();
	NVIC_Configuration();
	uart_init(115200);
	
	LED_Init();
	Encoder_Init_TIM2();  //=====编码器1
	Encoder_Init_TIM4();  //=====编码器2
	Motor_Init();
  PWM_Init(7199,0);     //10k的PWM波
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

