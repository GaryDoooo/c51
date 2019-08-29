;********************************************************************************
;                       跑马灯试验	       										*
;																				*
;       开机8个灯循环点亮。                                                     *
;       硬件连接：p1口8路指示灯，												*

;********************************************************************************

	ORG 0000H	  ;程序0000起始地址
	AJMP MAIN	  ;跳转到MAIN

	ORG 030H      ;MAIN 程序起始地址
MAIN:	MOV P1,#0FEH
	ACALL DEL	    ;调用子程序
	MOV P1,#0FDH	;将立即数传给P2
	ACALL DEL
	MOV P1,#0FBH
	ACALL DEL
	MOV P1,#0F7H
	ACALL DEL
	MOV P1,#0EFH
	ACALL DEL
	MOV P1,#0DFH
	ACALL DEL
	MOV P1,#0BFH
	ACALL DEL
	MOV P1,#07FH
	ACALL DEL
	MOV P1,#0FFH
	AJMP MAIN 

;延时子程序
DEL:	MOV R5,#04H
DEL1:	MOV R6,#0FFH
DEL2:	MOV R7,#0FFH
DEL3:	DJNZ R7, DEL3
	DJNZ R6, DEL2
	DJNZ R5, DEL1
	RET
	END
