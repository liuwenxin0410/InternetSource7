#ifndef  __PID_H
#define  __PID_H

#include "sys.h"

int balance(float Angle,float Gyro);
int velocity(int encoder_left,int encoder_right);
void Set_Pwm(int moto1,int moto2);
void Xianfu_Pwm(void);
int myabs(int a);
#endif 

