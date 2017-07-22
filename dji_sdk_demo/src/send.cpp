#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<time.h>
#define MAX_BUFFER_SIZE 512

int fd;

int open_serial()
{
    fd = open("/dev/ttyTHS2",O_RDWR | O_NOCTTY | O_NONBLOCK);
    if(fd == -1)
    {
        perror("open serial port error!\n");
        return -1;
    }

    printf("Open serial port success!");
    return 0;
}

int sendpadpass(unsigned short int a,unsigned  short int b,unsigned  short int c,unsigned  short int d,unsigned short int e)
{
	unsigned short int sbuf[7] = { 0xaa };
	sbuf[1] = a;
	sbuf[2] = b;
	sbuf[3] = c;
	sbuf[4] = d;
    	sbuf[5] = e;
	for(int i=1;i<=5;i++) printf("( %d ) , ",sbuf[i]);
	printf("\n");
	unsigned short int end_buf = 0;
	for (int i = 1; i <= 5; i++)
    {
        unsigned short int t_h = sbuf[i] >> 8;
	    end_buf += (sbuf[i] % 256);
        end_buf += t_h;
	    printf("-%d-", end_buf);
    }
    sbuf[6] = end_buf;
    int length = sizeof(sbuf);
	return write(fd, sbuf, length);
}
int Send(unsigned short int a, unsigned short int b, unsigned short int c,unsigned short int d,unsigned short int e)
{
    int retv;
    struct termios option;

	retv = open_serial();
    if(retv <0)
    {
        perror("open serial port error!\n");
        return -1;
    }

    printf("Ready for sendingdata...\n");

    tcgetattr(fd,&option);
    cfmakeraw(&option);

    cfsetispeed(&option,B115200);
    cfsetospeed(&option,B115200);

    tcsetattr(fd, TCSANOW,&option);

	retv = sendpadpass(a, b, c, d, e);
    if(retv == -1)
    {
        perror("Write data error!\n");
        return -1;
    }
	retv = close(fd);
	if(retv == -1)
    {
        perror("close serial data error!\n");
        return -1;
    }
    printf("The number of charsent is %d\n", retv);
    return 0;
}
