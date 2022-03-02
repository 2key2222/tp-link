/****************************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:voice
 * 
 *    Copyright (c) 2015 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 *
 ***************************************************************************/
#ifndef _APM_REGS_H
#define _APM_REGS_H

#include <dsphal_chip.h>

/*
** BCM APM Register Structure and definitions
*/
struct apm_ctrl_regs
{
  uint32      apm_dev_diag_sel_irq_status;              // (0x00) read only block interrupt status
#define   APM_DIAG_HI_SEL                 0xff000000
#define   APM_DIAG_LO_SEL                 0x00ff0000
#define   DEV_INTERRUPT                   0x00000001    // DMA interrupt pending
#define   APM_INTERRUPT_1                 0x00000002    // APM interrupt pending from bank 1
#define   APM_INTERRUPT_2                 0x00000004    // APM interrupt pending from bank 2
#define   APM_INTERRUPT_3                 0x00000008    // APM interrupt pending from bank 3
#define   PCM_INTERRUPT                   0x00000010    // PCM interrupt pending

// semantic from IUDMA perpesctive
// Tx mem to APM
// Rx APM to mem
  uint32        apm_dev_irq_pend;                       // (0x04) DMA interrupt pending register
#define   DMA_A_RX                        0x00000001    // Ch A receive channel interrupt
#define   DMA_A_TX                        0x00000002    // Ch A transmit channel interrupt
#define   DMA_B_RX                        0x00000004    // Ch B receive channel interrupt
#define   DMA_B_TX                        0x00000008    // Ch B transmit channel interrupt
#define   DMA_TX_UNDERFLOW_A              0x00000010    // Ch A transmit channel underflow
#define   DMA_TX_UNDERFLOW_B              0x00000020    // Ch B transmit channel underflow
#define   DMA_RX_OVERFLOW_A               0x00000040    // Ch A receive channel overflow
#define   DMA_RX_OVERFLOW_B               0x00000080    // Ch B receive channel overflow
#define   DMA_PCM_RX                      0x00000100    // PCM Rx DMA IRQ
#define   DMA_PCM_TX                      0x00000200    // PCM Tx DMA IRQ
#define   DEV_BMU_IRQ                     0x00000400    // BMU block IRQ

  uint32        apm_dev_irq_mask;                       // (0x08)DMA interrupt mask register

// Note semantic change
// IUDMA refers to mem to periph as Tx
// and periph to mem as Rx
// APM core refers to path from mem as Rx
// and path to mem as Tx
#if defined(CONFIG_BCM963158)
#define   CHANNEL_UNMASK_BIT              0x300        // APM Ch4 and Ch5 unmask bits
#define   SELECT_IUDMA_INTERRUPT          0x00010010   // block mask register to select iudma interrupt
  uint32        apm_block_irq_mask;
#else
  uint32        apm_dev_control;                        // (0x0c) Device control register
#endif
#define   RX_PACKET_SIZE_A                0x000000ff    // Number of samples to form quasi packet to mem channel A
#define   RX_PACKET_SIZE_B                0x0000ff00    // Number of samples to form quasi packet to mem channel B

#define   RX_DMA_ENABLE_A                 0x10000000    // Enable for Ch A DMA to mem
#define   RX_DMA_ENABLE_A_SHIFT           28

#define   RX_DMA_ENABLE_B                 0x20000000    // Enable for Ch B DMA to mem
#define   RX_DMA_ENABLE_B_SHIFT           29

#define   TX_DMA_ENABLE_A                 0x40000000    // Enable for Ch A DMA from mem
#define   TX_DMA_ENABLE_A_SHIFT           30

#define   TX_DMA_ENABLE_B                 0x80000000    // Enable for Ch B DMA from mem
#define   TX_DMA_ENABLE_B_SHIFT           31

#if defined(CONFIG_BCM96858) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878) 
  uint32        ignore[8];
  uint32        dpll_control;                           // (0x30) DPLL control register
#define   DPLL_SOFT_INIT                  0x80000000
#define   DPLL_FORCE_ACQ                  0x40000000
#define   DPLL_OPEN_LOOP                  0x20000000
#define   DPLL_CONST_K                    0x10000000
#define   DPLL_PHS_THSHLD_SHIFT           4
  uint32        dpll_nom_freq;                          // (0x34) DPLL nominal frequency (control)
  uint32        dpll_div;                               // (0x38) DPLL divide register
#define   DPLL_REF_DIV_SHIFT              16
  uint32        dpll_acq_freq;                          // (0x3c) DPLL acquired frequency
  uint32        dpll_status;                            // (0x40) DPLL status register
#define   DPLL_IN_SYNC                    0x80000000
#define   DPLL_ACQ_FREQ_VALID             0x40000000
#define   DPLL_IN_SYNC                    0x80000000
#define   DPLL_K0_SHIFT                   8

#else
// APM core registers
  uint32        reg_apm_coeff_wr_data;                  // (0x10) 20 bit 2's comp coefficient to be written into coeff RAM
#define   COEFF_PROG_INPUT                0x000FFFFF

  uint32        reg_apm_coeff_config;                   // (0x14)
#define   COEFF_PROG_ADDR                 0x000000FF    //8 bit address into coefficient RAM space
#define   COEFF_PROG_WE                   0x00000100    //1=write into memory 0= read from memory
#define   EQ_TX_ACCESS_COEFF_RAM_A        0x00010000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a equalizer
#define   EQ_RX_ACCESS_COEFF_RAM_A        0x00020000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a equalizer
#define   HISPD_HYBAL_ACCESS_COEFF_RAM_A  0x00040000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a asrc interpolator
#define   LOSPD_HYBAL_ACCESS_COEFF_RAM_A  0x00080000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a asrc interpolator
#define   YFLTR_ACCESS_COEFF_RAM_A        0x00100000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a hybrid balance
#define   ASRC_INT_ACCESS_COEFF_RAM_A     0x00200000    //1=processor intrf has control of coefficient RAM 0=normal operation channel b hybrid balance
#define   ASRC_DEC_ACCESS_COEFF_RAM_A     0x00400000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a y filter
#define   EQ_TX_ACCESS_COEFF_RAM_B        0x00800000    //1=processor intrf has control of coefficient RAM 0=normal operation channel b y filter
#define   EQ_RX_ACCESS_COEFF_RAM_B        0x01000000    //1=processor intrf has control of coefficient RAM 0=normal operation channel b y filter
#define   HISPD_HYBAL_ACCESS_COEFF_RAM_B  0x02000000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a asrc interpolator
#define   LOSPD_HYBAL_ACCESS_COEFF_RAM_B  0x04000000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a asrc interpolator
#define   YFLTR_ACCESS_COEFF_RAM_B        0x08000000    //1=processor intrf has control of coefficient RAM 0=normal operation channel b asrc interpolator
#define   ASRC_INT_ACCESS_COEFF_RAM_B     0x10000000    //1=processor intrf has control of coefficient RAM 0=normal operation channel a asrc decimator
#define   ASRC_DEC_ACCESS_COEFF_RAM_B     0x20000000    //1=processor intrf has control of coefficient RAM 0=normal operation channel b asrc decimator

#define   APM_HYBAL_NUM_TAPS            5
#define   APM_YFLTR_FIR_NUM_TAPS       18
#define   APM_YFLTR_IIR1_NUM_TAPS       1
#define   APM_YFLTR_IIR2_NUM_TAPS       5
#define   APM_YFLTR_BLOCK_SIZE         28
#define   APM_RX_EQ_NUM_TAPS           80
#define   APM_TX_EQ_NUM_TAPS           80
#define   APM_ASRC_DEC_NUM_TAPS       120
#define   APM_ASRC_INT_NUM_TAPS       120

  uint32        reg_cha_test_config;                    // (0x18)
#define   RX_IN_MUX_CTRL                  0x00000003    //2 bits mux control  at eq input 0=test stimulus 1=rx_data_in 2=loopback from tx path channel a
#define   RX_IN_MUX_CTRL_SHIFT            0

#define   NETWORK_LPBK                    0x00000004    //1=take data inputs and loopback to data outputs (network side) channel a
#define   NETWORK_LPBK_SHIFT              2

#define   RX_98K_MUX_CTRL                 0x00000018    //1=bypass 0=use eq output on rx side channel a
#define   RX_98K_MUX_CTRL_SHIFT           3

#define   ADC_MUX_CTRL                    0x00000060    //2 bits mux at input to tx path 0=loopback 1=adc out 2=test stimulus channel a
#define   ADC_MUX_CTRL_SHIFT              5

#define   ADC_DAC_LPBK                    0x00000080    //1=take 4 bit ADC codes and send them to the DEM and DAC
#define   ADC_DAC_LPBK_SHIFT              7

#define   RX_TX_98K_LPBK                  0x00000100    //1=loopback from rx to tx path channel a
#define   RX_TX_98K_LPBK_SHIFT            8

#define   SLEW_INSTANT                    0x00000200    //1=slew scale, 0=make scale changes instantaneously
#define   SLEW_INSTANT_SHIFT              9

#define   ASRC_EN                         0x00000400    //1=asrc and eq are active 0=inactive
#define   ASRC_EN_SHIFT                   10


  uint32        reg_chb_test_config;                    // (0x1c)

  uint32        reg_cha_eq_config;                      // (0x20)
#define   EQ_RX_NUM_TAPS                  0x0000007f    //7 bit number of recieve taps
#define   EQ_RX_NUM_TAPS_SHIFT            0

#define   EQ_TX_NUM_TAPS                  0x00007f00    //7 bit number of transmit taps
#define   EQ_TX_NUM_TAPS_SHIFT            8

#define   EQ_TX_SHFT                      0x000f0000    //4 bits controls output shifter (powers of 2 gain control) for rx path channel a
#define   EQ_TX_SHFT_SHIFT                16

#define   EQ_RX_SHFT                      0x00f00000    //4 bits controls output shifter (powers of 2 gain control) for tx path channel a
#define   EQ_RX_SHFT_SHIFT                20

#define   EQ_RX_IMP_RESP                  0x01000000    //1=use ext RAM for eq coefficients 0=use int ROM for eq coefficients channel a
#define   EQ_RX_IMP_RESP_SHIFT            24

#define   EQ_TX_IMP_RESP                  0x02000000    //1 the eq has an impulse shape response, 0= use the RAM or ROM for eq coefficients
#define   EQ_TX_IMP_RESP_SHIFT            25

#define   EQ_RX_ENABLE                    0x04000000    //equalizer transmit enable
#define   EQ_RX_ENABLE_SHIFT              26

#define   EQ_TX_ENABLE                    0x08000000    //equalizer receive enable
#define   EQ_TX_ENABLE_SHIFT              27

#define   SOFT_INIT                       0x80000000    //initializes state machines and registers
#define   SOFT_INIT_SHIFT                 31

  uint32        reg_cha_hybal_config;                   // (0x24)
#define   HISPD_HYBAL_SHFT                0x00000007    //
#define   HISPD_HYBAL_SHFT_SHIFT          0

#define   LOSPD_HYBAL_SHFT                0x00000038    //
#define   LOSPD_HYBAL_SHFT_SHIFT          3

#define   HISPD_HYBAL_EN                  0x00000080    //
#define   HISPD_HYBAL_EN_SHIFT            7

#define   LOSPD_HYBAL_EN                  0x00000100    //
#define   LOSPD_HYBAL_EN_SHIFT            8

#define   HISPD_HYBAL_SMPL_OFFSET         0x00007000    //
#define   HISPD_HYBAL_SMPL_OFFSET_SHIFT   12

#define   YFLTR_EN                        0x00008000    //1=y-filter is active 0=y-filter outputs 0 only
#define   YFLTR_EN_SHIFT                  15

#define   HPF_EN                          0x00010000    //1=high pass filter is active 0=high pass filter outputs 0 only
#define   HPF_EN_SHIFT                    16

#define   LOSPD_HYBAL_SMPL_OFFSET         0x3f000000    //
#define   LOSPD_HYBAL_SMPL_OFFSET_SHIFT   24

  uint32        reg_cha_int_config_1;                   // (0x28)
#define   ASRC_INT_NUM_SECT               0x001f0000    //5 bits--if symmetric it represents 1/2 of the number of sections (minus 1) in the filter channel a
#define   ASRC_INT_NUM_SECT_SHIFT         16            //  if asymmetric, it represents the number of sections (minus 1) channel a

#define   ASRC_INT_HRNR_SHFT              0x03000000    //2 bits defines shifting at output of asrc int hrnr channel a
#define   ASRC_INT_HRNR_SHFT_SHIFT        24

#define   ASRC_INT_SYM_ASYM               0x04000000    //1=filter coefficients are symmetrical (only 1/2 are stored) channel a
#define   ASRC_INT_SYM_ASYM_SHIFT         26

#define   ASRC_INT_COEFF_SEL              0x18000000    //
#define   ASRC_INT_COEFF_SEL_SHIFT        27

  uint32        reg_cha_int_config_2;                   // (0x2c)
#define   ASRC_INT_SCALE                  0x0000ffff    //16 bit scale value channel a
#define   ASRC_INT_SCALE_SHIFT            0

#define   ASRC_INT_FIR_SHFT               0x00070000    //3 bits defines shifting at output of mac before writing into data RAM channel a
#define   ASRC_INT_FIR_SHFT_SHIFT         16

#define   ASRC_SLEW_SPEED                 0x00780000    //
#define   ASRC_SLEW_SPEED_SHIFT           19

  uint32        reg_cha_pm_config_1;                    // (0x30)
#define   PM_ON_TIME                      0x00000fff    //12 bit number in 2 msec units for on-time channel a
#define   PM_ON_TIME_SHIFT                0

#define   PM_OFF_TIME                     0x0fff0000    //12 bit number in 2 msec units for off-time channel a
#define   PM_OFF_TIME_SHIFT               16

#define   PM_FREQ_16_12                   0x10000000    //1=16 kHz frequency 0=12 kHz frequency channel a
#define   PM_FREQ_16_12_SHIFT             28

#define   PM_TIME_MS                      2 / 5


  uint32        reg_cha_pm_config_2;                    // (0x34)
#define   PM_SCALE                        0x0000ffff    //16 bit 2's complement number that scales the output from full scale channel a
#define   PM_SCALE_SHIFT                  0

#define   PM_RISE_INC                     0x00ff0000    //8 bit number goes into accumulator for rise time channel a
#define   PM_RISE_INC_SHIFT               16

#define   PM_FALL_INC                     0xff000000    //8 bit number goes into accumulator for fall time channel a
#define   PM_FALL_INC_SHIFT               24

  uint32        reg_cha_pm_config_3;                    // (0x38)
#define   PM_BURST_LENGTH                 0x0000ffff    //16 bit number defines the number of bursts to send out
#define   PM_BURST_LENGTH_SHIFT           0

#define   PM_BURST_CONT                   0x00010000    //1=send out infinite number of bursts 0=send out "pm_burst_length"
#define   PM_BURST_CONT_SHIFT             16

#define   PM_BURST_START                  0x00020000    //strobe the indicates that a burst should start (this will be edge detected)
#define   PM_BURST_START_SHIFT            17

#define   PM_ENABLE                       0x00040000    //1=pulse metering is active and on, 0=inactive and off channel a
#define   PM_ENABLE_SHIFT                 18

  uint32        reg_cha_cic_config;                     // (0x3c)
#define   CIC_DEC_SHFT                    0x00000007    //3 bits controls output shifter (powers of 2 gain control) channel a
#define   CIC_DEC_SHFT_SHIFT              0

#define   CIC_INC_SHFT                    0x00000038    //3 bits controls output shifter (powers of 2 gain control) channel a
#define   CIC_INC_SHFT_SHIFT              3

#define   CIC_INC_EQ_EN                   0x00000100    //1=enable equalizer
#define   CIC_INC_EQ_EN_SHIFT             8

#define   CIC_DEC_EQ_EN                   0x00000200    //1=enable equalizer
#define   CIC_DEC_EQ_EN_SHIFT             9

  uint32        reg_cha_asrc_dec_config;                // (0x40)
#define   ASRC_DEC_SCALE                  0x0000ffff    //16 bit 2's complement scale value channel a
#define   ASRC_DEC_SCALE_SHIFT            0

#define   ASRC_DEC_NUM_SECT               0x001f0000    //5 bit number 0-20 defines the number of sections in the filter channel a
#define   ASRC_DEC_NUM_SECT_SHIFT         16            //   if symmetric it equals the number of sections/2 -1
                                                        //   if asymmetric it equals the number of sections -1
#define   ASRC_DEC_SHFT                   0x0f000000    //4 bits defines msb location at input [38:31] channel a
#define   ASRC_DEC_SHFT_SHIFT             24

#define   ASRC_DEC_SYM_ASYM               0x10000000    //1=symmetric filter 0=asymmetric filter channel a
#define   ASRC_DEC_SYM_ASYM_SHIFT         28

#define   ASRC_DEC_COEFF_SEL              0x60000000    //ASRC DEC coefficient select
#define   ASRC_DEC_COEFF_SEL_SHIFT        29

  uint32        reg_cha_fcw_config_1;                   // (0x44)
#define   FCW_SCALE                       0xffffffff    //32 bit unsigned scale value for frequency control word channel a

  uint32        reg_cha_fcw_config_2;                   // (0x48)
#define   FCW_SHFT                        0x0000000f    //4 bit shift control for fcw channel a
#define   FCW_SHFT_SHIFT                  0

#define   CLOCK_SOURCE                    0x00000030    //2 bit mux control 0=NTP 1=DPLL 2=misc for channel a
#define   CLOCK_SOURCE_SHIFT              4


  uint32        reg_cha_digmod_config;                  // (0x4c)
#define   DIGMOD_DEM_TONE                 0x00000001    //1=suppress tones at fs/2 channel a
#define   DIGMOD_DEM_TONE_SHIFT           0

#define   DIGMOD_DEM_DIS                  0x00000002    //1=use balanced code as output instead of dynamic element matcher channel a
#define   DIGMOD_DEM_DIS_SHIFT            1

#define   DIGMOD_DITH_SCALE               0x0000ff00    // new 10/1
#define   DIGMOD_DITH_SCALE_SHIFT         8


// CH B use same bit position defines as Ch A
  uint32        reg_chb_eq_config;                      // (0x50)
  uint32        reg_chb_hybal_config;                   // (0x54)
  uint32        reg_chb_int_config_1;                   // (0x58)
  uint32        reg_chb_int_config_2;                   // (0x5c)

  uint32        reg_chb_pm_config_1;                    // (0x60)
  uint32        reg_chb_pm_config_2;                    // (0x64)
  uint32        reg_chb_pm_config_3;                    // (0x68)
  uint32        reg_chb_cic_config;                     // (0x6c)
  uint32        reg_chb_asrc_dec_config;                // (0x70)
  uint32        reg_chb_fcw_config_1;                   // (0x74)
  uint32        reg_chb_fcw_config_2;                   // (0x78)
  uint32        reg_chb_digmod_config;                  // (0x7c)

  uint32        reg_fcw_config_1;                       // (0x80)
#define   FCW_REG                         0xffffffff    //32 bit frequency control word from NTP block

  uint32        reg_fcw_config_2;                       // (0x84)
#define   LOAD_NTP                        0x00000001    // triggers pulse to load FCW to NTP
#define   LOAD_NTP_SHIFT                  0

#define   LOAD_MISC_A                     0x00000002    // triggers pulse to load FCW to ch A
#define   LOAD_MISC_A_SHIFT               1

#define   LOAD_MISC_B                     0x00000004    // triggers pulse to load FCW to ch B
#define   LOAD_MISC_B_SHIFT               2

#define   LOAD_FCW_NOM_A                  0x00000008    //strobe to load nominal FCW value
#define   LOAD_FCW_NOM_A_SHIFT            3

#define   LOAD_FCW_NOM_B                  0x00000010    //strobe to load nominal FCW value
#define   LOAD_FCW_NOM_B_SHIFT            4

#define   FCW_LIMIT                       0x00000f00    //4 bits defines allowable error on FCW relative to nominal
#define   FCW_LIMIT_SHIFT                 8

  uint32        reg_ntp_config_1;                       // (0x88)
#define   NTP_TIME_DVD                    0x0000ffff    //16 bit divide value for time counter (16'd374 is default)

  uint32        reg_ntp_config_2;                       // (0x8c)
#define   NTP_READ_TIME                   0x00000001    //strobe asks for new time count value

  uint32        reg_ring_config_1;                      // (0x90)
#define   RING_START_IMMED_A              0x00000001    //1=start cadence
#define   RING_START_IMMED_A_SHIFT        0

#define   RING_START_IMMED_B              0x00000002    //1=start cadence
#define   RING_START_IMMED_B_SHIFT        1

#define   RING_START_NEXT_PHASE_A         0x00000004    //1=start cadence
#define   RING_START_NEXT_PHASE_A_SHIFT   2

#define   RING_START_NEXT_PHASE_B         0x00000008    //1=start cadence
#define   RING_START_NEXT_PHASE_B_SHIFT   3

#define   RING_STOP_IMMED_A               0x00000010    // stop ring now!
#define   RING_STOP_IMMED_A_SHIFT         4

#define   RING_STOP_IMMED_B               0x00000020    // stop ring now!
#define   RING_STOP_IMMED_B_SHIFT         5

#define   RING_STOP_NEXT_PHASE_A          0x00000040    // stop ring at next phase
#define   RING_STOP_NEXT_PHASE_A_SHIFT    6

#define   RING_STOP_NEXT_PHASE_B          0x00000080    // stop ring at next phase
#define   RING_STOP_NEXT_PHASE_B_SHIFT    7

#define   RING_OMEGA_NORM                 0x000fff00    //the omega man is Charlton Heston
#define   RING_OMEGA_NORM_SHIFT           8

#define   RING_DELAY                      0x01f00000    //ring start delay
#define   RING_DELAY_SHIFT                20

#define   RING_GEN_SOFT_INIT              0x80000000    //soft init bit
#define   RING_GEN_SOFT_INIT_SHIFT        31

  uint32        reg_ring_config_2;                      // (0x94)
  uint32        reg_ring_config_3;                      // (0x98)
#define   RING_OFFSET                     0xffff0000    //ring offset
#define   RING_OFFSET_SHIFT               16

#define   RING_SCALE                      0x0000ffff    //ring scale
#define   RING_SCALE_SHIFT                0

  uint32        reg_ring_config_4;                      // (0x9c)
#define   RING_CREST_FACTOR_A             0x00000007    //3 bit crest factor
#define   RING_CREST_FACTOR_A_SHIFT       0

#define   RING_GEN_ENABLE_A               0x00000008    //1=enabled
#define   RING_GEN_ENABLE_A_SHIFT         3

#define   RING_GEN_PHASE_A                0x00003ff0    //start/stop phase
#define   RING_GEN_PHASE_A_SHIFT          4

#define   RING_CREST_FACTOR_B             0x00070000    //3 bit crest factor
#define   RING_CREST_FACTOR_B_SHIFT       16

#define   RING_GEN_ENABLE_B               0x00080000    //1=enabled
#define   RING_GEN_ENABLE_B_SHIFT         19

#define   RING_GEN_PHASE_B                0x3ff00000    //start/stop phase
#define   RING_GEN_PHASE_B_SHIFT          20

     uint32 reg_ser_config;                         // (0xa0)
#define   SER_MUX_SEL                     0x00000003
#define   SER_MUX_SEL_SHIFT               0

//#define   SER_TST_SHFT_CTRL               0x07800000    //
#define   AUD_SER_TST_FCW_MUX_CTRL        0x08000000    //
#define   AUD_SER_TST_FCW_MUX_CTRL_SHIFT  27

//#define   SER_TST_LOAD_REGFILE            0x20000000    //1->use channel b requests for transfer 0-> use channel a
#define   SER_TST_CLKS                    0x40000000    //1=use clocks supplied by SER 0=generate internal clocks
#define   SER_TST_CLKS_SHIFT              30

#define   SOFT_INIT_AP                    0x80000000
#define   SOFT_INIT_AP_SHIFT              31

  uint32        reg_spare_unused;                       // (0xa4)
//#define   SER_TST_SCALE                   0xffffffff

  uint32        reg_stats_config;                       // (0xa8)
#define   START_STATS                     0x00008000    //[15]
#define   STATS_MUX_CTL_VADCA             0x00000800    //[11]
#define   STATS_MUX_CTL_VADCB             0x00000400    //[10]
#define   STATS_CHOP_ENABLE_A             0x00000200    //[9]
#define   STATS_CHOP_ENABLE_B             0x00000100    //[8]
#define   STATS_DURATION                  0x000000f0    //[7:4]
#define   STATS_CHOP_PERIOD               0x0000000f    //[3:0]

  // APM Status Registers
  uint32        reg_apm_status_1;                       // (0xac)
#define   DIGMOD_SAT_QUANT                0x01000000    //strobe indicating quantizer has saturated
#define   DIGMOD_SAT_COUNT_0              0x00ff0000    //8 bit counter of saturation on integrator 0 channel a
#define   DIGMOD_SAT_COUNT_1              0x0000ff00    //8 bit counter of saturation on integrator 1 channel a
#define   DIGMOD_SAT_COUNT_QUANT          0x000000ff    //8 bit counter of saturation on quantizer channel a

  uint32        reg_apm_status_2;                       // (0xb0) same as status 1 for ch B

  uint32        reg_apm_status_3;                       // (0xb4)
#define   AP_XMT_UFLOW                    0x00200000    //level indicating xnt fifo is empty when read attempted
#define   AP_XMT_OVLOW                    0x00100000    //level indicating xmt fifo is full when write attempted
#define   AP_NCO_SATURATED                0x00080000    // NCO is saturated
#define   AP_XMT_FIFO_DEPTH               0x00070000    //3 bit depth number on xmt fifo
#define   AP_RCV_UFLOW                    0x00000020    //level indicating rcv fifo is empty when read attempted
#define   AP_RCV_OVLOW                    0x00000010    //level indicating rcv fifo is full when write attempted
#define   AP_RCV_FIFO_DEPTH               0x00000007    //3 bit depth number on receive fifo

  uint32        reg_apm_status_4;                       // (0xb8)
#define   EQ_RX_COEFF                     0xffff0000    //16 bit 2's complement coefficients from RAM
#define   EQ_TX_COEFF                     0x0000ffff    //16 bit coefficient read from RAM or ROM

  uint32        reg_apm_status_5;                       // (0xbc)
#define   ASRC_INT_COEFF                  0xffff0000    //16 bit 2's comp current coefficient value
#define   ASRC_DEC_COEFF                  0x0000ffff    //16 bit coefficient from RAM or ROM

  uint32        reg_apm_status_6;                       // (0xc0)
#define   YFLTR_COEFF                     0x000fffff    //20 bit 2's complement coefficients from RAM

// Status 9-7 same as 6-4 for Ch B
  uint32        reg_apm_status_7;                       // (0xc4)
  uint32        reg_apm_status_8;                       // (0xc8)
  uint32        reg_apm_status_9;                       // (0xcc)

  uint32        reg_apm_status_10;                      // (0xd0)
#define   NTP_TIME_COUNT_INTEGER          0x0001ffff    //17 integer bits (in seconds)

  uint32        reg_apm_status_11;                      // (0xd4)
#define   NTP_TIME_COUNT_FRACT            0x0003ffff    //18 fractional bits (in seconds)

  uint32        reg_apm_status_12;                      // (0xd8)
#define   RING_CADENCE_STOPPED_A          0x00000008    //
#define   RING_ON_OFF_A                   0x00000004    //
#define   RING_CADENCE_STOPPED_B          0x00000002    //
#define   RING_ON_OFF_B                   0x00000001    //

  uint32        reg_apm_status_13;                      // (0xdc)
#define   HISPD_HYBAL_COEFF_A             0xffff0000    //
#define   HISPD_HYBAL_COEFF_B             0x0000ffff    //

  uint32        reg_apm_status_14;                      // (0xe0)
#define   LOSPD_HYBAL_COEFF_A             0xffff0000    //
#define   LOSPD_HYBAL_COEFF_B             0x0000ffff    //

  int32        reg_apm_stats_1;                        // (0xe4)
#define   MEAN                            0xffffffff    // 16 bit mean stats

  int32        reg_apm_stats_2;                        // (0xe8), same as reg_apm_stats_1 for channel B
  uint32        reg_apm_stats_3;                        // (0xec)
#define   MEAN_SQUARE_LO                  0xffffffff    // lower 32 bits of 40 bit mean square value

  uint32        reg_apm_stats_4;                        // (0xf0)
#define   MEAN_SAT                        0x00040000
#define   MEAN_SQUARE_SAT                 0x00020000
#define   STATS_BUSY                      0x00010000    // 1 bit stats busy
#define   MEAN_SQUARE_HI                  0x00003fff    // upper 14 bits of 46 bit mean square value

  uint32        reg_apm_stats_5;                        // (0xf4), same as reg_apm_stats_3 for channel B
  uint32        reg_apm_stats_6;                        // (0xf8), same as reg_apm_stats_4 for channel B

  uint32        reg_apm_audio_fcw_a;                    // (0xfc)
  uint32        reg_apm_audio_fcw_b;                    // (0x100)

  uint32        reg_apm_irq_pend_1;                     // (0x104) Ch A status
#define   PM_BURST_DONE                   0x80000000    //strobe indicating that PM burst has completed
#define   ASRC_INT_DONE_SLEWING           0x40000000    //strobe indicating that slewing has completed
#define   ASRC_DEC_DONE_SLEWING           0x20000000    //strobe indicating that slewing has completed
#define   RX_PATH_SAT                     0x10000000    //strobed high when audio + pulse meter + y-filter exceeds 16 bit number
#define   EQ_TX_SAT                       0x08000000    //strobe indicates that the result on the eq tx path was saturated
#define   EQ_RX_SAT                       0x04000000    //strobe indicates that the result on the rx path was saturated at output
#define   EQ_TX_RQST_ERR                  0x02000000    //strobe indicating a tx_rqst was asked for while a tx was pending
#define   EQ_RX_RQST_ERR                  0x01000000    //strobe indicating a rx_rqst was asked for while a rx was pending
#define   LOSPD_HYBAL_SAT                 0x00800000    //strobe indicates that the result on the tx path was saturated at output
#define   HISPD_HYBAL_SAT                 0x00400000    //strobe indicates that the result on the tx path was saturated at output
#define   HISPD_HYBAL_RQST_ERR            0x00200000    //strobe indicating a output_rqst was asked for while computation engine was busy
#define   YFLTR_IIR1_SAT                  0x00100000    //strobe indicating iir-1 is saturating
#define   YFLTR_FIR_SAT                   0x00080000    //strobe indicating fir is saturating
#define   YFLTR_IIR2_SAT                  0x00040000    //strobe indicating iir-2 is saturating
#define   YFLTR_IIR1_ACCUM_SAT            0x00020000    //strobe indicating iir1 accumulator saturated
#define   YFLTR_FIR_ACCUM_SAT             0x00010000    //strobe indicating fir accumulator saturated
#define   YFLTR_IIR2_ACCUM_SAT            0x00008000    //strobe indicating iir2 accumulator saturated
#define   YFLTR_RQST_ERR                  0x00004000    //strobe indicating a output_rqst was asked for while computation engine was busy
#define   NCO_SAT                         0x00002000    //strobe indicates scaling and shifting saturated the result
#define   ASRC_INT_HRNR_TIM_ERR           0x00001000    //strobe indicating delta has rolled over too quickly before fir has completed computation
#define   ASRC_INT_HRNR_SAT               0x00000800    //strobe indicating data has saturated at the mac output
#define   ASRC_INT_FIR_TIM_ERR            0x00000400    //strobe indicating delta has rolled over too quickly before fir has completed computation
#define   ASRC_INT_FIR_BANK_ERR           0x00000200    //strobe indicating that horner ngn asked for a bank switch while fir was busy
#define   ASRC_INT_FIR_SAT                0x00000100    //strobe indicating data has saturated at the mac output
#define   ASRC_INT_HRNR_MAC_SAT           0x00000080    //strobe indicating ser mac in hrnr block has saturated
#define   CIC_INT_SAT                     0x00000040    //strobe indicates that the result on the tx path was saturated at output
#define   DIGMOD_SAT_0                    0x00000020    //strobe indicating the integrator 0 has saturated
#define   DIGMOD_SAT_1                    0x00000010    //strobe indicating integrator 1 has saturated
#define   TX_PATH_SAT                     0x00000008
#define   CIC_DEC_SAT                     0x00000004    //strobe indicates that the result on the tx path was saturated at output
#define   ASRC_DEC_TIM_ERR                0x00000002    //strobe asserted when "input_data_ready" is asserted while ngn is busy
#define   ASRC_DEC_SAT                    0x00000001    //strobe indicating that the input was saturated

  uint32        reg_apm_irq_mask_1;                     // (0x108)

  uint32        reg_apm_irq_pend_2;                     // (0x10c) same as APM_IRQ_1 for Ch B
  uint32        reg_apm_irq_mask_2;                     // (0x110)

  uint32        reg_apm_irq_pend_3;                     // (0x114)
#define   STATS_DONE_A                    0x00000400    //strobe indicating statistics gathered and computed chA
#define   STATS_DONE_B                    0x00000200    //strobe indicating statistics gathered and computed chB
#define   FCW_OOB_A                       0x00000100    //level indicating that FCW error is too large
#define   FCW_OOB_B                       0x00000080    //level indicating that FCW error is too large
#define   HPF_SAT_A                       0x00000040    //strobe indicating high pass filter has saturated, Channel A
#define   HPF_SAT_B                       0x00000020    //strobe indicating high pass filter has saturated, Channel B
#define   ASRC_INT_DELTA_ADJ_DONE_A       0x00000010    //strobe indicating TODO
#define   ASRC_INT_DELTA_ADJ_DONE_B       0x00000008    //strobe indicating TODO
#define   LOSPD_HYBAL_RQST_ERR_A          0x00000004    //strobe indicating a output_rqst was asked for while computation engine was busy, channel A
#define   LOSPD_HYBAL_RQST_ERR_B          0x00000002    //strobe indicating a output_rqst was asked for while computation engine was busy, channel B
#define   NTP_TIME_VALID                  0x00000001    //strobe in clk_200 domain (4 clock periods)

  uint32        reg_apm_irq_mask_3;                     // (0x118)
  uint32        reg_spare_2;                            // (0x11c)

  uint32        reg_codec_config_0;                     // (0x120)
  uint32        reg_codec_config_1;                     // (0x124) VTX1
  uint32        reg_codec_config_2;                     // (0x128) same as config 16 for VTX2

  uint32        reg_codec_config_3;                     // (0x12c) VRX1
#define   PGA_CTL_VADC                    0x30000000
#define   PGA_CTL_VADC_SHIFT                      28

  uint32        reg_codec_config_4;                     // (0x130) same as config 18 for VRX2
#define   VREF_CTL_VDAC                   0x70000000
#define   PWRDN_REF_VDAC                  0x01000000
#define   PWRDN_REF_VDAC_A                0x00020000
#define   TESTEN_VDAC_A                   0x00010000
#define   DRVVOCMCTL_VDAC                 0x00007000
#define   PGA_GAIN_CTL_VDAC_A             0x00000180
#define   PGA_GAIN_CTL_VDAC_A_SHIFT                7
#define   PWRDN_REF_VDAC_B                0x00000040
#define   TESTEN_VDAC_B                   0x00000020
#define   PGA_GAIN_CTL_VDAC_B             0x00000018
#define   PGA_GAIN_CTL_VDAC_B_SHIFT                3

  uint32        reg_codec_config_5;                     // (0x134) 32Khz Ring Gen config

#if defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
  uint32        reg_otp_0;                              // (0x138) OTP read back, otp_apm[31:0]
#define   APM_OTP_TRIM                    0x00000FC0
#define   APM_OTP_TRIM_SHIFT                       6
  uint32        reg_otp_1;                              // (0x13c) OTP read back, otp_apm[63:32]
  uint32        reg_diag_readback;                      // (0x140) diag bus read back
  uint32        dpll_control;                           // (0x144) DPLL control register
#define   DPLL_SOFT_INIT                  0x80000000
#define   DPLL_FORCE_ACQ                  0x40000000
#define   DPLL_OPEN_LOOP                  0x20000000
#define   DPLL_CONST_K                    0x10000000
#define   DPLL_PHS_THSHLD_SHIFT           4
  uint32        dpll_nom_freq;                          // (0x148) DPLL nominal frequency (control)
  uint32        dpll_div;                               // (0x14c) DPLL divide register
#define   DPLL_REF_DIV_SHIFT              16
  uint32        dpll_acq_freq;                          // (0x150) DPLL acquired frequency
  uint32        dpll_status;                            // (0x154) DPLL status register
#define   DPLL_IN_SYNC                    0x80000000
#define   DPLL_ACQ_FREQ_VALID             0x40000000
#define   DPLL_IN_SYNC                    0x80000000
#define   DPLL_K0_SHIFT                   8

#else
  uint32        reg_codec_config_6;                     // (0x138) reserved
#define   DIAG_TYPE_VADC_A                0x00070000
#define   DIAG_TYPE_VADC_A_SHIFT                  16
#define   DIAG_TYPE_VADC_B                0x00000007
#define   DIAG_TYPE_VADC_B_SHIFT                   0

  uint32        reg_codec_config_7;                     // (0x13c) reserved
  uint32        reg_codec_config_8;                     // (0x140) reserved

  uint32        reg_apm_codec_fb_0;                     // (0x144) 32Khz Feedback
  uint32        reg_mbist_0_unused;                     // (0x148) MBIST control register
  uint32        reg_mbist_1_unused;                     // (0x14c) MBIST control register
  uint32        reg_otp_0;                              // (0x150) OTP read back, otp_apm[31:0]
#define   APM_OTP_TRIM                    0x00000FC0
#define   APM_OTP_TRIM_SHIFT                       6
  uint32        reg_otp_1;                              // (0x154) OTP read back, otp_apm[63:32]
  uint32        reg_diag_readback;                      // (0x158) diag bus read back
  uint32        audio_spare_2;                          // (0x15C) audio spare register 2
  uint32        dpll_control;                           // (0x160) DPLL control register
#define   DPLL_SOFT_INIT                  0x80000000
#define   DPLL_FORCE_ACQ                  0x40000000
#define   DPLL_OPEN_LOOP                  0x20000000
#define   DPLL_CONST_K                    0x10000000
#define   DPLL_PHS_THSHLD_SHIFT           4

  uint32        dpll_nom_freq;                          // (0x164) DPLL nominal frequency (control)
  uint32        dpll_div;                               // (0x168) DPLL divide register
#define   DPLL_REF_DIV_SHIFT              16
  uint32        dpll_acq_freq;                          // (0x16c) DPLL acquired frequency
  uint32        dpll_status;                            // (0x170) DPLL status register
#define   DPLL_IN_SYNC                    0x80000000
#define   DPLL_ACQ_FREQ_VALID             0x40000000
#define   DPLL_IN_SYNC                    0x80000000
#define   DPLL_K0_SHIFT                   8

#endif /* defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148) */
#endif /* defined(CONFIG_BCM96858) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878) */
};
#define APM   ((volatile struct apm_ctrl_regs * const) APM_BASE)


#endif /* _APM_REGS_H */
