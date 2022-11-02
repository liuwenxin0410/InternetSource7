#include "mpuiic.h"
#include "delay.h"
 
/**********************************************
�������ƣ�MPU_IIC_Delay
�������ܣ�MPU IIC��ʱ��������ʱ2ms
������������
��������ֵ����
**********************************************/
void MPU_IIC_Delay(void)
{
	delay_us(2);
}

/**********************************************
�������ƣ�MPU_IIC_Init
�������ܣ�MPU IIC��ʼ��
������������
��������ֵ����
**********************************************/
void MPU_IIC_Init(void)
{					     
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);			//��ʹ������IO PORTBʱ�� 
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	  //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				  //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 					//�����趨������ʼ��GPIO 
	
  GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);						  //PB10,PB11 �����	
 
}

/**********************************************
�������ƣ�MPU_IIC_Start
�������ܣ�MPU IIC������ʼ�ź�
������������
��������ֵ����
**********************************************/
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //SDA�� ���
	MPU_IIC_SDA=1;	  	  
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
 	MPU_IIC_SDA=0;     //START:��SCL�ߴ��ڸߵ�ƽʱ,SDA��ͻȻ�Ӹ߱��,������ʼ�ź�
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;		 //ǯסI2C���ߣ�׼�����ͻ�������� 
}

/**********************************************
�������ƣ�MPU_IIC_Stop
�������ܣ�MPU IIC����ֹͣ�ź�
������������
��������ֵ����
**********************************************/
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();		 //SDA�����
	MPU_IIC_SCL=0;
	MPU_IIC_SDA=0;		 //STOP:��SCL�ߴ��ڸߵ�ƽʱ,SDA��ͻȻ�ӵͱ��,����ֹͣ�ź�
 	MPU_IIC_Delay();
	MPU_IIC_SCL=1; 
	MPU_IIC_SDA=1;		 //����I2C���߽����ź�
	MPU_IIC_Delay();							   	
}

/**********************************************
�������ƣ�MPU_IIC_Wait_Ack
�������ܣ�MPU IIC�ȴ��źŵ���
������������
��������ֵ��1:����Ӧ���źųɹ�  0:����Ӧ���ź�ʧ��
**********************************************/
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();  //SDA����Ϊ����  
	MPU_IIC_SDA=1;MPU_IIC_Delay();
	MPU_IIC_SCL=1;MPU_IIC_Delay();
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL=0;//ʱ�����0
	return 0;
} 

/**********************************************
�������ƣ�MPU_IIC_Ack
�������ܣ�MPU IIC����Ӧ���ź�
������������
��������ֵ����
**********************************************/
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=0;
	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}

/**********************************************
�������ƣ�MPU_IIC_NAck
�������ܣ�MPU IIC������Ӧ���ź�
������������
��������ֵ����
**********************************************/   
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}

/**********************************************
�������ƣ�MPU_IIC_Send_Byte
�������ܣ�MPU IIC����һ���ֽ�
����������txd��Ҫ���͵�����
��������ֵ����
ע�⣺IIC�����ֽ���һ��һ��λ���͵ģ�����һ���ֽ���Ҫ���Ͱ˴�
**********************************************/
void MPU_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		MPU_SDA_OUT(); 	    
    MPU_IIC_SCL=0;		//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        MPU_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		    MPU_IIC_SCL=1;
		    MPU_IIC_Delay(); 
		    MPU_IIC_SCL=0;	
		    MPU_IIC_Delay();
    }	 
} 	    

/**********************************************
�������ƣ�MPU_IIC_Read_Byte
�������ܣ�MPU IIC��ȡһ���ֽ�
����������ack: 1,����ACK   0,����NACK 
��������ֵ�����յ�������
ע�⣺IIC��ȡ�ֽ���һ��һ��λ��ȡ�ģ���ȡһ���ֽ���Ҫ��ȡ�˴�
**********************************************/ 
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
  MPU_SDA_IN();              //SDA����Ϊ����
    for(i=0;i<8;i++)
	  {
        MPU_IIC_SCL=0;
        MPU_IIC_Delay();
				MPU_IIC_SCL=1;
        receive<<=1;
        if(MPU_READ_SDA)receive++;   //�������������
				MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();   //����nACK
    else
        MPU_IIC_Ack();    //����ACK   
    return receive;
}
