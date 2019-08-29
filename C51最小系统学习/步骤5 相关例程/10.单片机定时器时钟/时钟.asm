                KEY_HH BIT P2.5		  //设置按键
				KEY_MM BIT P2.6
				ORG   00H
				LJMP  START
				ORG   0BH
				LJMP  INTT0
				ORG   30H
		START: 
		        MOV   30H,#0
				MOV   31H,#0
				MOV   32H,#0
				MOV   33H,#0

				MOV   TH0,#4CH
				MOV   TL0,#00H
				MOV   TMOD,#01H
				MOV   TCON,#10H
				MOV   IE,  #82H

				MOV   R0,#10

				MOV   R1,#50  //秒
				MOV   R2,#00  //分
				MOV   R3,#05  //时
 


		 MAIN:  LCALL DISPLAY
		        JNB   KEY_HH,SETHH
				JNB   KEY_MM,SETMM
		        AJMP  MAIN
 /***************************************************************/
 //设置时

  SETHH: 		LCALL DISPLAY
                LCALL DISPLAY
				JB    KEY_HH,MAIN

			    
 KEY_REPAT:     LCALL DISPLAY
                JNB   KEY_HH,KEY_REPAT

				INC   R3
				CJNE  R3,#24,MAIN_OUT
				MOV   R3,#0
	MAIN_OUT:
	            MOV   A,R3
				MOV   B,#10
				DIV   AB
				MOV   30H,A
				MOV   31H,B
                AJMP  MAIN
/****************************************************************/
//设置分部分由同学们自已编写

  SETMM:       
       			AJMP  MAIN

/****************************************************************/

DISPLAY: 
	            MOV  DPTR,#TAB

			    MOV  A,33H
			    MOVC A,@A+DPTR
			    MOV  P0,A
			    CLR  P2.3
			    LCALL DL2MS
			    SETB P2.3

			    MOV  A,32H
			    MOVC A,@A+DPTR
			   	MOV  P0,A
			    CLR  P2.2
			    LCALL DL2MS
			    SETB P2.2

		        MOV  A,31H	 
			    MOVC A,@A+DPTR
			    MOV  C, 20H.0
				MOV  ACC.7,C
			    MOV  P0,A
			    CLR  P2.1
			    LCALL DL2MS
			    SETB P2.1
		    
			    MOV  A,30H
			    MOVC A,@A+DPTR
			    MOV  P0,A
			    CLR  P2.0
			    LCALL DL2MS
			    SETB P2.0
			    RET
/*************************************************/
INTT0:  		MOV  TH0,#4CH
                MOV  TL0,#00H
				DJNZ R0,INTTOUT
				MOV  R0,#10
				CPL  20H.0//1//1//0
                JNB  20H.0,INTTOUT

                CJNE R1,#00,INTTOUT_1
				CJNE R2,#00,INTTOUT_1
				CJNE R3,#06,INTTOUT_1
				CLR  P2.0



   INTTOUT_1:             
				MOV  A,R2
				MOV  B,#10
				DIV  AB
				MOV  32H,A
				MOV  33H,B

				MOV  A,R3
				MOV  B,#10
				DIV  AB
				MOV  30H,A
				MOV  31H,B


                INC  R1
				CJNE R1,#60,INTTOUT
				MOV  R1,#0
				INC  R2
				CJNE R2,#60,INTTOUT
				MOV  R2,#0
				INC  R3
				CJNE R3,#24,INTTOUT
				MOV  R3,#0



INTTOUT:
                RETI
/*************************************************/
DL2MS:          MOV  34H,#20
DL1:            MOV  35H,#30
DL2:            DJNZ 35H,DL2
                DJNZ 34H,DL1
			    RET
/*************************************************/

TAB:            DB        0C0H;0
                DB        0F9H;1
                DB        0A4H;2
                DB        0B0H;3
                DB        099H;4
                DB        092H;5
                DB        082H;6
                DB        0F8H;7
                DB        080H;8
                DB        090H;9 ;013456789字形码


	  			END