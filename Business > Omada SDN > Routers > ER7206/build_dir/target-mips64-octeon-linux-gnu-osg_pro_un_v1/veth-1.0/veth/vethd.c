/***************************************************************************
                      vethd.c  -  Virtual Ethernet Daemon
                             -------------------
    begin                : dom oct 19 13:19:41 VET 2003
    copyright            : (C) 2003 by Nestor Peña
    email                : nestor@linux.org.ve
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <fcntl.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_tun.h>
#include <net/ethernet.h>

#define max(a,b) ((a)>(b) ? (a):(b))

#define VERSION "1.0"

#define TUN_DEVICE "/dev/net/tun"
#define TUN_DEVICE2 "/dev/tun"

#define VETH0_DEVICE "veth0"
#define ETH_DEVICE "eth0"

#define MAC_ALL_ZEROS "\0\0\0\0\0\0"
#define MAC_ALL_FFS "\xFF\xFF\xFF\xFF\xFF\xFF"

#define MAX_ETH_STR 30
#define MAX_MAC_STR 18

#define ERR_OPEN_TAP -1
#define ERR_IOCTL -2
#define ERR_BIND -3

typedef int eth_handler;
typedef unsigned char hw_addr[6];

void set_locale(void)
{
	setlocale(LC_ALL, (const char *)getenv("LC_ALL"));
}

void show_copyright()
{
	fprintf(stderr,
		"VETH " VERSION " - Virtual Ethernet Driver\n"
		"(C) MMIII by Nestor Peña <nestor@linux.org.ve>\n"
		"This software is GPL - See LICENSE for details\n\n"
		);
}


void hwstring2mac(const char *hwstr, hw_addr *mac)
{
	char *aux, *aux2;
	char *hwstr_copy;
	unsigned int auxx, i;

	hwstr_copy = (char *)malloc(strlen(hwstr));
	memcpy(hwstr_copy, hwstr, strlen(hwstr));
	aux = (char *)hwstr_copy;
	for(i = 0; i < 6; i++)
	{
		aux2 = aux;
		while(
		      (*aux2 >= '0' && *aux2 <= '9') ||
		      (*aux2 >= 'a' && *aux2 <= 'f') ||
		      (*aux2 >= 'A' && *aux2 <= 'F'))
			aux2++;
		*aux2 = '\0';
		sscanf(aux, "%x", &auxx);
		(*mac)[i] = (unsigned char)auxx;
		aux = aux2 + 1;
	}
}

void shutdown_vethd(void)
{
	fprintf(stderr, "\nvethd - Shutdown signal received...\n");
	_exit(0);
}

void shutdown_segv_vethd(void)
{
	fprintf(stderr, "\nvethd - :-O Killed by a SEGV signal...\nThis shouldn't be happened :'(\n");
	_exit(10);
}

eth_handler open_tap_device(const char *veth_device, const char *hwaddr_string)
{
	struct ifreq ifr;
	eth_handler fd, vfd;
	hw_addr hwaddr;

	if((fd = open(TUN_DEVICE, O_RDWR)) < 0)
	{
		perror(TUN_DEVICE);
		fprintf(stderr, "Trying old-style tun driver (%s)...\n", TUN_DEVICE2);
		if((fd = open(TUN_DEVICE2, O_RDWR)) < 0)
		{
			perror(TUN_DEVICE2);
			fprintf(stderr,
				"Neither the %s device nor the %s device exists\n\n"
				"This can be caused by this:\n\n"
				"- Do yo have the devices created in /dev?  If not, then create it:\n\n"
				"  # mknod /dev/tun c 10 200\n\n"
				"- Do you have the tun module loaded?  If not, write\n"
				"  # modprobe tun\n\n"
				"  and try again.\n\n",
				TUN_DEVICE,
				TUN_DEVICE2);
			return ERR_OPEN_TAP;
		}
	}

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
	strncpy(ifr.ifr_name, veth_device, sizeof(ifr.ifr_name));
	if(ioctl(fd, TUNSETIFF, &ifr) < 0)
	{
		perror("When ioctl'ing TUNSETIFF to veth");
		return ERR_IOCTL;
	}


	vfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	strncpy(ifr.ifr_name, veth_device, sizeof(ifr.ifr_name));
 	if(ioctl(vfd, SIOCGIFHWADDR, &ifr) < 0)
 	{
 		perror("Error while getting veth hw address");
 		return ERR_IOCTL;
 	}

	if(strlen(hwaddr_string) > 0)
	{
		hwstring2mac(hwaddr_string, &hwaddr);
		if(!strncmp(hwaddr_string, MAC_ALL_ZEROS, 6) ||
		   !strncmp(hwaddr_string, MAC_ALL_FFS, 6))
		{
			fprintf(stderr, "Error: mac address value is incorrect\n");
			return ERR_OPEN_TAP;
		}
		memcpy(ifr.ifr_hwaddr.sa_data, hwaddr, 6);
		strncpy(ifr.ifr_name, veth_device, sizeof(ifr.ifr_name));

		if(ioctl(vfd, SIOCSIFHWADDR, &ifr) < 0)
		{
			perror("Error while ioctl'ing hardware address to veth");
			return ERR_IOCTL;
		}
	}
	return fd;
}

eth_handler open_eth_device(const char *device)
{
	struct ifreq ifr;
	eth_handler sock_fd;
	int if_index;
	struct sockaddr_ll sll;

	sock_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	strncpy(ifr.ifr_name, device, sizeof(ifr.ifr_name));
	if(ioctl(sock_fd, SIOCGIFINDEX, &ifr) < 0)
	{
		perror("Error while ioctl'ing SIOCGIFINDEX in network device");
		return ERR_IOCTL;
	}
	if_index = ifr.ifr_ifindex;

	if(ioctl(sock_fd, SIOCGIFFLAGS, &ifr) < 0)
	{
		perror("Error while ioctl'ing SIOCGIFFLAGS in network device");
		return ERR_IOCTL;
	}
	ifr.ifr_flags |= IFF_PROMISC;

	if(ioctl(sock_fd, SIOCSIFFLAGS, &ifr) < 0)
	{
		perror("Error while ioctl'ing SIOCSIFFLAGS on network device");
		return ERR_IOCTL;
	}
	

	memset(&sll, 0, sizeof(sll));
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = if_index;
	sll.sll_protocol = htons(ETH_P_ALL);
	if(bind(sock_fd, (struct sockaddr *)&sll, sizeof(sll)) < 0)
	{
		perror("Error while bind'ing eth0");
		return ERR_BIND;
	}
	return sock_fd;
}

int main(int argc, char **argv)
{
	char buffer[1600],
		veth_device[MAX_ETH_STR + 1] = VETH0_DEVICE,
		eth_device[MAX_ETH_STR + 1] = ETH_DEVICE,
		mac_addr_str[MAX_MAC_STR + 1] = "";

	int vfd, nfd, leidos, opc, foreground = 0;
	fd_set fds;
	struct ether_header const* const ether_hdr = (struct ether_header const *)buffer;

	set_locale();
	show_copyright();

	signal(SIGINT, (void (*)(int))shutdown_vethd);
	signal(SIGQUIT, (void (*)(int))shutdown_vethd);
	signal(SIGTERM, (void (*)(int))shutdown_vethd);
	signal(SIGSEGV, (void (*)(int))shutdown_segv_vethd);

	if(geteuid() != 0)
	{
		fprintf(stderr, 
			"Not running as root\n"
			"root privileges are needed to open TUN and eth interfaces.\n"
			"Aborting...\n");
		return 5;
	}

	while((opc = getopt(argc, argv, "v:e:m:f")) != -1)
	{
		switch(opc)
		{
		case 'v':
			if(*optarg == '-')
			{
				fprintf(stderr, "%s: Invalid veth name\n", optarg);
				return 9;
			}
			else
				strncpy(veth_device, optarg, MAX_ETH_STR + 1);
			break;

		case 'e':
			if(*optarg == '-')
			{
				fprintf(stderr, "%s: Invalid eth name\n", optarg);
				return 9;
			}
			else
				strncpy(eth_device, optarg, MAX_ETH_STR + 1);
			break;

		case 'm':
			if(*optarg == '-')
			{
				fprintf(stderr, "%s: Invalid MAC address\n", optarg);
				return 9;
			}
			else
			strncpy(mac_addr_str, optarg, MAX_MAC_STR + 1);
			break;

		case 'f':
			foreground = 1;
			break;
			       
		default:
			fprintf(stderr,
				"Usage: vethd [-v veth-device] [-e eth-device] [-m mac-address]\n\n"
				"veth-device\tName you want in the VIRTUAL device, for example: veth0\n"
				"eth-device\tName of the REAL device, for example: eth0, eth1\n"
				"mac-address\tMAC address desired, like this: 00:11:22:33:44:55\n\n"
				"If some or all of them are not defined, these are the defaults:\n\n"
				"veth-device\tveth0\n"
				"eth-device\teth0\n"
				"mac-address\tGenerated automagically (and dynamic) by kernel\n");
			return 10;
		}
	}

	if((vfd = open_tap_device(veth_device, mac_addr_str)) < 0)
	{
		fprintf(stderr, "Error opening TAP device\n");
		return 1;
	}

	if((nfd = open_eth_device(eth_device)) < 0)
	{
		fprintf(stderr, "Error opening ETH device\n");
		return -1;
	}

	fprintf(stderr, "Attached %s into %s\n", veth_device, eth_device);

	if(foreground)
		printf("Running in foreground...\n");
	else
	{
			switch(fork())
			{
			case 0:
				break;
				
			case -1:
				fprintf(stderr, "Unable to fork() itself.\n"
					"Falling back into foreground mode...\n");
				break;

			default:
				return 0;
			}
	}


	FD_ZERO(&fds);
	FD_SET(nfd, &fds);
	FD_SET(vfd, &fds);

	while(1)
	{
		if(select(max(vfd, nfd) + 1, &fds, NULL, NULL, NULL) < 0)
		{
			perror("Error in select()");
			return 4;
		}
		if(FD_ISSET(vfd, &fds))
		{
			leidos = read(vfd, buffer, sizeof(buffer));
			if(leidos == -1)
			{
				perror("Error reading from TAP");
				return 2;
			}
			write(nfd, buffer, leidos);
		}
		if(FD_ISSET(nfd, &fds))
		{
			leidos = read(nfd, buffer, sizeof(buffer));
			if(leidos == -1)
			{
				perror("Error reading from ethernet interface");
				return 2;
			}
			/* drop multicast and ppp session */
			if (!(ether_hdr->ether_dhost[0] == 0x01)
			   && (ether_hdr->ether_type != htons(ETH_P_PPP_SES))) {
				write(vfd, buffer, leidos);
			}
		}
		FD_ZERO(&fds);
		FD_SET(nfd, &fds);
		FD_SET(vfd, &fds);
	}

	return 0;
}
