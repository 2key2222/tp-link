/*
**    BPALogin - lightweight portable BIDS2 login client
**    Copyright (c) 2001-3 Shane Hyde, and others.
** 
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
** 
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
*/ 

/**
 * Changes:
 * 2001-09-19:  wdrose    Fixed incorrect use of single fork() to put
 *                        BPALogin into background.  Replaced with
 *                        fork(), setsid(), fork().
 *
 * 2001-12-05:  wdrose    Added fix gleaned from Sam Johnston to include
 *                        errno.h for errno, rather than assuming it is an
 *                        extern int.
 */
#include "bpalogin.h"

#ifdef TP_WEB_LOG
//added by yangxv for new syslog, 2008.11.03
#include <libmsglog.h>
#endif

#define BPALOGIN_BANNER \
        "BPALogin v2.0.2 - portable BigPond Broadband login client"

struct session s;
int debug_level = DEFAULT_DEBUG;
int dosyslog = 1;
// added by yangxv for bpa phase, 2008.08.08
int httpd_pid = 0;
int (*new_phase_hook) (int) = NULL;

static void init_args(int argc, char *argv[]);
int send_phase(int bpa_phase);
// end added 

//int parse_parms(struct session *,char * conffile);
void usage( void );
void debug(int l,char *s,...);


void onconnected(int i)
{
	#if 0
    if(strcmp(s.connectedprog,""))
    {
        char buf[500];
        sprintf(buf,"%.500s %d",s.connectedprog,s.listenport);

        debug(0,"Executing external command - %s\n",buf);
        system(buf);
    }
	#endif
}

void ondisconnected(int reason)
{
	#if 0
    if(strcmp(s.disconnectedprog,""))
    {
        char buf[500];
        sprintf(buf,"%.500s %d",s.disconnectedprog,reason);

        debug(0,"Executing external command - %s\n",buf);
        system(buf);
    }
	#endif
}

void critical(char *ss)
{
	#ifdef TP_WEB_LOG
	msglogd(LOG_INFO, LOGTYPE_OTHER, ss);
	#endif
	LINE_BACKUP_LOGGER_REG(LOGGER_INFO_ID_BPA_FAIL_LOGOUT, LOGGER_PARAM_STRING, s.zonex);
    if(dosyslog)
    	syslog(LOG_CRIT,"Critical error: %s\n",ss);
    else
    	printf("Critical error: %s\n",ss);
    exit(1);
}

void debug(int l,char *s,...)
{
    va_list ap;
    va_start(ap,s);
    if(debug_level > l)
    {
        int pri;
        char buf[256];

        switch(l)
        {
        case 0:
            pri = LOG_INFO;
            break;
        case 1:
            pri = LOG_INFO;
            break;
        case 2:
        case 3:
        default:
            pri = LOG_INFO;
            break;
        }
        vsprintf(buf,s,ap);
		// added by yangxv for web log, 2008.08.25
		#ifdef TP_WEB_LOG
		if (0 == l)
			msglogd(LOG_INFO, LOGTYPE_OTHER, buf);
		#endif	
		// end added
		
        if(dosyslog)
        	syslog(pri,"%s",buf);
        else
        	printf("%s",buf);
		
    }
    va_end(ap);
}

void noncritical(char *s,...)
{
    char buf[256];

    va_list ap;
    va_start(ap,s);
    vsprintf(buf,s,ap);

	#ifdef TP_WEB_LOG
	msglogd(LOG_INFO, LOGTYPE_OTHER, s);
	#endif
	
    if(dosyslog)
    	syslog(LOG_CRIT,buf);
    else
    	printf(buf);
	
    va_end(ap);
}

void onsignal(int i)
{
    debug(1,"Signal caught\n");
    logout(0,&s);
    s.ondisconnected(0);
    closelog();
    exit(1);
}

int main(int argc,char* argv[])
{
    int makedaemon = 1;
    char conffile[256];

    signal(SIGINT,onsignal);
    signal(SIGHUP,onsignal);
    signal(SIGTERM,onsignal);

    strcpy(s.authserver,DEFAULT_AUTHSERVER);
    strcpy(s.authdomain,DEFAULT_AUTHDOMAIN);
    s.authport = DEFAULT_AUTHPORT;
    strcpy(s.username,"");
    strcpy(s.password,"");
    strcpy(s.connectedprog,"");
    strcpy(s.disconnectedprog,"");
    strcpy(conffile,DEFAULT_CONFFILE);
    strcpy(s.localaddress,"");
    s.localport = BPA_UDP_PORT_LISTEN;
    s.minheartbeat = 60;
    s.maxheartbeat = 420;

	// added by yangxv, 2008.08.08
	init_args(argc, argv);

#ifdef QSDK/*  by Huangwenzhong, 15May14 */
	new_phase_hook = send_phase;
#else
	if (httpd_pid)
		new_phase_hook = send_phase;
#endif

	new_phase(PHASE_INITIALIZE);

	#ifdef BPA_DEBUG
	dosyslog = 0;
	#endif
	// end add
	
	#if 0
	int c;
	
    while( (c = getopt( argc, argv, "c:d:l:D" )) > -1 ) {
        switch( c ) {
        case 'c':
            strncpy( conffile, optarg, MAXCONFFILE);
            break;
        case '?':
            usage();
            exit(1);
            break;
        }
    }

    if(!parse_parms(&s,conffile)) {
        printf( "bpalogin: Could not read configuration file (%s)\n\n",
                conffile );
        usage();
        exit(1);
    }

    optind = 1;
    while( (c = getopt( argc, argv, "c:d:l:D" )) > -1 ) {
        switch( c ) {
        case 'D':
            makedaemon = 0;
            break;
        case 'c':
            break;
        case 'd':
            debug_level = atoi(optarg);
            break;
	case 'l':
	    if( strcasecmp( optarg, "stdout" ) == 0 )
	      	dosyslog = 0;
	    else
		dosyslog = 1;
	    break;
        case '?':
            break;
        case ':':
            break;
        }
    }
	#endif

    if(makedaemon) {
      /**
       * Original code did not perform the setsid() or second fork(), and
       * hence did not correctly make itself a daemon.  There is a library
       * call in FreeBSD (daemon) that does the actions below, but the
       * portability is unknown.
       */
      switch( fork() ) {
        case 0:
          break;
          
        case -1:
          perror("Could not run BPALogin in the background");
          exit(1);
          break;
          
        default:
          exit(0);
          break;
      }

      if( setsid() < 0 ) {
        perror("Could not run BPALogin in the background");
        exit(1);
      }

      /**
       * while not strictly necessary, the second fork ensures we stay
       * detached from a terminal by preventing the program using its
       * status as session leader to regain a terminal.
       */
      switch( fork() ) {
        case 0:
          break;

        case -1:
          perror("Could not run BPALogin in the background");
          exit(1);
          break;

        default:
          exit(0);
          break;
      }
    }
    

    openlog("bpalogin",LOG_PID,LOG_DAEMON);

    if(dosyslog)    
        syslog( LOG_INFO, BPALOGIN_BANNER "\n" );
    else
        printf( BPALOGIN_BANNER "\n");

    if(!strcmp(s.username,""))
    {
        critical("Username has not been set");
        exit(1);
    }
    if(!strcmp(s.password,""))
    {
        critical("Password has not been set");
        exit(1);
    }
    s.debug = debug;
    s.critical = critical;
    s.noncritical = noncritical;
    s.onconnected = onconnected;
    s.ondisconnected = ondisconnected;

    while(mainloop(&s));
    s.ondisconnected(0);

	/* added by yangxv
	 * There's no need to executive logout() when mainloop break out under s->shutdown=1
	 * because mainloop break out means not connected yet  
	 */
    exit(0);
}

static void init_args(int argc, char *argv[])
{
    int i=0;

    for (i = 1; i < argc; i++) {
		if (! strncmp(argv[i], "user", 4)) {
			if (++i == argc)
				usage();
			else
				strncpy(s.username, argv[i],
						sizeof(s.username) - 1);
		}
		else if (! strncmp(argv[i], "password", 8)) {
			if (++i == argc)
				usage();
			else
				strncpy(s.password, argv[i],
						sizeof(s.password) - 1);
		}
		else if (! strncmp(argv[i], "authserver", 10)) {
			if (++i == argc)
				usage();
			else
				strncpy(s.authserver, argv[i],
						sizeof(s.authserver) - 1);
		}
		else if (! strncmp(argv[i], "authdomain", 10)) {
			if (++i == argc)
				usage();
			else
				strncpy(s.authdomain, argv[i],
						sizeof(s.authdomain) - 1);
		}
		else if (! strncmp(argv[i], "httpd-pid", 9)) {
			if (++i == argc)
				usage();
			else
				httpd_pid = atoi(argv[i]);
		}
		else if (! strncmp(argv[i], "interface", 9)) {
			if (++i == argc)
				usage();
			else
				strncpy(s.interface, argv[i],
						sizeof(s.interface) - 1);
		}
		else if (! strncmp(argv[i], "zonex", 5)) {
			if (++i == argc)
				usage();
			else
				strncpy(s.zonex, argv[i],
						sizeof(s.zonex) - 1);
		}
        else {
            usage();
        }
    }
}

#if 0
int parse_parms(struct session *s,char * conffile)
{
    char buf[512];
    FILE * f;

    f = fopen(conffile,"rt");
    if(!f)
    {
        debug(0,"Cannot open conf file\n");
        return FALSE;
    }

    while(fgets(buf,400,f) != NULL)
    {
        char parm[100];
        char value[100];

        if(buf[0] == '#')
            continue;

        /**
         * Problem with using sscanf(buf, "%s %s"), parm, value):
         * usernames with periods et al are not picked up correctly.
         * Really need to use strtok.
         */
        sscanf(buf,"%s %s",parm,value);    
        debug(2,"Parameter %s set to %s\n",parm,value);

        if(!strcasecmp(parm,"username"))
        {
            strcpy(s->username,value);
        }
        else if(!strcasecmp(parm,"password"))
        {
            strcpy(s->password,value);
        }
        else if(!strcasecmp(parm,"authdomain"))
        {
            strcpy(s->authdomain,".");
            strcat(s->authdomain,value);
        }
        else if(!strcasecmp(parm,"authserver"))
        {
            strcpy(s->authserver,value);
        }
        else if(!strcasecmp(parm,"localaddress"))
        {
            strcpy(s->localaddress,value);
        }
        else if(!strcasecmp(parm,"logging"))
        {
            if(!strcasecmp("stdout",value) ||
               !strcasecmp("sysout",value)) dosyslog = 0; // for compatibility
            if(!strcasecmp("syslog",value)) dosyslog = 1;
        }
        else if(!strcasecmp(parm,"debuglevel"))
        {
            debug_level = atoi(value);
        }
        else if(!strcasecmp(parm,"minheartbeatinterval"))
        {
            s->minheartbeat = atoi(value);   
        }
        else if(!strcasecmp(parm,"maxheartbeatinterval"))
        {
            s->maxheartbeat = atoi(value);   
        }
        else if(!strcasecmp(parm,"localport"))
        {
            s->localport = atoi(value);
        }
        else if(!strcasecmp(parm,"connectedprog"))
        {
            strcpy(s->connectedprog,value);
        }
        else if(!strcasecmp(parm,"disconnectedprog"))
        {
            strcpy(s->disconnectedprog,value);
        }
    }
    
    fclose(f);
    strcat(s->authserver,s->authdomain);
    return TRUE;
}

void usage( void )
{
    printf( BPALOGIN_BANNER "\n");
    printf("Copyright (c) 2001-3 Shane Hyde and others\n\n");
    printf("This program is *not* a product of Big Pond Advance\n\n");
    printf("Usage: bpalogin [-c file] [-d level] [-l style] [-D]\n\n");
    printf(" -c file            Specifies the configuration file to use\n");
    printf("                    (default is %s)\n\n", DEFAULT_CONFFILE);
    printf(" -d level           Set the verbosity of log messages\n");
    printf("                    (0 is quiet, 2 is most verbose)\n\n");
    printf(" -l style           Use syslog or stdout for messages\n\n" );
    printf(" -D                 Dont run bpalogin as a daemon (run in "
           "foreground)\n\n");
    printf("Command line options override the values in the configuration "
           "file\n");
}
#endif 

void usage (void)
{
	printf("wrong input, no usage and exit:-)\n");
	exit(1);
}

int send_phase(int bpa_phase)
{
#ifdef QSDK/*  by Huangwenzhong, 12May14 */
#define UBUS_SET_STATUS_CMD_FORMAT		"ubus call internet set_status '{\"name\": \"%s\", \"status\": %d}'"
		char cmdline[256];
#endif

	union sigval phase_val;

	phase_val.sival_int = bpa_phase;

#ifdef BPA_DEBUG
	debug(1, "In bpalogin the httpd-id is %d\n", httpd_pid);
#endif

#ifdef QSDK/*  by Huangwenzhong, 12May14 */
	/* tell connModed that status had changed */	
	memset(cmdline, 0, sizeof(cmdline));
	sprintf(cmdline, UBUS_SET_STATUS_CMD_FORMAT, s.interface, phase_val.sival_int);
	system(cmdline);
#else	
	if (sigqueue((pid_t)httpd_pid, SIG_PHASE, phase_val) == -1)
		debug(1, "Send phase error");
#endif

	return 0;
}

void new_phase(int phase)
{
	if (new_phase_hook)
		(*new_phase_hook)(phase);

	return;
}

int closesocket(int s)
{
    return close(s);
}

void socketerror(struct session *s, const char * str)
{
    char buf[200];
    sprintf(buf,"%.100s - %.80s",str,strerror(errno));
    s->noncritical(buf);
}
