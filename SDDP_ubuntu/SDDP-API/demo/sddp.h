#ifndef __SDDP_H__
#define __SDDP_H__
#include <time.h>
#include <pthread.h>


/*
 * THIS FILE IS PART OF SELF-DRIVING DEVELOPMENT PLATFORM(SDDP) PROJECT
 *
 * sddp.h - The header file of SDDP SDK Library
 *
 * 2017-06-31 by youzuo, hexiaoyu,
 * Define the interfaces and create implementation of most interfaces.
 *
 * 2017-09-20 by youzuo, hexiaoyu,
 * Bug fix
 *
 * 2018-07-19 by youzuo, hexiaoyu,
 * Bug fix and add some notes
 *
 * Version: 2.0.0
 * Copyright(c) 2017 VIRHAND.Co.Ltd. All rights reserved. 
 */

#define SDDP_OK		(0)
#define SDDP_ERR	(-1)

#define SDDP_STEER_ANG_MAX	(780)
#define SDDP_STEER_ANG_MIN	(-780)

#define SDDP_ACC_MAX	(115)
#define SDDP_ACC_MIN	(-140)

class SddpOperator {
public:
	SddpOperator();

	/************************************************
	 * Function:	InitService
	 * Description: init the system and set the connection with the underlying controller
	 * Input:  n/a
	 * Return:
	 *	SDDP_OK	 -	success
	 *	SDDP_ERR -	failed
	 * Others: n/a
	 ************************************************/
	int  InitService();

	/************************************************
	 * Function:	UninitService
	 * Description: uninit the system and disconnect the connection with the underlying controller
	 * Input:  n/a
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void UninitService();

	/*Service Status*/
	enum SERVICE_STATUS
	{
		SS_ONLINE = 0,
		SS_CONNECTING,
		SS_OFFLINE,
	};
	
	/************************************************
	 * Function:	EnableSteerCtrl
	 * Description: enable sdk to control steer angle
	 * Input:
	 *	true	-	enable
	 *	false	-	disable
	 * Return:
	 *	SDDP_OK	 -	success
	 *	SDDP_ERR -	failed
	 * Others: n/a
	 ************************************************/
	int EnableSteerCtrl(bool enable);

	/************************************************
	* Function:	EnableSpeedCtrl
	* Description: enable sdk to control acceleration value
	* Input:
	*	true	-	enable
	*	false	-	disable
	* Return:
	*	SDDP_OK	 -	success
	*	SDDP_ERR -	failed
	* Others: n/a
	************************************************/
	int EnableSpeedCtrl(bool enable);

	/************************************************
	 * Function:	EnterParking
	 * Description: set car parking mode to park mode
	 * Input:  n/a
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void EnterParking();

	/************************************************
	 * Function:	ExitParking
	 * Description: set car parking mode to release mode
	 * Input:  n/a
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	int ExitParking();

	/************************************************
	 * Function:	Stop
	 * Description: brake car's speed to 0, and change gear to GEAR_N
	 * Input:  n/a
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void Stop();

	/************************************************
	* Function:	AEBSlowDown
	* Description: use AEB to stop for a while, slow the speed to 0 for a while and then start to move
	* Input:  n/a
	* Return: n/a
	* Others: n/a
	************************************************/
	void AEBSlowDown();

	/************************************************
	* Function:	AEBBrake
	* Description: brake car's speed by using AEB
	* Input:
	*  @brake	[1, 100], the brake value simulate braking pressure percentage
	* Return: n/a
	*	SDDP_OK	 -	success
	*	SDDP_ERR -	failed
	* Others: n/a
	************************************************/
	int AEBBrake(int brake);
	
	/************************************************
	 * Function:	SetMode
	 * Description: set car to manual mode or self-driving mode
	 * Input:
	 *  @mode	MD_MANUAL: manual mode; MD_SELF_DRIVING: self_drving mode, see Enum MODE
	 * Return: 
	 *	SDDP_OK	 -	success
	 *	SDDP_ERR -	failed
	 * Others: n/a
	 ************************************************/
	int  SetMode(int mode);
	
	/*************************************************
	 * Function:	GetMode
	 * Description: get car's mode
	 * Input:  n/a
	 * Return: the current mode, see Enum MODE
	 * Others: n/a
	 ************************************************/
	int	 GetMode();

	/* Car Mode */
	enum MODE
	{
		MD_MANUAL = 1,		// Manual Mode
		MD_SELF_DRIVING,	// Self-Driving Mode
	};

	/************************************************
	 * Function:	SetGear
	 * Description: set car's gear level, for safty concern, only GEAR_N & GEAR_D are available gear to be set by user
	 * Input:
	 *  @mode	GEAR_N: NEUTRAL; GEAR_D: DRIVE
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void SetGear(int gear_set_value);

	/*************************************************
	 * Function:	GetGear
	 * Description: get car's gear type
	 * Input:  n/a
	 * Return: current gear type, see Enum GEAR_TYPE
	 * Others: n/a
	 ************************************************/
	int GetGear();

	/* Gear Type */
	enum GEAR_TYPE
	{
		GEAR_P = 1,	// PARKING
		GEAR_R,		// REVERSE
		GEAR_N,		// NEUTRAL
		GEAR_D,		// DRIVE
	};

	/*************************************************
	 * Function:	SetSteering
	 * Description: set the steer angle
	 * Input:
	 *  @steer_value	( -780°, 780°)
	 * Return: none
	 * Others: n/a
	 ************************************************/
	void SetSteering(int steer_value);

	/*************************************************
	 * Function:	GetSteering
	 * Description: get the current steer angle
	 * Input: none
	 * Return: the current steer angle : ranging from ( -780°, 780°)
	 * Others: n/a
	 ************************************************/
	int GetSteering();

	/*************************************************
	 * Function:	OnSteerAdd
	 * Description: add steer angle 5 degree
	 * Input: none
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void OnSteerAdd();

	/*************************************************
	 * Function:	OnSteerSub
	 * Description: sub steer angle 5 degree
	 * Input: none
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void OnSteerSub();

	/*************************************************
	 * Function:	OnAccAdd
	 * Description: sub acc value 5 m/s2
	 * Input: none
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void OnAccAdd();

	/*************************************************
	 * Function:	OnAccSub
	 * Description: sub acc value 5 m/s2
	 * Input: none
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void OnAccSub();

	/*************************************************
	 * Function:	SetAcc
	 * Description: set acc value
	 * Input: none
	 * Return: n/a
	 * Others: n/a
	 ************************************************/
	void SetAcc(int acc_value);

	/*************************************************
	* Function:	GetAcc
	* Description: get acc value
	* Input: none
	* Return: the current acc value
	* Others: n/a
	************************************************/
	int GetAcc();

	/*************************************************
	* Function:	GetWheelSpeed
	* Description: get wheel speed: 
	* Input: none
	* Return: an array representing the wheel speed
	*  m_front_left_wheel_speed_rpm
	*  m_front_right_wheel_speed_rpm
	*  m_back_left_wheel_speed_rpm
	*  m_back_right_wheel_speed_rpm
	* Others: n/a
	************************************************/
	int * GetWheelSpeed();

	/*************************************************
	* Function:	GetEngineSpeed
	* Description: get engine speed:
	* Input: none
	* Return: engine speed : rounds per minute (rpm)
	* Others: n/a
	************************************************/
	int  GetEngineSpeed();

	/*************************************************
	 * Function:	SetBrake
	 * Description: set the brake value
	 * Input:
	 *  @brake_value	ranging from (0, 100)
	 * Return: none
	 * Others: n/a
	 ************************************************/
	void SetBrake(int brake_value);

	/*************************************************
	 * Function:	GetBrake
	 * Description: get the current brake value
	 * Input: none
	 * Return: the current brake value : ranging from (0, 100)
	 * Others: n/a
	 ************************************************/
	int GetBrake();

	/*************************************************
	 * Function:	SetThrottle
	 * Description: set throttle value
	 * Input:
	 *  @throttle_value		ranging from (0, 100)
	 * Return: none
	 * Others: n/a
	 ************************************************/
	void SetThrottle(int throttle_value);

	/*************************************************
	 * Function:	GetThrottle
	 * Description: get current throttle value
	 * Input: none
	 * Return: the current throttle value : ranging from (0, 100)
	 * Others: n/a
	 ************************************************/
	int GetThrottle();

	/*************************************************
	 * Function:	GetEngineStatus
	 * Description: get engine status, normal or fault
	 * Input: none
	 * Return:
	 *  ES_NORMAL - normal
	 *  ES_FAULT  - fault, engine error occurs, see Enum ENGINE_STATUS
	 * Others: n/a
	 ************************************************/
	int GetEngineStatus();

	/* Engine Status */
	enum ENGINE_STATUS
	{
		ES_NORMAL = 0,  //NORMAL
		ES_FAULT,		//FAULT
	};

	/*************************************************
	 * Function:	GetEngineStatus
	 * Description: get car's battery voltage
	 * Input: none
	 * Return: battery voltage
	 * Others: n/a
	 ************************************************/
	int GetBatteryStatus();

	/*************************************************
	 * Function:	GetLastError
	 * Description: get underlying board sending's last error
	 * Input: none
	 * Return: m_error
	 * Others: n/a
	 ************************************************/
	char* GetLastError();

	/* menber below can not be used by user */
	/* the context parameter of the zmq socket(pub_sub mode) */
	void *ctx_sub_status;

	/* the created socket handle of the zmq socket(pub_sub mode) */
	void *sub_status;

	/* the context parameter of the zmq socket(req_rep mode) */
	void *ctx_req_ctrl;

	/* the created socket handle of the zmq socket(req_rep mode) */
	void *req_ctrl;

	/* the context parameter of the zmq socket(pub_sub mode) */
	void *ctx_sub_keepalive;

	/* the created socket handle of the zmq socket(pub_sub mode) */
	void *sub_keepalive;

	/* system status:
	SYS_UNINIT or SYS_INIT */
	int m_system_state;

	/* indicates whether the system initializes a variable of type bool */
	bool m_bInit;

	/* connection status between the control board and the upper-PC: SS_ONLINE = 0,SS_CONNECTING or SS_OFFLINE */
	int m_service_status;

	/* keepAlive variable */
	time_t m_time_keepalive_last;

	/* system mode: MD_MANUAL = 1 or MD_SELF_DRIVING */
	int m_mode;

	/* throttle value (0, 100) */
	int m_throte;

	/* brake value (0, 100) */
	int m_brake;

	/* steering angle value (-780, 780) */
	int m_steer;

	/* gear value (1: PARKING；2: REVERSE; 3：NEUTRAL；4：DRIVE) */
	int m_gear;

	/* steering control mode (SCM_OFF = 0,SCM_STANDBY,SCM_SEARCHING,SCM_GUIDANCE,
	SCM_COMPLITED,SCM_FAILURE,SCM_TERMINATED,SCM_INVALID) */
	int m_steer_ctrl_mode;

	/* is steering control enable */
	bool m_steer_ctrl_enable;

	/* log status (LST_RUNING, LST_PAUSE, LST_STOP) */
	int m_log_status;

	/* accelerate value (-140, 115) */
	int m_accelerate;

	/* accelerate control mode (ACM_OFF = 0, ACM_PASSIVE, ACM_STANDBY, ACM_ACTIVE,
	ACM_BRAKE_ONLY, ACM_OVERRIDE, ACM_RESERVED, ACM_FAILURE) */
	int m_acc_ctrl_mode;

	/* is accelerate control enable */
	bool m_acc_ctrl_enable;

	/* epb unit status (EPB_ENTER = 0, EPB_EXIT) */
	int m_epb_status;

	/* ems engine status (ES_NORMAL = 0, ES_FAULT) */
	int m_ems_engine_status;

	/* ems battery voltage value (V) */
	int m_ems_battery_voltage;

	/* vehicle speed value (km/h) */
	int m_vdisplay;

	/* eps steering torque value (Nm) */
	double m_eps_steering_torque;

	/* steering wheel speed value (rpm) */
	int m_steering_wheel_speed;

	/* actual engine torque value (Nm) */
	int m_actual_engine_torque;

	/* engine speed value (rpm) */
	int m_engine_speed_rpm;

	/* vehicle's 4 wheels speed value (rpm) */
	int m_front_left_wheel_speed_rpm;
	int m_front_right_wheel_speed_rpm;
	int m_back_left_wheel_speed_rpm;
	int m_back_right_wheel_speed_rpm;

	/* variable that logs error information */
	char m_error[1024];

	/* thread control variables */
	pthread_t  	m_hThreadMsgRcev;
	bool		m_bThreadMsgRcevExit;
	pthread_t  	m_hThreadKeepaliveRcev;
	bool		m_bThreadKeepaliveRcevExit;

	/* enumeration type variable */
	enum LOG_STATUS_TYPE
	{
		LST_RUNING,
		LST_PAUSE,
		LST_STOP,
	};

	enum STEER_CTRL_MODE
	{
		SCM_OFF = 0,
		SCM_STANDBY,
		SCM_SEARCHING,
		SCM_GUIDANCE,
		SCM_COMPLITED,
		SCM_FAILURE,
		SCM_TERMINATED,
		SCM_INVALID,
	};

	enum ACC_CTRL_MODE
	{
		ACM_OFF = 0,
		ACM_PASSIVE,
		ACM_STANDBY,
		ACM_ACTIVE,
		ACM_BRAKE_ONLY,
		ACM_OVERRIDE,
		ACM_RESERVED,
		ACM_FAILURE
	};

	enum ACC_AEB_STOP
	{
		AEB_NOT_STOP = 0,
		AEB_STOP = 1,
	};

	enum EPB_STATUS
	{
		EPB_ENTER = 0,
		EPB_EXIT,
	};

	enum SYSTEM_STATE {
		SYS_UNINIT,
		SYS_INIT,
	};

private:
	int  ConnectBoard();
	void DisconnectBoard();
	int  InitLogDir();
	bool CheckServiceOnline();
};

#endif // __SDDP_H__

