/*�˳������ʵ�֣���ˮ�Ƶ�1��2����������ʱ����ˮ�Ƶ�3��4����Ȼ����ˮ�Ƶ�5��6����
  Ȼ����ˮ�Ƶ�7��8��������һֱѭ������*/
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

/*��ʾ������*/
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