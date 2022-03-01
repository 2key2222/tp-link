/*****************************************************************************
Copyright? 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
File name: stunone.h
Description: stunclient. libstun internal implementation.
Author: AaronChen
Version: in code
Date: continuing
History: in svn
*****************************************************************************/

#ifndef STUNONE_H
#define STUNONE_H
#include <time.h>

// if you change this version, change in makefile too
#define STUN_VERSION "0.97"
#define TRUE 1
#define FALSE 0

#ifdef __MACH__
//typedef int socklen_t;
#endif

#include <errno.h>

#ifdef WIN32

#include <winsock2.h>

typedef int socklen_t;
typedef SOCKET Socket;

#define _EWOULDBLOCK             WSAEWOULDBLOCK
#define _EINPROGRESS             WSAEINPROGRESS
#define _EALREADY                WSAEALREADY
#define _ENOTSOCK                WSAENOTSOCK
#define _EDESTADDRREQ            WSAEDESTADDRREQ
#define _EMSGSIZE                WSAEMSGSIZE
#define _EPROTOTYPE              WSAEPROTOTYPE
#define _ENOPROTOOPT             WSAENOPROTOOPT
#define _EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define _ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define _EOPNOTSUPP              WSAEOPNOTSUPP
#define _EPFNOSUPPORT            WSAEPFNOSUPPORT
#define _EAFNOSUPPORT            WSAEAFNOSUPPORT
#define _EADDRINUSE              WSAEADDRINUSE
#define _EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define _ENETDOWN                WSAENETDOWN
#define _ENETUNREACH             WSAENETUNREACH
#define _ENETRESET               WSAENETRESET
#define _ECONNABORTED            WSAECONNABORTED
#define _ECONNRESET              WSAECONNRESET
#define _ENOBUFS                 WSAENOBUFS
#define _EISCONN                 WSAEISCONN
#define _ENOTCONN                WSAENOTCONN
#define _ESHUTDOWN               WSAESHUTDOWN
#define _ETOOMANYREFS            WSAETOOMANYREFS
#define _ETIMEDOUT               WSAETIMEDOUT
#define _ECONNREFUSED            WSAECONNREFUSED
#define _ELOOP                   WSAELOOP
#define _EHOSTDOWN               WSAEHOSTDOWN
#define _EHOSTUNREACH            WSAEHOSTUNREACH
#define _EPROCLIM                WSAEPROCLIM
#define _EUSERS                  WSAEUSERS
#define _EDQUOT                  WSAEDQUOT
#define _ESTALE                  WSAESTALE
#define _EREMOTE                 WSAEREMOTE

typedef LONGLONG Int64;
inline int getErrno() { return WSAGetLastError(); }

#else

typedef int Socket;
static const Socket INVALID_SOCKET = -1;
static const int SOCKET_ERROR = -1;

#define _EWOULDBLOCK             EWOULDBLOCK
#define _EINPROGRESS             EINPROGRESS
#define _EALREADY                EALREADY
#define _ENOTSOCK                ENOTSOCK
#define _EDESTADDRREQ            EDESTADDRREQ
#define _EMSGSIZE                EMSGSIZE
#define _EPROTOTYPE              EPROTOTYPE
#define _ENOPROTOOPT             ENOPROTOOPT
#define _EPROTONOSUPPORT         EPROTONOSUPPORT
#define _ESOCKTNOSUPPORT         ESOCKTNOSUPPORT
#define _EOPNOTSUPP              EOPNOTSUPP
#define _EPFNOSUPPORT            EPFNOSUPPORT
#define _EAFNOSUPPORT            EAFNOSUPPORT
#define _EADDRINUSE              EADDRINUSE
#define _EADDRNOTAVAIL           EADDRNOTAVAIL
#define _ENETDOWN                ENETDOWN
#define _ENETUNREACH             ENETUNREACH
#define _ENETRESET               ENETRESET
#define _ECONNABORTED            ECONNABORTED
#define _ECONNRESET              ECONNRESET
#define _ENOBUFS                 ENOBUFS
#define _EISCONN                 EISCONN
#define _ENOTCONN                ENOTCONN
#define _ESHUTDOWN               ESHUTDOWN
#define _ETOOMANYREFS            ETOOMANYREFS
#define _ETIMEDOUT               ETIMEDOUT
#define _ECONNREFUSED            ECONNREFUSED
#define _ELOOP                   ELOOP
#define _EHOSTDOWN               EHOSTDOWN
#define _EHOSTUNREACH            EHOSTUNREACH
#define _EPROCLIM                EPROCLIM
#define _EUSERS                  EUSERS
#define _EDQUOT                  EDQUOT
#define _ESTALE                  ESTALE
#define _EREMOTE                 EREMOTE

inline int closesocket ( Socket fd ) { return close ( fd ); };

inline int getErrno() { return errno; }

#define WSANOTINITIALISED  EPROTONOSUPPORT

#endif

/// Open a UDP socket to receive on the given port - if port is 0, pick a a
/// port, if interfaceIp!=0 then use ONLY the interface specified instead of
/// all of them
Socket
openPort ( unsigned short port, unsigned int interfaceIp, int mustsuccess,
		   int verbose );


/// recive a UDP message
int
getMessage ( Socket fd, char *buf, int *len,
			 unsigned int *srcIp, unsigned short *srcPort,
			 int verbose );


/// send a UDP message
int
sendMessage ( Socket fd, char *msg, int len,
			  unsigned int dstIp, unsigned short dstPort,
			  int verbose );


/// set up network - does nothing in unix but needed for windows
int
initNetwork();



#define STUN_MAX_STRING 256
#define STUN_MAX_UNKNOWN_ATTRIBUTES 8
#define STUN_MAX_MESSAGE_SIZE 2048

#define STUN_PORT 3478
#define FEEDBACK_PORT 8089

// define some basic types
typedef unsigned char  UInt8;
typedef unsigned short UInt16;
typedef unsigned int   UInt32;
#if defined( WIN32 )
typedef unsigned __int64 UInt64;
#else
typedef unsigned long long UInt64;
#endif
typedef struct { unsigned char octet[16]; }  UInt128;

/// define a structure to hold a stun address
const UInt8  IPv4Family = 0x01;
const UInt8  IPv6Family = 0x02;

// define  flags
const UInt32 ChangeIpFlag   = 0x04;
const UInt32 ChangePortFlag = 0x02;

// define  stun attribute
const UInt16 MappedAddress    = 0x0001;
const UInt16 ResponseAddress  = 0x0002;
const UInt16 ChangeRequest    = 0x0003;
const UInt16 SourceAddress    = 0x0004;
const UInt16 ChangedAddress   = 0x0005;
const UInt16 Username         = 0x0006;
const UInt16 Password         = 0x0007;
const UInt16 MessageIntegrity = 0x0008;
const UInt16 ErrorCode        = 0x0009;
const UInt16 UnknownAttribute = 0x000A;
const UInt16 ReflectedFrom    = 0x000B;
const UInt16 XorMappedAddress = 0x8020;
const UInt16 XorOnly          = 0x0021;
const UInt16 ServerName       = 0x8022;
const UInt16 SecondaryAddress = 0x8050; // Non standard extention

// define types for a stun message
const UInt16 BindRequestMsg               = 0x0001;
const UInt16 BindResponseMsg              = 0x0101;
const UInt16 BindErrorResponseMsg         = 0x0111;
const UInt16 SharedSecretRequestMsg       = 0x0002;
const UInt16 SharedSecretResponseMsg      = 0x0102;
const UInt16 SharedSecretErrorResponseMsg = 0x0112;

typedef struct
{
	UInt16 msgType;
	UInt16 msgLength;
	UInt128 id;
} StunMsgHdr;


typedef struct
{
	UInt16 type;
	UInt16 length;
} StunAtrHdr;

typedef struct
{
	UInt16 port;
	UInt32 addr;
} StunAddress4;

typedef struct
{
	UInt8 pad;
	UInt8 family;
	StunAddress4 ipv4;
} StunAtrAddress4;

typedef struct
{
	UInt32 value;
} StunAtrChangeRequest;

typedef struct
{
	UInt16 pad; // all 0
	UInt8 errorClass;
	UInt8 number;
	char reason[STUN_MAX_STRING];
	UInt16 sizeReason;
} StunAtrError;

typedef struct
{
	UInt16 attrType[STUN_MAX_UNKNOWN_ATTRIBUTES];
	UInt16 numAttributes;
} StunAtrUnknown;

typedef struct
{
	char value[STUN_MAX_STRING];
	UInt16 sizeValue;
} StunAtrString;

typedef struct
{
	char hash[20];
} StunAtrIntegrity;

typedef enum
{
	HmacUnkown = 0,
	HmacOK,
	HmacBadUserName,
	HmacUnkownUserName,
	HmacFailed,
} StunHmacStatus;

typedef struct
{
	StunMsgHdr msgHdr;

	int hasMappedAddress;
	StunAtrAddress4  mappedAddress;

	int hasResponseAddress;
	StunAtrAddress4  responseAddress;

	int hasChangeRequest;
	StunAtrChangeRequest changeRequest;

	int hasSourceAddress;
	StunAtrAddress4 sourceAddress;

	int hasChangedAddress;
	StunAtrAddress4 changedAddress;

	int hasUsername;
	StunAtrString username;

	int hasPassword;
	StunAtrString password;

	int hasMessageIntegrity;
	StunAtrIntegrity messageIntegrity;

	int hasErrorCode;
	StunAtrError errorCode;

	int hasUnknownAttributes;
	StunAtrUnknown unknownAttributes;

	int hasReflectedFrom;
	StunAtrAddress4 reflectedFrom;

	int hasXorMappedAddress;
	StunAtrAddress4  xorMappedAddress;

	int xorOnly;

	int hasServerName;
	StunAtrString serverName;

	int hasSecondaryAddress;
	StunAtrAddress4 secondaryAddress;
} StunMessage;


// Define enum with different types of NAT
typedef enum
{
	StunTypeUnknown = 0,
	StunTypeFailure,
	StunTypeOpen,
	StunTypeBlocked,

	StunTypeIndependentFilter,
	StunTypeDependentFilter,
	StunTypePortDependedFilter,
	StunTypeDependentMapping,

	//StunTypeConeNat,
	//StunTypeRestrictedNat,
	//StunTypePortRestrictedNat,
	//StunTypeSymNat,

	StunTypeFirewall,
} NatType;

#ifdef WIN32
typedef SOCKET Socket;
#else
typedef int Socket;
#endif

#define MAX_MEDIA_RELAYS 500
#define MAX_RTP_MSG_SIZE 1500
#define MEDIA_RELAY_TIMEOUT 3*60

typedef struct
{
	int relayPort;       // media relay port
	int fd;              // media relay file descriptor
	StunAddress4 destination; // NAT IP:port
	time_t expireTime;      // if no activity after time, close the socket
} StunMediaRelay;

typedef struct
{
	StunAddress4 myAddr;
	StunAddress4 altAddr;
	Socket myFd;
	Socket altPortFd;
	Socket altIpFd;
	Socket altIpPortFd;
	int relay; // TRUE if media relaying is to be done
	StunMediaRelay relays[MAX_MEDIA_RELAYS];
} StunServerInfo;

int
stunParseMessage ( char *buf,
				   unsigned int bufLen,
				   StunMessage &message,
				   int verbose );

void
stunBuildReqSimple ( StunMessage *msg,
					 const StunAtrString &username,
					 int changePort, int changeIp, unsigned int id = 0 );

unsigned int
stunEncodeMessage ( const StunMessage &message,
					char *buf,
					unsigned int bufLen,
					const StunAtrString &password,
					int verbose );

void
stunCreateUserName ( const StunAddress4 &addr, StunAtrString *username );

void
stunGetUserNameAndPassword (  const StunAddress4 &dest,
							  StunAtrString *username,
							  StunAtrString *password );

void
stunCreatePassword ( const StunAtrString &username, StunAtrString *password );

int
stunRand();

UInt64
stunGetSystemTimeSecs();

/// find the IP address of a the specified stun server - return FALSE is fails parse
int
stunParseServerName ( char *serverName, StunAddress4 &stunServerAddr );

int
stunParseHostName ( char *peerName,
					UInt32 &ip,
					UInt16 &portVal,
					UInt16 defaultPort );

/// return TRUE if all is OK
/// Create a media relay and do the STERN thing if startMediaPort is non-zero
int
stunInitServer ( StunServerInfo &info,
				 const StunAddress4 &myAddr,
				 const StunAddress4 &altAddr,
				 int startMediaPort,
				 int verbose );

void
stunStopServer ( StunServerInfo &info );

/// return TRUE if all is OK
int
stunServerProcess ( StunServerInfo &info, int verbose );

/// returns number of address found - take array or addres
int
stunFindLocalInterfaces ( UInt32 *addresses, int maxSize );

void
stunTest ( StunAddress4 &dest, int testNum, int verbose, StunAddress4 *srcAddr = 0 );

NatType
stunNatType ( StunAddress4 &dest, int verbose,
			  int *preservePort = 0, // if set, is return for if NAT preservers ports or not
			  int *hairpin = 0 , // if set, is the return for if NAT will hairpin packets
			  int port = 0, // port to use for the test, 0 to choose random port
			  StunAddress4 *sAddr = 0 // NIC to use
			);


int
stunServerProcessMsg ( char *buf,
					   unsigned int bufLen,
					   StunAddress4 &from,
					   StunAddress4 &myAddr,
					   StunAddress4 &altAddr,
					   StunMessage *resp,
					   StunAddress4 *destination,
					   StunAtrString *hmacPassword,
					   int *changePort,
					   int *changeIp,
					   int verbose );

int
stunOpenSocket ( StunAddress4 &dest,
				 StunAddress4 *mappedAddr,
				 int port = 0,
				 StunAddress4 *srcAddr = 0,
				 int verbose = FALSE );

int
stunOpenSocketPair ( StunAddress4 &dest, StunAddress4 *mappedAddr,
					 int *fd1, int *fd2,
					 int srcPort = 0,  StunAddress4 *srcAddr = 0,
					 int verbose = FALSE );

int
stunRandomPort();

#endif
