#ifndef __OCTEON_EBB6300_SHARED_H__
#define __OCTEON_EBB6300_SHARED_H__

#define WD3UE02GX818_1333L_CT_spd      \
0x92,0x10,0x0b,0x02,0x02,0x11,0x00,0x09,0x0b,0x52,0x01,0x08,0x0c,0x00,0x3c,0x00, \
0x69,0x78,0x69,0x30,0x69,0x11,0x20,0x89,0x70,0x03,0x3c,0x3c,0x00,0xf0,0x83,0x05, \
0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x11,0x04,0x01, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00,0x00,0x00,0x00,0x01,0x61,0x00,0x09,0x00,0x00,0x00,0x00,0x00,0x99,0xc0, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
0x00,0x00

#define WD3RE02GX818V_1333L_PEI_spd      \
0x92, 0x10, 0x0b, 0x01, 0x02, 0x19, 0x00, 0x09, 0x0b, 0x52, 0x01, 0x08, 0x0c, 0x00, 0x3c, 0x00, \
0x69, 0x78, 0x69, 0x30, 0x69, 0x11, 0x20, 0x89, 0x70, 0x03, 0x3c, 0x3c, 0x00, 0xf0, 0x83, 0x01, \
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x11, 0x0a, 0x05, \
0x00, 0x04, 0xb3, 0x04, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x61, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x5f, \
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
0x00, 0x00


#define USE_COMPILED_IN_SPD 0
#if USE_COMPILED_IN_SPD
#define OCTEON_EBB6300_DRAM_SOCKET_CONFIGURATION0 \
    {{0x00, 0x00}, {ebb6300_spd_values, NULL}},{{0x00, 0x0}, {NULL, NULL}}
#else
#define OCTEON_EBB6300_DRAM_SOCKET_CONFIGURATION0 \
    {{0x50, 0x0}, {NULL, NULL}},{{0x51, 0x0}, {NULL, NULL}}
#endif



#define OCTEON_EBB6300_BOARD_EEPROM_TWSI_ADDR        (0x56)
  


/*
** Local copy of these parameters to allow for customization for this
** board design.  The generic version resides in lib_octeon_shared.h.
** */

/* LMC0_MODEREG_PARAMS1 */
#define OCTEON_EBB6300_MODEREG_PARAMS1_1RANK_1SLOT      \
    { .cn63xx = { .pasr_00      = 0,                    \
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00    = 0,                    \
                  .dic_00       = 0,                    \
                  .rtt_nom_00   = rttnom_40ohm,         \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = 0,                    \
                  .dic_01       = 0,                    \
                  .rtt_nom_01   = 0,                    \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = 0,                    \
                  .dic_10       = 0,                    \
                  .rtt_nom_10   = 0,                    \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11       = 0,                    \
                  .rtt_nom_11   = 0,                    \
        }                                               \
    }

#define OCTEON_EBB6300_MODEREG_PARAMS1_1RANK_2SLOT      \
    { .cn63xx = { .pasr_00      = 0,                    \
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00    = rttwr_120ohm,         \
                  .dic_00       = 0,                    \
                  .rtt_nom_00   = rttnom_20ohm,         \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = 0,                    \
                  .dic_01       = 0,                    \
                  .rtt_nom_01   = 0,                    \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = rttwr_120ohm,         \
                  .dic_10       = 0,                    \
                  .rtt_nom_10   = rttnom_20ohm,         \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11       = 0,                    \
                  .rtt_nom_11   = 0                     \
        }                                               \
    }

#define OCTEON_EBB6300_MODEREG_PARAMS1_2RANK_1SLOT      \
    { .cn63xx = { .pasr_00      = 0,                    \
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00    = 0,                    \
                  .dic_00       = 0,                    \
                  .rtt_nom_00   = rttnom_40ohm,         \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = 0,                    \
                  .dic_01       = 0,                    \
                  .rtt_nom_01   = 0,                    \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = 0,                    \
                  .dic_10       = 0,                    \
                  .rtt_nom_10   = 0,                    \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11       = 0,                    \
                  .rtt_nom_11   = 0,                    \
        }                                               \
    }

 /* Some 2-rank dimms work better in the ebb6300 board using 20 ohms
    for rtt_nom_01/11 at 1333 DDR */
#define OCTEON_EBB6300_MODEREG_PARAMS1_2RANK_2SLOT      \
    { .cn63xx = { .pasr_00      = 0,                    \
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00    = 0,                    \
                  .dic_00       = 1,                    \
                  .rtt_nom_00   = rttnom_30ohm,         \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = 0,                    \
                  .dic_01       = 1,                    \
                  .rtt_nom_01   = rttnom_120ohm,        \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = 0,                    \
                  .dic_10       = 1,                    \
                  .rtt_nom_10   = rttnom_30ohm,         \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = 0,                    \
                  .dic_11       = 1,                    \
                  .rtt_nom_11   = rttnom_120ohm,        \
        }                                               \
    }

#define OCTEON_EBB6300_MODEREG_PARAMS1_4RANK_1SLOT      \
    { .cn63xx = { .pasr_00      = 0,                    \
                  .asr_00       = 0,                    \
                  .srt_00       = 0,                    \
                  .rtt_wr_00    = rttwr_120ohm,         \
                  .dic_00       = 0,                    \
                  .rtt_nom_00   = rttnom_40ohm,         \
                  .pasr_01      = 0,                    \
                  .asr_01       = 0,                    \
                  .srt_01       = 0,                    \
                  .rtt_wr_01    = rttwr_120ohm,         \
                  .dic_01       = 0,                    \
                  .rtt_nom_01   = rttnom_none,          \
                  .pasr_10      = 0,                    \
                  .asr_10       = 0,                    \
                  .srt_10       = 0,                    \
                  .rtt_wr_10    = rttwr_120ohm,         \
                  .dic_10       = 0,                    \
                  .rtt_nom_10   = rttnom_40ohm,         \
                  .pasr_11      = 0,                    \
                  .asr_11       = 0,                    \
                  .srt_11       = 0,                    \
                  .rtt_wr_11    = rttwr_120ohm,         \
                  .dic_11       = 0,                    \
                  .rtt_nom_11   = rttnom_none,          \
        }                                               \
    }


#define OCTEON_EBB6300_CN63XX_DRAM_ODT_1RANK_CONFIGURATION \
    /* DIMMS   reserved  WODT_MASK                LMCX_MODEREG_PARAMS1            RODT_CTL    RODT_MASK    reserved */ \
    /* =====   ======== ============== ========================================== ========= ============== ======== */ \
    /*   1 */ {   0,    0x00000001ULL, OCTEON_EBB6300_MODEREG_PARAMS1_1RANK_1SLOT,    3,     0x00000000ULL,  0  },      \
    /*   2 */ {   0,    0x00050005ULL, OCTEON_EBB6300_MODEREG_PARAMS1_1RANK_2SLOT,    3,     0x00010004ULL,  0  }

#define OCTEON_EBB6300_CN63XX_DRAM_ODT_2RANK_CONFIGURATION \
    /* DIMMS   reserved  WODT_MASK                LMCX_MODEREG_PARAMS1            RODT_CTL    RODT_MASK    reserved */ \
    /* =====   ======== ============== ========================================== ========= ============== ======== */ \
    /*   1 */ {   0,    0x00000101ULL, OCTEON_EBB6300_MODEREG_PARAMS1_2RANK_1SLOT,    3,     0x00000000ULL,    0  },    \
    /*   2 */ {   0,    0x09090606ULL, OCTEON_EBB6300_MODEREG_PARAMS1_2RANK_2SLOT,    3,     0x01010404ULL,    0  }

#define OCTEON_EBB6300_CN63XX_DRAM_ODT_4RANK_CONFIGURATION \
    /* DIMMS   reserved  WODT_MASK                LMCX_MODEREG_PARAMS1            RODT_CTL    RODT_MASK    reserved */ \
    /* =====   ======== ============== ========================================== ========= ============== ======== */ \
    /*   1 */ {   0,    0x01030203ULL, OCTEON_EBB6300_MODEREG_PARAMS1_4RANK_1SLOT,    3,     0x01010202ULL,    0  }


/* Construct a static initializer for the ddr_configuration_t variable that holds
** (almost) all of the information required for DDR initialization.
*/

/*
  The parameters below make up the custom_lmc_config data structure.
  This structure is used to customize the way that the LMC DRAM
  Controller is configured for a particular board design.

  Refer to the file lib_octeon_board_table_entry.h for a description
  of the custom board settings.  It is usually kept in the following
  location... arch/mips/include/asm/arch-octeon/

*/

#define OCTEON_EBB6300_DDR_CONFIGURATION                                \
    /* Interface 0 */                                                   \
    {                                                                   \
        .custom_lmc_config = {                                          \
            .min_rtt_nom_idx	= 2,                                    \
            .max_rtt_nom_idx	= 5,                                    \
            .min_rodt_ctl	= 1,                                    \
            .max_rodt_ctl	= 4,                                    \
            .dqx_ctl		= 4,                                    \
            .ck_ctl		= 4,                                    \
            .cmd_ctl		= 4,                                    \
            .min_cas_latency	= 7,                                    \
            .offset_en 		= 0,                                    \
            .offset_udimm	= 2,                                    \
            .offset_rdimm	= 1,                                    \
            .ddr_rtt_nom_auto	= 0,                                    \
            .ddr_rodt_ctl_auto	= 0,                                    \
            .rlevel_compute 	= 1,                                    \
            .ddr2t_udimm 	= 1,                                    \
            .ddr2t_rdimm 	= 1,                                    \
            .maximum_adjacent_rlevel_delay_increment = 2,               \
            .fprch2		= 1,                                    \
            .parity		= 0},                                   \
            .dimm_config_table = {                                      \
            OCTEON_EBB6300_DRAM_SOCKET_CONFIGURATION0,                  \
            DIMM_CONFIG_TERMINATOR},                                    \
                 .unbuffered = {                                        \
            .ddr_board_delay = 0,                                       \
            .lmc_delay_clk = 0,                                         \
            .lmc_delay_cmd = 0,                                         \
            .lmc_delay_dq = 0},                                         \
                      .registered = {                                   \
            .ddr_board_delay = 0,                                       \
            .lmc_delay_clk = 0,                                         \
            .lmc_delay_cmd = 0,                                         \
            .lmc_delay_dq = 0},                                         \
                           .odt_1rank_config = {                        \
            OCTEON_EBB6300_CN63XX_DRAM_ODT_1RANK_CONFIGURATION},        \
                                .odt_2rank_config = {                   \
            OCTEON_EBB6300_CN63XX_DRAM_ODT_2RANK_CONFIGURATION},        \
                                     .odt_4rank_config = {              \
            OCTEON_EBB6300_CN63XX_DRAM_ODT_4RANK_CONFIGURATION}         \
    }

#endif   /* __OCTEON_EBB6300_SHARED_H__ */
