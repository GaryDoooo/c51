#include <stdio.h>

#include <stdlib.h>

#include <signal.h>

#include <sys/time.h>

#include <ctype.h>

#include <string.h>

#include <errno.h>

#include <termios.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>



#define KNRM  "\x1B[0m" ////// These are for printf to console color codes

#define KRED  "\x1B[31m"

#define KGRN  "\x1B[32m"

#define KYEL  "\x1B[33m"

#define KBLU  "\x1B[34m"

#define KMAG  "\x1B[35m"

#define KCYN  "\x1B[36m"

#define KWHT  "\x1B[37m"



#define PARAMETER_FILE "parameters"



struct Waveform {

unsigned int idle1;

unsigned int idle2;

unsigned int cycle1;

unsigned int cycle2;

unsigned int voltage1;

unsigned int voltage2;

unsigned int freq1;

unsigned int freq2;

			//The waiting time (in sec), cycle #,voltage, freq for the one test round, 1 is high freq, 2 is low

unsigned int round_num; //how many rounds to repeat

float gain; //gain ratio of the amplifier

};



int fd; //rs232 port rw handle

int timeout = 0; //time out for if no feedback from

unsigned char debug = 0;



int

set_interface_attribs (int fd, int speed, int parity)

{

        struct termios tty;

        memset (&tty, 0, sizeof tty);

        if (tcgetattr (fd, &tty) != 0)

        {

                printf ("error %d from tcgetattr", errno);

                return -1;

        }



        cfsetospeed (&tty, speed);

        cfsetispeed (&tty, speed);



        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars

        // disable IGNBRK for mismatched speed tests; otherwise receive break

        // as \000 chars

        tty.c_iflag &= ~IGNBRK;         // disable break processing

        tty.c_lflag = 0;                // no signaling chars, no echo,

                                        // no canonical processing

        tty.c_oflag = 0;                // no remapping, no delays

        tty.c_cc[VMIN]  = 0;            // read doesn't block

        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout



        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl



        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,

                                        // enable reading

        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity

        tty.c_cflag |= parity;

        tty.c_cflag &= ~CSTOPB;

        tty.c_cflag &= ~CRTSCTS;



        if (tcsetattr (fd, TCSANOW, &tty) != 0)

        {

                printf ("error %d from tcsetattr", errno);

                return -1;

        }

        return 0;

}



void

set_blocking (int fd, int should_block)

{

        struct termios tty;

        memset (&tty, 0, sizeof tty);

        if (tcgetattr (fd, &tty) != 0)

        {

                printf ("error %d from tggetattr", errno);

                return;

        }



        tty.c_cc[VMIN]  = should_block ? 1 : 0;

        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout



        if (tcsetattr (fd, TCSANOW, &tty) != 0)

                printf ("error %d setting term attributes", errno);

}



/*

...

char *portname = "/dev/ttyUSB0"

 ...

int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

if (fd < 0)

{

        error_message ("error %d opening %s: %s", errno, portname, strerror (errno));

        return;

}



set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)

set_blocking (fd, 0);                // set no blocking



write (fd, "hello!\n", 7);           // send 7 character greeting



usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus

                                     // receive 25:  approx 100 uS per char transmit

char buf [100];

int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read

*/



int init232()

{

char *portname = "/dev/ttyUSB0";



fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

if (fd < 0)

{

        printf ("error %d opening %s: %s \n", errno, portname, strerror (errno));

        return(0);

}



set_interface_attribs (fd, B19200, 0);  // set speed to 115,200 bps, 8n1 (odd parity)

set_blocking (fd, 0);                // set no blocking

return(1);

}



unsigned char read232() 

// will send back status of reading:bit0,ie 1, is has 55 feedback, bit1, ie 2, is switching done

{

unsigned char buf [100];

int n,i;

unsigned char return_value=0;



n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read, n is number of byte read

if(debug) {

	printf("%s\tread: ",KBLU);

	for(i=0;i<n;i++) printf("%d ", (unsigned int)buf[i]); printf("%s\n",KNRM);

	}



for (i=0;i<n;i++)

{

	if (buf[i]==201) return_value |=1; // has been in 201 status ie no output

	if (buf[i]==202) return_value |=2; // has been in 202 status dc output

	if (buf[i]==203) return_value |=4; // has been in 203 status ac output

	if (buf[i]==211) return_value |=64; // has been set new DAC

}

if (buf[n-1]==201) return_value |=8; // end in 201 status ie no output

if (buf[n-1]==202) return_value |=16; // end in 202 status dc output

if (buf[n-1]==203) return_value |=32; // end in 203 status ac output

return(return_value);

}



void send232(unsigned char char2send)  // The rs232 sending

{

unsigned char sending[1];



sending[0]=char2send;

if (debug) printf("%s send: %d %s\n",KBLU, char2send,KNRM);

write (fd, sending, 1); 

}



int number_input(char* message, int min, int max, int has_default, int default_number)

{

    unsigned char dump, string[400];

    unsigned long i=6553555;

    //unsigned int min=0, max=10;



    do{

    string[0]=0;

    if(has_default == 1) printf("\n%s%s[default %d]:",KNRM, message,default_number); else printf("\n%s:",message);

    scanf ("%[^\n]", string);

    scanf("%c", &dump);

    //printf ("You entered: %d", (unsigned int)string[0]);

    if(has_default == 1) if (string[0]== 0) return(default_number);

		if ((string[0]>47)&&(string[0]<58)) i= strtol(string, NULL,  10);

		//if(stop[0]>0) i = 6553555;

		//printf("get number i= %d\n",i);

		} while ((i< min)||(i>max));

	 printf("\n");

    return(i);

}



int no_output(){

	int i;

	for(i=0;i<60;i++) {

		send232(201);

		usleep(10000);

		if(read232()&8) { printf("SUCCESS: set to Zero output.\n"); return(1); }

		}

	printf("%sTIMEOUT: to shut off the output. Please try to reboot the control box. If keep seeing this message, check the hardware, something wrong. Don't use the equipment.\n",KMAG);

	return(0);

}



int dc_output(){

	int i;



	for(i=0;i<30;i++){

		send232(202);

		usleep(10000);

		if(read232()&16) { printf("SUCCESS: set to DC output.\n"); return(1); }

		}

	printf("TIMEOUT: set to DC output.\n");

	return(0);

}



unsigned char set_dac(int input_dac)

{

	unsigned char dac;

	int i;



	dac= (unsigned char)input_dac;

	for(i=0;i<30;i++){

	send232(211);

	send232(dac);

	usleep(10000);

	if(read232()&64) { printf("SUCCESS: set voltage level.\n"); return(dac); }

	}

	printf("TIMEOUT: set voltage level.\n");

	return(0);

}



int ac_output(unsigned char freq, unsigned char cycle)

{

	unsigned char has_ac_ended =0;

	unsigned char read_from_232;

	int i, i_timeout;



	for (i=0; i<30; i++) {

		has_ac_ended =0;

		send232(212); send232(freq);

		send232(213); send232(cycle);

		send232(203);

		usleep(10000);

		read_from_232 = read232();

		if(read_from_232 & 8) has_ac_ended =1;

		if(i == 29) printf("TIMEOUT: start AC waveform.\n");

		if(read_from_232 & 4) { printf("SUCCESS: start AC waveform.\n"); i=30;}

		}



	i_timeout = (int)cycle * 100; //timeout time is cycle number x 100ms



	for (i=0;i<i_timeout;i++){

		if(has_ac_ended) { printf("SUCCESS: Zero output.\n"); return(1); }

		usleep(10000);

		if(read232() & 8) has_ac_ended=1;

		}

	printf("TIMEOUT: wait to set to Zero output.\n");

	no_output();

	return(0);

}



int ac_output_cont(unsigned char freq)

{

	int i;

	

	for(i=0;i<30;i++){

		send232(212); send232(freq);

		send232(213); send232(0);

		send232(203);

		usleep(10000);

		if(read232()&32) {printf("SUCCESS: set continous AC output.\n"); return(1);}

		}

	printf("TIMEOUT: set continous AC output.\n");

	return(0);

}



int para_write(struct Waveform *w)

{

	FILE *fp;



	fp=fopen( PARAMETER_FILE , "w");

	if (fp == NULL) {

  	printf("Can't open output parameter file. Exit.\n");

  	exit(0);

  	} else {

  	fprintf(fp, "idle1 idle2 voltage1 voltage2 cycle1 cycle2 freq1 freq2 round_num gain\n");

  	fprintf(fp, "%u %u %u %u %u %u %u %u %u %e\n", 

  		w->idle1, w->idle2, w->voltage1, w->voltage2, w->cycle1,

  		w->cycle2, w->freq1, w->freq2, w->round_num, w->gain);

	  	fclose(fp);

  	}

}



int para_read(struct Waveform *w)

{

	FILE *fp;

	char string[400];



	fp=fopen( PARAMETER_FILE , "r");

	if (fp == NULL) {

  	printf("Can't open input parameter file. Will create a default one.\n");

  	w->idle1=1; w->idle2=1; w->voltage1=80; w->voltage2=90; w->cycle1=100;

  	w->cycle2=100; w->freq1=1000; w->freq2=50; w->round_num=20; w->gain=50;

  	para_write(w);

  	} else {

  	fscanf (fp, "%[^\n]", string);

  	fscanf(fp, "%u %u %u %u %u %u %u %u %u %e\n",

  		&(w->idle1), &(w->idle2), &(w->voltage1), &(w->voltage2), &(w->cycle1),

  		&(w->cycle2), &(w->freq1), &(w->freq2), &(w->round_num) ,&(w->gain) );

  	fclose(fp);

  	}

}



float read_vcc()

{

unsigned char buf [100];

int n,i,j;

	no_output();

	for(j=1;j<50;j++)

		{

		read232();

		send232(221);

		usleep(100000);

		n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read, n is number of byte read

		if(debug) {

			printf("%s\tread: ",KBLU);

			for(i=0;i<n;i++) printf("%d ", (unsigned int)buf[i]); printf("%s\n",KNRM);

			}



		for (i=0;i<n-2;i++)

			{

			if (buf[i]==221) {

				return((float)( (float)buf[i+1] / (float)buf[i+2] ));

				}

			}

		//sleep(0.02);


		}

	printf("Error to read Vcc.\n");

	exit(0);

}



float gain_calibrate()

{

	float g[4],vcc; //amplifier's gain for 4 samples and vcc voltage from the controller

	//Gain = Vout/vcc/DAC; no the actual gain;

	//vcc is AD reading of Vcc/3.3V

	int i;

	unsigned char DAC, FREQ;



	printf("%sWill you redo the calibration of the amplifier's gain? Need scope connected and read the output waveform values.%s\n (1) Yes\n (2) No\n",KYEL,KNRM);

	i = number_input("Choose (1 or 2)",1,2,1,2);

	if (i==2) return(0);



	vcc = read_vcc();

	DAC= set_dac(100);

	FREQ=(unsigned char)(1);

	ac_output_cont(FREQ);

	i = number_input("Full DAC rate and 4KHz.\n Please read the Vamp and input here",0,1000,0,0);

	g[0] = (float)i /vcc/DAC;


	vcc = read_vcc();

	DAC= set_dac(50);

	FREQ=(unsigned char)(80);

	ac_output_cont(FREQ);

	i = number_input("Half DAC rate and 50Hz.\n Please read the Vamp and input here",0,1000,0,0);

	g[1] = (float)i /vcc/DAC;


	vcc = read_vcc();

	DAC= set_dac(100);

	FREQ=(unsigned char)(80);

	ac_output_cont(FREQ);

	i = number_input("Full DAC rate and 50Hz.\n Please read the Vamp and input here",0,1000,0,0);

	g[2] = (float)i /vcc/DAC;


	vcc = read_vcc();

	DAC= set_dac(50);

	FREQ=(unsigned char)(1);

	ac_output_cont(FREQ);

	i = number_input("Half DAC rate and 4KHz.\n Please read the Vamp and input here",0,1000,0,0);

	g[3] = (float)i /vcc/DAC;

	no_output();

	return( (g[0]+g[1]+g[2]+g[3])/4);

}



int main()

{

//printf("Get the number = %d", number_input("Give a number (1-10)",1,10,0,5));

int level1_input =0 , level2_input=0 , level3_input=0; //menu input for different level of menus

unsigned char DAC=80, CYCLE=1, FREQ=1; //cycle is real cycle number /10, freq is the timer1_goal in mcu, ie 4000/target_freq

struct Waveform settings;

unsigned int i, Vmax, Vmin;



init232();

para_read(&settings);

while(1){

	printf("\n%s=== Main menu ===%s\n (1) Zero output\n (2) DC output\n (3) Single switch waveform\n (4) Repeated test cycles\n (5) Output voltage calibration\n (6) Turn on/off debug mode\n (0) Quit%s\n",KGRN,KWHT,KNRM);

	level1_input = number_input("Choose (0-6)",0,6,1,1);

	if(level1_input == 0) { no_output(); printf("%s\n\n\n",KNRM); exit(0); }

	if(level1_input == 1) no_output();

	if(level1_input == 5) {

		if((settings.gain = gain_calibrate()) ==0)

			para_read(&settings);

			else

			para_write(&settings);

		}

	if(level1_input == 6) {

		if (debug) {

			printf("\nDebug mode is now OFF.\n");

			debug = 0;

			} else {

			printf("\nDebug mode is now ON.\n");

			debug = 1;

			}

		}

	if(level1_input == 2) {

		do{

		printf("\n%s=== DC output menu ===%s\n (1) Turn On DC output\n (2) Turn Off DC output\n (3) Set voltage\n (0) Turn off DC and exit to main menu%s\n",KGRN,KWHT,KNRM);

		level2_input = number_input("Choose (0-3)",0,3,1,2);

		if (level2_input == 1) dc_output();

		if (level2_input == 2) no_output();

		if (level2_input == 3) DAC = set_dac(number_input("New DAC duty% (0-100)",0,100,0,0));

		if (level2_input == 0) no_output();

		} while (level2_input != 0);

		}



	if(level1_input == 3){

		do{

		printf("\n%s=== High freq output ===%s\n Current setting: %dV %dHz %dcycles\n %s(1) Send waveform out\n (2) Change parameters\n (3) Conituous output\n",

			KGRN,KCYN, settings.voltage1, settings.freq1, settings.cycle1, KWHT);

		printf("\n%s=== Low freq output ===%s\n Current setting: %dV %dHz %dcycles\n %s(4) Send waveform out\n (5) Change parameters\n (6) Continuous output\n\n",

			KGRN,KCYN, settings.voltage2, settings.freq2, settings.cycle2, KWHT);

		printf("%s=============\n %s(7) Turn off output\n (0) Turn off output and exit to the main menu%s\n",KGRN,KWHT,KNRM);



		level2_input = number_input("Choose (0-7)",0,7,1,7);



		if(level2_input == 1) {

			DAC = settings.voltage1 / settings.gain / read_vcc();

			if ((DAC<50)||(DAC>100)){

				printf("%sVoltage setting beyond current equipment gain, skip high freq output, please reset high freq setting.%s\n",KMAG,KNRM);

				} else {

				set_dac( DAC );

				FREQ=(unsigned char) (4000/settings.freq1);

				CYCLE=(unsigned char) (settings.cycle1/10);

				ac_output(FREQ,CYCLE);

				}

			}

		if(level2_input ==2) {

			Vmax = (unsigned int)( settings.gain * read_vcc() *100 );

			Vmin = Vmax /2;

			Vmin += 2; Vmax -=2; //add tollerence

			printf("%sVoltage setting range: %uV to %uV.%s\n",KCYN,Vmin, Vmax,KNRM);

			if ((settings.voltage1 > Vmax) || (settings.voltage1 < Vmin))

				settings.voltage1 = number_input("High freq -- Input the voltage",Vmin,Vmax,1,Vmin);

				else

				settings.voltage1 = number_input("High freq -- Input the voltage",Vmin,Vmax,1,settings.voltage1);

			settings.freq1 = number_input("High freq -- Input freq (Hz)(500-4000)",500,4000,1,settings.freq1);

			settings.cycle1 = number_input("High freq -- Input # of cycles (10-2000)",10,2000,1,settings.cycle1);

			para_write(&settings);

			}

		if(level2_input == 3) {

			DAC = settings.voltage1 / settings.gain / read_vcc();

			if ((DAC<50)||(DAC>100)){

				printf("%sVoltage setting beyond current equipment gain, skip high freq output, please reset high freq setting.\n%s",KMAG,KNRM);

				} else {

				set_dac( DAC );

				FREQ=(unsigned char)(4000/settings.freq1);

				ac_output_cont(FREQ);

				}

			}



		//level2_input = number_input("Choose (1-5)",1,5,1,4);

		if(level2_input == 4) {

			DAC = settings.voltage2 / settings.gain / read_vcc();

			if ((DAC<50)||(DAC>100)){

				printf("%sVoltage setting beyond current equipment gain, skip low freq output, please reset low freq setting.%s\n", KMAG,KNRM);

				} else {

				set_dac( DAC );

				//DAC= set_dac( settings.voltage2 );

				FREQ=(unsigned char) (4000/settings.freq2);

				CYCLE=(unsigned char) (settings.cycle2/10);

				ac_output(FREQ,CYCLE);

				}

			}

		if(level2_input ==5) {

			Vmax = (unsigned int)( settings.gain * read_vcc() *100 );

			Vmin = Vmax /2;

			Vmin += 2; Vmax -=2; //add tollerence

			printf("%sVoltage setting range: %uV to %uV.%s\n", KCYN, Vmin, Vmax, KNRM);

			if ((settings.voltage2 > Vmax) || (settings.voltage2 < Vmin))

				settings.voltage2 = number_input("Low freq -- Input the voltage",Vmin,Vmax,1,Vmin);

				else

				settings.voltage2 = number_input("Low freq -- Input the voltage",Vmin,Vmax,1,settings.voltage2);

			//settings.voltage2 = number_input("Low freq -- Input DAC duty% (50-100)",50,100,1,settings.voltage2);

			settings.freq2 = number_input("Low freq -- Input freq (Hz)(10-100)",10,100,1,settings.freq2);

			settings.cycle2 = number_input("Low freq -- Input # of cycles (10-2000)",10,2000,1,settings.cycle2);

			para_write(&settings);

			}

		if(level2_input == 6) {

			DAC = settings.voltage2 / settings.gain / read_vcc();

			if ((DAC<50)||(DAC>100)){

				printf("%sVoltage setting beyond current equipment gain, skip low freq output, please reset low freq setting.%s\n",KMAG,KNRM);

				} else {

				set_dac( DAC );

				//DAC= set_dac(settings.voltage2);

				FREQ=(unsigned char)(4000/settings.freq2);

				ac_output_cont(FREQ);

				}

			}

		if(level2_input == 7) no_output();

		if(level2_input == 0) no_output();

		} while(level2_input != 0);

		}



	if(level1_input == 4){

		do{

		printf("\n%s=== Repeat cycles menu ===%s\n Current setting:\n Low freq: %dV %dHz %dcycles\n High freq: %dV %dHz %dcycles\n Idle before low freq %d sec, Idle before high freq %d sec, total repeat %d times\n\n %s(1) Send waveform out\n (2) Change parameters\n (0) Exit to the main menu\n%s",

			KGRN,KCYN, settings.voltage2, settings.freq2, settings.cycle2, settings.voltage1,

			settings.freq1, settings.cycle1, settings.idle1, settings.idle2, settings.round_num,

			KWHT,KNRM);

		level2_input = number_input("Choose (0-2)",0,2,0,0);

		if(level2_input == 1) {

			for(i=0;i<settings.round_num;i++)

				{

				printf("%sUse ctrl-C to exit program if need stop.", KRED);

				printf("\t%sRepeat time # %s %u/%u %s\n", KBLU, KYEL,i+1,settings.round_num, KNRM);

				printf("High Freq:\n");

				DAC = settings.voltage1 / settings.gain / read_vcc();

				if ((DAC<50)||(DAC>100)){

					printf("%sVoltage setting beyond current equipment gain, skip high freq output, please reset high freq setting.\n%s", KMAG, KNRM);

					} else {

					set_dac( DAC );

					//DAC= set_dac( settings.voltage1 );

					sleep(settings.idle1);

					FREQ=(unsigned char) (4000/settings.freq1);

					CYCLE=(unsigned char) (settings.cycle1/10);

					ac_output(FREQ,CYCLE);

					}



				printf("Low Freq:\n");

				DAC = settings.voltage2 / settings.gain / read_vcc();

				if ((DAC<50)||(DAC>100)){

					printf("%sVoltage setting beyond current equipment gain, skip low freq output, please reset low freq setting.%s\n", KMAG, KNRM);

					} else {

					set_dac( DAC );

					//DAC= set_dac( settings.voltage2 );

					sleep(settings.idle2);

					FREQ=(unsigned char) (4000/settings.freq2);

					CYCLE=(unsigned char) (settings.cycle2/10);

					ac_output(FREQ,CYCLE);

					}

				}

			}

		if(level2_input ==2) {

			/* settings.voltage2 = number_input("Low freq -- Input DAC duty% (50-100)",50,100,1,settings.voltage2);

			settings.freq2 = number_input("Low freq -- Input freq (Hz)(10-100)",10,100,1,settings.freq2);

			settings.cycle2 = number_input("Low freq -- Input # of cycles (0-2000)",0,2000,1,settings.cycle2);

			settings.voltage1 = number_input("High freq -- Input DAC duty% (50-100)",50,100,1,settings.voltage1);

			settings.freq1 = number_input("High freq -- Input freq (Hz)(500-4000)",500,4000,1,settings.freq1);

			settings.cycle1 = number_input("High freq -- Input # of cycles (0-2000)",0,2000,1,settings.cycle1);

			*/

			printf("%sTo modify the switching voltage, Hz and waveform cycle#, use the Single Switch menu.%s\n",KYEL,KNRM);

			settings.idle1 = number_input("Idle sec before low freq output (0-3000)",0,3000,1,settings.idle1);

			settings.idle2 = number_input("Idle sec before high freq output (0-3000)",0,3000,1,settings.idle2);

			settings.round_num = number_input("Total repeat times (1-60000)",1,60000,1,settings.round_num);

			para_write(&settings);

			}

		} while(level2_input != 0);

		}

}

}



/************* color code sample ***********

#include <stdio.h>



#define KNRM  "\x1B[0m"

#define KRED  "\x1B[31m"

#define KGRN  "\x1B[32m"

#define KYEL  "\x1B[33m"

#define KBLU  "\x1B[34m"

#define KMAG  "\x1B[35m"

#define KCYN  "\x1B[36m"

#define KWHT  "\x1B[37m"



int main()

{

    printf("%sred\n", KRED);

    printf("%sgreen\n", KGRN);

    printf("%syellow\n", KYEL);

    printf("%sblue\n", KBLU);

    printf("%smagenta\n", KMAG);

    printf("%scyan\n", KCYN);

    printf("%swhite\n", KWHT);

    printf("%snormal\n", KNRM);



    return 0;

}

******************************************/

