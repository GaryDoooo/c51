                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 3.1.0 #7066 (Jun 14 2012) (Linux)
                              4 ; This file was generated Sat May 17 17:25:13 2014
                              5 ;--------------------------------------------------------
                              6 	.module PWM
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _ser_int
                             13 	.globl _T1zd
                             14 	.globl _main
                             15 	.globl _switch2mode
                             16 	.globl _buffer_send
                             17 	.globl _send232
                             18 	.globl _rs232init
                             19 	.globl _system_Ini
                             20 	.globl _ISendStr
                             21 	.globl _SendByte
                             22 	.globl _Stop_I2c
                             23 	.globl _Start_I2c
                             24 	.globl _Delay1us
                             25 	.globl _CY
                             26 	.globl _AC
                             27 	.globl _F0
                             28 	.globl _RS1
                             29 	.globl _RS0
                             30 	.globl _OV
                             31 	.globl _F1
                             32 	.globl _P
                             33 	.globl _PS
                             34 	.globl _PT1
                             35 	.globl _PX1
                             36 	.globl _PT0
                             37 	.globl _PX0
                             38 	.globl _RD
                             39 	.globl _WR
                             40 	.globl _T1
                             41 	.globl _T0
                             42 	.globl _INT1
                             43 	.globl _INT0
                             44 	.globl _TXD
                             45 	.globl _RXD
                             46 	.globl _P3_7
                             47 	.globl _P3_6
                             48 	.globl _P3_5
                             49 	.globl _P3_4
                             50 	.globl _P3_3
                             51 	.globl _P3_2
                             52 	.globl _P3_1
                             53 	.globl _P3_0
                             54 	.globl _EA
                             55 	.globl _ES
                             56 	.globl _ET1
                             57 	.globl _EX1
                             58 	.globl _ET0
                             59 	.globl _EX0
                             60 	.globl _P2_7
                             61 	.globl _P2_6
                             62 	.globl _P2_5
                             63 	.globl _P2_4
                             64 	.globl _P2_3
                             65 	.globl _P2_2
                             66 	.globl _P2_1
                             67 	.globl _P2_0
                             68 	.globl _SM0
                             69 	.globl _SM1
                             70 	.globl _SM2
                             71 	.globl _REN
                             72 	.globl _TB8
                             73 	.globl _RB8
                             74 	.globl _TI
                             75 	.globl _RI
                             76 	.globl _P1_7
                             77 	.globl _P1_6
                             78 	.globl _P1_5
                             79 	.globl _P1_4
                             80 	.globl _P1_3
                             81 	.globl _P1_2
                             82 	.globl _P1_1
                             83 	.globl _P1_0
                             84 	.globl _TF1
                             85 	.globl _TR1
                             86 	.globl _TF0
                             87 	.globl _TR0
                             88 	.globl _IE1
                             89 	.globl _IT1
                             90 	.globl _IE0
                             91 	.globl _IT0
                             92 	.globl _P0_7
                             93 	.globl _P0_6
                             94 	.globl _P0_5
                             95 	.globl _P0_4
                             96 	.globl _P0_3
                             97 	.globl _P0_2
                             98 	.globl _P0_1
                             99 	.globl _P0_0
                            100 	.globl _T2MOD
                            101 	.globl _P1M1
                            102 	.globl _P1M0
                            103 	.globl _P0M1
                            104 	.globl _P0M0
                            105 	.globl _B
                            106 	.globl _ACC
                            107 	.globl _PSW
                            108 	.globl _IP
                            109 	.globl _P3
                            110 	.globl _IE
                            111 	.globl _P2
                            112 	.globl _SBUF
                            113 	.globl _SCON
                            114 	.globl _P1
                            115 	.globl _TH1
                            116 	.globl _TH0
                            117 	.globl _TL1
                            118 	.globl _TL0
                            119 	.globl _TMOD
                            120 	.globl _TCON
                            121 	.globl _PCON
                            122 	.globl _DPH
                            123 	.globl _DPL
                            124 	.globl _SP
                            125 	.globl _P0
                            126 	.globl _ack
                            127 	.globl _have232connected
                            128 	.globl _received232
                            129 	.globl _time_out232
                            130 	.globl _duty4modes
                            131 	.globl _current_mode
                            132 	.globl _I2C_mode_codes
                            133 	.globl _SenData
                            134 	.globl _ReData
                            135 	.globl _buffer_pointer
                            136 	.globl _sending_data
                            137 	.globl _timer2_4switch
                            138 	.globl _timer2_goal
                            139 	.globl _timer2
                            140 	.globl _switching
                            141 	.globl _duty
                            142 	.globl _timer1
                            143 ;--------------------------------------------------------
                            144 ; special function registers
                            145 ;--------------------------------------------------------
                            146 	.area RSEG    (ABS,DATA)
   0000                     147 	.org 0x0000
                    0080    148 _P0	=	0x0080
                    0081    149 _SP	=	0x0081
                    0082    150 _DPL	=	0x0082
                    0083    151 _DPH	=	0x0083
                    0087    152 _PCON	=	0x0087
                    0088    153 _TCON	=	0x0088
                    0089    154 _TMOD	=	0x0089
                    008A    155 _TL0	=	0x008a
                    008B    156 _TL1	=	0x008b
                    008C    157 _TH0	=	0x008c
                    008D    158 _TH1	=	0x008d
                    0090    159 _P1	=	0x0090
                    0098    160 _SCON	=	0x0098
                    0099    161 _SBUF	=	0x0099
                    00A0    162 _P2	=	0x00a0
                    00A8    163 _IE	=	0x00a8
                    00B0    164 _P3	=	0x00b0
                    00B8    165 _IP	=	0x00b8
                    00D0    166 _PSW	=	0x00d0
                    00E0    167 _ACC	=	0x00e0
                    00F0    168 _B	=	0x00f0
   0000                     169 _P0M0::
   0000                     170 	.ds 1
   0001                     171 _P0M1::
   0001                     172 	.ds 1
   0002                     173 _P1M0::
   0002                     174 	.ds 1
   0003                     175 _P1M1::
   0003                     176 	.ds 1
   0004                     177 _T2MOD::
   0004                     178 	.ds 1
                            179 ;--------------------------------------------------------
                            180 ; special function bits
                            181 ;--------------------------------------------------------
                            182 	.area RSEG    (ABS,DATA)
   0000                     183 	.org 0x0000
                    0080    184 _P0_0	=	0x0080
                    0081    185 _P0_1	=	0x0081
                    0082    186 _P0_2	=	0x0082
                    0083    187 _P0_3	=	0x0083
                    0084    188 _P0_4	=	0x0084
                    0085    189 _P0_5	=	0x0085
                    0086    190 _P0_6	=	0x0086
                    0087    191 _P0_7	=	0x0087
                    0088    192 _IT0	=	0x0088
                    0089    193 _IE0	=	0x0089
                    008A    194 _IT1	=	0x008a
                    008B    195 _IE1	=	0x008b
                    008C    196 _TR0	=	0x008c
                    008D    197 _TF0	=	0x008d
                    008E    198 _TR1	=	0x008e
                    008F    199 _TF1	=	0x008f
                    0090    200 _P1_0	=	0x0090
                    0091    201 _P1_1	=	0x0091
                    0092    202 _P1_2	=	0x0092
                    0093    203 _P1_3	=	0x0093
                    0094    204 _P1_4	=	0x0094
                    0095    205 _P1_5	=	0x0095
                    0096    206 _P1_6	=	0x0096
                    0097    207 _P1_7	=	0x0097
                    0098    208 _RI	=	0x0098
                    0099    209 _TI	=	0x0099
                    009A    210 _RB8	=	0x009a
                    009B    211 _TB8	=	0x009b
                    009C    212 _REN	=	0x009c
                    009D    213 _SM2	=	0x009d
                    009E    214 _SM1	=	0x009e
                    009F    215 _SM0	=	0x009f
                    00A0    216 _P2_0	=	0x00a0
                    00A1    217 _P2_1	=	0x00a1
                    00A2    218 _P2_2	=	0x00a2
                    00A3    219 _P2_3	=	0x00a3
                    00A4    220 _P2_4	=	0x00a4
                    00A5    221 _P2_5	=	0x00a5
                    00A6    222 _P2_6	=	0x00a6
                    00A7    223 _P2_7	=	0x00a7
                    00A8    224 _EX0	=	0x00a8
                    00A9    225 _ET0	=	0x00a9
                    00AA    226 _EX1	=	0x00aa
                    00AB    227 _ET1	=	0x00ab
                    00AC    228 _ES	=	0x00ac
                    00AF    229 _EA	=	0x00af
                    00B0    230 _P3_0	=	0x00b0
                    00B1    231 _P3_1	=	0x00b1
                    00B2    232 _P3_2	=	0x00b2
                    00B3    233 _P3_3	=	0x00b3
                    00B4    234 _P3_4	=	0x00b4
                    00B5    235 _P3_5	=	0x00b5
                    00B6    236 _P3_6	=	0x00b6
                    00B7    237 _P3_7	=	0x00b7
                    00B0    238 _RXD	=	0x00b0
                    00B1    239 _TXD	=	0x00b1
                    00B2    240 _INT0	=	0x00b2
                    00B3    241 _INT1	=	0x00b3
                    00B4    242 _T0	=	0x00b4
                    00B5    243 _T1	=	0x00b5
                    00B6    244 _WR	=	0x00b6
                    00B7    245 _RD	=	0x00b7
                    00B8    246 _PX0	=	0x00b8
                    00B9    247 _PT0	=	0x00b9
                    00BA    248 _PX1	=	0x00ba
                    00BB    249 _PT1	=	0x00bb
                    00BC    250 _PS	=	0x00bc
                    00D0    251 _P	=	0x00d0
                    00D1    252 _F1	=	0x00d1
                    00D2    253 _OV	=	0x00d2
                    00D3    254 _RS0	=	0x00d3
                    00D4    255 _RS1	=	0x00d4
                    00D5    256 _F0	=	0x00d5
                    00D6    257 _AC	=	0x00d6
                    00D7    258 _CY	=	0x00d7
                            259 ;--------------------------------------------------------
                            260 ; overlayable register banks
                            261 ;--------------------------------------------------------
                            262 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     263 	.ds 8
                            264 	.area REG_BANK_1	(REL,OVR,DATA)
   0008                     265 	.ds 8
                            266 ;--------------------------------------------------------
                            267 ; overlayable bit register bank
                            268 ;--------------------------------------------------------
                            269 	.area BIT_BANK	(REL,OVR,DATA)
   0021                     270 bits:
   0021                     271 	.ds 1
                    8000    272 	b0 = bits[0]
                    8100    273 	b1 = bits[1]
                    8200    274 	b2 = bits[2]
                    8300    275 	b3 = bits[3]
                    8400    276 	b4 = bits[4]
                    8500    277 	b5 = bits[5]
                    8600    278 	b6 = bits[6]
                    8700    279 	b7 = bits[7]
                            280 ;--------------------------------------------------------
                            281 ; internal ram data
                            282 ;--------------------------------------------------------
                            283 	.area DSEG    (DATA)
   0022                     284 _timer1::
   0022                     285 	.ds 1
   0023                     286 _duty::
   0023                     287 	.ds 1
   0024                     288 _switching::
   0024                     289 	.ds 1
   0025                     290 _timer2::
   0025                     291 	.ds 1
   0026                     292 _timer2_goal::
   0026                     293 	.ds 1
   0027                     294 _timer2_4switch::
   0027                     295 	.ds 1
   0028                     296 _sending_data::
   0028                     297 	.ds 1
   0029                     298 _buffer_pointer::
   0029                     299 	.ds 1
   002A                     300 _ReData::
   002A                     301 	.ds 1
   002B                     302 _SenData::
   002B                     303 	.ds 1
   002C                     304 _I2C_mode_codes::
   002C                     305 	.ds 4
   0030                     306 _current_mode::
   0030                     307 	.ds 1
   0031                     308 _duty4modes::
   0031                     309 	.ds 4
   0035                     310 _time_out232::
   0035                     311 	.ds 2
   0037                     312 _received232::
   0037                     313 	.ds 1
   0038                     314 _have232connected::
   0038                     315 	.ds 1
                            316 ;--------------------------------------------------------
                            317 ; overlayable items in internal ram 
                            318 ;--------------------------------------------------------
                            319 	.area	OSEG    (OVR,DATA)
                            320 	.area	OSEG    (OVR,DATA)
                            321 ;--------------------------------------------------------
                            322 ; Stack segment in internal ram 
                            323 ;--------------------------------------------------------
                            324 	.area	SSEG	(DATA)
   0039                     325 __start__stack:
   0039                     326 	.ds	1
                            327 
                            328 ;--------------------------------------------------------
                            329 ; indirectly addressable internal ram data
                            330 ;--------------------------------------------------------
                            331 	.area ISEG    (DATA)
                            332 ;--------------------------------------------------------
                            333 ; absolute internal ram data
                            334 ;--------------------------------------------------------
                            335 	.area IABS    (ABS,DATA)
                            336 	.area IABS    (ABS,DATA)
                            337 ;--------------------------------------------------------
                            338 ; bit data
                            339 ;--------------------------------------------------------
                            340 	.area BSEG    (BIT)
   0000                     341 _ack::
   0000                     342 	.ds 1
                            343 ;--------------------------------------------------------
                            344 ; paged external ram data
                            345 ;--------------------------------------------------------
                            346 	.area PSEG    (PAG,XDATA)
                            347 ;--------------------------------------------------------
                            348 ; external ram data
                            349 ;--------------------------------------------------------
                            350 	.area XSEG    (XDATA)
                            351 ;--------------------------------------------------------
                            352 ; absolute external ram data
                            353 ;--------------------------------------------------------
                            354 	.area XABS    (ABS,XDATA)
                            355 ;--------------------------------------------------------
                            356 ; external initialized ram data
                            357 ;--------------------------------------------------------
                            358 	.area XISEG   (XDATA)
                            359 	.area HOME    (CODE)
                            360 	.area GSINIT0 (CODE)
                            361 	.area GSINIT1 (CODE)
                            362 	.area GSINIT2 (CODE)
                            363 	.area GSINIT3 (CODE)
                            364 	.area GSINIT4 (CODE)
                            365 	.area GSINIT5 (CODE)
                            366 	.area GSINIT  (CODE)
                            367 	.area GSFINAL (CODE)
                            368 	.area CSEG    (CODE)
                            369 ;--------------------------------------------------------
                            370 ; interrupt vector 
                            371 ;--------------------------------------------------------
                            372 	.area HOME    (CODE)
   0000                     373 __interrupt_vect:
   0000 02 00 2B            374 	ljmp	__sdcc_gsinit_startup
   0003 32                  375 	reti
   0004                     376 	.ds	7
   000B 02 02 89            377 	ljmp	_T1zd
   000E                     378 	.ds	5
   0013 32                  379 	reti
   0014                     380 	.ds	7
   001B 32                  381 	reti
   001C                     382 	.ds	7
   0023 02 02 A9            383 	ljmp	_ser_int
                            384 ;--------------------------------------------------------
                            385 ; global & static initialisations
                            386 ;--------------------------------------------------------
                            387 	.area HOME    (CODE)
                            388 	.area GSINIT  (CODE)
                            389 	.area GSFINAL (CODE)
                            390 	.area GSINIT  (CODE)
                            391 	.globl __sdcc_gsinit_startup
                            392 	.globl __sdcc_program_startup
                            393 	.globl __start__stack
                            394 	.globl __mcs51_genXINIT
                            395 	.globl __mcs51_genXRAMCLEAR
                            396 	.globl __mcs51_genRAMCLEAR
                            397 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:19: uchar I2C_mode_codes[4]={0,6,12,15};
   0084 75 2C 00            398 	mov	_I2C_mode_codes,#0x00
   0087 75 2D 06            399 	mov	(_I2C_mode_codes + 0x0001),#0x06
   008A 75 2E 0C            400 	mov	(_I2C_mode_codes + 0x0002),#0x0C
   008D 75 2F 0F            401 	mov	(_I2C_mode_codes + 0x0003),#0x0F
                            402 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:21: uchar duty4modes[4]={0,3,3,3};
   0090 75 31 00            403 	mov	_duty4modes,#0x00
   0093 75 32 03            404 	mov	(_duty4modes + 0x0001),#0x03
   0096 75 33 03            405 	mov	(_duty4modes + 0x0002),#0x03
   0099 75 34 03            406 	mov	(_duty4modes + 0x0003),#0x03
                            407 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:33: __sfr P0M0    = 0x94;
   009C 75 00 94            408 	mov	_P0M0,#0x94
                            409 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:34: __sfr P0M1    = 0x93;
   009F 75 01 93            410 	mov	_P0M1,#0x93
                            411 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:35: __sfr P1M0    = 0x91;
   00A2 75 02 91            412 	mov	_P1M0,#0x91
                            413 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:36: __sfr P1M1    = 0x92;
   00A5 75 03 92            414 	mov	_P1M1,#0x92
                            415 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:38: __sfr T2MOD = 0xc9;
   00A8 75 04 C9            416 	mov	_T2MOD,#0xC9
                            417 	.area GSFINAL (CODE)
   00AB 02 00 26            418 	ljmp	__sdcc_program_startup
                            419 ;--------------------------------------------------------
                            420 ; Home
                            421 ;--------------------------------------------------------
                            422 	.area HOME    (CODE)
                            423 	.area HOME    (CODE)
   0026                     424 __sdcc_program_startup:
   0026 12 02 17            425 	lcall	_main
                            426 ;	return from main will lock up
   0029 80 FE               427 	sjmp .
                            428 ;--------------------------------------------------------
                            429 ; code
                            430 ;--------------------------------------------------------
                            431 	.area CSEG    (CODE)
                            432 ;------------------------------------------------------------
                            433 ;Allocation info for local variables in function 'Delay1us'
                            434 ;------------------------------------------------------------
                            435 ;time_length               Allocated to registers r7 
                            436 ;i                         Allocated to registers r6 
                            437 ;------------------------------------------------------------
                            438 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:42: void Delay1us(uchar time_length)
                            439 ;	-----------------------------------------
                            440 ;	 function Delay1us
                            441 ;	-----------------------------------------
   00AE                     442 _Delay1us:
                    0007    443 	ar7 = 0x07
                    0006    444 	ar6 = 0x06
                    0005    445 	ar5 = 0x05
                    0004    446 	ar4 = 0x04
                    0003    447 	ar3 = 0x03
                    0002    448 	ar2 = 0x02
                    0001    449 	ar1 = 0x01
                    0000    450 	ar0 = 0x00
   00AE AF 82               451 	mov	r7,dpl
                            452 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:45: for(i=0;i<time_length;i++);
   00B0 7E 00               453 	mov	r6,#0x00
   00B2                     454 00101$:
   00B2 C3                  455 	clr	c
   00B3 EE                  456 	mov	a,r6
   00B4 9F                  457 	subb	a,r7
   00B5 50 03               458 	jnc	00105$
   00B7 0E                  459 	inc	r6
   00B8 80 F8               460 	sjmp	00101$
   00BA                     461 00105$:
   00BA 22                  462 	ret
                            463 ;------------------------------------------------------------
                            464 ;Allocation info for local variables in function 'Start_I2c'
                            465 ;------------------------------------------------------------
                            466 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:53: void Start_I2c()
                            467 ;	-----------------------------------------
                            468 ;	 function Start_I2c
                            469 ;	-----------------------------------------
   00BB                     470 _Start_I2c:
                            471 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:55: SDA=1;     /*发送起始条件的数据信号*/
   00BB D2 96               472 	setb	_P1_6
                            473 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:56: Delay1us(1);
   00BD 75 82 01            474 	mov	dpl,#0x01
   00C0 12 00 AE            475 	lcall	_Delay1us
                            476 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:57: SCL=1;
   00C3 D2 97               477 	setb	_P1_7
                            478 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:58: Delay1us(5);      /*起始条件建立时间大于4.7us,延时*/
   00C5 75 82 05            479 	mov	dpl,#0x05
   00C8 12 00 AE            480 	lcall	_Delay1us
                            481 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:60: SDA=0;     /*发送起始信号*/
   00CB C2 96               482 	clr	_P1_6
                            483 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:61: Delay1us(5);      /* 起始条件锁定时间大于4μs*/
   00CD 75 82 05            484 	mov	dpl,#0x05
   00D0 12 00 AE            485 	lcall	_Delay1us
                            486 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:63: SCL=0;     /*钳住I2C总线，准备发送或接收数据 */
   00D3 C2 97               487 	clr	_P1_7
                            488 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:64: Delay1us(2);
   00D5 75 82 02            489 	mov	dpl,#0x02
   00D8 02 00 AE            490 	ljmp	_Delay1us
                            491 ;------------------------------------------------------------
                            492 ;Allocation info for local variables in function 'Stop_I2c'
                            493 ;------------------------------------------------------------
                            494 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:72: void Stop_I2c()
                            495 ;	-----------------------------------------
                            496 ;	 function Stop_I2c
                            497 ;	-----------------------------------------
   00DB                     498 _Stop_I2c:
                            499 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:74: SDA=0;    /*发送结束条件的数据信号*/
   00DB C2 96               500 	clr	_P1_6
                            501 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:75: Delay1us(1);     /*发送结束条件的时钟信号*/
   00DD 75 82 01            502 	mov	dpl,#0x01
   00E0 12 00 AE            503 	lcall	_Delay1us
                            504 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:76: SCL=1;    /*结束条件建立时间大于4us*/
   00E3 D2 97               505 	setb	_P1_7
                            506 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:77: Delay1us(5);
   00E5 75 82 05            507 	mov	dpl,#0x05
   00E8 12 00 AE            508 	lcall	_Delay1us
                            509 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:79: SDA=1;    /*发送I2C总线结束信号*/
   00EB D2 96               510 	setb	_P1_6
                            511 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:80: Delay1us(4);
   00ED 75 82 04            512 	mov	dpl,#0x04
   00F0 02 00 AE            513 	ljmp	_Delay1us
                            514 ;------------------------------------------------------------
                            515 ;Allocation info for local variables in function 'SendByte'
                            516 ;------------------------------------------------------------
                            517 ;c                         Allocated to registers r7 
                            518 ;BitCnt                    Allocated to registers r6 
                            519 ;------------------------------------------------------------
                            520 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:90: void   SendByte(uchar c)
                            521 ;	-----------------------------------------
                            522 ;	 function SendByte
                            523 ;	-----------------------------------------
   00F3                     524 _SendByte:
   00F3 AF 82               525 	mov	r7,dpl
                            526 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:94: for(BitCnt=0;BitCnt<8;BitCnt++)   /*要传送的数据长度为8位*/
   00F5 7E 00               527 	mov	r6,#0x00
   00F7                     528 00107$:
   00F7 BE 08 00            529 	cjne	r6,#0x08,00118$
   00FA                     530 00118$:
   00FA 50 38               531 	jnc	00110$
                            532 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:96: if((c<<BitCnt)&0x80)SDA=1;    /*判断发送位*/
   00FC 8F 04               533 	mov	ar4,r7
   00FE 7D 00               534 	mov	r5,#0x00
   0100 8E F0               535 	mov	b,r6
   0102 05 F0               536 	inc	b
   0104 80 06               537 	sjmp	00121$
   0106                     538 00120$:
   0106 EC                  539 	mov	a,r4
   0107 2C                  540 	add	a,r4
   0108 FC                  541 	mov	r4,a
   0109 ED                  542 	mov	a,r5
   010A 33                  543 	rlc	a
   010B FD                  544 	mov	r5,a
   010C                     545 00121$:
   010C D5 F0 F7            546 	djnz	b,00120$
   010F EC                  547 	mov	a,r4
   0110 30 E7 04            548 	jnb	acc.7,00102$
   0113 D2 96               549 	setb	_P1_6
   0115 80 02               550 	sjmp	00103$
   0117                     551 00102$:
                            552 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:97: else   SDA=0;               
   0117 C2 96               553 	clr	_P1_6
   0119                     554 00103$:
                            555 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:98: Delay1us(1);
   0119 75 82 01            556 	mov	dpl,#0x01
   011C C0 07               557 	push	ar7
   011E C0 06               558 	push	ar6
   0120 12 00 AE            559 	lcall	_Delay1us
                            560 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:100: SCL=1;                /*置时钟线为高，通知被控器开始接收数据位*/      
   0123 D2 97               561 	setb	_P1_7
                            562 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:101: Delay1us(5);              /*保证时钟高电平周期大于4μs*/
   0125 75 82 05            563 	mov	dpl,#0x05
   0128 12 00 AE            564 	lcall	_Delay1us
   012B D0 06               565 	pop	ar6
   012D D0 07               566 	pop	ar7
                            567 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:103: SCL=0;
   012F C2 97               568 	clr	_P1_7
                            569 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:94: for(BitCnt=0;BitCnt<8;BitCnt++)   /*要传送的数据长度为8位*/
   0131 0E                  570 	inc	r6
   0132 80 C3               571 	sjmp	00107$
   0134                     572 00110$:
                            573 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:106: Delay1us(2);
   0134 75 82 02            574 	mov	dpl,#0x02
   0137 12 00 AE            575 	lcall	_Delay1us
                            576 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:107: SDA=1;                 /*8位发送完后释放数据线，准备接收应答位*/
   013A D2 96               577 	setb	_P1_6
                            578 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:108: Delay1us(2);   
   013C 75 82 02            579 	mov	dpl,#0x02
   013F 12 00 AE            580 	lcall	_Delay1us
                            581 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:109: SCL=1;
   0142 D2 97               582 	setb	_P1_7
                            583 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:110: Delay1us(3);
   0144 75 82 03            584 	mov	dpl,#0x03
   0147 12 00 AE            585 	lcall	_Delay1us
                            586 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:111: if(SDA==1)ack=0;     
   014A 30 96 04            587 	jnb	_P1_6,00105$
   014D C2 00               588 	clr	_ack
   014F 80 02               589 	sjmp	00106$
   0151                     590 00105$:
                            591 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:112: else ack=1;         /*判断是否接收到应答信号*/
   0151 D2 00               592 	setb	_ack
   0153                     593 00106$:
                            594 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:113: SCL=0;
   0153 C2 97               595 	clr	_P1_7
                            596 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:114: Delay1us(20);
   0155 75 82 14            597 	mov	dpl,#0x14
   0158 02 00 AE            598 	ljmp	_Delay1us
                            599 ;------------------------------------------------------------
                            600 ;Allocation info for local variables in function 'ISendStr'
                            601 ;------------------------------------------------------------
                            602 ;s                         Allocated to registers r7 
                            603 ;------------------------------------------------------------
                            604 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:127: __bit ISendStr(uchar s)
                            605 ;	-----------------------------------------
                            606 ;	 function ISendStr
                            607 ;	-----------------------------------------
   015B                     608 _ISendStr:
   015B AF 82               609 	mov	r7,dpl
                            610 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:130: Start_I2c();                /*启动总线*/
   015D C0 07               611 	push	ar7
   015F 12 00 BB            612 	lcall	_Start_I2c
                            613 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:131: SendByte(0xe0);             /*发送数据*/
   0162 75 82 E0            614 	mov	dpl,#0xE0
   0165 12 00 F3            615 	lcall	_SendByte
   0168 D0 07               616 	pop	ar7
                            617 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:133: SendByte(s);             /*发送数据*/
   016A 8F 82               618 	mov	dpl,r7
   016C 12 00 F3            619 	lcall	_SendByte
                            620 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:137: Stop_I2c();                 /*结束总线*/
   016F 12 00 DB            621 	lcall	_Stop_I2c
                            622 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:139: return(1);
   0172 D3                  623 	setb	c
   0173 22                  624 	ret
                            625 ;------------------------------------------------------------
                            626 ;Allocation info for local variables in function 'system_Ini'
                            627 ;------------------------------------------------------------
                            628 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:143: void system_Ini()
                            629 ;	-----------------------------------------
                            630 ;	 function system_Ini
                            631 ;	-----------------------------------------
   0174                     632 _system_Ini:
                            633 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:146: duty=5;	  // Init the backlight as off, PWM positive duty in 20%
   0174 75 23 05            634 	mov	_duty,#0x05
                            635 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:147: timer1=0; //timer for PWM
   0177 75 22 00            636 	mov	_timer1,#0x00
                            637 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:148: switching=0; //status of in process of switching
   017A 75 24 00            638 	mov	_switching,#0x00
                            639 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:149: timer2=0; //timer for switching black frame
   017D 75 25 00            640 	mov	_timer2,#0x00
                            641 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:150: timer2_goal = 0; //timer2 length setting
   0180 75 26 00            642 	mov	_timer2_goal,#0x00
                            643 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:151: sending_data =0; // if send data thru rs232
   0183 75 28 00            644 	mov	_sending_data,#0x00
                            645 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:152: buffer_pointer = 0; //if data received from rs232
   0186 75 29 00            646 	mov	_buffer_pointer,#0x00
                            647 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:154: timer2_4switch = 200; //how many PWM piorids for the black frame
   0189 75 27 C8            648 	mov	_timer2_4switch,#0xC8
                            649 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:156: time_out232=0;		//time out for no 232 data
                            650 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:157: received232=0;		//get data from 232 input
                            651 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:158: have232connected=0; //init assuming no 232					
                            652 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:162: P0M0 = 0;
                            653 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:163: P0M1 = 0;
   018C E4                  654 	clr a
   018D F5 35               655 	mov _time_out232,a
   018F F5 36               656 	mov (_time_out232 + 1),a
   0191 F5 37               657 	mov _received232,a
   0193 F5 38               658 	mov _have232connected,a
   0195 F5 00               659 	mov _P0M0,a
   0197 F5 01               660 	mov _P0M1,a
                            661 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:164: P1M0 = 0;
   0199 75 02 00            662 	mov	_P1M0,#0x00
                            663 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:165: P1M1 = 0;
   019C 75 03 00            664 	mov	_P1M1,#0x00
   019F 22                  665 	ret
                            666 ;------------------------------------------------------------
                            667 ;Allocation info for local variables in function 'rs232init'
                            668 ;------------------------------------------------------------
                            669 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:172: void rs232init()
                            670 ;	-----------------------------------------
                            671 ;	 function rs232init
                            672 ;	-----------------------------------------
   01A0                     673 _rs232init:
                            674 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:193: SCON = 0x50;      //REN=1允许串行接受状态，串口工作模式1    	       	   
   01A0 75 98 50            675 	mov	_SCON,#0x50
                            676 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:194: TMOD|= 0x20;      //定时器工作方式2                    
   01A3 43 89 20            677 	orl	_TMOD,#0x20
                            678 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:195: PCON|= 0x80;                                                          
   01A6 43 87 80            679 	orl	_PCON,#0x80
                            680 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:196: TH1  = 0xFD;     //baud*2  /* reload value 19200、数据位8、停止位1。效验位无 (11.0592) 
   01A9 75 8D FD            681 	mov	_TH1,#0xFD
                            682 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:198: TL1 = 0xF3;    
   01AC 75 8B F3            683 	mov	_TL1,#0xF3
                            684 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:211: TMOD|=0x01;		  //T0 freq setup.
   01AF 43 89 01            685 	orl	_TMOD,#0x01
                            686 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:212: TH0=0xfe;
   01B2 75 8C FE            687 	mov	_TH0,#0xFE
                            688 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:213: TL0=0xfd;
   01B5 75 8A FD            689 	mov	_TL0,#0xFD
                            690 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:214: ET0=1;
   01B8 D2 A9               691 	setb	_ET0
                            692 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:217: ES   = 1;        //开串口中断                  
   01BA D2 AC               693 	setb	_ES
                            694 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:218: EA   = 1;        // 开总中断
   01BC D2 AF               695 	setb	_EA
                            696 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:219: PS = 8; //serial port priority =1
   01BE D2 BC               697 	setb	_PS
                            698 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:221: TR0=1;
   01C0 D2 8C               699 	setb	_TR0
                            700 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:223: TR1  = 1;                                                             
   01C2 D2 8E               701 	setb	_TR1
   01C4 22                  702 	ret
                            703 ;------------------------------------------------------------
                            704 ;Allocation info for local variables in function 'send232'
                            705 ;------------------------------------------------------------
                            706 ;send_number               Allocated to registers r7 
                            707 ;------------------------------------------------------------
                            708 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:229: void send232(uchar send_number)
                            709 ;	-----------------------------------------
                            710 ;	 function send232
                            711 ;	-----------------------------------------
   01C5                     712 _send232:
   01C5 AF 82               713 	mov	r7,dpl
                            714 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:231: if(buffer_pointer<32) buffer_pointer++;
   01C7 74 E0               715 	mov	a,#0x100 - 0x20
   01C9 25 29               716 	add	a,_buffer_pointer
   01CB 40 02               717 	jc	00102$
   01CD 05 29               718 	inc	_buffer_pointer
   01CF                     719 00102$:
                            720 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:234: SenData = send_number;
   01CF 8F 2B               721 	mov	_SenData,r7
   01D1 22                  722 	ret
                            723 ;------------------------------------------------------------
                            724 ;Allocation info for local variables in function 'buffer_send'
                            725 ;------------------------------------------------------------
                            726 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:237: void buffer_send()
                            727 ;	-----------------------------------------
                            728 ;	 function buffer_send
                            729 ;	-----------------------------------------
   01D2                     730 _buffer_send:
                            731 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:239: if ((buffer_pointer>=1) && (sending_data ==0) &&(TI==0) )
   01D2 74 FF               732 	mov	a,#0x100 - 0x01
   01D4 25 29               733 	add	a,_buffer_pointer
   01D6 50 0F               734 	jnc	00102$
   01D8 E5 28               735 	mov	a,_sending_data
   01DA 70 0B               736 	jnz	00102$
   01DC 20 99 08            737 	jb	_TI,00102$
                            738 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:242: SBUF = SenData;
   01DF 85 2B 99            739 	mov	_SBUF,_SenData
                            740 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:243: sending_data=1;
   01E2 75 28 01            741 	mov	_sending_data,#0x01
                            742 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:244: buffer_pointer--;
   01E5 15 29               743 	dec	_buffer_pointer
   01E7                     744 00102$:
                            745 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:250: if( (sending_data==1)&&(TI!=0)) 
   01E7 74 01               746 	mov	a,#0x01
   01E9 B5 28 08            747 	cjne	a,_sending_data,00108$
   01EC 30 99 05            748 	jnb	_TI,00108$
                            749 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:251: {sending_data=0; TI=0;}  //check if data sent, init the status
   01EF 75 28 00            750 	mov	_sending_data,#0x00
   01F2 C2 99               751 	clr	_TI
   01F4                     752 00108$:
   01F4 22                  753 	ret
                            754 ;------------------------------------------------------------
                            755 ;Allocation info for local variables in function 'switch2mode'
                            756 ;------------------------------------------------------------
                            757 ;to_mode                   Allocated to registers r7 
                            758 ;------------------------------------------------------------
                            759 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:254: void switch2mode(uchar to_mode)
                            760 ;	-----------------------------------------
                            761 ;	 function switch2mode
                            762 ;	-----------------------------------------
   01F5                     763 _switch2mode:
   01F5 AF 82               764 	mov	r7,dpl
                            765 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:256: switching = 1;
   01F7 75 24 01            766 	mov	_switching,#0x01
                            767 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:257: timer2 = 0;
   01FA 75 25 00            768 	mov	_timer2,#0x00
                            769 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:258: timer2_goal = timer2_4switch;
   01FD 85 27 26            770 	mov	_timer2_goal,_timer2_4switch
                            771 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:260: duty=10;
   0200 75 23 0A            772 	mov	_duty,#0x0A
                            773 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:261: ISendStr(I2C_mode_codes[to_mode]);
   0203 EF                  774 	mov	a,r7
   0204 24 2C               775 	add	a,#_I2C_mode_codes
   0206 F9                  776 	mov	r1,a
   0207 87 82               777 	mov	dpl,@r1
   0209 C0 07               778 	push	ar7
   020B 12 01 5B            779 	lcall	_ISendStr
   020E D0 07               780 	pop	ar7
                            781 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:262: current_mode=to_mode;
   0210 8F 30               782 	mov	_current_mode,r7
                            783 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:263: send232(to_mode);
   0212 8F 82               784 	mov	dpl,r7
   0214 02 01 C5            785 	ljmp	_send232
                            786 ;------------------------------------------------------------
                            787 ;Allocation info for local variables in function 'main'
                            788 ;------------------------------------------------------------
                            789 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:266: main()
                            790 ;	-----------------------------------------
                            791 ;	 function main
                            792 ;	-----------------------------------------
   0217                     793 _main:
                            794 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:270: system_Ini();
   0217 12 01 74            795 	lcall	_system_Ini
                            796 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:274: rs232init();
   021A 12 01 A0            797 	lcall	_rs232init
                            798 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:276: switch2mode(3);  //to all clear
   021D 75 82 03            799 	mov	dpl,#0x03
   0220 12 01 F5            800 	lcall	_switch2mode
                            801 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:278: while(1)
   0223                     802 00120$:
                            803 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:283: if(timer1>9) 
   0223 E5 22               804 	mov	a,_timer1
   0225 24 F6               805 	add	a,#0xff - 0x09
   0227 50 05               806 	jnc	00102$
                            807 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:285: timer1=0;
   0229 75 22 00            808 	mov	_timer1,#0x00
                            809 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:286: timer2++;
   022C 05 25               810 	inc	_timer2
   022E                     811 00102$:
                            812 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:288: if(timer1>=duty) 
   022E C3                  813 	clr	c
   022F E5 22               814 	mov	a,_timer1
   0231 95 23               815 	subb	a,_duty
   0233 40 06               816 	jc	00104$
                            817 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:290: PWM1 = 0; 
   0235 C2 81               818 	clr	_P0_1
                            819 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:291: PWM2 = 0; 
   0237 C2 82               820 	clr	_P0_2
   0239 80 04               821 	sjmp	00105$
   023B                     822 00104$:
                            823 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:293: else { PWM1=1; PWM2=1; }
   023B D2 81               824 	setb	_P0_1
   023D D2 82               825 	setb	_P0_2
   023F                     826 00105$:
                            827 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:296: if (switching == 1)
   023F 74 01               828 	mov	a,#0x01
   0241 B5 24 13            829 	cjne	a,_switching,00114$
                            830 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:298: if (timer2 > timer2_goal)
   0244 C3                  831 	clr	c
   0245 E5 26               832 	mov	a,_timer2_goal
   0247 95 25               833 	subb	a,_timer2
   0249 50 20               834 	jnc	00115$
                            835 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:300: switching = 0; 
   024B 75 24 00            836 	mov	_switching,#0x00
                            837 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:301: duty=duty4modes[current_mode];
   024E E5 30               838 	mov	a,_current_mode
   0250 24 31               839 	add	a,#_duty4modes
   0252 F9                  840 	mov	r1,a
   0253 87 23               841 	mov	_duty,@r1
   0255 80 14               842 	sjmp	00115$
   0257                     843 00114$:
                            844 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:306: if (GoHaze==0)
   0257 20 86 08            845 	jb	_P0_6,00111$
                            846 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:308: switch2mode(0); //mode 0 is all haze
   025A 75 82 00            847 	mov	dpl,#0x00
   025D 12 01 F5            848 	lcall	_switch2mode
   0260 80 09               849 	sjmp	00115$
   0262                     850 00111$:
                            851 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:310: else if (GoClear==0)
   0262 20 87 06            852 	jb	_P0_7,00115$
                            853 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:312: switch2mode(3); //mode 3 is all clear
   0265 75 82 03            854 	mov	dpl,#0x03
   0268 12 01 F5            855 	lcall	_switch2mode
   026B                     856 00115$:
                            857 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:317: buffer_send(); //send the data in rs232 buffer out.	
   026B 12 01 D2            858 	lcall	_buffer_send
                            859 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:318: if ((time_out232 > 1000 )&&(have232connected==1)){
   026E C3                  860 	clr	c
   026F 74 E8               861 	mov	a,#0xE8
   0271 95 35               862 	subb	a,_time_out232
   0273 74 03               863 	mov	a,#0x03
   0275 95 36               864 	subb	a,(_time_out232 + 1)
   0277 50 AA               865 	jnc	00120$
   0279 74 01               866 	mov	a,#0x01
   027B B5 38 A5            867 	cjne	a,_have232connected,00120$
                            868 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:319: switch2mode(3); //if 232 no data time out switch to clear
   027E 75 82 03            869 	mov	dpl,#0x03
   0281 12 01 F5            870 	lcall	_switch2mode
                            871 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:320: have232connected =0;
   0284 75 38 00            872 	mov	_have232connected,#0x00
   0287 80 9A               873 	sjmp	00120$
                            874 ;------------------------------------------------------------
                            875 ;Allocation info for local variables in function 'T1zd'
                            876 ;------------------------------------------------------------
                            877 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:330: void T1zd(void) __interrupt 1  __using 0  //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断	5 is T2
                            878 ;	-----------------------------------------
                            879 ;	 function T1zd
                            880 ;	-----------------------------------------
   0289                     881 _T1zd:
   0289 C0 E0               882 	push	acc
   028B C0 D0               883 	push	psw
                            884 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:341: TH0=0xfd;
   028D 75 8C FD            885 	mov	_TH0,#0xFD
                            886 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:342: TL0=0xfd;
   0290 75 8A FD            887 	mov	_TL0,#0xFD
                            888 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:345: timer1++;
   0293 05 22               889 	inc	_timer1
                            890 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:346: if(received232 == 0 ) time_out232++;
   0295 E5 37               891 	mov	a,_received232
   0297 70 08               892 	jnz	00102$
   0299 05 35               893 	inc	_time_out232
   029B E4                  894 	clr	a
   029C B5 35 02            895 	cjne	a,_time_out232,00107$
   029F 05 36               896 	inc	(_time_out232 + 1)
   02A1                     897 00107$:
   02A1                     898 00102$:
                            899 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:347: received232 = 0;
   02A1 75 37 00            900 	mov	_received232,#0x00
   02A4 D0 D0               901 	pop	psw
   02A6 D0 E0               902 	pop	acc
   02A8 32                  903 	reti
                            904 ;	eliminated unneeded mov psw,# (no regs used in bank)
                            905 ;	eliminated unneeded push/pop dpl
                            906 ;	eliminated unneeded push/pop dph
                            907 ;	eliminated unneeded push/pop b
                            908 ;------------------------------------------------------------
                            909 ;Allocation info for local variables in function 'ser_int'
                            910 ;------------------------------------------------------------
                            911 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:354: void ser_int (void) __interrupt 4 __using 1
                            912 ;	-----------------------------------------
                            913 ;	 function ser_int
                            914 ;	-----------------------------------------
   02A9                     915 _ser_int:
                    000F    916 	ar7 = 0x0F
                    000E    917 	ar6 = 0x0E
                    000D    918 	ar5 = 0x0D
                    000C    919 	ar4 = 0x0C
                    000B    920 	ar3 = 0x0B
                    000A    921 	ar2 = 0x0A
                    0009    922 	ar1 = 0x09
                    0008    923 	ar0 = 0x08
   02A9 C0 21               924 	push	bits
   02AB C0 E0               925 	push	acc
   02AD C0 F0               926 	push	b
   02AF C0 82               927 	push	dpl
   02B1 C0 83               928 	push	dph
   02B3 C0 07               929 	push	(0+7)
   02B5 C0 06               930 	push	(0+6)
   02B7 C0 05               931 	push	(0+5)
   02B9 C0 04               932 	push	(0+4)
   02BB C0 03               933 	push	(0+3)
   02BD C0 02               934 	push	(0+2)
   02BF C0 01               935 	push	(0+1)
   02C1 C0 00               936 	push	(0+0)
   02C3 C0 D0               937 	push	psw
                            938 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:359: if(RI == 1)        //RI接受中断标志
                            939 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:361: RI = 0;		    //清除RI接受中断标志
   02C5 10 98 02            940 	jbc	_RI,00106$
   02C8 80 1A               941 	sjmp	00103$
   02CA                     942 00106$:
                            943 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:362: ReData = SBUF;  //SUBF接受/发送缓冲器
   02CA 85 99 2A            944 	mov	_ReData,_SBUF
                            945 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:365: send232(ReData);
   02CD 85 2A 82            946 	mov	dpl,_ReData
   02D0 75 D0 00            947 	mov	psw,#0x00
   02D3 12 01 C5            948 	lcall	_send232
   02D6 75 D0 08            949 	mov	psw,#0x08
                            950 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:366: received232=1;	 // get 232 data
   02D9 75 37 01            951 	mov	_received232,#0x01
                            952 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:367: time_out232=0;   //reset time out
   02DC E4                  953 	clr	a
   02DD F5 35               954 	mov	_time_out232,a
   02DF F5 36               955 	mov	(_time_out232 + 1),a
                            956 ;	/home/du/download/c51/SID_19inch_monitor_control/PWM.c:368: have232connected=1;    
   02E1 75 38 01            957 	mov	_have232connected,#0x01
   02E4                     958 00103$:
   02E4 D0 D0               959 	pop	psw
   02E6 D0 00               960 	pop	(0+0)
   02E8 D0 01               961 	pop	(0+1)
   02EA D0 02               962 	pop	(0+2)
   02EC D0 03               963 	pop	(0+3)
   02EE D0 04               964 	pop	(0+4)
   02F0 D0 05               965 	pop	(0+5)
   02F2 D0 06               966 	pop	(0+6)
   02F4 D0 07               967 	pop	(0+7)
   02F6 D0 83               968 	pop	dph
   02F8 D0 82               969 	pop	dpl
   02FA D0 F0               970 	pop	b
   02FC D0 E0               971 	pop	acc
   02FE D0 21               972 	pop	bits
   0300 32                  973 	reti
                            974 ;	eliminated unneeded mov psw,# (no regs used in bank)
                            975 	.area CSEG    (CODE)
                            976 	.area CONST   (CODE)
                            977 	.area XINIT   (CODE)
                            978 	.area CABS    (ABS,CODE)
