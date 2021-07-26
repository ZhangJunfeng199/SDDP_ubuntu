#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "log.h"

Log* Log::p = new Log();

Log* Log::instance()
{
	return p;
}

void Log::ctrl(int ctrl_type)
{
	if (ctrl_type == CT_START && status != ST_RUNING) {
		if (status == ST_PAUSE) {
			status = ST_RUNING;
		}
		else if (status == ST_STOP) {
			init();
			status = ST_RUNING;
		}
	}
	else if (ctrl_type == CT_PAUSE && status != ST_PAUSE) {
		if (status == ST_RUNING) {
			status = ST_PAUSE;
		}
	}
	else if (ctrl_type == CT_STOP && status != ST_STOP) {
		if (status == ST_RUNING || status == ST_PAUSE) {
			status = ST_STOP;
		}
	}
	else if (ctrl_type == CT_RESTART) {
		init();
		status = ST_RUNING;
	}
}

void Log::enable(int log_type, bool enable /*= true*/)
{
	if (enable == true) {
		log_flag |= log_type;
	} 
	else {
		log_flag &= ~log_type;
	}
}

void Log::record_message(char* msg)
{
	if (status != ST_RUNING) {
		printf("status != ST_RUNING");
		return;
	}

	if (!(log_flag & LF_MSG)) {
		printf("!(log_flag & LF_MSG");
		return;
	}

	FILE* fp = fopen(file_path[LT_MESSAGE], "a+");
	if (fp == NULL) {
		printf("fp == NULL");
		return;
	}

	time_t create_time;
	create_time = time((time_t *)0);
	struct tm *create_tm = gmtime(&create_time);
	char message_time[1024];
	sprintf(message_time, "%04d%02d%02d-%02d:%02d:%02d ", create_tm->tm_year + 1900, create_tm->tm_mon + 1, \
		create_tm->tm_mday, create_tm->tm_hour, create_tm->tm_min, create_tm->tm_sec);

	fputs(message_time, fp);
	fputs(msg, fp);
	if (msg[strlen(msg) - 1] != '\n') {
		fputc('\n', fp);
	}

	fclose(fp);
}

void Log::record_frame(struct can_frame* pfr, int type)
{
	if (status != ST_RUNING) {
		return;
	}

	if (!(log_flag & (0x01 << type))) {
		return;
	}

	canid_t idFilter[] = {0x1a1, 0x132, 0x231};
	canid_t id = pfr->can_id;
	bool res = false;
	for (int i = 0; i < sizeof(idFilter) / sizeof(canid_t); ++i) {
		if (idFilter[i] == id) {
			res = true;
		}
	}
	if (res == false) {
		return;
	}

	FILE* fp = fopen(file_path[type], "a+");
	if (fp == NULL) {
		return;
	}

	time_t frame_time;
	frame_time = time((time_t *)0);
	char buf[1024];
	int n = 0;
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%ld 0x%08x 0x%02x ", frame_time, pfr->can_id, pfr->can_dlc);
	n = strlen(buf);
	char* data = (char*)pfr->data;
	for (int i = 0; i < pfr->can_dlc; ++i) {
		sprintf(&buf[n], "%02x ", data[i]);
		n = strlen(buf);
	}
	sprintf(&buf[n], "\n");
	fputs(buf, fp);

	fclose(fp);

	if ((type != LT_FRAME_ALL) && (log_flag & LF_FRAME_ALL)) {
		fp = fopen(file_path[LT_FRAME_ALL], "a+");
		if (fp == NULL) {
			return;
		}
		char prefix[1024] = "xxx_xxxx ";
		switch (type)
		{
		case LT_FRAME_CAN0_RECV:
			sprintf(prefix, "can0_recv ");
			break;
		case LT_FRAME_CAN0_SEND:
			sprintf(prefix, "can0_send ");
			break;
		case LT_FRAME_CAN1_RECV:
			sprintf(prefix, "can1_recv ");
			break;
		case LT_FRAME_CAN1_SEND:
			sprintf(prefix, "can1_send ");
			break;
		default:
			break;
		}
		fputs(prefix, fp);

		fputs(buf, fp);
		fclose(fp);
	}
}

Log::Log()
{
	log_flag = 0x00;
	status = ST_STOP;
}

Log::~Log()
{
	for (int i = 0; i < LOG_TYPE_NUM; ++i) {
		fclose(pfile[i]);
	}
}

void Log::init()
{
	if (opendir("./data") == NULL) {
		int status = mkdir("./data", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (status) {
			perror("failed to create directory for recording data\n");
		}
	}

	if (opendir("./log") == NULL) {
		int status = mkdir("./log", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if (status) {
			perror("failed to create directory for recording log\n");
		}
	}

	time_t create_time;
	create_time = time((time_t *)0);
	printf("current time: %ld\n", create_time);
	struct tm *create_tm = gmtime(&create_time);

	char file_prefix[1024];
	sprintf(file_prefix, "%04d%02d%02d-%02d:%02d:%02d", create_tm->tm_year + 1900, create_tm->tm_mon + 1,	\
		create_tm->tm_mday, create_tm->tm_hour, create_tm->tm_min, create_tm->tm_sec);

	sprintf(file_path[LT_MESSAGE], "data/%s-log.txt", file_prefix);
	sprintf(file_path[LT_FRAME_ALL], "data/%s-frame-all.txt", file_prefix);
	sprintf(file_path[LT_FRAME_CAN0_RECV], "data/%s-frame-can0-recv.txt", file_prefix);
	sprintf(file_path[LT_FRAME_CAN0_SEND], "data/%s-frame-can0-send.txt", file_prefix);
	sprintf(file_path[LT_FRAME_CAN1_RECV], "data/%s-frame-can1-recv.txt", file_prefix);
	sprintf(file_path[LT_FRAME_CAN1_SEND], "data/%s-frame-can1-send.txt", file_prefix);
	
	// create log file
	for (int i = 0; i < LOG_TYPE_NUM; ++i) {
		create_file(i);
	}
}

bool Log::create_file(int fn)
{
	pfile[fn] = fopen(file_path[fn], "w");
	if (pfile[fn] == NULL) {
		printf("failed to open log file %s\n", file_path[fn]);
		return false;
	}
	printf("success to open log file %s\n", file_path[fn]);
	fclose(pfile[fn]);
	return true;
}
