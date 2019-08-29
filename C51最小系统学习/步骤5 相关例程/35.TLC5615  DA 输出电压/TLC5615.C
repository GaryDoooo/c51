

#include <intrins.h>
#include <reg51.h>
/************定义接口总线**************/
//TLC5615管脚定义 与开发板硬件对应
sbit SPI_CLK   = P1^7;    //时钟
sbit SPI_DATA  = P1^5;     //数据输出
sbit CS_DA     = P1^4;      //片选

sbit LED1       = P2 ^ 4;
sbit LED2       = P2 ^ 5;
sbit LED3       = P2 ^ 6;
sbit LED4       = P2 ^ 7;

sbit KEY1       = P3 ^ 4;
sbit KEY2       = P3 ^ 5;

/*-------------------------------------------------------------*/
//数据定义


unsigned char LED[4];     //电压数据转换成数码管数字
unsigned int  Volt=200;

 

/*-------------------------------------------------------------*/
//函数声明					
void da5615(unsigned int da);   //DA数据 SPI发送函数
void Volt_To_LED(void);        //数据转换成数码管显示数字

/************接口总线定义结束**********/
unsigned char code LEDData1 [ ] = {                
                                    0x03,/*0*/
                                    0x9F,/*1*/
                                    0x25,/*2*/
                                    0x0D,/*3*/
                                    0x99,/*4*/
                                    0x49,/*5*/
                                    0x41,/*6*/
                                    0x1F,/*7*/
                                    0x01,/*8*/
                                    0x09,/*9*/
                                  }; //0-9LED数值




    void da5615(unsigned int da)
{
/******************************************
   unsigned char i;
   da<<=6;
   CS_DA=0;
   SPI_CLK=0;

   for (i=0;i<12;i++)
   {
   SPI_DATA=(bit)(da&0x8000);
   SPI_CLK=1;
   da<<=1;
   SPI_CLK=0;
   }

   CS_DA=1;
   SPI_CLK=0;
   for (i=0;i<12;i++);
}
***********************************************/
unsigned char i;
SPI_CLK=0;//时钟低
CS_DA=0;//片选有效
for (i=0;i<12;i++)
{
    if((da&0x800)==0){SPI_DATA=0;}
    else SPI_DATA=1;
    SPI_CLK=1;//时钟高
    da=da<<1;//左移一位
    SPI_CLK=0;//时钟低
}
CS_DA=1;//
} 




/*-------------------------------------------------------------*/
//数据转换成数码管显示数字
void Volt_To_LED(void)
{
 //da5615(100);              //电压换算并扩大1000倍
 LED[0] = Volt / 1000 ;//& 0x7f;   //千位加小数点
 LED[1] = Volt / 100 % 10;           //百位
 LED[2] = Volt / 10 % 10;             //十位
 LED[3] = Volt % 10;                    //个位 
}



     void Delay(int num)//延时函数
{
	 while(num--) ;
}


      void   Display(void)			  
{
      unsigned char k;
	  for(k=0;k<20;k++)
	  {
      P0=LEDData1[ LED[0]];
	  LED1=0;
	  Delay(255);
	  LED1=1;

	  P0=LEDData1[ LED[1]];
	  LED2=0;
	  Delay(255);
	  LED2=1;

	  P0=LEDData1[ LED[2]];
	  LED3=0;
	  Delay(255);
	  LED3=1;

	  P0=LEDData1[ LED[3]];
	  LED4=0;
	  Delay(255);
	  LED4=1;
	  }
 } 

      void   main (void)
{
	 da5615(Volt);
	 Volt_To_LED(); 
 

	  while(1)
	  {

	  if(KEY1==0)
	{ 
	  Delay(100);
	  if(KEY1==0)
	  {
	   while(!KEY1)
	   Display();

	   Volt=Volt+10;
	   da5615(Volt);              
	   Volt_To_LED();
	  }
	}
	 
	    if(KEY2==0)
	{ 
	  Delay(100);
	  if(KEY2==0)
	  {
	   while(!KEY2)
	   Display();
	   
	   Volt=Volt-10;
	   da5615(Volt);              
	   Volt_To_LED();
	   
	  }
	}

	  Display();
	  }
}