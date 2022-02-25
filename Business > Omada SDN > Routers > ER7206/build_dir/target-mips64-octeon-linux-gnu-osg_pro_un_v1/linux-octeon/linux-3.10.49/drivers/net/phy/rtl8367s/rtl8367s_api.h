#ifndef __RTL8367S_API_H__
#define __RTL8367S_API_H__

#define ETH_ALEN 6
#define RTK_TOTAL_NUM_OF_WORD_FOR_1BIT_PORT_LIST    1

#define RTK_SWITCH_PORT_NUM (32)
#define RTK_PORTMASK_CLEAR(__portmask__)                    ((__portmask__).bits[0] = 0)
#define RTK_PORTMASK_PORT_SET(__portmask__, __port__)       ((__portmask__).bits[0] |= (0x00000001 << __port__))
#define RTK_PORTMASK_PORT_CLEAR(__portmask__, __port__)     ((__portmask__).bits[0] &= ~(0x00000001 << __port__))
#define RTK_PORTMASK_IS_PORT_SET(__portmask__, __port__)    (((__portmask__).bits[0] & (0x00000001 << __port__)) ? 1 : 0)
#define RTK_PORTMASK_SCAN(__portmask__, __port__)           for(__port__ = 0; __port__ < RTK_SWITCH_PORT_NUM; __port__++)  if(RTK_PORTMASK_IS_PORT_SET(__portmask__, __port__))

typedef unsigned long long      rtk_uint64;
typedef long long               rtk_int64;
typedef unsigned int            rtk_uint32;
typedef int                     rtk_int32;
typedef unsigned short          rtk_uint16;
typedef short                   rtk_int16;
typedef unsigned char           rtk_uint8;
typedef char                    rtk_int8;
typedef unsigned char           u8;
typedef unsigned short          u16;
typedef unsigned int            u32;
//typedef char                    s8;
typedef short                   s16;
typedef int                     s32;

typedef rtk_int32                   ret_t;
typedef rtk_uint32                  rtk_rate_t;     /* rate type  */
typedef rtk_uint32                      ipaddr_t;

typedef rtk_int32                   rtk_api_ret_t;
typedef rtk_uint32  rtk_vlan_t;     /* vlan id type */
typedef rtk_uint32  rtk_pri_t;      /* priority vlaue */
typedef rtk_uint64                  rtk_u_long_t;
typedef rtk_u_long_t rtk_stat_counter_t;
typedef rtk_uint32  rtk_data_t;

#define RTL8367C_LUT_ENTRY_SIZE                 6
#define RTL8367C_LUT_BUSY_CHECK_NO              10
#define RTL8367C_HIT_STATUS_OFFSET              12

typedef enum rt_error_code_e
{
    RT_ERR_FAILED = -1,                             /* General Error                                                                    */

    /* 0x0000xxxx for common error code */
    RT_ERR_OK = 0,                                  /* 0x00000000, OK                                                                   */
    RT_ERR_INPUT,                                   /* 0x00000001, invalid input parameter                                              */
    RT_ERR_UNIT_ID,                                 /* 0x00000002, invalid unit id                                                      */
    RT_ERR_PORT_ID,                                 /* 0x00000003, invalid port id                                                      */
    RT_ERR_PORT_MASK,                               /* 0x00000004, invalid port mask                                                    */
    RT_ERR_PORT_LINKDOWN,                           /* 0x00000005, link down port status                                                */
    RT_ERR_ENTRY_INDEX,                             /* 0x00000006, invalid entry index                                                  */
    RT_ERR_NULL_POINTER,                            /* 0x00000007, input parameter is null pointer                                      */
    RT_ERR_QUEUE_ID,                                /* 0x00000008, invalid queue id                                                     */
    RT_ERR_QUEUE_NUM,                               /* 0x00000009, invalid queue number                                                 */
    RT_ERR_BUSYWAIT_TIMEOUT,                        /* 0x0000000a, busy watting time out                                                */
    RT_ERR_MAC,                                     /* 0x0000000b, invalid mac address                                                  */
    RT_ERR_OUT_OF_RANGE,                            /* 0x0000000c, input parameter out of range                                         */
    RT_ERR_CHIP_NOT_SUPPORTED,                      /* 0x0000000d, functions not supported by this chip model                           */
    RT_ERR_SMI,                                     /* 0x0000000e, SMI error                                                            */
    RT_ERR_NOT_INIT,                                /* 0x0000000f, The module is not initial                                            */
    RT_ERR_CHIP_NOT_FOUND,                          /* 0x00000010, The chip can not found                                               */
    RT_ERR_NOT_ALLOWED,                             /* 0x00000011, actions not allowed by the function                                  */
    RT_ERR_DRIVER_NOT_FOUND,                        /* 0x00000012, The driver can not found                                             */
    RT_ERR_SEM_LOCK_FAILED,                         /* 0x00000013, Failed to lock semaphore                                             */
    RT_ERR_SEM_UNLOCK_FAILED,                       /* 0x00000014, Failed to unlock semaphore                                           */
    RT_ERR_ENABLE,                                  /* 0x00000015, invalid enable parameter                                             */
    RT_ERR_TBL_FULL,                                /* 0x00000016, input table full                                                     */

    /* 0x0001xxxx for vlan */
    RT_ERR_VLAN_VID = 0x00010000,                   /* 0x00010000, invalid vid                                                          */
    RT_ERR_VLAN_PRIORITY,                           /* 0x00010001, invalid 1p priority                                                  */
    RT_ERR_VLAN_EMPTY_ENTRY,                        /* 0x00010002, emtpy entry of vlan table                                            */
    RT_ERR_VLAN_ACCEPT_FRAME_TYPE,                  /* 0x00010003, invalid accept frame type                                            */
    RT_ERR_VLAN_EXIST,                              /* 0x00010004, vlan is exist                                                        */
    RT_ERR_VLAN_ENTRY_NOT_FOUND,                    /* 0x00010005, specified vlan entry not found                                       */
    RT_ERR_VLAN_PORT_MBR_EXIST,                     /* 0x00010006, member port exist in the specified vlan                              */
    RT_ERR_VLAN_PROTO_AND_PORT,                     /* 0x00010008, invalid protocol and port based vlan                              */

    /* 0x0002xxxx for svlan */
    RT_ERR_SVLAN_ENTRY_INDEX = 0x00020000,          /* 0x00020000, invalid svid entry no                                                */
    RT_ERR_SVLAN_ETHER_TYPE,                        /* 0x00020001, invalid SVLAN ether type                                             */
    RT_ERR_SVLAN_TABLE_FULL,                        /* 0x00020002, no empty entry in SVLAN table                                        */
    RT_ERR_SVLAN_ENTRY_NOT_FOUND,                   /* 0x00020003, specified svlan entry not found                                      */
    RT_ERR_SVLAN_EXIST,                             /* 0x00020004, SVLAN entry is exist                                                 */
    RT_ERR_SVLAN_VID,                               /* 0x00020005, invalid svid                                                         */

    /* 0x0003xxxx for MSTP */
    RT_ERR_MSTI = 0x00030000,                       /* 0x00030000, invalid msti                                                         */
    RT_ERR_MSTP_STATE,                              /* 0x00030001, invalid spanning tree status                                         */
    RT_ERR_MSTI_EXIST,                              /* 0x00030002, MSTI exist                                                           */
    RT_ERR_MSTI_NOT_EXIST,                          /* 0x00030003, MSTI not exist                                                       */

    /* 0x0004xxxx for BUCKET */
    RT_ERR_TIMESLOT = 0x00040000,                   /* 0x00040000, invalid time slot                                                    */
    RT_ERR_TOKEN,                                   /* 0x00040001, invalid token amount                                                 */
    RT_ERR_RATE,                                    /* 0x00040002, invalid rate                                                         */
    RT_ERR_TICK,                                    /* 0x00040003, invalid tick                                                 */

    /* 0x0005xxxx for RMA */
    RT_ERR_RMA_ADDR = 0x00050000,                   /* 0x00050000, invalid rma mac address                                              */
    RT_ERR_RMA_ACTION,                              /* 0x00050001, invalid rma action                                                   */

    /* 0x0006xxxx for L2 */
    RT_ERR_L2_HASH_KEY = 0x00060000,                /* 0x00060000, invalid L2 Hash key                                                  */
    RT_ERR_L2_HASH_INDEX,                           /* 0x00060001, invalid L2 Hash index                                                */
    RT_ERR_L2_CAM_INDEX,                            /* 0x00060002, invalid L2 CAM index                                                 */
    RT_ERR_L2_ENRTYSEL,                             /* 0x00060003, invalid EntrySel                                                     */
    RT_ERR_L2_INDEXTABLE_INDEX,                     /* 0x00060004, invalid L2 index table(=portMask table) index                        */
    RT_ERR_LIMITED_L2ENTRY_NUM,                     /* 0x00060005, invalid limited L2 entry number                                      */
    RT_ERR_L2_AGGREG_PORT,                          /* 0x00060006, this aggregated port is not the lowest physical
                                                                   port of its aggregation group                                        */
    RT_ERR_L2_FID,                                  /* 0x00060007, invalid fid                                                          */
    RT_ERR_L2_VID,                                 /* 0x00060008, invalid cvid                                                         */
    RT_ERR_L2_NO_EMPTY_ENTRY,                       /* 0x00060009, no empty entry in L2 table                                           */
    RT_ERR_L2_ENTRY_NOTFOUND,                       /* 0x0006000a, specified entry not found                                            */
    RT_ERR_L2_INDEXTBL_FULL,                        /* 0x0006000b, the L2 index table is full                                           */
    RT_ERR_L2_INVALID_FLOWTYPE,                     /* 0x0006000c, invalid L2 flow type                                                 */
    RT_ERR_L2_L2UNI_PARAM,                          /* 0x0006000d, invalid L2 unicast parameter                                         */
    RT_ERR_L2_L2MULTI_PARAM,                        /* 0x0006000e, invalid L2 multicast parameter                                       */
    RT_ERR_L2_IPMULTI_PARAM,                        /* 0x0006000f, invalid L2 ip multicast parameter                                    */
    RT_ERR_L2_PARTIAL_HASH_KEY,                     /* 0x00060010, invalid L2 partial Hash key                                          */
    RT_ERR_L2_EMPTY_ENTRY,                          /* 0x00060011, the entry is empty(invalid)                                          */
    RT_ERR_L2_FLUSH_TYPE,                           /* 0x00060012, the flush type is invalid                                            */
    RT_ERR_L2_NO_CPU_PORT,                          /* 0x00060013, CPU port not exist                                                   */

    /* 0x0007xxxx for FILTER (PIE) */
    RT_ERR_FILTER_BLOCKNUM = 0x00070000,            /* 0x00070000, invalid block number                                                 */
    RT_ERR_FILTER_ENTRYIDX,                         /* 0x00070001, invalid entry index                                                  */
    RT_ERR_FILTER_CUTLINE,                          /* 0x00070002, invalid cutline value                                                */
    RT_ERR_FILTER_FLOWTBLBLOCK,                     /* 0x00070003, block belongs to flow table                                          */
    RT_ERR_FILTER_INACLBLOCK,                       /* 0x00070004, block belongs to ingress ACL                                         */
    RT_ERR_FILTER_ACTION,                           /* 0x00070005, action doesn't consist to entry type                                 */
    RT_ERR_FILTER_INACL_RULENUM,                    /* 0x00070006, invalid ACL rulenum                                                  */
    RT_ERR_FILTER_INACL_TYPE,                       /* 0x00070007, entry type isn't an ingress ACL rule                                 */
    RT_ERR_FILTER_INACL_EXIST,                      /* 0x00070008, ACL entry is already exit                                            */
    RT_ERR_FILTER_INACL_EMPTY,                      /* 0x00070009, ACL entry is empty                                                   */
    RT_ERR_FILTER_FLOWTBL_TYPE,                     /* 0x0007000a, entry type isn't an flow table rule                                  */
    RT_ERR_FILTER_FLOWTBL_RULENUM,                  /* 0x0007000b, invalid flow table rulenum                                           */
    RT_ERR_FILTER_FLOWTBL_EMPTY,                    /* 0x0007000c, flow table entry is empty                                            */
    RT_ERR_FILTER_FLOWTBL_EXIST,                    /* 0x0007000d, flow table entry is already exist                                    */
    RT_ERR_FILTER_METER_ID,                         /* 0x0007000e, invalid metering id                                                  */
    RT_ERR_FILTER_LOG_ID,                           /* 0x0007000f, invalid log id                                                       */
    RT_ERR_FILTER_INACL_NONE_BEGIN_IDX,             /* 0x00070010, entry index is not starting index of a group of rules                */
    RT_ERR_FILTER_INACL_ACT_NOT_SUPPORT,            /* 0x00070011, action not support                                                    */
    RT_ERR_FILTER_INACL_RULE_NOT_SUPPORT,           /* 0x00070012, rule not support                                                   */

    /* 0x0008xxxx for ACL Rate Limit */
    RT_ERR_ACLRL_HTHR = 0x00080000,                 /* 0x00080000, invalid high threshold                                               */
    RT_ERR_ACLRL_TIMESLOT,                          /* 0x00080001, invalid time slot                                                    */
    RT_ERR_ACLRL_TOKEN,                             /* 0x00080002, invalid token amount                                                 */
    RT_ERR_ACLRL_RATE,                              /* 0x00080003, invalid rate                                                         */

    /* 0x0009xxxx for Link aggregation */
    RT_ERR_LA_CPUPORT = 0x00090000,                 /* 0x00090000, CPU port can not be aggregated port                                  */
    RT_ERR_LA_TRUNK_ID,                             /* 0x00090001, invalid trunk id                                                     */
    RT_ERR_LA_PORTMASK,                             /* 0x00090002, invalid port mask                                                    */
    RT_ERR_LA_HASHMASK,                             /* 0x00090003, invalid hash mask                                                    */
    RT_ERR_LA_DUMB,                                 /* 0x00090004, this API should be used in 802.1ad dumb mode                         */
    RT_ERR_LA_PORTNUM_DUMB,                         /* 0x00090005, it can only aggregate at most four ports when 802.1ad dumb mode      */
    RT_ERR_LA_PORTNUM_NORMAL,                       /* 0x00090006, it can only aggregate at most eight ports when 802.1ad normal mode   */
    RT_ERR_LA_MEMBER_OVERLAP,                       /* 0x00090007, the specified port mask is overlapped with other group               */
    RT_ERR_LA_NOT_MEMBER_PORT,                      /* 0x00090008, the port is not a member port of the trunk                           */
    RT_ERR_LA_TRUNK_NOT_EXIST,                      /* 0x00090009, the trunk doesn't exist                                              */


    /* 0x000axxxx for storm filter */
    RT_ERR_SFC_TICK_PERIOD = 0x000a0000,            /* 0x000a0000, invalid SFC tick period                                              */
    RT_ERR_SFC_UNKNOWN_GROUP,                       /* 0x000a0001, Unknown Storm filter group                                           */

    /* 0x000bxxxx for pattern match */
    RT_ERR_PM_MASK = 0x000b0000,                    /* 0x000b0000, invalid pattern length. Pattern length should be 8                   */
    RT_ERR_PM_LENGTH,                               /* 0x000b0001, invalid pattern match mask, first byte must care                     */
    RT_ERR_PM_MODE,                                 /* 0x000b0002, invalid pattern match mode                                           */

    /* 0x000cxxxx for input bandwidth control */
    RT_ERR_INBW_TICK_PERIOD = 0x000c0000,           /* 0x000c0000, invalid tick period for input bandwidth control                      */
    RT_ERR_INBW_TOKEN_AMOUNT,                       /* 0x000c0001, invalid amount of token for input bandwidth control                  */
    RT_ERR_INBW_FCON_VALUE,                         /* 0x000c0002, invalid flow control ON threshold value for input bandwidth control  */
    RT_ERR_INBW_FCOFF_VALUE,                        /* 0x000c0003, invalid flow control OFF threshold value for input bandwidth control */
    RT_ERR_INBW_FC_ALLOWANCE,                       /* 0x000c0004, invalid allowance of incomming packet for input bandwidth control    */
    RT_ERR_INBW_RATE,                               /* 0x000c0005, invalid input bandwidth                                              */

    /* 0x000dxxxx for QoS */
    RT_ERR_QOS_1P_PRIORITY = 0x000d0000,            /* 0x000d0000, invalid 802.1P priority                                              */
    RT_ERR_QOS_DSCP_VALUE,                          /* 0x000d0001, invalid DSCP value                                                   */
    RT_ERR_QOS_INT_PRIORITY,                        /* 0x000d0002, invalid internal priority                                            */
    RT_ERR_QOS_SEL_DSCP_PRI,                        /* 0x000d0003, invalid DSCP selection priority                                      */
    RT_ERR_QOS_SEL_PORT_PRI,                        /* 0x000d0004, invalid port selection priority                                      */
    RT_ERR_QOS_SEL_IN_ACL_PRI,                      /* 0x000d0005, invalid ingress ACL selection priority                               */
    RT_ERR_QOS_SEL_CLASS_PRI,                       /* 0x000d0006, invalid classifier selection priority                                */
    RT_ERR_QOS_EBW_RATE,                            /* 0x000d0007, invalid egress bandwidth rate                                        */
    RT_ERR_QOS_SCHE_TYPE,                           /* 0x000d0008, invalid QoS scheduling type                                          */
    RT_ERR_QOS_QUEUE_WEIGHT,                        /* 0x000d0009, invalid Queue weight                                                 */
    RT_ERR_QOS_SEL_PRI_SOURCE,                      /* 0x000d000a, invalid selection of priority source                                                 */

    /* 0x000exxxx for port ability */
    RT_ERR_PHY_PAGE_ID = 0x000e0000,                /* 0x000e0000, invalid PHY page id                                                  */
    RT_ERR_PHY_REG_ID,                              /* 0x000e0001, invalid PHY reg id                                                   */
    RT_ERR_PHY_DATAMASK,                            /* 0x000e0002, invalid PHY data mask                                                */
    RT_ERR_PHY_AUTO_NEGO_MODE,                      /* 0x000e0003, invalid PHY auto-negotiation mode*/
    RT_ERR_PHY_SPEED,                               /* 0x000e0004, invalid PHY speed setting                                            */
    RT_ERR_PHY_DUPLEX,                              /* 0x000e0005, invalid PHY duplex setting                                           */
    RT_ERR_PHY_FORCE_ABILITY,                       /* 0x000e0006, invalid PHY force mode ability parameter                             */
    RT_ERR_PHY_FORCE_1000,                          /* 0x000e0007, invalid PHY force mode 1G speed setting                              */
    RT_ERR_PHY_TXRX,                                /* 0x000e0008, invalid PHY tx/rx                                                    */
    RT_ERR_PHY_ID,                                  /* 0x000e0009, invalid PHY id                                                       */
    RT_ERR_PHY_RTCT_NOT_FINISH,                     /* 0x000e000a, PHY RTCT in progress                                                 */

    /* 0x000fxxxx for mirror */
    RT_ERR_MIRROR_DIRECTION = 0x000f0000,           /* 0x000f0000, invalid error mirror direction                                       */
    RT_ERR_MIRROR_SESSION_FULL,                     /* 0x000f0001, mirroring session is full                                            */
    RT_ERR_MIRROR_SESSION_NOEXIST,                  /* 0x000f0002, mirroring session not exist                                          */
    RT_ERR_MIRROR_PORT_EXIST,                       /* 0x000f0003, mirroring port already exists                                        */
    RT_ERR_MIRROR_PORT_NOT_EXIST,                   /* 0x000f0004, mirroring port does not exists                                       */
    RT_ERR_MIRROR_PORT_FULL,                        /* 0x000f0005, Exceeds maximum number of supported mirroring port                   */

    /* 0x0010xxxx for stat */
    RT_ERR_STAT_INVALID_GLOBAL_CNTR = 0x00100000,   /* 0x00100000, Invalid Global Counter                                               */
    RT_ERR_STAT_INVALID_PORT_CNTR,                  /* 0x00100001, Invalid Port Counter                                                 */
    RT_ERR_STAT_GLOBAL_CNTR_FAIL,                   /* 0x00100002, Could not retrieve/reset Global Counter                              */
    RT_ERR_STAT_PORT_CNTR_FAIL,                     /* 0x00100003, Could not retrieve/reset Port Counter                                */
    RT_ERR_STAT_INVALID_CNTR,                       /* 0x00100004, Invalid Counter                                                      */
    RT_ERR_STAT_CNTR_FAIL,                          /* 0x00100005, Could not retrieve/reset Counter                                     */

    /* 0x0011xxxx for dot1x */
    RT_ERR_DOT1X_INVALID_DIRECTION = 0x00110000,    /* 0x00110000, Invalid Authentication Direction                                     */
    RT_ERR_DOT1X_PORTBASEDPNEN,                     /* 0x00110001, Port-based enable port error                                         */
    RT_ERR_DOT1X_PORTBASEDAUTH,                     /* 0x00110002, Port-based auth port error                                           */
    RT_ERR_DOT1X_PORTBASEDOPDIR,                    /* 0x00110003, Port-based opdir error                                               */
    RT_ERR_DOT1X_MACBASEDPNEN,                      /* 0x00110004, MAC-based enable port error                                          */
    RT_ERR_DOT1X_MACBASEDOPDIR,                     /* 0x00110005, MAC-based opdir error                                                */
    RT_ERR_DOT1X_PROC,                              /* 0x00110006, unauthorized behavior error                                          */
    RT_ERR_DOT1X_GVLANIDX,                          /* 0x00110007, guest vlan index error                                               */
    RT_ERR_DOT1X_GVLANTALK,                         /* 0x00110008, guest vlan OPDIR error                                               */
    RT_ERR_DOT1X_MAC_PORT_MISMATCH,                 /* 0x00110009, Auth MAC and port mismatch eror                                      */

    RT_ERR_END                                       /* The symbol is the latest symbol                                                  */
} rt_error_code_t;

typedef enum rtk_port_e
{
    UTP_PORT0 = 0,
    UTP_PORT1,
    UTP_PORT2,
    UTP_PORT3,
    UTP_PORT4,
    UTP_PORT5,
    UTP_PORT6,
    UTP_PORT7,

    EXT_PORT0 = 16,
    EXT_PORT1,
    EXT_PORT2,

    UNDEFINE_PORT = 30,
    RTK_PORT_MAX = 31
} rtk_port_t;

typedef struct rtk_portmask_s
{
    rtk_uint32  bits[RTK_TOTAL_NUM_OF_WORD_FOR_1BIT_PORT_LIST];
} rtk_portmask_t;

typedef struct  rtk_vlan_cfg_s
{
        rtk_portmask_t  mbr;
    rtk_portmask_t      untag;
    rtk_uint16      ivl_en;
    rtk_uint16      fid_msti;
    rtk_uint16      envlanpol;
    rtk_uint16      meteridx;
    rtk_uint16      vbpen;
    rtk_uint16      vbpri;
}rtk_vlan_cfg_t;

typedef enum rtk_port_speed_e
{
    PORT_SPEED_10M = 0,
    PORT_SPEED_100M,
    PORT_SPEED_1000M,
    PORT_SPEED_500M,
    PORT_SPEED_2500M,
    PORT_SPEED_END
} rtk_port_speed_t;

typedef enum rtk_port_linkStatus_e
{
    PORT_LINKDOWN = 0,
    PORT_LINKUP,
    PORT_LINKSTATUS_END
} rtk_port_linkStatus_t;

typedef enum rtk_enable_e
{
    DISABLED = 0,
    ENABLED,
    RTK_ENABLE_END
} rtk_enable_t;

typedef enum rtk_port_duplex_e
{
    PORT_HALF_DUPLEX = 0,
    PORT_FULL_DUPLEX,
    PORT_DUPLEX_END
} rtk_port_duplex_t;

/* enum for mac link mode */
enum LINKMODE
{
    MAC_NORMAL = 0,
    MAC_FORCE,
};

/* enum for port current link duplex mode */
enum DUPLEXMODE
{
    HALF_DUPLEX = 0,
    FULL_DUPLEX
};

typedef struct  rtk_port_mac_ability_s
{
    rtk_uint32 forcemode;
    rtk_uint32 speed;
    rtk_uint32 duplex;
    rtk_uint32 link;
    rtk_uint32 nway;
    rtk_uint32 txpause;
    rtk_uint32 rxpause;
}rtk_port_mac_ability_t;

typedef enum rtk_stat_port_type_e
{
    STAT_IfInOctets = 0,
    STAT_Dot3StatsFCSErrors,
    STAT_Dot3StatsSymbolErrors,
    STAT_Dot3InPauseFrames,
    STAT_Dot3ControlInUnknownOpcodes,
    STAT_EtherStatsFragments,
    STAT_EtherStatsJabbers,
    STAT_IfInUcastPkts,
    STAT_EtherStatsDropEvents,
    STAT_EtherStatsOctets,
    STAT_EtherStatsUnderSizePkts,
    STAT_EtherOversizeStats,
    STAT_EtherStatsPkts64Octets,
    STAT_EtherStatsPkts65to127Octets,
    STAT_EtherStatsPkts128to255Octets,
    STAT_EtherStatsPkts256to511Octets,
    STAT_EtherStatsPkts512to1023Octets,
    STAT_EtherStatsPkts1024to1518Octets,
    STAT_EtherStatsMulticastPkts,
    STAT_EtherStatsBroadcastPkts,
    STAT_IfOutOctets,
    STAT_Dot3StatsSingleCollisionFrames,
    STAT_Dot3StatsMultipleCollisionFrames,
    STAT_Dot3StatsDeferredTransmissions,
    STAT_Dot3StatsLateCollisions,
    STAT_EtherStatsCollisions,
    STAT_Dot3StatsExcessiveCollisions,
    STAT_Dot3OutPauseFrames,
    STAT_Dot1dBasePortDelayExceededDiscards,
    STAT_Dot1dTpPortInDiscards,
    STAT_IfOutUcastPkts,
    STAT_IfOutMulticastPkts,
    STAT_IfOutBroadcastPkts,
    STAT_OutOampduPkts,
    STAT_InOampduPkts,
    STAT_PktgenPkts,
    STAT_InMldChecksumError,
    STAT_InIgmpChecksumError,
    STAT_InMldSpecificQuery,
    STAT_InMldGeneralQuery,
    STAT_InIgmpSpecificQuery,
    STAT_InIgmpGeneralQuery,
    STAT_InMldLeaves,
    STAT_InIgmpInterfaceLeaves,
    STAT_InIgmpJoinsSuccess,
    STAT_InIgmpJoinsFail,
    STAT_InMldJoinsSuccess,
    STAT_InMldJoinsFail,
    STAT_InReportSuppressionDrop,
    STAT_InLeaveSuppressionDrop,
    STAT_OutIgmpReports,
    STAT_OutIgmpLeaves,
    STAT_OutIgmpGeneralQuery,
    STAT_OutIgmpSpecificQuery,
    STAT_OutMldReports,
    STAT_OutMldLeaves,
    STAT_OutMldGeneralQuery,
    STAT_OutMldSpecificQuery,
    STAT_InKnownMulticastPkts,
    STAT_IfInMulticastPkts,
    STAT_IfInBroadcastPkts,
    STAT_IfOutDiscards,
    STAT_PORT_CNTR_END
}rtk_stat_port_type_t;

typedef struct rtk_stat_port_cntr_s
{
    rtk_uint64 ifInOctets;
    rtk_uint32 dot3StatsFCSErrors;
    rtk_uint32 dot3StatsSymbolErrors;
    rtk_uint32 dot3InPauseFrames;
    rtk_uint32 dot3ControlInUnknownOpcodes;
    rtk_uint32 etherStatsFragments;
    rtk_uint32 etherStatsJabbers;
    rtk_uint32 ifInUcastPkts;
    rtk_uint32 etherStatsDropEvents;
    rtk_uint64 etherStatsOctets;
    rtk_uint32 etherStatsUndersizePkts;
    rtk_uint32 etherStatsOversizePkts;
    rtk_uint32 etherStatsPkts64Octets;
    rtk_uint32 etherStatsPkts65to127Octets;
    rtk_uint32 etherStatsPkts128to255Octets;
    rtk_uint32 etherStatsPkts256to511Octets;
    rtk_uint32 etherStatsPkts512to1023Octets;
    rtk_uint32 etherStatsPkts1024toMaxOctets;
    rtk_uint32 etherStatsMcastPkts;
    rtk_uint32 etherStatsBcastPkts;
    rtk_uint64 ifOutOctets;
    rtk_uint32 dot3StatsSingleCollisionFrames;
    rtk_uint32 dot3StatsMultipleCollisionFrames;
    rtk_uint32 dot3StatsDeferredTransmissions;
    rtk_uint32 dot3StatsLateCollisions;
    rtk_uint32 etherStatsCollisions;
    rtk_uint32 dot3StatsExcessiveCollisions;
    rtk_uint32 dot3OutPauseFrames;
    rtk_uint32 dot1dBasePortDelayExceededDiscards;
    rtk_uint32 dot1dTpPortInDiscards;
    rtk_uint32 ifOutUcastPkts;
    rtk_uint32 ifOutMulticastPkts;
    rtk_uint32 ifOutBrocastPkts;
    rtk_uint32 outOampduPkts;
    rtk_uint32 inOampduPkts;
    rtk_uint32 pktgenPkts;
    rtk_uint32 inMldChecksumError;
    rtk_uint32 inIgmpChecksumError;
    rtk_uint32 inMldSpecificQuery;
    rtk_uint32 inMldGeneralQuery;
    rtk_uint32 inIgmpSpecificQuery;
    rtk_uint32 inIgmpGeneralQuery;
    rtk_uint32 inMldLeaves;
    rtk_uint32 inIgmpLeaves;
    rtk_uint32 inIgmpJoinsSuccess;
    rtk_uint32 inIgmpJoinsFail;
    rtk_uint32 inMldJoinsSuccess;
    rtk_uint32 inMldJoinsFail;
    rtk_uint32 inReportSuppressionDrop;
    rtk_uint32 inLeaveSuppressionDrop;
    rtk_uint32 outIgmpReports;
    rtk_uint32 outIgmpLeaves;
    rtk_uint32 outIgmpGeneralQuery;
    rtk_uint32 outIgmpSpecificQuery;
    rtk_uint32 outMldReports;
    rtk_uint32 outMldLeaves;
    rtk_uint32 outMldGeneralQuery;
    rtk_uint32 outMldSpecificQuery;
    rtk_uint32 inKnownMulticastPkts;
    rtk_uint32 ifInMulticastPkts;
    rtk_uint32 ifInBroadcastPkts;
    rtk_uint32 ifOutDiscards;
}rtk_stat_port_cntr_t;

typedef enum rtk_mode_ext_e
{
    MODE_EXT_DISABLE = 0,
    MODE_EXT_RGMII,
    MODE_EXT_MII_MAC,
    MODE_EXT_MII_PHY,
    MODE_EXT_TMII_MAC,
    MODE_EXT_TMII_PHY,
    MODE_EXT_GMII,
    MODE_EXT_RMII_MAC,
    MODE_EXT_RMII_PHY,
    MODE_EXT_SGMII,
    MODE_EXT_HSGMII,
    MODE_EXT_END
} rtk_mode_ext_t;

typedef enum RTL8367C_MIBCOUNTER_E {

    /* RX */
        ifInOctets = 0,

        dot3StatsFCSErrors,
        dot3StatsSymbolErrors,
        dot3InPauseFrames,
        dot3ControlInUnknownOpcodes,

        etherStatsFragments,
        etherStatsJabbers,
        ifInUcastPkts,
        etherStatsDropEvents,

    ifInMulticastPkts,
    ifInBroadcastPkts,
    inMldChecksumError,
    inIgmpChecksumError,
    inMldSpecificQuery,
    inMldGeneralQuery,
    inIgmpSpecificQuery,
    inIgmpGeneralQuery,
    inMldLeaves,
    inIgmpLeaves,

    /* TX/RX */
        etherStatsOctets,

        etherStatsUnderSizePkts,
        etherOversizeStats,
        etherStatsPkts64Octets,
        etherStatsPkts65to127Octets,
        etherStatsPkts128to255Octets,
        etherStatsPkts256to511Octets,
        etherStatsPkts512to1023Octets,
        etherStatsPkts1024to1518Octets,

    /* TX */
        ifOutOctets,

        dot3StatsSingleCollisionFrames,
        dot3StatMultipleCollisionFrames,
        dot3sDeferredTransmissions,
        dot3StatsLateCollisions,
        etherStatsCollisions,
        dot3StatsExcessiveCollisions,
        dot3OutPauseFrames,
    ifOutDiscards,

    /* ALE */
        dot1dTpPortInDiscards,
        ifOutUcastPkts,
        ifOutMulticastPkts,
        ifOutBroadcastPkts,
        outOampduPkts,
        inOampduPkts,

    inIgmpJoinsSuccess,
    inIgmpJoinsFail,
    inMldJoinsSuccess,
    inMldJoinsFail,
    inReportSuppressionDrop,
    inLeaveSuppressionDrop,
    outIgmpReports,
    outIgmpLeaves,
    outIgmpGeneralQuery,
    outIgmpSpecificQuery,
    outMldReports,
    outMldLeaves,
    outMldGeneralQuery,
    outMldSpecificQuery,
    inKnownMulticastPkts,

        /*Device only */
        dot1dTpLearnedEntryDiscards,
        RTL8367C_MIBS_NUMBER,

}RTL8367C_MIBCOUNTER;

typedef struct  rtk_mac_s
{
    rtk_uint8 octet[ETH_ALEN];
} rtk_mac_t;

typedef struct LUTTABLE{

        ipaddr_t sip;
        ipaddr_t dip;
        rtk_mac_t mac;
        rtk_uint16 ivl_svl:1;
        rtk_uint16 cvid_fid:12;
        rtk_uint16 fid:4;
        rtk_uint16 efid:3;

        rtk_uint16 nosalearn:1;
        rtk_uint16 da_block:1;
        rtk_uint16 sa_block:1;
        rtk_uint16 auth:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 sa_en:1;
        rtk_uint16 fwd_en:1;
        rtk_uint16 mbr:11;
        rtk_uint16 spa:4;
        rtk_uint16 age:3;
        rtk_uint16 l3lookup:1;
        rtk_uint16 igmp_asic:1;
        rtk_uint16 igmpidx:8;

        rtk_uint16 lookup_hit:1;
        rtk_uint16 lookup_busy:1;
        rtk_uint16 address:13;

    rtk_uint16 l3vidlookup:1;
        rtk_uint16 l3_vid:12;

    rtk_uint16 wait_time;

}rtl8367c_luttb;

struct fdb_maclearn_st{

#ifdef _LITTLE_ENDIAN
        rtk_uint16 mac5:8;
        rtk_uint16 mac4:8;

        rtk_uint16 mac3:8;
        rtk_uint16 mac2:8;

        rtk_uint16 mac1:8;
        rtk_uint16 mac0:8;

        rtk_uint16 cvid_fid:12;
        rtk_uint16 l3lookup:1;
        rtk_uint16 ivl_svl:1;
    rtk_uint16 reserved:1;
    rtk_uint16 spa3:1;

        rtk_uint16 efid:3;
        rtk_uint16 fid:4;
        rtk_uint16 sa_en:1;
        rtk_uint16 spa:3;
        rtk_uint16 age:3;
        rtk_uint16 auth:1;
        rtk_uint16 sa_block:1;

        rtk_uint16 da_block:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 fwd_en:1;
        rtk_uint16 nosalearn:1;
    rtk_uint16 reserved2:10;
#else
        rtk_uint16 mac4:8;
        rtk_uint16 mac5:8;

        rtk_uint16 mac2:8;
        rtk_uint16 mac3:8;

        rtk_uint16 mac0:8;
        rtk_uint16 mac1:8;

    rtk_uint16 spa3:1;
    rtk_uint16 reserved:1;
        rtk_uint16 ivl_svl:1;
        rtk_uint16 l3lookup:1;
        rtk_uint16 cvid_fid:12;

        rtk_uint16 sa_block:1;
        rtk_uint16 auth:1;
        rtk_uint16 age:3;
        rtk_uint16 spa:3;
        rtk_uint16 sa_en:1;
        rtk_uint16 fid:4;
        rtk_uint16 efid:3;

    rtk_uint16 reserved2:10;
        rtk_uint16 nosalearn:1;
        rtk_uint16 fwd_en:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 da_block:1;
#endif
};

struct fdb_l2multicast_st{

#ifdef _LITTLE_ENDIAN
        rtk_uint16 mac5:8;
        rtk_uint16 mac4:8;

        rtk_uint16 mac3:8;
        rtk_uint16 mac2:8;

        rtk_uint16 mac1:8;
        rtk_uint16 mac0:8;

        rtk_uint16 cvid_fid:12;
        rtk_uint16 l3lookup:1;
        rtk_uint16 ivl_svl:1;
    rtk_uint16 mbr8:1;
    rtk_uint16 mbr9:1;

        rtk_uint16 mbr:8;
        rtk_uint16 igmpidx:8;

        rtk_uint16 igmp_asic:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 fwd_en:1;
        rtk_uint16 nosalearn:1;
        rtk_uint16 valid:1;
    rtk_uint16 mbr10:1;
    rtk_uint16 reserved2:8;
#else
        rtk_uint16 mac4:8;
        rtk_uint16 mac5:8;

        rtk_uint16 mac2:8;
        rtk_uint16 mac3:8;

        rtk_uint16 mac0:8;
        rtk_uint16 mac1:8;

    rtk_uint16 mbr9:1;
    rtk_uint16 mbr8:1;
        rtk_uint16 ivl_svl:1;
        rtk_uint16 l3lookup:1;
        rtk_uint16 cvid_fid:12;

        rtk_uint16 igmpidx:8;
        rtk_uint16 mbr:8;

    rtk_uint16 reserved2:8;
    rtk_uint16 mbr10:1;
        rtk_uint16 valid:1;
        rtk_uint16 nosalearn:1;
        rtk_uint16 fwd_en:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 igmp_asic:1;
#endif
};

struct fdb_ipmulticast_st{

#ifdef _LITTLE_ENDIAN
    rtk_uint16 sip0:8;
        rtk_uint16 sip1:8;

        rtk_uint16 sip2:8;
        rtk_uint16 sip3:8;

        rtk_uint16 dip0:8;
        rtk_uint16 dip1:8;

        rtk_uint16 dip2:8;
        rtk_uint16 dip3:4;
        rtk_uint16 l3lookup:1;
    rtk_uint16 vidlookup:1;
    rtk_uint16 mbr8:1;
    rtk_uint16 mbr9:1;

        rtk_uint16 mbr:8;
        rtk_uint16 igmpidx:8;

        rtk_uint16 igmp_asic:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 fwd_en:1;
        rtk_uint16 nosalearn:1;
        rtk_uint16 valid:1;
        rtk_uint16 mbr10:1;
    rtk_uint16 reserved2:8;
#else
        rtk_uint16 sip1:8;
    rtk_uint16 sip0:8;

        rtk_uint16 sip3:8;
        rtk_uint16 sip2:8;

        rtk_uint16 dip1:8;
        rtk_uint16 dip0:8;

    rtk_uint16 mbr9:1;
    rtk_uint16 mbr8:1;
    rtk_uint16 vidlookup:1;
        rtk_uint16 l3lookup:1;
        rtk_uint16 dip3:4;
        rtk_uint16 dip2:8;

        rtk_uint16 igmpidx:8;
        rtk_uint16 mbr:8;

    rtk_uint16 reserved2:8;
    rtk_uint16 mbr10:1;
        rtk_uint16 valid:1;
        rtk_uint16 nosalearn:1;
        rtk_uint16 fwd_en:1;
        rtk_uint16 lut_pri:3;
        rtk_uint16 igmp_asic:1;

#endif
};

struct fdb_vidipmulticast_st{

#ifdef _LITTLE_ENDIAN
    rtk_uint16 sip0:8;
        rtk_uint16 sip1:8;

        rtk_uint16 sip2:8;
        rtk_uint16 sip3:8;

        rtk_uint16 dip0:8;
        rtk_uint16 dip1:8;

        rtk_uint16 dip2:8;
        rtk_uint16 dip3:4;
        rtk_uint16 l3lookup:1;
    rtk_uint16 vidlookup:1;
    rtk_uint16 mbr8:1;
    rtk_uint16 mbr9:1;


        rtk_uint16 mbr:8;
        rtk_uint16 vid0:8;

        rtk_uint16 vid1:4;
        rtk_uint16 reserved1:1;
        rtk_uint16 nosalearn:1;
        rtk_uint16 valid:1;
        rtk_uint16 mbr10:1;
    rtk_uint16 reserved2:8;
#else
        rtk_uint16 sip1:8;
    rtk_uint16 sip0:8;

        rtk_uint16 sip3:8;
        rtk_uint16 sip2:8;

        rtk_uint16 dip1:8;
        rtk_uint16 dip0:8;

    rtk_uint16 mbr9:1;
    rtk_uint16 mbr8:1;
    rtk_uint16 vidlookup:1;
        rtk_uint16 l3lookup:1;
        rtk_uint16 dip3:4;
        rtk_uint16 dip2:8;

        rtk_uint16 vid0:8;
        rtk_uint16 mbr:8;

    rtk_uint16 reserved2:8;
    rtk_uint16 mbr10:1;
        rtk_uint16 valid:1;
        rtk_uint16 nosalearn:1;
        rtk_uint16 reserved1:1;
        rtk_uint16 vid1:4;

#endif
};

typedef union FDBSMITABLE{

        struct fdb_ipmulticast_st           smi_ipmul;
    struct fdb_vidipmulticast_st        smi_vidipmul;
        struct fdb_l2multicast_st       smi_l2mul;
        struct fdb_maclearn_st              smi_auto;

}rtl8367c_fdbtb;

/* l2 address table - unicast data structure */
typedef struct rtk_l2_ucastAddr_s
{
    rtk_mac_t       mac;
    rtk_uint32      ivl;
    rtk_uint32      cvid;
    rtk_uint32      fid;
    rtk_uint32      efid;
    rtk_uint32      port;
    rtk_uint32      sa_block;
    rtk_uint32      da_block;
    rtk_uint32      auth;
    rtk_uint32      is_static;
    rtk_uint32      priority;
    rtk_uint32      sa_pri_en;
    rtk_uint32      fwd_pri_en;
    rtk_uint32      address;
}rtk_l2_ucastAddr_t;

typedef enum rtk_led_operation_e
{
    LED_OP_SCAN=0,
    LED_OP_PARALLEL,
    LED_OP_SERIAL,
    LED_OP_END,
}rtk_led_operation_t;


typedef enum rtk_led_active_e
{
    LED_ACTIVE_HIGH=0,
    LED_ACTIVE_LOW,
    LED_ACTIVE_END,
}rtk_led_active_t;

typedef enum rtk_led_config_e
{
    LED_CONFIG_LEDOFF=0,
    LED_CONFIG_DUPCOL,
    LED_CONFIG_LINK_ACT,
    LED_CONFIG_SPD1000,
    LED_CONFIG_SPD100,
    LED_CONFIG_SPD10,
    LED_CONFIG_SPD1000ACT,
    LED_CONFIG_SPD100ACT,
    LED_CONFIG_SPD10ACT,
    LED_CONFIG_SPD10010ACT,
    LED_CONFIG_LOOPDETECT,
    LED_CONFIG_EEE,
    LED_CONFIG_LINKRX,
    LED_CONFIG_LINKTX,
    LED_CONFIG_MASTER,
    LED_CONFIG_ACT,
    LED_CONFIG_END,
}rtk_led_congig_t;

typedef struct rtk_led_ability_s
{
    rtk_enable_t link_10m;
    rtk_enable_t link_100m;
    rtk_enable_t link_500m;
    rtk_enable_t link_1000m;
    rtk_enable_t act_rx;
    rtk_enable_t act_tx;
}rtk_led_ability_t;

typedef enum rtk_led_blink_rate_e
{
    LED_BLINKRATE_32MS=0,
    LED_BLINKRATE_64MS,
    LED_BLINKRATE_128MS,
    LED_BLINKRATE_256MS,
    LED_BLINKRATE_512MS,
    LED_BLINKRATE_1024MS,
    LED_BLINKRATE_48MS,
    LED_BLINKRATE_96MS,
    LED_BLINKRATE_END,
}rtk_led_blink_rate_t;

typedef enum rtk_led_group_e
{
    LED_GROUP_0 = 0,
    LED_GROUP_1,
    LED_GROUP_2,
    LED_GROUP_END
}rtk_led_group_t;


typedef enum rtk_led_force_mode_e
{
    LED_FORCE_NORMAL=0,
    LED_FORCE_BLINK,
    LED_FORCE_OFF,
    LED_FORCE_ON,
    LED_FORCE_END
}rtk_led_force_mode_t;

typedef enum init_state_e
{
    INIT_NOT_COMPLETED = 0,
    INIT_COMPLETED,
    INIT_STATE_END
} init_state_t;

#define RTK_CHK_INIT_STATE()                                \
    do                                                      \
    {                                                       \
        if(rtk_switch_initialState_get() != INIT_COMPLETED) \
        {                                                   \
            return RT_ERR_NOT_INIT;                         \
        }                                                   \
    }while(0)

#define RTK_CHK_PORT_IS_EXT(__port__)                           \
    do                                                          \
    {                                                           \
        if(rtk_switch_isExtPort(__port__) != RT_ERR_OK)         \
        {                                                       \
            return RT_ERR_PORT_ID;                              \
        }                                                       \
    }while(0)

rtk_api_ret_t rtk_switch_init(void);

rtk_api_ret_t rtk_vlan_init(void);
rtk_api_ret_t rtk_vlan_set(rtk_vlan_t vid, rtk_vlan_cfg_t *pVlanCfg);
rtk_api_ret_t rtk_vlan_get(rtk_vlan_t vid, rtk_vlan_cfg_t *pVlanCfg);
rtk_api_ret_t rtk_vlan_portPvid_set(rtk_port_t port, rtk_vlan_t pvid, rtk_pri_t priority);

rtk_port_t rtk_switch_port_P2L_get(rtk_uint32 physicalPort);
rtk_uint32 rtk_switch_port_L2P_get(rtk_port_t logicalPort);
ret_t rtk_switch_getReg(rtk_uint32 reg, rtk_uint32 *pValue);
ret_t rtk_switch_setReg(rtk_uint32 reg, rtk_uint32 value);
ret_t rtl8367c_setAsicPHYOCPReg(rtk_uint32 phyNo, rtk_uint32 ocpAddr, rtk_uint32 ocpData);
ret_t rtl8367c_getAsicPHYOCPReg(rtk_uint32 phyNo, rtk_uint32 ocpAddr, rtk_uint32 *pRegData);
ret_t rtk_switch_setPHYReg(rtk_uint32 phyNo, rtk_uint32 phyAddr, rtk_uint32 phyData);
ret_t rtk_switch_getPHYReg(rtk_uint32 phyNo, rtk_uint32 phyAddr, rtk_uint32 *pRegData);

rtk_api_ret_t rtk_port_macStatus_get(rtk_port_t port, rtk_port_mac_ability_t *pPortstatus);
rtk_api_ret_t rtk_port_macForceLinkExt_set(rtk_port_t port, rtk_mode_ext_t mode, rtk_port_mac_ability_t *pPortability);

ret_t rtl8367c_getAsicMIBsCounter(rtk_uint32 port, RTL8367C_MIBCOUNTER mibIdx, rtk_uint64* pCounter);
rtk_api_ret_t rtk_stat_port_get(rtk_port_t port, rtk_stat_port_type_t cntr_idx, rtk_stat_counter_t *pCntr);
rtk_api_ret_t rtk_stat_port_getAll(rtk_port_t port, rtk_stat_port_cntr_t *pPort_cntrs);
rtk_api_ret_t rtk_stat_port_reset(rtk_port_t port);
void bind_static_lan_mac(rtk_uint8 *mac);
rtk_api_ret_t rtk_mirror_portIso_set(rtk_enable_t enable);
rtk_api_ret_t rtk_mirror_portBased_set(rtk_port_t mirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask);
rtk_api_ret_t rtk_mirror_portBased_get(rtk_port_t *pMirroring_port, rtk_portmask_t *pMirrored_rx_portmask, rtk_portmask_t *pMirrored_tx_portmask);
rtk_api_ret_t rtk_led_enable_set(rtk_led_group_t group, rtk_portmask_t *pPortmask);
rtk_api_ret_t rtk_led_operation_set(rtk_led_operation_t mode);
rtk_api_ret_t rtk_led_blinkRate_set(rtk_led_blink_rate_t blinkRate);
rtk_api_ret_t rtk_led_groupConfig_set(rtk_led_group_t group, rtk_led_congig_t config);
extern ret_t rtl8367c_setAsicForceLed(rtk_uint32 port, rtk_uint32 group, rtk_uint32 mode);
rtk_api_ret_t rtk_led_modeForce_set(rtk_port_t port, rtk_led_group_t group, rtk_led_force_mode_t mode);
rtk_api_ret_t rtk_port_rgmiiDelayExt_set(rtk_port_t port, rtk_data_t txDelay, rtk_data_t rxDelay);
rtk_api_ret_t rtk_port_rgmiiDelayExt_get(rtk_port_t port, rtk_data_t *pTxDelay, rtk_data_t *pRxDelay);
init_state_t rtk_switch_initialState_get(void);
rtk_api_ret_t rtk_switch_isExtPort(rtk_port_t logicalPort);

rtk_int32 smi_read(rtk_uint32 mAddrs, rtk_uint32 *rData);
rtk_int32 smi_write(rtk_uint32 mAddrs, rtk_uint32 rData);
ret_t rtl8367c_setAsicRegBit(rtk_uint32 reg, rtk_uint32 bit, rtk_uint32 value);
ret_t rtl8367c_getAsicRegBits(rtk_uint32 reg, rtk_uint32 bits, rtk_uint32 *pValue);
ret_t rtl8367c_getAsicRegBit(rtk_uint32 reg, rtk_uint32 bit, rtk_uint32 *pValue);
ret_t rtl8367c_setAsicRegBits(rtk_uint32 reg, rtk_uint32 bits, rtk_uint32 value);
ret_t rtl8367c_getAsicReg(rtk_uint32 reg, rtk_uint32 *pValue);
ret_t rtl8367c_setAsicReg(rtk_uint32 reg, rtk_uint32 value);
rtk_api_ret_t rtk_switch_logicalPortCheck(rtk_port_t logicalPort);
rtk_api_ret_t rtk_switch_logPortMask_get(rtk_portmask_t *pPortmask);

typedef rtk_uint32 rtk_svlan_index_t;

typedef struct rtk_svlan_memberCfg_s{
    rtk_uint32 svid;
    rtk_portmask_t memberport;
    rtk_portmask_t untagport;
    rtk_uint32 fiden;
    rtk_uint32 fid;
    rtk_uint32 priority;
    rtk_uint32 efiden;
    rtk_uint32 efid;
}rtk_svlan_memberCfg_t;

typedef enum rtk_svlan_pri_ref_e
{
    REF_INTERNAL_PRI = 0,
    REF_CTAG_PRI,
    REF_SVLAN_PRI,
    REF_PB_PRI,
    REF_PRI_END
} rtk_svlan_pri_ref_t;

#define RTL8367C_C2SIDXNO               128
#define RTL8367C_C2SIDXMAX              (RTL8367C_C2SIDXNO-1)
#define RTL8367C_MC2SIDXNO              32
#define RTL8367C_MC2SIDXMAX             (RTL8367C_MC2SIDXNO-1)
#define RTL8367C_SP2CIDXNO              128
#define RTL8367C_SP2CMAX        		(RTL8367C_SP2CIDXNO-1)

#define RTL8367C_SVLAN_MEMCONF_LEN      4
#define RTL8367C_SVLAN_MC2S_LEN         5
#define RTL8367C_SVLAN_SP2C_LEN         2

enum RTL8367C_SPRISEL
{
    SPRISEL_INTERNALPRI =  0,
    SPRISEL_CTAGPRI,
    SPRISEL_VSPRI,
    SPRISEL_PBPRI,
    SPRISEL_END
};

enum RTL8367C_SUNACCEPT
{
    SUNACCEPT_DROP =  0,
    SUNACCEPT_TRAP,
    SUNACCEPT_SVLAN,
    SUNACCEPT_END
};

enum RTL8367C_SVLAN_MC2S_MODE
{
    SVLAN_MC2S_MODE_MAC =  0,
    SVLAN_MC2S_MODE_IP,
    SVLAN_MC2S_MODE_END
};


typedef struct  rtl8367c_svlan_memconf_s{

    rtk_uint16 vs_member:11;
    rtk_uint16 vs_untag:11;

    rtk_uint16 vs_fid_msti:4;
    rtk_uint16 vs_priority:3;
    rtk_uint16 vs_force_fid:1;
    rtk_uint16 reserved:8;

    rtk_uint16 vs_svid:12;
    rtk_uint16 vs_efiden:1;
    rtk_uint16 vs_efid:3;


}rtl8367c_svlan_memconf_t;


typedef struct  rtl8367c_svlan_mc2s_s{

    rtk_uint16 valid:1;
    rtk_uint16 format:1;
    rtk_uint16 svidx:6;
    rtk_uint32 sdata;
    rtk_uint32 smask;
}rtl8367c_svlan_mc2s_t;


typedef struct  rtl8367c_svlan_s2c_s{

	rtk_uint16 valid:1;
    rtk_uint16 svidx:6;
    rtk_uint16 dstport:4;
    rtk_uint32 vid:12;
}rtl8367c_svlan_s2c_t;

typedef rtk_uint32 rtk_svlan_tpid_t;

typedef enum rtk_svlan_untag_action_e
{
    UNTAG_DROP = 0,
    UNTAG_TRAP,
    UNTAG_ASSIGN,
    UNTAG_END
} rtk_svlan_untag_action_t;

typedef enum rtk_svlan_unmatch_action_e
{
    UNMATCH_DROP = 0,
    UNMATCH_TRAP,
    UNMATCH_ASSIGN,
    UNMATCH_END
} rtk_svlan_unmatch_action_t;

typedef enum rtk_svlan_unassign_action_e
{
    UNASSIGN_PBSVID = 0,
    UNASSIGN_TRAP,
    UNASSIGN_END
} rtk_svlan_unassign_action_t;


typedef enum rtk_svlan_lookupType_e
{
    SVLAN_LOOKUP_S64MBRCGF  = 0,
    SVLAN_LOOKUP_C4KVLAN,
    SVLAN_LOOKUP_END,

} rtk_svlan_lookupType_t;

enum CPUTAG_INSERT_MODE
{
    CPUTAG_INSERT_TO_ALL = 0,
    CPUTAG_INSERT_TO_TRAPPING,
    CPUTAG_INSERT_TO_NO,
    CPUTAG_INSERT_END
};

#define RTL8367C_FIELDSEL_FORMAT_NUMBER      (16)
#define RTL8367C_FIELDSEL_MAX_OFFSET         (255)

enum FIELDSEL_FORMAT_FORMAT
{
    FIELDSEL_FORMAT_DEFAULT = 0,
    FIELDSEL_FORMAT_RAW,
	FIELDSEL_FORMAT_LLC,
	FIELDSEL_FORMAT_IPV4,
	FIELDSEL_FORMAT_ARP,
	FIELDSEL_FORMAT_IPV6,
	FIELDSEL_FORMAT_IPPAYLOAD,
	FIELDSEL_FORMAT_L4PAYLOAD,
    FIELDSEL_FORMAT_END
};

#define RTL8367C_ACLRULENO					96

#define RTL8367C_ACLRULEMAX					(RTL8367C_ACLRULENO-1)
#define RTL8367C_ACLRULEFIELDNO			    8
#define RTL8367C_ACLTEMPLATENO				5
#define RTL8367C_ACLTYPEMAX					(RTL8367C_ACLTEMPLATENO-1)

#define RTL8367C_ACLRULETBLEN				9
#define RTL8367C_ACLACTTBLEN				4
#define RTL8367C_ACLRULETBADDR(type, rule)	((type << 6) | rule)
#define RTL8367C_ACLRULETBADDR2(type, rule)	((type << 5) | (rule + 64))

#define ACL_ACT_CVLAN_ENABLE_MASK           0x1
#define ACL_ACT_SVLAN_ENABLE_MASK           0x2
#define ACL_ACT_PRIORITY_ENABLE_MASK    	0x4
#define ACL_ACT_POLICING_ENABLE_MASK    	0x8
#define ACL_ACT_FWD_ENABLE_MASK    			0x10
#define ACL_ACT_INTGPIO_ENABLE_MASK    		0x20

#define RTL8367C_ACLRULETAGBITS				5

#define RTL8367C_ACLRANGENO					16

#define RTL8367C_ACLRANGEMAX				(RTL8367C_ACLRANGENO-1)

#define RTL8367C_ACL_PORTRANGEMAX           (0xFFFF)
#define RTL8367C_ACL_ACT_TABLE_LEN          (4)

enum ACLTCAMTYPES
{
	CAREBITS= 0,
	DATABITS
};

typedef enum aclFwdAct
{
    RTL8367C_ACL_FWD_MIRROR = 0,
    RTL8367C_ACL_FWD_REDIRECT,
    RTL8367C_ACL_FWD_MIRRORFUNTION,
    RTL8367C_ACL_FWD_TRAP,
} rtl8367c_aclFwd_t;

enum ACLFIELDTYPES
{
	ACL_UNUSED,
	ACL_DMAC0,
	ACL_DMAC1,
	ACL_DMAC2,
	ACL_SMAC0,
	ACL_SMAC1,
	ACL_SMAC2,
	ACL_ETHERTYPE,
	ACL_STAG,
	ACL_CTAG,
	ACL_IP4SIP0 = 0x10,
	ACL_IP4SIP1,
	ACL_IP4DIP0,
	ACL_IP4DIP1,
	ACL_IP6SIP0WITHIPV4 = 0x20,
	ACL_IP6SIP1WITHIPV4,
	ACL_IP6DIP0WITHIPV4 = 0x28,
	ACL_IP6DIP1WITHIPV4,
	ACL_VIDRANGE = 0x30,
	ACL_IPRANGE,
	ACL_PORTRANGE,
	ACL_FIELD_VALID,
	ACL_FIELD_SELECT00 = 0x40,
	ACL_FIELD_SELECT01,
	ACL_FIELD_SELECT02,
	ACL_FIELD_SELECT03,
	ACL_FIELD_SELECT04,
	ACL_FIELD_SELECT05,
	ACL_FIELD_SELECT06,
	ACL_FIELD_SELECT07,
	ACL_FIELD_SELECT08,
	ACL_FIELD_SELECT09,
	ACL_FIELD_SELECT10,
	ACL_FIELD_SELECT11,
	ACL_FIELD_SELECT12,
	ACL_FIELD_SELECT13,
	ACL_FIELD_SELECT14,
	ACL_FIELD_SELECT15,
	ACL_TCPSPORT = 0x80,
	ACL_TCPDPORT,
	ACL_TCPFLAG,
	ACL_UDPSPORT,
	ACL_UDPDPORT,
	ACL_ICMPCODETYPE,
	ACL_IGMPTYPE,
	ACL_SPORT,
	ACL_DPORT,
	ACL_IP4TOSPROTO,
	ACL_IP4FLAGOFF,
	ACL_TCNH,
	ACL_CPUTAG,
	ACL_L2PAYLOAD,
	ACL_IP6SIP0,
	ACL_IP6SIP1,
	ACL_IP6SIP2,
	ACL_IP6SIP3,
	ACL_IP6SIP4,
	ACL_IP6SIP5,
	ACL_IP6SIP6,
	ACL_IP6SIP7,
	ACL_IP6DIP0,
	ACL_IP6DIP1,
	ACL_IP6DIP2,
	ACL_IP6DIP3,
	ACL_IP6DIP4,
	ACL_IP6DIP5,
	ACL_IP6DIP6,
	ACL_IP6DIP7,
	ACL_TYPE_END
};

struct acl_rule_smi_st{
    rtk_uint16 rule_info;
	rtk_uint16 field[RTL8367C_ACLRULEFIELDNO];
};

struct acl_rule_smi_ext_st{
    rtk_uint16 rule_info;
};

typedef struct ACLRULESMI{
	struct acl_rule_smi_st	care_bits;
	rtk_uint16		valid:1;
	struct acl_rule_smi_st	data_bits;

	struct acl_rule_smi_ext_st care_bits_ext;
	struct acl_rule_smi_ext_st data_bits_ext;
}rtl8367c_aclrulesmi;

struct acl_rule_st{
	rtk_uint16 active_portmsk:11;
	rtk_uint16 type:3;
	rtk_uint16 tag_exist:5;
	rtk_uint16 field[RTL8367C_ACLRULEFIELDNO];
};

typedef struct ACLRULE{
	struct acl_rule_st	data_bits;
	rtk_uint16		valid:1;
	struct acl_rule_st	care_bits;
}rtl8367c_aclrule;


typedef struct rtl8367c_acltemplate_s{
	rtk_uint8 field[8];
}rtl8367c_acltemplate_t;


typedef struct acl_act_s{
	rtk_uint16 cvidx_cact:7;
	rtk_uint16 cact:2;
	rtk_uint16 svidx_sact:7;
	rtk_uint16 sact:2;


	rtk_uint16 aclmeteridx:7;
	rtk_uint16 fwdpmask:11;
	rtk_uint16 fwdact:2;

	rtk_uint16 pridx:7;
	rtk_uint16 priact:2;
	rtk_uint16 gpio_pin:4;
	rtk_uint16 gpio_en:1;
	rtk_uint16 aclint:1;

	rtk_uint16 cact_ext:2;
	rtk_uint16 fwdact_ext:1;
	rtk_uint16 tag_fmt:2;
}rtl8367c_acl_act_t;

typedef struct acl_rule_union_s
{
    rtl8367c_aclrule aclRule;
    rtl8367c_acl_act_t aclAct;
    rtk_uint32 aclActCtrl;
    rtk_uint32 aclNot;
}rtl8367c_acl_rule_union_t;

/*
 * Data Type Declaration
 */
#define RTK_FILTER_RAW_FIELD_NUMBER                8

#define ACL_DEFAULT_ABILITY                         0
#define ACL_DEFAULT_UNMATCH_PERMIT                  1

#define ACL_RULE_FREE                               0
#define ACL_RULE_INAVAILABLE                        1
#define ACL_RULE_CARETAG_MASK						0x1F
#define FILTER_POLICING_MAX                         4
#define FILTER_LOGGING_MAX                          8
#define FILTER_PATTERN_MAX                          4

#define FILTER_ENACT_CVLAN_MASK         0x01
#define FILTER_ENACT_SVLAN_MASK         0x02
#define FILTER_ENACT_PRIORITY_MASK    	0x04
#define FILTER_ENACT_POLICING_MASK    	0x08
#define FILTER_ENACT_FWD_MASK    		0x10
#define FILTER_ENACT_INTGPIO_MASK    	0x20
#define FILTER_ENACT_INIT_MASK			0x3F

typedef enum rtk_filter_act_cactext_e
{
    FILTER_ENACT_CACTEXT_VLANONLY=0,
    FILTER_ENACT_CACTEXT_BOTHVLANTAG,
    FILTER_ENACT_CACTEXT_TAGONLY,
    FILTER_ENACT_CACTEXT_END,


}rtk_filter_act_cactext_t;

typedef enum rtk_filter_act_ctagfmt_e
{
    FILTER_CTAGFMT_UNTAG=0,
    FILTER_CTAGFMT_TAG,
    FILTER_CTAGFMT_KEEP,
    FILTER_CTAGFMT_KEEP1PRMK,


}rtk_filter_act_ctag_t;





#define RTK_MAX_NUM_OF_FILTER_TYPE                  5
#define RTK_MAX_NUM_OF_FILTER_FIELD                 8

#define RTK_DOT_1AS_TIMESTAMP_UNIT_IN_WORD_LENGTH   3UL
#define RTK_IPV6_ADDR_WORD_LENGTH                   4UL

#define FILTER_ENACT_CVLAN_TYPE(type)	(type - FILTER_ENACT_CVLAN_INGRESS)
#define FILTER_ENACT_SVLAN_TYPE(type)	(type - FILTER_ENACT_SVLAN_INGRESS)
#define FILTER_ENACT_FWD_TYPE(type)		(type - FILTER_ENACT_ADD_DSTPORT)
#define FILTER_ENACT_PRI_TYPE(type)		(type - FILTER_ENACT_PRIORITY)

#define RTK_FILTER_FIELD_USED_MAX					8
#define RTK_FILTER_FIELD_INDEX(template, index)  	((template << 4) + index)


typedef enum rtk_filter_act_enable_e
{
    /* CVLAN */
    FILTER_ENACT_CVLAN_INGRESS = 0,
    FILTER_ENACT_CVLAN_EGRESS,
    FILTER_ENACT_CVLAN_SVID,
    FILTER_ENACT_POLICING_1,

    /* SVLAN */
    FILTER_ENACT_SVLAN_INGRESS,
    FILTER_ENACT_SVLAN_EGRESS,
    FILTER_ENACT_SVLAN_CVID,
    FILTER_ENACT_POLICING_2,

    /* Policing and Logging */
    FILTER_ENACT_POLICING_0,

    /* Forward */
    FILTER_ENACT_COPY_CPU,
    FILTER_ENACT_DROP,
    FILTER_ENACT_ADD_DSTPORT,
    FILTER_ENACT_REDIRECT,
    FILTER_ENACT_MIRROR,
    FILTER_ENACT_TRAP_CPU,
    FILTER_ENACT_ISOLATION,

    /* QoS */
    FILTER_ENACT_PRIORITY,
    FILTER_ENACT_DSCP_REMARK,
    FILTER_ENACT_1P_REMARK,
    FILTER_ENACT_POLICING_3,

    /* Interrutp and GPO */
    FILTER_ENACT_INTERRUPT,
    FILTER_ENACT_GPO,

    /*VLAN tag*/
    FILTER_ENACT_EGRESSCTAG_UNTAG,
    FILTER_ENACT_EGRESSCTAG_TAG,
    FILTER_ENACT_EGRESSCTAG_KEEP,
    FILTER_ENACT_EGRESSCTAG_KEEPAND1PRMK,

    FILTER_ENACT_END,
} rtk_filter_act_enable_t;


typedef struct
{
    rtk_filter_act_enable_t actEnable[FILTER_ENACT_END];

	/* CVLAN acton */
	rtk_uint32     	filterCvlanVid;
	rtk_uint32     	filterCvlanIdx;
	/* SVLAN action */
    rtk_uint32      filterSvlanVid;
    rtk_uint32      filterSvlanIdx;

	/* Policing action */
	rtk_uint32     	filterPolicingIdx[FILTER_POLICING_MAX];

	/* Forwarding action */
	rtk_portmask_t 	filterPortmask;

	/* QOS action */
    rtk_uint32      filterPriority;

	/*GPO*/
    rtk_uint32      filterPin;

} rtk_filter_action_t;

typedef struct rtk_filter_flag_s
{
    rtk_uint32 value;
    rtk_uint32 mask;
} rtk_filter_flag_t;

typedef enum rtk_filter_care_tag_index_e
{
    CARE_TAG_CTAG = 0,
    CARE_TAG_STAG,
    CARE_TAG_PPPOE,
    CARE_TAG_IPV4,
    CARE_TAG_IPV6,
    CARE_TAG_TCP,
    CARE_TAG_UDP,
    CARE_TAG_ARP,
    CARE_TAG_RSV1,
    CARE_TAG_RSV2,
    CARE_TAG_ICMP,
    CARE_TAG_IGMP,
    CARE_TAG_LLC,
    CARE_TAG_RSV3,
    CARE_TAG_HTTP,
    CARE_TAG_RSV4,
    CARE_TAG_RSV5,
    CARE_TAG_DHCP,
    CARE_TAG_DHCPV6,
    CARE_TAG_SNMP,
    CARE_TAG_OAM,
    CARE_TAG_END,
} rtk_filter_care_tag_index_t;

typedef struct rtk_filter_care_tag_s
{
    rtk_filter_flag_t tagType[CARE_TAG_END];
} rtk_filter_care_tag_t;

typedef struct rtk_filter_field rtk_filter_field_t;

typedef struct
{
    rtk_uint32 value[RTK_DOT_1AS_TIMESTAMP_UNIT_IN_WORD_LENGTH];
} rtk_filter_dot1as_timestamp_t;

typedef enum rtk_filter_field_data_type_e
{
    FILTER_FIELD_DATA_MASK = 0,
    FILTER_FIELD_DATA_RANGE,
    FILTER_FIELD_DATA_END ,
} rtk_filter_field_data_type_t;

typedef struct rtk_filter_ip_s
{
    rtk_uint32 dataType;
    rtk_uint32 rangeStart;
    rtk_uint32 rangeEnd;
    rtk_uint32 value;
    rtk_uint32 mask;
} rtk_filter_ip_t;

typedef struct rtk_filter_mac_s
{
    rtk_uint32 dataType;
    rtk_mac_t value;
    rtk_mac_t mask;
    rtk_mac_t rangeStart;
    rtk_mac_t rangeEnd;
} rtk_filter_mac_t;

typedef rtk_uint32 rtk_filter_op_t;

typedef struct rtk_filter_value_s
{
    rtk_uint32 dataType;
    rtk_uint32 value;
    rtk_uint32 mask;
    rtk_uint32 rangeStart;
    rtk_uint32 rangeEnd;

} rtk_filter_value_t;

typedef struct rtk_filter_activeport_s
{
    rtk_portmask_t value;
    rtk_portmask_t mask;

} rtk_filter_activeport_t;



typedef struct rtk_filter_tag_s
{
    rtk_filter_value_t pri;
    rtk_filter_flag_t cfi;
    rtk_filter_value_t vid;
} rtk_filter_tag_t;

typedef struct rtk_filter_ipFlag_s
{
    rtk_filter_flag_t xf;
    rtk_filter_flag_t mf;
    rtk_filter_flag_t df;
} rtk_filter_ipFlag_t;

typedef struct
{
    rtk_uint32 addr[RTK_IPV6_ADDR_WORD_LENGTH];
} rtk_filter_ip6_addr_t;

typedef struct
{
    rtk_uint32 dataType;
    rtk_filter_ip6_addr_t value;
    rtk_filter_ip6_addr_t mask;
    rtk_filter_ip6_addr_t rangeStart;
    rtk_filter_ip6_addr_t rangeEnd;
} rtk_filter_ip6_t;

typedef rtk_uint32 rtk_filter_number_t;

typedef struct rtk_filter_pattern_s
{
    rtk_uint32 value[FILTER_PATTERN_MAX];
    rtk_uint32 mask[FILTER_PATTERN_MAX];
} rtk_filter_pattern_t;

typedef struct rtk_filter_tcpFlag_s
{
    rtk_filter_flag_t urg;
    rtk_filter_flag_t ack;
    rtk_filter_flag_t psh;
    rtk_filter_flag_t rst;
    rtk_filter_flag_t syn;
    rtk_filter_flag_t fin;
    rtk_filter_flag_t ns;
    rtk_filter_flag_t cwr;
    rtk_filter_flag_t ece;
} rtk_filter_tcpFlag_t;

typedef rtk_uint32 rtk_filter_field_raw_t;

typedef enum rtk_filter_field_temple_input_e
{
    FILTER_FIELD_TEMPLE_INPUT_TYPE = 0,
    FILTER_FIELD_TEMPLE_INPUT_INDEX,
    FILTER_FIELD_TEMPLE_INPUT_MAX ,
} rtk_filter_field_temple_input_t;

struct rtk_filter_field
{
    rtk_uint32 fieldType;

    union
    {
        /* L2 struct */
        rtk_filter_mac_t       dmac;
        rtk_filter_mac_t       smac;
        rtk_filter_value_t     etherType;
        rtk_filter_tag_t       ctag;
        rtk_filter_tag_t       relayCtag;
        rtk_filter_tag_t       stag;
        rtk_filter_tag_t       l2tag;
        rtk_filter_dot1as_timestamp_t dot1asTimeStamp;
        rtk_filter_mac_t       mac;

        /* L3 struct */
	    rtk_filter_ip_t      sip;
        rtk_filter_ip_t      dip;
        rtk_filter_ip_t      ip;
        rtk_filter_value_t   protocol;
        rtk_filter_value_t   ipTos;
        rtk_filter_ipFlag_t  ipFlag;
        rtk_filter_value_t   ipOffset;
	    rtk_filter_ip6_t     sipv6;
        rtk_filter_ip6_t     dipv6;
        rtk_filter_ip6_t     ipv6;
        rtk_filter_value_t   ipv6TrafficClass;
        rtk_filter_value_t   ipv6NextHeader;
        rtk_filter_value_t   flowLabel;

        /* L4 struct */
        rtk_filter_value_t   tcpSrcPort;
        rtk_filter_value_t   tcpDstPort;
        rtk_filter_tcpFlag_t tcpFlag;
        rtk_filter_value_t   tcpSeqNumber;
        rtk_filter_value_t   tcpAckNumber;
        rtk_filter_value_t   udpSrcPort;
        rtk_filter_value_t   udpDstPort;
        rtk_filter_value_t   icmpCode;
        rtk_filter_value_t   icmpType;
        rtk_filter_value_t   igmpType;

        /* pattern match */
        rtk_filter_pattern_t pattern;

        rtk_filter_value_t   inData;

	} filter_pattern_union;

    rtk_uint32 fieldTemplateNo;
    rtk_uint32 fieldTemplateIdx[RTK_FILTER_FIELD_USED_MAX];

    struct rtk_filter_field *next;
};

typedef enum rtk_filter_field_type_e
{
    FILTER_FIELD_DMAC = 0,
    FILTER_FIELD_SMAC,
    FILTER_FIELD_ETHERTYPE,
    FILTER_FIELD_CTAG,
    FILTER_FIELD_STAG,

    FILTER_FIELD_IPV4_SIP,
    FILTER_FIELD_IPV4_DIP,
    FILTER_FIELD_IPV4_TOS,
    FILTER_FIELD_IPV4_PROTOCOL,
    FILTER_FIELD_IPV4_FLAG,
    FILTER_FIELD_IPV4_OFFSET,
    FILTER_FIELD_IPV6_SIPV6,
    FILTER_FIELD_IPV6_DIPV6,
    FILTER_FIELD_IPV6_TRAFFIC_CLASS,
    FILTER_FIELD_IPV6_NEXT_HEADER,

    FILTER_FIELD_TCP_SPORT,
    FILTER_FIELD_TCP_DPORT,
    FILTER_FIELD_TCP_FLAG,
    FILTER_FIELD_UDP_SPORT,
    FILTER_FIELD_UDP_DPORT,
    FILTER_FIELD_ICMP_CODE,
    FILTER_FIELD_ICMP_TYPE,
    FILTER_FIELD_IGMP_TYPE,

    FILTER_FIELD_VID_RANGE,
    FILTER_FIELD_IP_RANGE,
    FILTER_FIELD_PORT_RANGE,

    FILTER_FIELD_USER_DEFINED00,
    FILTER_FIELD_USER_DEFINED01,
    FILTER_FIELD_USER_DEFINED02,
    FILTER_FIELD_USER_DEFINED03,
    FILTER_FIELD_USER_DEFINED04,
    FILTER_FIELD_USER_DEFINED05,
    FILTER_FIELD_USER_DEFINED06,
    FILTER_FIELD_USER_DEFINED07,
    FILTER_FIELD_USER_DEFINED08,
    FILTER_FIELD_USER_DEFINED09,
    FILTER_FIELD_USER_DEFINED10,
    FILTER_FIELD_USER_DEFINED11,
    FILTER_FIELD_USER_DEFINED12,
    FILTER_FIELD_USER_DEFINED13,
    FILTER_FIELD_USER_DEFINED14,
    FILTER_FIELD_USER_DEFINED15,

    FILTER_FIELD_PATTERN_MATCH,

    FILTER_FIELD_END,
} rtk_filter_field_type_t;


typedef enum rtk_filter_field_type_raw_e
{
    FILTER_FIELD_RAW_UNUSED = 0,
    FILTER_FIELD_RAW_DMAC_15_0,
    FILTER_FIELD_RAW_DMAC_31_16,
	FILTER_FIELD_RAW_DMAC_47_32,
    FILTER_FIELD_RAW_SMAC_15_0,
    FILTER_FIELD_RAW_SMAC_31_16,
    FILTER_FIELD_RAW_SMAC_47_32,
    FILTER_FIELD_RAW_ETHERTYPE,
    FILTER_FIELD_RAW_STAG,
    FILTER_FIELD_RAW_CTAG,

    FILTER_FIELD_RAW_IPV4_SIP_15_0 = 0x10,
    FILTER_FIELD_RAW_IPV4_SIP_31_16,
    FILTER_FIELD_RAW_IPV4_DIP_15_0,
    FILTER_FIELD_RAW_IPV4_DIP_31_16,


    FILTER_FIELD_RAW_IPV6_SIP_15_0 = 0x20,
    FILTER_FIELD_RAW_IPV6_SIP_31_16,
    FILTER_FIELD_RAW_IPV6_DIP_15_0 = 0x28,
    FILTER_FIELD_RAW_IPV6_DIP_31_16,

	FILTER_FIELD_RAW_VIDRANGE = 0x30,
	FILTER_FIELD_RAW_IPRANGE,
	FILTER_FIELD_RAW_PORTRANGE,
	FILTER_FIELD_RAW_FIELD_VALID,

	FILTER_FIELD_RAW_FIELD_SELECT00 = 0x40,
	FILTER_FIELD_RAW_FIELD_SELECT01,
	FILTER_FIELD_RAW_FIELD_SELECT02,
	FILTER_FIELD_RAW_FIELD_SELECT03,
	FILTER_FIELD_RAW_FIELD_SELECT04,
	FILTER_FIELD_RAW_FIELD_SELECT05,
	FILTER_FIELD_RAW_FIELD_SELECT06,
	FILTER_FIELD_RAW_FIELD_SELECT07,
	FILTER_FIELD_RAW_FIELD_SELECT08,
	FILTER_FIELD_RAW_FIELD_SELECT09,
	FILTER_FIELD_RAW_FIELD_SELECT10,
	FILTER_FIELD_RAW_FIELD_SELECT11,
	FILTER_FIELD_RAW_FIELD_SELECT12,
	FILTER_FIELD_RAW_FIELD_SELECT13,
	FILTER_FIELD_RAW_FIELD_SELECT14,
	FILTER_FIELD_RAW_FIELD_SELECT15,

    FILTER_FIELD_RAW_END,
} rtk_filter_field_type_raw_t;

typedef enum rtk_filter_flag_care_type_e
{
    FILTER_FLAG_CARE_DONT_CARE = 0,
    FILTER_FLAG_CARE_1,
    FILTER_FLAG_CARE_0,
    FILTER_FLAG_END
} rtk_filter_flag_care_type_t;

typedef rtk_uint32  rtk_filter_id_t;    /* filter id type */

typedef enum rtk_filter_invert_e
{
    FILTER_INVERT_DISABLE = 0,
    FILTER_INVERT_ENABLE,
    FILTER_INVERT_END,
} rtk_filter_invert_t;

typedef rtk_uint32 rtk_filter_state_t;

typedef rtk_uint32 rtk_filter_unmatch_action_t;

typedef enum rtk_filter_unmatch_action_e
{
    FILTER_UNMATCH_DROP = 0,
    FILTER_UNMATCH_PERMIT,
    FILTER_UNMATCH_END,
} rtk_filter_unmatch_action_type_t;

typedef struct
{
    rtk_filter_field_t      *fieldHead;
    rtk_filter_care_tag_t   careTag;
    rtk_filter_activeport_t activeport;

    rtk_filter_invert_t     invert;
} rtk_filter_cfg_t;

typedef struct
{
    rtk_filter_field_raw_t      dataFieldRaw[RTK_FILTER_RAW_FIELD_NUMBER];
    rtk_filter_field_raw_t      careFieldRaw[RTK_FILTER_RAW_FIELD_NUMBER];
	rtk_filter_field_type_raw_t fieldRawType[RTK_FILTER_RAW_FIELD_NUMBER];
    rtk_filter_care_tag_t       careTag;
    rtk_filter_activeport_t     activeport;

    rtk_filter_invert_t         invert;
	rtk_enable_t                valid;
} rtk_filter_cfg_raw_t;

typedef struct
{
    rtk_uint32 index;
    rtk_filter_field_type_raw_t fieldType[RTK_FILTER_RAW_FIELD_NUMBER];
} rtk_filter_template_t;

typedef enum rtk_field_sel_e
{
    FORMAT_DEFAULT = 0,
    FORMAT_RAW,
	FORMAT_LLC,
	FORMAT_IPV4,
	FORMAT_ARP,
	FORMAT_IPV6,
	FORMAT_IPPAYLOAD,
	FORMAT_L4PAYLOAD,
    FORMAT_END
}rtk_field_sel_t;

typedef enum rtk_filter_iprange_e
{
    IPRANGE_UNUSED = 0,
    IPRANGE_IPV4_SIP,
    IPRANGE_IPV4_DIP,
    IPRANGE_IPV6_SIP,
    IPRANGE_IPV6_DIP,
    IPRANGE_END
}rtk_filter_iprange_t;

typedef enum rtk_filter_vidrange_e
{
    VIDRANGE_UNUSED = 0,
    VIDRANGE_CVID,
    VIDRANGE_SVID,
    VIDRANGE_END
}rtk_filter_vidrange_t;

typedef enum rtk_filter_portrange_e
{
    PORTRANGE_UNUSED = 0,
    PORTRANGE_SPORT,
    PORTRANGE_DPORT,
    PORTRANGE_END
}rtk_filter_portrange_t;

#include "rtl8367c_base.h"

#define RTL8367C_SVIDXNO                    64
#define RTL8367C_SVIDXMAX                   (RTL8367C_SVIDXNO-1)

#define CONST_T     const

extern rtk_api_ret_t rtk_filter_igrAcl_init(void);
extern rtk_api_ret_t rtk_filter_igrAcl_field_add(rtk_filter_cfg_t *pFilter_cfg, rtk_filter_field_t *pFilter_field);
extern rtk_api_ret_t rtk_filter_igrAcl_cfg_add(rtk_filter_id_t filter_id, rtk_filter_cfg_t *pFilter_cfg, rtk_filter_action_t *pAction, rtk_filter_number_t *ruleNum);
extern rtk_api_ret_t rtk_filter_igrAcl_cfg_del(rtk_filter_id_t filter_id);
extern rtk_api_ret_t rtk_filter_igrAcl_cfg_delAll(void);
extern rtk_api_ret_t rtk_filter_igrAcl_cfg_get(rtk_filter_id_t filter_id, rtk_filter_cfg_raw_t *pFilter_cfg, rtk_filter_action_t *pAction);
extern rtk_api_ret_t rtk_filter_igrAcl_unmatchAction_set(rtk_port_t port, rtk_filter_unmatch_action_t action);
extern rtk_api_ret_t rtk_filter_igrAcl_unmatchAction_get(rtk_port_t port, rtk_filter_unmatch_action_t* action);
extern rtk_api_ret_t rtk_filter_igrAcl_state_set(rtk_port_t port, rtk_filter_state_t state);
extern rtk_api_ret_t rtk_filter_igrAcl_state_get(rtk_port_t port, rtk_filter_state_t* state);
extern rtk_api_ret_t rtk_filter_igrAcl_template_set(rtk_filter_template_t *aclTemplate);
extern rtk_api_ret_t rtk_filter_igrAcl_template_get(rtk_filter_template_t *aclTemplate);
extern rtk_api_ret_t rtk_filter_igrAcl_field_sel_set(rtk_uint32 index, rtk_field_sel_t format, rtk_uint32 offset);
extern rtk_api_ret_t rtk_filter_igrAcl_field_sel_get(rtk_uint32 index, rtk_field_sel_t *pFormat, rtk_uint32 *pOffset);
extern rtk_api_ret_t rtk_filter_iprange_set(rtk_uint32 index, rtk_filter_iprange_t type, ipaddr_t upperIp, ipaddr_t lowerIp);
extern rtk_api_ret_t rtk_filter_iprange_get(rtk_uint32 index, rtk_filter_iprange_t *pType, ipaddr_t *pUpperIp, ipaddr_t *pLowerIp);
extern rtk_api_ret_t rtk_filter_vidrange_set(rtk_uint32 index, rtk_filter_vidrange_t type, rtk_uint32 upperVid, rtk_uint32 lowerVid);
extern rtk_api_ret_t rtk_filter_vidrange_get(rtk_uint32 index, rtk_filter_vidrange_t *pType, rtk_uint32 *pUpperVid, rtk_uint32 *pLowerVid);
extern rtk_api_ret_t rtk_filter_portrange_set(rtk_uint32 index, rtk_filter_portrange_t type, rtk_uint32 upperPort, rtk_uint32 lowerPort);
extern rtk_api_ret_t rtk_filter_portrange_get(rtk_uint32 index, rtk_filter_portrange_t *pType, rtk_uint32 *pUpperPort, rtk_uint32 *pLowerPort);
extern rtk_api_ret_t rtk_filter_igrAclPolarity_set(rtk_uint32 polarity);
extern rtk_api_ret_t rtk_filter_igrAclPolarity_get(rtk_uint32* pPolarity);
extern rtk_api_ret_t rtk_svlan_init(void);
extern rtk_api_ret_t rtk_svlan_servicePort_add(rtk_port_t port);
extern rtk_api_ret_t rtk_svlan_servicePort_get(rtk_portmask_t *pSvlan_portmask);
extern rtk_api_ret_t rtk_svlan_servicePort_del(rtk_port_t port);
extern rtk_api_ret_t rtk_svlan_tpidEntry_set(rtk_uint32 svlan_tag_id);
extern rtk_api_ret_t rtk_svlan_tpidEntry_get(rtk_uint32 *pSvlan_tag_id);
extern rtk_api_ret_t rtk_svlan_priorityRef_set(rtk_svlan_pri_ref_t ref);
extern rtk_api_ret_t rtk_svlan_priorityRef_get(rtk_svlan_pri_ref_t *pRef);
extern rtk_api_ret_t rtk_svlan_memberPortEntry_set(rtk_uint32 svid_idx, rtk_svlan_memberCfg_t *psvlan_cfg);
extern rtk_api_ret_t rtk_svlan_memberPortEntry_get(rtk_uint32 svid_idx, rtk_svlan_memberCfg_t *pSvlan_cfg);
extern rtk_api_ret_t rtk_svlan_memberPortEntry_adv_set(rtk_uint32 idx, rtk_svlan_memberCfg_t *pSvlan_cfg);
extern rtk_api_ret_t rtk_svlan_memberPortEntry_adv_get(rtk_uint32 idx, rtk_svlan_memberCfg_t *pSvlan_cfg);
extern rtk_api_ret_t rtk_svlan_defaultSvlan_set(rtk_port_t port, rtk_vlan_t svid);
extern rtk_api_ret_t rtk_svlan_defaultSvlan_get(rtk_port_t port, rtk_vlan_t *pSvid);
extern rtk_api_ret_t rtk_svlan_c2s_add(rtk_vlan_t vid, rtk_port_t src_port, rtk_vlan_t svid);
extern rtk_api_ret_t rtk_svlan_c2s_del(rtk_vlan_t vid, rtk_port_t src_port);
extern rtk_api_ret_t rtk_svlan_c2s_get(rtk_vlan_t vid, rtk_port_t src_port, rtk_vlan_t *pSvid);
extern rtk_api_ret_t rtk_svlan_untag_action_set(rtk_svlan_untag_action_t action, rtk_vlan_t svid);
extern rtk_api_ret_t rtk_svlan_untag_action_get(rtk_svlan_untag_action_t *pAction, rtk_vlan_t *pSvid);
extern rtk_api_ret_t rtk_svlan_unmatch_action_set(rtk_svlan_unmatch_action_t action, rtk_vlan_t svid);
extern rtk_api_ret_t rtk_svlan_unmatch_action_get(rtk_svlan_unmatch_action_t *pAction, rtk_vlan_t *pSvid);
extern rtk_api_ret_t rtk_svlan_dmac_vidsel_set(rtk_port_t port, rtk_enable_t enable);
extern rtk_api_ret_t rtk_svlan_dmac_vidsel_get(rtk_port_t port, rtk_enable_t *pEnable);
extern rtk_api_ret_t rtk_svlan_ipmc2s_add(ipaddr_t ipmc, ipaddr_t ipmcMsk, rtk_vlan_t svid);
extern rtk_api_ret_t rtk_svlan_ipmc2s_del(ipaddr_t ipmc, ipaddr_t ipmcMsk);
extern rtk_api_ret_t rtk_svlan_ipmc2s_get(ipaddr_t ipmc, ipaddr_t ipmcMsk, rtk_vlan_t *pSvid);
extern rtk_api_ret_t rtk_svlan_l2mc2s_add(rtk_mac_t mac, rtk_mac_t macMsk, rtk_vlan_t svid);
extern rtk_api_ret_t rtk_svlan_l2mc2s_del(rtk_mac_t mac, rtk_mac_t macMsk);
extern rtk_api_ret_t rtk_svlan_l2mc2s_get(rtk_mac_t mac, rtk_mac_t macMsk, rtk_vlan_t *pSvid);
extern rtk_api_ret_t rtk_svlan_sp2c_add(rtk_vlan_t svid, rtk_port_t dst_port, rtk_vlan_t cvid);
extern rtk_api_ret_t rtk_svlan_sp2c_get(rtk_vlan_t svid, rtk_port_t dst_port, rtk_vlan_t *pCvid);
extern rtk_api_ret_t rtk_svlan_sp2c_del(rtk_vlan_t svid, rtk_port_t dst_port);
extern rtk_api_ret_t rtk_svlan_lookupType_set(rtk_svlan_lookupType_t type);
extern rtk_api_ret_t rtk_svlan_lookupType_get(rtk_svlan_lookupType_t *pType);
extern rtk_api_ret_t rtk_svlan_trapPri_set(rtk_pri_t priority);
extern rtk_api_ret_t rtk_svlan_trapPri_get(rtk_pri_t *pPriority);
extern rtk_api_ret_t rtk_svlan_unassign_action_set(rtk_svlan_unassign_action_t action);
extern rtk_api_ret_t rtk_svlan_unassign_action_get(rtk_svlan_unassign_action_t *pAction);
extern rtk_api_ret_t rtk_svlan_checkAndCreateMbr(rtk_vlan_t vid, rtk_uint32 *pIndex);
/*
 * Data Type Declaration
 */
#define RTK_MAX_METER_ID            (rtk_switch_maxMeterId_get())
#define RTK_METER_NUM               (RTK_MAX_METER_ID + 1)
#define RTL8367C_MAX_LOG_CNT_NUM                (32)
#define RTL8367C_DSCPMAX    				63

#define RTK_CHK_PORT_VALID(__port__)                            \
    do                                                          \
    {                                                           \
        if(rtk_switch_logicalPortCheck(__port__) != RT_ERR_OK)  \
        {                                                       \
            return RT_ERR_PORT_ID;                              \
        }                                                       \
    }while(0)
#define RTK_CHK_PORTMASK_VALID(__portmask__)                        \
    do                                                              \
    {                                                               \
        if(rtk_switch_isPortMaskValid(__portmask__) != RT_ERR_OK)   \
        {                                                           \
            return RT_ERR_PORT_MASK;                                  \
        }                                                           \
    }while(0)
#define RTK_MAX_NUM_OF_PROTO_TYPE                   0xFFFF
#define RTL8367C_EFIDMAX                    0x7
#define RTL8367C_FIDMAX                     0xF

enum {
	CMT_ACTION_FLUSH,
	CMT_ACTION_ADD_DENY,
	CMT_ACTION_ADD_ALLOW,
	CMT_ACTION_MAX
};
extern int rtk_acl_init(void);
extern int rtk_acl_cfg_start(void **handl);
extern int rtk_acl_cfg_add_snet(void *handl, unsigned int ipaddr, unsigned int ipmask);
extern int rtk_acl_cfg_add_dnet(void *handl, unsigned int ipaddr, unsigned int ipmask);
extern int rtk_acl_cfg_add_vid(void *handl, unsigned short vid);
extern int rtk_acl_cfg_add_padding(void *handl);
extern int rtk_acl_cfg_commit(void *handl, int action, int index, int port, int *outdex);
extern int rtk_acl_cfg_finish(void *handl);
#endif /* __RTL8367S_API_H__ */
