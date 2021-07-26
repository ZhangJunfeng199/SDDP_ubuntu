#ifndef __LOG_H__
#define __LOG_H__

#include <net/if.h>
#include <linux/can.h>


class Log
{
public:
	enum LOG_TYPE
	{
		LT_MESSAGE = 0, 		//message
		LT_FRAME_ALL, 			//frame_all
		LT_FRAME_CAN0_RECV, 	//frame_
		LT_FRAME_CAN0_SEND,
		LT_FRAME_CAN1_RECV,
		LT_FRAME_CAN1_SEND,
	};
#define LOG_TYPE_NUM	(6)

	enum LOG_FLAG
	{
		LF_MSG			   = 0x01,
		LF_FRAME_ALL	   = 0x02,
		LF_FRAME_CAN0_RECV = 0x04,
		LF_FRAME_CAN0_SEND = 0x08,
		LF_FRAME_CAN1_RECV = 0x10,
		LF_FRAME_CAN1_SEND = 0x20,
	};

	unsigned int log_flag;
	int status;

protected:
	Log();
	~Log();
	void init();
	bool create_file(int fn);
private:
	static Log* p;
	FILE* pfile[LOG_TYPE_NUM];
	char file_path[LOG_TYPE_NUM][1024];

public:
	static Log* instance();

	void ctrl(int ctrl_type);
	void enable(int log_type, bool enable = true);
	void record_message(char* msg);
	void record_frame(struct can_frame* pfr, int type);

	enum FRAME_TYPE {
		FT_CAN0_RECV = 0,
		FT_CAN0_SEND,
		FT_CAN1_RECV,
		FT_CAN1_SEND,
	};

	enum STATUS_TYPE
	{
		ST_RUNING,
		ST_PAUSE,
		ST_STOP,
	};

	enum CTRL_TYPE {
		CT_MIN = 0, //min
		CT_START,	//start
		CT_PAUSE,	//pause
		CT_STOP,	//stop
		CT_RESTART,	//restart
		CT_MAX,	//max
	};
};

#endif
