/*****************************************************************************
* Copyright@ 2004-2016 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: logWrite.c
* Author:    LiLi 
* Version:   1.0
* Description:
*     
* information.
*  		supply log write api to shell script 
* History:  
*     2016-04-5: LiLi    File created.   
*****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <syslog.h>

#include "logApi.h"
#define  LOG_ERROR(fmt,args...) printf("LogModule: "fmt"",##args)
//#define  LOG_ERROR(fmt,args...) while(0){};

//#define  LOG_PRINT(fmt,args...) printf("LogModule: "fmt"",##args)
#define  SHELL_PRINT(fmt,args...) while(0){};

#define  WRITE 1
void usage(void)
{
	printf("\nthe usage of logWrite:\n\n");
	printf("     logApi OPERATION PROCESS_NAME LEVEL MODULE_NAME \"CONTENT\"\n\n");
	printf("     OPERATION:now just have write\n");
	printf("     PROCESS_NAME:which process to write log\n");
	printf("     LEVEL:log level,is a number between 0 and 7,{0:EMERG;1:ALERT;2:CRIT;3:ERR;4:WARNING;5:NOTICE;6:INFO;7:DEBUG}\n");
	printf("     MODULE_NAME:which module to write log\n");
	printf("     CONTENT:the log content,must include in \"\"\n\n");
	printf("for example: logApi write mediaService 6 streamd \"log test\"\n\n");
}

int main(int argc, char** argv)
{
	int index = 0;
	int level = 0;
	int operation = 0;	
	char message[1024] = {0};

	/*at least have 2 parameters*/
	if (argc < 2) 
	{		
		usage();
		return -1;
	}
	

	for(index = 0;index < argc;index++)
	{
		SHELL_PRINT("argc[%d]:%s\n",index,argv[index]);
	}
	
	if (strncmp(argv[1],"write",5) == 0)
	{
		/*at least have 6 parameters*/
		if (argc  < 6) 
		{		
			usage();
			return -1;
		}

		for(index = 5;index < argc;index++)
		{
			sprintf(message,"%s %s",message,argv[index]);
		}
		operation = WRITE;
	}
	else
	{
		usage();
		return -1;
	}		

	level = atoi(argv[3]);
	if (level < 0 || level >= 8)
	{
		LOG_ERROR("wrong log level");
		return -1;
	}	
	
			

	swLogOpenWithoutPthread(argv[2]);

	switch (operation)
	{
		case WRITE:
			
			SYSLOG(level, argv[4],message);
			break;
		
		default:
			break;
	}	
	
	swLogCloseWithoutPthread();	
	return 0;
}



