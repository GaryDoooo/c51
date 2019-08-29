

        #define tByte unsigned char
        #define tWord unsigned int
		#define tLong unsigned long
		#include <reg51.h>
		sbit  FSYNC=P0^2;
		sbit  SCLK =P0^1;
		sbit  SDATA=P0^0;
		tWord Config_Data[8];
		void  Wave_Generate(tLong,tByte);

		void main(void)
		{

  		FSYNC=1;
  		SCLK=0;
  		Wave_Generate(5,2);
  		while(1) ;

		}

		//向ad9833写一命令字(2Bytes)

		void AD9833_Send_Word(tWord Data_In)

{

   		tByte i;
   		SCLK=1;
   		FSYNC=0;
   		for(i=0;i<16;i++)

   		{

     	SCLK=1;
     	SDATA=(bit)((Data_In & 0x8000)>>15);
     	SCLK=0;
     	Data_In=Data_In<<1;

   		}
   		FSYNC=1;
   		SCLK=0;
}





//波形发生函数

//入口参数: 频率:Freq (<=12000000)

//          形状:0(正弦波),1(三角波),2(方波)

//默认: Fmclk=25MHz, 0相移，方波不分频.

		void  Wave_Generate(tLong Freq,tByte Shape)
{

   		tLong temp;
   		tByte k;
   		if(Freq>12000000) Freq=12000000;
   		switch(Shape)
   		{
     case 0: Config_Data[0]=0x2108;
             Config_Data[7]=0x2008;
             break;
     case 1: Config_Data[0]=0x210A;
             Config_Data[7]=0x200A;
             break;
     case 2: Config_Data[0]=0x2128;
             Config_Data[7]=0x2028;
             break;
     default:Config_Data[0]=0x2108;
             Config_Data[7]=0x2008;

   		}



   		temp=Freq*10.73;   //temp=Freq*(0x10000000/20000000);
   		Config_Data[1]=temp&0x00003fff;
   		Config_Data[3]=Config_Data[1];
   		Config_Data[2]=(temp&0x0fffc000)>>14;
   		Config_Data[4]=Config_Data[2];
   		Config_Data[1]=Config_Data[1]|0x4000;
   		Config_Data[2]=Config_Data[2]|0x4000;
   		Config_Data[3]=Config_Data[3]|0x8000;
   		Config_Data[4]=Config_Data[4]|0x8000;
   		Config_Data[5]=0xC000;
   		Config_Data[6]=0xE000;



   		for(k=0;k<8;k++)

  		{
     	AD9833_Send_Word(Config_Data[k]);
  		}



}









