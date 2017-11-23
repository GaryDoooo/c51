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

int fd; //rs232 port rw handle
int timeout = 0; //time out for if no feedback from 

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
char *portname = "/dev/ttyUSB1";

fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
if (fd < 0)
{
        printf ("error %d opening %s: %s \n", errno, portname, strerror (errno));
        return(0);
}

set_interface_attribs (fd, B19200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
set_blocking (fd, 0);                // set no blocking
return(1);
}

unsigned char read232() 
// will send back status of reading:bit0,ie 1, is has 55 feedback, bit1, ie 2, is switching done
{
char buf [100];
int n,i;
unsigned char return_value=0;

n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read, n is number of byte read
printf("read: "); for(i=0;i<n;i++) printf("%d ", (unsigned int)buf[i]); printf("\n");

for (i=0;i<n;i++)
{
	if ((buf[i]!=55) && (buf[i]>10)) return_value |=2; // no exam 88 in case 232 wrong sending.
	if (buf[i]==55) return_value |=1;
}
return(return_value);
}

void send232(unsigned char char2send)  // The rs232 sending
{
unsigned char sending[1];

sending[0]=char2send;
printf("%d \n",char2send);
write (fd, sending, 1); 
}

int number_input(char* message, int min, int max, int has_default, int default_number)
{
    unsigned char dump, string[400];
    unsigned long i=6553555;
    //unsigned int min=0, max=10;
    
    do{
    string[0]=0;
    if(has_default == 1) printf("\n%s[default %d]:",message,default_number); else printf("\n%s:",message);
    scanf ("%[^\n]", string);
    scanf("%c", &dump);
    //printf ("You entered: %d", (unsigned int)string[0]);
    if(has_default == 1) if (string[0]== 0) return(default_number);
		if ((string[0]>47)&&(string[0]<58)) i= strtol(string, NULL,  10);
		//if(stop[0]>0) i = 6553555;
		//printf("get number i= %d\n",i);
		} while ((i< min)||(i>max));
		
    return(i);
}

int main()
{

printf("Get the number = %d", number_input("Give a number (1-10)",1,10,0,5));
while(1) printf("%c ",getchar());
}
