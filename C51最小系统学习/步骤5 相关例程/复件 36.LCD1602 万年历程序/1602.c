 

/*============================================================== 
SMC1602A(16*2)ģ����߽��߷�ʽ
������ͼ: 
---------------------------------------------------
|LCM-----51 ��| LCM-----51����|��LCM------51 |
---------------------------------------------|
|DB0-----P1.7 | DB4-----P1.3 | RW-------P2.4 |
|DB1-----P1.6 | DB5-----P1.2 | RS-------P2.3 |
|DB2-----P1.5 | DB6-----P1.1 | E--------P2.5 |
|DB3-----P1.4 | DB7-----P1.0 | VLCD��1K���赽GND|
---------------------------------------------------


[ע:AT89S51ʹ��12M����]
=============================================================*/

#define LCM_RW   P2_4 //��������
#define LCM_RS   P2_3
#define LCM_E    P2_5
#define LCM_Data P0
#define Busy 0x01 //���ڼ��LCM״̬���е�Busy��ʶ
#include <at89x51.h>
void WriteDataLCM    (unsigned char WDLCM);
void WriteCommandLCM (unsigned char WCLCM,BuysC);
void DisplayOneChar  (unsigned char X, unsigned char Y, unsigned char DData);
void DisplayListChar (unsigned char X, unsigned char Y, unsigned char code *DData);
unsigned char ReadDataLCM(void);
unsigned char ReadStatusLCM(void);

void pro_timedate(void);
bit leap_year(); //�ж��Ƿ�Ϊ����
unsigned char data year=11,month=5,date=22;//�ꡢ�¡��ա�����
unsigned char disbuf[16];
unsigned char data hour=23,min=59,sec=55,sec20=0; //ʱ���֡��롢�ٷ�֮һ��
unsigned char code email[] = {"YEA:MON:DAT:TIME"};
void updatetime (void);
void LCMInit    (void);
void pro_display(void);
void Delay400Ms (void);
void Delay5Ms   (void);
void main(void)
{
     Delay400Ms(); //�����ȴ�����LCM���빤��״̬
     LCMInit(); //LCM��ʼ��
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
		          {date=1;month++;} //����31 ��
         if (month==4||month==6||month==9||month==11)
         if (date>30) 
		          {date=1;month++;} //С��30 ��
         if (month==2)
                   {if( leap_year()) //���������
                   {if (date>29) {date=1;month++;}} //����2 ��Ϊ29 ��
                     else
                   {if (date>28) {date=1;month++;}} //ƽ��2 ��Ϊ28 ��
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
       if((year%4==0&&year%100!=0)||year%400==0)//���������
       leap=1;
       else
       leap=0;
       return leap;
}
//Timer0 �жϴ������,��Ĳ���
void timer0() interrupt 1
{
     TH0=0x4C; //Timer0 ��10ms ��ʱ��ֵdc00H(2^16=65536D,dc00H=56320D)
     TL0=0x00; //��ʱʱ��=(65536-56320)*(1/11.0592)*12=10ms (f0=11.0592Mhz)
     sec20++;      
     if(sec20 >= 20) //1 ��ʱ�� (100*10ms=1000ms=1s)
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
//��ʾ�������
void pro_display()
{ unsigned char f;
   for (f=0;f<=15;f++)
   {DisplayOneChar( f,  0,  disbuf[f]);}
   
}
//д����
void WriteDataLCM(unsigned char WDLCM)
{
ReadStatusLCM(); //���æ
WDLCM = ((WDLCM&0x01)<<7)|((WDLCM&0x02)<<5)|((WDLCM&0x04)<<3)|((WDLCM&0x08)<<1)|((WDLCM&0x10)>>1)|((WDLCM&0x20)>>3)|((WDLCM&0x40)>>5)|((WDLCM&0x80)>>7);
LCM_Data = WDLCM;
LCM_RS = 1;
LCM_RW = 0;
LCM_E = 0; //�������ٶ�̫�߿���������С����ʱ
LCM_E = 0; //��ʱ
LCM_E = 1;
}

//дָ��
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysCΪ0ʱ����æ���
{
if (BuysC) ReadStatusLCM(); //������Ҫ���æ
WCLCM = ((WCLCM&0x01)<<7)|((WCLCM&0x02)<<5)|((WCLCM&0x04)<<3)|((WCLCM&0x08)<<1)|((WCLCM&0x10)>>1)|((WCLCM&0x20)>>3)|((WCLCM&0x40)>>5)|((WCLCM&0x80)>>7);
LCM_Data = WCLCM;

LCM_RS = 0;
LCM_RW = 0; 
LCM_E = 0;
LCM_E = 0;
LCM_E = 1; 
}

//������
unsigned char ReadDataLCM(void)
{
LCM_RS = 1; 
LCM_RW = 1;
LCM_E = 0;
LCM_E = 0;
LCM_E = 1;
return(LCM_Data);
}

//��״̬
unsigned char ReadStatusLCM(void)
{
LCM_Data = 0xFF; 
LCM_RS = 0;
LCM_RW = 1;
LCM_E = 0;
LCM_E = 0;
LCM_E = 1;
while (LCM_Data & Busy); //���æ�ź�
return(LCM_Data);
}

void LCMInit(void) //LCM��ʼ��
{
LCM_Data = 0;
WriteCommandLCM(0x38,0); //������ʾģʽ���ã������æ�ź�
Delay5Ms(); 
WriteCommandLCM(0x38,0);
Delay5Ms(); 
WriteCommandLCM(0x38,0);
Delay5Ms(); 

WriteCommandLCM(0x38,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
WriteCommandLCM(0x08,1); //�ر���ʾ
WriteCommandLCM(0x01,1); //��ʾ����
WriteCommandLCM(0x06,1); // ��ʾ����ƶ�����
WriteCommandLCM(0x0C,1); // ��ʾ�����������
}

//��ָ��λ����ʾһ���ַ�
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
Y &= 0x1;
X &= 0xF; //����X���ܴ���15��Y���ܴ���1
if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
X |= 0x80; //���ָ����
WriteCommandLCM(X, 0); //���ﲻ���æ�źţ����͵�ַ��
WriteDataLCM(DData);
}
//��ָ��λ����ʾһ���ַ�
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
unsigned char ListLength;
ListLength = 0;
Y &= 0x1;
X &= 0xF;         //����X���ܴ���15��Y���ܴ���1
while (DData[ListLength]>0x20) //�������ִ�β���˳�
{
if (X <= 0xF) //X����ӦС��0xF
{
DisplayOneChar(X, Y, DData[ListLength]); //��ʾ�����ַ�
ListLength++;
X++;
}
}
}
//50ms��ʱ
void Delay5Ms(void)
{
unsigned int TempCyc = 5552;
while(TempCyc--);
}

//400ms��ʱ
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
 
 