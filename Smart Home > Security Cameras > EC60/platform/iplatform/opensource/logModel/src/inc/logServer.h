/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: syslogd.h
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     
* information.
*  
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#ifndef _LOGSERVER_H_
#define _LOGSERVER_H_

int syslogdSetLevel(unsigned char mask);
int syslogdSetModule(uint64_t mask);
unsigned char  syslogdGetLevel(void);
uint64_t syslogdGetModule(void);
#endif