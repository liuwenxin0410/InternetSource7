#include "openmv.h"
int openmv[18];//stm32接收数据数组
int16_t X_red_data;//接收黑色中心横坐标的绝对值
int16_t Y_red_data;//接收黑色中心纵坐标的绝对值

int16_t X_green_data;//接收红色中心横坐标的绝对值
int16_t Y_green_data;//接收红色中心纵坐标的绝对值

int16_t X_blue_data;//接收黄色中心横坐标的绝对值
int16_t Y_blue_data;//接收黄色中心纵坐标的绝对值

int16_t get_color;

int i=0;

void Openmv_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 state = 0;
	if(state==0&&data==0x2C)
	{
		state=1;
		openmv[0]=data;
	}
	else if(state==1&&data==18)
	{
		state=2;
		openmv[1]=data;
	}
	else if(state==2)
	{
		state=3;
		openmv[2]=data;
	}
	else if(state==3)
	{
		state = 4;
		openmv[3]=data;
	}
	else if(state==4)
	{
        state = 5;
        openmv[4]=data;
	}
	else if(state==5)
	{
        state = 6;
        openmv[5]=data;
	}
	else if(state==6)
	{
        state = 7;
        openmv[6]=data;
	}
	else if(state==7)
	{
        state = 8;
        openmv[7]=data;
	}
	else if(state==8)
	{
        state = 9;
        openmv[8]=data;
	}
	else if(state==9)
	{
        state = 10;
        openmv[9]=data;
	}
	else if(state==10)
	{
        state = 11;
        openmv[10]=data;
	}
	else if(state==11)
	{
        state = 12;
        openmv[11]=data;
	}
	else if(state==12)
	{
        state = 13;
        openmv[12]=data;
	}
	else if(state==13)
	{
        state = 14;
        openmv[13]=data;
	}
	else if(state==14)
	{
        state = 15;
        openmv[14]=data;
    }
	else if(state==15)
	{
        state = 16;
        openmv[15]=data;
	}
	else if(state==16)
	{
        state = 17;
        openmv[16]=data;
	}
	else if(state==17)		//检测是否接受到结束标志
	{
        if(data == 0x5B)
        {
            state = 0;
            openmv[17]=data;
            Openmv_Data();
        }
        else if(data != 0x5B)
        {
            state = 0;
            for(i=0;i<18;i++)
            {
                openmv[i]=0x00;
            }           
        }
	}    
	else
		{
			state = 0;
            for(i=0;i<18;i++)
            {
                openmv[i]=0x00;
            }
		}
}

void Openmv_Data(void)
{
    X_red_data=openmv[4];
    Y_red_data=openmv[5];
    X_green_data=openmv[8];
    Y_green_data=openmv[9];
    X_blue_data=openmv[12];
    Y_blue_data=openmv[13];
	  get_color = openmv[14];
}

