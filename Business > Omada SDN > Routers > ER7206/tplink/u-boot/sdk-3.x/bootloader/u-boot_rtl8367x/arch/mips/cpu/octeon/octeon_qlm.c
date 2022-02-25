/***********************license start************************************
 * Copyright (c) 2013 Cavium, Inc. <support@cavium.com>.  All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *     * Neither the name of Cavium Inc. nor the names of
 *       its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
 * PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET
 * POSSESSION OR CORRESPONDENCE TO DESCRIPTION.  THE ENTIRE RISK ARISING OUT
 * OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 *
 *
 * For any questions regarding licensing please contact
 * marketing@cavium.com
 *
 ***********************license end**************************************/

#include <common.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/cvmx-qlm.h>
#include <asm/arch/cvmx-sata-defs.h>

DECLARE_GLOBAL_DATA_PTR;

int cvmx_qlm_is_ref_clock(int qlm, int reference_mhz)
{
    int ref_clock = cvmx_qlm_measure_clock(qlm);
    int mhz = ref_clock / 1000000;
    int range = reference_mhz / 10;
    return ((mhz >= reference_mhz - range) &&
        (mhz <= reference_mhz + range));
}

static int __get_qlm_spd(int qlm, int speed)
{
    int qlm_spd = 0xf;

    if (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN5XXX))
        return -1;

    if (cvmx_qlm_is_ref_clock(qlm, 100)) {
        if (speed == 1250)
            qlm_spd = 0x3;
        else if (speed == 2500)
            qlm_spd = 0x2;
        else if (speed == 5000)
            qlm_spd = 0x0;
        else {
            qlm_spd = 0xf;
        }
    } else if (cvmx_qlm_is_ref_clock(qlm, 125)) {
        if (speed == 1250)
            qlm_spd = 0xa;
        else if (speed == 2500)
            qlm_spd = 0x9;
        else if (speed == 3125)
            qlm_spd = 0x8;
        else if (speed == 5000)
            qlm_spd = 0x6;
        else if (speed == 6250)
            qlm_spd = 0x5;
        else {
            qlm_spd = 0xf;
        }
    } else if (cvmx_qlm_is_ref_clock(qlm, 156)) {
        if (speed == 1250)
            qlm_spd = 0x4;
        else if (speed == 2500)
            qlm_spd = 0x7;
        else if (speed == 3125)
            qlm_spd = 0xe;
        else if (speed == 3750)
            qlm_spd = 0xd;
        else if (speed == 5000)
            qlm_spd = 0xb;
        else if (speed == 6250)
            qlm_spd = 0xc;
        else {
            qlm_spd = 0xf;
        }
    }
    return qlm_spd;
}

static void __set_qlm_pcie_mode_61xx(int pcie_port, int root_complex)
{
    int rc = root_complex ? 1 : 0;
    int ep = root_complex ? 0 : 1;
    cvmx_ciu_soft_prst1_t soft_prst1;
    cvmx_ciu_soft_prst_t soft_prst;
    cvmx_mio_rst_ctlx_t rst_ctl;

    if (pcie_port) {
        soft_prst1.u64 = cvmx_read_csr(CVMX_CIU_SOFT_PRST1);
        soft_prst1.s.soft_prst = 1;
        cvmx_write_csr(CVMX_CIU_SOFT_PRST1, soft_prst1.u64);
    } else {
        soft_prst.u64 = cvmx_read_csr(CVMX_CIU_SOFT_PRST);
        soft_prst.s.soft_prst = 1;
        cvmx_write_csr(CVMX_CIU_SOFT_PRST, soft_prst.u64);
    }

    rst_ctl.u64 = cvmx_read_csr(CVMX_MIO_RST_CTLX(pcie_port));

    rst_ctl.s.prst_link = rc;
    rst_ctl.s.rst_link = ep;
    rst_ctl.s.prtmode = rc;
    rst_ctl.s.rst_drv = rc;
    rst_ctl.s.rst_rcv = 0;
    rst_ctl.s.rst_chip = ep;
    cvmx_write_csr(CVMX_MIO_RST_CTLX(pcie_port), rst_ctl.u64);

    if (root_complex == 0) {
        if (pcie_port) {
            soft_prst1.u64 = cvmx_read_csr(CVMX_CIU_SOFT_PRST1);
            soft_prst1.s.soft_prst = 0;
            cvmx_write_csr(CVMX_CIU_SOFT_PRST1, soft_prst1.u64);
        } else {
            soft_prst.u64 = cvmx_read_csr(CVMX_CIU_SOFT_PRST);
            soft_prst.s.soft_prst = 0;
            cvmx_write_csr(CVMX_CIU_SOFT_PRST, soft_prst.u64);
        }
    }
}

/**
 * Configure qlm speed and mode. MIO_QLMX_CFG[speed,mode] are not set
 * for CN61XX.
 *
 * @param qlm     The QLM to configure
 * @param speed   The speed the QLM needs to be configured in Mhz.
 * @param mode    The QLM to be configured as SGMII/XAUI/PCIe.
 *                  QLM 0: 0 = PCIe0 1X4, 1 = Reserved, 2 = SGMII1, 3 = XAUI1
 *                  QLM 1: 0 = PCIe1 1x2, 1 = PCIe(0/1) 2x1, 2 - 3 = Reserved
 *                  QLM 2: 0 - 1 = Reserved, 2 = SGMII0, 3 = XAUI0
 * @param rc      Only used for PCIe, rc = 1 for root complex mode, 0 for EP
 *        mode.
 * @param pcie2x1 Only used when QLM1 is in PCIE2x1 mode.  The QLM_SPD has a
 *        different value on how PEMx needs to be configured:
 *                   0x0 - both PEM0 & PEM1 are in gen1 mode.
 *                   0x1 - PEM0 in gen2 and PEM1 in gen1 mode.
 *                   0x2 - PEM0 in gen1 and PEM1 in gen2 mode.
 *                   0x3 - both PEM0 & PEM1 are in gen2 mode.
 *               SPEED value is ignored in this mode. QLM_SPD is set based on
 *               pcie2x1 value in this mode.
 *
 * @return       Return 0 on success or -1.
 */
static int octeon_configure_qlm_cn61xx(int qlm, int speed, int mode, int rc,
                       int pcie2x1)
{
    cvmx_mio_qlmx_cfg_t qlm_cfg;

    /* The QLM speed varies for SGMII/XAUI and PCIe mode. And depends on
     * reference clock.
     */
    if (!OCTEON_IS_MODEL(OCTEON_CN61XX))
        return -1;

    if (qlm < 3)
        qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(qlm));
    else {
        cvmx_dprintf("WARNING: Invalid QLM(%d) passed\n", qlm);
        return -1;
    }

    switch (qlm) {
        /* SGMII/XAUI mode */
    case 2:
        {
            if (mode < 2) {
                qlm_cfg.s.qlm_spd = 0xf;
                break;
            }
            qlm_cfg.s.qlm_spd = __get_qlm_spd(qlm, speed);
            qlm_cfg.s.qlm_cfg = mode;
            break;
        }
    case 1:
        {
            if (mode == 1) {    /* 2x1 mode */
                cvmx_mio_qlmx_cfg_t qlm0;

                /* When QLM0 is configured as PCIe(QLM_CFG=0x0)
                 * and enabled (QLM_SPD != 0xf), QLM1 cannot be
                 * configured as PCIe 2x1 mode (QLM_CFG=0x1)
                 * and enabled (QLM_SPD != 0xf).
                 */
                qlm0.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(0));
                if (qlm0.s.qlm_spd != 0xf && qlm0.s.qlm_cfg == 0) {
                    cvmx_dprintf("Invalid mode(%d) for QLM(%d) as QLM1 is PCIe mode\n", mode, qlm);
                    qlm_cfg.s.qlm_spd = 0xf;
                    break;
                }

                /* Set QLM_SPD based on reference clock and mode */
                if (cvmx_qlm_is_ref_clock(qlm, 100)) {
                    if (pcie2x1 == 0x3)
                        qlm_cfg.s.qlm_spd = 0x0;
                    else if (pcie2x1 == 0x1)
                        qlm_cfg.s.qlm_spd = 0x2;
                    else if (pcie2x1 == 0x2)
                        qlm_cfg.s.qlm_spd = 0x1;
                    else if (pcie2x1 == 0x0)
                        qlm_cfg.s.qlm_spd = 0x3;
                    else
                        qlm_cfg.s.qlm_spd = 0xf;
                } else if (cvmx_qlm_is_ref_clock(qlm, 125)) {
                    if (pcie2x1 == 0x3)
                        qlm_cfg.s.qlm_spd = 0x4;
                    else if (pcie2x1 == 0x1)
                        qlm_cfg.s.qlm_spd = 0x6;
                    else if (pcie2x1 == 0x2)
                        qlm_cfg.s.qlm_spd = 0x9;
                    else if (pcie2x1 == 0x0)
                        qlm_cfg.s.qlm_spd = 0x7;
                    else
                        qlm_cfg.s.qlm_spd = 0xf;
                }
                qlm_cfg.s.qlm_cfg = mode;
                cvmx_write_csr(CVMX_MIO_QLMX_CFG(qlm),
                           qlm_cfg.u64);

                /* Set PCIe mode bits */
                __set_qlm_pcie_mode_61xx(0, rc);
                __set_qlm_pcie_mode_61xx(1, rc);
                return 0;
            } else if (mode > 1) {
                cvmx_dprintf("Invalid mode(%d) for QLM(%d).\n",
                         mode, qlm);
                qlm_cfg.s.qlm_spd = 0xf;
                break;
            }

            /* Set speed and mode for PCIe 1x2 mode. */
            if (cvmx_qlm_is_ref_clock(qlm, 100)) {
                if (speed == 5000)
                    qlm_cfg.s.qlm_spd = 0x1;
                else if (speed == 2500)
                    qlm_cfg.s.qlm_spd = 0x2;
                else
                    qlm_cfg.s.qlm_spd = 0xf;
            } else if (cvmx_qlm_is_ref_clock(qlm, 125)) {
                if (speed == 5000)
                    qlm_cfg.s.qlm_spd = 0x4;
                else if (speed == 2500)
                    qlm_cfg.s.qlm_spd = 0x6;
                else
                    qlm_cfg.s.qlm_spd = 0xf;
            } else
                qlm_cfg.s.qlm_spd = 0xf;

            qlm_cfg.s.qlm_cfg = mode;
            cvmx_write_csr(CVMX_MIO_QLMX_CFG(qlm), qlm_cfg.u64);

            /* Set PCIe mode bits */
            __set_qlm_pcie_mode_61xx(1, rc);
            return 0;
        }
    case 0:
        {
            /* QLM_CFG = 0x1 - Reserved */
            if (mode == 1) {
                qlm_cfg.s.qlm_spd = 0xf;
                break;
            }
            /* QLM_CFG = 0x0 - PCIe 1x4(PEM0) */
            if (mode == 0 && speed != 5000 && speed != 2500) {
                qlm_cfg.s.qlm_spd = 0xf;
                break;
            }

            /* Set speed and mode */
            qlm_cfg.s.qlm_spd = __get_qlm_spd(qlm, speed);
            qlm_cfg.s.qlm_cfg = mode;
            cvmx_write_csr(CVMX_MIO_QLMX_CFG(qlm), qlm_cfg.u64);

            /* Set PCIe mode bits */
            if (mode == 0)
                __set_qlm_pcie_mode_61xx(0, rc);

            return 0;
        }
    default:
        cvmx_dprintf("WARNING: Invalid QLM(%d) passed\n", qlm);
        qlm_cfg.s.qlm_spd = 0xf;
    }
    cvmx_write_csr(CVMX_MIO_QLMX_CFG(qlm), qlm_cfg.u64);
    return 0;
}

/* qlm      : DLM to configure
 * baud_mhz : speed of the DLM
 * ref_clk_sel  :  reference clock selection
 * ref_clk_input:  reference clock input
 * is_sff7000_rxaui : boolean to indicate whether qlm is RXAUI on SFF7000
 */
static int __dlm_setup_pll_cn70xx(int qlm, int baud_mhz, int ref_clk_sel,
                  int ref_clk_input, int is_sff7000_rxaui)
{
    cvmx_gserx_dlmx_test_powerdown_t dlmx_test_powerdown;
    cvmx_gserx_dlmx_ref_ssp_en_t dlmx_ref_ssp_en;
    cvmx_gserx_dlmx_mpll_en_t dlmx_mpll_en;
    cvmx_gserx_dlmx_phy_reset_t dlmx_phy_reset;
    cvmx_gserx_dlmx_tx_amplitude_t tx_amplitude;
    cvmx_gserx_dlmx_tx_amplitude_t tx_amplitude_old;
    cvmx_gserx_dlmx_tx_preemph_t tx_preemph;
    cvmx_gserx_dlmx_rx_eq_t rx_eq;
    cvmx_gserx_dlmx_ref_clkdiv2_t ref_clkdiv2;
    cvmx_gserx_dlmx_mpll_multiplier_t mpll_multiplier;
    int gmx_ref_clk = 100;

#if 0
    if (ref_clk_input == 1)
        gmx_ref_clk = 156;
    else if (ref_clk_sel == 1)
        gmx_ref_clk = 125;
#endif

    /* Hardware defaults are invalid */
    tx_amplitude.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_AMPLITUDE(qlm, 0));
    if (is_sff7000_rxaui) {
        tx_amplitude.s.tx0_amplitude = 100;
        tx_amplitude.s.tx1_amplitude = 100;
    }
    else {
    tx_amplitude.s.tx0_amplitude = 65;
    tx_amplitude.s.tx1_amplitude = 65;
    }

    tx_amplitude_old.u64 = tx_amplitude.u64;

    tx_amplitude.s.tx0_amplitude = 127;
    tx_amplitude.s.tx1_amplitude = 65;

    printf("CVMX_GSERX_DLMX_TX_AMPLITUDE ER7520G %016x (SDK %016x)\n", tx_amplitude.u64, tx_amplitude_old.u64);

    cvmx_write_csr(CVMX_GSERX_DLMX_TX_AMPLITUDE(qlm, 0), tx_amplitude.u64);

    tx_preemph.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_PREEMPH(qlm, 0));

    if (is_sff7000_rxaui) {
        tx_preemph.s.tx0_preemph = 0;
        tx_preemph.s.tx1_preemph = 0;
    }
    else {
    tx_preemph.s.tx0_preemph = 22;
    tx_preemph.s.tx1_preemph = 22;
    }
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_PREEMPH(qlm, 0), tx_preemph.u64);

    rx_eq.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_RX_EQ(qlm, 0));
    rx_eq.s.rx0_eq = 0;
    rx_eq.s.rx1_eq = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_RX_EQ(qlm, 0), rx_eq.u64);

    /* 1. Write GSER0_DLM0_REF_USE_PAD[REF_USE_PAD] = 1 (to select
     *    reference-clock input)
     */
    cvmx_write_csr(CVMX_GSERX_DLMX_REF_USE_PAD(0, 0), ref_clk_input);

    /* Reference clock was already chosen before we got here */

    /* 2. Write GSER0_DLM0_REFCLK_SEL[REFCLK_SEL] if required for
     *    reference-clock selection.
     */
    cvmx_write_csr(CVMX_GSERX_DLMX_REFCLK_SEL(0, 0), ref_clk_sel);

    /* Reference clock was already chosen before we got here */

    /* 3. If required, write GSER0_DLM0_REF_CLKDIV2[REF_CLKDIV2] (must be
     *    set if reference clock > 100 MHz)
     */
    /* Apply workaround for Errata (G-20669) MPLL may not come up. */
    ref_clkdiv2.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_REF_CLKDIV2(qlm, 0));
    if (gmx_ref_clk == 100)
        ref_clkdiv2.s.ref_clkdiv2 = 0;
    else
        ref_clkdiv2.s.ref_clkdiv2 = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_REF_CLKDIV2(qlm, 0), ref_clkdiv2.u64);

    /* 1. Ensure GSER(0)_DLM(0..2)_PHY_RESET[PHY_RESET] is set. */
    dlmx_phy_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0));
    dlmx_phy_reset.s.phy_reset = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0), dlmx_phy_reset.u64);

    /* 2. If SGMII or QSGMII or RXAUI (i.e. if DLM0) set
          GSER(0)_DLM(0)_MPLL_EN[MPLL_EN] to one. */
    /* 7. Set GSER0_DLM0_MPLL_EN[MPLL_EN] = 1 */
    dlmx_mpll_en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_MPLL_EN(0, 0));
    dlmx_mpll_en.s.mpll_en = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_MPLL_EN(0, 0), dlmx_mpll_en.u64);

    /* 3. Set GSER(0)_DLM(0..2)_MPLL_MULTIPLIER[MPLL_MULTIPLIER]
          to the value in the preceding table, which is different
          than the desired setting prescribed by the HRM. */
    mpll_multiplier.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0));
    if (gmx_ref_clk == 100)
        mpll_multiplier.s.mpll_multiplier = 35;
    else if (gmx_ref_clk == 125)
        mpll_multiplier.s.mpll_multiplier = 56;
    else
        mpll_multiplier.s.mpll_multiplier = 45;
    cvmx_write_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0), mpll_multiplier.u64);

    /* 5. Clear GSER0_DLM0_TEST_POWERDOWN[TEST_POWERDOWN] */
    dlmx_test_powerdown.u64 =
            cvmx_read_csr(CVMX_GSERX_DLMX_TEST_POWERDOWN(qlm, 0));
    dlmx_test_powerdown.s.test_powerdown = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_TEST_POWERDOWN(qlm, 0),
               dlmx_test_powerdown.u64);

    /* 6. Set GSER0_DLM0_REF_SSP_EN[REF_SSP_EN] = 1 */
    dlmx_ref_ssp_en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_REF_SSP_EN(qlm, 0));
    dlmx_ref_ssp_en.s.ref_ssp_en = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_REF_SSP_EN(0, 0), dlmx_ref_ssp_en.u64);

    /* 8. Clear GSER0_DLM0_PHY_RESET[PHY_RESET] = 0 */
    dlmx_phy_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0));
    dlmx_phy_reset.s.phy_reset = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0), dlmx_phy_reset.u64);

    /* 5. If PCIe or SATA (i.e. if DLM1 or DLM2), set both MPLL_EN
       and MPLL_EN_OVRD to one in GSER(0)_PHY(1..2)_OVRD_IN_LO. */

    /* 6. Decrease MPLL_MULTIPLIER by one continually until it reaches
         the desired long-term setting, ensuring that each MPLL_MULTIPLIER
         value is constant for at least 1 msec before changing to the next
         value. The desired long-term setting is as indicated in HRM tables
         21-1, 21-2, and 21-3. This is not required with the HRM
         sequence. */
    mpll_multiplier.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0));
    __cvmx_qlm_set_mult(qlm, baud_mhz, mpll_multiplier.s.mpll_multiplier);

    /* 9. Poll until the MPLL locks. Wait for
     *    GSER0_DLM0_MPLL_STATUS[MPLL_STATUS] = 1
     */
    if ((gd->arch.board_desc.board_type != CVMX_BOARD_TYPE_SIM)
         && CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_MPLL_STATUS(qlm, 0),
                      cvmx_gserx_dlmx_mpll_status_t,
                      mpll_status, ==, 1, 10000)) {
        cvmx_warn("PLL for DLM%d failed to lock\n", qlm);
        return -1;
    }
    return 0;
}

static int __dlm0_setup_tx_cn70xx(void)
{
    int need0, need1;
    cvmx_gmxx_inf_mode_t mode0, mode1;
    cvmx_gserx_dlmx_tx_rate_t rate;
    cvmx_gserx_dlmx_tx_en_t en;
    cvmx_gserx_dlmx_tx_cm_en_t cm_en;
    cvmx_gserx_dlmx_tx_data_en_t data_en;
    cvmx_gserx_dlmx_tx_reset_t tx_reset;

    mode0.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(0));
    mode1.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(1));

    /* Which lanes do we need? */
    need0 = (mode0.s.mode != CVMX_GMX_INF_MODE_DISABLED);
    need1 = (mode1.s.mode != CVMX_GMX_INF_MODE_DISABLED)
         || (mode0.s.mode == CVMX_GMX_INF_MODE_RXAUI);

    /* 1. Write GSER0_DLM0_TX_RATE[TXn_RATE] (Set according to required
          data rate (see Table 21-1). */
    rate.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_RATE(0, 0));
    rate.s.tx0_rate = (mode0.s.mode == CVMX_GMX_INF_MODE_SGMII) ? 2 : 0;
    rate.s.tx1_rate = (mode1.s.mode == CVMX_GMX_INF_MODE_SGMII) ? 2 : 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_RATE(0, 0), rate.u64);

    /* 2. Set GSER0_DLM0_TX_EN[TXn_EN] = 1 */
    en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_EN(0, 0));
    en.s.tx0_en = need0;
    en.s.tx1_en = need1;
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_EN(0, 0), en.u64);

    /* 3 set GSER0_DLM0_TX_CM_EN[TXn_CM_EN] = 1 */
    cm_en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_CM_EN(0, 0));
    cm_en.s.tx0_cm_en = need0;
    cm_en.s.tx1_cm_en = need1;
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_CM_EN(0, 0), cm_en.u64);

    /* 4. Set GSER0_DLM0_TX_DATA_EN[TXn_DATA_EN] = 1 */
    data_en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_DATA_EN(0, 0));
    data_en.s.tx0_data_en = need0;
    data_en.s.tx1_data_en = need1;
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_DATA_EN(0, 0), data_en.u64);

    /* 5. Clear GSER0_DLM0_TX_RESET[TXn_DATA_EN] = 0 */
#if 0
    tx_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_TX_RESET(0, 0));
    tx_reset.s.tx0_reset = !need0;
    tx_reset.s.tx1_reset = !need1;
    printf("CVMX_GSERX_DLMX_TX_RESET SDK %016x\n", tx_reset.u64);
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_RESET(0, 0), tx_reset.u64);
#else
    tx_reset.s.tx0_reset = 1;
    tx_reset.s.tx1_reset = 1;
    printf("CVMX_GSERX_DLMX_TX_RESET ER7520G %016x\n", tx_reset.u64);
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_RESET(0, 0), tx_reset.u64);

    cvmx_wait(1000);

    tx_reset.s.tx0_reset = 0;
    tx_reset.s.tx1_reset = 0;
    printf("CVMX_GSERX_DLMX_TX_RESET ER7520G %016x\n", tx_reset.u64);
    cvmx_write_csr(CVMX_GSERX_DLMX_TX_RESET(0, 0), tx_reset.u64);


#endif


    

    /* 6. Poll GSER0_DLM0_TX_STATUS[TXn_STATUS, TXn_CM_STATUS] until both
     *    are set to 1. This prevents GMX from transmitting until the DLM
     *    is ready.
     */
    if ((gd->arch.board_desc.board_type != CVMX_BOARD_TYPE_SIM) && need0) {
        if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_TX_STATUS(0, 0),
            cvmx_gserx_dlmx_tx_status_t, tx0_status, ==, 1, 10000)) {
            cvmx_warn("DLM0 TX0 status fail\n");
            return -1;
        }
        if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_TX_STATUS(0, 0),
            cvmx_gserx_dlmx_tx_status_t, tx0_cm_status, ==, 1, 10000)) {
            cvmx_warn("DLM0 TX0 CM status fail\n");
            return -1;
        }
    }
    if ((gd->arch.board_desc.board_type != CVMX_BOARD_TYPE_SIM) && need1) {
        if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_TX_STATUS(0, 0),
            cvmx_gserx_dlmx_tx_status_t, tx1_status, ==, 1, 10000)) {
            cvmx_warn("DLM0 TX1 status fail\n");
            return -1;
        }
        if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_TX_STATUS(0, 0),
            cvmx_gserx_dlmx_tx_status_t, tx1_cm_status, ==, 1, 10000)) {
            cvmx_warn("DLM0 TX1 CM status fail\n");
            return -1;
        }
    }
    return 0;
}

static int __dlm0_setup_rx_cn70xx(void)
{
    int need0, need1;
    cvmx_gmxx_inf_mode_t mode0, mode1;
    cvmx_gserx_dlmx_rx_rate_t rate;
    cvmx_gserx_dlmx_rx_pll_en_t pll_en;
    cvmx_gserx_dlmx_rx_data_en_t data_en;
    cvmx_gserx_dlmx_rx_reset_t rx_reset;

    mode0.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(0));
    mode1.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(1));

    /* Which lanes do we need? */
    need0 = (mode0.s.mode != CVMX_GMX_INF_MODE_DISABLED);
    need1 = (mode1.s.mode != CVMX_GMX_INF_MODE_DISABLED)
         || (mode0.s.mode == CVMX_GMX_INF_MODE_RXAUI);

    /* 1. Write GSER0_DLM0_RX_RATE[RXn_RATE] (must match the
       GER0_DLM0_TX_RATE[TXn_RATE] setting). */
    rate.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_RX_RATE(0, 0));
    rate.s.rx0_rate = (mode0.s.mode == CVMX_GMX_INF_MODE_SGMII) ? 2 : 0;
    rate.s.rx1_rate = (mode1.s.mode == CVMX_GMX_INF_MODE_SGMII) ? 2 : 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_RX_RATE(0, 0), rate.u64);

    /* 2. Set GSER0_DLM0_RX_PLL_EN[RXn_PLL_EN] = 1 */
    pll_en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_RX_PLL_EN(0, 0));
    pll_en.s.rx0_pll_en = need0;
    pll_en.s.rx1_pll_en = need1;
    cvmx_write_csr(CVMX_GSERX_DLMX_RX_PLL_EN(0, 0), pll_en.u64);

    /* 3. Set GSER0_DLM0_RX_DATA_EN[RXn_DATA_EN] = 1 */
    data_en.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_RX_DATA_EN(0, 0));
    data_en.s.rx0_data_en = need0;
    data_en.s.rx1_data_en = need1;
    cvmx_write_csr(CVMX_GSERX_DLMX_RX_DATA_EN(0, 0), data_en.u64);

    /* 4. Clear GSER0_DLM0_RX_RESET[RXn_DATA_EN] = 0. Now the GMX can be
       enabled: set GMX(0..1)_INF_MODE[EN] = 1 */
    rx_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_RX_RESET(0, 0));
    rx_reset.s.rx0_reset = !need0;
    rx_reset.s.rx1_reset = !need1;
    cvmx_write_csr(CVMX_GSERX_DLMX_RX_RESET(0, 0), rx_reset.u64);

    return 0;
}

static uint8_t sata_clkdiv_table[8] = {1, 2, 3, 4, 6, 8, 16, 24};

static int __dlm2_sata_uctl_init_cn70xx(void)
{
    int i;
    cvmx_sata_uctl_ctl_t uctl_ctl;

    /* Wait for all voltages to reach a stable stable. Ensure the
     * reference clock is up and stable.
     */

    /* 2. Wait for IOI reset to deassert. */

    /* 3. Optionally program the GPIO CSRs for SATA features.
     *    a. For cold-presence detect:
     *   i. Select a GPIO for the input and program GPIO_SATA_CTL[sel]
     *      for port0 and port1.
     *   ii. Select a GPIO for the output and program
     *       GPIO_BIT_CFG*[OUTPUT_SEL] for port0 and port1.
     *    b. For mechanical-presence detect, select a GPIO for the input
     *   and program GPIO_SATA_CTL[SEL] for port0/port1.
     *    c. For LED activity, select a GPIO for the output and program
     *   GPIO_BIT_CFG*[OUTPUT_SEL] for port0/port1.
     */

    /* 4. Assert all resets:
     *    a. UAHC reset: SATA_UCTL_CTL[UAHC_RST] = 1
     *    a. UCTL reset: SATA_UCTL_CTL[UCTL_RST] = 1
     */

    uctl_ctl.u64 = cvmx_read_csr(CVMX_SATA_UCTL_CTL);
    uctl_ctl.s.sata_uahc_rst = 1;
    uctl_ctl.s.sata_uctl_rst = 1;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

    /* 5. Configure the ACLK:
     *    a. Reset the clock dividers: SATA_UCTL_CTL[A_CLKDIV_RST] = 1.
     *    b. Select the ACLK frequency (400 MHz maximum)
     *   i. SATA_UCTL_CTL[A_CLKDIV] = desired value,
     *   ii. SATA_UCTL_CTL[A_CLKDIV_EN] = 1 to enable the ACLK,
     *    c. Deassert the ACLK clock divider reset:
     *   SATA_UCTL_CTL[A_CLKDIV_RST] = 0
     */
    uctl_ctl.s.a_clkdiv_rst = 1;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

    uctl_ctl.s.a_clkdiv_sel = 0;
    for (i = 0; i < 8; i++) {
        if (cvmx_clock_get_rate(CVMX_CLOCK_SCLK) / sata_clkdiv_table[i] <= 400000000) {
            uctl_ctl.s.a_clkdiv_sel = i;
            break;
        }
    }
    uctl_ctl.s.a_clk_en = 1;
    uctl_ctl.s.a_clk_byp_sel = 0;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

    uctl_ctl.s.a_clkdiv_rst = 0;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

    /* 6. Deassert UCTL and UAHC resets:
     *    a. SATA_UCTL_CTL[UCTL_RST] = 0
     *    b. SATA_UCTL_CTL[UAHC_RST] = 0
     *    c. Wait 10 ACLK cycles before accessing any ACLK-only registers.
     */

    uctl_ctl.s.sata_uctl_rst = 0;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

    uctl_ctl.s.sata_uahc_rst = 0;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

    cvmx_wait(50);

    /* 7. Enable conditional SCLK of UCTL by writing
          SATA_UCTL_CTL[CSCLK_EN] = 1 */

    uctl_ctl.s.csclk_en = 1;
    cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

#if 0
    /* 8. Configure PHY for SATA:
     *    a. Enable SATA: SATA_CFG[SATA_EN] = 1
     *    b. Program spread spectrum clock as desired:
     *   i. SATA_SSC_EN
     *   ii. SATA_SSC_RANGE
     *   iii. SATA_SSC_CLK_SEL
     *    c. Clear lane resets: SATA_LANE_RST[L*RST] = 0
     *    d. Enable reference clock: SATA_REF_SSP_EN[REF_SSP_EN] = 1
     *    e. Program reference clock divide-by-2 based on reference clock
     *   frequence.
     *   i. DLM2_REF_CLKDIV2[REF_CLKDIV2] = 0 (for 100 Mhz ref clock)
     *   ii. DLM2_REF_CLKDIV2[REF_CLKDIV2] = 1 (for 125 Mhz ref clock)
     */
#endif

    return 0;
}

static int __dlm2_sata_dlm_init_cn70xx(int qlm, int baud_mhz, int ref_clk_sel,
                int ref_clk_input)
{
    cvmx_gserx_sata_cfg_t sata_cfg;
    cvmx_gserx_sata_lane_rst_t sata_lane_rst;
    cvmx_gserx_dlmx_phy_reset_t dlmx_phy_reset;
    cvmx_gserx_dlmx_test_powerdown_t dlmx_test_powerdown;
    cvmx_gserx_sata_ref_ssp_en_t ref_ssp_en;
    cvmx_gserx_dlmx_mpll_multiplier_t mpll_multiplier;
    cvmx_gserx_dlmx_ref_clkdiv2_t ref_clkdiv2;
    cvmx_sata_uctl_shim_cfg_t shim_cfg;
    cvmx_gserx_phyx_ovrd_in_lo_t ovrd_in;
    int sata_ref_clk = 100;

    /* 5. Set GSERX0_SATA_CFG[SATA_EN] = 1 to configure DLM2 multiplexing.
     */
    sata_cfg.u64 = cvmx_read_csr(CVMX_GSERX_SATA_CFG(0));
    sata_cfg.s.sata_en = 1;
    cvmx_write_csr(CVMX_GSERX_SATA_CFG(0), sata_cfg.u64);

    /* 6. Clear either/both lane0 and lane1 resets:
     *    GSER0_SATA_LANE_RST[L0_RST, L1_RST] = 0.
     */
    sata_lane_rst.u64 = cvmx_read_csr(CVMX_GSERX_SATA_LANE_RST(0));
    sata_lane_rst.s.l0_rst = 0;
    sata_lane_rst.s.l1_rst = 0;
    cvmx_write_csr(CVMX_GSERX_SATA_LANE_RST(0), sata_lane_rst.u64);

    /* 1. Write GSER(0)_DLM2_REFCLK_SEL[REFCLK_SEL] if required for
     *    reference-clock selection.
     */

    cvmx_write_csr(CVMX_GSERX_DLMX_REFCLK_SEL(qlm, 0), ref_clk_sel);

    ref_ssp_en.u64 = cvmx_read_csr(CVMX_GSERX_SATA_REF_SSP_EN(0));
    ref_ssp_en.s.ref_ssp_en = 1;
    cvmx_write_csr(CVMX_GSERX_SATA_REF_SSP_EN(0), ref_ssp_en.u64);

    /* Apply workaround for Errata (G-20669) MPLL may not come up. */

    /* Set REF_CLKDIV2 based on the Ref Clock */
    ref_clkdiv2.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_REF_CLKDIV2(qlm, 0));
    if (sata_ref_clk == 100)
        ref_clkdiv2.s.ref_clkdiv2 = 0;
    else
        ref_clkdiv2.s.ref_clkdiv2 = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_REF_CLKDIV2(qlm, 0), ref_clkdiv2.u64);

    /* 1. Ensure GSER(0)_DLM(0..2)_PHY_RESET[PHY_RESET] is set. */
    dlmx_phy_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0));
    dlmx_phy_reset.s.phy_reset = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0), dlmx_phy_reset.u64);

    /* 2. If SGMII or QSGMII or RXAUI (i.e. if DLM0) set
          GSER(0)_DLM(0)_MPLL_EN[MPLL_EN] to one. */

    /* 3. Set GSER(0)_DLM(0..2)_MPLL_MULTIPLIER[MPLL_MULTIPLIER]
          to the value in the preceding table, which is different
          than the desired setting prescribed by the HRM. */

    mpll_multiplier.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0));
    if (sata_ref_clk == 100)
        mpll_multiplier.s.mpll_multiplier = 35;
    else
        mpll_multiplier.s.mpll_multiplier = 56;
    cvmx_write_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0), mpll_multiplier.u64);

    /* 3. Clear GSER0_DLM2_TEST_POWERDOWN[TEST_POWERDOWN] = 0 */
    dlmx_test_powerdown.u64 =
            cvmx_read_csr(CVMX_GSERX_DLMX_TEST_POWERDOWN(qlm, 0));
    dlmx_test_powerdown.s.test_powerdown = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_TEST_POWERDOWN(qlm, 0),
                dlmx_test_powerdown.u64);

    /* 4. Clear GSER0_DLM2_PHY_RESET */
    dlmx_phy_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0));
    dlmx_phy_reset.s.phy_reset = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0), dlmx_phy_reset.u64);

    /* 5. If PCIe or SATA (i.e. if DLM1 or DLM2), set both MPLL_EN
       and MPLL_EN_OVRD to one in GSER(0)_PHY(1..2)_OVRD_IN_LO. */
    ovrd_in.u64 = cvmx_read_csr(CVMX_GSERX_PHYX_OVRD_IN_LO(qlm, 0));
    ovrd_in.s.mpll_en = 1;
    ovrd_in.s.mpll_en_ovrd = 1;
    cvmx_write_csr(CVMX_GSERX_PHYX_OVRD_IN_LO(qlm, 0), ovrd_in.u64);

    /* 6. Decrease MPLL_MULTIPLIER by one continually until it reaches
         the desired long-term setting, ensuring that each MPLL_MULTIPLIER
         value is constant for at least 1 msec before changing to the next
         value. The desired long-term setting is as indicated in HRM tables
         21-1, 21-2, and 21-3. This is not required with the HRM
         sequence. */
    mpll_multiplier.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0));
    if (sata_ref_clk == 100)
        mpll_multiplier.s.mpll_multiplier = 0x1e;
    else
        mpll_multiplier.s.mpll_multiplier = 0x30;
    cvmx_write_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0), mpll_multiplier.u64);

    if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_MPLL_STATUS(qlm, 0),
        cvmx_gserx_dlmx_mpll_status_t, mpll_status, ==, 1, 10000)) {
        printf("ERROR: SATA MPLL failed to set\n");
        return -1;
    }

    if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_RX_STATUS(qlm, 0),
        cvmx_gserx_dlmx_rx_status_t, rx0_status, ==, 1, 10000)) {
        printf("ERROR: SATA RX0_STATUS failed to set\n");
        return -1;
    }
    if (CVMX_WAIT_FOR_FIELD64(CVMX_GSERX_DLMX_RX_STATUS(qlm, 0),
        cvmx_gserx_dlmx_rx_status_t, rx1_status, ==, 1, 10000)) {
        printf("ERROR: SATA RX1_STATUS failed to set\n");
        return -1;
    }

    /* 10. Initialize UAHC as described in the AHCI Specification (UAHC_*
     *     registers
     */

    /* set-up endian mode */
    shim_cfg.u64 = cvmx_read_csr(CVMX_SATA_UCTL_SHIM_CFG);
    shim_cfg.s.dma_endian_mode = 1;
    shim_cfg.s.csr_endian_mode = 3;
    cvmx_write_csr(CVMX_SATA_UCTL_SHIM_CFG, shim_cfg.u64);

    return 0;
}

static int __dlm2_sata_uahc_init_cn70xx(void)
{
    cvmx_sata_uahc_gbl_cap_t gbl_cap;
    cvmx_sata_uahc_px_sctl_t sctl;
    cvmx_sata_uahc_gbl_pi_t pi;
    cvmx_sata_uahc_px_cmd_t cmd;
    cvmx_sata_uahc_px_sctl_t sctl0, sctl1;
    cvmx_sata_uahc_px_ssts_t ssts;
    uint64_t done;
    int result = -1;

    /* Set-u global capabilities reg (GBL_CAP) */
    gbl_cap.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_GBL_CAP);
    gbl_cap.s.sss = 1;
    gbl_cap.s.smps = 1;
    cvmx_write64_int32(CVMX_SATA_UAHC_GBL_CAP, gbl_cap.u32);

    /* Set-up global hba control reg (interrupt enables) */
    /* Set-up port SATA control registers (speed limitation) */

    sctl.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_SCTL(0));
    sctl.s.spd = 3;
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_SCTL(0), sctl.u32);
    sctl.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_SCTL(1));
    sctl.s.spd = 3;
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_SCTL(1), sctl.u32);

    /* Set-up ports implemented reg. */
    pi.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_GBL_PI);
    pi.s.pi = 3;
    cvmx_write64_int32(CVMX_SATA_UAHC_GBL_PI, pi.u32);

    /* Clear port SERR and IS registers */
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_SERR(0),
            cvmx_read64_int32(CVMX_SATA_UAHC_PX_SERR(0)));
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_SERR(1),
            cvmx_read64_int32(CVMX_SATA_UAHC_PX_SERR(1)));
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_IS(0),
            cvmx_read64_int32(CVMX_SATA_UAHC_PX_IS(0)));
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_IS(1),
            cvmx_read64_int32(CVMX_SATA_UAHC_PX_IS(1)));

    /* Set spin-up, power on, FIS RX enable, start, active */
    cmd.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_CMD(0));
    cmd.s.fre = 1;
    cmd.s.sud = 1;
    cmd.s.pod = 1;
    cmd.s.st = 1;
    cmd.s.icc = 1;
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_CMD(0), cmd.u32);
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_CMD(1), cmd.u32);

    sctl0.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_SCTL(0));
    sctl0.s.det = 1;
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_SCTL(0), sctl0.u32);

    /* check status */
        done = cvmx_clock_get_count(CVMX_CLOCK_CORE) + 1000000 *
                        cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000000;
    while (1) {
        ssts.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_SSTS(0));

        if ((ssts.s.ipm == 1) && (ssts.s.det == 3)) {
            result = 0;
            break;
        } else if (cvmx_clock_get_count(CVMX_CLOCK_CORE) > done) {
            result = -1;
            break;
        } else
            cvmx_wait(100);
    }

    if (result == -1) {
        printf("SATA0: not available\n");
#if 0
        printf("ERROR: Failed to detect SATA0 device: 0x%lx\n",
               cvmx_read64_int32(CVMX_SATA_UAHC_PX_SSTS(0)));

        return -1;
#endif
    } else
        printf("SATA0: available\n");

    sctl1.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_SCTL(1));
    sctl1.s.det = 1;
    cvmx_write64_int32(CVMX_SATA_UAHC_PX_SCTL(1), sctl1.u32);

    /* check status */
        done = cvmx_clock_get_count(CVMX_CLOCK_CORE) + 1000000 *
                        cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000000;
    while (1) {
        ssts.u32 = cvmx_read64_int32(CVMX_SATA_UAHC_PX_SSTS(1));

        if ((ssts.s.ipm == 1) && (ssts.s.det == 3)) {
            result = 0;
            break;
        } else if (cvmx_clock_get_count(CVMX_CLOCK_CORE) > done) {
            result = -1;
            break;
        } else
            cvmx_wait(100);
    }

    if (result == -1) {
        printf("SATA1: not available\n");
#if 0
        printf("ERROR: Failed to detect SATA1 device: 0x%lx\n",
               cvmx_read64_int32(CVMX_SATA_UAHC_PX_SSTS(1)));
        return -1;
#endif
    } else
        printf("SATA1: available\n");

    return 0;
}

static int __sata_bist_cn70xx(int qlm, int baud_mhz, int ref_clk_sel,
                  int ref_clk_input)
{
    cvmx_sata_uctl_bist_status_t bist_status;
    cvmx_sata_uctl_ctl_t uctl_ctl;
    cvmx_sata_uctl_shim_cfg_t shim_cfg;
    uint64_t done;
    int result = -1;

    bist_status.u64 = cvmx_read_csr(CVMX_SATA_UCTL_BIST_STATUS);
    if (bist_status.s.uctl_xm_r_bist_ndone &&
        bist_status.s.uctl_xm_w_bist_ndone &&
        bist_status.s.uahc_p0_rxram_bist_ndone &&
        bist_status.s.uahc_p1_rxram_bist_ndone &&
        bist_status.s.uahc_p0_txram_bist_ndone &&
        bist_status.s.uahc_p1_txram_bist_ndone) {
        if (__dlm2_sata_uctl_init_cn70xx()) {
            printf("ERROR: Failed to initialize SATA UCTL CSRs\n");
            return -1;
        }
        if (__dlm2_sata_dlm_init_cn70xx(qlm, baud_mhz, ref_clk_sel,
                        ref_clk_input)) {
            printf("ERROR: Failed to initialize SATA GSER CSRs\n");
            return -1;
        }
        if (__dlm2_sata_uahc_init_cn70xx()) {
            printf("ERROR: Failed to initialize SATA UAHC CSRs\n");
            return -1;
        }
        uctl_ctl.u64 = cvmx_read_csr(CVMX_SATA_UCTL_CTL);
        uctl_ctl.s.start_bist = 1;
        cvmx_write_csr(CVMX_SATA_UCTL_CTL, uctl_ctl.u64);

        /* Set-up for a 1 sec timer. */
            done = cvmx_clock_get_count(CVMX_CLOCK_CORE) + 1000000 *
                        cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000000;
        while (1) {
            bist_status.u64 = cvmx_read_csr(CVMX_SATA_UCTL_BIST_STATUS);
            if ((bist_status.s.uctl_xm_r_bist_ndone |
                 bist_status.s.uctl_xm_w_bist_ndone |
                 bist_status.s.uahc_p0_rxram_bist_ndone |
                 bist_status.s.uahc_p1_rxram_bist_ndone |
                 bist_status.s.uahc_p0_txram_bist_ndone |
                 bist_status.s.uahc_p1_txram_bist_ndone) == 0) {
                result = 0;
                break;
            } else if (cvmx_clock_get_count(CVMX_CLOCK_CORE) > done) {
                result = -1;
                break;
            } else
                cvmx_wait(100);
        }
        if (result == -1) {
            cvmx_warn("ERROR: SATA_UCTL_BIST_STATUS = 0x%llx\n",
                     bist_status.u64);
            return -1;
        }
    }

    /* Change CSR_ENDIAN_MODE to big endian to use Open Source xHCI SATA
       driver */
    shim_cfg.u64 = cvmx_read_csr(CVMX_SATA_UCTL_SHIM_CFG);
    shim_cfg.s.csr_endian_mode = 1;
    cvmx_write_csr(CVMX_SATA_UCTL_SHIM_CFG, shim_cfg.u64);

    printf("SATA BIST STATUS = 0x%llx\n",
           cvmx_read_csr(CVMX_SATA_UCTL_BIST_STATUS));

    return 0;
}

static int __dlm2_setup_sata_cn70xx(int qlm, int baud_mhz, int ref_clk_sel,
                    int ref_clk_input)
{
    return __sata_bist_cn70xx(qlm, baud_mhz, ref_clk_sel, ref_clk_input);
}


static int __dlmx_setup_pcie_cn70xx(int qlm, enum cvmx_qlm_mode mode,
                int gen2, int rc, int ref_clk_sel,
                int ref_clk_input)
{
    cvmx_gserx_dlmx_phy_reset_t dlmx_phy_reset;
    cvmx_gserx_dlmx_test_powerdown_t dlmx_test_powerdown;
    cvmx_gserx_dlmx_mpll_multiplier_t mpll_multiplier;
    cvmx_gserx_dlmx_ref_clkdiv2_t ref_clkdiv2;

    if (rc == 0) {
        debug("Skipping initializing PCIe dlm %d in endpoint mode\n",
              qlm);
        return 0;
    }

    /* 1. Write GSER0_DLM(1..2)_REFCLK_SEL[REFCLK_SEL] if required for
     *    reference-clock selection
     */

    cvmx_write_csr(CVMX_GSERX_DLMX_REFCLK_SEL(qlm, 0), ref_clk_sel);

    /* 2. If required, write GSER0_DLM(1..2)_REF_CLKDIV2[REF_CLKDIV2] = 1
     *    (must be set if reference clock >= 100 MHz)
     */

    /* 4. Configure the PCIE PIPE:
     *  a. Write GSER0_PCIE_PIPE_PORT_SEL[PIPE_PORT_SEL] to configure the
     *     PCIE PIPE.
     *  0x0 = disables all pipes
     *  0x1 = enables pipe0 only (PEM0 4-lane)
     *  0x2 = enables pipes 0 and 1 (PEM0 and PEM1 2-lanes each)
     *  0x3 = enables pipes 0, 1, 2, and 3 (PEM0, PEM1, and PEM3 are
     *        one-lane each)
     *  b. Configure GSER0_PCIE_PIPE_PORT_SEL[CFG_PEM1_DLM2]. If PEM1 is
     *     to be configured, this bit must reflect which DLM it is logically
     *     tied to. This bit sets multiplexing logic in GSER, and it is used
     *     by the RST logic to determine when the MAC can come out of reset.
     *  0 = PEM1 is tied to DLM1 (for 3 x 1 PCIe mode).
     *  1 = PEM1 is tied to DLM2 (for all other PCIe modes).
     */
    if (qlm == 1) {
        cvmx_gserx_pcie_pipe_port_sel_t pipe_port;

        pipe_port.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_PORT_SEL(0));
        pipe_port.s.cfg_pem1_dlm2 =
                (mode == CVMX_QLM_MODE_PCIE_1X1) ? 1 : 0;
        pipe_port.s.pipe_port_sel =
                (mode == CVMX_QLM_MODE_PCIE) ? 1 : /* PEM0 only */
                (mode == CVMX_QLM_MODE_PCIE_1X2) ? 2 : /* PEM0-1 */
                (mode == CVMX_QLM_MODE_PCIE_1X1) ? 3 : /* PEM0-2 */
                (mode == CVMX_QLM_MODE_PCIE_2X1) ? 3 : /* PEM0-1 */
                0; /* PCIe disabled */
        cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_PORT_SEL(0), pipe_port.u64);
    }

    /* Apply workaround for Errata (G-20669) MPLL may not come up. */

    /* Set REF_CLKDIV2 based on the Ref Clock */
    ref_clkdiv2.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_REF_CLKDIV2(qlm, 0));
    ref_clkdiv2.s.ref_clkdiv2 = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_REF_CLKDIV2(qlm, 0), ref_clkdiv2.u64);

    /* 1. Ensure GSER(0)_DLM(0..2)_PHY_RESET[PHY_RESET] is set. */
    dlmx_phy_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0));
    dlmx_phy_reset.s.phy_reset = 1;
    cvmx_write_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0), dlmx_phy_reset.u64);

    /* 2. If SGMII or QSGMII or RXAUI (i.e. if DLM0) set
          GSER(0)_DLM(0)_MPLL_EN[MPLL_EN] to one. */

    /* 3. Set GSER(0)_DLM(0..2)_MPLL_MULTIPLIER[MPLL_MULTIPLIER]
          to the value in the preceding table, which is different
          than the desired setting prescribed by the HRM. */
    mpll_multiplier.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0));
    mpll_multiplier.s.mpll_multiplier = 56;
    cvmx_write_csr(CVMX_GSERX_DLMX_MPLL_MULTIPLIER(qlm, 0), mpll_multiplier.u64);
    /* 5. Clear GSER0_DLM(1..2)_TEST_POWERDOWN. Configurations that only
     *    use DLM1 need not clear GSER0_DLM2_TEST_POWERDOWN
     */
    dlmx_test_powerdown.u64 =
            cvmx_read_csr(CVMX_GSERX_DLMX_TEST_POWERDOWN(qlm, 0));
    dlmx_test_powerdown.s.test_powerdown = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_TEST_POWERDOWN(qlm, 0),
               dlmx_test_powerdown.u64);

    /* 6. Clear GSER0_DLM(1..2)_PHY_RESET. Configurations that use only
     *    need DLM1 need not clear GSER0_DLM2_PHY_RESET
     */
    dlmx_phy_reset.u64 = cvmx_read_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0));
    dlmx_phy_reset.s.phy_reset = 0;
    cvmx_write_csr(CVMX_GSERX_DLMX_PHY_RESET(qlm, 0), dlmx_phy_reset.u64);

    /* 6. Decrease MPLL_MULTIPLIER by one continually until it reaches
         the desired long-term setting, ensuring that each MPLL_MULTIPLIER
         value is constant for at least 1 msec before changing to the next
         value. The desired long-term setting is as indicated in HRM tables
         21-1, 21-2, and 21-3. This is not required with the HRM
         sequence. */
    /* This is set when initializing PCIe after soft reset is asserted. */

    /* 7. Write the GSER0_PCIE_PIPE_RST register to take the appropriate
     *    PIPE out of reset. There is a PIPEn_RST bit for each PIPE. Clear
     *    the appropriate bits based on the configuration (reset is
     *     active high).
     */
    if (qlm == 1) {
        cvmx_pemx_cfg_t pemx_cfg;
        cvmx_pemx_on_t pemx_on;
        cvmx_gserx_pcie_pipe_rst_t pipe_rst;
        cvmx_rst_ctlx_t rst_ctl;

        switch(mode) {
        case CVMX_QLM_MODE_PCIE: /* PEM0 on DLM1 & DLM2 */
        case CVMX_QLM_MODE_PCIE_1X2: /* PEM0 on DLM1 */
        case CVMX_QLM_MODE_PCIE_1X1: /* PEM0 on DLM1 using lane 0 */
            pemx_cfg.u64 = cvmx_read_csr(CVMX_PEMX_CFG(0));
            pemx_cfg.cn70xx.hostmd = rc;
            if (mode == CVMX_QLM_MODE_PCIE_1X1) {
                pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_1LANE
                             : CVMX_PEM_MD_GEN1_1LANE;
            } else if (mode == CVMX_QLM_MODE_PCIE) {
                pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_4LANE
                             : CVMX_PEM_MD_GEN1_4LANE;
            } else {
                pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_2LANE
                             : CVMX_PEM_MD_GEN1_2LANE;
            }
            cvmx_write_csr(CVMX_PEMX_CFG(0), pemx_cfg.u64);

            rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(0));
            rst_ctl.s.rst_drv = 1;
            cvmx_write_csr(CVMX_RST_CTLX(0), rst_ctl.u64);

            /* PEM0 is on DLM1&2 which is pipe0 */
            pipe_rst.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_RST(0));
            pipe_rst.s.pipe0_rst = 0;
            cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_RST(0),
                       pipe_rst.u64);

            pemx_on.u64 = cvmx_read_csr(CVMX_PEMX_ON(0));
            pemx_on.s.pemon = 1;
            cvmx_write_csr(CVMX_PEMX_ON(0), pemx_on.u64);
            break;
        case CVMX_QLM_MODE_PCIE_2X1: /* PEM0 and PEM1 on DLM1 */
            pemx_cfg.u64 = cvmx_read_csr(CVMX_PEMX_CFG(0));
            pemx_cfg.cn70xx.hostmd = rc;
            pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_1LANE
                         : CVMX_PEM_MD_GEN1_1LANE;
            cvmx_write_csr(CVMX_PEMX_CFG(0), pemx_cfg.u64);

            rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(0));
            rst_ctl.s.rst_drv = 1;
            cvmx_write_csr(CVMX_RST_CTLX(0), rst_ctl.u64);

            /* PEM0 is on DLM1 which is pipe0 */
            pipe_rst.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_RST(0));
            pipe_rst.s.pipe0_rst = 0;
            cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_RST(0),
                       pipe_rst.u64);

            pemx_on.u64 = cvmx_read_csr(CVMX_PEMX_ON(0));
            pemx_on.s.pemon = 1;
            cvmx_write_csr(CVMX_PEMX_ON(0), pemx_on.u64);

            pemx_cfg.u64 = cvmx_read_csr(CVMX_PEMX_CFG(1));
            pemx_cfg.cn70xx.hostmd = 1;
            pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_1LANE
                         : CVMX_PEM_MD_GEN1_1LANE;
            cvmx_write_csr(CVMX_PEMX_CFG(1), pemx_cfg.u64);
            rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(1));
            rst_ctl.s.rst_drv = 1;
            cvmx_write_csr(CVMX_RST_CTLX(1), rst_ctl.u64);
            /* PEM1 is on DLM2 which is pipe1 */
            pipe_rst.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_RST(0));
            pipe_rst.s.pipe1_rst = 0;
            cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_RST(0),
                       pipe_rst.u64);
            pemx_on.u64 = cvmx_read_csr(CVMX_PEMX_ON(1));
            pemx_on.s.pemon = 1;
            cvmx_write_csr(CVMX_PEMX_ON(1), pemx_on.u64);
            break;
        default:
            break;
        }
    } else {
        cvmx_pemx_cfg_t pemx_cfg;
        cvmx_pemx_on_t pemx_on;
        cvmx_gserx_pcie_pipe_rst_t pipe_rst;
        cvmx_rst_ctlx_t rst_ctl;

        switch (mode) {
        case CVMX_QLM_MODE_PCIE_1X2:  /* PEM1 on DLM2 */
            pemx_cfg.u64 = cvmx_read_csr(CVMX_PEMX_CFG(1));
            pemx_cfg.cn70xx.hostmd = 1;
            pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_2LANE
                         : CVMX_PEM_MD_GEN1_2LANE;
            cvmx_write_csr(CVMX_PEMX_CFG(1), pemx_cfg.u64);

            rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(1));
            rst_ctl.s.rst_drv = 1;
            cvmx_write_csr(CVMX_RST_CTLX(1), rst_ctl.u64);

            /* PEM1 is on DLM1 lane 0, which is pipe1 */
            pipe_rst.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_RST(0));
            pipe_rst.s.pipe1_rst = 0;
            cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_RST(0),
                       pipe_rst.u64);

            pemx_on.u64 = cvmx_read_csr(CVMX_PEMX_ON(1));
            pemx_on.s.pemon = 1;
            cvmx_write_csr(CVMX_PEMX_ON(1), pemx_on.u64);
            break;
        case CVMX_QLM_MODE_PCIE_2X1:  /* PEM1 and PEM2 on DLM2 */
            pemx_cfg.u64 = cvmx_read_csr(CVMX_PEMX_CFG(1));
            pemx_cfg.cn70xx.hostmd = 1;
            pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_1LANE
                         : CVMX_PEM_MD_GEN1_1LANE;
            cvmx_write_csr(CVMX_PEMX_CFG(1), pemx_cfg.u64);

            rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(1));
            rst_ctl.s.rst_drv = 1;
            cvmx_write_csr(CVMX_RST_CTLX(1), rst_ctl.u64);

            /* PEM1 is on DLM2 lane 0, which is pipe2 */
            pipe_rst.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_RST(0));
            pipe_rst.s.pipe2_rst = 0;
            cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_RST(0),
                       pipe_rst.u64);

            pemx_on.u64 = cvmx_read_csr(CVMX_PEMX_ON(1));
            pemx_on.s.pemon = 1;
            cvmx_write_csr(CVMX_PEMX_ON(1), pemx_on.u64);

            pemx_cfg.u64 = cvmx_read_csr(CVMX_PEMX_CFG(2));
            pemx_cfg.cn70xx.hostmd = 1;
            pemx_cfg.cn70xx.md = gen2 ? CVMX_PEM_MD_GEN2_1LANE
                         : CVMX_PEM_MD_GEN1_1LANE;
            cvmx_write_csr(CVMX_PEMX_CFG(2), pemx_cfg.u64);

            rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(2));
            rst_ctl.s.rst_drv = 1;
            cvmx_write_csr(CVMX_RST_CTLX(2), rst_ctl.u64);

            /* PEM2 is on DLM2 lane 1, which is pipe3 */
            pipe_rst.u64 = cvmx_read_csr(CVMX_GSERX_PCIE_PIPE_RST(0));
            pipe_rst.s.pipe3_rst = 0;
            cvmx_write_csr(CVMX_GSERX_PCIE_PIPE_RST(0),
                       pipe_rst.u64);

            pemx_on.u64 = cvmx_read_csr(CVMX_PEMX_ON(2));
            pemx_on.s.pemon = 1;
            cvmx_write_csr(CVMX_PEMX_ON(2), pemx_on.u64);
            break;
        default:
            break;
        }
    }
    return 0;
}

/**
 * Configure dlm speed and mode for cn70xx.
 *
 * @param qlm     The DLM to configure
 * @param speed   The speed the DLM needs to be configured in Mhz.
 * @param mode    The DLM to be configured as SGMII/XAUI/PCIe.
 *                  DLM 0: has 2 interfaces which can be configured as
 *                         SGMII/QSGMII/RXAUI. Need to configure both at the
 *                         same time. These are valid option
 *              CVMX_QLM_MODE_QSGMII,
 *              CVMX_QLM_MODE_SGMII_SGMII,
 *              CVMX_QLM_MODE_SGMII_DISABLED,
 *              CVMX_QLM_MODE_DISABLED_SGMII,
 *              CVMX_QLM_MODE_SGMII_QSGMII,
 *              CVMX_QLM_MODE_QSGMII_QSGMII,
 *              CVMX_QLM_MODE_QSGMII_DISABLED,
 *              CVMX_QLM_MODE_DISABLED_QSGMII,
 *              CVMX_QLM_MODE_QSGMII_SGMII,
 *              CVMX_QLM_MODE_RXAUI_1X2
 *
 *                  DLM 1: PEM0/1 in PCIE_1x4/PCIE_2x1/PCIE_1X1
 *                  DLM 2: PEM0/1/2 in PCIE_1x4/PCIE_1x2/PCIE_2x1/PCIE_1x1
 * @param rc      Only used for PCIe, rc = 1 for root complex mode, 0 for EP mode.
 * @param gen2    Only used for PCIe, gen2 = 1, in GEN2 mode else in GEN1 mode.
 *
 * @param ref_clk_input  The reference-clock input to use to configure QLM
 * @param ref_clk_sel    The reference-clock selection to use to configure QLM
 *
 * @return       Return 0 on success or -1.
 */
static int octeon_configure_qlm_cn70xx(int qlm, int speed, int mode, int rc,
                       int gen2, int ref_clk_sel,
                       int ref_clk_input)
{
    switch (qlm) {
    case 0:
        {
            int is_sff7000_rxaui = 0;
            cvmx_gmxx_inf_mode_t inf_mode0, inf_mode1;

            inf_mode0.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(0));
            inf_mode1.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(1));
            if (inf_mode0.s.en || inf_mode1.s.en) {
                cvmx_dprintf("DLM0 already configured\n");
                return -1;
            }

            switch (mode) {
            case CVMX_QLM_MODE_SGMII_SGMII:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_SGMII;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_SGMII;
                break;
            case CVMX_QLM_MODE_SGMII_QSGMII:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_SGMII;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_QSGMII;
                break;
            case CVMX_QLM_MODE_SGMII_DISABLED:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_SGMII;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                break;
            case CVMX_QLM_MODE_DISABLED_SGMII:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_SGMII;
                break;
            case CVMX_QLM_MODE_QSGMII_SGMII:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_QSGMII;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_SGMII;
                break;
            case CVMX_QLM_MODE_QSGMII_QSGMII:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_QSGMII;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_QSGMII;
                break;
            case CVMX_QLM_MODE_QSGMII_DISABLED:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_QSGMII;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                break;
            case CVMX_QLM_MODE_DISABLED_QSGMII:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_QSGMII;
                break;
            case CVMX_QLM_MODE_RXAUI:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_RXAUI;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                if (gd->arch.board_desc.board_type == CVMX_BOARD_TYPE_SFF7000) {
                    is_sff7000_rxaui = 1;
                }

                break;
            default:
                inf_mode0.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                inf_mode1.s.mode = CVMX_GMX_INF_MODE_DISABLED;
                break;
            }
            cvmx_write_csr(CVMX_GMXX_INF_MODE(0), inf_mode0.u64);
            cvmx_write_csr(CVMX_GMXX_INF_MODE(1), inf_mode1.u64);

            /* Bringup the PLL */
            if (__dlm_setup_pll_cn70xx(qlm, speed, ref_clk_sel,
                     ref_clk_input, is_sff7000_rxaui))
                return -1;

            /* TX Lanes */
            if (__dlm0_setup_tx_cn70xx())
                return -1;

            /* RX Lanes */
            if (__dlm0_setup_rx_cn70xx())
                return -1;

            /* Enable the interface */
            inf_mode0.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(0));
            if (inf_mode0.s.mode != CVMX_GMX_INF_MODE_DISABLED)
                inf_mode0.s.en = 1;
            cvmx_write_csr(CVMX_GMXX_INF_MODE(0), inf_mode0.u64);
            inf_mode1.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(1));
            if (inf_mode1.s.mode != CVMX_GMX_INF_MODE_DISABLED)
                inf_mode1.s.en = 1;
            cvmx_write_csr(CVMX_GMXX_INF_MODE(1), inf_mode1.u64);
            break;
        }
    case 1:
        switch (mode) {
        case CVMX_QLM_MODE_PCIE: /* PEM0 on DLM1 & DLM2 */
            if (__dlmx_setup_pcie_cn70xx(1, mode, gen2, rc,
                             ref_clk_sel,
                             ref_clk_input))
                return -1;
            if (__dlmx_setup_pcie_cn70xx(2, mode, gen2, rc,
                             ref_clk_sel,
                             ref_clk_input))
                return -1;
            break;
        case CVMX_QLM_MODE_PCIE_1X2: /* PEM0 on DLM1 */
        case CVMX_QLM_MODE_PCIE_2X1: /* PEM0 & PEM1 on DLM1 */
        case CVMX_QLM_MODE_PCIE_1X1: /* PEM0 on DLM1, only 1 lane */
            if (__dlmx_setup_pcie_cn70xx(qlm, mode, gen2, rc,
                             ref_clk_sel,
                             ref_clk_input))
                return -1;
            break;
        case CVMX_QLM_MODE_DISABLED:
            break;
        default:
            debug("DLM1 illegal mode specified\n");
            return -1;
        }
        break;
    case 2:
        switch (mode) {
        case CVMX_QLM_MODE_SATA_2X1:
            /* DLM2 is SATA, PCIE2 is disabled */
            if (__dlm2_setup_sata_cn70xx(qlm, speed, ref_clk_sel,
                             ref_clk_input))
                return -1;
            break;
        case CVMX_QLM_MODE_PCIE:
            /* DLM2 is PCIE0, PCIE1-2 are disabled. */
            /* Do nothing, its initialized in DLM1 */
            break;
        case CVMX_QLM_MODE_PCIE_1X2: /* PEM1 on DLM2 */
        case CVMX_QLM_MODE_PCIE_2X1: /* PEM1 & PEM2 on DLM2 */
            if (__dlmx_setup_pcie_cn70xx(qlm, mode, gen2, rc,
                             ref_clk_sel,
                             ref_clk_input))
                return -1;
            break;
        case CVMX_QLM_MODE_DISABLED:
            break;
        default:
            debug("DLM2 illegal mode specified\n");
            return -1;
        }
    default:
            return -1;
    }

    return 0;
}

/**
 * Configure qlm/dlm speed and mode.
 * @param qlm     The QLM or DLM to configure
 * @param speed   The speed the QLM needs to be configured in Mhz.
 * @param mode    The QLM to be configured as SGMII/XAUI/PCIe.
 * @param rc      Only used for PCIe, rc = 1 for root complex mode, 0 for EP
 *        mode.
 * @param pcie_mode Only used when qlm/dlm are in pcie mode.
 * @param ref_clk_sel Reference clock to use for 70XX
 * @param ref_clk_input When set selects the external ref_pad_clk_{p,m} inputs
 *          as the reference-clock source.  When deasserted,
 *          ref_alt_clk_{p,m} are selected from an on-chip source of
 *          the reference clock.
 *
 * @return       Return 0 on success or -1.
 */
int octeon_configure_qlm(int qlm, int speed, int mode, int rc, int pcie_mode,
            int ref_clk_sel, int ref_clk_input)
{
    if (OCTEON_IS_MODEL(OCTEON_CN61XX) || OCTEON_IS_MODEL(OCTEON_CNF71XX))
        return octeon_configure_qlm_cn61xx(qlm, speed, mode, rc,
                           pcie_mode);
    else if (OCTEON_IS_MODEL(OCTEON_CN70XX))
        return octeon_configure_qlm_cn70xx(qlm, speed, mode, rc,
                           pcie_mode, ref_clk_sel,
                           ref_clk_input);
    else
        return -1;
}
