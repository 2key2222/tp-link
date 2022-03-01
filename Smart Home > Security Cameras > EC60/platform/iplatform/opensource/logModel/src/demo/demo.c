/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: demo.c
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     
* information.
*  		how to use LOG() and DBG() to record and display message
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <syslog.h>

#include "logApi.h"
int main(int argc, char** argv)
{
	int i = 0;
	int count = 0;
	swLogOpen("record");
	
	do{
		count++;
		
		LOG(MYLOG_EMERG, INDEX_DAY_NIGHT, "[0] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_ALERT, INDEX_DAY_NIGHT, "[1] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_CRIT, INDEX_DAY_NIGHT, "[2] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_ERR, INDEX_DAY_NIGHT, "[3] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_WARNING, INDEX_DAY_NIGHT, "[4] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_NOTICE, INDEX_DAY_NIGHT, "[5] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_INFO, INDEX_DAY_NIGHT, "[6] ==========DAY_NIGHT count:%d\n", count);
		LOG(MYLOG_DEBUG, INDEX_DAY_NIGHT, "[7] ==========DAY_NIGHT count:%d\n", count);
		
		sleep(1);
	}while(1);
	
	swLogClose();
	return 0;
}
