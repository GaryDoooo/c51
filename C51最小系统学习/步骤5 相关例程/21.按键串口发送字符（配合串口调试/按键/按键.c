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
	TMOD = 0x20;			// 定时器1工作于8位自动重载模式, 用于产生波特率
	TH1 = 0xF3;				// 波特率2400
	TL1 = 0xF3;	
	SCON = 0x50;			// 设定串行口工作方式
	PCON |= 0x80;			// 波特率倍增	  4800
	TR1 = 1;				// 启动定时器1
	IE = 0x0;				// 禁止任何中断
	while(1)
	{
		if(!K1)		// 扫描按键
		{
			delayms(10);			// 延时去抖动
			if(K1)break;
			while(!K1)
			{delayms(10);
			}
			
			 send_str();	
			
		}
		if(RI)						// 是否有数据到来
		{
			RI = 0;
			tmp = SBUF;				// 暂存接收到的数据
			tmp=255-tmp;
			P1 = tmp;				// 数据传送到P1口
			send_char(tmp);			// 回传接收到的数据
		}		
	}
}

	  void send_str()
                   // 传送字串
    {
	    unsigned char i = 0;
	    while(str[i] != '\0')
	   {
		SBUF = str[i];
		while(!TI);				// 等特数据传送
		TI = 0;					// 清除数据传送标志
		i++;					// 下一个字符
	   }	
    }

     void delayms(unsigned char ms)	
                          // 延时子程序
      {						
	     unsigned char i;
	      while(ms--)
	      {
		     for(i = 0; i < 120; i++);
	      }
      }
    