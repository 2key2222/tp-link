/*******************************************************************************
Copyright (C) Marvell International Ltd. and its affiliates

This software file (the "File") is owned and distributed by Marvell
International Ltd. and/or its affiliates ("Marvell") under the following
alternative licensing terms.  Once you have made an election to distribute the
File under one of the following license alternatives, please (i) delete this
introductory statement regarding license alternatives, (ii) delete the two
license alternatives that you have not elected to use and (iii) preserve the
Marvell copyright notice above.

********************************************************************************
Marvell Commercial License Option

If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.

********************************************************************************
Marvell GPL License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File in accordance with the terms and conditions of the General
Public License Version 2, June 1991 (the "GPL License"), a copy of which is
available along with the File in the license.txt file or by writing to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 or
on the worldwide web at http://www.gnu.org/licenses/gpl.txt.

THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE IMPLIED
WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY
DISCLAIMED.  The GPL License provides additional details about this warranty
disclaimer.
********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    *   Redistributions of source code must retain the above copyright notice,
	    this list of conditions and the following disclaimer.

    *   Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

    *   Neither the name of Marvell nor the names of its contributors may be
		used to endorse or promote products derived from this software without
		specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/
#include "config_marvell.h"  	/* Required to identify SOC and Board */
#include "mv_os.h"
#include "mvUart.h"
#include "mvBinHdrComponents.h"
#include "printf.h"

#ifdef MV_DEBUG_MODE
#include "debug.h"
#endif

MV_BINARY_HEADER_COMPONENTS componentTable[]={ BIN_HEADER_COMPONENT_TABLE};

#ifdef MV_DEBUG_MODE
static void print_menu() {
	mvPrintf("\nPlease choose one of the following commands:\n");
	mvPrintf("\t1.SERDES initialization\n");
	mvPrintf("\t2.DRAM initialization\n");
	mvPrintf("\t3.Suspend wake up\n");
	mvPrintf("\t4.Prompt mode\n");
	mvPrintf("\t\tSelected command number:");
}
#endif

int mvBinHdrDispatcher(void)
{
	MV_BINARY_HEADER_COMPONENTS *pComponent= componentTable;
	MV_STATUS rc;
#ifdef MV_DEBUG_MODE
	int i;
	char c;
#endif

#ifndef MV_DEBUG_MODE
    while (pComponent->ComponentFunc){
		rc = pComponent->ComponentFunc();
		if (rc != MV_OK)
		{
			mvUartInit();
			DEBUG_INIT_S("\n\n **********          ");
			DEBUG_INIT_S(pComponent->ComponentName);
			DEBUG_INIT_S(" failed!   ********\n");
			while(1);
		}
		pComponent++;
	}
#else
	/* Run GeneralInit component
	 * needed for genereal MPP's (i.e UART, I2C, etc.) */
	if (pComponent->ComponentFunc)
		pComponent->ComponentFunc();
	/* send ACKs to the sender to finish sx-at91 protocol running
	 * and start using UART for prints
	 * 3 ACKS are required to finish transaction */
	for (i = 0; i < 3; ++i)
		mvUartPutc(MV_UART_XMODEM_ACK_CHAR);
	/* get the last char sent by the protocol (EOT) */
	mvUartGetc();

	while (1) {
		print_menu();
		c = mvUartGetc();

		if (c >= '1' && c <= '3') {
			pComponent = componentTable + (c - '0');
			if (pComponent->ComponentFunc) {
				rc = pComponent->ComponentFunc();
				if (rc != MV_OK)
					mvPrintf("\n\n ********** %s failed! **********", pComponent->ComponentName);
			}
		} else if (c == '4') {
			rc = mvBinHeaderDebugPrompt();
			if (rc != MV_OK)
				mvPrintf("\n\n ********** Binary Header Debug Prompt failed! **********");
		} else
			mvPrintf("\n\nInvalid command number\n");
	}
#endif
	return 0;
}
