
/*****************************************************************************
Copyright? 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
File name: stun.h
Description: stunclient. 给出libstun接口
Author: AaronChen
Version: in code
Date: continuing
History: in svn
*****************************************************************************/


#ifndef STUN_H
#define STUN_H

#ifdef __cplusplus
extern "C"
{
#endif

/*************************************************
Function: STUN_nattest_init
Description: init the STUN process. start the feed process;
Input: globals
Output: file
Return: returns 0 when init work finished
Others:
*************************************************/
int
STUN_nattest_init ( char *servername );

/*************************************************
Function: STUN_nattest_finish
Description: Closing STUN process. send feed stop message;
Input: globals
Output: file
Return: when P2P success ,the STATUS would be 1. otherwise would be 0
Others: returns 0 when closing-up work finished
*************************************************/
int
STUN_nattest_finish ( char *servername, int status );


/*
when the verbose is TRUE lib will cout log ,vice versa.

the return val defines here:
{
	StunTypeFailure 			-1;
	StunTypeUnknown 			0xEE;
	StunTypeOpen 				0x00;
	StunTypeIndependentFilter	0x02;
	StunTypeDependentFilter 	0x04;
	StunTypePortDependedFilter 	0x06;
	StunTypeDependentMapping 	0x08;
	StunTypeFirewall 			0x0A;
	StunTypeBlocked 			0x0C;
	WouldHairpin 				0x10;
	Unkown NAT type 			0x0E;
}
After we commit a servername to getnattype() it will return the type value in 1.5 second(my linux desk OS).
When the type in {StunTypeOpen, StunTypeDependentFilter, StunTypeIndependentFilter, StunTypePortDependedFilter},
NAT penetrate is highly possible. It's strongly recommended that we should try more times for P2P.
When the type in {StunTypeFailure, StunTypeUnknown, Unkown NAT type},
the possible reason is that server may currently busy. We can try the test again.
When the type in {StunTypeFirewall, StunTypeBlocked},
it is nearly impossible to complish NAT penetrate.
When the type is {StunTypeDependentMapping}, the penetration success depends on peer's NAT type.

*/
#define	NAT_TYPE_OPEN					0x00
#define	NAT_TYPE_INDEPENDENT_FILTER		0X02
#define	NAT_TYPE_DEPENDENT_FILTER		0x04
#define	NAT_TYPE_PORT_DEPENDENT_FILTER	0x06
#define	NAT_TYPE_DEPENDENT_MAPPING		0x08
#define	NAT_TYPE_FIREWALL				0x0A
#define	NAT_TYPE_BLOCKED				0x0C
#define	NAT_TYPE_UNKNOWN				0x0E
int
STUN_get_nat_type ( char *servername, int verbose );


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
STUN_get_mapped_ip ( char *servername, char *mapaddr, int verboseornot );


/*************************************************
Function: STUN_build_binding_request
Description: build simple binding request(without sending), user should send the request by yourself
Input: None
Output: buf and buflen
Return: returns -1 on fail, # of chars in buf when success
Others:
*************************************************/

int
STUN_build_binding_request ( char *buf, int buflen );

/*************************************************
Function: STUN_parse_binding_response
Description: parse bind response.
Input: msg, msglen,verboseornot
Output: mapaddr
Return: 0 when success. -1 when fail
Others:when this function returns success ,the addr would be in the 3rd parameter.
					eg. 218.18.232.145:52673
*************************************************/

int
STUN_parse_binding_response ( char *msg, int msgLen, char *mapaddr, int verboseornot );

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
							int clientRelayCount, int clientP2PCount, int countLimit , int relayHold);


// 
// `STUN_get_nat_type' is a blocked API. 
// It will keep blocking for about 3 seconds when you call it.
// In some(most) situations, we need non-block APIs, so we asynchronous them and we have below APIs.
// 
// ------------------------------------------------------------------------
int STUN_init_async();

typedef void (*STUN_get_nat_type_cb)(int nat_type, void *arg);
int STUN_get_nat_type_async(char *servername, int verbose, 
					int timeout, STUN_get_nat_type_cb cb, void *arg);// timeout: in second

int STUN_clean_async();
// ========================================================================


#ifdef __cplusplus
}
#endif

#endif

