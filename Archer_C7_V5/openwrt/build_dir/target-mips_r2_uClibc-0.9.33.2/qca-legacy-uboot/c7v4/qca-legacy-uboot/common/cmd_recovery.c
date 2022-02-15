#include <common.h>
#include <command.h>

#include "nm_lib.h"
#include "nm_fwup.h"

int do_fwrecovery( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    int ret = 0;
    int bufLen  = 0;
    unsigned char *addr = NULL;

	if (argc < 2) {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return -1;
	}

    addr   = simple_strtoul(argv[1], NULL, 0);
    bufLen = simple_strtoul(argv[2], NULL, 0);

    if (!addr || !bufLen)
    {
		printf ("Usage:\n%s\n", cmdtp->usage);
		return -2;
    }

	ret = nm_tpFirmwareRecovery(addr, bufLen);
	if (ret != 0)
	{
		printf("recovery failed.\n");
		return -1;
	}

    printf("All Done!\n");
    return 0;
}

/**************************************************/
U_BOOT_CMD(
	fwrecov,     3,     1,      do_fwrecovery,
	"fwrecov - TP-Link Firmware Recovery Tools\n",
	"address filelen\n"
);

