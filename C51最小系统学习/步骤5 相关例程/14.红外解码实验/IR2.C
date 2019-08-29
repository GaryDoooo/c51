/*程序说明： 
51单片机红外遥控解码程序
单片机采用外部中断INTI管脚和红外接收头的信号线相连，
中断方式为边沿触发方式。并用定时器0计算中断的间隔时间，
来区分前导码、二进制的1,0;8位操作码提取出来在数码管上显示。
 
解码值在Im[2]中，当IrOK=1时解码有效。 
用遥控器对准红外接收头，按下遥控器按键，在数码管的两位上就会显示对应按键的编码
*/
#include <reg52.h>
#define uchar unsigned char 
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
//sbit dula=P2^6;
//sbit wela=P2^7;
/*uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};*/
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,
                        0xf8,0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e};
uchar f;

#define Imax 14000    //此处为晶振为11.0592时的取值, 
#define Imin 8000    //如用其它频率的晶振时,
#define Inum1 1450    //要改变相应的取值。
#define Inum2 700 
#define Inum3 3000 

unsigned char Im[4]={0x00,0x00,0x00,0x00};
uchar show[2]={0,0};
unsigned long m,Tc;
unsigned char IrOK;


void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void display()
{
   P2_0 = 0;P2_1 = 1;P2_2 = 1;P2_3 = 1;
   P0=table[show[0]];
   delay(2);

   P2_0 = 1;P2_1 = 0;P2_2 = 1;P2_3 = 1;
   P0=table[show[1]];
   delay(2);

  /* dula=0;
   P0=table[show[1]];
   dula=1;
   dula=0;
   
   wela=0;
   P0=0xfd;
   wela=1;
   wela=0;
   delay(5);
   
   P0=table[show[0]];
   dula=1;
   dula=0;
   
   P0=0xfe;
   wela=1;
   wela=0;
   delay(5);*/
}


//外部中断解码程序
void intersvr1(void) interrupt 2 using 1
{
 Tc=TH0*256+TL0;                                               //提取中断时间间隔时长
 TH0=0; 
    TL0=0;              //定时中断重新置零
 if((Tc>Imin)&&(Tc<Imax))
      { 
  m=0;
        f=1;
  return;
      }       //找到启始码
   if(f==1)
      {
        if(Tc>Inum1&&Tc<Inum3) 
    {
   Im[m/8]=Im[m/8]>>1|0x80; m++; 
       }
      if(Tc>Inum2&&Tc<Inum1) 
        {
         Im[m/8]=Im[m/8]>>1; m++; //取码
  }
  if(m==32) 
   {
         m=0;  
         f=0;
         if(Im[2]==~Im[3]) 
      {
           IrOK=1; 
   }
        else IrOK=0;   //取码完成后判断读码是否正确
     }
               //准备读下一码
   }
 
}


/*演示主程序*/
void main(void)
{
    unsigned int  a;
   
 m=0;
    f=0;
 EA=1;
 
 IT1=1;EX1=1;
 
 TMOD=0x11;  
 TH0=0;TL0=0;
 TR0=1;//ET0=1;

 while(1)
 {
 
       if(IrOK==1) 
  {
      show[1]=Im[2] & 0x0F;     //取键码的低四位
           show[0]=Im[2] >> 4;  
           IrOK=0;
     
  }
           for(a=100;a>0;a--)
          {
    display();
   }
 
 }
}

