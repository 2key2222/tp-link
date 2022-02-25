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
rtk_api_ret_t rtk_port_rgmiiDelayExt_set(rtk_port_t port, rtk_data_t txDelay, rtk_data_t rxDelay);
rtk_api_ret_t rtk_port_rgmiiDelayExt_get(rtk_port_t port, rtk_data_t *pTxDelay, rtk_data_t *pRxDelay);
init_state_t rtk_switch_initialState_get(void);
rtk_api_ret_t rtk_switch_isExtPort(rtk_port_t logicalPort);

#endif /* __RTL8367S_API_H__ */
