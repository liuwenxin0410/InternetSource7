一.接线
模块共有:Stm32f103C8T6、OLED、MPU6050
①OLED:          SCL->PA1     SDA->PA2                       供电为3.3V
②MPU6050:   SCL->PB10   SDA->PB11  AD0接PA15   供电为5V

二.MPU6050
1.mpuiic编写关于MPU6050的IIC的一系列函数；
2.mpu6050存放MPU6050寄存器的地址的宏定义、MPU6050初始化函数、