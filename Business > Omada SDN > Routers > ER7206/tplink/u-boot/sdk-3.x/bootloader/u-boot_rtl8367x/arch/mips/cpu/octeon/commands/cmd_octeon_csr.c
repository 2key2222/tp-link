/*
 * (C) Copyright 2000
 * Subodh Nijsure, SkyStream Networks, snijsure@skystream.com
 *
 * (C) Copyright 2011
 * Cavium Inc., Inc. <support@cavium.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/**
 * @file
 * 
 * Command to display CSR of the local Octeon
 * 
 * $Id: cmd_octeon_csr.c 96612 2014-04-16 01:14:29Z terenditsov $
 * 
 * 
 */
#include <config.h>
#include <common.h>
#include <command.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-csr-db.h>
#include <asm/arch/cvmx-srio.h>

#define CVMX_SRIO_CONFIG_TIMEOUT	1000

#define is_digit(c) ((c) >= '0' && (c) <= '9')

int do_octcsr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int index;
	const char *csr_name;
	uint32_t model;
	
	if (argc < 2)
		return cmd_usage(cmdtp);

	
	model = cvmx_get_proc_id();
	index = 1;
	while (index < argc) {
		csr_name = argv[index];
		const CVMX_CSR_DB_ADDRESS_TYPE *csr;
		
		/* Find the CSR address from the name.  If this fails it will
		 * return 0.
		 */
		csr = cvmx_csr_db_get(model, csr_name);
		
		if (!csr) {
			printf("CSR not found in list.  "
			       "Looking for prefix \"%s\"\n",
			       csr_name);
			cvmx_csr_db_print_decode_by_prefix(model, csr_name, 0);
			index++;
			continue;
		}

		/* See if it's a read or write */
		if ((index + 1 < argc) && is_digit(argv[index + 1][0])) {
			/* Write */
			uint64_t value = simple_strtoull(argv[index + 1], NULL, 0);
			if ((csr->type == CVMX_CSR_DB_TYPE_PCICONFIGEP)
			    || (csr->type == CVMX_CSR_DB_TYPE_PCICONFIGRC)) {
				/* Names are of the format 
				 * "PCIE??#_CFG???". The # is the pcie
				 * port number
				 */
				int pcie_port = (csr->name[6] - '0');
				if (octeon_has_feature(OCTEON_FEATURE_NPEI)) {
					cvmx_pescx_cfg_wr_t pescx_cfg_wr;
					pescx_cfg_wr.u64 = 0;
					pescx_cfg_wr.s.addr = csr->address;
					pescx_cfg_wr.s.data = value;
					cvmx_write_csr(CVMX_PESCX_CFG_WR(pcie_port),
						       pescx_cfg_wr.u64);
				} else {
					cvmx_pemx_cfg_wr_t pemx_cfg_wr;
					pemx_cfg_wr.u64 = 0;
					pemx_cfg_wr.s.addr = csr->address;
					pemx_cfg_wr.s.data = value;
					cvmx_write_csr(CVMX_PEMX_CFG_WR(pcie_port),
						       pemx_cfg_wr.u64);
				}
			} else if (csr->type == CVMX_CSR_DB_TYPE_SRIOMAINT &&
				   octeon_has_feature(OCTEON_FEATURE_SRIO)) {
				/* Names are of the format "SRIOMAINT#_*".
				 * The # is the srio port number
				 */
				int srio_port = (csr->name[9] - '0');
				if (cvmx_srio_config_write32(srio_port, 0, -1,
							     0, 0, csr->address,
							     value))
					puts("SRIO access failed\n");
				else if (csr->widthbits == 32) {
					cvmx_write64_uint32(csr->address, value);
					if (((csr->address >> 40) & 0x7ffff) == 0x118)
						/* Perform immediate read to 
						 * force write to complete.
						 */
						cvmx_read64_uint64(CVMX_MIO_BOOT_BIST_STAT);
				} else
					cvmx_write_csr(csr->address, value);
				index += 2;
			}
		} else { /* Else read operation */
			uint64_t value;
			if ((csr->type == CVMX_CSR_DB_TYPE_PCICONFIGEP) || 
			    (csr->type == CVMX_CSR_DB_TYPE_PCICONFIGRC)) {
				/* Names are of the format "PCIE??#_CFG???".
				 * The # is the pcie port number
				 */
				int pcie_port = (csr->name[6] - '0');
				if (octeon_has_feature(OCTEON_FEATURE_NPEI)) {
					cvmx_pescx_cfg_rd_t pescx_cfg_rd;
					pescx_cfg_rd.u64 = 0;
					pescx_cfg_rd.s.addr = csr->address;
					cvmx_write_csr(CVMX_PESCX_CFG_RD(pcie_port),
						       pescx_cfg_rd.u64);
					pescx_cfg_rd.u64 = cvmx_read_csr(CVMX_PESCX_CFG_RD(pcie_port));
					value = 0xffffffffull & pescx_cfg_rd.s.data;
				} else {
					cvmx_pemx_cfg_rd_t pemx_cfg_rd;
					pemx_cfg_rd.u64 = 0;
					pemx_cfg_rd.s.addr = csr->address;
					cvmx_write_csr(CVMX_PEMX_CFG_RD(pcie_port),
						       pemx_cfg_rd.u64);
					pemx_cfg_rd.u64 = cvmx_read_csr(CVMX_PEMX_CFG_RD(pcie_port));
					value = 0xffffffffull & pemx_cfg_rd.s.data;
				}
			} else if (csr->type == CVMX_CSR_DB_TYPE_SRIOMAINT &&
				   octeon_has_feature(OCTEON_FEATURE_SRIO)) {
				/* Names are of the format "SRIOMAINT#_*".
				 * The # is the srio port number
				 */
				int srio_port = (csr->name[9] - '0');
				uint32_t result;
				if (cvmx_srio_config_read32(srio_port, 0, -1, 0,
							    0, csr->address,
							    &result)) {
					puts("SRIO access failed\n");
					result = 0;
				}
				value = result;
			} else if (csr->widthbits == 32)
				value = cvmx_read64_uint32(csr->address);
			else
				value = cvmx_read_csr(csr->address);
			cvmx_csr_db_decode_by_name(model, csr->name, value);
			index++;
		}
	}
	return 0;
}

U_BOOT_CMD(
	octcsr,	2,	1,	do_octcsr,
	"Read or write a CSR by name.",
	"    CSR    Name of CSR to read or write.  Case is ignored.\n"
	"    value  If present, write this value to the CSR, otherwise do a read.\n"
	"           The value can be in decimal or hex (0x...).\n"
	"\n"
	"    If CSR is a partial name, the list of CSRs starting with it are displayed.\n"
);
