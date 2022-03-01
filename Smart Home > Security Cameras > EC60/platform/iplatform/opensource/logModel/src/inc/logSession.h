/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: syslogdApiser.h
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     
* information.
*  
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#ifndef _LOGSESSION_H_
#define _LOGSESSION_H_

#include <stdint.h>
#define SUCCESS 0
#define FAILURE -1
#define TURE 1
#define FALSE 0
#define LOG_API_PORT 515
#define LOG_API_UNIX_DOMAIN "/var/run/logUnixdomain"

typedef struct _LOG_SERVER_CTX{
	int runing ;
	int listenFd;
	int listenUnixFd;
	int maxFd;
	struct timeval timeOut;
	fd_set masterSet;
	fd_set unixSet;
	fd_set workingSet;
	pthread_t logT;
	pthread_t logT2;
	pthread_t logUnix;
	pthread_mutex_t logMutex;
}LOG_SERVER_CTX_ST;


/*****************************************************************************
* Function:   logApiSerInit
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     init the socket server thread
*****************************************************************************/
int logApiSerInit(void);

/*****************************************************************************
* Function:   logApiSerInit
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     0 if succeed. -1 if failed.
* Drecription:
*     uninit the socket server thread
*****************************************************************************/
int logApiSerUnInit(void);


/*****************************************************************************
* Function:   logApiSerInit
* Author:     dongzhenhua
* Param[in]:  moduleName		-the name string of module
* Param[out]:  index			-the index of the moduleName which in g_moduleMap[], NULL is not allowed
* Param[out]:  find				-the falg which whether find the moduleName in g_moduleMap[] or not£¬ NULL is not allowed
* Return:     the specific module mask ,with the name equal  Param[in]:  moduleName
* Drecription:
*     get the specific module masks, with the module name  in param[0] moduleName
*****************************************************************************/
uint64_t logGetModuleMask(char *moduleName, int *index, int *find);

/*****************************************************************************
* Function:   logApiSerInit
* Author:     dongzhenhua
* Param[in]:  N/A
* Return:     the enable flag of network
* Drecription:
*     get the enable flag of network
*****************************************************************************/
int logMutexSerGetNetEnable(void);

/*****************************************************************************
* Function:   logSetTmpFileLineNum
* Author:     dongzhenhua
* Param[in]: value				-the value of line num to set
* Return:     N/A
* Drecription:
*     set the value of lineNum
*****************************************************************************/
void logSetTmpFileLineNum(int value);

/*****************************************************************************
* Function:   logAddTmpFileLineNum
* Author:     dongzhenhua
* Param[in]: N/A
* Return:     N/A
* Drecription:
*     increase the value of lineNum with one unit
*****************************************************************************/
void logAddTmpFileLineNum();

/*****************************************************************************
* Function:   logGetTmpFileLineNum
* Author:     dongzhenhua
* Param[in]: N/A				
* Return:     the value of line num 
* Drecription:
*     get the value of lineNum
*****************************************************************************/
int logGetTmpFileLineNum();

/*****************************************************************************
* Function:   logSetNewFileLineNum
* Author:     dongzhenhua
* Param[in]: value				-the value of line num to set
* Return:     N/A
* Drecription:
*     set the value of lineNum
*****************************************************************************/
void logSetNewFileLineNum(int value);

/*****************************************************************************
* Function:   logAddNewFileLineNum
* Author:     dongzhenhua
* Param[in]: N/A
* Return:     N/A
* Drecription:
*     increase the value of lineNum with one unit
*****************************************************************************/
void logAddNewFileLineNum();

/*****************************************************************************
* Function:   logGetNewFileLineNum
* Author:     dongzhenhua
* Param[in]: N/A				
* Return:     the value of line num 
* Drecription:
*     get the value of lineNum
*****************************************************************************/
int logGetNewFileLineNum();

/*****************************************************************************
* Function:   logSetOldFileLineNum
* Author:     dongzhenhua
* Param[in]: value				-the value of line num to set
* Return:     N/A
* Drecription:
*     set the value of lineNum
*****************************************************************************/
void logSetOldFileLineNum(int value);

/*****************************************************************************
* Function:   logAddOldFileLineNum
* Author:     dongzhenhua
* Param[in]: N/A
* Return:     N/A
* Drecription:
*     increase the value of lineNum with one unit
*****************************************************************************/
void logAddOldFileLineNum();

/*****************************************************************************
* Function:   logGetOldFileLineNum
* Author:     dongzhenhua
* Param[in]: N/A				
* Return:     the value of line num 
* Drecription:
*     get the value of lineNum
*****************************************************************************/
int logGetOldFileLineNum();

/*****************************************************************************
* Function:   logReadFileLineNum
* Author:     dongzhenhua
* Param[in]: path						-the path of the file			
* Return:     0 if succeed. -1 if failed. 
* Drecription:
*     get the lineNum of file
*****************************************************************************/
int logReadFileLineNum(char *path);

/*****************************************************************************
* Function:   logCopyFile
* Author:     dongzhenhua
* Param[in]: srcFilePath						-the srcpath of the file	
* Param[in]: dstFilePath					-the dstpath of the file	
* Return:     0 if succeed. -1 if failed. 
* Drecription:
*     copy file form srcFilePath to dstFilePath
*****************************************************************************/
int logCopyFile(char *srcFilePath, char *dstFilePath);

/*****************************************************************************
* Function:   logAddFile
* Author:     dongzhenhua
* Param[in]: srcFilePath						-the srcpath of the file	
* Param[in]: dstFilePath					-the dstpath of the file	
* Return:     num of add line if succeed. -1 if failed. 
* Drecription:
*     superadd file form srcFilePath to dstFilePath
*****************************************************************************/
int logAddFile(char *srcFilePath, char *dstFilePath);

/*****************************************************************************
* Function:   logCopyCatheFile
* Author:     dongzhenhua
* Param[in]: cacheFilePath					-the cachePath of the file	
* Param[in]: newFilePath					-the newPath of the file	
* Param[in]: oldFilePath					-the oldPath of the file	
* Return:     0 if succeed. -1 if failed. 
* Drecription:
*     copy message form cachePath and newpath to oldPath
*****************************************************************************/
int logCopyCatheFile(char *cacheFilePath, char *newFilePath,char *oldFilePath);

/*****************************************************************************
* Function:   logClearFile
* Author:     dongzhenhua
* Param[in]: filePath						-the path of the file	
* Return:     0 if succeed. -1 if failed. 
* Drecription:
*     clear the file content
*****************************************************************************/
int logClearFile(char *filePath);


/*****************************************************************************
* Function:   logMutexSerGetEnable
* Author:     dongzhenhua
* Param[in]: N/A					
* Return:     the file enable flag of DBG
* Drecription:
*     get the enable flag of DBG's file function
*****************************************************************************/
int logMutexSerGetEnable(void);

#endif
