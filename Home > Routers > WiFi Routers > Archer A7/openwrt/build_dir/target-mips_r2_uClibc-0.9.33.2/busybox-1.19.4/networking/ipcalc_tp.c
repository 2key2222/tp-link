#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//usage:#define ipcalc_tp_trivial_usage
//usage:       "ADDRESS NETMASK START_IP COUNT"
//usage:#define ipcalc_tp_full_usage "\n\n"
//usage:       "TP-LINK uses to Calculate IP network settings from a IP address for DHCP Server\n"
//
char usage[] = "ipcalc:\n"
		"ipcalc ip mask start count";

int ipcalc_tp_main(int argc, char **argv)
{
	struct in_addr ip;
	struct in_addr mask;
	struct in_addr broadcast;
	struct in_addr network;
	struct in_addr start;
	struct in_addr end;
	int ip_start;
	int prefix = 0;
	int count = 0;
	int i = 0;

	if (argc != 5) {
		printf("input paramters error\n\n%s\n", usage);
		goto error;
	}
	ip.s_addr = ntohl(inet_addr(argv[1]));
	mask.s_addr = ntohl(inet_addr(argv[2]));
	ip_start = atoi(argv[3]);
	count = atoi(argv[4]);

	if (ip.s_addr == -1 || mask.s_addr == -1 || start.s_addr == -1) {
		printf("input paramters error\n\n%s\n", usage);
		goto error;
	}

	broadcast.s_addr = ip.s_addr | (~mask.s_addr);
	network.s_addr = ip.s_addr & mask.s_addr;
	for (i = 31; i >= 0 ; i--) {
		if (mask.s_addr & (1 << i))
			prefix ++;
		else
			break;
	}

	start.s_addr = network.s_addr + (ip_start & 0xff);
	if ((start.s_addr & 0xff) + count > 254)
			end.s_addr = (start.s_addr & 0xffffff00) | 0xfe;
		else
			end.s_addr = start.s_addr + count;

	ip.s_addr = htonl(ip.s_addr);
	mask.s_addr = htonl(mask.s_addr);
	broadcast.s_addr = htonl(broadcast.s_addr);
	network.s_addr = htonl(network.s_addr);
	start.s_addr = htonl(start.s_addr);
	end.s_addr = htonl(end.s_addr);

	//printf("ip %8x mask %8x broadcast %8x network %8x prefix %d start %8x end %8x\n", 
	//ip.s_addr, mask.s_addr, broadcast.s_addr, network.s_addr, prefix, start.s_addr, end.s_addr);
	printf("IP=%s\n", inet_ntoa(ip));
	printf("NETMASK=%s\n", inet_ntoa(mask));
	printf("BROADCAST=%s\n", inet_ntoa(broadcast));
	printf("NETWORK=%s\n", inet_ntoa(network));
	printf("PREFIX=%d\n", prefix);
	printf("START=%s\n", inet_ntoa(start));
	printf("END=%s\n", inet_ntoa(end));

	return 0;
error:
	return -1;
}
