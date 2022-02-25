#include <common.h>

static int l_FWRecoveryFlag = 0;

int isFWRecoveryStarted(void)
{
    return l_FWRecoveryFlag;
}

void perform_tpFwRecovery(void)
{
    int  ret = 0;
    char *s;
    char cmdBuff[128] = {0};
    int  file_size = 0;
	const char *ep1 = getenv("autostart");

    fwrecovery_gpio_init();
    fwrecovery_led_off();

    ret = fwrecovery_rst_btn_pressed();
    if (ret)
	{
#ifdef CFG_ATHRS27_PHY
		enable_phy_ports_all();
#endif
		fwrecovery_led_on();
		l_FWRecoveryFlag = 1;		 

		/* wait for ethernet config done. by HouXB, 28Apr11 */
		udelay(2000*1000);

		memset(cmdBuff, 0, 128);
		sprintf(cmdBuff, "setenv serverip %s;setenv ipaddr %s", 
			FIRMWARE_RECOVERY_SERVER_IP, FIRMWARE_RECOVERY_IP_ADDR);
		printf("run command %s\n", cmdBuff);
		run_command(cmdBuff, 0);

		setenv("autostart","no"); //just don't auto start the download file
		memset(cmdBuff, 0, 128);
		sprintf(cmdBuff, "tftp 0x%x %s", CONFIG_FW_RECOVERY_ADDR, FIRMWARE_RECOVERY_NAME);		
		printf("run command %s\n", cmdBuff);
		ret = run_command(cmdBuff, 0);

		if (ep1)
		{
			setenv("autostart",ep1);
		}
		else
		{
			setenv("autostart","");
		}

		//check tftp command result
		if(ret < 0)
		{
			printf("tftpboot firmware failed, now start normally.\n");
			goto normal_start;
		}
	
		s = getenv("filesize");
		if (s)
		{
			file_size = simple_strtoul(s, NULL, 16);
		}
		else
		{
			printf("Firmware file size not find, now start normally.\n");
			goto normal_start;			
		}

		printf("Firmware downloaded... filesize = 0x%x fileaddr = 0x%08x.\n", 
				file_size, CONFIG_FW_RECOVERY_ADDR);

        memset(cmdBuff, 0, 128);
        sprintf(cmdBuff, "fwrecov 0x%x 0x%08x", CONFIG_FW_RECOVERY_ADDR, file_size); 
        run_command(cmdBuff, 0);

reset:		
		printf("now restart...\n");
		run_command("reset", 0);
		
normal_start:
		fwrecovery_led_off();
#ifdef CFG_ATHRS27_PHY
		disable_phy_ports_all();
#endif	
	}
}

