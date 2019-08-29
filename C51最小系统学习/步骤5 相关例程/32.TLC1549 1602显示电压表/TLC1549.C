
/*本程序为10位AD TLC1549。1602显示读内部电位器分压请J20跳线往左插*/
/*如果外部电压输入请把J20跳线往右插*******************************/
/*最大输入电压0-5V。。程序扩大10倍如需正常显示请修改相应程序******/

#include <reg52.h>    //52系列头文件
#define Disdata P0    //液晶数据端口
#define uchar unsigned char    //无符号字符8位
#define uint  unsigned int //无符号整数8位
uint data dis[4]={0x00,0x00,0x00,0x00};//4个数据单元和一个
uchar code table[]="VOLTAGE:+  .   V"; //定义初始上电液晶默认显示状态
uchar code table1[]="designed by :";
uchar code table3[]="MUCSTUDIO";
uchar code table2[]="SCOPE:  0-50.00V";


sbit  lcden=P2^5;//定义液晶使能端
sbit  lcdrs=P2^3;//定义液晶RS端
sbit  rw   =P2^4;//定义液晶RW端

sbit  cs_ad=P1^3;//片选段，低电平有效
sbit  dout =P1^6;//数据输出端
sbit  clk  =P1^7;  //转换结束标志位

data  int result;//测量变量暂存地址

uchar num,num1,num2,num3,num4,num5;
uchar shii,gei;

//********延时函数************
void delay(uint z)
{
   uint x,y;
    for(x=z;x>0;x--)
    for(y=110;y>0;y--);
}
   
//*************
void write_com(uchar com)          //液晶写命令函数
{
  lcdrs=0;
  P0 = ((com&0x01)<<7)|((com&0x02)<<5)|((com&0x04)<<3)|((com&0x08)<<1)|((com&0x10)>>1)|((com&0x20)>>3)|((com&0x40)>>5)|((com&0x80)>>7);
  delay(5);
  lcden=1;
  delay(5);
  lcden=0;
 }
 void write_data(uchar date)        //液晶写数据函数
 {
   lcdrs=1;
   P0 = ((date&0x01)<<7)|((date&0x02)<<5)|((date&0x04)<<3)|((date&0x08)<<1)|((date&0x10)>>1)|((date&0x20)>>3)|((date&0x40)>>5)|((date&0x80)>>7);
   delay(5);
   lcden=1;
   delay(5);
   lcden=0;
 }
void write_sg(uchar add,uchar date)//写整数位和小数位函数
{
   uchar shi,ge;
   shi=date/10;                    //分解出一个2位数的十位
   ge= date%10;
   write_com(0x80+add);            //设置显示位置
   write_data(0x30+shi);           //送去液晶显示十位
   write_data(0x30+ge);            //送去液晶显示个位
}

void init()                                        
{
     rw=0;                                                   
     lcden=0;
     shii=0;
     gei=0;
     write_com(0x38);     //初始化1602液晶
     write_com(0x0c);
     write_com(0x06);
     write_com(0x01);
     write_com(0x80);     //设置显示初始坐标

 for(num2=0;num2<13;num2++)
  {
    write_data(table1[num2]);
    delay(5);
  } 
 write_com(0x80+40);     
   for(num3;num3<16;num3++)
   {
     write_data(table3[num3]);
     delay(5);
   }
     delay(3000);
 
 }

 //*******************************
void scan1()
{
   write_com(0x80);              //设置显示初始坐标
  for(num=0;num<16;num++)
  {
    write_data(table[num]);
    delay(5);
  } 
    write_sg(9,shii);                                        
    write_sg(12,gei);
    write_com(0x80+40);     
   for(num1;num1<16;num1++)
   {
     write_data(table2[num1]);
     delay(5);
   }
     write_sg(9,shii);
     write_sg(12,gei);
 }
   
//*********************************TLC1549转换处理子函数****************************************

void test()

{ 
     data  uchar i;
     cs_ad=1;                    //禁止i/o clock
     cs_ad=0;                    //开启控制电路，使能data out和i/o clock
     result=0;                   //清转换变量
     for(i=0;i<10;i++)           //采集10次 ，即10bit
       { 
          clk=0;
          result*=2;
          if(dout) result++;
          clk=1;
        }
     delay(590);
     cs_ad=1; ;;;; //data out 返回到高阻状态而终止序列
//**********************************数据转换处理**************************************************
     result=result*10;     //结果值扩大10倍
     dis[2]=result/205;    //计算整数位
     dis[3]=result%205;    //余数暂存
     dis[3]=dis[3]*10;     //计算小数第一位
     dis[1]=dis[3]/205;                                   
     dis[3]=dis[3]%205;                   
     dis[3]=dis[3]*10;     //计算小数第二位
     dis[0]=dis[3]/205;
     shii=dis[2];
     gei=dis[1]*10+dis[0];
     write_sg(9,shii);
     write_sg(12,gei);
}  
//************************************主函数******************************************************
void main()
{
     init();
     scan1();
     while(1)
  {
     test(); 
   } 
}
 
 
 
 
