/*此程序可以实现，按开关S10,流水灯第1和2亮，按开关S9,流水灯第3和4亮；按开关S8,流水灯第5和6亮；
  按开关S2,流水灯第7和8亮*/
#include <reg52.h>
#define uchar unsigned char 
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;

void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void display()
{
   if(P2_7 == 0)
   {
      delay(10);//延时去抖动
	  if(P2_7 == 0)
      {
         P1_0 = 0;
         P1_1 = 0;
      }
   }
   if(P2_6 == 0)
   {
      delay(10);//延时去抖动
	  if(P2_6 == 0)
      {
         P1_2 = 0;
         P1_3 = 0;
      }
   }
   if(P2_5 == 0)
   {
      delay(10);//延时去抖动
	  if(P2_5 == 0)
      {
         P1_4 = 0;
         P1_5 = 0;
      }
   }
   if(P2_4 == 0)
   {
      delay(10);//延时去抖动
	  if(P2_4 == 0)
      {
         P1_6 = 0;
         P1_7 = 0;
      }
   }
}

/*演示主程序*/
void main(void)
{
    unsigned int  a;
   P2_7 = 1; P2_6 = 1; P2_5 = 1; P2_4 = 1; // 按键端口设置为输入
 while(1)
 {
 
   for(a=100;a>0;a--)
   {
     display();
   }
 
 }
}