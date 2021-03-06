/*
 * (C) 2006 by Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#include "internal/internal.h"

/*
 * XML output sample:
 *
 * <flow>
 * 	<meta direction="original">
 * 		<layer3 protonum="2" protoname="IPv4">
 * 			<src>192.168.0.1</src>
 * 			<dst>192.168.0.2</dst>
 * 		</layer3>
 * 		<layer4 protonum="16" protoname"udp">
 * 			<sport>80</sport>
 * 			<dport>56665</dport>
 * 		</layer4>
 * 		<counters>
 * 			<bytes>10</bytes>
 * 			<packets>1</packets>
 * 		</counters>
 * 	</meta>
 * 	<meta direction="reply">
 * 		<layer3 protonum="2" protoname="IPv4">
 * 			<src>192.168.0.2</src>
 * 			<dst>192.168.0.1</dst>
 * 		</layer3>
 * 		<layer4 protonum="16" protoname="udp">
 * 			<sport>80</sport>
 * 			<dport>56665</dport>
 * 		</layer4>
 * 		<counters>
 * 			<bytes>5029</bytes>
 * 			<packets>12</packets>
 *		</counters>
 * 	</meta>
 * 	<meta direction="independent">
 * 		<state>ESTABLISHED</state>
 * 		<timeout>100</timeout>
 * 		<mark>1</mark>
 * 		<secmark>0</secmark>
 * 		<id>453281439</id>
 * 		<use>1</use>
 * 		<assured/>
 * 	</meta>
 * </flow>
 */

enum {
	__ADDR_SRC = 0,
	__ADDR_DST,
};

static const char *__proto2str(u_int8_t protonum)
{
	return proto2str[protonum] ? proto2str[protonum] : "unknown";
}

static const char *__l3proto2str(u_int8_t protonum)
{
	return l3proto2str[protonum] ? l3proto2str[protonum] : "unknown";
}

static int __snprintf_ipv4_xml(char *buf,
			       unsigned int len,
			       const struct __nfct_tuple *tuple,
			       unsigned int type)
{
	struct in_addr addr = { 
		.s_addr = (type == __ADDR_SRC) ? tuple->src.v4 : tuple->dst.v4,
	};

	return snprintf(buf, len, "%s", inet_ntoa(addr));
}

static int __snprintf_ipv6_xml(char *buf,
			       unsigned int len,
			       const struct __nfct_tuple *tuple,
			       unsigned int type)
{
	struct in6_addr addr;
	static char tmp[INET6_ADDRSTRLEN];
	const void *p = (type == __ADDR_SRC) ? &tuple->src.v6 : &tuple->dst.v6;

	memcpy(&addr, p, sizeof(struct in6_addr));

	if (!inet_ntop(AF_INET6, &addr, tmp, sizeof(tmp)))
		return -1;

	return snprintf(buf, len, "%s", tmp);
}

static int __snprintf_addr_xml(char *buf,
			       unsigned int len,
			       const struct __nfct_tuple *tuple, 
			       unsigned int type)
{
	int ret;
	unsigned int size = 0, offset = 0;

	switch(type) {
	case __ADDR_SRC:
		ret = snprintf(buf, len, "<src>");
		BUFFER_SIZE(ret, size, len, offset);
		break;
	case __ADDR_DST:
		ret = snprintf(buf+offset, len, "<dst>");
		BUFFER_SIZE(ret, size, len, offset);
		break;
	}

	switch (tuple->l3protonum) {
	case AF_INET:
		ret = __snprintf_ipv4_xml(buf+offset, len, tuple, type);
		BUFFER_SIZE(ret, size, len, offset);
		break;
	case AF_INET6:
		ret = __snprintf_ipv6_xml(buf+offset, len, tuple, type);
		BUFFER_SIZE(ret, size, len, offset);
		break;
	}

	switch(type) {
	case __ADDR_SRC:
		ret = snprintf(buf+offset, len, "</src>");
		BUFFER_SIZE(ret, size, len, offset);
		break;
	case __ADDR_DST:
		ret = snprintf(buf+offset, len, "</dst>");
		BUFFER_SIZE(ret, size, len, offset);
		break;
	}

	return size;
}

static int __snprintf_proto_xml(char *buf,
				unsigned int len,
				const struct __nfct_tuple *tuple, 
				unsigned int type)
{
	int ret = 0;
	unsigned int size = 0, offset = 0;

	switch(tuple->protonum) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
	case IPPROTO_UDPLITE:
	case IPPROTO_SCTP:
	case IPPROTO_DCCP:
		if (type == __ADDR_SRC) {
			ret = snprintf(buf, len, "<sport>%u</sport>", 
				       ntohs(tuple->l4src.tcp.port));
			BUFFER_SIZE(ret, size, len, offset);
		} else {
			ret = snprintf(buf, len, "<dport>%u</dport>",
				       ntohs(tuple->l4dst.tcp.port));
			BUFFER_SIZE(ret, size, len, offset);
		}
		break;
	case IPPROTO_GRE:
		if (type == __ADDR_SRC) {
			ret = snprintf(buf, len, "<srckey>0x%x</srckey>", 
				       ntohs(tuple->l4src.all));
			BUFFER_SIZE(ret, size, len, offset);
		} else {
			ret = snprintf(buf, len, "<dstkey>0x%x</dstkey>",
				       ntohs(tuple->l4dst.all));
			BUFFER_SIZE(ret, size, len, offset);
		}
		break;
	}

	return ret;
}

static int __snprintf_counters_xml(char *buf,
				   unsigned int len,
				   const struct nf_conntrack *ct,
				   unsigned int type)
{
	int ret;
	unsigned int size = 0, offset = 0;

	ret = snprintf(buf, len, "<packets>%llu</packets>",
		       (unsigned long long)ct->counters[type].packets);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<bytes>%llu</bytes>",
		       (unsigned long long)ct->counters[type].bytes);
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

static int
__snprintf_timestamp_start(char *buf, unsigned int len,
			   const struct nf_conntrack *ct)
{
	int ret;
	unsigned int size = 0, offset = 0;

	ret = snprintf(buf, len, "<start>%llu</start>",
		       (unsigned long long)ct->timestamp.start);
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

static int
__snprintf_timestamp_stop(char *buf, unsigned int len,
			  const struct nf_conntrack *ct)
{
	int ret;
	unsigned int size = 0, offset = 0;

	ret = snprintf(buf, len, "<stop>%llu</stop>",
		       (unsigned long long)ct->timestamp.stop);
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

static int
__snprintf_deltatime_now(char *buf, unsigned int len,
			 const struct nf_conntrack *ct)
{
	int ret;
	unsigned int size = 0, offset = 0;
	time_t now, delta_time;

	time(&now);
        delta_time = now - (time_t)(ct->timestamp.start / NSEC_PER_SEC);

	ret = snprintf(buf+offset, len, "<deltatime>%llu</deltatime>",
		(unsigned long long)delta_time);
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

static int
__snprintf_deltatime(char *buf, unsigned int len, const struct nf_conntrack *ct)
{
	int ret;
	unsigned int size = 0, offset = 0;
	time_t delta_time = (time_t)((ct->timestamp.stop -
				ct->timestamp.start) / NSEC_PER_SEC);

	ret = snprintf(buf+offset, len, "<deltatime>%llu</deltatime>",
		(unsigned long long)delta_time);
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

static int
__snprintf_localtime_xml(char *buf, unsigned int len, const struct tm *tm)
{
	int ret = 0;
	unsigned int size = 0, offset = 0;

	ret = snprintf(buf+offset, len, "<hour>%d</hour>", tm->tm_hour);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<min>%02d</min>", tm->tm_min);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<sec>%02d</sec>", tm->tm_sec);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<wday>%d</wday>", tm->tm_wday + 1);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<day>%d</day>", tm->tm_mday);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<month>%d</month>", tm->tm_mon + 1);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "<year>%d</year>", 1900 + tm->tm_year);
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

static int __snprintf_tuple_xml(char *buf,
				unsigned int len,
				const struct nf_conntrack *ct,
				unsigned int dir)
{
	int ret;
	unsigned int size = 0, offset = 0;
	const struct __nfct_tuple *tuple = &ct->tuple[dir];

	ret = snprintf(buf, len, "<meta direction=\"%s\">",
		       dir == __DIR_ORIG ? "original" : "reply");
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, 
		       "<layer3 protonum=\"%d\" protoname=\"%s\">",
		       tuple->l3protonum, __l3proto2str(tuple->l3protonum));
	BUFFER_SIZE(ret, size, len, offset);

	ret = __snprintf_addr_xml(buf+offset, len, tuple, __DIR_ORIG);
	BUFFER_SIZE(ret, size, len, offset);

	ret = __snprintf_addr_xml(buf+offset, len, tuple, __DIR_REPL);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "</layer3>");
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, 
		       "<layer4 protonum=\"%d\" protoname=\"%s\">",
		       tuple->protonum, __proto2str(tuple->protonum));
	BUFFER_SIZE(ret, size, len, offset);

	ret = __snprintf_proto_xml(buf+offset, len, tuple, __DIR_ORIG);
	BUFFER_SIZE(ret, size, len, offset);

	ret = __snprintf_proto_xml(buf+offset, len, tuple, __DIR_REPL);
	BUFFER_SIZE(ret, size, len, offset);

	ret = snprintf(buf+offset, len, "</layer4>");
	BUFFER_SIZE(ret, size, len, offset);

	if (test_bit(ATTR_ORIG_COUNTER_PACKETS, ct->set) &&
	    test_bit(ATTR_ORIG_COUNTER_BYTES, ct->set)) {
		ret = snprintf(buf+offset, len, "<counters>");
		BUFFER_SIZE(ret, size, len, offset);

		ret = __snprintf_counters_xml(buf+offset, len, ct, dir);
		BUFFER_SIZE(ret, size, len, offset);

		ret = snprintf(buf+offset, len, "</counters>");
		BUFFER_SIZE(ret, size, len, offset);
	}

	ret = snprintf(buf+offset, len, "</meta>");
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}

int __snprintf_conntrack_xml(char *buf,
			     unsigned int len,
			     const struct nf_conntrack *ct,
			     const unsigned int msg_type,
			     const unsigned int flags) 
{
	int ret = 0;
	unsigned int size = 0, offset = 0;

	switch(msg_type) {
		case NFCT_T_NEW:
			ret = snprintf(buf, len, "<flow type=\"new\">");
			break;
		case NFCT_T_UPDATE:
			ret = snprintf(buf, len, "<flow type=\"update\">");
			break;
		case NFCT_T_DESTROY:
			ret = snprintf(buf, len, "<flow type=\"destroy\">");
			break;
		default:
			ret = snprintf(buf, len, "<flow>");
			break;
	}

	BUFFER_SIZE(ret, size, len, offset);

	ret = __snprintf_tuple_xml(buf+offset, len, ct, __DIR_ORIG);
	BUFFER_SIZE(ret, size, len, offset);

	ret = __snprintf_tuple_xml(buf+offset, len, ct, __DIR_REPL);
	BUFFER_SIZE(ret, size, len, offset);

	if (test_bit(ATTR_TCP_STATE, ct->set) ||
	    test_bit(ATTR_SCTP_STATE, ct->set) ||
	    test_bit(ATTR_DCCP_STATE, ct->set) ||
	    test_bit(ATTR_TIMEOUT, ct->set) ||
	    test_bit(ATTR_MARK, ct->set) ||
	    test_bit(ATTR_SECMARK, ct->set) ||
	    test_bit(ATTR_ZONE, ct->set) ||
	    test_bit(ATTR_USE, ct->set) ||
	    test_bit(ATTR_STATUS, ct->set) ||
	    test_bit(ATTR_ID, ct->set) ||
	    test_bit(ATTR_TIMESTAMP_START, ct->set) ||
	    test_bit(ATTR_TIMESTAMP_STOP, ct->set)) {
		ret = snprintf(buf+offset, len, 
			       "<meta direction=\"independent\">");
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_TCP_STATE, ct->set)) {
		ret = snprintf(buf+offset, len, "<state>%s</state>",
			       ct->protoinfo.tcp.state < TCP_CONNTRACK_MAX ?
			       states[ct->protoinfo.tcp.state] :
			       states[TCP_CONNTRACK_NONE]);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_SCTP_STATE, ct->set)) {
		ret = snprintf(buf+offset, len, "<state>%s</state>",
			       ct->protoinfo.sctp.state < SCTP_CONNTRACK_MAX ?
			       states[ct->protoinfo.sctp.state] :
			       states[SCTP_CONNTRACK_NONE]);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_DCCP_STATE, ct->set)) {
		ret = snprintf(buf+offset, len, "<state>%s</state>",
			       ct->protoinfo.sctp.state < DCCP_CONNTRACK_MAX ?
			       states[ct->protoinfo.dccp.state] :
			       states[DCCP_CONNTRACK_NONE]);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_TIMEOUT, ct->set)) {
		ret = snprintf(buf+offset, len,
				"<timeout>%u</timeout>", ct->timeout);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_MARK, ct->set)) {
		ret = snprintf(buf+offset, len, "<mark>%u</mark>", ct->mark);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_SECMARK, ct->set)) {
		ret = snprintf(buf+offset, len, 
				"<secmark>%u</secmark>", ct->secmark);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_SECCTX, ct->set)) {
		ret = snprintf(buf+offset, len,
				"<secctx>%s</secctx>", ct->secctx);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_ZONE, ct->set)) {
		ret = snprintf(buf+offset, len, "<zone>%u</zone>", ct->zone);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_USE, ct->set)) {
		ret = snprintf(buf+offset, len, "<use>%u</use>", ct->use);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_ID, ct->set)) {
		ret = snprintf(buf+offset, len, "<id>%u</id>", ct->id);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_STATUS, ct->set)
	    && ct->status & IPS_ASSURED) {
		ret = snprintf(buf+offset, len, "<assured/>");
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_STATUS, ct->set) 
	    && !(ct->status & IPS_SEEN_REPLY)) {
		ret = snprintf(buf+offset, len, "<unreplied/>");
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (flags & NFCT_OF_TIMESTAMP) {
		if (test_bit(ATTR_TIMESTAMP_START, ct->set) ||
		    test_bit(ATTR_TIMESTAMP_STOP, ct->set)) {
			ret = snprintf(buf+offset, len, "<timestamp>");
			BUFFER_SIZE(ret, size, len, offset);
		}
		if (test_bit(ATTR_TIMESTAMP_START, ct->set)) {
	 		ret = __snprintf_timestamp_start(buf+offset, len, ct);
			BUFFER_SIZE(ret, size, len, offset);
		}
		if (test_bit(ATTR_TIMESTAMP_STOP, ct->set)) {
	 		ret = __snprintf_timestamp_stop(buf+offset, len, ct);
			BUFFER_SIZE(ret, size, len, offset);
		}
		if (test_bit(ATTR_TIMESTAMP_START, ct->set) ||
		    test_bit(ATTR_TIMESTAMP_STOP, ct->set)) {
			ret = snprintf(buf+offset, len, "</timestamp>");
			BUFFER_SIZE(ret, size, len, offset);
		}
	}
	if (test_bit(ATTR_TIMESTAMP_START, ct->set) &&
	    test_bit(ATTR_TIMESTAMP_STOP, ct->set)) {
		ret = __snprintf_deltatime(buf+offset, len, ct);
		BUFFER_SIZE(ret, size, len, offset);
	} else if (test_bit(ATTR_TIMESTAMP_START, ct->set)) {
		ret = __snprintf_deltatime_now(buf+offset, len, ct);
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (test_bit(ATTR_TCP_STATE, ct->set) ||
	    test_bit(ATTR_SCTP_STATE, ct->set) ||
	    test_bit(ATTR_DCCP_STATE, ct->set) ||
	    test_bit(ATTR_TIMEOUT, ct->set) ||
	    test_bit(ATTR_MARK, ct->set) ||
	    test_bit(ATTR_SECMARK, ct->set) ||
	    test_bit(ATTR_ZONE, ct->set) ||
	    test_bit(ATTR_USE, ct->set) ||
	    test_bit(ATTR_STATUS, ct->set) ||
	    test_bit(ATTR_ID, ct->set) ||
	    test_bit(ATTR_TIMESTAMP_START, ct->set) ||
	    test_bit(ATTR_TIMESTAMP_STOP, ct->set)) {
	    	ret = snprintf(buf+offset, len, "</meta>");
		BUFFER_SIZE(ret, size, len, offset);
	}

	if (flags & NFCT_OF_TIME) {
		time_t t;
		struct tm tm;

		t = time(NULL);
		if (localtime_r(&t, &tm) == NULL)
			goto err_out;

		ret = snprintf(buf+offset, len, "<when>");
		BUFFER_SIZE(ret, size, len, offset);

		ret = __snprintf_localtime_xml(buf+offset, len, &tm);
		BUFFER_SIZE(ret, size, len, offset);

		ret = snprintf(buf+offset, len, "</when>");
		BUFFER_SIZE(ret, size, len, offset);
	}

err_out:
	ret = snprintf(buf+offset, len, "</flow>");
	BUFFER_SIZE(ret, size, len, offset);

	return size;
}
