#include "8051.h"
//#include <intrins.h>
#include <stdlib.h>
#define   uchar unsigned char   /*�궨Ҷ嶨*/
#define   uint   unsigned int

uchar buffer_pointer;
unsigned char ReData,SenData,sending_data;

void rs232init()
{
                SCON = 0x50;      //REN=1Աʱб���бнӽʽܽ״̬�����ڹ� �ģʽ1 
            TMOD|= 0x20;      //��ʱƱ���ױ���ʽ2
                PCON|= 0x80;
                TH1  = 0xFD;   
        TL1 = 0xF3;    
                ES   = 1;        //�������ж϶                  
                EA   = 1;        // �����ж϶
                PS = 8; //serial port priority =1
                TR1  = 1;
}
void send232(uchar send_number)
{
                if(buffer_pointer<32) buffer_pointer++;

                SenData = send_number;
}

void buffer_send()
{
          if ((buffer_pointer>=1) && (sending_data ==0) &&(TI==0) )
          {
             //SBUF= *( send_buffer + buffer_pointer);               //SUBF�ӱʱܱ/��˱ͻ���ƻ�
                 SBUF = SenData;
                 sending_data=1;
                 buffer_pointer--;
                /*while(TI==0);
         TI=0;
                 buffer_pointer--; */
          }

        if( (sending_data==1)&&(TI!=0)) 
                {sending_data=0; TI=0;}  //check if data sent, init the status
}

main()
{

  rs232init();

  while(1)
  {

        buffer_send(); //send the data in rs232 buffer out.     
   }

 }
/****************************************************
               �����жϳ̳г�
******************************************************/
void ser_int (void) __interrupt 4 __using 1
{
 if(RI == 1)        //RI�����жϱ�־
 {
        RI = 0;             //����RI�����жϱ�־
        ReData = SBUF;  //SUBF����/���ͻ���ƻ�
        //SenData=ReData;
        //buffer_pointer=1;
        send232(ReData);
        P1=ReData;
 }
}



