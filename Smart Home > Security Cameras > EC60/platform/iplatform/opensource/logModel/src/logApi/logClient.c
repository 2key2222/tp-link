/*
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define __FORCE_GLIBC
#define _GNU_SOURCE
#include <features.h>
/*
 * SYSLOG -- print message on log file
 *
 * This routine looks a lot like printf, except that it outputs to the
 * log file instead of the standard output.  Also:
 *	adds a timestamp,
 *	prints the module name in front of the message,
 *	has some other formatting types (or will sometime),
 *	adds a newline on the end of the message.
 *
 * The output of this routine is intended to be read by syslogd(8).
 *
 * Author: Eric Allman
 * Modified to use UNIX domain IPC by Ralph Campbell
 * Patched March 12, 1996 by A. Ian Vogelesang <vogelesang@hdshq.com>
 *  - to correct the handling of message & format string truncation,
 *  - to visibly tag truncated records to facilitate
 *    investigation of such Bad Things with grep, and,
 *  - to correct the handling of case where "write"
 *    returns after writing only part of the message.
 * Rewritten by Martin Mares <mj@atrey.karlin.mff.cuni.cz> on May 14, 1997
 *  - better buffer overrun checks.
 *  - special handling of "%m" removed as we use GNU sprintf which handles
 *    it automatically.
 *  - Major code cleanup.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/signal.h>
#include <sys/syslog.h>

#include <sys/uio.h>
#include <sys/wait.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <paths.h>
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include "logApi.h"
#include "logClient.h"

#if defined(__UCLIBC_HAS_THREADS__) && defined(USE_PTHREAD)
#include <pthread.h>
static pthread_mutex_t mylock = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
# define LOCK	__pthread_mutex_lock(&mylock)
# define UNLOCK	__pthread_mutex_unlock(&mylock)
#else
# define LOCK
# define UNLOCK
#endif

static int	LogFile = -1;		/* fd for log */
static int	connected;		/* have done connect */
static int	LogStat = 0;		/* status bits, set by openlog() */
static const char *LogTag = "syslog";	/* string to tag the entry with */
static int	LogFacility = LOG_USER;	/* default facility code */
static int	LogMask = 0xff;		/* mask of priorities to be logged */
static struct sockaddr_un SyslogAddr;	/* AF_UNIX address of local logger */

static void closelog_intern( int );
void syslog( int, const char *, ...);
void vsyslogd( int, const char *, va_list );
void openlogd( const char *, int, int );
void closelogd( void );
int setlogmask(int pmask);

static void 
closelog_intern(int to_default)
{
	LOCK;
	if (LogFile != -1) {
	    (void) close(LogFile);
	}
	LogFile = -1;
	connected = 0;
	if (to_default)
	{
		LogStat = 0;
		LogTag = "syslog";
		LogFacility = LOG_USER;
		LogMask = 0xff;
	}
	UNLOCK;
}

static void
sigpipe_handler (int sig)
{
  closelog_intern (0);
}

/*
 * syslog, vsyslog --
 *     print message on log file; output is intended for syslogd(8).
 */
void mySyslog(int pri, const char *fmt, ...)
{
	//printf("mySyslog===================\n");
	va_list ap;

	va_start(ap, fmt);
	vsyslogd(pri, fmt, ap);
	va_end(ap);
}

int syslog_send(int sockfd, void * buff,int size)
{
	if(NULL == buff || sockfd < 0 || size <= 0){
		return -1;
	}
	int count = 0;
	int ret = 0;
	int retry = 3;

	struct timeval ctval;
	ctval.tv_sec = 0;
	ctval.tv_usec = 2*1000;
	fd_set set;
	FD_ZERO(&set);
	FD_SET(sockfd,&set);
	int reflag = select(sockfd+1,NULL,&set,NULL,&ctval);
	if(reflag <= 0){
		return reflag;
	}

	if(FD_ISSET(sockfd, &set)){
		do{
			ret = send(sockfd,buff,size,0);
			if(ret < 0){
				if(errno == EINTR || errno == EAGAIN){
					usleep(0);
					continue;
				}
				break;
			}

			break;
		}while(retry-- > 0);
	}

	return ret;
}

void
vsyslogd( int pri, const char *fmt, va_list ap )
{
	register char *p;
	char *last_chr, *head_end, *end, *stdp;
	time_t now;
	int fd, saved_errno;
	int rc;
	char tbuf[1024];	/* syslogd is unable to handle longer messages */

	struct sigaction action, oldaction;
	int sigpipe;
	memset (&action, 0, sizeof (action));
	action.sa_handler = sigpipe_handler;
	sigemptyset (&action.sa_mask);
	sigpipe = sigaction (SIGPIPE, &action, &oldaction);

	saved_errno = errno;

	LOCK;
	/* See if we should just throw out this message. */
	if (!(LogMask & LOG_MASK(LOG_PRI(pri))) || (pri &~ (LOG_PRIMASK|LOG_FACMASK)))
		goto getout;

	
	if (LogFile < 0 || !connected)
		openlogd(LogTag, LogStat | LOG_NDELAY, 0);
	
	/* Set default facility if none specified. */
	if ((pri & LOG_FACMASK) == 0)
		pri |= LogFacility;

	/* Build the message. We know the starting part of the message can take
	 * no longer than 64 characters plus length of the LogTag. So it's
	 * safe to test only LogTag and use normal sprintf everywhere else.
	 */
	(void)time(&now);
	stdp = p = tbuf + sprintf(tbuf, "<%d>%.15s ", pri, ctime(&now) + 4);
	
	if (LogTag) {
		if (strlen(LogTag) < sizeof(tbuf) - 64)
			{
				p += sprintf(p, "%s", LogTag);
			}
		else
			{
				p += sprintf(p, "<BUFFER OVERRUN ATTEMPT>");
			}
	}

	
	if (LogStat & LOG_PID)
		{
			p += sprintf(p, "[%d]", getpid());
		}
	if (LogTag) {
		*p++ = ':';
		*p++ = ' ';
	}
	head_end = p;


	
	/* We format the rest of the message. If the buffer becomes full, we mark
	 * the message as truncated. Note that we require at least 2 free bytes
	 * in the buffer as we might want to add "\r\n" there.
	 */
	end = tbuf + sizeof(tbuf) - 1;
	//__set_errno(saved_errno);
	p += vsnprintf(p, end - p, fmt, ap);
	if (p >= end || p < head_end) {	/* Returned -1 in case of error... */
		static const char truncate_msg[12] = "[truncated] ";
		memmove(head_end + sizeof(truncate_msg), head_end,
			end - head_end - sizeof(truncate_msg));
		memcpy(head_end, truncate_msg, sizeof(truncate_msg));
		if (p < head_end) {
			while (p < end && *p) {
				p++;
			}
		}
		else {
			p = end - 1;
		}

	}
	last_chr = p;


	/* Output to stderr if requested. */
	if (LogStat & LOG_PERROR) {
		*last_chr = '\n';
		(void)write(STDERR_FILENO, stdp, last_chr - stdp + 1);
	}

	/* Output the message to the local logger using NUL as a message delimiter. */
	p = tbuf;
	*last_chr = 0;
	int count = 3;

	do {
		rc = syslog_send(LogFile, p, last_chr + 1 - p);
		if (rc < 0) {
			closelog_intern(0);
			break;
		}
		p+=rc;
	} while (p <= last_chr && count-- > 0);
	if (rc >= 0)
	{
		goto getout;
	}

	/*
	 * Output the message to the console; don't worry about blocking,
	 * if console blocks everything will.  Make sure the error reported
	 * is the one from the syslogd failure.
	 */
	/* should mode be `O_WRONLY | O_NOCTTY' ? -- Uli */
	if (LogStat & LOG_CONS &&
	    (fd = open(_PATH_CONSOLE, O_WRONLY, 0)) >= 0) {
		p = index(tbuf, '>') + 1;
		last_chr[0] = '\r';
		last_chr[1] = '\n';
		(void)write(fd, p, last_chr - p + 2);
		(void)close(fd);
	}

getout:
	UNLOCK;
	if (sigpipe == 0)
		sigaction (SIGPIPE, &oldaction,
			(struct sigaction *) NULL);
}

/*
 * OPENLOG -- open system log
 */
void
openlogd( const char *ident, int logstat, int logfac )
{
    int logType = SOCK_DGRAM;

    LOCK;
	
	
    if (ident != NULL)
	LogTag = ident;
    LogStat = logstat;
    if (logfac != 0 && (logfac &~ LOG_FACMASK) == 0)
	LogFacility = logfac;
    if (LogFile == -1) {
		
		SyslogAddr.sun_family = AF_UNIX;
		(void)strncpy(SyslogAddr.sun_path, LOG_SOCK_PATH,
		      sizeof(SyslogAddr.sun_path));
retry:
	if (LogStat & LOG_NDELAY) {
	    if ((LogFile = socket(AF_UNIX, logType, 0)) == -1){
		UNLOCK;
		return;
	    }
	    /*			fcntl(LogFile, F_SETFD, 1); */
	}
    }

    if (LogFile != -1 && !connected) {
	if (connect(LogFile, &SyslogAddr, sizeof(SyslogAddr)) != -1)
	{
	    connected = 1;
		
		/* set fd to no block */
		int flags = fcntl(LogFile,F_GETFL,0); 
		fcntl(LogFile,F_SETFL,flags | O_NONBLOCK); 
	} else if (logType == SOCK_DGRAM) {
	    logType = SOCK_STREAM;
	    if (LogFile != -1) {
		close(LogFile);
		LogFile = -1;
	    }
	    goto retry;
	} else {
	    if (LogFile != -1) {
		close(LogFile);
		LogFile = -1;
	    }
	}
    }

    UNLOCK;
}

/*
 * CLOSELOG -- close the system log
 */
void
closelogd( void )
{
	closelog_intern(1);
}

/* setlogmask -- set the log mask level */
int setlogmask(int pmask)
{
    int omask;

    omask = LogMask;
    LOCK;
    if (pmask != 0)
	LogMask = pmask;
    UNLOCK;
    return (omask);
}

#if 0
int main(void)
{
	
	openlogd("myMegMask", LOG_CONS | LOG_PID | LOG_PERROR, 0);
	
	
	syslog(LOG_DEBUG,"test");
	
	
	closelogd();
}
#endif

