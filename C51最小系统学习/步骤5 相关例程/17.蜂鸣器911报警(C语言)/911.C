
                   
#include <reg51.h>
#include <intrins.h>

sbit	SPK = P3^7;

unsigned char frq; 

void delayms(unsigned char ms);

main()
{
	TMOD = 0x01;
	frq = 0x00;
	TH0 = 0x00;
	TL0 = 0xff;	
	TR0 = 1;
	IE = 0x82;
	
	while(1)
	{
		frq++;
		delayms(1);
	}
}

void timer0() interrupt 1 using 1
{
	TH0 = 0xfe;
	TL0 = frq;
	SPK = ~SPK;	
}

void delayms(unsigned char ms)	
// ÑÓÊ±×Ó³ÌÐò
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 120; i++);
	}
}