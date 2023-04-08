#ifndef _TM1637_H_
#define _TM1637_H_


#include "main.h"
#include "gpio.h"
//#include "delay.h"

#define CLK_0 	HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_RESET)
#define CLK_1 	HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_SET)

#define DIO_0 	HAL_GPIO_WritePin(SCL_GPIO_Port,DO_Pin,GPIO_PIN_RESET)
#define DIO_1 	HAL_GPIO_WritePin(SCL_GPIO_Port,DO_Pin,GPIO_PIN_SET)


extern unsigned char tab[];

    //相关函数声明
/************************************
TM1637_DATA_Config
参数
unsigned char fb						；(88):88 显示数字设置
unsigned char fb_show_flag	；(88):88 显示开关设置	1:显示  0不显示
unsigned char sb						；88:(88) 显示数字设置
unsigned char sb_show_flag	；88:(88) 显示开关设置	1:显示  0不显示
unsigned char dot						；88(:)88 显示开关设置	1:显示  0不显示

使用例程 ：
TM1637_DATA_Config(11,1,22,1,1);
TM1637_DATA_Display();
显示效果 ：11:22

使用例程 ：
TM1637_DATA_Config(12,0,34,1,1);
TM1637_DATA_Display();
显示效果 ：__:34

使用例程 ：
TM1637_DATA_Config(12,0,34,0,1);
TM1637_DATA_Display();
显示效果 ：__:__
**************************************/
    void TM1637_DATA_Config(unsigned char fb,unsigned char fb_show_flag,unsigned char sb,unsigned char sb_show_flag,unsigned char dot);
    void I2C_Start(void);
    void I2C_stop(void);
    void TM1637_WriteBit(unsigned char mBit);
    void TM1637_WriteByte(unsigned char Byte);
    void TM1637_WriteCommand(unsigned char mData);
    void TM1637_WriteData(unsigned char addr,unsigned char mData);
    void TM1637_DATA_Display(void);
#endif
