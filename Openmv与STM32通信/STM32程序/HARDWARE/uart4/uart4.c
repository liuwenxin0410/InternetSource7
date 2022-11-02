#include "sys.h"
#include "uart4.h"
#include "openmv.h"
#include "lcd.h"
void uart4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;//���ڲ������ýṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;//�����ж����ýṹ�����
//	USART_DeInit(UART4);  //��λ����4 
	//ʹ�� UART4 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴��ڸ���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //��PC�˿�ʱ��
  
	//UART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�趨IO�ڵ�����ٶ�Ϊ50MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10
   
  //UART4_RX	  GPIOC.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC.11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 115200;//���ڲ�����Ϊ115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽʹ��
	USART_Init(UART4, &USART_InitStructure); //��ʼ������4
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  
	USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���4 
  
  //�����������1���ֽ��޷���ȷ���ͳ�ȥ������
   USART_ClearFlag(UART4, USART_FLAG_TC);                //�崮��4���ͱ�־
  
}

u8 Tx4Buffer[256];
u8 Tx4Counter=0;
u8 count4=0; 

void uart4_SendByte(unsigned char *DataToSend ,u8 data_num)	  //�ô���4����һ���ֽ�����
{	   
	u8 i;
	for(i=0;i<data_num;i++)
	{
		Tx4Buffer[count4++] = *(DataToSend+i);
	}

	if(!(UART4->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(UART4, USART_IT_TXE, ENABLE); //�򿪷����ж�
	}
}


void UART4_IRQHandler(void)			   //����4ȫ���жϷ�����
{
	u8 com_data;

  //�����ж�
	if( USART_GetITStatus(UART4,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);//����жϱ�־

		com_data = UART4->DR;
		Openmv_Receive_Data(com_data);
		Openmv_Data();		//openmv���ݴ�����
	}

	//���ͣ�������λ���ж�
	if( USART_GetITStatus(UART4,USART_IT_TXE ) )
	{
				
		UART4->DR = Tx4Buffer[Tx4Counter++]; //дDR����жϱ�־
          
		if(Tx4Counter == count4)
		{
			UART4->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�������жϣ��ж�
		}


		//USART_ClearITPendingBit(USART4,USART_IT_TXE);
	}

}


