;这是关于单个DS18B20的测温程序,数据脚为P3.7,晶振是11.059MHZ
;温度传感器18B20采用器件默认的12位转化,最大转化时间要750毫秒
;用1602液晶屏显示,显示温度从00到99度,精确到0.0625度
;内存分配声明
TEMPER_L EQU 29H;用于保存读出温度的低字节
TEMPER_H EQU 28H;用于保存读出温度的高字节
T_DF EQU 27H ;FORMAT后的小数部分(decimal fraction)，半字节的温度小数(存在低四位)
T_INTEGER EQU 26H ;FORMAT后的整数部分(integer),将两字节的温度整合成1字节
FLAG1 BIT 50H;位地址50H是字节2AH的最低位，用作是否检测到DS18B20的标志位

A_BIT EQU 20h ;液晶十位数存放内存位置
B_BIT EQU 21h ;液晶个位数存放内存位置
C_BIT EQU 22H ;个位小数
D_BIT EQU 23H ;十位小数
E_BIT EQU 24H ;百位小数
F_BIT EQU 25H ;千位小数



ORG 0000H
            LJMP MAIN
ORG 0100H
MAIN:   
           LCALL   INIT_RS232
          // CLR P1.3
           LCALL T_CONVERSION;调用读温度子程序
           LCALL T_FORMAT;将读出的2字节温度格式化
           LCALL DISPLAY;调用液晶显示子程序
           LCALL D1S;延时1秒后再测
           LJMP MAIN

;--------------DS18B20的温度转换子程序,具体时序请参考资料-------------------
T_CONVERSION:        LCALL INIT_1820;先复位DS18B20
                     JB FLAG1,T_C0
                     RET ; 判断DS1820是否存在  若DS18B20不存在则返回

T_C0:                MOV A,#0CCH ; 跳过ROM匹配
                     LCALL WRITE_1820
                     MOV A,#44H ; 发出温度转换命令
                     LCALL WRITE_1820
                     LCALL D1S   ;这里等待AD转换结束,12位的话要延时750m秒
                     LCALL INIT_1820;准备读温度前先复位
                     MOV A,#0CCH ; 跳过ROM匹配
                     LCALL WRITE_1820
                     MOV A,#0BEH ; 发出读温度命令
                     LCALL WRITE_1820
                     LCALL READ_1820; 将读出的温度数据保存到28H(TEMPER_H)和29H(TEMPER_L)处
                     RET

;------DS18B20复位初始化程序-----------------------------------------
INIT_1820:   SETB P3.7
                   NOP
                   CLR P3.7
                   MOV R0,#2 ;主机发出延时500微秒的复位低脉冲
INIT0:         MOV R1,#250
                   DJNZ R1,$
                   DJNZ R0,INIT0

                   SETB P3.7;然后拉高数据线
                   NOP

                   MOV R0, #15
INIT1:         JNB P3.7, INIT3;延时60us等待DS18B20回应
                   DJNZ R0, INIT1
                   LJMP INIT4 ; 超时而没有响应
INIT3:         SETB FLAG1 ; 置标志位,表示DS1820存在
                   LJMP INIT5
INIT4:         CLR FLAG1 ; 清标志位,表示DS1820不存在
                   LJMP INIT6
INIT5:         MOV R0, #120
                   DJNZ R0, $ ; 延时240us
INIT6:         SETB P3.7
                   RET

;---------写DS18B20的子程序(有具体的时序要求)-------------------------------------
WRITE_1820:   MOV R2,#8;一共8位数据
WR0:              CLR P3.7
                     MOV R3,#6
                     DJNZ R3,$
                     RRC A
                     MOV P3.7,C
                     MOV R3,#20
                     DJNZ R3,$
                     SETB P3.7
                     NOP
                     NOP
                     DJNZ R2,WR0
                     SETB P3.7
                     RET

;------读DS18B20的程序,从DS18B20中读出两个字节的温度数据--------------------------
READ_1820:      MOV R4,#2 ; 将温度高位和低位从DS18B20中读出
                MOV R1,#TEMPER_L ; 低位存入29H(TEMPER_L)
RE0:            MOV R2,#8
RE1:            SETB P3.7
                   NOP
                   NOP
                   CLR P3.7
                   NOP
                   NOP
                   SETB P3.7
                   MOV R3,#5
                   DJNZ R3, $
                   MOV C,P3.7
                   MOV R3,#20
                   DJNZ R3, $
                   RRC A
                   DJNZ R2,RE1
                   MOV @R1,A
                   DEC R1            ; 高位存入28H(TEMPER_H)
                   DJNZ R4,RE0
                   RET

;-----整合读出的两字节温度(关于DS18B20读出的2字节温度格式请参考资料)----------
T_FORMAT:         MOV A, #0FH
                  ANL A, TEMPER_L
                  MOV T_DF, A           ;获得小数部分(4位)

                  MOV A, TEMPER_L
                  SWAP A
                  MOV TEMPER_L, A

                  MOV A, TEMPER_H
                  SWAP A
                  MOV R0, #TEMPER_L
                  XCHD A, @R0

                  MOV T_INTEGER, A       ;获得整数部分(1字节)
                  RET

;-------液晶显示的子程序(显示前先格式转换)---------------------------------------
DISPLAY:             mov a, T_INTEGER
                     mov b,#10
                     div ab
                     mov A_BIT,a ;十位存在A_BIT
					      mov B_BIT,b ;个位存在B_BIT
                     MOV A, T_DF
                     MOV R0, #C_BIT
                    MOV R2, #4
               	D0: MOV B, #10
                     MUL AB
                     MOV B, #16
                     DIV AB
                     MOV @R0, A      ;从个位小数C_BIT,到十位D_BIT,百位E_BIT,千位F_BIT
                     INC R0
                     MOV A, B
                     DJNZ R2, D0
                     ;----二进制到ASCII码转换--------------
                     MOV A, #30H
                     ORL A_BIT, A
                     ORL B_BIT, A
                     ORL C_BIT, A
                     ORL D_BIT, A
                     ORL E_BIT, A
                     ORL F_BIT, A
                     ;-------------------------------------
                 
                     
                     MOV A, A_BIT
                     LCALL TX_CHAR
   
                     MOV A, B_BIT
		               LCALL TX_CHAR
                   
                     MOV A, #2EH
                     LCALL TX_CHAR;'.'字符
                   
                     MOV A, C_BIT
		               LCALL TX_CHAR
                   
                     MOV A, D_BIT
		               LCALL TX_CHAR
                    
                     MOV A, E_BIT
		               LCALL TX_CHAR
                    
                     MOV A, F_BIT
		               LCALL TX_CHAR
                    
                     MOV A, #0DFH                        ;下面两个是摄氏度的数字符号
		               LCALL TX_CHAR
                   
                     MOV A, #43H
		               LCALL TX_CHAR
                   
                     MOV A, #0AH
		               LCALL TX_CHAR
                     
                    
                     RET


;---1mS延时(按12MHZ算)-----------------------------------------------------------------
D1mS:      MOV R7,#250
LOOP0:    NOP
              NOP
              DJNZ R7,LOOP0
              RET
;----1S延时(按12MHZ算)-----------------------------------------------------------------
D1S:       Mov R6,#4
LOOP2:    mov R5,#250
LOOP1:    LCALL D1mS
              DJNZ R5,LOOP1
              DJNZ R6,LOOP2
              RET
INIT_RS232:
	MOV SCON,#50H
	MOV TMOD,#20H
	MOV TH1,#0FDH
	SETB TR1
	SETB TI
	RET
;-----------------------
TX_CHAR:
	JNB TI,$
	CLR TI
	MOV SBUF, A
	RET
;--------------------------------------------------------------------------------------

END