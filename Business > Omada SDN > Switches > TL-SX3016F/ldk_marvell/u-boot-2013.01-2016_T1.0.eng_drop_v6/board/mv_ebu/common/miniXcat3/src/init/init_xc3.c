#define _BSD_SOURCE

#include "driver.h"
#include "cpssTypes.h"

DRIVER_OBJ_STC *drv = NULL;


static GT_U32 device[] = {
    PRV_CPSS_XCAT3_8GE_4STACK_PORTS_DEVICES,
    PRV_CPSS_XCAT3_16GE_4STACK_PORTS_DEVICES,
    PRV_CPSS_XCAT3_24GE_2STACK_PORTS_DEVICES,
    PRV_CPSS_XCAT3_24GE_4STACK_PORTS_DEVICES,
    0
};

#include "init_tables.h"

GT_STATUS do_write(const char *t, 
    HW_WRITE_REG_FUNC writePtr,
    INIT_OP_STC *op,
    GT_U32 addrOffset
)
{
    GT_U32 addr = op->p0 + addrOffset;
    GT_U32 value = op->p1;
    /*printf("write %s 0x%08x 0x%08x\n",t,addr,value);*/
    return writePtr(drv,addr,value);
}

GT_STATUS do_write_field(const char *t,
    HW_READ_REG_FUNC readPtr,
    HW_WRITE_REG_FUNC writePtr,
    INIT_OP_STC *op,
    GT_U32 addrOffset
)
{
    GT_U32 regvalue;
    GT_U32 mask;
    GT_U32 addr = op->p0 + addrOffset;
    GT_U32 value = op->p1;
    GT_U32 bitOffs = op->p2;
    GT_U32 bitLen = op->p3;

    readPtr(drv,addr,&regvalue);
    /*printf("read %s 0x%08x 0x%08x\n",t,addr,regvalue);*/
    mask = ~(0xffffffff << bitLen);
    value &= mask;
    regvalue &= ~(mask<<bitOffs);
    regvalue |= value <<bitOffs;
    /*printf("write %s 0x%08x 0x%08x\n",t,addr,regvalue);*/
    return writePtr(drv,addr,regvalue);
}

GT_STATUS do_write_mask(const char *t,
    HW_READ_REG_FUNC readPtr,
    HW_WRITE_REG_FUNC writePtr,
    INIT_OP_STC *op,
    GT_U32 addrOffset
)
{
    GT_U32 regvalue;
    GT_U32 addr = op->p0 + addrOffset;
    GT_U32 value = op->p1;
    GT_U32 mask = op->p2;

    readPtr(drv,addr,&regvalue);
    /*printf("read %s 0x%08x 0x%08x\n",t,addr,regvalue);*/
    value &= mask;
    regvalue &= ~(mask);
    regvalue |= value;
    /*printf("write %s 0x%08x 0x%08x\n",t,addr,regvalue);*/
    return writePtr(drv,addr,regvalue);
}

GT_STATUS do_write_phy(const char *t, HW_WRITE_PHY_REG_FUNC writePhyPtr, INIT_OP_STC *op)
{
    GT_U32 phyAddr = op->p0;
    GT_U32 devAddr = op->p1;
	GT_U16 regAddr = op->p2;
	GT_U16 data = (GT_U16)(op->p3 & 0x0000ffff);
    //printf("write %s phy_addr:0x%08x dev_addr:0x%08x reg_addr:0x%04x val=0x%04x\n",t,phyAddr,devAddr,regAddr,data);
    return writePhyPtr(drv,phyAddr,devAddr,regAddr,data);

}

GT_STATUS do_read_phy(const char *t, HW_READ_PHY_REG_FUNC readPhyPtr, INIT_OP_STC *op)
{
    GT_U32 phyAddr = op->p0;
    GT_U32 devAddr = op->p1;
	GT_U16 regAddr = op->p2;
	GT_U16 data = 0;
	readPhyPtr(drv,phyAddr,devAddr,regAddr,&data);
    printf("read %s phy_addr:0x%08x dev_addr:0x%08x reg_addr:0x%04x data:0x%04x\n",t,phyAddr,devAddr,regAddr,data);
    return GT_OK;
}

GT_STATUS do_init_seq(INIT_OP_STC *seq)
{
    int i;
    int cycle_count = 0;
    int cycle_cur = 0;
    int cycle_start = -1;
    GT_U32 cycle_offset_multiplier = 0;

    GT_U32 delay = 0;
    GT_U32 addrOffset = 0;
    
    for (i = 0; seq[i].op != OP_END; i++)
    {
        switch (seq[i].op)
        {
        	case OP_WR_XSMI:
				do_write_phy("phy_xsmi", drv->writeXsmi, seq+i);
				break;
			case OP_RD_XSMI:
				do_read_phy("phy_xsmi", drv->readXsmi, seq+i);
				break;
            case OP_WR_REG:
                do_write("reg", drv->writeReg, seq+i, addrOffset);
                break;
            case OP_WR_MNG:
                do_write("mng", drv->writeMng, seq+i, addrOffset);
                break;
            case OP_WR_DFX:
                do_write("dfx", drv->writeDfx, seq+i, addrOffset);
                break;
            case OP_WR_F_REG:
                do_write_field("reg", drv->readReg, drv->writeReg, seq+i, addrOffset);
                break;
            case OP_WR_F_MNG:
                do_write_field("mng", drv->readMng, drv->writeMng, seq+i, addrOffset);
                break;
            case OP_WR_F_DFX:
                do_write_field("dfx", drv->readDfx, drv->writeDfx, seq+i, addrOffset);
                break;
            case OP_WR_M_REG:
                do_write_mask("reg", drv->readReg, drv->writeReg, seq+i, addrOffset);
                break;
            case OP_CYCLE_START:
                cycle_start = i;
                cycle_count = seq[i].p0;
                cycle_offset_multiplier = seq[i].p1;
                cycle_cur = 0;
                addrOffset = cycle_cur*cycle_offset_multiplier;
                /*printf("** start cycle count=%d offset=i*0x%x\n",cycle_count,cycle_offset_multiplier);*/
                break;
            case OP_CYCLE_END:
                if (cycle_start >= 0)
                {
                    cycle_cur++;
                    if (cycle_cur < cycle_count)
                    {
                        i = cycle_start;
                        addrOffset = cycle_cur*cycle_offset_multiplier;
                    }
                    else
                    {
                        /*printf("** end cycle\n");*/
                        cycle_start = -1;
                        addrOffset = 0;
                    }
                }
                break;
            case OP_DELAY_START:
                delay = seq[i].p0;
                continue;
            case OP_DELAY_END:
                delay = 0;
                continue;

            case OP_COMMENT:
                printf("%s\n",seq[i].str);
                continue;
            default:
                break;
        }
        if (delay != 0)
        {
            udelay(delay*1000);
        }
    }
    return GT_OK;
}



#include "init_table_hu.h"
#include "init_tables_cpss.h"
#include "common/mvDeviceId.h"

GT_STATUS do_init()
{
    /* Set address completion for backward compatible */
    drv->writeReg(drv,0x140,0x00010000);
    
	#ifdef COMMON_UBOOT
	GT_U32	deviceId = mvCtrlModelGet();
	printf("deviceId %x\r\n", deviceId);
	if (deviceId == MV_ALLEYCAT3_98DX226S_DEV_ID)
	{
		printf("phy_aq_init\r\n");
    	do_init_seq(phy_aq_init);
	}
	else
	{
		printf("phy_1680_init\r\n");
		do_init_seq(phy_1680_init);
	}
	#else
    do_init_seq(init);
    #endif
    printf("done\r\n");
    return 0;
}

GT_STATUS do_serdes_power_down()
{
    /* Set address completion for backward compatible */
    drv->writeReg(drv,0x140,0x00010000);

    do_init_seq(serdesPowerDownSeq);

    printf("SERDES_0 power down done\r\n");
    return 0;
}

GT_STATUS do_soft_reset_seq()
{
    GT_U32 regAddr;
    GT_U32 boardTypeRegValue;
    GT_U32 mgDecodingValue[6*2];/*registers needed for the device for SDMA operations */
    GT_U32 mgDecodingAddress = 0x0000020C;/*registers needed for the device for SDMA operations */
    GT_U32 mgWindowControlValue[6];/*registers needed for the device for SDMA operations */
    GT_U32 mgWindowControlAddress = 0x00000254;/*registers needed for the device for SDMA operations */
    GT_U32 ii;

    /* Set address completion for backward compatible */
    drv->writeReg(drv,0x140,0x00010000);

    /* save User Defined Register 0x7c with AC3 board type */
    drv->readReg(drv,0x7c,&boardTypeRegValue);

    /* SAVE SDMA configurations */
    for(ii = 0 ; ii < 6 ; ii++)
    {
       /* save <MG_IP> MG_IP/MG Registers/Address Decoding/Base Address %n*/
        drv->readReg(drv,mgDecodingAddress + ii*8 + 0,&mgDecodingValue[2*ii + 0]);

        /* save <MG_IP> MG_IP/MG Registers/Address Decoding/Size (S) %n*/
        drv->readReg(drv,mgDecodingAddress + ii*8 + 4,&mgDecodingValue[2*ii + 1]);

        /* save <MG_IP> MG_IP/MG Registers/Address Decoding/Window Control Register%n*/
        drv->readReg(drv,mgWindowControlAddress + ii*4 ,&mgWindowControlValue[ii]);
    }

    do_init_seq(softResetSeq);

    /* restore User Defined Register 0x7c with AC3 board type */
    drv->writeReg(drv,0x7c,boardTypeRegValue);

    /* RESTORE SDMA configurations */
    for(ii = 0 ; ii < 6 ; ii++)
    {
       /* restore <MG_IP> MG_IP/MG Registers/Address Decoding/Base Address %n*/
        drv->writeReg(drv,mgDecodingAddress + ii*8 + 0,mgDecodingValue[2*ii + 0]);

        /* restore <MG_IP> MG_IP/MG Registers/Address Decoding/Size (S) %n*/
        drv->writeReg(drv,mgDecodingAddress + ii*8 + 4,mgDecodingValue[2*ii + 1]);

        /* restore <MG_IP> MG_IP/MG Registers/Address Decoding/Window Control Register%n*/
        drv->writeReg(drv,mgWindowControlAddress + ii*4 ,mgWindowControlValue[ii]);
    }

    /* Implementing WA for table skip init:
         - tables skip init disable cause to CPU stuck, therefore it should be enalbed and
           some common tables should be cleared manually*/

    /* VLAN Table */
    regAddr = 0x03a00000;
    for(ii = 0; ii < (4096 * 8); ii++)
    {
        drv->writeReg(drv, regAddr + ii * 4, 0x0);
    }

    /* FDB Table */
    regAddr = 0x0b400000;
    for(ii = 0; ii < (16384 * 4); ii++)
    {
        drv->writeReg(drv, regAddr + ii * 4, 0x0);
    }

    /* VLAN PORT Private VLAN Edge Table*/
    regAddr = 0x01000000;
    for(ii = 0; ii < 28; ii++)
    {
        drv->writeReg(drv, (regAddr + ii * 0x1000), 0x0);
    }
    /* CPU entry (offset 63) */
    drv->writeReg(drv, (regAddr + 0x3f * 0x1000), 0x0);

    printf("SW reset done\r\n");
    return 0;
}


GT_STATUS do_init1()
{
    printf("init_phase1p1\n");
    do_init_seq(init_phase1p1);
    printf("init_phase1p2\n");
    do_init_seq(init_phase1p2);
    printf("init_phase2\n");
    do_init_seq(init_phase2);
    printf("init_libs\n");
    do_init_seq(init_libs);
    printf("done");
    return 0;
}

GT_32 gtPpFd = -1;

unsigned long str_toul(const char* s)
{
    if (!strncmp(s,"0x",2))
        return simple_strtoul(s+2, NULL, 16);  
    return simple_strtoul(s,NULL, 10);
}
static int read_regs(HW_READ_REG_FUNC func, int argc, char **argv)
{
    GT_U32 addr;
    GT_U32 len = 1;
    GT_U32 i,val;

    addr = str_toul(argv[2]);
    if (argc > 3)
    {
        len = str_toul(argv[3]);
    }
    for (i = 0; i < len; i++, addr+=4)
    {
        if (i % 4 == 0)
        {
            if (i != 0)
                printf("\n");
            printf("  0x%08x: ", addr);
        }
        func(drv, addr, &val);
        printf(" 0x%08x", val);
    }
    printf("\n");
    return 0;
}

static int write_regs(HW_WRITE_REG_FUNC func, int argc, char **argv)
{
    GT_U32 addr;
    GT_U32 val;

    addr = str_toul(argv[2]);
    val = str_toul(argv[3]);

    func(drv,addr,val);
    printf(" WR 0x%08x value 0x%08x\n", addr,val);
    return 0;
}

static int read_xsmi(HW_READ_PHY_REG_FUNC func, int argc, char **argv)
{
	GT_U32 phy_addr, dev_addr;
	GT_U16 reg_addr, val=0;

	phy_addr = str_toul(argv[2]);
	dev_addr = str_toul(argv[3]);
	reg_addr = str_toul(argv[4]);

	func(drv, phy_addr, dev_addr, reg_addr, &val);
	printf("RD value 0x%04x\n",val);
	return 0;
}

static int write_xsmi(HW_WRITE_PHY_REG_FUNC func, int argc, char **argv)
{
	GT_U32 phy_addr, dev_addr;
	GT_U16 reg_addr, val;

    phy_addr = str_toul(argv[2]);
    dev_addr = str_toul(argv[3]);
	reg_addr = str_toul(argv[4]);
	val = str_toul(argv[5]);
	
    func(drv, phy_addr, dev_addr, reg_addr, val);
    printf(" WR value 0x%08x\n",val);
    return 0;
}


/**********************************************************************/


/*******************************************************************************
* mvGenRegisterGet
*
* DESCRIPTION:
*       Read access to device registers.
*
* INPUTS:
*       devNum    - Device Number
*       portGroup - port group (core) number
*       address   - address to access
*
* OUTPUTS:
*       data      - read data
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
static GT_STATUS mvGenRegisterGet
(
	GT_U32			address,
	GT_U32			*data,
	GT_U32			mask
)
{
#ifdef REG_ACCESS_BY_MEMORY_MAP
	*data = GT_MEMIO_LE32_READ(address) & mask;
#elif SMI_INTERFASE_IS_USED
    #error - missing support to access switch registers by SMI
#else
    #error - missing support to access switch registers
#endif
	return GT_OK;
}

/*******************************************************************************
* mvGenRegisterSet
*
* DESCRIPTION:
*       Implement write access to device registers.
*
* INPUTS:
*       address   - address to access
*       data      - data to write
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       0  - on success
*       1  - on error
*
*******************************************************************************/
static GT_STATUS mvGenRegisterSet
(
	GT_U32			address,
	GT_U32			data,
	GT_U32			mask
)
{
	GT_U32 regData;

#ifdef REG_ACCESS_BY_MEMORY_MAP
	if (mask != 0xFFFFFFFF) {
		regData = GT_MEMIO_LE32_READ(address);
		regData = (regData & ~mask) | (data & mask);
	} else
		regData = data;
	GT_MEMIO_LE32_WRITE(address, regData);
#elif SMI_INTERFASE_IS_USED
    #error - missing support to access switch registers by SMI
#else
    #error - missing support to access switch registers
#endif
	return GT_OK;
}



GT_STATUS AllocateCpuMemoryArea()
{
	
    DRV_HW_INFO             hwInfo;
	GT_STATUS rc;

	/* Prepare data to be used by access functions for various SOC regions */

    /***************************************************/
    /* CUSTOMER_NOTICE:
       This function should include the Host CPU configuration to be able to access the PP.

       The avilable interface from the Host CPU to the PP are: Internal mapping, PCIe, I2C or SMI;
       This is the place to configure the Host CPU part to enable these interfaces.

       The below is implementation of CPU A385 as Root Complex and PP-BobK as End Point (PCIe_INTERFASE_IS_USED) or 
        	MSYS internal mapping (MSYS_INTERNAL_CPU_IS_USED).
       
    */

#ifdef  PCIe_INTERFASE_IS_USED 

    hwInfo.baseAddr = PP_SWITCH_REGS_BASE;
    hwInfo.internalPciBase = PP_INTER_REGS_BASE;
    hwInfo.resetAndInitControllerBase = PP_DFX_REGS_BASE;

#endif  /* PCIe_INTERFASE_IS_USED */
	
#ifdef MSYS_INTERNAL_CPU_IS_USED
	
    hwInfo.baseAddr = SWITCH_REGS_BASE;
    hwInfo.internalPciBase = CPU_INTER_REGS_BASE;
    hwInfo.resetAndInitControllerBase = DFX_REGS_BASE;
	
#endif /* MSYS_INTERNAL_CPU_IS_USED */
    
    rc = driverInit(&hwInfo, &drv);
    if (rc != GT_OK)
    {
        printf("Failed initialzie driver rc=%d\n",rc);
        return rc;
    }
    printf("driver initialized\n");
    drv->hwInit(drv);


#ifdef PCIe_INTERFASE_IS_USED
	/* This configuration should be addressed to the MSYS-Internal registers and not to the external CPU */
	/*mvUnitInfoSet(INTERNAL_REG_UNIT,	PP_INTER_REGS_BASE,		MV_INTERNAL_OFFSET);
	mvUnitInfoSet(MG_UNIT,				0,						MV_INTERNAL_OFFSET);
	mvUnitInfoSet(SERDES_UNIT,			MV_SERDES_BASE,			MV_SERDES_OFFSET);*/

    /*1. Need to verify the PCIe mapping from the HOST CPU to the BobK MG is configured correctly*/
    rc = mvGenRegisterSet( INTER_REGS_BASE + 0x20000, 0x07ffe881, 0xFFFFFFFF);
    rc = mvGenRegisterSet( INTER_REGS_BASE + 0x20010, 0x01ffe880, 0xFFFFFFFF);
    rc = mvGenRegisterSet( INTER_REGS_BASE + 0x20020, 0x01ffe880, 0xFFFFFFFF);
    rc = mvGenRegisterSet( INTER_REGS_BASE + 0x20030, 0x01ffe880, 0xFFFFFFFF);
    rc = mvGenRegisterSet( INTER_REGS_BASE + 0x20008, 0xe0000000, 0xFFFFFFFF);


    /* 2. Configuring Bar0 in the Msys of the AC3
       pci write.l 0.0.0 0x10 0xe0000000
       pci write.l 0.0.0 0x14 0x0 */
    pci_write_config_dword(PCI_BDF(0,0,0), 0x10, PP_INTER_REGS_BASE);
    pci_write_config_dword(PCI_BDF(0,0,0), 0x14, 0x00000000);

    /* For SW (0xxxxxxx3x for SW) - Window 0 pcie ctrl reg use Bar1 target 3 (switch)
    mw.l e0041820 03ff0031
    mw.l e0041824 e4000000
    // For DFX (0xxxxxxx8x for DFX) - Window 1 pcie ctrl reg use Bar2 target 8 (DFX)
    mw.l e0041830 007f0083
    mw.l e0041834 e0800000*/
    rc = mvGenRegisterSet( PP_INTER_REGS_BASE + 0x41820, 0x03ff0031, 0xFFFFFFFF);
    rc = mvGenRegisterSet( PP_INTER_REGS_BASE + 0x41824, 0xe4000000, 0xFFFFFFFF);
    rc = mvGenRegisterSet( PP_INTER_REGS_BASE + 0x41830, 0x007f0083, 0xFFFFFFFF);
    rc = mvGenRegisterSet( PP_INTER_REGS_BASE + 0x41834, 0xe0800000, 0xFFFFFFFF);

    /* 3. Set the 64MB allocated base address - as the base address for the RD/WR commands */

    /* Configuring the Bar 1 in the Msys of the AC3.
    pci write.l 0.0.0 0x18 0xe4000000
    pci write.l 0.0.0 0x1c 0x0 */
    pci_write_config_dword(PCI_BDF(0,0,0), 0x18, PP_SWITCH_REGS_BASE);
    pci_write_config_dword(PCI_BDF(0,0,0), 0x1C, 0x00000000);

    /* Configuring the Bar 2 in the Msys of the AC3.
    pci write.l 0.0.0 0x20 0xe0800000
    pci write.l 0.0.0 0x24 0x0 */
    pci_write_config_dword(PCI_BDF(0,0,0), 0x20, PP_DFX_REGS_BASE);
    pci_write_config_dword(PCI_BDF(0,0,0), 0x24, 0x00000000);

    /* 4. Set the legacy mode address completion
        	- mvGenUnitRegisterSet(MG_UNIT, 0, 0x140, (1 << 16), (1 << 16)); */
    /* Set Address Completion legacy mode to "4 addresses" */
    rc = mvGenRegisterSet( PP_SWITCH_REGS_BASE + 0x140, 0x18102, 0xFFFFFFFF);

    /* 5. Check the completion register setting is correct in reference to the Avago Address space in the MG */
    /* Validate from U-Boot command line
        sp
        md f1020000
        PCI space
        md e0040000
        // (Switch space)
        md e4000000
        (DFX space)
        md e08f8240  */

    /* At this stage  -the PP BARs are expected to be configured and mapped correctly to the Host CPU */

#endif  /* PCIe_INTERFASE_IS_USED */
	
#ifdef MSYS_INTERNAL_CPU_IS_USED
    /* 4. Set the legacy mode address completion
        	- mvGenUnitRegisterSet(MG_UNIT, 0, 0x140, (1 << 16), (1 << 16)); */
    /* Set Address Completion legacy mode to "4 addresses" */
    rc = mvGenRegisterSet( SWITCH_REGS_BASE + 0x140, 0x18102, 0xFFFFFFFF);
#endif

	return GT_OK;
}


/**********************************************************************/
/*********   Main function                          *******************/
/**********************************************************************/
int miniXcat3_main(int argc, char **argv)
{
    GT_STATUS ret;
    GT_BOOL first;

	/* Map all registers via PCIe or Memory Map */
	ret = AllocateCpuMemoryArea();
    if (ret != GT_OK)
        
        return ret;

    if (argc > 2 && !strcmp(argv[1],"rdreg"))
        return read_regs(drv->readReg,argc,argv);
    if (argc > 2 && !strcmp(argv[1],"rddfx"))
        return read_regs(drv->readDfx,argc,argv);
    if (argc > 2 && !strcmp(argv[1],"rdmng"))
        return read_regs(drv->readMng,argc,argv);

    if (argc > 3 && !strcmp(argv[1],"wrreg"))
        return write_regs(drv->writeReg,argc,argv);
    if (argc > 3 && !strcmp(argv[1],"wrdfx"))
        return write_regs(drv->writeDfx,argc,argv);
    if (argc > 3 && !strcmp(argv[1],"wrmng"))
        return write_regs(drv->writeMng,argc,argv);

	/*XSMI reg cmd*/
    if (argc > 4 && !strcmp(argv[1],"rdxsmi"))
        return read_xsmi(drv->readXsmi,argc,argv);	
    if (argc > 5 && !strcmp(argv[1],"wrxsmi"))
        return write_xsmi(drv->writeXsmi,argc,argv);	

    if (argc > 1 && (!strcmp(argv[1],"?") || !strcmp(argv[1],"help")))
    {
        printf(
                "Usage:\n"
                "    mini_xcat3 rdreg _addr_ [_count_]\n"
                "    mini_xcat3 rddfx _addr_ [_count_]\n"
                "    mini_xcat3 rdmng _addr_ [_count_]\n"
                "    mini_xcat3 rdxsmi phy_addr dev_addr reg_addr [_count_]\n"
                "    mini_xcat3 wrreg _addr_ _val_\n"
                "    mini_xcat3 wrdfx _addr_ _val_\n"
                "    mini_xcat3 wrmnt _addr_ _val_\n"
                "    mini_xcat3 wrxsmi phy_addr dev_addr reg_addr val\n"
                "    mini_xcat3\n"
                "                (with no params) - write init sequence\n");
        return 0;
    }
    if (argc > 1 && !strcmp(argv[1], "init1"))
        return do_init1();

    if (argc > 1 && !strcmp(argv[1], "serdesPowerDown"))
        return do_serdes_power_down();

    if (argc > 1 && !strcmp(argv[1], "softReset"))
        return do_soft_reset_seq();

    return do_init();
}
