//working with 12c5a60s2
#include "8051.h"
//#include <intrins.h>
#include <stdlib.h>
#define   uchar unsigned char   /*�궨��*/
#define   uint   unsigned int
//extern void Delay1us(unsigned char );

#define SDA P1_6             /*ģ��I2C���ݴ���λ*/
#define SCL P1_7              /*ģ��I2Cʱ�ӿ���λ*/
__bit ack;            /*Ӧ���־λ*/

unsigned char timer1,duty,switching, timer2, timer2_goal, timer2_4switch,sending_data; 
//unsigned char send_buffer;  //rs232 sending buffer

uchar buffer_pointer;
unsigned char ReData,SenData;

uchar I2C_mode_codes[4]={0,6,12,15};
uchar current_mode;
uchar duty4modes[4]={0,3,3,3};

uint time_out232;
uchar received232;
uchar have232connected;

//__sbit PWM=P1^1;
#define GoHaze P0_6
#define GoClear P0_7
#define PWM1   P0_1
#define PWM2   P0_2

__sfr P0M0    = 0x94;
__sfr P0M1    = 0x93;
__sfr P1M0    = 0x91;
__sfr P1M1    = 0x92;

__sfr T2MOD = 0xc9;

/////////////////////////// start I2C ////////////////////////

void Delay1us(uchar time_length)
{
uchar i;
for(i=0;i<time_length;i++);
}

/*******************************************************************
                      �����ߺ���               
����ԭ��: void   Start_I2c();  
����:      ����I2C����,������I2C��ʼ����.  
********************************************************************/
void Start_I2c()
{
   SDA=1;     /*������ʼ�����������ź�*/
   Delay1us(1);
   SCL=1;
   Delay1us(5);      /*��ʼ��������ʱ�����4.7us,��ʱ*/
   
   SDA=0;     /*������ʼ�ź�*/
   Delay1us(5);      /* ��ʼ��������ʱ�����4��s*/
        
   SCL=0;     /*ǯסI2C���ߣ�׼�����ͻ�������� */
   Delay1us(2);
}

/*******************************************************************
                       �������ߺ���               
����ԭ��: void   Stop_I2c();  
����:      ����I2C����,������I2C��������.  
********************************************************************/
void Stop_I2c()
{
   SDA=0;    /*���ͽ��������������ź�*/
   Delay1us(1);     /*���ͽ���������ʱ���ź�*/
   SCL=1;    /*������������ʱ�����4us*/
   Delay1us(5);
  
   SDA=1;    /*����I2C���߽����ź�*/
   Delay1us(4);

}
/*******************************************************************
                  �ֽ����ݷ��ͺ���               
����ԭ��: void   SendByte(uchar c);
����:      ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
           ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0)     
         ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void   SendByte(uchar c)
{
uchar BitCnt;

for(BitCnt=0;BitCnt<8;BitCnt++)   /*Ҫ���͵����ݳ���Ϊ8λ*/
     {
      if((c<<BitCnt)&0x80)SDA=1;    /*�жϷ���λ*/
        else   SDA=0;               
      Delay1us(1);

      SCL=1;                /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/      
      Delay1us(5);              /*��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/
            
      SCL=0;
     }
   
     Delay1us(2);
     SDA=1;                 /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
     Delay1us(2);   
     SCL=1;
     Delay1us(3);
     if(SDA==1)ack=0;     
        else ack=1;         /*�ж��Ƿ���յ�Ӧ���ź�*/
     SCL=0;
     Delay1us(20);
}

/*******************************************************************
                     �����ӵ�ַ�������Ͷ��ֽ����ݺ���               
����ԭ��: bit   ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
����:      ���������ߵ����͵�ַ���ӵ�ַ,���ݣ��������ߵ�ȫ����,������
           ��ַsla���ӵ�ַsuba������������sָ������ݣ�����no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺     ʹ��ǰ�����ѽ������ߡ�

Removed the address part, and just changed it to single byte sending
********************************************************************/
__bit ISendStr(uchar s)
{

    Start_I2c();                /*��������*/
      SendByte(0xe0);             /*��������*/
      //if(ack==0)return(0);
      SendByte(s);             /*��������*/
      //if(ack==0)return(0);
// Need uncomment the ack bit when connected

    Stop_I2c();                 /*��������*/

    return(1);
}
////////////////////////// end for I2C //////////////////////

void system_Ini()
{

	duty=5;	  // Init the backlight as off, PWM positive duty in 20%
	timer1=0; //timer for PWM
	switching=0; //status of in process of switching
	timer2=0; //timer for switching black frame
	timer2_goal = 0; //timer2 length setting
	sending_data =0; // if send data thru rs232
	buffer_pointer = 0; //if data received from rs232
		
	timer2_4switch = 200; //how many PWM piorids for the black frame
	//send_buffer=(uchar*)malloc(8);
	time_out232=0;		//time out for no 232 data
	received232=0;		//get data from 232 input
	have232connected=0; //init assuming no 232					

	//duty_after_switch = duty; //duty set when button pressed for the duty% after black frame
	
	P0M0 = 0;
	P0M1 = 0;
	P1M0 = 0;
	P1M1 = 0;

	//Increase = 1;
	//Decrease = 1;
		
}

void rs232init()
{
            /*TMOD|= 0x03;
	//PWM  
	TH0 = 0xfe; //11.0592
	TL0 = 0xe3;
	TR0  = 1; 
    IE =0x8A;
	//////////////////
	

	RCAP2H=0xfe;
	RCAP2L=0xe3;
	TH2=RCAP2H;
	TL2=RCAP2L;
	T2CON=0x80;
	ET2=1;
	TR2=1;
	EA=1;	*/
	
		
		SCON = 0x50;      //REN=1�����н���״̬�����ڹ���ģʽ1    	       	   
	    TMOD|= 0x20;      //��ʱ��������ʽ2                    
		PCON|= 0x80;                                                          
		TH1  = 0xFD;     //baud*2  /* reload value 19200������λ8��ֹͣλ1��Ч��λ�� (11.0592) 
		//TH1 = 0xF3;					// //baud*2  /*  ������4800������λ8��ֹͣλ1��Ч��λ�� (12M)
    	TL1 = 0xF3;    
		
		/*//T2CON=0x34;
		//T2MOD=0x0;
		RCAP2H=0xfd;
		RCAP2L=0x33;
		TH2=RCAP2H;
		TL2=RCAP2L;
		//TH2 = 0xfd;
		//TL2 = 0xf3;
		ET2=1;
		*/

		TMOD|=0x01;		  //T0 freq setup.
		TH0=0xfe;
		TL0=0xfd;
		ET0=1;

		//SCON=0x50;
		ES   = 1;        //�������ж�                  
		EA   = 1;        // �����ж�
		PS = 8; //serial port priority =1
		
		TR0=1;
		        
		TR1  = 1;                                                             
 
		//BEEP=1;
	   // IE = 0x0;
}

void send232(uchar send_number)
{
	 	if(buffer_pointer<32) buffer_pointer++;
		//*(send_buffer + buffer_pointer) = send_number;	//add the number to buffer

		SenData = send_number;
}

void buffer_send()
{
	  if ((buffer_pointer>=1) && (sending_data ==0) &&(TI==0) )
	  {
	     //SBUF= *( send_buffer + buffer_pointer);	             //SUBF����/���ͻ�����
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

void switch2mode(uchar to_mode)
{
			switching = 1;
			timer2 = 0;
			timer2_goal = timer2_4switch;
			
			duty=10;
			ISendStr(I2C_mode_codes[to_mode]);
			current_mode=to_mode;
			send232(to_mode);
}

 main()
{
  //int i;

  system_Ini();

  //for(i=0;i<10000;i++);

  rs232init();

  switch2mode(3);  //to all clear

  while(1)
  { 
  	// PWM waveform generate
	//timer1++;
	
	if(timer1>9) 
		{
		timer1=0;
		timer2++;
		}
    if(timer1>=duty) 
		{ 
		PWM1 = 0; 
		PWM2 = 0; 
		}
    else { PWM1=1; PWM2=1; }

	// Switching control
	if (switching == 1)
		{
		if (timer2 > timer2_goal)
			{
			switching = 0; 
			duty=duty4modes[current_mode];
			}
		}
		else //detecting switch button
		{
		if (GoHaze==0)
			{
			switch2mode(0); //mode 0 is all haze
			}
		else if (GoClear==0)
			{
			switch2mode(3); //mode 3 is all clear
			}

		}
		
	buffer_send(); //send the data in rs232 buffer out.	
   	if ((time_out232 > 1000 )&&(have232connected==1)){
		 switch2mode(3); //if 232 no data time out switch to clear
		 have232connected =0;
		 }
   }

 }

/*************************************
 [ t1 (0.5ms)�ж�] �ж����� PWM ���
  ------------1000/(0.02ms*250)=200Hz
*************************************/
void T1zd(void) __interrupt 1  __using 0  //3 Ϊ��ʱ��1���жϺ�  1 ��ʱ��0���жϺ� 0 �ⲿ�ж�1 2 �ⲿ�ж�2  4 �����ж�	5 is T2
{
	//TF2=0;	  // T2 timer need this TF2=0, no hardware turning

//	if( (sending_data==1)&&(buffer_pointer==1)&&(TI!=0)) 
//		{sending_data=0; buffer_pointer=0; TI=0;}  //check if data sent, init the status
	//RCAP2H=0xfe;
	//RCAP2L=0xe3;
	//TH2 = 0xfe; //11.0592
	//TL2 = 0xe3; //It's T2MOD=0, so no need reassign the numbers.

		TH0=0xfd;
		TL0=0xfd;
		//TR0=1;
	
	 timer1++;
	 if(received232 == 0 ) time_out232++;
	 received232 = 0;
    
}	   

/****************************************************
               �����жϳ���
******************************************************/
void ser_int (void) __interrupt 4 __using 1
{

 

 if(RI == 1)        //RI�����жϱ�־
 {
 	RI = 0;		    //���RI�����жϱ�־
	ReData = SBUF;  //SUBF����/���ͻ�����
	//SenData=ReData;
 	//buffer_pointer=1;
	send232(ReData);
	received232=1;	 // get 232 data
	time_out232=0;   //reset time out
	have232connected=1;    
 }
}
