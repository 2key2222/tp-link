/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
* driver_pci.c
*
* DESCRIPTION:
*       Prestera driver Hardware read and write functions simple implementation.
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/

#include "driver.h"


#undef _ERRATA_SERDES_INTERNAL_REGS_ACCESS_WA_E
/* mutex protection */
#define ADDR_COMP_REG 0

#if 0
#define debugPrint(_x)\
    printf _x
#endif
#define debugPrint(_x)

#ifdef HW_DEBUG_TRACE
#define debugTrace(_x)      printf _x
#else
#define debugTrace(_x)
#endif  /* HW_DEBUG_TRACE */

#ifdef CPU_ARM
#define GT_SYNC
#endif

#ifndef GT_SYNC
#define GT_SYNC
#endif


typedef struct DRIVER_OBJ_PCI_STCT {
    DRIVER_OBJ_STC common;
    GT_UINTPTR          baseAddr;
    GT_UINTPTR          internalPciBase;
    GT_UINTPTR          resetAndInitControllerBase;
    GT_U32              addrCompletShadow[4];
    GT_U8               compIdx;
} DRIVER_OBJ_PCI_STC;


#if defined(CPU_LE)
    #define CPSS_32BIT_LE(X)  (X)
#elif defined(CPU_BE)
    #define CPSS_32BIT_LE(X)  __builtin_bswap32(X)
#else
    #error "CPU endianess isn't defined!\n"
#endif






/*******************************************************************************
* Intenal Macros and definitions
*******************************************************************************/
/* future changes possible */
#define BASEADDR(_drv) (_drv->baseAddr)

/*******************************************************************************
* External usage environment parameters
*******************************************************************************/

/*******************************************************************************
* Forward functions declarations.
*******************************************************************************/
static GT_STATUS hwWrite
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32      regAddr,
    GT_U32      length,
    GT_U32      *dataPtr
);



static GT_STATUS hwCompletion
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32      regAddr,
    GT_U8       *compIdxPtr,
    GT_UINTPTR  *addressPtr
)
{
    GT_U8   addrRegion; /* 8 bit MST value of PP internal address*/
    GT_UINTPTR  address;  /*physical access address for PCI access */
    GT_U8   compIdx; /* address completion register field index 0-3*/
    GT_U8   i;      /* count iterator for the completion index compare loop*/
    GT_U32  data;   /* data to be write to memory */

    /* check if addrRegion is 0 */
    if ((regAddr & 0xFF000000) == 0)
    {
        compIdx = 0;
    }
    else
    {
        addrRegion = (GT_U8)(regAddr >> 24);
        /* compare addr region to existing Address regions*/
        for (i = 3;(i > 1) &&
             (addrRegion != drv->addrCompletShadow[i]);
             i--);
        if(i == 1)
        {   /* Set addrRegion in AddrCompletion register */

            /*round robin on Region index : 2,3*/
            drv->compIdx++;
            if (drv->compIdx >= 4)
                drv->compIdx = 2;
            compIdx = drv->compIdx;

                      /*update Address Completion shadow*/
            drv->addrCompletShadow[compIdx] = addrRegion;

            /* update Hw Address Completion - using completion region 0 */
            address = BASEADDR(drv) + ADDR_COMP_REG;
            data = (drv->addrCompletShadow[1]<<8) |
                   (drv->addrCompletShadow[2]<<16) |
                   (drv->addrCompletShadow[3]<<24);

            data = CPSS_32BIT_LE(data);

            *(volatile GT_U32 *)(address) = data;
            /*write the address completion 3 times.
            because the PP have a 2 entry write buffer
            so, the 3 writes will make sure we do get
            to the hardware register itself */
            GT_SYNC;
            *(volatile GT_U32 *)(address) = data;
            GT_SYNC;
            *(volatile GT_U32 *)(address) = data;
            GT_SYNC;
        }
        else
        {
            compIdx = i;
        }
    }

    address = (BASEADDR(drv) + ((compIdx << 24) | (regAddr & 0x00ffffff)));
    *compIdxPtr = compIdx;
    *addressPtr = address;
    return GT_OK;
}

/*******************************************************************************
*  hwWrite
*
* DESCRIPTION:
*      This function receives address and data pointer and write the data to
*      the PP.
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address .
*       length  - Nubmber of writes in 4 byte each.
*       dataPtr - Pointer to data array.
*
* OUTPUTS:
*       None.
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on hardware error
*
* COMMENTS:
*       in case that the region (addr[31:24]) is 0 we preform the write sequence
*       without any mutual exclusion, this is mandatory due to the fact that
*       the ISR also uses this function.
*
*******************************************************************************/
static GT_STATUS hwWrite
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32      regAddr,
    GT_U32      length,
    GT_U32      *dataPtr
)
{
    GT_UINTPTR  address;  /*physical address for PCI access */
    GT_U8   compIdx; /* address completion register field index 0-3*/
    GT_U32  j = 0;      /* count iterator for the write loop*/
    GT_U32  nextRegionAddr; /* address of the next region after the one
                                currently used */
    GT_U32  loopLength = 0; /* when length exceeds region addr, Set to end of
                            region range */

    debugTrace(("Write: addr 0x%X len 0x%X data 0x%X \n", regAddr, length, *dataPtr));

    hwCompletion(drv, regAddr, &compIdx, &address);

    /* check whether completion region boundaries exceeded*/
    nextRegionAddr =  (GT_U32)(drv->addrCompletShadow[compIdx] + 1)<<24;
    if((GT_U32)(regAddr + length * 4 - 1) < nextRegionAddr)
    {

        for(j = 0; j < length; j++)
        {
            *((volatile GT_U32*)address) = CPSS_32BIT_LE(dataPtr[j]);

            /* need to put GT_SYNC to avoid from having the CPU doing
            * write combine. Some CPUs like advanced new PPC can do write combining
            * of two writes to continuous addresses. So, to avoid that we use the eioio
            * in PPC architecture;*/
            GT_SYNC;

            address += 4;
        }
    }
    else
    {
        loopLength = (nextRegionAddr - regAddr) / 4;
        for(j = 0; j < loopLength; j++)
        {
            *((volatile GT_U32*)address) = CPSS_32BIT_LE(dataPtr[j]);
            /* need to put GT_SYNC to avoid from having the CPU doing
            * write combine. Some CPUs like advanced new PPC can do write combining
            * of two writes to continuous addresses. So, to avoid that we use the eioio
            * in PPC architecture; */
            GT_SYNC;

            address += 4;
        }

        /* Recursive call for rest of data in next region.  */
        hwWrite(drv,nextRegionAddr,length-loopLength,
                dataPtr+loopLength);
    }   /* End of if complId !=0    */

    return GT_OK;
}




/*******************************************************************************
*  hwRead
*
* DESCRIPTION:
*      This function receives address and buffer pointer and reads the the PP
*      RAM into the buffer.
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address .
*       length  - Nubmber of writes in 4 byte each.
*       dataPtr - Pointer to data array.
*
* OUTPUTS:
*       None.
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on hardware error
*
* COMMENTS:
*       in case that the region (addr[31:24]) is 0 we preform the read sequence
*       without any mutual exclusion, this is mandatory due to the fact that
*       the ISR also uses this function.
*
*******************************************************************************/
static GT_STATUS hwRead
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32      regAddr,
    GT_U32      length,
    GT_U32      *dataPtr
)
{
    GT_UINTPTR  address;  /*physical access address for PCI access */
    GT_U8   compIdx; /* address completion register field index 0-3*/
    GT_U32  temp;
    GT_U32  j;      /* count iterator for the write loop*/
    GT_U32  nextRegionAddr; /* address of the next region after the one
                                currently used */
    GT_U32  loopLength = 0; /* when length exceeds region addr, Set to end of
                            region range */

    hwCompletion(drv, regAddr, &compIdx, &address);

    /* check whether completion region boundaries are exceeded*/
    nextRegionAddr = (GT_U32)(drv->addrCompletShadow[compIdx]+1)<<24;
    if ((GT_U32)(regAddr+length*4-1) < nextRegionAddr)
    {
        for(j = 0;j < length;j++)
        {
            temp = *( (volatile GT_U32 *) address);
            GT_SYNC; /*to avoid read combine */
            dataPtr[j] = CPSS_32BIT_LE(temp);
            address += 4;
        }
    }
    else
    {
        loopLength =  (nextRegionAddr - regAddr)/4;
        for(j = 0;j < loopLength ;j++)
        {
            temp = *( (volatile GT_U32 *) address);
            GT_SYNC;/* to avoid read combine by some advanced CPUs */
            dataPtr[j] = CPSS_32BIT_LE(temp);
            address += 4;
        }

        /* recursive call for rest of data in next region */
        hwRead(drv,nextRegionAddr,length-loopLength,
                dataPtr+loopLength);
    }

    debugTrace(("Read: addr 0x%X len 0x%X data 0x%X \n", regAddr, length, *dataPtr));


    return GT_OK;
}


/*******************************************************************************
* hwPpPciReadRegister
*
* DESCRIPTION:
*       Read a register value from the given PP.
*
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address to read from.
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
static GT_STATUS hwPpPciReadRegister
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32   regAddr,
    GT_U32  *data
)
{
    if ((regAddr & 0xFFFF0000) == 0x09800000)
    {
#ifdef _ERRATA_SERDES_INTERNAL_REGS_ACCESS_WA_E
        GT_U32 dummy;

        hwRead (drv, PRV_CPSS_DEVICE_ID_AND_REV_REG_ADDR_CNS, 1, &dummy);
        hwRead (drv, PRV_CPSS_DEVICE_ID_AND_REV_REG_ADDR_CNS, 1, &dummy);
#endif
    }

    debugPrint(("Read from reg 0x%x,", regAddr));
    hwRead (drv,regAddr,1, data);
    debugPrint((" data 0x%x.\n", *data));
    return GT_OK;
}


/*******************************************************************************
* hwPpPciWriteRegister
*
* DESCRIPTION:
*       Write to a PP's given register.
*
* INPUTS:
*       drv             - Driver object ptr
*       regAddr - The register's address to write to.
*       data    - The value to be written.
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
static GT_STATUS hwPpPciWriteRegister
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32 regAddr,
    GT_U32 value
)
{
    if ((regAddr & 0xFFFF0000) == 0x09800000)
    {
#ifdef _ERRATA_SERDES_INTERNAL_REGS_ACCESS_WA_E
        GT_U32 dummy;

        hwRead (drv, PRV_CPSS_DEVICE_ID_AND_REV_REG_ADDR_CNS, 1, &dummy);
        hwRead (drv, PRV_CPSS_DEVICE_ID_AND_REV_REG_ADDR_CNS, 1, &dummy);
#endif
    }

    debugPrint(("Write to reg 0x%x, data 0x%x.\n", regAddr, value));

    hwWrite (drv,regAddr, 1,&value);

    return GT_OK;
}


/*******************************************************************************
* hwPpPciReadInternalPciReg
*
* DESCRIPTION:
*       This function reads from an internal pci register, it's used by the
*       initialization process and the interrupt service routine.
*
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address to read from.
*
* OUTPUTS:
*       data    - The read data.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
* COMMENTS:
*       None.
*
*******************************************************************************/
static GT_STATUS hwPpPciReadInternalPciReg
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32  regAddr,
    GT_U32  *data
)
{
    GT_UINTPTR address;     /* physical access address for PCI transaction. */
    GT_U32  temp;

    address = (drv->internalPciBase + regAddr);
    temp = *((volatile GT_U32 *)address);

    GT_SYNC; /*to avoid read combining */

    *data = CPSS_32BIT_LE(temp);

    debugTrace(("PCI Read: addr 0x%X data 0x%X \n", regAddr, *data));

    return GT_OK;
}


/*******************************************************************************
* hwPpPciWriteInternalPciReg
*
* DESCRIPTION:
*       This function writes to an internal pci register, it's used by the
*       initialization process and the interrupt service routine.
*
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address to write to.
*       data    - Data to be written.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
* COMMENTS:
*       None.
*
*******************************************************************************/
static GT_STATUS hwPpPciWriteInternalPciReg
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32  regAddr,
    GT_U32  data
)
{
    GT_UINTPTR address;     /* physical address for PCI transaction.    */

    debugTrace(("PCI Write: addr 0x%X data 0x%X \n", regAddr, data));

    address = (drv->internalPciBase + regAddr);
    *((volatile GT_U32*)address) = CPSS_32BIT_LE(data);

    return GT_OK;
}


/*******************************************************************************
* hwPpPciResetAndInitCtrlReadRegister
*
* DESCRIPTION:
*       This function reads a register from the Reset and Init Controller.
*
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address to read from.
*
* OUTPUTS:
*       data    - The read data.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
* COMMENTS:
*       None.
*
*******************************************************************************/
static GT_STATUS hwPpPciResetAndInitCtrlReadRegister
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32  regAddr,
    GT_U32  *data
)
{
    GT_UINTPTR address;     /* physical access address for transaction. */
    GT_U32  temp;

    if (drv->resetAndInitControllerBase == 0)
        return GT_NOT_SUPPORTED;

    address = (drv->resetAndInitControllerBase + regAddr);
    temp = *((volatile GT_U32 *)address);

    GT_SYNC; /*to avoid read combining */

    *data = CPSS_32BIT_LE(temp);

    debugTrace(("Reset and Init Controller Read: addr 0x%X data 0x%X \n", 
                regAddr, *data));

    return GT_OK;
}


/*******************************************************************************
* hwPpPciResetAndInitCtrlWriteRegister
*
* DESCRIPTION:
*       This function writes a register to the Reset and Init Controller.
*
* INPUTS:
*       drv     - Driver object ptr
*       regAddr - The register's address to wrire to.
*       data    - Data to be written.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       GT_OK   - on success,
*       GT_FAIL - otherwise.
*
* COMMENTS:
*       None.
*
*******************************************************************************/
static GT_STATUS hwPpPciResetAndInitCtrlWriteRegister
(
    DRIVER_OBJ_PCI_STC *drv,
    GT_U32  regAddr,
    GT_U32  data
)
{
    GT_UINTPTR address;     /* physical address for transaction.    */

    if (drv->resetAndInitControllerBase == 0)
        return GT_NOT_SUPPORTED;

    debugTrace(("Reset and Init Controller Write: addr 0x%X data 0x%X \n", regAddr, data));

    address = (drv->resetAndInitControllerBase + regAddr);
    *((volatile GT_U32*)address) = CPSS_32BIT_LE(data);

    return GT_OK;
}

/*XSMI base addr: 0xa8000000:Switch Reg Base Addr*/
#include "eth-phy/mvEthPhyRegs.h"

/* CPU architecture dependent 32, 16, 8 bit read/write IO addresses */
#define CPSS_MEMIO32_WRITE(addr, data)	\
    ((*((volatile unsigned int*)(addr))) = ((unsigned int)(data)))

#define CPSS_MEMIO32_READ(addr)       	\
    ((*((volatile unsigned int*)(addr))))

/* 32bit write in little endian mode */
#define CPSS_MEMIO_LE32_WRITE(addr, data) \
        CPSS_MEMIO32_WRITE(addr, CPSS_32BIT_LE(data))

/* 32bit read in little endian mode */
static __inline GT_U32 CPSS_MEMIO_LE32_READ(GT_U32 addr)
{
	GT_U32 data;

	data= (GT_U32)CPSS_MEMIO32_READ(addr);

	return (GT_U32)CPSS_32BIT_LE(data);
}


#define HWPP_XSMI_REG_OFF 0x40000

static GT_STATUS hwPpXsmiCheckParam(GT_U32 phyAddr, GT_U32 devAddr, GT_U16 regAddr)
{
	/* check parameters */
	if ((phyAddr << ETH_PHY_XSMI_PHY_ADDR_OFFS) & ~ETH_PHY_XSMI_PHY_ADDR_MASK) {
		printf("%s: Err. Illegal PHY address %d\n", __func__, phyAddr);
		return GT_FAIL;
	}
	if ((devAddr <<  ETH_PHY_XSMI_DEV_ADDR_OFFS) & ~ETH_PHY_XSMI_DEV_ADDR_MASK) {
		printf("%s: Err. Illegal device address %d\n", __func__, devAddr);
		return GT_FAIL;
	}
	if ((regAddr << ETH_PHY_XSMI_REG_ADDR_OFFS) & ~ETH_PHY_XSMI_REG_ADDR_MASK) {
		printf("%s: Err. Illegal register address %d\n", __func__, regAddr);
		return GT_FAIL;
	}
	return GT_OK;
}

static GT_STATUS hwPpXsmiWaitReady(DRIVER_OBJ_PCI_STC *drv)
{
	GT_U32 xSmiReg;
	volatile GT_U32 timeout;
	timeout = ETH_PHY_XSMI_TIMEOUT;
	/* wait till the XSMI is not busy*/
	do {
		/* read xsmi register */
		xSmiReg = CPSS_MEMIO_LE32_READ(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_MANAGEMENT);
		if (timeout-- == 0) {
			printf("%s: XSMI busy timeout\n", __func__);
			return GT_FAIL;
		}
	} while (xSmiReg & ETH_PHY_XSMI_BUSY_MASK);

	return GT_OK;
}

static GT_STATUS hwPpXsmiWaitValid(DRIVER_OBJ_PCI_STC *drv)
{
	GT_U32 xSmiReg;
	volatile GT_U32 timeout;
	timeout = ETH_PHY_XSMI_TIMEOUT;

	/*wait till readed value is ready */
	do {
		/* read xsmi register */
		xSmiReg = CPSS_MEMIO_LE32_READ(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_MANAGEMENT);

		if (timeout-- == 0) {
			printf("%s: XSMI read-valid timeout\n", __func__);
			return GT_FAIL;
		}
	} while (!(xSmiReg & ETH_PHY_XSMI_READ_VALID_MASK));

	return GT_OK;
}

static GT_STATUS hwPpPciWriteXsmiReg
(
	DRIVER_OBJ_PCI_STC *drv,
	GT_U32 phyAddr, GT_U32 devAddr, GT_U16 regAddr, GT_U16 data
)
{
	GT_U32 xSmiReg, xSmiAddr;

	if (hwPpXsmiCheckParam(phyAddr, devAddr, regAddr) != GT_OK)
		return GT_FAIL;

	if (hwPpXsmiWaitReady(drv) != GT_OK)
		return GT_FAIL;

	xSmiAddr = (regAddr << ETH_PHY_XSMI_REG_ADDR_OFFS);
	CPSS_MEMIO_LE32_WRITE(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_REG_ADDR, xSmiAddr);

	/* fill the phy address and regiser offset and write opcode and data*/
	xSmiReg = (data << ETH_PHY_XSMI_DATA_OFFS);
	xSmiReg |= (phyAddr <<  ETH_PHY_XSMI_PHY_ADDR_OFFS) | (devAddr << ETH_PHY_XSMI_DEV_ADDR_OFFS);
	xSmiReg |= ETH_PHY_XSMI_OPCODE_ADDR_WRITE;

	/* write the xsmi register */
	//printf("%s: phyAddr=0x%08x devAddr = 0x%08x regAddr=0x%08x data=0x%04x\n", __func__, phyAddr, devAddr, regAddr, data);
	CPSS_MEMIO_LE32_WRITE(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_MANAGEMENT, xSmiReg);

	return GT_OK;

}

static GT_STATUS hwPpPciReadXsmiReg
(
	DRIVER_OBJ_PCI_STC *drv,
	GT_U32 phyAddr, GT_U32 devAddr, GT_U16 regAddr, GT_U16 *data
)
{
	GT_U32 xSmiReg, xSmiAddr;

	if (hwPpXsmiCheckParam(phyAddr, devAddr, regAddr) != GT_OK)
		return GT_FAIL;

	if (hwPpXsmiWaitReady(drv) != GT_OK)
		return GT_FAIL;	

	xSmiAddr = (regAddr << ETH_PHY_XSMI_REG_ADDR_OFFS);
	CPSS_MEMIO_LE32_WRITE(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_REG_ADDR, xSmiAddr);

	/* fill the phy address and regiser offset and read opcode */
	xSmiReg = (phyAddr <<  ETH_PHY_XSMI_PHY_ADDR_OFFS) | (devAddr << ETH_PHY_XSMI_DEV_ADDR_OFFS)|
			   ETH_PHY_XSMI_OPCODE_ADDR_READ;

	/* write the xsmi register */
	CPSS_MEMIO_LE32_WRITE(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_MANAGEMENT, xSmiReg);

	if (hwPpXsmiWaitValid(drv) != GT_OK)
		return GT_FAIL;

	*data = (GT_U16)(CPSS_MEMIO_LE32_READ(drv->baseAddr+HWPP_XSMI_REG_OFF + ETH_PHY_XSMI_MANAGEMENT) &
			ETH_PHY_XSMI_DATA_MASK);

	return GT_OK;	
}

/*******************************************************************************
* hwPpPciHwInit
*
* DESCRIPTION:
*       This function initializes a given PP.
*
* INPUTS:
*       drv     - Driver object ptr
*
* OUTPUTS:
*
* RETURNS:
*       GT_OK   - on success
*       GT_FAIL - on hardware error
*
* COMMENTS:
*       None.
*
*******************************************************************************/
static GT_STATUS hwPpPciHwInit
(
    DRIVER_OBJ_PCI_STC *drv
)
{
    GT_UINTPTR  address;
    GT_U8       i;

    /* Reset Hw Address Completion          */
    address = BASEADDR(drv) + ADDR_COMP_REG;

    *(volatile GT_U32 *)(address) = 0;
    *(volatile GT_U32 *)(address) = 0;
    *(volatile GT_U32 *)(address) = 0;
    GT_SYNC;

    /* Update Address Completion shadow     */
    for (i = 0; i < 4; i++)
    {
       drv->addrCompletShadow[i] = 0;
    }
    return GT_OK;
}

/*******************************************************************************
* hwPpPciDestroyDrv
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
static void hwPpPciDestroyDrv
(
    DRIVER_OBJ_PCI_STC *drv
)
{
    free(drv);
}

/*******************************************************************************
* driverInit
*
* DESCRIPTION:
*       This function initializes the Hw control structure of a given PP.
*
* INPUTS:
*       hwInfo      - Hardware info 
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
    DRIVER_OBJ_STC     **drvRet
)
{
    DRIVER_OBJ_PCI_STC *drv;

    /* create object */
    drv = (DRIVER_OBJ_PCI_STC*)malloc(sizeof(*drv));
    if (drv == NULL)
        return GT_FAIL;

    memset(drv, 0, sizeof(*drv));
    drv->common.destroyDrv = (HW_DESTROY_DRV_FUNC) hwPpPciDestroyDrv;
    drv->common.hwInit = (HW_INIT_FUNC) hwPpPciHwInit;
    drv->common.readReg = (HW_READ_REG_FUNC) hwPpPciReadRegister;
    drv->common.writeReg = (HW_WRITE_REG_FUNC) hwPpPciWriteRegister;
    drv->common.readMng = (HW_READ_REG_FUNC) hwPpPciReadInternalPciReg;
    drv->common.writeMng = (HW_WRITE_REG_FUNC) hwPpPciWriteInternalPciReg;
    drv->common.readDfx = (HW_READ_REG_FUNC)hwPpPciResetAndInitCtrlReadRegister;
    drv->common.writeDfx = (HW_WRITE_REG_FUNC)hwPpPciResetAndInitCtrlWriteRegister;
	drv->common.writeXsmi = (HW_WRITE_PHY_REG_FUNC)hwPpPciWriteXsmiReg;
	drv->common.readXsmi = (HW_READ_PHY_REG_FUNC)hwPpPciReadXsmiReg;

    drv->baseAddr = hwInfo->baseAddr;
    drv->internalPciBase = hwInfo->internalPciBase;
    drv->resetAndInitControllerBase = hwInfo->resetAndInitControllerBase;

    drv->compIdx            = 2;

    *drvRet = (DRIVER_OBJ_STC*)drv;

    return GT_OK;
}
