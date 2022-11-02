#include "LJY_TEST.h"

extern int16_t get_color;
extern int16_t X_red_data;
extern int16_t Y_red_data;

 int main(void)
 {		
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	uart4_Init();
	LCD_Init();
	OLED_Init();
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART	
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
