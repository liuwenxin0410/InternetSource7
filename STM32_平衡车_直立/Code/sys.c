/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ��ϵͳ����  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/*
 * ��������NVIC_Configuration
 * ����  ������NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 * ����  ����
 * ���  ����
 */
void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
void Sys_Soft_Reset()
{
		SCB->AIRCR=0X05FA0000|(u32)0x04;
}
