//程序功能1602液晶第一行显示"0123456789ABCDEF";第二行显示"!@#$%^&*()<>{}?+";
#include "reg52.h"
#define uchar unsigned char 
#define uint unsigned int

sbit rs=P2^3;//H数据，L命令
sbit lcden=P2^5;//高脉冲使能，使能脉宽最小150ns
sbit rw=P2^4;
uchar code table[]="mcustudio.com.cn";
uchar code table1[]="TEL:159808545601";
void delay(uchar x)
{	uint y;
			for(;x>0;x--)
	 {									 
		for(y=100;y>0;y--)
				{};
	 }
}
void lcdwrdata(uchar dat)
{
    dat = ((dat&0x01)<<7)|((dat&0x02)<<5)|((dat&0x04)<<3)|((dat&0x08)<<1)|((dat&0x10)>>1)|((dat&0x20)>>3)|((dat&0x40)>>5)|((dat&0x80)>>7);
	rs=1;//写数据时RS拉高
	lcden=1;
	P0=dat;
	delay(6);
	lcden=0;
	delay(6);
}
void lcdwrcom(uchar cdat)//写指令数据到LCD  
{	
    cdat = ((cdat&0x01)<<7)|((cdat&0x02)<<5)|((cdat&0x04)<<3)|((cdat&0x08)<<1)|((cdat&0x10)>>1)|((cdat&0x20)>>3)|((cdat&0x40)>>5)|((cdat&0x80)>>7);
    rs=0;//写指令时RS拉低
	lcden=1;
    P0=cdat;//
	delay(6);//不加此延时将导致不能写入指令，但能写入显示数据
	lcden=0;
	delay(6);
}
void lcd_init()
{
	lcdwrcom(0x38);//0x38设置显示模式为：16X2 显示,5X7 点阵,8 位数据接口
	lcdwrcom(0x0c);//打开显示光标闪烁
	lcdwrcom(0x06);//
	lcdwrcom(0x01);//
}
void main()
{	uchar n;
    rw=0;
	delay(200);
	lcden=0;
	lcd_init();
	lcdwrcom(0x00|0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table[n]);
		delay(100);
	}

	lcdwrcom(0x40|0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table1[n]);
		delay(100);
	}
	while(1)
	{
	}
}
