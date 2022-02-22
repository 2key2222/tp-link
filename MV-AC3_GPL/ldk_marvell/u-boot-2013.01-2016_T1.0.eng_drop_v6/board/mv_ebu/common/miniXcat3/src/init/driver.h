/*#include <inttypes.h>*/
#include <stddef.h>
#include <configs/msys.h>

typedef unsigned long  GT_UINTPTR;
typedef unsigned int   GT_U32;
typedef unsigned short GT_U16;
typedef unsigned char  GT_U8;

typedef int             GT_32;
typedef short           GT_16;
typedef char            GT_8;
typedef unsigned int   GT_BOOL;


typedef GT_U32    GT_STATUS;

#define GT_OK                    (0x00) /* Operation succeeded */
#define GT_FAIL                  (0x01) /* Operation failed    */
#define GT_NOT_SUPPORTED         (0x10) /* This request is not support           */


/*
 * typedef: struct DRV_HW_INFO
 *
 * Description:
 *
 * Hardware access info to manage PP
 *
 * Fields:
 *
 *   baseAddr        - Base address to which PP is mapped on PCI.
 *                     in case of SMI it would be smiIdSel.
 *   internalPciBase - Base address to which the internal PCI registers
 *                     are mapped to.
 *   resetAndInitControllerBase - Base address to which Reset and Init
 *                     Controller (a.k.a. DFX server) are mapped to.
 *                     (APPLICABLE DEVICES: Lion3; Bobcat2; xCat3, etc)
 *   busNo           - PCI/PEX busNo or SMI Id
 *   devSel          - PCI/PEX deviceNo
 *   funcNo          - PCI/PEX func
 *
 * Comments:
 *
 */
typedef struct
{
    GT_UINTPTR  baseAddr;
    GT_UINTPTR  internalPciBase;
    GT_UINTPTR  resetAndInitControllerBase;
    GT_U32      busNo;
    GT_U32      devSel;
    GT_U32      funcNo;
} DRV_HW_INFO;

struct DRIVER_OBJ_STCT;

/*******************************************************************************
* HW_DESTROY_DRV_FUNC
*
* DESCRIPTION:
*       Destroy driver object
*
* INPUTS:
*       drv             - Driver object ptr
*
* OUTPUTS:
*       None
*
* RETURNS:
*       None
*
* COMMENTS:
*       None.
*
*******************************************************************************/
typedef void (*HW_DESTROY_DRV_FUNC)
(
    struct DRIVER_OBJ_STCT *drv
);

/*******************************************************************************
* HW_INIT_FUNC
*
* DESCRIPTION:
*       This function initializes a given PP.
*
* INPUTS:
*       drv             - Driver object ptr
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on error.
*
* COMMENTS:
*       None.
*
*******************************************************************************/
typedef GT_STATUS (*HW_INIT_FUNC)
(
    struct DRIVER_OBJ_STCT *drv
);

/*******************************************************************************
* HW_READ_REG_FUNC
*
* DESCRIPTION:
*       Read a register value from the given PP.
*
* INPUTS:
*       drv             - Driver object ptr
*       regAddr         - The register's address to read from.
*
* OUTPUTS:
*       data - Includes the register value.
*
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on hardware error
*
* COMMENTS:
*       None.
*
*******************************************************************************/
typedef GT_STATUS (*HW_READ_REG_FUNC)
(
    struct DRIVER_OBJ_STCT *drv,
    GT_U32   regAddr,
    GT_U32  *data
);

/*******************************************************************************
* HW_WRITE_REG_FUNC
*
* DESCRIPTION:
*       Write to a PP's given register.
*
* INPUTS:
*       drv             - Driver object ptr
*       regAddr         - The register's address to write to.
*       data            - The value to be written.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on hardware error
*
* COMMENTS:
*       None.
*
*******************************************************************************/
typedef GT_STATUS (*HW_WRITE_REG_FUNC)
(
    struct DRIVER_OBJ_STCT *drv,
    GT_U32   regAddr,
    GT_U32   value
);

typedef GT_STATUS (*HW_WRITE_PHY_REG_FUNC)
(
    struct DRIVER_OBJ_STCT *drv,
	GT_U32 phyAddr, GT_U32 devAddr, GT_U16 regAddr, GT_U16 data
);

typedef GT_STATUS (*HW_READ_PHY_REG_FUNC)
(
    struct DRIVER_OBJ_STCT *drv,
	GT_U32 phyAddr, GT_U32 devAddr, GT_U16 regAddr, GT_U16 *data
);


/*
 * Typedef: struct DRIVER_OBJ_STC
 *
 * Description: The structure defines the PCI/SMI/TWSI driver object
 *
 *
 * Fields:
 *      readReg       - read register value
 *      writeReg      - write register value
 *      readMng       - (optional) read internal PCI register
 *      writeMng      - (optional) write internal PCI register
 *      readDfx       - (optional) read Reset and Init 
 *                                  Controller register value
 *      writeDfx      - (optional) write Reset and Init 
 *                                  Controller register value
 */
typedef struct DRIVER_OBJ_STCT {
    HW_DESTROY_DRV_FUNC               destroyDrv;
    HW_INIT_FUNC                      hwInit;
    HW_READ_REG_FUNC                  readReg;
    HW_WRITE_REG_FUNC                 writeReg;
    HW_READ_REG_FUNC                  readMng;
    HW_WRITE_REG_FUNC                 writeMng;
    HW_READ_REG_FUNC                  readDfx;
    HW_WRITE_REG_FUNC                 writeDfx;
	HW_WRITE_PHY_REG_FUNC			  writeXsmi;
	HW_READ_PHY_REG_FUNC			  readXsmi;
}DRIVER_OBJ_STC;

/*******************************************************************************
* cpssDriverPpHwBusPciInit
*
* DESCRIPTION:
*       This function initializes the Hw control structure of a given PP.
*
* INPUTS:
*       devNum      - The PP's device number to init the structure for.
*       portGroupId - The port group id.
*       hwInfo      - Hardware info (PCI address)
*
* OUTPUTS:
*       drvPtr   - pointer
*
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on error.
*
* COMMENTS:
*
*******************************************************************************/
GT_STATUS driverInit
(
    DRV_HW_INFO    *hwInfo,
    DRIVER_OBJ_STC **drvRet
);



/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

/* Adding special/missing settings here */

extern void printf(const char *fmt, ...);
extern void mvPrintf(const char *fmt, ...);
extern void mvSprintf(char* s,char *fmt, ...);

/***************************************************/
/* CUSTOMER_NOTICE:
   Set here thge project/board related settings
   
*/

#define CPU_LE   /* Need to find more appropriate place for that */

/* Set here one of the interfaces modes used to access the PP device */
#undef  PCIe_INTERFASE_IS_USED
#define MSYS_INTERNAL_CPU_IS_USED
#undef  SMI_ACCESS_IS_USED    /* For future implementation */

#if defined(PCIe_INTERFASE_IS_USED) || defined(MSYS_INTERNAL_CPU_IS_USED)
#define REG_ACCESS_BY_MEMORY_MAP
#endif

#define INTER_REGS_BASE                         0xF1000000

/* Set only one of the PHY types used in this project (xCAT3-DB is using 1548) */
 
#ifdef CONFIG_PHY_1680
#define  SUPPORT_PHY_1680 
#elif defined(CONFIG_PHY_AQR412C)
#define SUPPORT_PHY_AQR412C
#else
#define SUPPORT_PHY_1548
#endif

/* CUSTOMER_NOTICE_END */

/* Swap tool */

/* 16bit nibble swap. For example 0x1234 -> 0x2143                          */
#define GT_NIBBLE_SWAP_16BIT(X)    (((X&0xf) << 4) |     \
                                    ((X&0xf0) >> 4) |    \
                                    ((X&0xf00) << 4) |   \
                                    ((X&0xf000) >> 4))
        
/* 32bit nibble swap. For example 0x12345678 -> 0x21436587                  */
#define GT_NIBBLE_SWAP_32BIT(X)    (((X&0xf) << 4) |       \
                                    ((X&0xf0) >> 4) |      \
                                    ((X&0xf00) << 4) |     \
                                    ((X&0xf000) >> 4) |    \
                                    ((X&0xf0000) << 4) |   \
                                    ((X&0xf00000) >> 4) |  \
                                    ((X&0xf000000) << 4) | \
                                    ((X&0xf0000000) >> 4))

/* 16bit byte swap. For example 0x1122 -> 0x2211                            */
#define GT_BYTE_SWAP_16BIT(X) ((((X)&0xff)<<8) | (((X)&0xff00)>>8))

/* 32bit byte swap. For example 0x11223344 -> 0x44332211                    */
#define GT_BYTE_SWAP_32BIT(X) ((((X)&0xff)<<24) |                       \
                               (((X)&0xff00)<<8) |                      \
                               (((X)&0xff0000)>>8) |                    \
                               (((X)&0xff000000)>>24))

/* 64bit byte swap. For example 0x11223344.55667788 -> 0x88776655.44332211  */
#define GT_BYTE_SWAP_64BIT(X) ((l64) ((((X)&0xffULL)<<56) |             \
                                      (((X)&0xff00ULL)<<40) |           \
                                      (((X)&0xff0000ULL)<<24) |         \
                                      (((X)&0xff000000ULL)<<8) |        \
                                      (((X)&0xff00000000ULL)>>8) |      \
                                      (((X)&0xff0000000000ULL)>>24) |   \
                                      (((X)&0xff000000000000ULL)>>40) | \
                                      (((X)&0xff00000000000000ULL)>>56)))

/* Endianess macros.                                                        */
#if defined(CPU_LE)
    #define GT_16BIT_LE(X)  (X) 
    #define GT_32BIT_LE(X)  (X)
    #define GT_64BIT_LE(X)  (X)
    #define GT_16BIT_BE(X)  GT_BYTE_SWAP_16BIT(X)
    #define GT_32BIT_BE(X)  GT_BYTE_SWAP_32BIT(X)
    #define GT_64BIT_BE(X)  GT_BYTE_SWAP_64BIT(X)
#elif defined(CPU_BE)
    #define GT_16BIT_LE(X)  GT_BYTE_SWAP_16BIT(X) 
    #define GT_32BIT_LE(X)  GT_BYTE_SWAP_32BIT(X)
    #define GT_64BIT_LE(X)  GT_BYTE_SWAP_64BIT(X)
    #define GT_16BIT_BE(X)  (X)
    #define GT_32BIT_BE(X)  (X)
    #define GT_64BIT_BE(X)  (X)
#else
    #error "CPU endianess isn't defined!\n"
#endif 


/* CPU architecture dependent 32, 16, 8 bit read/write IO addresses */
#define GT_MEMIO32_WRITE(addr, data)	\
    ((*((volatile unsigned int*)(addr))) = ((unsigned int)(data)))

#define GT_MEMIO32_READ(addr)       	\
    ((*((volatile unsigned int*)(addr))))

#define GT_MEMIO16_WRITE(addr, data)	\
    ((*((volatile unsigned short*)(addr))) = ((unsigned short)(data)))

#define GT_MEMIO16_READ(addr)       	\
    ((*((volatile unsigned short*)(addr))))

#define GT_MEMIO8_WRITE(addr, data) 	\
    ((*((volatile unsigned char*)(addr))) = ((unsigned char)(data)))

#define GT_MEMIO8_READ(addr)        	\
    ((*((volatile unsigned char*)(addr))))


/* No Fast Swap implementation (in assembler) for ARM */
#define GT_32BIT_LE_FAST(val)            GT_32BIT_LE(val)
#define GT_16BIT_LE_FAST(val)            GT_16BIT_LE(val)
#define GT_32BIT_BE_FAST(val)            GT_32BIT_BE(val)
#define GT_16BIT_BE_FAST(val)            GT_16BIT_BE(val)
    
/* 32 and 16 bit read/write in big/little endian mode */

/* 16bit write in little endian mode */
#define GT_MEMIO_LE16_WRITE(addr, data) \
        GT_MEMIO16_WRITE(addr, GT_16BIT_LE_FAST(data))
        

/* 16bit read in little endian mode */
static __inline GT_U16 GT_MEMIO_LE16_READ(GT_U32 addr)
{
	GT_U16 data;

	data= (GT_U16)GT_MEMIO16_READ(addr);

	return (GT_U16)GT_16BIT_LE_FAST(data);
}

/* 32bit write in little endian mode */
#define GT_MEMIO_LE32_WRITE(addr, data) \
        GT_MEMIO32_WRITE(addr, GT_32BIT_LE_FAST(data))

/* 32bit read in little endian mode */
static __inline GT_U32 GT_MEMIO_LE32_READ(GT_U32 addr)
{
	GT_U32 data;

	data= (GT_U32)GT_MEMIO32_READ(addr);

	return (GT_U32)GT_32BIT_LE_FAST(data);
}


#define GT_REG_READ(offset)         	\
        (GT_MEMIO_LE32_READ(INTER_REGS_BASE | (offset)))

#define GT_REG_WRITE(offset, val)    \
        GT_MEMIO_LE32_WRITE((INTER_REGS_BASE | (offset)), (val))
                                                

#define PCI_BUS(d)	(((d) >> 16) & 0xff)
#define PCI_DEV(d)	(((d) >> 11) & 0x1f)
#define PCI_FUNC(d)	(((d) >> 8) & 0x7)
#define PCI_BDF(b,d,f)	((b) << 16 | (d) << 11 | (f) << 8)

/*******************************************/

/***************************************************/
/* CUSTOMER_NOTICE:
   Set here thge project/board related address values
   
*/
#ifdef  PCIe_INTERFASE_IS_USED

	/* In case the PP is connected via PCIe interface */
	#define PP_INTER_REGS_BASE  0xE0000000
	#define PP_SWITCH_REGS_BASE 0xE4000000
	#define PP_DFX_REGS_BASE    0xE0800000

#elif defined(MSYS_INTERNAL_CPU_IS_USED)

	/* In case the PP is connected via MBUS interface */
	#define CPU_INTER_REGS_BASE  INTER_REGS_BASE
	#define SWITCH_REGS_BASE     0xA8000000
	#define DFX_REGS_BASE        0xF6000000

#else
	#error  - CPU type not defined here...
#endif 

/* CUSTOMER_NOTICE_END */
