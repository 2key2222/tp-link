/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: logFile.h
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*      use to manage log file
* information.
*  
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#ifndef _LOG_FILE_H_
#define _LOG_FILE_H_

#define FILE_INDEX_MAX 9000
#define FILE_INDEX_BUILT_TIME "2015-11-24_16:47:00"  //if LOG_FILE_INDEX_ST change than rebuilt index.bin auto when dev boot init
#define FILE_INDEX_PATH "/usr/log/index.bin"

typedef struct _LOG_FILE_INDEX{
	int					fileTotalSize;
	int					fileNumber;
	int					fileOldestIndex;
	int   				fileNewestIndex;
	char					fileBuiltTime[32];
}LOG_FILE_INDEX_ST;
 
void logFileInit();
int logFileClearAllLog(void);
#endif
