#ifndef __UDT_C_H__
#define __UDT_C_H__

#ifndef WIN32
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
#else
   #ifdef __MINGW__
      #include <stdint.h>
      #include <ws2tcpip.h>
   #endif
   #include <windows.h>
#endif


//////////////////////////////////// error code ///////////////////////////////////
#define SUCCESS   0 
#define ECONNSETUP   1000 
#define ENOSERVER   1001 
#define ECONNREJ   1002 
#define ESOCKFAIL   1003 
#define ESECFAIL   1004 
#define ECONNFAIL   2000 
#define ECONNLOST   2001 
#define ENOCONN   2002 
#define ERESOURCE   3000 
#define ETHREAD   3001 
#define ENOBUF   3002 
#define EFILE   4000 
#define EINVRDOFF   4001 
#define ERDPERM   4002 
#define EINVWROFF   4003 
#define EWRPERM   4004 
#define EINVOP   5000 
#define EBOUNDSOCK   5001 
#define ECONNSOCK   5002 
#define EINVPARAM   5003 
#define EINVSOCK   5004 
#define EUNBOUNDSOCK   5005 
#define ENOLISTEN   5006 
#define ERDVNOSERV   5007 
#define ERDVUNBOUND   5008 
#define ESTREAMILL   5009 
#define EDGRAMILL   5010 
#define EDUPLISTEN   5011 
#define ELARGEMSG   5012 
#define EINVPOLLID   5013 
#define EASYNCFAIL   6000 
#define EASYNCSND   6001 
#define EASYNCRCV   6002 
#define ETIMEOUT   6003 
#define EPEERERR   7000 
#define EUNKNOWN   -1 
////////////////////////////////////////////////////////////////////////////////

//if compiling on VC6.0 or pre-WindowsXP systems
//use -DLEGACY_WIN32

//if compiling with MinGW, it only works on XP or above
//use -D_WIN32_WINNT=0x0501


#ifdef WIN32
   #ifndef __MINGW__
      // Explicitly define 32-bit and 64-bit numbers
      typedef __int32 int32_t;
      typedef __int64 int64_t;
      typedef unsigned __int32 uint32_t;
      #ifndef LEGACY_WIN32
         typedef unsigned __int64 uint64_t;
      #else
         // VC 6.0 does not support unsigned __int64: may cause potential problems.
         typedef __int64 uint64_t;
      #endif

      #ifdef UDT_EXPORTS
         #define UDT_API __declspec(dllexport)
      #else
         #define UDT_API
      #endif
   #else
      #define UDT_API
   #endif
#else
   #define UDT_API __attribute__ ((visibility("default")))
#endif

#define NO_BUSY_WAITING

#ifdef WIN32
   #ifndef __MINGW__
      typedef SOCKET SYSSOCKET;
   #else
      typedef int SYSSOCKET;
   #endif
#else
   typedef int SYSSOCKET;
#endif

typedef SYSSOCKET UDPSOCKET;
typedef int UDTSOCKET;

typedef enum 
{
   // this values are defined same as linux epoll.h
   // so that if system values are used by mistake, they should have the same effect
   UDT_EPOLL_IN = 0x1,
   UDT_EPOLL_OUT = 0x4,
   UDT_EPOLL_ERR = 0x8
}EPOLLOpt;

typedef enum{INIT = 1, OPENED, LISTENING, CONNECTING, CONNECTED, BROKEN, CLOSING, CLOSED, NONEXIST}UDTSTATUS ;

////////////////////////////////////////////////////////////////////////////////

typedef enum 
{
   UDT_MSS,             // the Maximum Transfer Unit
   UDT_SNDSYN,          // if sending is blocking
   UDT_RCVSYN,          // if receiving is blocking
   UDT_CC,              // custom congestion control algorithm
   UDT_FC,		// Flight flag size (window size)
   UDT_SNDBUF,          // maximum buffer in sending queue
   UDT_RCVBUF,          // UDT receiving buffer size
   UDT_LINGER,          // waiting for unsent data when closing
   UDP_SNDBUF,          // UDP sending buffer size
   UDP_RCVBUF,          // UDP receiving buffer size
   UDT_MAXMSG,          // maximum datagram message size
   UDT_MSGTTL,          // time-to-live of a datagram message
   UDT_RENDEZVOUS,      // rendezvous connection mode
   UDT_SNDTIMEO,        // send() timeout
   UDT_RCVTIMEO,        // recv() timeout
   UDT_REUSEADDR,	// reuse an existing port or create a new one
   UDT_MAXBW,		// maximum bandwidth (bytes per second) that the connection can use
   UDT_STATE,		// current socket state, see UDTSTATUS, read only
   UDT_EVENT,		// current avalable events associated with the socket
   UDT_SNDDATA,		// size of data in the sending buffer
   UDT_RCVDATA		// size of data available for recv
}UDTOpt;

////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
   // global measurements
   int64_t msTimeStamp;                 // time since the UDT entity is started, in milliseconds
   int64_t pktSentTotal;                // total number of sent data packets, including retransmissions
   int64_t pktRecvTotal;                // total number of received packets
   int pktSndLossTotal;                 // total number of lost packets (sender side)
   int pktRcvLossTotal;                 // total number of lost packets (receiver side)
   int pktRetransTotal;                 // total number of retransmitted packets
   int pktSentACKTotal;                 // total number of sent ACK packets
   int pktRecvACKTotal;                 // total number of received ACK packets
   int pktSentNAKTotal;                 // total number of sent NAK packets
   int pktRecvNAKTotal;                 // total number of received NAK packets
   int64_t usSndDurationTotal;		// total time duration when UDT is sending data (idle time exclusive)

   // local measurements
   int64_t pktSent;                     // number of sent data packets, including retransmissions
   int64_t pktRecv;                     // number of received packets
   int pktSndLoss;                      // number of lost packets (sender side)
   int pktRcvLoss;                      // number of lost packets (receiver side)
   int pktRetrans;                      // number of retransmitted packets
   int pktSentACK;                      // number of sent ACK packets
   int pktRecvACK;                      // number of received ACK packets
   int pktSentNAK;                      // number of sent NAK packets
   int pktRecvNAK;                      // number of received NAK packets
   double mbpsSendRate;                 // sending rate in Mb/s
   double mbpsRecvRate;                 // receiving rate in Mb/s
   int64_t usSndDuration;		// busy sending time (i.e., idle time exclusive)

   // instant measurements
   double usPktSndPeriod;               // packet sending period, in microseconds
   int pktFlowWindow;                   // flow window size, in number of packets
   int pktCongestionWindow;             // congestion window size, in number of packets
   int pktFlightSize;                   // number of packets on flight
   double msRTT;                        // RTT, in milliseconds
   double mbpsBandwidth;                // estimated bandwidth, in Mb/s
   int byteAvailSndBuf;                 // available UDT sender buffer size
   int byteAvailRcvBuf;                 // available UDT receiver buffer size
}CPerfMon;


typedef UDTOpt SOCKOPT;
typedef CPerfMon TRACEINFO;


UDT_API int udt_startup();
UDT_API int udt_cleanup();
UDT_API UDTSOCKET udt_socket(int af, int type, int protocol);
UDT_API int udt_bind(UDTSOCKET u, const struct sockaddr* name, int namelen);
UDT_API int udt_bind2(UDTSOCKET u, UDPSOCKET udpsock);
UDT_API int udt_listen(UDTSOCKET u, int backlog);
UDT_API UDTSOCKET udt_accept(UDTSOCKET u, struct sockaddr* addr, int* addrlen);
UDT_API int udt_connect(UDTSOCKET u, const struct sockaddr* name, int namelen);
UDT_API int udt_close(UDTSOCKET u);
UDT_API int udt_getpeername(UDTSOCKET u, struct sockaddr* name, int* namelen);
UDT_API int udt_getsockname(UDTSOCKET u, struct sockaddr* name, int* namelen);
UDT_API int udt_getsockopt(UDTSOCKET u, int level, SOCKOPT optname, void* optval, int* optlen);
UDT_API int udt_setsockopt(UDTSOCKET u, int level, SOCKOPT optname, const void* optval, int optlen);
UDT_API int udt_send(UDTSOCKET u, const char* buf, int len, int flags);
UDT_API int udt_recv(UDTSOCKET u, char* buf, int len, int flags);
UDT_API int udt_sendmsg(UDTSOCKET u, const char* buf, int len, int ttl, int inorder);
UDT_API int udt_recvmsg(UDTSOCKET u, char* buf, int len);
UDT_API int udt_epoll_create();
UDT_API int udt_epoll_add_usock(int eid, UDTSOCKET u, const int* events);
UDT_API int udt_epoll_add_ssock(int eid, SYSSOCKET s, const int* events);
UDT_API int udt_epoll_remove_usock(int eid, UDTSOCKET u);
UDT_API int udt_epoll_remove_ssock(int eid, SYSSOCKET s);
UDT_API int udt_epoll_wait2(int eid,
	   	UDTSOCKET* readfds, int* rnum, UDTSOCKET* writefds,	int* wnum,
	   	int64_t msTimeOut,
	   	SYSSOCKET* lrfds, int* lrnum,	SYSSOCKET* lwfds, int* lwnum);
UDT_API int udt_epoll_release(int eid);
UDT_API int udt_getlasterror_code();
UDT_API const char* udt_getlasterror_desc();
UDT_API int udt_perfmon(UDTSOCKET u, TRACEINFO* perf, int clear);
UDT_API UDTSTATUS udt_getsockstate(UDTSOCKET u);

#endif
