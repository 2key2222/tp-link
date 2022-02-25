/* Generated automatically by the program `genopinit'
from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tm_p.h"
#include "flags.h"
#include "insn-config.h"
#include "recog.h"
#include "expr.h"
#include "optabs.h"
#include "reload.h"

void
init_all_optabs (void)
{
#ifdef FIXUNS_TRUNC_LIKE_FIX_TRUNC
  int i, j;
#endif

  if (HAVE_addsf3)
    set_optab_handler (addv_optab, SFmode, CODE_FOR_addsf3),
    set_optab_handler (add_optab, SFmode, CODE_FOR_addsf3);
  if (HAVE_adddf3)
    set_optab_handler (addv_optab, DFmode, CODE_FOR_adddf3),
    set_optab_handler (add_optab, DFmode, CODE_FOR_adddf3);
  if (HAVE_addv2sf3)
    set_optab_handler (addv_optab, V2SFmode, CODE_FOR_addv2sf3),
    set_optab_handler (add_optab, V2SFmode, CODE_FOR_addv2sf3);
  if (HAVE_subsf3)
    set_optab_handler (subv_optab, SFmode, CODE_FOR_subsf3),
    set_optab_handler (sub_optab, SFmode, CODE_FOR_subsf3);
  if (HAVE_subdf3)
    set_optab_handler (subv_optab, DFmode, CODE_FOR_subdf3),
    set_optab_handler (sub_optab, DFmode, CODE_FOR_subdf3);
  if (HAVE_subv2sf3)
    set_optab_handler (subv_optab, V2SFmode, CODE_FOR_subv2sf3),
    set_optab_handler (sub_optab, V2SFmode, CODE_FOR_subv2sf3);
  set_optab_handler (sub_optab, SImode, CODE_FOR_subsi3);
  if (HAVE_subdi3)
    set_optab_handler (sub_optab, DImode, CODE_FOR_subdi3);
  if (HAVE_mulv2sf3)
    set_optab_handler (smulv_optab, V2SFmode, CODE_FOR_mulv2sf3),
    set_optab_handler (smul_optab, V2SFmode, CODE_FOR_mulv2sf3);
  if (HAVE_msubsidi4)
    set_widening_optab_handler (smsub_widen_optab, DImode, SImode, CODE_FOR_msubsidi4);
  if (HAVE_umsubsidi4)
    set_widening_optab_handler (umsub_widen_optab, DImode, SImode, CODE_FOR_umsubsidi4);
  if (HAVE_smuldi3_highpart)
    set_optab_handler (smul_highpart_optab, DImode, CODE_FOR_smuldi3_highpart);
  if (HAVE_umuldi3_highpart)
    set_optab_handler (umul_highpart_optab, DImode, CODE_FOR_umuldi3_highpart);
  if (HAVE_maddsidi4)
    set_widening_optab_handler (smadd_widen_optab, DImode, SImode, CODE_FOR_maddsidi4);
  if (HAVE_umaddsidi4)
    set_widening_optab_handler (umadd_widen_optab, DImode, SImode, CODE_FOR_umaddsidi4);
  if (HAVE_divmodsi4)
    set_optab_handler (sdivmod_optab, SImode, CODE_FOR_divmodsi4);
  if (HAVE_divmoddi4)
    set_optab_handler (sdivmod_optab, DImode, CODE_FOR_divmoddi4);
  set_optab_handler (udivmod_optab, SImode, CODE_FOR_udivmodsi4);
  if (HAVE_udivmoddi4)
    set_optab_handler (udivmod_optab, DImode, CODE_FOR_udivmoddi4);
  if (HAVE_sqrtsf2)
    set_optab_handler (sqrt_optab, SFmode, CODE_FOR_sqrtsf2);
  if (HAVE_sqrtdf2)
    set_optab_handler (sqrt_optab, DFmode, CODE_FOR_sqrtdf2);
  if (HAVE_sqrtv2sf2)
    set_optab_handler (sqrt_optab, V2SFmode, CODE_FOR_sqrtv2sf2);
  if (HAVE_abssf2)
    set_optab_handler (absv_optab, SFmode, CODE_FOR_abssf2),
    set_optab_handler (abs_optab, SFmode, CODE_FOR_abssf2);
  if (HAVE_absdf2)
    set_optab_handler (absv_optab, DFmode, CODE_FOR_absdf2),
    set_optab_handler (abs_optab, DFmode, CODE_FOR_absdf2);
  if (HAVE_absv2sf2)
    set_optab_handler (absv_optab, V2SFmode, CODE_FOR_absv2sf2),
    set_optab_handler (abs_optab, V2SFmode, CODE_FOR_absv2sf2);
  if (HAVE_clzsi2)
    set_optab_handler (clz_optab, SImode, CODE_FOR_clzsi2);
  if (HAVE_clzdi2)
    set_optab_handler (clz_optab, DImode, CODE_FOR_clzdi2);
  if (HAVE_popcountsi2)
    set_optab_handler (popcount_optab, SImode, CODE_FOR_popcountsi2);
  if (HAVE_popcountdi2)
    set_optab_handler (popcount_optab, DImode, CODE_FOR_popcountdi2);
  set_optab_handler (neg_optab, SImode, CODE_FOR_negsi2);
  if (HAVE_negdi2)
    set_optab_handler (neg_optab, DImode, CODE_FOR_negdi2);
  if (HAVE_negsf2)
    set_optab_handler (negv_optab, SFmode, CODE_FOR_negsf2),
    set_optab_handler (neg_optab, SFmode, CODE_FOR_negsf2);
  if (HAVE_negdf2)
    set_optab_handler (negv_optab, DFmode, CODE_FOR_negdf2),
    set_optab_handler (neg_optab, DFmode, CODE_FOR_negdf2);
  if (HAVE_negv2sf2)
    set_optab_handler (negv_optab, V2SFmode, CODE_FOR_negv2sf2),
    set_optab_handler (neg_optab, V2SFmode, CODE_FOR_negv2sf2);
  set_optab_handler (one_cmpl_optab, SImode, CODE_FOR_one_cmplsi2);
  if (HAVE_one_cmpldi2)
    set_optab_handler (one_cmpl_optab, DImode, CODE_FOR_one_cmpldi2);
  if (HAVE_truncdfsf2)
    set_convert_optab_handler (trunc_optab, SFmode, DFmode, CODE_FOR_truncdfsf2);
  if (HAVE_truncdiqi2)
    set_convert_optab_handler (trunc_optab, QImode, DImode, CODE_FOR_truncdiqi2);
  if (HAVE_truncdihi2)
    set_convert_optab_handler (trunc_optab, HImode, DImode, CODE_FOR_truncdihi2);
  if (HAVE_truncdisi2)
    set_convert_optab_handler (trunc_optab, SImode, DImode, CODE_FOR_truncdisi2);
  if (HAVE_extendsidi2)
    set_convert_optab_handler (sext_optab, DImode, SImode, CODE_FOR_extendsidi2);
  if (HAVE_extendsfdf2)
    set_convert_optab_handler (sext_optab, DFmode, SFmode, CODE_FOR_extendsfdf2);
  if (HAVE_fix_truncdfdi2)
    set_convert_optab_handler (sfixtrunc_optab, DImode, DFmode, CODE_FOR_fix_truncdfdi2);
  if (HAVE_fix_truncsfdi2)
    set_convert_optab_handler (sfixtrunc_optab, DImode, SFmode, CODE_FOR_fix_truncsfdi2);
  if (HAVE_floatsidf2)
    set_convert_optab_handler (sfloat_optab, DFmode, SImode, CODE_FOR_floatsidf2);
  if (HAVE_floatdidf2)
    set_convert_optab_handler (sfloat_optab, DFmode, DImode, CODE_FOR_floatdidf2);
  if (HAVE_floatsisf2)
    set_convert_optab_handler (sfloat_optab, SFmode, SImode, CODE_FOR_floatsisf2);
  if (HAVE_floatdisf2)
    set_convert_optab_handler (sfloat_optab, SFmode, DImode, CODE_FOR_floatdisf2);
  if (HAVE_movcc)
    set_optab_handler (mov_optab, CCmode, CODE_FOR_movcc);
  if (HAVE_rotrsi3)
    set_optab_handler (rotr_optab, SImode, CODE_FOR_rotrsi3);
  if (HAVE_rotrdi3)
    set_optab_handler (rotr_optab, DImode, CODE_FOR_rotrdi3);
  if (HAVE_sync_compare_and_swapsi)
    set_direct_optab_handler (sync_compare_and_swap_optab, SImode, CODE_FOR_sync_compare_and_swapsi);
  if (HAVE_sync_compare_and_swapdi)
    set_direct_optab_handler (sync_compare_and_swap_optab, DImode, CODE_FOR_sync_compare_and_swapdi);
  if (HAVE_sync_addsi)
    set_direct_optab_handler (sync_add_optab, SImode, CODE_FOR_sync_addsi);
  if (HAVE_sync_adddi)
    set_direct_optab_handler (sync_add_optab, DImode, CODE_FOR_sync_adddi);
  if (HAVE_sync_subsi)
    set_direct_optab_handler (sync_sub_optab, SImode, CODE_FOR_sync_subsi);
  if (HAVE_sync_subdi)
    set_direct_optab_handler (sync_sub_optab, DImode, CODE_FOR_sync_subdi);
  if (HAVE_sync_old_addsi)
    set_direct_optab_handler (sync_old_add_optab, SImode, CODE_FOR_sync_old_addsi);
  if (HAVE_sync_old_adddi)
    set_direct_optab_handler (sync_old_add_optab, DImode, CODE_FOR_sync_old_adddi);
  if (HAVE_sync_old_subsi)
    set_direct_optab_handler (sync_old_sub_optab, SImode, CODE_FOR_sync_old_subsi);
  if (HAVE_sync_old_subdi)
    set_direct_optab_handler (sync_old_sub_optab, DImode, CODE_FOR_sync_old_subdi);
  if (HAVE_sync_new_addsi)
    set_direct_optab_handler (sync_new_add_optab, SImode, CODE_FOR_sync_new_addsi);
  if (HAVE_sync_new_adddi)
    set_direct_optab_handler (sync_new_add_optab, DImode, CODE_FOR_sync_new_adddi);
  if (HAVE_sync_new_subsi)
    set_direct_optab_handler (sync_new_sub_optab, SImode, CODE_FOR_sync_new_subsi);
  if (HAVE_sync_new_subdi)
    set_direct_optab_handler (sync_new_sub_optab, DImode, CODE_FOR_sync_new_subdi);
  if (HAVE_sync_iorsi)
    set_direct_optab_handler (sync_ior_optab, SImode, CODE_FOR_sync_iorsi);
  if (HAVE_sync_xorsi)
    set_direct_optab_handler (sync_xor_optab, SImode, CODE_FOR_sync_xorsi);
  if (HAVE_sync_andsi)
    set_direct_optab_handler (sync_and_optab, SImode, CODE_FOR_sync_andsi);
  if (HAVE_sync_iordi)
    set_direct_optab_handler (sync_ior_optab, DImode, CODE_FOR_sync_iordi);
  if (HAVE_sync_xordi)
    set_direct_optab_handler (sync_xor_optab, DImode, CODE_FOR_sync_xordi);
  if (HAVE_sync_anddi)
    set_direct_optab_handler (sync_and_optab, DImode, CODE_FOR_sync_anddi);
  if (HAVE_sync_old_iorsi)
    set_direct_optab_handler (sync_old_ior_optab, SImode, CODE_FOR_sync_old_iorsi);
  if (HAVE_sync_old_xorsi)
    set_direct_optab_handler (sync_old_xor_optab, SImode, CODE_FOR_sync_old_xorsi);
  if (HAVE_sync_old_andsi)
    set_direct_optab_handler (sync_old_and_optab, SImode, CODE_FOR_sync_old_andsi);
  if (HAVE_sync_old_iordi)
    set_direct_optab_handler (sync_old_ior_optab, DImode, CODE_FOR_sync_old_iordi);
  if (HAVE_sync_old_xordi)
    set_direct_optab_handler (sync_old_xor_optab, DImode, CODE_FOR_sync_old_xordi);
  if (HAVE_sync_old_anddi)
    set_direct_optab_handler (sync_old_and_optab, DImode, CODE_FOR_sync_old_anddi);
  if (HAVE_sync_new_iorsi)
    set_direct_optab_handler (sync_new_ior_optab, SImode, CODE_FOR_sync_new_iorsi);
  if (HAVE_sync_new_xorsi)
    set_direct_optab_handler (sync_new_xor_optab, SImode, CODE_FOR_sync_new_xorsi);
  if (HAVE_sync_new_andsi)
    set_direct_optab_handler (sync_new_and_optab, SImode, CODE_FOR_sync_new_andsi);
  if (HAVE_sync_new_iordi)
    set_direct_optab_handler (sync_new_ior_optab, DImode, CODE_FOR_sync_new_iordi);
  if (HAVE_sync_new_xordi)
    set_direct_optab_handler (sync_new_xor_optab, DImode, CODE_FOR_sync_new_xordi);
  if (HAVE_sync_new_anddi)
    set_direct_optab_handler (sync_new_and_optab, DImode, CODE_FOR_sync_new_anddi);
  if (HAVE_sync_nandsi)
    set_direct_optab_handler (sync_nand_optab, SImode, CODE_FOR_sync_nandsi);
  if (HAVE_sync_nanddi)
    set_direct_optab_handler (sync_nand_optab, DImode, CODE_FOR_sync_nanddi);
  if (HAVE_sync_old_nandsi)
    set_direct_optab_handler (sync_old_nand_optab, SImode, CODE_FOR_sync_old_nandsi);
  if (HAVE_sync_old_nanddi)
    set_direct_optab_handler (sync_old_nand_optab, DImode, CODE_FOR_sync_old_nanddi);
  if (HAVE_sync_new_nandsi)
    set_direct_optab_handler (sync_new_nand_optab, SImode, CODE_FOR_sync_new_nandsi);
  if (HAVE_sync_new_nanddi)
    set_direct_optab_handler (sync_new_nand_optab, DImode, CODE_FOR_sync_new_nanddi);
  if (HAVE_sync_lock_test_and_setsi)
    set_direct_optab_handler (sync_lock_test_and_set_optab, SImode, CODE_FOR_sync_lock_test_and_setsi);
  if (HAVE_sync_lock_test_and_setdi)
    set_direct_optab_handler (sync_lock_test_and_set_optab, DImode, CODE_FOR_sync_lock_test_and_setdi);
  if (HAVE_vec_extractv2sf)
    set_optab_handler (vec_extract_optab, V2SFmode, CODE_FOR_vec_extractv2sf);
  if (HAVE_addv2hi3)
    set_optab_handler (add_optab, V2HImode, CODE_FOR_addv2hi3);
  if (HAVE_addv4qi3)
    set_optab_handler (add_optab, V4QImode, CODE_FOR_addv4qi3);
  if (HAVE_subv2hi3)
    set_optab_handler (sub_optab, V2HImode, CODE_FOR_subv2hi3);
  if (HAVE_subv4qi3)
    set_optab_handler (sub_optab, V4QImode, CODE_FOR_subv4qi3);
  if (HAVE_mulv2hi3)
    set_optab_handler (smul_optab, V2HImode, CODE_FOR_mulv2hi3);
  set_optab_handler (add_optab, QQmode, CODE_FOR_addqq3);
  set_optab_handler (add_optab, HQmode, CODE_FOR_addhq3);
  set_optab_handler (add_optab, SQmode, CODE_FOR_addsq3);
  if (HAVE_adddq3)
    set_optab_handler (add_optab, DQmode, CODE_FOR_adddq3);
  set_optab_handler (add_optab, UQQmode, CODE_FOR_adduqq3);
  set_optab_handler (add_optab, UHQmode, CODE_FOR_adduhq3);
  set_optab_handler (add_optab, USQmode, CODE_FOR_addusq3);
  if (HAVE_addudq3)
    set_optab_handler (add_optab, UDQmode, CODE_FOR_addudq3);
  set_optab_handler (add_optab, HAmode, CODE_FOR_addha3);
  set_optab_handler (add_optab, SAmode, CODE_FOR_addsa3);
  if (HAVE_addda3)
    set_optab_handler (add_optab, DAmode, CODE_FOR_addda3);
  set_optab_handler (add_optab, UHAmode, CODE_FOR_adduha3);
  set_optab_handler (add_optab, USAmode, CODE_FOR_addusa3);
  if (HAVE_adduda3)
    set_optab_handler (add_optab, UDAmode, CODE_FOR_adduda3);
  if (HAVE_usadduqq3)
    set_optab_handler (usadd_optab, UQQmode, CODE_FOR_usadduqq3);
  if (HAVE_usadduhq3)
    set_optab_handler (usadd_optab, UHQmode, CODE_FOR_usadduhq3);
  if (HAVE_usadduha3)
    set_optab_handler (usadd_optab, UHAmode, CODE_FOR_usadduha3);
  if (HAVE_usaddv4uqq3)
    set_optab_handler (usadd_optab, V4UQQmode, CODE_FOR_usaddv4uqq3);
  if (HAVE_usaddv2uhq3)
    set_optab_handler (usadd_optab, V2UHQmode, CODE_FOR_usaddv2uhq3);
  if (HAVE_usaddv2uha3)
    set_optab_handler (usadd_optab, V2UHAmode, CODE_FOR_usaddv2uha3);
  if (HAVE_ssaddhq3)
    set_optab_handler (ssadd_optab, HQmode, CODE_FOR_ssaddhq3);
  if (HAVE_ssaddsq3)
    set_optab_handler (ssadd_optab, SQmode, CODE_FOR_ssaddsq3);
  if (HAVE_ssaddha3)
    set_optab_handler (ssadd_optab, HAmode, CODE_FOR_ssaddha3);
  if (HAVE_ssaddsa3)
    set_optab_handler (ssadd_optab, SAmode, CODE_FOR_ssaddsa3);
  if (HAVE_ssaddv2hq3)
    set_optab_handler (ssadd_optab, V2HQmode, CODE_FOR_ssaddv2hq3);
  if (HAVE_ssaddv2ha3)
    set_optab_handler (ssadd_optab, V2HAmode, CODE_FOR_ssaddv2ha3);
  set_optab_handler (sub_optab, QQmode, CODE_FOR_subqq3);
  set_optab_handler (sub_optab, HQmode, CODE_FOR_subhq3);
  set_optab_handler (sub_optab, SQmode, CODE_FOR_subsq3);
  if (HAVE_subdq3)
    set_optab_handler (sub_optab, DQmode, CODE_FOR_subdq3);
  set_optab_handler (sub_optab, UQQmode, CODE_FOR_subuqq3);
  set_optab_handler (sub_optab, UHQmode, CODE_FOR_subuhq3);
  set_optab_handler (sub_optab, USQmode, CODE_FOR_subusq3);
  if (HAVE_subudq3)
    set_optab_handler (sub_optab, UDQmode, CODE_FOR_subudq3);
  set_optab_handler (sub_optab, HAmode, CODE_FOR_subha3);
  set_optab_handler (sub_optab, SAmode, CODE_FOR_subsa3);
  if (HAVE_subda3)
    set_optab_handler (sub_optab, DAmode, CODE_FOR_subda3);
  set_optab_handler (sub_optab, UHAmode, CODE_FOR_subuha3);
  set_optab_handler (sub_optab, USAmode, CODE_FOR_subusa3);
  if (HAVE_subuda3)
    set_optab_handler (sub_optab, UDAmode, CODE_FOR_subuda3);
  if (HAVE_ussubuqq3)
    set_optab_handler (ussub_optab, UQQmode, CODE_FOR_ussubuqq3);
  if (HAVE_ussubuhq3)
    set_optab_handler (ussub_optab, UHQmode, CODE_FOR_ussubuhq3);
  if (HAVE_ussubuha3)
    set_optab_handler (ussub_optab, UHAmode, CODE_FOR_ussubuha3);
  if (HAVE_ussubv4uqq3)
    set_optab_handler (ussub_optab, V4UQQmode, CODE_FOR_ussubv4uqq3);
  if (HAVE_ussubv2uhq3)
    set_optab_handler (ussub_optab, V2UHQmode, CODE_FOR_ussubv2uhq3);
  if (HAVE_ussubv2uha3)
    set_optab_handler (ussub_optab, V2UHAmode, CODE_FOR_ussubv2uha3);
  if (HAVE_sssubhq3)
    set_optab_handler (sssub_optab, HQmode, CODE_FOR_sssubhq3);
  if (HAVE_sssubsq3)
    set_optab_handler (sssub_optab, SQmode, CODE_FOR_sssubsq3);
  if (HAVE_sssubha3)
    set_optab_handler (sssub_optab, HAmode, CODE_FOR_sssubha3);
  if (HAVE_sssubsa3)
    set_optab_handler (sssub_optab, SAmode, CODE_FOR_sssubsa3);
  if (HAVE_sssubv2hq3)
    set_optab_handler (sssub_optab, V2HQmode, CODE_FOR_sssubv2hq3);
  if (HAVE_sssubv2ha3)
    set_optab_handler (sssub_optab, V2HAmode, CODE_FOR_sssubv2ha3);
  if (HAVE_ssmulv2hq3)
    set_optab_handler (ssmul_optab, V2HQmode, CODE_FOR_ssmulv2hq3);
  if (HAVE_ssmulhq3)
    set_optab_handler (ssmul_optab, HQmode, CODE_FOR_ssmulhq3);
  if (HAVE_ssmulsq3)
    set_optab_handler (ssmul_optab, SQmode, CODE_FOR_ssmulsq3);
  if (HAVE_ssmaddsqdq4)
    set_widening_optab_handler (ssmadd_widen_optab, DQmode, SQmode, CODE_FOR_ssmaddsqdq4);
  if (HAVE_ssmsubsqdq4)
    set_widening_optab_handler (ssmsub_widen_optab, DQmode, SQmode, CODE_FOR_ssmsubsqdq4);
  if (HAVE_vec_pack_ssat_v2si)
    set_optab_handler (vec_pack_ssat_optab, V2SImode, CODE_FOR_vec_pack_ssat_v2si);
  if (HAVE_vec_pack_ssat_v4hi)
    set_optab_handler (vec_pack_ssat_optab, V4HImode, CODE_FOR_vec_pack_ssat_v4hi);
  if (HAVE_vec_pack_usat_v4hi)
    set_optab_handler (vec_pack_usat_optab, V4HImode, CODE_FOR_vec_pack_usat_v4hi);
  if (HAVE_addv2si3)
    set_optab_handler (add_optab, V2SImode, CODE_FOR_addv2si3);
  if (HAVE_addv4hi3)
    set_optab_handler (add_optab, V4HImode, CODE_FOR_addv4hi3);
  if (HAVE_addv8qi3)
    set_optab_handler (add_optab, V8QImode, CODE_FOR_addv8qi3);
  if (HAVE_smaxv4hi3)
    set_optab_handler (smax_optab, V4HImode, CODE_FOR_smaxv4hi3);
  if (HAVE_umaxv8qi3)
    set_optab_handler (umax_optab, V8QImode, CODE_FOR_umaxv8qi3);
  if (HAVE_sminv4hi3)
    set_optab_handler (smin_optab, V4HImode, CODE_FOR_sminv4hi3);
  if (HAVE_uminv8qi3)
    set_optab_handler (umin_optab, V8QImode, CODE_FOR_uminv8qi3);
  if (HAVE_umulv4hi3_highpart)
    set_optab_handler (umul_highpart_optab, V4HImode, CODE_FOR_umulv4hi3_highpart);
  if (HAVE_smulv4hi3_highpart)
    set_optab_handler (smul_highpart_optab, V4HImode, CODE_FOR_smulv4hi3_highpart);
  if (HAVE_mulv4hi3)
    set_optab_handler (smul_optab, V4HImode, CODE_FOR_mulv4hi3);
  if (HAVE_ashlv2si3)
    set_optab_handler (ashl_optab, V2SImode, CODE_FOR_ashlv2si3);
  if (HAVE_ashlv4hi3)
    set_optab_handler (ashl_optab, V4HImode, CODE_FOR_ashlv4hi3);
  if (HAVE_ashrv2si3)
    set_optab_handler (ashr_optab, V2SImode, CODE_FOR_ashrv2si3);
  if (HAVE_ashrv4hi3)
    set_optab_handler (ashr_optab, V4HImode, CODE_FOR_ashrv4hi3);
  if (HAVE_lshrv2si3)
    set_optab_handler (lshr_optab, V2SImode, CODE_FOR_lshrv2si3);
  if (HAVE_lshrv4hi3)
    set_optab_handler (lshr_optab, V4HImode, CODE_FOR_lshrv4hi3);
  if (HAVE_subv2si3)
    set_optab_handler (sub_optab, V2SImode, CODE_FOR_subv2si3);
  if (HAVE_subv4hi3)
    set_optab_handler (sub_optab, V4HImode, CODE_FOR_subv4hi3);
  if (HAVE_subv8qi3)
    set_optab_handler (sub_optab, V8QImode, CODE_FOR_subv8qi3);
  if (HAVE_vec_interleave_highv2si)
    set_optab_handler (vec_interleave_high_optab, V2SImode, CODE_FOR_vec_interleave_highv2si);
  if (HAVE_vec_interleave_highv4hi)
    set_optab_handler (vec_interleave_high_optab, V4HImode, CODE_FOR_vec_interleave_highv4hi);
  if (HAVE_vec_interleave_highv8qi)
    set_optab_handler (vec_interleave_high_optab, V8QImode, CODE_FOR_vec_interleave_highv8qi);
  if (HAVE_vec_interleave_lowv2si)
    set_optab_handler (vec_interleave_low_optab, V2SImode, CODE_FOR_vec_interleave_lowv2si);
  if (HAVE_vec_interleave_lowv4hi)
    set_optab_handler (vec_interleave_low_optab, V4HImode, CODE_FOR_vec_interleave_lowv4hi);
  if (HAVE_vec_interleave_lowv8qi)
    set_optab_handler (vec_interleave_low_optab, V8QImode, CODE_FOR_vec_interleave_lowv8qi);
  if (HAVE_divsi3)
    set_optab_handler (sdiv_optab, SImode, CODE_FOR_divsi3);
  if (HAVE_udivsi3)
    set_optab_handler (udiv_optab, SImode, CODE_FOR_udivsi3);
  if (HAVE_divdi3)
    set_optab_handler (sdiv_optab, DImode, CODE_FOR_divdi3);
  if (HAVE_udivdi3)
    set_optab_handler (udiv_optab, DImode, CODE_FOR_udivdi3);
  if (HAVE_modsi3)
    set_optab_handler (smod_optab, SImode, CODE_FOR_modsi3);
  if (HAVE_umodsi3)
    set_optab_handler (umod_optab, SImode, CODE_FOR_umodsi3);
  if (HAVE_moddi3)
    set_optab_handler (smod_optab, DImode, CODE_FOR_moddi3);
  if (HAVE_umoddi3)
    set_optab_handler (umod_optab, DImode, CODE_FOR_umoddi3);
  if (HAVE_ctrapsi4)
    set_optab_handler (ctrap_optab, SImode, CODE_FOR_ctrapsi4);
  if (HAVE_ctrapdi4)
    set_optab_handler (ctrap_optab, DImode, CODE_FOR_ctrapdi4);
  set_optab_handler (add_optab, SImode, CODE_FOR_addsi3);
  if (HAVE_adddi3)
    set_optab_handler (add_optab, DImode, CODE_FOR_adddi3);
  if (HAVE_mulsf3)
    set_optab_handler (smulv_optab, SFmode, CODE_FOR_mulsf3),
    set_optab_handler (smul_optab, SFmode, CODE_FOR_mulsf3);
  if (HAVE_muldf3)
    set_optab_handler (smulv_optab, DFmode, CODE_FOR_muldf3),
    set_optab_handler (smul_optab, DFmode, CODE_FOR_muldf3);
  set_optab_handler (smul_optab, SImode, CODE_FOR_mulsi3);
  if (HAVE_muldi3)
    set_optab_handler (smul_optab, DImode, CODE_FOR_muldi3);
  if (HAVE_mulsidi3)
    set_widening_optab_handler (smul_widen_optab, DImode, SImode, CODE_FOR_mulsidi3);
  if (HAVE_umulsidi3)
    set_widening_optab_handler (umul_widen_optab, DImode, SImode, CODE_FOR_umulsidi3);
  set_optab_handler (smul_highpart_optab, SImode, CODE_FOR_smulsi3_highpart);
  set_optab_handler (umul_highpart_optab, SImode, CODE_FOR_umulsi3_highpart);
  if (HAVE_mulditi3)
    set_widening_optab_handler (smul_widen_optab, TImode, DImode, CODE_FOR_mulditi3);
  if (HAVE_umulditi3)
    set_widening_optab_handler (umul_widen_optab, TImode, DImode, CODE_FOR_umulditi3);
  if (HAVE_divsf3)
    set_optab_handler (sdiv_optab, SFmode, CODE_FOR_divsf3);
  if (HAVE_divdf3)
    set_optab_handler (sdiv_optab, DFmode, CODE_FOR_divdf3);
  if (HAVE_divv2sf3)
    set_optab_handler (sdiv_optab, V2SFmode, CODE_FOR_divv2sf3);
  set_optab_handler (and_optab, SImode, CODE_FOR_andsi3);
  if (HAVE_anddi3)
    set_optab_handler (and_optab, DImode, CODE_FOR_anddi3);
  set_optab_handler (ior_optab, SImode, CODE_FOR_iorsi3);
  if (HAVE_iordi3)
    set_optab_handler (ior_optab, DImode, CODE_FOR_iordi3);
  set_optab_handler (xor_optab, SImode, CODE_FOR_xorsi3);
  if (HAVE_xordi3)
    set_optab_handler (xor_optab, DImode, CODE_FOR_xordi3);
  if (HAVE_zero_extendsidi2)
    set_convert_optab_handler (zext_optab, DImode, SImode, CODE_FOR_zero_extendsidi2);
  set_convert_optab_handler (zext_optab, SImode, QImode, CODE_FOR_zero_extendqisi2);
  if (HAVE_zero_extendqidi2)
    set_convert_optab_handler (zext_optab, DImode, QImode, CODE_FOR_zero_extendqidi2);
  set_convert_optab_handler (zext_optab, SImode, HImode, CODE_FOR_zero_extendhisi2);
  if (HAVE_zero_extendhidi2)
    set_convert_optab_handler (zext_optab, DImode, HImode, CODE_FOR_zero_extendhidi2);
  set_convert_optab_handler (zext_optab, HImode, QImode, CODE_FOR_zero_extendqihi2);
  set_convert_optab_handler (sext_optab, SImode, QImode, CODE_FOR_extendqisi2);
  if (HAVE_extendqidi2)
    set_convert_optab_handler (sext_optab, DImode, QImode, CODE_FOR_extendqidi2);
  set_convert_optab_handler (sext_optab, SImode, HImode, CODE_FOR_extendhisi2);
  if (HAVE_extendhidi2)
    set_convert_optab_handler (sext_optab, DImode, HImode, CODE_FOR_extendhidi2);
  set_convert_optab_handler (sext_optab, HImode, QImode, CODE_FOR_extendqihi2);
  if (HAVE_fix_truncdfsi2)
    set_convert_optab_handler (sfixtrunc_optab, SImode, DFmode, CODE_FOR_fix_truncdfsi2);
  if (HAVE_fix_truncsfsi2)
    set_convert_optab_handler (sfixtrunc_optab, SImode, SFmode, CODE_FOR_fix_truncsfsi2);
  if (HAVE_fixuns_truncdfsi2)
    set_convert_optab_handler (ufixtrunc_optab, SImode, DFmode, CODE_FOR_fixuns_truncdfsi2);
  if (HAVE_fixuns_truncdfdi2)
    set_convert_optab_handler (ufixtrunc_optab, DImode, DFmode, CODE_FOR_fixuns_truncdfdi2);
  if (HAVE_fixuns_truncsfsi2)
    set_convert_optab_handler (ufixtrunc_optab, SImode, SFmode, CODE_FOR_fixuns_truncsfsi2);
  if (HAVE_fixuns_truncsfdi2)
    set_convert_optab_handler (ufixtrunc_optab, DImode, SFmode, CODE_FOR_fixuns_truncsfdi2);
  set_optab_handler (mov_optab, DImode, CODE_FOR_movdi);
  set_optab_handler (mov_optab, SImode, CODE_FOR_movsi);
  if (HAVE_movv2hi)
    set_optab_handler (mov_optab, V2HImode, CODE_FOR_movv2hi);
  if (HAVE_movv4qi)
    set_optab_handler (mov_optab, V4QImode, CODE_FOR_movv4qi);
  if (HAVE_movv2hq)
    set_optab_handler (mov_optab, V2HQmode, CODE_FOR_movv2hq);
  if (HAVE_movv2uhq)
    set_optab_handler (mov_optab, V2UHQmode, CODE_FOR_movv2uhq);
  if (HAVE_movv2ha)
    set_optab_handler (mov_optab, V2HAmode, CODE_FOR_movv2ha);
  if (HAVE_movv2uha)
    set_optab_handler (mov_optab, V2UHAmode, CODE_FOR_movv2uha);
  if (HAVE_movv4qq)
    set_optab_handler (mov_optab, V4QQmode, CODE_FOR_movv4qq);
  if (HAVE_movv4uqq)
    set_optab_handler (mov_optab, V4UQQmode, CODE_FOR_movv4uqq);
  if (HAVE_reload_incc)
    set_direct_optab_handler (reload_in_optab, CCmode, CODE_FOR_reload_incc);
  if (HAVE_reload_outcc)
    set_direct_optab_handler (reload_out_optab, CCmode, CODE_FOR_reload_outcc);
  set_optab_handler (mov_optab, HImode, CODE_FOR_movhi);
  set_optab_handler (mov_optab, QImode, CODE_FOR_movqi);
  set_optab_handler (mov_optab, SFmode, CODE_FOR_movsf);
  set_optab_handler (mov_optab, DFmode, CODE_FOR_movdf);
  if (HAVE_movti)
    set_optab_handler (mov_optab, TImode, CODE_FOR_movti);
  if (HAVE_movtf)
    set_optab_handler (mov_optab, TFmode, CODE_FOR_movtf);
  if (HAVE_movv2sf)
    set_optab_handler (mov_optab, V2SFmode, CODE_FOR_movv2sf);
  if (HAVE_movmemsi)
    set_direct_optab_handler (movmem_optab, SImode, CODE_FOR_movmemsi);
  set_optab_handler (ashl_optab, SImode, CODE_FOR_ashlsi3);
  set_optab_handler (ashr_optab, SImode, CODE_FOR_ashrsi3);
  set_optab_handler (lshr_optab, SImode, CODE_FOR_lshrsi3);
  if (HAVE_ashldi3)
    set_optab_handler (ashl_optab, DImode, CODE_FOR_ashldi3);
  if (HAVE_ashrdi3)
    set_optab_handler (ashr_optab, DImode, CODE_FOR_ashrdi3);
  if (HAVE_lshrdi3)
    set_optab_handler (lshr_optab, DImode, CODE_FOR_lshrdi3);
  set_optab_handler (cbranch_optab, SImode, CODE_FOR_cbranchsi4);
  if (HAVE_cbranchdi4)
    set_optab_handler (cbranch_optab, DImode, CODE_FOR_cbranchdi4);
  if (HAVE_cbranchsf4)
    set_optab_handler (cbranch_optab, SFmode, CODE_FOR_cbranchsf4);
  if (HAVE_cbranchdf4)
    set_optab_handler (cbranch_optab, DFmode, CODE_FOR_cbranchdf4);
  set_optab_handler (cstore_optab, SImode, CODE_FOR_cstoresi4);
  if (HAVE_cstoredi4)
    set_optab_handler (cstore_optab, DImode, CODE_FOR_cstoredi4);
  if (HAVE_movsicc)
    set_direct_optab_handler (movcc_optab, SImode, CODE_FOR_movsicc);
  if (HAVE_movdicc)
    set_direct_optab_handler (movcc_optab, DImode, CODE_FOR_movdicc);
  if (HAVE_movsfcc)
    set_direct_optab_handler (movcc_optab, SFmode, CODE_FOR_movsfcc);
  if (HAVE_movdfcc)
    set_direct_optab_handler (movcc_optab, DFmode, CODE_FOR_movdfcc);
  if (HAVE_sync_compare_and_swapqi)
    set_direct_optab_handler (sync_compare_and_swap_optab, QImode, CODE_FOR_sync_compare_and_swapqi);
  if (HAVE_sync_compare_and_swaphi)
    set_direct_optab_handler (sync_compare_and_swap_optab, HImode, CODE_FOR_sync_compare_and_swaphi);
  if (HAVE_sync_addqi)
    set_direct_optab_handler (sync_add_optab, QImode, CODE_FOR_sync_addqi);
  if (HAVE_sync_subqi)
    set_direct_optab_handler (sync_sub_optab, QImode, CODE_FOR_sync_subqi);
  if (HAVE_sync_iorqi)
    set_direct_optab_handler (sync_ior_optab, QImode, CODE_FOR_sync_iorqi);
  if (HAVE_sync_xorqi)
    set_direct_optab_handler (sync_xor_optab, QImode, CODE_FOR_sync_xorqi);
  if (HAVE_sync_andqi)
    set_direct_optab_handler (sync_and_optab, QImode, CODE_FOR_sync_andqi);
  if (HAVE_sync_addhi)
    set_direct_optab_handler (sync_add_optab, HImode, CODE_FOR_sync_addhi);
  if (HAVE_sync_subhi)
    set_direct_optab_handler (sync_sub_optab, HImode, CODE_FOR_sync_subhi);
  if (HAVE_sync_iorhi)
    set_direct_optab_handler (sync_ior_optab, HImode, CODE_FOR_sync_iorhi);
  if (HAVE_sync_xorhi)
    set_direct_optab_handler (sync_xor_optab, HImode, CODE_FOR_sync_xorhi);
  if (HAVE_sync_andhi)
    set_direct_optab_handler (sync_and_optab, HImode, CODE_FOR_sync_andhi);
  if (HAVE_sync_old_addqi)
    set_direct_optab_handler (sync_old_add_optab, QImode, CODE_FOR_sync_old_addqi);
  if (HAVE_sync_old_subqi)
    set_direct_optab_handler (sync_old_sub_optab, QImode, CODE_FOR_sync_old_subqi);
  if (HAVE_sync_old_iorqi)
    set_direct_optab_handler (sync_old_ior_optab, QImode, CODE_FOR_sync_old_iorqi);
  if (HAVE_sync_old_xorqi)
    set_direct_optab_handler (sync_old_xor_optab, QImode, CODE_FOR_sync_old_xorqi);
  if (HAVE_sync_old_andqi)
    set_direct_optab_handler (sync_old_and_optab, QImode, CODE_FOR_sync_old_andqi);
  if (HAVE_sync_old_addhi)
    set_direct_optab_handler (sync_old_add_optab, HImode, CODE_FOR_sync_old_addhi);
  if (HAVE_sync_old_subhi)
    set_direct_optab_handler (sync_old_sub_optab, HImode, CODE_FOR_sync_old_subhi);
  if (HAVE_sync_old_iorhi)
    set_direct_optab_handler (sync_old_ior_optab, HImode, CODE_FOR_sync_old_iorhi);
  if (HAVE_sync_old_xorhi)
    set_direct_optab_handler (sync_old_xor_optab, HImode, CODE_FOR_sync_old_xorhi);
  if (HAVE_sync_old_andhi)
    set_direct_optab_handler (sync_old_and_optab, HImode, CODE_FOR_sync_old_andhi);
  if (HAVE_sync_new_addqi)
    set_direct_optab_handler (sync_new_add_optab, QImode, CODE_FOR_sync_new_addqi);
  if (HAVE_sync_new_subqi)
    set_direct_optab_handler (sync_new_sub_optab, QImode, CODE_FOR_sync_new_subqi);
  if (HAVE_sync_new_iorqi)
    set_direct_optab_handler (sync_new_ior_optab, QImode, CODE_FOR_sync_new_iorqi);
  if (HAVE_sync_new_xorqi)
    set_direct_optab_handler (sync_new_xor_optab, QImode, CODE_FOR_sync_new_xorqi);
  if (HAVE_sync_new_andqi)
    set_direct_optab_handler (sync_new_and_optab, QImode, CODE_FOR_sync_new_andqi);
  if (HAVE_sync_new_addhi)
    set_direct_optab_handler (sync_new_add_optab, HImode, CODE_FOR_sync_new_addhi);
  if (HAVE_sync_new_subhi)
    set_direct_optab_handler (sync_new_sub_optab, HImode, CODE_FOR_sync_new_subhi);
  if (HAVE_sync_new_iorhi)
    set_direct_optab_handler (sync_new_ior_optab, HImode, CODE_FOR_sync_new_iorhi);
  if (HAVE_sync_new_xorhi)
    set_direct_optab_handler (sync_new_xor_optab, HImode, CODE_FOR_sync_new_xorhi);
  if (HAVE_sync_new_andhi)
    set_direct_optab_handler (sync_new_and_optab, HImode, CODE_FOR_sync_new_andhi);
  if (HAVE_sync_nandqi)
    set_direct_optab_handler (sync_nand_optab, QImode, CODE_FOR_sync_nandqi);
  if (HAVE_sync_nandhi)
    set_direct_optab_handler (sync_nand_optab, HImode, CODE_FOR_sync_nandhi);
  if (HAVE_sync_old_nandqi)
    set_direct_optab_handler (sync_old_nand_optab, QImode, CODE_FOR_sync_old_nandqi);
  if (HAVE_sync_old_nandhi)
    set_direct_optab_handler (sync_old_nand_optab, HImode, CODE_FOR_sync_old_nandhi);
  if (HAVE_sync_new_nandqi)
    set_direct_optab_handler (sync_new_nand_optab, QImode, CODE_FOR_sync_new_nandqi);
  if (HAVE_sync_new_nandhi)
    set_direct_optab_handler (sync_new_nand_optab, HImode, CODE_FOR_sync_new_nandhi);
  if (HAVE_sync_lock_test_and_setqi)
    set_direct_optab_handler (sync_lock_test_and_set_optab, QImode, CODE_FOR_sync_lock_test_and_setqi);
  if (HAVE_sync_lock_test_and_sethi)
    set_direct_optab_handler (sync_lock_test_and_set_optab, HImode, CODE_FOR_sync_lock_test_and_sethi);
  if (HAVE_movv2sfcc)
    set_direct_optab_handler (movcc_optab, V2SFmode, CODE_FOR_movv2sfcc);
  if (HAVE_vec_initv2sf)
    set_optab_handler (vec_init_optab, V2SFmode, CODE_FOR_vec_initv2sf);
  if (HAVE_vec_setv2sf)
    set_optab_handler (vec_set_optab, V2SFmode, CODE_FOR_vec_setv2sf);
  if (HAVE_vcondv2sf)
    set_direct_optab_handler (vcond_optab, V2SFmode, CODE_FOR_vcondv2sf);
  if (HAVE_sminv2sf3)
    set_optab_handler (smin_optab, V2SFmode, CODE_FOR_sminv2sf3);
  if (HAVE_smaxv2sf3)
    set_optab_handler (smax_optab, V2SFmode, CODE_FOR_smaxv2sf3);
  if (HAVE_movv2si)
    set_optab_handler (mov_optab, V2SImode, CODE_FOR_movv2si);
  if (HAVE_movv4hi)
    set_optab_handler (mov_optab, V4HImode, CODE_FOR_movv4hi);
  if (HAVE_movv8qi)
    set_optab_handler (mov_optab, V8QImode, CODE_FOR_movv8qi);
  if (HAVE_vec_initv2si)
    set_optab_handler (vec_init_optab, V2SImode, CODE_FOR_vec_initv2si);
  if (HAVE_vec_initv4hi)
    set_optab_handler (vec_init_optab, V4HImode, CODE_FOR_vec_initv4hi);
  if (HAVE_vec_initv8qi)
    set_optab_handler (vec_init_optab, V8QImode, CODE_FOR_vec_initv8qi);

#ifdef FIXUNS_TRUNC_LIKE_FIX_TRUNC
  /* This flag says the same insns that convert to a signed fixnum
     also convert validly to an unsigned one.  */
  for (i = 0; i < NUM_MACHINE_MODES; i++)
    for (j = 0; j < NUM_MACHINE_MODES; j++)
      set_convert_optab_handler
 	(ufixtrunc_optab, (enum machine_mode) i, (enum machine_mode) j,
	 convert_optab_handler (sfixtrunc_optab, (enum machine_mode) i,
						 (enum machine_mode) j));
#endif
}
