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
#ifndef _LOGCLIENT_H_
#define _LOGCLIENT_H_

void mySyslog(int pri, const char *fmt, ...);
void openlogd( const char *ident, int logstat, int logfac);
void closelogd( void );
#endif
