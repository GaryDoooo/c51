#include <AT89X51.H>
#include <STDIO.H>
#include <math.h>
void  main(void)
{float x,y,z;
 SCON=0x50;
 TMOD=0x20;
 TH1=0xE8;
 TL1=0xE8;
 TI=1;
 TR1=1;

 while(1)
    {  printf("��ã����ǵ�Ƭ��STC89C516RC+���һ��������⣡\n");
	   printf("������������X��Y\n");
	   scanf("%f,%f",&x,&y);
	   z=x*y;
	   printf("\n");
	   printf("z=%f\n",z);  

    }
}



