	ORG 0000H
	LJMP MAIN
	ORG 030H
MAIN:	MOV P0,#00H
	MOV P1 ,#00H
	MOV P2 ,#00H
	MOV P3 ,#00H
	ACALL DEL
	MOV P0 ,#0FFH
	MOV P1 ,#0FFH
	MOV P2 ,#0FFH
	MOV P3 ,#0FFH
	ACALL DEL
	AJMP MAIN
	ORG 0200H
DEL:	MOV R5,#04H
F3:	MOV R6,#0FFH
F2:	MOV R7,#0FFH
F1:	DJNZ R7,F1
	DJNZ R6,F2
	DJNZ R5,F3
	RET
	END
