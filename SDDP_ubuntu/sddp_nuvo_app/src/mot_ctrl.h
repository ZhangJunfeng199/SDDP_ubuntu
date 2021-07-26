#ifndef __MOT_CTRL_H__
#define __MOT_CTRL_H__
#include <pthread.h>

class MotCtrl
{
public:
	int fd;
	float position;
	float percent;

	MotCtrl();
	int query_pos();
	int move_forward();
	int move_backward();
	int move_start();
	int move_stop();
	int set_zero();
	int set_pos(float p);
	
	int uart_write(const char *w_buf,size_t len);
	int uart_read(char *r_buf,size_t len);

private:
	int init();
	int set_serial(int fd,int nSpeed,int nBits,char nEvent,int nStop);
	ssize_t safe_write(int f, const void *vptr, size_t n);
	ssize_t safe_read(int f,void *vptr,size_t n);
	pthread_t thread_recv;
	static void* work_thread_recv(void *arg);
};

#endif //__MOT_CTRL_H__