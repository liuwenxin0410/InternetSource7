#include "sys.h"


extern int openmv[18];//stm32接收数据数组
extern int16_t X_black_data;//接收黑色中心横坐标的绝对值
extern int16_t Y_black_data;//接收黑色中心纵坐标的绝对值
extern int16_t X_black_sign;//接收黑色横坐标符号位
extern int16_t Y_black_sign;//接收黑色纵坐标符号位
extern int16_t X_black_relative_displacement;//黑色中心横坐标
extern int16_t Y_black_relative_displacement;//黑色中心纵坐标
extern int16_t X_red_data;//接收红色中心横坐标的绝对值
extern int16_t Y_red_data;//接收红色中心纵坐标的绝对值
extern int16_t X_red_sign;//接收红色横坐标符号位
extern int16_t Y_red_sign;//接收红色纵坐标符号位
extern int16_t X_red_relative_displacement;//红色中心横坐标
extern int16_t Y_red_relative_displacement;//红色中心纵坐标
extern int16_t X_yellow_data;//接收黄色中心横坐标的绝对值
extern int16_t Y_yellow_data;//接收黄色中心纵坐标的绝对值
extern int16_t X_yellow_sign;//接收黄色横坐标符号位
extern int16_t Y_yellow_sign;//接收黄色纵坐标符号位
extern int16_t X_yellow_relative_displacement;//黄色中心横坐标
extern int16_t Y_yellow_relative_displacement;//黄色中心纵坐标
extern int16_t L_black;
extern int16_t L_red;
extern int16_t L_yellow;



void Openmv_Receive_Data(int16_t data);
void Openmv_Data(void);

