;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.1.0 #7066 (Jun 14 2012) (Linux)
; This file was generated Sat May 17 17:25:13 2014
;--------------------------------------------------------
	.module PWM
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _ser_int
	.globl _T1zd
	.globl _main
	.globl _switch2mode
	.globl _buffer_send
	.globl _send232
	.globl _rs232init
	.globl _system_Ini
	.globl _ISendStr
	.globl _SendByte
	.globl _Stop_I2c
	.globl _Start_I2c
	.globl _Delay1us
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _T2MOD
	.globl _P1M1
	.globl _P1M0
	.globl _P0M1
	.globl _P0M0
	.globl _B
	.globl _ACC
	.globl _PSW
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _ack
	.globl _have232connected
	.globl _received232
	.globl _time_out232
	.globl _duty4modes
	.globl _current_mode
	.globl _I2C_mode_codes
	.globl _SenData
	.globl _ReData
	.globl _buffer_pointer
	.globl _sending_data
	.globl _timer2_4switch
	.globl _timer2_goal
	.globl _timer2
	.globl _switching
	.globl _duty
	.globl _timer1
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
_P0M0::
	.ds 1
_P0M1::
	.ds 1
_P1M0::
	.ds 1
_P1M1::
	.ds 1
_T2MOD::
	.ds 1
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
	.area REG_BANK_1	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; overlayable bit register bank
;--------------------------------------------------------
	.area BIT_BANK	(REL,OVR,DATA)
bits:
	.ds 1
	b0 = bits[0]
	b1 = bits[1]
	b2 = bits[2]
	b3 = bits[3]
	b4 = bits[4]
	b5 = bits[5]
	b6 = bits[6]
	b7 = bits[7]
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_timer1::
	.ds 1
_duty::
	.ds 1
_switching::
	.ds 1
_timer2::
	.ds 1
_timer2_goal::
	.ds 1
_timer2_4switch::
	.ds 1
_sending_data::
	.ds 1
_buffer_pointer::
	.ds 1
_ReData::
	.ds 1
_SenData::
	.ds 1
_I2C_mode_codes::
	.ds 4
_current_mode::
	.ds 1
_duty4modes::
	.ds 4
_time_out232::
	.ds 2
_received232::
	.ds 1
_have232connected::
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG	(DATA)
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
_ack::
	.ds 1
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
	reti
	.ds	7
	ljmp	_T1zd
	.ds	5
	reti
	.ds	7
	reti
	.ds	7
	ljmp	_ser_int
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:19: uchar I2C_mode_codes[4]={0,6,12,15};
	mov	_I2C_mode_codes,#0x00
	mov	(_I2C_mode_codes + 0x0001),#0x06
	mov	(_I2C_mode_codes + 0x0002),#0x0C
	mov	(_I2C_mode_codes + 0x0003),#0x0F
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:21: uchar duty4modes[4]={0,3,3,3};
	mov	_duty4modes,#0x00
	mov	(_duty4modes + 0x0001),#0x03
	mov	(_duty4modes + 0x0002),#0x03
	mov	(_duty4modes + 0x0003),#0x03
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:33: __sfr P0M0    = 0x94;
	mov	_P0M0,#0x94
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:34: __sfr P0M1    = 0x93;
	mov	_P0M1,#0x93
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:35: __sfr P1M0    = 0x91;
	mov	_P1M0,#0x91
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:36: __sfr P1M1    = 0x92;
	mov	_P1M1,#0x92
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:38: __sfr T2MOD = 0xc9;
	mov	_T2MOD,#0xC9
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	lcall	_main
;	return from main will lock up
	sjmp .
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'Delay1us'
;------------------------------------------------------------
;time_length               Allocated to registers r7 
;i                         Allocated to registers r6 
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:42: void Delay1us(uchar time_length)
;	-----------------------------------------
;	 function Delay1us
;	-----------------------------------------
_Delay1us:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
	mov	r7,dpl
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:45: for(i=0;i<time_length;i++);
	mov	r6,#0x00
00101$:
	clr	c
	mov	a,r6
	subb	a,r7
	jnc	00105$
	inc	r6
	sjmp	00101$
00105$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Start_I2c'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:53: void Start_I2c()
;	-----------------------------------------
;	 function Start_I2c
;	-----------------------------------------
_Start_I2c:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:55: SDA=1;     /*发送起始条件的数据信号*/
	setb	_P1_6
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:56: Delay1us(1);
	mov	dpl,#0x01
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:57: SCL=1;
	setb	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:58: Delay1us(5);      /*起始条件建立时间大于4.7us,延时*/
	mov	dpl,#0x05
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:60: SDA=0;     /*发送起始信号*/
	clr	_P1_6
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:61: Delay1us(5);      /* 起始条件锁定时间大于4μs*/
	mov	dpl,#0x05
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:63: SCL=0;     /*钳住I2C总线，准备发送或接收数据 */
	clr	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:64: Delay1us(2);
	mov	dpl,#0x02
	ljmp	_Delay1us
;------------------------------------------------------------
;Allocation info for local variables in function 'Stop_I2c'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:72: void Stop_I2c()
;	-----------------------------------------
;	 function Stop_I2c
;	-----------------------------------------
_Stop_I2c:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:74: SDA=0;    /*发送结束条件的数据信号*/
	clr	_P1_6
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:75: Delay1us(1);     /*发送结束条件的时钟信号*/
	mov	dpl,#0x01
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:76: SCL=1;    /*结束条件建立时间大于4us*/
	setb	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:77: Delay1us(5);
	mov	dpl,#0x05
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:79: SDA=1;    /*发送I2C总线结束信号*/
	setb	_P1_6
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:80: Delay1us(4);
	mov	dpl,#0x04
	ljmp	_Delay1us
;------------------------------------------------------------
;Allocation info for local variables in function 'SendByte'
;------------------------------------------------------------
;c                         Allocated to registers r7 
;BitCnt                    Allocated to registers r6 
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:90: void   SendByte(uchar c)
;	-----------------------------------------
;	 function SendByte
;	-----------------------------------------
_SendByte:
	mov	r7,dpl
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:94: for(BitCnt=0;BitCnt<8;BitCnt++)   /*要传送的数据长度为8位*/
	mov	r6,#0x00
00107$:
	cjne	r6,#0x08,00118$
00118$:
	jnc	00110$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:96: if((c<<BitCnt)&0x80)SDA=1;    /*判断发送位*/
	mov	ar4,r7
	mov	r5,#0x00
	mov	b,r6
	inc	b
	sjmp	00121$
00120$:
	mov	a,r4
	add	a,r4
	mov	r4,a
	mov	a,r5
	rlc	a
	mov	r5,a
00121$:
	djnz	b,00120$
	mov	a,r4
	jnb	acc.7,00102$
	setb	_P1_6
	sjmp	00103$
00102$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:97: else   SDA=0;               
	clr	_P1_6
00103$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:98: Delay1us(1);
	mov	dpl,#0x01
	push	ar7
	push	ar6
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:100: SCL=1;                /*置时钟线为高，通知被控器开始接收数据位*/      
	setb	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:101: Delay1us(5);              /*保证时钟高电平周期大于4μs*/
	mov	dpl,#0x05
	lcall	_Delay1us
	pop	ar6
	pop	ar7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:103: SCL=0;
	clr	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:94: for(BitCnt=0;BitCnt<8;BitCnt++)   /*要传送的数据长度为8位*/
	inc	r6
	sjmp	00107$
00110$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:106: Delay1us(2);
	mov	dpl,#0x02
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:107: SDA=1;                 /*8位发送完后释放数据线，准备接收应答位*/
	setb	_P1_6
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:108: Delay1us(2);   
	mov	dpl,#0x02
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:109: SCL=1;
	setb	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:110: Delay1us(3);
	mov	dpl,#0x03
	lcall	_Delay1us
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:111: if(SDA==1)ack=0;     
	jnb	_P1_6,00105$
	clr	_ack
	sjmp	00106$
00105$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:112: else ack=1;         /*判断是否接收到应答信号*/
	setb	_ack
00106$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:113: SCL=0;
	clr	_P1_7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:114: Delay1us(20);
	mov	dpl,#0x14
	ljmp	_Delay1us
;------------------------------------------------------------
;Allocation info for local variables in function 'ISendStr'
;------------------------------------------------------------
;s                         Allocated to registers r7 
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:127: __bit ISendStr(uchar s)
;	-----------------------------------------
;	 function ISendStr
;	-----------------------------------------
_ISendStr:
	mov	r7,dpl
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:130: Start_I2c();                /*启动总线*/
	push	ar7
	lcall	_Start_I2c
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:131: SendByte(0xe0);             /*发送数据*/
	mov	dpl,#0xE0
	lcall	_SendByte
	pop	ar7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:133: SendByte(s);             /*发送数据*/
	mov	dpl,r7
	lcall	_SendByte
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:137: Stop_I2c();                 /*结束总线*/
	lcall	_Stop_I2c
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:139: return(1);
	setb	c
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'system_Ini'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:143: void system_Ini()
;	-----------------------------------------
;	 function system_Ini
;	-----------------------------------------
_system_Ini:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:146: duty=5;	  // Init the backlight as off, PWM positive duty in 20%
	mov	_duty,#0x05
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:147: timer1=0; //timer for PWM
	mov	_timer1,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:148: switching=0; //status of in process of switching
	mov	_switching,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:149: timer2=0; //timer for switching black frame
	mov	_timer2,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:150: timer2_goal = 0; //timer2 length setting
	mov	_timer2_goal,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:151: sending_data =0; // if send data thru rs232
	mov	_sending_data,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:152: buffer_pointer = 0; //if data received from rs232
	mov	_buffer_pointer,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:154: timer2_4switch = 200; //how many PWM piorids for the black frame
	mov	_timer2_4switch,#0xC8
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:156: time_out232=0;		//time out for no 232 data
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:157: received232=0;		//get data from 232 input
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:158: have232connected=0; //init assuming no 232					
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:162: P0M0 = 0;
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:163: P0M1 = 0;
	clr a
	mov _time_out232,a
	mov (_time_out232 + 1),a
	mov _received232,a
	mov _have232connected,a
	mov _P0M0,a
	mov _P0M1,a
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:164: P1M0 = 0;
	mov	_P1M0,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:165: P1M1 = 0;
	mov	_P1M1,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'rs232init'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:172: void rs232init()
;	-----------------------------------------
;	 function rs232init
;	-----------------------------------------
_rs232init:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:193: SCON = 0x50;      //REN=1允许串行接受状态，串口工作模式1    	       	   
	mov	_SCON,#0x50
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:194: TMOD|= 0x20;      //定时器工作方式2                    
	orl	_TMOD,#0x20
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:195: PCON|= 0x80;                                                          
	orl	_PCON,#0x80
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:196: TH1  = 0xFD;     //baud*2  /* reload value 19200、数据位8、停止位1。效验位无 (11.0592) 
	mov	_TH1,#0xFD
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:198: TL1 = 0xF3;    
	mov	_TL1,#0xF3
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:211: TMOD|=0x01;		  //T0 freq setup.
	orl	_TMOD,#0x01
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:212: TH0=0xfe;
	mov	_TH0,#0xFE
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:213: TL0=0xfd;
	mov	_TL0,#0xFD
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:214: ET0=1;
	setb	_ET0
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:217: ES   = 1;        //开串口中断                  
	setb	_ES
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:218: EA   = 1;        // 开总中断
	setb	_EA
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:219: PS = 8; //serial port priority =1
	setb	_PS
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:221: TR0=1;
	setb	_TR0
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:223: TR1  = 1;                                                             
	setb	_TR1
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send232'
;------------------------------------------------------------
;send_number               Allocated to registers r7 
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:229: void send232(uchar send_number)
;	-----------------------------------------
;	 function send232
;	-----------------------------------------
_send232:
	mov	r7,dpl
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:231: if(buffer_pointer<32) buffer_pointer++;
	mov	a,#0x100 - 0x20
	add	a,_buffer_pointer
	jc	00102$
	inc	_buffer_pointer
00102$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:234: SenData = send_number;
	mov	_SenData,r7
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'buffer_send'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:237: void buffer_send()
;	-----------------------------------------
;	 function buffer_send
;	-----------------------------------------
_buffer_send:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:239: if ((buffer_pointer>=1) && (sending_data ==0) &&(TI==0) )
	mov	a,#0x100 - 0x01
	add	a,_buffer_pointer
	jnc	00102$
	mov	a,_sending_data
	jnz	00102$
	jb	_TI,00102$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:242: SBUF = SenData;
	mov	_SBUF,_SenData
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:243: sending_data=1;
	mov	_sending_data,#0x01
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:244: buffer_pointer--;
	dec	_buffer_pointer
00102$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:250: if( (sending_data==1)&&(TI!=0)) 
	mov	a,#0x01
	cjne	a,_sending_data,00108$
	jnb	_TI,00108$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:251: {sending_data=0; TI=0;}  //check if data sent, init the status
	mov	_sending_data,#0x00
	clr	_TI
00108$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'switch2mode'
;------------------------------------------------------------
;to_mode                   Allocated to registers r7 
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:254: void switch2mode(uchar to_mode)
;	-----------------------------------------
;	 function switch2mode
;	-----------------------------------------
_switch2mode:
	mov	r7,dpl
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:256: switching = 1;
	mov	_switching,#0x01
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:257: timer2 = 0;
	mov	_timer2,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:258: timer2_goal = timer2_4switch;
	mov	_timer2_goal,_timer2_4switch
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:260: duty=10;
	mov	_duty,#0x0A
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:261: ISendStr(I2C_mode_codes[to_mode]);
	mov	a,r7
	add	a,#_I2C_mode_codes
	mov	r1,a
	mov	dpl,@r1
	push	ar7
	lcall	_ISendStr
	pop	ar7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:262: current_mode=to_mode;
	mov	_current_mode,r7
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:263: send232(to_mode);
	mov	dpl,r7
	ljmp	_send232
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:266: main()
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:270: system_Ini();
	lcall	_system_Ini
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:274: rs232init();
	lcall	_rs232init
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:276: switch2mode(3);  //to all clear
	mov	dpl,#0x03
	lcall	_switch2mode
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:278: while(1)
00120$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:283: if(timer1>9) 
	mov	a,_timer1
	add	a,#0xff - 0x09
	jnc	00102$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:285: timer1=0;
	mov	_timer1,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:286: timer2++;
	inc	_timer2
00102$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:288: if(timer1>=duty) 
	clr	c
	mov	a,_timer1
	subb	a,_duty
	jc	00104$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:290: PWM1 = 0; 
	clr	_P0_1
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:291: PWM2 = 0; 
	clr	_P0_2
	sjmp	00105$
00104$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:293: else { PWM1=1; PWM2=1; }
	setb	_P0_1
	setb	_P0_2
00105$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:296: if (switching == 1)
	mov	a,#0x01
	cjne	a,_switching,00114$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:298: if (timer2 > timer2_goal)
	clr	c
	mov	a,_timer2_goal
	subb	a,_timer2
	jnc	00115$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:300: switching = 0; 
	mov	_switching,#0x00
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:301: duty=duty4modes[current_mode];
	mov	a,_current_mode
	add	a,#_duty4modes
	mov	r1,a
	mov	_duty,@r1
	sjmp	00115$
00114$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:306: if (GoHaze==0)
	jb	_P0_6,00111$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:308: switch2mode(0); //mode 0 is all haze
	mov	dpl,#0x00
	lcall	_switch2mode
	sjmp	00115$
00111$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:310: else if (GoClear==0)
	jb	_P0_7,00115$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:312: switch2mode(3); //mode 3 is all clear
	mov	dpl,#0x03
	lcall	_switch2mode
00115$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:317: buffer_send(); //send the data in rs232 buffer out.	
	lcall	_buffer_send
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:318: if ((time_out232 > 1000 )&&(have232connected==1)){
	clr	c
	mov	a,#0xE8
	subb	a,_time_out232
	mov	a,#0x03
	subb	a,(_time_out232 + 1)
	jnc	00120$
	mov	a,#0x01
	cjne	a,_have232connected,00120$
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:319: switch2mode(3); //if 232 no data time out switch to clear
	mov	dpl,#0x03
	lcall	_switch2mode
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:320: have232connected =0;
	mov	_have232connected,#0x00
	sjmp	00120$
;------------------------------------------------------------
;Allocation info for local variables in function 'T1zd'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:330: void T1zd(void) __interrupt 1  __using 0  //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断	5 is T2
;	-----------------------------------------
;	 function T1zd
;	-----------------------------------------
_T1zd:
	push	acc
	push	psw
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:341: TH0=0xfd;
	mov	_TH0,#0xFD
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:342: TL0=0xfd;
	mov	_TL0,#0xFD
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:345: timer1++;
	inc	_timer1
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:346: if(received232 == 0 ) time_out232++;
	mov	a,_received232
	jnz	00102$
	inc	_time_out232
	clr	a
	cjne	a,_time_out232,00107$
	inc	(_time_out232 + 1)
00107$:
00102$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:347: received232 = 0;
	mov	_received232,#0x00
	pop	psw
	pop	acc
	reti
;	eliminated unneeded mov psw,# (no regs used in bank)
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'ser_int'
;------------------------------------------------------------
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:354: void ser_int (void) __interrupt 4 __using 1
;	-----------------------------------------
;	 function ser_int
;	-----------------------------------------
_ser_int:
	ar7 = 0x0F
	ar6 = 0x0E
	ar5 = 0x0D
	ar4 = 0x0C
	ar3 = 0x0B
	ar2 = 0x0A
	ar1 = 0x09
	ar0 = 0x08
	push	bits
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+7)
	push	(0+6)
	push	(0+5)
	push	(0+4)
	push	(0+3)
	push	(0+2)
	push	(0+1)
	push	(0+0)
	push	psw
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:359: if(RI == 1)        //RI接受中断标志
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:361: RI = 0;		    //清除RI接受中断标志
	jbc	_RI,00106$
	sjmp	00103$
00106$:
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:362: ReData = SBUF;  //SUBF接受/发送缓冲器
	mov	_ReData,_SBUF
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:365: send232(ReData);
	mov	dpl,_ReData
	mov	psw,#0x00
	lcall	_send232
	mov	psw,#0x08
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:366: received232=1;	 // get 232 data
	mov	_received232,#0x01
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:367: time_out232=0;   //reset time out
	clr	a
	mov	_time_out232,a
	mov	(_time_out232 + 1),a
;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:368: have232connected=1;    
	mov	_have232connected,#0x01
00103$:
	pop	psw
	pop	(0+0)
	pop	(0+1)
	pop	(0+2)
	pop	(0+3)
	pop	(0+4)
	pop	(0+5)
	pop	(0+6)
	pop	(0+7)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	pop	bits
	reti
;	eliminated unneeded mov psw,# (no regs used in bank)
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
