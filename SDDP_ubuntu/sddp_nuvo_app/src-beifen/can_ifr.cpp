#include "can_ifr.h"
#include "string.h"

int chn_info[4] = {0, 1, 2, 3};

CanIfr::CanIfr()
{
	for (int i = 0; i < CAN_CHN_NUM; ++i) {
		if (pthread_mutex_init(&mtx[i], NULL) != 0){
			printf("failed to init mutex");
		}
	}
	canInitializeLibrary();
}

CanIfr::~CanIfr()
{
	canStatus stat;
	stat = canUnloadLibrary();
	if (stat != canOK) {
		check("canUnloadLibrary", stat);
		exit(1);
	}
}

int CanIfr::init()
{
	int res = 0;
	int chn_num = 0;
	canStatus stat;
	int beta;
	char betaString[10];
	unsigned int canlibVersion;
	char name[256];
	char driverName[256];

	printf("init can interface\n");
	
	beta = canGetVersionEx(canVERSION_CANLIB32_BETA);
	if (beta) {
		sprintf(betaString, "BETA");
	} else {
		betaString[0] = '\0';
	}
	canlibVersion = canGetVersionEx(canVERSION_CANLIB32_PRODVER);
	printf("CANlib version %d.%d %s\n",
			canlibVersion >> 8,
			canlibVersion & 0xff,
			betaString);

	stat = canGetNumberOfChannels(&chn_num);
	if (stat != canOK) {
		printf("failed to get CAN channel number\n");
		return -1;
	}
	if (chn_num < CAN_CHN_NUM) {
		printf("invalid CAN channel number: %d\n", chn_num);
		return -1;
	}

	for (int i = 0; i < CAN_CHN_NUM; ++i) {
		memset(name, 0, sizeof(name));
		memset(driverName, 0, sizeof(driverName));
	
		stat = canGetChannelData(i, canCHANNELDATA_DRIVER_NAME, &driverName, sizeof(driverName));
		if (stat != canOK) {
			check("canGetChannelData: DRIVER_NAME", stat);
      		return -1;
		}

		stat = canGetChannelData(i, canCHANNELDATA_DEVDESCR_ASCII,
        							&name, sizeof(name));
	    if (stat != canOK) {
			check("canGetChannelData: DEVDESCR_ASCII", stat);
			return -1;
	    }
		
		printf("ch %2.1d: %-22s\t%s\n", i, name, driverName);

		if (strcmp("pciefd", driverName) != 0) {
			printf("invalid CAN channel\n");
			return -1;
		}
	}

	for (int i = 0; i < CAN_CHN_NUM; ++i) {
		res = open(i);
		if (res < 0) {
			printf("failed to open CAN channel %d\n", i);
			return -1;
		}
	}
	printf("open all CAN channels success\n");

	return 0;
}

void CanIfr::check(const char* id, canStatus stat)
{
	if (stat != canOK) {
		char buf[50];
		buf[0] = '\0';
		canGetErrorText(stat, buf, sizeof(buf));
		printf("%s: failed, stat=%d (%s)\n", id, (int)stat, buf);
	}
}

void CanIfr::notifyCallback(canNotifyData *data)
{
	int* pchn = (int*)(data->tag);
	
	switch (data->eventType) {
	case canEVENT_STATUS:
		printf("CAN[%d] Status Event: %s\n", *pchn, busStatToStr(data->info.status.busStatus));
		break;
	case canEVENT_ERROR:
		printf("CAN[%d] Error Event\n", *pchn);
		break;
	case canEVENT_TX:
		//printf("CAN[%d] Tx Event\n", *pchn);
		break;
	case canEVENT_RX:
		//printf("CAN[%d] Rx Event\n", *pchn);
		break;
	}
	return;
}

int CanIfr::open(int chn)
{
	canStatus stat;
	
	if (chn < 0 || chn >= CAN_CHN_NUM) {
		return -1;
	}
	hnd[chn] = canOpenChannel(chn, canOPEN_EXCLUSIVE | canOPEN_REQUIRE_EXTENDED | canOPEN_ACCEPT_VIRTUAL);
	if (hnd[chn] < 0) {
		printf("canOpenChannel %d", chn);
		check("", (canStatus)hnd[chn]);
		return -1;
	}

	stat = canSetNotify(hnd[chn], notifyCallback, canNOTIFY_RX | canNOTIFY_TX | canNOTIFY_ERROR | canNOTIFY_STATUS
													| canNOTIFY_ENVVAR, &chn_info[chn]);
	check("canSetNotify", stat);

	stat = canSetBusParams(hnd[chn], canBITRATE_500K, 0, 0, 0, 0, 0);
	check("canSetBusParams", stat);
	if (stat != canOK) {
		goto ErrorExit;
	}

	stat = canBusOn(hnd[chn]);
	check("canBusOn", stat);
	if (stat != canOK) {
		goto ErrorExit;
	}

	return 0;

ErrorExit:
	stat = canBusOff(hnd[chn]);
	check("canBusOff", stat);
	usleep(50 * 1000);	// sleep just to get the last notification.
	stat = canClose(hnd[chn]);
	check("canClose", stat);
	return -1;
}

const char* CanIfr::busStatToStr(const unsigned long flag) {
    const char* tempStr = NULL;
    #define MACRO2STR(x) case x: tempStr = #x; break
    switch (flag) {
        MACRO2STR( CHIPSTAT_BUSOFF        );
        MACRO2STR( CHIPSTAT_ERROR_PASSIVE );
        MACRO2STR( CHIPSTAT_ERROR_WARNING );
        MACRO2STR( CHIPSTAT_ERROR_ACTIVE  );
        default: tempStr = ""; break;
    }
    #undef MACRO2STR
    return tempStr;
}

int CanIfr::send(int chn, long id, void* msg, unsigned int dlc, unsigned int flag)
{
	canStatus stat;
	stat = canWrite(hnd[chn], id, msg, dlc, flag);
	check("canWrite", stat);
	if (stat != canOK) {
		return -1;
	}
	stat = canWriteSync(hnd[chn], 1000);
	check("canWriteSync", stat);
	if (stat != canOK) {
		return -1;
	}
	return 0;
}
