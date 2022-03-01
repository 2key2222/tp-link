/******************************************************************************
 *
 * Copyright (c) 2015 TP-LINK Technologies CO.,LTD.
 * All rights reserved.
 *
 * FILE NAME  :   stun_async.c
 * VERSION    :   1.0
 * DESCRIPTION:   asynchronous APIs of libstun
 *
 * AUTHOR     :   GeGuipeng <geguipeng@tp-link.net>
 * CREATE DATE:   07/27/2015
 *
 * HISTORY    :
 * 01   07/27/2015  GeGuipeng create
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#ifndef WIN32
#include <sys/select.h>
#endif
#include <event2/util.h>
#include "platform.h"
#include "stun.h"

FILE* g_dbgfile = NULL;
const char* g_module_name = "libstun";


// gnt means get_nat_type
// ------------------------------------------------------------------------
#ifndef GNT_TASK_MAX_CNT
#define GNT_TASK_MAX_CNT		20
#endif
#define GNT_SERVERNAME_MAX_LEN	128

struct gnt_task{
	char					stun_server[GNT_SERVERNAME_MAX_LEN];
	int						verbose;
	time_t					expire_time;// when this task expires
	STUN_get_nat_type_cb	gnt_cb;
	void*					gnt_cb_arg;
};

// isempty:	q_head ==  q_tail
// isfull:	q_head == (q_tail+1) % q_len 
// enqueue:	q_tail =  (q_tail+1) % q_len
// dequeue:	q_head =  (q_head+1) % q_len
struct gnt_task_queue{
	struct gnt_task		 tasks[GNT_TASK_MAX_CNT];
	int					 q_head;
	int					 q_tail;
};

static MUTEX_DEFINIT			(gnt_lock);
static evutil_socket_t			 gnt_notifier = -1;// the one who send notification
static evutil_socket_t			 gnt_notifiee = -1;// the one who recv notification
static struct gnt_task_queue	 gnt_task_queue;
static int						 gnt_async_enabled = 0;


// sockfd should be non-blocking
static int socket_is_recv_open(evutil_socket_t sockfd)
{
	char ch;
	int nrecv;

	nrecv = recv(sockfd, &ch, 1, 0);
	if( nrecv == 0 ){
		// socket closed
		return 0;
	}
	else if( nrecv < 0 ){
		// error, caller should check errno
		return -1;
	}
	else{
		// socket not closed, return the char read
		return (int)ch;
	}
}

// sockfd should be non-blocking
static void socket_empty_recv_buf(evutil_socket_t sockfd)
{
	char buf[32];

	if( sockfd == -1 ){
		return ;
	}

	while( recv(sockfd, buf, sizeof(buf), 0) > 0 ){
		;
	}

	return ;
}

static int STUN_gnt_task_enqueue(char *servername, int verbose, 
					int timeout, STUN_get_nat_type_cb cb, void *arg)
{
	int q_tail, q_head, q_next;
	struct gnt_task *task;

	if( !servername || !servername[0] 
		|| strlen(servername) >= GNT_SERVERNAME_MAX_LEN 
			){
		return -1;
	}

	MUTEX_LOCK(gnt_lock);
	q_tail = gnt_task_queue.q_tail;
	q_head = gnt_task_queue.q_head;
	q_next = (q_tail + 1) % GNT_TASK_MAX_CNT;
	if( q_next == q_head ){
		// queue full
		MUTEX_UNLOCK(gnt_lock);
		return -1;
	}

	task = &gnt_task_queue.tasks[q_tail];
	strcpy(task->stun_server, servername);//len has been checked, so use strcpy instead of strncpy
	task->verbose = verbose;
	task->expire_time = time(NULL) + timeout;
	task->gnt_cb = cb;
	task->gnt_cb_arg = arg;
	gnt_task_queue.q_tail = q_next;
	MUTEX_UNLOCK(gnt_lock);

	// notify that task submitted
	send(gnt_notifier, "#", 1, 0);//notify gnt_notifiee, by making the sockfd readable

	return 0;
}

static struct gnt_task *STUN_gnt_task_dequeue()
{
	struct gnt_task *task = NULL;

	MUTEX_LOCK(gnt_lock);
	if( gnt_task_queue.q_head != gnt_task_queue.q_tail ){
		// queue not empty
		task = &gnt_task_queue.tasks[gnt_task_queue.q_head];
		gnt_task_queue.q_head = (gnt_task_queue.q_head + 1) % GNT_TASK_MAX_CNT;
	}
	MUTEX_UNLOCK(gnt_lock);

	return task;
}

static THREAD_RETURN STUN_gnt_thread(void* arg)
{
	struct gnt_task *task;
	int exit_code = 0;

#ifndef WIN32
	pthread_detach(pthread_self());
#endif

	while(1){
		int recvopen;
		
		socket_empty_recv_buf(gnt_notifiee);
		recvopen = socket_is_recv_open(gnt_notifiee);
		if( !recvopen 
			|| (recvopen < 0 && !sock_func_will_block(recvopen)) 
				){
			goto out;
		}

		task = STUN_gnt_task_dequeue();
		if( task ){
			int nat_type;

			nat_type = STUN_get_nat_type(task->stun_server, task->verbose);
			if( difftime(time(NULL), task->expire_time) < 0 
				&& task->gnt_cb 
					){
				task->gnt_cb(nat_type, task->gnt_cb_arg);
			}
		}// task != NULL
		else{
			// wait for notification about task-submitted or thread-to-exit
			fd_set rset;
			int nselect;
			struct timeval tv = {1, 1};

			FD_ZERO(&rset);
			FD_SET(gnt_notifiee, &rset);
			nselect = select(gnt_notifiee+1, &rset, NULL, NULL, &tv);
			if( nselect < 0 && errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR ){
				PRINTF("select error. errno: %d\n", sock_errno);
				exit_code = -1;
				goto out;
			}
		}// task == NULL
	}// while(1) loop

out:
	evutil_closesocket(gnt_notifiee);
	gnt_notifiee = -1;
	gnt_async_enabled = 0;

	PRINTF("STUN_gnt_thread exit. exit_code: %d\n", exit_code);
	exit_thread(exit_code);
}

static int STUN_init_gnt_async()
{
#ifdef WIN32
	static volatile long init_once = 0, init_done = 0;
#endif
	evutil_socket_t socks[2];
	pthread_t tid;

	if( gnt_async_enabled ){
		// already init
		return -1;
	}

#ifdef WIN32
	if( _InterlockedOr(&init_once, 1) == 0 ){
		WSADATA wsaData;

		WSAStartup(MAKEWORD(2, 2), &wsaData);
		MUTEX_INIT(gnt_lock);
		init_done = 1;
	}
	while( !init_done ){
		msleep(50);
	}
#endif

	MUTEX_LOCK(gnt_lock);
	if( gnt_async_enabled ){
		MUTEX_UNLOCK(gnt_lock);
		return 0;
	}

	// create a pair of socket, for event notification
	socks[0] = socks[1] = -1;
	if( evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, socks) < 0 ){
		PRINTF("socketpair fail. errno: %d\n", sock_errno);
		goto FAILED;
	}

	evutil_make_socket_nonblocking(socks[0]);
	gnt_notifier = socks[0];// for sending notification

	evutil_make_socket_nonblocking(socks[1]);
	gnt_notifiee = socks[1];// for recving notification

	// init gnt queue
	gnt_task_queue.q_head = 0;
	gnt_task_queue.q_tail = 0;

	// create worker thread
	if( create_thread(tid, STUN_gnt_thread, NULL) ){
		PRINTF("create STUN_gnt_thread fail. errno: %d\n", sys_errno);
		goto FAILED;
	}
	PRINTF("STUN_gnt_thread start\n");
#ifdef WIN32
	CloseHandle(tid);
#endif

	// init success
	gnt_async_enabled = 1;
	MUTEX_UNLOCK(gnt_lock);
	PRINTF("STUN async gnt init OK\n");
	return 0;

FAILED:
	if( socks[0] != -1 ){
		evutil_closesocket(socks[0]);
	}
	if( socks[1] != -1 ){
		evutil_closesocket(socks[1]);
	}
	gnt_notifier = -1;
	gnt_notifiee = -1;
	PRINTF("STUN async gnt init fail\n");
	MUTEX_UNLOCK(gnt_lock);
	return -1;
}

static int STUN_clean_gnt_async()
{
	if( !gnt_async_enabled ){
		return -1;
	}

	// cleanup resources in STUN_gnt_thread, so we don't have to wait it to stop
	evutil_shutdown_socket_both(gnt_notifier);
	gnt_notifier = -1;
	while( gnt_async_enabled ){
		msleep(50);
	}
	return 0;
}

int STUN_get_nat_type_async(char *servername, int verbose, 
					int timeout, STUN_get_nat_type_cb cb, void *arg)
{
	if( !gnt_async_enabled && (STUN_init_gnt_async() < 0) ){
		return -1;
	}

	PRINTF("request [%s] for NAT type\n", servername);
	return STUN_gnt_task_enqueue(servername, verbose, timeout, cb, arg);
}
// ========================================================================


int STUN_init_async()
{
	// init all STUN async module. Currently, only gnt module.
	return STUN_init_gnt_async();
}

int STUN_clean_async()
{
	// cleanup all STUN async module
	return STUN_clean_gnt_async();
}
