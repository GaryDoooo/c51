/*此程序可以实现，流水灯第1和2亮，稍作延时后流水灯第3和4亮；然后流水灯第5和6亮；
  然后流水灯第7和8亮，这样一直循环亮灭*/
#include <reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

uchar code table[]={0xfc,0xf9,0xf3,0xe7,0xcf,0x9f,0x3f};                      

void delay(uint i)
{
  uint j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void display()
{
   uchar i;
   for(i=0;i<7;i++)
   {
      P1=table[i];
      delay(1000);
   }
  
}

/*演示主程序*/
void main(void)
{
    unsigned int  a;
   
 while(1)
 {
 
   for(a=100;a>0;a--)
   {
     display();
   }
 
 }
}