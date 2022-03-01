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
#include <fcntl.h>

typedef struct _LOG_FILE_INDEX{
	int					fileTotalSize;
	int					fileNumber;
	int					fileOldestIndex;
	int   				fileNewestIndex;
	char					fileBuiltTime[32];
}LOG_FILE_INDEX_ST;

static void logFilePrintf(char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);

	fflush(stdout);
	return;
}

static int logFullyRead(int fd, void *buf, int nbytes)
{
	if(NULL == buf){
		logFilePrintf("[logFullyRead] arg error\n");
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
			
			logFilePrintf("read error:%s\n", strerror(errno));
			return -1;
		}else if(ret == 0){
			break;
		}

		nread += ret;
	}

	return nread;
}

int main(int argc, char **argv)
{		
	int fd = -1;
	FILE *fdWrite = NULL;
	char *filePath = NULL;
	LOG_FILE_INDEX_ST logIndex_t;
	
	if(argc < 2){
		printf("argc must large than 2, such as :./logIndexParse  index.bin\n");
		return -1;
	}

	filePath = argv[1];
	memset(&logIndex_t, 0, sizeof(logIndex_t));

	fd = open(filePath, O_RDONLY);
	if(fd == -1){
		logFilePrintf("open %s error:%s\n", filePath, strerror(errno));
		return -1;
	}

	fdWrite = fopen("index.txt", "w");
	if(fdWrite == NULL){
		logFilePrintf("open %s error:%s\n", "index.txt", strerror(errno));
		return -1;
	}

	if(logFullyRead(fd, &logIndex_t, sizeof(logIndex_t)) < 0){
		logFilePrintf("read %s \n", filePath);
		return -1;
	}

	fprintf(fdWrite, "fileTotalSize:%d\n", logIndex_t.fileTotalSize);
	fprintf(fdWrite, "fileNumber:%d\n", logIndex_t.fileNumber);
	fprintf(fdWrite, "fileOldestIndex:%d\n", logIndex_t.fileOldestIndex);
	fprintf(fdWrite, "fileNewestIndex:%d\n", logIndex_t.fileNewestIndex);
	fprintf(fdWrite, "fileBuiltTime:%s\n", logIndex_t.fileBuiltTime);

	fclose(fdWrite);
	close(fd);
	return 0;
}