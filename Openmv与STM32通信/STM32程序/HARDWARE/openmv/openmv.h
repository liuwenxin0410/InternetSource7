#include "sys.h"


extern int openmv[18];//stm32������������
extern int16_t X_black_data;//���պ�ɫ���ĺ�����ľ���ֵ
extern int16_t Y_black_data;//���պ�ɫ����������ľ���ֵ
extern int16_t X_black_sign;//���պ�ɫ���������λ
extern int16_t Y_black_sign;//���պ�ɫ���������λ
extern int16_t X_black_relative_displacement;//��ɫ���ĺ�����
extern int16_t Y_black_relative_displacement;//��ɫ����������
extern int16_t X_red_data;//���պ�ɫ���ĺ�����ľ���ֵ
extern int16_t Y_red_data;//���պ�ɫ����������ľ���ֵ
extern int16_t X_red_sign;//���պ�ɫ���������λ
extern int16_t Y_red_sign;//���պ�ɫ���������λ
extern int16_t X_red_relative_displacement;//��ɫ���ĺ�����
extern int16_t Y_red_relative_displacement;//��ɫ����������
extern int16_t X_yellow_data;//���ջ�ɫ���ĺ�����ľ���ֵ
extern int16_t Y_yellow_data;//���ջ�ɫ����������ľ���ֵ
extern int16_t X_yellow_sign;//���ջ�ɫ���������λ
extern int16_t Y_yellow_sign;//���ջ�ɫ���������λ
extern int16_t X_yellow_relative_displacement;//��ɫ���ĺ�����
extern int16_t Y_yellow_relative_displacement;//��ɫ����������
extern int16_t L_black;
extern int16_t L_red;
extern int16_t L_yellow;



void Openmv_Receive_Data(int16_t data);
void Openmv_Data(void);

