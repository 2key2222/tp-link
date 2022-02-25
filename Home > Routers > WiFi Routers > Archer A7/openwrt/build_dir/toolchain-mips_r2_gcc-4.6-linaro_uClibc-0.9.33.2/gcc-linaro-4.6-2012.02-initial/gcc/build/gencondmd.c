/* Generated automatically by the program `genconditions' from the target
   machine description file.  */

#include "bconfig.h"
#include "system.h"

/* It is necessary, but not entirely safe, to include the headers below
   in a generator program.  As a defensive measure, don't do so when the
   table isn't going to have anything in it.  */
#if GCC_VERSION >= 3001

/* Do not allow checking to confuse the issue.  */
#undef ENABLE_CHECKING
#undef ENABLE_TREE_CHECKING
#undef ENABLE_RTL_CHECKING
#undef ENABLE_RTL_FLAG_CHECKING
#undef ENABLE_GC_CHECKING
#undef ENABLE_GC_ALWAYS_COLLECT

#include "coretypes.h"
#include "tm.h"
#include "insn-constants.h"
#include "rtl.h"
#include "tm_p.h"
#include "function.h"

/* Fake - insn-config.h doesn't exist yet.  */
#define MAX_RECOG_OPERANDS 10
#define MAX_DUP_OPERANDS 10
#define MAX_INSNS_PER_SPLIT 5

#include "regs.h"
#include "recog.h"
#include "output.h"
#include "flags.h"
#include "hard-reg-set.h"
#include "resource.h"
#include "diagnostic-core.h"
#include "reload.h"
#include "tm-constrs.h"

#define HAVE_eh_return 1
#include "except.h"

/* Dummy external declarations.  */
extern rtx insn;
extern rtx ins1;
extern rtx operands[];

#endif /* gcc >= 3.0.1 */

/* Structure definition duplicated from gensupport.h rather than
   drag in that file and its dependencies.  */
struct c_test
{
  const char *expr;
  int value;
};

/* This table lists each condition found in the machine description.
   Each condition is mapped to its truth value (0 or 1), or -1 if that
   cannot be calculated at compile time.
   If we don't have __builtin_constant_p, or it's not acceptable in array
   initializers, fall back to assuming that all conditions potentially
   vary at run time.  It works in 3.0.1 and later; 3.0 only when not
   optimizing.  */

#if GCC_VERSION >= 3001
static const struct c_test insn_conditions[] = {

  { "((ISA_HAS_LWXS) && (TARGET_DSP)) && (Pmode == DImode)",
    __builtin_constant_p ((
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) ((
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "((TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && (Pmode == DImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 3837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 3837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(!TARGET_FIX_VR4120) && ( reload_completed)",
    __builtin_constant_p (
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120) && 
#line 2317 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) (
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120) && 
#line 2317 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(!ISA_MIPS1) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_MIPS1) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_MIPS1) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(ISA_HAS_DMUL3) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 1360 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_DMUL3) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 1360 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_DMUL3) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && (Pmode == DImode)",
    __builtin_constant_p (
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "((ISA_HAS_FP4) && (Pmode == SImode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 6009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_SIBCALLS && SIBLING_CALL_P (insn)",
    __builtin_constant_p 
#line 6009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SIBCALLS && SIBLING_CALL_P (insn))
    ? (int) 
#line 6009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SIBCALLS && SIBLING_CALL_P (insn))
    : -1 },
#line 1846 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_FIX_R4000",
    __builtin_constant_p 
#line 1846 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000)
    ? (int) 
#line 1846 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000)
    : -1 },
  { "(ISA_HAS_CONDMOVE) && (TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF)",
    __builtin_constant_p (
#line 6304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF))
    ? (int) (
#line 6304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V2UHAmode)\n\
       || reg_or_0_operand (operands[1], V2UHAmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2UHAmode)
       || reg_or_0_operand (operands[1], V2UHAmode))) && 
#line 611 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2UHAmode)
       || reg_or_0_operand (operands[1], V2UHAmode))) && 
#line 611 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && (Pmode == SImode)",
    __builtin_constant_p (
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(TARGET_HARD_FLOAT) && (!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 6253 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_PREFETCH && TARGET_EXPLICIT_RELOCS",
    __builtin_constant_p 
#line 6253 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_PREFETCH && TARGET_EXPLICIT_RELOCS)
    ? (int) 
#line 6253 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_PREFETCH && TARGET_EXPLICIT_RELOCS)
    : -1 },
#line 1360 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MUL3",
    __builtin_constant_p 
#line 1360 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3)
    ? (int) 
#line 1360 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3)
    : -1 },
  { "(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4987 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_MIPS16",
    __builtin_constant_p 
#line 4987 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16)
    ? (int) 
#line 4987 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16)
    : -1 },
  { "(TARGET_4300_MUL_FIX) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 1261 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_4300_MUL_FIX) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 1261 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_4300_MUL_FIX) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(TARGET_64BIT && !TARGET_MIPS16 && ISA_HAS_EXTS) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3147 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && ISA_HAS_EXTS) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3147 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && ISA_HAS_EXTS) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V2UHAmode)\n\
       || register_operand (operands[1], V2UHAmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2UHAmode)
       || register_operand (operands[1], V2UHAmode))) && 
#line 611 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2UHAmode)
       || register_operand (operands[1], V2UHAmode))) && 
#line 611 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
#line 4431 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "(TARGET_SOFT_FLOAT || TARGET_SINGLE_FLOAT) && !TARGET_MIPS16\n\
   && (register_operand (operands[0], DFmode)\n\
       || reg_or_0_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 4431 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
((TARGET_SOFT_FLOAT || TARGET_SINGLE_FLOAT) && !TARGET_MIPS16
   && (register_operand (operands[0], DFmode)
       || reg_or_0_operand (operands[1], DFmode)))
    ? (int) 
#line 4431 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
((TARGET_SOFT_FLOAT || TARGET_SINGLE_FLOAT) && !TARGET_MIPS16
   && (register_operand (operands[0], DFmode)
       || reg_or_0_operand (operands[1], DFmode)))
    : -1 },
  { "(ISA_HAS_PREFETCHX && TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT) && (Pmode == SImode)",
    __builtin_constant_p (
#line 6268 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_PREFETCHX && TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 6268 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_PREFETCHX && TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 1888 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && (ISA_HAS_MSAC || GENERATE_MADD_MSUB || ISA_HAS_DSP)",
    __builtin_constant_p 
#line 1888 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && (ISA_HAS_MSAC || GENERATE_MADD_MSUB || ISA_HAS_DSP))
    ? (int) 
#line 1888 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && (ISA_HAS_MSAC || GENERATE_MADD_MSUB || ISA_HAS_DSP))
    : -1 },
  { "(ISA_HAS_FP4 && TARGET_FLOAT64 && flag_unsafe_math_optimizations) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2432 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4 && TARGET_FLOAT64 && flag_unsafe_math_optimizations) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2432 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4 && TARGET_FLOAT64 && flag_unsafe_math_optimizations) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V4QImode)\n\
       || register_operand (operands[1], V4QImode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V4QImode)
       || register_operand (operands[1], V4QImode))) && 
#line 607 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V4QImode)
       || register_operand (operands[1], V4QImode))) && 
#line 607 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V2HQmode)\n\
       || reg_or_0_operand (operands[1], V2HQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2HQmode)
       || reg_or_0_operand (operands[1], V2HQmode))) && 
#line 608 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2HQmode)
       || reg_or_0_operand (operands[1], V2HQmode))) && 
#line 608 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
#line 3578 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_EXTS && TARGET_64BIT && IN_RANGE (INTVAL (operands[2]), 32, 63)",
    __builtin_constant_p 
#line 3578 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && TARGET_64BIT && IN_RANGE (INTVAL (operands[2]), 32, 63))
    ? (int) 
#line 3578 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && TARGET_64BIT && IN_RANGE (INTVAL (operands[2]), 32, 63))
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && (Pmode == DImode)",
    __builtin_constant_p (
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(ISA_HAS_ROR) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5117 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_ROR) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5117 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_ROR) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && !ISA_HAS_SEQ_SNE",
    __builtin_constant_p 
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE)
    ? (int) 
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE)
    : -1 },
  { "(ISA_HAS_FP_CONDMOVE) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 6346 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 6346 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V2UHQmode)\n\
       || reg_or_0_operand (operands[1], V2UHQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2UHQmode)
       || reg_or_0_operand (operands[1], V2UHQmode))) && 
#line 609 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2UHQmode)
       || reg_or_0_operand (operands[1], V2UHQmode))) && 
#line 609 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(mips_split_symbol (operands[2], operands[1], MAX_MACHINE_MODE, NULL)) && (Pmode == DImode)",
    __builtin_constant_p (
#line 3925 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_split_symbol (operands[2], operands[1], MAX_MACHINE_MODE, NULL)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 3925 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_split_symbol (operands[2], operands[1], MAX_MACHINE_MODE, NULL)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(reload_completed && !TARGET_64BIT\n\
   && mips_split_64bit_move_p (operands[0], operands[1])) && (TARGET_HARD_FLOAT && TARGET_LOONGSON_VECTORS)",
    __builtin_constant_p (
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && !TARGET_64BIT
   && mips_split_64bit_move_p (operands[0], operands[1])) && 
#line 621 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_LOONGSON_VECTORS))
    ? (int) (
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && !TARGET_64BIT
   && mips_split_64bit_move_p (operands[0], operands[1])) && 
#line 621 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_LOONGSON_VECTORS))
    : -1 },
#line 1694 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "GENERATE_MADD_MSUB",
    __builtin_constant_p 
#line 1694 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MADD_MSUB)
    ? (int) 
#line 1694 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MADD_MSUB)
    : -1 },
  { "(!TARGET_MIPS16) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5460 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5460 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 944 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_COND_TRAP",
    __builtin_constant_p 
#line 944 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_COND_TRAP)
    ? (int) 
#line 944 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_COND_TRAP)
    : -1 },
#line 1110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && TARGET_64BIT && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && REGNO (operands[0]) != REGNO (operands[1])\n\
   && ((INTVAL (operands[2]) > 0x7\n\
	&& INTVAL (operands[2]) <= 0x7 + 0xf)\n\
       || (INTVAL (operands[2]) < - 0x8\n\
	   && INTVAL (operands[2]) >= - 0x8 - 0x10))",
    __builtin_constant_p 
#line 1110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_64BIT && reload_completed && !TARGET_DEBUG_D_MODE
   && REGNO (operands[0]) != REGNO (operands[1])
   && ((INTVAL (operands[2]) > 0x7
	&& INTVAL (operands[2]) <= 0x7 + 0xf)
       || (INTVAL (operands[2]) < - 0x8
	   && INTVAL (operands[2]) >= - 0x8 - 0x10)))
    ? (int) 
#line 1110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_64BIT && reload_completed && !TARGET_DEBUG_D_MODE
   && REGNO (operands[0]) != REGNO (operands[1])
   && ((INTVAL (operands[2]) > 0x7
	&& INTVAL (operands[2]) <= 0x7 + 0xf)
       || (INTVAL (operands[2]) < - 0x8
	   && INTVAL (operands[2]) >= - 0x8 - 0x10)))
    : -1 },
  { "(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2122 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2122 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "(!ISA_HAS_MULHI) && ( reload_completed && !TARGET_FIX_R4000)",
    __builtin_constant_p (
#line 1929 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_MULHI) && 
#line 1931 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && !TARGET_FIX_R4000))
    ? (int) (
#line 1929 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_MULHI) && 
#line 1931 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && !TARGET_FIX_R4000))
    : -1 },
#line 5850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_CALL_CLOBBERED_GP",
    __builtin_constant_p 
#line 5850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_CALL_CLOBBERED_GP)
    ? (int) 
#line 5850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_CALL_CLOBBERED_GP)
    : -1 },
  { "((!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && (TARGET_64BIT)) && ( reload_completed && REG_P (operands[1]))",
    __builtin_constant_p ((
#line 3009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 3013 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && REG_P (operands[1])))
    ? (int) ((
#line 3009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 3013 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && REG_P (operands[1])))
    : -1 },
#line 1408 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_FIX_R4000",
    __builtin_constant_p 
#line 1408 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_FIX_R4000)
    ? (int) 
#line 1408 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_FIX_R4000)
    : -1 },
  { "((ISA_HAS_FP_CONDMOVE) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)) && 
#line 600 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)) && 
#line 600 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(ISA_HAS_FP_CONDMOVE) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 6346 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 6346 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 3205 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT && !ISA_HAS_TRUNC_W",
    __builtin_constant_p 
#line 3205 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT && !ISA_HAS_TRUNC_W)
    ? (int) 
#line 3205 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT && !ISA_HAS_TRUNC_W)
    : -1 },
  { "((ISA_HAS_SEQ_SNE) && (TARGET_64BIT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 5524 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && TARGET_ABSOLUTE_JUMPS",
    __builtin_constant_p 
#line 5524 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && TARGET_ABSOLUTE_JUMPS)
    ? (int) 
#line 5524 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && TARGET_ABSOLUTE_JUMPS)
    : -1 },
  { "(!ISA_MIPS1) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_MIPS1) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_MIPS1) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "(ISA_HAS_COND_TRAP) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 944 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_COND_TRAP) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 944 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_COND_TRAP) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!HONOR_NANS (V2SFmode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "(ISA_HAS_CLZ_CLO) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2479 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CLZ_CLO) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2479 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CLZ_CLO) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(ISA_HAS_LWXS) && (Pmode == DImode)",
    __builtin_constant_p (
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
#line 3043 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "GENERATE_MIPS16E",
    __builtin_constant_p 
#line 3043 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MIPS16E)
    ? (int) 
#line 3043 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MIPS16E)
    : -1 },
#line 1734 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "mips_mulsidi3_gen_fn (ZERO_EXTEND) != NULL",
    __builtin_constant_p 
#line 1734 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_mulsidi3_gen_fn (ZERO_EXTEND) != NULL)
    ? (int) 
#line 1734 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_mulsidi3_gen_fn (ZERO_EXTEND) != NULL)
    : -1 },
#line 4347 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && ((INTVAL (operands[1]) < 0\n\
	&& INTVAL (operands[1]) >= -0x80)\n\
       || (INTVAL (operands[1]) >= 32\n\
	   && INTVAL (operands[1]) <= 31 + 0x7f))",
    __builtin_constant_p 
#line 4347 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x80)
       || (INTVAL (operands[1]) >= 32
	   && INTVAL (operands[1]) <= 31 + 0x7f)))
    ? (int) 
#line 4347 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x80)
       || (INTVAL (operands[1]) >= 32
	   && INTVAL (operands[1]) <= 31 + 0x7f)))
    : -1 },
  { "(ISA_HAS_NMADD3_NMSUB3 (V2SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && HONOR_SIGNED_ZEROS (V2SFmode)\n\
   && !HONOR_NANS (V2SFmode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2203 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (V2SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2203 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (V2SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 3972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && TARGET_MIPS16\n\
   && (register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 3972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    ? (int) 
#line 3972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    : -1 },
#line 3450 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && TARGET_64BIT && TARGET_DOUBLE_FLOAT",
    __builtin_constant_p 
#line 3450 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_64BIT && TARGET_DOUBLE_FLOAT)
    ? (int) 
#line 3450 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_64BIT && TARGET_DOUBLE_FLOAT)
    : -1 },
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_SEQ_SNE",
    __builtin_constant_p 
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEQ_SNE)
    ? (int) 
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEQ_SNE)
    : -1 },
  { "(HAVE_AS_TLS && !TARGET_MIPS16) && (Pmode == SImode)",
    __builtin_constant_p (
#line 6455 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 6455 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 2479 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_CLZ_CLO",
    __builtin_constant_p 
#line 2479 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CLZ_CLO)
    ? (int) 
#line 2479 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CLZ_CLO)
    : -1 },
#line 5062 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && TARGET_MIPS16",
    __builtin_constant_p 
#line 5062 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16)
    ? (int) 
#line 5062 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16)
    : -1 },
#line 4400 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16\n\
   && (register_operand (operands[0], SFmode)\n\
       || register_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 4400 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], SFmode)
       || register_operand (operands[1], SFmode)))
    ? (int) 
#line 4400 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], SFmode)
       || register_operand (operands[1], SFmode)))
    : -1 },
  { "(TARGET_64BIT && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)) && ( reload_completed && !TARGET_FIX_R4000)",
    __builtin_constant_p (
#line 1994 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)) && 
#line 1996 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && !TARGET_FIX_R4000))
    ? (int) (
#line 1994 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)) && 
#line 1996 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && !TARGET_FIX_R4000))
    : -1 },
#line 1387 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MUL3 && peep2_reg_dead_p (2, operands[0])",
    __builtin_constant_p 
#line 1387 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3 && peep2_reg_dead_p (2, operands[0]))
    ? (int) 
#line 1387 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3 && peep2_reg_dead_p (2, operands[0]))
    : -1 },
#line 2852 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !ISA_HAS_EXT_INS && reload_completed",
    __builtin_constant_p 
#line 2852 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !ISA_HAS_EXT_INS && reload_completed)
    ? (int) 
#line 2852 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !ISA_HAS_EXT_INS && reload_completed)
    : -1 },
  { "(mips_current_loadgp_style () == LOADGP_RTP) && (Pmode == SImode)",
    __builtin_constant_p (
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 5323 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_BBIT && UINTVAL (operands[2]) < GET_MODE_BITSIZE (SImode)",
    __builtin_constant_p 
#line 5323 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BBIT && UINTVAL (operands[2]) < GET_MODE_BITSIZE (SImode))
    ? (int) 
#line 5323 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BBIT && UINTVAL (operands[2]) < GET_MODE_BITSIZE (SImode))
    : -1 },
  { "(TARGET_MIPS16) && (Pmode == DImode)",
    __builtin_constant_p (
#line 3892 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 3892 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(TARGET_64BIT && !TARGET_MIPS16) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2939 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2939 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "((mips_current_loadgp_style () == LOADGP_ABSOLUTE) && (Pmode == SImode)) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p ((
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 4733 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) ((
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 4733 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
#line 1978 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MULHI",
    __builtin_constant_p 
#line 1978 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MULHI)
    ? (int) 
#line 1978 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MULHI)
    : -1 },
#line 2838 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && ISA_HAS_EXT_INS",
    __builtin_constant_p 
#line 2838 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && ISA_HAS_EXT_INS)
    ? (int) 
#line 2838 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && ISA_HAS_EXT_INS)
    : -1 },
#line 2495 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_POP",
    __builtin_constant_p 
#line 2495 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_POP)
    ? (int) 
#line 2495 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_POP)
    : -1 },
#line 1031 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && ((INTVAL (operands[1]) > 0x7f\n\
	&& INTVAL (operands[1]) <= 0x7f + 0x7f)\n\
       || (INTVAL (operands[1]) < - 0x80\n\
	   && INTVAL (operands[1]) >= - 0x80 - 0x80))",
    __builtin_constant_p 
#line 1031 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) > 0x7f
	&& INTVAL (operands[1]) <= 0x7f + 0x7f)
       || (INTVAL (operands[1]) < - 0x80
	   && INTVAL (operands[1]) >= - 0x80 - 0x80)))
    ? (int) 
#line 1031 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) > 0x7f
	&& INTVAL (operands[1]) <= 0x7f + 0x7f)
       || (INTVAL (operands[1]) < - 0x80
	   && INTVAL (operands[1]) >= - 0x80 - 0x80)))
    : -1 },
#line 1428 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MACC && !ISA_HAS_MUL3",
    __builtin_constant_p 
#line 1428 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && !ISA_HAS_MUL3)
    ? (int) 
#line 1428 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && !ISA_HAS_MUL3)
    : -1 },
  { "(ISA_HAS_NMADD3_NMSUB3 (V2SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && !HONOR_SIGNED_ZEROS (V2SFmode)\n\
   && !HONOR_NANS (V2SFmode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2231 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (V2SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2231 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (V2SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 1869 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && ISA_HAS_MULS",
    __builtin_constant_p 
#line 1869 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && ISA_HAS_MULS)
    ? (int) 
#line 1869 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && ISA_HAS_MULS)
    : -1 },
  { "(ISA_HAS_NMADD3_NMSUB3 (DFmode)\n\
   && TARGET_FUSED_MADD\n\
   && HONOR_SIGNED_ZEROS (DFmode)\n\
   && !HONOR_NANS (DFmode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2203 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (DFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2203 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (DFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(TARGET_64BIT && TARGET_MIPS16) && ( reload_completed)",
    __builtin_constant_p (
#line 1152 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16) && 
#line 1154 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) (
#line 1152 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16) && 
#line 1154 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
#line 3633 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_CINS\n\
   && mask_low_and_shift_p (SImode, operands[3], operands[2], 32)",
    __builtin_constant_p 
#line 3633 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CINS
   && mask_low_and_shift_p (SImode, operands[3], operands[2], 32))
    ? (int) 
#line 3633 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CINS
   && mask_low_and_shift_p (SImode, operands[3], operands[2], 32))
    : -1 },
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE",
    __builtin_constant_p 
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE)
    ? (int) 
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE)
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS) && ( epilogue_completed)",
    __builtin_constant_p (
#line 3715 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS) && 
#line 3717 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( epilogue_completed))
    ? (int) (
#line 3715 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS) && 
#line 3717 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( epilogue_completed))
    : -1 },
#line 5837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_USE_GOT",
    __builtin_constant_p 
#line 5837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_USE_GOT)
    ? (int) 
#line 5837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_USE_GOT)
    : -1 },
#line 6194 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "reload_completed && TARGET_SPLIT_CALLS",
    __builtin_constant_p 
#line 6194 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && TARGET_SPLIT_CALLS)
    ? (int) 
#line 6194 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && TARGET_SPLIT_CALLS)
    : -1 },
#line 3242 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && !ISA_HAS_TRUNC_W",
    __builtin_constant_p 
#line 3242 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !ISA_HAS_TRUNC_W)
    ? (int) 
#line 3242 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !ISA_HAS_TRUNC_W)
    : -1 },
  { "(mips_must_initialize_gp_p ()) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5867 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_must_initialize_gp_p ()) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5867 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_must_initialize_gp_p ()) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 3692 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && mips_mem_fits_mode_p (SImode, operands[0])",
    __builtin_constant_p 
#line 3692 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (SImode, operands[0]))
    ? (int) 
#line 3692 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (SImode, operands[0]))
    : -1 },
#line 5803 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "! TARGET_64BIT",
    __builtin_constant_p 
#line 5803 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(! TARGET_64BIT)
    ? (int) 
#line 5803 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(! TARGET_64BIT)
    : -1 },
#line 1513 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MACC",
    __builtin_constant_p 
#line 1513 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC)
    ? (int) 
#line 1513 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC)
    : -1 },
#line 4541 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && INTVAL (operands[1]) < 0",
    __builtin_constant_p 
#line 4541 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && INTVAL (operands[1]) < 0)
    ? (int) 
#line 4541 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && INTVAL (operands[1]) < 0)
    : -1 },
  { "(!TARGET_FIX_VR4120) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 3159 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_MIPS16 && ISA_HAS_EXTS",
    __builtin_constant_p 
#line 3159 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && ISA_HAS_EXTS)
    ? (int) 
#line 3159 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && ISA_HAS_EXTS)
    : -1 },
  { "((TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && (Pmode == DImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 3823 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 3823 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(TARGET_64BIT && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)) && ( reload_completed && !TARGET_FIX_R4000)",
    __builtin_constant_p (
#line 1994 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)) && 
#line 1996 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && !TARGET_FIX_R4000))
    ? (int) (
#line 1994 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)) && 
#line 1996 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && !TARGET_FIX_R4000))
    : -1 },
  { "(ISA_HAS_CONDMOVE) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 6334 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 6334 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 3982 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_MIPS16\n\
   && (register_operand (operands[0], DImode)\n\
       || reg_or_0_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 3982 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || reg_or_0_operand (operands[1], DImode)))
    ? (int) 
#line 3982 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || reg_or_0_operand (operands[1], DImode)))
    : -1 },
#line 1465 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "GENERATE_MADD_MSUB && !TARGET_MIPS16",
    __builtin_constant_p 
#line 1465 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MADD_MSUB && !TARGET_MIPS16)
    ? (int) 
#line 1465 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MADD_MSUB && !TARGET_MIPS16)
    : -1 },
#line 3769 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS && cse_not_expected",
    __builtin_constant_p 
#line 3769 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS && cse_not_expected)
    ? (int) 
#line 3769 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS && cse_not_expected)
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && (Pmode == SImode)",
    __builtin_constant_p (
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(!TARGET_MIPS16 && and_operands_ok (DImode, operands[1], operands[2])) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && and_operands_ok (DImode, operands[1], operands[2])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && and_operands_ok (DImode, operands[1], operands[2])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3009 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4007 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && TARGET_MIPS16 && reload_completed\n\
   && !TARGET_DEBUG_D_MODE\n\
   && ((INTVAL (operands[1]) < 0\n\
	&& INTVAL (operands[1]) >= -0x10)\n\
       || (INTVAL (operands[1]) >= 32 * 8\n\
	   && INTVAL (operands[1]) <= 31 * 8 + 0x8)\n\
       || (INTVAL (operands[1]) >= 0\n\
	   && INTVAL (operands[1]) < 32 * 8\n\
	   && (INTVAL (operands[1]) & 7) != 0))",
    __builtin_constant_p 
#line 4007 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16 && reload_completed
   && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x10)
       || (INTVAL (operands[1]) >= 32 * 8
	   && INTVAL (operands[1]) <= 31 * 8 + 0x8)
       || (INTVAL (operands[1]) >= 0
	   && INTVAL (operands[1]) < 32 * 8
	   && (INTVAL (operands[1]) & 7) != 0)))
    ? (int) 
#line 4007 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16 && reload_completed
   && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x10)
       || (INTVAL (operands[1]) >= 32 * 8
	   && INTVAL (operands[1]) <= 31 * 8 + 0x8)
       || (INTVAL (operands[1]) >= 0
	   && INTVAL (operands[1]) < 32 * 8
	   && (INTVAL (operands[1]) & 7) != 0)))
    : -1 },
  { "(ISA_HAS_SYNCI) && (Pmode == SImode)",
    __builtin_constant_p (
#line 4881 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SYNCI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 4881 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SYNCI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "((ISA_HAS_FP_CONDMOVE) && (TARGET_HARD_FLOAT)) && (TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF)",
    __builtin_constant_p ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT)) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF))
    ? (int) ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT)) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF))
    : -1 },
  { "(GENERATE_LL_SC) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 522 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
(GENERATE_LL_SC) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 522 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
(GENERATE_LL_SC) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!HONOR_NANS (SFmode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 1929 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!ISA_HAS_MULHI",
    __builtin_constant_p 
#line 1929 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_MULHI)
    ? (int) 
#line 1929 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_MULHI)
    : -1 },
  { "(ISA_HAS_SEB_SEH) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEB_SEH) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEB_SEH) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 2594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && and_operands_ok (SImode, operands[1], operands[2])",
    __builtin_constant_p 
#line 2594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && and_operands_ok (SImode, operands[1], operands[2]))
    ? (int) 
#line 2594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && and_operands_ok (SImode, operands[1], operands[2]))
    : -1 },
#line 1763 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && TARGET_FIX_R4000",
    __builtin_constant_p 
#line 1763 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_FIX_R4000)
    ? (int) 
#line 1763 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_FIX_R4000)
    : -1 },
  { "(TARGET_SB1) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SB1) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SB1) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 592 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT",
    __builtin_constant_p 
#line 592 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT)
    ? (int) 
#line 592 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT)
    : -1 },
  { "((HAVE_AS_TLS && !TARGET_MIPS16) && (Pmode == DImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 6438 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 6440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 6438 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 6440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
#line 1790 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_FIX_R4000 && ISA_HAS_EXT_INS && reload_completed",
    __builtin_constant_p 
#line 1790 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000 && ISA_HAS_EXT_INS && reload_completed)
    ? (int) 
#line 1790 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000 && ISA_HAS_EXT_INS && reload_completed)
    : -1 },
#line 1057 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && REGNO (operands[0]) != REGNO (operands[1])\n\
   && ((INTVAL (operands[2]) > 0x7\n\
	&& INTVAL (operands[2]) <= 0x7 + 0x7f)\n\
       || (INTVAL (operands[2]) < - 0x8\n\
	   && INTVAL (operands[2]) >= - 0x8 - 0x80))",
    __builtin_constant_p 
#line 1057 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && REGNO (operands[0]) != REGNO (operands[1])
   && ((INTVAL (operands[2]) > 0x7
	&& INTVAL (operands[2]) <= 0x7 + 0x7f)
       || (INTVAL (operands[2]) < - 0x8
	   && INTVAL (operands[2]) >= - 0x8 - 0x80)))
    ? (int) 
#line 1057 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && REGNO (operands[0]) != REGNO (operands[1])
   && ((INTVAL (operands[2]) > 0x7
	&& INTVAL (operands[2]) <= 0x7 + 0x7f)
       || (INTVAL (operands[2]) < - 0x8
	   && INTVAL (operands[2]) >= - 0x8 - 0x80)))
    : -1 },
#line 620 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
  { "ISA_HAS_DSPR2 && !TARGET_64BIT",
    __builtin_constant_p 
#line 620 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
(ISA_HAS_DSPR2 && !TARGET_64BIT)
    ? (int) 
#line 620 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
(ISA_HAS_DSPR2 && !TARGET_64BIT)
    : -1 },
#line 3195 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT && ISA_HAS_TRUNC_W",
    __builtin_constant_p 
#line 3195 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT && ISA_HAS_TRUNC_W)
    ? (int) 
#line 3195 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT && ISA_HAS_TRUNC_W)
    : -1 },
  { "(TARGET_64BIT && !TARGET_MIPS16 && !ISA_HAS_EXTS) && ( reload_completed)",
    __builtin_constant_p (
#line 3128 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && !ISA_HAS_EXTS) && 
#line 3130 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) (
#line 3128 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && !ISA_HAS_EXTS) && 
#line 3130 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
#line 1482 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS3900 && !TARGET_MIPS16",
    __builtin_constant_p 
#line 1482 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS3900 && !TARGET_MIPS16)
    ? (int) 
#line 1482 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS3900 && !TARGET_MIPS16)
    : -1 },
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_FIX_VR4120",
    __builtin_constant_p 
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120)
    ? (int) 
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120)
    : -1 },
  { "(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && (!TARGET_64BIT && TARGET_LOONGSON_VECTORS)",
    __builtin_constant_p (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_LOONGSON_VECTORS))
    ? (int) (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_LOONGSON_VECTORS))
    : -1 },
#line 2028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && !TARGET_FIX_R4000\n\
   && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)",
    __builtin_constant_p 
#line 2028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_FIX_R4000
   && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    ? (int) 
#line 2028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_FIX_R4000
   && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 52 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 52 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && reload_completed",
    __builtin_constant_p 
#line 4529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && reload_completed)
    ? (int) 
#line 4529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && reload_completed)
    : -1 },
  { "((ISA_HAS_CONDMOVE) && (TARGET_64BIT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 6304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 600 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 6304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 600 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16\n\
   && (register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    ? (int) 
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    : -1 },
  { "(ISA_HAS_BBIT && UINTVAL (operands[2]) < GET_MODE_BITSIZE (DImode)) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5323 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BBIT && UINTVAL (operands[2]) < GET_MODE_BITSIZE (DImode)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5323 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BBIT && UINTVAL (operands[2]) < GET_MODE_BITSIZE (DImode)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && ( reload_completed && REG_P (operands[1]))",
    __builtin_constant_p (
#line 3054 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && 
#line 3058 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && REG_P (operands[1])))
    ? (int) (
#line 3054 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E) && 
#line 3058 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && REG_P (operands[1])))
    : -1 },
  { "(mips_current_loadgp_style () == LOADGP_RTP) && (Pmode == DImode)",
    __builtin_constant_p (
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 521 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
(TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 521 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
(TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 3962 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && !TARGET_MIPS16\n\
   && (register_operand (operands[0], DImode)\n\
       || reg_or_0_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 3962 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && !TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || reg_or_0_operand (operands[1], DImode)))
    ? (int) 
#line 3962 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && !TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || reg_or_0_operand (operands[1], DImode)))
    : -1 },
  { "(!TARGET_FIX_R4000) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 1398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_R4000) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 1398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_R4000) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(TARGET_MIPS16) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5472 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5472 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(TARGET_MIPS16 && and_operands_ok (DImode, operands[1], operands[2])) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && and_operands_ok (DImode, operands[1], operands[2])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && and_operands_ok (DImode, operands[1], operands[2])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "((ISA_HAS_FP4) && (Pmode == DImode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "(TARGET_HARD_FLOAT) && (!TARGET_64BIT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 140 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
  { "TUNE_LOONGSON_2EF",
    __builtin_constant_p 
#line 140 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
(TUNE_LOONGSON_2EF)
    ? (int) 
#line 140 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
(TUNE_LOONGSON_2EF)
    : -1 },
  { "(!TARGET_4300_MUL_FIX) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 1248 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_4300_MUL_FIX) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 1248 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_4300_MUL_FIX) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 3589 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16",
    __builtin_constant_p 
#line 3589 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16)
    ? (int) 
#line 3589 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16)
    : -1 },
  { "(ISA_HAS_NMADD4_NMSUB4 (SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && !HONOR_SIGNED_ZEROS (SFmode)\n\
   && !HONOR_NANS (SFmode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "((ISA_HAS_FP4) && (Pmode == SImode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 5709 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "mips_can_use_return_insn ()",
    __builtin_constant_p 
#line 5709 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_can_use_return_insn ())
    ? (int) 
#line 5709 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_can_use_return_insn ())
    : -1 },
  { "(!TARGET_MIPS16 && mips_mem_fits_mode_p (DImode, operands[0])) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3692 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (DImode, operands[0])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3692 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (DImode, operands[0])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 1198 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
  { "ISA_HAS_DSP && !TARGET_64BIT",
    __builtin_constant_p 
#line 1198 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP && !TARGET_64BIT)
    ? (int) 
#line 1198 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP && !TARGET_64BIT)
    : -1 },
#line 5531 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && !TARGET_ABSOLUTE_JUMPS",
    __builtin_constant_p 
#line 5531 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !TARGET_ABSOLUTE_JUMPS)
    ? (int) 
#line 5531 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !TARGET_ABSOLUTE_JUMPS)
    : -1 },
  { "(!TARGET_MIPS16) && (Pmode == DImode)",
    __builtin_constant_p (
#line 3883 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 3883 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(TARGET_SB1 && (!TARGET_FIX_SB1 || flag_unsafe_math_optimizations)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2251 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SB1 && (!TARGET_FIX_SB1 || flag_unsafe_math_optimizations)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2251 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SB1 && (!TARGET_FIX_SB1 || flag_unsafe_math_optimizations)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && (TARGET_64BIT && TARGET_FLOAT64)",
    __builtin_constant_p (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_FLOAT64))
    ? (int) (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_FLOAT64))
    : -1 },
#line 2800 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_EXTS && TARGET_64BIT && UINTVAL (operands[2]) < 32",
    __builtin_constant_p 
#line 2800 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && TARGET_64BIT && UINTVAL (operands[2]) < 32)
    ? (int) 
#line 2800 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && TARGET_64BIT && UINTVAL (operands[2]) < 32)
    : -1 },
  { "(ISA_HAS_SEQ_SNE) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4797 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_CPRESTORE_DIRECTIVE || operands[2] == pic_offset_table_rtx",
    __builtin_constant_p 
#line 4797 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_CPRESTORE_DIRECTIVE || operands[2] == pic_offset_table_rtx)
    ? (int) 
#line 4797 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_CPRESTORE_DIRECTIVE || operands[2] == pic_offset_table_rtx)
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V4UQQmode)\n\
       || reg_or_0_operand (operands[1], V4UQQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V4UQQmode)
       || reg_or_0_operand (operands[1], V4UQQmode))) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V4UQQmode)
       || reg_or_0_operand (operands[1], V4UQQmode))) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "(ISA_HAS_NMADD4_NMSUB4 (V2SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && HONOR_SIGNED_ZEROS (V2SFmode)\n\
   && !HONOR_NANS (V2SFmode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (V2SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (V2SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "((ISA_HAS_LWXS) && (TARGET_DSP)) && (Pmode == SImode)",
    __builtin_constant_p ((
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) ((
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(ISA_HAS_BADDU && TARGET_64BIT) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 1189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && TARGET_64BIT) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 1189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && TARGET_64BIT) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2122 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2122 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 2014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)",
    __builtin_constant_p 
#line 2014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    ? (int) 
#line 2014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    : -1 },
  { "(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && (!TARGET_64BIT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 4462 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && !TARGET_MIPS16\n\
   && (register_operand (operands[0], TImode)\n\
       || reg_or_0_operand (operands[1], TImode))",
    __builtin_constant_p 
#line 4462 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_MIPS16
   && (register_operand (operands[0], TImode)
       || reg_or_0_operand (operands[1], TImode)))
    ? (int) 
#line 4462 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_MIPS16
   && (register_operand (operands[0], TImode)
       || reg_or_0_operand (operands[1], TImode)))
    : -1 },
#line 3903 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && TARGET_USE_GOT && reload_completed",
    __builtin_constant_p 
#line 3903 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_USE_GOT && reload_completed)
    ? (int) 
#line 3903 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_USE_GOT && reload_completed)
    : -1 },
#line 3671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && mips_mem_fits_mode_p (SImode, operands[1])",
    __builtin_constant_p 
#line 3671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (SImode, operands[1]))
    ? (int) 
#line 3671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (SImode, operands[1]))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V4QQmode)\n\
       || reg_or_0_operand (operands[1], V4QQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V4QQmode)
       || reg_or_0_operand (operands[1], V4QQmode))) && 
#line 612 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V4QQmode)
       || reg_or_0_operand (operands[1], V4QQmode))) && 
#line 612 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
#line 5987 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_SIBCALLS",
    __builtin_constant_p 
#line 5987 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SIBCALLS)
    ? (int) 
#line 5987 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SIBCALLS)
    : -1 },
  { "(ISA_HAS_POP) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2495 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_POP) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2495 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_POP) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(mips_use_ins_ext_p (operands[1], INTVAL (operands[2]),\n\
		       INTVAL (operands[3]))) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3566 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[1], INTVAL (operands[2]),
		       INTVAL (operands[3]))) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3566 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[1], INTVAL (operands[2]),
		       INTVAL (operands[3]))) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 1674 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MUL3 && peep2_reg_dead_p (3, operands[1])",
    __builtin_constant_p 
#line 1674 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3 && peep2_reg_dead_p (3, operands[1]))
    ? (int) 
#line 1674 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3 && peep2_reg_dead_p (3, operands[1]))
    : -1 },
#line 4507 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && TARGET_MIPS16\n\
   && (register_operand (operands[0], TFmode)\n\
       || register_operand (operands[1], TFmode))",
    __builtin_constant_p 
#line 4507 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_MIPS16
   && (register_operand (operands[0], TFmode)
       || register_operand (operands[1], TFmode)))
    ? (int) 
#line 4507 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_MIPS16
   && (register_operand (operands[0], TFmode)
       || register_operand (operands[1], TFmode)))
    : -1 },
#line 4272 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && ((INTVAL (operands[1]) < 0\n\
	&& INTVAL (operands[1]) >= -0x80)\n\
       || (INTVAL (operands[1]) >= 32 * 2\n\
	   && INTVAL (operands[1]) <= 31 * 2 + 0x7e)\n\
       || (INTVAL (operands[1]) >= 0\n\
	   && INTVAL (operands[1]) < 32 * 2\n\
	   && (INTVAL (operands[1]) & 1) != 0))",
    __builtin_constant_p 
#line 4272 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x80)
       || (INTVAL (operands[1]) >= 32 * 2
	   && INTVAL (operands[1]) <= 31 * 2 + 0x7e)
       || (INTVAL (operands[1]) >= 0
	   && INTVAL (operands[1]) < 32 * 2
	   && (INTVAL (operands[1]) & 1) != 0)))
    ? (int) 
#line 4272 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x80)
       || (INTVAL (operands[1]) >= 32 * 2
	   && INTVAL (operands[1]) <= 31 * 2 + 0x7e)
       || (INTVAL (operands[1]) >= 0
	   && INTVAL (operands[1]) < 32 * 2
	   && (INTVAL (operands[1]) & 1) != 0)))
    : -1 },
  { "(TARGET_HARD_FLOAT) && (TARGET_64BIT && TARGET_FLOAT64)",
    __builtin_constant_p (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_FLOAT64))
    ? (int) (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_FLOAT64))
    : -1 },
  { "(!TARGET_MIPS16) && (Pmode == SImode)",
    __builtin_constant_p (
#line 3883 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 3883 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 2028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && !TARGET_FIX_R4000\n\
   && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)",
    __builtin_constant_p 
#line 2028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_FIX_R4000
   && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    ? (int) 
#line 2028 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_FIX_R4000
   && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    : -1 },
#line 1641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MUL3 && peep2_reg_dead_p (2, operands[1])",
    __builtin_constant_p 
#line 1641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3 && peep2_reg_dead_p (2, operands[1]))
    ? (int) 
#line 1641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MUL3 && peep2_reg_dead_p (2, operands[1]))
    : -1 },
#line 6334 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_CONDMOVE",
    __builtin_constant_p 
#line 6334 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE)
    ? (int) 
#line 6334 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE)
    : -1 },
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "reload_completed && !TARGET_64BIT\n\
   && mips_split_64bit_move_p (operands[0], operands[1])",
    __builtin_constant_p 
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && !TARGET_64BIT
   && mips_split_64bit_move_p (operands[0], operands[1]))
    ? (int) 
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && !TARGET_64BIT
   && mips_split_64bit_move_p (operands[0], operands[1]))
    : -1 },
#line 1179 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_BADDU && !BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 1179 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && !BYTES_BIG_ENDIAN)
    ? (int) 
#line 1179 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && !BYTES_BIG_ENDIAN)
    : -1 },
#line 2777 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_MIPS16 && IN_RANGE (INTVAL (operands[2]), 32, 63)",
    __builtin_constant_p 
#line 2777 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && IN_RANGE (INTVAL (operands[2]), 32, 63))
    ? (int) 
#line 2777 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && IN_RANGE (INTVAL (operands[2]), 32, 63))
    : -1 },
  { "(ISA_HAS_NMADD3_NMSUB3 (SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && HONOR_SIGNED_ZEROS (SFmode)\n\
   && !HONOR_NANS (SFmode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2203 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2203 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 1153 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
  { "ISA_HAS_DSP",
    __builtin_constant_p 
#line 1153 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP)
    ? (int) 
#line 1153 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP)
    : -1 },
  { "(mips_use_ins_ext_p (operands[0], INTVAL (operands[1]),\n\
		       INTVAL (operands[2]))) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3615 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[0], INTVAL (operands[1]),
		       INTVAL (operands[2]))) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3615 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[0], INTVAL (operands[1]),
		       INTVAL (operands[2]))) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16\n\
   && (register_operand (operands[0], SImode)\n\
       || reg_or_0_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], SImode)
       || reg_or_0_operand (operands[1], SImode)))
    ? (int) 
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], SImode)
       || reg_or_0_operand (operands[1], SImode)))
    : -1 },
  { "((TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && (TARGET_64BIT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 5366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(TARGET_CALL_CLOBBERED_GP) && ( epilogue_completed)",
    __builtin_constant_p (
#line 5850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_CALL_CLOBBERED_GP) && 
#line 5852 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( epilogue_completed))
    ? (int) (
#line 5850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_CALL_CLOBBERED_GP) && 
#line 5852 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( epilogue_completed))
    : -1 },
#line 45 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
  { "GENERATE_SYNC",
    __builtin_constant_p 
#line 45 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
(GENERATE_SYNC)
    ? (int) 
#line 45 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
(GENERATE_SYNC)
    : -1 },
  { "(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 4247 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16\n\
   && (register_operand (operands[0], HImode)\n\
       || reg_or_0_operand (operands[1], HImode))",
    __builtin_constant_p 
#line 4247 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], HImode)
       || reg_or_0_operand (operands[1], HImode)))
    ? (int) 
#line 4247 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], HImode)
       || reg_or_0_operand (operands[1], HImode)))
    : -1 },
  { "((TARGET_MIPS16) && (TARGET_64BIT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 5472 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 5472 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!HONOR_NANS (DFmode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "((ISA_HAS_FP4) && (Pmode == SImode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(!TARGET_4300_MUL_FIX) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 1248 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_4300_MUL_FIX) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 1248 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_4300_MUL_FIX) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "((ISA_HAS_CONDMOVE) && (TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 6304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 6304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CONDMOVE) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(reload_completed) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2349 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2349 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
  { "TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT",
    __builtin_constant_p 
#line 630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)
    ? (int) 
#line 630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)
    : -1 },
  { "((!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && (TARGET_64BIT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 5388 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !ISA_HAS_SEQ_SNE) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(TARGET_64BIT && !ISA_HAS_EXT_INS) && ( reload_completed && REG_P (operands[1]))",
    __builtin_constant_p (
#line 2822 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !ISA_HAS_EXT_INS) && 
#line 2826 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && REG_P (operands[1])))
    ? (int) (
#line 2822 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !ISA_HAS_EXT_INS) && 
#line 2826 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && REG_P (operands[1])))
    : -1 },
#line 1734 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "mips_mulsidi3_gen_fn (SIGN_EXTEND) != NULL",
    __builtin_constant_p 
#line 1734 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_mulsidi3_gen_fn (SIGN_EXTEND) != NULL)
    ? (int) 
#line 1734 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_mulsidi3_gen_fn (SIGN_EXTEND) != NULL)
    : -1 },
#line 6213 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_SPLIT_CALLS",
    __builtin_constant_p 
#line 6213 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SPLIT_CALLS)
    ? (int) 
#line 6213 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SPLIT_CALLS)
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V2HQmode)\n\
       || register_operand (operands[1], V2HQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2HQmode)
       || register_operand (operands[1], V2HQmode))) && 
#line 608 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2HQmode)
       || register_operand (operands[1], V2HQmode))) && 
#line 608 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(ISA_HAS_SYNCI) && (Pmode == DImode)",
    __builtin_constant_p (
#line 4881 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SYNCI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 4881 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SYNCI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && (Pmode == DImode)",
    __builtin_constant_p (
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "((mips_current_loadgp_style () == LOADGP_ABSOLUTE) && (Pmode == DImode)) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p ((
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 4733 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) ((
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 4733 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
  { "(ISA_HAS_CINS\n\
   && mask_low_and_shift_p (DImode, operands[3], operands[2], 32)) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3633 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CINS
   && mask_low_and_shift_p (DImode, operands[3], operands[2], 32)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3633 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CINS
   && mask_low_and_shift_p (DImode, operands[3], operands[2], 32)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V4QImode)\n\
       || reg_or_0_operand (operands[1], V4QImode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V4QImode)
       || reg_or_0_operand (operands[1], V4QImode))) && 
#line 607 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V4QImode)
       || reg_or_0_operand (operands[1], V4QImode))) && 
#line 607 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 595 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 595 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 3992 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && TARGET_MIPS16\n\
   && (register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 3992 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    ? (int) 
#line 3992 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_MIPS16
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V4QQmode)\n\
       || register_operand (operands[1], V4QQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V4QQmode)
       || register_operand (operands[1], V4QQmode))) && 
#line 612 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V4QQmode)
       || register_operand (operands[1], V4QQmode))) && 
#line 612 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
#line 4390 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_SOFT_FLOAT && !TARGET_MIPS16\n\
   && (register_operand (operands[0], SFmode)\n\
       || reg_or_0_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 4390 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SOFT_FLOAT && !TARGET_MIPS16
   && (register_operand (operands[0], SFmode)
       || reg_or_0_operand (operands[1], SFmode)))
    ? (int) 
#line 4390 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SOFT_FLOAT && !TARGET_MIPS16
   && (register_operand (operands[0], SFmode)
       || reg_or_0_operand (operands[1], SFmode)))
    : -1 },
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT",
    __builtin_constant_p 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT)
    ? (int) 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT)
    : -1 },
  { "(ISA_HAS_FP4 && flag_unsafe_math_optimizations) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2432 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4 && flag_unsafe_math_optimizations) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2432 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4 && flag_unsafe_math_optimizations) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 2040 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && TARGET_FIX_R4000\n\
   && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)",
    __builtin_constant_p 
#line 2040 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_FIX_R4000
   && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    ? (int) 
#line 2040 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_FIX_R4000
   && !(SIGN_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    : -1 },
#line 1580 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MACC && reload_completed",
    __builtin_constant_p 
#line 1580 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && reload_completed)
    ? (int) 
#line 1580 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && reload_completed)
    : -1 },
#line 6413 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "operands[1] == stack_pointer_rtx\n\
   && mips16e_save_restore_pattern_p (operands[0], INTVAL (operands[2]), NULL)",
    __builtin_constant_p 
#line 6413 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(operands[1] == stack_pointer_rtx
   && mips16e_save_restore_pattern_p (operands[0], INTVAL (operands[2]), NULL))
    ? (int) 
#line 6413 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(operands[1] == stack_pointer_rtx
   && mips16e_save_restore_pattern_p (operands[0], INTVAL (operands[2]), NULL))
    : -1 },
#line 3074 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_SEB_SEH",
    __builtin_constant_p 
#line 3074 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEB_SEH)
    ? (int) 
#line 3074 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_SEB_SEH)
    : -1 },
#line 5083 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && INTVAL (operands[2]) > 8\n\
   && INTVAL (operands[2]) <= 16",
    __builtin_constant_p 
#line 5083 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && INTVAL (operands[2]) > 8
   && INTVAL (operands[2]) <= 16)
    ? (int) 
#line 5083 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && INTVAL (operands[2]) > 8
   && INTVAL (operands[2]) <= 16)
    : -1 },
#line 1189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_BADDU && TARGET_64BIT",
    __builtin_constant_p 
#line 1189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && TARGET_64BIT)
    ? (int) 
#line 1189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && TARGET_64BIT)
    : -1 },
  { "((mips_current_loadgp_style () == LOADGP_NEWABI) && (Pmode == DImode)) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p ((
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 4716 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) ((
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 4716 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
  { "(GENERATE_MIPS16E) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 2998 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MIPS16E) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 2998 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(GENERATE_MIPS16E) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V2HAmode)\n\
       || reg_or_0_operand (operands[1], V2HAmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2HAmode)
       || reg_or_0_operand (operands[1], V2HAmode))) && 
#line 610 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2HAmode)
       || reg_or_0_operand (operands[1], V2HAmode))) && 
#line 610 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(ISA_HAS_PREFETCHX && TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT) && (Pmode == DImode)",
    __builtin_constant_p (
#line 6268 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_PREFETCHX && TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 6268 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_PREFETCHX && TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
#line 3566 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "mips_use_ins_ext_p (operands[1], INTVAL (operands[2]),\n\
		       INTVAL (operands[3]))",
    __builtin_constant_p 
#line 3566 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[1], INTVAL (operands[2]),
		       INTVAL (operands[3])))
    ? (int) 
#line 3566 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[1], INTVAL (operands[2]),
		       INTVAL (operands[3])))
    : -1 },
#line 2014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)",
    __builtin_constant_p 
#line 2014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    ? (int) 
#line 2014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    : -1 },
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT",
    __builtin_constant_p 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)
    ? (int) 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)
    : -1 },
#line 4176 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_8CC && TARGET_HARD_FLOAT",
    __builtin_constant_p 
#line 4176 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_8CC && TARGET_HARD_FLOAT)
    ? (int) 
#line 4176 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_8CC && TARGET_HARD_FLOAT)
    : -1 },
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && TARGET_FLOAT64",
    __builtin_constant_p 
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_FLOAT64)
    ? (int) 
#line 651 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && TARGET_FLOAT64)
    : -1 },
#line 2822 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !ISA_HAS_EXT_INS",
    __builtin_constant_p 
#line 2822 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !ISA_HAS_EXT_INS)
    ? (int) 
#line 2822 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !ISA_HAS_EXT_INS)
    : -1 },
#line 534 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
  { "GENERATE_LL_SC",
    __builtin_constant_p 
#line 534 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
(GENERATE_LL_SC)
    ? (int) 
#line 534 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
(GENERATE_LL_SC)
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V2UHQmode)\n\
       || register_operand (operands[1], V2UHQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2UHQmode)
       || register_operand (operands[1], V2UHQmode))) && 
#line 609 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2UHQmode)
       || register_operand (operands[1], V2UHQmode))) && 
#line 609 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(mips_split_symbol (operands[2], operands[1], MAX_MACHINE_MODE, NULL)) && (Pmode == SImode)",
    __builtin_constant_p (
#line 3925 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_split_symbol (operands[2], operands[1], MAX_MACHINE_MODE, NULL)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 3925 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_split_symbol (operands[2], operands[1], MAX_MACHINE_MODE, NULL)) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && (!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 4696 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_MXHC1) && 
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 2069 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "(TARGET_MAD || ISA_HAS_MACC || GENERATE_MADD_MSUB || ISA_HAS_DSP)\n\
   && !TARGET_64BIT",
    __builtin_constant_p 
#line 2069 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
((TARGET_MAD || ISA_HAS_MACC || GENERATE_MADD_MSUB || ISA_HAS_DSP)
   && !TARGET_64BIT)
    ? (int) 
#line 2069 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
((TARGET_MAD || ISA_HAS_MACC || GENERATE_MADD_MSUB || ISA_HAS_DSP)
   && !TARGET_64BIT)
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V2HAmode)\n\
       || register_operand (operands[1], V2HAmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2HAmode)
       || register_operand (operands[1], V2HAmode))) && 
#line 610 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2HAmode)
       || register_operand (operands[1], V2HAmode))) && 
#line 610 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_DSP",
    __builtin_constant_p 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP)
    ? (int) 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP)
    : -1 },
  { "(reload_completed && !TARGET_64BIT\n\
   && mips_split_64bit_move_p (operands[0], operands[1])) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && !TARGET_64BIT
   && mips_split_64bit_move_p (operands[0], operands[1])) && 
#line 618 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 4518 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed && !TARGET_64BIT
   && mips_split_64bit_move_p (operands[0], operands[1])) && 
#line 618 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "(ISA_HAS_NMADD4_NMSUB4 (SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && HONOR_SIGNED_ZEROS (SFmode)\n\
   && !HONOR_NANS (SFmode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (SFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 1398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_FIX_R4000",
    __builtin_constant_p 
#line 1398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_R4000)
    ? (int) 
#line 1398 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_R4000)
    : -1 },
  { "(TARGET_USE_GOT) && (Pmode == DImode)",
    __builtin_constant_p (
#line 5931 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_USE_GOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 5931 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_USE_GOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS && cse_not_expected) && ( reload_completed)",
    __builtin_constant_p (
#line 3769 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS && cse_not_expected) && 
#line 3771 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) (
#line 3769 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS && cse_not_expected) && 
#line 3771 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(ISA_HAS_DSP) && (Pmode == DImode)",
    __builtin_constant_p (
#line 1167 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 1167 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "((mips_current_loadgp_style () == LOADGP_RTP) && (Pmode == DImode)) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p ((
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 4759 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) ((
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 4759 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
  { "((ISA_HAS_FP4) && (Pmode == DImode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 1857 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && ISA_HAS_DMUL3",
    __builtin_constant_p 
#line 1857 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && ISA_HAS_DMUL3)
    ? (int) 
#line 1857 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && ISA_HAS_DMUL3)
    : -1 },
  { "((ISA_HAS_FP4) && (Pmode == DImode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) ((
#line 4208 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP4) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(TARGET_MIPS16) && (Pmode == SImode)",
    __builtin_constant_p (
#line 3892 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 3892 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 2630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && and_operands_ok (SImode, operands[1], operands[2])",
    __builtin_constant_p 
#line 2630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && and_operands_ok (SImode, operands[1], operands[2]))
    ? (int) 
#line 2630 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && and_operands_ok (SImode, operands[1], operands[2]))
    : -1 },
  { "((TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && (Pmode == SImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 3823 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 3821 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && TARGET_XGOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 3823 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(ISA_HAS_NMADD4_NMSUB4 (V2SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && !HONOR_SIGNED_ZEROS (V2SFmode)\n\
   && !HONOR_NANS (V2SFmode)) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (V2SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (V2SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (V2SFmode)
   && !HONOR_NANS (V2SFmode)) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 4907 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_CACHE",
    __builtin_constant_p 
#line 4907 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CACHE)
    ? (int) 
#line 4907 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_CACHE)
    : -1 },
#line 521 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
  { "TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A",
    __builtin_constant_p 
#line 521 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
(TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A)
    ? (int) 
#line 521 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
(TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A)
    : -1 },
  { "((TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && (Pmode == SImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 3837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 3837 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
#line 3529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_EXTS && UINTVAL (operands[2]) <= 32",
    __builtin_constant_p 
#line 3529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && UINTVAL (operands[2]) <= 32)
    ? (int) 
#line 3529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && UINTVAL (operands[2]) <= 32)
    : -1 },
#line 4868 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_SYNCI",
    __builtin_constant_p 
#line 4868 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SYNCI)
    ? (int) 
#line 4868 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SYNCI)
    : -1 },
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && TARGET_LOONGSON_VECTORS",
    __builtin_constant_p 
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_LOONGSON_VECTORS)
    ? (int) 
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_LOONGSON_VECTORS)
    : -1 },
  { "(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && (Pmode == SImode)",
    __builtin_constant_p (
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 4731 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_ABSOLUTE) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD4_MSUB4 && TARGET_FUSED_MADD) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "(!TARGET_MIPS16 && mips_mem_fits_mode_p (DImode, operands[1])) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (DImode, operands[1])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && mips_mem_fits_mode_p (DImode, operands[1])) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 1775 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_FIX_R4000 && !ISA_HAS_DMUL3",
    __builtin_constant_p 
#line 1775 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000 && !ISA_HAS_DMUL3)
    ? (int) 
#line 1775 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000 && !ISA_HAS_DMUL3)
    : -1 },
  { "((HAVE_AS_TLS && !TARGET_MIPS16) && (Pmode == SImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 6438 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 6440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 6438 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 6440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(!TARGET_FIX_SB1 || flag_unsafe_math_optimizations) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2251 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_SB1 || flag_unsafe_math_optimizations) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2251 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_SB1 || flag_unsafe_math_optimizations) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 4473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && TARGET_MIPS16\n\
   && (register_operand (operands[0], TImode)\n\
       || register_operand (operands[1], TImode))",
    __builtin_constant_p 
#line 4473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_MIPS16
   && (register_operand (operands[0], TImode)
       || register_operand (operands[1], TImode)))
    ? (int) 
#line 4473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_MIPS16
   && (register_operand (operands[0], TImode)
       || register_operand (operands[1], TImode)))
    : -1 },
  { "(!TARGET_MIPS16\n\
   && (register_operand (operands[0], V2HImode)\n\
       || reg_or_0_operand (operands[1], V2HImode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2HImode)
       || reg_or_0_operand (operands[1], V2HImode))) && 
#line 606 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4060 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], V2HImode)
       || reg_or_0_operand (operands[1], V2HImode))) && 
#line 606 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(ISA_HAS_EXTS && UINTVAL (operands[2]) <= 32) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && UINTVAL (operands[2]) <= 32) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3529 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_EXTS && UINTVAL (operands[2]) <= 32) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 3741 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS",
    __builtin_constant_p 
#line 3741 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS)
    ? (int) 
#line 3741 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && ABI_HAS_64BIT_SYMBOLS)
    : -1 },
#line 4380 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT\n\
   && (register_operand (operands[0], SFmode)\n\
       || reg_or_0_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 4380 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT
   && (register_operand (operands[0], SFmode)
       || reg_or_0_operand (operands[1], SFmode)))
    ? (int) 
#line 4380 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT
   && (register_operand (operands[0], SFmode)
       || reg_or_0_operand (operands[1], SFmode)))
    : -1 },
#line 2056 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MAD",
    __builtin_constant_p 
#line 2056 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MAD)
    ? (int) 
#line 2056 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MAD)
    : -1 },
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && TARGET_DOUBLE_FLOAT",
    __builtin_constant_p 
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_DOUBLE_FLOAT)
    ? (int) 
#line 646 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_DOUBLE_FLOAT)
    : -1 },
#line 4441 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16\n\
   && (register_operand (operands[0], DFmode)\n\
       || register_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 4441 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    ? (int) 
#line 4441 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    : -1 },
  { "((TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && (Pmode == SImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 3850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 3850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V2HImode)\n\
       || register_operand (operands[1], V2HImode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2HImode)
       || register_operand (operands[1], V2HImode))) && 
#line 606 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V2HImode)
       || register_operand (operands[1], V2HImode))) && 
#line 606 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "((!TARGET_FIX_VR4120) && (TARGET_64BIT)) && ( reload_completed)",
    __builtin_constant_p ((
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 2317 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 2315 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_FIX_VR4120) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 2317 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
#line 119 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
  { "TARGET_HARD_FLOAT && TARGET_LOONGSON_VECTORS",
    __builtin_constant_p 
#line 119 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
(TARGET_HARD_FLOAT && TARGET_LOONGSON_VECTORS)
    ? (int) 
#line 119 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
(TARGET_HARD_FLOAT && TARGET_LOONGSON_VECTORS)
    : -1 },
  { "((mips_current_loadgp_style () == LOADGP_RTP) && (Pmode == SImode)) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p ((
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 4759 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) ((
#line 4757 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_RTP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 4759 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
#line 4257 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16\n\
   && (register_operand (operands[0], HImode)\n\
       || register_operand (operands[1], HImode))",
    __builtin_constant_p 
#line 4257 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode)))
    ? (int) 
#line 4257 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode)))
    : -1 },
  { "(TARGET_MIPS16 && TARGET_USE_GOT && reload_completed) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 3903 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_USE_GOT && reload_completed) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 3903 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_USE_GOT && reload_completed) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && ( reload_completed)",
    __builtin_constant_p (
#line 384 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 386 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
( reload_completed))
    ? (int) (
#line 384 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 386 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
( reload_completed))
    : -1 },
#line 1810 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_FIX_R4000 && !ISA_HAS_EXT_INS && reload_completed",
    __builtin_constant_p 
#line 1810 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000 && !ISA_HAS_EXT_INS && reload_completed)
    ? (int) 
#line 1810 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_FIX_R4000 && !ISA_HAS_EXT_INS && reload_completed)
    : -1 },
  { "(TARGET_FIX_R4000) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 1408 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_FIX_R4000) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 1408 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_FIX_R4000) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4322 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16\n\
   && (register_operand (operands[0], QImode)\n\
       || reg_or_0_operand (operands[1], QImode))",
    __builtin_constant_p 
#line 4322 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], QImode)
       || reg_or_0_operand (operands[1], QImode)))
    ? (int) 
#line 4322 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16
   && (register_operand (operands[0], QImode)
       || reg_or_0_operand (operands[1], QImode)))
    : -1 },
#line 1554 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MACC && !ISA_HAS_MSAC",
    __builtin_constant_p 
#line 1554 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && !ISA_HAS_MSAC)
    ? (int) 
#line 1554 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && !ISA_HAS_MSAC)
    : -1 },
  { "(TARGET_MIPS16\n\
   && (register_operand (operands[0], V4UQQmode)\n\
       || register_operand (operands[1], V4UQQmode))) && (TARGET_DSP)",
    __builtin_constant_p (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V4UQQmode)
       || register_operand (operands[1], V4UQQmode))) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    ? (int) (
#line 4070 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], V4UQQmode)
       || register_operand (operands[1], V4UQQmode))) && 
#line 613 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_DSP))
    : -1 },
  { "(TARGET_HARD_FLOAT) && (!TARGET_64BIT && TARGET_LOONGSON_VECTORS)",
    __builtin_constant_p (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_LOONGSON_VECTORS))
    ? (int) (
#line 4671 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT) && 
#line 650 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_LOONGSON_VECTORS))
    : -1 },
#line 3128 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT && !TARGET_MIPS16 && !ISA_HAS_EXTS",
    __builtin_constant_p 
#line 3128 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && !ISA_HAS_EXTS)
    ? (int) 
#line 3128 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT && !TARGET_MIPS16 && !ISA_HAS_EXTS)
    : -1 },
  { "(TARGET_USE_GOT) && (Pmode == SImode)",
    __builtin_constant_p (
#line 5931 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_USE_GOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 5931 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_USE_GOT) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2122 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2122 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_MADD3_MSUB3 && TARGET_FUSED_MADD) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
#line 2040 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && TARGET_FIX_R4000\n\
   && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120)",
    __builtin_constant_p 
#line 2040 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_FIX_R4000
   && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    ? (int) 
#line 2040 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && TARGET_FIX_R4000
   && !(ZERO_EXTEND == ZERO_EXTEND && TARGET_FIX_VR4120))
    : -1 },
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "Pmode == SImode",
    __builtin_constant_p 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)
    ? (int) 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)
    : -1 },
  { "((TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && (Pmode == DImode)) && ( reload_completed)",
    __builtin_constant_p ((
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 3850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) ((
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)) && 
#line 3850 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
  { "((ISA_HAS_FP_CONDMOVE) && (TARGET_HARD_FLOAT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT)) && 
#line 600 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT)) && 
#line 600 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(ISA_HAS_NMADD3_NMSUB3 (DFmode)\n\
   && TARGET_FUSED_MADD\n\
   && !HONOR_SIGNED_ZEROS (DFmode)\n\
   && !HONOR_NANS (DFmode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2231 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (DFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2231 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (DFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 4496 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT\n\
   && !TARGET_MIPS16\n\
   && (register_operand (operands[0], TFmode)\n\
       || reg_or_0_operand (operands[1], TFmode))",
    __builtin_constant_p 
#line 4496 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_MIPS16
   && (register_operand (operands[0], TFmode)
       || reg_or_0_operand (operands[1], TFmode)))
    ? (int) 
#line 4496 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT
   && !TARGET_MIPS16
   && (register_operand (operands[0], TFmode)
       || reg_or_0_operand (operands[1], TFmode)))
    : -1 },
#line 3793 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed",
    __builtin_constant_p 
#line 3793 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed)
    ? (int) 
#line 3793 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed)
    : -1 },
  { "(mips_current_loadgp_style () == LOADGP_NEWABI) && (Pmode == SImode)",
    __builtin_constant_p (
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "((ISA_HAS_FP_CONDMOVE) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)) && (TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF)",
    __builtin_constant_p ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF))
    ? (int) ((
#line 6319 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_FP_CONDMOVE) && 
#line 641 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)) && 
#line 601 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && !TARGET_LOONGSON_2EF))
    : -1 },
#line 3615 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "mips_use_ins_ext_p (operands[0], INTVAL (operands[1]),\n\
		       INTVAL (operands[2]))",
    __builtin_constant_p 
#line 3615 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[0], INTVAL (operands[1]),
		       INTVAL (operands[2])))
    ? (int) 
#line 3615 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_use_ins_ext_p (operands[0], INTVAL (operands[1]),
		       INTVAL (operands[2])))
    : -1 },
#line 4922 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_MIPS16 && !TARGET_MEMCPY",
    __builtin_constant_p 
#line 4922 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !TARGET_MEMCPY)
    ? (int) 
#line 4922 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16 && !TARGET_MEMCPY)
    : -1 },
#line 4818 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_CPRESTORE_DIRECTIVE",
    __builtin_constant_p 
#line 4818 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_CPRESTORE_DIRECTIVE)
    ? (int) 
#line 4818 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_CPRESTORE_DIRECTIVE)
    : -1 },
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "Pmode == DImode",
    __builtin_constant_p 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)
    ? (int) 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode)
    : -1 },
#line 42 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md"
  { "ISA_HAS_DSPR2",
    __builtin_constant_p 
#line 42 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md"
(ISA_HAS_DSPR2)
    ? (int) 
#line 42 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md"
(ISA_HAS_DSPR2)
    : -1 },
#line 4085 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && ((INTVAL (operands[1]) < 0\n\
	&& INTVAL (operands[1]) >= -0x80)\n\
       || (INTVAL (operands[1]) >= 32 * 4\n\
	   && INTVAL (operands[1]) <= 31 * 4 + 0x7c)\n\
       || (INTVAL (operands[1]) >= 0\n\
	   && INTVAL (operands[1]) < 32 * 4\n\
	   && (INTVAL (operands[1]) & 3) != 0))",
    __builtin_constant_p 
#line 4085 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x80)
       || (INTVAL (operands[1]) >= 32 * 4
	   && INTVAL (operands[1]) <= 31 * 4 + 0x7c)
       || (INTVAL (operands[1]) >= 0
	   && INTVAL (operands[1]) < 32 * 4
	   && (INTVAL (operands[1]) & 3) != 0)))
    ? (int) 
#line 4085 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) < 0
	&& INTVAL (operands[1]) >= -0x80)
       || (INTVAL (operands[1]) >= 32 * 4
	   && INTVAL (operands[1]) <= 31 * 4 + 0x7c)
       || (INTVAL (operands[1]) >= 0
	   && INTVAL (operands[1]) < 32 * 4
	   && (INTVAL (operands[1]) & 3) != 0)))
    : -1 },
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT",
    __builtin_constant_p 
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT)
    ? (int) 
#line 647 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && TARGET_PAIRED_SINGLE_FLOAT)
    : -1 },
#line 3054 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E",
    __builtin_constant_p 
#line 3054 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E)
    ? (int) 
#line 3054 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!ISA_HAS_SEB_SEH && !GENERATE_MIPS16E)
    : -1 },
#line 4332 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16\n\
   && (register_operand (operands[0], QImode)\n\
       || register_operand (operands[1], QImode))",
    __builtin_constant_p 
#line 4332 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode)))
    ? (int) 
#line 4332 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16
   && (register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode)))
    : -1 },
  { "(TARGET_SB1 && flag_unsafe_math_optimizations) && (TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT)",
    __builtin_constant_p (
#line 2432 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SB1 && flag_unsafe_math_optimizations) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    ? (int) (
#line 2432 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_SB1 && flag_unsafe_math_optimizations) && 
#line 637 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT))
    : -1 },
  { "(ISA_HAS_DSP) && (Pmode == SImode)",
    __builtin_constant_p (
#line 1167 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 1167 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
(ISA_HAS_DSP) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 5117 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_ROR",
    __builtin_constant_p 
#line 5117 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_ROR)
    ? (int) 
#line 5117 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_ROR)
    : -1 },
  { "(ISA_HAS_MACC && !ISA_HAS_MSAC) && ( reload_completed)",
    __builtin_constant_p (
#line 1554 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && !ISA_HAS_MSAC) && 
#line 1556 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    ? (int) (
#line 1554 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MACC && !ISA_HAS_MSAC) && 
#line 1556 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed))
    : -1 },
#line 3308 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && TARGET_FLOAT64 && TARGET_DOUBLE_FLOAT",
    __builtin_constant_p 
#line 3308 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_FLOAT64 && TARGET_DOUBLE_FLOAT)
    ? (int) 
#line 3308 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_FLOAT64 && TARGET_DOUBLE_FLOAT)
    : -1 },
#line 3232 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && ISA_HAS_TRUNC_W",
    __builtin_constant_p 
#line 3232 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_TRUNC_W)
    ? (int) 
#line 3232 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && ISA_HAS_TRUNC_W)
    : -1 },
  { "((mips_current_loadgp_style () == LOADGP_NEWABI) && (Pmode == SImode)) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p ((
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 4716 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) ((
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode)) && 
#line 4716 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
  { "(TARGET_4300_MUL_FIX) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 1261 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_4300_MUL_FIX) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 1261 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_4300_MUL_FIX) && 
#line 640 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "(mips_current_loadgp_style () == LOADGP_NEWABI) && (Pmode == DImode)",
    __builtin_constant_p (
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 4714 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_current_loadgp_style () == LOADGP_NEWABI) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
#line 1534 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MSAC",
    __builtin_constant_p 
#line 1534 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MSAC)
    ? (int) 
#line 1534 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MSAC)
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && (Pmode == SImode)",
    __builtin_constant_p (
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 3835 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_p[SYMBOL_GOT_DISP]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
  { "(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && (Pmode == DImode)",
    __builtin_constant_p (
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 3848 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_EXPLICIT_RELOCS && !mips_split_hi_p[SYMBOL_GOT_PAGE_OFST]) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
#line 4565 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT\n\
   && TARGET_PAIRED_SINGLE_FLOAT\n\
   && (register_operand (operands[0], V2SFmode)\n\
       || reg_or_0_operand (operands[1], V2SFmode))",
    __builtin_constant_p 
#line 4565 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT
   && TARGET_PAIRED_SINGLE_FLOAT
   && (register_operand (operands[0], V2SFmode)
       || reg_or_0_operand (operands[1], V2SFmode)))
    ? (int) 
#line 4565 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT
   && TARGET_PAIRED_SINGLE_FLOAT
   && (register_operand (operands[0], V2SFmode)
       || reg_or_0_operand (operands[1], V2SFmode)))
    : -1 },
  { "(TARGET_MIPS16) && ( mips_must_initialize_gp_p ())",
    __builtin_constant_p (
#line 4778 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 4780 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    ? (int) (
#line 4778 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16) && 
#line 4780 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( mips_must_initialize_gp_p ()))
    : -1 },
  { "(!TARGET_64BIT) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 592 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 592 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
  { "(ISA_HAS_NMADD3_NMSUB3 (SFmode)\n\
   && TARGET_FUSED_MADD\n\
   && !HONOR_SIGNED_ZEROS (SFmode)\n\
   && !HONOR_NANS (SFmode)) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 2231 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 2231 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD3_NMSUB3 (SFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (SFmode)
   && !HONOR_NANS (SFmode)) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
#line 1594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MSAC && reload_completed",
    __builtin_constant_p 
#line 1594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MSAC && reload_completed)
    ? (int) 
#line 1594 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MSAC && reload_completed)
    : -1 },
#line 1748 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "!TARGET_64BIT && (!TARGET_FIX_R4000 || ISA_HAS_DSP)",
    __builtin_constant_p 
#line 1748 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && (!TARGET_FIX_R4000 || ISA_HAS_DSP))
    ? (int) 
#line 1748 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_64BIT && (!TARGET_FIX_R4000 || ISA_HAS_DSP))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && (TARGET_HARD_FLOAT)",
    __builtin_constant_p (
#line 595 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    ? (int) (
#line 595 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
(TARGET_HARD_FLOAT && TARGET_PAIRED_SINGLE_FLOAT) && 
#line 635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT))
    : -1 },
  { "(TARGET_64BIT) && ( reload_completed && register_operand (operands[1], VOIDmode))",
    __builtin_constant_p (
#line 2977 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT) && 
#line 2981 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && register_operand (operands[1], VOIDmode)))
    ? (int) (
#line 2977 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT) && 
#line 2981 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
( reload_completed && register_operand (operands[1], VOIDmode)))
    : -1 },
  { "(ISA_HAS_NMADD4_NMSUB4 (DFmode)\n\
   && TARGET_FUSED_MADD\n\
   && HONOR_SIGNED_ZEROS (DFmode)\n\
   && !HONOR_NANS (DFmode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (DFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2189 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (DFmode)
   && TARGET_FUSED_MADD
   && HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
  { "(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && INTVAL (operands[2]) > 8\n\
   && INTVAL (operands[2]) <= 16) && (TARGET_64BIT)",
    __builtin_constant_p (
#line 5083 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && INTVAL (operands[2]) > 8
   && INTVAL (operands[2]) <= 16) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) (
#line 5083 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && INTVAL (operands[2]) > 8
   && INTVAL (operands[2]) <= 16) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 5867 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "mips_must_initialize_gp_p ()",
    __builtin_constant_p 
#line 5867 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_must_initialize_gp_p ())
    ? (int) 
#line 5867 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(mips_must_initialize_gp_p ())
    : -1 },
  { "(HAVE_AS_TLS && !TARGET_MIPS16) && (Pmode == DImode)",
    __builtin_constant_p (
#line 6455 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    ? (int) (
#line 6455 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(HAVE_AS_TLS && !TARGET_MIPS16) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == DImode))
    : -1 },
  { "(ISA_HAS_LWXS) && (Pmode == SImode)",
    __builtin_constant_p (
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    ? (int) (
#line 4223 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_LWXS) && 
#line 596 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(Pmode == SImode))
    : -1 },
#line 1723 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_MULS",
    __builtin_constant_p 
#line 1723 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MULS)
    ? (int) 
#line 1723 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_MULS)
    : -1 },
#line 6375 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16",
    __builtin_constant_p 
#line 6375 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16)
    ? (int) 
#line 6375 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16)
    : -1 },
  { "((!TARGET_MIPS16) && (TARGET_64BIT)) && (TARGET_64BIT)",
    __builtin_constant_p ((
#line 5460 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    ? (int) ((
#line 5460 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(!TARGET_MIPS16) && 
#line 588 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)) && 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT))
    : -1 },
#line 4123 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && INTVAL (operands[1]) >= 0x100\n\
   && INTVAL (operands[1]) <= 0xff + 0x7f",
    __builtin_constant_p 
#line 4123 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && INTVAL (operands[1]) >= 0x100
   && INTVAL (operands[1]) <= 0xff + 0x7f)
    ? (int) 
#line 4123 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && reload_completed && !TARGET_DEBUG_D_MODE
   && INTVAL (operands[1]) >= 0x100
   && INTVAL (operands[1]) <= 0xff + 0x7f)
    : -1 },
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_64BIT",
    __builtin_constant_p 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)
    ? (int) 
#line 584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_64BIT)
    : -1 },
#line 1084 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_MIPS16 && TARGET_64BIT && reload_completed && !TARGET_DEBUG_D_MODE\n\
   && ((INTVAL (operands[1]) > 0xf\n\
	&& INTVAL (operands[1]) <= 0xf + 0xf)\n\
       || (INTVAL (operands[1]) < - 0x10\n\
	   && INTVAL (operands[1]) >= - 0x10 - 0x10))",
    __builtin_constant_p 
#line 1084 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_64BIT && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) > 0xf
	&& INTVAL (operands[1]) <= 0xf + 0xf)
       || (INTVAL (operands[1]) < - 0x10
	   && INTVAL (operands[1]) >= - 0x10 - 0x10)))
    ? (int) 
#line 1084 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_MIPS16 && TARGET_64BIT && reload_completed && !TARGET_DEBUG_D_MODE
   && ((INTVAL (operands[1]) > 0xf
	&& INTVAL (operands[1]) <= 0xf + 0xf)
       || (INTVAL (operands[1]) < - 0x10
	   && INTVAL (operands[1]) >= - 0x10 - 0x10)))
    : -1 },
  { "(ISA_HAS_NMADD4_NMSUB4 (DFmode)\n\
   && TARGET_FUSED_MADD\n\
   && !HONOR_SIGNED_ZEROS (DFmode)\n\
   && !HONOR_NANS (DFmode)) && (TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT)",
    __builtin_constant_p (
#line 2217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (DFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    ? (int) (
#line 2217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_NMADD4_NMSUB4 (DFmode)
   && TARGET_FUSED_MADD
   && !HONOR_SIGNED_ZEROS (DFmode)
   && !HONOR_NANS (DFmode)) && 
#line 636 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT))
    : -1 },
#line 6396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "reload_completed",
    __builtin_constant_p 
#line 6396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed)
    ? (int) 
#line 6396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(reload_completed)
    : -1 },
#line 4421 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT\n\
   && (register_operand (operands[0], DFmode)\n\
       || reg_or_0_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 4421 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT
   && (register_operand (operands[0], DFmode)
       || reg_or_0_operand (operands[1], DFmode)))
    ? (int) 
#line 4421 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(TARGET_HARD_FLOAT && TARGET_DOUBLE_FLOAT
   && (register_operand (operands[0], DFmode)
       || reg_or_0_operand (operands[1], DFmode)))
    : -1 },
#line 1169 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
  { "ISA_HAS_BADDU && BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 1169 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && BYTES_BIG_ENDIAN)
    ? (int) 
#line 1169 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
(ISA_HAS_BADDU && BYTES_BIG_ENDIAN)
    : -1 },

};
#endif /* gcc >= 3.0.1 */

int
main(void)
{
  unsigned int i;
  const char *p;
  puts ("(define_conditions [");
#if GCC_VERSION >= 3001
  for (i = 0; i < ARRAY_SIZE (insn_conditions); i++)
    {
      printf ("  (%d \"", insn_conditions[i].value);
      for (p = insn_conditions[i].expr; *p; p++)
        {
          switch (*p)
	     {
	     case '\\':
	     case '\"': putchar ('\\'); break;
	     default: break;
	     }
          putchar (*p);
        }
      puts ("\")");
    }
#endif /* gcc >= 3.0.1 */
  puts ("])");
  fflush (stdout);
return ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE;
}
