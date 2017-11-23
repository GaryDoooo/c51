//working with 12c5a60s2
#include "8051.h"
//#include <intrins.h>
#include <stdlib.h>
#define   uchar unsigned char   /*宏定义*/
#define   uint   unsigned int
//extern void Delay1us(unsigned char );

#define SDA P1_6             /*模拟I2C数据传送位*/
#define SCL P1_7              /*模拟I2C时钟控制位*/
__bit ack;            /*应答标志位*/

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
                      起动总线函数               
函数原型: void   Start_I2c();  
功能:      启动I2C总线,即发送I2C起始条件.  
********************************************************************/
void Start_I2c()
{
   SDA=1;     /*发送起始条件的数据信号*/
   Delay1us(1);
   SCL=1;
   Delay1us(5);      /*起始条件建立时间大于4.7us,延时*/
   
   SDA=0;     /*发送起始信号*/
   Delay1us(5);      /* 起始条件锁定时间大于4μs*/
        
   SCL=0;     /*钳住I2C总线，准备发送或接收数据 */
   Delay1us(2);
}

/*******************************************************************
                       结束总线函数               
函数原型: void   Stop_I2c();  
功能:      结束I2C总线,即发送I2C结束条件.  
********************************************************************/
void Stop_I2c()
{
   SDA=0;    /*发送结束条件的数据信号*/
   Delay1us(1);     /*发送结束条件的时钟信号*/
   SCL=1;    /*结束条件建立时间大于4us*/
   Delay1us(5);
  
   SDA=1;    /*发送I2C总线结束信号*/
   Delay1us(4);

}
/*******************************************************************
                  字节数据发送函数               
函数原型: void   SendByte(uchar c);
功能:      将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
           此状态位进行操作.(不应答或非应答都使ack=0)     
         发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
********************************************************************/
void   SendByte(uchar c)
{
uchar BitCnt;

for(BitCnt=0;BitCnt<8;BitCnt++)   /*要传送的数据长度为8位*/
     {
      if((c<<BitCnt)&0x80)SDA=1;    /*判断发送位*/
        else   SDA=0;               
      Delay1us(1);

      SCL=1;                /*置时钟线为高，通知被控器开始接收数据位*/      
      Delay1us(5);              /*保证时钟高电平周期大于4μs*/
            
      SCL=0;
     }
   
     Delay1us(2);
     SDA=1;                 /*8位发送完后释放数据线，准备接收应答位*/
     Delay1us(2);   
     SCL=1;
     Delay1us(3);
     if(SDA==1)ack=0;     
        else ack=1;         /*判断是否接收到应答信号*/
     SCL=0;
     Delay1us(20);
}

/*******************************************************************
                     向有子地址器件发送多字节数据函数               
函数原型: bit   ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
功能:      从启动总线到发送地址，子地址,数据，结束总线的全过程,从器件
           地址sla，子地址suba，发送内容是s指向的内容，发送no个字节。
           如果返回1表示操作成功，否则操作有误。
注意：     使用前必须已结束总线。

Removed the address part, and just changed it to single byte sending
********************************************************************/
__bit ISendStr(uchar s)
{

    Start_I2c();                /*启动总线*/
      SendByte(0xe0);             /*发送数据*/
      //if(ack==0)return(0);
      SendByte(s);             /*发送数据*/
      //if(ack==0)return(0);
// Need uncomment the ack bit when connected

    Stop_I2c();                 /*结束总线*/

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
	
		
		SCON = 0x50;      //REN=1允许串行接受状态，串口工作模式1    	       	   
	    TMOD|= 0x20;      //定时器工作方式2                    
		PCON|= 0x80;                                                          
		TH1  = 0xFD;     //baud*2  /* reload value 19200、数据位8、停止位1。效验位无 (11.0592) 
		//TH1 = 0xF3;					// //baud*2  /*  波特率4800、数据位8、停止位1。效验位无 (12M)
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
		ES   = 1;        //开串口中断                  
		EA   = 1;        // 开总中断
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
	     //SBUF= *( send_buffer + buffer_pointer);	             //SUBF接受/发送缓冲器
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
 [ t1 (0.5ms)中断] 中断中做 PWM 输出
  ------------1000/(0.02ms*250)=200Hz
*************************************/
void T1zd(void) __interrupt 1  __using 0  //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断	5 is T2
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
               串口中断程序
******************************************************/
void ser_int (void) __interrupt 4 __using 1
{

 

 if(RI == 1)        //RI接受中断标志
 {
 	RI = 0;		    //清除RI接受中断标志
	ReData = SBUF;  //SUBF接受/发送缓冲器
	//SenData=ReData;
 	//buffer_pointer=1;
	send232(ReData);
	received232=1;	 // get 232 data
	time_out232=0;   //reset time out
	have232connected=1;    
 }
}
