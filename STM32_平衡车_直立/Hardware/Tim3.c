#include "Tim3.h"
#include "Led.h"	 
#include "usart2.h"
#include "usart.h"
#include "delay.h"
#include "Pid.h"
#include "encoder.h"

u8 count1;
extern char usart2_buff[30]; //6050缓存数组
extern char USART2_Flag;       //6050接收状态标记	
extern float volatile a[3],w[3],angle[3],T;
extern int Moto1,Moto2;//PWM变量
extern int Encoder_Left,Encoder_Right; //左右编码器的脉冲计数
extern int Blance_Pwm;   //直立环PID计算
extern int Velocity_Pwm; //速度环PID计算

/*
 * 函数名：TIM3_Int_Init
 * 描述  ：通用定时器3中断初始化，这里时钟选择为APB1的2倍，而APB1为36M
 * 输入  ：arr：自动重装值。
					 psc：时钟预分频数
 * 输出  ：无
 */	 
void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}

/*
 * 函数名：TIM3_IRQHandler
 * 描述  ：定时器3中断服务程序
 * 输入  ：无
 * 输出  ：无
 */	
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志
    	
//					printf("left%d\r\n",Read_Encoder(2));
//		printf("right%d\r\n",Read_Encoder(4));
		
		Encoder_Left=Read_Encoder(2);//===读取编码器的值，因为两个电机的旋转了180度的，所以对其中一个取反，保证输出极性一致
		Encoder_Right=Read_Encoder(4);//===读取编码器的值

		Blance_Pwm=balance(angle[0],w[0]);  
		Velocity_Pwm=velocity(Encoder_Left,Encoder_Right);
		Moto1=Blance_Pwm+Velocity_Pwm;
		Moto2=Blance_Pwm+Velocity_Pwm;

		Set_Pwm(Moto1,Moto2);
	}
}
