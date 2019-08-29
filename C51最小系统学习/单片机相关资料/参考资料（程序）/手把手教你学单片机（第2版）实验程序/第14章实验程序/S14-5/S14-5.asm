	ORG 0000H
	AJMP MAIN
	ORG 030H
MAIN:	MOV R0,#0FFH
	MOV DPTR,#TAB
START:	JNB P2.0,L0				
	JNB P2.1,L1			
	JNB P2.2,L2	
	JNB P2.3,L3			
	JNB P2.7,L7
	CJNE R0,#0FFH, NEXT
	AJMP START
NEXT:	MOV A,R0
	RL A
	JMP @A+DPTR
L0:	ACALL  DEL10MS
	JB P2.0,START
	MOV R0,#00H
	AJMP START 
L1:	ACALL  DEL10MS
	JB P2.1, START 
	MOV R0,#01H
	AJMP START 
L2:	ACALL  DEL10MS
   	JB P2.2, START 
	MOV R0,#02H
	AJMP START 
L3: 	ACALL  DEL10MS
   	JB P2.3, START 
	MOV R0,#03H
	LJMP START 
L7:	LCALL  DEL10MS
   	JB P2.7, START 
	MOV R0,#04H
	AJMP START 
TAB:	AJMP SUADD
	AJMP SUSUB
	AJMP SUMUL
	AJMP SUDIV
	AJMP DIS
SUADD :	MOV A,P1
	ADD A,P3
	MOV R1,A
	CLR A
	ADDC A,#00H
	MOV R3,A
	AJMP START
SUSUB :	MOV A,P1
	CLR C
	SUBB A,P3
	MOV R1,A
	CLR A
	RLC A
	MOV R3,A
	AJMP START
SUMUL :	MOV A,P1
	MOV B,P3
	MUL AB
	MOV R1,A
	MOV R3,B
	AJMP START
SUDIV :	MOV A,P1
	MOV B,P3
	DIV AB
	MOV R1,A
	MOV R3,B
	AJMP START
DIS:	MOV P1,R1
	MOV P3,R3
	ACALL DEL10MS
	AJMP START
DEL10MS:MOV R5,#0BH			
F1:	MOV R7,#02H
F2:	MOV R6,#0FFH
F3:	DJNZ R6,F3
	DJNZ R7,F2
	DJNZ R5,F1
	RET
	END
