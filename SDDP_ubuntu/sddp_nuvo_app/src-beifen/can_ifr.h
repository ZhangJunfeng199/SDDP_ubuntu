#ifndef __CAN_IFR_H__
#define __CAN_IFR_H__

#include <linux/can.h>
#include <canlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "vcanevt.h"

#define READ_WAIT_INFINITE    	(unsigned long)(-1)
#define CAN_CHN_NUM				(4)

#define CAN_CHN_P				(0)
#define CAN_CHN_H				(1)
#define CAN_CHN_X				(2)

class CanIfr
{
public:
	canHandle hnd[CAN_CHN_NUM];
	pthread_mutex_t mtx[CAN_CHN_NUM];

	CanIfr();
	~CanIfr();
	int init();
	int send(int chn, long id, void* msg, unsigned int dlc, unsigned int flag);
	
	static void check(const char* id, canStatus stat);
	
private:
	int open(int chn);
	
	static void notifyCallback(canNotifyData *data);
	static const char* busStatToStr(const unsigned long flag);
};

#endif // __CAN_IFR_H__

