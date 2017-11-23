﻿#include <stdio.h>Z#include <stdlib.h>Z#include <signal.h>Z#include <sys/time.h>Z#include <ctype.h>Z#include <string.h>Z#include <errno.h>Z#include <termios.h>Z#include <unistd.h>Z#include <sys/types.h>Z#include <sys/stat.h>Z#include <fcntl.h>ZZ#define KNRM  "\x1B[0m" ////// These are for printf to console color codesZ#define KRED  "\x1B[31m"Z#define KGRN  "\x1B[32m"Z#define KYEL  "\x1B[33m"Z#define KBLU  "\x1B[34m"Z#define KMAG  "\x1B[35m"Z#define KCYN  "\x1B[36m"Z#define KWHT  "\x1B[37m"ZZ#define PARAMETER_FILE "parameters"ZZstruct Waveform {Zunsigned int idle1;Zunsigned int idle2;Zunsigned int cycle1;Zunsigned int cycle2;Zunsigned int voltage1;Zunsigned int voltage2;Zunsigned int freq1;Zunsigned int freq2;Z			//The waiting time (in sec), cycle #,voltage, freq for the one test round, 1 is high freq, 2 is lowZunsigned int round_num; //how many rounds to repeatZfloat gain; //gain ratio of the amplifierZ};ZZint fd; //rs232 port rw handleZint timeout = 0; //time out for if no feedback fromZunsigned char debug = 0;ZZintZset_interface_attribs (int fd, int speed, int parity)Z{Z        struct termios tty;Z        memset (&tty, 0, sizeof tty);Z        if (tcgetattr (fd, &tty) != 0)Z        {Z                printf ("error %d from tcgetattr", errno);Z                return -1;Z        }ZZ        cfsetospeed (&tty, speed);Z        cfsetispeed (&tty, speed);ZZ        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit charsZ        // disable IGNBRK for mismatched speed tests; otherwise receive breakZ        // as \000 charsZ        tty.c_iflag &= ~IGNBRK;         // disable break processingZ        tty.c_lflag = 0;                // no signaling chars, no echo,Z                                        // no canonical processingZ        tty.c_oflag = 0;                // no remapping, no delaysZ        tty.c_cc[VMIN]  = 0;            // read doesn't blockZ        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeoutZZ        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrlZZ        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,Z                                        // enable readingZ        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parityZ        tty.c_cflag |= parity;Z        tty.c_cflag &= ~CSTOPB;Z        tty.c_cflag &= ~CRTSCTS;ZZ        if (tcsetattr (fd, TCSANOW, &tty) != 0)Z        {Z                printf ("error %d from tcsetattr", errno);Z                return -1;Z        }Z        return 0;Z}ZZvoidZset_blocking (int fd, int should_block)Z{Z        struct termios tty;Z        memset (&tty, 0, sizeof tty);Z        if (tcgetattr (fd, &tty) != 0)Z        {Z                printf ("error %d from tggetattr", errno);Z                return;Z        }ZZ        tty.c_cc[VMIN]  = should_block ? 1 : 0;Z        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeoutZZ        if (tcsetattr (fd, TCSANOW, &tty) != 0)Z                printf ("error %d setting term attributes", errno);Z}ZZ/*Z...Zchar *portname = "/dev/ttyUSB0"Z ...Zint fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);Zif (fd < 0)Z{Z        error_message ("error %d opening %s: %s", errno, portname, strerror (errno));Z        return;Z}ZZset_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)Zset_blocking (fd, 0);                // set no blockingZZwrite (fd, "hello!\n", 7);           // send 7 character greetingZZusleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plusZ                                     // receive 25:  approx 100 uS per char transmitZchar buf [100];Zint n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to readZ*/ZZint init232()Z{Zchar *portname = "/dev/ttyUSB0";ZZfd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);Zif (fd < 0)Z{Z        printf ("error %d opening %s: %s \n", errno, portname, strerror (errno));Z        return(0);Z}ZZset_interface_attribs (fd, B19200, 0);  // set speed to 115,200 bps, 8n1 (odd parity)Zset_blocking (fd, 0);                // set no blockingZreturn(1);Z}ZZunsigned char read232() Z// will send back status of reading:bit0,ie 1, is has 55 feedback, bit1, ie 2, is switching doneZ{Zunsigned char buf [100];Zint n,i;Zunsigned char return_value=0;ZZn = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read, n is number of byte readZif(debug) {Z	printf("%s\tread: ",KBLU);Z	for(i=0;i<n;i++) printf("%d ", (unsigned int)buf[i]); printf("%s\n",KNRM);Z	}ZZfor (i=0;i<n;i++)Z{Z	if (buf[i]==201) return_value |=1; // has been in 201 status ie no outputZ	if (buf[i]==202) return_value |=2; // has been in 202 status dc outputZ	if (buf[i]==203) return_value |=4; // has been in 203 status ac outputZ	if (buf[i]==211) return_value |=64; // has been set new DACZ}Zif (buf[n-1]==201) return_value |=8; // end in 201 status ie no outputZif (buf[n-1]==202) return_value |=16; // end in 202 status dc outputZif (buf[n-1]==203) return_value |=32; // end in 203 status ac outputZreturn(return_value);Z}ZZvoid send232(unsigned char char2send)  // The rs232 sendingZ{Zunsigned char sending[1];ZZsending[0]=char2send;Zif (debug) printf("%s send: %d %s\n",KBLU, char2send,KNRM);Zwrite (fd, sending, 1); Z}ZZint number_input(char* message, int min, int max, int has_default, int default_number)Z{Z    unsigned char dump, string[400];Z    unsigned long i=6553555;Z    //unsigned int min=0, max=10;ZZ    do{Z    string[0]=0;Z    if(has_default == 1) printf("\n%s%s[default %d]:",KNRM, message,default_number); else printf("\n%s:",message);Z    scanf ("%[^\n]", string);Z    scanf("%c", &dump);Z    //printf ("You entered: %d", (unsigned int)string[0]);Z    if(has_default == 1) if (string[0]== 0) return(default_number);Z		if ((string[0]>47)&&(string[0]<58)) i= strtol(string, NULL,  10);Z		//if(stop[0]>0) i = 6553555;Z		//printf("get number i= %d\n",i);Z		} while ((i< min)||(i>max));Z	 printf("\n");Z    return(i);Z}ZZint no_output(){Z	int i;Z	for(i=0;i<60;i++) {Z		send232(201);Z		usleep(10000);Z		if(read232()&8) { printf("SUCCESS: set to Zero output.\n"); return(1); }Z		}Z	printf("%sTIMEOUT: to shut off the output. Please try to reboot the control box. If keep seeing this message, check the hardware, something wrong. Don't use the equipment.\n",KMAG);Z	return(0);Z}ZZint dc_output(){Z	int i;ZZ	for(i=0;i<30;i++){Z		send232(202);Z		usleep(10000);Z		if(read232()&16) { printf("SUCCESS: set to DC output.\n"); return(1); }Z		}Z	printf("TIMEOUT: set to DC output.\n");Z	return(0);Z}ZZunsigned char set_dac(int input_dac)Z{Z	unsigned char dac;Z	int i;ZZ	dac= (unsigned char)input_dac;Z	for(i=0;i<30;i++){Z	send232(211);Z	send232(dac);Z	usleep(10000);Z	if(read232()&64) { printf("SUCCESS: set voltage level.\n"); return(dac); }Z	}Z	printf("TIMEOUT: set voltage level.\n");Z	return(0);Z}ZZint ac_output(unsigned char freq, unsigned char cycle)Z{Z	unsigned char has_ac_ended =0;Z	unsigned char read_from_232;Z	int i, i_timeout;ZZ	for (i=0; i<30; i++) {Z		has_ac_ended =0;Z		send232(212); send232(freq);Z		send232(213); send232(cycle);Z		send232(203);Z		usleep(10000);Z		read_from_232 = read232();Z		if(read_from_232 & 8) has_ac_ended =1;Z		if(i == 29) printf("TIMEOUT: start AC waveform.\n");Z		if(read_from_232 & 4) { printf("SUCCESS: start AC waveform.\n"); i=30;}Z		}ZZ	i_timeout = (int)cycle * 100; //timeout time is cycle number x 100msZZ	for (i=0;i<i_timeout;i++){Z		if(has_ac_ended) { printf("SUCCESS: Zero output.\n"); return(1); }Z		usleep(10000);Z		if(read232() & 8) has_ac_ended=1;Z		}Z	printf("TIMEOUT: wait to set to Zero output.\n");Z	no_output();Z	return(0);Z}ZZint ac_output_cont(unsigned char freq)Z{Z	int i;Z	Z	for(i=0;i<30;i++){Z		send232(212); send232(freq);Z		send232(213); send232(0);Z		send232(203);Z		usleep(10000);Z		if(read232()&32) {printf("SUCCESS: set continous AC output.\n"); return(1);}Z		}Z	printf("TIMEOUT: set continous AC output.\n");Z	return(0);Z}ZZint para_write(struct Waveform *w)Z{Z	FILE *fp;ZZ	fp=fopen( PARAMETER_FILE , "w");Z	if (fp == NULL) {Z  	printf("Can't open output parameter file. Exit.\n");Z  	exit(0);Z  	} else {Z  	fprintf(fp, "idle1 idle2 voltage1 voltage2 cycle1 cycle2 freq1 freq2 round_num gain\n");Z  	fprintf(fp, "%u %u %u %u %u %u %u %u %u %e\n", Z  		w->idle1, w->idle2, w->voltage1, w->voltage2, w->cycle1,Z  		w->cycle2, w->freq1, w->freq2, w->round_num, w->gain);Z	  	fclose(fp);Z  	}Z}ZZint para_read(struct Waveform *w)Z{Z	FILE *fp;Z	char string[400];ZZ	fp=fopen( PARAMETER_FILE , "r");Z	if (fp == NULL) {Z  	printf("Can't open input parameter file. Will create a default one.\n");Z  	w->idle1=1; w->idle2=1; w->voltage1=80; w->voltage2=90; w->cycle1=100;Z  	w->cycle2=100; w->freq1=1000; w->freq2=50; w->round_num=20; w->gain=50;Z  	para_write(w);Z  	} else {Z  	fscanf (fp, "%[^\n]", string);Z  	fscanf(fp, "%u %u %u %u %u %u %u %u %u %e\n",Z  		&(w->idle1), &(w->idle2), &(w->voltage1), &(w->voltage2), &(w->cycle1),Z  		&(w->cycle2), &(w->freq1), &(w->freq2), &(w->round_num) ,&(w->gain) );Z  	fclose(fp);Z  	}Z}ZZfloat read_vcc()Z{Zunsigned char buf [100];Zint n,i,j;Z	no_output();Z	for(j=1;j<50;j++)Z		{Z		read232();Z		send232(221);Z		usleep(100000);Z		n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read, n is number of byte readZ		if(debug) {Z			printf("%s\tread: ",KBLU);Z			for(i=0;i<n;i++) printf("%d ", (unsigned int)buf[i]); printf("%s\n",KNRM);Z			}ZZ		for (i=0;i<n-2;i++)Z			{Z			if (buf[i]==221) {Z				return((float)( (float)buf[i+1] / (float)buf[i+2] ));Z				}Z			}Z		//sleep(0.02);ZZ		}Z	printf("Error to read Vcc.\n");Z	exit(0);Z}ZZfloat gain_calibrate()Z{Z	float
 g[4],vcc; //amplifier's gain for 4 samples and vcc voltage from the controllerZ	//Gain = Vout/vcc/DAC; no the actual gain;Z	//vcc is AD reading of Vcc/3.3VZ	int i;Z	unsigned char DAC, FREQ;ZZ	printf("%sWill you redo the calibration of the amplifier's gain? Need scope connected and read the output waveform values.%s\n (1) Yes\n (2) No\n",KYEL,KNRM);Z	i = number_input("Choose (1 or 2)",1,2,1,2);Z	if (i==2) return(0);ZZ	vcc = read_vcc();Z	DAC= set_dac(100);Z	FREQ=(unsigned char)(1);Z	ac_output_cont(FREQ);Z	i = number_input("Full DAC rate and 4KHz.\n Please read the Vamp and input here",0,1000,0,0);Z	g[0] = (float)i /vcc/DAC;ZZ	vcc = read_vcc();Z	DAC= set_dac(50);Z	FREQ=(unsigned char)(80);Z	ac_output_cont(FREQ);Z	i = number_input("Half DAC rate and 50Hz.\n Please read the Vamp and input here",0,1000,0,0);Z	g[1] = (float)i /vcc/DAC;ZZ	vcc = read_vcc();Z	DAC= set_dac(100);Z	FREQ=(unsigned char)(80);Z	ac_output_cont(FREQ);Z	i = number_input("Full DAC rate and 50Hz.\n Please read the Vamp and input here",0,1000,0,0);Z	g[2] = (float)i /vcc/DAC;ZZ	vcc = read_vcc();Z	DAC= set_dac(50);Z	FREQ=(unsigned char)(1);Z	ac_output_cont(FREQ);Z	i = number_input("Half DAC rate and 4KHz.\n Please read the Vamp and input here",0,1000,0,0);Z	g[3] = (float)i /vcc/DAC;Z	no_output();Z	return( (g[0]+g[1]+g[2]+g[3])/4);Z}ZZint main()Z{Z//printf("Get the number = %d", number_input("Give a number (1-10)",1,10,0,5));Zint level1_input =0 , level2_input=0 , level3_input=0; //menu input for different level of menusZunsigned char DAC=80, CYCLE=1, FREQ=1; //cycle is real cycle number /10, freq is the timer1_goal in mcu, ie 4000/target_freqZstruct Waveform settings;Zunsigned int i, Vmax, Vmin;ZZinit232();Zpara_read(&settings);Zwhile(1){Z	printf("\n%s=== Main menu ===%s\n (1) Zero output\n (2) DC output\n (3) Single switch waveform\n (4) Repeated test cycles\n (5) Output voltage calibration\n (6) Turn on/off debug mode\n (0) Quit%s\n",KGRN,KWHT,KNRM);Z	level1_input = number_input("Choose (0-6)",0,6,1,1);Z	if(level1_input == 0) { no_output(); printf("%s\n\n\n",KNRM); exit(0); }Z	if(level1_input == 1) no_output();Z	if(level1_input == 5) {Z		if((settings.gain = gain_calibrate()) ==0)Z			para_read(&settings);Z			elseZ			para_write(&settings);Z		}Z	if(level1_input == 6) {Z		if (debug) {Z			printf("\nDebug mode is now OFF.\n");Z			debug = 0;Z			} else {Z			printf("\nDebug mode is now ON.\n");Z			debug = 1;Z			}Z		}Z	if(level1_input == 2) {Z		do{Z		printf("\n%s=== DC output menu ===%s\n (1) Turn On DC output\n (2) Turn Off DC output\n (3) Set voltage\n (0) Turn off DC and exit to main menu%s\n",KGRN,KWHT,KNRM);Z		level2_input = number_input("Choose (0-3)",0,3,1,2);Z		if (level2_input == 1) dc_output();Z		if (level2_input == 2) no_output();Z		if (level2_input == 3) DAC = set_dac(number_input("New DAC duty% (0-100)",0,100,0,0));Z		if (level2_input == 0) no_output();Z		} while (level2_input != 0);Z		}ZZ	if(level1_input == 3){Z		do{Z		printf("\n%s=== High freq output ===%s\n Current setting: %dV %dHz %dcycles\n %s(1) Send waveform out\n (2) Change parameters\n (3) Conituous output\n",Z			KGRN,KCYN, settings.voltage1, settings.freq1, settings.cycle1, KWHT);Z		printf("\n%s=== Low freq output ===%s\n Current setting: %dV %dHz %dcycles\n %s(4) Send waveform out\n (5) Change parameters\n (6) Continuous output\n\n",Z			KGRN,KCYN, settings.voltage2, settings.freq2, settings.cycle2, KWHT);Z		printf("%s=============\n %s(7) Turn off output\n (0) Turn off output and exit to the main menu%s\n",KGRN,KWHT,KNRM);ZZ		level2_input = number_input("Choose (0-7)",0,7,1,7);ZZ		if(level2_input == 1) {Z			DAC = settings.voltage1 / settings.gain / read_vcc();Z			if ((DAC<50)||(DAC>100)){Z				printf("%sVoltage setting beyond current equipment gain, skip high freq output, please reset high freq setting.%s\n",KMAG,KNRM);Z				} else {Z				set_dac( DAC );Z				FREQ=(unsigned char) (4000/settings.freq1);Z				CYCLE=(unsigned char) (settings.cycle1/10);Z				ac_output(FREQ,CYCLE);Z				}Z			}Z		if(level2_input ==2) {Z			Vmax = (unsigned int)( settings.gain * read_vcc() *100 );Z			Vmin = Vmax /2;Z			Vmin += 2; Vmax -=2; //add tollerenceZ			printf("%sVoltage setting range: %uV to %uV.%s\n",KCYN,Vmin, Vmax,KNRM);Z			if ((settings.voltage1 > Vmax) || (settings.voltage1 < Vmin))Z				settings.voltage1 = number_input("High freq -- Input the voltage",Vmin,Vmax,1,Vmin);Z				elseZ				settings.voltage1 = number_input("High freq -- Input the voltage",Vmin,Vmax,1,settings.voltage1);Z			settings.freq1 = number_input("High freq -- Input freq (Hz)(500-4000)",500,4000,1,settings.freq1);Z			settings.cycle1 = number_input("High freq -- Input # of cycles (10-2000)",10,2000,1,settings.cycle1);Z			para_write(&settings);Z			}Z		if(level2_input == 3) {Z			DAC = settings.voltage1 / settings.gain / read_vcc();Z			if ((DAC<50)||(DAC>100)){Z				printf("%sVoltage setting beyond current equipment gain, skip high freq output, please reset high freq setting.\n%s",KMAG,KNRM);Z				} else {Z				set_dac( DAC );Z				FREQ=(unsigned char)(4000/settings.freq1);Z				ac_output_cont(FREQ);Z				}Z			}ZZ		//level2_input = number_input("Choose (1-5)",1,5,1,4);Z		if(level2_input == 4) {Z			DAC = settings.voltage2 / settings.gain / read_vcc();Z			if ((DAC<50)||(DAC>100)){Z				printf("%sVoltage setting beyond current equipment gain, skip low freq output, please reset low freq setting.%s\n", KMAG,KNRM);Z				} else {Z				set_dac( DAC );Z				//DAC= set_dac( settings.voltage2 );Z				FREQ=(unsigned char) (4000/settings.freq2);Z				CYCLE=(unsigned char) (settings.cycle2/10);Z				ac_output(FREQ,CYCLE);Z				}Z			}Z		if(level2_input ==5) {Z			Vmax = (unsigned int)( settings.gain * read_vcc() *100 );Z			Vmin = Vmax /2;Z			Vmin += 2; Vmax -=2; //add tollerenceZ			printf("%sVoltage setting range: %uV to %uV.%s\n", KCYN, Vmin, Vmax, KNRM);Z			if ((settings.voltage2 > Vmax) || (settings.voltage2 < Vmin))Z				settings.voltage2 = number_input("Low freq -- Input the voltage",Vmin,Vmax,1,Vmin);Z				elseZ				settings.voltage2 = number_input("Low freq -- Input the voltage",Vmin,Vmax,1,settings.voltage2);Z			//settings.voltage2 = number_input("Low freq -- Input DAC duty% (50-100)",50,100,1,settings.voltage2);Z			settings.freq2 = number_input("Low freq -- Input freq (Hz)(10-100)",10,100,1,settings.freq2);Z			settings.cycle2 = number_input("Low freq -- Input # of cycles (10-2000)",10,2000,1,settings.cycle2);Z			para_write(&settings);Z			}Z		if(level2_input == 6) {Z			DAC = settings.voltage2 / settings.gain / read_vcc();Z			if ((DAC<50)||(DAC>100)){Z				printf("%sVoltage setting beyond current equipment gain, skip low freq output, please reset low freq setting.%s\n",KMAG,KNRM);Z				} else {Z				set_dac( DAC );Z				//DAC= set_dac(settings.voltage2);Z				FREQ=(unsigned char)(4000/settings.freq2);Z				ac_output_cont(FREQ);Z				}Z			}Z		if(level2_input == 7) no_output();Z		if(level2_input == 0) no_output();Z		} while(level2_input != 0);Z		}ZZ	if(level1_input == 4){Z		do{Z		printf("\n%s=== Repeat cycles menu ===%s\n Current setting:\n Low freq: %dV %dHz %dcycles\n High freq: %dV %dHz %dcycles\n Idle before low freq %d sec, Idle before high freq %d sec, total repeat %d times\n\n %s(1) Send waveform out\n (2) Change parameters\n (0) Exit to the main menu\n%s",Z			KGRN,KCYN, settings.voltage2, settings.freq2, settings.cycle2, settings.voltage1,Z			settings.freq1, settings.cycle1, settings.idle1, settings.idle2, settings.round_num,Z			KWHT,KNRM);Z		level2_input = number_input("Choose (0-2)",0,2,0,0);Z		if(level2_input == 1) {Z			for(i=0;i<settings.round_num;i++)Z				{Z				printf("%sUse ctrl-C to exit program if need stop.", KRED);Z				printf("\t%sRepeat time # %s %u/%u %s\n", KBLU, KYEL,i+1,settings.round_num, KNRM);Z				printf("High Freq:\n");Z				DAC = settings.voltage1 / settings.gain / read_vcc();Z				if ((DAC<50)||(DAC>100)){Z					printf("%sVoltage setting beyond current equipment gain, skip high freq output, please reset high freq setting.\n%s", KMAG, KNRM);Z					} else {Z					set_dac( DAC );Z					//DAC= set_dac( settings.voltage1 );Z					sleep(settings.idle1);Z					FREQ=(unsigned char) (4000/settings.freq1);Z					CYCLE=(unsigned char) (settings.cycle1/10);Z					ac_output(FREQ,CYCLE);Z					}ZZ				printf("Low Freq:\n");Z				DAC = settings.voltage2 / settings.gain / read_vcc();Z				if ((DAC<50)||(DAC>100)){Z					printf("%sVoltage setting beyond current equipment gain, skip low freq output, please reset low freq setting.%s\n", KMAG, KNRM);Z					} else {Z					set_dac( DAC );Z					//DAC= set_dac( settings.voltage2 );Z					sleep(settings.idle2);Z					FREQ=(unsigned char) (4000/settings.freq2);Z					CYCLE=(unsigned char) (settings.cycle2/10);Z					ac_output(FREQ,CYCLE);Z					}Z				}Z			}Z		if(level2_input ==2) {Z			/* settings.voltage2 = number_input("Low freq -- Input DAC duty% (50-100)",50,100,1,settings.voltage2);Z			settings.freq2 = number_input("Low freq -- Input freq (Hz)(10-100)",10,100,1,settings.freq2);Z			settings.cycle2 = number_input("Low freq -- Input # of cycles (0-2000)",0,2000,1,settings.cycle2);Z			settings.voltage1 = number_input("High freq -- Input DAC duty% (50-100)",50,100,1,settings.voltage1);Z			settings.freq1 = number_input("High freq -- Input freq (Hz)(500-4000)",500,4000,1,settings.freq1);Z			settings.cycle1 = number_input("High freq -- Input # of cycles (0-2000)",0,2000,1,settings.cycle1);Z			*/Z			printf("%sTo modify the switching voltage, Hz and waveform cycle#, use the Single Switch menu.%s\n",KYEL,KNRM);Z			settings.idle1 = number_input("Idle sec before low freq output (0-3000)",0,3000,1,settings.idle1);Z			settings.idle2 = number_input("Idle sec before high freq output (0-3000)",0,3000,1,settings.idle2);Z			settings.round_num = number_input("Total
 repeat times (1-60000)",1,60000,1,settings.round_num);Z			para_write(&settings);Z			}Z		} while(level2_input != 0);Z		}Z}Z}ZZ/************* color code sample ***********Z#include <stdio.h>ZZ#define KNRM  "\x1B[0m"Z#define KRED  "\x1B[31m"Z#define KGRN  "\x1B[32m"Z#define KYEL  "\x1B[33m"Z#define KBLU  "\x1B[34m"Z#define KMAG  "\x1B[35m"Z#define KCYN  "\x1B[36m"Z#define KWHT  "\x1B[37m"ZZint main()Z{Z    printf("%sred\n", KRED);Z    printf("%sgreen\n", KGRN);Z    printf("%syellow\n", KYEL);Z    printf("%sblue\n", KBLU);Z    printf("%smagenta\n", KMAG);Z    printf("%scyan\n", KCYN);Z    printf("%swhite\n", KWHT);Z    printf("%snormal\n", KNRM);ZZ    return 0;Z}Z******************************************/Z
