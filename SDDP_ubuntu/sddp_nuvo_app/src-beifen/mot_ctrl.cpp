#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


#include "mot_ctrl.h"

#define SERIAL_DEV	"/dev/ttyUSB0"
#define MAX_POS		(35)


MotCtrl::MotCtrl(): position(0)
{
	init();
}

int MotCtrl::init()
{
	fd = open(SERIAL_DEV, O_RDWR|O_NOCTTY|O_NDELAY);
	if (fd == -1) {
		perror("Open UART failed!\n");
		return -1;
	}
	set_serial(fd, 115200, 8, 'N', 1);

	int res = pthread_create(&thread_recv, NULL, &work_thread_recv, (void *)this);
	if (res != 0) {
		perror("Thread creation failed: thread_recv");
		exit(1);
	}

	return 0;
}

void* MotCtrl::work_thread_recv(void *arg)
{
	MotCtrl* mot_ctrl = (MotCtrl*)arg;
	int ret;
	unsigned char r_buf[1024];
	bzero(r_buf,1024);
	unsigned char buf[1024];
	int cnt = 0;
	int pos = 0;

	while(1) {
		ret = mot_ctrl->uart_read((char*)r_buf,1024);
		if(ret == -1) {
			if (cnt > 0) {
				for (int i = 0; i < cnt; ++i) {
					printf("%02X ", buf[i]);
				}
				printf("\n");
				if (buf[0] == 0x03 && buf[1] == 0x03 && buf[2] == 0x44) {
					
					pos |= 0xff & buf[3];
					pos <<= 8;
					pos |= 0xff & buf[4];
					pos <<= 8;
					pos |= 0xff & buf[5];
					pos <<= 8;
					pos |= 0xff & buf[6];
					mot_ctrl->position = (float)pos / 100.0f;
					printf("buf %02x %02x %02x %02x \n", buf[3], buf[4], buf[5], buf[6]);
					printf("pos %x\n", pos);
					printf("pos %d\n", pos);
 					printf("position update %.2f\n", mot_ctrl->position);
				}
				cnt = 0;
				pos = 0;
			}
			continue;
		}
		for (int i = 0; i < ret; ++i) {
			buf[cnt + i] = r_buf[i];
		}
		cnt += ret;
	}
}

int MotCtrl::move_forward()
{
	char cmd1[] = {0x03, 0x17, 0x90, 0x00, 0x00, 0x22, 0x0F, 0x00, 0x00, 0x14, 0x28, 0x00, 0x00, 0x27, 0x1A, 0x00, \
		0x00, 0x0B, 0xB8, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x59, 0x00, \
		0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, \
		0x06};
	char cmd2[] = {0x03, 0x05, 0x04, 0x2e, 0xff, 0x00, 0xec, 0xe1};
	char cmd3[] = {0x03, 0x05, 0x04, 0x2c, 0xff, 0x00, 0x4d, 0x21};
    size_t cmd1_len = sizeof(cmd1);
	size_t cmd2_len = sizeof(cmd2);
	size_t cmd3_len = sizeof(cmd3);

	uart_write(cmd1,cmd1_len);
	usleep(1000000);
	uart_write(cmd2,cmd2_len);
	usleep(1000000);
	uart_write(cmd3,cmd3_len);
	usleep(1000000);
}
int MotCtrl::move_backward()
{
	char cmd1[] = {0x03, 0x17, 0x90, 0x00, 0x00, 0x22, 0x0F, 0x00, 0x00, 0x14, 0x28, 0xFF, 0xFF, 0xFF, 0xF6, 0x00, \
		0x00, 0x0B, 0xB8, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x59, 0x00, \
		0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, \
		0x70};
    size_t cmd1_len = sizeof(cmd1);

	uart_write(cmd1,cmd1_len);
	usleep(100000);
}

int MotCtrl::move_start() {
	char cmd2[] = {0x03, 0x05, 0x04, 0x2e, 0xff, 0x00, 0xec, 0xe1};
	size_t cmd2_len = sizeof(cmd2);
	uart_write(cmd2,cmd2_len);
	usleep(100000);
	query_pos();
	usleep(100000);
}
int MotCtrl::move_stop() {
	char cmd3[] = {0x03, 0x05, 0x04, 0x2c, 0xff, 0x00, 0x4d, 0x21};
	size_t cmd3_len = sizeof(cmd3);
	uart_write(cmd3,cmd3_len);
	usleep(1000000);
}

int MotCtrl::set_zero()
{
	
}
int MotCtrl::set_pos(float p)
{
	char cmd_forward[] = {0x03, 0x17, 0x90, 0x00, 0x00, 0x22, 0x0F, 0x00, 0x00, 0x14, 0x28, 0x00, 0x00, 0x27, 0x1A, 0x00, \
			0x00, 0x0B, 0xB8, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x59, 0x00, \
			0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, \
			0x06};

	char cmd_back[] = {0x03, 0x17, 0x90, 0x00, 0x00, 0x22, 0x0F, 0x00, 0x00, 0x14, 0x28, 0xFF, 0xFF, 0xFF, 0xF6, 0x00, \
			0x00, 0x0B, 0xB8, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x59, 0x00, \
			0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, \
			0x70};
	size_t len;
	char* cmd;

	if (p > 1.0f || p < 0) {
		return -1;
	}

	float pos = MAX_POS * p;
	if (position > pos && position - pos > 0.3) {
		cmd = cmd_back;
		len = sizeof(cmd_back);
	}
	else if (position < pos && pos - position > 0.3) {
		cmd = cmd_forward;
		len = sizeof(cmd_forward);
	}
	else {
		return 0;
	}

	uart_write(cmd,len);
	usleep(100000);

	move_start();
	
	while (1) {
		query_pos();
		usleep(30000);
		if (cmd == cmd_back && (abs(pos - position) <= 0.3 || position < pos)) {
			break;
		} else if (cmd == cmd_forward && (abs(pos - position) <= 0.3 || position > pos)) {
			break;
		}
	}

	move_stop();
}



int MotCtrl::query_pos()
{
	char w_buf[] = {0x03, 0x03, 0x90, 0x00, 0x00, 0x22, 0xE9, 0x31};
    size_t w_len = sizeof(w_buf);

	uart_write(w_buf,w_len);
	usleep(10000);
}


int MotCtrl::set_serial(int f, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newttys1,oldttys1;

     /*保存原有串口配置*/
     if(tcgetattr(f,&oldttys1)!=0) 
     {
          perror("Setupserial 1");
          return -1;
     }
     memset(&newttys1,0, sizeof(newttys1));
     newttys1.c_cflag|=(CLOCAL|CREAD ); /*CREAD 开启串行数据接收，CLOCAL并打开本地连接模式*/

     newttys1.c_cflag &=~CSIZE;/*设置数据位*/
     /*数据位选择*/   
     switch(nBits)
     {
         case 7:
             newttys1.c_cflag |=CS7;
             break;
         case 8:
             newttys1.c_cflag |=CS8;
             break;
     }
     /*设置奇偶校验位*/
     switch( nEvent )
     {
         case '0':  /*奇校验*/
             newttys1.c_cflag |= PARENB;/*开启奇偶校验*/
             newttys1.c_iflag |= (INPCK | ISTRIP);/*INPCK打开输入奇偶校验；ISTRIP去除字符的第八个比特  */
             newttys1.c_cflag |= PARODD;/*启用奇校验(默认为偶校验)*/
             break;
         case 'E':/*偶校验*/
             newttys1.c_cflag |= PARENB; /*开启奇偶校验  */
             newttys1.c_iflag |= ( INPCK | ISTRIP);/*打开输入奇偶校验并去除字符第八个比特*/
             newttys1.c_cflag &= ~PARODD;/*启用偶校验*/
             break;
         case 'N': /*无奇偶校验*/
             newttys1.c_cflag &= ~PARENB;
             break;
     }
     /*设置波特率*/
    switch( nSpeed )  
    {
        case 2400:
            cfsetispeed(&newttys1, B2400);
            cfsetospeed(&newttys1, B2400);
            break;
        case 4800:
            cfsetispeed(&newttys1, B4800);
            cfsetospeed(&newttys1, B4800);
            break;
        case 9600:
            cfsetispeed(&newttys1, B9600);
            cfsetospeed(&newttys1, B9600);
            break;
        case 115200:
            cfsetispeed(&newttys1, B115200);
            cfsetospeed(&newttys1, B115200);
            break;
        default:
            cfsetispeed(&newttys1, B9600);
            cfsetospeed(&newttys1, B9600);
            break;
    }
     /*设置停止位*/
    if( nStop == 1)/*设置停止位；若停止位为1，则清除CSTOPB，若停止位为2，则激活CSTOPB*/
    {
        newttys1.c_cflag &= ~CSTOPB;/*默认为一位停止位； */
    }
    else if( nStop == 2)
    {
        newttys1.c_cflag |= CSTOPB;/*CSTOPB表示送两位停止位*/
    }

    /*设置最少字符和等待时间，对于接收字符和等待时间没有特别的要求时*/
    newttys1.c_cc[VTIME] = 0;/*非规范模式读取时的超时时间；*/
    newttys1.c_cc[VMIN]  = 0; /*非规范模式读取时的最小字符数*/
    tcflush(f ,TCIFLUSH);/*tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来 */

     /*激活配置使其生效*/
    if((tcsetattr( f, TCSANOW,&newttys1))!=0)
    {
        perror("com set error");
        return -1;
    }

    return 0;
}

int MotCtrl::uart_write(const char *w_buf,size_t len)
{
    ssize_t cnt = 0;

    cnt = safe_write(fd,w_buf,len);
    if(cnt == -1) {
        fprintf(stderr,"write error!\n");
        return -1;
    }

    return cnt;
}


int MotCtrl::uart_read(char *r_buf,size_t len)
{
    ssize_t cnt = 0;
    fd_set rfds;
    struct timeval time;

    /*将文件描述符加入读描述符集合*/
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    /*设置超时为15s*/
    time.tv_sec = 0;
    time.tv_usec = 5000;

    /*实现串口的多路I/O*/
    int ret = select(fd+1,&rfds,NULL,NULL,&time);
    switch(ret)
    {
        case -1:
            fprintf(stderr,"select error!\n");
            return -1;
        case 0:
            //fprintf(stderr,"time over!\n");
            return -1;
        default:
            cnt = safe_read(fd,r_buf,len);
            if(cnt == -1)
            {
                fprintf(stderr,"read error!\n");
                return -1;
            }
            return cnt;
    }
}

ssize_t MotCtrl::safe_write(int f, const void *vptr, size_t n)
{
    size_t  nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = (const char*)vptr;
    nleft = n;

    while(nleft > 0) {
    	if((nwritten = write(f, ptr, nleft)) <= 0) {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n);
}


ssize_t MotCtrl::safe_read(int f,void *vptr,size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr=(char*)vptr;
    nleft=n;

    while(nleft > 0) {
        if((nread = read(f,ptr,nleft)) < 0)
        {
            if(errno == EINTR)//被信号中断
                nread = 0;
            else
                return -1;
        }
        else
        if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n-nleft);
}



