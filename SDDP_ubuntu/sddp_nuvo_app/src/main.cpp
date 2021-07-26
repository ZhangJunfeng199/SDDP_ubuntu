#include <linux/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <iostream>
#include "zmq/zmq.h"
#include "json/json.h"
#include "can_ifr.h"
#include "mot_ctrl.h"
#include "log.h"
#include <fstream>

#define ADDR_SYSTEM_STATUS_PUB	"tcp://*:5555"
#define ADDR_CTRL_REP			"tcp://*:5556"
#define ADDR_KEEPALIVE			"tcp://*:5557"

#define msleep(x)	do {usleep((x)*1000);} while(0)

void *work_thread_recv_from_pcan(void *arg);
void *work_thread_recv_from_hcan(void *arg);
void *work_thread_recv_from_xcan(void *arg);

CanIfr* can_ifr = NULL;
MotCtrl* mot_ctrl = NULL;

int main(int argc, char** argv)
{

	//MY LOG
	
	printf("test 2018-11-23\n");
	can_ifr = new CanIfr();
	if (can_ifr == NULL) {
		perror("failed to create can_ifr!\n");
		exit(1);
	}


	char w_buf[] = {0x03, 0x45, 0x00, 0x0a, 0x00, 0x07, 0x00, 0x00, 0x3d, 0x1a};
    size_t w_len = sizeof(w_buf);

	msleep(50);
	
	//
	pthread_t thread_recv_pcan;
	pthread_t thread_recv_hcan;
	pthread_t thread_recv_xcan;

	int res;

	printf("VIRHAND SELF-DRIVING DEVELOPMENT PLATFORM\n");
	printf("start...\n");

	bool rc;
	// init can interface
	res = can_ifr->init();
	if (res < 0) {
		perror("failed to init can interface\n");
		exit(1);
	}

	res = pthread_create(&thread_recv_pcan, NULL, work_thread_recv_from_pcan, (void *)can_ifr);
	if (res != 0) {
		perror("Thread creation failed: work_thread_recv_from_pcan");
		exit(1);
	}

/*
	res = pthread_create(&thread_recv_hcan, NULL, work_thread_recv_from_hcan, (void *)can_ifr);
	if (res != 0) {
		perror("Thread creation failed: work_thread_recv_from_hcan");
		exit(1);
	}

	res = pthread_create(&thread_recv_xcan, NULL, work_thread_recv_from_xcan, (void *)can_ifr);
	if (res != 0) {
		perror("Thread creation failed: work_thread_recv_from_xcan");
		exit(1);
	}
	*/

	void *thread_result;
	pthread_join(thread_recv_pcan, &thread_result);
	//pthread_join(thread_recv_hcan, &thread_result);
	//pthread_join(thread_recv_xcan, &thread_result);

	// exit app
	printf("Exit..\n");
	if (can_ifr) {
		delete can_ifr;
		can_ifr = NULL;
	}
	
	return 0;
}

void * work_thread_recv_from_pcan(void *arg)
{
	FILE* pCAN_recv;
	canHandle hnd;
	canStatus stat;

	CanIfr* can_ifr = (CanIfr*)arg;
	

	long id;
    unsigned char msg[8];
    unsigned int dlc;
    unsigned int flag;
    unsigned long time;
	
	//Log::instance()->enable(Log::LF_MSG, true);
	//Log::instance()->enable(Log::LT_FRAME_CAN0_RECV, true);
	//Log::instance()->ctrl (Log::CT_START);

	do {
		memset(msg, 0, sizeof(msg));

		pthread_mutex_lock(&can_ifr->mtx[CAN_CHN_P]);
		stat = canReadWait(can_ifr->hnd[CAN_CHN_P], &id, &msg, &dlc, &flag, &time, READ_WAIT_INFINITE);
		pthread_mutex_unlock(&can_ifr->mtx[CAN_CHN_P]);


		if (stat != canOK) {
			printf("can read failed\n");
			continue;
		}


		pCAN_recv = fopen("pCAN_recv.txt","a+");
		if (!(flag & canMSG_ERROR_FRAME)) {
			printf("[CANP_Rx]id:0x%04x dlc:%u data: ", (unsigned int)id, dlc);
			fprintf(pCAN_recv,"[CANP_Rx]id:0x%04x dlc:%u data: ", (unsigned int)id, dlc);
		
			if (dlc > 8) {
				dlc = 8;
			}
			for (int i = 0; i < dlc; ++i) {
				printf("%2.2x ", msg[i]);
				fprintf(pCAN_recv,"%2.2x ", msg[i]);
			}
			printf(" flags:0x%x time:%lu\n", flag, time);
			fprintf(pCAN_recv," flags:0x%x time:%lu\n", flag, time);
			if (dlc > 8) {
				dlc = 8;
			}

			pthread_mutex_lock(&can_ifr->mtx[CAN_CHN_X]);
			//can_ifr->send(CAN_CHN_X, id, &msg, dlc, flag);
			pthread_mutex_unlock(&can_ifr->mtx[CAN_CHN_X]);
      	}
		else {
			printf("ERROR FRAME");
		}
		fclose(pCAN_recv);
		
	} while (stat == canOK);
}

void * work_thread_recv_from_hcan(void *arg)
{
	float percent = 0.3f;
	while (1) {
		char key = getchar();
		if (key == '=') {
			percent += 0.1f;
			//mot_ctrl->set_pos(percent);
		} else if (key == '-') {
			percent -= 0.1f;
			//mot_ctrl->set_pos(percent);
		}
	}
}

void * work_thread_recv_from_xcan(void *arg)
{
	canStatus stat;

	CanIfr* can_ifr = (CanIfr*)arg;
	
	long id;
    unsigned char msg[8];
    unsigned int dlc;
    unsigned int flag;
    unsigned long time;
	do {
		memset(msg, 0, sizeof(msg));

		//can_ifr->mtx[CAN_CHN_X].lock();
		pthread_mutex_lock(&can_ifr->mtx[CAN_CHN_X]);
		stat = canReadWait(can_ifr->hnd[CAN_CHN_X], &id, &msg, &dlc, &flag, &time, READ_WAIT_INFINITE);
		
		pthread_mutex_unlock(&can_ifr->mtx[CAN_CHN_X]);
		//can_ifr->mtx[CAN_CHN_X].unlock();
		
		if (stat != canOK) {
			printf("can read failed\n");
			continue;
		}

		if (!(flag & canMSG_ERROR_FRAME)) {
			printf("id:0x%04x dlc:%u data: ", (unsigned int)id, dlc);
			if (dlc > 8) {
				dlc = 8;
			}
			for (int i = 0; i < dlc; ++i) {
				printf("%2.2x ", msg[i]);
			}
			printf(" flags:0x%x time:%lu\n", flag, time);
			if (dlc > 8) {
				dlc = 8;
			}

			pthread_mutex_lock(&can_ifr->mtx[CAN_CHN_P]);
			can_ifr->send(CAN_CHN_P, id, &msg, dlc, flag);
			pthread_mutex_unlock(&can_ifr->mtx[CAN_CHN_P]);
		}
		else {
			printf("ERROR FRAME");
		}
	} while (stat == canOK);
}


