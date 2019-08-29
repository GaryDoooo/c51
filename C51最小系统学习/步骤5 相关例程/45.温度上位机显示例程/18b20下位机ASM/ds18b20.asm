;���ǹ��ڵ���DS18B20�Ĳ��³���,���ݽ�ΪP3.7,������11.059MHZ
;�¶ȴ�����18B20��������Ĭ�ϵ�12λת��,���ת��ʱ��Ҫ750����
;��1602Һ������ʾ,��ʾ�¶ȴ�00��99��,��ȷ��0.0625��
;�ڴ��������
TEMPER_L EQU 29H;���ڱ�������¶ȵĵ��ֽ�
TEMPER_H EQU 28H;���ڱ�������¶ȵĸ��ֽ�
T_DF EQU 27H ;FORMAT���С������(decimal fraction)�����ֽڵ��¶�С��(���ڵ���λ)
T_INTEGER EQU 26H ;FORMAT�����������(integer),�����ֽڵ��¶����ϳ�1�ֽ�
FLAG1 BIT 50H;λ��ַ50H���ֽ�2AH�����λ�������Ƿ��⵽DS18B20�ı�־λ

A_BIT EQU 20h ;Һ��ʮλ������ڴ�λ��
B_BIT EQU 21h ;Һ����λ������ڴ�λ��
C_BIT EQU 22H ;��λС��
D_BIT EQU 23H ;ʮλС��
E_BIT EQU 24H ;��λС��
F_BIT EQU 25H ;ǧλС��



ORG 0000H
            LJMP MAIN
ORG 0100H
MAIN:   
           LCALL   INIT_RS232
          // CLR P1.3
           LCALL T_CONVERSION;���ö��¶��ӳ���
           LCALL T_FORMAT;��������2�ֽ��¶ȸ�ʽ��
           LCALL DISPLAY;����Һ����ʾ�ӳ���
           LCALL D1S;��ʱ1����ٲ�
           LJMP MAIN

;--------------DS18B20���¶�ת���ӳ���,����ʱ����ο�����-------------------
T_CONVERSION:        LCALL INIT_1820;�ȸ�λDS18B20
                     JB FLAG1,T_C0
                     RET ; �ж�DS1820�Ƿ����  ��DS18B20�������򷵻�

T_C0:                MOV A,#0CCH ; ����ROMƥ��
                     LCALL WRITE_1820
                     MOV A,#44H ; �����¶�ת������
                     LCALL WRITE_1820
                     LCALL D1S   ;����ȴ�ADת������,12λ�Ļ�Ҫ��ʱ750m��
                     LCALL INIT_1820;׼�����¶�ǰ�ȸ�λ
                     MOV A,#0CCH ; ����ROMƥ��
                     LCALL WRITE_1820
                     MOV A,#0BEH ; �������¶�����
                     LCALL WRITE_1820
                     LCALL READ_1820; ���������¶����ݱ��浽28H(TEMPER_H)��29H(TEMPER_L)��
                     RET

;------DS18B20��λ��ʼ������-----------------------------------------
INIT_1820:   SETB P3.7
                   NOP
                   CLR P3.7
                   MOV R0,#2 ;����������ʱ500΢��ĸ�λ������
INIT0:         MOV R1,#250
                   DJNZ R1,$
                   DJNZ R0,INIT0

                   SETB P3.7;Ȼ������������
                   NOP

                   MOV R0, #15
INIT1:         JNB P3.7, INIT3;��ʱ60us�ȴ�DS18B20��Ӧ
                   DJNZ R0, INIT1
                   LJMP INIT4 ; ��ʱ��û����Ӧ
INIT3:         SETB FLAG1 ; �ñ�־λ,��ʾDS1820����
                   LJMP INIT5
INIT4:         CLR FLAG1 ; ���־λ,��ʾDS1820������
                   LJMP INIT6
INIT5:         MOV R0, #120
                   DJNZ R0, $ ; ��ʱ240us
INIT6:         SETB P3.7
                   RET

;---------дDS18B20���ӳ���(�о����ʱ��Ҫ��)-------------------------------------
WRITE_1820:   MOV R2,#8;һ��8λ����
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

;------��DS18B20�ĳ���,��DS18B20�ж��������ֽڵ��¶�����--------------------------
READ_1820:      MOV R4,#2 ; ���¶ȸ�λ�͵�λ��DS18B20�ж���
                MOV R1,#TEMPER_L ; ��λ����29H(TEMPER_L)
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
                   DEC R1            ; ��λ����28H(TEMPER_H)
                   DJNZ R4,RE0
                   RET

;-----���϶��������ֽ��¶�(����DS18B20������2�ֽ��¶ȸ�ʽ��ο�����)----------
T_FORMAT:         MOV A, #0FH
                  ANL A, TEMPER_L
                  MOV T_DF, A           ;���С������(4λ)

                  MOV A, TEMPER_L
                  SWAP A
                  MOV TEMPER_L, A

                  MOV A, TEMPER_H
                  SWAP A
                  MOV R0, #TEMPER_L
                  XCHD A, @R0

                  MOV T_INTEGER, A       ;�����������(1�ֽ�)
                  RET

;-------Һ����ʾ���ӳ���(��ʾǰ�ȸ�ʽת��)---------------------------------------
DISPLAY:             mov a, T_INTEGER
                     mov b,#10
                     div ab
                     mov A_BIT,a ;ʮλ����A_BIT
					      mov B_BIT,b ;��λ����B_BIT
                     MOV A, T_DF
                     MOV R0, #C_BIT
                    MOV R2, #4
               	D0: MOV B, #10
                     MUL AB
                     MOV B, #16
                     DIV AB
                     MOV @R0, A      ;�Ӹ�λС��C_BIT,��ʮλD_BIT,��λE_BIT,ǧλF_BIT
                     INC R0
                     MOV A, B
                     DJNZ R2, D0
                     ;----�����Ƶ�ASCII��ת��--------------
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
                     LCALL TX_CHAR;'.'�ַ�
                   
                     MOV A, C_BIT
		               LCALL TX_CHAR
                   
                     MOV A, D_BIT
		               LCALL TX_CHAR
                    
                     MOV A, E_BIT
		               LCALL TX_CHAR
                    
                     MOV A, F_BIT
		               LCALL TX_CHAR
                    
                     MOV A, #0DFH                        ;�������������϶ȵ����ַ���
		               LCALL TX_CHAR
                   
                     MOV A, #43H
		               LCALL TX_CHAR
                   
                     MOV A, #0AH
		               LCALL TX_CHAR
                     
                    
                     RET


;---1mS��ʱ(��12MHZ��)-----------------------------------------------------------------
D1mS:      MOV R7,#250
LOOP0:    NOP
              NOP
              DJNZ R7,LOOP0
              RET
;----1S��ʱ(��12MHZ��)-----------------------------------------------------------------
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