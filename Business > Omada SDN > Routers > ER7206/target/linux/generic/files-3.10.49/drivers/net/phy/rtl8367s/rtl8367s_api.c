#include "rtl8367s_api.h"
#include <linux/switch.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <asm/octeon/cvmx.h>
#include <asm/octeon/cvmx-app-init.h>
#include <asm/octeon/cvmx-smix-defs.h>
#include <asm/octeon/cvmx-gmxx-defs.h>
#include <asm/octeon/cvmx-asxx-defs.h>
#include <asm/octeon/cvmx-mdio.h>

/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/
#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MDC_MDIO_DUMMY_ID           29
#define MDC_MDIO_CTRL0_REG          31
#define MDC_MDIO_CTRL1_REG          21
#define MDC_MDIO_ADDRESS_REG        23
#define MDC_MDIO_DATA_WRITE_REG     24
#define MDC_MDIO_DATA_READ_REG      25
#define MDC_MDIO_START_REG          29
#define MDC_MDIO_PREAMBLE_LEN       32
#define MDC_MDIO_ADDR_OP           0x000E
#define MDC_MDIO_READ_OP           0x0001
#define MDC_MDIO_WRITE_OP          0x0003
#define MDC_MDIO_START_OP          0xFFFF

#define RTK_SCAN_ALL_LOG_PORT(__port__)                     for(__port__ = 0; __port__ < RTK_SWITCH_PORT_NUM; __port__++)  if( rtk_switch_logicalPortCheck(__port__) == RT_ERR_OK)

#define    RTK_SWITCH_PORT_NUM                          (32)
#define    UNDEFINE_PHY_PORT                            (0xFF)
#define    RTL8367C_PORTNO                              11
#define    RTL8367C_PORTIDMAX                           (RTL8367C_PORTNO-1)
#define    RTL8367C_QOS_GRANULARTY_MAX                  0x7FFFF
#define    RTL8367C_QOS_GRANULARTY_LSB_MASK             0xFFFF
#define    RTL8367C_QOS_GRANULARTY_MSB_MASK             0x70000
#define    RTL8367C_QOS_GRANULARTY_MSB_OFFSET           16
#define    RTL8367C_PORT6_EGRESSBW_CTRL1_MASK           0x7
#define    RTL8367C_PORT0_EEECFG_EEEP_ENABLE_TX_OFFSET  14
#define    RTL8367C_PORT0_EEECFG_EEEP_ENABLE_TX_MASK    0x4000
#define    RTL8367C_PORT0_EEECFG_EEEP_ENABLE_RX_OFFSET  13
#define    RTL8367C_PORT0_EEECFG_EEEP_ENABLE_RX_MASK    0x2000
#define    RTL8367C_PORT0_EEECFG_EEE_FORCE_OFFSET       12
#define    RTL8367C_PORT0_EEECFG_EEE_FORCE_MASK         0x1000
#define    RTL8367C_PORT0_EEECFG_EEE_100M_OFFSET        11
#define    RTL8367C_PORT0_EEECFG_EEE_100M_MASK          0x800
#define    RTL8367C_PORT0_EEECFG_EEE_GIGA_500M_OFFSET   10
#define    RTL8367C_PORT0_EEECFG_EEE_GIGA_500M_MASK     0x400
#define    RTL8367C_PORT0_EEECFG_EEE_TX_OFFSET          9
#define    RTL8367C_PORT0_EEECFG_EEE_TX_MASK            0x200
#define    RTL8367C_PORT0_EEECFG_EEE_RX_OFFSET          8
#define    RTL8367C_PORT0_EEECFG_EEE_RX_MASK            0x100
#define    RTL8367C_PORT0_EEECFG_EEE_DSP_RX_OFFSET      6
#define    RTL8367C_PORT0_EEECFG_EEE_DSP_RX_MASK        0x40
#define    RTL8367C_PORT0_EEECFG_EEE_LPI_OFFSET         5
#define    RTL8367C_PORT0_EEECFG_EEE_LPI_MASK           0x20
#define    RTL8367C_PORT0_EEECFG_EEE_TX_LPI_OFFSET      4
#define    RTL8367C_PORT0_EEECFG_EEE_TX_LPI_MASK        0x10
#define    RTL8367C_PORT0_EEECFG_EEE_RX_LPI_OFFSET      3
#define    RTL8367C_PORT0_EEECFG_EEE_RX_LPI_MASK        0x8
#define    RTL8367C_PORT0_EEECFG_EEE_PAUSE_INDICATOR_OFFSET    2
#define    RTL8367C_PORT0_EEECFG_EEE_PAUSE_INDICATOR_MASK    0x4
#define    RTL8367C_PORT0_EEECFG_EEE_WAKE_REQ_OFFSET    1
#define    RTL8367C_PORT0_EEECFG_EEE_WAKE_REQ_MASK      0x2
#define    RTL8367C_PORT0_EEECFG_EEE_SLEEP_REQ_OFFSET   0
#define    RTL8367C_PORT0_EEECFG_EEE_SLEEP_REQ_MASK     0x1

#define    RTL8367C_REGBITLENGTH                        16
#define    RTL8367C_REGDATAMAX                          0xFFFF
#define    RTL8367C_QOS_RATE_INPUT_MAX_HSG              (0x7FFFF * 8)
#define    RTL8367C_INT_EN_OFFSET                       1
#define    RTL8367C_UNKNOWN_UNICAST_DA_BEHAVE_MASK      0xC0
#define    RTL8367C_PHY_BASE                            0x2000
#define    RTL8367C_PHY_OFFSET                          5
#define    RTL8367C_RMAMAX                              0x2F
#define    RTL8367C_QOS_RATE_INPUT_MIN                  8
#define    RTL8367C_QOS_RATE_INPUT_MAX                  (0x1FFFF * 8)
#define    RTL8367C_EXTNO                               3

#define    RTL8367C_REG_PORT0_EEECFG                    0x0018
#define    RTL8367C_REG_UTP_FIB_DET                     0x13eb
#define    RTL8367C_REG_MAX_LENGTH_LIMINT_IPG           0x1200
#define    RTL8367C_MAX_LENTH_CTRL_MASK                 0x6000
#define    RTL8367C_REG_MAX_LEN_RX_TX                   0x0884
#define    RTL8367C_MAX_LEN_RX_TX_MASK                  0x3
#define    RTL8367C_REG_ACL_ACCESS_MODE                 0x06EB
#define    RTL8367C_ACL_ACCESS_MODE_MASK                0x1
#define    RTL8367C_REG_PORT_SECURITY_CTRL              0x08c8
#define    RTL8367C_PORT_SECURIT_CTRL_REG               RTL8367C_REG_PORT_SECURITY_CTRL
#define    RTL8367C_REG_IO_MISC_FUNC                    0x1d32
#define    RTL8367C_CFG_CPU_OCPADR_MSB_MASK             0xFC0
#define    RTL8367C_REG_GPHY_OCP_MSB_0                  0x1d15
#define    RTL8367C_REG_LUT_CFG                         0x0a30
#define    RTL8367C_LUT_IPMC_LOOKUP_OP_OFFSET           3
#define    RTL8367C_REG_RMA_CTRL00                      0x0800
#define    RTL8367C_TRAP_PRIORITY_MASK                  0x38
#define    RTL8367C_REG_MIRROR_CTRL2                    0x09DA
#define    RTL8367C_MIRROR_TX_ISOLATION_LEAKY_OFFSET    2
#define    RTL8367C_REG_SCHEDULE_WFQ_CTRL               0x0300
#define    RTL8367C_SCHEDULE_WFQ_CTRL_OFFSET            0
#define    RTL8367C_INGRESSBW_PORT0_RATE_CTRL1_INGRESSBW_RATE16_MASK    0x7
#define    RTL8367C_PORT0_MISC_CFG_INGRESSBW_IFG_OFFSET         10
#define    RTL8367C_PORT0_MISC_CFG_INGRESSBW_FLOWCTRL_OFFSET    11
#define    RTL8367C_REG_INGRESSBW_PORT0_RATE_CTRL0              0x000f
#define    RTL8367C_INGRESSBW_PORT_RATE_LSB_BASE                RTL8367C_REG_INGRESSBW_PORT0_RATE_CTRL0
#define    RTL8367C_INGRESSBW_PORT_RATE_LSB_REG(port)           (RTL8367C_INGRESSBW_PORT_RATE_LSB_BASE + (port << 5))
#define    RTL8367C_REG_PORT0_MISC_CFG                          0x000e
#define    RTL8367C_PORT_MISC_CFG_BASE                          RTL8367C_REG_PORT0_MISC_CFG
#define    RTL8367C_PORT_MISC_CFG_REG(port)                     (RTL8367C_PORT_MISC_CFG_BASE + (port << 5))
#define    RTL8367C_REG_PORT0_EGRESSBW_CTRL1                    0x038d
#define    RTL8367C_PORT_EGRESSBW_MSB_BASE                      RTL8367C_REG_PORT0_EGRESSBW_CTRL1
#define    RTL8367C_PORT_EGRESSBW_MSB_REG(port)                 (RTL8367C_PORT_EGRESSBW_MSB_BASE + (port << 1))
#define    RTL8367C_REG_PORT0_EGRESSBW_CTRL0                    0x038c
#define    RTL8367C_PORT_EGRESSBW_LSB_BASE                      RTL8367C_REG_PORT0_EGRESSBW_CTRL0
#define    RTL8367C_PORT_EGRESSBW_LSB_REG(port)                 (RTL8367C_PORT_EGRESSBW_LSB_BASE + (port << 1))
#define    RTL8367C_REG_SDS_INDACS_DATA                 0x6602
#define    RTL8367C_REG_SDS_INDACS_ADR                  0x6601
#define    RTL8367C_REG_SDS_INDACS_CMD                  0x6600
#define    RTL8367C_REG_SDS_MISC                        0x1d11
#define    RTL8367C_CFG_MAC8_SEL_SGMII_OFFSET           6
#define    RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET          11
#define    RTL8367C_REG_DIGITAL_INTERFACE_SELECT        0x1305
#define    RTL8367C_SELECT_GMII_0_MASK                  0xF
#define    RTL8367C_SELECT_GMII_1_OFFSET                4
#define    RTL8367C_REG_EXT0_RGMXF                      0x1306
#define    RTL8367C_EXT0_RGTX_INV_OFFSET                6
#define    RTL8367C_EXT0_RGTX_INV_MASK                  0x40
#define    RTL8367C_EXT0_RGRX_INV_OFFSET                5
#define    RTL8367C_EXT0_RGRX_INV_MASK                  0x20
#define    RTL8367C_EXT0_RGMXF_OFFSET                   0
#define    RTL8367C_EXT0_RGMXF_MASK                     0x1F
#define    RTL8367C_EXT1_RGTX_INV_OFFSET                6
#define    RTL8367C_REG_EXT_TXC_DLY                     0x13f9
#define    RTL8367C_EXT1_GMII_TX_DELAY_MASK             0x7000
#define    RTL8367C_EXT0_GMII_TX_DELAY_MASK             0xE00
#define    RTL8367C_REG_BYPASS_LINE_RATE                0x03f7
#define    RTL8367C_REG_DIGITAL_INTERFACE_SELECT_1      0x13c3
#define    RTL8367C_SELECT_GMII_2_MASK                  0xF
#define    RTL8367C_CFG_SGMII_FDUP_OFFSET               10
#define    RTL8367C_CFG_SGMII_SPD_MASK                  0x180
#define    RTL8367C_CFG_SGMII_LINK_OFFSET               9
#define    RTL8367C_CFG_SGMII_TXFC_OFFSET               13
#define    RTL8367C_CFG_SGMII_RXFC_OFFSET               14
#define    RTL8367C_REG_DIGITAL_INTERFACE0_FORCE        0x1310
#define    RTL8367C_REG_DIGITAL_INTERFACE2_FORCE        0x13c4
#define    RTL8367C_REG_EXT1_RGMXF                      0x1307
#define    RTL8367C_REG_EXT2_RGMXF                      0x13c5

#define    RTL8367C_PHY_REGNOMAX                        0x1F

#define    RTL8367C_PORT10_RESET_OFFSET    15
#define    RTL8367C_PORT10_RESET_MASK    0x8000
#define    RTL8367C_PORT9_RESET_OFFSET    14
#define    RTL8367C_PORT9_RESET_MASK    0x4000
#define    RTL8367C_PORT8_RESET_OFFSET    13
#define    RTL8367C_PORT8_RESET_MASK    0x2000
#define    RTL8367C_RESET_VALUE_OFFSET    12
#define    RTL8367C_RESET_VALUE_MASK    0x1000
#define    RTL8367C_GLOBAL_RESET_OFFSET    11
#define    RTL8367C_GLOBAL_RESET_MASK    0x800
#define    RTL8367C_QM_RESET_OFFSET    10
#define    RTL8367C_QM_RESET_MASK    0x400
#define    RTL8367C_PORT7_RESET_OFFSET    9
#define    RTL8367C_PORT7_RESET_MASK    0x200
#define    RTL8367C_PORT6_RESET_OFFSET    8
#define    RTL8367C_PORT6_RESET_MASK    0x100
#define    RTL8367C_PORT5_RESET_OFFSET    7
#define    RTL8367C_PORT5_RESET_MASK    0x80
#define    RTL8367C_PORT4_RESET_OFFSET    6
#define    RTL8367C_PORT4_RESET_MASK    0x40
#define    RTL8367C_PORT3_RESET_OFFSET    5
#define    RTL8367C_PORT3_RESET_MASK    0x20
#define    RTL8367C_PORT2_RESET_OFFSET    4
#define    RTL8367C_PORT2_RESET_MASK    0x10
#define    RTL8367C_PORT1_RESET_OFFSET    3
#define    RTL8367C_PORT1_RESET_MASK    0x8
#define    RTL8367C_PORT0_RESET_OFFSET    2
#define    RTL8367C_PORT0_RESET_MASK    0x4
#define    RTL8367C_RESET_FLAG_OFFSET    1
#define    RTL8367C_MIB_CTRL0_BUSY_FLAG_OFFSET    0
#define    RTL8367C_MIB_PORT07_MASK                                (0xFF<<RTL8367C_PORT0_RESET_OFFSET)

#define    RTL8367C_REG_MIRROR_CTRL    0x121c
#define    RTL8367C_MIRROR_CTRL_DUMMY_OFFSET    12
#define    RTL8367C_MIRROR_CTRL_DUMMY_MASK    0xF000
#define    RTL8367C_MIRROR_ISO_OFFSET    11
#define    RTL8367C_MIRROR_ISO_MASK    0x800
#define    RTL8367C_MIRROR_TX_OFFSET    10
#define    RTL8367C_MIRROR_TX_MASK    0x400
#define    RTL8367C_MIRROR_RX_OFFSET    9
#define    RTL8367C_MIRROR_RX_MASK    0x200
#define    RTL8367C_MIRROR_MONITOR_PORT_OFFSET    4
#define    RTL8367C_MIRROR_MONITOR_PORT_MASK    0xF0
#define    RTL8367C_MIRROR_SOURCE_PORT_OFFSET    0
#define    RTL8367C_MIRROR_SOURCE_PORT_MASK    0xF
#define    RTL8367C_MIRROR_CTRL_REG                                RTL8367C_REG_MIRROR_CTRL

#define    RTL8367C_REG_MIRROR_SRC_PMSK    0x12fb
#define    RTL8367C_MIRROR_SRC_PMSK_OFFSET    0
#define    RTL8367C_MIRROR_SRC_PMSK_MASK    0x7FF

#define    RTL8367C_LEDGROUPNO                  3
#define    RTL8367C_LEDGROUPMASK               0x7
#define    RTL8367C_REG_CPU_FORCE_LED0_CFG0    0x1b08
#define    RTL8367C_REG_CPU_FORCE_LED0_CFG1    0x1b09
#define    RTL8367C_REG_CPU_FORCE_LED1_CFG0    0x1b0a
#define    RTL8367C_REG_CPU_FORCE_LED1_CFG1    0x1b0b
#define    RTL8367C_REG_CPU_FORCE_LED2_CFG0    0x1b0c
#define    RTL8367C_REG_CPU_FORCE_LED2_CFG1    0x1b0d
#define    RTL8367C_LED_FORCE_MODE_BASE        RTL8367C_REG_CPU_FORCE_LED0_CFG0
#define    RTL8367C_LED_FORCE_CTRL             RTL8367C_REG_CPU_FORCE_LED_CFG
#define    RTL8367C_REG_PARA_LED_IO_EN1    0x1b24
#define    RTL8367C_LED1_PARA_P07_00_OFFSET    8
#define    RTL8367C_LED1_PARA_P07_00_MASK    0xFF00
#define    RTL8367C_LED0_PARA_P07_00_OFFSET    0
#define    RTL8367C_LED0_PARA_P07_00_MASK    0xFF

#define    RTL8367C_REG_PARA_LED_IO_EN2    0x1b25
#define    RTL8367C_DUMMY_15_8_OFFSET    8
#define    RTL8367C_DUMMY_15_8_MASK    0xFF00
#define    RTL8367C_LED2_PARA_P07_00_OFFSET    0
#define    RTL8367C_LED2_PARA_P07_00_MASK    0xFF

#define    RTL8367C_REG_PARA_LED_IO_EN3    0x1b33
#define    RTL8367C_dummy_1b33a_OFFSET    6
#define    RTL8367C_dummy_1b33a_MASK    0xFFC0
#define    RTL8367C_LED2_PARA_P09_08_OFFSET    4
#define    RTL8367C_LED2_PARA_P09_08_MASK    0x30
#define    RTL8367C_LED1_PARA_P09_08_OFFSET    2
#define    RTL8367C_LED1_PARA_P09_08_MASK    0xC
#define    RTL8367C_LED0_PARA_P09_08_OFFSET    0
#define    RTL8367C_LED0_PARA_P09_08_MASK    0x3

#define    RTL8367C_REG_LED_SYS_CONFIG    0x1b00
#define    RTL8367C_LED_SYS_CONFIG_DUMMY_15_OFFSET    15
#define    RTL8367C_LED_SYS_CONFIG_DUMMY_15_MASK    0x8000
#define    RTL8367C_LED_SERIAL_OUT_MODE_OFFSET    14
#define    RTL8367C_LED_SERIAL_OUT_MODE_MASK    0x4000
#define    RTL8367C_LED_EEE_LPI_MODE_OFFSET    13
#define    RTL8367C_LED_EEE_LPI_MODE_MASK    0x2000
#define    RTL8367C_LED_EEE_LPI_EN_OFFSET    12
#define    RTL8367C_LED_EEE_LPI_EN_MASK    0x1000
#define    RTL8367C_LED_EEE_LPI_10_OFFSET    11
#define    RTL8367C_LED_EEE_LPI_10_MASK    0x800
#define    RTL8367C_LED_EEE_CAP_10_OFFSET    10
#define    RTL8367C_LED_EEE_CAP_10_MASK    0x400
#define    RTL8367C_LED_LPI_SEL_OFFSET    8
#define    RTL8367C_LED_LPI_SEL_MASK    0x300
#define    RTL8367C_SERI_LED_ACT_LOW_OFFSET    7
#define    RTL8367C_SERI_LED_ACT_LOW_MASK    0x80
#define    RTL8367C_LED_POWERON_2_OFFSET    6
#define    RTL8367C_LED_POWERON_2_MASK    0x40
#define    RTL8367C_LED_POWERON_1_OFFSET    5
#define    RTL8367C_LED_POWERON_1_MASK    0x20
#define    RTL8367C_LED_POWERON_0_OFFSET    4
#define    RTL8367C_LED_POWERON_0_MASK    0x10
#define    RTL8367C_LED_IO_DISABLE_OFFSET    3
#define    RTL8367C_LED_IO_DISABLE_MASK    0x8
#define    RTL8367C_DUMMY_2_2_OFFSET    2
#define    RTL8367C_DUMMY_2_2_MASK    0x4
#define    RTL8367C_LED_SELECT_OFFSET    0
#define    RTL8367C_LED_SELECT_MASK    0x3

#define    RTL8367C_REG_SCAN0_LED_IO_EN1    0x1b26
#define    RTL8367C_SCAN0_LED_IO_EN1_DUMMY_OFFSET    3
#define    RTL8367C_SCAN0_LED_IO_EN1_DUMMY_MASK    0xFFF8
#define    RTL8367C_LED_LOOP_DET_BUZZER_EN_OFFSET    2
#define    RTL8367C_LED_LOOP_DET_BUZZER_EN_MASK    0x4
#define    RTL8367C_LED_SERI_DATA_EN_OFFSET    1
#define    RTL8367C_LED_SERI_DATA_EN_MASK    0x2
#define    RTL8367C_LED_SERI_CLK_EN_OFFSET    0
#define    RTL8367C_LED_SERI_CLK_EN_MASK    0x1

#define    RTL8367C_REG_LED_MODE    0x1b02
#define    RTL8367C_DLINK_TIME_OFFSET    15
#define    RTL8367C_DLINK_TIME_MASK    0x8000
#define    RTL8367C_LED_BUZZ_DUTY_OFFSET    14
#define    RTL8367C_LED_BUZZ_DUTY_MASK    0x4000
#define    RTL8367C_BUZZER_RATE_OFFSET    12
#define    RTL8367C_BUZZER_RATE_MASK    0x3000
#define    RTL8367C_LOOP_DETECT_MODE_OFFSET    11
#define    RTL8367C_LOOP_DETECT_MODE_MASK    0x800
#define    RTL8367C_SEL_PWRON_TIME_OFFSET    9
#define    RTL8367C_SEL_PWRON_TIME_MASK    0x600
#define    RTL8367C_EN_DLINK_LED_OFFSET    8
#define    RTL8367C_EN_DLINK_LED_MASK    0x100
#define    RTL8367C_LOOP_DETECT_RATE_OFFSET    6
#define    RTL8367C_LOOP_DETECT_RATE_MASK    0xC0
#define    RTL8367C_FORCE_RATE_OFFSET    4
#define    RTL8367C_FORCE_RATE_MASK    0x30
#define    RTL8367C_SEL_LEDRATE_OFFSET    1
#define    RTL8367C_SEL_LEDRATE_MASK    0xE
#define    RTL8367C_SPEED_UP_OFFSET    0
#define    RTL8367C_SPEED_UP_MASK    0x1

#define    RTL8367C_REG_LED_CONFIGURATION    0x1b03
#define    RTL8367C_LED_CONFIGURATION_DUMMY_OFFSET    15
#define    RTL8367C_LED_CONFIGURATION_DUMMY_MASK    0x8000
#define    RTL8367C_LED_CONFIG_SEL_OFFSET    14
#define    RTL8367C_LED_CONFIG_SEL_MASK    0x4000
#define    RTL8367C_DATA_LED_OFFSET    12
#define    RTL8367C_DATA_LED_MASK    0x3000
#define    RTL8367C_LED2_CFG_OFFSET    8
#define    RTL8367C_LED2_CFG_MASK    0xF00
#define    RTL8367C_LED1_CFG_OFFSET    4
#define    RTL8367C_LED1_CFG_MASK    0xF0
#define    RTL8367C_LED0_CFG_OFFSET    0
#define    RTL8367C_LED0_CFG_MASK    0xF

#if defined(FORCE_PROBE_RTL8367C)
static init_state_t    init_state = INIT_COMPLETED;
#elif defined(FORCE_PROBE_RTL8370B)
static init_state_t    init_state = INIT_COMPLETED;
#else
static init_state_t    init_state = INIT_COMPLETED;
#endif
/**************************************************************************************************/
/*                                           TYPES                                                */
/**************************************************************************************************/


typedef struct  rtl8367c_rma_s{

#ifdef _LITTLE_ENDIAN
    rtk_uint16 portiso_leaky:1;
    rtk_uint16 vlan_leaky:1;
    rtk_uint16 keep_format:1;
    rtk_uint16 trap_priority:3;
    rtk_uint16 discard_storm_filter:1;
    rtk_uint16 operation:2;
    rtk_uint16 reserved:7;
#else
    rtk_uint16 reserved:7;
    rtk_uint16 operation:2;
    rtk_uint16 discard_storm_filter:1;
    rtk_uint16 trap_priority:3;
    rtk_uint16 keep_format:1;
    rtk_uint16 vlan_leaky:1;
    rtk_uint16 portiso_leaky:1;
#endif

}rtl8367c_rma_t;

typedef struct  rtl8367c_port_ability_s{
#ifdef _LITTLE_ENDIAN
    rtk_uint16 speed:2;
    rtk_uint16 duplex:1;
    rtk_uint16 reserve1:1;
    rtk_uint16 link:1;
    rtk_uint16 rxpause:1;
    rtk_uint16 txpause:1;
    rtk_uint16 nway:1;
    rtk_uint16 mstmode:1;
    rtk_uint16 mstfault:1;
    rtk_uint16 reserve2:2;
    rtk_uint16 forcemode:1;
    rtk_uint16 reserve3:3;
#else
    rtk_uint16 reserve3:3;
    rtk_uint16 forcemode:1;
    rtk_uint16 reserve2:2;
    rtk_uint16 mstfault:1;
    rtk_uint16 mstmode:1;
    rtk_uint16 nway:1;
    rtk_uint16 txpause:1;
    rtk_uint16 rxpause:1;
    rtk_uint16 link:1;
    rtk_uint16 reserve1:1;
    rtk_uint16 duplex:1;
    rtk_uint16 speed:2;

#endif
}rtl8367c_port_ability_t;

enum EXTMODE
{
    EXT_DISABLE = 0,
    EXT_RGMII,
    EXT_MII_MAC,
    EXT_MII_PHY,
    EXT_TMII_MAC,
    EXT_TMII_PHY,
    EXT_GMII,
    EXT_RMII_MAC,
    EXT_RMII_PHY,
    EXT_SGMII,
    EXT_HSGMII,
    EXT_END
};

typedef enum switch_chip_e
{
    CHIP_RTL8367C = 0,
    CHIP_RTL8370B,
    CHIP_END
}switch_chip_t;

typedef enum port_type_e
{
    UTP_PORT = 0,
    EXT_PORT,
    UNKNOWN_PORT = 0xFF,
    PORT_TYPE_END
}port_type_t;

typedef struct rtk_switch_halCtrl_s
{
    switch_chip_t   switch_type;
    rtk_uint32      l2p_port[RTK_SWITCH_PORT_NUM];
    rtk_uint32      p2l_port[RTK_SWITCH_PORT_NUM];
    port_type_t     log_port_type[RTK_SWITCH_PORT_NUM];
    rtk_uint32      ptp_port[RTK_SWITCH_PORT_NUM];
    rtk_uint32      valid_portmask;
    rtk_uint32      valid_utp_portmask;
    rtk_uint32      valid_ext_portmask;
    rtk_uint32      min_phy_port;
    rtk_uint32      max_phy_port;
    rtk_uint32      phy_portmask;
    rtk_uint32      combo_logical_port;
    rtk_uint32      hsg_logical_port;
    rtk_uint32      max_meter_id;
    rtk_uint32      max_lut_addr_num;
    rtk_uint32      max_trunk_id;

}rtk_switch_halCtrl_t;

enum RTL8367C_LEDOP{

    LEDOP_SCAN0=0,
    LEDOP_SCAN1,
    LEDOP_PARALLEL,
    LEDOP_SERIAL,
    LEDOP_END,
};

enum RTL8367C_LEDBLINKRATE{

    LEDBLINKRATE_32MS=0,
    LEDBLINKRATE_64MS,
    LEDBLINKRATE_128MS,
    LEDBLINKRATE_256MS,
    LEDBLINKRATE_512MS,
    LEDBLINKRATE_1024MS,
    LEDBLINKRATE_48MS,
    LEDBLINKRATE_96MS,
    LEDBLINKRATE_END,
};

enum RTL8367C_LEDCONF{

    LEDCONF_LEDOFF=0,
    LEDCONF_DUPCOL,
    LEDCONF_LINK_ACT,
    LEDCONF_SPD1000,
    LEDCONF_SPD100,
    LEDCONF_SPD10,
    LEDCONF_SPD1000ACT,
    LEDCONF_SPD100ACT,
    LEDCONF_SPD10ACT,
    LEDCONF_SPD10010ACT,
    LEDCONF_LOOPDETECT,
    LEDCONF_EEE,
    LEDCONF_LINKRX,
    LEDCONF_LINKTX,
    LEDCONF_MASTER,
    LEDCONF_ACT,
    LEDCONF_END
};

enum RTL8367C_LEDFORCEMODE{

    LEDFORCEMODE_NORMAL=0,
    LEDFORCEMODE_BLINK,
    LEDFORCEMODE_OFF,
    LEDFORCEMODE_ON,
    LEDFORCEMODE_END,
};

static rtk_switch_halCtrl_t halCtrl =
{
    /* Switch Chip */
    CHIP_RTL8367C,

    /* Logical to Physical */
    {0, 1, 2,    3,       4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     6, 7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },

    /* Physical to Logical */
    {UTP_PORT0, UTP_PORT1, UTP_PORT2, UTP_PORT3, UTP_PORT4, UNDEFINE_PORT, EXT_PORT0, EXT_PORT1,
     UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT,
     UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT,
     UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT, UNDEFINE_PORT},

    /* Port Type */
    {UTP_PORT, UTP_PORT, UTP_PORT, UTP_PORT, UTP_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT,
     UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT,
     EXT_PORT, EXT_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT,
     UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT, UNKNOWN_PORT},

    /* PTP port */
    {1, 1, 1, 1, 1, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0 },

    /* Valid port mask */
    ( (0x1 << UTP_PORT0) | (0x1 << UTP_PORT1) | (0x1 << UTP_PORT2) | (0x1 << UTP_PORT3) | (0x1 << UTP_PORT4) | (0x1 << EXT_PORT0) | (0x1 << EXT_PORT1) ),

    /* Valid UTP port mask */
    ( (0x1 << UTP_PORT0) | (0x1 << UTP_PORT1) | (0x1 << UTP_PORT2) | (0x1 << UTP_PORT3) | (0x1 << UTP_PORT4) ),

    /* Valid EXT port mask */
    ( (0x1 << EXT_PORT0) | (0x1 << EXT_PORT1) ),

    /* Minimum physical port number */
    0,

    /* Maxmum physical port number */
    7,

    /* Physical port mask */
    0xDF,

    /* Combo Logical port ID */
    4,

    /* HSG Logical port ID */
    EXT_PORT0,

    /* Max Meter ID */
    31,

    /* MAX LUT Address Number */
    2112,

    /* MAX TRUNK ID */
    1
};

/**************************************************************************************************/
/*                                           FUNCTIONS                                            */
/**************************************************************************************************/

void MDC_MDIO_READ(uint32_t preamble_len, int32_t phy_id, int32_t register_id, uint32_t *pdata);
void MDC_MDIO_WRITE(uint32_t preamble_len, int32_t phy_id, int32_t register_id, uint16_t data);

static struct mutex mdio_switch_lock = __MUTEX_INITIALIZER(mdio_switch_lock);

static s32 rtl_smi_read(u32 mAddrs, u32 *rData)
{
     mutex_lock(&mdio_switch_lock);
    /* Write address control code to register 31 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL0_REG, MDC_MDIO_ADDR_OP);

    /* Write address to register 23 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_ADDRESS_REG, mAddrs);

    /* Write read control code to register 21 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL1_REG, MDC_MDIO_READ_OP);

    /* Read data from register 25 */
    MDC_MDIO_READ(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_DATA_READ_REG, rData);

    mutex_unlock(&mdio_switch_lock);
    return RT_ERR_OK;
}

static s32 rtl_smi_write(u32 mAddrs, u32 rData)
{
    mutex_lock(&mdio_switch_lock);
    /* Write address control code to register 31 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL0_REG, MDC_MDIO_ADDR_OP);

    /* Write address to register 23 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_ADDRESS_REG, mAddrs);

    /* Write data to register 24 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_DATA_WRITE_REG, rData);

    /* Write data control code to register 21 */
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL1_REG, MDC_MDIO_WRITE_OP);

    mutex_unlock(&mdio_switch_lock);
    return RT_ERR_OK;
}

rtk_int32 smi_read(rtk_uint32 mAddrs, rtk_uint32 *rData)
{
	return rtl_smi_read(mAddrs, rData);
}

rtk_int32 smi_write(rtk_uint32 mAddrs, rtk_uint32 rData)
{
	return rtl_smi_write(mAddrs, rData);
}
/* Function Name:
 *      rtl8367c_setAsicRegBit
 * Description:
 *      Set a bit value of a specified register
 * Input:
 *      reg     - register's address
 *      bit     - bit location
 *      value   - value to set. It can be value 0 or 1.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      Set a bit of a specified register to 1 or 0.
 */
ret_t rtl8367c_setAsicRegBit(rtk_uint32 reg, rtk_uint32 bit, rtk_uint32 value)
{
    rtk_uint32 regData;
    ret_t retVal;

    if(bit >= RTL8367C_REGBITLENGTH)
        return RT_ERR_INPUT;

    retVal = rtl_smi_read(reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    if(value)
        regData = regData | (1 << bit);
    else
        regData = regData & (~(1 << bit));

    retVal = rtl_smi_write(reg, regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicRegBits
 * Description:
 *      Get bits value of a specified register
 * Input:
 *      reg     - register's address
 *      bits    - bits mask for setting
 *      value   - bits value for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicRegBits(rtk_uint32 reg, rtk_uint32 bits, rtk_uint32 *pValue)
{
    rtk_uint32 regData;
    ret_t retVal;
    rtk_uint32 bitsShift;

    if(bits>= (1<<RTL8367C_REGBITLENGTH) )
        return RT_ERR_INPUT;

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367C_REGBITLENGTH)
            return RT_ERR_INPUT;
    }

    retVal = rtl_smi_read(reg, &regData);
    if(retVal != RT_ERR_OK) return RT_ERR_SMI;

    *pValue = (regData & bits) >> bitsShift;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicRegBit
 * Description:
 *      Get a bit value of a specified register
 * Input:
 *      reg     - register's address
 *      bit     - bit location
 *      value   - value to get.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicRegBit(rtk_uint32 reg, rtk_uint32 bit, rtk_uint32 *pValue)
{
    rtk_uint32 regData;
    ret_t retVal;

    retVal = rtl_smi_read(reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    *pValue = (regData & (0x1 << bit)) >> bit;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicRegBits
 * Description:
 *      Set bits value of a specified register
 * Input:
 *      reg     - register's address
 *      bits    - bits mask for setting
 *      value   - bits value for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      Set bits of a specified register to value. Both bits and value are be treated as bit-mask
 */
ret_t rtl8367c_setAsicRegBits(rtk_uint32 reg, rtk_uint32 bits, rtk_uint32 value)
{
    rtk_uint32 regData;
    ret_t retVal;
    rtk_uint32 bitsShift;
    rtk_uint32 valueShifted;

    if(bits >= (1 << RTL8367C_REGBITLENGTH) )
        return RT_ERR_INPUT;

    bitsShift = 0;
    while(!(bits & (1 << bitsShift)))
    {
        bitsShift++;
        if(bitsShift >= RTL8367C_REGBITLENGTH)
            return RT_ERR_INPUT;
    }
    valueShifted = value << bitsShift;

    if(valueShifted > RTL8367C_REGDATAMAX)
        return RT_ERR_INPUT;

    retVal = rtl_smi_read(reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    regData = regData & (~bits);
    regData = regData | (valueShifted & bits);

    retVal = rtl_smi_write(reg, regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicReg
 * Description:
 *      Set content of asic register
 * Input:
 *      reg     - register's address
 *      value   - Value setting to register
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      The value will be set to ASIC mapping address only and it is always return RT_ERR_OK while setting un-mapping address registers
 */
ret_t rtl8367c_setAsicReg(rtk_uint32 reg, rtk_uint32 value)
{
    ret_t retVal;

    retVal = rtl_smi_write(reg, value);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    return RT_ERR_OK;
}

ret_t rtk_switch_setReg(rtk_uint32 reg, rtk_uint32 value)
{
    return rtl8367c_setAsicReg(reg, value);
}

/* Function Name:
 *      rtl8367c_getAsicReg
 * Description:
 *      Get content of asic register
 * Input:
 *      reg     - register's address
 *      value   - Value setting to register
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      Value 0x0000 will be returned for ASIC un-mapping address
 */
ret_t rtl8367c_getAsicReg(rtk_uint32 reg, rtk_uint32 *pValue)
{
    rtk_uint32 regData;
    ret_t retVal;

    retVal = rtl_smi_read(reg, &regData);
    if(retVal != RT_ERR_OK)
        return RT_ERR_SMI;

    *pValue = regData;

    return RT_ERR_OK;
}

ret_t rtk_switch_getReg(rtk_uint32 reg, rtk_uint32 *pValue)
{
    return rtl8367c_getAsicReg(reg, pValue);
}

/* Function Name:
 *      rtl8367c_setAsicPHYOCPReg
 * Description:
 *      Set PHY OCP registers
 * Input:
 *      phyNo   - Physical port number (0~7)
 *      ocpAddr - OCP address
 *      ocpData - Writing data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PHY_REG_ID       - invalid PHY address
 *      RT_ERR_PHY_ID           - invalid PHY no
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPHYOCPReg(rtk_uint32 phyNo, rtk_uint32 ocpAddr, rtk_uint32 ocpData )
{
    ret_t retVal;
    rtk_uint32 regAddr;
    rtk_uint32 ocpAddrPrefix, ocpAddr9_6, ocpAddr5_1;

    /* OCP prefix */
    ocpAddrPrefix = ((ocpAddr & 0xFC00) >> 10);
    if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_GPHY_OCP_MSB_0, RTL8367C_CFG_CPU_OCPADR_MSB_MASK, ocpAddrPrefix)) != RT_ERR_OK)
        return retVal;

    /*prepare access address*/
    ocpAddr9_6 = ((ocpAddr >> 6) & 0x000F);
    ocpAddr5_1 = ((ocpAddr >> 1) & 0x001F);
    regAddr = RTL8367C_PHY_BASE | (ocpAddr9_6 << 8) | (phyNo << RTL8367C_PHY_OFFSET) | ocpAddr5_1;
    if((retVal = rtl8367c_setAsicReg(regAddr, ocpData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicPHYOCPReg
 * Description:
 *      Get PHY OCP registers
 * Input:
 *      phyNo   - Physical port number (0~7)
 *      ocpAddr - PHY address
 *      pRegData - read data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PHY_REG_ID       - invalid PHY address
 *      RT_ERR_PHY_ID           - invalid PHY no
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPHYOCPReg(rtk_uint32 phyNo, rtk_uint32 ocpAddr, rtk_uint32 *pRegData )
{
    ret_t retVal;
    rtk_uint32 regAddr;
    rtk_uint32 ocpAddrPrefix, ocpAddr9_6, ocpAddr5_1;

    /* OCP prefix */
    ocpAddrPrefix = ((ocpAddr & 0xFC00) >> 10);
    if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_GPHY_OCP_MSB_0, RTL8367C_CFG_CPU_OCPADR_MSB_MASK, ocpAddrPrefix)) != RT_ERR_OK)
        return retVal;

    /*prepare access address*/
    ocpAddr9_6 = ((ocpAddr >> 6) & 0x000F);
    ocpAddr5_1 = ((ocpAddr >> 1) & 0x001F);
    regAddr = RTL8367C_PHY_BASE | (ocpAddr9_6 << 8) | (phyNo << RTL8367C_PHY_OFFSET) | ocpAddr5_1;
    if((retVal = rtl8367c_getAsicReg(regAddr, pRegData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicPHYReg
 * Description:
 *      Set PHY registers
 * Input:
 *      phyNo   - Physical port number (0~7)
 *      phyAddr - PHY address (0~31)
 *      phyData - Writing data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PHY_REG_ID       - invalid PHY address
 *      RT_ERR_PHY_ID           - invalid PHY no
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      None
 */
static ret_t 
rtl8367c_setAsicPHYReg(rtk_uint32 phyNo, rtk_uint32 phyAddr, rtk_uint32 phyData )
{
    rtk_uint32 ocp_addr;

    if(phyAddr > RTL8367C_PHY_REGNOMAX)
        return RT_ERR_PHY_REG_ID;

    ocp_addr = 0xa400 + phyAddr*2;

    return rtl8367c_setAsicPHYOCPReg(phyNo, ocp_addr, phyData);
}

ret_t rtk_switch_setPHYReg(rtk_uint32 phyNo, rtk_uint32 phyAddr, rtk_uint32 phyData)
{
    return rtl8367c_setAsicPHYReg(phyNo, phyAddr, phyData);
}

/* Function Name:
 *      rtl8367c_getAsicPHYReg
 * Description:
 *      Get PHY registers
 * Input:
 *      phyNo   - Physical port number (0~7)
 *      phyAddr - PHY address (0~31)
 *      pRegData - Writing data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PHY_REG_ID       - invalid PHY address
 *      RT_ERR_PHY_ID           - invalid PHY no
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      None
 */
static ret_t 
rtl8367c_getAsicPHYReg(rtk_uint32 phyNo, rtk_uint32 phyAddr, rtk_uint32 *pRegData )
{
    rtk_uint32 ocp_addr;

    if(phyAddr > RTL8367C_PHY_REGNOMAX)
        return RT_ERR_PHY_REG_ID;

    ocp_addr = 0xa400 + phyAddr*2;

    return rtl8367c_getAsicPHYOCPReg(phyNo, ocp_addr, pRegData);
}

ret_t rtk_switch_getPHYReg(rtk_uint32 phyNo, rtk_uint32 phyAddr, rtk_uint32 *pRegData)
{
    return rtl8367c_getAsicPHYReg(phyNo, phyAddr, pRegData);
}

/* Function Name:
 *      rtk_switch_logicalPortCheck
 * Description:
 *      Check logical port ID.
 * Input:
 *      logicalPort     - logical port ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Port ID is correct
 *      RT_ERR_FAILED   - Port ID is not correct
 *      RT_ERR_NOT_INIT - Not Initialize
 * Note:
 *
 */
rtk_api_ret_t rtk_switch_logicalPortCheck(rtk_port_t logicalPort)
{
    if(logicalPort >= RTK_SWITCH_PORT_NUM)
        return RT_ERR_FAILED;

    if(halCtrl.l2p_port[logicalPort] == 0xFF)
        return RT_ERR_FAILED;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_logPortMask_get
 * Description:
 *      Get Logical portmask
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_NOT_INIT     - Not Initialize
 *      RT_ERR_NULL_POINTER - Null pointer
 * Note:
 *
 */
rtk_api_ret_t rtk_switch_logPortMask_get(rtk_portmask_t *pPortmask)
{
    if(init_state != INIT_COMPLETED)
        return RT_ERR_FAILED;

    if(NULL == pPortmask)
        return RT_ERR_NULL_POINTER;

    pPortmask->bits[0] = halCtrl.valid_portmask;
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_isUtpPort
 * Description:
 *      Check is logical port a UTP port
 * Input:
 *      logicalPort     - logical port ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Port ID is a UTP port
 *      RT_ERR_FAILED   - Port ID is not a UTP port
 *      RT_ERR_NOT_INIT - Not Initialize
 * Note:
 *
 */
static rtk_api_ret_t rtk_switch_isUtpPort(rtk_port_t logicalPort)
{
    if(logicalPort >= RTK_SWITCH_PORT_NUM)
        return RT_ERR_FAILED;

    if(halCtrl.log_port_type[logicalPort] == UTP_PORT)
        return RT_ERR_OK;
    else
        return RT_ERR_FAILED;
}

/* Function Name:
 *      rtk_switch_port_P2L_get
 * Description:
 *      Get logical port ID
 * Input:
 *      physicalPort       - physical port ID
 * Output:
 *      None
 * Return:
 *      logical port ID
 * Note:
 *
 */
rtk_port_t rtk_switch_port_P2L_get(rtk_uint32 physicalPort)
{
    if(physicalPort >= RTK_SWITCH_PORT_NUM)
        return UNDEFINE_PORT;

    return (halCtrl.p2l_port[physicalPort]);
}

/* Function Name:
 *      rtk_switch_port_L2P_get
 * Description:
 *      Get physical port ID
 * Input:
 *      logicalPort       - logical port ID
 * Output:
 *      None
 * Return:
 *      Physical port ID
 * Note:
 *
 */
rtk_uint32 rtk_switch_port_L2P_get(rtk_port_t logicalPort)
{
    if(logicalPort >= RTK_SWITCH_PORT_NUM)
        return UNDEFINE_PHY_PORT;

    return (halCtrl.l2p_port[logicalPort]);
}

/* Function Name:
 *      rtl8367c_setAsicLutIpLookupMethod
 * Description:
 *      Set Lut IP lookup hash with DIP or {DIP,SIP} pair
 * Input:
 *      type - 1: When DIP can be found in IPMC_GROUP_TABLE, use DIP+SIP Hash, otherwise, use DIP+(SIP=0.0.0.0) Hash.
 *             0: When DIP can be found in IPMC_GROUP_TABLE, use DIP+(SIP=0.0.0.0) Hash, otherwise use DIP+SIP Hash.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicLutIpLookupMethod(rtk_uint32 type)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_LUT_CFG, RTL8367C_LUT_IPMC_LOOKUP_OP_OFFSET, type);
}
/* Function Name:
 *      rtl8367c_setAsicRma
 * Description:
 *      Set reserved multicast address for CPU trapping
 * Input:
 *      index     - reserved multicast LSB byte, 0x00~0x2F is available value
 *      pRmacfg     - type of RMA for trapping frame type setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK         - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_RMA_ADDR - Invalid RMA address index
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicRma(rtk_uint32 index, rtl8367c_rma_t* pRmacfg)
{
    rtk_uint32 regData;
    ret_t retVal;

    if(index > RTL8367C_RMAMAX)
        return RT_ERR_RMA_ADDR;

    regData = *(rtk_uint16*)pRmacfg;

    if( (index >= 0x4 && index <= 0x7) || (index >= 0x9 && index <= 0x0C) || (0x0F == index))
        index = 0x04;
    else if((index >= 0x13 && index <= 0x17) || (0x19 == index) || (index >= 0x1B && index <= 0x1f))
        index = 0x13;
    else if(index >= 0x22 && index <= 0x2F)
        index = 0x22;

    retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_RMA_CTRL00, RTL8367C_TRAP_PRIORITY_MASK, pRmacfg->trap_priority);
    if(retVal != RT_ERR_OK)
        return retVal;

    return rtl8367c_setAsicReg(RTL8367C_REG_RMA_CTRL00+index, regData);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorIsolationTxLeaky
 * Description:
 *      Set the mirror function of Isolation TX leaky
 * Input:
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortMirrorIsolationTxLeaky(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_MIRROR_CTRL2, RTL8367C_MIRROR_TX_ISOLATION_LEAKY_OFFSET, enabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortIngressBandwidth
 * Description:
 *      Set per-port total ingress bandwidth
 * Input:
 *      port        - Physical port number (0~7)
 *      bandwidth   - The total ingress bandwidth (unit: 8Kbps), 0x1FFFF:disable
 *      preifg      - Include preamble and IFG, 0:Exclude, 1:Include
 *      enableFC    - Action when input rate exceeds. 0: Drop   1: Flow Control
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortIngressBandwidth(rtk_uint32 port, rtk_uint32 bandwidth, rtk_uint32 preifg, rtk_uint32 enableFC)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint32 regAddr;

    /* Invalid input parameter */
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    if(bandwidth > RTL8367C_QOS_GRANULARTY_MAX)
        return RT_ERR_OUT_OF_RANGE;

    regAddr = RTL8367C_INGRESSBW_PORT_RATE_LSB_REG(port);
    regData = bandwidth & RTL8367C_QOS_GRANULARTY_LSB_MASK;
    retVal = rtl8367c_setAsicReg(regAddr, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    regAddr += 1;
    regData = (bandwidth & RTL8367C_QOS_GRANULARTY_MSB_MASK) >> RTL8367C_QOS_GRANULARTY_MSB_OFFSET;
    retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_INGRESSBW_PORT0_RATE_CTRL1_INGRESSBW_RATE16_MASK, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    regAddr = RTL8367C_PORT_MISC_CFG_REG(port);
    retVal = rtl8367c_setAsicRegBit(regAddr, RTL8367C_PORT0_MISC_CFG_INGRESSBW_IFG_OFFSET, preifg);
    if(retVal != RT_ERR_OK)
        return retVal;

    regAddr = RTL8367C_PORT_MISC_CFG_REG(port);
    retVal = rtl8367c_setAsicRegBit(regAddr, RTL8367C_PORT0_MISC_CFG_INGRESSBW_FLOWCTRL_OFFSET, enableFC);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_rate_igrBandwidthCtrlRate_set
 * Description:
 *      Set port ingress bandwidth control
 * Input:
 *      port        - Port id
 *      rate        - Rate of share meter
 *      ifg_include - include IFG or not, ENABLE:include DISABLE:exclude
 *      fc_enable   - enable flow control or not, ENABLE:use flow control DISABLE:drop
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_ENABLE       - Invalid IFG parameter.
 *      RT_ERR_INBW_RATE    - Invalid ingress rate parameter.
 * Note:
 *      The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *      The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 */
static rtk_api_ret_t rtk_rate_igrBandwidthCtrlRate_set(rtk_port_t port, rtk_rate_t rate, rtk_enable_t ifg_include, rtk_enable_t fc_enable)
{
    rtk_api_ret_t retVal;

    if(ifg_include >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if(fc_enable >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if (ifg_include >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortIngressBandwidth(rtk_switch_port_L2P_get(port), rate>>3, ifg_include,fc_enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicPortEgressRate
 * Description:
 *      Set per-port egress rate
 * Input:
 *      port        - Physical port number (0~10)
 *      rate        - Egress rate
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_QOS_EBW_RATE - Invalid bandwidth/rate
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortEgressRate(rtk_uint32 port, rtk_uint32 rate)
{
    ret_t retVal;
    rtk_uint32 regAddr, regData;

    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(rate > RTL8367C_QOS_GRANULARTY_MAX)
        return RT_ERR_QOS_EBW_RATE;

    regAddr = RTL8367C_PORT_EGRESSBW_LSB_REG(port);
    regData = RTL8367C_QOS_GRANULARTY_LSB_MASK & rate;

    retVal = rtl8367c_setAsicReg(regAddr, regData);

    if(retVal != RT_ERR_OK)
        return retVal;

    regAddr = RTL8367C_PORT_EGRESSBW_MSB_REG(port);
    regData = (RTL8367C_QOS_GRANULARTY_MSB_MASK & rate) >> RTL8367C_QOS_GRANULARTY_MSB_OFFSET;

    retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_PORT6_EGRESSBW_CTRL1_MASK, regData);

    return retVal;
}

/* Function Name:
 *      rtl8367c_setAsicPortEgressRateIfg
 * Description:
 *      Set per-port egress rate calculate include/exclude IFG
 * Input:
 *      ifg     - 1:include IFG 0:exclude IFG
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortEgressRateIfg(rtk_uint32 ifg)
{
    ret_t retVal;

    retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SCHEDULE_WFQ_CTRL, RTL8367C_SCHEDULE_WFQ_CTRL_OFFSET, ifg);

    return retVal;
}

/* Function Name:
 *      rtk_rate_egrBandwidthCtrlRate_set
 * Description:
 *      Set port egress bandwidth control
 * Input:
 *      port        - Port id
 *      rate        - Rate of egress bandwidth
 *      ifg_include - include IFG or not, ENABLE:include DISABLE:exclude
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_QOS_EBW_RATE - Invalid egress bandwidth/rate
 * Note:
 *     The rate unit is 1 kbps and the range is from 8k to 1048568k. The granularity of rate is 8 kbps.
 *     The ifg_include parameter is used for rate calculation with/without inter-frame-gap and preamble.
 */
static rtk_api_ret_t rtk_rate_egrBandwidthCtrlRate_set( rtk_port_t port, rtk_rate_t rate,  rtk_enable_t ifg_include)
{
    rtk_api_ret_t retVal;

    if (ifg_include >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortEgressRate(rtk_switch_port_L2P_get(port), rate>>3)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicPortEgressRateIfg(ifg_include)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

static rtk_api_ret_t _rtk_switch_init_8367c(void)
{
    rtk_port_t port;
    rtk_uint32 retVal;
    rtk_uint32 regData;
    rtk_uint32 regValue;

    if( (retVal = rtl8367c_setAsicReg(0x13c2, 0x0249)) != RT_ERR_OK)
        return retVal;

    if( (retVal = rtl8367c_getAsicReg(0x1301, &regValue)) != RT_ERR_OK)
        return retVal;

    if( (retVal = rtl8367c_setAsicReg(0x13c2, 0x0000)) != RT_ERR_OK)
        return retVal;

    RTK_SCAN_ALL_LOG_PORT(port)
    {
         if(rtk_switch_isUtpPort(port) == RT_ERR_OK)
         {
             if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_PORT0_EEECFG + (0x20 * port), RTL8367C_PORT0_EEECFG_EEE_100M_OFFSET, 1)) != RT_ERR_OK)
                 return retVal;

             if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_PORT0_EEECFG + (0x20 * port), RTL8367C_PORT0_EEECFG_EEE_GIGA_500M_OFFSET, 1)) != RT_ERR_OK)
                 return retVal;

             if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_PORT0_EEECFG + (0x20 * port), RTL8367C_PORT0_EEECFG_EEE_TX_OFFSET, 1)) != RT_ERR_OK)
                 return retVal;

             if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_PORT0_EEECFG + (0x20 * port), RTL8367C_PORT0_EEECFG_EEE_RX_OFFSET, 1)) != RT_ERR_OK)
                 return retVal;

             if((retVal = rtl8367c_getAsicPHYOCPReg(port, 0xA428, &regData)) != RT_ERR_OK)
                return retVal;

             regData &= ~(0x0200);
             if((retVal = rtl8367c_setAsicPHYOCPReg(port, 0xA428, regData)) != RT_ERR_OK)
                 return retVal;

             if((regValue & 0x00F0) == 0x00A0)
             {
                 if((retVal = rtl8367c_getAsicPHYOCPReg(port, 0xA5D0, &regData)) != RT_ERR_OK)
                     return retVal;

                 regData |= 0x0006;
                 if((retVal = rtl8367c_setAsicPHYOCPReg(port, 0xA5D0, regData)) != RT_ERR_OK)
                     return retVal;
             }
         }
    }

    if((retVal = rtl8367c_setAsicReg(RTL8367C_REG_UTP_FIB_DET, 0x15BB)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x1303, 0x06D6)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x1304, 0x0700)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x13E2, 0x003F)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x13F9, 0x0090)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x121e, 0x03CA)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x1233, 0x0352)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x1237, 0x00a0)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x123a, 0x0030)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x1239, 0x0084)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x0301, 0x1000)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x1349, 0x001F)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicRegBit(0x18e0, 0, 0)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicRegBit(0x122b, 14, 1)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicRegBits(0x1305, 0xC000, 3)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_init
 * Description:
 *      Set chip to default configuration enviroment
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can set chip registers to default configuration for different release chip model.
 */
rtk_api_ret_t rtk_switch_init(void)
{
    rtk_uint32  retVal;
    rtl8367c_rma_t rmaCfg;

    if((retVal = _rtk_switch_init_8367c()) != RT_ERR_OK)
        return retVal;

    /* Set Old max packet length to 16K */
    if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_MAX_LENGTH_LIMINT_IPG, RTL8367C_MAX_LENTH_CTRL_MASK, 3)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_MAX_LEN_RX_TX, RTL8367C_MAX_LEN_RX_TX_MASK, 3)) != RT_ERR_OK)
        return retVal;

    /* ACL Mode */
    if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_ACL_ACCESS_MODE, RTL8367C_ACL_ACCESS_MODE_MASK, 1)) != RT_ERR_OK)
        return retVal;

    /* Max rate */
    if((retVal = rtk_rate_igrBandwidthCtrlRate_set(EXT_PORT0, RTL8367C_QOS_RATE_INPUT_MAX_HSG, DISABLED, ENABLED)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtk_rate_egrBandwidthCtrlRate_set(EXT_PORT0, RTL8367C_QOS_RATE_INPUT_MAX_HSG, ENABLED)) != RT_ERR_OK)
        return retVal;

    if((retVal = rtl8367c_setAsicReg(0x03fa, 0x0007)) != RT_ERR_OK)
        return retVal;

    /* Change unknown DA to per port setting */
    if((retVal = rtl8367c_setAsicRegBits(RTL8367C_PORT_SECURIT_CTRL_REG, RTL8367C_UNKNOWN_UNICAST_DA_BEHAVE_MASK, 3)) != RT_ERR_OK)
        return retVal;

    /* LUT lookup OP = 1 */
    if ((retVal = rtl8367c_setAsicLutIpLookupMethod(1))!=RT_ERR_OK)
        return retVal;

    /* Set RMA */
    rmaCfg.portiso_leaky = 0;
    rmaCfg.vlan_leaky = 0;
    rmaCfg.keep_format = 0;
    rmaCfg.trap_priority = 0;
    rmaCfg.discard_storm_filter = 0;
    rmaCfg.operation = 0;
    if ((retVal = rtl8367c_setAsicRma(2, &rmaCfg))!=RT_ERR_OK)
        return retVal;

    /* Enable TX Mirror isolation leaky */
    if ((retVal = rtl8367c_setAsicPortMirrorIsolationTxLeaky(ENABLED)) != RT_ERR_OK)
        return retVal;

    /* INT EN */
    if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_IO_MISC_FUNC, RTL8367C_INT_EN_OFFSET, 1)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicPortForceLinkExt
 * Description:
 *      Set external interface force linking configuration
 * Input:
 *      id          - external interface id (0~2)
 *      portAbility - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortForceLinkExt(rtk_uint32 id, rtl8367c_port_ability_t *pPortAbility)
{
    rtk_uint32 retVal;
    rtk_uint32 reg_data;

    /* Invalid input parameter */
    if(id >= RTL8367C_EXTNO)
        return RT_ERR_OUT_OF_RANGE;

    reg_data = (rtk_uint32)(*(rtk_uint16 *)pPortAbility);

    if(1 == id)
    {
        if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_FDUP_OFFSET, pPortAbility->duplex)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_SPD_MASK, pPortAbility->speed)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_LINK_OFFSET, pPortAbility->link)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_TXFC_OFFSET, pPortAbility->txpause)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_RXFC_OFFSET, pPortAbility->rxpause)) != RT_ERR_OK)
            return retVal;
    }

    if(0 == id || 1 == id)
        return rtl8367c_setAsicReg(RTL8367C_REG_DIGITAL_INTERFACE0_FORCE + id, reg_data);
    else
        return rtl8367c_setAsicReg(RTL8367C_REG_DIGITAL_INTERFACE2_FORCE, reg_data);
}

/* Function Name:
 *      rtl8367c_setAsicPortExtMode
 * Description:
 *      Set external interface mode configuration
 * Input:
 *      id      - external interface id (0~2)
 *      mode    - external interface mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortExtMode(rtk_uint32 id, rtk_uint32 mode)
{
    ret_t   retVal;
    rtk_uint32 i, regValue;
    rtk_uint32 redData[][2] = { {0x7180, 0x2}, {0x04D7, 0x0480}, {0xF994, 0x0481}, {0x31A2, 0x0482}, {0x6960, 0x0483}, {0x9728, 0x0484}, {0x9D85, 0x0423}, {0xD810, 0x0424}, {0x0F80, 0x0001} };
    rtk_uint32 redData1[][2] = { {0x82F1, 0x0500}, {0xF195, 0x0501}, {0x31A2, 0x0502}, {0x796C, 0x0503}, {0x9728, 0x0504}, {0x9D85, 0x0423}, {0xD810, 0x0424}, {0x0F80, 0x0001} };
    rtk_uint32 redData5[][2] = { {0x82F1, 0x0500}, {0xF195, 0x0501}, {0x31A2, 0x0502}, {0x796C, 0x0503}, {0x9728, 0x0504}, {0x9D85, 0x0423}, {0xD810, 0x0424}, {0x0F80, 0x0001} };
    rtk_uint32 redData6[][2] = { {0x82F1, 0x0500}, {0xF195, 0x0501}, {0x31A2, 0x0502}, {0x796C, 0x0503}, {0x9728, 0x0504}, {0x9D85, 0x0423}, {0xD810, 0x0424}, {0x0F80, 0x0001} };
    rtk_uint32 redData7[][2] = { {0x82F1, 0x0500}, {0xF995, 0x0501}, {0x31A2, 0x0502}, {0x796C, 0x0503}, {0x9728, 0x0504}, {0x9D85, 0x0423}, {0xD810, 0x0424}, {0x0F80, 0x0001} };
    rtk_uint32 redData8[][2] = { {0x82F1, 0x0500}, {0xF995, 0x0501}, {0x31A2, 0x0502}, {0x796C, 0x0503}, {0x9728, 0x0504}, {0x9D85, 0x0423}, {0xD810, 0x0424}, {0x0F80, 0x0001} };

    if(id >= RTL8367C_EXTNO)
        return RT_ERR_OUT_OF_RANGE;

    if(mode >= EXT_END)
        return RT_ERR_OUT_OF_RANGE;

    if( (mode == EXT_SGMII) || (mode == EXT_HSGMII) )
    {
        if(id != 1)
            return RT_ERR_PORT_ID;
    }

    if(mode == EXT_GMII)
    {
        if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_EXT0_RGMXF, RTL8367C_EXT0_RGTX_INV_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_EXT1_RGMXF, RTL8367C_EXT1_RGTX_INV_OFFSET, 1)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_EXT_TXC_DLY, RTL8367C_EXT1_GMII_TX_DELAY_MASK, 5)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_EXT_TXC_DLY, RTL8367C_EXT0_GMII_TX_DELAY_MASK, 6)) != RT_ERR_OK)
            return retVal;
    }

    /* Serdes reset */
    if( (mode == EXT_TMII_MAC) || (mode == EXT_TMII_PHY) )
    {
        if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_BYPASS_LINE_RATE, id, 1)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_BYPASS_LINE_RATE, id, 0)) != RT_ERR_OK)
            return retVal;
    }

    if(mode == EXT_SGMII)
    {
        for(i = 0; i <= 7; i++)
        {
            if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, redData[i][0])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, redData[i][1])) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
                return retVal;
        }
    }

    if(mode == EXT_HSGMII)
    {
        if( (retVal = rtl8367c_setAsicReg(0x13c2, 0x0249)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_getAsicReg(0x1301, &regValue)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_setAsicReg(0x13c2, 0x0000)) != RT_ERR_OK)
            return retVal;

        if ( ((regValue & 0x00F0) >> 4) == 0x0001)
        {
            for(i = 0; i <= 7; i++)
            {
                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, redData1[i][0])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, redData1[i][1])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else if ( ((regValue & 0x00F0) >> 4) == 0x0005)
        {
            for(i = 0; i <= 7; i++)
            {
                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, redData5[i][0])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, redData5[i][1])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else if ( ((regValue & 0x00F0) >> 4) == 0x0006)
        {
            for(i = 0; i <= 7; i++)
            {
                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, redData6[i][0])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, redData6[i][1])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else if ( ((regValue & 0x00F0) >> 4) == 0x0007)
        {
            for(i = 0; i <= 7; i++)
            {
                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, redData7[i][0])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, redData7[i][1])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else if ( ((regValue & 0x00F0) >> 4) == 0x0008)
        {
            for(i = 0; i <= 7; i++)
            {
                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, redData8[i][0])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, redData8[i][1])) != RT_ERR_OK)
                    return retVal;

                if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
                    return retVal;
            }
        }
    }

    /* Only one ext port should care SGMII setting */
    if(id == 1)
    {
        if(mode == EXT_SGMII)
        {
            if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_SGMII_OFFSET, 1)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET, 0)) != RT_ERR_OK)
                return retVal;
        }
        else if(mode == EXT_HSGMII)
        {
            if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_SGMII_OFFSET, 0)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET, 1)) != RT_ERR_OK)
                return retVal;
        }
        else
        {
            if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_SGMII_OFFSET, 0)) != RT_ERR_OK)
                return retVal;

            if( (retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET, 0)) != RT_ERR_OK)
                return retVal;
        }
    }

    if(0 == id || 1 == id)
    {
        if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_DIGITAL_INTERFACE_SELECT, RTL8367C_SELECT_GMII_0_MASK << (id * RTL8367C_SELECT_GMII_1_OFFSET), mode)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if((retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_DIGITAL_INTERFACE_SELECT_1, RTL8367C_SELECT_GMII_2_MASK, mode)) != RT_ERR_OK)
            return retVal;
    }

    /* Serdes not reset */
    if( (mode == EXT_SGMII) || (mode == EXT_HSGMII) )
    {
        if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_DATA, 0x7106)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_ADR, 0x0003)) != RT_ERR_OK)
            return retVal;

        if( (retVal = rtl8367c_setAsicReg(RTL8367C_REG_SDS_INDACS_CMD, 0x00C0)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicPortForceLinkExt
 * Description:
 *      Get external interface force linking configuration
 * Input:
 *      id          - external interface id (0~1)
 *      pPortAbility - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      None
 */
static ret_t rtl8367c_getAsicPortForceLinkExt(rtk_uint32 id, rtl8367c_port_ability_t *pPortAbility)
{
    rtk_uint32  reg_data;
    rtk_uint32  sgmiiSel;
    rtk_uint32  hsgmiiSel;
    rtk_uint16  ability_data;
    ret_t       retVal;

    /* Invalid input parameter */
    if(id >= RTL8367C_EXTNO)
        return RT_ERR_OUT_OF_RANGE;

    if(1 == id)
    {
        if((retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_SGMII_OFFSET, &sgmiiSel)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET, &hsgmiiSel)) != RT_ERR_OK)
            return retVal;

        if( (sgmiiSel == 1) || (hsgmiiSel == 1) )
        {
            memset(pPortAbility, 0x00, sizeof(rtl8367c_port_ability_t));
            pPortAbility->forcemode = 1;

            if((retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_FDUP_OFFSET, &reg_data)) != RT_ERR_OK)
                return retVal;

            pPortAbility->duplex = reg_data;

            if((retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_SPD_MASK, &reg_data)) != RT_ERR_OK)
                return retVal;

            pPortAbility->speed = reg_data;

            if((retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_LINK_OFFSET, &reg_data)) != RT_ERR_OK)
                return retVal;

            pPortAbility->link = reg_data;

            if((retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_TXFC_OFFSET, &reg_data)) != RT_ERR_OK)
                return retVal;

            pPortAbility->txpause = reg_data;

            if((retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_SGMII_RXFC_OFFSET, &reg_data)) != RT_ERR_OK)
                return retVal;

            pPortAbility->rxpause = reg_data;

            return RT_ERR_OK;
        }
    }

    if(0 == id || 1 == id)
        retVal = rtl8367c_getAsicReg(RTL8367C_REG_DIGITAL_INTERFACE0_FORCE+id, &reg_data);
    else
        retVal = rtl8367c_getAsicReg(RTL8367C_REG_DIGITAL_INTERFACE2_FORCE, &reg_data);

    if(retVal != RT_ERR_OK)
        return retVal;

    ability_data = (rtk_uint16)reg_data;
    memcpy(pPortAbility, &ability_data, sizeof(rtl8367c_port_ability_t));

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_macForceLinkExt_set
 * Description:
 *      Set external interface force linking configuration.
 * Input:
 *      port            - external port ID
 *      mode            - external interface mode
 *      pPortability    - port ability configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface force mode properties.
 *      The external interface can be set to:
 *      - MODE_EXT_DISABLE,
 *      - MODE_EXT_RGMII,
 *      - MODE_EXT_MII_MAC,
 *      - MODE_EXT_MII_PHY,
 *      - MODE_EXT_TMII_MAC,
 *      - MODE_EXT_TMII_PHY,
 *      - MODE_EXT_GMII,
 *      - MODE_EXT_RMII_MAC,
 *      - MODE_EXT_RMII_PHY,
 *      - MODE_EXT_SGMII,
 *      - MODE_EXT_HSGMII
 */
rtk_api_ret_t rtk_port_macForceLinkExt_set(rtk_port_t port, rtk_mode_ext_t mode, rtk_port_mac_ability_t *pPortability)
{
    rtk_api_ret_t retVal;
    rtl8367c_port_ability_t ability;
    rtk_uint32 ext_id;

    if(NULL == pPortability)
        return RT_ERR_NULL_POINTER;

    if (mode >=MODE_EXT_END)
        return RT_ERR_INPUT;

    if(mode == MODE_EXT_HSGMII)
    {
        if (pPortability->forcemode > 1 || pPortability->speed != PORT_SPEED_2500M || pPortability->duplex != PORT_FULL_DUPLEX ||
           pPortability->link >= PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;
    }
    else
    {
        if (pPortability->forcemode > 1 || pPortability->speed > PORT_SPEED_1000M || pPortability->duplex >= PORT_DUPLEX_END ||
           pPortability->link >= PORT_LINKSTATUS_END || pPortability->nway > 1 || pPortability->txpause > 1 || pPortability->rxpause > 1)
            return RT_ERR_INPUT;
    }

    ext_id = port - 15;

    if(mode == MODE_EXT_DISABLE)
    {
        memset(&ability, 0x00, sizeof(rtl8367c_port_ability_t));
        if ((retVal = rtl8367c_setAsicPortForceLinkExt(ext_id, &ability)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_setAsicPortExtMode(ext_id, mode)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if ((retVal = rtl8367c_setAsicPortExtMode(ext_id, mode)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_getAsicPortForceLinkExt(ext_id, &ability)) != RT_ERR_OK)
            return retVal;

        ability.forcemode = pPortability->forcemode;
        ability.speed     = (mode == MODE_EXT_HSGMII) ? PORT_SPEED_1000M : pPortability->speed;
        ability.duplex    = pPortability->duplex;
        ability.link      = pPortability->link;
        ability.nway      = pPortability->nway;
        ability.txpause   = pPortability->txpause;
        ability.rxpause   = pPortability->rxpause;

        if ((retVal = rtl8367c_setAsicPortForceLinkExt(ext_id, &ability)) != RT_ERR_OK)
            return retVal;
    }

    return RT_ERR_OK;
}



#define    RTL8367C_REG_PORT0_STATUS                0x1352
#define    RTL8367C_MIB_LEARNENTRYDISCARD_OFFSET    (0x420)
#define    RTL8367C_MIB_PORT_OFFSET                 (0x7C)
#define    RTL8367C_REG_MIB_ADDRESS                 0x1004
#define    RTL8367C_REG_MIB_CTRL0                   0x1005
#define    RTL8367C_MIB_CTRL_REG                    RTL8367C_REG_MIB_CTRL0
#define    RTL8367C_MIB_CTRL0_BUSY_FLAG_MASK        0x1
#define    RTL8367C_RESET_FLAG_MASK                 0x2
#define    RTL8367C_REG_MIB_COUNTER0                0x1000
#define    RTL8367C_MIB_COUNTER_BASE_REG            RTL8367C_REG_MIB_COUNTER0

typedef struct  rtl8367c_port_status_s{
#ifdef _LITTLE_ENDIAN
    rtk_uint16 speed:2;
    rtk_uint16 duplex:1;
    rtk_uint16 reserve1:1;
    rtk_uint16 link:1;
    rtk_uint16 rxpause:1;
    rtk_uint16 txpause:1;
    rtk_uint16 nway:1;
    rtk_uint16 mstmode:1;
    rtk_uint16 mstfault:1;
    rtk_uint16 lpi100:1;
    rtk_uint16 lpi1000:1;
    rtk_uint16 reserve2:4;
#else
    rtk_uint16 reserve2:4;
    rtk_uint16 lpi1000:1;
    rtk_uint16 lpi100:1;
    rtk_uint16 mstfault:1;
    rtk_uint16 mstmode:1;
    rtk_uint16 nway:1;
    rtk_uint16 txpause:1;
    rtk_uint16 rxpause:1;
    rtk_uint16 link:1;
    rtk_uint16 reserve1:1;
    rtk_uint16 duplex:1;
    rtk_uint16 speed:2;

#endif
}rtl8367c_port_status_t;

static ret_t rtl8367c_getAsicPortStatus(rtk_uint32 port, rtl8367c_port_status_t *pPortStatus)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint16 *accessPtr;
    rtl8367c_port_status_t status;

    /* Invalid input parameter */
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    memset(&status, 0x00, sizeof(rtl8367c_port_status_t));


    accessPtr =  (rtk_uint16*)&status;

    retVal = rtl8367c_getAsicReg(RTL8367C_REG_PORT0_STATUS+port,&regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    *accessPtr = regData;

    memcpy(pPortStatus, &status, sizeof(rtl8367c_port_status_t));

    return RT_ERR_OK;
}

static rtk_api_ret_t rtk_switch_isHsgPort(rtk_port_t logicalPort)
{
    if(logicalPort >= RTK_SWITCH_PORT_NUM)
        return RT_ERR_FAILED;

    if(logicalPort == halCtrl.hsg_logical_port)
        return RT_ERR_OK;
    else
        return RT_ERR_FAILED;
}

rtk_api_ret_t rtk_port_macStatus_get(rtk_port_t port, rtk_port_mac_ability_t *pPortstatus)
{
    rtk_api_ret_t retVal;
    rtl8367c_port_status_t status;
    rtk_uint32 hsgsel;

    if(NULL == pPortstatus)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortStatus(rtk_switch_port_L2P_get(port), &status)) != RT_ERR_OK)
        return retVal;


    pPortstatus->duplex    = status.duplex;
    pPortstatus->link      = status.link;
    pPortstatus->nway      = status.nway;
    pPortstatus->txpause   = status.txpause;
    pPortstatus->rxpause   = status.rxpause;

    if( (retVal = rtl8367c_getAsicRegBit(RTL8367C_REG_SDS_MISC, RTL8367C_CFG_MAC8_SEL_HSGMII_OFFSET, &hsgsel)) != RT_ERR_OK)
            return retVal;

    if( (rtk_switch_isHsgPort(port) == RT_ERR_OK) && (hsgsel == 1) )
        pPortstatus->speed = PORT_SPEED_2500M;
    else
        pPortstatus->speed = status.speed;

    return RT_ERR_OK;
}

/**************************************************************************************************/
/*                                           FOR VLAN                                             */
/**************************************************************************************************/

#define RTL8367C_CVIDXNO                    32
#define RTL8367C_CVIDXMAX                   (RTL8367C_CVIDXNO-1)
#define RTL8367C_EVIDMAX                    0x1FFF
#define RTL8367C_PORTMASK                   0x7FF
#define RTL8367C_FIDMAX                     0xF
#define RTL8367C_METERNO                    64
#define RTL8367C_METERMAX                   (RTL8367C_METERNO-1)
#define RTL8367C_PRIMAX                     7
#define RTL8367C_VIDMAX                     0xFFF
#define    RTL8367C_REG_TABLE_WRITE_DATA0    0x0510
#define    RTL8367C_TABLE_ACCESS_WRDATA_BASE                    RTL8367C_REG_TABLE_WRITE_DATA0
#define    RTL8367C_REG_TABLE_ACCESS_ADDR    0x0501
#define    RTL8367C_TABLE_ACCESS_ADDR_REG                        RTL8367C_REG_TABLE_ACCESS_ADDR
#define    RTL8367C_REG_TABLE_ACCESS_CTRL    0x0500
#define    RTL8367C_TABLE_ACCESS_CTRL_REG                        RTL8367C_REG_TABLE_ACCESS_CTRL
#define    RTL8367C_TABLE_TYPE_MASK    0x7
#define    RTL8367C_COMMAND_TYPE_MASK    0x8
#define RTK_PHY_PORTMASK_ALL                                (rtk_switch_phyPortMask_get())
#define    RTL8367C_REG_VLAN_MEMBER_CONFIGURATION0_CTRL0    0x0728
#define    RTL8367C_VLAN_MEMBER_CONFIGURATION_BASE                RTL8367C_REG_VLAN_MEMBER_CONFIGURATION0_CTRL0
#define    RTL8367C_REG_VLAN_INGRESS    0x07a9
#define    RTL8367C_VLAN_INGRESS_REG                            RTL8367C_REG_VLAN_INGRESS
#define    RTL8367C_REG_VLAN_CTRL    0x07a8
#define    RTL8367C_VLAN_CTRL_OFFSET    0
#define    RTL8367C_PORT0_MISC_CFG_VLAN_EGRESS_MODE_MASK    0x30
#define    RTL8367C_VLAN_EGRESS_MDOE_MASK                        RTL8367C_PORT0_MISC_CFG_VLAN_EGRESS_MODE_MASK

#define RTK_SCAN_ALL_PHY_PORTMASK(__port__)                 for(__port__ = 0; __port__ < RTK_SWITCH_PORT_NUM; __port__++)  if( (rtk_switch_phyPortMask_get() & (0x00000001 << __port__)))
#define RTL8367C_TABLE_ACCESS_REG_DATA(op, target)    ((op << 3) | target)
#define    RTL8367C_REG_VLAN_PVID_CTRL0    0x0700
#define    RTL8367C_VLAN_PVID_CTRL_BASE                            RTL8367C_REG_VLAN_PVID_CTRL0
#define    RTL8367C_VLAN_PVID_CTRL_REG(port)                    (RTL8367C_VLAN_PVID_CTRL_BASE + (port >> 1))
#define    RTL8367C_PORT0_VIDX_MASK    0x1F
#define    RTL8367C_PORT_VIDX_OFFSET(port)                        ((port &1)<<3)
#define    RTL8367C_PORT_VIDX_MASK(port)                        (RTL8367C_PORT0_VIDX_MASK << RTL8367C_PORT_VIDX_OFFSET(port))
#define    RTL8367C_REG_VLAN_PORTBASED_PRIORITY_CTRL0    0x0851
#define    RTL8367C_VLAN_PORTBASED_PRIORITY_BASE                RTL8367C_REG_VLAN_PORTBASED_PRIORITY_CTRL0
#define    RTL8367C_VLAN_PORTBASED_PRIORITY_REG(port)            (RTL8367C_VLAN_PORTBASED_PRIORITY_BASE + (port >> 2))
#define    RTL8367C_VLAN_PORTBASED_PRIORITY_OFFSET(port)        ((port & 0x3) << 2)
#define    RTL8367C_VLAN_PORTBASED_PRIORITY_MASK(port)            (0x7 << RTL8367C_VLAN_PORTBASED_PRIORITY_OFFSET(port))
#define RTL8367C_VLAN_BUSY_CHECK_NO     (10)
#define    RTL8367C_REG_TABLE_LUT_ADDR    0x0502
#define    RTL8367C_TABLE_ACCESS_STATUS_REG                        RTL8367C_REG_TABLE_LUT_ADDR
#define    RTL8367C_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET    13
#define    RTL8367C_TABLE_ACCESS_RDDATA_BASE                    RTL8367C_REG_TABLE_READ_DATA0
#define    RTL8367C_REG_TABLE_READ_DATA0    0x0520

#define RTK_MAX_METER_ID            (rtk_switch_maxMeterId_get())

typedef enum
{
    EG_TAG_MODE_ORI = 0,
    EG_TAG_MODE_KEEP,
    EG_TAG_MODE_PRI_TAG,
    EG_TAG_MODE_REAL_KEEP,
    EG_TAG_MODE_END
} rtl8367c_egtagmode;

enum RTL8367C_TABLE_ACCESS_OP
{
    TB_OP_READ = 0,
    TB_OP_WRITE
};

enum RTL8367C_TABLE_ACCESS_TARGET
{
    TB_TARGET_ACLRULE = 1,
    TB_TARGET_ACLACT,
    TB_TARGET_CVLAN,
    TB_TARGET_L2,
    TB_TARGET_IGMP_GROUP
};

typedef struct  VLANTABLE
{
 #ifdef _LITTLE_ENDIAN
    rtk_uint16  mbr:8;
    rtk_uint16  untag:8;

    rtk_uint16  fid_msti:4;
    rtk_uint16  vbpen:1;
    rtk_uint16 vbpri:3;
    rtk_uint16 envlanpol:1;
    rtk_uint16 meteridx:5;
    rtk_uint16 ivl_svl:1;
    rtk_uint16 mbr_ext_0:1;

    rtk_uint16 mbr_ext_1_2:2;
    rtk_uint16 untagset_ext:3;
    rtk_uint16 mtr_idx_ext:1;
     rtk_uint16 reserved:10;
  #else
    rtk_uint16  untag:8;
    rtk_uint16  mbr:8;

    rtk_uint16 mbr_ext_0:1;
    rtk_uint16 ivl_svl:1;
    rtk_uint16 meteridx:5;
    rtk_uint16 envlanpol:1;
    rtk_uint16 vbpri:3;
    rtk_uint16  vbpen:1;
    rtk_uint16  fid_msti:4;

    rtk_uint16 reserved:10;
    rtk_uint16 mtr_idx_ext:1;
    rtk_uint16 untagset_ext:3;
    rtk_uint16 mbr_ext_1_2:2;

#endif
}rtl8367c_vlan4kentrysmi;


typedef struct  VLANCONFIGUSER
{
    rtk_uint16  evid;
    rtk_uint16  mbr;
    rtk_uint16  fid_msti;
    rtk_uint16  envlanpol;
    rtk_uint16  meteridx;
    rtk_uint16  vbpen;
    rtk_uint16  vbpri;
}rtl8367c_vlanconfiguser;

typedef struct  USER_VLANTABLE{

    rtk_uint16  vid;
    rtk_uint16  mbr;
    rtk_uint16  untag;
    rtk_uint16  fid_msti;
    rtk_uint16  envlanpol;
    rtk_uint16  meteridx;
    rtk_uint16  vbpen;
    rtk_uint16  vbpri;
    rtk_uint16  ivl_svl;

}rtl8367c_user_vlan4kentry;

typedef struct  VLANCONFIGSMI
{
#ifdef _LITTLE_ENDIAN
    rtk_uint16  mbr:11;
    rtk_uint16  reserved:5;

    rtk_uint16  fid_msti:4;
    rtk_uint16  reserved2:12;

    rtk_uint16  vbpen:1;
    rtk_uint16  vbpri:3;
    rtk_uint16  envlanpol:1;
    rtk_uint16  meteridx:6;
    rtk_uint16  reserved3:5;

    rtk_uint16  evid:13;
    rtk_uint16  reserved4:3;
#else
    rtk_uint16  reserved:5;
    rtk_uint16  mbr:11;

    rtk_uint16  reserved2:12;
    rtk_uint16  fid_msti:4;

    rtk_uint16  reserved3:5;
    rtk_uint16  meteridx:6;
    rtk_uint16  envlanpol:1;
    rtk_uint16  vbpri:3;
    rtk_uint16  vbpen:1;

    rtk_uint16  reserved4:3;
    rtk_uint16  evid:13;
#endif

}rtl8367c_vlanconfigsmi;

typedef enum vlan_mbrCfgType_e
{
    MBRCFG_UNUSED = 0,
    MBRCFG_USED_BY_VLAN,
    MBRCFG_END
}vlan_mbrCfgType_t;

static rtk_vlan_t           vlan_mbrCfgVid[RTL8367C_CVIDXNO];
static vlan_mbrCfgType_t    vlan_mbrCfgUsage[RTL8367C_CVIDXNO];

/* Function Name:
 *      rtk_switch_phyPortMask_get
 * Description:
 *      Get physical portmask
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      0x00                - Not Initialize
 *      Other value         - Physical port mask
 * Note:
 *
 */
rtk_uint32 rtk_switch_phyPortMask_get(void)
{

    return (halCtrl.phy_portmask);
}

void _rtl8367c_VlanMCStUser2Smi(rtl8367c_vlanconfiguser *pVlanCg, rtl8367c_vlanconfigsmi *pSmiVlanCfg)
{
    pSmiVlanCfg->mbr        = pVlanCg->mbr;
    pSmiVlanCfg->fid_msti   = pVlanCg->fid_msti;
    pSmiVlanCfg->evid       = pVlanCg->evid;
    pSmiVlanCfg->meteridx   = pVlanCg->meteridx;
    pSmiVlanCfg->envlanpol  = pVlanCg->envlanpol;
    pSmiVlanCfg->vbpri      = pVlanCg->vbpri;
    pSmiVlanCfg->vbpen      = pVlanCg->vbpen;
}

/* Function Name:
 *      rtk_switch_maxMeterId_get
 * Description:
 *      Get Max Meter ID
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      0x00                - Not Initialize
 *      Other value         - Max Meter ID
 * Note:
 *
 */
rtk_uint32 rtk_switch_maxMeterId_get(void)
{
    return (halCtrl.max_meter_id);
}

/* Function Name:
 *      rtl8367c_setAsicVlanMemberConfig
 * Description:
 *      Set 32 VLAN member configurations
 * Input:
 *      index       - VLAN member configuration index (0~31)
 *      pVlanCg - VLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameter
 *      RT_ERR_L2_FID               - Invalid FID
 *      RT_ERR_PORT_MASK            - Invalid portmask
 *      RT_ERR_FILTER_METER_ID      - Invalid meter
 *      RT_ERR_QOS_INT_PRIORITY     - Invalid priority
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - Invalid VLAN member configuration index
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicVlanMemberConfig(rtk_uint32 index, rtl8367c_vlanconfiguser *pVlanCg)
{
    ret_t  retVal;
    rtk_uint32 regAddr;
    rtk_uint32 regData;
    rtk_uint16 *tableAddr;
    rtk_uint32 page_idx;
    rtl8367c_vlanconfigsmi  smi_vlancfg;

    /* Error Checking  */
    if(index > RTL8367C_CVIDXMAX)
        return RT_ERR_VLAN_ENTRY_NOT_FOUND;

    if(pVlanCg->evid > RTL8367C_EVIDMAX)
        return RT_ERR_INPUT;


    if(pVlanCg->mbr > RTL8367C_PORTMASK)
        return RT_ERR_PORT_MASK;

    if(pVlanCg->fid_msti > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    if(pVlanCg->meteridx > RTL8367C_METERMAX)
        return RT_ERR_FILTER_METER_ID;

    if(pVlanCg->vbpri > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    memset(&smi_vlancfg, 0x00, sizeof(rtl8367c_vlanconfigsmi));
    _rtl8367c_VlanMCStUser2Smi(pVlanCg, &smi_vlancfg);
    tableAddr = (rtk_uint16*)&smi_vlancfg;

    for(page_idx = 0; page_idx < 4; page_idx++)  /* 4 pages per VLAN Member Config */
    {
        regAddr = RTL8367C_VLAN_MEMBER_CONFIGURATION_BASE + (index * 4) + page_idx;
        regData = *tableAddr;

        retVal = rtl8367c_setAsicReg(regAddr, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        tableAddr++;
    }

    return RT_ERR_OK;
}

void _rtl8367c_Vlan4kStUser2Smi(rtl8367c_user_vlan4kentry *pUserVlan4kEntry, rtl8367c_vlan4kentrysmi *pSmiVlan4kEntry)
{
    pSmiVlan4kEntry->mbr        = pUserVlan4kEntry->mbr&0xff;
    pSmiVlan4kEntry->mbr_ext_0  = (pUserVlan4kEntry->mbr >> 8)&0x1;
    pSmiVlan4kEntry->mbr_ext_1_2 = (pUserVlan4kEntry->mbr >> 9)&0x3;
    pSmiVlan4kEntry->untag      = pUserVlan4kEntry->untag&0xff;
    pSmiVlan4kEntry->untagset_ext   =   (pUserVlan4kEntry->untag >> 8)&0x7;
    pSmiVlan4kEntry->fid_msti   = pUserVlan4kEntry->fid_msti;
    pSmiVlan4kEntry->vbpen      = pUserVlan4kEntry->vbpen;
    pSmiVlan4kEntry->vbpri      = pUserVlan4kEntry->vbpri;
    pSmiVlan4kEntry->envlanpol  = pUserVlan4kEntry->envlanpol;
    pSmiVlan4kEntry->meteridx   = pUserVlan4kEntry->meteridx & 0x1f;
    pSmiVlan4kEntry->mtr_idx_ext = (pUserVlan4kEntry->meteridx >> 5) & 0x1;
    pSmiVlan4kEntry->ivl_svl    = pUserVlan4kEntry->ivl_svl;
}


/* Function Name:
 *      rtl8367c_setAsicVlan4kEntry
 * Description:
 *      Set VID mapped entry to 4K VLAN table
 * Input:
 *      pVlan4kEntry - 4K VLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameter
 *      RT_ERR_L2_FID               - Invalid FID
 *      RT_ERR_VLAN_VID             - Invalid VID parameter (0~4095)
 *      RT_ERR_PORT_MASK            - Invalid portmask
 *      RT_ERR_FILTER_METER_ID      - Invalid meter
 *      RT_ERR_QOS_INT_PRIORITY     - Invalid priority
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicVlan4kEntry(rtl8367c_user_vlan4kentry *pVlan4kEntry )
{
    rtl8367c_vlan4kentrysmi vlan_4k_entry;
    rtk_uint32                  page_idx;
    rtk_uint16                  *tableAddr;
    ret_t                   retVal;
    rtk_uint32                  regData;

    if(pVlan4kEntry->vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    if(pVlan4kEntry->mbr > RTL8367C_PORTMASK)
        return RT_ERR_PORT_MASK;

    if(pVlan4kEntry->untag > RTL8367C_PORTMASK)
        return RT_ERR_PORT_MASK;

    if(pVlan4kEntry->fid_msti > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    if(pVlan4kEntry->meteridx > RTL8367C_METERMAX)
        return RT_ERR_FILTER_METER_ID;

    if(pVlan4kEntry->vbpri > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    memset(&vlan_4k_entry, 0x00, sizeof(rtl8367c_vlan4kentrysmi));
    _rtl8367c_Vlan4kStUser2Smi(pVlan4kEntry, &vlan_4k_entry);

    /* Prepare Data */
    tableAddr = (rtk_uint16 *)&vlan_4k_entry;
    for(page_idx = 0; page_idx < (sizeof(rtl8367c_vlan4kentrysmi) / 2); page_idx++)
    {
        regData = *tableAddr;
        retVal = rtl8367c_setAsicReg(RTL8367C_TABLE_ACCESS_WRDATA_BASE + page_idx, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        tableAddr++;
    }

    /* Write Address (VLAN_ID) */
    regData = pVlan4kEntry->vid;
    retVal = rtl8367c_setAsicReg(RTL8367C_TABLE_ACCESS_ADDR_REG, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /* Write Command */
    retVal = rtl8367c_setAsicRegBits(RTL8367C_TABLE_ACCESS_CTRL_REG, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK,RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_WRITE,TB_TARGET_CVLAN));
    if(retVal != RT_ERR_OK)
        return retVal;

#if defined(CONFIG_RTL8367C_ASICDRV_TEST)
    memcpy(&Rtl8370sVirtualVlanTable[pVlan4kEntry->vid], &vlan_4k_entry, sizeof(rtl8367c_vlan4kentrysmi));
#endif

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicVlanPortBasedVID
 * Description:
 *      Set port based VID which is indexed to 32 VLAN member configurations
 * Input:
 *      port    - Physical port number (0~10)
 *      index   - Index to VLAN member configuration
 *      pri     - 1Q Port based VLAN priority
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number
 *      RT_ERR_QOS_INT_PRIORITY     - Invalid priority
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - Invalid VLAN member configuration index
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicVlanPortBasedVID(rtk_uint32 port, rtk_uint32 index, rtk_uint32 pri)
{
    rtk_uint32 regAddr, bit_mask;
    ret_t  retVal;

    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(index > RTL8367C_CVIDXMAX)
        return RT_ERR_VLAN_ENTRY_NOT_FOUND;

    if(pri > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    regAddr = RTL8367C_VLAN_PVID_CTRL_REG(port);
    bit_mask = RTL8367C_PORT_VIDX_MASK(port);
    retVal = rtl8367c_setAsicRegBits(regAddr, bit_mask, index);
    if(retVal != RT_ERR_OK)
        return retVal;

    regAddr = RTL8367C_VLAN_PORTBASED_PRIORITY_REG(port);
    bit_mask = RTL8367C_VLAN_PORTBASED_PRIORITY_MASK(port);
    retVal = rtl8367c_setAsicRegBits(regAddr, bit_mask, pri);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicVlanIngressFilter
 * Description:
 *      Set VLAN Ingress Filter
 * Input:
 *      port        - Physical port number (0~10)
 *      enabled     - Enable or disable Ingress filter
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicVlanIngressFilter(rtk_uint32 port, rtk_uint32 enabled)
{
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    return rtl8367c_setAsicRegBit(RTL8367C_VLAN_INGRESS_REG, port, enabled);
}

/* Function Name:
 *      rtl8367c_setAsicVlanFilter
 * Description:
 *      Set enable CVLAN filtering function
 * Input:
 *      enabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicVlanFilter(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_VLAN_CTRL, RTL8367C_VLAN_CTRL_OFFSET, enabled);
}

/* Function Name:
 *      rtl8367c_setAsicVlanEgressTagMode
 * Description:
 *      Set CVLAN egress tag mode
 * Input:
 *      port        - Physical port number (0~10)
 *      tagMode     - The egress tag mode. Including Original mode, Keep tag mode and Priority tag mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_INPUT    - Invalid input parameter
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicVlanEgressTagMode(rtk_uint32 port, rtl8367c_egtagmode tagMode)
{
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(tagMode >= EG_TAG_MODE_END)
        return RT_ERR_INPUT;

    return rtl8367c_setAsicRegBits(RTL8367C_PORT_MISC_CFG_REG(port), RTL8367C_VLAN_EGRESS_MDOE_MASK, tagMode);
}

/* Function Name:
 *      rtk_vlan_init
 * Description:
 *      Initialize VLAN.
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      VLAN is disabled by default. User has to call this API to enable VLAN before
 *      using it. And It will set a default VLAN(vid 1) including all ports and set
 *      all ports PVID to the default VLAN.
 */
rtk_api_ret_t rtk_vlan_init(void)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtl8367c_user_vlan4kentry vlan4K;
    rtl8367c_vlanconfiguser vlanMC;

    /* Clean Database */
    memset(vlan_mbrCfgVid, 0x00, sizeof(rtk_vlan_t) * RTL8367C_CVIDXNO);
    memset(vlan_mbrCfgUsage, 0x00, sizeof(vlan_mbrCfgType_t) * RTL8367C_CVIDXNO);

    /* clean 32 VLAN member configuration */
    for (i = 0; i <= RTL8367C_CVIDXMAX; i++)
    {
        vlanMC.evid = 0;
        vlanMC.mbr = 0;
        vlanMC.fid_msti = 0;
        vlanMC.envlanpol = 0;
        vlanMC.meteridx = 0;
        vlanMC.vbpen = 0;
        vlanMC.vbpri = 0;
        if ((retVal = rtl8367c_setAsicVlanMemberConfig(i, &vlanMC)) != RT_ERR_OK)
            return retVal;
    }

    /* Set a default VLAN with vid 1 to 4K table for all ports */
    memset(&vlan4K, 0, sizeof(rtl8367c_user_vlan4kentry));
    vlan4K.vid = 1;
    vlan4K.mbr = RTK_PHY_PORTMASK_ALL;
    vlan4K.untag = RTK_PHY_PORTMASK_ALL;
    vlan4K.fid_msti = 0;
    if ((retVal = rtl8367c_setAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
        return retVal;

    /* Also set the default VLAN to 32 member configuration index 0 */
    memset(&vlanMC, 0, sizeof(rtl8367c_vlanconfiguser));
    vlanMC.evid = 1;
    vlanMC.mbr = RTK_PHY_PORTMASK_ALL;
    vlanMC.fid_msti = 0;
    if ((retVal = rtl8367c_setAsicVlanMemberConfig(0, &vlanMC)) != RT_ERR_OK)
            return retVal;

    /* Set all ports PVID to default VLAN and tag-mode to original */
    RTK_SCAN_ALL_PHY_PORTMASK(i)
    {
        if ((retVal = rtl8367c_setAsicVlanPortBasedVID(i, 0, 0)) != RT_ERR_OK)
            return retVal;
        if ((retVal = rtl8367c_setAsicVlanEgressTagMode(i, EG_TAG_MODE_ORI)) != RT_ERR_OK)
            return retVal;
    }

    /* Updata Databse */
    vlan_mbrCfgUsage[0] = MBRCFG_USED_BY_VLAN;
    vlan_mbrCfgVid[0] = 1;

    /* Enable Ingress filter */
    RTK_SCAN_ALL_PHY_PORTMASK(i)
    {
        if ((retVal = rtl8367c_setAsicVlanIngressFilter(i, ENABLED)) != RT_ERR_OK)
            return retVal;
    }

    /* enable VLAN */
    if ((retVal = rtl8367c_setAsicVlanFilter(ENABLED)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_isPortMaskValid
 * Description:
 *      Check portmask is valid or not
 * Input:
 *      pPmask       - logical port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - port mask is valid
 *      RT_ERR_FAILED       - port mask is not valid
 *      RT_ERR_NOT_INIT     - Not Initialize
 *      RT_ERR_NULL_POINTER - Null pointer
 * Note:
 *
 */
rtk_api_ret_t rtk_switch_isPortMaskValid(rtk_portmask_t *pPmask)
{
    if(NULL == pPmask)
        return RT_ERR_NULL_POINTER;

    if( (pPmask->bits[0] | halCtrl.valid_portmask) != halCtrl.valid_portmask )
        return RT_ERR_FAILED;
    else
        return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_portmask_L2P_get
 * Description:
 *      Get physicl portmask from logical portmask
 * Input:
 *      pLogicalPmask       - logical port mask
 * Output:
 *      pPhysicalPortmask   - physical port mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_NOT_INIT     - Not Initialize
 *      RT_ERR_NULL_POINTER - Null pointer
 *      RT_ERR_PORT_MASK    - Error port mask
 * Note:
 *
 */
rtk_api_ret_t rtk_switch_portmask_L2P_get(rtk_portmask_t *pLogicalPmask, rtk_uint32 *pPhysicalPortmask)
{
    rtk_uint32 log_port, phy_port;

    if(NULL == pLogicalPmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pPhysicalPortmask)
        return RT_ERR_NULL_POINTER;

    if(rtk_switch_isPortMaskValid(pLogicalPmask) != RT_ERR_OK)
        return RT_ERR_PORT_MASK;

    /* reset physical port mask */
    *pPhysicalPortmask = 0;

    RTK_PORTMASK_SCAN((*pLogicalPmask), log_port)
    {
        phy_port = rtk_switch_port_L2P_get((rtk_port_t)log_port);
        *pPhysicalPortmask |= (0x0001 << phy_port);
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_set
 * Description:
 *      Set a VLAN entry.
 * Input:
 *      vid - VLAN ID to configure.
 *      pVlanCfg - VLAN Configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameters.
 *      RT_ERR_L2_FID               - Invalid FID.
 *      RT_ERR_VLAN_PORT_MBR_EXIST  - Invalid member port mask.
 *      RT_ERR_VLAN_VID             - Invalid VID parameter.
 * Note:
 *
 */
rtk_api_ret_t rtk_vlan_set(rtk_vlan_t vid, rtk_vlan_cfg_t *pVlanCfg)
{
    rtk_api_ret_t retVal;
    rtk_uint32 phyMbrPmask;
    rtk_uint32 phyUntagPmask;
    rtl8367c_user_vlan4kentry vlan4K;
    rtl8367c_vlanconfiguser vlanMC;
    rtk_uint32 idx;
    rtk_uint32 empty_index = 0xffff;
    rtk_uint32 update_evid = 0;

    /* vid must be 0~8191 */
    if (vid > RTL8367C_EVIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pVlanCfg)
        return RT_ERR_NULL_POINTER;

    /* IVL_EN */
    if(pVlanCfg->ivl_en >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    /* fid must be 0~15 */
    if(pVlanCfg->fid_msti > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    /* Policing */
    if(pVlanCfg->envlanpol >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    /* Meter ID */
    if(pVlanCfg->meteridx > RTK_MAX_METER_ID)
        return RT_ERR_INPUT;

    /* VLAN based priority */
    if(pVlanCfg->vbpen >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    /* Priority */
    if(pVlanCfg->vbpri > RTL8367C_PRIMAX)
        return RT_ERR_INPUT;

    /* Get physical port mask */
    if(rtk_switch_portmask_L2P_get(&(pVlanCfg->mbr), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if(rtk_switch_portmask_L2P_get(&(pVlanCfg->untag), &phyUntagPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if (vid <= RTL8367C_VIDMAX)
    {
        /* update 4K table */
        memset(&vlan4K, 0, sizeof(rtl8367c_user_vlan4kentry));
        vlan4K.vid = vid;

        vlan4K.mbr    = (phyMbrPmask & 0xFFFF);
        vlan4K.untag  = (phyUntagPmask & 0xFFFF);

        vlan4K.ivl_svl      = pVlanCfg->ivl_en;
        vlan4K.fid_msti     = pVlanCfg->fid_msti;
        vlan4K.envlanpol    = pVlanCfg->envlanpol;
        vlan4K.meteridx     = pVlanCfg->meteridx;
        vlan4K.vbpen        = pVlanCfg->vbpen;
        vlan4K.vbpri        = pVlanCfg->vbpri;

        if ((retVal = rtl8367c_setAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
            return retVal;

        /* Update Member configuration if exist */
        for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
        {
            if(vlan_mbrCfgUsage[idx] == MBRCFG_USED_BY_VLAN)
            {
                if(vlan_mbrCfgVid[idx] == vid)
                {
                    /* Found! Update */
                    if(phyMbrPmask == 0x00)
                    {
                        /* Member port = 0x00, delete this VLAN from Member Configuration */
                        memset(&vlanMC, 0x00, sizeof(rtl8367c_vlanconfiguser));
                        if ((retVal = rtl8367c_setAsicVlanMemberConfig(idx, &vlanMC)) != RT_ERR_OK)
                            return retVal;

                        /* Clear Database */
                        vlan_mbrCfgUsage[idx] = MBRCFG_UNUSED;
                        vlan_mbrCfgVid[idx]   = 0;
                    }
                    else
                    {
                        /* Normal VLAN config, update to member configuration */
                        vlanMC.evid = vid;
                        vlanMC.mbr = vlan4K.mbr;
                        vlanMC.fid_msti = vlan4K.fid_msti;
                        vlanMC.meteridx = vlan4K.meteridx;
                        vlanMC.envlanpol= vlan4K.envlanpol;
                        vlanMC.vbpen = vlan4K.vbpen;
                        vlanMC.vbpri = vlan4K.vbpri;
                        if ((retVal = rtl8367c_setAsicVlanMemberConfig(idx, &vlanMC)) != RT_ERR_OK)
                            return retVal;
                    }

                    break;
                }
            }
        }
    }
    else
    {
        /* vid > 4095 */
        for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
        {
            if(vlan_mbrCfgUsage[idx] == MBRCFG_USED_BY_VLAN)
            {
                if(vlan_mbrCfgVid[idx] == vid)
                {
                    /* Found! Update */
                    if(phyMbrPmask == 0x00)
                    {
                        /* Member port = 0x00, delete this VLAN from Member Configuration */
                        memset(&vlanMC, 0x00, sizeof(rtl8367c_vlanconfiguser));
                        if ((retVal = rtl8367c_setAsicVlanMemberConfig(idx, &vlanMC)) != RT_ERR_OK)
                            return retVal;

                        /* Clear Database */
                        vlan_mbrCfgUsage[idx] = MBRCFG_UNUSED;
                        vlan_mbrCfgVid[idx]   = 0;
                    }
                    else
                    {
                        /* Normal VLAN config, update to member configuration */
                        vlanMC.evid = vid;
                        vlanMC.mbr = phyMbrPmask;
                        vlanMC.fid_msti = pVlanCfg->fid_msti;
                        vlanMC.meteridx = pVlanCfg->meteridx;
                        vlanMC.envlanpol= pVlanCfg->envlanpol;
                        vlanMC.vbpen = pVlanCfg->vbpen;
                        vlanMC.vbpri = pVlanCfg->vbpri;
                        if ((retVal = rtl8367c_setAsicVlanMemberConfig(idx, &vlanMC)) != RT_ERR_OK)
                            return retVal;

                        break;
                    }

                    update_evid = 1;
                }
            }

            if(vlan_mbrCfgUsage[idx] == MBRCFG_UNUSED)
            {
                if(0xffff == empty_index)
                    empty_index = idx;
            }
        }

        /* doesn't find out same EVID entry and there is empty index in member configuration */
        if( (phyMbrPmask != 0x00) && (update_evid == 0) && (empty_index != 0xFFFF) )
        {
            vlanMC.evid = vid;
            vlanMC.mbr = phyMbrPmask;
            vlanMC.fid_msti = pVlanCfg->fid_msti;
            vlanMC.meteridx = pVlanCfg->meteridx;
            vlanMC.envlanpol= pVlanCfg->envlanpol;
            vlanMC.vbpen = pVlanCfg->vbpen;
            vlanMC.vbpri = pVlanCfg->vbpri;
            if ((retVal = rtl8367c_setAsicVlanMemberConfig(empty_index, &vlanMC)) != RT_ERR_OK)
                return retVal;

            vlan_mbrCfgUsage[empty_index] = MBRCFG_USED_BY_VLAN;
            vlan_mbrCfgVid[empty_index] = vid;

        }
    }

    return RT_ERR_OK;
}

void _rtl8367c_Vlan4kStSmi2User(rtl8367c_vlan4kentrysmi *pSmiVlan4kEntry, rtl8367c_user_vlan4kentry *pUserVlan4kEntry)
{
    rtk_uint16 tmp;

    tmp = pSmiVlan4kEntry->mbr_ext_1_2 & 0x3;
    tmp = (tmp << 1)| pSmiVlan4kEntry->mbr_ext_0;
    pUserVlan4kEntry->mbr       = (tmp << 8) | pSmiVlan4kEntry->mbr;

    tmp = pSmiVlan4kEntry->untagset_ext;
    pUserVlan4kEntry->untag     = (tmp << 8) | pSmiVlan4kEntry->untag;
    pUserVlan4kEntry->fid_msti  = pSmiVlan4kEntry->fid_msti;
    pUserVlan4kEntry->vbpen     = pSmiVlan4kEntry->vbpen;
    pUserVlan4kEntry->vbpri     = pSmiVlan4kEntry->vbpri;
    pUserVlan4kEntry->envlanpol = pSmiVlan4kEntry->envlanpol;

    tmp = pSmiVlan4kEntry->mtr_idx_ext & 0x1;
    pUserVlan4kEntry->meteridx  = (tmp << 5) | pSmiVlan4kEntry->meteridx;
    pUserVlan4kEntry->ivl_svl   = pSmiVlan4kEntry->ivl_svl;
}


/* Function Name:
 *      rtl8367c_getAsicVlan4kEntry
 * Description:
 *      Get VID mapped entry to 4K VLAN table
 * Input:
 *      pVlan4kEntry - 4K VLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_VID         - Invalid VID parameter (0~4095)
 *      RT_ERR_BUSYWAIT_TIMEOUT - LUT is busy at retrieving
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicVlan4kEntry(rtl8367c_user_vlan4kentry *pVlan4kEntry )
{
    rtl8367c_vlan4kentrysmi     vlan_4k_entry;
    rtk_uint32                  page_idx;
    rtk_uint16                  *tableAddr;
    ret_t                       retVal;
    rtk_uint32                  regData;
    rtk_uint32                  busyCounter;

    if(pVlan4kEntry->vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Polling status */
    busyCounter = RTL8367C_VLAN_BUSY_CHECK_NO;
    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(RTL8367C_TABLE_ACCESS_STATUS_REG, RTL8367C_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    /* Write Address (VLAN_ID) */
    regData = pVlan4kEntry->vid;
    retVal = rtl8367c_setAsicReg(RTL8367C_TABLE_ACCESS_ADDR_REG, regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    /* Read Command */
    retVal = rtl8367c_setAsicRegBits(RTL8367C_TABLE_ACCESS_CTRL_REG, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK, RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_READ,TB_TARGET_CVLAN));
    if(retVal != RT_ERR_OK)
        return retVal;

    /* Polling status */
    busyCounter = RTL8367C_VLAN_BUSY_CHECK_NO;
    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(RTL8367C_TABLE_ACCESS_STATUS_REG, RTL8367C_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        if(regData == 0)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    /* Read VLAN data from register */
    tableAddr = (rtk_uint16 *)&vlan_4k_entry;
    for(page_idx = 0; page_idx < (sizeof(rtl8367c_vlan4kentrysmi) / 2); page_idx++)
    {
        retVal = rtl8367c_getAsicReg(RTL8367C_TABLE_ACCESS_RDDATA_BASE + page_idx, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *tableAddr = regData;
        tableAddr++;
    }

    _rtl8367c_Vlan4kStSmi2User(&vlan_4k_entry, pVlan4kEntry);

#if defined(CONFIG_RTL8367C_ASICDRV_TEST)
    _rtl8367c_Vlan4kStSmi2User(&Rtl8370sVirtualVlanTable[pVlan4kEntry->vid], pVlan4kEntry);
#endif

    return RT_ERR_OK;
}

void _rtl8367c_VlanMCStSmi2User(rtl8367c_vlanconfigsmi *pSmiVlanCfg, rtl8367c_vlanconfiguser *pVlanCg)
{
    pVlanCg->mbr            = pSmiVlanCfg->mbr;
    pVlanCg->fid_msti       = pSmiVlanCfg->fid_msti;
    pVlanCg->evid           = pSmiVlanCfg->evid;
    pVlanCg->meteridx       = pSmiVlanCfg->meteridx;
    pVlanCg->envlanpol      = pSmiVlanCfg->envlanpol;
    pVlanCg->vbpri          = pSmiVlanCfg->vbpri;
    pVlanCg->vbpen          = pSmiVlanCfg->vbpen;
}

/* Function Name:
 *      rtl8367c_getAsicVlanMemberConfig
 * Description:
 *      Get 32 VLAN member configurations
 * Input:
 *      index       - VLAN member configuration index (0~31)
 *      pVlanCg - VLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - Success
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_INPUT                - Invalid input parameter
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - Invalid VLAN member configuration index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicVlanMemberConfig(rtk_uint32 index, rtl8367c_vlanconfiguser *pVlanCg)
{
    ret_t  retVal;
    rtk_uint32 page_idx;
    rtk_uint32 regAddr;
    rtk_uint32 regData;
    rtk_uint16 *tableAddr;
    rtl8367c_vlanconfigsmi  smi_vlancfg;

    if(index > RTL8367C_CVIDXMAX)
        return RT_ERR_VLAN_ENTRY_NOT_FOUND;

    memset(&smi_vlancfg, 0x00, sizeof(rtl8367c_vlanconfigsmi));
    tableAddr  = (rtk_uint16*)&smi_vlancfg;

    for(page_idx = 0; page_idx < 4; page_idx++)  /* 4 pages per VLAN Member Config */
    {
        regAddr = RTL8367C_VLAN_MEMBER_CONFIGURATION_BASE + (index * 4) + page_idx;

        retVal = rtl8367c_getAsicReg(regAddr, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *tableAddr = (rtk_uint16)regData;
        tableAddr++;
    }

    _rtl8367c_VlanMCStSmi2User(&smi_vlancfg, pVlanCg);
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_checkAndCreateMbr
 * Description:
 *      Check and create Member configuration and return index
 * Input:
 *      vid  - VLAN id.
 * Output:
 *      pIndex  - Member configuration index
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_VLAN_VID     - Invalid VLAN ID.
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - VLAN not found
 *      RT_ERR_TBL_FULL     - Member Configuration table full
 * Note:
 *
 */
rtk_api_ret_t rtk_vlan_checkAndCreateMbr(rtk_vlan_t vid, rtk_uint32 *pIndex)
{
    rtk_api_ret_t retVal;
    rtl8367c_user_vlan4kentry vlan4K;
    rtl8367c_vlanconfiguser vlanMC;
    rtk_uint32 idx;
    rtk_uint32 empty_idx = 0xFFFF;

    /* vid must be 0~8191 */
    if (vid > RTL8367C_EVIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pIndex)
        return RT_ERR_NULL_POINTER;

    /* Get 4K VLAN */
    if (vid <= RTL8367C_VIDMAX)
    {
        memset(&vlan4K, 0x00, sizeof(rtl8367c_user_vlan4kentry));
        vlan4K.vid = vid;
        if ((retVal = rtl8367c_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
            return retVal;
    }

    /* Search exist entry */
    for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
    {
        if(vlan_mbrCfgUsage[idx] == MBRCFG_USED_BY_VLAN)
        {
            if(vlan_mbrCfgVid[idx] == vid)
            {
                /* Found! return index */
                *pIndex = idx;
                return RT_ERR_OK;
            }
        }
    }

    /* Not found, Read H/W Member Configuration table to update database */
    for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
    {
        if ((retVal = rtl8367c_getAsicVlanMemberConfig(idx, &vlanMC)) != RT_ERR_OK)
            return retVal;

        if( (vlanMC.evid == 0) && (vlanMC.mbr == 0x00))
        {
            vlan_mbrCfgUsage[idx]   = MBRCFG_UNUSED;
            vlan_mbrCfgVid[idx]     = 0;
        }
        else
        {
            vlan_mbrCfgUsage[idx]   = MBRCFG_USED_BY_VLAN;
            vlan_mbrCfgVid[idx]     = vlanMC.evid;
        }
    }

    /* Search exist entry again */
    for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
    {
        if(vlan_mbrCfgUsage[idx] == MBRCFG_USED_BY_VLAN)
        {
            if(vlan_mbrCfgVid[idx] == vid)
            {
                /* Found! return index */
                *pIndex = idx;
                return RT_ERR_OK;
            }
        }
    }

    /* try to look up an empty index */
    for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
    {
        if(vlan_mbrCfgUsage[idx] == MBRCFG_UNUSED)
        {
            empty_idx = idx;
            break;
        }
    }

    if(empty_idx == 0xFFFF)
    {
        /* No empty index */
        return RT_ERR_TBL_FULL;
    }

    if (vid > RTL8367C_VIDMAX)
    {
        /* > 4K, there is no 4K entry, create on member configuration directly */
        memset(&vlanMC, 0x00, sizeof(rtl8367c_vlanconfiguser));
        vlanMC.evid = vid;
        if ((retVal = rtl8367c_setAsicVlanMemberConfig(empty_idx, &vlanMC)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        /* Copy from 4K table */
        vlanMC.evid = vid;
        vlanMC.mbr = vlan4K.mbr;
        vlanMC.fid_msti = vlan4K.fid_msti;
        vlanMC.meteridx= vlan4K.meteridx;
        vlanMC.envlanpol= vlan4K.envlanpol;
        vlanMC.vbpen = vlan4K.vbpen;
        vlanMC.vbpri = vlan4K.vbpri;
        if ((retVal = rtl8367c_setAsicVlanMemberConfig(empty_idx, &vlanMC)) != RT_ERR_OK)
            return retVal;
    }

    /* Update Database */
    vlan_mbrCfgUsage[empty_idx] = MBRCFG_USED_BY_VLAN;
    vlan_mbrCfgVid[empty_idx] = vid;

    *pIndex = empty_idx;
    return RT_ERR_OK;
}

/* Function Name:
 *     rtk_vlan_portPvid_set
 * Description:
 *      Set port to specified VLAN ID(PVID).
 * Input:
 *      port - Port id.
 *      pvid - Specified VLAN ID.
 *      priority - 802.1p priority for the PVID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                   - OK
 *      RT_ERR_FAILED               - Failed
 *      RT_ERR_SMI                  - SMI access error
 *      RT_ERR_PORT_ID              - Invalid port number.
 *      RT_ERR_VLAN_PRIORITY        - Invalid priority.
 *      RT_ERR_VLAN_ENTRY_NOT_FOUND - VLAN entry not found.
 *      RT_ERR_VLAN_VID             - Invalid VID parameter.
 * Note:
 *       The API is used for Port-based VLAN. The untagged frame received from the
 *       port will be classified to the specified VLAN and assigned to the specified priority.
 */
rtk_api_ret_t rtk_vlan_portPvid_set(rtk_port_t port, rtk_vlan_t pvid, rtk_pri_t priority)
{
    rtk_api_ret_t retVal;
    rtk_uint32 index;

    /* vid must be 0~8191 */
    if (pvid > RTL8367C_EVIDMAX)
        return RT_ERR_VLAN_VID;

    /* priority must be 0~7 */
    if (priority > RTL8367C_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if((retVal = rtk_vlan_checkAndCreateMbr(pvid, &index)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicVlanPortBasedVID(rtk_switch_port_L2P_get(port), index, priority)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_portmask_P2L_get
 * Description:
 *      Get logical portmask from physical portmask
 * Input:
 *      physicalPortmask    - physical port mask
 * Output:
 *      pLogicalPmask       - logical port mask
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_NOT_INIT     - Not Initialize
 *      RT_ERR_NULL_POINTER - Null pointer
 *      RT_ERR_PORT_MASK    - Error port mask
 * Note:
 *
 */
rtk_api_ret_t rtk_switch_portmask_P2L_get(rtk_uint32 physicalPortmask, rtk_portmask_t *pLogicalPmask)
{
    rtk_uint32 log_port, phy_port;

    if(NULL == pLogicalPmask)
        return RT_ERR_NULL_POINTER;

    RTK_PORTMASK_CLEAR(*pLogicalPmask);

    for(phy_port = halCtrl.min_phy_port; phy_port <= halCtrl.max_phy_port; phy_port++)
    {
        if(physicalPortmask & (0x0001 << phy_port))
        {
            log_port = rtk_switch_port_P2L_get(phy_port);
            if(log_port != UNDEFINE_PORT)
            {
                RTK_PORTMASK_PORT_SET(*pLogicalPmask, log_port);
            }
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_get
 * Description:
 *      Get a VLAN entry.
 * Input:
 *      vid - VLAN ID to configure.
 * Output:
 *      pVlanCfg - VLAN Configuration
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 * Note:
 *
 */
rtk_api_ret_t rtk_vlan_get(rtk_vlan_t vid, rtk_vlan_cfg_t *pVlanCfg)
{
    rtk_api_ret_t retVal;
    rtk_uint32 phyMbrPmask;
    rtk_uint32 phyUntagPmask;
    rtl8367c_user_vlan4kentry vlan4K;
    rtl8367c_vlanconfiguser vlanMC;
    rtk_uint32 idx;

    /* vid must be 0~8191 */
    if (vid > RTL8367C_EVIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pVlanCfg)
        return RT_ERR_NULL_POINTER;

    if (vid <= RTL8367C_VIDMAX)
    {
        vlan4K.vid = vid;

        if ((retVal = rtl8367c_getAsicVlan4kEntry(&vlan4K)) != RT_ERR_OK)
            return retVal;

        phyMbrPmask   = vlan4K.mbr;
        phyUntagPmask = vlan4K.untag;
        if(rtk_switch_portmask_P2L_get(phyMbrPmask, &(pVlanCfg->mbr)) != RT_ERR_OK)
            return RT_ERR_FAILED;

        if(rtk_switch_portmask_P2L_get(phyUntagPmask, &(pVlanCfg->untag)) != RT_ERR_OK)
            return RT_ERR_FAILED;

        pVlanCfg->ivl_en    = vlan4K.ivl_svl;
        pVlanCfg->fid_msti  = vlan4K.fid_msti;
        pVlanCfg->envlanpol = vlan4K.envlanpol;
        pVlanCfg->meteridx  = vlan4K.meteridx;
        pVlanCfg->vbpen     = vlan4K.vbpen;
        pVlanCfg->vbpri     = vlan4K.vbpri;
    }
    else
    {
        for (idx = 0; idx <= RTL8367C_CVIDXMAX; idx++)
        {
            if(vlan_mbrCfgUsage[idx] == MBRCFG_USED_BY_VLAN)
            {
                if(vlan_mbrCfgVid[idx] == vid)
                {
                    if ((retVal = rtl8367c_getAsicVlanMemberConfig(idx, &vlanMC)) != RT_ERR_OK)
                        return retVal;

                    phyMbrPmask   = vlanMC.mbr;
                    if(rtk_switch_portmask_P2L_get(phyMbrPmask, &(pVlanCfg->mbr)) != RT_ERR_OK)
                        return RT_ERR_FAILED;

                    pVlanCfg->untag.bits[0] = 0;
                    pVlanCfg->ivl_en    = 0;
                    pVlanCfg->fid_msti  = vlanMC.fid_msti;
                    pVlanCfg->envlanpol = vlanMC.envlanpol;
                    pVlanCfg->meteridx  = vlanMC.meteridx;
                    pVlanCfg->vbpen     = vlanMC.vbpen;
                    pVlanCfg->vbpri     = vlanMC.vbpri;
                }
            }
        }
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_getAsicMIBsCounter
 * Description:
 *      Get MIBs counter
 * Input:
 *      port        - Physical port number (0~7)
 *      mibIdx      - MIB counter index
 *      pCounter    - MIB retrived counter
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number
 *      RT_ERR_BUSYWAIT_TIMEOUT - MIB is busy at retrieving
 *      RT_ERR_STAT_CNTR_FAIL   - MIB is resetting
 * Note:
 *      Before MIBs counter retrieving, writting accessing address to ASIC at first and check the MIB
 *      control register status. If busy bit of MIB control is set, that means MIB counter have been
 *      waiting for preparing, then software must wait atfer this busy flag reset by ASIC. This driver
 *      did not recycle reading user desired counter. Software must use driver again to get MIB counter
 *      if return value is not RT_ERR_OK.
 */
ret_t rtl8367c_getAsicMIBsCounter(rtk_uint32 port, RTL8367C_MIBCOUNTER mibIdx, rtk_uint64* pCounter)
{
    ret_t retVal;
    rtk_uint32 regAddr;
    rtk_uint32 regData;
    rtk_uint32 mibAddr;
    rtk_uint32 mibOff=0;
    rtk_uint16 i;
    rtk_uint64 mibCounter;

    /* address offset to MIBs counter */
    const rtk_uint16 mibLength[RTL8367C_MIBS_NUMBER] = {
        4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        4,2,2,2,2,2,2,2,2,
        4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(mibIdx >= RTL8367C_MIBS_NUMBER)
        return RT_ERR_STAT_INVALID_CNTR;

    if(dot1dTpLearnedEntryDiscards == mibIdx)
    {
        mibAddr = RTL8367C_MIB_LEARNENTRYDISCARD_OFFSET;
    }
    else
    {
        i = 0;
        mibOff = RTL8367C_MIB_PORT_OFFSET * port;

        if(port > 7)
            mibOff = mibOff + 68;

        while(i < mibIdx)
        {
            mibOff += mibLength[i];
            i++;
        }

        mibAddr = mibOff;
    }


    /*writing access counter address first*/
    /*This address is SRAM address, and SRAM address = MIB register address >> 2*/
    /*then ASIC will prepare 64bits counter wait for being retrived*/
    /*Write Mib related address to access control register*/
    retVal = rtl8367c_setAsicReg(RTL8367C_REG_MIB_ADDRESS, (mibAddr >> 2));
    if(retVal != RT_ERR_OK)
        return retVal;



    /* polling busy flag */
    i = 100;
    while(i > 0)
    {
        /*read MIB control register*/
        retVal = rtl8367c_getAsicReg(RTL8367C_MIB_CTRL_REG,&regData);

        if((regData & RTL8367C_MIB_CTRL0_BUSY_FLAG_MASK) == 0)
        {
            break;
        }

        i--;
    }

    if(regData & RTL8367C_MIB_CTRL0_BUSY_FLAG_MASK)
        return RT_ERR_BUSYWAIT_TIMEOUT;

    if(regData & RTL8367C_RESET_FLAG_MASK)
        return RT_ERR_STAT_CNTR_FAIL;

    mibCounter = 0;
    i = mibLength[mibIdx];
    if(4 == i)
        regAddr = RTL8367C_MIB_COUNTER_BASE_REG + 3;
    else
        regAddr = RTL8367C_MIB_COUNTER_BASE_REG + ((mibOff + 1) % 4);

    while(i)
    {
        retVal = rtl8367c_getAsicReg(regAddr, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        mibCounter = (mibCounter << 16) | (regData & 0xFFFF);

        regAddr --;
        i --;

    }

    *pCounter = mibCounter;

    return RT_ERR_OK;
}


#define MIB_NOT_SUPPORT     (0xFFFF)
static rtk_api_ret_t _get_asic_mib_idx(rtk_stat_port_type_t cnt_idx, RTL8367C_MIBCOUNTER *pMib_idx)
{
    RTL8367C_MIBCOUNTER mib_asic_idx[STAT_PORT_CNTR_END] =
    {
        ifInOctets,                     /* STAT_IfInOctets */
        dot3StatsFCSErrors,             /* STAT_Dot3StatsFCSErrors */
        dot3StatsSymbolErrors,          /* STAT_Dot3StatsSymbolErrors */
        dot3InPauseFrames,              /* STAT_Dot3InPauseFrames */
        dot3ControlInUnknownOpcodes,    /* STAT_Dot3ControlInUnknownOpcodes */
        etherStatsFragments,            /* STAT_EtherStatsFragments */
        etherStatsJabbers,              /* STAT_EtherStatsJabbers */
        ifInUcastPkts,                  /* STAT_IfInUcastPkts */
        etherStatsDropEvents,           /* STAT_EtherStatsDropEvents */
        etherStatsOctets,               /* STAT_EtherStatsOctets */
        etherStatsUnderSizePkts,        /* STAT_EtherStatsUnderSizePkts */
        etherOversizeStats,             /* STAT_EtherOversizeStats */
        etherStatsPkts64Octets,         /* STAT_EtherStatsPkts64Octets */
        etherStatsPkts65to127Octets,    /* STAT_EtherStatsPkts65to127Octets */
        etherStatsPkts128to255Octets,   /* STAT_EtherStatsPkts128to255Octets */
        etherStatsPkts256to511Octets,   /* STAT_EtherStatsPkts256to511Octets */
        etherStatsPkts512to1023Octets,  /* STAT_EtherStatsPkts512to1023Octets */
        etherStatsPkts1024to1518Octets, /* STAT_EtherStatsPkts1024to1518Octets */
        ifInMulticastPkts,              /* STAT_EtherStatsMulticastPkts */
        ifInBroadcastPkts,              /* STAT_EtherStatsBroadcastPkts */
        ifOutOctets,                    /* STAT_IfOutOctets */
        dot3StatsSingleCollisionFrames, /* STAT_Dot3StatsSingleCollisionFrames */
        dot3StatMultipleCollisionFrames,/* STAT_Dot3StatsMultipleCollisionFrames */
        dot3sDeferredTransmissions,     /* STAT_Dot3StatsDeferredTransmissions */
        dot3StatsLateCollisions,        /* STAT_Dot3StatsLateCollisions */
        etherStatsCollisions,           /* STAT_EtherStatsCollisions */
        dot3StatsExcessiveCollisions,   /* STAT_Dot3StatsExcessiveCollisions */
        dot3OutPauseFrames,             /* STAT_Dot3OutPauseFrames */
        MIB_NOT_SUPPORT,                /* STAT_Dot1dBasePortDelayExceededDiscards */
        dot1dTpPortInDiscards,          /* STAT_Dot1dTpPortInDiscards */
        ifOutUcastPkts,                 /* STAT_IfOutUcastPkts */
        ifOutMulticastPkts,             /* STAT_IfOutMulticastPkts */
        ifOutBroadcastPkts,             /* STAT_IfOutBroadcastPkts */
        outOampduPkts,                  /* STAT_OutOampduPkts */
        inOampduPkts,                   /* STAT_InOampduPkts */
        MIB_NOT_SUPPORT,                /* STAT_PktgenPkts */
        inMldChecksumError,             /* STAT_InMldChecksumError */
        inIgmpChecksumError,            /* STAT_InIgmpChecksumError */
        inMldSpecificQuery,             /* STAT_InMldSpecificQuery */
        inMldGeneralQuery,              /* STAT_InMldGeneralQuery */
        inIgmpSpecificQuery,            /* STAT_InIgmpSpecificQuery */
        inIgmpGeneralQuery,             /* STAT_InIgmpGeneralQuery */
        inMldLeaves,                    /* STAT_InMldLeaves */
        inIgmpLeaves,                   /* STAT_InIgmpInterfaceLeaves */
        inIgmpJoinsSuccess,             /* STAT_InIgmpJoinsSuccess */
        inIgmpJoinsFail,                /* STAT_InIgmpJoinsFail */
        inMldJoinsSuccess,              /* STAT_InMldJoinsSuccess */
        inMldJoinsFail,                 /* STAT_InMldJoinsFail */
        inReportSuppressionDrop,        /* STAT_InReportSuppressionDrop */
        inLeaveSuppressionDrop,         /* STAT_InLeaveSuppressionDrop */
        outIgmpReports,                 /* STAT_OutIgmpReports */
        outIgmpLeaves,                  /* STAT_OutIgmpLeaves */
        outIgmpGeneralQuery,            /* STAT_OutIgmpGeneralQuery */
        outIgmpSpecificQuery,           /* STAT_OutIgmpSpecificQuery */
        outMldReports,                  /* STAT_OutMldReports */
        outMldLeaves,                   /* STAT_OutMldLeaves */
        outMldGeneralQuery,             /* STAT_OutMldGeneralQuery */
        outMldSpecificQuery,            /* STAT_OutMldSpecificQuery */
        inKnownMulticastPkts,           /* STAT_InKnownMulticastPkts */
        ifInMulticastPkts,              /* STAT_IfInMulticastPkts */
        ifInBroadcastPkts,              /* STAT_IfInBroadcastPkts */
        ifOutDiscards                   /* STAT_IfOutDiscards */
    };

    if(cnt_idx >= STAT_PORT_CNTR_END)
        return RT_ERR_STAT_INVALID_PORT_CNTR;

    if(mib_asic_idx[cnt_idx] == MIB_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    *pMib_idx = mib_asic_idx[cnt_idx];
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_port_get
 * Description:
 *      Get per port MIB counter by index
 * Input:
 *      port        - port id.
 *      cntr_idx    - port counter index.
 * Output:
 *      pCntr - MIB retrived counter.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Get per port MIB counter by index definition.
 */
rtk_api_ret_t rtk_stat_port_get(rtk_port_t port, rtk_stat_port_type_t cntr_idx, rtk_stat_counter_t *pCntr)
{
    rtk_api_ret_t       retVal;
    RTL8367C_MIBCOUNTER mib_idx;
    rtk_stat_counter_t  second_cnt;

    if(NULL == pCntr)
        return RT_ERR_NULL_POINTER;

    if (cntr_idx >= STAT_PORT_CNTR_END)
        return RT_ERR_STAT_INVALID_PORT_CNTR;

    if((retVal = _get_asic_mib_idx(cntr_idx, &mib_idx)) != RT_ERR_OK)
        return retVal;

    if(mib_idx == MIB_NOT_SUPPORT)
        return RT_ERR_CHIP_NOT_SUPPORTED;

    if ((retVal = rtl8367c_getAsicMIBsCounter(rtk_switch_port_L2P_get(port), mib_idx, pCntr)) != RT_ERR_OK)
        return retVal;

    if(cntr_idx == STAT_EtherStatsMulticastPkts)
    {
        if((retVal = _get_asic_mib_idx(STAT_IfOutMulticastPkts, &mib_idx)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicMIBsCounter(rtk_switch_port_L2P_get(port), mib_idx, &second_cnt)) != RT_ERR_OK)
            return retVal;

        *pCntr += second_cnt;
    }

    if(cntr_idx == STAT_EtherStatsBroadcastPkts)
    {
        if((retVal = _get_asic_mib_idx(STAT_IfOutBroadcastPkts, &mib_idx)) != RT_ERR_OK)
            return retVal;

        if((retVal = rtl8367c_getAsicMIBsCounter(rtk_switch_port_L2P_get(port), mib_idx, &second_cnt)) != RT_ERR_OK)
            return retVal;

        *pCntr += second_cnt;
    }

    return RT_ERR_OK;
}


/* Get all counters of one specified port in the specified device. */
rtk_api_ret_t rtk_stat_port_getAll(rtk_port_t port, rtk_stat_port_cntr_t *pPort_cntrs)
{
    rtk_api_ret_t retVal;
    rtk_uint32 mibIndex;
    rtk_uint64 mibCounter;
    rtk_uint32 *accessPtr;
    /* address offset to MIBs counter */
    const rtk_uint16 mibLength[STAT_PORT_CNTR_END]= {
        2,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    if(NULL == pPort_cntrs)
        return RT_ERR_NULL_POINTER;

    accessPtr = (rtk_uint32*)pPort_cntrs;
    for (mibIndex=0; mibIndex < STAT_PORT_CNTR_END; mibIndex++)
    {
        if ((retVal = rtk_stat_port_get(port, mibIndex, &mibCounter)) != RT_ERR_OK)
        {
            if (retVal == RT_ERR_CHIP_NOT_SUPPORTED)
                mibCounter = 0;
            else
                return retVal;
        }

        if (2 == mibLength[mibIndex])
            *(rtk_uint64*)accessPtr = mibCounter;
        else if (1 == mibLength[mibIndex])
            *accessPtr = mibCounter;
        else
            return RT_ERR_FAILED;

        accessPtr += mibLength[mibIndex];
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicMIBsCounterReset
 * Description:
 *      Reset global/queue manage or per-port MIB counter
 * Input:
 *      greset  - Global reset
 *      qmreset - Queue maganement reset
 *      portmask    - Port reset mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - Success
 *      RT_ERR_SMI              - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicMIBsCounterReset(rtk_uint32 greset, rtk_uint32 qmreset, rtk_uint32 portmask)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint32 regBits;

    regBits = RTL8367C_GLOBAL_RESET_MASK |
                RTL8367C_QM_RESET_MASK |
                    RTL8367C_MIB_PORT07_MASK |
                    ((rtk_uint32)0x7 << 13);
    regData = ((greset << RTL8367C_GLOBAL_RESET_OFFSET) & RTL8367C_GLOBAL_RESET_MASK) |
                ((qmreset << RTL8367C_QM_RESET_OFFSET) & RTL8367C_QM_RESET_MASK) |
                (((portmask & 0xFF) << RTL8367C_PORT0_RESET_OFFSET) & RTL8367C_MIB_PORT07_MASK) |
                (((portmask >> 8)&0x7) << 13);


    retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_MIB_CTRL0, regBits, (regData >> RTL8367C_PORT0_RESET_OFFSET));

    return retVal;
}

/* Function Name:
 *      rtk_stat_port_reset
 * Description:
 *      Reset per port MIB counter by port.
 * Input:
 *      port - port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *
 */
rtk_api_ret_t rtk_stat_port_reset(rtk_port_t port)
{
    rtk_api_ret_t retVal;

    if ((retVal = rtl8367c_setAsicMIBsCounterReset(FALSE,FALSE,1 << rtk_switch_port_L2P_get(port))) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

void _rtl8367c_fdbStUser2Smi( rtl8367c_luttb *pLutSt, rtl8367c_fdbtb *pFdbSmi)
{
    /*L3 lookup*/
    if(pLutSt->l3lookup)
    {
        if(pLutSt->l3vidlookup)
        {
#if 0
            pFdbSmi->smi_vidipmul.sip0          = (pLutSt->sip & 0xFF000000) >> 24;
            pFdbSmi->smi_vidipmul.sip1          = (pLutSt->sip & 0x00FF0000) >> 16;
            pFdbSmi->smi_vidipmul.sip2          = (pLutSt->sip & 0x0000FF00) >> 8;
            pFdbSmi->smi_vidipmul.sip3          = pLutSt->sip & 0x000000FF;

            pFdbSmi->smi_vidipmul.dip0          = (pLutSt->dip & 0xFF000000) >> 24;
            pFdbSmi->smi_vidipmul.dip1          = (pLutSt->dip & 0x00FF0000) >> 16;
            pFdbSmi->smi_vidipmul.dip2          = (pLutSt->dip & 0x0000FF00) >> 8;
            pFdbSmi->smi_vidipmul.dip3          = pLutSt->dip & 0x000000FF;
#else
            pFdbSmi->smi_vidipmul.sip0          = pLutSt->sip & 0x000000FF;
            pFdbSmi->smi_vidipmul.sip1          = (pLutSt->sip & 0x0000FF00) >> 8;
            pFdbSmi->smi_vidipmul.sip2          = (pLutSt->sip & 0x00FF0000) >> 16;
            pFdbSmi->smi_vidipmul.sip3          = (pLutSt->sip & 0xFF000000) >> 24;

            pFdbSmi->smi_vidipmul.dip0          = pLutSt->dip & 0x000000FF;
            pFdbSmi->smi_vidipmul.dip1          = (pLutSt->dip & 0x0000FF00) >> 8;
            pFdbSmi->smi_vidipmul.dip2          = (pLutSt->dip & 0x00FF0000) >> 16;
            pFdbSmi->smi_vidipmul.dip3          = (pLutSt->dip & 0xFF000000) >> 24;
#endif
            pFdbSmi->smi_vidipmul.mbr           = pLutSt->mbr;
            pFdbSmi->smi_vidipmul.vid0          = pLutSt->l3_vid & 0x000000FF;
            pFdbSmi->smi_vidipmul.vid1          = (pLutSt->l3_vid & 0x00000F00) >> 8;

            pFdbSmi->smi_vidipmul.mbr8 = (pLutSt->mbr >> 8) & 1;
            pFdbSmi->smi_vidipmul.mbr9 = (pLutSt->mbr >> 9) & 1;
            pFdbSmi->smi_vidipmul.mbr10 = (pLutSt->mbr >> 10) & 1;

            pFdbSmi->smi_vidipmul.l3lookup      = pLutSt->l3lookup;
            pFdbSmi->smi_vidipmul.vidlookup     = pLutSt->l3vidlookup;
            pFdbSmi->smi_vidipmul.nosalearn     = pLutSt->nosalearn;

            //pFdbSmi->smi_vidipmul.reserved      = 0;
            pFdbSmi->smi_vidipmul.reserved1     = 0;
            pFdbSmi->smi_vidipmul.reserved2     = 0;
        }
        else
        {
#if 0
            pFdbSmi->smi_ipmul.sip0         = (pLutSt->sip & 0xFF000000) >> 24;
            pFdbSmi->smi_ipmul.sip1         = (pLutSt->sip & 0x00FF0000) >> 16;
            pFdbSmi->smi_ipmul.sip2         = (pLutSt->sip & 0x0000FF00) >> 8;
            pFdbSmi->smi_ipmul.sip3         = pLutSt->sip & 0x000000FF;

            pFdbSmi->smi_ipmul.dip0         = (pLutSt->dip & 0xFF000000) >> 24;
            pFdbSmi->smi_ipmul.dip1         = (pLutSt->dip & 0x00FF0000) >> 16;
            pFdbSmi->smi_ipmul.dip2         = (pLutSt->dip & 0x0000FF00) >> 8;
            pFdbSmi->smi_ipmul.dip3         = pLutSt->dip & 0x000000FF;
#else
            pFdbSmi->smi_ipmul.sip0         = pLutSt->sip & 0x000000FF;
            pFdbSmi->smi_ipmul.sip1         = (pLutSt->sip & 0x0000FF00) >> 8;
            pFdbSmi->smi_ipmul.sip2         = (pLutSt->sip & 0x00FF0000) >> 16;
            pFdbSmi->smi_ipmul.sip3         = (pLutSt->sip & 0xFF000000) >> 24;

            pFdbSmi->smi_ipmul.dip0         = pLutSt->dip & 0x000000FF;
            pFdbSmi->smi_ipmul.dip1         = (pLutSt->dip & 0x0000FF00) >> 8;
            pFdbSmi->smi_ipmul.dip2         = (pLutSt->dip & 0x00FF0000) >> 16;
            pFdbSmi->smi_ipmul.dip3         = (pLutSt->dip & 0xFF000000) >> 24;
#endif
            pFdbSmi->smi_ipmul.lut_pri      = pLutSt->lut_pri;

            pFdbSmi->smi_ipmul.fwd_en       = pLutSt->fwd_en;

            pFdbSmi->smi_ipmul.mbr          = pLutSt->mbr;
            pFdbSmi->smi_ipmul.igmpidx      = pLutSt->igmpidx;

            pFdbSmi->smi_ipmul.mbr8 = (pLutSt->mbr >> 8) & 1;
            pFdbSmi->smi_ipmul.mbr9 = (pLutSt->mbr >> 9) & 1;
            pFdbSmi->smi_ipmul.mbr10 = (pLutSt->mbr >> 10) & 1;

            pFdbSmi->smi_ipmul.igmp_asic    = pLutSt->igmp_asic;
            pFdbSmi->smi_ipmul.l3lookup     = pLutSt->l3lookup;
            pFdbSmi->smi_ipmul.nosalearn    = pLutSt->nosalearn;

//            pFdbSmi->smi_ipmul.reserved     = 0;
        }
    }
    /*Multicast L2 Lookup*/
    else if(pLutSt->mac.octet[0] & 0x01)
    {
        pFdbSmi->smi_l2mul.mac0         = pLutSt->mac.octet[0];
        pFdbSmi->smi_l2mul.mac1         = pLutSt->mac.octet[1];
        pFdbSmi->smi_l2mul.mac2         = pLutSt->mac.octet[2];
        pFdbSmi->smi_l2mul.mac3         = pLutSt->mac.octet[3];
        pFdbSmi->smi_l2mul.mac4         = pLutSt->mac.octet[4];
        pFdbSmi->smi_l2mul.mac5         = pLutSt->mac.octet[5];

        pFdbSmi->smi_l2mul.cvid_fid     = pLutSt->cvid_fid;
        pFdbSmi->smi_l2mul.lut_pri      = pLutSt->lut_pri;
        pFdbSmi->smi_l2mul.fwd_en       = pLutSt->fwd_en;

        pFdbSmi->smi_l2mul.mbr          = pLutSt->mbr;
        pFdbSmi->smi_l2mul.igmpidx      = pLutSt->igmpidx;

        pFdbSmi->smi_l2mul.mbr8 = (pLutSt->mbr >> 8) & 1;
        pFdbSmi->smi_l2mul.mbr9 = (pLutSt->mbr >> 9) & 1;
        pFdbSmi->smi_l2mul.mbr10 = (pLutSt->mbr >> 10) & 1;

        pFdbSmi->smi_l2mul.igmp_asic    = pLutSt->igmp_asic;
        pFdbSmi->smi_l2mul.l3lookup     = pLutSt->l3lookup;
        pFdbSmi->smi_l2mul.ivl_svl      = pLutSt->ivl_svl;
        pFdbSmi->smi_l2mul.nosalearn    = pLutSt->nosalearn;

      //  pFdbSmi->smi_l2mul.reserved     = 0;
    }
    /*Asic auto-learning*/
    else
    {
        pFdbSmi->smi_auto.mac0          = pLutSt->mac.octet[0];
        pFdbSmi->smi_auto.mac1          = pLutSt->mac.octet[1];
        pFdbSmi->smi_auto.mac2          = pLutSt->mac.octet[2];
        pFdbSmi->smi_auto.mac3          = pLutSt->mac.octet[3];
        pFdbSmi->smi_auto.mac4          = pLutSt->mac.octet[4];
        pFdbSmi->smi_auto.mac5          = pLutSt->mac.octet[5];

        pFdbSmi->smi_auto.cvid_fid      = pLutSt->cvid_fid;
        pFdbSmi->smi_auto.lut_pri       = pLutSt->lut_pri;
        pFdbSmi->smi_auto.fwd_en        = pLutSt->fwd_en;
        pFdbSmi->smi_auto.sa_en         = pLutSt->sa_en;
        pFdbSmi->smi_auto.auth          = pLutSt->auth;;
        pFdbSmi->smi_auto.spa           = pLutSt->spa;
        pFdbSmi->smi_auto.age           = pLutSt->age;
        pFdbSmi->smi_auto.fid           = pLutSt->fid;
        pFdbSmi->smi_auto.efid          = pLutSt->efid;
        pFdbSmi->smi_auto.da_block      = pLutSt->da_block;

        pFdbSmi->smi_auto.spa3 = (pLutSt->spa >> 3) & 1; 

        pFdbSmi->smi_auto.sa_block      = pLutSt->sa_block;
        pFdbSmi->smi_auto.l3lookup      = pLutSt->l3lookup;
        pFdbSmi->smi_auto.ivl_svl       = pLutSt->ivl_svl;
        pFdbSmi->smi_auto.nosalearn     = pLutSt->nosalearn;

        pFdbSmi->smi_auto.reserved      = 0;
    }
}

/* Function Name:
 *      rtl8367c_setAsicL2LookupTb
 * Description:
 *      Set filtering database entry
 * Input:
 *      pL2Table    - L2 table entry writing to 8K+64 filtering database
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK   - Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicL2LookupTb(rtl8367c_luttb *pL2Table)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtl8367c_fdbtb smil2Table;
    rtk_uint32 tblCmd;
    rtk_uint32 busyCounter;

    memset(&smil2Table, 0x00, sizeof(rtl8367c_fdbtb));
    _rtl8367c_fdbStUser2Smi(pL2Table, &smil2Table);

    if(pL2Table->wait_time == 0)
        busyCounter = RTL8367C_LUT_BUSY_CHECK_NO;
    else
        busyCounter = pL2Table->wait_time;

    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(RTL8367C_TABLE_ACCESS_STATUS_REG, RTL8367C_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        pL2Table->lookup_busy = regData;
        if(!regData)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    accessPtr =  (rtk_uint16*)&smil2Table;
    regData = *accessPtr;
    for(i = 0; i < RTL8367C_LUT_ENTRY_SIZE; i++)
    {
        retVal = rtl8367c_setAsicReg(RTL8367C_TABLE_ACCESS_WRDATA_BASE + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        accessPtr ++;
        regData = *accessPtr;

    }

    tblCmd = (RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_WRITE,TB_TARGET_L2)) & (RTL8367C_TABLE_TYPE_MASK  | RTL8367C_COMMAND_TYPE_MASK);
    /* Write Command */
    retVal = rtl8367c_setAsicReg(RTL8367C_TABLE_ACCESS_CTRL_REG, tblCmd);
    if(retVal != RT_ERR_OK)
        return retVal;

    if(pL2Table->wait_time == 0)
        busyCounter = RTL8367C_LUT_BUSY_CHECK_NO;
    else
        busyCounter = pL2Table->wait_time;

    while(busyCounter)
    {
        retVal = rtl8367c_getAsicRegBit(RTL8367C_TABLE_ACCESS_STATUS_REG, RTL8367C_TABLE_LUT_ADDR_BUSY_FLAG_OFFSET,&regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        pL2Table->lookup_busy = regData;
        if(!regData)
            break;

        busyCounter --;
        if(busyCounter == 0)
            return RT_ERR_BUSYWAIT_TIMEOUT;
    }

    /*Read access status*/
    retVal = rtl8367c_getAsicRegBit(RTL8367C_TABLE_ACCESS_STATUS_REG, RTL8367C_HIT_STATUS_OFFSET, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    pL2Table->lookup_hit = regData;
    if(!pL2Table->lookup_hit)
        return RT_ERR_FAILED;

    /*Read access address*/
    /*
    retVal = rtl8367c_getAsicRegBits(RTL8367C_TABLE_ACCESS_STATUS_REG, RTL8367C_TABLE_LUT_ADDR_TYPE_MASK | RTL8367C_TABLE_LUT_ADDR_ADDRESS_MASK,&regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    pL2Table->address = regData;*/

    retVal = rtl8367c_getAsicReg(RTL8367C_TABLE_ACCESS_STATUS_REG, &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    pL2Table->address = (regData & 0x7ff) | ((regData & 0x4000) >> 3) | ((regData & 0x800) << 1);
    pL2Table->lookup_busy = 0;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_l2_addr_add
 * Description:
 *      Add LUT unicast entry.
 * Input:
 *      pMac - 6 bytes unicast(I/G bit is 0) mac address to be written into LUT.
 *      pL2_data - Unicast entry parameter
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_MAC              - Invalid MAC address.
 *      RT_ERR_L2_FID           - Invalid FID .
 *      RT_ERR_L2_INDEXTBL_FULL - hashed index is full of entries.
 *      RT_ERR_INPUT            - Invalid input parameters.
 * Note:
 *      If the unicast mac address already existed in LUT, it will udpate the status of the entry.
 *      Otherwise, it will find an empty or asic auto learned entry to write. If all the entries
 *      with the same hash value can't be replaced, ASIC will return a RT_ERR_L2_INDEXTBL_FULL error.
 */
rtk_api_ret_t rtk_l2_addr_add(rtk_mac_t *pMac, rtk_l2_ucastAddr_t *pL2_data)
{
    rtk_api_ret_t retVal;
    rtk_uint32 method;
    rtl8367c_luttb l2Table;

    memset(&l2Table, 0, sizeof(rtl8367c_luttb));
    memcpy(l2Table.mac.octet, pMac->octet, ETH_ALEN);
    l2Table.ivl_svl     = pL2_data->ivl;
    l2Table.cvid_fid    = pL2_data->cvid;
    l2Table.fid         = pL2_data->fid;
    l2Table.efid        = pL2_data->efid;
    l2Table.spa         = rtk_switch_port_L2P_get(pL2_data->port);
    l2Table.nosalearn   = pL2_data->is_static;
    l2Table.sa_block    = pL2_data->sa_block;
    l2Table.da_block    = pL2_data->da_block;
    l2Table.l3lookup    = 0;
    l2Table.auth        = pL2_data->auth;
    l2Table.age         = 6;
    l2Table.lut_pri     = pL2_data->priority;
    l2Table.sa_en       = pL2_data->sa_pri_en;
    l2Table.fwd_en      = pL2_data->fwd_pri_en;

    if ((retVal = rtl8367c_setAsicL2LookupTb(&l2Table)) != RT_ERR_OK)
        return retVal;
}

void bind_static_lan_mac(rtk_uint8 *mac)
{
    rtk_l2_ucastAddr_t l2_entry;
    rtk_mac_t mac_addr;
    
    if (mac == NULL)
        return;

    memcpy(mac_addr.octet, mac, ETH_ALEN);
    memset(&l2_entry, 0x0, sizeof(rtk_l2_ucastAddr_t));

    l2_entry.port = EXT_PORT0;
    l2_entry.ivl = 1;
    l2_entry.cvid = 1;
    l2_entry.is_static = 1;
    rtk_l2_addr_add(&mac_addr, &l2_entry);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorIsolation
 * Description:
 *      Set the traffic isolation on monitor port
 * Input:
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortMirrorIsolation(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_ISO_OFFSET, enabled);
}

/* Function Name:
 *      rtk_mirror_portIso_set
 * Description:
 *      Set mirror port isolation.
 * Input:
 *      enable |Mirror isolation status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input
 * Note:
 *      The API is to set mirror isolation function that prevent normal forwarding packets to miror port.
 */
rtk_api_ret_t rtk_mirror_portIso_set(rtk_enable_t enable)
{
    rtk_api_ret_t retVal;

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortMirrorIsolation(enable)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicPortMirror
 * Description:
 *      Set port mirror function
 * Input:
 *      source  - Source port
 *      monitor - Monitor (destination) port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortMirror(rtk_uint32 source, rtk_uint32 monitor)
{
    ret_t retVal;

    if((source > RTL8367C_PORTIDMAX) || (monitor > RTL8367C_PORTIDMAX))
        return RT_ERR_PORT_ID;

    retVal = rtl8367c_setAsicRegBits(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_SOURCE_PORT_MASK, source);
    if(retVal != RT_ERR_OK)
        return retVal;


    return rtl8367c_setAsicRegBits(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_MONITOR_PORT_MASK, monitor);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorMask
 * Description:
 *      Set mirror source port mask
 * Input:
 *      SourcePortmask  - Source Portmask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_MASK- Port Mask Error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortMirrorMask(rtk_uint32 SourcePortmask)
{
    if( SourcePortmask > RTL8367C_PORTMASK)
        return RT_ERR_PORT_MASK;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_MIRROR_SRC_PMSK, RTL8367C_MIRROR_SRC_PMSK_MASK, SourcePortmask);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorRxFunction
 * Description:
 *      Set the mirror function on RX of the mirrored
 * Input:
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortMirrorRxFunction(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_RX_OFFSET, enabled);
}

/* Function Name:
 *      rtl8367c_setAsicPortMirrorTxFunction
 * Description:
 *      Set the mirror function on TX of the mirrored
 * Input:
 *      enabled     - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_setAsicPortMirrorTxFunction(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_TX_OFFSET, enabled);
}

/* Function Name:
 *      rtk_mirror_portBased_set
 * Description:
 *      Set port mirror function.
 * Input:
 *      mirroring_port          - Monitor port.
 *      pMirrored_rx_portmask   - Rx mirror port mask.
 *      pMirrored_tx_portmask   - Tx mirror port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number
 *      RT_ERR_PORT_MASK    - Invalid portmask.
 * Note:
 *      The API is to set mirror function of source port and mirror port.
 *      The mirror port can only be set to one port and the TX and RX mirror ports
 *      should be identical.
 */
rtk_api_ret_t rtk_mirror_portBased_set(rtk_port_t mirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask)
{
    rtk_api_ret_t retVal;
    rtk_enable_t mirRx, mirTx;
    rtk_uint32 i, pmask;
    rtk_port_t source_port;

    if(NULL == pMirrored_rx_portmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMirrored_tx_portmask)
        return RT_ERR_NULL_POINTER;

    /*Mirror Sorce Port Mask Check*/
    if (pMirrored_tx_portmask->bits[0]!=pMirrored_rx_portmask->bits[0]&&pMirrored_tx_portmask->bits[0]!=0&&pMirrored_rx_portmask->bits[0]!=0)
        return RT_ERR_PORT_MASK;

     /*mirror port != source port*/
    if(RTK_PORTMASK_IS_PORT_SET((*pMirrored_tx_portmask), mirroring_port) || RTK_PORTMASK_IS_PORT_SET((*pMirrored_rx_portmask), mirroring_port))
        return RT_ERR_PORT_MASK;

   source_port = 0;

    RTK_SCAN_ALL_LOG_PORT(i)
    {
        if (pMirrored_tx_portmask->bits[0]&(1<<i))
        {
            source_port = i;
            break;
        }

        if (pMirrored_rx_portmask->bits[0]&(1<<i))
        {
            source_port = i;
            break;
        }
    }

    if ((retVal = rtl8367c_setAsicPortMirror(rtk_switch_port_L2P_get(source_port), rtk_switch_port_L2P_get(mirroring_port))) != RT_ERR_OK)
        return retVal;

    if(pMirrored_rx_portmask->bits[0] != 0)
    {
        if ((retVal = rtk_switch_portmask_L2P_get(pMirrored_rx_portmask, &pmask)) != RT_ERR_OK)
            return retVal;
        if ((retVal = rtl8367c_setAsicPortMirrorMask(pmask)) != RT_ERR_OK)
            return retVal;
    }
    else
    {
        if ((retVal = rtk_switch_portmask_L2P_get(pMirrored_tx_portmask, &pmask)) != RT_ERR_OK)
            return retVal;
        if ((retVal = rtl8367c_setAsicPortMirrorMask(pmask)) != RT_ERR_OK)
            return retVal;
    }


    if (pMirrored_rx_portmask->bits[0])
        mirRx = ENABLED;
    else
        mirRx = DISABLED;

    if ((retVal = rtl8367c_setAsicPortMirrorRxFunction(mirRx)) != RT_ERR_OK)
        return retVal;

    if (pMirrored_tx_portmask->bits[0])
        mirTx = ENABLED;
    else
        mirTx = DISABLED;

    if ((retVal = rtl8367c_setAsicPortMirrorTxFunction(mirTx)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtl8367c_getAsicPortMirror
 * Description:
 *      Get port mirror function
 * Input:
 *      pSource     - Source port
 *      pMonitor - Monitor (destination) port
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_getAsicPortMirror(rtk_uint32 *pSource, rtk_uint32 *pMonitor)
{
    ret_t retVal;

    retVal = rtl8367c_getAsicRegBits(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_SOURCE_PORT_MASK, pSource);
    if(retVal != RT_ERR_OK)
        return retVal;

    return rtl8367c_getAsicRegBits(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_MONITOR_PORT_MASK, pMonitor);
}

/* Function Name:
 *      rtl8367c_getAsicPortMirrorRxFunction
 * Description:
 *      Get the mirror function on RX of the mirrored
 * Input:
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_getAsicPortMirrorRxFunction(rtk_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_RX_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_getAsicPortMirrorTxFunction
 * Description:
 *      Get the mirror function on TX of the mirrored
 * Input:
 *      pEnabled    - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 * Note:
 *      None
 */
static ret_t rtl8367c_getAsicPortMirrorTxFunction(rtk_uint32* pEnabled)
{
    return rtl8367c_getAsicRegBit(RTL8367C_MIRROR_CTRL_REG, RTL8367C_MIRROR_TX_OFFSET, pEnabled);
}

/* Function Name:
 *      rtl8367c_getAsicPortMirrorMask
 * Description:
 *      Get mirror source port mask
 * Input:
 *      None
 * Output:
 *      pSourcePortmask     - Source Portmask
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI      - SMI access error
 *      RT_ERR_PORT_MASK- Port Mask Error
 * Note:
 *      None
 */
static ret_t rtl8367c_getAsicPortMirrorMask(rtk_uint32 *pSourcePortmask)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_MIRROR_SRC_PMSK, RTL8367C_MIRROR_SRC_PMSK_MASK, pSourcePortmask);
}

/* Function Name:
 *      rtk_mirror_portBased_get
 * Description:
 *      Get port mirror function.
 * Input:
 *      None
 * Output:
 *      pMirroring_port         - Monitor port.
 *      pMirrored_rx_portmask   - Rx mirror port mask.
 *      pMirrored_tx_portmask   - Tx mirror port mask.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API is to get mirror function of source port and mirror port.
 */
rtk_api_ret_t rtk_mirror_portBased_get(rtk_port_t *pMirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask)
{
    rtk_api_ret_t retVal;
    rtk_port_t source_port;
    rtk_enable_t mirRx, mirTx;
    rtk_uint32 sport, mport, pmask;

    if(NULL == pMirrored_rx_portmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMirrored_tx_portmask)
        return RT_ERR_NULL_POINTER;

    if(NULL == pMirroring_port)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicPortMirror(&sport, &mport)) != RT_ERR_OK)
        return retVal;
    source_port = rtk_switch_port_P2L_get(sport);
    *pMirroring_port = rtk_switch_port_P2L_get(mport);

    if ((retVal = rtl8367c_getAsicPortMirrorRxFunction((rtk_uint32*)&mirRx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPortMirrorTxFunction((rtk_uint32*)&mirTx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicPortMirrorMask(&pmask)) != RT_ERR_OK)
        return retVal;

    if (DISABLED == mirRx)
        pMirrored_rx_portmask->bits[0]=0;
    else
    {
        if ((retVal = rtk_switch_portmask_P2L_get(pmask, pMirrored_rx_portmask)) != RT_ERR_OK)
            return retVal;
        pMirrored_rx_portmask->bits[0] |= 1<<source_port;
    }

     if (DISABLED == mirTx)
        pMirrored_tx_portmask->bits[0]=0;
    else
    {
        if ((retVal = rtk_switch_portmask_P2L_get(pmask, pMirrored_tx_portmask)) != RT_ERR_OK)
            return retVal;
        pMirrored_tx_portmask->bits[0] |= 1<<source_port;
    }

    return RT_ERR_OK;

}

/*
@func ret_t | rtl8367c_setAsicLedGroupEnable | Turn on/off Led of all system ports
@parm rtk_uint32 | group | LED group id.
@parm rtk_uint32 | portmask | LED port mask.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error.
@rvalue RT_ERR_PORT_ID | Invalid port number.
@rvalue RT_ERR_INPUT | Invalid input value.
@comm
    The API can turn on/off leds of dedicated port while indicated information configuration of LED group is set to force mode.
 */
static ret_t rtl8367c_setAsicLedGroupEnable(rtk_uint32 group, rtk_uint32 portmask)
{
    ret_t retVal;
    rtk_uint32 regAddr;
    rtk_uint32 regDataMask;

    if ( group >= RTL8367C_LEDGROUPNO )
        return RT_ERR_INPUT;

    regAddr = RTL8367C_REG_PARA_LED_IO_EN1 + group/2;
    regDataMask = 0xFF << ((group%2)*8);
    retVal = rtl8367c_setAsicRegBits(regAddr, regDataMask, portmask&0xff);
    if(retVal != RT_ERR_OK)
        return retVal;

    regAddr = RTL8367C_REG_PARA_LED_IO_EN3;
    regDataMask = 0x3 << (group*2);
    retVal = rtl8367c_setAsicRegBits(regAddr, regDataMask, (portmask>>8)&0x7);
    if(retVal != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_enable_set
 * Description:
 *      Set Led enable congiuration
 * Input:
 *      group       - LED group id.
 *      pPortmask   - LED enable port mask.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can be used to enable LED per port per group.
 */
rtk_api_ret_t rtk_led_enable_set(rtk_led_group_t group, rtk_portmask_t *pPortmask)
{
    rtk_api_ret_t retVal;
    rtk_uint32 pmask;

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if((retVal = rtk_switch_portmask_L2P_get(pPortmask, &pmask)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_setAsicLedGroupEnable(group, pmask)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/*
@func ret_t | rtl8367c_setAsicLedOperationMode | Set LED operation mode
@parm rtk_uint32 | mode | LED mode. 1:scan mode 1, 2:parallel mode, 3:mdx mode (serial mode)
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error.
@rvalue RT_ERR_INPUT | Invalid input value.
@comm
    The API can turn on/off led serial mode and set signal to active high/low.
 */
static ret_t rtl8367c_setAsicLedOperationMode(rtk_uint32 mode)
{
    ret_t retVal;

    /* Invalid input parameter */
    if( mode >= LEDOP_END)
        return RT_ERR_INPUT;

    if( (mode == LEDOP_SCAN0) || (mode == LEDOP_SCAN1) )
        return RT_ERR_INPUT;

    switch(mode)
    {
        case LEDOP_PARALLEL:
            if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_LED_SYS_CONFIG, RTL8367C_LED_SELECT_OFFSET, 0))!=  RT_ERR_OK)
                return retVal;
            /*Disable serial CLK mode*/
            if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SCAN0_LED_IO_EN1,RTL8367C_LED_SERI_CLK_EN_OFFSET, 0))!=  RT_ERR_OK)
                return retVal;
            /*Disable serial DATA mode*/
            if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SCAN0_LED_IO_EN1,RTL8367C_LED_SERI_DATA_EN_OFFSET, 0))!=  RT_ERR_OK)
                return retVal;
            break;
        case LEDOP_SERIAL:
            if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_LED_SYS_CONFIG, RTL8367C_LED_SELECT_OFFSET, 1))!=  RT_ERR_OK)
                return retVal;
            /*Enable serial CLK mode*/
            if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SCAN0_LED_IO_EN1,RTL8367C_LED_SERI_CLK_EN_OFFSET, 1))!=  RT_ERR_OK)
                return retVal;
            /*Enable serial DATA mode*/
            if((retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_SCAN0_LED_IO_EN1,RTL8367C_LED_SERI_DATA_EN_OFFSET, 1))!=  RT_ERR_OK)
                return retVal;
            break;
        default:
            break;
    };

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicLedBlinkRate
 * Description:
 *      Set led blinking rate at mode 0 to mode 3
 * Input:
 *      blinkRate   - Support 6 blink rates
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      LED blink rate can be at 43ms, 84ms, 120ms, 170ms, 340ms and 670ms
 */
static ret_t rtl8367c_setAsicLedBlinkRate(rtk_uint32 blinkRate)
{
    if(blinkRate >= LEDBLINKRATE_END)
        return RT_ERR_OUT_OF_RANGE;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_LED_MODE, RTL8367C_SEL_LEDRATE_MASK, blinkRate);
}

/* Function Name:
 *      rtl8367c_setAsicLedIndicateInfoConfig
 * Description:
 *      Set Leds indicated information mode
 * Input:
 *      ledno   - LED group number. There are 1 to 1 led mapping to each port in each led group
 *      config  - Support 16 types configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      The API can set LED indicated information configuration for each LED group with 1 to 1 led mapping to each port.
 *      Definition        LED Statuses            Description
 *      0000        LED_Off                LED pin Tri-State.
 *      0001        Dup/Col                Collision, Full duplex Indicator. Blinking every 43ms when collision happens. Low for full duplex, and high for half duplex mode.
 *      0010        Link/Act               Link, Activity Indicator. Low for link established. Link/Act Blinks every 43ms when the corresponding port is transmitting or receiving.
 *      0011        Spd1000                1000Mb/s Speed Indicator. Low for 1000Mb/s.
 *      0100        Spd100                 100Mb/s Speed Indicator. Low for 100Mb/s.
 *      0101        Spd10                  10Mb/s Speed Indicator. Low for 10Mb/s.
 *      0110        Spd1000/Act            1000Mb/s Speed/Activity Indicator. Low for 1000Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *      0111        Spd100/Act             100Mb/s Speed/Activity Indicator. Low for 100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *      1000        Spd10/Act              10Mb/s Speed/Activity Indicator. Low for 10Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *      1001        Spd100 (10)/Act        10/100Mb/s Speed/Activity Indicator. Low for 10/100Mb/s. Blinks every 43ms when the corresponding port is transmitting or receiving.
 *      1010        Fiber                  Fiber link Indicator. Low for Fiber.
 *      1011        Fault                  Auto-negotiation     Fault Indicator. Low for Fault.
 *      1100        Link/Rx                Link, Activity Indicator. Low for link established. Link/Rx Blinks every 43ms when the corresponding port is transmitting.
 *      1101        Link/Tx                Link, Activity Indicator. Low for link established. Link/Tx Blinks every 43ms when the corresponding port is receiving.
 *      1110        Master                 Link on Master Indicator. Low for link Master established.
 *      1111        LED_Force              Force LED output, LED output value reference
 */
static ret_t rtl8367c_setAsicLedIndicateInfoConfig(rtk_uint32 ledno, rtk_uint32 config)
{
    ret_t   retVal;
    const rtk_uint16 bits[RTL8367C_LEDGROUPNO] = {RTL8367C_LED0_CFG_MASK, RTL8367C_LED1_CFG_MASK, RTL8367C_LED2_CFG_MASK};

    if(ledno >= RTL8367C_LEDGROUPNO)
        return RT_ERR_OUT_OF_RANGE;

    if(config >= LEDCONF_END)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_LED_CONFIGURATION, RTL8367C_LED_CONFIG_SEL_OFFSET, 0);
    if(retVal != RT_ERR_OK)
        return retVal;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_LED_CONFIGURATION, bits[ledno], config);
}

/* Function Name:
 *      rtl8367c_setAsicForceLeds
 * Description:
 *      Set group LED mode
 * Input:
 *      port 	- Physical port number (0~7)
 *      group 	- LED group number
 *      mode 	- LED mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_PORT_ID  	- Invalid port number
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *		None
 */
ret_t rtl8367c_setAsicForceLed(rtk_uint32 port, rtk_uint32 group, rtk_uint32 mode)
{
    rtk_uint16 regAddr;

    /* Invalid input parameter */
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if(group >= RTL8367C_LEDGROUPNO)
        return RT_ERR_OUT_OF_RANGE;

    if(mode >= LEDFORCEMODE_END)
        return RT_ERR_OUT_OF_RANGE;
    /* Set Related Registers */
	if(port < 8){
    	regAddr = RTL8367C_LED_FORCE_MODE_BASE + (group << 1);
    	return rtl8367c_setAsicRegBits(regAddr, 0x3 << (port * 2), mode);
	}else if(port >= 8){
    	regAddr = RTL8367C_REG_CPU_FORCE_LED0_CFG1 + (group << 1);
    	return rtl8367c_setAsicRegBits(regAddr, 0x3 << ((port-8) * 2), mode);
	}

	return RT_ERR_OK;

}

/* Function Name:
 *      rtk_led_modeForce_set
 * Description:
 *      Set Led group to congiuration force mode
 * Input:
 *      port    - port ID
 *      group   - Support LED group id.
 *      mode    - Support LED force mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      The API can force to one force mode.
 *      The force modes that can be set are as following:
 *      - LED_FORCE_NORMAL,
 *      - LED_FORCE_BLINK,
 *      - LED_FORCE_OFF,
 *      - LED_FORCE_ON.
 */
rtk_api_ret_t rtk_led_modeForce_set(rtk_port_t port, rtk_led_group_t group, rtk_led_force_mode_t mode)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check Port Valid */
    RTK_CHK_PORT_VALID(port);

    if (group >= LED_GROUP_END)
        return RT_ERR_INPUT;

    if (mode >= LED_FORCE_END)
        return RT_ERR_NOT_ALLOWED;

    if ((retVal = rtl8367c_setAsicForceLed(rtk_switch_port_L2P_get(port), group, mode)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_operation_set
 * Description:
 *      Set Led operation mode
 * Input:
 *      mode - LED operation mode.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set Led operation mode.
 *      The modes that can be set are as following:
 *      - LED_OP_SCAN,
 *      - LED_OP_PARALLEL,
 *      - LED_OP_SERIAL,
 */
rtk_api_ret_t rtk_led_operation_set(rtk_led_operation_t mode)
{
    rtk_api_ret_t retVal;
    rtk_uint32 regData;

    if ( mode >= LED_OP_END)
      return RT_ERR_INPUT;

    if ( mode == LED_OP_SCAN)
      return RT_ERR_CHIP_NOT_SUPPORTED;

    switch (mode)
    {
        case LED_OP_PARALLEL:
            regData = LEDOP_PARALLEL;
            break;
        case LED_OP_SERIAL:
            regData = LEDOP_SERIAL;
            break;
        default:
            regData = 0;
            break;
    }

    if ((retVal = rtl8367c_setAsicLedOperationMode(regData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_blinkRate_set
 * Description:
 *      Set LED blinking rate
 * Input:
 *      blinkRate - blinking rate.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      ASIC support 6 types of LED blinking rates at 43ms, 84ms, 120ms, 170ms, 340ms and 670ms.
 */
rtk_api_ret_t rtk_led_blinkRate_set(rtk_led_blink_rate_t blinkRate)
{
    rtk_api_ret_t retVal;

    if (blinkRate >= LED_BLINKRATE_END)
        return RT_ERR_FAILED;

    if ((retVal = rtl8367c_setAsicLedBlinkRate(blinkRate)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_led_groupConfig_set
 * Description:
 *      Set per group Led to congiuration mode
 * Input:
 *      group   - LED group.
 *      config  - LED configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set LED indicated information configuration for each LED group with 1 to 1 led mapping to each port.
 *      - Definition  LED Statuses      Description
 *      - 0000        LED_Off           LED pin Tri-State.
 *      - 0001        Dup/Col           Collision, Full duplex Indicator.
 *      - 0010        Link/Act          Link, Activity Indicator.
 *      - 0011        Spd1000           1000Mb/s Speed Indicator.
 *      - 0100        Spd100            100Mb/s Speed Indicator.
 *      - 0101        Spd10             10Mb/s Speed Indicator.
 *      - 0110        Spd1000/Act       1000Mb/s Speed/Activity Indicator.
 *      - 0111        Spd100/Act        100Mb/s Speed/Activity Indicator.
 *      - 1000        Spd10/Act         10Mb/s Speed/Activity Indicator.
 *      - 1001        Spd100 (10)/Act   10/100Mb/s Speed/Activity Indicator.
 *      - 1010        LoopDetect        LoopDetect Indicator.
 *      - 1011        EEE               EEE Indicator.
 *      - 1100        Link/Rx           Link, Activity Indicator.
 *      - 1101        Link/Tx           Link, Activity Indicator.
 *      - 1110        Master            Link on Master Indicator.
 *      - 1111        Act               Activity Indicator. Low for link established.
 */
rtk_api_ret_t rtk_led_groupConfig_set(rtk_led_group_t group, rtk_led_congig_t config)
{
    rtk_api_ret_t retVal;

    if (LED_GROUP_END <= group)
        return RT_ERR_FAILED;

    if (LED_CONFIG_END <= config)
        return RT_ERR_FAILED;

    if ((retVal = rtl8367c_setAsicLedIndicateInfoConfig(group, config)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_initialState_get
 * Description:
 *      Get initial status
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      INIT_COMPLETED     - Initialized
 *      INIT_NOT_COMPLETED - Uninitialized
 * Note:
 *
 */
init_state_t rtk_switch_initialState_get(void)
{
    return init_state;
}

/* Function Name:
 *      rtk_switch_isExtPort
 * Description:
 *      Check is logical port a Extension port
 * Input:
 *      logicalPort     - logical port ID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Port ID is a EXT port
 *      RT_ERR_FAILED   - Port ID is not a EXT port
 *      RT_ERR_NOT_INIT - Not Initialize
 * Note:
 *
 */
rtk_api_ret_t rtk_switch_isExtPort(rtk_port_t logicalPort)
{
    if(init_state != INIT_COMPLETED)
        return RT_ERR_NOT_INIT;

    if(logicalPort >= RTK_SWITCH_PORT_NUM)
        return RT_ERR_FAILED;

    if(halCtrl.log_port_type[logicalPort] == EXT_PORT)
        return RT_ERR_OK;
    else
        return RT_ERR_FAILED;
}
/* Function Name:
 *      rtk_port_rgmiiDelayExt_set
 * Description:
 *      Set RGMII interface delay value for TX and RX.
 * Input:
 *      txDelay - TX delay value, 1 for delay 2ns and 0 for no-delay
 *      rxDelay - RX delay value, 0~7 for delay setup.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for no-delay, and 7 for maximum delay.
 */
rtk_api_ret_t rtk_port_rgmiiDelayExt_set(rtk_port_t port, rtk_data_t txDelay, rtk_data_t rxDelay)
{
    rtk_api_ret_t retVal;
    rtk_uint32 regAddr, regData;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check Port Valid */
    RTK_CHK_PORT_IS_EXT(port);

    if ((txDelay > 1) || (rxDelay > 7))
        return RT_ERR_INPUT;

    if(port == EXT_PORT0)
        regAddr = RTL8367C_REG_EXT1_RGMXF;
    else if(port == EXT_PORT1)
        regAddr = RTL8367C_REG_EXT2_RGMXF;
    else
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_getAsicReg(regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    regData = (regData & 0xFFF0) | ((txDelay << 3) & 0x0008) | (rxDelay & 0x0007);

    if ((retVal = rtl8367c_setAsicReg(regAddr, regData)) != RT_ERR_OK)
        return retVal;
    printk(KERN_ERR "rgmii delay set:port=%d, txDelay=%d, rxDelay=%d, reg=0x%x, regData=0x%x \r\n", port, txDelay, rxDelay, regAddr, regData);
    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_rgmiiDelayExt_get
 * Description:
 *      Get RGMII interface delay value for TX and RX.
 * Input:
 *      None
 * Output:
 *      pTxDelay - TX delay value
 *      pRxDelay - RX delay value
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API can set external interface 2 RGMII delay.
 *      In TX delay, there are 2 selection: no-delay and 2ns delay.
 *      In RX dekay, there are 8 steps for delay tunning. 0 for n0-delay, and 7 for maximum delay.
 */
rtk_api_ret_t rtk_port_rgmiiDelayExt_get(rtk_port_t port, rtk_data_t *pTxDelay, rtk_data_t *pRxDelay)
{
    rtk_api_ret_t retVal;
    rtk_uint32 regAddr, regData;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check Port Valid */
    RTK_CHK_PORT_IS_EXT(port);

    if( (NULL == pTxDelay) || (NULL == pRxDelay) )
        return RT_ERR_NULL_POINTER;

    if(port == EXT_PORT0)
        regAddr = RTL8367C_REG_EXT1_RGMXF;
    else if(port == EXT_PORT1)
        regAddr = RTL8367C_REG_EXT2_RGMXF;
    else
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_getAsicReg(regAddr, &regData)) != RT_ERR_OK)
        return retVal;

    *pTxDelay = (regData & 0x0008) >> 3;
    *pRxDelay = regData & 0x0007;

    return RT_ERR_OK;
}

/****************************************ACL*************************************/

static void _rtl8367c_svlanConfStUser2Smi( rtl8367c_svlan_memconf_t *pUserSt, rtk_uint16 *pSmiSt)
{
    pSmiSt[0] |= (pUserSt->vs_member & 0x00FF);
    pSmiSt[0] |= (pUserSt->vs_untag & 0x00FF) << 8;

    pSmiSt[1] |= (pUserSt->vs_fid_msti & 0x000F);
    pSmiSt[1] |= (pUserSt->vs_priority & 0x0007) << 4;
    pSmiSt[1] |= (pUserSt->vs_force_fid & 0x0001) << 7;

    pSmiSt[2] |= (pUserSt->vs_svid & 0x0FFF);
    pSmiSt[2] |= (pUserSt->vs_efiden & 0x0001) << 12;
    pSmiSt[2] |= (pUserSt->vs_efid & 0x0007) << 13;

    pSmiSt[3] |= ((pUserSt->vs_member & 0x0700) >> 8);
    pSmiSt[3] |= ((pUserSt->vs_untag & 0x0700) >> 8) << 3;
}

static void _rtl8367c_svlanConfStSmi2User( rtl8367c_svlan_memconf_t *pUserSt, rtk_uint16 *pSmiSt)
{

    pUserSt->vs_member = (pSmiSt[0] & 0x00FF) | ((pSmiSt[3] & 0x0007) << 8);
    pUserSt->vs_untag = ((pSmiSt[0] & 0xFF00) >> 8) | (((pSmiSt[3] & 0x0038) >> 3) << 8);

    pUserSt->vs_fid_msti = (pSmiSt[1] & 0x000F);
    pUserSt->vs_priority = (pSmiSt[1] & 0x0070) >> 4;
    pUserSt->vs_force_fid = (pSmiSt[1] & 0x0080) >> 7;

    pUserSt->vs_svid = (pSmiSt[2] & 0x0FFF);
    pUserSt->vs_efiden = (pSmiSt[2] & 0x1000) >> 12;
    pUserSt->vs_efid = (pSmiSt[2] & 0xE000) >> 13;
}

static void _rtl8367c_svlanMc2sStUser2Smi(rtl8367c_svlan_mc2s_t *pUserSt, rtk_uint16 *pSmiSt)
{
    pSmiSt[0] |= (pUserSt->svidx & 0x003F);
    pSmiSt[0] |= (pUserSt->format & 0x0001) << 6;
    pSmiSt[0] |= (pUserSt->valid & 0x0001) << 7;

    pSmiSt[1] = (rtk_uint16)(pUserSt->smask & 0x0000FFFF);
    pSmiSt[2] = (rtk_uint16)((pUserSt->smask & 0xFFFF0000) >> 16);

    pSmiSt[3] = (rtk_uint16)(pUserSt->sdata & 0x0000FFFF);
    pSmiSt[4] = (rtk_uint16)((pUserSt->sdata & 0xFFFF0000) >> 16);
}

static void _rtl8367c_svlanMc2sStSmi2User(rtl8367c_svlan_mc2s_t *pUserSt, rtk_uint16 *pSmiSt)
{
    pUserSt->svidx = (pSmiSt[0] & 0x003F);
    pUserSt->format = (pSmiSt[0] & 0x0040) >> 6;
    pUserSt->valid = (pSmiSt[0] & 0x0080) >> 7;

    pUserSt->smask = pSmiSt[1] | (pSmiSt[2] << 16);
    pUserSt->sdata = pSmiSt[3] | (pSmiSt[4] << 16);
}

static void _rtl8367c_svlanSp2cStUser2Smi(rtl8367c_svlan_s2c_t *pUserSt, rtk_uint16 *pSmiSt)
{
    pSmiSt[0] |= (pUserSt->dstport & 0x0007);
    pSmiSt[0] |= (pUserSt->svidx & 0x003F) << 3;
    pSmiSt[0] |= ((pUserSt->dstport & 0x0008) >> 3) << 9;

    pSmiSt[1] |= (pUserSt->vid & 0x0FFF);
    pSmiSt[1] |= (pUserSt->valid & 0x0001) << 12;
}

static void _rtl8367c_svlanSp2cStSmi2User(rtl8367c_svlan_s2c_t *pUserSt, rtk_uint16 *pSmiSt)
{
    pUserSt->dstport = (((pSmiSt[0] & 0x0200) >> 9) << 3) | (pSmiSt[0] & 0x0007);
    pUserSt->svidx   = (pSmiSt[0] & 0x01F8) >> 3;
    pUserSt->vid     = (pSmiSt[1] & 0x0FFF);
    pUserSt->valid   = (pSmiSt[1] & 0x1000) >> 12;
}

/* Function Name:
 *      rtl8367c_setAsicSvlanUplinkPortMask
 * Description:
 *      Set uplink ports mask
 * Input:
 *      portMask 	- Uplink port mask setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanUplinkPortMask(rtk_uint32 portMask)
{
    return rtl8367c_setAsicReg(RTL8367C_REG_SVLAN_UPLINK_PORTMASK, portMask);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanUplinkPortMask
 * Description:
 *      Get uplink ports mask
 * Input:
 *      pPortmask 	- Uplink port mask setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanUplinkPortMask(rtk_uint32* pPortmask)
{
    return rtl8367c_getAsicReg(RTL8367C_REG_SVLAN_UPLINK_PORTMASK, pPortmask);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanTpid
 * Description:
 *      Set accepted S-VLAN ether type. The default ether type of S-VLAN is 0x88a8
 * Input:
 *      protocolType 	- Ether type of S-tag frame parsing in uplink ports
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200
 * 		for Q-in-Q SLAN design. User can set mathced ether type as service provider supported protocol
 */
ret_t rtl8367c_setAsicSvlanTpid(rtk_uint32 protocolType)
{
    return rtl8367c_setAsicReg(RTL8367C_REG_VS_TPID, protocolType);
}
/* Function Name:
 *      rtl8367c_getAsicReg
 * Description:
 *      Get accepted S-VLAN ether type. The default ether type of S-VLAN is 0x88a8
 * Input:
 *      pProtocolType 	- Ether type of S-tag frame parsing in uplink ports
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanTpid(rtk_uint32* pProtocolType)
{
    return rtl8367c_getAsicReg(RTL8367C_REG_VS_TPID, pProtocolType);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanPrioritySel
 * Description:
 *      Set SVLAN priority field setting
 * Input:
 *      priSel 	- S-priority assignment method, 0:internal priority 1:C-tag priority 2:using Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_INPUT  	- Invalid input parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanPrioritySel(rtk_uint32 priSel)
{
    if(priSel >= SPRISEL_END)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_SPRISEL_MASK, priSel);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanPrioritySel
 * Description:
 *      Get SVLAN priority field setting
 * Input:
 *      pPriSel 	- S-priority assignment method, 0:internal priority 1:C-tag priority 2:using Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanPrioritySel(rtk_uint32* pPriSel)
{
   	return rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_SPRISEL_MASK, pPriSel);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanTrapPriority
 * Description:
 *      Set trap to CPU priority assignment
 * Input:
 *      priority 	- Priority assignment
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_QOS_INT_PRIORITY - Invalid priority
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanTrapPriority(rtk_uint32 priority)
{
    if(priority > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_QOS_TRAP_PRIORITY0, RTL8367C_SVLAN_PRIOIRTY_MASK, priority);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanTrapPriority
 * Description:
 *      Get trap to CPU priority assignment
 * Input:
 *      pPriority 	- Priority assignment
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanTrapPriority(rtk_uint32* pPriority)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_QOS_TRAP_PRIORITY0, RTL8367C_SVLAN_PRIOIRTY_MASK, pPriority);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanDefaultVlan
 * Description:
 *      Set default egress SVLAN
 * Input:
 *      port 	- Physical port number (0~10)
 *      index 	- index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_PORT_ID  			- Invalid port number
 *      RT_ERR_SVLAN_ENTRY_INDEX  	- Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanDefaultVlan(rtk_uint32 port, rtk_uint32 index)
{
    ret_t retVal;

	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

	if(port < 8){
		if(port & 1)
	    	retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT1_SVIDX_MASK,index);
		else
	    	retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT0_SVIDX_MASK,index);
	}else{
		switch(port){
			case 8:
				retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT8_SVIDX_MASK,index);
				break;

			case 9:
				retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT9_SVIDX_MASK,index);
				break;

			case 10:
				retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL5, RTL8367C_SVLAN_PORTBASED_SVIDX_CTRL5_MASK,index);
				break;
		}
	}

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanDefaultVlan
 * Description:
 *      Get default egress SVLAN
 * Input:
 *      port 	- Physical port number (0~7)
 *      pIndex 	- index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanDefaultVlan(rtk_uint32 port, rtk_uint32* pIndex)
{
    ret_t retVal;

	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	if(port < 8){
		if(port & 1)
	    	retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT1_SVIDX_MASK,pIndex);
		else
	    	retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL0 + (port >> 1), RTL8367C_VS_PORT0_SVIDX_MASK,pIndex);
	}else{
		switch(port){
			case 8:
				retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT8_SVIDX_MASK,pIndex);
				break;

			case 9:
				retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL4, RTL8367C_VS_PORT9_SVIDX_MASK,pIndex);
				break;

			case 10:
				retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_PORTBASED_SVIDX_CTRL5, RTL8367C_SVLAN_PORTBASED_SVIDX_CTRL5_MASK,pIndex);
				break;
		}
	}

    return retVal;

}
/* Function Name:
 *      rtl8367c_setAsicSvlanIngressUntag
 * Description:
 *      Set action received un-Stag frame from unplink port
 * Input:
 *      mode 		- 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanIngressUntag(rtk_uint32 mode)
{
    return rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNTAG_MASK, mode);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanIngressUntag
 * Description:
 *      Get action received un-Stag frame from unplink port
 * Input:
 *      pMode 		- 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanIngressUntag(rtk_uint32* pMode)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNTAG_MASK, pMode);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanIngressUnmatch
 * Description:
 *      Set action received unmatched Stag frame from unplink port
 * Input:
 *      mode 		- 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanIngressUnmatch(rtk_uint32 mode)
{
    return rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNMAT_MASK, mode);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanIngressUnmatch
 * Description:
 *      Get action received unmatched Stag frame from unplink port
 * Input:
 *      pMode 		- 0:Drop 1:Trap 2:Assign SVLAN
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanIngressUnmatch(rtk_uint32* pMode)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UNMAT_MASK, pMode);

}
/* Function Name:
 *      rtl8367c_setAsicSvlanEgressUnassign
 * Description:
 *      Set unplink stream without egress SVID action
 * Input:
 *      enabled 	- 1:Trap egress unassigned frames to CPU, 0: Use SVLAN setup in VS_CPSVIDX as egress SVID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanEgressUnassign(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UIFSEG_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanEgressUnassign
 * Description:
 *      Get unplink stream without egress SVID action
 * Input:
 *      pEnabled 	- 1:Trap egress unassigned frames to CPU, 0: Use SVLAN setup in VS_CPSVIDX as egress SVID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 	- Success
 *      RT_ERR_SMI  - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanEgressUnassign(rtk_uint32* pEnabled)
{
   	return rtl8367c_getAsicRegBit(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_UIFSEG_OFFSET, pEnabled);
}


/* Function Name:
 *      rtl8367c_setAsicSvlanMemberConfiguration
 * Description:
 *      Set system 64 S-tag content
 * Input:
 *      index 			- index of 64 s-tag configuration
 *      pSvlanMemCfg 	- SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX  	- Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanMemberConfiguration(rtk_uint32 index, rtl8367c_svlan_memconf_t* pSvlanMemCfg)
{
    ret_t retVal;
    rtk_uint32 regAddr, regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtk_uint16 smiSvlanMemConf[RTL8367C_SVLAN_MEMCONF_LEN];

    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    memset(smiSvlanMemConf, 0x00, sizeof(rtk_uint16) * RTL8367C_SVLAN_MEMCONF_LEN);
    _rtl8367c_svlanConfStUser2Smi(pSvlanMemCfg, smiSvlanMemConf);

    accessPtr = smiSvlanMemConf;

    regData = *accessPtr;
    for(i = 0; i < 3; i++)
    {
        retVal = rtl8367c_setAsicReg(RTL8367C_SVLAN_MEMBERCFG_BASE_REG(index) + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        accessPtr ++;
        regData = *accessPtr;
    }

	if(index < 63)
		regAddr = RTL8367C_REG_SVLAN_MEMBERCFG0_CTRL4+index;
	else if(index == 63)
		regAddr = RTL8367C_REG_SVLAN_MEMBERCFG63_CTRL4;

	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	return RT_ERR_OK;

}
/* Function Name:
 *      rtl8367c_getAsicSvlanMemberConfiguration
 * Description:
 *      Get system 64 S-tag content
 * Input:
 *      index 			- index of 64 s-tag configuration
 *      pSvlanMemCfg 	- SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX  	- Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanMemberConfiguration(rtk_uint32 index,rtl8367c_svlan_memconf_t* pSvlanMemCfg)
{
    ret_t retVal;
    rtk_uint32 regAddr,regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtk_uint16 smiSvlanMemConf[RTL8367C_SVLAN_MEMCONF_LEN];

    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    memset(smiSvlanMemConf, 0x00, sizeof(rtk_uint16) * RTL8367C_SVLAN_MEMCONF_LEN);

    accessPtr = smiSvlanMemConf;

    for(i = 0; i < 3; i++)
    {
        retVal = rtl8367c_getAsicReg(RTL8367C_SVLAN_MEMBERCFG_BASE_REG(index) + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;

        accessPtr ++;
    }

	if(index < 63)
		regAddr = RTL8367C_REG_SVLAN_MEMBERCFG0_CTRL4+index;
	else if(index == 63)
		regAddr = RTL8367C_REG_SVLAN_MEMBERCFG63_CTRL4;

	retVal = rtl8367c_getAsicReg(regAddr, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	*accessPtr = regData;

    _rtl8367c_svlanConfStSmi2User(pSvlanMemCfg, smiSvlanMemConf);

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicSvlanC2SConf
 * Description:
 *      Set SVLAN C2S table
 * Input:
 *      index 	- index of 128 Svlan C2S configuration
 *      evid 	- Enhanced VID
 *      portmask 	- available c2s port mask
 *      svidx 	- index of 64 Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      ASIC will check upstream's VID and assign related SVID to mathed packet
 */
ret_t rtl8367c_setAsicSvlanC2SConf(rtk_uint32 index, rtk_uint32 evid, rtk_uint32 portmask, rtk_uint32 svidx)
{
    ret_t retVal;

    if(index > RTL8367C_C2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    retVal = rtl8367c_setAsicReg(RTL8367C_SVLAN_C2SCFG_BASE_REG(index), svidx);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_setAsicReg(RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 1, portmask);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_setAsicReg(RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 2, evid);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanC2SConf
 * Description:
 *      Get SVLAN C2S table
 * Input:
 *      index 	- index of 128 Svlan C2S configuration
 *      pEvid 	- Enhanced VID
 *      pPortmask 	- available c2s port mask
 *      pSvidx 	- index of 64 Svlan member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanC2SConf(rtk_uint32 index, rtk_uint32* pEvid, rtk_uint32* pPortmask, rtk_uint32* pSvidx)
{
    ret_t retVal;

    if(index > RTL8367C_C2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    retVal = rtl8367c_getAsicReg(RTL8367C_SVLAN_C2SCFG_BASE_REG(index), pSvidx);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_getAsicReg(RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 1, pPortmask);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_getAsicReg(RTL8367C_SVLAN_C2SCFG_BASE_REG(index) + 2, pEvid);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicSvlanMC2SConf
 * Description:
 *      Set system MC2S content
 * Input:
 *      index 			- index of 32 SVLAN 32 MC2S configuration
 *      pSvlanMc2sCfg 	- SVLAN Multicast to SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      If upstream packet is L2 multicast or IPv4 multicast packet and DMAC/DIP is matched MC2S
 * 		configuration, ASIC will assign egress SVID to the packet
 */
ret_t rtl8367c_setAsicSvlanMC2SConf(rtk_uint32 index,rtl8367c_svlan_mc2s_t* pSvlanMc2sCfg)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtk_uint16 smiSvlanMC2S[RTL8367C_SVLAN_MC2S_LEN];

    if(index > RTL8367C_MC2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    memset(smiSvlanMC2S, 0x00, sizeof(rtk_uint16) * RTL8367C_SVLAN_MC2S_LEN);
    _rtl8367c_svlanMc2sStUser2Smi(pSvlanMc2sCfg, smiSvlanMC2S);

    accessPtr = smiSvlanMC2S;

    regData = *accessPtr;
    for(i = 0; i < 5; i++)
    {
        retVal = rtl8367c_setAsicReg(RTL8367C_SVLAN_MCAST2S_ENTRY_BASE_REG(index) + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        accessPtr ++;
        regData = *accessPtr;
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanMC2SConf
 * Description:
 *      Get system MC2S content
 * Input:
 *      index 			- index of 32 SVLAN 32 MC2S configuration
 *      pSvlanMc2sCfg 	- SVLAN Multicast to SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanMC2SConf(rtk_uint32 index, rtl8367c_svlan_mc2s_t* pSvlanMc2sCfg)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtk_uint16 smiSvlanMC2S[RTL8367C_SVLAN_MC2S_LEN];

    if(index > RTL8367C_MC2SIDXMAX)
        return RT_ERR_ENTRY_INDEX;

    memset(smiSvlanMC2S, 0x00, sizeof(rtk_uint16) * RTL8367C_SVLAN_MC2S_LEN);

    accessPtr = smiSvlanMC2S;

    for(i = 0; i < 5; i++)
    {
        retVal = rtl8367c_getAsicReg(RTL8367C_SVLAN_MCAST2S_ENTRY_BASE_REG(index) + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;
        accessPtr ++;
    }


    _rtl8367c_svlanMc2sStSmi2User(pSvlanMc2sCfg, smiSvlanMC2S);

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicSvlanSP2CConf
 * Description:
 *      Set system 128 SP2C content
 * Input:
 *      index 			- index of 128 SVLAN & Port to CVLAN configuration
 *      pSvlanSp2cCfg 	- SVLAN & Port to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanSP2CConf(rtk_uint32 index, rtl8367c_svlan_s2c_t* pSvlanSp2cCfg)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtk_uint16 smiSvlanSP2C[RTL8367C_SVLAN_SP2C_LEN];

    if(index > RTL8367C_SP2CMAX)
        return RT_ERR_ENTRY_INDEX;

    memset(smiSvlanSP2C, 0x00, sizeof(rtk_uint16) * RTL8367C_SVLAN_SP2C_LEN);
    _rtl8367c_svlanSp2cStUser2Smi(pSvlanSp2cCfg,smiSvlanSP2C);

    accessPtr = smiSvlanSP2C;

    regData = *accessPtr;
    for(i = 0; i < 2; i++)
    {
        retVal = rtl8367c_setAsicReg(RTL8367C_SVLAN_S2C_ENTRY_BASE_REG(index) + i, regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        accessPtr ++;
        regData = *accessPtr;
    }

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicSvlanSP2CConf
 * Description:
 *      Get system 128 SP2C content
 * Input:
 *      index 			- index of 128 SVLAN & Port to CVLAN configuration
 *      pSvlanSp2cCfg 	- SVLAN & Port to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_ENTRY_INDEX  - Invalid entry index
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanSP2CConf(rtk_uint32 index,rtl8367c_svlan_s2c_t* pSvlanSp2cCfg)
{
    ret_t retVal;
    rtk_uint32 regData;
    rtk_uint16 *accessPtr;
    rtk_uint32 i;
    rtk_uint16 smiSvlanSP2C[RTL8367C_SVLAN_SP2C_LEN];

    if(index > RTL8367C_SP2CMAX)
        return RT_ERR_ENTRY_INDEX;

    memset(smiSvlanSP2C, 0x00, sizeof(rtk_uint16) * RTL8367C_SVLAN_SP2C_LEN);

    accessPtr = smiSvlanSP2C;

    for(i = 0; i < 2; i++)
    {
        retVal = rtl8367c_getAsicReg(RTL8367C_SVLAN_S2C_ENTRY_BASE_REG(index) + i, &regData);
        if(retVal != RT_ERR_OK)
            return retVal;

        *accessPtr = regData;

        accessPtr ++;
    }

    _rtl8367c_svlanSp2cStSmi2User(pSvlanSp2cCfg, smiSvlanSP2C);

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicSvlanDmacCvidSel
 * Description:
 *      Set downstream CVID decision by DMAC
 * Input:
 *      port 		- Physical port number (0~7)
 *      enabled 	- 0:disabled, 1:enabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanDmacCvidSel(rtk_uint32 port, rtk_uint32 enabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	if(port < 8)
    	return rtl8367c_setAsicRegBit(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_PORT0_DMACVIDSEL_OFFSET + port, enabled);
	else
		return rtl8367c_setAsicRegBit(RTL8367C_REG_SVLAN_CFG_EXT, RTL8367C_VS_PORT8_DMACVIDSEL_OFFSET + (port-8), enabled);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanDmacCvidSel
 * Description:
 *      Get downstream CVID decision by DMAC
 * Input:
 *      port 		- Physical port number (0~7)
 *      pEnabled 	- 0:disabled, 1:enabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanDmacCvidSel(rtk_uint32 port, rtk_uint32* pEnabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	if(port < 8)
    	return rtl8367c_getAsicRegBit(RTL8367C_REG_SVLAN_CFG, RTL8367C_VS_PORT0_DMACVIDSEL_OFFSET + port, pEnabled);
	else
		return rtl8367c_getAsicRegBit(RTL8367C_REG_SVLAN_CFG_EXT, RTL8367C_VS_PORT8_DMACVIDSEL_OFFSET + (port-8), pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicSvlanUntagVlan
 * Description:
 *      Set default ingress untag SVLAN
 * Input:
 *      index 	- index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX  	- Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanUntagVlan(rtk_uint32 index)
{
    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNTAG_SVIDX_MASK, index);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanUntagVlan
 * Description:
 *      Get default ingress untag SVLAN
 * Input:
 *      pIndex 	- index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanUntagVlan(rtk_uint32* pIndex)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNTAG_SVIDX_MASK, pIndex);
}

/* Function Name:
 *      rtl8367c_setAsicSvlanUnmatchVlan
 * Description:
 *      Set default ingress unmatch SVLAN
 * Input:
 *      index 	- index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_SVLAN_ENTRY_INDEX  	- Invalid SVLAN index parameter
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanUnmatchVlan(rtk_uint32 index)
{
    if(index > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNMAT_SVIDX_MASK, index);
}
/* Function Name:
 *      rtl8367c_getAsicSvlanUnmatchVlan
 * Description:
 *      Get default ingress unmatch SVLAN
 * Input:
 *      pIndex 	- index SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanUnmatchVlan(rtk_uint32* pIndex)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_SVLAN_UNTAG_UNMAT_CFG, RTL8367C_VS_UNMAT_SVIDX_MASK, pIndex);
}


/* Function Name:
 *      rtl8367c_setAsicSvlanLookupType
 * Description:
 *      Set svlan lookup table selection
 * Input:
 *      type 	- lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSvlanLookupType(rtk_uint32 type)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_SVLAN_LOOKUP_TYPE, RTL8367C_SVLAN_LOOKUP_TYPE_OFFSET, type);
}

/* Function Name:
 *      rtl8367c_getAsicSvlanLookupType
 * Description:
 *      Get svlan lookup table selection
 * Input:
 *      pType 	- lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicSvlanLookupType(rtk_uint32* pType)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_SVLAN_LOOKUP_TYPE, RTL8367C_SVLAN_LOOKUP_TYPE_OFFSET, pType);
}

rtk_uint8               svlan_mbrCfgUsage[RTL8367C_SVIDXNO];
rtk_uint16              svlan_mbrCfgVid[RTL8367C_SVIDXNO];
rtk_svlan_lookupType_t  svlan_lookupType;
/* Function Name:
 *      rtk_svlan_init
 * Description:
 *      Initialize SVLAN Configuration
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200 for Q-in-Q SLAN design.
 *      User can set mathced ether type as service provider supported protocol.
 */
rtk_api_ret_t rtk_svlan_init(void)
{
    rtk_uint32 i;
    rtk_api_ret_t retVal;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;
    rtk_uint32 svidx;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /*default use C-priority*/
    if ((retVal = rtl8367c_setAsicSvlanPrioritySel(SPRISEL_CTAGPRI)) != RT_ERR_OK)
        return retVal;

    /*Drop SVLAN untag frame*/
    if ((retVal = rtl8367c_setAsicSvlanIngressUntag(UNTAG_DROP)) != RT_ERR_OK)
        return retVal;

    /*Drop SVLAN unmatch frame*/
    if ((retVal = rtl8367c_setAsicSvlanIngressUnmatch(UNMATCH_DROP)) != RT_ERR_OK)
        return retVal;

    /*Set TPID to 0x88a8*/
    if ((retVal = rtl8367c_setAsicSvlanTpid(0x88a8)) != RT_ERR_OK)
        return retVal;

    /*Clean Uplink Port Mask to none*/
    if ((retVal = rtl8367c_setAsicSvlanUplinkPortMask(0)) != RT_ERR_OK)
        return retVal;

    /*Clean SVLAN Member Configuration*/
    for (i=0; i<= RTL8367C_SVIDXMAX; i++)
    {
        memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
        if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;
    }

    /*Clean C2S Configuration*/
    for (i=0; i<= RTL8367C_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_setAsicSvlanC2SConf(i, 0,0,0)) != RT_ERR_OK)
            return retVal;
    }

    /*Clean SP2C Configuration*/
    for (i=0; i <= RTL8367C_SP2CMAX ; i++)
    {
        memset(&svlanSP2CConf, 0, sizeof(rtl8367c_svlan_s2c_t));
        if ((retVal = rtl8367c_setAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;
    }

    /*Clean MC2S Configuration*/
    for (i=0 ; i<= RTL8367C_MC2SIDXMAX; i++)
    {
        memset(&svlanMC2SConf, 0, sizeof(rtl8367c_svlan_mc2s_t));
        if ((retVal = rtl8367c_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;
    }


    if ((retVal = rtk_svlan_lookupType_set(SVLAN_LOOKUP_S64MBRCGF)) != RT_ERR_OK)
        return retVal;


    for (svidx = 0; svidx <= RTL8367C_SVIDXMAX; svidx++)
    {
        svlan_mbrCfgUsage[svidx] = FALSE;
    }


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_servicePort_add
 * Description:
 *      Add one service port in the specified device
 * Input:
 *      port - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
rtk_api_ret_t rtk_svlan_servicePort_add(rtk_port_t port)
{
    rtk_api_ret_t retVal;
    rtk_uint32 pmsk;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* check port valid */
    RTK_CHK_PORT_VALID(port);

    if ((retVal = rtl8367c_getAsicSvlanUplinkPortMask(&pmsk)) != RT_ERR_OK)
        return retVal;

    pmsk = pmsk | (1<<rtk_switch_port_L2P_get(port));

    if ((retVal = rtl8367c_setAsicSvlanUplinkPortMask(pmsk)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_servicePort_get
 * Description:
 *      Get service ports in the specified device.
 * Input:
 *      None
 * Output:
 *      pSvlan_portmask - pointer buffer of svlan ports.
 * Return:
 *      RT_ERR_OK          - OK
 *      RT_ERR_FAILED      - Failed
 *      RT_ERR_SMI         - SMI access error
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
rtk_api_ret_t rtk_svlan_servicePort_get(rtk_portmask_t *pSvlan_portmask)
{
    rtk_api_ret_t retVal;
    rtk_uint32 phyMbrPmask;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvlan_portmask)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanUplinkPortMask(&phyMbrPmask)) != RT_ERR_OK)
        return retVal;

    if(rtk_switch_portmask_P2L_get(phyMbrPmask, pSvlan_portmask) != RT_ERR_OK)
        return RT_ERR_FAILED;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_servicePort_del
 * Description:
 *      Delete one service port in the specified device
 * Input:
 *      port - Port id.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 * Note:
 *      This API is removing SVLAN service port in the specified device.
 */
rtk_api_ret_t rtk_svlan_servicePort_del(rtk_port_t port)
{
    rtk_api_ret_t retVal;
    rtk_uint32 pmsk;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* check port valid */
    RTK_CHK_PORT_VALID(port);

    if ((retVal = rtl8367c_getAsicSvlanUplinkPortMask(&pmsk)) != RT_ERR_OK)
        return retVal;

    pmsk = pmsk & ~(1<<rtk_switch_port_L2P_get(port));

    if ((retVal = rtl8367c_setAsicSvlanUplinkPortMask(pmsk)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_tpidEntry_set
 * Description:
 *      Configure accepted S-VLAN ether type.
 * Input:
 *      svlan_tag_id - Ether type of S-tag frame parsing in uplink ports.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      Ether type of S-tag in 802.1ad is 0x88a8 and there are existed ether type 0x9100 and 0x9200 for Q-in-Q SLAN design.
 *      User can set mathced ether type as service provider supported protocol.
 */
rtk_api_ret_t rtk_svlan_tpidEntry_set(rtk_svlan_tpid_t svlan_tag_id)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (svlan_tag_id>RTK_MAX_NUM_OF_PROTO_TYPE)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicSvlanTpid(svlan_tag_id)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_tpidEntry_get
 * Description:
 *      Get accepted S-VLAN ether type setting.
 * Input:
 *      None
 * Output:
 *      pSvlan_tag_id -  Ether type of S-tag frame parsing in uplink ports.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This API is setting which port is connected to provider switch. All frames receiving from this port must
 *      contain accept SVID in S-tag field.
 */
rtk_api_ret_t rtk_svlan_tpidEntry_get(rtk_svlan_tpid_t *pSvlan_tag_id)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvlan_tag_id)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanTpid(pSvlan_tag_id)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_priorityRef_set
 * Description:
 *      Set S-VLAN upstream priority reference setting.
 * Input:
 *      ref - reference selection parameter.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      The API can set the upstream SVLAN tag priority reference source. The related priority
 *      sources are as following:
 *      - REF_INTERNAL_PRI,
 *      - REF_CTAG_PRI,
 *      - REF_SVLAN_PRI.
 */
rtk_api_ret_t rtk_svlan_priorityRef_set(rtk_svlan_pri_ref_t ref)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (ref >= REF_PRI_END)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367c_setAsicSvlanPrioritySel(ref)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_priorityRef_get
 * Description:
 *      Get S-VLAN upstream priority reference setting.
 * Input:
 *      None
 * Output:
 *      pRef - reference selection parameter.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      The API can get the upstream SVLAN tag priority reference source. The related priority
 *      sources are as following:
 *      - REF_INTERNAL_PRI,
 *      - REF_CTAG_PRI,
 *      - REF_SVLAN_PRI.
 */
rtk_api_ret_t rtk_svlan_priorityRef_get(rtk_svlan_pri_ref_t *pRef)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pRef)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanPrioritySel(pRef)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_memberPortEntry_set
 * Description:
 *      Configure system SVLAN member content
 * Input:
 *      svid - SVLAN id
 *      psvlan_cfg - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameter.
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_SVLAN_TABLE_FULL - SVLAN configuration is full.
 * Note:
 *      The API can set system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped by default setup.
 *      - rtk_svlan_memberCfg_t->svid is SVID of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->memberport is member port mask of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->fid is filtering database of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->priority is priority of SVLAN member configuration.
 */
rtk_api_ret_t rtk_svlan_memberPortEntry_set(rtk_vlan_t svid, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    rtk_api_ret_t retVal;
    rtk_int32 i;
    rtk_uint32 empty_idx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtk_uint32 phyMbrPmask;
    rtk_vlan_cfg_t vlanCfg;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if(svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    RTK_CHK_PORTMASK_VALID(&(pSvlan_cfg->memberport));

    RTK_CHK_PORTMASK_VALID(&(pSvlan_cfg->untagport));

    if (pSvlan_cfg->fiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->fid > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->priority > RTL8367C_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if (pSvlan_cfg->efiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->efid > RTL8367C_EFIDMAX)
        return RT_ERR_L2_FID;

    if(SVLAN_LOOKUP_C4KVLAN == svlan_lookupType)
    {
        if ((retVal = rtk_vlan_get(svid, &vlanCfg)) != RT_ERR_OK)
            return retVal;

        vlanCfg.mbr = pSvlan_cfg->memberport;
        vlanCfg.untag = pSvlan_cfg->untagport;

        if ((retVal = rtk_vlan_set(svid, &vlanCfg)) != RT_ERR_OK)
            return retVal;

        empty_idx = 0xFF;

        for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
        {
            if (svid == svlan_mbrCfgVid[i] && TRUE == svlan_mbrCfgUsage[i])
            {
                memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
                svlanMemConf.vs_svid        = svid;
                svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
                svlanMemConf.vs_efid        = pSvlan_cfg->efid;
                svlanMemConf.vs_priority    = pSvlan_cfg->priority;

                /*for create check*/
                if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
                    svlanMemConf.vs_efid = 1;

                if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
            else if (FALSE == svlan_mbrCfgUsage[i] && 0xFF == empty_idx)
            {
                empty_idx = i;
            }
        }

        if (empty_idx != 0xFF)
        {
            svlan_mbrCfgUsage[empty_idx] = TRUE;
            svlan_mbrCfgVid[empty_idx] = svid;

            memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
            svlanMemConf.vs_svid        = svid;
            svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
            svlanMemConf.vs_efid        = pSvlan_cfg->efid;
            svlanMemConf.vs_priority    = pSvlan_cfg->priority;

            /*for create check*/
            if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
                svlanMemConf.vs_efid = 1;

            if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(empty_idx, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

        }

        return RT_ERR_OK;
    }


    empty_idx = 0xFF;

    for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
    {
        /*
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;
        */
        if (svid == svlan_mbrCfgVid[i] && TRUE == svlan_mbrCfgUsage[i])
        {
            svlanMemConf.vs_svid = svid;

            if(rtk_switch_portmask_L2P_get(&(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
                return RT_ERR_FAILED;

            svlanMemConf.vs_member = phyMbrPmask;

            if(rtk_switch_portmask_L2P_get(&(pSvlan_cfg->untagport), &phyMbrPmask) != RT_ERR_OK)
                return RT_ERR_FAILED;

            svlanMemConf.vs_untag = phyMbrPmask;

            svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
            svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
            svlanMemConf.vs_priority    = pSvlan_cfg->priority;
            svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
            svlanMemConf.vs_efid        = pSvlan_cfg->efid;

            /*all items are reset means deleting*/
            if( 0 == svlanMemConf.vs_member &&
                0 == svlanMemConf.vs_untag &&
                0 == svlanMemConf.vs_force_fid &&
                0 == svlanMemConf.vs_fid_msti &&
                0 == svlanMemConf.vs_priority &&
                0 == svlanMemConf.vs_efiden &&
                0 == svlanMemConf.vs_efid)
            {
                svlan_mbrCfgUsage[i] = FALSE;
                svlan_mbrCfgVid[i] = 0;

                /* Clear SVID also */
                svlanMemConf.vs_svid = 0;
            }
            else
            {
                svlan_mbrCfgUsage[i] = TRUE;
                svlan_mbrCfgVid[i] = svlanMemConf.vs_svid;

                if(0 == svlanMemConf.vs_svid)
                {
                    /*for create check*/
                    if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
                    {
                        svlanMemConf.vs_efid = 1;
                    }
                }
            }

            if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

            return RT_ERR_OK;
        }
        else if (FALSE == svlan_mbrCfgUsage[i] && 0xFF == empty_idx)
        {
            empty_idx = i;
        }
    }

    if (empty_idx != 0xFF)
    {
        memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
        svlanMemConf.vs_svid = svid;

        if(rtk_switch_portmask_L2P_get(&(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
            return RT_ERR_FAILED;

        svlanMemConf.vs_member = phyMbrPmask;

        if(rtk_switch_portmask_L2P_get(&(pSvlan_cfg->untagport), &phyMbrPmask) != RT_ERR_OK)
            return RT_ERR_FAILED;

        svlanMemConf.vs_untag = phyMbrPmask;

        svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
        svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
        svlanMemConf.vs_priority    = pSvlan_cfg->priority;

        svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
        svlanMemConf.vs_efid        = pSvlan_cfg->efid;

        /*change efid for empty svid 0*/
        if(0 == svlanMemConf.vs_svid)
        {   /*for create check*/
            if(0 == svlanMemConf.vs_efiden && 0 == svlanMemConf.vs_efid)
            {
                svlanMemConf.vs_efid = 1;
            }
        }

        svlan_mbrCfgUsage[empty_idx] = TRUE;
        svlan_mbrCfgVid[empty_idx] = svlanMemConf.vs_svid;

        if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(empty_idx, &svlanMemConf)) != RT_ERR_OK)
        {
            return retVal;
        }

        return RT_ERR_OK;
    }

    return RT_ERR_SVLAN_TABLE_FULL;
}

/* Function Name:
 *      rtk_svlan_memberPortEntry_get
 * Description:
 *      Get SVLAN member Configure.
 * Input:
 *      svid - SVLAN id
 * Output:
 *      pSvlan_cfg - SVLAN member configuration
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can get system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped.
 */
rtk_api_ret_t rtk_svlan_memberPortEntry_get(rtk_vlan_t svid, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;


    for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            pSvlan_cfg->svid        = svlanMemConf.vs_svid;

            if(rtk_switch_portmask_P2L_get(svlanMemConf.vs_member,&(pSvlan_cfg->memberport)) != RT_ERR_OK)
                return RT_ERR_FAILED;

            if(rtk_switch_portmask_P2L_get(svlanMemConf.vs_untag,&(pSvlan_cfg->untagport)) != RT_ERR_OK)
                return RT_ERR_FAILED;

            pSvlan_cfg->fiden       = svlanMemConf.vs_force_fid;
            pSvlan_cfg->fid         = svlanMemConf.vs_fid_msti;
            pSvlan_cfg->priority    = svlanMemConf.vs_priority;
            pSvlan_cfg->efiden      = svlanMemConf.vs_efiden;
            pSvlan_cfg->efid        = svlanMemConf.vs_efid;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

}

/* Function Name:
 *      rtk_svlan_memberPortEntry_adv_set
 * Description:
 *      Configure system SVLAN member by index
 * Input:
 *      idx         - Index (0 ~ 63)
 *      psvlan_cfg  - SVLAN member configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameter.
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_PORT_MASK        - Invalid portmask.
 *      RT_ERR_SVLAN_TABLE_FULL - SVLAN configuration is full.
 * Note:
 *      The API can set system 64 accepted s-tag frame format by index.
 *      - rtk_svlan_memberCfg_t->svid is SVID of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->memberport is member port mask of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->fid is filtering database of SVLAN member configuration.
 *      - rtk_svlan_memberCfg_t->priority is priority of SVLAN member configuration.
 */
rtk_api_ret_t rtk_svlan_memberPortEntry_adv_set(rtk_uint32 idx, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    rtk_api_ret_t retVal;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtk_uint32 phyMbrPmask;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (idx > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if (pSvlan_cfg->svid>RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    RTK_CHK_PORTMASK_VALID(&(pSvlan_cfg->memberport));

    RTK_CHK_PORTMASK_VALID(&(pSvlan_cfg->untagport));

    if (pSvlan_cfg->fiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->fid > RTL8367C_FIDMAX)
        return RT_ERR_L2_FID;

    if (pSvlan_cfg->priority > RTL8367C_PRIMAX)
        return RT_ERR_VLAN_PRIORITY;

    if (pSvlan_cfg->efiden > ENABLED)
        return RT_ERR_ENABLE;

    if (pSvlan_cfg->efid > RTL8367C_EFIDMAX)
        return RT_ERR_L2_FID;

    memset(&svlanMemConf, 0, sizeof(rtl8367c_svlan_memconf_t));
    svlanMemConf.vs_svid        = pSvlan_cfg->svid;
    if(rtk_switch_portmask_L2P_get(&(pSvlan_cfg->memberport), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    svlanMemConf.vs_member = phyMbrPmask;

    if(rtk_switch_portmask_L2P_get(&(pSvlan_cfg->untagport), &phyMbrPmask) != RT_ERR_OK)
        return RT_ERR_FAILED;

    svlanMemConf.vs_untag = phyMbrPmask;


    svlanMemConf.vs_force_fid   = pSvlan_cfg->fiden;
    svlanMemConf.vs_fid_msti    = pSvlan_cfg->fid;
    svlanMemConf.vs_priority    = pSvlan_cfg->priority;
    svlanMemConf.vs_efiden      = pSvlan_cfg->efiden;
    svlanMemConf.vs_efid        = pSvlan_cfg->efid;

    if(0 == svlanMemConf.vs_svid &&
        0 == svlanMemConf.vs_member &&
        0 == svlanMemConf.vs_untag &&
        0 == svlanMemConf.vs_force_fid &&
        0 == svlanMemConf.vs_fid_msti &&
        0 == svlanMemConf.vs_priority &&
        0 == svlanMemConf.vs_efiden &&
        0 == svlanMemConf.vs_efid)
    {
        svlan_mbrCfgUsage[idx] = FALSE;
        svlan_mbrCfgVid[idx] = 0;
    }
    else
    {
        svlan_mbrCfgUsage[idx] = TRUE;
        svlan_mbrCfgVid[idx] = svlanMemConf.vs_svid;
    }

    if ((retVal = rtl8367c_setAsicSvlanMemberConfiguration(idx, &svlanMemConf)) != RT_ERR_OK)
        return retVal;


    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_memberPortEntry_adv_get
 * Description:
 *      Get SVLAN member Configure by index.
 * Input:
 *      idx         - Index (0 ~ 63)
 * Output:
 *      pSvlan_cfg  - SVLAN member configuration
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can get system 64 accepted s-tag frame format. Only 64 SVID S-tag frame will be accpeted
 *      to receiving from uplink ports. Other SVID S-tag frame or S-untagged frame will be droped.
 */
rtk_api_ret_t rtk_svlan_memberPortEntry_adv_get(rtk_uint32 idx, rtk_svlan_memberCfg_t *pSvlan_cfg)
{
    rtk_api_ret_t retVal;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvlan_cfg)
        return RT_ERR_NULL_POINTER;

    if (idx > RTL8367C_SVIDXMAX)
        return RT_ERR_SVLAN_ENTRY_INDEX;

    if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(idx, &svlanMemConf)) != RT_ERR_OK)
        return retVal;

    pSvlan_cfg->svid        = svlanMemConf.vs_svid;
    if(rtk_switch_portmask_P2L_get(svlanMemConf.vs_member,&(pSvlan_cfg->memberport)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    if(rtk_switch_portmask_P2L_get(svlanMemConf.vs_untag,&(pSvlan_cfg->untagport)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    pSvlan_cfg->fiden       = svlanMemConf.vs_force_fid;
    pSvlan_cfg->fid         = svlanMemConf.vs_fid_msti;
    pSvlan_cfg->priority    = svlanMemConf.vs_priority;
    pSvlan_cfg->efiden      = svlanMemConf.vs_efiden;
    pSvlan_cfg->efid        = svlanMemConf.vs_efid;

    return RT_ERR_OK;

}

/* Function Name:
 *      rtk_svlan_defaultSvlan_set
 * Description:
 *      Configure default egress SVLAN.
 * Input:
 *      port - Source port
 *      svid - SVLAN id
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_INPUT                    - Invalid input parameter.
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 * Note:
 *      The API can set port n S-tag format index while receiving frame from port n
 *      is transmit through uplink port with s-tag field
 */
rtk_api_ret_t rtk_svlan_defaultSvlan_set(rtk_port_t port, rtk_vlan_t svid)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check port Valid */
    RTK_CHK_PORT_VALID(port);

    /* svid must be 0~4095 */
    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            if ((retVal = rtl8367c_setAsicSvlanDefaultVlan(rtk_switch_port_L2P_get(port), i)) != RT_ERR_OK)
                return retVal;

            return RT_ERR_OK;
        }
    }

    return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
}

/* Function Name:
 *      rtk_svlan_defaultSvlan_get
 * Description:
 *      Get the configure default egress SVLAN.
 * Input:
 *      port - Source port
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can get port n S-tag format index while receiving frame from port n
 *      is transmit through uplink port with s-tag field
 */
rtk_api_ret_t rtk_svlan_defaultSvlan_get(rtk_port_t port, rtk_vlan_t *pSvid)
{
    rtk_api_ret_t retVal;
    rtk_uint32 idx;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(port);

    if ((retVal = rtl8367c_getAsicSvlanDefaultVlan(rtk_switch_port_L2P_get(port), &idx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(idx, &svlanMemConf)) != RT_ERR_OK)
        return retVal;

    *pSvid = svlanMemConf.vs_svid;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_c2s_add
 * Description:
 *      Configure SVLAN C2S table
 * Input:
 *      vid - VLAN ID
 *      src_port - Ingress Port
 *      svid - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port ID.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can set system C2S configuration. ASIC will check upstream's VID and assign related
 *      SVID to mathed packet. There are 128 SVLAN C2S configurations.
 */
rtk_api_ret_t rtk_svlan_c2s_add(rtk_vlan_t vid, rtk_port_t src_port, rtk_vlan_t svid)
{
    rtk_api_ret_t retVal, i;
    rtk_uint32 empty_idx;
    rtk_uint32 evid, pmsk, svidx, c2s_svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtk_port_t phyPort;
    rtk_uint16 doneFlag;


    /* Check initialization state */
    RTK_CHK_INIT_STATE();


    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(src_port);

    phyPort = rtk_switch_port_L2P_get(src_port);

    empty_idx = 0xFFFF;
    svidx = 0xFFFF;
    doneFlag = FALSE;

    for (i = 0; i<= RTL8367C_SVIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_VID;

    for (i=RTL8367C_C2SIDXMAX; i>=0; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanC2SConf(i, &evid, &pmsk, &c2s_svidx)) != RT_ERR_OK)
                return retVal;

        if (evid == vid)
        {
            /* Check Src_port */
            if(pmsk & (1 << phyPort))
            {
                /* Check SVIDX */
                if(c2s_svidx == svidx)
                {
                    /* All the same, do nothing */
                }
                else
                {
                    /* New svidx, remove src_port and find a new slot to add a new enrty */
                    pmsk = pmsk & ~(1 << phyPort);
                    if(pmsk == 0)
                        c2s_svidx = 0;

                    if ((retVal = rtl8367c_setAsicSvlanC2SConf(i, vid, pmsk, c2s_svidx)) != RT_ERR_OK)
                        return retVal;
                }
            }
            else
            {
                if(c2s_svidx == svidx && doneFlag == FALSE)
                {
                    pmsk = pmsk | (1 << phyPort);
                    if ((retVal = rtl8367c_setAsicSvlanC2SConf(i, vid, pmsk, svidx)) != RT_ERR_OK)
                        return retVal;

                    doneFlag = TRUE;
                }
            }
        }
        else if (evid==0&&pmsk==0)
        {
            empty_idx = i;
        }
    }

    if (0xFFFF != empty_idx && doneFlag ==FALSE)
    {
       if ((retVal = rtl8367c_setAsicSvlanC2SConf(empty_idx, vid, (1<<phyPort), svidx)) != RT_ERR_OK)
           return retVal;

       return RT_ERR_OK;
    }
    else if(doneFlag == TRUE)
    {
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_c2s_del
 * Description:
 *      Delete one C2S entry
 * Input:
 *      vid - VLAN ID
 *      src_port - Ingress Port
 *      svid - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_VLAN_VID         - Invalid VID parameter.
 *      RT_ERR_PORT_ID          - Invalid port ID.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete system C2S configuration. There are 128 SVLAN C2S configurations.
 */
rtk_api_ret_t rtk_svlan_c2s_del(rtk_vlan_t vid, rtk_port_t src_port)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtk_uint32 evid, pmsk, svidx;
    rtk_port_t phyPort;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (vid > RTL8367C_EVIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(src_port);
    phyPort = rtk_switch_port_L2P_get(src_port);

    for (i = 0; i <= RTL8367C_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanC2SConf(i, &evid, &pmsk, &svidx)) != RT_ERR_OK)
            return retVal;

        if (evid == vid)
        {
            if(pmsk & (1 << phyPort))
            {
                pmsk = pmsk & ~(1 << phyPort);
                if(pmsk == 0)
                {
                    vid = 0;
                    svidx = 0;
                }

                if ((retVal = rtl8367c_setAsicSvlanC2SConf(i, vid, pmsk, svidx)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_c2s_get
 * Description:
 *      Get configure SVLAN C2S table
 * Input:
 *      vid - VLAN ID
 *      src_port - Ingress Port
 * Output:
 *      pSvid - SVLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_PORT_ID      - Invalid port ID.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *     The API can get system C2S configuration. There are 128 SVLAN C2S configurations.
 */
rtk_api_ret_t rtk_svlan_c2s_get(rtk_vlan_t vid, rtk_port_t src_port, rtk_vlan_t *pSvid)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtk_uint32 evid, pmsk, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtk_port_t phyPort;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(src_port);
    phyPort = rtk_switch_port_L2P_get(src_port);

    for (i = 0; i <= RTL8367C_C2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanC2SConf(i, &evid, &pmsk, &svidx)) != RT_ERR_OK)
            return retVal;

        if (evid == vid)
        {
            if(pmsk & (1 << phyPort))
            {
                if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(svidx, &svlanMemConf)) != RT_ERR_OK)
                    return retVal;

                *pSvid = svlanMemConf.vs_svid;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_untag_action_set
 * Description:
 *      Configure Action of downstream UnStag packet
 * Input:
 *      action  - Action for UnStag
 *      svid    - The SVID assigned to UnStag packet
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of downstream Un-Stag packet. A SVID assigned
 *      to the un-stag is also supported by this API. The parameter of svid is
 *      only referenced when the action is set to UNTAG_ASSIGN
 */
rtk_api_ret_t rtk_svlan_untag_action_set(rtk_svlan_untag_action_t action, rtk_vlan_t svid)
{
    rtk_api_ret_t   retVal;
    rtk_uint32      i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (action >= UNTAG_END)
        return RT_ERR_OUT_OF_RANGE;

    if(action == UNTAG_ASSIGN)
    {
        if (svid > RTL8367C_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((retVal = rtl8367c_setAsicSvlanIngressUntag((rtk_uint32)action)) != RT_ERR_OK)
        return retVal;

    if(action == UNTAG_ASSIGN)
    {
        for (i = 0; i < RTL8367C_SVIDXNO; i++)
        {
            if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

            if (svid == svlanMemConf.vs_svid)
            {
                if ((retVal = rtl8367c_setAsicSvlanUntagVlan(i)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
        }

        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_untag_action_get
 * Description:
 *      Get Action of downstream UnStag packet
 * Input:
 *      None
 * Output:
 *      pAction  - Action for UnStag
 *      pSvid    - The SVID assigned to UnStag packet
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can Get action of downstream Un-Stag packet. A SVID assigned
 *      to the un-stag is also retrieved by this API. The parameter pSvid is
 *      only refernced when the action is UNTAG_ASSIGN
 */
rtk_api_ret_t rtk_svlan_untag_action_get(rtk_svlan_untag_action_t *pAction, rtk_vlan_t *pSvid)
{
    rtk_api_ret_t   retVal;
    rtk_uint32      svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pAction || NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanIngressUntag(pAction)) != RT_ERR_OK)
        return retVal;

    if(*pAction == UNTAG_ASSIGN)
    {
        if ((retVal = rtl8367c_getAsicSvlanUntagVlan(&svidx)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(svidx, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        *pSvid = svlanMemConf.vs_svid;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_unmatch_action_set
 * Description:
 *      Configure Action of downstream Unmatch packet
 * Input:
 *      action  - Action for Unmatch
 *      svid    - The SVID assigned to Unmatch packet
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of downstream Un-match packet. A SVID assigned
 *      to the un-match is also supported by this API. The parameter od svid is
 *      only refernced when the action is set to UNMATCH_ASSIGN
 */
rtk_api_ret_t rtk_svlan_unmatch_action_set(rtk_svlan_unmatch_action_t action, rtk_vlan_t svid)
{
    rtk_api_ret_t   retVal;
    rtk_uint32      i;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (action >= UNMATCH_END)
        return RT_ERR_OUT_OF_RANGE;

    if (action == UNMATCH_ASSIGN)
    {
        if (svid > RTL8367C_VIDMAX)
            return RT_ERR_SVLAN_VID;
    }

    if ((retVal = rtl8367c_setAsicSvlanIngressUnmatch((rtk_uint32)action)) != RT_ERR_OK)
        return retVal;

    if(action == UNMATCH_ASSIGN)
    {
        for (i = 0; i < RTL8367C_SVIDXNO; i++)
        {
            if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
                return retVal;

            if (svid == svlanMemConf.vs_svid)
            {
                if ((retVal = rtl8367c_setAsicSvlanUnmatchVlan(i)) != RT_ERR_OK)
                    return retVal;

                return RT_ERR_OK;
            }
        }

        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_unmatch_action_get
 * Description:
 *      Get Action of downstream Unmatch packet
 * Input:
 *      None
 * Output:
 *      pAction  - Action for Unmatch
 *      pSvid    - The SVID assigned to Unmatch packet
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can Get action of downstream Un-match packet. A SVID assigned
 *      to the un-match is also retrieved by this API. The parameter pSvid is
 *      only refernced when the action is UNMATCH_ASSIGN
 */
rtk_api_ret_t rtk_svlan_unmatch_action_get(rtk_svlan_unmatch_action_t *pAction, rtk_vlan_t *pSvid)
{
    rtk_api_ret_t   retVal;
    rtk_uint32      svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pAction || NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicSvlanIngressUnmatch(pAction)) != RT_ERR_OK)
        return retVal;

    if(*pAction == UNMATCH_ASSIGN)
    {
        if ((retVal = rtl8367c_getAsicSvlanUnmatchVlan(&svidx)) != RT_ERR_OK)
            return retVal;

        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(svidx, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        *pSvid = svlanMemConf.vs_svid;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_unassign_action_set
 * Description:
 *      Configure Action of upstream without svid assign action
 * Input:
 *      action  - Action for Un-assign
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can configure action of upstream Un-assign svid packet. If action is not
 *      trap to CPU, the port-based SVID sure be assign as system need
 */
rtk_api_ret_t rtk_svlan_unassign_action_set(rtk_svlan_unassign_action_t action)
{
    rtk_api_ret_t   retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (action >= UNASSIGN_END)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367c_setAsicSvlanEgressUnassign((rtk_uint32)action);

    return retVal;
}

/* Function Name:
 *      rtk_svlan_unassign_action_get
 * Description:
 *      Get action of upstream without svid assignment
 * Input:
 *      None
 * Output:
 *      pAction  - Action for Un-assign
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 * Note:
 *      None
 */
rtk_api_ret_t rtk_svlan_unassign_action_get(rtk_svlan_unassign_action_t *pAction)
{
    rtk_api_ret_t   retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pAction)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367c_getAsicSvlanEgressUnassign(pAction);

    return retVal;
}

/* Function Name:
 *      rtk_svlan_dmac_vidsel_set
 * Description:
 *      Set DMAC CVID selection
 * Input:
 *      port    - Port
 *      enable  - state of DMAC CVID Selection
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      This API can set DMAC CVID Selection state
 */
rtk_api_ret_t rtk_svlan_dmac_vidsel_set(rtk_port_t port, rtk_enable_t enable)
{
    rtk_api_ret_t   retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check port Valid */
    RTK_CHK_PORT_VALID(port);

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicSvlanDmacCvidSel(rtk_switch_port_L2P_get(port), enable)) != RT_ERR_OK)
            return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_dmac_vidsel_get
 * Description:
 *      Get DMAC CVID selection
 * Input:
 *      port    - Port
 * Output:
 *      pEnable - state of DMAC CVID Selection
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      This API can get DMAC CVID Selection state
 */
rtk_api_ret_t rtk_svlan_dmac_vidsel_get(rtk_port_t port, rtk_enable_t *pEnable)
{
    rtk_api_ret_t   retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pEnable)
        return RT_ERR_NULL_POINTER;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(port);

    if ((retVal = rtl8367c_getAsicSvlanDmacCvidSel(rtk_switch_port_L2P_get(port), pEnable)) != RT_ERR_OK)
            return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_svlan_ipmc2s_add
 * Description:
 *      add ip multicast address to SVLAN
 * Input:
 *      svid    - SVLAN VID
 *      ipmc    - ip multicast address
 *      ipmcMsk - ip multicast mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can set IP mutlicast to SVID configuration. If upstream packet is IPv4 multicast
 *      packet and DIP is matched MC2S configuration, ASIC will assign egress SVID to the packet.
 *      There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtk_api_ret_t rtk_svlan_ipmc2s_add(ipaddr_t ipmc, ipaddr_t ipmcMsk,rtk_vlan_t svid)
{
    rtk_api_ret_t retVal, i;
    rtk_uint32 empty_idx;
    rtk_uint32 svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
            return RT_ERR_SVLAN_ENTRY_NOT_FOUND;


    empty_idx = 0xFFFF;

    for (i = RTL8367C_MC2SIDXMAX; i >= 0; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_IP &&
                svlanMC2SConf.sdata==ipmc&&
                svlanMC2SConf.smask==ipmcMsk)
            {
                svlanMC2SConf.svidx = svidx;
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanMC2SConf.valid = TRUE;
        svlanMC2SConf.svidx = svidx;
        svlanMC2SConf.format = SVLAN_MC2S_MODE_IP;
        svlanMC2SConf.sdata = ipmc;
        svlanMC2SConf.smask = ipmcMsk;
        if ((retVal = rtl8367c_setAsicSvlanMC2SConf(empty_idx, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      rtk_svlan_ipmc2s_del
 * Description:
 *      delete ip multicast address to SVLAN
 * Input:
 *      ipmc    - ip multicast address
 *      ipmcMsk - ip multicast mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete IP mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtk_api_ret_t rtk_svlan_ipmc2s_del(ipaddr_t ipmc, ipaddr_t ipmcMsk)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_IP &&
                svlanMC2SConf.sdata==ipmc&&
                svlanMC2SConf.smask==ipmcMsk)
            {
                memset(&svlanMC2SConf, 0, sizeof(rtl8367c_svlan_mc2s_t));
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_ipmc2s_get
 * Description:
 *      Get ip multicast address to SVLAN
 * Input:
 *      ipmc    - ip multicast address
 *      ipmcMsk - ip multicast mask
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *      The API can get IP mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtk_api_ret_t rtk_svlan_ipmc2s_get(ipaddr_t ipmc, ipaddr_t ipmcMsk, rtk_vlan_t *pSvid)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if ((ipmc&0xF0000000)!=0xE0000000)
        return RT_ERR_INPUT;

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid &&
            svlanMC2SConf.format == SVLAN_MC2S_MODE_IP &&
            svlanMC2SConf.sdata == ipmc &&
            svlanMC2SConf.smask == ipmcMsk)
        {
            if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(svlanMC2SConf.svidx, &svlanMemConf)) != RT_ERR_OK)
                return retVal;
            *pSvid = svlanMemConf.vs_svid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_l2mc2s_add
 * Description:
 *      Add L2 multicast address to SVLAN
 * Input:
 *      mac     - L2 multicast address
 *      macMsk  - L2 multicast address mask
 *      svid    - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                       - OK
 *      RT_ERR_FAILED                   - Failed
 *      RT_ERR_SMI                      - SMI access error
 *      RT_ERR_SVLAN_VID                - Invalid SVLAN VID parameter.
 *      RT_ERR_SVLAN_ENTRY_NOT_FOUND    - specified svlan entry not found.
 *      RT_ERR_OUT_OF_RANGE             - input out of range.
 *      RT_ERR_INPUT                    - Invalid input parameters.
 * Note:
 *      The API can set L2 Mutlicast to SVID configuration. If upstream packet is L2 multicast
 *      packet and DMAC is matched, ASIC will assign egress SVID to the packet. There are 32
 *      SVLAN multicast configurations for IP and L2 multicast.
 */
rtk_api_ret_t rtk_svlan_l2mc2s_add(rtk_mac_t mac, rtk_mac_t macMsk, rtk_vlan_t svid)
{
    rtk_api_ret_t retVal, i;
    rtk_uint32 empty_idx;
    rtk_uint32 svidx, l2add, l2Mask;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    l2add = (mac.octet[2] << 24) | (mac.octet[3] << 16) | (mac.octet[4] << 8) | mac.octet[5];
    l2Mask = (macMsk.octet[2] << 24) | (macMsk.octet[3] << 16) | (macMsk.octet[4] << 8) | macMsk.octet[5];

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    empty_idx = 0xFFFF;

    for (i = RTL8367C_MC2SIDXMAX; i >=0; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC &&
                svlanMC2SConf.sdata==l2add&&
                svlanMC2SConf.smask==l2Mask)
            {
                svlanMC2SConf.svidx = svidx;
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
            }
        }
        else
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanMC2SConf.valid = TRUE;
        svlanMC2SConf.svidx = svidx;
        svlanMC2SConf.format = SVLAN_MC2S_MODE_MAC;
        svlanMC2SConf.sdata = l2add;
        svlanMC2SConf.smask = l2Mask;

        if ((retVal = rtl8367c_setAsicSvlanMC2SConf(empty_idx, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_l2mc2s_del
 * Description:
 *      delete L2 multicast address to SVLAN
 * Input:
 *      mac     - L2 multicast address
 *      macMsk  - L2 multicast address mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_SVLAN_VID        - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can delete Mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtk_api_ret_t rtk_svlan_l2mc2s_del(rtk_mac_t mac, rtk_mac_t macMsk)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtk_uint32 l2add, l2Mask;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    l2add = (mac.octet[2] << 24) | (mac.octet[3] << 16) | (mac.octet[4] << 8) | mac.octet[5];
    l2Mask = (macMsk.octet[2] << 24) | (macMsk.octet[3] << 16) | (macMsk.octet[4] << 8) | macMsk.octet[5];

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC &&
                svlanMC2SConf.sdata==l2add&&
                svlanMC2SConf.smask==l2Mask)
            {
                memset(&svlanMC2SConf, 0, sizeof(rtl8367c_svlan_mc2s_t));
                if ((retVal = rtl8367c_setAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
                    return retVal;
                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_l2mc2s_get
 * Description:
 *      Get L2 multicast address to SVLAN
 * Input:
 *      mac     - L2 multicast address
 *      macMsk  - L2 multicast address mask
 * Output:
 *      pSvid - SVLAN VID
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT            - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE     - input out of range.
 * Note:
 *      The API can get L2 mutlicast to SVID configuration. There are 32 SVLAN multicast configurations for IP and L2 multicast.
 */
rtk_api_ret_t rtk_svlan_l2mc2s_get(rtk_mac_t mac, rtk_mac_t macMsk, rtk_vlan_t *pSvid)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i;
    rtk_uint32 l2add,l2Mask;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_mc2s_t svlanMC2SConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pSvid)
        return RT_ERR_NULL_POINTER;

    if (mac.octet[0]!= 1&&mac.octet[1]!=0)
        return RT_ERR_INPUT;

    l2add = (mac.octet[2] << 24) | (mac.octet[3] << 16) | (mac.octet[4] << 8) | mac.octet[5];
    l2Mask = (macMsk.octet[2] << 24) | (macMsk.octet[3] << 16) | (macMsk.octet[4] << 8) | macMsk.octet[5];

    for (i = 0; i <= RTL8367C_MC2SIDXMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMC2SConf(i, &svlanMC2SConf)) != RT_ERR_OK)
            return retVal;

        if (TRUE == svlanMC2SConf.valid)
        {
            if (svlanMC2SConf.format == SVLAN_MC2S_MODE_MAC &&
                svlanMC2SConf.sdata==l2add&&
                svlanMC2SConf.smask==l2Mask)
            {
                if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(svlanMC2SConf.svidx, &svlanMemConf)) != RT_ERR_OK)
                    return retVal;
                *pSvid = svlanMemConf.vs_svid;

                return RT_ERR_OK;
            }
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_sp2c_add
 * Description:
 *      Add system SP2C configuration
 * Input:
 *      cvid        - VLAN ID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 *      svid        - SVLAN VID
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_VLAN_VID     - Invalid VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      The API can add SVID & Destination Port to CVLAN configuration. The downstream frames with assigned
 *      SVID will be add C-tag with assigned CVID if the output port is the assigned destination port.
 *      There are 128 SP2C configurations.
 */
rtk_api_ret_t rtk_svlan_sp2c_add(rtk_vlan_t svid, rtk_port_t dst_port, rtk_vlan_t cvid)
{
    rtk_api_ret_t retVal, i;
    rtk_uint32 empty_idx, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;
    rtk_port_t port;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    if (cvid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(dst_port);
    port = rtk_switch_port_L2P_get(dst_port);

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    empty_idx = 0xFFFF;

    for (i=RTL8367C_SP2CMAX; i >=0 ; i--)
    {
        if ((retVal = rtl8367c_getAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == port) && (svlanSP2CConf.valid == 1))
        {
            empty_idx = i;
            break;
        }
        else if (svlanSP2CConf.valid == 0)
        {
            empty_idx = i;
        }
    }

    if (empty_idx!=0xFFFF)
    {
        svlanSP2CConf.valid     = 1;
        svlanSP2CConf.vid       = cvid;
        svlanSP2CConf.svidx     = svidx;
        svlanSP2CConf.dstport   = port;

        if ((retVal = rtl8367c_setAsicSvlanSP2CConf(empty_idx, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;
        return RT_ERR_OK;
    }

    return RT_ERR_OUT_OF_RANGE;

}

/* Function Name:
 *      rtk_svlan_sp2c_get
 * Description:
 *      Get configure system SP2C content
 * Input:
 *      svid 	    - SVLAN VID
 *      dst_port 	- Destination port of SVLAN to CVLAN configuration
 * Output:
 *      pCvid - VLAN ID
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 * Note:
 *     The API can get SVID & Destination Port to CVLAN configuration. There are 128 SP2C configurations.
 */
rtk_api_ret_t rtk_svlan_sp2c_get(rtk_vlan_t svid, rtk_port_t dst_port, rtk_vlan_t *pCvid)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pCvid)
        return RT_ERR_NULL_POINTER;

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(dst_port);
    dst_port = rtk_switch_port_L2P_get(dst_port);

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    for (i = 0; i <= RTL8367C_SP2CMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1) )
        {
            *pCvid = svlanSP2CConf.vid;
            return RT_ERR_OK;
        }
    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_sp2c_del
 * Description:
 *      Delete system SP2C configuration
 * Input:
 *      svid        - SVLAN VID
 *      dst_port    - Destination port of SVLAN to CVLAN configuration
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port number.
 *      RT_ERR_SVLAN_VID    - Invalid SVLAN VID parameter.
 *      RT_ERR_OUT_OF_RANGE - input out of range.
 * Note:
 *      The API can delete SVID & Destination Port to CVLAN configuration. There are 128 SP2C configurations.
 */
rtk_api_ret_t rtk_svlan_sp2c_del(rtk_vlan_t svid, rtk_port_t dst_port)
{
    rtk_api_ret_t retVal;
    rtk_uint32 i, svidx;
    rtl8367c_svlan_memconf_t svlanMemConf;
    rtl8367c_svlan_s2c_t svlanSP2CConf;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (svid > RTL8367C_VIDMAX)
        return RT_ERR_SVLAN_VID;

    /* Check port Valid */
    RTK_CHK_PORT_VALID(dst_port);
    dst_port = rtk_switch_port_L2P_get(dst_port);

    svidx = 0xFFFF;

    for (i = 0; i < RTL8367C_SVIDXNO; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanMemberConfiguration(i, &svlanMemConf)) != RT_ERR_OK)
            return retVal;

        if (svid == svlanMemConf.vs_svid)
        {
            svidx = i;
            break;
        }
    }

    if (0xFFFF == svidx)
        return RT_ERR_SVLAN_ENTRY_NOT_FOUND;

    for (i = 0; i <= RTL8367C_SP2CMAX; i++)
    {
        if ((retVal = rtl8367c_getAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
            return retVal;

        if ( (svlanSP2CConf.svidx == svidx) && (svlanSP2CConf.dstport == dst_port) && (svlanSP2CConf.valid == 1) )
        {
            svlanSP2CConf.valid     = 0;
            svlanSP2CConf.vid       = 0;
            svlanSP2CConf.svidx     = 0;
            svlanSP2CConf.dstport   = 0;

            if ((retVal = rtl8367c_setAsicSvlanSP2CConf(i, &svlanSP2CConf)) != RT_ERR_OK)
                return retVal;
            return RT_ERR_OK;
        }

    }

    return RT_ERR_OUT_OF_RANGE;
}

/* Function Name:
 *      rtk_svlan_lookupType_set
 * Description:
 *      Set lookup type of SVLAN
 * Input:
 *      type 		- lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      none
 */
rtk_api_ret_t rtk_svlan_lookupType_set(rtk_svlan_lookupType_t type)
{
    rtk_api_ret_t   retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (type >= SVLAN_LOOKUP_END)
        return RT_ERR_CHIP_NOT_SUPPORTED;


    svlan_lookupType = type;

    retVal = rtl8367c_setAsicSvlanLookupType((rtk_uint32)type);

    return retVal;
}

/* Function Name:
 *      rtk_svlan_lookupType_get
 * Description:
 *      Get lookup type of SVLAN
 * Input:
 *      pType 		- lookup type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 * Note:
 *      none
 */
rtk_api_ret_t rtk_svlan_lookupType_get(rtk_svlan_lookupType_t *pType)
{
    rtk_api_ret_t   retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pType)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367c_getAsicSvlanLookupType(pType);

    svlan_lookupType = *pType;

    return retVal;
}

/* Function Name:
 *      rtk_svlan_trapPri_set
 * Description:
 *      Set svlan trap priority
 * Input:
 *      priority - priority for trap packets
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_QOS_INT_PRIORITY
 * Note:
 *      None
 */
rtk_api_ret_t rtk_svlan_trapPri_set(rtk_pri_t priority)
{
    rtk_api_ret_t   retVal;

    RTK_CHK_INIT_STATE();

    if(priority > RTL8367C_PRIMAX)
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367c_setAsicSvlanTrapPriority(priority);

    return retVal;
}   /* end of rtk_svlan_trapPri_set */

/* Function Name:
 *      rtk_svlan_trapPri_get
 * Description:
 *      Get svlan trap priority
 * Input:
 *      None
 * Output:
 *      pPriority - priority for trap packets
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NULL_POINTER - input parameter may be null pointer
 * Note:
 *      None
 */
rtk_api_ret_t rtk_svlan_trapPri_get(rtk_pri_t *pPriority)
{
    rtk_api_ret_t   retVal;

    RTK_CHK_INIT_STATE();

    if(NULL == pPriority)
        return RT_ERR_NULL_POINTER;

    retVal = rtl8367c_getAsicSvlanTrapPriority(pPriority);

    return retVal;
}   /* end of rtk_svlan_trapPri_get */


/* Function Name:
 *      rtk_svlan_checkAndCreateMbr
 * Description:
 *      Check and create Member configuration and return index
 * Input:
 *      vid  - VLAN id.
 * Output:
 *      pIndex  - Member configuration index
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_VLAN_VID     - Invalid VLAN ID.
 *      RT_ERR_TBL_FULL     - Member Configuration table full
 * Note:
 *
 */
rtk_api_ret_t rtk_svlan_checkAndCreateMbr(rtk_vlan_t vid, rtk_uint32 *pIndex)
{
    rtk_api_ret_t retVal;
    rtk_uint32 svidx;
    rtk_uint32 empty_idx = 0xFFFF;
    rtl8367c_svlan_memconf_t svlan_cfg;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* vid must be 0~4095 */
    if (vid > RTL8367C_VIDMAX)
        return RT_ERR_VLAN_VID;

    /* Null pointer check */
    if(NULL == pIndex)
        return RT_ERR_NULL_POINTER;

    /* Search exist entry */
    for (svidx = 0; svidx <= RTL8367C_SVIDXMAX; svidx++)
    {
        if(svlan_mbrCfgUsage[svidx] == TRUE)
        {
            if(svlan_mbrCfgVid[svidx] == vid)
            {
                /* Found! return index */
                *pIndex = svidx;
                return RT_ERR_OK;
            }
        }
        else if(empty_idx == 0xFFFF)
        {
            empty_idx = svidx;
        }

    }

    if(empty_idx == 0xFFFF)
    {
        /* No empty index */
        return RT_ERR_TBL_FULL;
    }

    svlan_mbrCfgUsage[svidx] = TRUE;
    svlan_mbrCfgVid[svidx] = vid;

    memset(&svlan_cfg, 0, sizeof(rtl8367c_svlan_memconf_t));

    svlan_cfg.vs_svid = vid;
    /*for create check*/
    if(vid == 0)
    {
        svlan_cfg.vs_efid = 1;
    }

    if((retVal = rtl8367c_setAsicSvlanMemberConfiguration(empty_idx, &svlan_cfg)) != RT_ERR_OK)
        return retVal;

    *pIndex = empty_idx;
    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicCputagEnable
 * Description:
 *      Set cpu tag function enable/disable
 * Input:
 *      enabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_ENABLE  	- Invalid enable/disable input
 * Note:
 *      If CPU tag function is disabled, CPU tag will not be added to frame
 *    	forwarded to CPU port, and all ports cannot parse CPU tag.
 */
ret_t rtl8367c_setAsicCputagEnable(rtk_uint32 enabled)
{
    if(enabled > 1)
        return RT_ERR_ENABLE;

    return rtl8367c_setAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_EN_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicCputagEnable
 * Description:
 *      Get cpu tag function enable/disable
 * Input:
 *      pEnabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicCputagEnable(rtk_uint32 *pEnabled)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_EN_OFFSET, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicCputagTrapPort
 * Description:
 *      Set cpu tag trap port
 * Input:
 *      port - port number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *     API can set destination port of trapping frame
 */
ret_t rtl8367c_setAsicCputagTrapPort(rtk_uint32 port)
{
    ret_t retVal;
    
    if(port >= RTL8367C_PORTNO)
        return RT_ERR_PORT_ID;

    retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TRAP_PORT_MASK, port & 7);
    if(retVal != RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TRAP_PORT_EXT_MASK, (port>>3) & 1);
    if(retVal != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicCputagTrapPort
 * Description:
 *      Get cpu tag trap port
 * Input:
 *      pPort - port number
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *     None
 */
ret_t rtl8367c_getAsicCputagTrapPort(rtk_uint32 *pPort)
{
    ret_t retVal;
    rtk_uint32 tmpPort;
    
    retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TRAP_PORT_MASK, &tmpPort);
    if(retVal != RT_ERR_OK)
        return retVal;
    *pPort = tmpPort;

    retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TRAP_PORT_EXT_MASK, &tmpPort);
    if(retVal != RT_ERR_OK)
        return retVal;
    *pPort |= (tmpPort & 1) << 3;

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicCputagPortmask
 * Description:
 *      Set ports that can parse CPU tag
 * Input:
 *      portmask - port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_PORT_MASK  	- Invalid portmask
 * Note:
 *     None
 */
ret_t rtl8367c_setAsicCputagPortmask(rtk_uint32 portmask)
{
    if(portmask > RTL8367C_PORTMASK)
        return RT_ERR_PORT_MASK;

    return rtl8367c_setAsicReg(RTL8367C_CPU_PORT_MASK_REG, portmask);
}
/* Function Name:
 *      rtl8367c_getAsicCputagPortmask
 * Description:
 *      Get ports that can parse CPU tag
 * Input:
 *      pPortmask - port mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 * Note:
 *     None
 */
ret_t rtl8367c_getAsicCputagPortmask(rtk_uint32 *pPortmask)
{
    return rtl8367c_getAsicReg(RTL8367C_CPU_PORT_MASK_REG, pPortmask);
}
/* Function Name:
 *      rtl8367c_setAsicCputagInsertMode
 * Description:
 *      Set CPU-tag insert mode
 * Input:
 *      mode - 0: insert to all packets; 1: insert to trapped packets; 2: don't insert
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_NOT_ALLOWED  - Actions not allowed by the function
 * Note:
 *     None
 */
ret_t rtl8367c_setAsicCputagInsertMode(rtk_uint32 mode)
{
    if(mode >= CPUTAG_INSERT_END)
        return RT_ERR_NOT_ALLOWED;

    return rtl8367c_setAsicRegBits(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_INSERTMODE_MASK, mode);
}
/* Function Name:
 *      rtl8367c_getAsicCputagInsertMode
 * Description:
 *      Get CPU-tag insert mode
 * Input:
 *      pMode - 0: insert to all packets; 1: insert to trapped packets; 2: don't insert
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 * Note:
 *     None
 */
ret_t rtl8367c_getAsicCputagInsertMode(rtk_uint32 *pMode)
{
    return rtl8367c_getAsicRegBits(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_INSERTMODE_MASK, pMode);
}
/* Function Name:
 *      rtl8367c_setAsicCputagPriorityRemapping
 * Description:
 *      Set queue assignment of CPU port
 * Input:
 *      srcPri - internal priority (0~7)
 *      newPri - internal priority after remapping (0~7)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_QOS_INT_PRIORITY  	- Invalid priority
 * Note:
 *     None
 */
ret_t rtl8367c_setAsicCputagPriorityRemapping(rtk_uint32 srcPri, rtk_uint32 newPri)
{
    if((srcPri > RTL8367C_PRIMAX) || (newPri > RTL8367C_PRIMAX))
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_setAsicRegBits(RTL8367C_QOS_PRIPORITY_REMAPPING_IN_CPU_REG(srcPri), RTL8367C_QOS_PRIPORITY_REMAPPING_IN_CPU_MASK(srcPri), newPri);
}
/* Function Name:
 *      rtl8367c_getAsicCputagPriorityRemapping
 * Description:
 *      Get queue assignment of CPU port
 * Input:
 *      srcPri - internal priority (0~7)
 *      pNewPri - internal priority after remapping (0~7)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 *      RT_ERR_QOS_INT_PRIORITY  	- Invalid priority
 * Note:
 *     None
 */
ret_t rtl8367c_getAsicCputagPriorityRemapping(rtk_uint32 srcPri, rtk_uint32 *pNewPri)
{
    if(srcPri > RTL8367C_PRIMAX)
        return RT_ERR_QOS_INT_PRIORITY;

    return rtl8367c_getAsicRegBits(RTL8367C_QOS_PRIPORITY_REMAPPING_IN_CPU_REG(srcPri), RTL8367C_QOS_PRIPORITY_REMAPPING_IN_CPU_MASK(srcPri), pNewPri);
}
/* Function Name:
 *      rtl8367c_setAsicCputagPosition
 * Description:
 *      Set cpu tag insert position
 * Input:
 *      postion - 1: After entire packet(before CRC field), 0: After MAC_SA (Default)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 * Note:
 *     None
 */
ret_t rtl8367c_setAsicCputagPosition(rtk_uint32 postion)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TAG_POSITION_OFFSET, postion);
}
/* Function Name:
 *      rtl8367c_getAsicCputagPosition
 * Description:
 *      Get cpu tag insert position
 * Input:
 *      pPostion - 1: After entire packet(before CRC field), 0: After MAC_SA (Default)
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 					- Success
 *      RT_ERR_SMI  				- SMI access error
 * Note:
 *     None
 */
ret_t rtl8367c_getAsicCputagPosition(rtk_uint32* pPostion)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TAG_POSITION_OFFSET, pPostion);
}

/* Function Name:
 *      rtl8367c_setAsicCputagMode
 * Description:
 *      Set cpu tag mode
 * Input:
 *      mode - 1: 4bytes mode, 0: 8bytes mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_INPUT 	- Invalid input parameters
 * Note:
 *      If CPU tag function is disabled, CPU tag will not be added to frame
 *    	forwarded to CPU port, and all ports cannot parse CPU tag.
 */
ret_t rtl8367c_setAsicCputagMode(rtk_uint32 mode)
{
    if(mode > 1)
        return RT_ERR_INPUT;

    return rtl8367c_setAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TAG_FORMAT_OFFSET, mode);
}
/* Function Name:
 *      rtl8367c_getAsicCputagMode
 * Description:
 *      Get cpu tag mode
 * Input:
 *      pMode - 1: 4bytes mode, 0: 8bytes mode
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicCputagMode(rtk_uint32 *pMode)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TAG_FORMAT_OFFSET, pMode);
}
/* Function Name:
 *      rtl8367c_setAsicCputagRxMinLength
 * Description:
 *      Set cpu tag mode
 * Input:
 *      mode - 1: 64bytes, 0: 72bytes
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_INPUT 	- Invalid input parameters
 * Note:
 *      If CPU tag function is disabled, CPU tag will not be added to frame
 *    	forwarded to CPU port, and all ports cannot parse CPU tag.
 */
ret_t rtl8367c_setAsicCputagRxMinLength(rtk_uint32 mode)
{
    if(mode > 1)
        return RT_ERR_INPUT;

    return rtl8367c_setAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TAG_RXBYTECOUNT_OFFSET, mode);
}
/* Function Name:
 *      rtl8367c_getAsicCputagRxMinLength
 * Description:
 *      Get cpu tag mode
 * Input:
 *      pMode - 1: 64bytes, 0: 72bytes
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicCputagRxMinLength(rtk_uint32 *pMode)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_CPU_CTRL, RTL8367C_CPU_TAG_RXBYTECOUNT_OFFSET, pMode);
}

/* Function Name:
 *      rtl8367c_setAsicFieldSelector
 * Description:
 *      Set user defined field selectors in HSB
 * Input:
 *      index 		- index of field selector 0-15
 *      format 		- Format of field selector
 *      offset 		- Retrieving data offset
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 *      RT_ERR_OUT_OF_RANGE - input parameter out of range
 * Note:
 *      System support 16 user defined field selctors.
 * 		Each selector can be enabled or disable. User can defined retrieving 16-bits in many predefiend
 * 		standard l2/l3/l4 payload.
 */
ret_t rtl8367c_setAsicFieldSelector(rtk_uint32 index, rtk_uint32 format, rtk_uint32 offset)
{
	rtk_uint32 regData;

	if(index > RTL8367C_FIELDSEL_FORMAT_NUMBER)
		return RT_ERR_OUT_OF_RANGE;

	if(format >= FIELDSEL_FORMAT_END)
		return RT_ERR_OUT_OF_RANGE;

	regData = (((format << RTL8367C_FIELD_SELECTOR_FORMAT_OFFSET) & RTL8367C_FIELD_SELECTOR_FORMAT_MASK ) |
			   ((offset << RTL8367C_FIELD_SELECTOR_OFFSET_OFFSET) & RTL8367C_FIELD_SELECTOR_OFFSET_MASK ));

    return rtl8367c_setAsicReg(RTL8367C_FIELD_SELECTOR_REG(index), regData);
}
/* Function Name:
 *      rtl8367c_getAsicFieldSelector
 * Description:
 *      Get user defined field selectors in HSB
 * Input:
 *      index 	    - index of field selector 0-15
 *      pFormat 	- Format of field selector
 *      pOffset 	- Retrieving data offset
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicFieldSelector(rtk_uint32 index, rtk_uint32* pFormat, rtk_uint32* pOffset)
{
    ret_t retVal;
	rtk_uint32 regData;

    retVal = rtl8367c_getAsicReg(RTL8367C_FIELD_SELECTOR_REG(index), &regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	*pFormat    = ((regData & RTL8367C_FIELD_SELECTOR_FORMAT_MASK) >> RTL8367C_FIELD_SELECTOR_FORMAT_OFFSET);
	*pOffset    = ((regData & RTL8367C_FIELD_SELECTOR_OFFSET_MASK) >> RTL8367C_FIELD_SELECTOR_OFFSET_OFFSET);

    return RT_ERR_OK;
}

/*
	Exchange structure type define with MMI and SMI
*/
static void _rtl8367c_aclRuleStSmi2User( rtl8367c_aclrule *pAclUser, rtl8367c_aclrulesmi *pAclSmi)
{
    rtk_uint8 *care_ptr, *data_ptr;
    rtk_uint8 care_tmp, data_tmp;
    rtk_uint32 i;

	pAclUser->data_bits.active_portmsk = (((pAclSmi->data_bits_ext.rule_info >> 1) & 0x0007) << 8) | ((pAclSmi->data_bits.rule_info >> 8) & 0x00FF);
	pAclUser->data_bits.type = (pAclSmi->data_bits.rule_info & 0x0007);
	pAclUser->data_bits.tag_exist = (pAclSmi->data_bits.rule_info & 0x00F8) >> 3;

    care_ptr = (rtk_uint8*)&pAclSmi->care_bits;
    data_ptr = (rtk_uint8*)&pAclSmi->data_bits;

    for ( i = 0; i < sizeof(struct acl_rule_smi_st); i++)
    {
        care_tmp = *(care_ptr + i) ^ (*(data_ptr + i));
        data_tmp = *(data_ptr + i);

        *(care_ptr + i) = care_tmp;
        *(data_ptr + i) = data_tmp;
    }

    care_ptr = (rtk_uint8*)&pAclSmi->care_bits_ext;
    data_ptr = (rtk_uint8*)&pAclSmi->data_bits_ext;
    care_tmp = (*care_ptr) ^ (*data_ptr);
    data_tmp = (*data_ptr);
    *care_ptr = care_tmp;
    *data_ptr = data_tmp;

	for(i = 0; i < RTL8367C_ACLRULEFIELDNO; i++)
		pAclUser->data_bits.field[i] = pAclSmi->data_bits.field[i];

	pAclUser->valid = pAclSmi->valid;

    pAclUser->care_bits.active_portmsk = (((pAclSmi->care_bits_ext.rule_info >> 1) & 0x0007) << 8) | ((pAclSmi->care_bits.rule_info >> 8) & 0x00FF);
	pAclUser->care_bits.type = (pAclSmi->care_bits.rule_info & 0x0007);
	pAclUser->care_bits.tag_exist = (pAclSmi->care_bits.rule_info & 0x00F8) >> 3;

	for(i = 0; i < RTL8367C_ACLRULEFIELDNO; i++)
		pAclUser->care_bits.field[i] = pAclSmi->care_bits.field[i];
}

/*
	Exchange structure type define with MMI and SMI
*/
static void _rtl8367c_aclRuleStUser2Smi(rtl8367c_aclrule *pAclUser, rtl8367c_aclrulesmi *pAclSmi)
{
    rtk_uint8 *care_ptr, *data_ptr;
    rtk_uint8 care_tmp, data_tmp;
    rtk_uint32 i;

	pAclSmi->data_bits_ext.rule_info = ((pAclUser->data_bits.active_portmsk >> 8) & 0x7) << 1;
    pAclSmi->data_bits.rule_info = ((pAclUser->data_bits.active_portmsk & 0xff) << 8) | ((pAclUser->data_bits.tag_exist & 0x1F) << 3) | (pAclUser->data_bits.type & 0x07);

	for(i = 0;i < RTL8367C_ACLRULEFIELDNO; i++)
		pAclSmi->data_bits.field[i] = pAclUser->data_bits.field[i];

	pAclSmi->valid = pAclUser->valid;

	pAclSmi->care_bits_ext.rule_info = ((pAclUser->care_bits.active_portmsk >> 8) & 0x7) << 1;
    pAclSmi->care_bits.rule_info = ((pAclUser->care_bits.active_portmsk & 0xff) << 8) | ((pAclUser->care_bits.tag_exist & 0x1F) << 3) | (pAclUser->care_bits.type & 0x07);

	for(i = 0; i < RTL8367C_ACLRULEFIELDNO; i++)
		pAclSmi->care_bits.field[i] = pAclUser->care_bits.field[i];

    care_ptr = (rtk_uint8*)&pAclSmi->care_bits;
    data_ptr = (rtk_uint8*)&pAclSmi->data_bits;

    for ( i = 0; i < sizeof(struct acl_rule_smi_st); i++)
    {
        care_tmp = *(care_ptr + i) & ~(*(data_ptr + i));
        data_tmp = *(care_ptr + i) & *(data_ptr + i);

        *(care_ptr + i) = care_tmp;
        *(data_ptr + i) = data_tmp;
    }

	care_ptr = (rtk_uint8*)&pAclSmi->care_bits_ext;
    data_ptr = (rtk_uint8*)&pAclSmi->data_bits_ext;
	care_tmp = *care_ptr & ~(*data_ptr);
	data_tmp = *care_ptr & *data_ptr;

	*care_ptr = care_tmp;
	*data_ptr = data_tmp;
}

/*
	Exchange structure type define with MMI and SMI
*/
static void _rtl8367c_aclActStSmi2User(rtl8367c_acl_act_t *pAclUser, rtk_uint16 *pAclSmi)
{
    pAclUser->cact = (pAclSmi[0] & 0x00C0) >> 6;
    pAclUser->cvidx_cact = (pAclSmi[0] & 0x003F) | (((pAclSmi[3] & 0x0008) >> 3) << 6);

    pAclUser->sact = (pAclSmi[0] & 0xC000) >> 14;
    pAclUser->svidx_sact = ((pAclSmi[0] & 0x3F00) >> 8) | (((pAclSmi[3] & 0x0010) >> 4) << 6);

    pAclUser->aclmeteridx = (pAclSmi[1] & 0x003F) | (((pAclSmi[3] & 0x0020) >> 5) << 6);

    pAclUser->fwdact = (pAclSmi[1] & 0xC000) >> 14;
    pAclUser->fwdpmask = ((pAclSmi[1] & 0x3FC0) >> 6) | (((pAclSmi[3] & 0x01C0) >> 6) << 8);

    pAclUser->priact = (pAclSmi[2] & 0x00C0) >> 6;
    pAclUser->pridx = (pAclSmi[2] & 0x003F) | (((pAclSmi[3] & 0x0200) >> 9) << 6);

    pAclUser->aclint = (pAclSmi[2] & 0x2000) >> 13;
    pAclUser->gpio_en = (pAclSmi[2] & 0x1000) >> 12;
    pAclUser->gpio_pin = (pAclSmi[2] & 0x0F00) >> 8;

    pAclUser->cact_ext = (pAclSmi[2] & 0xC000) >> 14;
    pAclUser->tag_fmt = (pAclSmi[3] & 0x0003);
    pAclUser->fwdact_ext = (pAclSmi[3] & 0x0004) >> 2;
}

/*
	Exchange structure type define with MMI and SMI
*/
static void _rtl8367c_aclActStUser2Smi(rtl8367c_acl_act_t *pAclUser, rtk_uint16 *pAclSmi)
{
    pAclSmi[0] |= (pAclUser->cvidx_cact & 0x003F);
    pAclSmi[0] |= (pAclUser->cact & 0x0003) << 6;
    pAclSmi[0] |= (pAclUser->svidx_sact & 0x003F) << 8;
    pAclSmi[0] |= (pAclUser->sact & 0x0003) << 14;

    pAclSmi[1] |= (pAclUser->aclmeteridx & 0x003F);
    pAclSmi[1] |= (pAclUser->fwdpmask & 0x00FF) << 6;
    pAclSmi[1] |= (pAclUser->fwdact & 0x0003) << 14;

    pAclSmi[2] |= (pAclUser->pridx & 0x003F);
    pAclSmi[2] |= (pAclUser->priact & 0x0003) << 6;
    pAclSmi[2] |= (pAclUser->gpio_pin & 0x000F) << 8;
    pAclSmi[2] |= (pAclUser->gpio_en & 0x0001) << 12;
    pAclSmi[2] |= (pAclUser->aclint & 0x0001) << 13;
    pAclSmi[2] |= (pAclUser->cact_ext & 0x0003) << 14;

    pAclSmi[3] |= (pAclUser->tag_fmt & 0x0003);
    pAclSmi[3] |= (pAclUser->fwdact_ext & 0x0001) << 2;
    pAclSmi[3] |= ((pAclUser->cvidx_cact & 0x0040) >> 6) << 3;
    pAclSmi[3] |= ((pAclUser->svidx_sact & 0x0040) >> 6) << 4;
    pAclSmi[3] |= ((pAclUser->aclmeteridx & 0x0040) >> 6) << 5;
    pAclSmi[3] |= ((pAclUser->fwdpmask & 0x0700) >> 8) << 6;
    pAclSmi[3] |= ((pAclUser->pridx & 0x0040) >> 6) << 9;
}

/* Function Name:
 *      rtl8367c_setAsicAcl
 * Description:
 *      Set port acl function enable/disable
 * Input:
 *      port 	- Physical port number (0~10)
 *      enabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicAcl(rtk_uint32 port, rtk_uint32 enabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	return rtl8367c_setAsicRegBit(RTL8367C_ACL_ENABLE_REG, port, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicAcl
 * Description:
 *      Get port acl function enable/disable
 * Input:
 *      port 	- Physical port number (0~10)
 *      enabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicAcl(rtk_uint32 port, rtk_uint32* pEnabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	return rtl8367c_getAsicRegBit(RTL8367C_ACL_ENABLE_REG, port, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicAclUnmatchedPermit
 * Description:
 *      Set port acl function unmatched permit action
 * Input:
 *      port 	- Physical port number (0~10)
 *      enabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicAclUnmatchedPermit(rtk_uint32 port, rtk_uint32 enabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	return rtl8367c_setAsicRegBit(RTL8367C_ACL_UNMATCH_PERMIT_REG, port, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicAclUnmatchedPermit
 * Description:
 *      Get port acl function unmatched permit action
 * Input:
 *      port 	- Physical port number (0~10)
 *      enabled - 1: enabled, 0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 *      RT_ERR_PORT_ID  - Invalid port number
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicAclUnmatchedPermit(rtk_uint32 port, rtk_uint32* pEnabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;

	return rtl8367c_getAsicRegBit(RTL8367C_ACL_UNMATCH_PERMIT_REG, port, pEnabled);
}

/* Function Name:
 *      rtl8367c_setAsicAclRule
 * Description:
 *      Set acl rule content
 * Input:
 *      index 	- ACL rule index (0-95) of 96 ACL rules
 *      pAclRule - ACL rule stucture for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
 * Note:
 *		System supported 95 shared 289-bit ACL ingress rule. Index was available at range 0-95 only.
 *		If software want to modify ACL rule, the ACL function should be disable at first or unspecify
 *		acl action will be executed.
 *		One ACL rule structure has three parts setting:
 *		Bit 0-147		Data Bits of this Rule
 *		Bit	148		Valid Bit
 *		Bit 149-296	Care Bits of this Rule
 *		There are four kinds of field in Data Bits and Care Bits: Active Portmask, Type, Tag Exist, and 8 fields
 */
ret_t rtl8367c_setAsicAclRule(rtk_uint32 index, rtl8367c_aclrule* pAclRule)
{
	rtl8367c_aclrulesmi aclRuleSmi;
	rtk_uint16* tableAddr;
	rtk_uint32 regAddr;
	rtk_uint32	regData;
	rtk_uint32 i;
	ret_t retVal;

	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

    memset(&aclRuleSmi, 0x00, sizeof(rtl8367c_aclrulesmi));

 	_rtl8367c_aclRuleStUser2Smi(pAclRule, &aclRuleSmi);

    /* Write valid bit = 0 */
    regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
    if(index >= 64)
        regData = RTL8367C_ACLRULETBADDR2(DATABITS, index);
    else
        regData = RTL8367C_ACLRULETBADDR(DATABITS, index);
    retVal = rtl8367c_setAsicReg(regAddr,regData);
    if(retVal !=RT_ERR_OK)
        return retVal;

    retVal = rtl8367c_setAsicRegBits(RTL8367C_TABLE_ACCESS_WRDATA_REG(RTL8367C_ACLRULETBLEN), 0x1, 0);
    if(retVal !=RT_ERR_OK)
        return retVal;

    regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
    regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_WRITE, TB_TARGET_ACLRULE);
    retVal = rtl8367c_setAsicReg(regAddr, regData);
    if(retVal !=RT_ERR_OK)
        return retVal;



  	/* Write ACS_ADR register */
	regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
    if(index >= 64)
	    regData = RTL8367C_ACLRULETBADDR2(CAREBITS, index);
    else
	    regData = RTL8367C_ACLRULETBADDR(CAREBITS, index);
	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write Care Bits to ACS_DATA registers */
	 tableAddr = (rtk_uint16*)&aclRuleSmi.care_bits;
	 regAddr = RTL8367C_TABLE_ACCESS_WRDATA_BASE;

	for(i = 0; i < RTL8367C_ACLRULETBLEN; i++)
	{
		regData = *tableAddr;
		retVal = rtl8367c_setAsicReg(regAddr, regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		regAddr++;
		tableAddr++;
	}
	retVal = rtl8367c_setAsicRegBits(RTL8367C_TABLE_ACCESS_WRDATA_REG(RTL8367C_ACLRULETBLEN), (0x0007 << 1), (aclRuleSmi.care_bits_ext.rule_info >> 1) & 0x0007);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write ACS_CMD register */
	regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
	regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_WRITE, TB_TARGET_ACLRULE);
	retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK,regData);
	if(retVal != RT_ERR_OK)
		return retVal;



	/* Write ACS_ADR register for data bits */
	regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
    if(index >= 64)
	    regData = RTL8367C_ACLRULETBADDR2(DATABITS, index);
    else
	    regData = RTL8367C_ACLRULETBADDR(DATABITS, index);

	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write Data Bits to ACS_DATA registers */
	 tableAddr = (rtk_uint16*)&aclRuleSmi.data_bits;
	 regAddr = RTL8367C_TABLE_ACCESS_WRDATA_BASE;

	for(i = 0; i < RTL8367C_ACLRULETBLEN; i++)
	{
		regData = *tableAddr;
		retVal = rtl8367c_setAsicReg(regAddr, regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		regAddr++;
		tableAddr++;
	}

	retVal = rtl8367c_setAsicRegBit(RTL8367C_TABLE_ACCESS_WRDATA_REG(RTL8367C_ACLRULETBLEN), 0, aclRuleSmi.valid);
	if(retVal != RT_ERR_OK)
		return retVal;
	retVal = rtl8367c_setAsicRegBits(RTL8367C_TABLE_ACCESS_WRDATA_REG(RTL8367C_ACLRULETBLEN), (0x0007 << 1), (aclRuleSmi.care_bits_ext.rule_info >> 1) & 0x0007);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write ACS_CMD register for care bits*/
	regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
	regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_WRITE, TB_TARGET_ACLRULE);
	retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

#ifdef CONFIG_RTL8367C_ASICDRV_TEST
	memcpy(&Rtl8370sVirtualAclRuleTable[index], &aclRuleSmi, sizeof(rtl8367c_aclrulesmi));
#endif

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicAclRule
 * Description:
 *      Get acl rule content
 * Input:
 *      index 	- ACL rule index (0-63) of 64 ACL rules
 *      pAclRule - ACL rule stucture for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-63)
  * Note:
 *		None
 */
ret_t rtl8367c_getAsicAclRule(rtk_uint32 index, rtl8367c_aclrule *pAclRule)
{
	rtl8367c_aclrulesmi aclRuleSmi;
	rtk_uint32 regAddr, regData;
	ret_t retVal;
	rtk_uint16* tableAddr;
	rtk_uint32 i;

	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

	memset(&aclRuleSmi, 0x00, sizeof(rtl8367c_aclrulesmi));

	/* Write ACS_ADR register for data bits */
	regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
    if(index >= 64)
        regData = RTL8367C_ACLRULETBADDR2(DATABITS, index);
    else
	    regData = RTL8367C_ACLRULETBADDR(DATABITS, index);

	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;


	/* Write ACS_CMD register */
	regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
	regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_READ, TB_TARGET_ACLRULE);
	retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Read Data Bits */
	regAddr = RTL8367C_TABLE_ACCESS_RDDATA_BASE;
	tableAddr = (rtk_uint16*)&aclRuleSmi.data_bits;
	for(i = 0; i < RTL8367C_ACLRULETBLEN; i++)
	{
		retVal = rtl8367c_getAsicReg(regAddr, &regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		*tableAddr = regData;

		regAddr ++;
		tableAddr ++;
	}

	/* Read Valid Bit */
	retVal = rtl8367c_getAsicRegBit(RTL8367C_TABLE_ACCESS_RDDATA_REG(RTL8367C_ACLRULETBLEN), 0, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;
	aclRuleSmi.valid = regData & 0x1;
	/* Read active_portmsk_ext Bits */
	retVal = rtl8367c_getAsicRegBits(RTL8367C_TABLE_ACCESS_RDDATA_REG(RTL8367C_ACLRULETBLEN), 0x7<<1, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;
	aclRuleSmi.data_bits_ext.rule_info = (regData % 0x0007) << 1;


	/* Write ACS_ADR register for carebits*/
	regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
    if(index >= 64)
	    regData = RTL8367C_ACLRULETBADDR2(CAREBITS, index);
    else
        regData = RTL8367C_ACLRULETBADDR(CAREBITS, index);

	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write ACS_CMD register */
	regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
	regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_READ, TB_TARGET_ACLRULE);
	retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Read Care Bits */
	regAddr = RTL8367C_TABLE_ACCESS_RDDATA_BASE;
	tableAddr = (rtk_uint16*)&aclRuleSmi.care_bits;
	for(i = 0; i < RTL8367C_ACLRULETBLEN; i++)
	{
		retVal = rtl8367c_getAsicReg(regAddr, &regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		*tableAddr = regData;

		regAddr ++;
		tableAddr ++;
	}
	/* Read active_portmsk_ext care Bits */
	retVal = rtl8367c_getAsicRegBits(RTL8367C_TABLE_ACCESS_RDDATA_REG(RTL8367C_ACLRULETBLEN), 0x7<<1, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;
	aclRuleSmi.care_bits_ext.rule_info = (regData & 0x0007) << 1;

#ifdef CONFIG_RTL8367C_ASICDRV_TEST
	memcpy(&aclRuleSmi,&Rtl8370sVirtualAclRuleTable[index], sizeof(rtl8367c_aclrulesmi));
#endif

	 _rtl8367c_aclRuleStSmi2User(pAclRule, &aclRuleSmi);

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicAclNot
 * Description:
 *      Set rule comparison result inversion / no inversion
 * Input:
 *      index 	- ACL rule index (0-95) of 96 ACL rules
 *      not 	- 1: inverse, 0: don't inverse
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
 * Note:
 *		None
 */
ret_t rtl8367c_setAsicAclNot(rtk_uint32 index, rtk_uint32 not)
{
	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

	if(index < 64)
		return rtl8367c_setAsicRegBit(RTL8367C_ACL_ACTION_CTRL_REG(index), RTL8367C_ACL_OP_NOT_OFFSET(index), not);
	else
		return rtl8367c_setAsicRegBit(RTL8367C_ACL_ACTION_CTRL2_REG(index), RTL8367C_ACL_OP_NOT_OFFSET(index), not);

}
/* Function Name:
 *      rtl8367c_getAsicAcl
 * Description:
 *      Get rule comparison result inversion / no inversion
 * Input:
 *      index 	- ACL rule index (0-95) of 95 ACL rules
 *      pNot 	- 1: inverse, 0: don't inverse
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
 * Note:
 *		None
 */
ret_t rtl8367c_getAsicAclNot(rtk_uint32 index, rtk_uint32* pNot)
{
	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

	if(index < 64)
		return rtl8367c_getAsicRegBit(RTL8367C_ACL_ACTION_CTRL_REG(index), RTL8367C_ACL_OP_NOT_OFFSET(index), pNot);
	else
		return rtl8367c_getAsicRegBit(RTL8367C_ACL_ACTION_CTRL2_REG(index), RTL8367C_ACL_OP_NOT_OFFSET(index), pNot);

}
/* Function Name:
 *      rtl8367c_setAsicAclTemplate
 * Description:
 *      Set fields of a ACL Template
 * Input:
 *      index 	- ACL template index(0~4)
 *      pAclType - ACL type stucture for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL template index(0~4)
 * Note:
 *	    The API can set type field of the 5 ACL rule templates.
 *		Each type has 8 fields. One field means what data in one field of a ACL rule means
 *		8 fields of ACL rule 0~95 is descripted by one type in ACL group
 */
ret_t rtl8367c_setAsicAclTemplate(rtk_uint32 index, rtl8367c_acltemplate_t* pAclType)
{
	ret_t retVal;
	rtk_uint32 i;
	rtk_uint32 regAddr, regData;

	if(index >= RTL8367C_ACLTEMPLATENO)
		return RT_ERR_OUT_OF_RANGE;

	regAddr = RTL8367C_ACL_RULE_TEMPLATE_CTRL_REG(index);

	for(i = 0; i < (RTL8367C_ACLRULEFIELDNO/2); i++)
    {
    	regData = pAclType->field[i*2+1];
		regData = regData << 8 | pAclType->field[i*2];

		retVal = rtl8367c_setAsicReg(regAddr + i, regData);

		if(retVal != RT_ERR_OK)
	        return retVal;
	}

	return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicAclTemplate
 * Description:
 *      Get fields of a ACL Template
 * Input:
 *      index 	- ACL template index(0~4)
 *      pAclType - ACL type stucture for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL template index(0~4)
 * Note:
 *	    None
 */
ret_t rtl8367c_getAsicAclTemplate(rtk_uint32 index, rtl8367c_acltemplate_t *pAclType)
{
	ret_t retVal;
	rtk_uint32 i;
	rtk_uint32 regData, regAddr;

	if(index >= RTL8367C_ACLTEMPLATENO)
		return RT_ERR_OUT_OF_RANGE;

	regAddr = RTL8367C_ACL_RULE_TEMPLATE_CTRL_REG(index);

	for(i = 0; i < (RTL8367C_ACLRULEFIELDNO/2); i++)
	{
		retVal = rtl8367c_getAsicReg(regAddr + i,&regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		pAclType->field[i*2] = regData & 0xFF;
		pAclType->field[i*2 + 1] = (regData >> 8) & 0xFF;
	}

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicAclAct
 * Description:
 *      Set ACL rule matched Action
 * Input:
 *      index 	- ACL rule index (0-95) of 96 ACL rules
 *      pAclAct 	- ACL action stucture for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
 * Note:
 *	    None
 */
ret_t rtl8367c_setAsicAclAct(rtk_uint32 index, rtl8367c_acl_act_t* pAclAct)
{
	rtk_uint16 aclActSmi[RTL8367C_ACL_ACT_TABLE_LEN];
	ret_t retVal;
	rtk_uint32 regAddr, regData;
	rtk_uint16* tableAddr;
	rtk_uint32 i;

	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

	memset(aclActSmi, 0x00, sizeof(rtk_uint16) * RTL8367C_ACL_ACT_TABLE_LEN);
	 _rtl8367c_aclActStUser2Smi(pAclAct, aclActSmi);

	/* Write ACS_ADR register for data bits */
	regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
	regData = index;
	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write Data Bits to ACS_DATA registers */
	 tableAddr = aclActSmi;
	 regAddr = RTL8367C_TABLE_ACCESS_WRDATA_BASE;

	for(i = 0; i < RTL8367C_ACLACTTBLEN; i++)
	{
		regData = *tableAddr;
		retVal = rtl8367c_setAsicReg(regAddr, regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		regAddr++;
		tableAddr++;
	}

	/* Write ACS_CMD register for care bits*/
	regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
	regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_WRITE, TB_TARGET_ACLACT);
	retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

#ifdef CONFIG_RTL8367C_ASICDRV_TEST
    memcpy(&Rtl8370sVirtualAclActTable[index][0], aclActSmi, sizeof(rtk_uint16) * RTL8367C_ACL_ACT_TABLE_LEN);
#endif

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicAclAct
 * Description:
 *      Get ACL rule matched Action
 * Input:
 *      index 	- ACL rule index (0-95) of 96 ACL rules
 *      pAclAct 	- ACL action stucture for setting
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
  * Note:
 *	    None
 */
ret_t rtl8367c_getAsicAclAct(rtk_uint32 index, rtl8367c_acl_act_t *pAclAct)
{
	rtk_uint16 aclActSmi[RTL8367C_ACL_ACT_TABLE_LEN];
	ret_t retVal;
	rtk_uint32 regAddr, regData;
	rtk_uint16 *tableAddr;
	rtk_uint32 i;

	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

	memset(aclActSmi, 0x00, sizeof(rtk_uint16) * RTL8367C_ACL_ACT_TABLE_LEN);

	/* Write ACS_ADR register for data bits */
	regAddr = RTL8367C_TABLE_ACCESS_ADDR_REG;
	regData = index;
	retVal = rtl8367c_setAsicReg(regAddr, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Write ACS_CMD register */
	regAddr = RTL8367C_TABLE_ACCESS_CTRL_REG;
	regData = RTL8367C_TABLE_ACCESS_REG_DATA(TB_OP_READ, TB_TARGET_ACLACT);
	retVal = rtl8367c_setAsicRegBits(regAddr, RTL8367C_TABLE_TYPE_MASK | RTL8367C_COMMAND_TYPE_MASK, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	/* Read Data Bits */
	regAddr = RTL8367C_TABLE_ACCESS_RDDATA_BASE;
	tableAddr = aclActSmi;
	for(i = 0; i < RTL8367C_ACLACTTBLEN; i++)
	{
		retVal = rtl8367c_getAsicReg(regAddr, &regData);
		if(retVal != RT_ERR_OK)
			return retVal;

		*tableAddr = regData;

		regAddr ++;
		tableAddr ++;
	}

#ifdef CONFIG_RTL8367C_ASICDRV_TEST
    memcpy(aclActSmi, &Rtl8370sVirtualAclActTable[index][0], sizeof(rtk_uint16) * RTL8367C_ACL_ACT_TABLE_LEN);
#endif

	 _rtl8367c_aclActStSmi2User(pAclAct, aclActSmi);

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicAclActCtrl
 * Description:
 *      Set ACL rule matched Action Control Bits
 * Input:
 *      index 		- ACL rule index (0-95) of 96 ACL rules
 *      aclActCtrl 	- 6 ACL Control Bits
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
 * Note:
 *	    ACL Action Control Bits Indicate which actions will be take when a rule matches
 */
ret_t rtl8367c_setAsicAclActCtrl(rtk_uint32 index, rtk_uint32 aclActCtrl)
{
	ret_t retVal;

	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(index >= 64)
        retVal = rtl8367c_setAsicRegBits(RTL8367C_ACL_ACTION_CTRL2_REG(index), RTL8367C_ACL_OP_ACTION_MASK(index), aclActCtrl);
    else
        retVal = rtl8367c_setAsicRegBits(RTL8367C_ACL_ACTION_CTRL_REG(index), RTL8367C_ACL_OP_ACTION_MASK(index), aclActCtrl);

    return retVal;
}
/* Function Name:
 *      rtl8367c_getAsicAclActCtrl
 * Description:
 *      Get ACL rule matched Action Control Bits
 * Input:
 *      index 		- ACL rule index (0-95) of 96 ACL rules
 *      pAclActCtrl 	- 6 ACL Control Bits
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL rule index (0-95)
 * Note:
 *	    None
 */
ret_t rtl8367c_getAsicAclActCtrl(rtk_uint32 index, rtk_uint32 *pAclActCtrl)
{
	ret_t retVal;
	rtk_uint32 regData;

	if(index > RTL8367C_ACLRULEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(index >= 64)
        retVal = rtl8367c_getAsicRegBits(RTL8367C_ACL_ACTION_CTRL2_REG(index), RTL8367C_ACL_OP_ACTION_MASK(index), &regData);
    else
        retVal = rtl8367c_getAsicRegBits(RTL8367C_ACL_ACTION_CTRL_REG(index), RTL8367C_ACL_OP_ACTION_MASK(index), &regData);

	if(retVal != RT_ERR_OK)
		return retVal;

	*pAclActCtrl = regData;

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicAclPortRange
 * Description:
 *      Set ACL TCP/UDP range check
 * Input:
 *      index 		- TCP/UDP port range check table index
 *      type 		- Range check type
 *      upperPort 	- TCP/UDP port range upper bound
 *      lowerPort 	- TCP/UDP port range lower bound
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid TCP/UDP port range check table index
 * Note:
 *	    None
 */
ret_t rtl8367c_setAsicAclPortRange(rtk_uint32 index, rtk_uint32 type, rtk_uint32 upperPort, rtk_uint32 lowerPort)
{
	ret_t retVal;

	if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

	retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_ACL_SDPORT_RANGE_ENTRY0_CTRL2 + index*3, RTL8367C_ACL_SDPORT_RANGE_ENTRY0_CTRL2_MASK, type);
	if(retVal != RT_ERR_OK)
		return retVal;

	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_SDPORT_RANGE_ENTRY0_CTRL1 + index*3, upperPort);
	if(retVal != RT_ERR_OK)
		return retVal;

	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_SDPORT_RANGE_ENTRY0_CTRL0 + index*3, lowerPort);
	if(retVal != RT_ERR_OK)
		return retVal;

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicAclPortRange
 * Description:
 *      Get ACL TCP/UDP range check
 * Input:
 *      index 		- TCP/UDP port range check table index
 *      pType 		- Range check type
 *      pUpperPort 	- TCP/UDP port range upper bound
 *      pLowerPort 	- TCP/UDP port range lower bound
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid TCP/UDP port range check table index
 * Note:
 *	    None
 */
ret_t rtl8367c_getAsicAclPortRange(rtk_uint32 index, rtk_uint32* pType, rtk_uint32* pUpperPort, rtk_uint32* pLowerPort)
{
	ret_t retVal;

	if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

	retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_ACL_SDPORT_RANGE_ENTRY0_CTRL2 + index*3, RTL8367C_ACL_SDPORT_RANGE_ENTRY0_CTRL2_MASK, pType);
	if(retVal != RT_ERR_OK)
		return retVal;

	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_SDPORT_RANGE_ENTRY0_CTRL1 + index*3, pUpperPort);
	if(retVal != RT_ERR_OK)
		return retVal;

	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_SDPORT_RANGE_ENTRY0_CTRL0 + index*3, pLowerPort);
	if(retVal != RT_ERR_OK)
		return retVal;

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicAclVidRange
 * Description:
 *      Set ACL VID range check
 * Input:
 *      index 		- ACL VID range check index(0~15)
 *      type 		- Range check type
 *      upperVid 	- VID range upper bound
 *      lowerVid 	- VID range lower bound
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL  VID range check index(0~15)
 * Note:
 *	    None
 */
ret_t rtl8367c_setAsicAclVidRange(rtk_uint32 index, rtk_uint32 type, rtk_uint32 upperVid, rtk_uint32 lowerVid)
{
	ret_t retVal;
	rtk_uint32 regData;

	if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

	regData = ((type << RTL8367C_ACL_VID_RANGE_ENTRY0_CTRL1_CHECK0_TYPE_OFFSET) & RTL8367C_ACL_VID_RANGE_ENTRY0_CTRL1_CHECK0_TYPE_MASK) |
				(upperVid & RTL8367C_ACL_VID_RANGE_ENTRY0_CTRL1_CHECK0_HIGH_MASK);

	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_VID_RANGE_ENTRY0_CTRL1 + index*2, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_VID_RANGE_ENTRY0_CTRL0 + index*2, lowerVid);
	if(retVal != RT_ERR_OK)
		return retVal;

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicAclVidRange
 * Description:
 *      Get ACL VID range check
 * Input:
 *      index 		- ACL VID range check index(0~15)
 *      pType 		- Range check type
 *      pUpperVid 	- VID range upper bound
 *      pLowerVid 	- VID range lower bound
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL VID range check index(0~15)
 * Note:
 *	    None
 */
ret_t rtl8367c_getAsicAclVidRange(rtk_uint32 index, rtk_uint32* pType, rtk_uint32* pUpperVid, rtk_uint32* pLowerVid)
{
	ret_t retVal;
	rtk_uint32 regData;

	if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_VID_RANGE_ENTRY0_CTRL1 + index*2, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	*pType = (regData & RTL8367C_ACL_VID_RANGE_ENTRY0_CTRL1_CHECK0_TYPE_MASK) >> RTL8367C_ACL_VID_RANGE_ENTRY0_CTRL1_CHECK0_TYPE_OFFSET;
	*pUpperVid = regData & RTL8367C_ACL_VID_RANGE_ENTRY0_CTRL1_CHECK0_HIGH_MASK;

	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_VID_RANGE_ENTRY0_CTRL0 + index*2, pLowerVid);
	if(retVal != RT_ERR_OK)
		return retVal;

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicAclIpRange
 * Description:
 *      Set ACL IP range check
 * Input:
 *      index 		- ACL IP range check index(0~15)
 *      type 		- Range check type
 *      upperIp 	- IP range upper bound
 *      lowerIp 	- IP range lower bound
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL IP range check index(0~15)
 * Note:
 *	    None
 */
ret_t rtl8367c_setAsicAclIpRange(rtk_uint32 index, rtk_uint32 type, ipaddr_t upperIp, ipaddr_t lowerIp)
{
	ret_t retVal;
	rtk_uint32 regData;
	ipaddr_t ipData;

	if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

	retVal = rtl8367c_setAsicRegBits(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL4 + index*5, RTL8367C_ACL_IP_RANGE_ENTRY0_CTRL4_MASK, type);
	if(retVal != RT_ERR_OK)
		return retVal;

	ipData = upperIp;

	regData = ipData & 0xFFFF;
	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL2 + index*5, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	regData = (ipData>>16) & 0xFFFF;
	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL3 + index*5, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	ipData = lowerIp;

	regData = ipData & 0xFFFF;
	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL0 + index*5, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	regData = (ipData>>16) & 0xFFFF;
	retVal = rtl8367c_setAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL1 + index*5, regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicAclIpRange
 * Description:
 *      Get ACL IP range check
 * Input:
 *      index 		- ACL IP range check index(0~15)
 *      pType 		- Range check type
 *      pUpperIp 	- IP range upper bound
 *      pLowerIp 	- IP range lower bound
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 				- Success
 *      RT_ERR_SMI  			- SMI access error
 *      RT_ERR_OUT_OF_RANGE  	- Invalid ACL IP range check index(0~15)
 * Note:
 *	    None
 */
ret_t rtl8367c_getAsicAclIpRange(rtk_uint32 index, rtk_uint32* pType, ipaddr_t* pUpperIp, ipaddr_t* pLowerIp)
{
	ret_t retVal;
	rtk_uint32 regData;
	ipaddr_t ipData;

	if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

	retVal = rtl8367c_getAsicRegBits(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL4 + index*5, RTL8367C_ACL_IP_RANGE_ENTRY0_CTRL4_MASK, pType);
	if(retVal != RT_ERR_OK)
		return retVal;

	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL2 + index*5, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;
	ipData = regData;


	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL3 + index*5, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	ipData = (regData <<16) | ipData;
	*pUpperIp = ipData;


	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL0 + index*5, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;
	ipData = regData;


	retVal = rtl8367c_getAsicReg(RTL8367C_REG_ACL_IP_RANGE_ENTRY0_CTRL1 + index*5, &regData);
	if(retVal != RT_ERR_OK)
		return retVal;

	ipData = (regData << 16) | ipData;
	*pLowerIp = ipData;

	return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicAclGpioPolarity
 * Description:
 *      Set ACL Goip control palarity
 * Input:
 *      polarity - 1: High, 0: Low
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      none
 */
ret_t rtl8367c_setAsicAclGpioPolarity(rtk_uint32 polarity)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_ACL_GPIO_POLARITY, RTL8367C_ACL_GPIO_POLARITY_OFFSET, polarity);
}
/* Function Name:
 *      rtl8367c_getAsicAclGpioPolarity
 * Description:
 *      Get ACL Goip control palarity
 * Input:
 *      pPolarity - 1: High, 0: Low
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      none
 */
ret_t rtl8367c_getAsicAclGpioPolarity(rtk_uint32* pPolarity)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_ACL_GPIO_POLARITY, RTL8367C_ACL_GPIO_POLARITY_OFFSET, pPolarity);
}


CONST_T rtk_uint8 filter_templateField[RTL8367C_ACLTEMPLATENO][RTL8367C_ACLRULEFIELDNO] = {
    {ACL_DMAC0,   			ACL_DMAC1, 		 	ACL_DMAC2, 	 		ACL_SMAC0,   		ACL_SMAC1, 			ACL_SMAC2, 			ACL_ETHERTYPE, 		ACL_FIELD_SELECT15},
    {ACL_IP4SIP0, 			ACL_IP4SIP1, 		ACL_IP4DIP0, 		ACL_IP4DIP1, 		ACL_FIELD_SELECT13, ACL_FIELD_SELECT14, ACL_FIELD_SELECT02, ACL_FIELD_SELECT15},
    {ACL_IP6SIP0WITHIPV4,	ACL_IP6SIP1WITHIPV4,ACL_FIELD_SELECT03, ACL_FIELD_SELECT04, ACL_FIELD_SELECT05,	ACL_FIELD_SELECT06, ACL_FIELD_SELECT07,	ACL_FIELD_SELECT08},
    {ACL_IP6DIP0WITHIPV4,	ACL_IP6DIP1WITHIPV4,ACL_FIELD_SELECT09, ACL_FIELD_SELECT10, ACL_FIELD_SELECT11,	ACL_FIELD_SELECT12, ACL_FIELD_SELECT13,	ACL_FIELD_SELECT14},
    {ACL_VIDRANGE,			ACL_IPRANGE, 		ACL_PORTRANGE,  	ACL_CTAG,  			ACL_STAG, 			ACL_FIELD_SELECT13, ACL_FIELD_SELECT14,	ACL_FIELD_SELECT15}
};

CONST_T rtk_uint8 filter_advanceCaretagField[RTL8367C_ACLTEMPLATENO][2] = {
    {TRUE,		7},
    {TRUE,		7},
    {FALSE,		0},
    {FALSE,		0},
    {TRUE,		7},
};


CONST_T rtk_uint8 filter_fieldTemplateIndex[FILTER_FIELD_END][RTK_FILTER_FIELD_USED_MAX] = {
	{0x00, 0x01,0x02},
	{0x03, 0x04,0x05},
	{0x06},
	{0x43},
	{0x44},
	{0x10, 0x11},
	{0x12, 0x13},
	{0x24},
	{0x25},
	{0x35},
	{0x35},
	{0x20, 0x21,0x22,0x23},
	{0x30, 0x31,0x32,0x33},
	{0x26},
	{0x27},
	{0x14},
	{0x15},
	{0x16},
	{0x14},
	{0x15},
	{0x14},
	{0x14},
	{0x14},

	{0x40},
	{0x41},
	{0x42},

	{0x14},
	{0x15},
	{0x16},
	{0x22},
	{0x23},
	{0x24},
	{0x25},
	{0x26},
	{0x27},
	{0x32},
	{0x33},
	{0x34},
	{0x35},
	{0x36},
	{0x37},
	{0x47},

    {0xFF} /* Pattern Match */
};

CONST_T rtk_uint8 filter_fieldSize[FILTER_FIELD_END] = {
    3, 3, 1, 1, 1,
    2, 2, 1, 1, 1, 1, 4, 4, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    8
};

CONST_T rtk_uint16 field_selector[RTL8367C_FIELDSEL_FORMAT_NUMBER][2] =
{
    {FIELDSEL_FORMAT_DEFAULT, 0},    /* Field Selector 0 */
    {FIELDSEL_FORMAT_DEFAULT, 0},    /* Field Selector 1 */
    {FIELDSEL_FORMAT_IPPAYLOAD, 12}, /* Field Selector 2 */
    {FIELDSEL_FORMAT_IPV6, 10},      /* Field Selector 3 */
    {FIELDSEL_FORMAT_IPV6, 8},       /* Field Selector 4 */
    {FIELDSEL_FORMAT_IPV4, 0},       /* Field Selector 5 */
    {FIELDSEL_FORMAT_IPV4, 8},       /* Field Selector 6 */
    {FIELDSEL_FORMAT_IPV6, 0},       /* Field Selector 7 */
    {FIELDSEL_FORMAT_IPV6, 6},       /* Field Selector 8 */
    {FIELDSEL_FORMAT_IPV6, 26},      /* Field Selector 9 */
    {FIELDSEL_FORMAT_IPV6, 24},      /* Field Selector 10 */
    {FIELDSEL_FORMAT_DEFAULT, 0},    /* Field Selector 11 */
    {FIELDSEL_FORMAT_IPV4, 6},       /* Field Selector 12 */
    {FIELDSEL_FORMAT_IPPAYLOAD, 0},  /* Field Selector 13 */
    {FIELDSEL_FORMAT_IPPAYLOAD, 2},  /* Field Selector 14 */
    {FIELDSEL_FORMAT_DEFAULT, 0}     /* Field Selector 15 */
};


static rtk_api_ret_t _rtk_filter_igrAcl_writeDataField(rtl8367c_aclrule *aclRule, rtk_filter_field_t *fieldPtr);


/* Function Name:
 *      rtk_filter_igrAcl_init
 * Description:
 *      ACL initialization function
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - Pointer pFilter_field or pFilter_cfg point to NULL.
 * Note:
 *      This function enable and intialize ACL function
 */
rtk_api_ret_t rtk_filter_igrAcl_init(void)
{
    rtl8367c_acltemplate_t       aclTemp;
    rtk_uint32                 i, j;
    rtk_api_ret_t          ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if ((ret = rtk_filter_igrAcl_cfg_delAll()) != RT_ERR_OK)
        return ret;

    for(i = 0; i < RTL8367C_ACLTEMPLATENO; i++)
    {
        for(j = 0; j < RTL8367C_ACLRULEFIELDNO;j++)
            aclTemp.field[j] = filter_templateField[i][j];

        if ((ret = rtl8367c_setAsicAclTemplate(i, &aclTemp)) != RT_ERR_OK)
            return ret;
    }

    for(i = 0; i < RTL8367C_FIELDSEL_FORMAT_NUMBER; i++)
    {
        if ((ret = rtl8367c_setAsicFieldSelector(i, field_selector[i][0], field_selector[i][1])) != RT_ERR_OK)
            return ret;
    }

    RTK_SCAN_ALL_PHY_PORTMASK(i)
    {
        if ((ret = rtl8367c_setAsicAcl(i, TRUE)) != RT_ERR_OK)
            return ret;

        if ((ret = rtl8367c_setAsicAclUnmatchedPermit(i, TRUE)) != RT_ERR_OK)
            return ret;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_field_add
 * Description:
 *      Add comparison rule to an ACL configuration
 * Input:
 *      pFilter_cfg     - The ACL configuration that this function will add comparison rule
 *      pFilter_field   - The comparison rule that will be added.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_NULL_POINTER    	- Pointer pFilter_field or pFilter_cfg point to NULL.
 *      RT_ERR_INPUT 			- Invalid input parameters.
 * Note:
 *      This function add a comparison rule (*pFilter_field) to an ACL configuration (*pFilter_cfg).
 *      Pointer pFilter_cfg points to an ACL configuration structure, this structure keeps multiple ACL
 *      comparison rules by means of linked list. Pointer pFilter_field will be added to linked
 *      list keeped by structure that pFilter_cfg points to.
 */
rtk_api_ret_t rtk_filter_igrAcl_field_add(rtk_filter_cfg_t* pFilter_cfg, rtk_filter_field_t* pFilter_field)
{
	rtk_uint32 i;
	rtk_filter_field_t *tailPtr;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pFilter_cfg || NULL == pFilter_field)
        return RT_ERR_NULL_POINTER;

    if(pFilter_field->fieldType >= FILTER_FIELD_END)
        return RT_ERR_ENTRY_INDEX;


	if(0 == pFilter_field->fieldTemplateNo)
	{
		pFilter_field->fieldTemplateNo = filter_fieldSize[pFilter_field->fieldType];

		for(i = 0; i < pFilter_field->fieldTemplateNo; i++)
		{
			pFilter_field->fieldTemplateIdx[i] = filter_fieldTemplateIndex[pFilter_field->fieldType][i];
		}
	}

    if(NULL == pFilter_cfg->fieldHead)
    {
        pFilter_cfg->fieldHead = pFilter_field;
    }
    else
    {
        if (pFilter_cfg->fieldHead->next == NULL)
        {
            pFilter_cfg->fieldHead->next = pFilter_field;
        }
        else
        {
            tailPtr = pFilter_cfg->fieldHead->next;
            while( tailPtr->next != NULL)
            {
                tailPtr = tailPtr->next;
            }
            tailPtr->next = pFilter_field;
        }
    }

    return RT_ERR_OK;
}

static rtk_api_ret_t _rtk_filter_igrAcl_writeDataField(rtl8367c_aclrule *aclRule, rtk_filter_field_t *fieldPtr)
{
    rtk_uint32 i, tempIdx,fieldIdx, ipValue, ipMask;
    rtk_uint32 ip6addr[RTK_IPV6_ADDR_WORD_LENGTH];
    rtk_uint32 ip6mask[RTK_IPV6_ADDR_WORD_LENGTH];

	for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
	{
		tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;

		aclRule[tempIdx].valid = TRUE;
	}

    switch (fieldPtr->fieldType)
    {
    /* use DMAC structure as representative for mac structure */
    case FILTER_FIELD_DMAC:
    case FILTER_FIELD_SMAC:

		for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
		{
			tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

			aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.mac.value.octet[5 - i*2] | (fieldPtr->filter_pattern_union.mac.value.octet[5 - (i*2 + 1)] << 8);
			aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.mac.mask.octet[5 - i*2] | (fieldPtr->filter_pattern_union.mac.mask.octet[5 - (i*2 + 1)] << 8);
		}
   		break;
    case FILTER_FIELD_ETHERTYPE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.etherType.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.etherType.mask;
        }
        break;
    case FILTER_FIELD_IPV4_SIP:
    case FILTER_FIELD_IPV4_DIP:

		ipValue = fieldPtr->filter_pattern_union.sip.value;
		ipMask = fieldPtr->filter_pattern_union.sip.mask;

		for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
		{
			tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

			aclRule[tempIdx].data_bits.field[fieldIdx] = (ipValue & (0xFFFF << (i << 4))) >> (i << 4);
			aclRule[tempIdx].care_bits.field[fieldIdx] = (ipMask & (0xFFFF << (i << 4))) >> (i << 4);
		}
		break;
    case FILTER_FIELD_IPV4_TOS:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.ipTos.value & 0xFF;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.ipTos.mask  & 0xFF;
        }
        break;
    case FILTER_FIELD_IPV4_PROTOCOL:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.protocol.value & 0xFF;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.protocol.mask  & 0xFF;
        }
        break;
    case FILTER_FIELD_IPV6_SIPV6:
    case FILTER_FIELD_IPV6_DIPV6:
        for(i = 0; i < RTK_IPV6_ADDR_WORD_LENGTH; i++)
        {
            ip6addr[i] = fieldPtr->filter_pattern_union.sipv6.value.addr[i];
            ip6mask[i] = fieldPtr->filter_pattern_union.sipv6.mask.addr[i];
        }

		for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
		{
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
			fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            if(i < 2)
            {
                aclRule[tempIdx].data_bits.field[fieldIdx] = ((ip6addr[0] & (0xFFFF << (i * 16))) >> (i * 16));
                aclRule[tempIdx].care_bits.field[fieldIdx] = ((ip6mask[0] & (0xFFFF << (i * 16))) >> (i * 16));
            }
            else
            {
                /*default acl template for ipv6 address supports MSB 32-bits and LSB 32-bits only*/
                aclRule[tempIdx].data_bits.field[fieldIdx] = ((ip6addr[3] & (0xFFFF << ((i&1) * 16))) >> ((i&1) * 16));
                aclRule[tempIdx].care_bits.field[fieldIdx] = ((ip6mask[3] & (0xFFFF << ((i&1) * 16))) >> ((i&1) * 16));
            }
		}

		break;
	case FILTER_FIELD_CTAG:
    case FILTER_FIELD_STAG:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.l2tag.pri.value << 13) | (fieldPtr->filter_pattern_union.l2tag.cfi.value << 12) | fieldPtr->filter_pattern_union.l2tag.vid.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.l2tag.pri.mask << 13) | (fieldPtr->filter_pattern_union.l2tag.cfi.mask << 12) | fieldPtr->filter_pattern_union.l2tag.vid.mask;
        }
        break;
	case FILTER_FIELD_IPV4_FLAG:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0x1FFF;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.xf.value << 15);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.df.value << 14);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.mf.value << 13);

            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0x1FFF;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.xf.mask << 15);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.df.mask << 14);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.ipFlag.mf.mask << 13);
        }

        break;
	case FILTER_FIELD_IPV4_OFFSET:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0xE000;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.inData.value;

            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0xE000;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.inData.mask;
        }

        break;

	case FILTER_FIELD_IPV6_TRAFFIC_CLASS:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;


            aclRule[tempIdx].data_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.inData.value << 4)&0x0FF0;
            aclRule[tempIdx].care_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.inData.mask << 4)&0x0FF0;
        }
        break;
	case FILTER_FIELD_IPV6_NEXT_HEADER:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.value << 8;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.mask << 8;
        }
        break;
    case FILTER_FIELD_TCP_SPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpSrcPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpSrcPort.mask;
        }
        break;
    case FILTER_FIELD_TCP_DPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpDstPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.tcpDstPort.mask;
        }
        break;
	case FILTER_FIELD_TCP_FLAG:

        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.cwr.value << 7);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ece.value << 6);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.urg.value << 5);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ack.value << 4);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.psh.value << 3);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.rst.value << 2);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.syn.value << 1);
            aclRule[tempIdx].data_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.tcpFlag.fin.value;

            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.cwr.mask << 7);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ece.mask << 6);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.urg.mask << 5);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.ack.mask << 4);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.psh.mask << 3);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.rst.mask << 2);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.tcpFlag.syn.mask << 1);
            aclRule[tempIdx].care_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.tcpFlag.fin.mask;
        }
        break;
    case FILTER_FIELD_UDP_SPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpSrcPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpSrcPort.mask;
        }
        break;
    case FILTER_FIELD_UDP_DPORT:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpDstPort.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.udpDstPort.mask;
        }
        break;
	case FILTER_FIELD_ICMP_CODE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0xFF00;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.icmpCode.value;
            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0xFF00;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= fieldPtr->filter_pattern_union.icmpCode.mask;
        }
        break;
	case FILTER_FIELD_ICMP_TYPE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] &= 0x00FF;
            aclRule[tempIdx].data_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.icmpType.value << 8);
            aclRule[tempIdx].care_bits.field[fieldIdx] &= 0x00FF;
            aclRule[tempIdx].care_bits.field[fieldIdx] |= (fieldPtr->filter_pattern_union.icmpType.mask << 8);
        }
        break;
	case FILTER_FIELD_IGMP_TYPE:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.igmpType.value << 8);
            aclRule[tempIdx].care_bits.field[fieldIdx] = (fieldPtr->filter_pattern_union.igmpType.mask << 8);
        }
        break;
    case FILTER_FIELD_PATTERN_MATCH:
        for(i = 0; i < fieldPtr->fieldTemplateNo; i++)
        {
            tempIdx = (fieldPtr->fieldTemplateIdx[i] & 0xF0) >> 4;
            fieldIdx = fieldPtr->fieldTemplateIdx[i] & 0x0F;

            aclRule[tempIdx].data_bits.field[fieldIdx] = ((fieldPtr->filter_pattern_union.pattern.value[i/2] >> (16 * (i%2))) & 0x0000FFFF );
            aclRule[tempIdx].care_bits.field[fieldIdx] = ((fieldPtr->filter_pattern_union.pattern.mask[i/2] >> (16 * (i%2))) & 0x0000FFFF );
        }
        break;
    case FILTER_FIELD_VID_RANGE:
    case FILTER_FIELD_IP_RANGE:
    case FILTER_FIELD_PORT_RANGE:
    default:
		tempIdx = (fieldPtr->fieldTemplateIdx[0] & 0xF0) >> 4;
		fieldIdx = fieldPtr->fieldTemplateIdx[0] & 0x0F;

        aclRule[tempIdx].data_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.value;
        aclRule[tempIdx].care_bits.field[fieldIdx] = fieldPtr->filter_pattern_union.inData.mask;
        break;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_add
 * Description:
 *      Add an ACL configuration to ASIC
 * Input:
 *      filter_id       - Start index of ACL configuration.
 *      pFilter_cfg     - The ACL configuration that this function will add comparison rule
 *      pFilter_action  - Action(s) of ACL configuration.
 * Output:
 *      ruleNum - number of rules written in acl table
 * Return:
 *      RT_ERR_OK              					- OK
 *      RT_ERR_FAILED          					- Failed
 *      RT_ERR_SMI             					- SMI access error
 *      RT_ERR_NULL_POINTER    					- Pointer pFilter_field or pFilter_cfg point to NULL.
 *      RT_ERR_INPUT 							- Invalid input parameters.
 *      RT_ERR_ENTRY_INDEX 						- Invalid filter_id .
 *      RT_ERR_NULL_POINTER 					- Pointer pFilter_action or pFilter_cfg point to NULL.
 *      RT_ERR_FILTER_INACL_ACT_NOT_SUPPORT 	- Action is not supported in this chip.
 *      RT_ERR_FILTER_INACL_RULE_NOT_SUPPORT 	- Rule is not supported.
 * Note:
 *      This function store pFilter_cfg, pFilter_action into ASIC. The starting
 *      index(es) is filter_id.
 */
rtk_api_ret_t rtk_filter_igrAcl_cfg_add(rtk_filter_id_t filter_id, rtk_filter_cfg_t* pFilter_cfg, rtk_filter_action_t* pFilter_action, rtk_filter_number_t *ruleNum)
{
    rtk_api_ret_t               retVal;
    rtk_uint32                  careTagData, careTagMask;
    rtk_uint32                  i,vidx, svidx, actType, ruleId;
    rtk_uint32                  aclActCtrl;
    rtk_uint32                  cpuPort;
    rtk_filter_field_t*         fieldPtr;
    rtl8367c_aclrule            aclRule[RTL8367C_ACLTEMPLATENO];
    rtl8367c_aclrule            tempRule;
    rtl8367c_acl_act_t          aclAct;
    rtk_uint32                  noRulesAdd;
    rtk_uint32                  portmask;
    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(filter_id > RTL8367C_ACLRULEMAX )
        return RT_ERR_ENTRY_INDEX;

    if((NULL == pFilter_cfg) || (NULL == pFilter_action) || (NULL == ruleNum))
        return RT_ERR_NULL_POINTER;

    fieldPtr = pFilter_cfg->fieldHead;

    /* init RULE */
    for(i = 0; i < RTL8367C_ACLTEMPLATENO; i++)
    {
        memset(&aclRule[i], 0, sizeof(rtl8367c_aclrule));

        aclRule[i].data_bits.type= i;
        aclRule[i].care_bits.type= 0x7;
    }

    while(NULL != fieldPtr)
    {
        _rtk_filter_igrAcl_writeDataField(aclRule, fieldPtr);

        fieldPtr = fieldPtr->next;
    }

	/*set care tag mask in User Defined Field 15*/
	/*Follow care tag should not be used while ACL template and User defined fields are fully control by system designer*/
    /*those advanced packet type care tag is used in default template design structure only*/
	careTagData = 0;
	careTagMask = 0;

	for(i = CARE_TAG_TCP; i < CARE_TAG_END; i++)
    {
		if(pFilter_cfg->careTag.tagType[i].mask)
			careTagMask = careTagMask | (1 << (i-CARE_TAG_TCP));

		if(pFilter_cfg->careTag.tagType[i].value)
			careTagData = careTagData | (1 << (i-CARE_TAG_TCP));
    }

	if(careTagData || careTagMask)
	{
		i = 0;
		while(i < RTL8367C_ACLTEMPLATENO)
		{
			if(aclRule[i].valid == 1 && filter_advanceCaretagField[i][0] == TRUE)
			{

				aclRule[i].data_bits.field[filter_advanceCaretagField[i][1]] = careTagData & 0xFFFF;
				aclRule[i].care_bits.field[filter_advanceCaretagField[i][1]] = careTagMask & 0xFFFF;
				break;
			}
			i++;
		}
		/*none of previous used template containing field 15*/
		if(i == RTL8367C_ACLTEMPLATENO)
		{
			i = 0;
			while(i <= RTL8367C_ACLTEMPLATENO)
			{
				if(filter_advanceCaretagField[i][0] == TRUE)
				{
					aclRule[i].data_bits.field[filter_advanceCaretagField[i][1]] = careTagData & 0xFFFF;
					aclRule[i].care_bits.field[filter_advanceCaretagField[i][1]] = careTagMask & 0xFFFF;
					aclRule[i].valid = 1;
					break;
				}
				i++;
			}
		}
	}

	/*Check rule number*/
	noRulesAdd = 0;
    for(i = 0; i < RTL8367C_ACLTEMPLATENO; i++)
    {
		if(1 == aclRule[i].valid)
		{
			noRulesAdd ++;
		}
    }

	*ruleNum = noRulesAdd;

	if((filter_id + noRulesAdd - 1) > RTL8367C_ACLRULEMAX)
	{
		return RT_ERR_ENTRY_INDEX;
	}

	/*set care tag mask in TAG Indicator*/
    careTagData = 0;
	careTagMask = 0;

    for(i = 0; i <= CARE_TAG_IPV6;i++)
    {
        if(0 == pFilter_cfg->careTag.tagType[i].mask )
        {
            careTagMask &=  ~(1 << i);
        }
        else
        {
            careTagMask |= (1 << i);
            if(0 == pFilter_cfg->careTag.tagType[i].value )
                careTagData &= ~(1 << i);
            else
                careTagData |= (1 << i);
        }
    }

    for(i = 0; i < RTL8367C_ACLTEMPLATENO; i++)
    {
        aclRule[i].data_bits.tag_exist = (careTagData) & ACL_RULE_CARETAG_MASK;
        aclRule[i].care_bits.tag_exist = (careTagMask) & ACL_RULE_CARETAG_MASK;
    }

    RTK_CHK_PORTMASK_VALID(&pFilter_cfg->activeport.value);
    RTK_CHK_PORTMASK_VALID(&pFilter_cfg->activeport.mask);

    for(i = 0; i < RTL8367C_ACLTEMPLATENO; i++)
    {
		if(TRUE == aclRule[i].valid)
		{
		    rtk_switch_portmask_L2P_get(&pFilter_cfg->activeport.value, &portmask);
			aclRule[i].data_bits.active_portmsk = portmask;

            rtk_switch_portmask_L2P_get(&pFilter_cfg->activeport.mask, &portmask);
			aclRule[i].care_bits.active_portmsk = portmask;
		}
    }

    if(pFilter_cfg->invert >= FILTER_INVERT_END )
        return RT_ERR_INPUT;


	/*Last action gets high priority if actions are the same*/
    memset(&aclAct, 0, sizeof(rtl8367c_acl_act_t));
    aclActCtrl = 0;
    for(actType = 0; actType < FILTER_ENACT_END; actType ++)
    {
        if(pFilter_action->actEnable[actType])
        {
            switch (actType)
            {
            case FILTER_ENACT_CVLAN_INGRESS:
                if(pFilter_action->filterCvlanVid > RTL8367C_EVIDMAX)
                    return RT_ERR_INPUT;

                if((retVal = rtk_vlan_checkAndCreateMbr(pFilter_action->filterCvlanVid, &vidx)) != RT_ERR_OK)
                {
                    return retVal;
                }
                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclAct.cvidx_cact = vidx;

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_TAGONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_VLANONLY;
                }

                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
            case FILTER_ENACT_CVLAN_EGRESS:
                if(pFilter_action->filterCvlanVid > RTL8367C_EVIDMAX)
                    return RT_ERR_INPUT;

                if((retVal = rtk_vlan_checkAndCreateMbr(pFilter_action->filterCvlanVid, &vidx)) != RT_ERR_OK)
                    return retVal;

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclAct.cvidx_cact = vidx;

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_TAGONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_VLANONLY;
                }

                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_CVLAN_SVID:

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_TAGONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_VLANONLY;
                }

                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_POLICING_1:
                if(pFilter_action->filterPolicingIdx[1] >= (RTK_METER_NUM + RTL8367C_MAX_LOG_CNT_NUM))
                    return RT_ERR_INPUT;

                aclAct.cact = FILTER_ENACT_CVLAN_TYPE(actType);
                aclAct.cvidx_cact = pFilter_action->filterPolicingIdx[1];

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_TAGONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_VLANONLY;
                }

                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;

            case FILTER_ENACT_SVLAN_INGRESS:
            case FILTER_ENACT_SVLAN_EGRESS:

                if((retVal = rtk_svlan_checkAndCreateMbr(pFilter_action->filterSvlanVid, &svidx)) != RT_ERR_OK)
				    return retVal;

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(actType);
				aclAct.svidx_sact = svidx;
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
                break;
            case FILTER_ENACT_SVLAN_CVID:

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(actType);
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
				break;
            case FILTER_ENACT_POLICING_2:
                if(pFilter_action->filterPolicingIdx[2] >= (RTK_METER_NUM + RTL8367C_MAX_LOG_CNT_NUM))
                    return RT_ERR_INPUT;

                aclAct.sact = FILTER_ENACT_SVLAN_TYPE(actType);
                aclAct.svidx_sact = pFilter_action->filterPolicingIdx[2];
                aclActCtrl |= FILTER_ENACT_SVLAN_MASK;
                break;
            case FILTER_ENACT_POLICING_0:
                if(pFilter_action->filterPolicingIdx[0] >= (RTK_METER_NUM + RTL8367C_MAX_LOG_CNT_NUM))
                    return RT_ERR_INPUT;

                aclAct.aclmeteridx = pFilter_action->filterPolicingIdx[0];
                aclActCtrl |= FILTER_ENACT_POLICING_MASK;
                break;
            case FILTER_ENACT_PRIORITY:
            case FILTER_ENACT_1P_REMARK:
                if(pFilter_action->filterPriority > RTL8367C_PRIMAX)
                    return RT_ERR_INPUT;

                aclAct.priact = FILTER_ENACT_PRI_TYPE(actType);
                aclAct.pridx = pFilter_action->filterPriority;
                aclActCtrl |= FILTER_ENACT_PRIORITY_MASK;
                break;
            case FILTER_ENACT_DSCP_REMARK:
                if(pFilter_action->filterPriority > RTL8367C_DSCPMAX)
                    return RT_ERR_INPUT;

                aclAct.priact = FILTER_ENACT_PRI_TYPE(actType);
                aclAct.pridx = pFilter_action->filterPriority;
                aclActCtrl |= FILTER_ENACT_PRIORITY_MASK;
                break;
            case FILTER_ENACT_POLICING_3:
                if(pFilter_action->filterPriority >= (RTK_METER_NUM + RTL8367C_MAX_LOG_CNT_NUM))
                    return RT_ERR_INPUT;

                aclAct.priact = FILTER_ENACT_PRI_TYPE(actType);
                aclAct.pridx = pFilter_action->filterPolicingIdx[3];
                aclActCtrl |= FILTER_ENACT_PRIORITY_MASK;
                break;
            case FILTER_ENACT_DROP:

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(FILTER_ENACT_REDIRECT);
                aclAct.fwdact_ext = FALSE;

                aclAct.fwdpmask = 0;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_REDIRECT:
                RTK_CHK_PORTMASK_VALID(&pFilter_action->filterPortmask);

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.fwdact_ext = FALSE;

                rtk_switch_portmask_L2P_get(&pFilter_action->filterPortmask, &portmask);
                aclAct.fwdpmask = portmask;

                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;

            case FILTER_ENACT_ADD_DSTPORT:
                RTK_CHK_PORTMASK_VALID(&pFilter_action->filterPortmask);

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.fwdact_ext = FALSE;

                rtk_switch_portmask_L2P_get(&pFilter_action->filterPortmask, &portmask);
                aclAct.fwdpmask = portmask;

                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_MIRROR:
                RTK_CHK_PORTMASK_VALID(&pFilter_action->filterPortmask);

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.cact_ext = FALSE;

                rtk_switch_portmask_L2P_get(&pFilter_action->filterPortmask, &portmask);
                aclAct.fwdpmask = portmask;

                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_TRAP_CPU:

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(actType);
                aclAct.fwdact_ext = FALSE;

                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_COPY_CPU:
                if((retVal = rtl8367c_getAsicCputagTrapPort(&cpuPort)) != RT_ERR_OK)
                    return retVal;

                aclAct.fwdact = FILTER_ENACT_FWD_TYPE(FILTER_ENACT_MIRROR);
                aclAct.fwdact_ext = FALSE;

                aclAct.fwdpmask = 1 << cpuPort;
                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;
            case FILTER_ENACT_ISOLATION:
                RTK_CHK_PORTMASK_VALID(&pFilter_action->filterPortmask);

                aclAct.fwdact_ext = TRUE;

                rtk_switch_portmask_L2P_get(&pFilter_action->filterPortmask, &portmask);
                aclAct.fwdpmask = portmask;

                aclActCtrl |= FILTER_ENACT_FWD_MASK;
                break;

            case FILTER_ENACT_INTERRUPT:

                aclAct.aclint = TRUE;
                aclActCtrl |= FILTER_ENACT_INTGPIO_MASK;
                break;
            case FILTER_ENACT_GPO:

                aclAct.gpio_en = TRUE;
                aclAct.gpio_pin = pFilter_action->filterPin;
                aclActCtrl |= FILTER_ENACT_INTGPIO_MASK;
                break;
             case FILTER_ENACT_EGRESSCTAG_TAG:

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_VLANONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_TAGONLY;
                }
                aclAct.tag_fmt = FILTER_CTAGFMT_TAG;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_EGRESSCTAG_UNTAG:

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_VLANONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_TAGONLY;
                }
                aclAct.tag_fmt = FILTER_CTAGFMT_UNTAG;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_EGRESSCTAG_KEEP:

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_VLANONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_TAGONLY;
                }
                aclAct.tag_fmt = FILTER_CTAGFMT_KEEP;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
             case FILTER_ENACT_EGRESSCTAG_KEEPAND1PRMK:

                if(aclActCtrl &(FILTER_ENACT_CVLAN_MASK))
                {
                    if(aclAct.cact_ext == FILTER_ENACT_CACTEXT_VLANONLY)
                        aclAct.cact_ext = FILTER_ENACT_CACTEXT_BOTHVLANTAG;
                }
                else
                {
                    aclAct.cact_ext = FILTER_ENACT_CACTEXT_TAGONLY;
                }
                aclAct.tag_fmt = FILTER_CTAGFMT_KEEP1PRMK;
                aclActCtrl |= FILTER_ENACT_CVLAN_MASK;
                break;
           default:
                return RT_ERR_FILTER_INACL_ACT_NOT_SUPPORT;
            }
        }
    }


	/*check if free ACL rules are enough*/
    for(i = filter_id; i < (filter_id + noRulesAdd); i++)
    {
        if((retVal = rtl8367c_getAsicAclRule(i, &tempRule)) != RT_ERR_OK )
            return retVal;

        if(tempRule.valid == TRUE)
        {
            return RT_ERR_TBL_FULL;
        }
    }

	ruleId = 0;
    for(i = 0; i < RTL8367C_ACLTEMPLATENO; i++)
    {
        if(aclRule[i].valid == TRUE)
        {
            /* write ACL action control */
            if((retVal = rtl8367c_setAsicAclActCtrl(filter_id + ruleId, aclActCtrl)) != RT_ERR_OK )
                return retVal;
            /* write ACL action */
            if((retVal = rtl8367c_setAsicAclAct(filter_id + ruleId, &aclAct)) != RT_ERR_OK )
                return retVal;

            /* write ACL not */
            if((retVal = rtl8367c_setAsicAclNot(filter_id + ruleId, pFilter_cfg->invert)) != RT_ERR_OK )
                return retVal;
            /* write ACL rule */
            if((retVal = rtl8367c_setAsicAclRule(filter_id + ruleId, &aclRule[i])) != RT_ERR_OK )
                return retVal;

            /* only the first rule will be written with input action control, aclActCtrl of other rules will be zero */
            aclActCtrl = 0;
            memset(&aclAct, 0, sizeof(rtl8367c_acl_act_t));

			ruleId ++;
		}
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_del
 * Description:
 *      Delete an ACL configuration from ASIC
 * Input:
 *      filter_id   - Start index of ACL configuration.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_FILTER_ENTRYIDX  - Invalid filter_id.
 * Note:
 *      This function delete a group of ACL rules starting from filter_id.
 */
rtk_api_ret_t rtk_filter_igrAcl_cfg_del(rtk_filter_id_t filter_id)
{
    rtl8367c_aclrule initRule;
    rtl8367c_acl_act_t  initAct;
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(filter_id > RTL8367C_ACLRULEMAX )
        return RT_ERR_FILTER_ENTRYIDX;

    memset(&initRule, 0, sizeof(rtl8367c_aclrule));
    memset(&initAct, 0, sizeof(rtl8367c_acl_act_t));

    if((ret = rtl8367c_setAsicAclRule(filter_id, &initRule)) != RT_ERR_OK)
        return ret;
    if((ret = rtl8367c_setAsicAclActCtrl(filter_id, FILTER_ENACT_INIT_MASK))!= RT_ERR_OK)
        return ret;
    if((ret = rtl8367c_setAsicAclAct(filter_id, &initAct)) != RT_ERR_OK)
        return ret;
    if((ret = rtl8367c_setAsicAclNot(filter_id, DISABLED)) != RT_ERR_OK )
        return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_delAll
 * Description:
 *      Delete all ACL entries from ASIC
 * Input:
 *      None
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This function delete all ACL configuration from ASIC.
 */
rtk_api_ret_t rtk_filter_igrAcl_cfg_delAll(void)
{
    rtk_uint32            i;
    rtk_api_ret_t     ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    for(i = 0; i < RTL8367C_ACLRULENO; i++)
    {
        if((ret = rtl8367c_setAsicAclActCtrl(i, FILTER_ENACT_INIT_MASK))!= RT_ERR_OK)
            return ret;
        if((ret = rtl8367c_setAsicAclNot(i, DISABLED)) != RT_ERR_OK )
            return ret;
    }

    return rtl8367c_setAsicRegBit(RTL8367C_REG_ACL_RESET_CFG, RTL8367C_ACL_RESET_CFG_OFFSET, TRUE);;
}

/* Function Name:
 *      rtk_filter_igrAcl_cfg_get
 * Description:
 *      Get one ingress acl configuration from ASIC.
 * Input:
 *      filter_id       - Start index of ACL configuration.
 * Output:
 *      pFilter_cfg     - buffer pointer of ingress acl data
 *      pFilter_action  - buffer pointer of ingress acl action
 * Return:
 *      RT_ERR_OK              	- OK
 *      RT_ERR_FAILED          	- Failed
 *      RT_ERR_SMI             	- SMI access error
 *      RT_ERR_NULL_POINTER 	- Pointer pFilter_action or pFilter_cfg point to NULL.
 *      RT_ERR_FILTER_ENTRYIDX 	- Invalid entry index.
 * Note:
 *      This function get configuration from ASIC.
 */
rtk_api_ret_t rtk_filter_igrAcl_cfg_get(rtk_filter_id_t filter_id, rtk_filter_cfg_raw_t *pFilter_cfg, rtk_filter_action_t *pAction)
{
    rtk_api_ret_t               retVal;
    rtk_uint32                  i, tmp;
    rtl8367c_aclrule            aclRule;
    rtl8367c_acl_act_t          aclAct;
    rtk_uint32                  cpuPort;
    rtl8367c_acltemplate_t      type;
    rtl8367c_svlan_memconf_t    svlan_cfg;
    rtl8367c_vlanconfiguser     vlanMC;
    rtk_uint32                  phyPmask;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pFilter_cfg || NULL == pAction)
        return RT_ERR_NULL_POINTER;

    if(filter_id > RTL8367C_ACLRULEMAX)
        return RT_ERR_ENTRY_INDEX;

    if ((retVal = rtl8367c_getAsicAclRule(filter_id, &aclRule)) != RT_ERR_OK)
        return retVal;

    /* Check valid */
    if(aclRule.valid == 0)
    {
        pFilter_cfg->valid = DISABLED;
        return RT_ERR_OK;
    }

    phyPmask = aclRule.data_bits.active_portmsk;
    if(rtk_switch_portmask_P2L_get(phyPmask,&(pFilter_cfg->activeport.value)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    phyPmask = aclRule.care_bits.active_portmsk;
    if(rtk_switch_portmask_P2L_get(phyPmask,&(pFilter_cfg->activeport.mask)) != RT_ERR_OK)
        return RT_ERR_FAILED;

    for(i = 0; i <= CARE_TAG_IPV6; i++)
    {
        if(aclRule.data_bits.tag_exist & (1 << i))
            pFilter_cfg->careTag.tagType[i].value = 1;
        else
            pFilter_cfg->careTag.tagType[i].value = 0;

        if (aclRule.care_bits.tag_exist & (1 << i))
            pFilter_cfg->careTag.tagType[i].mask = 1;
        else
            pFilter_cfg->careTag.tagType[i].mask = 0;
    }

    if(filter_advanceCaretagField[aclRule.data_bits.type][0] == TRUE)
    {
        /* Advanced Care tag setting */
        for(i = CARE_TAG_TCP; i < CARE_TAG_END; i++)
        {
            if(aclRule.data_bits.field[filter_advanceCaretagField[aclRule.data_bits.type][1]] & (0x0001 << (i-CARE_TAG_TCP)) )
                pFilter_cfg->careTag.tagType[i].value = 1;
            else
                pFilter_cfg->careTag.tagType[i].value = 0;

            if(aclRule.care_bits.field[filter_advanceCaretagField[aclRule.data_bits.type][1]] & (0x0001 << (i-CARE_TAG_TCP)) )
                pFilter_cfg->careTag.tagType[i].mask = 1;
            else
                pFilter_cfg->careTag.tagType[i].mask = 0;
        }
    }

    for(i = 0; i < RTL8367C_ACLRULEFIELDNO; i++)
    {
        pFilter_cfg->careFieldRaw[i] = aclRule.care_bits.field[i];
        pFilter_cfg->dataFieldRaw[i] = aclRule.data_bits.field[i];
    }

    if ((retVal = rtl8367c_getAsicAclNot(filter_id, &tmp))!= RT_ERR_OK)
        return retVal;

    pFilter_cfg->invert = tmp;

    pFilter_cfg->valid = aclRule.valid;

    memset(pAction, 0, sizeof(rtk_filter_action_t));

    if ((retVal = rtl8367c_getAsicAclActCtrl(filter_id, &tmp))!= RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367c_getAsicAclAct(filter_id, &aclAct)) != RT_ERR_OK)
        return retVal;

    if(tmp & FILTER_ENACT_FWD_MASK)
    {
        if(TRUE == aclAct.fwdact_ext)
        {
            pAction->actEnable[FILTER_ENACT_ISOLATION] = TRUE;

            phyPmask = aclAct.fwdpmask;
            if(rtk_switch_portmask_P2L_get(phyPmask,&(pAction->filterPortmask)) != RT_ERR_OK)
                return RT_ERR_FAILED;
        }
        else if(aclAct.fwdact == RTL8367C_ACL_FWD_TRAP)
        {
            pAction->actEnable[FILTER_ENACT_TRAP_CPU] = TRUE;
        }
        else if (aclAct.fwdact == RTL8367C_ACL_FWD_MIRRORFUNTION )
        {
        	pAction->actEnable[FILTER_ENACT_MIRROR] = TRUE;

            phyPmask = aclAct.fwdpmask;
            if(rtk_switch_portmask_P2L_get(phyPmask,&(pAction->filterPortmask)) != RT_ERR_OK)
                return RT_ERR_FAILED;
		}
        else if (aclAct.fwdact == RTL8367C_ACL_FWD_REDIRECT)
        {
            if(aclAct.fwdpmask == 0 )
                pAction->actEnable[FILTER_ENACT_DROP] = TRUE;
            else
            {
                pAction->actEnable[FILTER_ENACT_REDIRECT] = TRUE;

                phyPmask = aclAct.fwdpmask;
                if(rtk_switch_portmask_P2L_get(phyPmask,&(pAction->filterPortmask)) != RT_ERR_OK)
                    return RT_ERR_FAILED;
            }
        }
        else if (aclAct.fwdact == RTL8367C_ACL_FWD_MIRROR)
        {
            if((retVal = rtl8367c_getAsicCputagTrapPort(&cpuPort)) != RT_ERR_OK)
                return retVal;
            if (aclAct.fwdpmask == (1 << cpuPort))
            {
                pAction->actEnable[FILTER_ENACT_COPY_CPU] = TRUE;
            }
            else
            {
                pAction->actEnable[FILTER_ENACT_ADD_DSTPORT] = TRUE;

                phyPmask = aclAct.fwdpmask;
                if(rtk_switch_portmask_P2L_get(phyPmask,&(pAction->filterPortmask)) != RT_ERR_OK)
                    return RT_ERR_FAILED;
            }
        }
        else
        {
            return RT_ERR_FAILED;
        }
    }

    if(tmp & FILTER_ENACT_POLICING_MASK)
    {
        pAction->actEnable[FILTER_ENACT_POLICING_0] = TRUE;
        pAction->filterPolicingIdx[0] = aclAct.aclmeteridx;
    }

    if(tmp & FILTER_ENACT_PRIORITY_MASK)
    {
    	if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_PRIORITY))
        {
        	pAction->actEnable[FILTER_ENACT_PRIORITY] = TRUE;
        	pAction->filterPriority = aclAct.pridx;
    	}
		else if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_1P_REMARK))
        {
        	pAction->actEnable[FILTER_ENACT_1P_REMARK] = TRUE;
        	pAction->filterPriority = aclAct.pridx;
    	}
		else if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_DSCP_REMARK))
        {
        	pAction->actEnable[FILTER_ENACT_DSCP_REMARK] = TRUE;
        	pAction->filterPriority = aclAct.pridx;
    	}
		else if(aclAct.priact == FILTER_ENACT_PRI_TYPE(FILTER_ENACT_POLICING_3))
        {
        	pAction->actEnable[FILTER_ENACT_POLICING_3] = TRUE;
        	pAction->filterPolicingIdx[3]  = aclAct.pridx;
    	}
    }

    if(tmp & FILTER_ENACT_SVLAN_MASK)
    {
    	if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_INGRESS))
        {
            if((retVal = rtl8367c_getAsicSvlanMemberConfiguration(aclAct.svidx_sact, &svlan_cfg)) != RT_ERR_OK)
				return retVal;

        	pAction->actEnable[FILTER_ENACT_SVLAN_INGRESS] = TRUE;
        	pAction->filterSvlanIdx = aclAct.svidx_sact;
            pAction->filterSvlanVid = svlan_cfg.vs_svid;
    	}
    	else if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_EGRESS))
        {
            if((retVal = rtl8367c_getAsicSvlanMemberConfiguration(aclAct.svidx_sact, &svlan_cfg)) != RT_ERR_OK)
				return retVal;

        	pAction->actEnable[FILTER_ENACT_SVLAN_EGRESS] = TRUE;
        	pAction->filterSvlanIdx = aclAct.svidx_sact;
            pAction->filterSvlanVid = svlan_cfg.vs_svid;
    	}
    	else if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_SVLAN_CVID))
        	pAction->actEnable[FILTER_ENACT_SVLAN_CVID] = TRUE;
    	else if(aclAct.sact == FILTER_ENACT_SVLAN_TYPE(FILTER_ENACT_POLICING_2))
        {
        	pAction->actEnable[FILTER_ENACT_POLICING_2] = TRUE;
        	pAction->filterPolicingIdx[2]  = aclAct.svidx_sact;
    	}
    }


    if(tmp & FILTER_ENACT_CVLAN_MASK)
    {
        if(FILTER_ENACT_CACTEXT_TAGONLY == aclAct.cact_ext ||
            FILTER_ENACT_CACTEXT_BOTHVLANTAG == aclAct.cact_ext )
        {
            if(FILTER_CTAGFMT_UNTAG == aclAct.tag_fmt)
            {
                pAction->actEnable[FILTER_ENACT_EGRESSCTAG_UNTAG] = TRUE;
            }
            else if(FILTER_CTAGFMT_TAG == aclAct.tag_fmt)
            {
                pAction->actEnable[FILTER_ENACT_EGRESSCTAG_TAG] = TRUE;
            }
            else if(FILTER_CTAGFMT_KEEP == aclAct.tag_fmt)
            {
                pAction->actEnable[FILTER_ENACT_EGRESSCTAG_KEEP] = TRUE;
            }
             else if(FILTER_CTAGFMT_KEEP1PRMK== aclAct.tag_fmt)
            {
                pAction->actEnable[FILTER_ENACT_EGRESSCTAG_KEEPAND1PRMK] = TRUE;
            }

        }

        if(FILTER_ENACT_CACTEXT_VLANONLY == aclAct.cact_ext ||
            FILTER_ENACT_CACTEXT_BOTHVLANTAG == aclAct.cact_ext )
        {
            if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_INGRESS))
            {
                if((retVal = rtl8367c_getAsicVlanMemberConfig(aclAct.cvidx_cact, &vlanMC)) != RT_ERR_OK)
                    return retVal;

                pAction->actEnable[FILTER_ENACT_CVLAN_INGRESS] = TRUE;
                pAction->filterCvlanIdx  = aclAct.cvidx_cact;
                pAction->filterCvlanVid  = vlanMC.evid;
            }
            else if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_EGRESS))
            {
                if((retVal = rtl8367c_getAsicVlanMemberConfig(aclAct.cvidx_cact, &vlanMC)) != RT_ERR_OK)
                    return retVal;

                pAction->actEnable[FILTER_ENACT_CVLAN_EGRESS] = TRUE;
                pAction->filterCvlanIdx  = aclAct.cvidx_cact;
                pAction->filterCvlanVid  = vlanMC.evid;
            }
            else if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_CVLAN_SVID))
            {
                pAction->actEnable[FILTER_ENACT_CVLAN_SVID] = TRUE;
            }
        	else if(aclAct.cact == FILTER_ENACT_CVLAN_TYPE(FILTER_ENACT_POLICING_1))
            {
            	pAction->actEnable[FILTER_ENACT_POLICING_1] = TRUE;
            	pAction->filterPolicingIdx[1]  = aclAct.cvidx_cact;
        	}
        }
    }

    if(tmp & FILTER_ENACT_INTGPIO_MASK)
    {
		if(TRUE == aclAct.aclint)
		{
			pAction->actEnable[FILTER_ENACT_INTERRUPT] = TRUE;
		}

		if(TRUE == aclAct.gpio_en)
		{
			pAction->actEnable[FILTER_ENACT_GPO] = TRUE;
			pAction->filterPin = aclAct.gpio_pin;
		}
    }

    /* Get field type of RAW data */
    if ((retVal = rtl8367c_getAsicAclTemplate(aclRule.data_bits.type, &type))!= RT_ERR_OK)
        return retVal;

    for(i = 0; i < RTL8367C_ACLRULEFIELDNO; i++)
    {
        pFilter_cfg->fieldRawType[i] = type.field[i];
    }/* end of for(i...) */

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_unmatchAction_set
 * Description:
 *      Set action to packets when no ACL configuration match
 * Input:
 *      port    - Port id.
 *      action  - Action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID 		- Invalid port id.
 *      RT_ERR_INPUT 		- Invalid input parameters.
 * Note:
 *      This function sets action of packets when no ACL configruation matches.
 */
rtk_api_ret_t rtk_filter_igrAcl_unmatchAction_set(rtk_port_t port, rtk_filter_unmatch_action_t action)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check port valid */
    RTK_CHK_PORT_VALID(port);

    if(action >= FILTER_UNMATCH_END)
        return RT_ERR_INPUT;

    if((ret = rtl8367c_setAsicAclUnmatchedPermit(rtk_switch_port_L2P_get(port), action)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_unmatchAction_get
 * Description:
 *      Get action to packets when no ACL configuration match
 * Input:
 *      port    - Port id.
 * Output:
 *      pAction - Action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
rtk_api_ret_t rtk_filter_igrAcl_unmatchAction_get(rtk_port_t port, rtk_filter_unmatch_action_t* pAction)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pAction)
        return RT_ERR_NULL_POINTER;

    /* Check port valid */
    RTK_CHK_PORT_VALID(port);

    if((ret = rtl8367c_getAsicAclUnmatchedPermit(rtk_switch_port_L2P_get(port), pAction)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_state_set
 * Description:
 *      Set state of ingress ACL.
 * Input:
 *      port    - Port id.
 *      state   - Ingress ACL state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
rtk_api_ret_t rtk_filter_igrAcl_state_set(rtk_port_t port, rtk_filter_state_t state)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check port valid */
    RTK_CHK_PORT_VALID(port);

    if(state >= RTK_ENABLE_END)
        return RT_ERR_INPUT;

    if((ret = rtl8367c_setAsicAcl(rtk_switch_port_L2P_get(port), state)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_state_get
 * Description:
 *      Get state of ingress ACL.
 * Input:
 *      port    - Port id.
 * Output:
 *      pState  - Ingress ACL state.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID      - Invalid port id.
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function gets action of packets when no ACL configruation matches.
 */
rtk_api_ret_t rtk_filter_igrAcl_state_get(rtk_port_t port, rtk_filter_state_t* pState)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pState)
        return RT_ERR_NULL_POINTER;

    /* Check port valid */
    RTK_CHK_PORT_VALID(port);

    if((ret = rtl8367c_getAsicAcl(rtk_switch_port_L2P_get(port), pState)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}
/* Function Name:
 *      rtk_filter_igrAcl_template_set
 * Description:
 *      Set template of ingress ACL.
 * Input:
 *      template - Ingress ACL template
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_INPUT           - Invalid input parameters.
 * Note:
 *      This function set ACL template.
 */
rtk_api_ret_t rtk_filter_igrAcl_template_set(rtk_filter_template_t *aclTemplate)
{
    rtk_api_ret_t retVal;
    rtk_uint32 idxField;
    rtl8367c_acltemplate_t aclType;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(aclTemplate->index >= RTK_MAX_NUM_OF_FILTER_TYPE)
        return RT_ERR_INPUT;

    for(idxField = 0; idxField < RTK_MAX_NUM_OF_FILTER_FIELD; idxField++)
    {
        if(aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_DMAC_15_0 ||
            (aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_CTAG && aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_IPV4_SIP_15_0 ) ||
            (aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_IPV4_DIP_31_16 && aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_IPV6_SIP_15_0 ) ||
            (aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_IPV6_DIP_31_16 && aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_VIDRANGE ) ||
            (aclTemplate->fieldType[idxField] > FILTER_FIELD_RAW_FIELD_VALID && aclTemplate->fieldType[idxField] < FILTER_FIELD_RAW_FIELD_SELECT00 ) ||
            aclTemplate->fieldType[idxField] >= FILTER_FIELD_RAW_END)
        {
            return RT_ERR_INPUT;
        }
    }

    for(idxField = 0; idxField < RTK_MAX_NUM_OF_FILTER_FIELD; idxField++)
    {
        aclType.field[idxField] = aclTemplate->fieldType[idxField];
    }

    if((retVal = rtl8367c_setAsicAclTemplate(aclTemplate->index, &aclType)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_template_get
 * Description:
 *      Get template of ingress ACL.
 * Input:
 *      template - Ingress ACL template
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      This function gets template of ACL.
 */
rtk_api_ret_t rtk_filter_igrAcl_template_get(rtk_filter_template_t *aclTemplate)
{
    rtk_api_ret_t ret;
    rtk_uint32 idxField;
    rtl8367c_acltemplate_t aclType;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == aclTemplate)
        return RT_ERR_NULL_POINTER;

    if(aclTemplate->index >= RTK_MAX_NUM_OF_FILTER_TYPE)
        return RT_ERR_INPUT;

   if((ret = rtl8367c_getAsicAclTemplate(aclTemplate->index, &aclType)) != RT_ERR_OK)
       return ret;

    for(idxField = 0; idxField < RTK_MAX_NUM_OF_FILTER_FIELD; idxField ++)
    {
        aclTemplate->fieldType[idxField] = aclType.field[idxField];
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_field_sel_set
 * Description:
 *      Set user defined field selectors in HSB
 * Input:
 *      index 		- index of field selector 0-15
 *      format 		- Format of field selector
 *      offset 		- Retrieving data offset
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      System support 16 user defined field selctors.
 * 		Each selector can be enabled or disable.
 *      User can defined retrieving 16-bits in many predefiend
 * 		standard l2/l3/l4 payload.
 */
rtk_api_ret_t rtk_filter_igrAcl_field_sel_set(rtk_uint32 index, rtk_field_sel_t format, rtk_uint32 offset)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(index >= RTL8367C_FIELDSEL_FORMAT_NUMBER)
        return RT_ERR_OUT_OF_RANGE;

    if(format >= FORMAT_END)
        return RT_ERR_OUT_OF_RANGE;

    if(offset > RTL8367C_FIELDSEL_MAX_OFFSET)
        return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367c_setAsicFieldSelector(index, (rtk_uint32)format, offset)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAcl_field_sel_get
 * Description:
 *      Get user defined field selectors in HSB
 * Input:
 *      index 	    - index of field selector 0-15
 * Output:
 *      pFormat 	- Format of field selector
 *      pOffset 	- Retrieving data offset
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 * Note:
 *      None.
 */
rtk_api_ret_t rtk_filter_igrAcl_field_sel_get(rtk_uint32 index, rtk_field_sel_t *pFormat, rtk_uint32 *pOffset)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pFormat || NULL == pOffset)
        return RT_ERR_NULL_POINTER;

    if(index >= RTL8367C_FIELDSEL_FORMAT_NUMBER)
        return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367c_getAsicFieldSelector(index, pFormat, pOffset)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_iprange_set
 * Description:
 *      Set IP Range check
 * Input:
 *      index 	    - index of IP Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: IPv4_SIP, 2: IPv4_DIP, 3:IPv6_SIP, 4:IPv6_DIP
 *      upperIp     - The upper bound of IP range
 *      lowerIp     - The lower Bound of IP range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperIp must be larger or equal than lowerIp.
 */
rtk_api_ret_t rtk_filter_iprange_set(rtk_uint32 index, rtk_filter_iprange_t type, ipaddr_t upperIp, ipaddr_t lowerIp)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(type >= IPRANGE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(lowerIp > upperIp)
        return RT_ERR_INPUT;

    if((ret = rtl8367c_setAsicAclIpRange(index, type, upperIp, lowerIp)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_iprange_get
 * Description:
 *      Set IP Range check
 * Input:
 *      index 	    - index of IP Range 0-15
 * Output:
 *      pType        - IP Range check type, 0:Delete a entry, 1: IPv4_SIP, 2: IPv4_DIP, 3:IPv6_SIP, 4:IPv6_DIP
 *      pUpperIp     - The upper bound of IP range
 *      pLowerIp     - The lower Bound of IP range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 * Note:
 *      None.
 */
rtk_api_ret_t rtk_filter_iprange_get(rtk_uint32 index, rtk_filter_iprange_t *pType, ipaddr_t *pUpperIp, ipaddr_t *pLowerIp)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if((NULL == pType) || (NULL == pUpperIp) || (NULL == pLowerIp))
        return RT_ERR_NULL_POINTER;

    if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367c_getAsicAclIpRange(index, pType, pUpperIp, pLowerIp)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_vidrange_set
 * Description:
 *      Set VID Range check
 * Input:
 *      index 	    - index of VID Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: CVID, 2: SVID
 *      upperVid    - The upper bound of VID range
 *      lowerVid    - The lower Bound of VID range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperVid must be larger or equal than lowerVid.
 */
rtk_api_ret_t rtk_filter_vidrange_set(rtk_uint32 index, rtk_filter_vidrange_t type, rtk_uint32 upperVid, rtk_uint32 lowerVid)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(type >= VIDRANGE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(lowerVid > upperVid)
        return RT_ERR_INPUT;

    if( (upperVid > RTL8367C_VIDMAX) || (lowerVid > RTL8367C_VIDMAX))
        return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367c_setAsicAclVidRange(index, type, upperVid, lowerVid)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_vidrange_get
 * Description:
 *      Get VID Range check
 * Input:
 *      index 	    - index of VID Range 0-15
 * Output:
 *      pType        - IP Range check type, 0:Unused, 1: CVID, 2: SVID
 *      pUpperVid    - The upper bound of VID range
 *      pLowerVid    - The lower Bound of VID range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 * Note:
 *      None.
 */
rtk_api_ret_t rtk_filter_vidrange_get(rtk_uint32 index, rtk_filter_vidrange_t *pType, rtk_uint32 *pUpperVid, rtk_uint32 *pLowerVid)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if((NULL == pType) || (NULL == pUpperVid) || (NULL == pLowerVid))
        return RT_ERR_NULL_POINTER;

    if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367c_getAsicAclVidRange(index, pType, pUpperVid, pLowerVid)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_portrange_set
 * Description:
 *      Set Port Range check
 * Input:
 *      index 	    - index of Port Range 0-15
 *      type        - IP Range check type, 0:Delete a entry, 1: Source Port, 2: Destnation Port
 *      upperPort   - The upper bound of Port range
 *      lowerPort   - The lower Bound of Port range
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      upperPort must be larger or equal than lowerPort.
 */
rtk_api_ret_t rtk_filter_portrange_set(rtk_uint32 index, rtk_filter_portrange_t type, rtk_uint32 upperPort, rtk_uint32 lowerPort)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if(type >= PORTRANGE_END)
        return RT_ERR_OUT_OF_RANGE;

    if(lowerPort > upperPort)
        return RT_ERR_INPUT;

    if(upperPort > RTL8367C_ACL_PORTRANGEMAX)
        return RT_ERR_INPUT;

    if(lowerPort > RTL8367C_ACL_PORTRANGEMAX)
        return RT_ERR_INPUT;

    if((ret = rtl8367c_setAsicAclPortRange(index, type, upperPort, lowerPort)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_portrange_get
 * Description:
 *      Set Port Range check
 * Input:
 *      index 	    - index of Port Range 0-15
 * Output:
 *      pType       - IP Range check type, 0:Delete a entry, 1: Source Port, 2: Destnation Port
 *      pUpperPort  - The upper bound of Port range
 *      pLowerPort  - The lower Bound of Port range
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SMI             - SMI access error
 *      RT_ERR_OUT_OF_RANGE    - The parameter is out of range
 *      RT_ERR_INPUT           - Input error
 * Note:
 *      None.
 */
rtk_api_ret_t rtk_filter_portrange_get(rtk_uint32 index, rtk_filter_portrange_t *pType, rtk_uint32 *pUpperPort, rtk_uint32 *pLowerPort)
{
    rtk_api_ret_t ret;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if((NULL == pType) || (NULL == pUpperPort) || (NULL == pLowerPort))
        return RT_ERR_NULL_POINTER;

    if(index > RTL8367C_ACLRANGEMAX)
		return RT_ERR_OUT_OF_RANGE;

    if((ret = rtl8367c_getAsicAclPortRange(index, pType, pUpperPort, pLowerPort)) != RT_ERR_OK)
       return ret;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_filter_igrAclPolarity_set
 * Description:
 *      Set ACL Goip control palarity
 * Input:
 *      polarity - 1: High, 0: Low
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      none
 */
rtk_api_ret_t rtk_filter_igrAclPolarity_set(rtk_uint32 polarity)
{
    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(polarity > 1)
        return RT_ERR_OUT_OF_RANGE;
    return rtl8367c_setAsicAclGpioPolarity(polarity);
}
/* Function Name:
 *      rtk_filter_igrAclPolarity_get
 * Description:
 *      Get ACL Goip control palarity
 * Input:
 *      pPolarity - 1: High, 0: Low
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 		- Success
 *      RT_ERR_SMI  	- SMI access error
 * Note:
 *      none
 */
rtk_api_ret_t rtk_filter_igrAclPolarity_get(rtk_uint32* pPolarity)
{
    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pPolarity)
        return RT_ERR_NULL_POINTER;

    return rtl8367c_getAsicAclGpioPolarity(pPolarity);
}

int rtk_acl_init(void)
{
	rtk_filter_igrAcl_init();
	rtk_filter_igrAcl_state_set(EXT_PORT1, DISABLED);
}

int rtk_acl_cfg_start(void **handl)
{
	rtk_filter_cfg_t    *cfg;

	cfg = kmalloc(sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		return -1;

	memset(cfg, 0x00, sizeof(rtk_filter_cfg_t));
	*handl = cfg;
	return 0;
}

int rtk_acl_cfg_add_snet(void *handl, unsigned int ipaddr, unsigned int ipmask)
{
	rtk_filter_cfg_t    *cfg = handl;
	rtk_filter_field_t  *field;
	rtk_api_ret_t ret_val = 0;

	field = kmalloc(sizeof(*field), GFP_KERNEL);
	if (!field)
		return -1;
	memset(field, 0x00, sizeof(rtk_filter_field_t));
	field->fieldType = FILTER_FIELD_IPV4_SIP;
	field->filter_pattern_union.inData.dataType = FILTER_FIELD_DATA_MASK;
	field->filter_pattern_union.inData.value = ipaddr;
	field->filter_pattern_union.inData.mask = ipmask;

	ret_val = rtk_filter_igrAcl_field_add(cfg, field);
	if (ret_val != RT_ERR_OK) {
		return -1;
	}
	return 0;
}

int rtk_acl_cfg_add_dnet(void *handl, unsigned int ipaddr, unsigned int ipmask)
{
	rtk_filter_cfg_t    *cfg = handl;
	rtk_filter_field_t  *field;
	rtk_api_ret_t ret_val = 0;

	field = kmalloc(sizeof(*field), GFP_KERNEL);
	if (!field)
		return -1;
	memset(field, 0x00, sizeof(rtk_filter_field_t));
	field->fieldType = FILTER_FIELD_IPV4_DIP;
	field->filter_pattern_union.inData.dataType = FILTER_FIELD_DATA_MASK;
	field->filter_pattern_union.inData.value = ipaddr;
	field->filter_pattern_union.inData.mask = ipmask;

	ret_val = rtk_filter_igrAcl_field_add(cfg, field);
	if (ret_val != RT_ERR_OK) {
		return -1;
	}
	return 0;
}

int rtk_acl_cfg_add_vid(void *handl, unsigned short vid)
{
	rtk_filter_cfg_t    *cfg = handl;
	rtk_filter_field_t  *field;
	rtk_api_ret_t ret_val = 0;

	field = kmalloc(sizeof(*field), GFP_KERNEL);
	if (!field)
		return -1;
	memset(field, 0x00, sizeof(rtk_filter_field_t));
	field->fieldType = FILTER_FIELD_CTAG;
	field->filter_pattern_union.ctag.pri.value = 0;
	field->filter_pattern_union.ctag.pri.mask = 0;
	field->filter_pattern_union.ctag.cfi.value = 0;
	field->filter_pattern_union.ctag.cfi.mask = 0;
	field->filter_pattern_union.ctag.vid.value = vid;
	field->filter_pattern_union.ctag.vid.mask = 0x0FFF;

	ret_val = rtk_filter_igrAcl_field_add(cfg, field);
	if (ret_val != RT_ERR_OK) {
		return -1;
	}
	return 0;
}

int rtk_acl_cfg_add_padding(void *handl)
{
	rtk_filter_cfg_t    *cfg = handl;
	rtk_filter_field_t  *field;
	rtk_api_ret_t ret_val = 0;

	field = kmalloc(sizeof(*field), GFP_KERNEL);
	if (!field)
		return -1;
	memset(field, 0x00, sizeof(rtk_filter_field_t));
	field->fieldType = FILTER_FIELD_PATTERN_MATCH;

	ret_val = rtk_filter_igrAcl_field_add(cfg, field);
	if (ret_val != RT_ERR_OK) {
		return -1;
	}
	return 0;
}
/****
action
****/
int rtk_acl_cfg_commit(void *handl, int action, int index, int port, int *outdex)
{
	rtk_filter_cfg_t    *cfg = handl;
	rtk_filter_action_t act;
	unsigned int     ruleNum;
	rtk_portmask_t   portmask;
	rtk_api_ret_t ret_val = RT_ERR_INPUT;

	if (!cfg->fieldHead) {
		ret_val = rtk_acl_cfg_add_padding(handl);
		if (ret_val != 0) {
			return ret_val;
		}
	}

	portmask.bits[0] = halCtrl.valid_utp_portmask;
	if (port >= 0) {
		portmask.bits[0] = 0;
		port = rtk_switch_port_P2L_get(port);
		RTK_PORTMASK_PORT_SET(portmask, port);
	}

	ret_val = RT_ERR_INPUT;
	switch (action) {
		case CMT_ACTION_FLUSH:
			if (index >= 0) {
				ret_val = rtk_filter_igrAcl_cfg_del(index);
				if (ret_val == RT_ERR_OK) {
					*outdex = index - 1;
				}
			}
			else {
				ret_val = rtk_filter_igrAcl_cfg_delAll();
				if (ret_val == RT_ERR_OK) {
					*outdex = index - 1;
				}
			}
			break;
		case CMT_ACTION_ADD_DENY:
			memset(&act, 0x00, sizeof(rtk_filter_action_t));
			cfg->activeport.value.bits[0] = portmask.bits[0];
			rtk_switch_logPortMask_get(&cfg->activeport.mask);
			cfg->invert = 0;

			act.actEnable[FILTER_ENACT_DROP] = 1;
			ret_val = rtk_filter_igrAcl_cfg_add(index, cfg, &act, &ruleNum);
			if (ret_val == RT_ERR_OK) {
				*outdex = index + ruleNum - 1;
			}
			break;
		case CMT_ACTION_ADD_ALLOW:
			memset(&act, 0x00, sizeof(rtk_filter_action_t));
			cfg->activeport.value.bits[0] = portmask.bits[0];
			rtk_switch_logPortMask_get(&cfg->activeport.mask);
			cfg->invert = 0;

			act.actEnable[FILTER_ENACT_ADD_DSTPORT] = 1;
			//rtk_switch_logPortMask_get(&act.filterPortmask);
			ret_val = rtk_filter_igrAcl_cfg_add(index, cfg, &act, &ruleNum);
			if (ret_val == RT_ERR_OK) {
				*outdex = index + ruleNum - 1;
			}
			break;
		default:
			break;
	}
	if (ret_val != RT_ERR_OK) {
		return -1;
	}
	return 0;
}

int rtk_acl_cfg_finish(void *handl)
{
	rtk_filter_cfg_t    *cfg = handl;
	rtk_filter_field_t  *field;

	if (cfg) {
		while (cfg->fieldHead) {
			field = cfg->fieldHead;
			cfg->fieldHead = field->next;
			kfree(field);
		}
		kfree(cfg);
	}
	return 0;
}