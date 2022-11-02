#include "Pid.h"
#include "pwm.h"
#define ZHONGZHI  -1 //由实际情况决定

int Moto1=0,Moto2=0;
int Blance_Pwm=0;

extern int Encoder_Left,Encoder_Right; //左右编码器的脉冲计数
int Velocity_Pwm; //速度环PID计算

/**************************************************************************
函数功能：直立PD控制
入口参数：角度、角速度
返回  值：直立控制PWM
**************************************************************************/
int balance(float Angle,float Gyro)
{  
	//假设Kp值为720时，小车在±10°时就会慢转。故确定范围为0~720.从小逐渐增大Kp直到低频的抖动出现
	//观察陀螺仪的原始数据知道速度不会超过多少位数，再由7200表示满占空比，所以确定Kd值大小
	//Kp和Kd联合调试结果是出现抖动前参数越大越好。
   float Bias,kp=170,kd=20;    //kp是P系数 kd是D系数 kp=240,kd=9;  //180  9.5   //180  10
	 int balance;
	 Bias=Angle-ZHONGZHI;       //===求出平衡的角度中值 和机械相关
	 balance=kp*Bias+Gyro*kd;   //===计算平衡控制的电机PWM  PD控制  
	 return balance;
}
/**************************************************************************
函数功能：速度PI控制 修改前进后退速度，请修Target_Velocity，比如，改成60就比较慢了
入口参数：左轮编码器、右轮编码器
返回  值：速度控制PWM
作    者：平衡小车之家
**************************************************************************/
int velocity(int encoder_left,int encoder_right)
{  
    static float Velocity,Encoder_Least,Encoder;
	  static float Encoder_Integral;
	  static int i=0;
	  float kp=73,ki=kp /234.0;   //42  0.2  //51  52/200  //61  52/200
   //=============速度PI控制器=======================//	
		Encoder_Least =(Encoder_Left+Encoder_Right)-0;   //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
		Encoder *= 0.7;		                               //===一阶低通滤波器       
		Encoder += Encoder_Least*0.3;	                   //===一阶低通滤波器    
		Encoder_Integral +=Encoder;                      //===积分出位移 积分时间：10ms
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;  //===积分限幅
		if(Encoder_Integral<-10000)	Encoder_Integral=-10000;   //===积分限幅	
		Velocity=Encoder*kp+Encoder_Integral*ki;          //===速度控制	
	  i++;
		//if(i>200)   Encoder_Integral=0;      //===电机关闭后清除积分//80
	  return Velocity;
}
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM  带限幅
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
	    Xianfu_Pwm();
    	if(moto1>0)			AIN2=0,			AIN1=1;
			else 	          AIN2=1,			AIN1=0;
			PWMA=myabs(moto1);
		  if(moto2>0)	BIN1=1,			BIN2=0;
			else        BIN1=0,			BIN2=1;
			PWMB=myabs(moto2);	
} 

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=7000;    //===PWM满幅是7200 限制在6900
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
}
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

