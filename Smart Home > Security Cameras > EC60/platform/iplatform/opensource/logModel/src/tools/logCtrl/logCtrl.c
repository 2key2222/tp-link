/*****************************************************************************
* Copyright@ 2004-2015 TP-LINK TECHNOLOGIES CO., LTD.
* File Name: logCtrl.c
* Author:    dongzhenhua 
* Version:   1.0
* Description:
*     
* information.
*  		the tools to change level and module  in log daemon , dynamic
*            It is also the demo for web control.
* History:  
*     2015-09-17: dongzhenhua     File created.   
*****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <syslog.h>

#include "logApi.h"

extern int swLogInit(void);


int usage()
{
	fprintf(stderr, "usage: logCtrl [-lmn] [-l levelName] [-m moduleName] [-n networkEnable] \n" );
	exit(1);
}

int main(int argc, char** argv)
{
	int c;

	while((c = getopt(argc, argv, "?e:l:m:n:")) != -1){
		switch(c){
			case '?':
				printf("-? option explain:\n\n");
				printf("-l    ===>./logCtrl -l [0~7]                #to set level , such as: ./logCtrl -l 5 \n\n");
				printf("0: EMERG    ");
				printf("1: ALERT    ");
				printf("2: CRIT    ");
				printf("3: ERR    ");
				printf("4: WARNING    ");
				printf("5: NOTICE    ");
				printf("6: INFO    ");
				printf("7: DEBUG\n");
				printf("=================================================="
					  "==========================================================\n\n");
				
				printf("-m    ===>./logCtrl -m '0|1|2|3....|63'     #to set module mask  , such as: ./logCtrl -m '5|8' \n\n");
				printf(" 0:%-20s", "audioDetection");
				printf(" 1:%-20s", "autoUpgrade");
				printf(" 2:%-20s", "Bonjour");
				printf(" 3:%-20s", "Button");
				printf(" 4:%-20s\n", "Cloud");
				printf(" 5:%-20s", "DateTime");
				printf(" 6:%-20s", "DayNight");
				printf(" 7:%-20s", "DevFind");
				printf(" 8:%-20s", "Device");
				printf(" 9:%-20s\n", "IpcSwitch");

				printf("10:%-20s", "librpm");
				printf("11:%-20s", "Location");
				printf("12:%-20s", "MDNew");
				printf("13:%-20s", "MsgPush");
				printf("14:%-20s\n", "NetConfig");
				printf("15:%-20s", "NetSwitch");
				printf("16:%-20s", "Oem");
				printf("17:%-20s", "Onvif");
				printf("18:%-20s", "rpc_mod");
				printf("19:%-20s\n",  "rpms");

				printf("20:%-20s", "SD");
				printf("21:%-20s", "Session");
				printf("22:%-20s", "System");
				printf("23:%-20s", "tddp");
				printf("24:%-20s\n", "UPnP");
				printf("25:%-20s", "UserManage");
				printf("26:%-20s", "VideoControl");
				printf("27:%-20s", "Wireless");
				printf("28:%-20s", "WorkMode");
				printf("29:%-20s\n", "ADNew");

				printf("30:%-20s", "autoupgradenotice");
				printf("31:%-20s", "cloud");
				printf("32:%-20s", "ddns");
				printf("33:%-20s", "filecut");
				printf("34:%-20s\n", "ftpAlarmNew");
				printf("35:%-20s", "libcloud");
				printf("36:%-20s", "SDRecord");
				printf("37:%-20s", "speaker");
				printf("38:%-20s", "streamd");
				printf("39:%-20s\n",  "smtpAlarmNew");

				printf("40:%-20s\n", "vod");
				printf("41:%-20s\n", "server");
				printf("65:%-20s\n", "ALL MODULE CLOSE");
				printf("66:%-20s\n", "ALL MODULE OPEN");
				printf("=================================================="
					  "==========================================================\n\n");
				printf("-n    ===>./logCtrl -n [0~1]                #to set network\n\n");
				printf("0:  disable log info send to remote maching from network\n");
				printf("1:  enable log info send to remote maching from networ\n");
				printf("=================================================="
					  "==========================================================\n\n");
				printf("-e    ===>./logCtrl -e [0~1]                #to set printf log enable,it will auto open the network ,and also disable to wirte to file\n\n");
				printf("0:  in DBG(), disable to syslog()\n");
				printf("1:  in DBG(), enable  to syslog()\n");
				printf("=================================================="
					  "==========================================================\n\n");
				return 0;
				break;

			case 'e':
				swLogInit();
				
				printf("e:%s\n", optarg);
				int logEnable = atoi(optarg);
				printf("logEnable:%d\n", logEnable);
				swLogSetEnableFlag(logEnable);

				break;

			case 'l':
				swLogInit();
				
				printf("l:%s\n", optarg);
				int logLevel = atoi(optarg);
				printf("logLevel:%d\n", logLevel);
				swLogSetLevel(1 << logLevel);
				break;

			case 'm':
				swLogInit();
				
				printf("m:%s\n", optarg);
				uint64_t moduleMaskValue = 0;
				char *pStr = optarg;
				char  value[32] = {0};

				while(sscanf(pStr, "%[^|]", value) > 0){
					printf("pStr:%s, strlen(value):%d, value:%d\n", pStr, strlen(value), atoi(value));
					if(65 == atoi(value)){
						printf("all module close log\n");
						swLogSetModule(0);
						swLogUnInit();
						return 0;
					}
					else if(66 == atoi(value)){
						printf("all module open log\n");
						swLogSetModule(0xffffffffffffffffLL);
						swLogUnInit();
						return 0;
					}
					moduleMaskValue |= 1LL << atoi(value);
					pStr += strlen(value);
					if(*pStr == '|')pStr++;
					printf("0x%08llx\n", moduleMaskValue);
					memset(value, 0, sizeof(value));
				}
				
				swLogSetModule(moduleMaskValue);
				break;

			case 'n':
				swLogInit();
				int flag = atoi(optarg);
				printf("flag:%d\n", flag);
				switch(flag){
					case 0:
						swLogCloseNetWork();
						break;

					case 1:
						swLogOpenNetWork();
						break;

					default:
						printf("not know value:%d\n", flag);
						break;
				}
				
				break;

			default:
				usage();
		}
	}
	//sleep(1);

	swLogUnInit();
	return 0;
}
