#include "tm1637.h"
unsigned char dt=20; //延时时间参数
unsigned char  dpFlag = 0;//主函数有说明 
unsigned char  Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
unsigned char  DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x80};
struct {
	char shi;
	char ge;
}FB;
 
struct {
	char shi;
	char ge;
}SB;

void delay_us(uint16_t  time)
{    
   uint16_t i=0;  
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }
}
void TM1637_DATA_Config(unsigned char fb,unsigned char fb_show_flag,unsigned char sb,unsigned char sb_show_flag,unsigned char dot)
{
	if(fb_show_flag==1)
	{
		FB.shi = fb/10;
		FB.ge =  fb%10;
	}
	else
	{
		FB.shi=FB.ge=10;
	}
	if(sb_show_flag==1)
	{
		SB.shi = sb/10;
		SB.ge =  sb%10;
	}
	else
	{
		SB.shi=SB.ge=10;
	}
	dpFlag = dot;
		
}

void I2C_Start(void)
{
  CLK_1;
	DIO_1;
	delay_us(dt);
	
	DIO_0;
	delay_us(dt);
	CLK_0;
	delay_us(dt);
}

void I2C_stop(void)
{
	
	CLK_0;
	delay_us(dt);
  DIO_0;
	delay_us(dt);
	
  CLK_1;
	delay_us(dt);	
	DIO_1;
	delay_us(dt);  	
}

void TM1637_WriteBit(unsigned char mBit)
{
	CLK_0;
	delay_us(dt);
	if(mBit)
		DIO_1;
	else
		DIO_0;
	delay_us(dt);
	CLK_1;
	delay_us(dt);	
}
  
void TM1637_WriteByte(unsigned char Byte)
{
	char loop = 0;
	for(loop = 0;loop<8;loop++)
	{
		 TM1637_WriteBit((Byte>>loop) & 0x01);//先写低位	
	}
	CLK_0;
	delay_us(dt);
	DIO_1;	
	delay_us(dt);
	CLK_1;		
}
void TM1637_WriteCommand(unsigned char mData)
{
	I2C_Start();
	TM1637_WriteByte(mData);
	I2C_stop();
}


/*
*@note  写入地址和数据
*/

void TM1637_WriteData(unsigned char addr,unsigned char mData)
{
	I2C_Start();
	TM1637_WriteByte(addr);
	TM1637_WriteByte(mData);
	I2C_stop();
}
void TM1637_DATA_Display(void)
{
	TM1637_WriteCommand(0x44);
	TM1637_WriteData(0xc0,Data[FB.shi]);
	if(dpFlag)
			TM1637_WriteData(0xc1,DataDp[FB.ge]);
	else
			TM1637_WriteData(0xc1,Data[FB.ge]);
	
	TM1637_WriteData(0xc2, Data[SB.shi]);
	TM1637_WriteData(0xc3, Data[SB.ge]);
	TM1637_WriteCommand(0x88);
 }


