 

/*============================================================== 
SMC1602A(16*2)模拟口线接线方式
连接线图: 
---------------------------------------------------
|LCM-----51 　| LCM-----51　　|　LCM------51 |
---------------------------------------------|
|DB0-----P1.7 | DB4-----P1.3 | RW-------P2.4 |
|DB1-----P1.6 | DB5-----P1.2 | RS-------P2.3 |
|DB2-----P1.5 | DB6-----P1.1 | E--------P2.5 |
|DB3-----P1.4 | DB7-----P1.0 | VLCD接1K电阻到GND|
---------------------------------------------------


[注:AT89S51使用12M晶振]
=============================================================*/

#define LCM_RW   P2_4 //定义引脚
#define LCM_RS   P2_3
#define LCM_E    P2_5
#define LCM_Data P0
#define Busy 0x01 //用于检测LCM状态字中的Busy标识
#include <at89x51.h>
void WriteDataLCM    (unsigned char WDLCM);
void WriteCommandLCM (unsigned char WCLCM,BuysC);
void DisplayOneChar  (unsigned char X, unsigned char Y, unsigned char DData);
void DisplayListChar (unsigned char X, unsigned char Y, unsigned char code *DData);
unsigned char ReadDataLCM(void);
unsigned char ReadStatusLCM(void);

void pro_timedate(void);
bit leap_year(); //判断是否为闰年
unsigned char data year=11,month=5,date=22;//年、月、日、星期
unsigned char disbuf[16];
unsigned char data hour=23,min=59,sec=55,sec20=0; //时、分、秒、百分之一秒
unsigned char code email[] = {"YEA:MON:DAT:TIME"};
void updatetime (void);
void LCMInit    (void);
void pro_display(void);
void Delay400Ms (void);
void Delay5Ms   (void);
void main(void)
{
     Delay400Ms(); //启动等待，等LCM讲入工作状态
     LCMInit(); //LCM初始化
	 DisplayListChar(0, 1, email);
     TMOD=0X01;
     TH0=0X4C;
     TL0=0X00;
     TR0=1;
     ET0=1;
     EA=1;
     while(1);
}

void pro_timedate()
     {
       sec++;
        if(sec > 59)
               {sec = 0;
                     min++;
                        if(min>59)
                              {min=0;
                                  hour++;
                                    if(hour>23)
                                         {hour=0;
                                             date++;
         if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
         if (date>31)
		          {date=1;month++;} //大月31 天
         if (month==4||month==6||month==9||month==11)
         if (date>30) 
		          {date=1;month++;} //小月30 天
         if (month==2)
                   {if( leap_year()) //闰年的条件
                   {if (date>29) {date=1;month++;}} //闰年2 月为29 天
                     else
                   {if (date>28) {date=1;month++;}} //平年2 月为28 天
                   }
            if (month>12) {month=1;year++;}
            if (year>99) year=0;
                                        }
                             }
               }

	 }

bit leap_year()
{
       bit leap;
       if((year%4==0&&year%100!=0)||year%400==0)//闰年的条件
       leap=1;
       else
       leap=0;
       return leap;
}
//Timer0 中断处理程序,秒的产生
void timer0() interrupt 1
{
     TH0=0x4C; //Timer0 置10ms 定时初值dc00H(2^16=65536D,dc00H=56320D)
     TL0=0x00; //定时时间=(65536-56320)*(1/11.0592)*12=10ms (f0=11.0592Mhz)
     sec20++;      
     if(sec20 >= 20) //1 秒时间 (100*10ms=1000ms=1s)
          { sec20=0;
		    updatetime  (); 	
		    pro_timedate(); 
		    pro_display ();
			if(sec&0x01)
		    disbuf[13]=' ';
			else disbuf[13]=':';
		  }
}



void updatetime(void)
    {   disbuf[0] ='2';
		disbuf[1] ='0';
		disbuf[2] =year/10+48;
		disbuf[3] =year%10+48;
		disbuf[4] =' ';
		disbuf[5] =month/10+48;
		disbuf[6] =month%10+48;
		disbuf[7] ='.';
		disbuf[8] =date/10+48;
		disbuf[9] =date%10+48;
		disbuf[10] =' ';
        disbuf[11]=hour/10+48;
        disbuf[12]=hour%10+48;
		//disbuf[13]=' ';
        disbuf[14]=min/10+48;
        disbuf[15]=min%10+48;
	}
//显示处理程序
void pro_display()
{ unsigned char f;
   for (f=0;f<=15;f++)
   {DisplayOneChar( f,  0,  disbuf[f]);}
   
}
//写数据
void WriteDataLCM(unsigned char WDLCM)
{
ReadStatusLCM(); //检测忙
WDLCM = ((WDLCM&0x01)<<7)|((WDLCM&0x02)<<5)|((WDLCM&0x04)<<3)|((WDLCM&0x08)<<1)|((WDLCM&0x10)>>1)|((WDLCM&0x20)>>3)|((WDLCM&0x40)>>5)|((WDLCM&0x80)>>7);
LCM_Data = WDLCM;
LCM_RS = 1;
LCM_RW = 0;
LCM_E = 0; //若晶振速度太高可以在这后加小的延时
LCM_E = 0; //延时
LCM_E = 1;
}

//写指令
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
if (BuysC) ReadStatusLCM(); //根据需要检测忙
WCLCM = ((WCLCM&0x01)<<7)|((WCLCM&0x02)<<5)|((WCLCM&0x04)<<3)|((WCLCM&0x08)<<1)|((WCLCM&0x10)>>1)|((WCLCM&0x20)>>3)|((WCLCM&0x40)>>5)|((WCLCM&0x80)>>7);
LCM_Data = WCLCM;

LCM_RS = 0;
LCM_RW = 0; 
LCM_E = 0;
LCM_E = 0;
LCM_E = 1; 
}

//读数据
unsigned char ReadDataLCM(void)
{
LCM_RS = 1; 
LCM_RW = 1;
LCM_E = 0;
LCM_E = 0;
LCM_E = 1;
return(LCM_Data);
}

//读状态
unsigned char ReadStatusLCM(void)
{
LCM_Data = 0xFF; 
LCM_RS = 0;
LCM_RW = 1;
LCM_E = 0;
LCM_E = 0;
LCM_E = 1;
while (LCM_Data & Busy); //检测忙信号
return(LCM_Data);
}

void LCMInit(void) //LCM初始化
{
LCM_Data = 0;
WriteCommandLCM(0x38,0); //三次显示模式设置，不检测忙信号
Delay5Ms(); 
WriteCommandLCM(0x38,0);
Delay5Ms(); 
WriteCommandLCM(0x38,0);
Delay5Ms(); 

WriteCommandLCM(0x38,1); //显示模式设置,开始要求每次检测忙信号
WriteCommandLCM(0x08,1); //关闭显示
WriteCommandLCM(0x01,1); //显示清屏
WriteCommandLCM(0x06,1); // 显示光标移动设置
WriteCommandLCM(0x0C,1); // 显示开及光标设置
}

//按指定位置显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
Y &= 0x1;
X &= 0xF; //限制X不能大于15，Y不能大于1
if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
X |= 0x80; //算出指令码
WriteCommandLCM(X, 0); //这里不检测忙信号，发送地址码
WriteDataLCM(DData);
}
//按指定位置显示一串字符
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
unsigned char ListLength;
ListLength = 0;
Y &= 0x1;
X &= 0xF;         //限制X不能大于15，Y不能大于1
while (DData[ListLength]>0x20) //若到达字串尾则退出
{
if (X <= 0xF) //X坐标应小于0xF
{
DisplayOneChar(X, Y, DData[ListLength]); //显示单个字符
ListLength++;
X++;
}
}
}
//50ms延时
void Delay5Ms(void)
{
unsigned int TempCyc = 5552;
while(TempCyc--);
}

//400ms延时
void Delay400Ms(void)
{
unsigned char TempCycA = 5;
unsigned int TempCycB;
while(TempCycA--)
{
TempCycB=7269;
while(TempCycB--);
};
}
 
 