/*********************************************************************************/
/*                                                                               */
/*模块名：基于DS18B20的数字温度计                                                */                               
/*                                                                               */
/*创建人：廖文丹																 */
/*邮箱：fhwxaoo@163.com                                       MCU ： 8051        */
/*                                                                               */
/*功能描述：本模块采用DALLS公司的单线数字温度传感器DS18B20，抗干扰能力强，       */
/*          便于远距离测量，因而得到了广泛应用。                                 */
/*                                                                               */
/*版本号：VETA                                             日期：06/06/15        */
/*                                                                               */
/*                                                                               */
/*                                                       晶体：  11.0592 M       */
/*                                                                               */
/*********************************************************************************/
#include <at89x51.h>

sbit DQ =     P3 ^ 7;  //定义端口DQ
sbit led1    =P2^0;
sbit led2    =P2^1;
sbit led3    =P2^2;
sbit led4    =P2^3;
unsigned char tx[10]={0,0,0x2E,0,0,0,0,0xDF,0x43,0x0A};
unsigned code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90};
/******************************************************************************/
void Delay(int num)//延时函数
{
	while(num--) ;
}
/******************************************************************************/
void Delaynms(unsigned int di) //延时
{
	unsigned int da,db;
 	for(da=0;da<di;da++)
   		for(db=0;db<100;db++);
}

/******************************************************************************/

void TX(unsigned char TX_char)
{
  SBUF=TX_char;
  while(!TI);
  TI=0;

}
/******************************************************************************/	
void Init_DS18B20(void)//初始化ds1820
{
	unsigned char x=0;
	DQ = 1;    //DQ复位
	Delay(8);  //稍做延时
	DQ = 0;    //单片机将DQ拉低
	Delay(80); //精确延时 大于 480us
	DQ = 1;    //拉高总线
	Delay(14);
	x=DQ;      //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	Delay(20);
}
/******************************************************************************/
unsigned char ReadOneChar(void)//读一个字节
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; // 给脉冲信号
		dat>>=1;
		DQ = 1; // 给脉冲信号
		if(DQ)
		dat|=0x80;
		Delay(4);
	}
	return(dat);
}

/******************************************************************************/
void WriteOneChar(unsigned char dat)//写一个字节
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delay(2);
		DQ = 1;
		dat>>=1;
	}
}

/******************************************************************************/
void ReadTemperature(void)//读取温度
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned char Data_L=0;
	unsigned char num=0;
	Init_DS18B20();
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作
	WriteOneChar(0xBE); //读取温度寄存器
//	Delay(5000);
	a=ReadOneChar();  //读低8位
	b=ReadOneChar(); //读高8位

    tx[0] = (a/16+b*16)/10;      //整数部分


	tx[1] = (a/16+b*16)%10; 

    Data_L=a&0X0F;
     for(num=3;num<7;num++)		 //小数部分
   {
      Data_L=Data_L*10;				 //10	   //100		//40		 //80
     tx[num]=Data_L/16;			 //0	  //6			//2			 //5
      Data_L=Data_L%16;				 //10	   //4			//8
	}

}
/******************************************************************************/
void Int_232(void)	//232初始化
{
  TMOD=0x20;
  SCON=0x50;
  TH1=0xFD;
  TL1=0xFD;
  TR1=1;
  TI=0;
}

void Display_SMG(void)
{
   unsigned char a;
   for(a=0;a<=50;a++)
   {
   P0=table[tx[0]];
   P2_0 = 0;
   Delaynms(5);
   P2_0 = 1;

   P0=(table[tx[1]])&0x7f;
   P2_1 = 0;
   Delaynms(5);
   P2_1 = 1;

   P0=table[tx[3]];
   P2_2 = 0;
   Delaynms(5);
   P2_2 = 1;

    P0=table[tx[4]];
   P2_3 = 0;
   Delaynms(5);
   P2_3 = 1;
   }
}

/******************************************************************************/

void main(void)
{  	
 
  Int_232();


while(1)
{  

	ReadTemperature();	 //读取温度
//	TX(tx[0]+0x30);
//	TX(tx[1]+0x30);
//	TX(tx[2]);			//点
//	TX(tx[3]+0x30);
//	TX(tx[4]+0x30);
//	TX(tx[5]+0x30);
//	TX(tx[6]+0x30);	TX(tx[7]);
//	TX(tx[8]);
//	TX(tx[9]);
	Display_SMG();

//	Delaynms(2000);
} 	



}
