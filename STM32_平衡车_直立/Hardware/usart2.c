#include "usart2.h"
#include "stdio.h"

char usart2_buff[30];
char USART2_Flag=0;       //接收状态标记	
unsigned char count=0;
volatile float a[3],w[3],angle[3],T; //从6050获取的数据
void uart2_init( u32 bound )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
    
    
    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = bound;                //蚧般殍置蝍9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字3のa8位陏綴格杲
    USART_InitStructure.USART_StopBits = USART_StopBits_1;     //蚧个??位
    USART_InitStructure.USART_Parity = USART_Parity_No;        //蜹奇偶验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Y狩控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//暾??杲   
    
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
   // USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE);
}


void USART2_IRQHandler(void)                	//中断服务程序
{
	if ( USART_GetITStatus ( USART2, USART_IT_RXNE ) != RESET )
	{
		usart2_buff[count]=USART_ReceiveData(USART2);
		if(usart2_buff[0]!=0x55 && count==0) return;
		count++;
		if(count==11) //接收到一组数据
		{
			count=0;
			USART2_Flag=1;
		}
	}
} 

void UART_PutChar(USART_TypeDef* USARTx, uint8_t Data)  
{  
    USART_SendData(USARTx, Data);  
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET){}  
}  
void UART_PutStr (USART_TypeDef* USARTx, uint8_t *str)    
{    
    while (0 != *str)    
    {    
        UART_PutChar(USARTx, *str);    
        str++;    
    }    
}
int Get_6050Data(void)
{
	unsigned char i=0;
	if(USART2_Flag==1)
		{
			USART2_Flag=0;  //清接收标记
			if(usart2_buff[0]==0x55)
			{
				if(usart2_buff[1]==0x51)//加速度
				{
						a[0] = ((short)(usart2_buff[3]<<8| usart2_buff[2]))/32768.0*16;
						a[1] = ((short)(usart2_buff[5]<<8| usart2_buff[4]))/32768.0*16;
						a[2] = ((short)(usart2_buff[7]<<8| usart2_buff[6]))/32768.0*16;
				}
				else if(usart2_buff[1]==0x52)//角加速度
				{
						w[0] = ((short)(usart2_buff[3]<<8| usart2_buff[2]))/32768.0*2000;
						w[1] = ((short)(usart2_buff[5]<<8| usart2_buff[4]))/32768.0*2000;
						w[2] = ((short)(usart2_buff[7]<<8| usart2_buff[6]))/32768.0*2000;
				}
				else if(usart2_buff[1]==0x53)//角度
				{
						angle[0] = ((short)(usart2_buff[3]<<8| usart2_buff[2]))/32768.0*180;
						angle[1] = ((short)(usart2_buff[5]<<8| usart2_buff[4]))/32768.0*180;
						angle[2] = ((short)(usart2_buff[7]<<8| usart2_buff[6]))/32768.0*180;
				}
				
				for(i=0;i<30;i++)
			  {
				  usart2_buff[i]=0;
			  }
			}
			else
			{
				for(i=0;i<30;i++)
				{
					usart2_buff[i]=0;
				}
				return 0;
			}
	 }
	  return 1;
}
