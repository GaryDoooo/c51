     #include <reg51.h>
     #include <intrins.h>

     unsigned  tmp;
     char code str[] = "www.mucstudio.com.cn\n";
     void send_str();
     void delayms(unsigned char ms);
     void send_char(unsigned char txd);
     sbit	K1 = P2^7;
	 void  main(void)
{
	TMOD = 0x20;			// ��ʱ��1������8λ�Զ�����ģʽ, ���ڲ���������
	TH1 = 0xF3;				// ������2400
	TL1 = 0xF3;	
	SCON = 0x50;			// �趨���пڹ�����ʽ
	PCON |= 0x80;			// �����ʱ���	  4800
	TR1 = 1;				// ������ʱ��1
	IE = 0x0;				// ��ֹ�κ��ж�
	while(1)
	{
		if(!K1)		// ɨ�谴��
		{
			delayms(10);			// ��ʱȥ����
			if(K1)break;
			while(!K1)
			{delayms(10);
			}
			
			 send_str();	
			
		}
		if(RI)						// �Ƿ������ݵ���
		{
			RI = 0;
			tmp = SBUF;				// �ݴ���յ�������
			tmp=255-tmp;
			P1 = tmp;				// ���ݴ��͵�P1��
			send_char(tmp);			// �ش����յ�������
		}		
	}
}

	  void send_str()
                   // �����ִ�
    {
	    unsigned char i = 0;
	    while(str[i] != '\0')
	   {
		SBUF = str[i];
		while(!TI);				// �������ݴ���
		TI = 0;					// ������ݴ��ͱ�־
		i++;					// ��һ���ַ�
	   }	
    }

     void delayms(unsigned char ms)	
                          // ��ʱ�ӳ���
      {						
	     unsigned char i;
	      while(ms--)
	      {
		     for(i = 0; i < 120; i++);
	      }
      }
    