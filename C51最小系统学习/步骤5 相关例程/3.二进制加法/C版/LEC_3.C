/********************************************************************************
;                  二进制加法试验												*
; p1口八个灯作二进制加法。理解二进值的计算                                  	*
; 硬件连接：p1口8路指示灯														*
;																				*                   *
*********************************************************************************/
#include <reg52.h>
void delay(unsigned int i);  //声明延时函数


main()
{ 
  unsigned char Num = 0xff;
  while (1) 
  {P1  = Num;
   delay(1000);	   //延时函数
   Num--;
   }
 
}


/*******延时函数*************/
void delay(unsigned int i)
{
    unsigned char j;
    for(i; i > 0; i--)
        for(j = 255; j > 0; j--);

}



