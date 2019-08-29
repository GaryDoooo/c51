 /*************************本程序实现按键来实现计数功能****************************
 S4 关闭数码管	显示
 S3 按键计数
 **********************************************************************************/
        	 
		   KEY  BIT  P2.6		//S4
		   KEY1 BIT  P2.7		//S3
		  
		   ORG 00H
		   LJMP START
		   ORG 30H

START: 
          MOV   30H,#0
		  MOV   31H,#0
		  MOV   32H,#0
		  MOV   33H,#0 
		  MOV   R3, #0//软件计数
		  MOV   R4, #0
		  CLR   20H.0

MAIN:

   		  JB    20H.0,DISPLAY_OFF

	      LCALL DISPLAY	 //8MS
DISPLAY_OFF:
		  JNB   KEY, KEY_PRO//
		  JNB   KEY1,KEY_PRO_1
		  AJMP MAIN

KEY_PRO_1:
          LCALL DL10MS
		  JB    KEY1,MAIN
KEY_REPAT_1:
          LCALL DL10MS
		  JNB   KEY1,KEY_REPAT_1

		  CPL   20H.0
		  AJMP  MAIN







KEY_PRO:  
          //LCALL DL10MS
		  LCALL DISPLAY
		  JB    KEY,MAIN

KEY_REPAT:
          LCALL DISPLAY
		  JNB   KEY,KEY_REPAT

		  INC   R3	  //个位十位 //60
		  CJNE  R3,#60,OUT
		  MOV   R3,#0

		  INC   R4	 // 百位千位 //1
          CJNE  R4,#60,OUT
		  MOV   R4,#0



OUT:
          MOV   A,R3
		  MOV   B,#10
		  DIV   AB
		  MOV   32H,A
		  MOV   33H,B

		  MOV   A,R4
		  MOV   B,#10
		  DIV   AB
		  MOV   30H,A
		  MOV   31H,B


          AJMP MAIN




DISPLAY:  MOV   DPTR,#TAB
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
        //  AJMP  START
		  RET

DL2MS:    MOV   R0,#20
DL1:      MOV   R1,#40
DL2:      DJNZ  R1,DL2
          DJNZ  R0,DL1
		  RET

DL10MS:   MOV   R5,#100
DL3:      MOV   R6,#48
DL4:      DJNZ  R6,DL4
          DJNZ  R5,DL3
		  RET

         
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
 


 
