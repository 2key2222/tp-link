/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: logApi.c
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     This is the log module api
* information.
*  
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#ifdef USE_PHREAD
#include <pthread.h>
#endif
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdint.h>

#include "uci.h"
#include "logClient.h"
#include "logFile.h"
#include "logApi.h"
//#include "sysMtd.h"

LOG_CONFIG_ST g_logConfig;
LOG_CLIENT_CTX_ST g_logCliCtx_t;	
static unsigned char g_levelMask;
static FILE *fd_out = NULL;
static int g_flashEnable = 0;
static int g_serialInfo = -1;
static int g_level = -1;
static int g_time_flag = -1;
static int g_stdoutEnable = -1;
static int g_moduleLevel = 0;
static int g_moduleDebug = 0;
static char g_moduleName[32] = {0};
static char g_remoteAddress[20] = {0};

char g_log_path[64] = {0};
char g_log_message_path[64] = {0};
char g_log_bin_path[64] = {0};

static char g_module_name[256] = {0};
static char g_module_name_path[256] = {0};

//#define  LOG_PRINT(fmt,args...) if(fd_out){fprintf(fd_out, fmt, ##args);}
#define  LOG_PRINT(fmt,args...) while(0){};

static char g_LevelString[][10] = {
	"EMERG",			//LOG_EMERG
	"ALERT",			//LOG_ALERT
	"CRIT",			//LOG_CRIT
	"ERROR",			//LOG_ERR
	"WARNING",		//LOG_WARNING
	"NOTICE",		//LOG_NOTICE
	"INFO",			//LOG_INFO
	"DEBUG"			//LOG_DEBUG
};

char* g_LevelName[] = {
	"/tmp/logLevel/level_0",
	"/tmp/logLevel/level_1",
	"/tmp/logLevel/level_2",
	"/tmp/logLevel/level_3",
	"/tmp/logLevel/level_4",
	"/tmp/logLevel/level_5",
	"/tmp/logLevel/level_6",
	"/tmp/logLevel/level_7"
};

static char g_moduleWeb[][64] = {
	"audioDetection",
	"Bonjour",
	"Cloud",
	"DateTime",
	"System",
	"UserManage",
	"Wireless",
	"motion",
	"Client_mgmt",
	"Detection",
	"media-service",
	{0}
};

static int g_Index_Of_ModuleString = -1;

/*need modify when transplant*/
char g_moduleString[][64] = {
	"none",
	"audioDetection",
	"alarm_delivery",
	"autoUpgrade",
	"bonjour",
	"Button",
	"Cloud",
	"datetimed",
	"DayNight",
	"DevFind",
	"Device",
	"IpcSwitch",
	"librpm",
	"Location",
	"MDNew",
	"MsgPush",
	"NetConfig",
	"NetSwitch",
	"Oem",
	"Onvif",
	"rpc_mod",
	"rpms",
	"SD",
	"Session",
	"System",
	"tddp",
	"UPnP",
	"UserManage",
	"VideoControl",
	"Wireless",
	"WorkMode",
	"ADNew",
	"autoupgradenotice",
	"cloud",
	"ddns",
	"filecut",
	"ftpAlarmNew",
	"libcloud",
	"SDRecord",
	"speaker",
	"mediaService",
	"smtpAlarmNew",
	"vod",
	"server",
	"PTZ",
	"FTP",
	"Client_mgmt",
	"region",
	"motion",
	"imageCtrl",
	"detection",
	"NasRecord",
	"schedule",
	"shm",
	"mp4",
	"linkied",
	"relayd",
	"storage",
	"iot-client",
	"config-service",
	"snapshot",
	"timed",
	"healthinfo-service",
	"siren",
	"Led",
	{0}
};
static unsigned char g_Base64Index[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
static int logUnixSockInit(void);
static int logUnixSockUnInit(void);

#define _U8_TO_CHAR(c)	(((c) < 10) ? ((c) + '0') : ((c) - 10 + 'A'))
static int logByte2Str(const void *pIn, int byteLen, char *pStrOut, int nBufLen)
{
	size_t tmp;
	char cHi, cLo;
	const unsigned char *byte= (const unsigned char*)pIn;

	/* check parameter */
	if ((NULL == byte) ||
		(byteLen <= 0) ||
		(NULL == pStrOut) ||
		(nBufLen <= 0))
	{
		return -1;
	}

	/* check buffer length */
	if (nBufLen < (byteLen * 2 + 1))
	{
		return -1;
	}

	/* convert */
	memset(pStrOut, 0, nBufLen);
	for (tmp = 0; tmp < byteLen; tmp++)
	{
		cHi = (byte[tmp] >> 4) & 0x0F;
		cLo = (byte[tmp] >> 0) & 0x0F;
		pStrOut[tmp * 2 + 0] = _U8_TO_CHAR(cHi);
		pStrOut[tmp * 2 + 1] = _U8_TO_CHAR(cLo);
	}

	return 0;
}

static void logLock(void)
{
#ifdef USE_PHREAD
	pthread_mutex_lock(&g_logCliCtx_t.logMutex);
#endif
}

static void logUnLock(void)
{
#ifdef USE_PHREAD
	pthread_mutex_unlock(&g_logCliCtx_t.logMutex);
#endif
}

static int logSend(int sock, char *pBuf, int len)
{
	int ret = 0;
	int totalSendLen = 0;
	int needSendLen = len;

	if(NULL == pBuf){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	do{
		ret = send(sock, pBuf + totalSendLen, needSendLen, 0);
		if(ret < 0){
			if(errno == EINTR){
				continue;
			}

			LOG_PRINT("[%s:%d] send error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return FAILURE;
		}
		totalSendLen += ret;
		needSendLen -= ret;

	}while(needSendLen > 0);

	
	return SUCCESS;
}

static int logRecv(int sock, char *pBuf, int len)
{
	int ret = 0;
	int totalRecvLen = 0;
	int needRecvLen = len;
    fd_set fds;
    struct timeval overtime = {3,0};
    
	if(NULL == pBuf){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}    

	do{
        
        FD_ZERO(&fds);
        FD_SET(sock,&fds);
        overtime.tv_sec = 3;

        ret = select(sock+1,&fds,NULL,NULL,&overtime);
        if(ret > 0 && FD_ISSET(sock,&fds))
        {   			
		    ret = recv(sock, pBuf + totalRecvLen, needRecvLen, 0);			
		    if(ret <= 0){
			    if(errno == EINTR){
				    continue;
			    }
			    LOG_PRINT("[%s:%d] recv error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			    return FAILURE;
		    }

		    totalRecvLen += ret;
		    needRecvLen -= ret;
        
        }
        else
            return FAILURE;
        
	}while(needRecvLen > 0);

	return SUCCESS;
}

static int logMutexGetEnable(void)
{
	int logEnable = 0;
	
	logLock();
	logEnable = g_logCliCtx_t.logEnable;
	logUnLock();

	return logEnable;
}

static void logMutexSetEnable(int value)
{
	logLock();
	g_logCliCtx_t.logEnable = value;
	swLogCfgSetSerialInfo(value);
	logUnLock();
}

static int logUnixSockInit(void)
{
	#if 0
	socklen_t addrLen;

	addrLen = sizeof(struct sockaddr_un);

	logLock();
	g_logCliCtx_t.localUnixSock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(g_logCliCtx_t.localUnixSock < 0){
		LOG_PRINT("[%s:%d] socket error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logUnLock();
		return FAILURE;
	}

	g_logCliCtx_t.serUnixAddr.sun_family = AF_UNIX;
	strcpy(g_logCliCtx_t.serUnixAddr.sun_path,LOG_API_UNIX_DOMAIN);
	

	/*block*/
	if(connect(g_logCliCtx_t.localUnixSock, (struct sockaddr *)&g_logCliCtx_t.serUnixAddr, addrLen) < 0){
		LOG_PRINT("[%s:%d] connect() error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logUnLock();
		return FAILURE;
	}
	
	LOG_PRINT("[%s:%d] connect() success !\n", __FUNCTION__, __LINE__);
	logUnLock();
	#endif
	
	return SUCCESS;
}

static int logUnixSockUnInit(void)
{
	logLock();
	if(g_logCliCtx_t.localUnixSock != 0){
		close(g_logCliCtx_t.localUnixSock);
		g_logCliCtx_t.localUnixSock = 0;
	}

	logUnLock();
	return SUCCESS;
}

int LogLevelToInt(char *level)
{
	if(NULL == level){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	int i = 0;
	
	for(i = 0; i < 8; i++)
	{
		if(strncmp(level, g_LevelString[i], strlen(level)) == 0){

			return i;
		}
	}
	
	return -1;
}

/*base64 encode*/
int logBase64Encode(unsigned char *pIn, unsigned char *pOut, int nBufLen)
{
	unsigned char cByte1 = 0;  /*the first char*/
	unsigned char cByte2 = 0;
	unsigned char cByte3 = 0;
	unsigned char cByte4 = 0;
	int nInputLen = (NULL==pIn)?0:strlen((char *)pIn);
	
	if(NULL == pIn 
		|| NULL == pOut
		|| nBufLen < nInputLen)
	{
		return -1;
	}

	while(nInputLen > 0)
	{
		if(nBufLen < 4)
		{
			return -1;
		}
		
		cByte1 = 0x3F & ((*(pIn) & 0xFC) >> 2); /*byte1[0]-byte1[5] to cByte1[0]-cByte1[5]*/
		cByte2 = 0x30 & ((*(pIn++) & 0x03) << 4); /*byte1[6]-byte1[7] to cByte2[0]-cByte2[1]*/
		cByte3 = 64;
		cByte4 = 64;

		if(nInputLen > 1)
		{
			cByte2 |= 0x0F & ((*(pIn) & 0xF0) >> 4);
			cByte3 = 0x3C & ((*(pIn++) & 0x0F) << 2);
		}
		if(nInputLen > 2)
		{
			cByte3 |= 0x03 & ((*(pIn) & 0xC0) >> 6);
			cByte4 = 0x3F & ((*(pIn++) & 0x3F )); 
		}

		*pOut++ = g_Base64Index[cByte1];
		*pOut++ = g_Base64Index[cByte2];
		*pOut++ = g_Base64Index[cByte3];
		*pOut++ = g_Base64Index[cByte4];
		nBufLen -= 4;
		nInputLen -= 3;
	}
	
	*pOut = 0;
	return 0;
}

static void logPrintfIndex(LOG_FILE_INDEX_ST *pLogIndex_t)
{
	LOG_PRINT("fileOldestIndex:%d, fileNewestIndex:%d\n", pLogIndex_t->fileOldestIndex, pLogIndex_t->fileNewestIndex);
	LOG_PRINT("fileTotalSize:%d\n", pLogIndex_t->fileTotalSize);
	LOG_PRINT("fileNumber:%d\n", pLogIndex_t->fileNumber);
	LOG_PRINT("fileOldestIndex:%d\n", pLogIndex_t->fileOldestIndex);
	LOG_PRINT("fileNewestIndex:%d\n", pLogIndex_t->fileNewestIndex);
	LOG_PRINT("fileBuiltTime:%s\n", pLogIndex_t->fileBuiltTime);

	return;
}

static int logFullRead(int fd, void *buf, int nbytes)
{
	if(NULL == buf){
		LOG_PRINT("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	int ret = 0;
	int nread = 0;

	while(nread < nbytes){
		ret = read(fd, (char *)buf + nread, nbytes - nread);
		if(ret < 0){
			if(ret == EINTR || ret == EAGAIN){
				sleep(1);
				continue;
			}
			
			LOG_PRINT("[%s:%d] read error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return -1;
		}else if(ret == 0){
			break;
		}

		nread += ret;
	}

	return nread;
}

static int logGetIndexInfo(LOG_FILE_INDEX_ST *pLogIndex_t)
{		
	if(NULL == pLogIndex_t){
		LOG_PRINT("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	int fd = -1;

	fd = open(g_log_bin_path, O_RDONLY);
	if(fd == -1){
		LOG_PRINT("[%s:%d] open %s error:%s\n", __FUNCTION__, __LINE__, g_log_bin_path, strerror(errno));
		return -1;
	}

	if(logFullRead(fd, pLogIndex_t, sizeof(LOG_FILE_INDEX_ST)) < 0){
		LOG_PRINT("[%s:%d] read %s \n", __FUNCTION__, __LINE__, g_log_bin_path);
		return -1;
	}
	logPrintfIndex(pLogIndex_t);
		
	close(fd);
	return 0;
}

static int logGetBakFile(char *filePath)
{		
	if(NULL == filePath){
		LOG_PRINT("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	int fd = -1;
	LOG_FILE_INDEX_ST logIndex_t;
	memset(&logIndex_t, 0, sizeof(logIndex_t));

	fd = open(g_log_bin_path, O_RDONLY);
	if(fd == -1){
		LOG_PRINT("[%s:%d] open %s error:%s\n", __FUNCTION__, __LINE__, filePath, strerror(errno));
		return -1;
	}

	if(logFullRead(fd, &logIndex_t, sizeof(logIndex_t)) < 0){
		LOG_PRINT("[%s:%d] read %s \n", __FUNCTION__, __LINE__, g_log_bin_path);
		return -1;
	}
	logPrintfIndex(&logIndex_t);

	sprintf(filePath, "%s/message_bak_%04d.log", g_log_path, logIndex_t.fileNewestIndex);
	LOG_PRINT("logGetBakFile filePath:%s\n", filePath);
		
	close(fd);
	return 0;
}

/*******for http or serverCtrl process*******/
int swLogInit(void)
{
	memset(&g_logCliCtx_t, 0, sizeof(g_logCliCtx_t));
#ifdef USE_PHREAD	
	pthread_mutex_init(&g_logCliCtx_t.logMutex, NULL);
#endif

	if(logUnixSockInit() < 0){
		LOG_PRINT("[%s:%d] logUnixSockInit error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	g_logCliCtx_t.openFlag = 1;

	return SUCCESS;
}

int swLogUnInit(void)
{

	logUnixSockUnInit();

#ifdef USE_PHREAD
	pthread_mutex_destroy(&g_logCliCtx_t.logMutex);
#endif
	
	return SUCCESS;
}

int swLogGetWebModuleIndex(char *moduleName)
{
	int i = 0;
	int ret = FAILURE;

	if(NULL == moduleName ){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	for(i =  0; i < INDEX_MODULE_END; i++){
		if(g_moduleWeb[i] == 0){
			LOG_PRINT("out of current module totalNum , i:%d\n", i);
			break;
		}
		if(0 == strcmp(g_moduleWeb[i], moduleName)){
			ret = i;
			break;
		}
	}

	return ret;	
}


int swLogGetModuleIndex(char *moduleName)
{
	int i = 0;
	int ret = FAILURE;

	if(NULL == moduleName ){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	for(i =  0; i < INDEX_MODULE_END; i++){
		if(g_moduleString[i] == 0){
			LOG_PRINT("out of current module totalNum , i:%d\n", i);
			break;
		}
		if(0 == strcmp(g_moduleString[i], moduleName)){
			ret = i;
			break;
		}
	}

	return ret;	
}

char* swLogGetLevelName(int index)
{
	if(index < 0 ||index >= 8 ){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return NULL;
	}
	
	return g_LevelString[index];
}

char* swLogGetModuleName(int index)
{
	if(index < 0 ||index >= INDEX_MODULE_END ){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return NULL;
	}
	
	return g_moduleString[index];
}

char* swLogGetModuleName2(int index)
{
	if(index < 0 ||index >= INDEX_MODULE_END ){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return "";
	}

	if (g_Index_Of_ModuleString >= 0)
		return g_moduleString[g_Index_Of_ModuleString];
	else
		return g_moduleString[index];
}

/*
*such as:swLogSetLevelCustom(LEVEL_EMERG | LEVEL_WARNING | LEVEL_INFO);
*/
int swLogSetLevelCustom(unsigned char mask)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_SET_LEVEL;
	logMsg.msgLevelMask = mask;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

/*
*all msg which's level less than logLevel can be write into the log file
*/
int swLogSetLevel(LOG_LEVEL_T logLevel)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsg, 0, sizeof(logMsg));

	switch(logLevel)
	{
		case LEVEL_EMERG:
			logMsg.msgLevelMask = LEVEL_EMERG;
			break;

		case LEVEL_ALERT:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT;
			break;

		case LEVEL_CRIT:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT |LEVEL_CRIT;
			break;

		case LEVEL_ERR:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT |LEVEL_CRIT |LEVEL_ERR;
			break;

		case LEVEL_WARNING:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT |LEVEL_CRIT |LEVEL_ERR |LEVEL_WARNING;
			break;

		case LEVEL_NOTICE:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT |LEVEL_CRIT |LEVEL_ERR |LEVEL_WARNING 
							|LEVEL_NOTICE;
			break;

		case LEVEL_INFO:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT |LEVEL_CRIT |LEVEL_ERR |LEVEL_WARNING 
							|LEVEL_NOTICE |LEVEL_INFO;
			break;

		case LEVEL_DEBUG:
			logMsg.msgLevelMask = LEVEL_EMERG | LEVEL_ALERT |LEVEL_CRIT |LEVEL_ERR |LEVEL_WARNING 
							|LEVEL_NOTICE |LEVEL_INFO |LEVEL_DEBUG;
			break; 

		default:
			LOG_PRINT("[%s:%d] no know level\n", __FUNCTION__, __LINE__);
			break;
	}

	logMsg.msgLevel = logLevel;
	logMsg.msgType = LOG_MSG_SET_LEVEL;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRenv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}

unsigned char  swLogGetLevel(void)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_GET_LEVEL;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error localSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error localSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
		return FAILURE;
	}

	return logMsgRecv.msgLevelMask;
}


int swLogSetModule(unsigned long long mask)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_SET_MODULE;
	logMsg.msgModuleMask = mask;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

uint64_t  swLogGetModule(void)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_GET_MODULE;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error localSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logSend() error localSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
		return FAILURE;
	}

	return logMsgRecv.msgModuleMask;
}

int  swLogSetEnableFlag(int enable)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_SET_ENABLE;
	logMsg.msgLogEnable = enable;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

int  swLogGetEnableFlag(void)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_GET_ENABLE;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error localUnixSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logSend() error localUnixSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
		return FAILURE;
	}

	return logMsgRecv.msgLogEnable;
}

int  swLogGetNetFlag(void)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_GET_NETWORK;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return logMsgRecv.msgLogNet;
}


int swLogOpenNetWork(void)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_OPEN_NETWORK;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}

int swLogCloseNetWork(void)
{
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_CLOSE_NETWORK;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
} 


/*******for every process*******/
int swLogOpen(char *processName)
{
	if(NULL == processName){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	sprintf(g_module_name, "%s", processName);
	sprintf(g_module_name_path, "/tmp/logLevel/%s", processName);

	if(fd_out == NULL){
		fd_out = fopen("/dev/console", "w");
		if(!fd_out){
			LOG_PRINT("fopen /dev/console error:%s\n", strerror(errno));
		}
	}

	swLogCfgInit();

	if(g_flashEnable){
		openlogd(processName, LOG_CONS|LOG_NDELAY, LOG_LOCAL0);
		//swLogInit();
	}

	return SUCCESS;
}

int swLogOpenWithoutPthread(char *processName)
{
	if(NULL == processName){
		LOG_PRINT("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	sprintf(g_module_name, "%s", processName);

	if(fd_out == NULL){
		fd_out = fopen("/dev/console", "w");
		if(!fd_out){
			LOG_PRINT("fopen /dev/console error:%s\n", strerror(errno));
		}
	}

	swLogCfgInit();
	openlogd(processName,LOG_CONS|LOG_NDELAY, LOG_LOCAL0);
	
	memset(&g_logCliCtx_t, 0, sizeof(g_logCliCtx_t));
	g_logCliCtx_t.openFlag = 1;

	if(logUnixSockInit() < 0){
		LOG_PRINT("[%s:%d] logUnixSockInit error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

int swLogWriteWithoutModelfliter(int level, char *moduleName, const char *func, int line, const char * format,...)
{
	int len = 0;
	int lenStd = 0;
	char msg[5*1024] = {0};
	char msgStd[5*1024] = {0};
	va_list ap_list;

	if(!moduleName){
		LOG_PRINT("[%s:%d] func moduleName parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(level > g_level)
		return 0;

	va_start(ap_list, format);
	
	sprintf(msgStd, "[%s:%d] ", func, line);
	lenStd = strlen(msgStd);
	vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);

	if(LOG_CONSOLE_SWITCH){
		LOG_PRINT("%s\n", msgStd);
	}

	if(g_flashEnable == 1){
		sprintf(msg, "TP_%s: ", moduleName);
		len = strlen(msg);
		vsnprintf(msg + len, sizeof(msg) - len, format,ap_list);
		mySyslog(level, msg);
	}
	
	va_end(ap_list);
	return SUCCESS;
}

int swLogHighLight(int level, int moduleIndex, const char *func, int line, const char * format,...)
{
	int len = 0;
	int lenStd = 0;
	char msg[5*1024] = {0};
	char msgStd[5*1024] = {0};
	va_list ap_list;

	if(g_moduleDebug == 1){
		if(access(g_module_name_path, F_OK) != 0){
			return 0;
		}
	}
	
	if(access(g_LevelName[level], F_OK) != 0){
		return 0;
	}

	va_start(ap_list, format);
	
	sprintf(msgStd, COLOR_GREEN"[%s]"COLOR_NONE"[%s:%d] "COLOR_YELLOW, g_module_name, func, line);
	lenStd = strlen(msgStd);
	vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);
	
	if(g_stdoutEnable == 1){
		fprintf(stdout, "%s"COLOR_NONE, msgStd);
		fflush(stdout);
	}

	if(swLogCfgGetSerialInfo() == 1){
		if(fd_out){
			fprintf(fd_out, "%s"COLOR_NONE, msgStd);
			fflush(fd_out);
		}
	}

	if(g_flashEnable == 1){
		sprintf(msg, "TP_%s: ", g_module_name);
		len = strlen(msg);
		vsnprintf(msg + len, sizeof(msg) - len - 1, format,ap_list);
		mySyslog(level, msg);
	}
	
	va_end(ap_list);
	return SUCCESS;
}

int swLogWriteError(int level, int moduleIndex, const char *func, int line, const char * format,...)
{
	int len = 0;
	int lenStd = 0;
	char msg[5*1024] = {0};
	char msgStd[5*1024] = {0};
	va_list ap_list;
	time_t nowTime;
	struct tm nowTm;
	char strNowTime[20] = {0};

	if(g_moduleDebug == 1){
		if(access(g_module_name_path, F_OK) != 0){
			return 0;
		}
	}

	if(access(g_LevelName[level], F_OK) != 0){
		return 0;
	}

	va_start(ap_list, format);
	
	time(&nowTime);
	localtime_r(&nowTime, &nowTm);
	strftime(strNowTime, sizeof(strNowTime), "%Y-%m-%d/%H:%M:%S", &nowTm);
	sprintf(msgStd, COLOR_GREEN"[%s][%s]"COLOR_NONE"[%s:%d] "COLOR_RED, g_module_name, strNowTime, func, line);
	lenStd = strlen(msgStd);
	vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);

	if(g_stdoutEnable == 1){
		fprintf(stdout, "%s"COLOR_NONE, msgStd);
		fflush(stdout);
	}

	if(swLogCfgGetSerialInfo() == 1){
		if(fd_out){
			fprintf(fd_out, "%s"COLOR_NONE, msgStd);
			fflush(fd_out);
		}
	}

	if(g_flashEnable == 1){
		sprintf(msg, "TP_%s: ", g_module_name);
		len = strlen(msg);
		vsnprintf(msg + len, sizeof(msg) - len - 1, format,ap_list);
		mySyslog(level, msg);
	}
	
	va_end(ap_list);
	return SUCCESS;
}


int swLogDebugAdvanced(int level, char *moduleName, const char *func, int line, const char * format,...)
{
	if(!moduleName){
		LOG_PRINT("[%s:%d] func moduleName parameter error\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	int len = 0;
	int lenStd = 0;
	char msgStd[5*1024] = {0};
	va_list ap_list;
	
	if(level > g_moduleLevel || strcmp(moduleName, g_moduleName) != 0)
		return 0;

	va_start(ap_list, format);
	
	sprintf(msgStd, COLOR_GREEN"[%s]"COLOR_NONE"[%s:%d] debug--:"COLOR_YELLOW, moduleName, func, line);
	lenStd = strlen(msgStd);
	vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);

	if(g_stdoutEnable == 1){
		fprintf(stdout, "%s"COLOR_NONE, msgStd); 
		fflush(stdout);
	}

	if(swLogCfgGetSerialInfo() == 1){
		if(fd_out){
			fprintf(fd_out, "%s", msgStd);
			fflush(fd_out);
		}
	}

	va_end(ap_list);
	return SUCCESS;
}

void swLogShowData(char *pData, int len)
{
	if(!fd_out)
		return;

	int i = 0;

	for(i = 0; i < len; i++){
		if(pData[i] == 13)
			fprintf(fd_out, " (%02x ", pData[i]);
		else if(pData[i] == 10)
			fprintf(fd_out, "%02x )\n", pData[i]);
		else
			fprintf(fd_out, "%02x ", pData[i]);
	}
	
	fprintf(fd_out, "\n");
}

int swLogWrite(int level, int moduleIndex, const char *func, int line, const char * format,...)
{
	int len = 0;
	int lenStd = 0;
	char msg[5*1024] = {0};
	char msgStd[5*1024] = {0};
	va_list ap_list;
	time_t nowTime;
	struct tm nowTm;
	char strNowTime[32] = {0};
	char *content_color = COLOR_NONE;

	if(g_moduleDebug == 1){
		if(access(g_module_name_path, F_OK) != 0){
			return 0;
		}
	}
	
	if(access(g_LevelName[level], F_OK) != 0){
		return 0;
	}

	if (level <= MYLOG_ERR){
		content_color = COLOR_RED;
	}

	va_start(ap_list, format);

	if(g_time_flag == 1){
		time(&nowTime);
		localtime_r(&nowTime, &nowTm);
		strftime(strNowTime, sizeof(strNowTime), "%Y-%m-%d/%H:%M:%S", &nowTm);
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		int ms = ts.tv_nsec/1000000;
		char timeWithMs[32];
		snprintf(timeWithMs, sizeof(timeWithMs), "%s %d", strNowTime, ms);
		
		sprintf(msgStd, COLOR_GREEN"[%s]"COLOR_YELLOW"[%s]"COLOR_NONE"[%s:%d] %s", g_module_name, timeWithMs, func, line, content_color);
		lenStd = strlen(msgStd);
		vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);
		if(g_stdoutEnable == 1){
			fprintf(stdout, "%s"COLOR_NONE, msgStd);
			fflush(stdout);
		}
		if(g_serialInfo == 1 && fd_out != NULL){
			fprintf(fd_out, "%s"COLOR_NONE, msgStd);
			fflush(fd_out);
		}
	}else{
		sprintf(msgStd, COLOR_GREEN"[%s]"COLOR_NONE"[%s:%d] ", g_module_name, func, line);
		lenStd = strlen(msgStd);
		vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);
		if(g_stdoutEnable == 1){
			fprintf(stdout, "%s", msgStd); 
			fflush(stdout);
		}
		if(g_serialInfo == 1 && fd_out != NULL){
			fprintf(fd_out, "%s", msgStd);
			fflush(fd_out);
		}
	}

	if(g_flashEnable == 1){
		sprintf(msg, "TP_%s: ", g_module_name);
		len = strlen(msg);
		vsnprintf(msg + len, sizeof(msg) - len - 1, format,ap_list);
		mySyslog(level, msg);
	}
	
	va_end(ap_list);
	return SUCCESS;
}


int swLogWriteWithTime(int level, int moduleIndex, const char *func, int line, const char * format,...)
{
	int len = 0;
	int lenStd = 0;
	char msg[5*1024] = {0};
	char msgStd[5*1024] = {0};
	va_list ap_list;
	time_t nowTime;
	struct tm nowTm;
	char strNowTime[32] = {0};
	char *content_color = COLOR_NONE;

	if(g_moduleDebug == 1){
		if(access(g_module_name_path, F_OK) != 0){
			return 0;
		}
	}
	
	if(access(g_LevelName[level], F_OK) != 0){
		return 0;
	}

	if (level <= MYLOG_ERR){
		content_color = COLOR_RED;
	}

	time(&nowTime);
	localtime_r(&nowTime, &nowTm);
	strftime(strNowTime, sizeof(strNowTime), "%Y-%m-%d/%H:%M:%S", &nowTm);
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	int ms = ts.tv_nsec/1000000;
	char timeWithMs[32];
	snprintf(timeWithMs, sizeof(timeWithMs), "%s %d", strNowTime, ms);

	va_start(ap_list, format);

	sprintf(msgStd, COLOR_GREEN"[%s]"COLOR_YELLOW"[%s]"COLOR_NONE"[%s:%d] %s", g_module_name, timeWithMs, func, line, content_color);
	lenStd = strlen(msgStd);
	vsnprintf(msgStd + lenStd, sizeof(msgStd) - lenStd - 1, format,ap_list);

	if(g_stdoutEnable == 1){
		fprintf(stdout, "%s"COLOR_NONE, msgStd);
		fflush(stdout);
	}

	if(swLogCfgGetSerialInfo() == 1){
		if(fd_out){
			fprintf(fd_out, "%s"COLOR_NONE, msgStd);
			fflush(fd_out);
		}
	}

	if(g_flashEnable == 1){
		sprintf(msg, "TP_%s: ", g_module_name);
		len = strlen(msg);
		vsnprintf(msg + len, sizeof(msg) - len, format,ap_list);
		mySyslog(level, msg);
	}

	va_end(ap_list);
	return SUCCESS;
}


static int logFileGetIndex(LOG_FILE_INDEX_ST *logIndex_t)
{		
	if(NULL == logIndex_t){
		LOG_PRINT("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	int fd = -1;

	fd = open(g_log_bin_path, O_RDONLY);
	if(fd == -1){
		LOG_PRINT("[%s:%d] open %s error:%s\n", __FUNCTION__, __LINE__, g_log_bin_path, strerror(errno));
		return -1;
	}

	if(logFullRead(fd, logIndex_t, sizeof(LOG_FILE_INDEX_ST)) < 0){
		LOG_PRINT("[%s:%d] read %s \n", __FUNCTION__, __LINE__, g_log_bin_path);
		return -1;
	}
	logPrintfIndex(logIndex_t);
 		
	close(fd);
	return 0;
}

static int swLogQueryHandle(char *filePath, int level, char* modName, 
						int number, char* outbuff, int bufSize, int *totalNumber, int *totalSize)
{
	int i = 0;
	int ret = 0;
	int ret_status = 0;
	size_t size = 0;
	char *line = NULL;
	char bufLine[LOG_MSG_LEN] = {'\0'};
	char msgBUf[LOG_MSG_LEN] = {0};
	int pIndex = LOG_SINGLE_FILE_LINE_MAX;
	char *linePtr[LOG_SINGLE_FILE_LINE_MAX] = {NULL};
	LOG_FILE_ST logFile;

	LOG_PRINT("[%s:%d] swLogQueryHandle path:%s\n", __FUNCTION__, __LINE__, filePath);
	/*read line from file*/
	FILE* fpLog = fopen(filePath, "r");
	if(NULL != fpLog){
		while((-1 != getline(&line, &size, fpLog)) && (pIndex > 0)){
			if(NULL != line){
				linePtr[--pIndex] = line;
				line = NULL;
			}
		}

		if(NULL != line){
			free(line);
			line = NULL;
		}
		fclose(fpLog);
	}
	else{
		LOG_PRINT("[%s:%d] fopen error:%s, path:%s\n", __FUNCTION__, __LINE__, strerror(errno), filePath);
	}

	/*handle log message*/
	for(i = pIndex; i < LOG_LINE_QUERY_MAX ; i++){// use number

		if(ret_status == LOG_QUERY_STATUS_BUF_NOT_ENOUGH || ret_status == LOG_QUERY_STATUS_OK){
			free(linePtr[i]);
			linePtr[i] = NULL;
			continue;
		}

		LOG_PRINT("[%s:%d] swLogQueryHandle totalNumber:%d, number:%d\n", __FUNCTION__, __LINE__, *totalNumber, number);
		if(*totalNumber >= number){
			ret_status = LOG_QUERY_STATUS_OK;
			free(linePtr[i]);
			linePtr[i] = NULL;
			continue;
		}
		
		memset(&logFile, 0, sizeof(logFile));
		ret = sscanf(linePtr[i], "%s %s %s %[^\n]\n", logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, logFile.logMsg);
		logFile.logLevel = LogLevelToInt(logFile.logLevelStr);
		LOG_PRINT("[%s:%d] linePtr[i]:%s\n", __FUNCTION__, __LINE__, linePtr[i]);
		
		if((0 != strcmp(LOG_MODULE_ALL, modName) && (0 != strcmp(modName, logFile.logModuleName))) 
			|| (LOG_LEVEL_ALL != level && level != logFile.logLevel)){
			free(linePtr[i]);
			linePtr[i] = NULL;
			continue;
		}

		if(swLogCfgGetWebModelFilterEn()){
			if(swLogGetWebModuleIndex(logFile.logModuleName) < 0 || MYLOG_DEBUG == logFile.logLevel){
				free(linePtr[i]);
				linePtr[i] = NULL;
				continue;
			}
		}

		if(swLogCfgGetBase64Enable()){
			logBase64Encode((unsigned char *)logFile.logMsg, (unsigned char *)msgBUf, sizeof(msgBUf));
			sprintf(bufLine, "{\"time\":\"%s\",\"module\":\"%s\",\"level\":\"%s\",\"msg\":\"%s\"},", 
					logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, msgBUf);
		}else{
			sprintf(bufLine, "{\"time\":\"%s\",\"module\":\"%s\",\"level\":\"%s\",\"msg\":\"%s\"},", 
					logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, logFile.logMsg);
		}

		if(*totalSize + strlen(bufLine) > bufSize){
			ret_status = LOG_QUERY_STATUS_BUF_NOT_ENOUGH;
		}else{
			*totalSize += strlen(bufLine);
			strcat(outbuff, bufLine);
			(*totalNumber)++;
		}

		free(linePtr[i]);
		linePtr[i] = NULL;
	}

	LOG_PRINT("[%s:%d] swLogQueryHandle ret:%d\n", __FUNCTION__, __LINE__, ret_status);
	return ret_status;
}

int swLogQueryByNumber(int level, char* modName, int number, char* outbuff, int bufSize)
{
	if( NULL == modName ||NULL == outbuff || level < 0 || level > 8 ){
		LOG_PRINT("[%s:%d] parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	int i = 0;
	int ret = 0;
	int totalNumber = 0;
	int totalSize = 0;
	char filePath[255] = {0};
	char *p = NULL;
	LOG_FILE_INDEX_ST logIndex_t;

	memset(&logIndex_t, 0, sizeof(logIndex_t));
	memset(outbuff, 0, bufSize);
	sprintf(outbuff, "%c", '[');

	/*get log from file:message_cache.log */
	if(LOG_CACHE_SWITCH){
		ret = swLogQueryHandle(LOG_FILE_PATH_CACHE, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
		if(ret > 0){
			LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
				, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
			goto OUT;
		}
	}

	/*get log from file:message.log */
	ret = swLogQueryHandle(g_log_message_path, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
	if(ret > 0){
		LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
			, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
		goto OUT;
	}
	
	/*get log from file:message_bak_*.log */
	if(logFileGetIndex(&logIndex_t) > 0){
		LOG_PRINT("[%s:%d] logFileGetIndex error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logIndex_t.fileNewestIndex >= logIndex_t.fileOldestIndex){
		do{
			sprintf(filePath, "%s/message_bak_%04d.log", g_log_path, logIndex_t.fileNewestIndex);
			ret = swLogQueryHandle(filePath, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
			if(ret > 0){
				LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
					, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
				goto OUT;
			}
	
			logIndex_t.fileNewestIndex--;
		}while(logIndex_t.fileNewestIndex >= logIndex_t.fileOldestIndex);
	}else{
		do{
			sprintf(filePath, "%s/message_bak_%04d.log", g_log_path, logIndex_t.fileNewestIndex);
			ret = swLogQueryHandle(filePath, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
			if(ret > 0){
				LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
					, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
				goto OUT;
			}
			
			logIndex_t.fileNewestIndex--;
		}while(logIndex_t.fileNewestIndex >= 0);

		for(i = FILE_INDEX_MAX; i >= logIndex_t.fileOldestIndex; i--){
			sprintf(filePath, "%s/message_bak_%04d.log", g_log_path, i);
			ret = swLogQueryHandle(filePath, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
			if(ret > 0){
				LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
					, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
				goto OUT;
			}
		}
	}

OUT:
	p = strrchr(outbuff, ',');
	if(NULL != p){
		*p = ' ';
	}
	
	sprintf(outbuff + strlen(outbuff), "%c", ']');

	return totalNumber;
}

int swLogQueryByNumJson(int level, char* modName, int number, char* outbuff, int bufSize)
{
	if( NULL == modName ||NULL == outbuff || level < 0 || level > 8 ){
		LOG_PRINT("[%s:%d] parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	int i = 0;
	int ret = 0;
	int totalNumber = 0;
	int totalSize = 0;
	char filePath[255] = {0};
	char *p = NULL;
	LOG_FILE_INDEX_ST logIndex_t;

	memset(&logIndex_t, 0, sizeof(logIndex_t));
	memset(outbuff, 0, bufSize);
	sprintf(outbuff, "{\"errorCode\":%d,\"log\": ", 0);
	sprintf(outbuff + strlen(outbuff), "%c", '[');

	/*get log from file:message_cache.log */
	if(LOG_CACHE_SWITCH){
		ret = swLogQueryHandle(LOG_FILE_PATH_CACHE, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
		if(ret > 0){
			LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
				, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
			goto OUT;
		}
	}

	/*get log from file:message.log */
	ret = swLogQueryHandle(g_log_message_path, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
	if(ret > 0){
		LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
			, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
		goto OUT;
	}
	
	/*get log from file:message_bak_*.log */
	if(logFileGetIndex(&logIndex_t) > 0){
		LOG_PRINT("[%s:%d] logFileGetIndex error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logIndex_t.fileNewestIndex >= logIndex_t.fileOldestIndex){
		do{
			sprintf(filePath, "%s/message_bak_%04d.log", g_log_path, logIndex_t.fileNewestIndex);
			ret = swLogQueryHandle(filePath, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
			if(ret > 0){
				LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
					, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
				goto OUT;
			}
	
			logIndex_t.fileNewestIndex--;
		}while(logIndex_t.fileNewestIndex >= logIndex_t.fileOldestIndex);
	}else{
		do{
			sprintf(filePath, "%s/message_bak_%04d.log", g_log_path,logIndex_t.fileNewestIndex);
			ret = swLogQueryHandle(filePath, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
			if(ret > 0){
				LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
					, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
				goto OUT;
			}
			
			logIndex_t.fileNewestIndex--;
		}while(logIndex_t.fileNewestIndex >= 0);

		for(i = FILE_INDEX_MAX; i >= logIndex_t.fileOldestIndex; i--){
			sprintf(filePath, "%s/message_bak_%04d.log", g_log_path,i);
			ret = swLogQueryHandle(filePath, level, modName, number, outbuff, bufSize, &totalNumber, &totalSize);
			if(ret > 0){
				LOG_PRINT("[%s:%d] get log totalNumber:%d, number:%d, totalSize:%d, bufSize:%d\n"
					, __FUNCTION__, __LINE__, totalNumber, number, totalSize, bufSize);
				goto OUT;
			}
		}
	}

OUT:
	//LOG_PRINT("outbuff:%s\n", outbuff);
	if(totalNumber > 0){
		p = strrchr(outbuff, ',');
		if(NULL != p){
			*p = ' ';
		}
	}
	
	sprintf(outbuff + strlen(outbuff), "%c%c", ']', '}');

	return totalNumber;
}


/*return the newest log line by order*/
int swLogQuery(int level, char* modName, int number, char* outbuff, int bufSize)
{
	if( NULL == modName ||NULL == outbuff || level < 0 || level > 8 ){
		LOG_PRINT("[%s:%d] parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(bufSize < number*LOG_MSG_LEN){
		LOG_PRINT("[%s:%d] size is not enough large\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	int i = 0;
	int ret = 0;
	int totalLine = 0;
	int totalSize = 0;
	int pIndex = LOG_LINE_QUERY_MAX ;
	size_t size = 0;
	char *line = NULL;
	char bufLine[LOG_MSG_LEN] = {'\0'};
	char msgBUf[LOG_MSG_LEN ] = {0};
	char *linePtr[LOG_LINE_QUERY_MAX] = {NULL};
	char filePath[255] = {0};
	LOG_FILE_ST logFile;

	LOG_PRINT("[%s:%d] level:%d, modName:%s, number:%d\n", __FUNCTION__, __LINE__, level, modName, number);
	/*get the old file*/
	logGetBakFile(filePath);
	
	FILE* fpLog = fopen(filePath, "r");
	if(NULL != fpLog){
		while((-1 != getline(&line, &size, fpLog)) && (pIndex > 0)){
			if(NULL != line){
				linePtr[--pIndex] = line;
				line = NULL;
			}
		}

		if(NULL != line){
			free(line);
			line = NULL;
		}
		fclose(fpLog);
	}
	else{
		LOG_PRINT("[%s:%d] fopen error:%s, path:%s\n", __FUNCTION__, __LINE__, strerror(errno), filePath);
	}

	/*get the new file*/
	fpLog = fopen(g_log_message_path, "r");
	if(NULL != fpLog){
		while((-1 != getline(&line, &size, fpLog)) &&  (pIndex > 0)){
			if(NULL != line){
				linePtr[--pIndex] = line;
				line = NULL;
			}
		}
		
		if(NULL != line){
			free(line);
			line = NULL;
		}
		fclose(fpLog);
	}
	else{
		LOG_PRINT("[%s:%d] fopen error:%s, path:%s\n", __FUNCTION__, __LINE__, strerror(errno), g_log_message_path);
	}
	
	if(LOG_CACHE_SWITCH){
		/*get the cache file*/
		fpLog = fopen(LOG_FILE_PATH_CACHE, "r");
		if(NULL != fpLog){
			while((-1 != getline(&line, &size, fpLog)) && (pIndex > 0)){
				if(NULL != line){
					linePtr[--pIndex] = line;
					line = NULL;
				}
			}
			
			if(NULL != line){
				free(line);
				line = NULL;
			}
			fclose(fpLog);
		}
		else{
			LOG_PRINT("[%s:%d] fopen error:%s, path:%s\n", __FUNCTION__, __LINE__, strerror(errno), LOG_FILE_PATH_CACHE);
		}
	}
	LOG_PRINT("pIndex:%d == \n", pIndex);

	/* get the write line */
	memset(outbuff, 0, bufSize);
	sprintf(outbuff, "%c", '[');
	totalLine = LOG_LINE_QUERY_MAX - pIndex;
	
	for(i = pIndex; i < LOG_LINE_QUERY_MAX ; i++){// use number

		if(number <= 0){
			free(linePtr[i]);
			linePtr[i] = NULL;
			continue;
		}
		
		memset(&logFile, 0, sizeof(logFile));
		ret = sscanf(linePtr[i], "%s %s %s %[^\n]", logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, logFile.logMsg);
		logFile.logLevel = LogLevelToInt(logFile.logLevelStr);
		
		if((0 != strcmp(LOG_MODULE_ALL, modName) && (0 != strcmp(modName, logFile.logModuleName))) 
			|| (LOG_LEVEL_ALL != level && level != logFile.logLevel) 
			|| MYLOG_DEBUG == logFile.logLevel){

			free(linePtr[i]);
			linePtr[i] = NULL;
			continue;
		}

		if(swLogCfgGetWebModelFilterEn()){
			if(swLogGetWebModuleIndex(logFile.logModuleName) < 0){
				free(linePtr[i]);
				linePtr[i] = NULL;
				continue;
			}
		}

		if(swLogCfgGetBase64Enable()){
			logBase64Encode((unsigned char *)logFile.logMsg, (unsigned char *)msgBUf, sizeof(msgBUf));
			sprintf(bufLine, "{\"time\":\"%s\",\"module\":\"%s\",\"level\":\"%s\",\"msg\":\"%s\"},", 
					logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, msgBUf);
		}else{
			sprintf(bufLine, "{\"time\":\"%s\",\"module\":\"%s\",\"level\":\"%s\",\"msg\":\"%s\"},", 
					logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, logFile.logMsg);
		}
		
		totalSize += strlen(bufLine);
		strcat(outbuff, bufLine);
		number--;
		
		free(linePtr[i]);
		linePtr[i] = NULL;
	}
	
	char *p = strrchr(outbuff, ',');
	if(NULL != p){
		*p = ' ';
	}
	
	sprintf(outbuff + strlen(outbuff), "%c", ']');
	LOG_PRINT("[%s:%d] get log line number:%d\n", __FUNCTION__, __LINE__, totalLine);
	
	return SUCCESS;
}

int swLogSaveDo(int level, char* modName, char *srcFile, FILE* fpSaveLog)
{
	if(NULL == srcFile || NULL == fpSaveLog){
		LOG_PRINT("[%s:%d] parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	int ret = 0;
	size_t size = 0;
	char *line = NULL;
	LOG_FILE_ST logFile;
	
	memset(&logFile, 0, sizeof(logFile));
	
	FILE* fpLogSrc = fopen(srcFile, "r");
	if(NULL != fpLogSrc){
		/*get the src file*/
		while(-1 != getline(&line, &size, fpLogSrc)){

			memset(&logFile, 0, sizeof(logFile));
			ret = sscanf(line, "%s %s %s %[^\n]", logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, logFile.logMsg);
			logFile.logLevel = LogLevelToInt(logFile.logLevelStr);
			
			if((0 != strcmp(LOG_MODULE_ALL, modName) && (0 != strcmp(modName, logFile.logModuleName))) 
				|| (LOG_LEVEL_ALL != level && level != logFile.logLevel) ){

				continue;
			}

			fprintf(fpSaveLog, "%s", line);

			free(line);
			line = NULL;
		}
		
		if(NULL != line){
			free(line);
			line = NULL;
		}

		fclose(fpLogSrc);
	}
	return 0;
}

int swLogSave(int level, char* modName, char *filePath,LOG_DOWNLOAD_HEAD *logDownloadHead)
{
    char timeStr[32];
    char hwIdStr[SYSTEM_HW_ID_LEN*2+1];
    char oemIdStr[SYSTEM_OEM_ID_LEN*2+1];
    char devIdStr[SYSTEM_DEV_ID_LEN*2+1];

    time_t t = time(NULL);
    struct tm * now = gmtime(&t);
    if (now) {
            snprintf(timeStr, sizeof(timeStr)-1,"%04d-%02d-%02d %02d:%02d:%02d GMT",
                            now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                            now->tm_hour, now->tm_min, now->tm_sec);
    }
    else {
            timeStr[0] = '\0';
    }

    if(NULL == filePath){
            LOG_PRINT("[%s:%d] parameter error\n", __FUNCTION__, __LINE__);
            return FAILURE;
    }
    LOG_PRINT("[%s:%d] level:%d, modName:%s\n", __FUNCTION__, __LINE__, level, modName);

    int fileIndex = 0;
    char srcFile[255] = {0};
    LOG_FILE_INDEX_ST logIndex_t;
    memset(&logIndex_t, 0, sizeof(logIndex_t));

    /*get index.bin*/
    logGetIndexInfo(&logIndex_t);

    /*open savefile*/
    FILE* fpSaveLog = fopen(filePath, "w+");
    if(NULL == fpSaveLog){
            LOG_PRINT("[%s:%d] fopen w error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
            return FAILURE;
    }

	if(logDownloadHead)
	{
        	logByte2Str(logDownloadHead->hwIdStr,sizeof(logDownloadHead->hwIdStr),hwIdStr,sizeof(hwIdStr));
        	logByte2Str(logDownloadHead->oemIdStr,sizeof(logDownloadHead->oemIdStr),oemIdStr,sizeof(oemIdStr));
		logByte2Str(logDownloadHead->hwIdStr,sizeof(logDownloadHead->hwIdStr),hwIdStr,sizeof(hwIdStr));
        	logByte2Str(logDownloadHead->oemIdStr,sizeof(logDownloadHead->oemIdStr),oemIdStr,sizeof(oemIdStr));
        	logByte2Str(logDownloadHead->devIdStr,sizeof(logDownloadHead->devIdStr),devIdStr,sizeof(devIdStr));

        	fprintf(fpSaveLog,
                	"#################################################################\r\n"
                	"#                   %s  %s System Log\r\n"
                	"# Time         = %s\r\n"
                	"# SW           = %s\r\n"
                	"# MAC Address = %s\r\n"
                	"# Hardware ID = %s\r\n"
                	"# OEM ID       = %s\r\n"
                	"# Device ID   = %s\r\n"
                	"#################################################################\r\n"
                	"#time                          processName:moduleName        level               msg\r\n"
                	" \r\n\r\n",
                	logDownloadHead->modelStr,logDownloadHead->hardwareVer,timeStr,logDownloadHead->softwareVer,
                	logDownloadHead->macStr,hwIdStr,oemIdStr,devIdStr);
	}


    /*get file name*/
    fileIndex = logIndex_t.fileOldestIndex;
    do{
            sprintf(srcFile, "%s/message_bak_%04d.log", g_log_path, fileIndex);
            swLogSaveDo(level, modName, srcFile, fpSaveLog);

            ++fileIndex;
            fileIndex = (fileIndex)%FILE_INDEX_MAX;
    }while(fileIndex <= logIndex_t.fileNewestIndex);

    swLogSaveDo(level, modName, g_log_message_path, fpSaveLog);

    if(LOG_CACHE_SWITCH){
            swLogSaveDo(level, modName, LOG_FILE_PATH_CACHE, fpSaveLog);
    }

    fclose(fpSaveLog);
    return SUCCESS;
}

int swLogDelete(int level, char *modelName)
{
	if(!modelName){
		LOG_PRINT("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	LOG_PRINT("[%s:%d] g_logCliCtx_t.openFlag:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.openFlag);
	LOG_PRINT("[%s:%d] g_logCliCtx_t.localUnixSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
	if(g_logCliCtx_t.localUnixSock <= 0){
		if(logUnixSockInit() < 0){
			LOG_PRINT("[%s:%d] logSockInit error\n", __FUNCTION__, __LINE__);
			return FAILURE;
		}
	}
	LOG_PRINT("[%s:%d] g_logCliCtx_t.localUnixSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
	if(!strcmp(LOG_MODULE_ALL, modelName) && LOG_LEVEL_ALL == level){
		LOG_PRINT("[%s:%d] delete all\n", __FUNCTION__, __LINE__);
		swLogClear();
		goto clean;
	}

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_DELETE_LOG;
	logMsg.msgLevel = level;
	if(strlen(modelName) <= LOG_MODEL_NAME_LEN){
		sprintf(logMsg.modelName, "%s", modelName);
	}else{
		LOG_PRINT("[%s:%d] modelName too long\n", __FUNCTION__, __LINE__);
		goto failed;
	}

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		goto failed;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		goto failed;
	}
	if(logMsgRecv.msgRes < 0){
		LOG_PRINT("[%s:%d] clear log error\n", __FUNCTION__, __LINE__);
		goto failed;
	}
	LOG_PRINT("[%s:%d] clear log ok\n", __FUNCTION__, __LINE__);

clean:
	LOG_PRINT("[%s:%d] g_logCliCtx_t.openFlag:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.openFlag);
	if(!g_logCliCtx_t.openFlag){
		logUnixSockUnInit();
	}
	LOG_PRINT("[%s:%d] g_logCliCtx_t.localUnixSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
	return 0;
failed:

	logUnixSockUnInit();
	LOG_PRINT("[%s:%d] g_logCliCtx_t.localUnixSock:%d\n", __FUNCTION__, __LINE__, g_logCliCtx_t.localUnixSock);
	return -1;
}

int swLogClear()
{
	/*clear bak file*/
	LOG_MSG_ST logMsg;
	LOG_MSG_ST logMsgRecv;

	memset(&logMsgRecv, 0, sizeof(logMsgRecv));
	memset(&logMsg, 0, sizeof(logMsg));
	logMsg.msgType = LOG_MSG_CLEAR_LOG;

	if(logSend(g_logCliCtx_t.localUnixSock, (char *)&logMsg, sizeof(logMsg)) < 0){
		LOG_PRINT("[%s:%d] logSend() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	if(logRecv(g_logCliCtx_t.localUnixSock, (char *)&logMsgRecv, sizeof(logMsgRecv))){
		LOG_PRINT("[%s:%d] logRecv() error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	if(logMsgRecv.msgRes < 0){
		LOG_PRINT("[%s:%d] clear log error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	LOG_PRINT("[%s:%d] clear log ok\n", __FUNCTION__, __LINE__);
		

	int fp = open(g_log_message_path, O_WRONLY|O_TRUNC);
	if(fp < 0){
		LOG_PRINT("[%s:%d] open error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return FAILURE;
	}
	close(fp);

	if(LOG_CACHE_SWITCH){
		/*clear the tmp file*/
		fp = open(LOG_FILE_PATH_CACHE, O_WRONLY|O_TRUNC);
		if(fp < 0){
			LOG_PRINT("[%s:%d] open error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return FAILURE;
		}
		close(fp);
	}

	return SUCCESS;
}

int swLogClose(void)
{
	if(g_flashEnable){
		closelogd();
		//swLogUnInit();
	}

	g_logCliCtx_t.openFlag = 0;

	if(fd_out){
		fclose(fd_out);
		fd_out = NULL;
	}
	return SUCCESS;
}

int swLogCloseWithoutPthread(void)
{
	closelogd();

	logUnixSockUnInit();
	g_logCliCtx_t.openFlag = 0;

	if(fd_out){
		fclose(fd_out);
		fd_out = NULL;
	}
	return SUCCESS;
}

int swLogFlush(void)
{
	if(0 == LOG_CACHE_SWITCH)
		return FAILURE;
	
	int number = 0;
	size_t size = 0;
	char *line = NULL;
	FILE* fpSrc = NULL;
	FILE* fpDst = NULL;

	fpSrc = fopen(LOG_FILE_PATH_CACHE, "r");
	if(NULL == fpSrc){
		LOG_PRINT("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));

		sleep(1);
		return FAILURE;
	}

	fpDst = fopen(g_log_message_path, "a");
	if(NULL == fpDst){
		LOG_PRINT("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));

		sleep(1);
		return FAILURE;
	}

	while(-1 != getline(&line, &size, fpSrc)){

		fprintf(fpDst, "%s", line);
		
		number++;
		free(line);
		line = NULL;
	}

	if(NULL != line){
		free(line);
		line = NULL;
	}

	fclose(fpSrc);
	fclose(fpDst);

	LOG_PRINT("[%s:%d] swLogFlush\n", __FUNCTION__, __LINE__);
	return SUCCESS;
}

int swLogCfgInit()
{
	struct uci_context *ctx; 
	struct uci_ptr ptr;
	char strTmp[128] = {0};

	memset(&g_logConfig, 0, sizeof(LOG_CONFIG_ST));

	ctx = uci_alloc_context();
	
	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.writeByNameEnable");
 	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_logConfig.writeByNameEnable);
	}else{
		g_logConfig.writeByNameEnable = 1;
	}
	LOG_PRINT("g_logConfig.writeByNameEnable:%d\n", g_logConfig.writeByNameEnable);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.webModelFilterEn");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_logConfig.webModelFilterEn);
	}else{
		g_logConfig.webModelFilterEn = 1;
	}
	LOG_PRINT("g_logConfig.webModelFilterEn:%d\n", g_logConfig.webModelFilterEn);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.base64Enable");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_logConfig.base64Enable);
	}else{
		g_logConfig.base64Enable = 1;
	}
	LOG_PRINT("g_logConfig.base64Enable:%d\n", g_logConfig.base64Enable);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.flushLevel");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_logConfig.flushLevel);
	}else{
		g_logConfig.flushLevel = 3;
	}
	LOG_PRINT("g_logConfig.flushLevel:%d\n", g_logConfig.flushLevel);

	/*for ipcamera*/
	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.serialInfo");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_serialInfo);
	}
	LOG_PRINT("g_serialInfo:%d\n", g_serialInfo);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.level");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_level);
	}
	LOG_PRINT("g_level:%d\n", g_level);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.remoteAddress");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%s", &g_remoteAddress);
	}
	LOG_PRINT("g_remoteAddress:%s\n", g_remoteAddress);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.moduleDebug");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_moduleDebug);
	}
	LOG_PRINT("g_moduleLevel:%d\n", g_moduleDebug);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.moduleLevel");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_moduleLevel);
	}
	LOG_PRINT("g_moduleLevel:%d\n", g_moduleLevel);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.moduleName");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%s", &g_moduleName);
	}
	LOG_PRINT("g_moduleName:%s\n", g_moduleName);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.logSaveEnable");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_flashEnable);
	}
	LOG_PRINT("g_flashEnable:%d\n", g_flashEnable);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.timeEnable");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_time_flag);
	}
	LOG_PRINT("g_time_flag:%d\n", g_time_flag);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.stdoutEnable");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%d", &g_stdoutEnable);
	}
	LOG_PRINT("g_stdoutEnable:%d\n", g_stdoutEnable);

	memset(strTmp, 0, sizeof(strTmp));
	sprintf(strTmp, "%s", "syslog.cfg.logPath");
	uci_lookup_ptr(ctx, &ptr, strTmp, true) ;
	if(ptr.o != NULL)
	{
		sscanf(ptr.o->v.string, "%s", &g_log_path);
	}else{
		sprintf(g_log_path, "%s", "/tmp/tplog");
	}
	sprintf(g_log_message_path, "%s/message.log", g_log_path);
	sprintf(g_log_bin_path, "%s/index.bin", g_log_path);
	LOG_PRINT("g_log_path:%s\n", g_log_path);
	
	uci_free_context(ctx); 
}

char *swLogCfgGetProductName()
{
	return g_logConfig.productName;
}

int swLogCfgGetWriteByNameEnable()
{
	return g_logConfig.writeByNameEnable;
}

int swLogCfgGetWebModelFilterEn()
{
	return g_logConfig.webModelFilterEn;
}

int swLogCfgGetBase64Enable()
{
	return g_logConfig.base64Enable;
}

int swLogCfgGetFlushLevel()
{
	return g_logConfig.flushLevel;
}

int swLogCfgGetSerialInfo()
{
	return g_serialInfo;
}

int swLogCfgSetSerialInfo(int value)
{
	g_serialInfo = value;
	return 0;
}

int swLogCfgGetLevel()
{
	return g_level;
}

char *swLogCfgGetRemoteAddress()
{
	return g_remoteAddress;
}

