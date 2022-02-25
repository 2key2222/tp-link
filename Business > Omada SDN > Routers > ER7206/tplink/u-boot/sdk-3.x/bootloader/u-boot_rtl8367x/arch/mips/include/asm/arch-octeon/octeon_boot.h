/*
 * (C) Copyright 2004-2013
 * Cavium Inc.
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
 * @file octeon_boot.h
 *
 * $Id: octeon_boot.h 89778 2013-10-22 03:10:03Z awilliams $
 *
 */

#ifndef __OCTEON_BOOT_H__
#define __OCTEON_BOOT_H__

#include <asm/arch/octeon_mem_map.h>
#include <asm/arch/octeon-boot-info.h>
#include <asm/arch/cvmx-coremask.h>
#include <asm/arch/cvmx-asm.h>

/**
 * NOTE: This file duplicates the defines and data structures in the toolchain
 * octeon-app-init.h file.  Be sure to keep them in sync.
 */

/* Defines for GPIO switch usage */
/* Switch 0 is failsafe/normal bootloader */
#define OCTEON_GPIO_SHOW_FREQ       (0x1 << 1)	/* switch 1 set shows freq
						 * display
						 */

#define OCTEON_BOOT_DESC_IMAGE_LINUX	(1 << 0)
#define OCTEON_BOOT_DESC_LITTLE_ENDIAN	(1 << 1)

/* Define to allow conditional compilation in CVMX depending on
   version of the stand-alone Octeon support in newlib.  */
/* Version 2: added OCTEON_BL_FLAG_CONSOLE_PCI */
/* Version 3: added OCTEON_BL_FLAG_BREAK */
/* Version 4: added __octeon_uart_unlock */
#ifndef OCTEON_APP_INIT_H_VERSION
# define OCTEON_APP_INIT_H_VERSION		4
#endif

/* Macro indicates that bootmem related structures are now in
   cvmx-bootmem.h.  */
#ifndef OCTEON_APP_INIT_BOOTMEM_STRUCTS_MOVED
# define OCTEON_APP_INIT_BOOTMEM_STRUCTS_MOVED
#endif

/**
 * NOTE: This must duplicate octeon_boot_descriptor_t in the toolchain
 * octeon-app-init.h file.
 */
enum {
	/* If set, core should do app-wide init, only one core per app will have
	 * this flag set.
	 */
	BOOT_FLAG_INIT_CORE     = 1,
	OCTEON_BL_FLAG_DEBUG    = 1 << 1,
	OCTEON_BL_FLAG_NO_MAGIC = 1 << 2,
	OCTEON_BL_FLAG_CONSOLE_UART1 = 1 << 3,  /* If set, use uart1 for console */
	OCTEON_BL_FLAG_CONSOLE_PCI = 1 << 4,  /* If set, use PCI console */
	OCTEON_BL_FLAG_BREAK    = 1 << 5, /* Call exit on break on serial port */
	/* Be sure to update OCTEON_APP_INIT_H_VERSION when new fields are added
	 * and to conditionalize the new flag's usage based on the version.
	 */
} octeon_boot_descriptor_flag;

/**
 * NOTE: This must duplicate octeon_boot_descriptor_t in the toolchain
 * octeon-app-init.h file.
 */
#ifndef OCTEON_CURRENT_DESC_VERSION
# define OCTEON_CURRENT_DESC_VERSION	7
#endif
/**
 * NOTE: This must duplicate octeon_boot_descriptor_t in the toolchain
 * octeon-app-init.h file.
 */
/* Version 7 changes: Change names of deprecated fields */
#ifndef OCTEON_ARGV_MAX_ARGS
# define OCTEON_ARGV_MAX_ARGS		(64)
#endif

/**
 * NOTE: This must duplicate octeon_boot_descriptor_t in the toolchain
 * octeon-app-init.h file.
 */
#ifndef OCTEON_SERIAL_LEN
# define OCTEON_SERIAL_LEN		20
#endif

/**
 * Bootloader structure used to pass info to Octeon executive startup code.
 * NOTE: all fields are deprecated except for:
 *  * desc_version
 *  * desc_size,
 *  * heap_base
 *  * heap_end
 *  * eclock_hz
 *  * flags
 *  * argc
 *  * argv
 *  * cvmx_desc_vaddr
 *  * debugger_flags_base_addr
 *
 *  All other fields have been moved to the cvmx_descriptor, and the new
 *  fields should be added there. They are left as placeholders in this
 *  structure for binary compatibility.
 *
 * NOTE: This structure must match what is in the toolchain octeon-app-init.h
 * file.
 */
struct octeon_boot_descriptor {
	/* Start of block referenced by assembly code - do not change! */
	uint32_t desc_version;
	uint32_t desc_size;
	uint64_t stack_top;
	uint64_t heap_base;
	uint64_t heap_end;
	uint64_t deprecated17;
	uint64_t deprecated16;
	/* End of block referenced by assembly code - do not change! */
	uint32_t deprecated18;
	uint32_t deprecated15;
	uint32_t deprecated14;
	uint32_t argc;  /* argc for main() */
	uint32_t argv[OCTEON_ARGV_MAX_ARGS];  /* argv for main() */
	uint32_t flags;   /* Flags for application */
	uint32_t core_mask;   /* Coremask running this image */
	uint32_t dram_size;  /* DEPRECATED, DRAM size in megabyes. Used up to SDK 1.8.1 */
	uint32_t phy_mem_desc_addr;
	uint32_t debugger_flags_base_addr;  /* used to pass flags from app to debugger. */
	uint32_t eclock_hz;  /* CPU clock speed, in hz. */
	uint32_t deprecated10;
	uint32_t deprecated9;
	uint16_t deprecated8;
	uint8_t  deprecated7;
	uint8_t  deprecated6;
	uint16_t deprecated5;
	uint8_t  deprecated4;
	uint8_t  deprecated3;
	char     deprecated2[OCTEON_SERIAL_LEN];
	uint8_t  deprecated1[6];
	uint8_t  deprecated0;
	uint64_t cvmx_desc_vaddr;  /* Address of cvmx descriptor */
};

/* Debug flags bit definitions.  */
#define DEBUG_FLAG_CORE_DONE    0x1

uint64_t octeon_get_cycles (void);
extern uint32_t cur_exception_base;

#if defined(__U_BOOT__)
extern struct octeon_boot_descriptor boot_desc[CVMX_MIPS_MAX_CORES];
#endif

extern cvmx_coremask_t coremask_to_run;
extern uint64_t boot_cycle_adjustment;
extern uint32_t coremask_from_eeprom;

int octeon_bist(void);
uint32_t get_except_base_reg(void);
uint32_t get_core_num(void);
uint32_t get_except_base_addr(void);
void set_except_base_addr(uint32_t addr);
void copy_default_except_handlers(uint32_t addr);
void cvmx_set_cycle(uint64_t cycle);
cvmx_coremask_t *get_coremask_override(cvmx_coremask_t *pcm);
uint32_t octeon_coremask_num_cores(int num_cores);
uint64_t get_cop0_cvmctl_reg(void);
void set_cop0_cvmctl_reg(uint64_t val);
uint64_t get_cop0_cvmmemctl_reg(void);
void set_cop0_cvmmemctl_reg(uint64_t val);
uint64_t octeon_phy_mem_list_init(uint64_t mem_size, uint32_t low_reserved_bytes);
uint32_t octeon_get_cop0_status(void);
void octeon_display_mem_config(void);
void octeon_led_str_write(const char *str);
int octeon_mcu_read_ddr_clock(void);
int octeon_mcu_read_cpu_ref(void);
int octeon_ebt3000_rev1(void);
void octeon_delay_cycles(uint64_t cycles);
int octeon_boot_bus_init(void);
void octeon_write64_byte(uint64_t csr_addr, uint8_t val);
uint8_t octeon_read64_byte(uint64_t csr_addr);
void clear_tlb(int max_entry);

#define OCTEON_BZERO_PFS_STRIDE (8*128ULL)
#define OCTEON_BZERO_PFS_STRIDE_MASK (OCTEON_BZERO_PFS_STRIDE - 1)
void octeon_bzero64_pfs(uint64_t start_addr, uint64_t count);
int validate_coremask(cvmx_coremask_t *pcm);
void octeon_translate_gd_to_linux_app_global_data(linux_app_global_data_t *lagd);
int octeon_setup_boot_desc_block(cvmx_coremask_t *pcm,
                                 int argc, char * const argv[],
				 uint64_t entry_point, uint32_t stack_size,
				 uint32_t heap_size, uint32_t boot_flags,
				 uint64_t stack_heep_base_addr,
				 uint32_t image_flags, uint32_t config_flags,
				 cvmx_coremask_t *new_pcm, int app_index);
int octeon_setup_boot_vector(uint32_t func_addr, cvmx_coremask_t *pcm);
void start_cores(cvmx_coremask_t *pcm_to_start);
int cvmx_spi4000_initialize(int interface);
int cvmx_spi4000_detect(int interface);
void octeon_flush_l2_cache(void);
cvmx_coremask_t *octeon_get_available_coremask(cvmx_coremask_t *pcm);
uint32_t octeon_get_available_core_count(void);
void octeon_check_mem_load_range(void);
void octeon_setup_cvmx_sysinfo(void);
int octeon_check_mem_errors(void);
int octeon_check_nor_flash_enabled(uint32_t addr);
void octeon_setup_ram_env(void);
int octeon_uart_setup2(int uart_index, int cpu_clock_hertz, int baudrate);
int octeon_uart_setup(int uart_index);
uint64_t uboot_tlb_ptr_to_phys(void *ptr);
char *lowcase(char *str_arg);
void relocate_code_octeon(ulong, gd_t *, uint64_t, int)
    __attribute__((noreturn));

#define OCTEON_BREAK {asm volatile ("break");}
#define OCTEON_SYNC asm volatile ("sync" : : :"memory")
#define OCTEON_SYNCW asm volatile ("syncw" : : :"memory")

#define CAST64(v) ((long long)(long)(v))
#define CASTPTR(type, v) ((type *)(long)(v))

#include "executive-config.h"
#include "cvmx-config.h"
#include "octeon_hal.h"
#include "cvmx-bootmem.h"
#include "cvmx-twsi.h"

#define CVMX_CACHE_LINE_SIZE    (128)	/* In bytes */
#define CVMX_CACHE_LINE_MASK    (CVMX_CACHE_LINE_SIZE - 1) /* In bytes */

/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/

/* Move these out of octeon-app-init with new names, change to orig names once
** removed from octeon-app-init.h
*/
#define NUM_OCTEON_TLB_ENTRIES  256	/* Use maximum number for data
					 * structure
					 */
/** Description of TLB entry, used by bootloader */
typedef struct {
	uint64_t ri:1;
	uint64_t xi:1;
	uint64_t cca:3;
	uint64_t seg_type:3;
} tlb_flags_t;

typedef enum {
	RO_TLB_SEGMENT,
	RW_TLB_SEGMENT,
	SHARED_TLB_SEGMENT,
	STACK_HEAP_TLB_SEGMENT
} TLB_SEG_TYPE;

typedef struct {
	uint64_t phy_page0;
	uint64_t phy_page1;
	uint64_t virt_base;
	uint32_t page_size;
	tlb_flags_t flags;
} octeon_tlb_entry_t_bl;

void print_tlb_array(octeon_tlb_entry_t_bl *tlb_array, int num_entries);
void print_boot_aray(const cvmx_coremask_t *pcm);

#if defined(__U_BOOT__)
uint32_t mem_copy_tlb (octeon_tlb_entry_t_bl * tlb_array, uint64_t dest_virt,
		  uint64_t src_addr, uint32_t len);
#else
uint64_t mem_copy_tlb(octeon_tlb_entry_t_bl * tlb_array, uint64_t dest_virt,
		  uint64_t src_addr, uint32_t len);
#endif
void memset64(uint64_t start_addr, uint8_t value, uint64_t len);
uint64_t memcpy64(uint64_t dest_addr, uint64_t src_addr, uint64_t count);
void octeon_free_tmp_named_blocks(void);
int octeon_bootloader_shutdown(void);
void octeon_restore_std_mips_config(void);

/* These macros simplify the process of creating common IO addresses */
#define OCTEON_IO_SEG 2LL
#define OCTEON_ADD_SEG(segment, add)	((((uint64_t)segment) << 62) | (add))
#define OCTEON_ADD_IO_SEG(add)		OCTEON_ADD_SEG(OCTEON_IO_SEG, (add))

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

/* Bootloader internal structure for per-core boot information
 * This is used in addition the boot_init_vector_t structure to store
 * information that the cores need when starting an application.
 * This structure is only used by the bootloader.
 * The boot_desc_addr is the address of the boot descriptor
 * block that is used by the application startup code.  This descriptor
 * used to contain all the information that was used by the application - now
 * it just used for argc/argv, and heap.  The remaining fields are deprecated
 * and have been moved to the cvmx_descriptor, as they are all simple exec
 * related.
 *
 * The boot_desc_addr and cvmx_desc_addr addresses are physical for linux, and
 * virtual for simple exec applications.
*/
struct boot_info_block {
	octeon_tlb_entry_t_bl *tlb_entries;
	uint64_t entry_point;
	uint64_t boot_desc_addr;	/* address in core's final memory map */
	uint64_t stack_top;
	uint32_t exception_base;
	uint64_t cvmx_desc_addr;	/* address in core's final memory map */
	uint64_t flags;
};
typedef struct boot_info_block boot_info_block_t;

void print_boot_block(boot_info_block_t *i);

#define BOOT_INFO_FLAG_DISABLE_ICACHE_PREFETCH	(1 << 0)
#define BOOT_INFO_FLAG_LITTLE_ENDIAN		(1 << 1)

/* In addition to these two structures, there are also two more:
** 1) the boot_descriptor, which is used by the toolchain's crt0
**    code to setup the stack, head, and command line arguments
**    for the application.
** 2) the cvmx_boot_descriptor, which is used to pass additional
**    information to the simple exec.
*/

/************************************************************************/
#if defined (__U_BOOT__)

#define  OCTEON_SPINLOCK_UNLOCKED_VAL  0
typedef struct {
	volatile unsigned int value;
} cvmx_spinlock_t;
static inline void cvmx_spinlock_unlock (cvmx_spinlock_t * lock)
{
	OCTEON_SYNC;
	lock->value = 0;
	OCTEON_SYNCW;
}

static inline void cvmx_spinlock_lock (cvmx_spinlock_t * lock)
{
	unsigned int tmp;

	__asm__ __volatile__ (".set push              \n"
			      ".set noreorder         \n"
			      "1: ll   %[tmp], %[val] \n"
			      "   bnez %[tmp], 1b     \n"
			      "   li   %[tmp], 1      \n"
			      "   sc   %[tmp], %[val] \n"
			      "   beqz %[tmp], 1b     \n"
			      "   sync                \n"
			      ".set pop               \n"
			      :[val] "+m" (lock->value),
			      [tmp] "=&r" (tmp)
			      ::"memory");

}
#endif
/************************************************************************/

/* Default stack and heap sizes, in bytes */
#define DEFAULT_STACK_SIZE              (1*1024*1024)
#define DEFAULT_HEAP_SIZE               (3*1024*1024)

#define ALIGN_MASK(x)   ((~0ULL) << (x))
#define TLB_PAGE_SIZE_FROM_EXP(x)   ((1UL) << (x))
#define ALIGN_ADDR_DOWN(addr, align)   ((addr) & (align))
#define MAKE_XKPHYS(x)       ((1ULL << 63) | (x))
#define MAKE_KSEG0(x)       ((1 << 31) | (x))

/* Normalize any xkphys addresses to have only bit 63 set,
** and strip off any cache coherency information.
** Don't do anything to 32 bit compatibility addresses */
static inline uint64_t octeon_fixup_xkphys (uint64_t addr)
{
	if ((addr & (0xffffffffull << 32)) == (0xffffffffull << 32))
		return addr;

	return addr & ~(0x78ull << 56);
}

#ifdef CONFIG_OCTEON_QLM
/**
 * Configure qlm/dlm speed and mode.
 * @param qlm     The QLM or DLM to configure
 * @param speed   The speed the QLM needs to be configured in Mhz.
 * @param mode    The QLM to be configured as SGMII/XAUI/PCIe.
 * @param rc      Only used for PCIe, rc = 1 for root complex mode, 0 for EP
 *		  mode.
 * @param pcie_mode Only used when qlm/dlm are in pcie mode.
 * @param ref_clk_sel Reference clock to use for 70XX
 * @param ref_clk_input	When set selects the external ref_pad_clk_{p,m} inputs
 *			as the reference-clock source.  When deasserted,
 *			ref_alt_clk_{p,m} are selected from an on-chip source of
 *			the reference clock.
 *
 * @return       Return 0 on success or -1.
 */
extern int octeon_configure_qlm(int qlm, int speed, int mode, int rc,
				int pcie_mode, int ref_clk_sel,
				int ref_clk_input);
#endif

#endif /* __OCTEON_BOOT_H__ */
