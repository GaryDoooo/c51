

ORG 00H
JMP MAIN
ORG 30H

MAIN:
MOV A,#0
CALL LOOP ;由暗变亮子程序
MOV P1,#0FFH ;关灯,全暗
MOV A,#0
CALL LOOP2 ;由亮变暗子程序
MOV P1,#0 ;开灯,全亮
JMP MAIN


LOOP:
;这一段为点亮灯的延时
MOV P1,#0 ;把灯点亮
INC A  ;A的值加1
CJNE A,#0FFH,E2 ;A还没有加到FF,跳转E2
E1:JMP OVER ;A加到了FF,结束返回
E2:MOV R7,A ;A的值存入R7
D1:MOV R6,#30 ;延时子程序
DJNZ R6,$ 
DJNZ R7,D1 ;R7-1不为零就转D1,这里R7即上面预置的A值,用在这里,就是每次延时时间不同,有255级
MOV P1,#0FFH ;延时时间到,送所有灯

;这一段为关掉灯的延时,两段相加,组成占空比可变的方波输出控制灯由暗到亮
CPL A  ;A的值取反,
MOV R7,A 
D2:MOV R6,#30 ;延时子程序
DJNZ R6,$
DJNZ R7,D2
CPL A  ;再取反,恢复原来的值
JMP LOOP ;跳回循环
OVER:RET


;以下为由亮变暗子程序,原理与上面一样.
LOOP2:
MOV P1,#0FFH 
INC A  ;程序运行到此,A的值为0,经这一步后为1
CJNE A,#0FFH,W2
W1:JMP OVER2
W2:
MOV R7,A
D11:MOV R6,#30
DJNZ R6,$
DJNZ R7,D11
MOV P1,#0

CPL A
MOV R7,A
D22:MOV R6,#30
DJNZ R6,$
DJNZ R7,D22
CPL A
JMP LOOP2
OVER2:RET

END
