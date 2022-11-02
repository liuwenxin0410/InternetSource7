#include "Pid.h"
#include "pwm.h"
#define ZHONGZHI  -1 //��ʵ���������

int Moto1=0,Moto2=0;
int Blance_Pwm=0;

extern int Encoder_Left,Encoder_Right; //���ұ��������������
int Velocity_Pwm; //�ٶȻ�PID����

/**************************************************************************
�������ܣ�ֱ��PD����
��ڲ������Ƕȡ����ٶ�
����  ֵ��ֱ������PWM
**************************************************************************/
int balance(float Angle,float Gyro)
{  
	//����KpֵΪ720ʱ��С���ڡ�10��ʱ�ͻ���ת����ȷ����ΧΪ0~720.��С������Kpֱ����Ƶ�Ķ�������
	//�۲������ǵ�ԭʼ����֪���ٶȲ��ᳬ������λ��������7200��ʾ��ռ�ձȣ�����ȷ��Kdֵ��С
	//Kp��Kd���ϵ��Խ���ǳ��ֶ���ǰ����Խ��Խ�á�
   float Bias,kp=170,kd=20;    //kp��Pϵ�� kd��Dϵ�� kp=240,kd=9;  //180  9.5   //180  10
	 int balance;
	 Bias=Angle-ZHONGZHI;       //===���ƽ��ĽǶ���ֵ �ͻ�е���
	 balance=kp*Bias+Gyro*kd;   //===����ƽ����Ƶĵ��PWM  PD����  
	 return balance;
}
/**************************************************************************
�������ܣ��ٶ�PI���� �޸�ǰ�������ٶȣ�����Target_Velocity�����磬�ĳ�60�ͱȽ�����
��ڲ��������ֱ����������ֱ�����
����  ֵ���ٶȿ���PWM
��    �ߣ�ƽ��С��֮��
**************************************************************************/
int velocity(int encoder_left,int encoder_right)
{  
    static float Velocity,Encoder_Least,Encoder;
	  static float Encoder_Integral;
	  static int i=0;
	  float kp=73,ki=kp /234.0;   //42  0.2  //51  52/200  //61  52/200
   //=============�ٶ�PI������=======================//	
		Encoder_Least =(Encoder_Left+Encoder_Right)-0;   //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
		Encoder *= 0.7;		                               //===һ�׵�ͨ�˲���       
		Encoder += Encoder_Least*0.3;	                   //===һ�׵�ͨ�˲���    
		Encoder_Integral +=Encoder;                      //===���ֳ�λ�� ����ʱ�䣺10ms
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;  //===�����޷�
		if(Encoder_Integral<-10000)	Encoder_Integral=-10000;   //===�����޷�	
		Velocity=Encoder*kp+Encoder_Integral*ki;          //===�ٶȿ���	
	  i++;
		//if(i>200)   Encoder_Integral=0;      //===����رպ��������//80
	  return Velocity;
}
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM  ���޷�
����  ֵ����
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
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=7000;    //===PWM������7200 ������6900
    if(Moto1<-Amplitude) Moto1=-Amplitude;	
		if(Moto1>Amplitude)  Moto1=Amplitude;	
	  if(Moto2<-Amplitude) Moto2=-Amplitude;	
		if(Moto2>Amplitude)  Moto2=Amplitude;		
}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

