/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: logFile.c
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     	  use to manage log file
* information.
*  
* History:  
*     2015-12-17: dongzhenhua     File created.   
*****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

#include "logServer.h"
#include "logApi.h"
#include "logSession.h"
#include "logFile.h"

pthread_t g_log_t;
int g_running = 1;
LOG_FILE_INDEX_ST g_logIndex_t;

static int g_fileDebug = 0;
static int g_useIndex = 0;
static int g_dirty = 0;
static int g_flushFlag = 0;
static time_t last_flush_time = 0;
static int logIndexFileFlush(char *filePath, void *data, int dataSize);
static int logFileCheckExist(char *dirPath);

typedef struct _FILE_NODE{
	char fileName[254];
}FILE_NODE_ST;

static void logFilePrintf(char *fmt, ...)
{
	va_list ap;

	if ( !g_fileDebug)
		return;

	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);

	fflush(stdout);
	return;
}

static int logCmpCallback(const void *p1, const void *p2)
{
  return strcmp( ((FILE_NODE_ST *)p1)->fileName , ((FILE_NODE_ST *)p2)->fileName);
}

static int isLogBakFile(char *fileName)
{
	if(NULL == fileName){
		logFilePrintf("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	if(strstr(fileName, "message_bak_") != NULL){
		return 1;
	}

	return 0;
}

static int logGetFileSize(char *filePath)
{
	if(NULL == filePath){
		logFilePrintf("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	struct stat fileStat;

	if(stat(filePath, &fileStat) < 0 ){
		logFilePrintf("[%s:%d] stat %s error:%s\n", __FUNCTION__, __LINE__, filePath,strerror(errno));
		return -1;
	}

	return fileStat.st_size;
}

/*single file size*/
static int logFileCheckBySize(char *filePath)
{
	if(NULL == filePath){
		logFilePrintf("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	int ret = 0;

	ret = logGetFileSize(filePath);
	if(ret < 0){
		logFilePrintf("[%s:%d]logGetFileSize error \n", __FUNCTION__, __LINE__);
		return -1;
	}
	logFilePrintf("%s  file size:%d , file size :%dk, totalsize:%d, 	totalsize2:%dk\n"
		,filePath, ret, ret/1024, g_logIndex_t.fileTotalSize, g_logIndex_t.fileTotalSize/1024);
	
	if(ret >= LOG_FILE_SIZE_SINGLE){
		logFilePrintf("[%s:%d]single file %d large than %d\n", __FUNCTION__, __LINE__,ret ,LOG_FILE_SIZE_SINGLE);
		return  1;
	}

	return 0;
}

/*total file size*/
static int logDirCheckBySize(int size)
{
	int ret = 0;
	char oldPath[255] = {0};

	while(g_logIndex_t.fileTotalSize >=  LOG_FILE_SIZE_TOTAL){
		sprintf(oldPath, "%s/message_bak_%04d.log", g_log_path, g_logIndex_t.fileOldestIndex);
		if(access(oldPath, F_OK) == 0){
			ret = logGetFileSize(oldPath);
			if(ret < 0){
				logFilePrintf("[%s:%d]logGetFileSize error \n", __FUNCTION__, __LINE__);
				return -1;
			}
			g_logIndex_t.fileTotalSize -= ret;
			g_logIndex_t.fileNumber--;
			remove(oldPath);
		}
		g_logIndex_t.fileOldestIndex = (++g_logIndex_t.fileOldestIndex) % FILE_INDEX_MAX;

		if(g_logIndex_t.fileOldestIndex == g_logIndex_t.fileNewestIndex){
			logFilePrintf("[%s:%d]g_logIndex_t.fileOldestIndex == g_logIndex_t.fileNewestIndex:%d \n"
				, __FUNCTION__, __LINE__, g_logIndex_t.fileNewestIndex);
			break;
		}
	
		usleep(100);
	}

	g_dirty= 1;
	return SUCCESS;
}

int logFileCopyFile(char *srcFilePath, char *dstFilePath)
{
	int number = 0;
	size_t size = 0;
	char *line = NULL;
	FILE* fpSrc = NULL;
	FILE* fpDst = NULL;

	fpSrc = fopen(srcFilePath, "r");
	if(NULL == fpSrc){
		logFilePrintf("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));

		sleep(1);
		return FAILURE;
	}

	fpDst = fopen(dstFilePath, "w");
	if(NULL == fpDst){
		logFilePrintf("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));

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

	return number;
}


static int logFileExchange()
{
	logFilePrintf("[%s:%d]logFileExchange--------\n", __FUNCTION__, __LINE__);
	int ret = 0; 
	char newPath[255] = {0};
	char oldPath[255] = {0};

	if(g_logIndex_t.fileNewestIndex == 0 && logFileCheckExist(g_log_path) != 1){
		sprintf(newPath, "%s/message_bak_%04d.log", g_log_path, g_logIndex_t.fileNewestIndex);
	}else{
		g_logIndex_t.fileNewestIndex = (++g_logIndex_t.fileNewestIndex) % FILE_INDEX_MAX;
		sprintf(newPath, "%s/message_bak_%04d.log", g_log_path ,g_logIndex_t.fileNewestIndex);
	}
	logFilePrintf("[%s:%d]new file:%s\n",__FUNCTION__, __LINE__, newPath);
	logFileCopyFile(g_log_message_path, newPath);
	logClearFile(g_log_message_path);

	ret = logGetFileSize(newPath);
	if(ret < 0){
		logFilePrintf("[%s:%d] logGetFileSize error \n", __FUNCTION__, __LINE__);
		return -1;
	}

	g_logIndex_t.fileTotalSize += ret;
	g_logIndex_t.fileNumber++;
	g_dirty= 1;
	
	if(g_logIndex_t.fileTotalSize <  LOG_FILE_SIZE_TOTAL){
		return 0;
	}

	while(g_logIndex_t.fileTotalSize >=  LOG_FILE_SIZE_TOTAL){
		sprintf(oldPath, "%s/message_bak_%04d.log", g_log_path, g_logIndex_t.fileOldestIndex);
		if(access(oldPath, F_OK) == 0){
			ret = logGetFileSize(oldPath);
			if(ret < 0){
				logFilePrintf("[%s:%d]logGetFileSize error \n",  __FUNCTION__, __LINE__);
				return -1;
			}
			g_logIndex_t.fileTotalSize -= ret;
			g_logIndex_t.fileNumber--;
			remove(oldPath);
		}
		g_logIndex_t.fileOldestIndex = (++g_logIndex_t.fileOldestIndex) % FILE_INDEX_MAX;

		if(g_logIndex_t.fileOldestIndex == g_logIndex_t.fileNewestIndex){
			logFilePrintf("[%s:%d]g_logIndex_t.fileOldestIndex == g_logIndex_t.fileNewestIndex:%d \n"
				, __FUNCTION__, __LINE__, g_logIndex_t.fileNewestIndex);
			break;
		}
	
		usleep(100);
	}
	g_dirty= 1;
	
	return SUCCESS;
}

static int logRemoveOldestFile()
{
	int ret = 0;
	char oldPath[255] = {0};

	while(g_logIndex_t.fileTotalSize >=  LOG_FILE_SIZE_TOTAL){
		sprintf(oldPath, "%s/message_bak_%04d.log", g_log_path, g_logIndex_t.fileOldestIndex);
		if(access(oldPath, F_OK) == 0){
			ret = logGetFileSize(oldPath);
			if(ret < 0){
				logFilePrintf("[%s:%d] logGetFileSize error \n", __FUNCTION__, __LINE__);
				return -1;
			}
			g_logIndex_t.fileTotalSize -= ret;
			g_logIndex_t.fileNumber--;
			remove(oldPath);
		}
		g_logIndex_t.fileOldestIndex = (++g_logIndex_t.fileOldestIndex) % FILE_INDEX_MAX;

		if(g_logIndex_t.fileOldestIndex == g_logIndex_t.fileNewestIndex){
			logFilePrintf("[%s:%d]g_logIndex_t.fileOldestIndex == g_logIndex_t.fileNewestIndex:%d \n"
				, __FUNCTION__, __LINE__, g_logIndex_t.fileNewestIndex);
			break;
		}
	
		usleep(100);
	}

	g_dirty= 1;
	return SUCCESS;
}

static int logFileExchangeCache()
{
	int ret = 0;
	size_t size = 0;
	char *line = NULL;
	FILE* fpSrc = NULL;
	FILE* fpDst = NULL;

	/*message_cache.log  to  message.log*/
	fpSrc = fopen(LOG_FILE_PATH_CACHE, "r");
	if(NULL == fpSrc){
		logFilePrintf("[%s:%d] fopen %s error:%s\n", __FUNCTION__, __LINE__,LOG_FILE_PATH_CACHE ,strerror(errno));
		return -1;
	}

	fpDst = fopen(g_log_message_path, "a");
	if(NULL == fpDst){
		logFilePrintf("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		goto EXIT1;
	}

	while(-1 != getline(&line, &size, fpSrc)){
		fprintf(fpDst, "%s", line);
		fflush(fpDst);
		
		free(line);
		line = NULL;

		ret = logGetFileSize(g_log_message_path);
		if(ret < 0){
			logFilePrintf("[%s:%d]logGetFileSize error \n", __FUNCTION__, __LINE__);
			return -1;
		}

		if(ret >= LOG_FILE_SIZE_SINGLE){
			fclose(fpDst);
			fpDst = NULL;
			logFileExchange();

			fpDst = fopen(g_log_message_path, "a");
			if(NULL == fpDst){
				logFilePrintf("[%s:%d] fopen error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
				goto EXIT0;
			}
		}		
	}

	if(NULL != line){
		free(line);
		line = NULL;
	}
	fclose(fpDst);
	fclose(fpSrc);

	logClearFile(LOG_FILE_PATH_CACHE);
	return 0;	
EXIT0:
	fclose(fpDst);
EXIT1:
	fclose(fpSrc);
	return -1;
}

static void *logFileCheckBySizeCacheThread(void)
{	
	int ret = 0;
	time_t now_time = 0;

	last_flush_time = time(NULL);
	while(g_running){
		now_time = time(NULL);
		//logFilePrintf("[%s:%d]time inter:%d \n", __FUNCTION__, __LINE__, now_time - last_flush_time);
		if(now_time - last_flush_time >= 30 || last_flush_time - now_time >= 30){
			ret = logGetFileSize(LOG_FILE_PATH_CACHE);
			if(ret < 0){
				logFilePrintf("[%s:%d]logGetFileSize error \n", __FUNCTION__, __LINE__);
				return NULL;
			}

			if(ret > 0){
				logFileExchangeCache();
				last_flush_time = now_time;
			}

		}else{
			/*check message_cache.log file size*/
			ret = logFileCheckBySize(LOG_FILE_PATH_CACHE);
			if(ret == 1){/*reach the limit*/
				logFileExchangeCache();
			}
		}
		
		/*check log dir file size*/
		if(g_logIndex_t.fileTotalSize >=  LOG_FILE_SIZE_TOTAL){/*reach the limit*/
			logRemoveOldestFile();
		}

		//flush index file
		if(g_dirty == 1){
			logFilePrintf("[%s:%d] logIndexFileFlush ------------\n", __FUNCTION__, __LINE__);
			if(logIndexFileFlush(g_log_bin_path, &g_logIndex_t, sizeof(g_logIndex_t)) < 0){
				logFilePrintf("[%s:%d] logIndexFileFlush error\n", __FUNCTION__, __LINE__);
			}

			g_dirty = 0;
		}

		sleep(5);
	}

	g_running = 0;
	
	return NULL;
}

static void *logFileCheckBySizeThread(void)
{
	int ret = 0;
	
	while(g_running){
		/*check message.log file size*/
		ret = logFileCheckBySize(g_log_message_path);
		if(ret == 1){/*reach the limit*/
			logFileExchange();
		}

		/*check log dir file size*/
		if(g_logIndex_t.fileTotalSize >=  LOG_FILE_SIZE_TOTAL){/*reach the limit*/
			logRemoveOldestFile();
		}

		//flush index file
		if(g_dirty == 1){
			logFilePrintf("[%s:%d] logIndexFileFlush ------------\n", __FUNCTION__, __LINE__);
			if(logIndexFileFlush(g_log_bin_path, &g_logIndex_t, sizeof(g_logIndex_t)) < 0){
				logFilePrintf("[%s:%d] logIndexFileFlush error\n", __FUNCTION__, __LINE__);
			}

			g_dirty = 0;
		}

 		sleep(5);
	}

	g_running = 0;
	
	return NULL;
} 

static int logGetFileSeqNum(char *fileName)
{
	if(NULL == fileName){
		logFilePrintf("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	 int len = 0;
        int value = 0;
        char tmp[10] = {0};
        char *p1 = NULL;
        char *p2 = NULL;

        p1 = strrchr(fileName, '_');
        if(p1 == NULL){
                logFilePrintf("[%s:%d]  not found _ in fileName\n", __FUNCTION__, __LINE__);
                return -1;
        }

        p2 = strrchr(fileName, '.');
        if(p2 == NULL){
                logFilePrintf("[%s:%d]  not found . in fileName\n", __FUNCTION__, __LINE__);
                return -1;
        }
		
        len = p2 - p1 - 1;
        memcpy(tmp, p1+1, len);
        value = atoi(tmp);

	return value;
}

static void logGetIndexBinInfo(void)
{
	logFilePrintf("fileOldestIndex:%d, fileNewestIndex:%d\n", g_logIndex_t.fileOldestIndex, g_logIndex_t.fileNewestIndex);
	logFilePrintf("fileTotalSize:%d\n", g_logIndex_t.fileTotalSize);
	logFilePrintf("fileNumber:%d\n", g_logIndex_t.fileNumber);
	logFilePrintf("fileOldestIndex:%d\n", g_logIndex_t.fileOldestIndex);
	logFilePrintf("fileNewestIndex:%d\n", g_logIndex_t.fileNewestIndex);
	logFilePrintf("fileBuiltTime:%s\n", g_logIndex_t.fileBuiltTime);

	return;
}

static int logFullyWrite(int fd, void *buf, int nbytes)
{
	if(NULL == buf){
		logFilePrintf("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	int ret = 0;
	int nwritten = 0;

	while(nwritten < nbytes){
		ret = write(fd, (char *)buf + nwritten, nbytes - nwritten);
		if(ret < 0){
			if(ret == EINTR || ret == EAGAIN){
				sleep(1);
				continue;
			}
			
			logFilePrintf("[%s:%d] logFullyWrite error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return -1;
		}
		else if(ret == 0){
			break;
		}

		nwritten += ret;
	}

	ret = fsync(fd);
	if(ret < 0){
		return -1;
	}
	
	return nwritten;
}

static int logIndexFileFlush(char *filePath, void *data, int dataSize)
{
	if(NULL == filePath|| NULL == data){
		logFilePrintf("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	int fd = -1;

	fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if(fd == -1){
		logFilePrintf("[%s:%d] open %s error:%s\n", __FUNCTION__, __LINE__, filePath, strerror(errno));
		goto EXIT;
	}

	if(logFullyWrite(fd, data, dataSize) < 0){
		logFilePrintf("[%s:%d] write %s error\n", __FUNCTION__, __LINE__, filePath);
		goto EXIT;
	}

	close(fd);
	return 0;
	
EXIT:
	if(fd > 0){
		close(fd);
		fd = -1;
	}

	return -1;
}

static int logIndexReBuilt()
{
	logFilePrintf("[%s:%d] logIndexReBuilt\n", __FUNCTION__, __LINE__);
	int ret = 0;
	DIR *logDir = NULL;
	char tmpPath[128] = {0};
	FILE_NODE_ST tmpNode[50];
	struct dirent *logDirent = NULL;

	memset(&g_logIndex_t, 0, sizeof(g_logIndex_t));
	memset(tmpNode, 0, sizeof(tmpNode));

	sprintf(g_logIndex_t.fileBuiltTime, "%s", FILE_INDEX_BUILT_TIME);
	logDir = opendir(g_log_path);
	if(logDir == NULL){
		logFilePrintf("[%s:%d]  opendir error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while((logDirent = readdir(logDir)) != NULL){
		if(isLogBakFile(logDirent->d_name) == 1){
			sprintf(tmpNode[g_logIndex_t.fileNumber++].fileName, "%s", logDirent->d_name);

			memset(tmpPath, 0, sizeof(tmpPath));
			sprintf(tmpPath, "%s/%s", g_log_path, logDirent->d_name);

			ret = logGetFileSize(tmpPath);
			if(ret < 0){
				logFilePrintf("[%s:%d] logGetFileSize error\n", __FUNCTION__, __LINE__);
				//return -1;
			}
			g_logIndex_t.fileTotalSize += ret;
			logFilePrintf("file:%s, size:%d, fileNumber:%d, fileTotalSize:%d\n", tmpPath, ret , g_logIndex_t.fileNumber, g_logIndex_t.fileTotalSize);
		}
	}

	if(g_logIndex_t.fileNumber > 0){
		qsort(tmpNode, g_logIndex_t.fileNumber, sizeof(tmpNode[0]), logCmpCallback);
	}else{
		logFilePrintf("[%s:%d]  no bak file\n", __FUNCTION__, __LINE__);
		goto EXIT;
	}

	ret = logGetFileSeqNum(tmpNode[0].fileName);
	if(ret < 0){
		logFilePrintf("[%s:%d]  logGetFileSeqNum error\n", __FUNCTION__, __LINE__);
             goto EXIT;
	}
	g_logIndex_t.fileOldestIndex = ret;

	ret = logGetFileSeqNum(tmpNode[g_logIndex_t.fileNumber - 1].fileName);
	if(ret < 0){
		logFilePrintf("[%s:%d]  logGetFileSeqNum error\n", __FUNCTION__, __LINE__);
             goto EXIT;
	}
	g_logIndex_t.fileNewestIndex = ret;

	logGetIndexBinInfo();
	closedir(logDir);

	if(logIndexFileFlush(g_log_bin_path, &g_logIndex_t, sizeof(g_logIndex_t)) < 0){
		logFilePrintf("[%s:%d] logIndexFileFlush error\n", __FUNCTION__, __LINE__);
             goto EXIT1;
	}

	return 0;

	logFilePrintf("[%s:%d]  EXIT\n", __FUNCTION__, __LINE__);
EXIT:
	closedir(logDir);
	return -1;
EXIT1:
	return -1;
}

static int logIndexBuilt(void)
{
	logFilePrintf("[%s:%d] logIndexBuilt \n", __FUNCTION__, __LINE__);
	memset(&g_logIndex_t, 0, sizeof(g_logIndex_t));
	sprintf(g_logIndex_t.fileBuiltTime, "%s", FILE_INDEX_BUILT_TIME);

	if(logIndexFileFlush(g_log_bin_path, &g_logIndex_t, sizeof(g_logIndex_t)) < 0){
		logFilePrintf("[%s:%d] logIndexFileFlush error\n", __FUNCTION__, __LINE__);
             return -1;
	}

	return 0;
}

static int logFullyRead(int fd, void *buf, int nbytes)
{
	if(NULL == buf){
		logFilePrintf("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
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
			
			logFilePrintf("[%s:%d] read error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return -1;
		}else if(ret == 0){
			break;
		}

		nread += ret;
	}

	return nread;
}

static int logIndexLoad(char *filePath)
{
	if(NULL == filePath){
		logFilePrintf("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}
		
	int fd = -1;

	memset(&g_logIndex_t, 0, sizeof(g_logIndex_t));

	fd = open(filePath, O_RDONLY);
	if(fd == -1){
		logFilePrintf("[%s:%d] open %s error:%s\n", __FUNCTION__, __LINE__, filePath, strerror(errno));
		return -1;
	}

	if(logFullyRead(fd, &g_logIndex_t, sizeof(g_logIndex_t)) < 0){
		logFilePrintf("[%s:%d] read %s \n", __FUNCTION__, __LINE__, filePath);
		return -1;
	}

	logGetIndexBinInfo();

	close(fd);
	return 0;
}

static int logGetBakFileNum()
{	
	int count = 0;
	DIR *logDir = NULL;
	struct dirent *logDirent = NULL;

	logDir = opendir(g_log_path);
	if(logDir == NULL){
		logFilePrintf("[%s:%d] opendir error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while((logDirent = readdir(logDir)) != NULL){
		if(isLogBakFile(logDirent->d_name) == 1){
			count++;
		}
	}

	logFilePrintf("[%s:%d]  ,count:%d\n", __FUNCTION__, __LINE__, count);
	closedir(logDir);
	
	return count;
}

static int logIndexCheck()
{
	char newPath[255] = {0};
	char oldPath[255] = {0};

	/*check built time*/
	if(strcmp(g_logIndex_t.fileBuiltTime, FILE_INDEX_BUILT_TIME)  != 0){
		logFilePrintf("[%s:%d] built time not match\n", __FUNCTION__, __LINE__);
		if(remove(g_log_bin_path) < 0){
			logFilePrintf("[%s:%d] remove index.bin error:%s\n", __FUNCTION__, __LINE__,strerror(errno));
			return -1;
		}
		
		if(logIndexReBuilt() < 0){
			logFilePrintf("[%s:%d] logIndexReBuilt error\n", __FUNCTION__, __LINE__);
			return -1;
		}

		return 0;
	}

	/*check file number*/
	if(logGetBakFileNum() != g_logIndex_t.fileNumber){
		logFilePrintf("[%s:%d] fileNumber not match\n", __FUNCTION__, __LINE__);
		if(remove(g_log_bin_path) < 0){
			logFilePrintf("[%s:%d] remove index.bin error:%s\n", __FUNCTION__, __LINE__,strerror(errno));
			return -1;
		}
		
		if(logIndexReBuilt() < 0){
			logFilePrintf("[%s:%d]  error\n", __FUNCTION__, __LINE__);
			return -1;
		}

		return 0;
	}

	/*check index file*/
	if(g_logIndex_t.fileNumber > 0){
		sprintf(oldPath, "%s/message_bak_%04d.log", g_log_path, g_logIndex_t.fileOldestIndex);
		sprintf(newPath, "%s/message_bak_%04d.log", g_log_path, g_logIndex_t.fileNewestIndex);
		if(access(oldPath, F_OK) != 0 || access(newPath, F_OK) != 0){
			if(remove(g_log_bin_path) < 0){
				logFilePrintf("[%s:%d] remove index.bin error:%s\n", __FUNCTION__, __LINE__,strerror(errno));
				return -1;
			}
			
			if(logIndexReBuilt() < 0){
				logFilePrintf("[%s:%d]  error\n", __FUNCTION__, __LINE__);
				return -1;
			}
		}
	}
	
	return 0;
}

static int logFileCheckExist(char *dirPath)
{
	if(NULL == dirPath ){
		logFilePrintf("[%s:%d]  arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	int ret = 0;
	DIR *logDir = NULL;
	struct dirent *logDirent = NULL;

	logDir = opendir(dirPath);
	if(logDir == NULL){
		logFilePrintf("[%s:%d] opendir error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while((logDirent = readdir(logDir)) != NULL){
		if(isLogBakFile(logDirent->d_name) == 1){
			ret = 1;
			break;
		}
	}

	closedir(logDir);
	
	return ret;
}

static int logFileDeleteLogHandle(int level, char *modelName, char *filePath)
{
	if(!modelName || !filePath){
		logFilePrintf("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	int i = 0;
	int ret_line = 0;
	int ret = 0;
	size_t size = 0;
	char *line = NULL;
	int pIndex = 0;
	char *linePtr[LOG_SINGLE_FILE_LINE_MAX] = {NULL};
	LOG_FILE_ST logFile;

	/*read line from file*/
	FILE* fpLog = fopen(filePath, "r");
	if(NULL != fpLog){
		while((-1 != (ret_line = getline(&line, &size, fpLog))) && (pIndex <= LOG_SINGLE_FILE_LINE_MAX)){
			if(NULL != line){
				//logFilePrintf("line:%s\n", line);
				memset(&logFile, 0, sizeof(logFile));
				ret = sscanf(line, "%s %s %s %[^\n]", logFile.logTimeStr, logFile.logModuleName, logFile.logLevelStr, logFile.logMsg);
				logFile.logLevel = LogLevelToInt(logFile.logLevelStr);
				if((0 == strcmp(LOG_MODULE_ALL, modelName) || (0 == strcmp(modelName, logFile.logModuleName))) 
					&& (LOG_LEVEL_ALL == level || level == logFile.logLevel)){
					logFilePrintf("[%s:%d] +++++++++++++++++delete line:%s\n", __FUNCTION__, __LINE__, line);
					free(line);
					line = NULL;
					continue;
				}

				linePtr[pIndex++] = line;
				line = NULL;
			}
		}

		if(pIndex > LOG_SINGLE_FILE_LINE_MAX){
			logFilePrintf("[%s:%d] file line too much\n", __FUNCTION__, __LINE__);
		}

		if(NULL != line){
			free(line);
			line = NULL;
		}
		fclose(fpLog);
	}
	else{
		logFilePrintf("[%s:%d] fopen error:%s, path:%s\n", __FUNCTION__, __LINE__, strerror(errno), filePath);
	}

	/*clear empty the log file*/
	int fp = open(filePath, O_WRONLY|O_TRUNC);
	if(fp < 0){
		logFilePrintf("[%s:%d] open error:%s, file:%s\n", __FUNCTION__, __LINE__, strerror(errno), filePath);
		return FAILURE;
	}
	close(fp);
	
	if(pIndex == 0){
		/*handle not logsever file*/
		if(LOG_CACHE_SWITCH){
			if(0 != strcmp(filePath, LOG_FILE_PATH_CACHE)){
				logFilePrintf("func:%s , line:%d remove:%s\n", __FUNCTION__, __LINE__, filePath);
				remove(filePath);
				return 0;
			}
		}else{
			if(0 != strcmp(filePath, g_log_message_path)){
				logFilePrintf("func:%s , line:%d remove:%s\n", __FUNCTION__, __LINE__, filePath);
				remove(filePath);
				return 0;
			}
		}
		return 0;
	}

	/*has not mache log*/
	FILE* fpSaveLog = fopen(filePath, "w+");
    if(NULL == fpSaveLog){
            logFilePrintf("[%s:%d] fopen w error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
            return FAILURE;
    }

	for(i = 0; i < pIndex ; i++){
		fprintf(fpSaveLog, "%s", linePtr[i]);
		free(linePtr[i]);
		linePtr[i] = NULL;
	}
	fclose(fpSaveLog);
	return 0;
}

int logFileDeleteLog(int level, char *modelName)
{
	if(!modelName){
		logFilePrintf("[%s:%d] arg error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	char fullPath[255] = {0};
	DIR *logDir = NULL;
	struct dirent *logDirent = NULL;

	/*delete cache file message*/
	if(LOG_CACHE_SWITCH){
		if(logFileDeleteLogHandle(level, modelName, LOG_FILE_PATH_CACHE) < 0){
			logFilePrintf("[%s:%d] logFileDeleteLogHandle error\n", __FUNCTION__, __LINE__);
			return -1;
		}
	}

	/*delete message.log message*/
	if(logFileDeleteLogHandle(level, modelName, g_log_message_path) < 0){
		logFilePrintf("[%s:%d] logFileDeleteLogHandle error\n", __FUNCTION__, __LINE__);
		return -1;
	}

	/*delete bak file*/
	logDir = opendir(g_log_path);
	if(logDir == NULL){
		logFilePrintf("[%s:%d] opendir error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while((logDirent = readdir(logDir)) != NULL){
		if(isLogBakFile(logDirent->d_name) == 1){
			sprintf(fullPath, "%s/%s", g_log_path, logDirent->d_name);
			logFilePrintf("[%s:%d]delete fullPath:%s\n", __FUNCTION__, __LINE__, fullPath);
			if(logFileDeleteLogHandle(level, modelName, fullPath) < 0){
				logFilePrintf("[%s:%d] logFileDeleteLogHandle error\n", __FUNCTION__, __LINE__);
				goto failed;
			}
		}
	}
	closedir(logDir);

clean:
	logIndexReBuilt();
	return 0;
failed:
	logIndexReBuilt();
	return -1;
}

int logFileClearAllLog(void)
{
	char fullPath[255] = {0};
	DIR *logDir = NULL;
	struct dirent *logDirent = NULL;

	logDir = opendir(g_log_path);
	if(logDir == NULL){
		logFilePrintf("[%s:%d] opendir error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while((logDirent = readdir(logDir)) != NULL){
		if(isLogBakFile(logDirent->d_name) == 1){
			sprintf(fullPath, "%s/%s", g_log_path, logDirent->d_name);
			logFilePrintf("[%s:%d]remove fullPath:%s\n", __FUNCTION__, __LINE__, fullPath);
			remove(fullPath);
		}
	}
	closedir(logDir);

	logIndexBuilt();
	
	return 0;
}

int logFileClearOutMaxIndexFile()
{	
	int ret = 0;
	int num = 0;
	char fullPath[255] = {0};
	DIR *logDir = NULL;
	struct dirent *logDirent = NULL;

	logDir = opendir(g_log_path);
	if(logDir == NULL){
		logFilePrintf("[%s:%d] opendir error:%s\n", __FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

	while((logDirent = readdir(logDir)) != NULL){
		if(isLogBakFile(logDirent->d_name) == 1){
			num = logGetFileSeqNum(logDirent->d_name);
			if(num > FILE_INDEX_MAX){
				sprintf(fullPath, "%s/%s", g_log_path, logDirent->d_name);
				logFilePrintf("[%s:%d]remove fullPath:%s\n", __FUNCTION__, __LINE__, fullPath);
				remove(fullPath);
			}
		}
	}
	closedir(logDir);
	
	return ret;
}

int  logIndexInit()
{	
	//remove large than indexMax file
	logFileClearOutMaxIndexFile();
	
	//check index is exist or not
	if(access(g_log_bin_path, F_OK) != 0){
		logFilePrintf("[%s:%d] index not exist\n", __FUNCTION__, __LINE__);

		if(logFileCheckExist(g_log_path) == 1){//index not exist  ,file exist
			logFilePrintf("[%s:%d] file exist\n", __FUNCTION__, __LINE__);
			if(logIndexReBuilt() < 0){
				logFilePrintf("[%s:%d]  index error\n", __FUNCTION__, __LINE__);
				return -1;
			}
		}else{//index not exist  ,file not exist
			logFilePrintf("[%s:%d] file not exist\n", __FUNCTION__, __LINE__);
			if(logIndexBuilt() < 0){
				logFilePrintf("[%s:%d]  index error\n", __FUNCTION__, __LINE__);
				return -1;
			}
		}
		return 0;
	}

	logFilePrintf("[%s:%d] index exist\n", __FUNCTION__, __LINE__);
	if(logFileCheckExist(g_log_path) == 1){//index exist  ,file exist
		logFilePrintf("[%s:%d] file exist\n", __FUNCTION__, __LINE__);
		if(logIndexLoad(g_log_bin_path) < 0){
			logFilePrintf("[%s:%d]  index error\n", __FUNCTION__, __LINE__);
			return -1;
		}

		if(logIndexCheck() < 0){
			logFilePrintf("[%s:%d]  index error\n", __FUNCTION__, __LINE__);
			return -1;
		}
	}else{//index exist  ,file not exist
		logFilePrintf("[%s:%d] file not exist:%s\n", __FUNCTION__, __LINE__, g_log_path);
		if(logIndexBuilt() < 0){
				logFilePrintf("[%s:%d]  index error\n", __FUNCTION__, __LINE__);
				return -1;
		}
	}
	
	return 0;
}

void logFileInit()
{
	/*check log*/
	if(access(g_log_path, F_OK) != 0){
		if(mkdir(g_log_path, 0755) < 0){
			logFilePrintf("[%s:%d] mkdir %s error :%s\n", __FUNCTION__, __LINE__, g_log_path, strerror(errno));
			return ;
		}
	}
	
	/*index init*/
	memset(&g_logIndex_t, 0, sizeof(LOG_FILE_INDEX_ST));
	
	if(logIndexInit() < 0){
		g_useIndex = 0;
	}else{
		g_useIndex = 1;
	}

	logFilePrintf("[%s:%d]  g_useIndex:%d\n", __FUNCTION__, __LINE__, g_useIndex);
	
	/*start thread*/
	if(LOG_CACHE_SWITCH){
		if(0 != pthread_create(&g_log_t, NULL, (void *)logFileCheckBySizeCacheThread, NULL)){
			logFilePrintf("[%s:%d] pthread_create error :%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return ;
		}
	}else{
		if(0 != pthread_create(&g_log_t, NULL, (void *)logFileCheckBySizeThread, NULL)){
			logFilePrintf("[%s:%d] pthread_create error :%s\n", __FUNCTION__, __LINE__, strerror(errno));
			return ;
		}
	}

	return;
}

void logFileUninit()
{
	g_running = 0;

	logIndexFileFlush(g_log_bin_path, &g_logIndex_t, sizeof(g_logIndex_t));
	pthread_join(g_log_t, NULL);
}
