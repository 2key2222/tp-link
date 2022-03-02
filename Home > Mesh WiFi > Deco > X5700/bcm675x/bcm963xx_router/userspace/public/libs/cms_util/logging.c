/***********************************************************************
 *
<:copyright-BRCM:2006:DUAL/GPL:standard

   Copyright (c) 2006 Broadcom 
   All Rights Reserved

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation (the "GPL").

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.

:>
 *
************************************************************************/


#include <fcntl.h>      /* open */
#include "cms.h"
#include "cms_log.h"
#include "cms_eid.h"
#include "cms_strconv.h"
#include "cms_mem.h"
#include "oal.h"
#include "bcm_ulog.h"

/** local definitions **/

/* default settings */

/** external functions **/

/** external data **/

/** internal functions **/

/** public data **/

/** private data **/
static CmsEntityId gEid;     /**< try not to use this.  inefficient b/c requires eInfo lookup. */
static char *gAppName=NULL;  /**< name of app; set during init */
static CmsLogLevel             logLevel; /**< Message logging level.
                                          * This is set to one of the message
                                          * severity levels: LOG_ERR, LOG_NOTICE
                                          * or LOG_DEBUG. Messages with severity
                                          * level lower than or equal to logLevel
                                          * will be logged. Otherwise, they will
                                          * be ignored. This variable is local
                                          * to each process and is changeable
                                          * from CLI.
                                          */
static CmsLogDestination logDestination; /**< Message logging destination.
                                          * This is set to one of the
                                          * message logging destinations:
                                          * STDERR or SYSLOGD. This
                                          * variable is local to each
                                          * process and is changeable from
                                          * CLI.
                                          */
static UINT32 logHeaderMask; /**< Bitmask of which pieces of info we want
                              *   in the log line header.
                              */


UINT32 cmsLog_dest_to_mask(CmsLogDestination cmsLogDestination)
{
   if (cmsLogDestination == LOG_DEST_STDERR)
   {
      return BCMULOG_DESTMASK_STDERR;
   }
   else if (cmsLogDestination == LOG_DEST_SYSLOG)
   {
      return BCMULOG_DESTMASK_SYSLOG;
   }
   else
   {
      // bcmulog doesn't understand telnet destination.  Default to STDERR.
      return BCMULOG_DESTMASK_STDERR;
   }
}

void log_log(CmsLogLevel level, const char *func, UINT32 lineNum, const char *pFmt, ... )
{
   char logBuf[MAX_LOG_LINE_LENGTH];
   BcmuLogFormatInfo info;
   va_list ap;

   if (level > logLevel)
   {
      return;
   }

   /* Call external function to format the log line. */
   memset(&info, 0, sizeof(info));
   info.buf = logBuf;
   info.bufLen = sizeof(logBuf);
   info.logLevel = level;
   info.logDestMask = cmsLog_dest_to_mask(logDestination);
   info.logHeaderMask = logHeaderMask;
   info.lineNum = lineNum;
   cmsUtl_strncpy(info.funcName, func, sizeof(info.funcName));
   if (gAppName == NULL)
   {
      sprintf(info.appName, "%d", cmsEid_getPid());
   }
   else
   {
      cmsUtl_strncpy(info.appName, gAppName, sizeof(info.appName));
   }
   va_start(ap, pFmt);
   bcmuLog_formatLine(&info, pFmt, ap);
   va_end(ap);

   /* Do the output to configured destination */
   if (logDestination == LOG_DEST_STDERR)
   {
      fprintf(stderr, "%s\n", logBuf);
      fflush(stderr);
   }
   else if (logDestination == LOG_DEST_TELNET )
   {
      int logTelnetFd = -1;
#ifdef DESKTOP_LINUX
      /* Fedora Desktop Linux */
      logTelnetFd = open("/dev/pts/1", O_RDWR);
#else
      /* CPE use ptyp0 as the first pesudo terminal */
      logTelnetFd = open("/dev/ttyp0", O_RDWR);
#endif
      if(logTelnetFd != -1)
      {
         if (0 > write(logTelnetFd, logBuf, strlen(logBuf)))
            printf("write to telnet fd failed\n");
         if (0 > write(logTelnetFd, "\n", strlen("\n")))
            printf("write to telnet fd failed(2)\n");
         close(logTelnetFd);
      }
   }
   else
   {
      oalLog_syslog(level, logBuf);
   }

}  /* End of log_log() */


void cmsLog_initWithName(CmsEntityId eid, const char *appName)
{
   logLevel       = DEFAULT_LOG_LEVEL;
   logDestination = DEFAULT_LOG_DESTINATION;
   logHeaderMask  = DEFAULT_LOG_HEADER_MASK;

   gEid = eid;

   /*
    * highly unlikely this strdup will fail, but even if it does, the
    * code can handle a NULL gAppName.
    */
   gAppName = cmsMem_strdup(appName);

   oalLog_init();

   return;
}


void cmsLog_init(CmsEntityId eid)
{
   const CmsEntityInfo *eInfo;

   if (NULL != (eInfo = cmsEid_getEntityInfo(eid)))
   {
      cmsLog_initWithName(eid, eInfo->name);
   }
   else
   {
      cmsLog_initWithName(eid, NULL);
   }

   return;

}  /* End of cmsLog_init() */


void cmsLog_cleanup(void)
{
   oalLog_cleanup();
   CMSMEM_FREE_BUF_AND_NULL_PTR(gAppName);
   return;

}  /* End of cmsLog_cleanup() */


void cmsLog_setLevel(CmsLogLevel level)
{
   logLevel = level;
   bcmuLog_setLevel(level);
   return;
}


CmsLogLevel cmsLog_getLevel(void)
{
   return logLevel;
}


void cmsLog_setDestination(CmsLogDestination dest)
{
   logDestination = dest;
   bcmuLog_setDestMask(cmsLog_dest_to_mask(dest));
   return;
}


CmsLogDestination cmsLog_getDestination(void)
{
   return logDestination;
}


void cmsLog_setHeaderMask(UINT32 headerMask)
{
   logHeaderMask = headerMask;
   bcmuLog_setHdrMask(headerMask);
   return;
}


UINT32 cmsLog_getHeaderMask(void)
{
   return logHeaderMask;
}


int cmsLog_readPartial(int ptr, char* buffer)
{
   return (oal_readLogPartial(ptr, buffer));
}
