	          ORG  00H
			  LJMP START
			  ORG  0BH
		  LJMP INTT0
			  ORG  1BH
			  LJMP INTT1
			  ORG  30H
		START: 
		      MOV  30H,#0
			  MOV  31H,#0
			  MOV  32H,#0
			  MOV  33H,#0

			
			  MOV  R1, #99  //0.1S
			  MOV  R2, #59  //1S
			  MOV  R7, #10
              
			  MOV  TMOD,#00010001B
              MOV  TCON,#01010000B
			  MOV  IE  ,#10001000B
			  MOV  TH0, #4CH
			  MOV  TL0, #00H

              MOV  TH1, #0DCH
			  MOV  TL1, #00H  // 定时器T1开始计数   

		MAIN: JB   20H.0,XX1
		      LCALL DISPLAY
	   XX1:
			  AJMP MAIN

     INTT1:   MOV  TH1,#0DCH
	          MOV  TL1,#00H
			  CPL  20H.0
			  MOV   A, R1
			  MOV   B,#10
			  DIV   AB
			  MOV   32H,A
			  MOV   33H,B

			  MOV   A, R2
			  MOV   B,#10
			  DIV   AB 
			  MOV   30H,A
			  MOV   31H,B

			 

			  DEC  R1
			  CJNE R1,#255,INTTOUT
			  MOV  R1,#99
			  DEC  R2
			  CJNE R2,#255,INTTOUT
			  MOV  R2,#0
			  //MOV  IE,#00H
			  //AJMP MAIN
			  CLR  ET1
			 SETB ET0
			 //CLR  P2.0




	  INTTOUT:

	          RETI
  
  
  INTT0:    MOV  TH0,#4CH
            MOV  TL0,#00H
			DJNZ R7,INTTOUT1
	        MOV  R7,#10
			CPL  20H.0
			CPL  P2.0
  INTTOUT1:
			RETI
			

  DISPLAY: 
	     
			    MOV   DPTR,#TAB
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
DL2MS:      MOV  34H,#20
DL1:        MOV  35H,#40
DL2:        DJNZ 35H,DL2
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