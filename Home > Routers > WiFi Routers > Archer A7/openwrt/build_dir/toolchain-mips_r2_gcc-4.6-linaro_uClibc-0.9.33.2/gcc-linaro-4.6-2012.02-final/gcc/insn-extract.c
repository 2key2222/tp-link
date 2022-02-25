/* Generated automatically by the program `genextract'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "insn-config.h"
#include "recog.h"
#include "diagnostic-core.h"

/* This variable is used as the "location" of any missing operand
   whose numbers are skipped by a given pattern.  */
static rtx junk ATTRIBUTE_UNUSED;

void
insn_extract (rtx insn)
{
  rtx *ro = recog_data.operand;
  rtx **ro_loc = recog_data.operand_loc;
  rtx pat = PATTERN (insn);
  int i ATTRIBUTE_UNUSED; /* only for peepholes */

#ifdef ENABLE_CHECKING
  memset (ro, 0xab, sizeof (*ro) * MAX_RECOG_OPERANDS);
  memset (ro_loc, 0xab, sizeof (*ro_loc) * MAX_RECOG_OPERANDS);
#endif

  switch (INSN_CODE (insn))
    {
    default:
      /* Control reaches here if insn_extract has been called with an
         unrecognizable insn (code -1), or an insn whose INSN_CODE
         corresponds to a DEFINE_EXPAND in the machine description;
         either way, a bug.  */
      if (INSN_CODE (insn) < 0)
        fatal_insn ("unrecognizable insn:", insn);
      else
        fatal_insn ("insn with invalid code number:", insn);

    case 900:  /* ssmsubsqdq4 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[2] = 1;
      break;

    case 899:  /* ssmaddsqdq4 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[2] = 1;
      break;

    case 898:  /* ssmulsq3 */
    case 897:  /* ssmulhq3 */
    case 896:  /* ssmulv2hq3 */
    case 813:  /* mulv2hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      break;

    case 800:  /* mips_bposge */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 792:  /* mips_wrdsp */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 5), 1), 0, 1);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 5), 1), 0, 0);
      recog_data.dup_num[1] = 0;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 4), 1), 0, 1);
      recog_data.dup_num[2] = 1;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 4), 1), 0, 0);
      recog_data.dup_num[3] = 0;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 3), 1), 0, 1);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 3), 1), 0, 0);
      recog_data.dup_num[5] = 0;
      recog_data.dup_loc[6] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[6] = 1;
      recog_data.dup_loc[7] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[7] = 0;
      recog_data.dup_loc[8] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[8] = 1;
      recog_data.dup_loc[9] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[9] = 0;
      break;

    case 789:  /* mips_extpdp */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 2), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[2] = 2;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[3] = 1;
      break;

    case 843:  /* mips_dpsqx_sa_w_ph */
    case 842:  /* mips_dpsqx_s_w_ph */
    case 841:  /* mips_dpaqx_sa_w_ph */
    case 840:  /* mips_dpaqx_s_w_ph */
    case 767:  /* mips_maq_sa_w_phr */
    case 766:  /* mips_maq_sa_w_phl */
    case 765:  /* mips_maq_s_w_phr */
    case 764:  /* mips_maq_s_w_phl */
    case 763:  /* mips_dpsq_sa_l_w */
    case 762:  /* mips_dpaq_sa_l_w */
    case 761:  /* mips_mulsaq_s_w_ph */
    case 760:  /* mips_dpsq_s_w_ph */
    case 759:  /* mips_dpaq_s_w_ph */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[0] = 3;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[2] = 1;
      break;

    case 817:  /* mips_mulq_s_w */
    case 816:  /* mips_mulq_s_ph */
    case 815:  /* mips_mulq_rs_w */
    case 814:  /* mips_mul_s_ph */
    case 754:  /* mips_muleq_s_w_phr */
    case 753:  /* mips_muleq_s_w_phl */
    case 752:  /* mips_mulq_rs_ph */
    case 751:  /* mips_muleu_s_ph_qbr */
    case 750:  /* mips_muleu_s_ph_qbl */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 2), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      break;

    case 801:  /* mips_absq_s_qb */
    case 727:  /* mips_absq_s_ph */
    case 726:  /* mips_absq_s_w */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[0] = 1;
      break;

    case 827:  /* mips_subu_s_ph */
    case 826:  /* mips_subu_ph */
    case 810:  /* mips_cmpgdu_le_qb */
    case 809:  /* mips_cmpgdu_lt_qb */
    case 808:  /* mips_cmpgdu_eq_qb */
    case 803:  /* mips_addu_s_ph */
    case 791:  /* mips_mthlip */
    case 788:  /* mips_extp */
    case 787:  /* mips_extr_s_h */
    case 786:  /* mips_extr_rs_w */
    case 785:  /* mips_extr_r_w */
    case 784:  /* mips_extr_w */
    case 745:  /* mips_shll_s_ph */
    case 744:  /* mips_shll_s_w */
    case 743:  /* mips_shll_qb */
    case 742:  /* mips_shll_ph */
    case 731:  /* mips_precrqu_s_qb_ph */
    case 730:  /* mips_precrq_rs_ph_w */
    case 723:  /* mips_addwc */
    case 722:  /* mips_addsc */
    case 721:  /* mips_subu_s_qb */
    case 720:  /* mips_subq_s_ph */
    case 719:  /* mips_subq_s_w */
    case 716:  /* mips_addu_s_qb */
    case 715:  /* mips_addq_s_ph */
    case 714:  /* mips_addq_s_w */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      break;

    case 895:  /* sssubv2ha3 */
    case 894:  /* sssubv2hq3 */
    case 893:  /* sssubsa3 */
    case 892:  /* sssubha3 */
    case 891:  /* sssubsq3 */
    case 890:  /* sssubhq3 */
    case 889:  /* ussubv2uha3 */
    case 888:  /* ussubv2uhq3 */
    case 887:  /* ussubv4uqq3 */
    case 886:  /* ussubuha3 */
    case 885:  /* ussubuhq3 */
    case 884:  /* ussubuqq3 */
    case 869:  /* ssaddv2ha3 */
    case 868:  /* ssaddv2hq3 */
    case 867:  /* ssaddsa3 */
    case 866:  /* ssaddha3 */
    case 865:  /* ssaddsq3 */
    case 864:  /* ssaddhq3 */
    case 863:  /* usaddv2uha3 */
    case 862:  /* usaddv2uhq3 */
    case 861:  /* usaddv4uqq3 */
    case 860:  /* usadduha3 */
    case 859:  /* usadduhq3 */
    case 858:  /* usadduqq3 */
    case 802:  /* mips_addu_ph */
    case 718:  /* subv4qi3 */
    case 717:  /* subv2hi3 */
    case 713:  /* addv4qi3 */
    case 712:  /* addv2hi3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[0] = 2;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[1] = 1;
      break;

    case 699:  /* *branch_upper_lower_inverted */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0, 1));
      break;

    case 698:  /* *branch_upper_lower */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0, 1));
      break;

    case 697:  /* bc1any2f */
    case 696:  /* bc1any2t */
    case 695:  /* bc1any4f */
    case 694:  /* bc1any4t */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 680:  /* mips_cabs_cond_4s */
    case 679:  /* mips_c_cond_4s */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (pat, 1), 0, 3));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (pat, 1), 0, 4));
      break;

    case 670:  /* vec_extractv2sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XEXP (pat, 1), 1), 0, 0));
      break;

    case 661:  /* test_and_set_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 660:  /* sync_lock_test_and_setdi */
    case 659:  /* sync_lock_test_and_setsi */
    case 658:  /* sync_new_nanddi */
    case 657:  /* sync_new_nandsi */
    case 656:  /* sync_old_nanddi */
    case 655:  /* sync_old_nandsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 652:  /* sync_new_anddi */
    case 651:  /* sync_new_xordi */
    case 650:  /* sync_new_iordi */
    case 649:  /* sync_new_andsi */
    case 648:  /* sync_new_xorsi */
    case 647:  /* sync_new_iorsi */
    case 646:  /* sync_old_anddi */
    case 645:  /* sync_old_xordi */
    case 644:  /* sync_old_iordi */
    case 643:  /* sync_old_andsi */
    case 642:  /* sync_old_xorsi */
    case 641:  /* sync_old_iorsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 1);
      recog_data.dup_num[1] = 1;
      break;

    case 640:  /* sync_anddi */
    case 639:  /* sync_xordi */
    case 638:  /* sync_iordi */
    case 637:  /* sync_andsi */
    case 636:  /* sync_xorsi */
    case 635:  /* sync_iorsi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1);
      recog_data.dup_num[0] = 0;
      break;

    case 634:  /* sync_new_subdi */
    case 633:  /* sync_new_subsi */
    case 632:  /* sync_new_adddi */
    case 631:  /* sync_new_addsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 1);
      recog_data.dup_num[2] = 2;
      break;

    case 630:  /* sync_old_subdi */
    case 629:  /* sync_old_subsi */
    case 628:  /* sync_old_adddi */
    case 627:  /* sync_old_addsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0), 0);
      recog_data.dup_num[1] = 1;
      break;

    case 624:  /* sync_new_nand_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[1] = 4;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[4] = 1;
      break;

    case 623:  /* sync_old_nand_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 622:  /* sync_nand_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2);
      recog_data.dup_num[0] = 0;
      break;

    case 621:  /* sync_new_and_12 */
    case 620:  /* sync_new_xor_12 */
    case 619:  /* sync_new_ior_12 */
    case 618:  /* sync_new_sub_12 */
    case 617:  /* sync_new_add_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3);
      recog_data.dup_num[1] = 4;
      recog_data.dup_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2);
      recog_data.dup_num[2] = 3;
      recog_data.dup_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1);
      recog_data.dup_num[3] = 2;
      recog_data.dup_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0);
      recog_data.dup_num[4] = 1;
      recog_data.dup_loc[5] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 3), 0);
      recog_data.dup_num[5] = 0;
      break;

    case 616:  /* sync_old_and_12 */
    case 615:  /* sync_old_xor_12 */
    case 614:  /* sync_old_ior_12 */
    case 613:  /* sync_old_sub_12 */
    case 612:  /* sync_old_add_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2), 1));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2), 0);
      recog_data.dup_num[1] = 0;
      break;

    case 611:  /* sync_and_12 */
    case 610:  /* sync_xor_12 */
    case 609:  /* sync_ior_12 */
    case 608:  /* sync_sub_12 */
    case 607:  /* sync_add_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 2), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 626:  /* sync_subdi */
    case 625:  /* sync_subsi */
    case 606:  /* sync_adddi */
    case 605:  /* sync_addsi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0);
      recog_data.dup_num[0] = 0;
      break;

    case 604:  /* compare_and_swap_12 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      ro[4] = *(ro_loc[4] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 2));
      ro[5] = *(ro_loc[5] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 3));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 603:  /* sync_compare_and_swapdi */
    case 602:  /* sync_compare_and_swapsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 0));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0, 1));
      recog_data.dup_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 601:  /* *memory_barrier */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0);
      recog_data.dup_num[0] = 0;
      break;

    case 600:  /* *mips16e_save_restore */
      ro[0] = *(ro_loc[0] = &PATTERN (insn));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0);
      recog_data.dup_num[0] = 1;
      break;

    case 597:  /* consttable_int */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (pat, 0, 1));
      break;

    case 663:  /* *movcc_v2sf_di */
    case 662:  /* *movcc_v2sf_si */
    case 596:  /* *movdf_on_cc */
    case 595:  /* *movdf_on_di */
    case 594:  /* *movdf_on_si */
    case 593:  /* *movsf_on_cc */
    case 592:  /* *movsf_on_di */
    case 591:  /* *movsf_on_si */
    case 590:  /* *movdi_on_cc */
    case 589:  /* *movsi_on_cc */
    case 588:  /* *movdi_on_di */
    case 587:  /* *movsi_on_di */
    case 586:  /* *movdi_on_si */
    case 585:  /* *movsi_on_si */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      ro[4] = *(ro_loc[4] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 582:  /* *prefetch_indexed_di */
    case 581:  /* *prefetch_indexed_si */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (pat, 1));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 2));
      break;

    case 580:  /* prefetch */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      ro[2] = *(ro_loc[2] = &XEXP (pat, 2));
      break;

    case 577:  /* call_value_direct_split */
    case 576:  /* call_value_internal_direct */
    case 575:  /* call_value_split */
    case 574:  /* call_value_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      break;

    case 573:  /* call_direct_split */
    case 572:  /* call_internal_direct */
    case 571:  /* call_split */
    case 570:  /* call_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      break;

    case 579:  /* call_value_multiple_split */
    case 578:  /* call_value_multiple_internal */
    case 569:  /* sibcall_value_multiple_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 918:  /* loongson_pandn_d */
    case 917:  /* loongson_pandn_b */
    case 916:  /* loongson_pandn_h */
    case 915:  /* loongson_pandn_w */
    case 667:  /* mips_pll_ps */
    case 568:  /* sibcall_value_internal */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 567:  /* sibcall_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      break;

    case 559:  /* eh_set_lr_di */
    case 558:  /* eh_set_lr_si */
      ro[0] = *(ro_loc[0] = &XVECEXP (XVECEXP (pat, 0, 0), 0, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 560:  /* restore_gp */
    case 551:  /* return_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 548:  /* tablejumpdi */
    case 547:  /* tablejumpsi */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 0), 0));
      break;

    case 544:  /* *jump_mips16 */
    case 543:  /* *jump_pic */
    case 542:  /* *jump_absolute */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 443:  /* *branch_bit1di_inverted */
    case 442:  /* *branch_bit0di_inverted */
    case 441:  /* *branch_bit1si_inverted */
    case 440:  /* *branch_bit0si_inverted */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 2));
      break;

    case 439:  /* *branch_bit1di */
    case 438:  /* *branch_bit0di */
    case 437:  /* *branch_bit1si */
    case 436:  /* *branch_bit0si */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 2));
      break;

    case 435:  /* *branch_equalitydi_mips16 */
    case 434:  /* *branch_equalitysi_mips16 */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 433:  /* *branch_equalitydi_inverted */
    case 432:  /* *branch_equalitysi_inverted */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 431:  /* *branch_equalitydi */
    case 430:  /* *branch_equalitysi */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 429:  /* *branch_orderdi_inverted */
    case 428:  /* *branch_ordersi_inverted */
    case 425:  /* *branch_fp_inverted */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 2), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 427:  /* *branch_orderdi */
    case 426:  /* *branch_ordersi */
    case 424:  /* *branch_fp */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 777:  /* mips_cmpu_le_qb */
    case 776:  /* mips_cmp_le_ph */
    case 775:  /* mips_cmpu_lt_qb */
    case 774:  /* mips_cmp_lt_ph */
    case 773:  /* mips_cmpu_eq_qb */
    case 772:  /* mips_cmp_eq_ph */
    case 404:  /* mips_cache */
      ro[0] = *(ro_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 1));
      break;

    case 599:  /* align */
    case 598:  /* consttable_float */
    case 399:  /* synci */
      ro[0] = *(ro_loc[0] = &XVECEXP (pat, 0, 0));
      break;

    case 546:  /* indirect_jumpdi */
    case 545:  /* indirect_jumpsi */
    case 397:  /* use_cprestore */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 1));
      break;

    case 395:  /* potential_cprestore */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 943:  /* loongson_biadd */
    case 937:  /* loongson_pmovmskb */
    case 793:  /* mips_rddsp */
    case 771:  /* mips_repl_ph */
    case 770:  /* mips_repl_qb */
    case 768:  /* mips_bitrev */
    case 741:  /* mips_preceu_ph_qbra */
    case 740:  /* mips_preceu_ph_qbla */
    case 739:  /* mips_preceu_ph_qbr */
    case 738:  /* mips_preceu_ph_qbl */
    case 737:  /* mips_precequ_ph_qbra */
    case 736:  /* mips_precequ_ph_qbla */
    case 735:  /* mips_precequ_ph_qbr */
    case 734:  /* mips_precequ_ph_qbl */
    case 733:  /* mips_preceq_w_phr */
    case 732:  /* mips_preceq_w_phl */
    case 725:  /* mips_raddu_w_qb */
    case 708:  /* mips_recip1_ps */
    case 707:  /* mips_recip1_d */
    case 706:  /* mips_recip1_s */
    case 702:  /* mips_rsqrt1_ps */
    case 701:  /* mips_rsqrt1_d */
    case 700:  /* mips_rsqrt1_s */
    case 676:  /* *mips_abs_ps */
    case 674:  /* mips_cvt_ps_pw */
    case 673:  /* mips_cvt_pw_ps */
    case 654:  /* sync_nanddi */
    case 653:  /* sync_nandsi */
    case 562:  /* move_gpdi */
    case 561:  /* move_gpsi */
    case 557:  /* cop0_move */
    case 556:  /* mips_rdpgpr */
    case 396:  /* cprestore */
    case 394:  /* copygp_mips16 */
    case 390:  /* loadgp_absolute_di */
    case 389:  /* loadgp_absolute_si */
    case 386:  /* mfhc1tf */
    case 385:  /* mfhc1v8qi */
    case 384:  /* mfhc1v4hi */
    case 383:  /* mfhc1v2si */
    case 382:  /* mfhc1v2sf */
    case 381:  /* mfhc1di */
    case 380:  /* mfhc1df */
    case 358:  /* load_lowtf */
    case 357:  /* load_lowv8qi */
    case 356:  /* load_lowv4hi */
    case 355:  /* load_lowv2si */
    case 354:  /* load_lowv2sf */
    case 353:  /* load_lowdi */
    case 352:  /* load_lowdf */
    case 347:  /* mfhidi_ti */
    case 346:  /* mfhisi_ti */
    case 345:  /* mfhidi_di */
    case 344:  /* mfhisi_di */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      break;

    case 328:  /* *lwxs */
    case 327:  /* *lwxs */
    case 326:  /* *lwxs */
    case 325:  /* *lwxs */
    case 324:  /* *lwxs */
    case 323:  /* *lwxs */
    case 322:  /* *lwxs */
    case 321:  /* *lwxs */
    case 320:  /* *lwxs */
    case 319:  /* *lwxs */
    case 318:  /* *lwxs */
    case 317:  /* *lwxs */
    case 316:  /* *lwxs */
    case 315:  /* *lwxs */
    case 314:  /* *lwxs */
    case 313:  /* *lwxs */
    case 312:  /* *lwxs */
    case 311:  /* *lwxs */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 310:  /* *sdxc1_di */
    case 309:  /* *sdxc1_di */
    case 308:  /* *swxc1_di */
    case 307:  /* *sdxc1_si */
    case 306:  /* *sdxc1_si */
    case 305:  /* *swxc1_si */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 1));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 0), 0), 1));
      break;

    case 401:  /* rdhwr_synci_step_di */
    case 400:  /* rdhwr_synci_step_si */
    case 275:  /* *movdi_ra */
    case 274:  /* *movsi_ra */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      break;

    case 903:  /* movv8qi_internal */
    case 902:  /* movv4hi_internal */
    case 901:  /* movv2si_internal */
    case 343:  /* *movv2sf */
    case 342:  /* *movtf_mips16 */
    case 341:  /* *movtf */
    case 340:  /* *movti_mips16 */
    case 339:  /* *movti */
    case 338:  /* *movdf_mips16 */
    case 337:  /* *movdf_softfloat */
    case 336:  /* *movdf_hardfloat */
    case 335:  /* *movsf_mips16 */
    case 334:  /* *movsf_softfloat */
    case 333:  /* *movsf_hardfloat */
    case 332:  /* *movqi_mips16 */
    case 331:  /* *movqi_internal */
    case 330:  /* *movhi_mips16 */
    case 329:  /* *movhi_internal */
    case 298:  /* movcc */
    case 297:  /* *movv4uqq_mips16 */
    case 296:  /* *movv4qq_mips16 */
    case 295:  /* *movv2uha_mips16 */
    case 294:  /* *movv2ha_mips16 */
    case 293:  /* *movv2uhq_mips16 */
    case 292:  /* *movv2hq_mips16 */
    case 291:  /* *movv4qi_mips16 */
    case 290:  /* *movv2hi_mips16 */
    case 289:  /* *movsi_mips16 */
    case 288:  /* *movv4uqq_internal */
    case 287:  /* *movv4qq_internal */
    case 286:  /* *movv2uha_internal */
    case 285:  /* *movv2ha_internal */
    case 284:  /* *movv2uhq_internal */
    case 283:  /* *movv2hq_internal */
    case 282:  /* *movv4qi_internal */
    case 281:  /* *movv2hi_internal */
    case 280:  /* *movsi_internal */
    case 279:  /* *movdi_64bit_mips16 */
    case 278:  /* *movdi_64bit */
    case 277:  /* *movdi_32bit_mips16 */
    case 276:  /* *movdi_32bit */
    case 265:  /* *got_dispdi */
    case 264:  /* *got_dispsi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (pat, 1));
      break;

    case 259:  /* *lea64 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (pat, 0, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 257:  /* mov_sdr */
    case 256:  /* mov_swr */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      recog_data.dup_loc[0] = &XVECEXP (XEXP (pat, 1), 0, 2);
      recog_data.dup_num[0] = 0;
      break;

    case 945:  /* loongson_pshufh */
    case 839:  /* mips_dpsx_w_ph */
    case 838:  /* mips_dpax_w_ph */
    case 822:  /* mips_prepend */
    case 821:  /* mips_precr_sra_r_ph_w */
    case 820:  /* mips_precr_sra_ph_w */
    case 818:  /* mips_mulsa_w_ph */
    case 812:  /* mips_dps_w_ph */
    case 811:  /* mips_dpa_w_ph */
    case 807:  /* mips_balign */
    case 806:  /* mips_append */
    case 758:  /* mips_dpsu_h_qbr */
    case 757:  /* mips_dpsu_h_qbl */
    case 756:  /* mips_dpau_h_qbr */
    case 755:  /* mips_dpau_h_qbl */
    case 682:  /* mips_cabs_cond_ps */
    case 681:  /* mips_c_cond_ps */
    case 678:  /* mips_cabs_cond_d */
    case 677:  /* mips_cabs_cond_s */
    case 671:  /* mips_alnv_ps */
    case 664:  /* mips_cond_move_tf_ps */
    case 253:  /* mov_ldr */
    case 252:  /* mov_lwr */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      ro[3] = *(ro_loc[3] = &XVECEXP (XEXP (pat, 1), 0, 2));
      break;

    case 965:  /* vec_interleave_lowv8qi */
    case 964:  /* vec_interleave_lowv4hi */
    case 963:  /* vec_interleave_lowv2si */
    case 962:  /* vec_interleave_highv8qi */
    case 961:  /* vec_interleave_highv4hi */
    case 960:  /* vec_interleave_highv2si */
    case 955:  /* loongson_psubd */
    case 944:  /* loongson_psadbh */
    case 942:  /* loongson_pasubub */
    case 941:  /* loongson_pmuluw */
    case 939:  /* smulv4hi3_highpart */
    case 938:  /* umulv4hi3_highpart */
    case 932:  /* loongson_pmaddhw */
    case 931:  /* loongson_pinsrh_3 */
    case 930:  /* loongson_pinsrh_2 */
    case 929:  /* loongson_pinsrh_1 */
    case 928:  /* loongson_pinsrh_0 */
    case 927:  /* loongson_pextrh */
    case 926:  /* loongson_pcmpgtb */
    case 925:  /* loongson_pcmpgth */
    case 924:  /* loongson_pcmpgtw */
    case 923:  /* loongson_pcmpeqb */
    case 922:  /* loongson_pcmpeqh */
    case 921:  /* loongson_pcmpeqw */
    case 920:  /* loongson_pavgb */
    case 919:  /* loongson_pavgh */
    case 910:  /* loongson_paddd */
    case 837:  /* mips_subqh_r_w */
    case 836:  /* mips_subqh_w */
    case 835:  /* mips_subqh_r_ph */
    case 834:  /* mips_subqh_ph */
    case 833:  /* mips_addqh_r_w */
    case 832:  /* mips_addqh_w */
    case 831:  /* mips_addqh_r_ph */
    case 830:  /* mips_addqh_ph */
    case 829:  /* mips_subuh_r_qb */
    case 828:  /* mips_subuh_qb */
    case 825:  /* mips_shrl_ph */
    case 824:  /* mips_shra_r_qb */
    case 823:  /* mips_shra_qb */
    case 819:  /* mips_precr_qb_ph */
    case 805:  /* mips_adduh_r_qb */
    case 804:  /* mips_adduh_qb */
    case 790:  /* mips_shilo */
    case 783:  /* mips_packrl_ph */
    case 782:  /* mips_pick_qb */
    case 781:  /* mips_pick_ph */
    case 780:  /* mips_cmpgu_le_qb */
    case 779:  /* mips_cmpgu_lt_qb */
    case 778:  /* mips_cmpgu_eq_qb */
    case 769:  /* mips_insv */
    case 749:  /* mips_shra_r_ph */
    case 748:  /* mips_shra_r_w */
    case 747:  /* mips_shra_ph */
    case 746:  /* mips_shrl_qb */
    case 729:  /* mips_precrq_ph_w */
    case 728:  /* mips_precrq_qb_ph */
    case 724:  /* mips_modsub */
    case 711:  /* mips_recip2_ps */
    case 710:  /* mips_recip2_d */
    case 709:  /* mips_recip2_s */
    case 705:  /* mips_rsqrt2_ps */
    case 704:  /* mips_rsqrt2_d */
    case 703:  /* mips_rsqrt2_s */
    case 675:  /* mips_mulr_ps */
    case 672:  /* mips_addr_ps */
    case 564:  /* load_calldi */
    case 563:  /* load_callsi */
    case 393:  /* loadgp_rtp_di */
    case 392:  /* loadgp_rtp_si */
    case 388:  /* loadgp_newabi_di */
    case 387:  /* loadgp_newabi_si */
    case 379:  /* mthc1tf */
    case 378:  /* mthc1v8qi */
    case 377:  /* mthc1v4hi */
    case 376:  /* mthc1v2si */
    case 375:  /* mthc1v2sf */
    case 374:  /* mthc1di */
    case 373:  /* mthc1df */
    case 372:  /* store_wordtf */
    case 371:  /* store_wordv8qi */
    case 370:  /* store_wordv4hi */
    case 369:  /* store_wordv2si */
    case 368:  /* store_wordv2sf */
    case 367:  /* store_worddi */
    case 366:  /* store_worddf */
    case 365:  /* load_hightf */
    case 364:  /* load_highv8qi */
    case 363:  /* load_highv4hi */
    case 362:  /* load_highv2si */
    case 361:  /* load_highv2sf */
    case 360:  /* load_highdi */
    case 359:  /* load_highdf */
    case 351:  /* mthidi_ti */
    case 350:  /* mthisi_ti */
    case 349:  /* mthidi_di */
    case 348:  /* mthisi_di */
    case 269:  /* load_gotdi */
    case 268:  /* load_gotsi */
    case 255:  /* mov_sdl */
    case 254:  /* mov_swl */
    case 251:  /* mov_ldl */
    case 250:  /* mov_lwl */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XVECEXP (XEXP (pat, 1), 0, 0));
      ro[2] = *(ro_loc[2] = &XVECEXP (XEXP (pat, 1), 0, 1));
      break;

    case 247:  /* insvdi */
    case 246:  /* insvsi */
      ro[0] = *(ro_loc[0] = &XEXP (XEXP (pat, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 0), 2));
      ro[3] = *(ro_loc[3] = &XEXP (pat, 1));
      break;

    case 245:  /* *extzv_truncsi_exts */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 2));
      break;

    case 244:  /* extzvdi */
    case 243:  /* extzvsi */
    case 242:  /* extvdi */
    case 241:  /* extvsi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 2));
      break;

    case 234:  /* fix_truncsfsi2_macro */
    case 232:  /* fix_truncdfsi2_macro */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 229:  /* *extendhi_truncateqi_exts */
    case 228:  /* *extenddi_truncatehi_exts */
    case 227:  /* *extendsi_truncatehi_exts */
    case 226:  /* *extenddi_truncateqi_exts */
    case 225:  /* *extendsi_truncateqi_exts */
    case 224:  /* *extendhi_truncateqi */
    case 223:  /* *extendsi_truncatehi */
    case 222:  /* *extendsi_truncateqi */
    case 221:  /* *extenddi_truncatehi */
    case 220:  /* *extenddi_truncateqi */
    case 203:  /* *zero_extendhi_truncqi */
    case 202:  /* *zero_extenddi_trunchi */
    case 201:  /* *zero_extendsi_trunchi */
    case 200:  /* *zero_extenddi_truncqi */
    case 199:  /* *zero_extendsi_truncqi */
    case 176:  /* *lshr32_truncsi */
    case 175:  /* *lshr32_trunchi */
    case 174:  /* *lshr32_truncqi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      break;

    case 666:  /* mips_puu_ps */
    case 135:  /* *rsqrtv2sfa */
    case 134:  /* *rsqrtdfa */
    case 133:  /* *rsqrtsfa */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      break;

    case 487:  /* *sgeu_didi */
    case 486:  /* *sge_didi */
    case 485:  /* *sgeu_sidi */
    case 484:  /* *sge_sidi */
    case 483:  /* *sgeu_disi */
    case 482:  /* *sge_disi */
    case 481:  /* *sgeu_sisi */
    case 480:  /* *sge_sisi */
    case 459:  /* *sne_zero_didi */
    case 458:  /* *sne_zero_sidi */
    case 457:  /* *sne_zero_disi */
    case 456:  /* *sne_zero_sisi */
    case 451:  /* *seq_zero_didi_mips16 */
    case 450:  /* *seq_zero_sidi_mips16 */
    case 449:  /* *seq_zero_disi_mips16 */
    case 448:  /* *seq_zero_sisi_mips16 */
    case 447:  /* *seq_zero_didi */
    case 446:  /* *seq_zero_sidi */
    case 445:  /* *seq_zero_disi */
    case 444:  /* *seq_zero_sisi */
    case 267:  /* *got_pagedi */
    case 266:  /* *got_pagesi */
    case 261:  /* *xgot_hidi */
    case 260:  /* *xgot_hisi */
    case 258:  /* *lea_high64 */
    case 240:  /* floatdisf2 */
    case 239:  /* floatsisf2 */
    case 238:  /* floatdidf2 */
    case 237:  /* floatsidf2 */
    case 236:  /* fix_truncsfdi2 */
    case 235:  /* fix_truncdfdi2 */
    case 233:  /* fix_truncsfsi2_insn */
    case 231:  /* fix_truncdfsi2_insn */
    case 230:  /* extendsfdf2 */
    case 219:  /* *extendqihi2_seb */
    case 218:  /* *extendqihi2 */
    case 217:  /* *extendqihi2_mips16e */
    case 216:  /* *extendhidi2_seh */
    case 215:  /* *extendhisi2_seh */
    case 214:  /* *extendqidi2_seb */
    case 213:  /* *extendqisi2_seb */
    case 212:  /* *extendhidi2 */
    case 211:  /* *extendhisi2 */
    case 210:  /* *extendqidi2 */
    case 209:  /* *extendqisi2 */
    case 208:  /* *extendhidi2_mips16e */
    case 207:  /* *extendhisi2_mips16e */
    case 206:  /* *extendqidi2_mips16e */
    case 205:  /* *extendqisi2_mips16e */
    case 204:  /* extendsidi2 */
    case 198:  /* *zero_extendqihi2_mips16 */
    case 197:  /* *zero_extendqihi2 */
    case 196:  /* *zero_extendhidi2_mips16 */
    case 195:  /* *zero_extendhisi2_mips16 */
    case 194:  /* *zero_extendqidi2_mips16 */
    case 193:  /* *zero_extendqisi2_mips16 */
    case 192:  /* *zero_extendhidi2_mips16e */
    case 191:  /* *zero_extendhisi2_mips16e */
    case 190:  /* *zero_extendqidi2_mips16e */
    case 189:  /* *zero_extendqisi2_mips16e */
    case 188:  /* *zero_extendhidi2 */
    case 187:  /* *zero_extendhisi2 */
    case 186:  /* *zero_extendqidi2 */
    case 185:  /* *zero_extendqisi2 */
    case 184:  /* *zero_extendsidi2_dext */
    case 183:  /* *zero_extendsidi2 */
    case 170:  /* truncdisi2 */
    case 169:  /* truncdihi2 */
    case 168:  /* truncdiqi2 */
    case 167:  /* truncdfsf2 */
    case 152:  /* one_cmpldi2 */
    case 151:  /* one_cmplsi2 */
    case 150:  /* negv2sf2 */
    case 149:  /* negdf2 */
    case 148:  /* negsf2 */
    case 147:  /* negdi2 */
    case 146:  /* negsi2 */
    case 145:  /* popcountdi2 */
    case 144:  /* popcountsi2 */
    case 143:  /* clzdi2 */
    case 142:  /* clzsi2 */
    case 141:  /* absv2sf2 */
    case 140:  /* absdf2 */
    case 139:  /* abssf2 */
    case 132:  /* sqrtv2sf2 */
    case 131:  /* sqrtdf2 */
    case 130:  /* sqrtsf2 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 693:  /* sungt_ps */
    case 692:  /* sunge_ps */
    case 691:  /* sgt_ps */
    case 690:  /* sge_ps */
    case 689:  /* sle_ps */
    case 688:  /* slt_ps */
    case 687:  /* seq_ps */
    case 686:  /* sunle_ps */
    case 685:  /* sunlt_ps */
    case 684:  /* suneq_ps */
    case 683:  /* sunordered_ps */
    case 129:  /* udivmoddi4_hilo_ti */
    case 128:  /* divmoddi4_hilo_ti */
    case 127:  /* udivmodsi4_hilo_ti */
    case 126:  /* divmodsi4_hilo_ti */
    case 125:  /* udivmoddi4_hilo_di */
    case 124:  /* divmoddi4_hilo_di */
    case 123:  /* udivmodsi4_hilo_di */
    case 122:  /* divmodsi4_hilo_di */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1));
      break;

    case 121:  /* udivmoddi4 */
    case 120:  /* udivmodsi4 */
    case 119:  /* divmoddi4 */
    case 118:  /* divmodsi4 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[1] = 2;
      break;

    case 111:  /* *nmsub3v2sf_fastmath */
    case 110:  /* *nmsub3df_fastmath */
    case 109:  /* *nmsub3sf_fastmath */
    case 108:  /* *nmsub4v2sf_fastmath */
    case 107:  /* *nmsub4df_fastmath */
    case 106:  /* *nmsub4sf_fastmath */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 1), 1));
      break;

    case 105:  /* *nmsub3v2sf */
    case 104:  /* *nmsub3df */
    case 103:  /* *nmsub3sf */
    case 102:  /* *nmsub4v2sf */
    case 101:  /* *nmsub4df */
    case 100:  /* *nmsub4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      break;

    case 99:  /* *nmadd3v2sf_fastmath */
    case 98:  /* *nmadd3df_fastmath */
    case 97:  /* *nmadd3sf_fastmath */
    case 96:  /* *nmadd4v2sf_fastmath */
    case 95:  /* *nmadd4df_fastmath */
    case 94:  /* *nmadd4sf_fastmath */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 93:  /* *nmadd3v2sf */
    case 92:  /* *nmadd3df */
    case 91:  /* *nmadd3sf */
    case 90:  /* *nmadd4v2sf */
    case 89:  /* *nmadd4df */
    case 88:  /* *nmadd4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 249:  /* *cinsdi */
    case 248:  /* *cinssi */
    case 87:  /* *msub3v2sf */
    case 86:  /* *msub3df */
    case 85:  /* *msub3sf */
    case 84:  /* *msub4v2sf */
    case 83:  /* *msub4df */
    case 82:  /* *msub4sf */
    case 81:  /* *madd3v2sf */
    case 80:  /* *madd3df */
    case 79:  /* *madd3sf */
    case 78:  /* *madd4v2sf */
    case 77:  /* *madd4df */
    case 76:  /* *madd4sf */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 75:  /* umaddsidi4 */
    case 74:  /* maddsidi4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 73:  /* madsi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      recog_data.dup_loc[0] = &XEXP (XEXP (pat, 1), 1);
      recog_data.dup_num[0] = 0;
      break;

    case 66:  /* *umulsi3_highpart_neg_mulhi_internal */
    case 65:  /* *smulsi3_highpart_neg_mulhi_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 68:  /* umuldi3_highpart */
    case 67:  /* smuldi3_highpart */
    case 64:  /* umulsi3_highpart_mulhi_internal */
    case 63:  /* smulsi3_highpart_mulhi_internal */
    case 62:  /* umulsi3_highpart_internal */
    case 61:  /* smulsi3_highpart_internal */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 60:  /* umsubsidi4 */
    case 59:  /* msubsidi4 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (pat, 1), 0));
      break;

    case 58:  /* *mulsu_di */
    case 57:  /* *muls_di */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 1), 0));
      break;

    case 55:  /* umulsidi3_64bit_hilo */
    case 54:  /* mulsidi3_64bit_hilo */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (XEXP (pat, 1), 0, 0), 1), 0));
      break;

    case 53:  /* umulsidi3_64bit */
    case 52:  /* mulsidi3_64bit */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 72:  /* umulditi3_r4000 */
    case 71:  /* mulditi3_r4000 */
    case 56:  /* mulsidi3_64bit_dmul */
    case 51:  /* umulsidi3_32bit_r4000 */
    case 50:  /* mulsidi3_32bit_r4000 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 906:  /* vec_pack_usat_v4hi */
    case 905:  /* vec_pack_ssat_v4hi */
    case 904:  /* vec_pack_ssat_v2si */
    case 668:  /* mips_plu_ps */
    case 166:  /* *nordi3 */
    case 165:  /* *norsi3 */
    case 70:  /* umulditi3_internal */
    case 69:  /* mulditi3_internal */
    case 49:  /* umulsidi3_32bit */
    case 48:  /* mulsidi3_32bit */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 1), 0));
      break;

    case 47:  /* *muls */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 45:  /* *msac2 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0);
      recog_data.dup_num[0] = 0;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1), 0);
      recog_data.dup_num[1] = 1;
      recog_data.dup_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1), 1);
      recog_data.dup_num[2] = 2;
      recog_data.dup_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0);
      recog_data.dup_num[3] = 0;
      break;

    case 44:  /* *macc2 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      recog_data.dup_loc[0] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 0);
      recog_data.dup_num[0] = 1;
      recog_data.dup_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 0), 1);
      recog_data.dup_num[1] = 2;
      recog_data.dup_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 1), 1), 1);
      recog_data.dup_num[2] = 0;
      recog_data.dup_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1);
      recog_data.dup_num[3] = 0;
      break;

    case 46:  /* *mul_sub_si */
    case 43:  /* *msac_using_macc */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 42:  /* *msac */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 0));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 41:  /* *macc */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 40:  /* *mul_acc_si_r3900 */
    case 39:  /* *mul_acc_si */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[4] = *(ro_loc[4] = &XEXP (XVECEXP (pat, 0, 1), 0));
      ro[5] = *(ro_loc[5] = &XEXP (XVECEXP (pat, 0, 2), 0));
      break;

    case 38:  /* muldi3_r4000 */
    case 37:  /* mulsi3_r4000 */
    case 34:  /* muldi3_mul3 */
    case 33:  /* mulsi3_mul3 */
      ro[0] = *(ro_loc[0] = &XEXP (XVECEXP (pat, 0, 0), 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XVECEXP (pat, 0, 0), 1), 1));
      ro[3] = *(ro_loc[3] = &XEXP (XVECEXP (pat, 0, 1), 0));
      break;

    case 797:  /* mips_lhx_di */
    case 796:  /* mips_lhx_si */
    case 795:  /* mips_lbux_di */
    case 794:  /* mips_lbux_si */
    case 19:  /* *baddu_didi */
    case 18:  /* *baddu_disi */
    case 17:  /* *baddu_si_el */
    case 16:  /* *baddu_si_eb */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (XEXP (pat, 1), 0), 0), 1));
      break;

    case 799:  /* mips_lwx_di */
    case 798:  /* mips_lwx_si */
    case 414:  /* *lshrsi3_extend */
    case 413:  /* *ashrsi3_extend */
    case 412:  /* *ashlsi3_extend */
    case 304:  /* *ldxc1_di */
    case 303:  /* *ldxc1_di */
    case 302:  /* *lwxc1_di */
    case 301:  /* *ldxc1_si */
    case 300:  /* *ldxc1_si */
    case 299:  /* *lwxc1_si */
    case 182:  /* *lshr_truncsi_exts */
    case 181:  /* *ashr_truncsi_exts */
    case 180:  /* *lshr_trunchi_exts */
    case 179:  /* *ashr_trunchi_exts */
    case 178:  /* *lshr_truncqi_exts */
    case 177:  /* *ashr_truncqi_exts */
    case 173:  /* *ashr_truncsi */
    case 172:  /* *ashr_trunchi */
    case 171:  /* *ashr_truncqi */
    case 138:  /* *rsqrtv2sfb */
    case 137:  /* *rsqrtdfb */
    case 136:  /* *rsqrtsfb */
    case 25:  /* *subsi3_extended */
    case 15:  /* *addsi3_extended_mips16 */
    case 14:  /* *addsi3_extended */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (XEXP (pat, 1), 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (XEXP (pat, 1), 0), 1));
      break;

    case 973:  /* umoddi3 */
    case 972:  /* moddi3 */
    case 971:  /* umodsi3 */
    case 970:  /* modsi3 */
    case 969:  /* udivdi3 */
    case 968:  /* divdi3 */
    case 967:  /* udivsi3 */
    case 966:  /* divsi3 */
    case 959:  /* ussubv8qi3 */
    case 958:  /* ussubv4hi3 */
    case 957:  /* sssubv8qi3 */
    case 956:  /* sssubv4hi3 */
    case 954:  /* subv8qi3 */
    case 953:  /* subv4hi3 */
    case 952:  /* subv2si3 */
    case 951:  /* lshrv4hi3 */
    case 950:  /* lshrv2si3 */
    case 949:  /* ashrv4hi3 */
    case 948:  /* ashrv2si3 */
    case 947:  /* ashlv4hi3 */
    case 946:  /* ashlv2si3 */
    case 940:  /* mulv4hi3 */
    case 936:  /* uminv8qi3 */
    case 935:  /* sminv4hi3 */
    case 934:  /* umaxv8qi3 */
    case 933:  /* smaxv4hi3 */
    case 914:  /* usaddv8qi3 */
    case 913:  /* usaddv4hi3 */
    case 912:  /* ssaddv8qi3 */
    case 911:  /* ssaddv4hi3 */
    case 909:  /* addv8qi3 */
    case 908:  /* addv4hi3 */
    case 907:  /* addv2si3 */
    case 883:  /* subuda3 */
    case 882:  /* subusa3 */
    case 881:  /* subuha3 */
    case 880:  /* subda3 */
    case 879:  /* subsa3 */
    case 878:  /* subha3 */
    case 877:  /* subudq3 */
    case 876:  /* subusq3 */
    case 875:  /* subuhq3 */
    case 874:  /* subuqq3 */
    case 873:  /* subdq3 */
    case 872:  /* subsq3 */
    case 871:  /* subhq3 */
    case 870:  /* subqq3 */
    case 857:  /* adduda3 */
    case 856:  /* addusa3 */
    case 855:  /* adduha3 */
    case 854:  /* addda3 */
    case 853:  /* addsa3 */
    case 852:  /* addha3 */
    case 851:  /* addudq3 */
    case 850:  /* addusq3 */
    case 849:  /* adduhq3 */
    case 848:  /* adduqq3 */
    case 847:  /* adddq3 */
    case 846:  /* addsq3 */
    case 845:  /* addhq3 */
    case 844:  /* addqq3 */
    case 669:  /* vec_initv2sf_internal */
    case 665:  /* mips_pul_ps */
    case 541:  /* sungt_df */
    case 540:  /* sunge_df */
    case 539:  /* sgt_df */
    case 538:  /* sge_df */
    case 537:  /* sungt_sf */
    case 536:  /* sunge_sf */
    case 535:  /* sgt_sf */
    case 534:  /* sge_sf */
    case 533:  /* sle_df */
    case 532:  /* slt_df */
    case 531:  /* seq_df */
    case 530:  /* sunle_df */
    case 529:  /* sunlt_df */
    case 528:  /* suneq_df */
    case 527:  /* sunordered_df */
    case 526:  /* sle_sf */
    case 525:  /* slt_sf */
    case 524:  /* seq_sf */
    case 523:  /* sunle_sf */
    case 522:  /* sunlt_sf */
    case 521:  /* suneq_sf */
    case 520:  /* sunordered_sf */
    case 519:  /* *sleu_didi_mips16 */
    case 518:  /* *sle_didi_mips16 */
    case 517:  /* *sleu_sidi_mips16 */
    case 516:  /* *sle_sidi_mips16 */
    case 515:  /* *sleu_disi_mips16 */
    case 514:  /* *sle_disi_mips16 */
    case 513:  /* *sleu_sisi_mips16 */
    case 512:  /* *sle_sisi_mips16 */
    case 511:  /* *sleu_didi */
    case 510:  /* *sle_didi */
    case 509:  /* *sleu_sidi */
    case 508:  /* *sle_sidi */
    case 507:  /* *sleu_disi */
    case 506:  /* *sle_disi */
    case 505:  /* *sleu_sisi */
    case 504:  /* *sle_sisi */
    case 503:  /* *sltu_didi_mips16 */
    case 502:  /* *slt_didi_mips16 */
    case 501:  /* *sltu_sidi_mips16 */
    case 500:  /* *slt_sidi_mips16 */
    case 499:  /* *sltu_disi_mips16 */
    case 498:  /* *slt_disi_mips16 */
    case 497:  /* *sltu_sisi_mips16 */
    case 496:  /* *slt_sisi_mips16 */
    case 495:  /* *sltu_didi */
    case 494:  /* *slt_didi */
    case 493:  /* *sltu_sidi */
    case 492:  /* *slt_sidi */
    case 491:  /* *sltu_disi */
    case 490:  /* *slt_disi */
    case 489:  /* *sltu_sisi */
    case 488:  /* *slt_sisi */
    case 479:  /* *sgtu_didi_mips16 */
    case 478:  /* *sgt_didi_mips16 */
    case 477:  /* *sgtu_sidi_mips16 */
    case 476:  /* *sgt_sidi_mips16 */
    case 475:  /* *sgtu_disi_mips16 */
    case 474:  /* *sgt_disi_mips16 */
    case 473:  /* *sgtu_sisi_mips16 */
    case 472:  /* *sgt_sisi_mips16 */
    case 471:  /* *sgtu_didi */
    case 470:  /* *sgt_didi */
    case 469:  /* *sgtu_sidi */
    case 468:  /* *sgt_sidi */
    case 467:  /* *sgtu_disi */
    case 466:  /* *sgt_disi */
    case 465:  /* *sgtu_sisi */
    case 464:  /* *sgt_sisi */
    case 463:  /* *sne_didi_sne */
    case 462:  /* *sne_sidi_sne */
    case 461:  /* *sne_disi_sne */
    case 460:  /* *sne_sisi_sne */
    case 455:  /* *seq_didi_seq */
    case 454:  /* *seq_sidi_seq */
    case 453:  /* *seq_disi_seq */
    case 452:  /* *seq_sisi_seq */
    case 423:  /* rotrdi3 */
    case 422:  /* rotrsi3 */
    case 421:  /* *mips.md:5099 */
    case 420:  /* *lshrdi3_mips16 */
    case 419:  /* *ashrdi3_mips16 */
    case 418:  /* *ashldi3_mips16 */
    case 417:  /* *lshrsi3_mips16 */
    case 416:  /* *ashrsi3_mips16 */
    case 415:  /* *ashlsi3_mips16 */
    case 411:  /* *lshrdi3 */
    case 410:  /* *ashrdi3 */
    case 409:  /* *ashldi3 */
    case 408:  /* *lshrsi3 */
    case 407:  /* *ashrsi3 */
    case 406:  /* *ashlsi3 */
    case 273:  /* *lowdi_mips16 */
    case 272:  /* *lowsi_mips16 */
    case 271:  /* *lowdi */
    case 270:  /* *lowsi */
    case 263:  /* *xgot_lodi */
    case 262:  /* *xgot_losi */
    case 164:  /* *mips.md:2702 */
    case 163:  /* *mips.md:2702 */
    case 162:  /* *mips.md:2691 */
    case 161:  /* *mips.md:2691 */
    case 160:  /* *iordi3_mips16 */
    case 159:  /* *iorsi3_mips16 */
    case 158:  /* *iordi3 */
    case 157:  /* *iorsi3 */
    case 156:  /* *anddi3_mips16 */
    case 155:  /* *andsi3_mips16 */
    case 154:  /* *anddi3 */
    case 153:  /* *andsi3 */
    case 117:  /* *recipv2sf3 */
    case 116:  /* *recipdf3 */
    case 115:  /* *recipsf3 */
    case 114:  /* *divv2sf3 */
    case 113:  /* *divdf3 */
    case 112:  /* *divsf3 */
    case 36:  /* muldi3_internal */
    case 35:  /* mulsi3_internal */
    case 32:  /* muldi3_mul3_loongson */
    case 31:  /* mulsi3_mul3_loongson */
    case 30:  /* mulv2sf3 */
    case 29:  /* *muldf3_r4300 */
    case 28:  /* *mulsf3_r4300 */
    case 27:  /* *muldf3 */
    case 26:  /* *mulsf3 */
    case 24:  /* subdi3 */
    case 23:  /* subsi3 */
    case 22:  /* subv2sf3 */
    case 21:  /* subdf3 */
    case 20:  /* subsf3 */
    case 13:  /* *adddi3_mips16 */
    case 12:  /* *addsi3_mips16 */
    case 11:  /* *adddi3 */
    case 10:  /* *addsi3 */
    case 9:  /* addv2sf3 */
    case 8:  /* adddf3 */
    case 7:  /* addsf3 */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 1), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 1), 1));
      break;

    case 6:  /* *conditional_trapdi */
    case 5:  /* *conditional_trapsi */
      ro[0] = *(ro_loc[0] = &XEXP (pat, 0));
      ro[1] = *(ro_loc[1] = &XEXP (XEXP (pat, 0), 0));
      ro[2] = *(ro_loc[2] = &XEXP (XEXP (pat, 0), 1));
      break;

    case 584:  /* hazard_nop */
    case 583:  /* nop */
    case 566:  /* update_got_version */
    case 565:  /* set_got_version */
    case 555:  /* mips_ehb */
    case 554:  /* mips_di */
    case 553:  /* mips_deret */
    case 552:  /* mips_eret */
    case 550:  /* *return */
    case 549:  /* blockage */
    case 405:  /* r10k_cache_barrier */
    case 403:  /* clear_hazard_di */
    case 402:  /* clear_hazard_si */
    case 398:  /* sync */
    case 391:  /* loadgp_blockage */
    case 4:  /* trap */
    case 3:  /* ls2_falu2_turn_enabled_insn */
    case 2:  /* ls2_falu1_turn_enabled_insn */
    case 1:  /* ls2_alu2_turn_enabled_insn */
    case 0:  /* ls2_alu1_turn_enabled_insn */
      break;

    }
}
