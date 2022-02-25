#include "../ag71xx.h"
#include "rtl8367s_api.h"
#include <linux/switch.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/spinlock.h>
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

#define PHY_CONTROL_REG                             0
#define PHY_STATUS_REG                              1
#define PHY_AN_ADVERTISEMENT_REG                    4
#define PHY_AN_LINKPARTNER_REG                      5
#define PHY_1000_BASET_CONTROL_REG                  9
#define PHY_1000_BASET_STATUS_REG                   10
#define PHY_RESOLVED_REG                            26

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

#define    RTL8367C_REG_PHY_AD    0x130f
#define    RTL8367C_PDNPHY_OFFSET    5

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

extern void MDC_MDIO_READ(u32 preamble_len, u32 phy_id, u32 register_id, u32 *pData);
extern void MDC_MDIO_WRITE(u32 preamble_len, u32 phy_id, u32 register_id, u32 data);

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
static ret_t rtl8367c_setAsicRegBit(rtk_uint32 reg, rtk_uint32 bit, rtk_uint32 value)
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
static ret_t rtl8367c_getAsicRegBits(rtk_uint32 reg, rtk_uint32 bits, rtk_uint32 *pValue)
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
static ret_t rtl8367c_getAsicRegBit(rtk_uint32 reg, rtk_uint32 bit, rtk_uint32 *pValue)
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
static ret_t rtl8367c_setAsicRegBits(rtk_uint32 reg, rtk_uint32 bits, rtk_uint32 value)
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
static ret_t rtl8367c_setAsicReg(rtk_uint32 reg, rtk_uint32 value)
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
static ret_t rtl8367c_getAsicReg(rtk_uint32 reg, rtk_uint32 *pValue)
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
static rtk_api_ret_t rtk_switch_logicalPortCheck(rtk_port_t logicalPort)
{
    if(logicalPort >= RTK_SWITCH_PORT_NUM)
        return RT_ERR_FAILED;

    if(halCtrl.l2p_port[logicalPort] == 0xFF)
        return RT_ERR_FAILED;

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
#define RTK_PORTMASK_IS_PORT_SET(__portmask__, __port__)    (((__portmask__).bits[0] & (0x00000001 << __port__)) ? 1 : 0)
#define RTK_PORTMASK_SCAN(__portmask__, __port__)           for(__port__ = 0; __port__ < RTK_SWITCH_PORT_NUM; __port__++)  if(RTK_PORTMASK_IS_PORT_SET(__portmask__, __port__))
#define RTK_PORTMASK_CLEAR(__portmask__)                    ((__portmask__).bits[0] = 0)

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

ret_t rtl8367c_setAsicPortEnableAll(rtk_uint32 enable)
{
    if(enable >= 2)
        return RT_ERR_INPUT;

    return rtl8367c_setAsicRegBit(RTL8367C_REG_PHY_AD, RTL8367C_PDNPHY_OFFSET, !enable);
}

/* Function Name:
 *      rtk_port_phyEnableAll_set
 * Description:
 *      Set all PHY enable status.
 * Input:
 *      enable - PHY Enable State.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_ENABLE       - Invalid enable input.
 * Note:
 *      This API can set all PHY status.
 *      The configuration of all PHY is as following:
 *      - DISABLE
 *      - ENABLE
 */
rtk_api_ret_t rtk_port_phyEnableAll_set(rtk_enable_t enable)
{
    rtk_api_ret_t retVal;
    rtk_uint32 data;
    rtk_uint32 port;

    /* Check initialization state */
    //RTK_CHK_INIT_STATE();

    if (enable >= RTK_ENABLE_END)
        return RT_ERR_ENABLE;

    if ((retVal = rtl8367c_setAsicPortEnableAll(enable)) != RT_ERR_OK)
        return retVal;

    RTK_SCAN_ALL_LOG_PORT(port)
    {
        if(rtk_switch_isUtpPort(port) == RT_ERR_OK)
        {
            if ((retVal = rtk_port_phyReg_get(port, PHY_CONTROL_REG, &data)) != RT_ERR_OK)
                return retVal;

            if (ENABLED == enable)
            {
                data &= 0xF7FF;
                data |= 0x0200;
            }
            else
            {
                data |= 0x0800;
            }

            if ((retVal = rtk_port_phyReg_set(port, PHY_CONTROL_REG, data)) != RT_ERR_OK)
                return retVal;
        }
    }

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_port_phyReg_get
 * Description:
 *      Get PHY register data of the specific port.
 * Input:
 *      port    - Port id.
 *      reg     - Register id
 * Output:
 *      pData   - Register data
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can get PHY register data of the specific port.
 */
rtk_api_ret_t rtk_port_phyReg_get(rtk_port_t port, rtk_port_phy_reg_t reg, rtk_port_phy_data_t *pData)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
   // RTK_CHK_INIT_STATE();

    /* Check Port Valid */
    //RTK_CHK_PORT_IS_UTP(port);

    if ((retVal = rtl8367c_getAsicPHYReg(rtk_switch_port_L2P_get(port), reg, pData)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_port_phyReg_set
 * Description:
 *      Set PHY register data of the specific port.
 * Input:
 *      port    - port id.
 *      reg     - Register id
 *      regData - Register data
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID          - Invalid port number.
 *      RT_ERR_PHY_REG_ID       - Invalid PHY address
 *      RT_ERR_BUSYWAIT_TIMEOUT - PHY access busy
 * Note:
 *      This API can set PHY register data of the specific port.
 */
rtk_api_ret_t rtk_port_phyReg_set(rtk_port_t port, rtk_port_phy_reg_t reg, rtk_port_phy_data_t regData)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    //RTK_CHK_INIT_STATE();

    /* Check Port Valid */
    //RTK_CHK_PORT_IS_UTP(port);

    if ((retVal = rtl8367c_setAsicPHYReg(rtk_switch_port_L2P_get(port), reg, regData)) != RT_ERR_OK)
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
