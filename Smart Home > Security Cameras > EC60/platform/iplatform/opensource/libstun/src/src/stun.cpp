
/*****************************************************************************
Copyright? 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
File name: stun.cpp
Description: stunclient. 对libstun的具体实现；
Author: AaronChen
Version: in code
Date: continuing
History: in svn
*****************************************************************************/
#include "stun.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <winsock2.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")
#else

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <net/if.h>
#endif

#include "stunone.h"


#define FILE_STDERR	stderr
#define FILE_LOG	stderr
#define FILE_STDOUT	stdout

// e.g.:
//	printf("ip:port " IPv4AddressPrintFormat "\n", IPv4AddressPrintArg(ip, port));
//	printf("servername %s, ip:port " IPv4AddressPrintFormat "date %s\n",
//		"www.tp-link.com.cn", IPv4AddressPrintArg(ip, port), "2015-03-18");
#define IPv4AddressPrintFormat "%d.%d.%d.%d:%d"
//ip is an int32 and host-byte-order, port is host-byte-order
#define IPv4AddressPrintArg(ip, port) \
	((int)((ip)>>24)&0xFF), ((int)((ip)>>16)&0xFF), ((int)((ip)>>8)&0xFF), ((int)((ip)>>0)&0xFF), (port)

#ifdef WIN32
#define snprintf _snprintf
#endif

#define NOSSL

#define BINDING_REQUEST_MIN_SIZE	28
#define MAX_NIC 3


/*************************************************
Function: openPort
Description: 内部基础函数之一，在指定端口上创建socket
Input: port, interfaceIp etc.
Output: socket
Return: socket or errno
Others: mustsuccess是新增参数，指明此次openPort必须成功；在客户端启动
多个stun对象时可能出现port被占用情况，标记mustsuccess使其在端口占用时
端口++重试；
*************************************************/

Socket
openPort ( unsigned short port, unsigned int interfaceIp, int mustsuccess, int verbose )
{
	Socket fd = INVALID_SOCKET;
	fd = socket ( PF_INET, SOCK_DGRAM, IPPROTO_UDP );

	if ( fd == INVALID_SOCKET )
	{
		int err = getErrno();
		fprintf ( FILE_STDERR, "Could not create a UDP socket: %d\n", err );
        goto failed;
	}

retry:
	struct sockaddr_in addr;
	memset ( ( char * ) & ( addr ), 0, sizeof ( ( addr ) ) );
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl ( INADDR_ANY );
	addr.sin_port = htons ( port );

	if ( ( interfaceIp != 0 ) &&
			( interfaceIp != 0x100007f ) )
	{
		addr.sin_addr.s_addr = htonl ( interfaceIp );

		if ( verbose )
		{
			fprintf ( FILE_LOG, "Binding to interface %#x\n", htonl ( interfaceIp ) );
		}
	}

	if ( bind ( fd, ( struct sockaddr * ) &addr, sizeof ( addr ) ) != 0 )
	{
		int e = getErrno();

		switch ( e )
		{
			case 0:
			{
				fprintf ( FILE_STDERR, "Could not bind socket\n" );
                goto failed;
			}

			case _EADDRINUSE:
			{
				port = port + 5;

				if ( mustsuccess )
				{
					goto retry;
				}
				else
				{
					fprintf ( FILE_STDERR, "Port %d for receiving UDP is in use\n", port );
                    goto failed;
				}
			}

			case _EADDRNOTAVAIL:
			{
				if ( verbose )
				{
					fprintf ( FILE_STDERR, "Cannot assign requested address\n" );
				}

                goto failed;
			}

			default:
			{
				fprintf ( FILE_STDERR, "Could not bind UDP receive port. Error=%d %s\n",
						  e, strerror ( e ) );
                goto failed;
			}
		}
	}

	if ( verbose )
	{
		fprintf ( FILE_LOG, "Opened port %d with fd %d\n", port, fd );
	}

	assert ( fd != INVALID_SOCKET  );
	return fd;

failed:
    if( fd != INVALID_SOCKET ){
        closesocket(fd);
    }
    return INVALID_SOCKET;
}

/*************************************************
Function: getMessage
Description: 内部基础函数之一，在指定fd上收取message
Input: fd
Output: buf， srcIp， srcPort etc.
Return: 0 success
Others:
*************************************************/

int
getMessage ( Socket fd, char *buf, int *len,
			 unsigned int *srcIp, unsigned short *srcPort,
			 int verbose )
{
	assert ( fd != INVALID_SOCKET );
	int originalSize = *len;
	assert ( originalSize > 0 );
	struct sockaddr_in from;
	int fromLen = sizeof ( from );
	*len = recvfrom ( fd,
					  buf,
					  originalSize,
					  0,
					  ( struct sockaddr * ) &from,
					  ( socklen_t * ) &fromLen );

	if ( *len == SOCKET_ERROR )
	{
		int err = getErrno();

		switch ( err )
		{
			case _ENOTSOCK:
				fprintf ( FILE_STDERR, "Error fd not a socket\n" );
				break;

			case _ECONNRESET:
				fprintf ( FILE_STDERR, "Error connection reset - host not reachable\n" );
				break;

			default:
				fprintf ( FILE_STDERR, "Socket Error=%d\n", err );
		}

		return FALSE;
	}

	if ( *len < 0 )
	{
		fprintf ( FILE_LOG, "socket closed? negative len\n" );
		return FALSE;
	}

	if ( *len == 0 )
	{
		fprintf ( FILE_LOG, "socket closed? zero len\n" );
		return FALSE;
	}

	*srcPort = ntohs ( from.sin_port );
	*srcIp = ntohl ( from.sin_addr.s_addr );

	if ( ( *len ) + 1 >= originalSize )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Received a message that was too large\n" );
		}

		return FALSE;
	}

	buf[*len] = 0;
	return TRUE;
}

/*************************************************
Function: sendMessage
Description: 内部基础函数之一，在指定fd上发送message
Input: fd，buf
Output: srcIp， srcPort etc.
Return: 0 success
Others:
*************************************************/

int
sendMessage ( Socket fd, char *buf, int l,
			  unsigned int dstIp, unsigned short dstPort,
			  int verbose )
{
	assert ( fd != INVALID_SOCKET );
	int s;

	if ( dstPort == 0 )
	{
		// sending on a connected port
		assert ( dstIp == 0 );
		s = send ( fd, buf, l, 0 );
	}
	else
	{
		assert ( dstIp != 0 );
		assert ( dstPort != 0 );
		struct sockaddr_in to;
		int toLen = sizeof ( to );
		memset ( &to, 0, toLen );
		to.sin_family = AF_INET;
		to.sin_port = htons ( dstPort );
		to.sin_addr.s_addr = htonl ( dstIp );
		s = sendto ( fd, buf, l, 0, ( sockaddr * ) &to, toLen );
	}

	if ( s == SOCKET_ERROR )
	{
		int e = getErrno();

		switch ( e )
		{
			case _ECONNREFUSED:
			case _EHOSTDOWN:
			case _EHOSTUNREACH:
			{
				// quietly ignore this
			}
			break;

			case _EAFNOSUPPORT:
			{
				fprintf ( FILE_STDERR, "err EAFNOSUPPORT in send\n" );
			}
			break;

			default:
			{
				fprintf ( FILE_STDERR, "err %d %s in send\n", e, strerror ( e ) );
			}
		}

		return FALSE;
	}

	if ( s == 0 )
	{
		fprintf ( FILE_STDERR, "no data sent in send\n" );
		return FALSE;
	}

	if ( s != l )
	{
		if ( verbose )
		{
			fprintf ( FILE_STDERR, "only %d out of %d bytes sent\n", s, l );
		}

		return FALSE;
	}

	return TRUE;
}


int
initNetwork()
{
#ifdef WIN32
	WORD wVersionRequested = MAKEWORD ( 2, 2 );
	WSADATA wsaData;
	int err;
	err = WSAStartup ( wVersionRequested, &wsaData );

	if ( err != 0 )
	{
		// could not find a usable WinSock DLL
		fprintf ( FILE_STDERR, "Could not load winsock\n" );
		assert ( 0 ); // is this is failing, try a different version that 2.2, 1.0 or later will likely work
		return -1;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if ( LOBYTE ( wsaData.wVersion ) != 2 ||
			HIBYTE ( wsaData.wVersion ) != 2 )
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup( );
		fprintf ( FILE_STDERR, "Bad winsock version\n" );
		assert ( 0 ); // is this is failing, try a different version that 2.2, 1.0 or later will likely work
		return -1;
	}

#endif
	return 0;
}


static void
computeHmac ( char *hmac, const char *input, int length, const char *key, int keySize );

static int
stunParseAtrAddress ( char *body, unsigned int hdrLen,  StunAtrAddress4 &result )
{
	if ( hdrLen != 8 )
	{
		fprintf ( FILE_LOG, "hdrLen wrong for Address\n" );
		return FALSE;
	}

	result.pad = *body++;
	result.family = *body++;

	if ( result.family == IPv4Family )
	{
		UInt16 nport;
		memcpy ( &nport, body, 2 );
		body += 2;
		result.ipv4.port = ntohs ( nport );
		UInt32 naddr;
		memcpy ( &naddr, body, 4 );
		body += 4;
		result.ipv4.addr = ntohl ( naddr );
		return TRUE;
	}
	else if ( result.family == IPv6Family )
	{
		fprintf ( FILE_LOG, "ipv6 not supported\n" );
	}
	else
	{
		fprintf ( FILE_LOG, "bad address family: %d\n", result.family );
	}

	return FALSE;
}

static int
stunParseAtrChangeRequest ( char *body, unsigned int hdrLen,  StunAtrChangeRequest &result )
{
	if ( hdrLen != 4 )
	{
		fprintf ( FILE_LOG, "hdr length = %d expecting %d\n", hdrLen, sizeof ( result ) );
		fprintf ( FILE_LOG, "Incorrect size for ChangeRequest\n" );
		return FALSE;
	}
	else
	{
		memcpy ( &result.value, body, 4 );
		result.value = ntohl ( result.value );
		return TRUE;
	}
}

static int
stunParseAtrError ( char *body, unsigned int hdrLen,  StunAtrError &result )
{
	if ( hdrLen >= sizeof ( result ) )
	{
		fprintf ( FILE_LOG, "head on Error too large\n" );
		return FALSE;
	}
	else
	{
		memcpy ( &result.pad, body, 2 );
		body += 2;
		result.pad = ntohs ( result.pad );
		result.errorClass = *body++;
		result.number = *body++;
		result.sizeReason = hdrLen - 4;
		memcpy ( &result.reason, body, result.sizeReason );
		result.reason[result.sizeReason] = 0;
		return TRUE;
	}
}

static int
stunParseAtrUnknown ( char *body, unsigned int hdrLen,  StunAtrUnknown &result )
{
	if ( hdrLen >= sizeof ( result ) )
	{
		return FALSE;
	}
	else
	{
		if ( hdrLen % 4 != 0 ) { return FALSE; }

		result.numAttributes = hdrLen / 4;

		for ( int i = 0; i < result.numAttributes; i++ )
		{
			memcpy ( &result.attrType[i], body, 2 );
			body += 2;
			result.attrType[i] = ntohs ( result.attrType[i] );
		}

		return TRUE;
	}
}


static int
stunParseAtrString ( char *body, unsigned int hdrLen,  StunAtrString &result )
{
	if ( hdrLen >= STUN_MAX_STRING )
	{
		fprintf ( FILE_LOG, "String is too large\n" );
		return FALSE;
	}
	else
	{
		if ( hdrLen % 4 != 0 )
		{
			fprintf ( FILE_LOG, "Bad length string %d\n", hdrLen );
			return FALSE;
		}

		result.sizeValue = hdrLen;
		memcpy ( &result.value, body, hdrLen );
		result.value[hdrLen] = 0;
		return TRUE;
	}
}


static int
stunParseAtrIntegrity ( char *body, unsigned int hdrLen,  StunAtrIntegrity &result )
{
	if ( hdrLen != 20 )
	{
		fprintf ( FILE_LOG, "MessageIntegrity must be 20 bytes\n" );
		return FALSE;
	}
	else
	{
		memcpy ( &result.hash, body, hdrLen );
		return TRUE;
	}
}

/*************************************************
Function: stunParseMessage
Description: parse STUN response.
Input: buf
Output: msg
Return: TRUE when success. FALSE when fail
Others: called by stunNatType() TypeTest() STUN_parse_binding_response()
		and stunParseMessage()
*************************************************/

int
stunParseMessage ( char *buf, unsigned int bufLen, StunMessage &msg, int verbose )
{
	if ( verbose ) { fprintf ( FILE_LOG, "Received stun message: %d bytes\n", bufLen ); }

	memset ( &msg, 0, sizeof ( msg ) );

	if ( sizeof ( StunMsgHdr ) > bufLen )
	{
		fprintf ( FILE_LOG, "Bad message\n" );
		return FALSE;
	}

	memcpy ( &msg.msgHdr, buf, sizeof ( StunMsgHdr ) );
	msg.msgHdr.msgType = ntohs ( msg.msgHdr.msgType );
	msg.msgHdr.msgLength = ntohs ( msg.msgHdr.msgLength );

	if ( msg.msgHdr.msgLength + sizeof ( StunMsgHdr ) != bufLen )
	{
		fprintf ( FILE_LOG, "Message header length doesn't match message size: %d - %d\n",
				  msg.msgHdr.msgLength, bufLen );
		return FALSE;
	}

	char *body = buf + sizeof ( StunMsgHdr );
	unsigned int size = msg.msgHdr.msgLength;

	//clog << "bytes after header = " << size << endl;

	while ( size > 0 )
	{
		// !jf! should check that there are enough bytes left in the buffer
		StunAtrHdr *attr = reinterpret_cast<StunAtrHdr *> ( body );
		unsigned int attrLen = ntohs ( attr->length );
		int atrType = ntohs ( attr->type );

		//if (verbose) clog << "Found attribute type=" << AttrNames[atrType] << " length=" << attrLen << endl;
		if ( attrLen + 4 > size )
		{
			fprintf ( FILE_LOG, "claims attribute is larger than size of message (attribute type=%d)\n",
					  atrType );
			return FALSE;
		}

		body += 4; // skip the length and type in attribute header
		size -= 4;

		switch ( atrType )
		{
			case MappedAddress:
				msg.hasMappedAddress = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.mappedAddress ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing MappedAddress\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "MappedAddress = " IPv4AddressPrintFormat "\n",
								  IPv4AddressPrintArg ( msg.mappedAddress.ipv4.addr, msg.mappedAddress.ipv4.port ) );
					}
				}

				break;

			case ResponseAddress:
				msg.hasResponseAddress = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.responseAddress ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing ResponseAddress\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "ResponseAddress = " IPv4AddressPrintFormat "\n",
								  IPv4AddressPrintArg ( msg.responseAddress.ipv4.addr, msg.responseAddress.ipv4.port ) );
					}
				}

				break;

			case ChangeRequest:
				msg.hasChangeRequest = TRUE;

				if ( stunParseAtrChangeRequest ( body, attrLen, msg.changeRequest ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing ChangeRequest\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "ChangeRequest = %d\n", msg.changeRequest.value );
					}
				}

				break;

			case SourceAddress:
				msg.hasSourceAddress = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.sourceAddress ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing SourceAddress\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "SourceAddress = " IPv4AddressPrintFormat "\n",
								  IPv4AddressPrintArg ( msg.sourceAddress.ipv4.addr, msg.sourceAddress.ipv4.port ) );
					}
				}

				break;

			case ChangedAddress:
				msg.hasChangedAddress = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.changedAddress ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing ChangedAddress\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "ChangedAddress = " IPv4AddressPrintFormat "\n",
								  IPv4AddressPrintArg ( msg.changedAddress.ipv4.addr, msg.changedAddress.ipv4.port ) );
					}
				}

				break;

			case Username:
				msg.hasUsername = TRUE;

				if ( stunParseAtrString ( body, attrLen, msg.username ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing Username\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "Username = %s\n", msg.username.value );
					}
				}

				break;

			case Password:
				msg.hasPassword = TRUE;

				if ( stunParseAtrString ( body, attrLen, msg.password ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing Password\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "Password = %s\n", msg.password.value );
					}
				}

				break;

			case MessageIntegrity:
				msg.hasMessageIntegrity = TRUE;

				if ( stunParseAtrIntegrity ( body, attrLen, msg.messageIntegrity ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing MessageIntegrity\n" );
					return FALSE;
				}
				else
				{
					//if (verbose) {
					//	fprintf(FILE_LOG, "MessageIntegrity = %s\n", msg.messageIntegrity.hash);
					//}
				}

				// read the current HMAC
				// look up the password given the user of given the transaction id
				// compute the HMAC on the buffer
				// decide if they match or not
				break;

			case ErrorCode:
				msg.hasErrorCode = TRUE;

				if ( stunParseAtrError ( body, attrLen, msg.errorCode ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing ErrorCode\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "ErrorCode = %d %d %s\n",
								  int ( msg.errorCode.errorClass ), int ( msg.errorCode.number ), msg.errorCode.reason );
					}
				}

				break;

			case UnknownAttribute:
				msg.hasUnknownAttributes = TRUE;

				if ( stunParseAtrUnknown ( body, attrLen, msg.unknownAttributes ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing UnknownAttribute\n" );
					return FALSE;
				}

				break;

			case ReflectedFrom:
				msg.hasReflectedFrom = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.reflectedFrom ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing ReflectedFrom\n" );
					return FALSE;
				}

				break;

			case XorMappedAddress:
				msg.hasXorMappedAddress = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.xorMappedAddress ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing XorMappedAddressn\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "XorMappedAddress = " IPv4AddressPrintFormat "\n",
								  IPv4AddressPrintArg ( msg.mappedAddress.ipv4.addr, msg.mappedAddress.ipv4.port ) );
					}
				}

				break;

			case XorOnly:
				msg.xorOnly = TRUE;

				if ( verbose )
				{
					fprintf ( FILE_LOG, "xorOnly = TRUE\n" );
				}

				break;

			case ServerName:
				msg.hasServerName = TRUE;

				if ( stunParseAtrString ( body, attrLen, msg.serverName ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing ServerName\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "ServerName = %s\n", msg.serverName.value );
					}
				}

				break;

			case SecondaryAddress:
				msg.hasSecondaryAddress = TRUE;

				if ( stunParseAtrAddress (  body,  attrLen,  msg.secondaryAddress ) == FALSE )
				{
					fprintf ( FILE_LOG, "problem parsing secondaryAddress\n" );
					return FALSE;
				}
				else
				{
					if ( verbose )
					{
						fprintf ( FILE_LOG, "SecondaryAddress = " IPv4AddressPrintFormat "\n",
								  IPv4AddressPrintArg ( msg.secondaryAddress.ipv4.addr, msg.secondaryAddress.ipv4.port ) );
					}
				}

				break;

			default:
				if ( verbose )
				{
					fprintf ( FILE_LOG, "Unknown attribute: %d\n", atrType );
				}

				if ( atrType <= 0x7FFF )
				{
					return FALSE;
				}
		}

		body += attrLen;
		size -= attrLen;
	}

	return TRUE;
}


static char *
encode16 ( char *buf, UInt16 data )
{
	UInt16 ndata = htons ( data );
	memcpy ( buf, reinterpret_cast<void *> ( &ndata ), sizeof ( UInt16 ) );
	return buf + sizeof ( UInt16 );
}

static char *
encode32 ( char *buf, UInt32 data )
{
	UInt32 ndata = htonl ( data );
	memcpy ( buf, reinterpret_cast<void *> ( &ndata ), sizeof ( UInt32 ) );
	return buf + sizeof ( UInt32 );
}


static char *
encode ( char *buf, const char *data, unsigned int length )
{
	memcpy ( buf, data, length );
	return buf + length;
}


static char *
encodeAtrAddress4 ( char *ptr, UInt16 type, const StunAtrAddress4 &atr )
{
	ptr = encode16 ( ptr, type );
	ptr = encode16 ( ptr, 8 );
	*ptr++ = atr.pad;
	*ptr++ = IPv4Family;
	ptr = encode16 ( ptr, atr.ipv4.port );
	ptr = encode32 ( ptr, atr.ipv4.addr );
	return ptr;
}

static char *
encodeAtrChangeRequest ( char *ptr, const StunAtrChangeRequest &atr )
{
	ptr = encode16 ( ptr, ChangeRequest );
	ptr = encode16 ( ptr, 4 );
	ptr = encode32 ( ptr, atr.value );
	return ptr;
}

static char *
encodeAtrError ( char *ptr, const StunAtrError &atr )
{
	ptr = encode16 ( ptr, ErrorCode );
	ptr = encode16 ( ptr, 6 + atr.sizeReason );
	ptr = encode16 ( ptr, atr.pad );
	*ptr++ = atr.errorClass;
	*ptr++ = atr.number;
	ptr = encode ( ptr, atr.reason, atr.sizeReason );
	return ptr;
}


static char *
encodeAtrUnknown ( char *ptr, const StunAtrUnknown &atr )
{
	ptr = encode16 ( ptr, UnknownAttribute );
	ptr = encode16 ( ptr, 2 + 2 * atr.numAttributes );

	for ( int i = 0; i < atr.numAttributes; i++ )
	{
		ptr = encode16 ( ptr, atr.attrType[i] );
	}

	return ptr;
}


static char *
encodeXorOnly ( char *ptr )
{
	ptr = encode16 ( ptr, XorOnly );
	return ptr;
}


static char *
encodeAtrString ( char *ptr, UInt16 type, const StunAtrString &atr )
{
	assert ( atr.sizeValue % 4 == 0 );
	ptr = encode16 ( ptr, type );
	ptr = encode16 ( ptr, atr.sizeValue );
	ptr = encode ( ptr, atr.value, atr.sizeValue );
	return ptr;
}


static char *
encodeAtrIntegrity ( char *ptr, const StunAtrIntegrity &atr )
{
	ptr = encode16 ( ptr, MessageIntegrity );
	ptr = encode16 ( ptr, 20 );
	ptr = encode ( ptr, atr.hash, sizeof ( atr.hash ) );
	return ptr;
}

/*************************************************
Function: stunEncodeMessage
Description: build STUN response.
Input: msg
Output: buf
Return: TRUE when success. FALSE when fail
Others: called by stunSendTest() STUN_build_binding_response()
		and stunEncodeMessage()
*************************************************/

unsigned int
stunEncodeMessage ( const StunMessage &msg,
					char *buf,
					unsigned int bufLen,
					const StunAtrString &password,
					int verbose )
{
	assert ( bufLen >= sizeof ( StunMsgHdr ) );
	char *ptr = buf;
	ptr = encode16 ( ptr, msg.msgHdr.msgType );
	char *lengthp = ptr;
	ptr = encode16 ( ptr, 0 );
	ptr = encode ( ptr, reinterpret_cast<const char *> ( msg.msgHdr.id.octet ),
				   sizeof ( msg.msgHdr.id ) );

	if ( verbose )
	{
		fprintf ( FILE_LOG, "Encoding stun message: \n" );
	}

	if ( msg.hasMappedAddress )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding MappedAddress: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.mappedAddress.ipv4.addr, msg.mappedAddress.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, MappedAddress, msg.mappedAddress );
	}

	if ( msg.hasResponseAddress )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding ResponseAddress: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.responseAddress.ipv4.addr, msg.responseAddress.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, ResponseAddress, msg.responseAddress );
	}

	if ( msg.hasChangeRequest )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding ChangeRequest: %d\n", msg.changeRequest.value );
		}

		ptr = encodeAtrChangeRequest ( ptr, msg.changeRequest );
	}

	if ( msg.hasSourceAddress )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding SourceAddress: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.sourceAddress.ipv4.addr, msg.sourceAddress.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, SourceAddress, msg.sourceAddress );
	}

	if ( msg.hasChangedAddress )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding ChangedAddress: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.changedAddress.ipv4.addr, msg.changedAddress.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, ChangedAddress, msg.changedAddress );
	}

	if ( msg.hasUsername )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding Username: %s\n", msg.username.value );
		}

		ptr = encodeAtrString ( ptr, Username, msg.username );
	}

	if ( msg.hasPassword )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding Password: %s\n", msg.password.value );
		}

		ptr = encodeAtrString ( ptr, Password, msg.password );
	}

	if ( msg.hasErrorCode )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding ErrorCode: class=%d number=%d reason=%s\n",
					  int ( msg.errorCode.errorClass ), int ( msg.errorCode.number ), msg.errorCode.reason );
		}

		ptr = encodeAtrError ( ptr, msg.errorCode );
	}

	if ( msg.hasUnknownAttributes )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding UnknownAttribute: ???\n" );
		}

		ptr = encodeAtrUnknown ( ptr, msg.unknownAttributes );
	}

	if ( msg.hasReflectedFrom )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding ReflectedFrom: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.reflectedFrom.ipv4.addr, msg.reflectedFrom.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, ReflectedFrom, msg.reflectedFrom );
	}

	if ( msg.hasXorMappedAddress )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding XorMappedAddress: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.xorMappedAddress.ipv4.addr, msg.xorMappedAddress.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, XorMappedAddress, msg.xorMappedAddress );
	}

	if ( msg.xorOnly )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding xorOnly: \n" );
		}

		ptr = encodeXorOnly ( ptr );
	}

	if ( msg.hasServerName )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding ServerName: %s\n", msg.serverName.value );
		}

		ptr = encodeAtrString ( ptr, ServerName, msg.serverName );
	}

	if ( msg.hasSecondaryAddress )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "Encoding SecondaryAddress: " IPv4AddressPrintFormat "\n",
					  IPv4AddressPrintArg ( msg.secondaryAddress.ipv4.addr, msg.secondaryAddress.ipv4.port ) );
		}

		ptr = encodeAtrAddress4 ( ptr, SecondaryAddress, msg.secondaryAddress );
	}

	if ( password.sizeValue > 0 )
	{
		if ( verbose )
		{
			fprintf ( FILE_LOG, "HMAC with password: %s\n", password.value );
		}

		StunAtrIntegrity integrity;
		computeHmac ( integrity.hash, buf, int ( ptr - buf ) , password.value, password.sizeValue );
		ptr = encodeAtrIntegrity ( ptr, integrity );
	}

	if ( verbose )
	{
		fprintf ( FILE_LOG, "\n" );
	}

	encode16 ( lengthp, UInt16 ( ptr - buf - sizeof ( StunMsgHdr ) ) );
	return int ( ptr - buf );
}

int
stunRand()
{
#ifdef ORIGRAND
	// return 32 bits of random stuff
	assert ( sizeof ( int ) == 4 );
	static int init = FALSE;

	if ( !init )
	{
		init = TRUE;
		UInt64 tick;
#if defined(WIN32)
		volatile unsigned int lowtick = 0, hightick = 0;
		__asm
		{
			rdtsc
			mov lowtick, eax
			mov hightick, edx
		}
		tick = hightick;
		tick <<= 32;
		tick |= lowtick;
#elif defined(__GNUC__) && ( defined(__i686__) || defined(__i386__) )
		asm ( "rdtsc" : "=A" ( tick ) );
#elif defined (__SUNPRO_CC) || defined( __sparc__ )
		tick = gethrtime();
#elif defined(__MACH__)  || defined(__linux)
		int fd = open ( "/dev/random", O_RDONLY );
		read ( fd, &tick, sizeof ( tick ) );
		closesocket ( fd );
#else
#     error Need some way to seed the random number generator
#endif
		int seed = int ( tick );
#ifdef WIN32
		srand ( seed );
#else
		srandom ( seed );
#endif
	}

#ifdef WIN32
	assert ( RAND_MAX == 0x7fff );
	int r1 = rand();
	int r2 = rand();
	int ret = ( r1 << 16 ) + r2;
	return ret;
#else
	return random();
#endif
#else
	srand ( clock() );
	//srand( (unsigned)time( NULL ) );
	return rand();
#endif
}


// return a random number to use as a port
int
stunRandomPort()
{
	int min = 0x4000;
	int max = 0x7FFF;
	int ret = stunRand();
	ret = ret | min;
	ret = ret & max;
	return ret;
}


#ifdef NOSSL
static void
computeHmac ( char *hmac, const char *input, int length, const char *key, int sizeKey )
{
	strncpy ( hmac, "hmac-not-implemented", 20 );
}
#else
#include <openssl/hmac.h>

static void
computeHmac ( char *hmac, const char *input, int length, const char *key, int sizeKey )
{
	unsigned int resultSize = 0;
	HMAC ( EVP_sha1(),
		   key, sizeKey,
		   reinterpret_cast<const unsigned char *> ( input ), length,
		   reinterpret_cast<unsigned char *> ( hmac ), &resultSize );
	assert ( resultSize == 20 );
}
#endif


// returns TRUE if it succeed
int
stunParseHostName ( char *peerName,
					UInt32 &ip,
					UInt16 &portVal,
					UInt16 defaultPort )
{
	in_addr sin_addr;
	char host[512];
	strncpy ( host, peerName, 512 );
	host[512 - 1] = '\0';
	char *port = NULL;
	int portNum = defaultPort;
	// pull out the port part if present.
	char *sep = strchr ( host, ':' );

	if ( sep == NULL )
	{
		portNum = defaultPort;
	}
	else
	{
		*sep = '\0';
		port = sep + 1;
		// set port part
		char *endPtr = NULL;
		portNum = strtol ( port, &endPtr, 10 );

		if ( endPtr != NULL )
		{
			if ( *endPtr != '\0' )
			{
				portNum = defaultPort;
			}
		}
	}

	if ( portNum < 1024 ) { return FALSE; }

	if ( portNum >= 0xFFFF ) { return FALSE; }

	// figure out the host part
	struct hostent *h;
#ifdef WIN32
	assert ( strlen ( host ) >= 1 );

	if ( isdigit ( host[0] ) )
	{
		// assume it is a ip address
		unsigned long a = inet_addr ( host );
		//cerr << "a=0x" << hex << a << dec << endl;
		ip = ntohl ( a );
	}
	else
	{
		// assume it is a host name
		h = gethostbyname ( host );

		if ( h == NULL )
		{
			int err = getErrno();
			fprintf ( FILE_STDERR, "error was %d\n", err );
			assert ( err != WSANOTINITIALISED );
			ip = ntohl ( 0x7F000001L );
			return FALSE;
		}
		else
		{
			sin_addr = * ( struct in_addr * ) h->h_addr;
			ip = ntohl ( sin_addr.s_addr );
		}
	}

#else
	h = gethostbyname ( host );

	if ( h == NULL )
	{
		int err = getErrno();
		fprintf ( FILE_STDERR, "error was %d\n", err );
		ip = ntohl ( 0x7F000001L );
		return FALSE;
	}
	else
	{
		sin_addr = * ( struct in_addr * ) h->h_addr;
		ip = ntohl ( sin_addr.s_addr );
	}

#endif
	portVal = portNum;
	return TRUE;
}


int
stunParseServerName ( char *name, StunAddress4 &addr )
{
	assert ( name );
	// TODO - put in DNS SRV stuff.
	int ret = stunParseHostName ( name, addr.addr, addr.port, 3478 );

	if ( ret != TRUE )
	{
		addr.port = 0xFFFF;
	}

	return ret;
}

#if 0
static void
stunCreateSharedSecretErrorResponse ( StunMessage &response, int cl, int number, const char *msg )
{
	response.msgHdr.msgType = SharedSecretErrorResponseMsg;
	response.hasErrorCode = TRUE;
	response.errorCode.errorClass = cl;
	response.errorCode.number = number;
	strcpy ( response.errorCode.reason, msg );
}
#endif


void
stunBuildReqSimple ( StunMessage *msg,
					 const StunAtrString &username,
					 int changePort, int changeIp, unsigned int id )
{
	assert ( NULL != msg );
	memset ( msg , 0 , sizeof ( *msg ) );
	msg->msgHdr.msgType = BindRequestMsg;

	for ( int i = 0; i < 16; i = i + 4 )
	{
		assert ( i + 3 < 16 );
		int r = stunRand();
		msg->msgHdr.id.octet[i + 0] = r >> 0;
		msg->msgHdr.id.octet[i + 1] = r >> 8;
		msg->msgHdr.id.octet[i + 2] = r >> 16;
		msg->msgHdr.id.octet[i + 3] = r >> 24;
	}

	if ( id != 0 )
	{
		msg->msgHdr.id.octet[0] = id;
	}

	msg->hasChangeRequest = TRUE;
	msg->changeRequest.value = ( changeIp ? ChangeIpFlag : 0 ) |
							   ( changePort ? ChangePortFlag : 0 );

	if ( username.sizeValue > 0 )
	{
		msg->hasUsername = TRUE;
		msg->username = username;
	}
}


static void
stunSendTest ( Socket myFd, StunAddress4 &dest,
			   const StunAtrString &username, const StunAtrString &password,
			   int testNum, int verbose )
{
	assert ( dest.addr != 0 );
	assert ( dest.port != 0 );
	int changePort = FALSE;
	int changeIP = FALSE;

	switch ( testNum )
	{
		case 1:
		case 10:
		case 11:
			break;

		case 2:
			//changePort=TRUE;
			changeIP = TRUE;
			break;

		case 3:
			changePort = TRUE;
			break;

		case 4:
			changeIP = TRUE;
			break;

		default:
			fprintf ( FILE_STDERR, "Test %d is unknown\n", testNum );
			assert ( 0 );
	}

	StunMessage req;
	memset ( &req, 0, sizeof ( StunMessage ) );
	stunBuildReqSimple ( &req, username,
						 changePort , changeIP ,
						 testNum );
	char buf[STUN_MAX_MESSAGE_SIZE];
	int len = STUN_MAX_MESSAGE_SIZE;
	len = stunEncodeMessage ( req, buf, len, password, verbose );

	if ( verbose )
	{
		fprintf ( FILE_LOG, "About to send msg of len %d to " IPv4AddressPrintFormat "\n",
				  len, IPv4AddressPrintArg ( dest.addr, dest.port ) );
	}

	sendMessage ( myFd, buf, len, dest.addr, dest.port, verbose );
	// add some delay so the packets don't get sent too quickly
#ifdef WIN32 // !xy! TODO - should fix this up in windows
	clock_t now = clock();
	assert ( CLOCKS_PER_SEC == 1000 );

	while ( clock() <= now + 10 ) { };

#else
	usleep ( 10 * 1000 );

#endif
}
int parseStunAddress4 ( char *mapaddr, StunAddress4 addr )
{
	//printf("%x\n",addr.addr);
	//printf("%d\n",(addr.addr>>24)&0xFF);
	//printf("%d\n",(addr.addr>>16)&0xFF);
	//printf("%d\n",(addr.addr>>8)&0xFF);
	//printf("%d\n",(addr.addr>>0)&0xFF);
	sprintf ( mapaddr, "%d.%d.%d.%d:%d",
			  ( addr.addr >> 24 ) & 0xFF, ( addr.addr >> 16 ) & 0xFF,
			  ( addr.addr >> 8 ) & 0xFF, ( addr.addr >> 0 ) & 0xFF, addr.port );
	return 0;
}


StunAddress4
stunNatTypeTestI ( StunAddress4 &dest,
				   int verbose,
				   int *preservePort, // if set, is return for if NAT preservers ports or not
				   int *hairpin,  // if set, is the return for if NAT will hairpin packets
				   int port, // port to use for the test, 0 to choose random port
				   StunAddress4 *sAddr, // NIC to use
				   int *fd )
{
	assert ( dest.addr != 0 );
	assert ( dest.port != 0 );

	if ( hairpin )
	{
		*hairpin = FALSE;
	}

	if ( port == 0 )
	{
		port = stunRandomPort();
	}

	int respTestI = FALSE;
	StunAddress4 testImappedAddr;
	memset ( &testImappedAddr, 0, sizeof ( testImappedAddr ) );
	StunAtrString username;
	StunAtrString password;
	username.sizeValue = 0;
	password.sizeValue = 0;
	int count = 0;
	UInt32 interfaceIp = 0;

	if ( sAddr )
	{
		interfaceIp = sAddr->addr;
	}

	Socket myFd1 = openPort ( port, interfaceIp, TRUE, verbose );

	if ( myFd1 == INVALID_SOCKET )
	{
		fprintf ( FILE_STDERR, "Some problem opening port/interface to send on\n" );
        goto failed;
	}

	assert ( myFd1 != INVALID_SOCKET );

	while ( count < 2 ) //do this while twice. The first time sendTest. The second select msg recv.
	{
		//		cout << count << endl;
		struct timeval tv;
		fd_set fdSet;
#ifdef WIN32
		unsigned int fdSetSize;
#else
		int fdSetSize;
#endif
		FD_ZERO ( &fdSet );
		fdSetSize = 0;
		FD_SET ( myFd1, &fdSet );
		fdSetSize = ( myFd1 + 1 > fdSetSize ) ? myFd1 + 1 : fdSetSize;
		tv.tv_sec = 0;
		tv.tv_usec = 150 * 1000; // 150 ms

		if ( count == 0 ) { tv.tv_usec = 0; }

		int  err = select ( fdSetSize, &fdSet, NULL, NULL, &tv );
		int e = getErrno();

		if ( err == SOCKET_ERROR )
		{
			// error occurred
			fprintf ( FILE_STDERR, "Error %d %s in select\n", e, strerror ( e ) );
            goto failed;
		}
		else if ( err == 0 )
		{
			// timeout occurred
			count++;

			if ( !respTestI )
			{
				stunSendTest ( myFd1, dest, username, password, 1 , verbose );
			}
		}
		else
		{
			//if (verbose) clog << "-----------------------------------------" << endl;
			assert ( err > 0 );

			if ( myFd1 != INVALID_SOCKET )
			{
				if ( FD_ISSET ( myFd1, &fdSet ) )
				{
					char msg[STUN_MAX_MESSAGE_SIZE];
					int msgLen = sizeof ( msg );
					StunAddress4 from;
					getMessage ( myFd1,
								 msg,
								 &msgLen,
								 &from.addr,
								 &from.port, verbose );
					StunMessage resp;
					memset ( &resp, 0, sizeof ( StunMessage ) );
					stunParseMessage ( msg, msgLen, resp, verbose );

					if ( verbose )
					{
						fprintf ( FILE_LOG, "Received message of type %d  id=%d\n",
								  resp.msgHdr.msgType, ( int ) ( resp.msgHdr.id.octet[0] ) );
					}

					switch ( resp.msgHdr.id.octet[0] )
					{
						case 1:
						{
							if ( !respTestI )
							{
								testImappedAddr.addr = resp.mappedAddress.ipv4.addr;
								testImappedAddr.port = resp.mappedAddress.ipv4.port;
							}
						}
						break;
					}
				}
			}
		}
	}

	*fd = myFd1;
	return testImappedAddr;

failed:
    if( myFd1 != INVALID_SOCKET ){
        closesocket(myFd1);
    }
	return testImappedAddr;
}



NatType
stunNatType ( StunAddress4 &dest,
			  int verbose,
			  int *preservePort, // if set, is return for if NAT preservers ports or not
			  int *hairpin,  // if set, is the return for if NAT will hairpin packets
			  int port, // port to use for the test, 0 to choose random port
			  StunAddress4 *sAddr // NIC to use
			)
{
	assert ( dest.addr != 0 );
	assert ( dest.port != 0 );

	if ( hairpin )
	{
		*hairpin = FALSE;
	}

	if ( port == 0 )
	{
		port = stunRandomPort();
	}

	UInt32 interfaceIp = 0;

	if ( sAddr )
	{
		interfaceIp = sAddr->addr;
	}

	char feedbackBuf[MAX_RTP_MSG_SIZE];
	int feedbackLen = 0;
	Socket myFd1 = openPort ( port, interfaceIp, TRUE, verbose );
	Socket myFd2 = openPort ( port + 1, interfaceIp, TRUE, verbose );

	if ( ( myFd1 == INVALID_SOCKET ) || ( myFd2 == INVALID_SOCKET ) )
	{
		fprintf ( FILE_STDERR, "Some problem opening port/interface to send on\n" );
        if( myFd1 != INVALID_SOCKET ){
            closesocket(myFd1);
        }
        if( myFd2 != INVALID_SOCKET ){
            closesocket(myFd2);
        }
		return StunTypeFailure;
	}

	assert ( myFd1 != INVALID_SOCKET );
	assert ( myFd2 != INVALID_SOCKET );
	int respTestI = FALSE;
	int isNat = TRUE;
	StunAddress4 testIchangedAddr;
	StunAddress4 testImappedAddr;
	int respTestI2 = FALSE;
	int mappedIpSame = TRUE;
	StunAddress4 testI2mappedAddr;
	StunAddress4 testI2dest = dest;
	int respTestII = FALSE;
	int respTestIII = FALSE;
	int respTestHairpin = FALSE;
	int respTestPreservePort = FALSE;
	memset ( &testImappedAddr, 0, sizeof ( testImappedAddr ) );
	StunAtrString username;
	StunAtrString password;
	username.sizeValue = 0;
	password.sizeValue = 0;
	int count = 0;

	while ( count < 7 )
	{
		struct timeval tv;
		fd_set fdSet;
#ifdef WIN32
		unsigned int fdSetSize;
#else
		int fdSetSize;
#endif
		FD_ZERO ( &fdSet );
		fdSetSize = 0;
		FD_SET ( myFd1, &fdSet );
		fdSetSize = ( myFd1 + 1 > fdSetSize ) ? myFd1 + 1 : fdSetSize;
		FD_SET ( myFd2, &fdSet );
		fdSetSize = ( myFd2 + 1 > fdSetSize ) ? myFd2 + 1 : fdSetSize;
		tv.tv_sec = 0;
		tv.tv_usec = 150 * 1000; // 150 ms

		if ( count == 0 ) { tv.tv_usec = 0; }

		int  err = select ( fdSetSize, &fdSet, NULL, NULL, &tv );
		int e = getErrno();

		if ( err == SOCKET_ERROR )
		{
			// error occurred
			fprintf ( FILE_STDERR, "Error %d %s in select\n", e, strerror ( e ) );
            closesocket(myFd1);
            closesocket(myFd2);
			return StunTypeFailure;
		}
		else if ( err == 0 )
		{
			// timeout occurred
			count++;

			if ( !respTestI )
			{
				stunSendTest ( myFd1, dest, username, password, 1 , verbose );
			}

			if ( ( !respTestI2 ) && respTestI )
			{
				// check the address to send to if valid
				if (  ( testI2dest.addr != 0 ) &&
						( testI2dest.port != 0 ) )
				{
					stunSendTest ( myFd1, testI2dest, username, password, 10  , verbose );
				}
			}

			if ( !respTestII )
			{
				stunSendTest ( myFd2, dest, username, password, 2 , verbose );
			}

			if ( !respTestIII )
			{
				stunSendTest ( myFd2, dest, username, password, 3 , verbose );
			}

			if ( respTestI && ( !respTestHairpin ) )
			{
				if (  ( testImappedAddr.addr != 0 ) &&
						( testImappedAddr.port != 0 ) )
				{
					stunSendTest ( myFd1, testImappedAddr, username, password, 11 , verbose );
				}
			}
		}
		else
		{
			//if (verbose) clog << "-----------------------------------------" << endl;
			assert ( err > 0 );
			// data is available on some fd

			for ( int i = 0; i < 2; i++ )
			{
				Socket myFd;

				if ( i == 0 )
				{
					myFd = myFd1;
				}
				else
				{
					myFd = myFd2;
				}

				if ( myFd != INVALID_SOCKET )
				{
					if ( FD_ISSET ( myFd, &fdSet ) )
					{
						char msg[STUN_MAX_MESSAGE_SIZE];
						int msgLen = sizeof ( msg );
						StunAddress4 from;
						getMessage ( myFd,
									 msg,
									 &msgLen,
									 &from.addr,
									 &from.port, verbose );
						StunMessage resp;
						memset ( &resp, 0, sizeof ( StunMessage ) );
						stunParseMessage ( msg, msgLen, resp, verbose );

						if ( verbose )
						{
							fprintf ( FILE_LOG, "Received message of type %d  id=%d\n",
									  resp.msgHdr.msgType, ( int ) ( resp.msgHdr.id.octet[0] ) );
						}

						switch ( resp.msgHdr.id.octet[0] )
						{
							case 1:
							{
								if ( !respTestI )
								{
									testIchangedAddr.addr = resp.changedAddress.ipv4.addr;
									testIchangedAddr.port = resp.changedAddress.ipv4.port;
									testImappedAddr.addr = resp.mappedAddress.ipv4.addr;
									testImappedAddr.port = resp.mappedAddress.ipv4.port;
									respTestPreservePort = ( testImappedAddr.port == port );

									if ( preservePort )
									{
										*preservePort = respTestPreservePort;
									}

									testI2dest.addr = resp.changedAddress.ipv4.addr;

									if ( sAddr )
									{
										sAddr->port = testImappedAddr.port;
										sAddr->addr = testImappedAddr.addr;
									}

									count = 0;
								}

								respTestI = TRUE;
							}
							break;

							case 2:
							{
								respTestII = TRUE;
							}
							break;

							case 3:
							{
								respTestIII = TRUE;
							}
							break;

							case 10:
							{
								if ( !respTestI2 )
								{
									testI2mappedAddr.addr = resp.mappedAddress.ipv4.addr;
									testI2mappedAddr.port = resp.mappedAddress.ipv4.port;
									mappedIpSame = FALSE;

									if ( ( testI2mappedAddr.addr  == testImappedAddr.addr ) &&
											( testI2mappedAddr.port == testImappedAddr.port ) )
									{
										mappedIpSame = TRUE;
									}
								}

								respTestI2 = TRUE;
							}
							break;

							case 11:
							{
								if ( hairpin )
								{
									*hairpin = TRUE;
								}

								respTestHairpin = TRUE;
							}
							break;
						}
					}
				}
			}
		}
	}

	// see if we can bind to this address
	//cerr << "try binding to " << testImappedAddr << endl;
	Socket s = openPort ( 0/*use ephemeral*/, testImappedAddr.addr, FALSE, FALSE );

	if ( s != INVALID_SOCKET )
	{
		closesocket ( s );
		isNat = FALSE;
		//cerr << "binding worked" << endl;
	}
	else
	{
		isNat = TRUE;
		//cerr << "binding failed" << endl;
	}

	if ( verbose )
	{
		fprintf ( FILE_LOG, "test I = %d\n", respTestI );
		fprintf ( FILE_LOG, "test II = %d\n", respTestII );
		fprintf ( FILE_LOG, "test III = %d\n", respTestIII );
		fprintf ( FILE_LOG, "test I(2) = %d", respTestI2 );
		fprintf ( FILE_LOG, "is nat = %d\n", isNat );
		fprintf ( FILE_LOG, "mapped IP same = %d\n", mappedIpSame );
		fprintf ( FILE_LOG, "hairpin = %d\n", respTestHairpin );
		fprintf ( FILE_LOG, "preserver port = %d\n", respTestPreservePort );
	}

#if 0

	// implement logic flow chart from draft RFC
	if ( respTestI )
	{
		if ( isNat )
		{
			if ( respTestII )
			{
				return StunTypeConeNat;
			}
			else
			{
				if ( mappedIpSame )
				{
					if ( respTestIII )
					{
						return StunTypeRestrictedNat;
					}
					else
					{
						return StunTypePortRestrictedNat;
					}
				}
				else
				{
					return StunTypeSymNat;
				}
			}
		}
		else
		{
			if ( respTestII )
			{
				return StunTypeOpen;
			}
			else
			{
				return StunTypeSymFirewall;
			}
		}
	}
	else
	{
		return StunTypeBlocked;
	}

#else

	if ( respTestI ) // not blocked
	{
		if ( isNat )
		{
			if ( mappedIpSame )
			{
				if ( respTestII )
				{
					sprintf ( feedbackBuf, "%d,feedback yo", StunTypeIndependentFilter );
					feedbackLen = strlen ( feedbackBuf );
					sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
					closesocket ( myFd1 );
					closesocket ( myFd2 );
					return StunTypeIndependentFilter;
				}
				else
				{
					if ( respTestIII )
					{
						sprintf ( feedbackBuf, "%d,feedback yo", StunTypeDependentFilter );
						feedbackLen = strlen ( feedbackBuf );
						sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
						closesocket ( myFd1 );
						closesocket ( myFd2 );
						return StunTypeDependentFilter;
					}
					else
					{
						sprintf ( feedbackBuf, "%d,feedback yo", StunTypePortDependedFilter );
						feedbackLen = strlen ( feedbackBuf );
						sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
						closesocket ( myFd1 );
						closesocket ( myFd2 );
						return StunTypePortDependedFilter;
					}
				}
			}
			else // mappedIp is not same
			{
				sprintf ( feedbackBuf, "%d,feedback yo", StunTypeDependentMapping );
				feedbackLen = strlen ( feedbackBuf );
				sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
				closesocket ( myFd1 );
				closesocket ( myFd2 );
				return StunTypeDependentMapping;
			}
		}
		else  // isNat is FALSE
		{
			if ( respTestII )
			{
				sprintf ( feedbackBuf, "%d,feedback yo", StunTypeOpen );
				feedbackLen = strlen ( feedbackBuf );
				sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
				closesocket ( myFd1 );
				closesocket ( myFd2 );
				return StunTypeOpen;
			}
			else
			{
				sprintf ( feedbackBuf, "%d,feedback yo", StunTypeFirewall );
				feedbackLen = strlen ( feedbackBuf );
				sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
				closesocket ( myFd1 );
				closesocket ( myFd2 );
				return StunTypeFirewall;
			}
		}
	}
	else
	{
		sprintf ( feedbackBuf, "%d,feedback yo", StunTypeBlocked );
		feedbackLen = strlen ( feedbackBuf );
		sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
		closesocket ( myFd1 );
		closesocket ( myFd2 );
		return StunTypeBlocked;
	}

#endif
	sprintf ( feedbackBuf, "%d,feedback yo", StunTypeUnknown );
	feedbackLen = strlen ( feedbackBuf );
	sendMessage ( myFd1, feedbackBuf, feedbackLen, dest.addr, FEEDBACK_PORT, verbose );
	closesocket ( myFd1 );
	closesocket ( myFd2 );
	return StunTypeUnknown;
}


/*************************************************
Function: STUN_nattest_init
Description: init the STUN process. start the feed process;
Input: servername
Output:
Return: returns 0 when init work finished
Others:
*************************************************/

int
STUN_nattest_init ( char *servername )
{
	if ( servername == NULL )
	{
		fprintf ( FILE_STDERR, "servername == NULL\n" );
		return -1;
	}

	if ( -1 == initNetwork() )
	{
		return -1;
	}

	int verbose = FALSE;
	StunAddress4 stunServerAddr;
	stunServerAddr.addr = 0;
	int srcPort = 0;
	StunAddress4 sAddr[MAX_NIC];
	int numNic = 1;
	Socket myFd = 0;
	char feedbackBuf[MAX_RTP_MSG_SIZE];
	int feedbackLen = 0;
	UInt32 ret = 0;
	int i = 0;

	for ( i = 0; i < MAX_NIC; i++ )
	{
		sAddr[i].addr = 0;
		sAddr[i].port = 0;
	}

	ret = stunParseServerName ( servername, stunServerAddr );

	if ( ret != TRUE )
	{
		fprintf ( FILE_STDERR, "%s is not a valid host name\n", servername );
		return ( -1 );
	}

	if ( srcPort == 0 )
	{
		srcPort = stunRandomPort();
	}

	for ( int nic = 0; nic < numNic; nic++ )
	{
		sAddr[nic].port = srcPort;

		if ( stunServerAddr.addr == 0 )
		{
			return ( -1 );
		}

		myFd = openPort ( srcPort, sAddr[nic].addr, TRUE, verbose );
		sprintf ( feedbackBuf, "connection coming" );
		feedbackLen = strlen ( feedbackBuf );
		sendMessage ( myFd, feedbackBuf, feedbackLen, stunServerAddr.addr, FEEDBACK_PORT, verbose );
		closesocket ( myFd );
	}

	return 0;
}


/*************************************************
Function: STUN_nattest_finish
Description: Closing STUN process. send feed stop message;
Input: servername , status(success or fail)
Output: file
Return: when P2P success ,the STATUS would be 1. otherwise would be 0
Others: returns 0 when closing-up work finished
*************************************************/

int
STUN_nattest_finish ( char *servername, int status )
{
	if ( servername == NULL )
	{
		fprintf ( FILE_STDERR, "servername == NULL\n" );
		return -1;
	}

	int verbose = FALSE;
	StunAddress4 stunServerAddr;
	stunServerAddr.addr = 0;
	int srcPort = 0;
	StunAddress4 sAddr[MAX_NIC];
	int numNic = 1;
	int nic = 0;
	UInt32 ret = 0;

	if ( -1 == initNetwork() )
	{
		return -1;
	}

	for ( int i = 0; i < MAX_NIC; i++ )
	{
		sAddr[i].addr = 0;
		sAddr[i].port = 0;
	}

	ret = stunParseServerName ( servername, stunServerAddr );

	if ( ret != TRUE )
	{
		fprintf ( FILE_STDERR, "%s is not a valid host name\n", servername );
		return ( -1 );
	}

	if ( srcPort == 0 )
	{
		srcPort = stunRandomPort();
	}

	for ( nic = 0; nic < numNic; nic++ )
	{
		sAddr[nic].port = srcPort;

		if ( stunServerAddr.addr == 0 )
		{
			return ( -1 );
		}

		Socket myFd = openPort ( srcPort, sAddr[nic].addr, TRUE, verbose );
		char feedbackBuf[MAX_RTP_MSG_SIZE];
		int feedbackLen = 0;
		sprintf ( feedbackBuf, "%d,connection finished", status );
		feedbackLen = strlen ( feedbackBuf );
		sendMessage ( myFd, feedbackBuf, feedbackLen, stunServerAddr.addr, FEEDBACK_PORT, verbose );
		closesocket ( myFd );
	}

	return 0;
}


/*************************************************
Function: STUN_get_nat_type
Description:
			this is too long. plz refer to stun.h
			this is too long. plz refer to stun.h
			this is too long. plz refer to stun.h
Input: servername, verboseornot
Output: none
Return: returns 0 when get type success
Others: returns 0 when get type success
*************************************************/

int
STUN_get_nat_type ( char *servername, int verboseornot )
{
	if ( servername == NULL )
	{
		fprintf ( FILE_STDERR, "servername == NULL\n" );
		return -1;
	}

	int testNum = 0;
	int verbose = verboseornot;
	StunAddress4 stunServerAddr;
	stunServerAddr.addr = 0;
	int srcPort = 0;
	StunAddress4 sAddr[MAX_NIC];
	int retval[MAX_NIC];
	int numNic = 0;
	UInt32 ret = 0;
	int nic = 0;
	int i = 0;

	if ( -1 == initNetwork() )
	{
		return -1;
	}

	for ( i = 0; i < MAX_NIC; i++ )
	{
		sAddr[i].addr = 0;
		sAddr[i].port = 0;
		retval[i] = 0;
	}

	ret = stunParseServerName ( servername, stunServerAddr );

	if ( ret != TRUE )
	{
		fprintf ( FILE_STDERR, "%s is not a valid host name\n", servername );
		return -1;
	}

	if ( srcPort == 0 )
	{
		srcPort = stunRandomPort();
	}

	if ( numNic == 0 )
	{
		// use default
		numNic = 1;
	}

	for ( nic = 0; nic < numNic; nic++ )
	{
		sAddr[nic].port = srcPort;

		if ( stunServerAddr.addr == 0 )
		{
			return ( -1 );
		}

		if ( testNum == 0 )
		{
			int presPort = FALSE;
			int hairpin = FALSE;
			NatType stype = stunNatType ( stunServerAddr, verbose, &presPort, &hairpin,
										  srcPort, &sAddr[nic] );

			if ( nic == 0 )
			{
				fprintf ( FILE_STDOUT, "Primary: " );
			}
			else
			{
				fprintf ( FILE_STDOUT, "Secondary: " );
			}

			switch ( stype )
			{
				case StunTypeFailure:
					fprintf ( FILE_STDOUT, "Some stun error detecting NAT type" );
					retval[nic] = -1;
					break;

				case StunTypeUnknown:
					fprintf ( FILE_STDOUT, "Some unknown type error detecting NAT type" );
					retval[nic] = 0xEE;
					break;

				case StunTypeOpen:
					fprintf ( FILE_STDOUT, "Open" );
					retval[nic] = 0x00;
					break;

				case StunTypeIndependentFilter:
					fprintf ( FILE_STDOUT, "Independent Mapping, Independent Filter" );

					if ( presPort )
					{
						fprintf ( FILE_STDOUT, ", preserves ports" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", random port" );
					}

					if ( hairpin  )
					{
						fprintf ( FILE_STDOUT, ", will hairpin" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", no hairpin" );
					}

					retval[nic] = 0x02;
					break;

				case StunTypeDependentFilter:
					fprintf ( FILE_STDOUT, "Independent Mapping, Address Dependent Filter" );

					if ( presPort )
					{
						fprintf ( FILE_STDOUT, ", preserves ports" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", random port" );
					}

					if ( hairpin  )
					{
						fprintf ( FILE_STDOUT, ", will hairpin" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", no hairpin" );
					}

					retval[nic] = 0x04;
					break;

				case StunTypePortDependedFilter:
					fprintf ( FILE_STDOUT, "Independent Mapping, Port Dependent Filter" );

					if ( presPort )
					{
						fprintf ( FILE_STDOUT, ", preserves ports" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", random port" );
					}

					if ( hairpin  )
					{
						fprintf ( FILE_STDOUT, ", will hairpin" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", no hairpin" );
					}

					retval[nic] = 0x06;
					break;

				case StunTypeDependentMapping:
					fprintf ( FILE_LOG, "Dependent Mapping" );

					if ( presPort )
					{
						fprintf ( FILE_STDOUT, ", preserves ports" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", random port" );
					}

					if ( hairpin  )
					{
						fprintf ( FILE_STDOUT, ", will hairpin" );
					}
					else
					{
						fprintf ( FILE_STDOUT, ", no hairpin" );
					}

					retval[nic] = 0x08;
					break;

				case StunTypeFirewall:
					fprintf ( FILE_STDOUT, "Firewall" );
					retval[nic] = 0x0A;
					break;

				case StunTypeBlocked:
					fprintf ( FILE_STDOUT, "Blocked or could not reach STUN server" );
					retval[nic] = 0x0C;
					break;

				default:
					fprintf ( FILE_STDOUT, "%d unknown NAT type", stype );
					retval[nic] = 0x0E;  // Unknown NAT type
					break;
			}

			fprintf ( FILE_STDOUT, "\t" );
			fflush ( FILE_STDOUT );

			if ( hairpin )
			{
				retval[nic] |= 0x10;
			}

#if 0

			if ( presPort )
			{
				retval[nic] |= 0x01;
			}

#endif
		}
	} // end of for loop

	fprintf ( FILE_STDOUT, "\n" );
	ret = 0;

	for ( i = numNic - 1; i >= 0; i-- )
	{
		if ( retval[i] == -1 )
		{
			ret = 0xFFFFFFFF;
			break;
		}

		ret = ret << 8;
		ret = ret | ( retval[i] & 0xFF );
	}

	fprintf ( FILE_STDOUT, "Return value is %#x\n", ret );
	return ret;
}

/*************************************************
Function: STUN_get_mapped_ip
Description: get public ip.(mapped ip)
Input: servername,verboseornot
Output: mapaddr
Return: returns  -1 when fail
Others: otherwise this function returns the fd it uses,the addr would be in the 2nd parameter.
					eg. 218.18.232.145:52673

** WARNING!!!
   you need to close fd when this function returns a nonzero value.
*************************************************/

int
STUN_get_mapped_ip ( char *servername, char *mapaddr, int verboseornot )
{
	if ( servername == NULL )
	{
		fprintf ( FILE_STDERR, "servername == NULL\n" );
		return -1;
	}

	int testNum = 0;
	int verbose = verboseornot;
	StunAddress4 stunServerAddr;
	stunServerAddr.addr = 0;
	int srcPort = 0;
	StunAddress4 sAddr[MAX_NIC];
	int numNic = 0;
	UInt32 ret = 0;
	int nic = 0;
	int i = 0;
	int presPort = FALSE;
	int hairpin = FALSE;
	StunAddress4 mappedAddr = {0, 0};
	int UDPfd = -1;

	if ( -1 == initNetwork() )
	{
		return -1;
	}

	for ( i = 0; i < MAX_NIC; i++ )
	{
		sAddr[i].addr = 0;
		sAddr[i].port = 0;
	}

	ret = stunParseServerName ( servername, stunServerAddr );

	if ( ret != TRUE )
	{
		fprintf ( FILE_STDERR, "%s is not a valid host name\n", servername );
		return -1;
	}

	if ( srcPort == 0 )
	{
		srcPort = stunRandomPort();
	}

	if ( numNic == 0 )
	{
		// use default
		numNic = 1;
	}

	for ( nic = 0; nic < numNic; nic++ )
	{
		sAddr[nic].port = srcPort;

		if ( stunServerAddr.addr == 0 )
		{
			return ( -1 );
		}

		if ( testNum == 0 )
		{
			mappedAddr = stunNatTypeTestI ( stunServerAddr, verbose, &presPort, &hairpin,
											srcPort, &sAddr[nic], &UDPfd );
		}
	}

	if ( ( 0 == mappedAddr.addr ) || ( 0 == mappedAddr.port ) )
	{
		return -1;
	}
	else
	{
		parseStunAddress4 ( mapaddr, mappedAddr );
	}

	return UDPfd;
}


/*************************************************
Function: _STUN_P2P_penetrable
Description: App calls this function for determination of Relay or P2P.
Input: natType
Output: none
Return: 0 means non-penetrable . 1 means penetrable, -1 means error
Others:
*************************************************/

static int
_STUN_P2P_penetrable ( int natTypeApp, int natTypeDUT )
{
	/*
	{
		StunTypeFailure 			-1;
		StunTypeUnknown 			0xEE;
		StunTypeOpen 				0x00;
		StunTypeIndependentFilter 	0x02;
		StunTypeDependentFilter 	0x04;
		StunTypePortDependedFilter 	0x06;
		StunTypeDependentMapping 	0x08;
		StunTypeFirewall 			0x0A;
		StunTypeBlocked 			0x0C;
		WouldHairpin 				0x10;
		Unkown NAT type 			0x0E;
	}
	*/
	if ( ( natTypeApp == 0x0C ) ||
			( natTypeDUT == 0x0C ) )
	{
		return 0;
	}

	//neglect Hairpin
	natTypeApp &= 0x0F;
	natTypeDUT &= 0x0F;

	if ( ( natTypeApp == 0x00 ) || ( natTypeApp == 0x02 ) || ( natTypeApp == 0x04 ) ||
			( natTypeDUT == 0x00 ) || ( natTypeDUT == 0x02 ) || ( natTypeDUT == 0x04 ) )
	{
		//one of them has open or independentFilter is penetrable
		return 1;
	}

	if ( ( natTypeApp == 0x06 ) && ( natTypeDUT == 0x06 ) )
	{
		//Port Restricted
		return 1;
	}

	return 0;
}

/*************************************************
Function: _STUN_try_p2p
Description: App calls this function for determination of Relay or P2P.
Input: countLimit and DUT statis
Output: none
Return: 0 means must_relay . 1 try P2P, -1 means error
Others:
*************************************************/

static int
_STUN_try_p2p ( int clientRelayCount, int clientP2PCount, int countLimit )
{
	if ( ( countLimit <= 0 ) || ( clientRelayCount < 0 ) || ( clientP2PCount < 0 ) )
	{
		return -1;
	}
	
	if(1 != countLimit)
	{
		printf("1 != countLimit. \n");
		return -1;
	}
	
	if(clientRelayCount == 0  && clientP2PCount == 0)
	{
		return 1;	
	}
	else
	{
		return 0;
	}

	return -1;
}


/*************************************************
Function: STUN_determine_relayp2p
Description: App calls this function for determination of Relay or P2P.
Input: natType, DUT relay and P2P count , DUT count limit;
Output: Relay or P2P
Return: 0 means relay. 1 means p2p, -1 means error, should use relay
Others:
*************************************************/

int
STUN_determine_relayp2p ( int natTypeApp, int natTypeDUT ,
						  int clientRelayCount, int clientP2PCount, int countLimit , int relayHold )
{
	if ( clientRelayCount > relayHold )
	{
		return -1;
	}

	int ret = 0;
	//直接根据p2p and relay count return determine choice;
	ret = _STUN_try_p2p ( clientRelayCount, clientP2PCount, countLimit);

	if ( ret < 0 )
	{
		return -1;
	}

	if ( ret == 0 )
	{
		//must relay
		return 0;
	}

	//when count is ok, determine by NAT type;
	ret = _STUN_P2P_penetrable ( natTypeApp, natTypeDUT );

	if ( ret < 0 )
	{
		return -1;
	}

	if ( ret == 0 )
	{
		//non-penetrable use relay
		return 0;
	}

	return 1;
}

/*************************************************
Function: STUN_build_binding_request
Description: build simple binding request(without sending), user should send the request by yourself
Input: None
Output: buf and buflen
Return: returns -1 on fail, # of chars in buf when success
Others:
*************************************************/
int STUN_build_binding_request ( char *buf, int buflen )
{
	StunMessage req;
	StunAtrString username, password;
	int changeIP = FALSE, changePort = FALSE;
	int testNum = 1;
	int len;

	if ( !buf || buflen < BINDING_REQUEST_MIN_SIZE )
	{
		return -1;
	}

	memset ( &req, 0, sizeof ( StunMessage ) );
	username.sizeValue = 0;
	password.sizeValue = 0;
	stunBuildReqSimple ( &req, username, changePort, changeIP, testNum );
	len = stunEncodeMessage ( req, buf, buflen, password, 0 );

	if ( len <= 0 || len > buflen )
	{
		return -1;
	}
	else
	{
		return len;
	}
}

/*************************************************
Function: STUN_parse_binding_response
Description: parse bind response.
Input: msg, msglen,verboseornot
Output: mapaddr
Return: 0 when success. -1 when fail
Others:when this function returns success ,the addr would be in the 3rd parameter.
					eg. 218.18.232.145:52673
*************************************************/

int STUN_parse_binding_response ( char *msg, int msgLen, char *mapaddr, int verboseornot )
{
	StunMessage resp;
	StunAddress4 testImappedAddr;
	memset ( &testImappedAddr, 0, sizeof ( testImappedAddr ) );
	memset ( &resp, 0, sizeof ( StunMessage ) );

	if ( FALSE == stunParseMessage ( msg, msgLen, resp, verboseornot ) )
	{
		return -1;
	}

	if ( verboseornot )
	{
		fprintf ( FILE_LOG, "Received message of type %d id=%d\n",
				  resp.msgHdr.msgType, ( int ) ( resp.msgHdr.id.octet[0] ) );
	}

	if ( 1 !=  resp.msgHdr.id.octet[0] )
	{
		//this msg ought to be a response to SendTestI.
		fprintf ( FILE_LOG, "resp.msgHdr.id.octet[0] is %c\n", resp.msgHdr.id.octet[0] );
		return -1;
	}
	else
	{
		testImappedAddr.addr = resp.mappedAddress.ipv4.addr;
		testImappedAddr.port = resp.mappedAddress.ipv4.port;
	}

	parseStunAddress4 ( mapaddr, testImappedAddr );
	return 0;
}
