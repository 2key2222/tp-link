/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: logSession.c
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     	  It is the local socket server for log daemon which  handle  every connection
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
#include <stdint.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <time.h> 
#include <stdarg.h>

#include "logServer.h"
#include "logApi.h"
#include "logFile.h"
#include "logSession.h"

static int g_debug = 0;
static FILE *fd_out = NULL;
static LOG_SERVER_CTX_ST g_logCtx;
static unsigned char g_levelMask;
static uint64_t g_moduleMask;
static int g_logEnable;
static int g_netEnable;
static int g_tmpFileLineNum;
static int g_newFileLineNum;
static int g_oldFileLineNum;

static void logPrintf(char *fmt, ...)
{
	va_list ap;

	if ( !g_debug)
		return;

    if(fd_out == NULL){
		fd_out = fopen("/dev/console", "w");
		if(!fd_out){
			return -1;
		}
	}
	va_start(ap, fmt);
	vfprintf(fd_out, fmt, ap);
	va_end(ap);

	fflush(fd_out);
	return;
}
static void logSerLock(void)
{
    pthread_mutex_lock(&g_logCtx.logMutex);
}

static void logSerUnlock(void)
{
	pthread_mutex_unlock(&g_logCtx.logMutex);
}

void logSetTmpFileLineNum(int value)
{
	logSerLock();
	g_tmpFileLineNum = value;
	logSerUnlock();
}

void logAddTmpFileLineNum()
{
	logSerLock();
	g_tmpFileLineNum++ ;
	logSerUnlock();
}

int logGetTmpFileLineNum()
{
	int num = 0;
	logSerLock();
	num = g_tmpFileLineNum;
	logSerUnlock();

	return num;
}

void logSetNewFileLineNum(int value)
{
	logSerLock();
	g_newFileLineNum = value;
	logSerUnlock();
}

void logAddNewFileLineNum()
{
	logSerLock();
	g_newFileLineNum++ ;
	logSerUnlock();
}

int logGetNewFileLineNum()
{
	int num = 0;
	logSerLock();
	num = g_newFileLineNum;
	logSerUnlock();

	return num;
}

void logSetOldFileLineNum(int value)
{
	logSerLock();
	g_oldFileLineNum = value;
	logSerUnlock();
}

void logAddOldFileLineNum()
{
	logSerLock();
	g_oldFileLineNum++ ;
	logSerUnlock();
}

int logGetOldFileLineNum()
{
	int num = 0;
	logSerLock();
	num = g_oldFileLineNum;
	logSerUnlock();

	return num;
}

static void logMutexSerSetLevelMask(unsigned char levelMask)
{
	logSerLock();
	g_levelMask = levelMask;
	logSerUnlock();
}

static void logMutexSerSetModuleMask(uint64_t value)
{
	logSerLock();
	g_moduleMask = value;
	logSerUnlock();
}

int logMutexSerGetEnable(void)
{
	int logEnable = 0;
	
	logSerLock();
	logEnable = g_logEnable;
	logSerUnlock();

	return logEnable;
}

static void logMutexSerSetEnable(int value)
{
	logSerLock();
	g_logEnable = value;
	logSerUnlock();
}

int logMutexSerGetNetEnable()
{
	int logEnable = 0;
	
	logSerLock();
	logEnable = g_netEnable;
	logSerUnlock();

	return logEnable;
}

void logMutexSerSetNetEnable(int value)
{
	logSerLock();
	g_netEnable = value;
	logSerUnlock();
}

static int logMutexSerGetRuning(void)
{
	int run = 0;
	
	logSerLock();
	run = g_logCtx.runing;
	logSerUnlock();

	return run;
}

static void logMutexSerSetRuning(int value)
{
	logSerLock();
	g_logCtx.runing = value;
	logSerUnlock();
}

static int logMutexSerGetMaxFd(void)
{
	int maxFd = 0;
	
	logSerLock();
	maxFd = g_logCtx.maxFd;
	logSerUnlock();

	return maxFd;
}

uint64_t logGetModuleMask(char *moduleName, int *index, int *find)
{
	int index_ret = -1;
	uint64_t ret = 0;

	if(NULL == moduleName ||NULL == index ||NULL == find){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	index_ret = swLogGetModuleIndex(moduleName);
	if(index_ret != -1){
		*index = index_ret;
		*find = 1;
		 ret = 1LL << index_ret;
	}
	
	return ret;
}

static int logSend(int sock, char *pBuf, int len)
{
	int ret = 0;
	int totalSendLen = 0;
	int needSendLen = len;
	
	if(NULL == pBuf){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	do{
		ret = send(sock, pBuf + totalSendLen, needSendLen, 0);
		if(ret < 0){
			if(errno == EINTR){
				continue;
			}

			logPrintf("[%s:%d] send error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
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

	if(NULL == pBuf){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	do{		
		ret = recv(sock, pBuf + totalRecvLen, needRecvLen, 0);		
		if(ret <= 0){
			if(errno == EINTR){
				continue;
			}
			logPrintf("[%s:%d] recv error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return FAILURE;
		}

		totalRecvLen += ret;
		needRecvLen -= ret;

	}while(needRecvLen > 0);

	
	return SUCCESS;
}

static int logUnixSocketInit(void)
{
	int flag = 1;
	int flags = 0;
	struct sockaddr_un serAddr;

	logSerLock();
	g_logCtx.listenUnixFd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(g_logCtx.listenUnixFd< 0){
		logPrintf("[%s:%d] socket error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logSerUnlock();
		return FAILURE;
	}

	if(setsockopt(g_logCtx.listenUnixFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0){
		logPrintf("[%s:%d] setsockopt error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logSerUnlock();
		return FAILURE;
	}

	flags = fcntl(g_logCtx.listenUnixFd, F_GETFL, 0);
	if(fcntl(g_logCtx.listenUnixFd, F_SETFL, flags | O_NONBLOCK) < 0){
		logPrintf("[%s:%d] fcntl error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logSerUnlock();
		return FAILURE;
	}

	unlink(LOG_API_UNIX_DOMAIN);
	memset(&serAddr, 0, sizeof(serAddr));
	serAddr.sun_family = AF_UNIX;
	strcpy(serAddr.sun_path,LOG_API_UNIX_DOMAIN);

	if(bind(g_logCtx.listenUnixFd, (struct sockaddr *)&serAddr, sizeof(serAddr)) < 0){
		logPrintf("[%s:%d] bind error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logSerUnlock();
		return FAILURE;
	}

	if(listen(g_logCtx.listenUnixFd, 10) < 0){
		logPrintf("[%s:%d] bind error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		logSerUnlock();
		return FAILURE;
	}

	logSerUnlock();
	return SUCCESS;
}
	
static int logUnixSocketUnInit(void)
{
	logSerLock();
	if(0 != g_logCtx.listenUnixFd){
		close(g_logCtx.listenUnixFd);
		g_logCtx.listenUnixFd = 0;
	}
	 
	logSerUnlock();
	return SUCCESS;
}

static int logSocketUnInit(void)
{
	logSerLock();
	if(0 != g_logCtx.listenFd){
		close(g_logCtx.listenFd);
		g_logCtx.listenFd = 0;
	}
	 
	logSerUnlock();
	return SUCCESS;
}

static int logCmdSetLevel(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;
	
	memset(&logMsg, 0, sizeof(logMsg));

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	/*handleLevel*/
	syslogdSetLevel(pMsg->msgLevelMask);
	logMutexSerSetLevelMask(pMsg->msgLevelMask);
		
	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return  SUCCESS;
}

static int logCmdGetLevel(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));

	/*handleLevel*/
	logMsg.msgLevelMask =syslogdGetLevel();
		
	/*res*/
	logMsg.msgRes = 1;

	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return  SUCCESS;
}

static int logCmdSetModule(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleLevel*/
	syslogdSetModule(pMsg->msgModuleMask);
	logMutexSerSetModuleMask(pMsg->msgModuleMask);

	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

static int logCmdGetModule(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleModule*/
	logMsg.msgModuleMask = syslogdGetModule();

	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

static int logCmdSetEnable(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleModule*/
	logMutexSerSetEnable(pMsg->msgLogEnable);

	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

static int logCmdGetEnable(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleModule*/
	logMsg.msgLogEnable = logMutexSerGetEnable();

	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

static int logCmdGetNetwork(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleModule*/
	logMsg.msgLogNet = logMutexSerGetNetEnable();

	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}

	return SUCCESS;
}

static int logCmdOpenNet(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleLevel*/
	logMutexSerSetNetEnable(1);
	
	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
		
	return SUCCESS;
}

static int logCmdCloseNet(int sockcli, LOG_MSG_ST *pMsg)
{
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleLevel*/
	logMutexSerSetNetEnable(0);

	/*res*/
	logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}

static int logCmdDeleteLog(int sockcli, LOG_MSG_ST *pMsg)
{
	int ret = 0;
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));

	/*handleMsg*/
	ret = logFileDeleteLog(pMsg->msgLevel, pMsg->modelName);

	/*res*/
	if(ret < 0)
		logMsg.msgRes = ret;
	else
		logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}

static int logCmdClearLog(int sockcli, LOG_MSG_ST *pMsg)
{

    int ret = 0;
	LOG_MSG_ST logMsg;

	if(NULL == pMsg){
		logPrintf("[%s:%d] func parameter error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	memset(&logMsg, 0, sizeof(logMsg));
	
	/*handleMsg*/
	ret = logFileClearAllLog();
    
	/*res*/
	if(ret < 0)
		logMsg.msgRes = ret;
	else
		logMsg.msgRes = 1;
	if(logSend(sockcli, (char *)&logMsg, sizeof(logMsg)) < 0){
		logPrintf("[%s:%d] logSend error\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}

static int logCmdHandle(int sockcli, LOG_MSG_ST *pMsg)
{
	if(NULL == pMsg){
		logPrintf("[%s:%d] pMsg is null\n", __FUNCTION__, __LINE__);
		return FAILURE;
	}
	
	switch(pMsg->msgType)
	{
		case LOG_MSG_SET_LEVEL:
			if(logCmdSetLevel(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetLevel error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_GET_LEVEL:	
			if(logCmdGetLevel(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetLevel error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}

			break;

		case LOG_MSG_SET_MODULE:
			if(logCmdSetModule(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetModule error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_GET_MODULE:
			if(logCmdGetModule(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetModule error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_SET_ENABLE:
			if(logCmdSetEnable(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetModule error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_GET_ENABLE:
			if(logCmdGetEnable(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetModule error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_GET_NETWORK:
			if(logCmdGetNetwork(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdSetModule error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_OPEN_NETWORK:
			if(logCmdOpenNet(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdOpenNet error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_CLOSE_NETWORK:
			if(logCmdCloseNet(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdCloseNet error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_CLEAR_LOG:           
			if(logCmdClearLog(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdCloseNet error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		case LOG_MSG_DELETE_LOG:
			if(logCmdDeleteLog(sockcli, pMsg) < 0){
				logPrintf("[%s:%d] logCmdDeleteLog error\n", __FUNCTION__, __LINE__);
				return FAILURE;
			}
			break;

		default:
			logPrintf("[%s:%d] not know msgType:%d\n", __FUNCTION__, __LINE__, pMsg->msgType);
			break;
	}

	return SUCCESS;
}

static int logUnixAcceptHandle(void)
{
	int acceptFd = 0;
	socklen_t addlen;
	struct sockaddr_un cliAddr;

	addlen = sizeof(cliAddr);
	memset(&cliAddr, 0, sizeof(cliAddr));

	logSerLock();
	acceptFd = accept(g_logCtx.listenUnixFd, (struct sockaddr *)&cliAddr, &addlen);
	if(acceptFd < 0)
	{
		if(errno != EAGAIN && errno != EWOULDBLOCK){
			logPrintf("[%s:%d] accept error :%s\n", __FUNCTION__, __LINE__, strerror(errno));
		}
		logSerUnlock();
		return FAILURE;
	}

	FD_SET(acceptFd, &g_logCtx.unixSet);

	if(acceptFd > g_logCtx.maxFd){
		g_logCtx.maxFd = acceptFd;		
	}

	logSerUnlock();
	return SUCCESS;
}

static int logUnixSelectHandle(void)
{
	int i = 0;
	int ret = 0;
	int fd_ready;
	LOG_MSG_ST msg_t;

	logSerLock();
	memcpy(&g_logCtx.workingSet, &g_logCtx.unixSet, sizeof(g_logCtx.unixSet));
	g_logCtx.timeOut.tv_sec = 5;
	g_logCtx.timeOut.tv_usec = 0;
	logSerUnlock();

	ret = select(g_logCtx.maxFd+1, &g_logCtx.workingSet, NULL, NULL, &g_logCtx.timeOut);
	if(ret < 0){
		logPrintf("[%s:%d] select error :%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return FAILURE;
	}
	else if(0 == ret){
		return SUCCESS;
	}

	fd_ready = ret;

	for(i = 0; ((i <= logMutexSerGetMaxFd()) && (fd_ready > 0)); i++ )
	{
		
		logSerLock();
		if(0 == FD_ISSET(i, &g_logCtx.workingSet)){
			logSerUnlock();
			continue;
		}
		logSerUnlock();
		
		fd_ready--;

		/*new connection*/
		if(i == g_logCtx.listenUnixFd){
			logUnixAcceptHandle();
			continue;
		}

		/*old client's data*/
		if(logRecv(i, (char *)&msg_t, sizeof(msg_t)) < 0){

			close(i);
			logSerLock();
            
			FD_CLR(i, &g_logCtx.unixSet);
			if(i == g_logCtx.maxFd){
				while(FALSE == FD_ISSET(g_logCtx.maxFd, &g_logCtx.unixSet)){
					g_logCtx.maxFd--;
				}
			}
		    
			logSerUnlock();
			continue;
		}
		
		if(logCmdHandle(i, &msg_t) < 0){
			logPrintf("[%s:%d] logCmdHandle.error\n", __FUNCTION__, __LINE__);

			close(i);
			logSerLock();
			FD_CLR(i, &g_logCtx.unixSet);
			if(i == g_logCtx.maxFd){
				while(FALSE == FD_ISSET(g_logCtx.maxFd, &g_logCtx.unixSet)){
					g_logCtx.maxFd--;
				}
			}
			logSerUnlock();
			continue;
		}

	}
    
	return SUCCESS;
}

static int logUnixSelectInit(void)
{

	logSerLock();
	FD_ZERO(&g_logCtx.unixSet);
	g_logCtx.maxFd = g_logCtx.listenUnixFd;
	FD_SET(g_logCtx.listenUnixFd, &g_logCtx.unixSet);
	g_logCtx.timeOut.tv_sec = 5;
	g_logCtx.timeOut.tv_usec = 0;
	logSerUnlock();
	
	return SUCCESS;
}

static int logUnixSelectUnInit(void)
{
	int i;

	logSerLock();
	for(i = 0; i < g_logCtx.maxFd; i++)
	{
		if(TURE == FD_ISSET(i, &g_logCtx.unixSet)){
			close(i);
			if(i == g_logCtx.listenUnixFd){
				g_logCtx.listenUnixFd = 0;
			}
		}
	}
	logSerUnlock();
	
	return SUCCESS;
}

/*
 static void *logCheckFileSize(void)
{
	struct stat sBuf;
	printf("logCheckFileSize\n");

	while(logMutexSerGetRuning())
	{
		printf("logCheckFileSize\n");
		
		if(stat(LOG_FILE_PATH_NEW, &sBuf) < 0){
			perror("fopen error\n");
			//break;
		}
		printf("file size:%d\n", (int)sBuf.st_size);

		if(sBuf.st_size > LOG_FILE_SIZE){
			printf("clear log file\n");
			int fp = open(LOG_FILE_PATH_NEW, O_WRONLY|O_TRUNC);
			if(fp < 0){
				printf("[%s:%d] open error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
				//return FAILURE;
			}
			close(fp);
		}

		sleep(5);
	}

	return NULL;
}
*/

int logReadFileLineNum(char *path)
{
	int number = 0;
	size_t size = 0;
	char *line = NULL;
	FILE* fp = NULL;

	fp = fopen(path, "r");
	if(NULL == fp){
		logPrintf("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));

		sleep(1);
		return FAILURE;
	}

	while(-1 != getline(&line, &size, fp)){
		number++;
		free(line);
		line = NULL;
	}
	
	if(NULL != line){
		free(line);
		line = NULL;
	}
	
	fclose(fp);

	return number;
}

int logClearFile(char *filePath)
{
	int fp;
	
	fp= open(filePath, O_WRONLY|O_TRUNC);
	if(fp < 0){
		logPrintf("[%s:%d] open error:%s\n", __FUNCTION__, __LINE__, strerror(errno));

		sleep(1);
		return FAILURE;
	}
	
	close(fp);

	return SUCCESS;
}

static void *logUnixApiSerThread(void)
{
	if(logUnixSocketInit() < 0){
		logPrintf("[%s:%d] logSocketInit() error\n", __FUNCTION__, __LINE__);
		return NULL;
	}

	logUnixSelectInit();
	
	while(logMutexSerGetRuning())
	{
		if(logUnixSelectHandle() < 0){
			logPrintf("[%s:%d] logSelectHandle() error\n", __FUNCTION__, __LINE__);
			break;
		}
	}

	/*exit pthread*/
	logUnixSelectUnInit();
	logUnixSocketUnInit();
	logMutexSerSetRuning(0);

	return NULL;
}


int logApiSerInit(void)
{
	g_netEnable = 0;
	g_logEnable = swLogCfgGetSerialInfo();
	memset(&g_logCtx, 0, sizeof(g_logCtx));
	g_logCtx.runing = 1;
	pthread_mutex_init(&g_logCtx.logMutex, NULL);

	logFileInit();
    
	return SUCCESS;
}

int logApiSerUnInit(void)
{
	logMutexSerSetRuning(0);

	#if LOG_CACHE_SWITCH
	pthread_join(g_logCtx.logT2, NULL);
	#endif
	pthread_join(g_logCtx.logT, NULL);
	pthread_mutex_destroy(&g_logCtx.logMutex);

	return SUCCESS;
}

