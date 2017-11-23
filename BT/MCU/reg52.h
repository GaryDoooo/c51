/*--------------------------------------------------------------------------
REG52.H

Header file for generic 80C52 and 80C32 microcontroller.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __REG52_H__
#define __REG52_H__

/*  BYTE Registers  */
__sfr P0    = 0x80;
__sfr P1    = 0x90;
__sfr P2    = 0xA0;
__sfr P3    = 0xB0;
__sfr PSW   = 0xD0;
__sfr ACC   = 0xE0;
__sfr B     = 0xF0;
__sfr SP    = 0x81;
__sfr DPL   = 0x82;
__sfr DPH   = 0x83;
__sfr PCON  = 0x87;
__sfr TCON  = 0x88;
__sfr TMOD  = 0x89;
__sfr TL0   = 0x8A;
__sfr TL1   = 0x8B;
__sfr TH0   = 0x8C;
__sfr TH1   = 0x8D;
__sfr IE    = 0xA8;
__sfr IP    = 0xB8;
__sfr SCON  = 0x98;
__sfr SBUF  = 0x99;

/*  8052 Extensions  */
__sfr T2CON  = 0xC8;
__sfr RCAP2L = 0xCA;
__sfr RCAP2H = 0xCB;
__sfr TL2    = 0xCC;
__sfr TH2    = 0xCD;


/*  BIT Registers  */
/*  PSW  */
__sbit CY    = PSW_7;
__sbit AC    = PSW_6;
__sbit F0    = PSW_5;
__sbit RS1   = PSW_4;
__sbit RS0   = PSW_3;
__sbit OV    = PSW_2;
__sbit P     = PSW_0; //8052 only

/*  TCON  */
__sbit TF1   = TCON_7;
__sbit TR1   = TCON_6;
__sbit TF0   = TCON_5;
__sbit TR0   = TCON_4;
__sbit IE1   = TCON_3;
__sbit IT1   = TCON_2;
__sbit IE0   = TCON_1;
__sbit IT0   = TCON_0;

/*  IE  */
__sbit EA    = IE_7;
__sbit ET2   = IE_5; //8052 only
__sbit ES    = IE_4;
__sbit ET1   = IE_3;
__sbit EX1   = IE_2;
__sbit ET0   = IE_1;
__sbit EX0   = IE_0;

/*  IP  */
__sbit PT2   = IP_5;
__sbit PS    = IP_4;
__sbit PT1   = IP_3;
__sbit PX1   = IP_2;
__sbit PT0   = IP_1;
__sbit PX0   = IP_0;

/*  P3  */
__sbit RD    = P3_7;
__sbit WR    = P3_6;
__sbit T1    = P3_5;
__sbit T0    = P3_4;
__sbit INT1  = P3_3;
__sbit INT0  = P3_2;
__sbit TXD   = P3_1;
__sbit RXD   = P3_0;

/*  SCON  */
__sbit SM0   = SCON_7;
__sbit SM1   = SCON_6;
__sbit SM2   = SCON_5;
__sbit REN   = SCON_4;
__sbit TB8   = SCON_3;
__sbit RB8   = SCON_2;
__sbit TI    = SCON_1;
__sbit RI    = SCON_0;

/*  P1  */
__sbit T2EX  = P1_1; // 8052 only
__sbit T2    = P1_0; // 8052 only
             
/*  T2CON  */
__sbit TF2    = T2CON_7;
__sbit EXF2   = T2CON_6;
__sbit RCLK   = T2CON_5;
__sbit TCLK   = T2CON_4;
__sbit EXEN2  = T2CON_3;
__sbit TR2    = T2CON_2;
__sbit C_T2   = T2CON_1;
__sbit CP_RL2 = T2CON_0;

#endif
