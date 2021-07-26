#include "sddp.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "zmq.h"
#include "json/json.h"
#include "glog/logging.h"

#define THROTE_CTRL_STEP			(5)
#define BRAKE_CTRL_STEP				(5)
#define STEER_CTRL_STEP				(5)
#define ACCELERATE_CTRL_STEP		(5)

int InitConnection(void* arg);
int SendCtrlMsg(void* arg, Json::Value root);

/*************************************************
* Function:	ThreadMsgRcev
* Description: the thread to receive the state variable reading from the underlying controller
* Input:
*  @arg			this pointer
* Return: none
* Others: n/a
************************************************/
void* ThreadMsgRcev(void* param)
{
	SddpOperator* opt = (SddpOperator*)param;
	char buffer[2048];

	while (opt->m_bThreadMsgRcevExit == false) {
		Json::Reader reader;
		Json::Value root;

		memset(buffer, 0, 0);
		int nbytes = zmq_recv(opt->sub_status, buffer, sizeof(buffer), ZMQ_DONTWAIT);
		if (nbytes <= 0) {
			continue;
		}
		buffer[nbytes] = '\0';

		//printf("%s\n", buffer);

		if (reader.parse(buffer, root)) {
			int mode = root["mode"].asInt();
			
			if (mode == SddpOperator::MD_MANUAL && opt->m_mode != SddpOperator::MD_MANUAL) {		// manual
				opt->m_mode = SddpOperator::MD_MANUAL;
			}
			else if (mode == SddpOperator::MD_SELF_DRIVING && opt->m_mode != SddpOperator::MD_SELF_DRIVING) {	// self_drving
				opt->m_mode = SddpOperator::MD_SELF_DRIVING;
			}
			//printf("%d ", opt->m_mode);

			int throte = root["throte"].asInt();
			if ((throte != opt->m_throte) && throte >= 0 && throte <= 100) {
				opt->m_throte = throte;
			}

			int brake = root["brake"].asInt();
			if ((brake != opt->m_brake) && brake >= 0 && brake <= 100) {
				opt->m_brake = brake;
			}

			int steer = root["steer"].asInt();
			if ((steer != opt->m_steer) && steer >= -780 && steer <= 780) {
				opt->m_steer = steer;
			}

			int gear = root["gear"].asInt();
			if ((gear != opt->m_gear) && gear >= 1 && gear <= 4) {
				opt->m_gear = gear;
			}

			int scm = root["steer_ctrl_mode"].asInt();
			if (scm != opt->m_steer_ctrl_mode && scm >= SddpOperator::SCM_OFF && scm <= SddpOperator::SCM_INVALID) {
				opt->m_steer_ctrl_mode = scm;
				if (scm == SddpOperator::SCM_GUIDANCE) {
					opt->m_steer_ctrl_enable = true;
				}
				else {
					opt->m_steer_ctrl_enable = false;
				}
			}

			int log_status = root["log_status"].asInt();
			if (log_status != opt->m_log_status && log_status >= SddpOperator::LST_RUNING && log_status <= SddpOperator::LST_STOP) {
				opt->m_log_status = log_status;
			}

			int accelerate = root["accelerate"].asInt();
			if ((accelerate != opt->m_accelerate) && accelerate >= -140 && accelerate <= 115) {
				opt->m_accelerate = accelerate;
			}

			int acm = root["acc_ctrl_mode"].asInt();
			if (acm != opt->m_acc_ctrl_mode && acm >= SddpOperator::ACM_OFF && acm <= SddpOperator::ACM_FAILURE) {
				opt->m_acc_ctrl_mode = acm;
				if (acm == SddpOperator::ACM_ACTIVE) {
					opt->m_acc_ctrl_enable = true;
				}
				else {
					opt->m_acc_ctrl_enable = false;
				}
			}

			int epb_status = root["epb_status"].asInt();
			if (epb_status != opt->m_epb_status && (epb_status == SddpOperator::EPB_ENTER || epb_status == SddpOperator::EPB_EXIT)) {
				opt->m_epb_status = epb_status;
			}

			int ems_engine_status = root["ems_engine_status"].asInt();
			if (ems_engine_status != opt->m_ems_engine_status) {
				opt->m_ems_engine_status = ems_engine_status;
			}

			int ems_battery_voltage = root["ems_battery_voltage"].asInt();
			if (ems_battery_voltage != opt->m_ems_battery_voltage) {
				opt->m_ems_battery_voltage = ems_battery_voltage;
			}

			int ip_vdisplay = root["ip_vdisplay"].asInt();
			if (ip_vdisplay != opt->m_vdisplay) {
				opt->m_vdisplay = ip_vdisplay;
			}

			//****************************************************************************
			double eps_steering_torque = root["eps_steering_torque"].asDouble();
			if (eps_steering_torque != opt->m_eps_steering_torque) {
				opt->m_eps_steering_torque = eps_steering_torque;
			}

			int steering_wheel_speed = root["steering_wheel_speed"].asInt();
			if (steering_wheel_speed != opt->m_steering_wheel_speed) {
				opt->m_steering_wheel_speed = steering_wheel_speed;
			}

			int actual_engine_torque = root["actual_engine_torque"].asInt(); 
			if (actual_engine_torque != opt->m_actual_engine_torque) {
				opt->m_actual_engine_torque = actual_engine_torque;
			}

			int engine_speed_rpm = root["engine_speed_rpm"].asInt();
			if (engine_speed_rpm != opt->m_engine_speed_rpm) {
				opt->m_engine_speed_rpm = engine_speed_rpm;
			}

			int front_left_wheel_speed_rpm = root["front_left_wheel_speed_rpm"].asInt();
			if (front_left_wheel_speed_rpm != opt->m_front_left_wheel_speed_rpm) {
				opt->m_front_left_wheel_speed_rpm = front_left_wheel_speed_rpm;
			}

			int front_right_wheel_speed_rpm = root["front_right_wheel_speed_rpm"].asInt();
			if (front_right_wheel_speed_rpm != opt->m_front_right_wheel_speed_rpm) {
				opt->m_front_right_wheel_speed_rpm = front_right_wheel_speed_rpm;
			}

			int back_left_wheel_speed_rpm = root["back_left_wheel_speed_rpm"].asInt();
			if (back_left_wheel_speed_rpm != opt->m_back_left_wheel_speed_rpm) {
				opt->m_back_left_wheel_speed_rpm = back_left_wheel_speed_rpm;
			}

			int back_right_wheel_speed_rpm = root["back_right_wheel_speed_rpm"].asInt();
			if (back_right_wheel_speed_rpm != opt->m_back_right_wheel_speed_rpm) {
				opt->m_back_right_wheel_speed_rpm = back_right_wheel_speed_rpm;
			}
		}
		usleep(1000);
	}
	zmq_close(opt->sub_status);
	zmq_ctx_destroy(opt->ctx_sub_status);

	return 0;
}

void* ThreadKeepaliveRcev(void* param)
{
	SddpOperator* opt = (SddpOperator*)param;
	char buffer[2048];
	time_t time_keepalive_cur = time(NULL);

	while (opt->m_bThreadKeepaliveRcevExit == false) {
		Json::Reader reader;
		Json::Value root;

		memset(buffer, 0, 0);
		int nbytes = zmq_recv(opt->sub_keepalive, buffer, sizeof(buffer), ZMQ_DONTWAIT);
		if (nbytes <= 0) {
			if (opt->m_time_keepalive_last > time_keepalive_cur + 2) {
				opt->m_service_status = SddpOperator::SS_OFFLINE;
			}
			continue;
		}
		buffer[nbytes] = '\0';

		if (reader.parse(buffer, root)) {
			int keepalive = root["keepalive"].asInt();

			if (keepalive == 1) {
				opt->m_time_keepalive_last = time_keepalive_cur;
				opt->m_service_status = SddpOperator::SS_ONLINE;
			}
		}

		if (opt->m_time_keepalive_last > time_keepalive_cur + 2) {
			opt->m_service_status = SddpOperator::SS_OFFLINE;
		}

		usleep(50000);
	}

	zmq_close(opt->sub_keepalive);
	zmq_ctx_destroy(opt->ctx_sub_keepalive);

	return 0;
}

//
///*************************************************
//* Function:	InitConnection
//* Description: initialize the connection with the underlying controller 
//* Input:
//*  @arg			this pointer
//* Return: reserved
//* Others: n/a
//************************************************/
//int InitConnection(void* arg)
//{
//	SddpOperator* csdk = (SddpOperator*)arg;
//	printf("Connecting to hello world server...\n");
//	csdk->ctx_sub_status = zmq_ctx_new();
//	csdk->sub_status = zmq_socket(csdk->ctx_sub_status, ZMQ_SUB);
//	zmq_connect(csdk->sub_status, "tcp://192.168.1.171:5555");
//	printf("connected\n");
//	int rc = zmq_setsockopt(csdk->sub_status, ZMQ_SUBSCRIBE, "", 0);
//
//	csdk->ctx_req_ctrl = zmq_ctx_new();
//	csdk->req_ctrl = zmq_socket(csdk->ctx_req_ctrl, ZMQ_REQ);
//	rc = zmq_connect(csdk->req_ctrl, "tcp://192.168.1.171:5556");
//
//	csdk->ctx_sub_keepalive = zmq_ctx_new();
//	csdk->sub_keepalive = zmq_socket(csdk->ctx_sub_status, ZMQ_SUB);
//	zmq_connect(csdk->sub_keepalive, "tcp://192.168.1.171:5557");
//	printf("connected\n");
//	rc = zmq_setsockopt(csdk->sub_keepalive, ZMQ_SUBSCRIBE, "", 0);
//
//	return 0;
//}

/*************************************************
* Function:	SendCtrlMsg
* Description: the function to send zmq message to the underlying controller 
* Input:
*  @arg			this pointer
*  @root		json value variable
* Return: reserved
* Others: n/a
************************************************/
int SendCtrlMsg(void* arg, Json::Value root)
{
	if (arg == NULL) {
		LOG(ERROR) << "use SendCtrlMsg in wrong way, parameter arg == NULL";
		return SDDP_ERR;
	}
	SddpOperator* csdk = (SddpOperator*)arg;
	int rc;

	// construct message & send out
	Json::FastWriter writer;
	std::string msg = writer.write(root);
	if (msg.length() <= 0) {
		LOG(ERROR) << "invalid msg, msg.length <= 0";
		return SDDP_ERR;
	}
	rc = zmq_send(csdk->req_ctrl, msg.c_str(), msg.length(), ZMQ_DONTWAIT);
	//if (rc == -1) {
	//	LOG(ERROR) << "failed to send socket packet, error code: " << zmq_errno();
	//	return SDDP_ERR;
	//}

	// wait for reply
	char buf[1024] = { 0 };
	int n = 0;
	while (n < 30)
	{
		++n;
		int nbytes = zmq_recv(csdk->req_ctrl, buf, sizeof(buf), ZMQ_DONTWAIT);
		if (nbytes <= 0) {
			usleep(100000);
			continue;
		}
		Json::Value rootRep;
		Json::Reader reader;
		if (reader.parse(buf, rootRep)) {
			if (rootRep["reply"] == std::string("ok")) {
				return SDDP_OK;
			}
			else {
				std::string msg = rootRep["reason"].asString();
				LOG(ERROR) << msg;
				memset(csdk->m_error, 0, sizeof(csdk->m_error));
				strcpy(csdk->m_error, rootRep["reason"].asString().c_str());
				return SDDP_ERR;
			}
		}
		else {
			LOG(ERROR) << "failed to parse message from board";
		}
	}
	
	LOG(ERROR) << "receive msg reply timeout";
	return SDDP_ERR;
}

SddpOperator::SddpOperator()
{
	m_bInit = false;
	m_system_state = SYS_UNINIT;
	memset(m_error, 0, sizeof(m_error));
}

/*************************************************
* Function:	InitService
* Description: init the system and set the connection with the underlying controller 
* Input:  none
* Return: none
* Others: n/a
************************************************/
int SddpOperator::InitService(void)
{
	if (m_bInit == true) {
		return SDDP_OK;
	}

	int res;

	m_bThreadMsgRcevExit = false;

	m_time_keepalive_last = time(NULL);

	m_service_status = SS_OFFLINE;
	m_mode = MD_MANUAL;
	m_steer_ctrl_mode = SCM_OFF;
	m_steer_ctrl_enable = false;
	m_epb_status = EPB_ENTER;

	m_throte = 0;
	m_brake = 0;
	m_steer = 0;
	m_gear = GEAR_N;  // 1: PARKING；2: REVERSE; 3：NEUTRAL；4：DRIVE

	m_accelerate = 0;
	m_acc_ctrl_mode = ACM_OFF;
	m_acc_ctrl_enable = false;

	/* init log module */
	res = InitLogDir();
	if (res == SDDP_ERR) {
		LOG(ERROR) << "failed to init log file folder";
		return SDDP_ERR;
	}

    google::InitGoogleLogging("sddp");
    google::SetLogDestination(google::INFO,"./log/sddp-api-");


	res = ConnectBoard();
	if (res) {
		LOG(ERROR) << "failed to connect to board";
		google::ShutdownGoogleLogging();
		return SDDP_ERR;
	}
	LOG(INFO) << "success to connect to board";

	res = pthread_create(&m_hThreadMsgRcev, NULL, ThreadMsgRcev, (void *)this);
	if (res != 0) {
		LOG(ERROR) << "failed to create message receiving thread";
		google::ShutdownGoogleLogging();
		return SDDP_ERR;
	}
	m_bThreadMsgRcevExit = false;

	res = pthread_create(&m_hThreadKeepaliveRcev, NULL, ThreadKeepaliveRcev, (void *)this);
	if (res != 0) {
		LOG(ERROR) << "failed to create keepalive receiving thread";
		google::ShutdownGoogleLogging();
		return SDDP_ERR;
	}
	m_bThreadKeepaliveRcevExit = false;

	m_system_state = SYS_INIT;
	m_bInit = true;
	return SDDP_OK;
}

/*************************************************
* Function:	UninitService
* Description: uninit the system and disconnect the connection with the underlying controller
* Input:  none
* Return: none
* Others: n/a
************************************************/
void SddpOperator::UninitService(void)
{
	if (m_system_state != SYS_INIT) {
		return;
	}

	if (!CheckServiceOnline()) {
		return;
	}

	SetMode(SddpOperator::MD_MANUAL);

	m_bThreadMsgRcevExit = true;
	m_bThreadKeepaliveRcevExit = true;
	pthread_t handles[2] = { m_hThreadMsgRcev , m_hThreadKeepaliveRcev};

	void *thread_result;
	pthread_join(m_hThreadMsgRcev, &thread_result);
	pthread_join(m_hThreadKeepaliveRcev, &thread_result);

	//zmq_disconnect(sub_status, "tcp://192.168.1.171:5555");
	//zmq_disconnect(req_ctrl, "tcp://192.168.1.171:5556");
	//zmq_disconnect(sub_keepalive, "tcp://192.168.1.171:5557");

	google::ShutdownGoogleLogging();

	m_bInit = false;

	m_system_state = SYS_UNINIT;
}

/*************************************************
* Function:	SetMode
* Description: the function to set the mode
* Input:
*  @set_mode			MD_MAUAL: manual; MD_SELF_DRIVING: self_drving
* Return: none
* Others: n/a
************************************************/
int SddpOperator::SetMode(int mode)
{
	if (!CheckServiceOnline()) {
		return SDDP_ERR;
	}

	if (!(mode == MD_MANUAL || mode == MD_SELF_DRIVING)) {
		LOG(ERROR) << "invalid mode value";
		return SDDP_ERR;
	}

	if (m_mode == mode) {
		LOG(INFO) << "target mode is same to current mode";
		return SDDP_ERR;
	}

	int res = SDDP_OK;
	int rc;

	Json::Value root;
	root["type"] = "set_mode";
	root["value"] = mode;
	rc = SendCtrlMsg(this, root);
	if (rc == SDDP_ERR) {
		LOG(ERROR) << "failed to send command message to board";
		return SDDP_ERR;
	}

	return SDDP_OK;
}

/*************************************************
* Function:	GetMode
* Description: the function to get the current mode
* Input: none
* Return: the current mode : 1: manual; 2: self_drving
* Others: n/a
************************************************/
int SddpOperator::GetMode()
{
	if (!CheckServiceOnline()) {
		return SDDP_ERR;
	}

	return m_mode;
}

int SddpOperator::EnableSteerCtrl(bool enable)
{
	if (!CheckServiceOnline()) {
		return SDDP_ERR;
	}

	if (enable == true) {
		Json::Value root1;
		root1["type"] = "set_steer_ctrl_mode";
		root1["value"] = SCM_STANDBY;
		SendCtrlMsg(this, root1);
		usleep(1000000);

		Json::Value root2;
		root2["type"] = "set_steer_ctrl_mode";
		root2["value"] = SCM_SEARCHING;
		SendCtrlMsg(this, root2);
		usleep(3000000);

		Json::Value root3;
		root3["type"] = "set_steer_ctrl_mode";
		root3["value"] = SCM_GUIDANCE;
		SendCtrlMsg(this, root3);
		usleep(1000000);

		LOG(INFO) << "enable steer ctrl";
		return SDDP_OK;
	}
	else {
		Json::Value root;
		root["type"] = "set_steer_ctrl_mode";
		root["value"] = SCM_OFF;
		SendCtrlMsg(this, root);
		usleep(1000000);

		LOG(INFO) << "disable steer ctrl";
		return SDDP_OK;
	}

	return SDDP_ERR;
}

int SddpOperator::EnableSpeedCtrl(bool enable)
{
	if (!CheckServiceOnline()) {
		return SDDP_ERR;
	}

	if (enable == true) {
		Json::Value root1;
		root1["type"] = "set_eng_trq_req_active";
		root1["value"] = 1;
		SendCtrlMsg(this, root1);
		usleep(1000000);
		
		Json::Value root2;
		root2["type"] = "set_acc_ctrl_mode";
		root2["value"] = ACM_STANDBY;
		SendCtrlMsg(this, root2);
		usleep(3000000);

		Json::Value root3;
		root3["type"] = "set_acc_ctrl_mode";
		root3["value"] = ACM_ACTIVE;
		SendCtrlMsg(this, root3);
		usleep(1000000);

		LOG(INFO) << "enable speed ctrl";
		return SDDP_OK;
	}
	else {
		Json::Value root;
		root["type"] = "set_acc_ctrl_mode";
		root["value"] = ACM_OFF;
		SendCtrlMsg(this, root);
		usleep(1000000);

		Json::Value root1;
		root1["type"] = "set_eng_trq_req_active";
		root1["value"] = 0;
		SendCtrlMsg(this, root1);
		usleep(1000000);

		LOG(INFO) << "disable speed ctrl";
		return SDDP_OK;
	}

	return SDDP_ERR;
}

void SddpOperator::EnterParking()
{
	if (!CheckServiceOnline()) {
		return;
	}

	Json::Value root;
	root["type"] = "set_epb";
	root["value"] = EPB_ENTER;
	SendCtrlMsg(this, root);
}

int SddpOperator::ExitParking()
{
	if (!CheckServiceOnline()) {
		return SDDP_ERR;
	}

	Json::Value root1;
	root1["type"] = "set_epb";
	root1["value"] = EPB_EXIT;
	int res = SendCtrlMsg(this, root1);
	if (res == SDDP_ERR) {
		LOG(ERROR) << "failed to send command message to board";
		return SDDP_ERR;
	}

	return SDDP_OK;
}

void SddpOperator::Stop()
{
	if (!CheckServiceOnline()) {
		return;
	}

	Json::Value root1;
	root1["type"] = "stop_the_vehicle";
	root1["value"] = 50;
	SendCtrlMsg(this, root1);

	usleep(1000000);;

	Json::Value root2;
	root2["type"] = "set_gear";
	root2["value"] = GEAR_N;
	SendCtrlMsg(this, root2);
}


void SddpOperator::AEBSlowDown()
{
	if (!CheckServiceOnline()) {
		return;
	}

	Json::Value root1;
	root1["type"] = "stop_the_vehicle";
	root1["value"] = 50;
	SendCtrlMsg(this, root1);
}

int SddpOperator::AEBBrake(int brake)
{
	int res;

	if (brake <= 0 || brake > 100) {
		printf("Error: invalid brake percentage value, value in [1, 100] is valid\n");
		return SDDP_ERR;
	}

	if (!CheckServiceOnline()) {
		printf("Error: not in Self-driving Mode.\n");
		return SDDP_ERR;
	}

	Json::Value root1;
	root1["type"] = "stop_the_vehicle";
	root1["value"] = brake;

	res = SendCtrlMsg(this, root1);
	if (res == SDDP_ERR) {
		printf("Error: failed to send controll message to controller\n");
		return SDDP_ERR;
	}

	return SDDP_OK;
}

/*************************************************
* Function:	SetGear
* Description: the function to set the gear
* Input:
*  @gear_set_value			1: PARKING；2: REVERSE; 3：NEUTRAL；4：DRIVE
* Return: none
* Others: n/a
************************************************/
void SddpOperator::SetGear(int gear_set_value)
{
	if (!CheckServiceOnline()) {
		return;
	}
	Json::Value root;
	root["type"] = "set_gear";
	root["value"] = gear_set_value;
	SendCtrlMsg(this, root);
}

/*************************************************
* Function:	GetGear
* Description: the function to get the current gear
* Input: none
* Return: the current gear : 1: PARKING；2: REVERSE; 3：NEUTRAL；4：DRIVE；
* Others: n/a
************************************************/
int SddpOperator::GetGear()
{
	if (!CheckServiceOnline()) {
		return -1;
	}

	return m_gear;
}

/*************************************************
* Function:	SetSteering
* Description: the function to set the steer angle
* Input:
*  @steer_set_value			ranging from ( -780°, 780°)
* Return: none
* Others: n/a
************************************************/
void SddpOperator::SetSteering(int steer_set_value)
{
	if (!CheckServiceOnline()) {
		return;
	}

	if (steer_set_value > 780 || steer_set_value < -780) {
		return;
	}

	Json::Value root;
	root["type"] = "set_steer";
	root["value"] = steer_set_value;
	SendCtrlMsg(this, root);
}

/*************************************************
* Function:	GetSteering
* Description: the function to get the current steer angle
* Input: none
* Return: the current steer angle : ranging from ( -780°, 780°)
* Others: n/a
************************************************/
int SddpOperator::GetSteering()
{
	if (!CheckServiceOnline()) {
		return 0;
	}

	return m_steer;
}

/*************************************************
* Function:	SetBrake
* Description: the function to set the brake value
* Input:
*  @brake_set_value			ranging from (0, 100)
* Return: none
* Others: n/a
************************************************/
void SddpOperator::SetBrake(int brake_set_value)
{
	if (!CheckServiceOnline()) {
		return;
	}

	if (brake_set_value > 100 || brake_set_value < 0) {
		return;
	}

	Json::Value root;
	root["type"] = "set_accelerate";
	root["value"] = -1.4*brake_set_value;
	SendCtrlMsg(this, root);
}

/*************************************************
* Function:	GetBrake
* Description: the function to get the current brake value
* Input: none
* Return: the current brake value : ranging from (0, 100)
* Others: n/a
************************************************/
int SddpOperator::GetBrake()
{
	if (!CheckServiceOnline()) {
		return -1;
	}

	return int(m_accelerate / (-1.4));
}

/*************************************************
* Function:	SetThrottle
* Description: the function to set the throttle value
* Input:
*  @throttle_set_value			ranging from (0, 100)
* Return: none
* Others: n/a
************************************************/
void SddpOperator::SetThrottle(int throttle_set_value)
{
	if (!CheckServiceOnline()) {
		return;
	}

	if (throttle_set_value > 100 || throttle_set_value < 0) {
		return;
	}
	Json::Value root;
	root["type"] = "set_accelerate";
	root["value"] = 1.15*throttle_set_value;//转换成加速度
	SendCtrlMsg(this, root);
}

/*************************************************
* Function:	GetThrottle
* Description: the function to get the current throttle value
* Input: none
* Return: the current throttle value : ranging from (0, 100)
* Others: n/a
************************************************/
int SddpOperator::GetThrottle()
{
	if (!CheckServiceOnline()) {
		return -1;
	}

	return int(m_accelerate / 1.15);
}

int SddpOperator::GetEngineStatus()
{
	if (!CheckServiceOnline()) {
		return -1;
	}

	return m_ems_engine_status;
	
}

int SddpOperator::GetBatteryStatus()
{
	if (!CheckServiceOnline()) {
		return -1;
	}

	return m_ems_battery_voltage;
}

void SddpOperator::OnSteerAdd()
{
    if (!CheckServiceOnline()) {
        return;
    }

	if (m_steer == 780) {
		return;
	}

	Json::Value root;

	root["type"] = "set_steer";
	root["value"] = (m_steer + STEER_CTRL_STEP) > 780 ? 780 : m_steer + STEER_CTRL_STEP;

	SendCtrlMsg(this, root);
}

void SddpOperator::OnSteerSub()
{
    if (!CheckServiceOnline()) {
        return;
    }
	if (m_steer == -780) {
		return;
	}

	Json::Value root;

	root["type"] = "set_steer";
	root["value"] = (m_steer - STEER_CTRL_STEP) < -780 ? -780 : m_steer - STEER_CTRL_STEP;

	SendCtrlMsg(this, root);
}

void SddpOperator::OnAccAdd()
{
	if (m_accelerate >= 115) {
		return;
	}

	Json::Value root;

	root["type"] = "set_accelerate";
	root["value"] = (m_accelerate + ACCELERATE_CTRL_STEP) > 115 ? 115 : m_accelerate + ACCELERATE_CTRL_STEP;

	SendCtrlMsg(this, root);
}

void SddpOperator::OnAccSub()
{
	if (m_accelerate <= -140) {
		return;
	}

	Json::Value root;

	root["type"] = "set_accelerate";
	root["value"] = (m_accelerate - ACCELERATE_CTRL_STEP) < -140 ? -140 : m_accelerate - ACCELERATE_CTRL_STEP;

	SendCtrlMsg(this, root);
}

void SddpOperator::SetAcc(int acc_set_value)
{
	if (m_accelerate <= -140 || m_accelerate  >= 115) {
		return;
	}

	Json::Value root;

	root["type"] = "set_accelerate";
	root["value"] = acc_set_value;

	SendCtrlMsg(this, root);
}

int SddpOperator::GetAcc()
{
	if (!CheckServiceOnline()) {
		return -1;
	}

	return int(m_accelerate);
}

int * SddpOperator::GetWheelSpeed()
{
	static int r[4];
	r[0] = m_front_left_wheel_speed_rpm;
	r[1] = m_front_right_wheel_speed_rpm;
	r[2] = m_back_left_wheel_speed_rpm;
	r[3] = m_back_right_wheel_speed_rpm;
	return r;
}

int SddpOperator::GetEngineSpeed()
{
	return m_engine_speed_rpm;
}

char* SddpOperator::GetLastError()
{
	return m_error;
}

/*************************************************
* Function:	ConnectController
* Description: initialize the connection to on-board controller
* Input:  n/a
* Return:
*	SDDP_OK  - success
*	SDDP_ERR - fail
* Others: n/a
************************************************/
int SddpOperator::ConnectBoard()
{
	int rc = 0;

	LOG(INFO) << "connecting to board server...";

	ctx_sub_status = zmq_ctx_new();
	sub_status = zmq_socket(ctx_sub_status, ZMQ_SUB);
	zmq_connect(sub_status, "tcp://192.168.1.171:5555");
	LOG(INFO) << "connected to board server done";
	rc = zmq_setsockopt(sub_status, ZMQ_SUBSCRIBE, "", 0);

	ctx_req_ctrl = zmq_ctx_new();
	req_ctrl = zmq_socket(ctx_req_ctrl, ZMQ_REQ);
	rc = zmq_connect(req_ctrl, "tcp://192.168.1.171:5556");

	ctx_sub_keepalive = zmq_ctx_new();
	sub_keepalive = zmq_socket(ctx_sub_keepalive, ZMQ_SUB);
	zmq_connect(sub_keepalive, "tcp://192.168.1.171:5557");
	rc = zmq_setsockopt(sub_keepalive, ZMQ_SUBSCRIBE, "", 0);

	LOG(INFO) << "connected";
	return 0;
}

void SddpOperator::DisconnectBoard()
{
	return;
}

int SddpOperator::InitLogDir()
{
	if (opendir("./log") == NULL) {
		int status = mkdir("./log", 0775);
		if (status == -1) {
			LOG(ERROR) << "failed to create log folder";
			return SDDP_ERR;
		}

		LOG(INFO) << "create log folder to save log files";
		return SDDP_OK;
	}
		
	return SDDP_OK;
}

bool SddpOperator::CheckServiceOnline()
{
	if (m_service_status == SS_ONLINE) {
		return true;
	}
	else {
		LOG(WARNING) << "board not online or is still connecting, try again";
		return false;
	}
}


