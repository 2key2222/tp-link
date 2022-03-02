#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <stdarg.h>
#include "queue.h"

#define SERV_PORT 53
#define MAXLINE 600

struct pointer{
	void *p;
	LIST_ENTRY(pointer) link;
};

static UINT32 l_dbglvl = LOG_PRI_NOTICE;
static UINT32 l_sysloglvl = LOG_PRI_NOTICE;
static char use_syslog = 0;

LIST_HEAD(pointer_list, pointer);

struct offset{
	uint16_t offset;
	LIST_ENTRY(offset) link;
};

LIST_HEAD(offset_list, offset);
/*copy a dns name from src mesg to dsc mesg, dsc buffer volume 
 *is dlen bytes.
 *on success, return the number of bytes copied, else return -1
 */
int
namecpy(void *src, void *dsc, uint32_t dlen, struct pointer_list *labelplist_p)
{
	uint8_t *p, h;
	struct pointer *labelp_p; 
	int n;
	n = 0;
	while (1)
	{
		p = src;
		h = *p;
		if ( h == 0)
		{
			if (dlen < 1)
				return -1;
			memcpy(dsc, src, 1);
			n += 1;
			break;
		}
		else if ((h & 0xc0) == 0)
		{
			if (dlen < h + 1)
				return -1;
			memcpy(dsc, src, h + 1);
			src += h + 1;
			dsc += h + 1;
			dlen -= h + 1;
			n += h + 1;
		}
		else if ( (h & 0xc0) == 0xc0)
		{
			if (dlen < 2)
				return -1;
			labelp_p = (struct pointer *)malloc(sizeof(struct pointer));
			labelp_p -> p = dsc;
			LIST_INSERT_HEAD(labelplist_p, labelp_p, link);
			memcpy(dsc, src, 2);
			n += 2;
			break;
		}
		else
		{
			ividns_log_notice("Err:  label starts with neither 00 or 11");
			return -1;
		}
	}
	return n;
}
/*copy question section from src mesg to dsc mesg, dsc buffer volume
 *is dlen bytes.
 *on success, return the number of bytes copied, else return -1
 */
int
query_cpy(void *src, void *dsc, uint32_t dlen, struct pointer_list *labelplist_p)
{
	int n;
	n = namecpy(src, dsc, dlen, labelplist_p);
	if (n < 0)
		return n;
	dlen -= n;
	src += n;
	dsc += n;
	if (dlen >= 4)
	{
		memcpy(dsc, src, 4);
		return n + 4;
	}
	else 
		return -1;
}
// return in network order
struct in6_addr
a2aaaa(in_addr_t *ap, struct in6_addr *prefixp, int prefixlen)
{
	struct in6_addr r;
	int i;

	for(i = 0; i < 4; i++)
	{	
		r.s6_addr32[i] = 0;
		if ((prefixlen / 32) == i)
			r.s6_addr32[i] = (*ap) << (prefixlen % 32);
		if ((prefixlen / 32) == (i - 1))
			r.s6_addr32[i] = (*ap) >> (32 - (prefixlen % 32)); 
		r.s6_addr32[i] += prefixp->s6_addr32[i];
	}
	return r;
}
/*on success return 0, *psrc, *pdsc set to the mem addr after copy
 *else return -1
 *som mean start of message, just used to calculate offset when a record is
 *turned to aaaa
 */
int
rrcpy(void **psrc, void **pdsc, void *edsc, struct pointer_list *labelplist_p, struct offset_list *a_list_p, const void *som, struct in6_addr *prefixp, int prefixlen)
{
	int n,r;
	uint16_t *p, *rdlenp, *typep;
	uint16_t type, class, rdlen;
	in_addr_t a, *ap;
	struct in6_addr aaaa;
	struct offset *offset_p;
	n = 0;
	r = namecpy(*psrc, *pdsc, edsc - (*pdsc), labelplist_p);
	if (r < 0)
		return r;
	n += r;
	*psrc += r;
	*pdsc += r;
	if ((edsc - (*pdsc)) < 10)
		return -1;
	memcpy(*pdsc, *psrc, 10);
	typep = *pdsc;
	p = *psrc;
	type = ntohs(*p);
	p += 1;
	class = ntohs(*p);
	p += 3;
	rdlen = ntohs(*p);
	rdlenp = *pdsc + 8;
	*psrc += 10;
	*pdsc += 10;
	n += 10;
	if (class != 1)
		if ((edsc - (*pdsc)) < rdlen)
			return -1;
		else
		{
			memcpy(*pdsc, *psrc, rdlen);
			*pdsc += rdlen;
			*psrc += rdlen;
			n += rdlen;
			return n;
		}
	//now class == 1
	switch(type)
	{
		case 1:  //A record
			*typep = htons(28);
			ap = *psrc;
			aaaa = a2aaaa(ap, prefixp, prefixlen);
			//add a node in a_list
			offset_p = (struct offset *)malloc(sizeof(struct offset));
			offset_p->offset = (*psrc) - som;
			LIST_INSERT_HEAD(a_list_p, offset_p, link);
			*psrc += 4;
			if ((edsc - (*pdsc)) < 16)
				return -1;
			memcpy(*pdsc, &aaaa, 16);
			*pdsc += 16;
			n += 16;
			*rdlenp = htons(16);
			break;
		case 2:
		case 5:
		case 12:
			r = namecpy(*psrc, *pdsc, edsc - (*pdsc), labelplist_p);
			if (r < 0)
				return r;
			n += r;
			*psrc += r;
			*pdsc += r;
			break;
		default:
			if ((edsc - (*pdsc)) < rdlen)
				return -1;
			else
			{
				memcpy(*pdsc, *psrc, rdlen);
				*pdsc += rdlen;
				*psrc += rdlen;
				n += rdlen;
			}
	}
	
	return n;
}

/*when this func is call, the content in msg is correct except some
 *label-pointer. lplist record addresses of all the label-pointers
 *alist record the offset of the "original dns msg" where a to aaaa
 *translation was taken place
 */
void
changelabelp(void *msg, struct pointer_list *lplistp, struct offset_list *alistp)
{
	struct pointer *pp;
	struct offset *op;
	uint16_t h,i, *hp;

	LIST_FOREACH(pp,lplistp, link)
	{
		hp = (uint16_t *)(pp->p);
		h = ntohs(*hp);
		h -= 0xc000;
		i = 0;
		LIST_FOREACH(op, alistp, link)
		{
			if((op->offset) < h)
				i += 12;
		}
		h += i;	
		*hp = htons(h + 0xc000);
	}
}
void free_plist(struct pointer_list *llistp)
{
	struct pointer *p, *nextp;
	nextp = LIST_FIRST(llistp);
	while (nextp)
	{
		 p = nextp;
		 nextp = LIST_NEXT(nextp, link);
		 free(p);
	}
}

void free_offlist(struct offset_list *olistp)
{
	struct offset *p, *nextp;
	nextp = LIST_FIRST(olistp);
	while (nextp)
	{
		p = nextp;
		nextp = LIST_NEXT(nextp, link);
		free(p);
	}
}

int
rendermsg(void *src, uint32_t slen, void *dsc, uint32_t dlen, struct in6_addr *prefixp, int prefixlen)
{
	int qdcnt,rrcnt;
	int i;
	struct pointer_list labelplist;  //label records the pointer list of "label pointer", for future use
	struct offset_list a_list;	//change records the pointer list of a records to be changed to a6 in src
	LIST_INIT(&a_list);
	LIST_INIT(&labelplist);
	
	int n,r;
	void *edsc, *psrc, *pdsc;
	edsc = dsc + dlen;
	psrc = src;
	pdsc = dsc;
	
	uint16_t *p;
	p = src;
	qdcnt = ntohs(*(p + 2));
	rrcnt = ntohs(*(p + 3)) + ntohs(*(p + 4)) + ntohs(*(p + 5));
	memcpy(pdsc, psrc, 12);
	
	pdsc += 12;
	psrc += 12;
	n = 12;
	for (i = 1;i <= qdcnt; i++)
	{
		r = query_cpy(psrc, pdsc, edsc-pdsc, &labelplist);
		if (r < 0)
			return r;
		n += r;
		psrc += r;
		pdsc += r;
	}
	for (i = 1; i <= rrcnt; i++)
	{
		r = rrcpy(&psrc, &pdsc, edsc, &labelplist, &a_list, src, prefixp, prefixlen);
		if (r < 0)
			return r;
		n += r;
	}	
	changelabelp(dsc, &labelplist, &a_list);
	free_plist(&labelplist);
	free_offlist(&a_list);
	return n;
}

void *
jmp_name(void *src)
{
	uint8_t *p, h;
	p = src;
	while (1)
	{
		h = *p;
		if ( h == 0)
		{
			return p + 1;
		}
		else if ((h & 0xc0) == 0)
		{
			p += h + 1;
		}
		else if ( (h & 0xc0) == 0xc0)
		{
			return p + 2;
		}
		else
		{
			printf("Err:  label starts with neither 00 or 11\n");
			return NULL;
		}
	}
}
//return -1 on err, 0 means no answer corresponds to qtype , otherwise 1
int 
detect_msg(void *src, uint16_t *qtype)
{

	uint16_t *p;
	void *p2;
	int qdcnt, ancnt,i;
	p = src;
	p2 = src;
	qdcnt = ntohs(*(p + 2));
	ancnt = ntohs(*(p + 3));
	p2 += 12;
	ividns_log_notice("pdcnt:%d,  ancnt:%d\n",(int)qdcnt,(int)ancnt);
	if (qdcnt != 1)
		return -1;
	p2 = jmp_name(p2);
	if (p2 == NULL)
		return -1;
	p = p2;
	*qtype = ntohs(*p);
	ividns_log_notice("qtype:%d\n",*qtype);
	p2 += 4;
	for (i = 0; i<ancnt; i++)
	{
		p2 = jmp_name(p2);
		if (p2 == NULL)
			return -1;
		p = p2;
		if (*qtype == ntohs(*p))
			return 1;
		p2 += 8;
		p = p2;
		p2 += ntohs(*p) + 2;
	}
	return 0;
}
void
changeqtype(void *src)
{
	uint16_t *p16;
	void *p;
	p = src;
	p += 12;
	p = jmp_name(p);
	p16 = p;
	if (ntohs(*p16) == 28)
		*p16 = htons(1);
	else
		*p16 = htons(28);
}
void
proxy(int recvsd, struct sockaddr *pcliaddr, socklen_t clilen, struct sockaddr *pdnsaddr, socklen_t dnslen, struct in6_addr *prefixp, int prefixlen)
{
	struct msghdr a;
	int n,n2,n6,r;
	int flag;
	int sendsd;
	uint16_t id, qtype;
	socklen_t len,len2;
	char mesg[MAXLINE];
	char mesg_rec[MAXLINE];
	char mesg_a6[MAXLINE];
//	char temp[INET6_ADDRSTRLEN];
//	struct in6_addr *p;
	signal(SIGCHLD, SIG_IGN);
	while(1)
	{
		ividns_log_notice("haha******game begins*********\n");
		flag = 0;
		len = clilen;
		len2 = dnslen;
		n = recvfrom(recvsd, mesg, MAXLINE, 0, pcliaddr, &len);
		id = ntohs(*((uint16_t *)mesg));
		if (fork() == 0)
		{
			//initiate a new socket sendsd
			if ((sendsd = socket(PF_INET6, SOCK_DGRAM, 0)) < 0)
			{
				ividns_log_notice("send socket generation err");
				exit(1);
			}	
			struct timeval tv;
			tv.tv_sec = 5;
			tv.tv_usec = 0;
			setsockopt(sendsd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
		
			sendto(sendsd, mesg, n, 0, pdnsaddr, len2);
			n2 = recvfrom(sendsd, mesg_rec, MAXLINE, 0, pdnsaddr, &len2);
			if (n2 <= 0){
				ividns_log_notice("recv from dns server Err\n");
				exit(1);
			}
			if(id != ntohs(*((uint16_t *)mesg_rec)))
			{
				ividns_log_notice("recv dns id not equal to send id\n");
				exit(1);
			}
			r = detect_msg(mesg_rec, &qtype);
			if (r < 0){
				ividns_log_notice("pls check the funtion detect_msg() \n");
				exit(1);
			}
			if ( r == 1 || qtype != 28)
			{
				sendto(recvsd, mesg_rec, n2, 0, pcliaddr, len);
				exit(0);
			}
			else
			{
				changeqtype(mesg);
				sendto(sendsd, mesg, n, 0, pdnsaddr, len2);
				n2 = recvfrom(sendsd, mesg_rec, MAXLINE, 0, pdnsaddr, &len2);
				if (n2 <= 0){
					ividns_log_notice("recv from dns server Err\n");
					exit(1);
				}
				if(id != ntohs(*((uint16_t *)mesg_rec)))
				{
					ividns_log_notice("recv dns id not equal to send id\n");
					exit(1);
				}
				changeqtype(mesg_rec);	
				n6 = rendermsg(mesg_rec, n, mesg_a6, MAXLINE, prefixp, prefixlen);
				if (n6 > 0)
				{
					sendto(recvsd, mesg_a6, n6, 0, pcliaddr, len);
					exit(0);
				}
				else
				{	
					ividns_log_notice("n6= %d",n6);
					exit(1);
				}
			}
		}
	}
}
void
print_usage()
{
	printf("\
Usage:dnsproxy [OPTIONS] dns_server_address\n\
OPTIONS:\n\
	-p, --prefix prefix:specify the prefix ipv6 address in the mapping\n\
	                    prefix take the form of <ipv6_addr>/<prefix_len>\n\
			    e.g. \"::\",\"2001:da8:ff00::/40\"\n\
			    default:  ::/96\n\
	-l dbglvl:       Set debug levle: 0-None;1-Error;2-Info;3-Debug;4-Cmd (default is Error)\n\
	-L sysloglvl:    Set debug levle: 0-7\n\
	-S               use syslog\n\
	-6		  : the dns_server_address is interpreted as ipv6 address\n\
	-h, --help:         to print out this usage\n");
}

int 
main(int argc, char **argv)
{
	int recvsd;
	int r;
	char *cp;
	char v6_str[INET6_ADDRSTRLEN];
	struct sockaddr_in6 proxyaddr, cliaddr, dnsaddr;
	struct in6_addr prefix;
	struct option long_options[] = {
		{"prefix", 1, 0, 'p'},
		{"help", 0, 0, 'h'},
		{0, 0, 0, 0}
	};
	int lopt_ind, prefixlen;
	int flag46;
	flag46 = 0;
	prefixlen = 96;
	strcpy(v6_str, "::");
	while(1)
	{
		r = getopt_long (argc, argv, "p:h6", long_options, &lopt_ind);
		if (r == -1)
			break;
		switch (r) {
			case 'p':
				cp = strchr(optarg, '/');
				if (cp != NULL)
				{
					strncpy(v6_str, optarg, cp - optarg);
					v6_str[cp - optarg] = 0;
					prefixlen = atoi(cp + 1);
					if (prefixlen < 0 || prefixlen > 96)
					{
							ividns_log_notice("Prefix lengh should be set btw 0 and 96\n");
							exit(1);
					}
				}
				else
					strcpy(v6_str, optarg);
				break;
			case '6':
				flag46 = 1;
				break;
			case 'S':
				use_syslog = 1;
				break;

        			case 'l':
           			l_dbglvl = atoi(optarg);
            			if ((l_dbglvl < DBG_LEVEL_NONE) || (l_dbglvl > DBG_LEVEL_MAX))
				{
					ividns_log_notice("Incorrect number of debug levle");
					print_usage();
					exit(1);
				}
            			break;

			case 'L':
				l_sysloglvl = atoi(optarg);
				if ((l_sysloglvl < LOG_PRI_EMERG) || (l_sysloglvl > LOG_PRI_DEBUG))
				{
					ividns_log_notice("Incorrect number of debug levle");
					print_usage();
					exit(1);
				}
				break;
			case 'h':
			case '?':
				print_usage();
				exit(1);
			default:
				break;
	
		}
	}

	if ( (r = inet_pton(AF_INET6, v6_str, &prefix)) != 1)
	{
		ividns_log_notice("please check your prefix:%s\n", optarg);
		exit(1);
	}
	if (argc - optind != 1)
	{
		ividns_log_notice("optind= %d",optind);
		print_usage();
		exit(1);
	}
	/**********INITIALIZE**********/

	memset(&proxyaddr, 0, sizeof(proxyaddr));
	proxyaddr.sin6_family = AF_INET6;
	proxyaddr.sin6_addr = in6addr_any;
	proxyaddr.sin6_port = htons(SERV_PORT);

	memset(&cliaddr, 0, sizeof(cliaddr));
	memset(&dnsaddr, 0, sizeof(dnsaddr));
	dnsaddr.sin6_family = AF_INET6;
	dnsaddr.sin6_addr = in6addr_any;
	dnsaddr.sin6_port = htons(SERV_PORT);
	
	if(flag46 == 0)	/*generate v4-mapped v6 address for dns*/
	{
		strcpy(v6_str, "::ffff:");
		strcat(v6_str, argv[optind]);
	}
	else
		strcpy(v6_str, argv[optind]);
	if (inet_pton(AF_INET6, v6_str, & dnsaddr.sin6_addr) <= 0)
	{
		ividns_log_notice("please check the dns address");
		exit(1);
	}

	/*generate sockfd and bind (separate recv packets and sending packets*/
	if ((recvsd = socket(PF_INET6, SOCK_DGRAM, 0)) < 0)
	{
		ividns_log_notice("recv socket generation err");
		exit(1);
	}
	/*set recv timeout when recv from dns server*/
	
	if (bind(recvsd, (struct sockadd *)(&proxyaddr), sizeof(proxyaddr)) < 0)
	{
		ividns_log_notice(" recv sock bind err");
		exit(1);
	}

	proxy(recvsd, (struct sockaddr *)(&cliaddr), sizeof(cliaddr), (struct sockaddr *) &dnsaddr, sizeof(dnsaddr), &prefix, prefixlen);
	
}


void ividns_printf(UINT32 dbglvl, char *fmt, ...)
{
	char buf[2048] = {0};
	char cmd[2048] = {0};

    if ((dbglvl <= l_dbglvl) || ((1 == use_syslog) && (dbglvl <=  l_sysloglvl)))
    {
    	va_list valist;
    	va_start(valist, fmt);
    	vsprintf(buf, fmt, valist);
    	va_end(valist);
	}

	if (dbglvl <= l_dbglvl)
	{
    	sprintf(cmd, "echo \"[%5d] %s\" > /dev/console \r\n", getpid(), buf);
    	system(cmd);
    }

	if ((1 == use_syslog) && (dbglvl <=  l_sysloglvl))
	{
		openlog("dnsproxy", LOG_NDELAY, LOG_USER);
		syslog(dbglvl, "[%5d] %s",  getpid(), buf);
        closelog();
	}
	return ;
}


