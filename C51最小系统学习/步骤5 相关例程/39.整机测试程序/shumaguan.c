/*�˳������ʵ�֣��������ʾ1234��״̬���û������Լ�����ǰ�ߵ�����������б�д����ĳ������ʱ���������ʾĳ������*/
#include <reg52.h>
#define uchar unsigned char 
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x00};		//�����

uchar code table1[]={0xfc,0xf9,0xf3,0xe7,0xcf,0x9f,0x3f};      			    //��ˮ�������

uchar  buff[3]={0};

void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}



void display()
{ 
   P0=table[buff[0]];		//
   P2_0 = 0;
   delay(5);
   P2_0 = 1;

   P0=table[buff[0]];
   P2_1 = 0;
   delay(5);
   P2_1 = 1;

   P0=table[buff[0]];
   P2_2 = 0;
   delay(5);
   P2_2 = 1;

    P0=table[buff[0]];
   P2_3 = 0;
   delay(5);
   P2_3 = 1;
   
}



void KEY_SER()
{
  if(P2_4==0)
  {
     display();
     while(P2_4==0)   display();
     if(++buff[0]>=9)buff[0]=0;
   }
   if(P2_5==0)
  {
     display();
     while(P2_5==0)   display();
     if(++buff[0]>=9)buff[0]=0;
   }
   if(P2_6==0)
  {
     display();
     while(P2_6==0)   display();
     if(++buff[0]>=9)buff[0]=0;
   }
   if(P2_7==0)
  {
     display();
     while(P2_7==0)   display();
     if(++buff[0]>=9)buff[0]=0;
   }
}

/*��ʾ������*/
void main(void)
{
    unsigned int  a=0;
	unsigned char b=0;

	P1=0x00;	 //LEDȫ��
	buff[0]=10;  //ȫ��

    for(a=255;a>0;a--)
   {
     display();
   }

 	buff[0]=0;  //ȫ��ʾ0��  
 while(1)
 {
 
   for(a=80;a>0;a--)
   {
     display();
	 KEY_SER();
   }
   P1=table1[b];
   if(++b>=7)b=0;
 }					 
}