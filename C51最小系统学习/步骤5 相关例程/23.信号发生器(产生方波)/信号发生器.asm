       ORG 00H
	   LJMP START
	   ORG 0BH
	   LJMP INTT0
	   ORG 30H
START:  

       MOV  TMOD,#00000010B
	   MOV  TCON,#00010000B
	   MOV  IE  ,#10000010B
	   MOV  TH0,#0D2H    //¶¨Ê±50US
	   MOV  TL0,#0D2H	  //TH0===TL0

	   AJMP $

INTT0: 

	  CPL  P1.0//50US1//50US0
      RETI

	  END