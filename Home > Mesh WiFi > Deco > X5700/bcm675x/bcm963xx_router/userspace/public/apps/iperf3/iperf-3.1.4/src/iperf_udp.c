/*
 * iperf, Copyright (c) 2014, 2016, The Regents of the University of
 * California, through Lawrence Berkeley National Laboratory (subject
 * to receipt of any required approvals from the U.S. Dept. of
 * Energy).  All rights reserved.
 *
 * If you have questions about your rights to use or distribute this
 * software, please contact Berkeley Lab's Technology Transfer
 * Department at TTD@lbl.gov.
 *
 * NOTICE.  This software is owned by the U.S. Department of Energy.
 * As such, the U.S. Government has been granted for itself and others
 * acting on its behalf a paid-up, nonexclusive, irrevocable,
 * worldwide license in the Software to reproduce, prepare derivative
 * works, and perform publicly and display publicly.  Beginning five
 * (5) years after the date permission to assert copyright is obtained
 * from the U.S. Department of Energy, and subject to any subsequent
 * five (5) year renewals, the U.S. Government is granted for itself
 * and others acting on its behalf a paid-up, nonexclusive,
 * irrevocable, worldwide license in the Software to reproduce,
 * prepare derivative works, distribute copies to the public, perform
 * publicly and display publicly, and to permit others to do so.
 *
 * This code is distributed under a BSD style license, see the LICENSE
 * file for complete information.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <sys/time.h>
#include <sys/select.h>

#include "iperf.h"
#include "iperf_api.h"
#include "iperf_util.h"
#include "iperf_udp.h"
#include "timer.h"
#include "net.h"
#include "portable_endian.h"

#include "iperf_config.h"
#include <netinet/in.h>
#include <netdb.h>


#ifdef CONFIG_BCM_SPDTEST
#include "spdt_api.h"
#endif

/* iperf_udp_recv
 *
 * receives the data for UDP
 */
int
iperf_udp_recv(struct iperf_stream *sp)
{
    uint32_t  sec, usec;
    uint64_t  pcount;
    int       r;
    int       size = sp->settings->blksize;
    double    transit = 0, d = 0;
    struct timeval sent_time, arrival_time;

    r = Nread(sp->socket, sp->buffer, size, Pudp);

    /*
     * If we got an error in the read, or if we didn't read anything
     * because the underlying read(2) got a EAGAIN, then skip packet
     * processing.
     */
    if (r <= 0)
        return r;

    sp->result->bytes_received += r;
    sp->result->bytes_received_this_interval += r;

    if (sp->test->udp_counters_64bit) {
	memcpy(&sec, sp->buffer, sizeof(sec));
	memcpy(&usec, sp->buffer+4, sizeof(usec));
	memcpy(&pcount, sp->buffer+8, sizeof(pcount));
	sec = ntohl(sec);
	usec = ntohl(usec);
	pcount = be64toh(pcount);
	sent_time.tv_sec = sec;
	sent_time.tv_usec = usec;
    }
    else {
	uint32_t pc;
	memcpy(&sec, sp->buffer, sizeof(sec));
	memcpy(&usec, sp->buffer+4, sizeof(usec));
	memcpy(&pc, sp->buffer+8, sizeof(pc));
	sec = ntohl(sec);
	usec = ntohl(usec);
	pcount = ntohl(pc);
	sent_time.tv_sec = sec;
	sent_time.tv_usec = usec;
    }

    /* Out of order packets */
    if (pcount >= sp->packet_count + 1) {
        if (pcount > sp->packet_count + 1) {
            sp->cnt_error += (pcount - 1) - sp->packet_count;
        }
        sp->packet_count = pcount;
    } else {
        sp->outoforder_packets++;
	iperf_err(sp->test, "OUT OF ORDER - incoming packet = %zu and received packet = %d AND SP = %d", pcount, (unsigned int)sp->packet_count, sp->socket);
    }

    /* jitter measurement */
    gettimeofday(&arrival_time, NULL);

    transit = timeval_diff(&sent_time, &arrival_time);
    d = transit - sp->prev_transit;
    if (d < 0)
        d = -d;
    sp->prev_transit = transit;
    // XXX: This is NOT the way to calculate jitter
    //      J = |(R1 - S1) - (R0 - S0)| [/ number of packets, for average]
    sp->jitter += (d - sp->jitter) / 16.0;

    if (sp->test->debug) {
	fprintf(stderr, "packet_count %d\n", sp->packet_count);
    }

    return r;
}


/* iperf_udp_send
 *
 * sends the data for UDP
 */
int
iperf_udp_send(struct iperf_stream *sp)
{
    int r;
    int       size = sp->settings->blksize;
    struct timeval before;

    gettimeofday(&before, 0);

    ++sp->packet_count;

    if (sp->test->udp_counters_64bit) {

	uint32_t  sec, usec;
	uint64_t  pcount;

	sec = htonl(before.tv_sec);
	usec = htonl(before.tv_usec);
	pcount = htobe64(sp->packet_count);
	
	memcpy(sp->buffer, &sec, sizeof(sec));
	memcpy(sp->buffer+4, &usec, sizeof(usec));
	memcpy(sp->buffer+8, &pcount, sizeof(pcount));
	
    }
    else {

	uint32_t  sec, usec, pcount;

	sec = htonl(before.tv_sec);
	usec = htonl(before.tv_usec);
	pcount = htonl(sp->packet_count);
	
	memcpy(sp->buffer, &sec, sizeof(sec));
	memcpy(sp->buffer+4, &usec, sizeof(usec));
	memcpy(sp->buffer+8, &pcount, sizeof(pcount));
	
    }

    r = Nwrite(sp->socket, sp->buffer, size, Pudp);

    if (r < 0)
	return r;

    sp->result->bytes_sent += r;
    sp->result->bytes_sent_this_interval += r;

    return r;
}


/**************************************************************************/

/*
 * The following functions all have to do with managing UDP data sockets.
 * UDP of course is connectionless, so there isn't really a concept of
 * setting up a connection, although connect(2) can (and is) used to
 * bind the remote end of sockets.  We need to simulate some of the
 * connection management that is built-in to TCP so that each side of the
 * connection knows about each other before the real data transfers begin.
 */

/*
 * iperf_udp_accept
 *
 * Accepts a new UDP "connection"
 */
int
iperf_udp_accept(struct iperf_test *test)
{
    struct sockaddr_storage sa_peer;
    int       buf;
    socklen_t len;
    int       sz, s;

    /*
     * Get the current outstanding socket.  This socket will be used to handle
     * data transfers and a new "listening" socket will be created.
     */
    s = test->prot_listener;

    /*
     * Grab the UDP packet sent by the client.  From that we can extract the
     * client's address, and then use that information to bind the remote side
     * of the socket to the client.
     */
    len = sizeof(sa_peer);
    if ((sz = recvfrom(test->prot_listener, &buf, sizeof(buf), 0, (struct sockaddr *) &sa_peer, &len)) < 0) {
        i_errno = IESTREAMACCEPT;
        return -1;
    }

    if (connect(s, (struct sockaddr *) &sa_peer, len) < 0) {
        i_errno = IESTREAMACCEPT;
        return -1;
    }

    /*
     * Set socket buffer size if requested.  Do this for both sending and
     * receiving so that we can cover both normal and --reverse operation.
     */
    int opt;
    if ((opt = test->settings->socket_bufsize)) {
        if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt)) < 0) {
            i_errno = IESETBUF;
            return -1;
        }
        if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt)) < 0) {
            i_errno = IESETBUF;
            return -1;
        }
    }

#if defined(HAVE_SO_MAX_PACING_RATE)
    /* If socket pacing is available and not disabled, try it. */
    if (! test->no_fq_socket_pacing) {
	/* Convert bits per second to bytes per second */
	unsigned int rate = test->settings->rate / 8;
	if (rate > 0) {
	    if (test->debug) {
		printf("Setting fair-queue socket pacing to %u\n", rate);
	    }
	    if (setsockopt(s, SOL_SOCKET, SO_MAX_PACING_RATE, &rate, sizeof(rate)) < 0) {
		warning("Unable to set socket pacing, using application pacing instead");
		test->no_fq_socket_pacing = 1;
	    }
	}
    }
#endif /* HAVE_SO_MAX_PACING_RATE */

    /*
     * Create a new "listening" socket to replace the one we were using before.
     */
    test->prot_listener = netannounce(test->settings->domain, Pudp, test->bind_address, test->server_port);
    if (test->prot_listener < 0) {
        i_errno = IESTREAMLISTEN;
        return -1;
    }

    FD_SET(test->prot_listener, &test->read_set);
    test->max_fd = (test->max_fd < test->prot_listener) ? test->prot_listener : test->max_fd;

    /* Let the client know we're ready "accept" another UDP "stream" */
    buf = 987654321;		/* any content will work here */
    if (write(s, &buf, sizeof(buf)) < 0) {
        i_errno = IESTREAMWRITE;
        return -1;
    }

    return s;
}


/*
 * iperf_udp_listen
 *
 * Start up a listener for UDP stream connections.  Unlike for TCP,
 * there is no listen(2) for UDP.  This socket will however accept
 * a UDP datagram from a client (indicating the client's presence).
 */
int
iperf_udp_listen(struct iperf_test *test)
{
    int s;

    if ((s = netannounce(test->settings->domain, Pudp, test->bind_address, test->server_port)) < 0) {
        i_errno = IESTREAMLISTEN;
        return -1;
    }

    /*
     * The caller will put this value into test->prot_listener.
     */
    return s;
}


/*
 * iperf_udp_connect
 *
 * "Connect" to a UDP stream listener.
 */
int
iperf_udp_connect(struct iperf_test *test)
{
    int s, buf, sz;
#ifdef SO_RCVTIMEO
    struct timeval tv;
#endif

    /* Create and bind our local socket. */
    if ((s = netdial(test->settings->domain, Pudp, test->bind_address, test->bind_port, test->server_hostname, test->server_port)) < 0) {
        i_errno = IESTREAMCONNECT;
        return -1;
    }

    /*
     * Set socket buffer size if requested.  Do this for both sending and
     * receiving so that we can cover both normal and --reverse operation.
     */
    int opt;
    if ((opt = test->settings->socket_bufsize)) {
        if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(opt)) < 0) {
            i_errno = IESETBUF;
            return -1;
        }
        if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt)) < 0) {
            i_errno = IESETBUF;
            return -1;
        }
    }

#if defined(HAVE_SO_MAX_PACING_RATE)
    /* If socket pacing is available and not disabled, try it. */
    if (! test->no_fq_socket_pacing) {
	/* Convert bits per second to bytes per second */
	unsigned int rate = test->settings->rate / 8;
	if (rate > 0) {
	    if (test->debug) {
		printf("Setting fair-queue socket pacing to %u\n", rate);
	    }
	    if (setsockopt(s, SOL_SOCKET, SO_MAX_PACING_RATE, &rate, sizeof(rate)) < 0) {
		warning("Unable to set socket pacing, using application pacing instead");
		test->no_fq_socket_pacing = 1;
	    }
	}
    }
#endif /* HAVE_SO_MAX_PACING_RATE */

#ifdef SO_RCVTIMEO
    /* 30 sec timeout for a case when there is a network problem. */
    tv.tv_sec = 30;
    tv.tv_usec = 0;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
#endif

    /*
     * Write a datagram to the UDP stream to let the server know we're here.
     * The server learns our address by obtaining its peer's address.
     */
    buf = 123456789;		/* this can be pretty much anything */
    if (write(s, &buf, sizeof(buf)) < 0) {
        // XXX: Should this be changed to IESTREAMCONNECT? 
        i_errno = IESTREAMWRITE;
        return -1;
    }

    /*
     * Wait until the server replies back to us.
     */
    if ((sz = recv(s, &buf, sizeof(buf), 0)) < 0) {
        i_errno = IESTREAMREAD;
        return -1;
    }

    return s;
}


/* iperf_udp_init
 *
 * initializer for UDP streams in TEST_START
 */
int
iperf_udp_init(struct iperf_test *test)
{
    return 0;
}

#ifdef CONFIG_BCM_SPDTEST
int 
iperf_udp_hwoffl_recv(struct iperf_stream *sp)
{
    return 0;
}

int
iperf_udp_hwoffl_send(struct iperf_stream *sp)
{
    return 0;
}

int
iperf_udp_hwoffl_connect(struct iperf_test *test)
{
    uint8_t hw_fd;
    spdt_conn_params_t params = {};
    struct addrinfo hints, *local_res, *server_res;
    char portstr[6];
    int rc, connected = 0;
    int buf;

    memset(&hints, 0, sizeof(hints));

    rc = spdt_init(SPDT_IPERF3_UDP, &hw_fd);
    if (rc)
    {
        printf("spdt_init failed\n");
        i_errno = IESTREAMCONNECT;
        return -1;  
    }

    memset(&params.local_addr, 0, sizeof(params.local_addr));

    if (test->bind_address) 
    {
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = test->settings->domain;
        hints.ai_socktype = SOCK_DGRAM;
        if (getaddrinfo(test->bind_address, NULL, &hints, &local_res) != 0) {
            i_errno = IESTREAMCONNECT;
            goto error;
        }
        /* convert to sockaddr_storage */

        memcpy(&params.local_addr, local_res->ai_addr, local_res->ai_addrlen);

        /*may free addrinfo now */
        freeaddrinfo(local_res);
    }

    /* get server's address */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = test->settings->domain;
    hints.ai_socktype = SOCK_DGRAM;
    snprintf(portstr, sizeof(portstr), "%d", test->server_port);
    if (getaddrinfo(test->server_hostname, portstr, &hints, &server_res) != 0) {
        spdt_uninit(hw_fd);
        i_errno = IESTREAMCONNECT;
        goto error;
    }

     /* convert to sockaddr_storage */
    memset(&params.server_addr, 0, sizeof(params.server_addr));
    memcpy(&params.server_addr, server_res->ai_addr, server_res->ai_addrlen);

    /*may free addrinfo now */
    freeaddrinfo(server_res);

    if (test->settings->tos)
       params.tos = test->settings->tos;

    /* try to connect */
    rc = spdt_connect(hw_fd, test->sender ? SPDT_DIR_TX: SPDT_DIR_RX, &params);
    if (rc)
    {
        printf("spdt_connect failed\n");
        i_errno = IESTREAMCONNECT;
        goto error;
    }
    connected = 1;

    if (!test->sender)
    {
        spdt_rx_params_t rx_params = {};

        rc = spdt_recv_start(hw_fd, &rx_params);
        if (rc)
        {
            printf("spdt_recv_start failed\n");
            i_errno = IESTREAMCONNECT;
            goto error;
        }    
    }

    /*
     * Write a datagram to the UDP stream to let the server know we're here.
     * The server learns our address by obtaining its peer's address.
     */
    buf = 123456789;		/* this can be pretty much anything */
    rc = spdt_oob_send(hw_fd, &buf, sizeof(buf));
    if (rc < 0)
    {
        printf("%s:%d Failed to send start indication to the server, rc = %d\n", __FUNCTION__, __LINE__, rc);
        i_errno = IESTREAMWRITE;
        goto error;
    }

    if (test->sender)
    {
        spdt_tx_params_t tx_params = {};

        tx_params.proto.udp.data_buf_len = test->settings->blksize;
        tx_params.proto.udp.total_bytes_to_send = test->settings->bytes;
        tx_params.proto.udp.kbps = (uint32_t)(test->settings->rate / 1000);
        rc = spdt_send_start(hw_fd, &tx_params);
        if (rc)
        {
            printf("spdt_send_start failed\n");
            i_errno = IESTREAMCONNECT;
            goto error;
        }    
    }

    return hw_fd;

error:
    if (connected)
        iperf_hw_disconnect_sock(test, hw_fd);
    spdt_uninit(hw_fd);
    return -1;
}
#endif

