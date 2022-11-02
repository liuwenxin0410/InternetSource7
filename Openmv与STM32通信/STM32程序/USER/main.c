#include "LJY_TEST.h"

extern int16_t get_color;
extern int16_t X_red_data;
extern int16_t Y_red_data;

 int main(void)
 {		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	uart4_Init();
	LCD_Init();
	OLED_Init();
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART	
	//POINT_COLOR=RED;
  	while(1) 
	{	
		switch (get_color)
		{
			case 1:LCD_Fill(1,1,150,150,RED);
						 LCD_Fill(151,1,300,150,BLUE);
			       LCD_Fill(301,1,450,150,GREEN);
			       break;
			case 2:LCD_Fill(1,1,150,150,RED);
						 LCD_Fill(151,1,300,150,GREEN);
			       LCD_Fill(301,1,450,150,BLUE);
			       break;
		  case 3:LCD_Fill(1,1,150,150,BLUE);
						 LCD_Fill(151,1,300,150,RED);
			       LCD_Fill(301,1,450,150,GREEN);
			       break;
			case 4:LCD_Fill(1,1,150,150,GREEN);
						 LCD_Fill(151,1,300,150,BLUE);
			       LCD_Fill(301,1,450,150,RED);
			       break;	
			case 5:LCD_Fill(1,1,150,150,GREEN);
						 LCD_Fill(151,1,300,150,RED);
			       LCD_Fill(301,1,450,150,BLUE);
			       break;
			case 6:LCD_Fill(1,1,150,150,BLUE);
						 LCD_Fill(151,1,300,150,GREEN);
			       LCD_Fill(301,1,450,150,RED);
			       break;
			default:
			       break;						 
		}

			
		
	}  

}
