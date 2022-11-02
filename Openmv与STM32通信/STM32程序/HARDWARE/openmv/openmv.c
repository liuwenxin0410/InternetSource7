#include "openmv.h"
int openmv[18];//stm32������������
int16_t X_red_data;//���պ�ɫ���ĺ�����ľ���ֵ
int16_t Y_red_data;//���պ�ɫ����������ľ���ֵ

int16_t X_green_data;//���պ�ɫ���ĺ�����ľ���ֵ
int16_t Y_green_data;//���պ�ɫ����������ľ���ֵ

int16_t X_blue_data;//���ջ�ɫ���ĺ�����ľ���ֵ
int16_t Y_blue_data;//���ջ�ɫ����������ľ���ֵ

int16_t get_color;

int i=0;

void Openmv_Receive_Data(int16_t data)//����Openmv������������
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
	else if(state==17)		//����Ƿ���ܵ�������־
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

