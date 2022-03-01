/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: libLog.h
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     This is the log api  for syslogd
* information.
*  
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#ifndef _LOGAPI_H_
#define _LOGAPI_H_
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <fcntl.h>

/*need modify when transplant*/
#define LOG_CONSOLE_SWITCH 1
#define LOG_LEVEL_CTRL_SWITCH	 0
#define LOG_LEVEL_CTRL_VALUE	 7
#define LOG_LINE_MAX	   150
#define LOG_LINE_QUERY_MAX	   LOG_LINE_MAX*3 + 50
#define LOG_SINGLE_FILE_LINE_MAX	   500
#define LOG_FILE_SIZE_TOTAL  300*1024
#define LOG_FILE_SIZE_SINGLE 12*1024

#define LOG_SOCK_PATH "/dev/cameralog"
#define LOG_FILE_PATH_DIR 		"/etc/rwdir/log"
#define LOG_FILE_PATH 	    		"/etc/rwdir/log/message.log"
#define LOG_FILE_PATH_CACHE 	"/tmp/message_cache.log"
#define LOG_FILE_SAVE_ENCRYPT "/tmp/encrypt.log"

#define LOG_FILE_SAVE "/tmp/save.log"
#define LOG_ENCRYPTION_KEY "196FJAI59Olkfafj"

#define LOG_QUERY_STATUS_OK 1
#define LOG_QUERY_STATUS_BUF_NOT_ENOUGH 2
#define LOG_MODEL_NAME_LEN 128

extern char g_log_path[64];
extern char g_log_message_path[64];
extern char g_log_bin_path[64];

/*log cache switch*/
#define LOG_CACHE_SWITCH   1  /*1:use the cache,   0:not use the cache(message will direct be write to the flash)*/

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#ifndef TURE
#define TURE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#define LOG_SERVER_PORT 515
#define LOG_MSG_LEN		1024+512
#define LOG_MODULE_ALL "ALL"
#define LOG_LEVEL_ALL 8

#define LOG_API_UNIX_DOMAIN "/var/run/logUnixdomain"

#define COLOR_NONE              "\033[0000m"
#define COLOR_BLACK             "\033[0;30m"
#define COLOR_LIGHT_GRAY        "\033[0;37m"
#define COLOR_DARK_GRAY         "\033[1;30m"
#define COLOR_BLUE              "\033[0;34m"
#define COLOR_LIGHT_BLUE        "\033[1;34m"
#define COLOR_GREEN             "\033[0;32m"
#define COLOR_LIGHT_GREEN       "\033[1;32m"
#define COLOR_CYAN              "\033[0;36m"
#define COLOR_LIGHT_CYAN        "\033[1;36m"
#define COLOR_RED               "\033[0;31m"
#define COLOR_LIGHT_RED         "\033[1;31m"
#define COLOR_PURPLE            "\033[0;35m"
#define COLOR_LIGHT_PURPLE      "\033[1;35m"
#define COLOR_BROWN             "\033[0;33m"
#define COLOR_YELLOW            "\033[1;33m"
#define COLOR_WHITE             "\033[1;37m"

#define SYSTEM_CONFIG_LEN			64
#define SYLTEM_SOFTVER_LEN			64
#define SYSTEM_MAC_LEN				18
#define SYSTEM_DEV_ID_LEN			20
#define SYSTEM_HW_ID_LEN			16
#define SYSTEM_OEM_ID_LEN			16
#define SYSTEM_FW_ID_LEN			16

int swLogWriteError(int level, int moduleIndex, const char *func, int line, const char * format,...);
int swLogDebugAdvanced(int level, char *moduleName, const char *func, int line, const char * format,...);
int swLogHighLight(int level, int moduleIndex, const char *func, int line, const char * format,...);
int swLogWriteWithTime(int level, int moduleIndex, const char *func, int line, const char * format,...);

#define DEBUG(level, module, arg...)  swLogDebugAdvanced(level, module, __FUNCTION__, __LINE__, ##arg)
#define SYSLOG(level, module, arg...)  swLogWriteWithoutModelfliter(level, module, __FUNCTION__, __LINE__, ##arg)
#ifdef LOG
#undef LOG
#endif
#define LOG(level, module, arg...)  swLogWrite(level, module, __FUNCTION__, __LINE__, ##arg)
#define ERR(level, module, arg...)  swLogWriteError(level, module, __FUNCTION__, __LINE__, ##arg)
#define LOG_HIGHTLIGHT(level, module, arg...)  swLogHighLight(level, module, __FUNCTION__, __LINE__, ##arg)
#define LOG_TIME(level, module, arg...)  swLogWriteWithTime(level, module, __FUNCTION__, __LINE__, ##arg)

#define TPLOG(level, arg...)  swLogWrite(level, 0, __FUNCTION__, __LINE__, ##arg)
#define TPERR(level, arg...)  swLogWriteError(level, 0, __FUNCTION__, __LINE__, ##arg)
#define TPLOG_HIGHTLIGHT(level, arg...)  swLogHighLight(level, 0, __FUNCTION__, __LINE__, ##arg)
#define TPLOG_TIME(level, arg...)  swLogWriteWithTime(level, 0, __FUNCTION__, __LINE__, ##arg)

#ifndef STRINGIZE
#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)
#endif

typedef enum{
	LOG_MSG_SET_LEVEL = 1,
	LOG_MSG_GET_LEVEL ,
	LOG_MSG_SET_MODULE ,
	LOG_MSG_GET_MODULE ,
	LOG_MSG_SET_ENABLE ,
	LOG_MSG_GET_ENABLE ,
	LOG_MSG_GET_NETWORK,
	LOG_MSG_OPEN_NETWORK,
	LOG_MSG_CLOSE_NETWORK,
	LOG_MSG_CLEAR_LOG,
	LOG_MSG_DELETE_LOG,
}LOG_MSG_TYPE_T;

typedef enum{
	DEBUG_LEVEL1 = 1, //建议慢速循环打印使用，比如5s以上 或者 过程性的调试打印
	DEBUG_LEVEL2,     //快速循环的打印，建议1s左右使用		    	       
	DEBUG_LEVEL3,			      
	DEBUG_LEVEL4,			      
	DEBUG_LEVEL5,		      
	DEBUG_LEVEL6,		      
	DEBUG_LEVEL7,			    
	DEBUG_LEVEL8		           			
}LOG_DEBUG_T;

typedef enum{
	MYLOG_EMERG, // system is unusable 
	MYLOG_ALERT,		    	       // action must be taken immediately 
	MYLOG_CRIT,			       // critical conditions 
	MYLOG_ERR,			       // error conditions 
	MYLOG_WARNING,		      //warning conditions 
	MYLOG_NOTICE	,		      // normal but significant condition 
	MYLOG_INFO,			     //informational 
	MYLOG_DEBUG		           // debug-level messages 			
}LOG_LEVEL_T;

typedef enum{
	LEVEL_EMERG	= 1 << 0,
	LEVEL_ALERT	= 1 << 1,
	LEVEL_CRIT	= 1 << 2,
	LEVEL_ERR	= 1 << 3,
	LEVEL_WARNING	= 1 << 4,
	LEVEL_NOTICE	= 1 << 5,
	LEVEL_INFO	= 1 << 6,
	LEVEL_DEBUG	= 1 << 7 
}LOG_LEVEL_MASK_T;

/*need modify when transplant*/
typedef enum{
	INDEX_NONE							= 0,
	INDEX_AUDIO_DETECTION				,
	INDEX_ALARM_DELIVERY					,
	INDEX_AUTO_UPGRADE					,
	INDEX_BONJOUR							,
	INDEX_BUTTON							,
	INDEX_CLOUD							,
	INDEX_DATE_TIME						,
	INDEX_DAY_NIGHT						,
	INDEX_DEV_FIND							,
	INDEX_DEVICE							,
	INDEX_IPCSWITCH						,
	INDEX_LIBRPM							,
	INDEX_LOCATION						,
	INDEX_MDNEW							,
	INDEX_MSGPUSH							,
	INDEX_NETCONFIG						,
	INDEX_NETSWITCH						,
	INDEX_OEM								,
	INDEX_ONVIF							,
	INDEX_RPC_MOD							,
	INDEX_RPMS								,
	INDEX_SD								,
	INDEX_SESSION							,
	INDEX_SYSTEM							,
	INDEX_TDDP								,
	INDEX_UPNP								,
	INDEX_USERMANAGE						,
	INDEX_VIDEOCONTROL					,
	INDEX_WIRELESS						,
	INDEX_WORKMODE						,
	INDEX_ADNEW							,
	INDEX_AUTOUPGRADENOTICE				,
	INDEX_APPS_CLOUD						,
	INDEX_DDNS								,
	INDEX_FILECUT							,
	INDEX_FTPALARMNEW					,
	INDEX_LIBCLOUD						,
	INDEX_SDRECORD						,
	INDEX_SPEAKER							,
	INDEX_STREAM							,
	INDEX_SMTPALARMNEW					,
	INDEX_VOD								,
	INDEX_SERVER							,
	INDEX_PTZ								,
	INDEX_FTP								,
	INDEX_CLIENT_MGMT 					,
	INDEX_REGION						,
	INDEX_MOTION						,
	INDEX_IMAGECTRL						,
	INDEX_DETECTION						,
	INDEX_NASRECORD						,
	INDEX_SCHEDULE						,
	INDEX_SHM						    ,
	INDEX_MP4						    ,
	INDEX_LINKIED						,
	INDEX_RELAYD						,
	INDEX_STORAGE						,
	INDEX_IOTCLIENT						,
	INDEX_CONFIG_SERVICE				,
	INDEX_SNAPSHOT						,
	INDEX_TIMED							,
	INDEX_HEALTHINFO_SERVICE     		,
	INDEX_SIREN							,
	INDEX_LED							,
	INDEX_MODULE_END
}LOG_MODULE_INDEX_T;

extern char g_moduleString[][64];
typedef struct _LOG_MSG{
	LOG_MSG_TYPE_T		msgType;
	unsigned char 		msgLevelMask;
	uint64_t				msgModuleMask;
	int 					msgLevel;
	int					msgLogEnable;
	int					msgLogNet;
	int 					msgRes;
	int 					msgDataLen;/* reserve */
	char				modelName[LOG_MODEL_NAME_LEN];
	void* 				msgData[0];/* reserve */
}LOG_MSG_ST;

typedef struct _LOG_CLIENT_CTX{
	int					openFlag;
	int					runing;
#ifdef USE_PHREAD	
	pthread_t 			logT;
#endif
	int 					logEnable;
	int 					localSock;
	int 					localUnixSock;
	uint64_t				logModuleMask;
	struct sockaddr_in 	serAddr;
	struct sockaddr_un	serUnixAddr;
#ifdef USE_PHREAD
	pthread_mutex_t 		logMutex;
#endif
}LOG_CLIENT_CTX_ST;

typedef struct _LOG_FILE{
	int 			logLevel;
	time_t 		logTimeInt;
	char 		logTimeStr[1024];
	char 		logLevelStr[1024];
	char			logProcessName[1024];
	char			logModuleName[1024];
	char 		logMsg[LOG_MSG_LEN];
}LOG_FILE_ST;

typedef struct _LOG_DOWNLOAD_HEAD{
	char					softwareVer[SYLTEM_SOFTVER_LEN];
	char					hardwareVer[SYSTEM_CONFIG_LEN];
	char 				modelStr[SYSTEM_CONFIG_LEN];
	unsigned char			devIdStr[SYSTEM_DEV_ID_LEN];
	unsigned char			hwIdStr[SYSTEM_HW_ID_LEN];
	unsigned char			oemIdStr[SYSTEM_OEM_ID_LEN];
	unsigned char			macStr[SYSTEM_MAC_LEN];
}LOG_DOWNLOAD_HEAD;

typedef struct _LOG_CONFIG_H{
	char productName[128];
	int writeByNameEnable;
	int webModelFilterEn;
	int base64Enable;
	int flushLevel;
	int moduleLevel;
	char moduleName[32];
}LOG_CONFIG_ST;

/***********************************for log client process******************************************/

/*****************************************************************************
* Function:   swLogOpen
* Author:     dongzhenhua
* Param[in]:  processName       - the name of process which use log module. NULL not allowed.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     init the syslod() socket , ctrl socket, and getLevelThread
*****************************************************************************/
int swLogOpen(char *processName);
int swLogOpenWithoutPthread(char *processName);

/*****************************************************************************
* Function:   swLogWrite
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  moduleIndex    - the index of the moduleString  arrary ,  value: [0~64] ,   refer to g_moduleString[][64] in logApi.c
* Param[in]:  func       - the name of func which call LOG(). NULL not allowed.
* Param[in]:  line       - the line of files which call LOG().
* Param[in]:  format       - the format of log message. NULL not allowed.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     to printf() and syslog() ,
*****************************************************************************/
int swLogWrite(int level, int moduleIndex, const char *func, int line, const char * format,...);


/*****************************************************************************
* Function:   swLogWriteWithoutModelfliter
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  moduleName    - the name of module which log message
* Param[in]:  func       - the name of func which call LOG(). NULL not allowed.
* Param[in]:  line       - the line of files which call LOG().
* Param[in]:  format       - the format of log message. NULL not allowed.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     to printf() and syslog() ,
*****************************************************************************/
int swLogWriteWithoutModelfliter(int level, char *moduleName, const char *func, int line, const char * format,...);


/*****************************************************************************
* Function:   swLogConsole
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  moduleIndex    - the index of the moduleString  arrary ,  value: [0~64] ,   refer to g_moduleString[][64] in logApi.c
* Param[in]:  func       - the name of func which call LOG(). NULL not allowed.
* Param[in]:  line       - the line of files which call LOG().
* Param[in]:  format       - the format of log message. NULL not allowed.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     to printf() and syslog() ,and add control flag logEnable, which determine whether syslog() or not., use or DBG()
*****************************************************************************/
int swLogConsole(int level, int moduleIndex, const char *func, int line, const char * format,...);


/*****************************************************************************
* Function:   swLogClose
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     to close the log socket
*****************************************************************************/
int swLogClose(void);
int swLogCloseWithoutPthread(void);


/*****************************************************************************
* Function:   swLogQuery
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  modName    - the name of the module, refer to g_moduleString[][64] in logApi.c
* Param[in]:  number       - the line numbers which need to get .
* Param[out]:  outbuff       - the buf which use to storage log message, NULL not allowed.
* Param[in]:  bufSize       - the size of the outbuff.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     get the log message form files ,with the filtration
*****************************************************************************/
int swLogQuery(int level, char* modName, int number, char* outbuff, int bufSize);

/*****************************************************************************
* Function:   swLogQueryByNumber
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  modName    - the name of the module, refer to g_moduleString[][64] in logApi.c
* Param[in]:  number       - the line numbers which need to get .
* Param[out]:  outbuff       - the buf which use to storage log message, NULL not allowed.
* Param[in]:  bufSize       - the size of the outbuff.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     get the log message form files ,with the filtration
*****************************************************************************/
int swLogQueryByNumber(int level, char* modName, int number, char* outbuff, int bufSize);

/*****************************************************************************
* Function:   swLogQueryByNumJson
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  modName    - the name of the module, refer to g_moduleString[][64] in logApi.c
* Param[in]:  number       - the line numbers which need to get .
* Param[out]:  outbuff       - the buf which use to storage log message, NULL not allowed.
* Param[in]:  bufSize       - the size of the outbuff.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     get the log message form files ,with the filtration and full json
*****************************************************************************/
int swLogQueryByNumJson(int level, char* modName, int number, char* outbuff, int bufSize);

/*****************************************************************************
* Function:   swLogQueryByTime
* Author:     dongzhenhua
* Param[in]:  startTime       - the startTime of log message
* Param[in]:  endTime       - the endTime of log message
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  modName    - the name of the module, refer to g_moduleString[][64] in logApi.c
* Param[in]:  number       - the line numbers which need to get .
* Param[out]:  outbuff       - the buf which use to storage log message, NULL not allowed.
* Param[in]:  bufSize       - the size of the outbuff.
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     get the log message form files ,with the filtration, add time filtration
*****************************************************************************/
int swLogQueryByTime(char* startTime,char* endTime, int level, char* modName, int number, char* outbuff, int bufSize);

/*****************************************************************************
* Function:   swLogSave
* Author:     dongzhenhua
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  modName    - the name of the module, refer to g_moduleString[][64] in logApi.c
* Param[in]:  filePath       - the file path which use to export log message, such as "/tmp/message.log"
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     export the log message , with the filtration
*****************************************************************************/
int swLogSave(int level, char* modName, char *filePath,LOG_DOWNLOAD_HEAD *logDownloadHead);


/*****************************************************************************
* Function:   swLogSave
* Author:     dongzhenhua
* Param[in]:  startTime       - the startTime of log message
* Param[in]:  endTime       - the endTime of log message
* Param[in]:  level       - the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Param[in]:  modName    - the name of the module, refer to g_moduleString[][64] in logApi.c
* Param[in]:  filePath       - the file path which use to export log message, such as "/tmp/message.log"
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     export the log message , with the filtration
*****************************************************************************/
int swLogSaveByTime(char* startTime, char* endTime, int level, char* modName, char *filePath);


/*****************************************************************************
* Function:   swLogClear
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     clear the log file
*****************************************************************************/
int swLogClear();

/*****************************************************************************
* Function:   swLogDelete
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
*             Function call may fail in situations below:
*             1) Required parameter NULL.
* Drecription:
*     clear the log file
*****************************************************************************/
int swLogDelete(int level, char *modelName);

/***********************************for log ctrl    process******************************************/

/*****************************************************************************
* Function:   swLogInit
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     init the local socket which use to connect daemon
*****************************************************************************/
int swLogInit(void);


/*****************************************************************************
* Function:   swLogUnInit
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     uninit the local socket which use to connect daemon
*****************************************************************************/
int swLogUnInit(void);


/*****************************************************************************
* Function:   swLogSetLevel
* Author:     dongzhenhua
* Param[in]:  logLevel			- the log message level value [0~7]:MYLOG_EMERG,MYLOG_ALERT,MYLOG_CRIT, MYLOG_ERR
												    MYLOG_WARNING, MYLOG_NOTICE, MYLOG_INFO,MYLOG_DEBUG
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     to set the level mask of log daemon
*****************************************************************************/
int swLogSetLevel(LOG_LEVEL_T logLevel);

/*****************************************************************************
* Function:   swLogGetLevel
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     - the level mask of log daemon 
* Drecription:
*     to get the level mask of log daemon
*****************************************************************************/
unsigned char  swLogGetLevel(void);


/*****************************************************************************
* Function:   swLogSetModule
* Author:     dongzhenhua
* Param[in]:  mask			- the module mask of log daemon, refer to LOG_MODULE_MASK_T
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     to set the module mask of log daemon
*****************************************************************************/
int swLogSetModule(uint64_t mask);


/*****************************************************************************
* Function:   swLogGetModule
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     - the module mask of log daemon 
* Drecription:
*     to get the module mask of log daemon
*****************************************************************************/
uint64_t  swLogGetModule(void);


/*****************************************************************************
* Function:   swLogSetEnableFlag
* Author:     dongzhenhua
* Param[in]:  enable			- [0~1] ,use in DBG(), to determine  whether syslog() or not
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     use in DBG(), to determine  whether syslog() or not
*****************************************************************************/
int  swLogSetEnableFlag(int enable);


/*****************************************************************************
* Function:   swLogGetEnableFlag
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     - the value of enableFlag, use in DBG(), to determine  whether syslog() or not
* Drecription:
*     to get the enableFlag, use in DBG(), to determine  whether syslog() or not
*****************************************************************************/
int  swLogGetEnableFlag(void);

/*****************************************************************************
* Function:   swLogGetNetFlag
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     - the value of netflag
* Drecription:
*     to get the netFlag
*****************************************************************************/
int  swLogGetNetFlag(void);

/*****************************************************************************
* Function:   swLogOpenNetWork
* Author:     dongzhenhua
* Param[in]:  enable			- [0~1] ,to determine  whether send the log message to network
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     open the switch, than log message can be send to network
*****************************************************************************/
int swLogOpenNetWork(void);

/*****************************************************************************
* Function:   swLogCloseNetWork
* Author:     dongzhenhua
* Param[in]: N/A
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     close the switch, than log message can not be send to network
*****************************************************************************/
int swLogCloseNetWork(void);


/*****************************************************************************
* Function:   swLogGetModuleIndex
* Author:     dongzhenhua
* Param[in]: moduleName 			-the module's name
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     get the module index by moduleName
*****************************************************************************/
int swLogGetModuleIndex(char *moduleName);

/*****************************************************************************
* Function:   swLogGetModuleName
* Author:     dongzhenhua
* Param[in]: index 			-the module's index
* Return:     moduleName if succeed. NULL if failed.
* Drecription:
*     get the module name by index
*****************************************************************************/
char* swLogGetModuleName(int index);

/*****************************************************************************
* Function:   swLogFlush
* Author:     dongzhenhua
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     flush log
*****************************************************************************/
int swLogFlush(void);


/*****************************************************************************
* Function:   LogLevelToInt
* Author:     dongzhenhua
* Return:     level value if succeed. -1 if failed.
* Drecription:
*     get the level value with the string level
*****************************************************************************/
int LogLevelToInt(char *level);

/*****************************************************************************
* Function:   swLogGetLevelName
* Author:     dongzhenhua
* Param[in]: index 			-the module's index
* Return:     levelName if succeed. NULL if failed.
* Drecription:
*     get the level name by index
*****************************************************************************/
char* swLogGetLevelName(int index);

/*****************************************************************************
* Function:   swLogCfgInit
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     init log config
*****************************************************************************/
int swLogCfgInit();

/*****************************************************************************
* Function:   swLogCfgGetProductName
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     productName
* Drecription:
*     get product name in config
*****************************************************************************/
char *swLogCfgGetProductName();

/*****************************************************************************
* Function:   swLogCfgGetWriteByNameEnable
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get ModuleMaskEnabl in config
*****************************************************************************/
int swLogCfgGetWriteByNameEnable();

/*****************************************************************************
* Function:   swLogCfgGetWebModelFilterEn
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get WebModelFilterEn in config
*****************************************************************************/
int swLogCfgGetWebModelFilterEn();

/*****************************************************************************
* Function:   swLogCfgGetBase64Enable
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get Base64Enable in config
*****************************************************************************/
int swLogCfgGetBase64Enable();

/*****************************************************************************
* Function:   swLogCfgGetFlushLevel
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get flushLevel in config
*****************************************************************************/
int swLogCfgGetFlushLevel();

/*****************************************************************************
* Function:   swLogCfgGetSerialInfo
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get SerialInfo in config / it is to enable printf info in console
*****************************************************************************/
int swLogCfgGetSerialInfo();

/*****************************************************************************
* Function:   swLogCfgSetSerialInfo
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     set SerialInfo in config / it is to enable printf info in console
*****************************************************************************/
int swLogCfgSetSerialInfo(int value);

/*****************************************************************************
* Function:   swLogCfgGetLevel
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get level in config:it is to control the log level
*****************************************************************************/
int swLogCfgGetLevel();

/*****************************************************************************
* Function:   swLogCfgGetRemoteAddress
* Author:     dongzhenhua
* Param[in]: N 			
* Return:     1/0
* Drecription:
*     get RemoteAddress in config:it is to define where the log info to send
*****************************************************************************/
char *swLogCfgGetRemoteAddress();

void swLogShowData(char *pData, int len);
#endif
