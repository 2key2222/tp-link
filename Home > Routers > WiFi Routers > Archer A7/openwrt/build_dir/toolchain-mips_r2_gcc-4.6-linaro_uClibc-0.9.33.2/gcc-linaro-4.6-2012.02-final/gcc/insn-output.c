/* Generated automatically by the program `genoutput'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "flags.h"
#include "ggc.h"
#include "rtl.h"
#include "expr.h"
#include "insn-codes.h"
#include "tm_p.h"
#include "function.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "insn-config.h"

#include "conditions.h"
#include "insn-attr.h"

#include "recog.h"

#include "diagnostic-core.h"
#include "output.h"
#include "target.h"
#include "tm-constrs.h"

static const char *
output_0 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 108 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
{ gcc_unreachable (); }
}

static const char *
output_1 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 119 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
{ gcc_unreachable (); }
}

static const char *
output_2 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 130 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
{ gcc_unreachable (); }
}

static const char *
output_3 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 141 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md"
{ gcc_unreachable (); }
}

static const char *
output_4 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 929 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (ISA_HAS_COND_TRAP)
    return "teq\t$0,$0";
  else if (TARGET_MIPS16)
    return "break 0";
  else
    return "break";
}
}

static const char * const output_10[] = {
  "addu\t%0,%1,%2",
  "addiu\t%0,%1,%2",
};

static const char * const output_11[] = {
  "daddu\t%0,%1,%2",
  "daddiu\t%0,%1,%2",
};

static const char * const output_12[] = {
  "addiu\t%0,%2",
  "addiu\t%0,%1,%2",
  "addiu\t%0,%2",
  "addiu\t%0,%1,%2",
  "addu\t%0,%1,%2",
};

static const char * const output_13[] = {
  "daddiu\t%0,%2",
  "daddiu\t%0,%1,%2",
  "daddiu\t%0,%2",
  "daddiu\t%0,%1,%2",
  "daddu\t%0,%1,%2",
};

static const char * const output_14[] = {
  "addu\t%0,%1,%2",
  "addiu\t%0,%1,%2",
};

static const char *
output_31 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1346 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_LOONGSON_2EF)
    return "multu.g\t%0,%1,%2";
  else
    return "gsmultu\t%0,%1,%2";
}
}

static const char *
output_32 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1346 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_LOONGSON_2EF)
    return "dmultu.g\t%0,%1,%2";
  else
    return "gsdmultu\t%0,%1,%2";
}
}

static const char *
output_33 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1361 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 1)
    return "mult\t%1,%2";
  if (SImode == SImode && TARGET_MIPS3900)
    return "mult\t%0,%1,%2";
  return "mul\t%0,%1,%2";
}
}

static const char *
output_34 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1361 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 1)
    return "dmult\t%1,%2";
  if (DImode == SImode && TARGET_MIPS3900)
    return "mult\t%0,%1,%2";
  return "dmul\t%0,%1,%2";
}
}

static const char * const output_39[] = {
  "madd\t%1,%2",
  "#",
};

static const char * const output_40[] = {
  "madd\t%1,%2",
  "madd\t%0,%1,%2",
  "#",
};

static const char *
output_41 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1514 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 1)
    return "macc\t%0,%1,%2";
  else if (TARGET_MIPS5500)
    return "madd\t%1,%2";
  else
    /* The VR4130 assumes that there is a two-cycle latency between a macc
       that "writes" to $0 and an instruction that reads from it.  We avoid
       this by assigning to $1 instead.  */
    return "%[macc\t%@,%1,%2%]";
}
}

static const char *
output_42 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1535 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 1)
    return "msac\t%0,%2,%3";
  else if (TARGET_MIPS5500)
    return "msub\t%2,%3";
  else
    return "msac\t$0,%2,%3";
}
}

static const char * const output_46[] = {
  "msub\t%2,%3",
  "#",
};

static const char * const output_47[] = {
  "muls\t$0,%1,%2",
  "muls\t%0,%1,%2",
};

static const char *
output_48 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1749 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (ISA_HAS_DSP_MULT)
    return "mult\t%q0,%1,%2";
  else
    return "mult\t%1,%2";
}
}

static const char *
output_49 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1749 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (ISA_HAS_DSP_MULT)
    return "multu\t%q0,%1,%2";
  else
    return "multu\t%1,%2";
}
}

static const char *
output_59 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1889 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (ISA_HAS_DSP_MULT)
    return "msub\t%q0,%1,%2";
  else if (TARGET_MIPS5500 || GENERATE_MADD_MSUB)
    return "msub\t%1,%2";
  else
    return "msac\t$0,%1,%2";
}
}

static const char *
output_60 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1889 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (ISA_HAS_DSP_MULT)
    return "msubu\t%q0,%1,%2";
  else if (TARGET_MIPS5500 || GENERATE_MADD_MSUB)
    return "msubu\t%1,%2";
  else
    return "msacu\t$0,%1,%2";
}
}

static const char *
output_61 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1930 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_FIX_R4000 ? "mult\t%1,%2\n\tmfhi\t%0" : "#"; }
}

static const char *
output_62 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1930 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_FIX_R4000 ? "multu\t%1,%2\n\tmfhi\t%0" : "#"; }
}

static const char *
output_67 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1995 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_FIX_R4000 ? "dmult\t%1,%2\n\tmfhi\t%0" : "#"; }
}

static const char *
output_68 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1995 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_FIX_R4000 ? "dmultu\t%1,%2\n\tmfhi\t%0" : "#"; }
}

static const char *
output_74 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2071 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_MAD)
    return "mad\t%1,%2";
  else if (ISA_HAS_DSP_MULT)
    return "madd\t%q0,%1,%2";
  else if (GENERATE_MADD_MSUB || TARGET_MIPS5500)
    return "madd\t%1,%2";
  else
    /* See comment in *macc.  */
    return "%[macc\t%@,%1,%2%]";
}
}

static const char *
output_75 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2071 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_MAD)
    return "madu\t%1,%2";
  else if (ISA_HAS_DSP_MULT)
    return "maddu\t%q0,%1,%2";
  else if (GENERATE_MADD_MSUB || TARGET_MIPS5500)
    return "maddu\t%1,%2";
  else
    /* See comment in *macc.  */
    return "%[maccu\t%@,%1,%2%]";
}
}

static const char *
output_112 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2275 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "div.s\t%0,%1,%2\n\tmov.s\t%0,%0";
  else
    return "div.s\t%0,%1,%2";
}
}

static const char *
output_113 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2275 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "div.d\t%0,%1,%2\n\tmov.d\t%0,%0";
  else
    return "div.d\t%0,%1,%2";
}
}

static const char *
output_114 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2275 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "div.ps\t%0,%1,%2\n\tmov.ps\t%0,%0";
  else
    return "div.ps\t%0,%1,%2";
}
}

static const char *
output_115 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2293 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "recip.s\t%0,%2\n\tmov.s\t%0,%0";
  else
    return "recip.s\t%0,%2";
}
}

static const char *
output_116 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2293 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "recip.d\t%0,%2\n\tmov.d\t%0,%0";
  else
    return "recip.d\t%0,%2";
}
}

static const char *
output_117 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2293 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "recip.ps\t%0,%2\n\tmov.ps\t%0,%0";
  else
    return "recip.ps\t%0,%2";
}
}

static const char *
output_122 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("div\t%.,%1,%2", operands); }
}

static const char *
output_123 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("divu\t%.,%1,%2", operands); }
}

static const char *
output_124 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("ddiv\t%.,%1,%2", operands); }
}

static const char *
output_125 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("ddivu\t%.,%1,%2", operands); }
}

static const char *
output_126 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("div\t%.,%1,%2", operands); }
}

static const char *
output_127 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("divu\t%.,%1,%2", operands); }
}

static const char *
output_128 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("ddiv\t%.,%1,%2", operands); }
}

static const char *
output_129 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2379 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_division ("ddivu\t%.,%1,%2", operands); }
}

static const char *
output_130 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2397 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "sqrt.s\t%0,%1\n\tmov.s\t%0,%0";
  else
    return "sqrt.s\t%0,%1";
}
}

static const char *
output_131 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2397 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "sqrt.d\t%0,%1\n\tmov.d\t%0,%0";
  else
    return "sqrt.d\t%0,%1";
}
}

static const char *
output_132 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2397 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "sqrt.ps\t%0,%1\n\tmov.ps\t%0,%0";
  else
    return "sqrt.ps\t%0,%1";
}
}

static const char *
output_133 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2415 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "rsqrt.s\t%0,%2\n\tmov.s\t%0,%0";
  else
    return "rsqrt.s\t%0,%2";
}
}

static const char *
output_134 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2415 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "rsqrt.d\t%0,%2\n\tmov.d\t%0,%0";
  else
    return "rsqrt.d\t%0,%2";
}
}

static const char *
output_135 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2415 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "rsqrt.ps\t%0,%2\n\tmov.ps\t%0,%0";
  else
    return "rsqrt.ps\t%0,%2";
}
}

static const char *
output_136 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2433 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "rsqrt.s\t%0,%2\n\tmov.s\t%0,%0";
  else
    return "rsqrt.s\t%0,%2";
}
}

static const char *
output_137 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2433 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "rsqrt.d\t%0,%2\n\tmov.d\t%0,%0";
  else
    return "rsqrt.d\t%0,%2";
}
}

static const char *
output_138 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2433 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_FIX_SB1)
    return "rsqrt.ps\t%0,%2\n\tmov.ps\t%0,%0";
  else
    return "rsqrt.ps\t%0,%2";
}
}

static const char *
output_146 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2511 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_MIPS16)
    return "neg\t%0,%1";
  else
    return "subu\t%0,%.,%1";
}
}

static const char *
output_151 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2544 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_MIPS16)
    return "not\t%0,%1";
  else
    return "nor\t%0,%.,%1";
}
}

static const char *
output_152 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2544 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_MIPS16)
    return "not\t%0,%1";
  else
    return "nor\t%0,%.,%1";
}
}

static const char *
output_153 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2595 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  int len;

  switch (which_alternative)
    {
    case 0:
      operands[1] = gen_lowpart (QImode, operands[1]);
      return "lbu\t%0,%1";
    case 1:
      operands[1] = gen_lowpart (HImode, operands[1]);
      return "lhu\t%0,%1";
    case 2:
      operands[1] = gen_lowpart (SImode, operands[1]);
      return "lwu\t%0,%1";
    case 3:
      return "andi\t%0,%1,%x2";
    case 4:
      len = low_bitmask_len (SImode, INTVAL (operands[2]));
      operands[2] = GEN_INT (len);
      return "ext\t%0,%1,0,%2";
    case 5:
      return "#";
    case 6:
      return "and\t%0,%1,%2";
    default:
      gcc_unreachable ();
    }
}
}

static const char *
output_154 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2595 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  int len;

  switch (which_alternative)
    {
    case 0:
      operands[1] = gen_lowpart (QImode, operands[1]);
      return "lbu\t%0,%1";
    case 1:
      operands[1] = gen_lowpart (HImode, operands[1]);
      return "lhu\t%0,%1";
    case 2:
      operands[1] = gen_lowpart (SImode, operands[1]);
      return "lwu\t%0,%1";
    case 3:
      return "andi\t%0,%1,%x2";
    case 4:
      len = low_bitmask_len (DImode, INTVAL (operands[2]));
      operands[2] = GEN_INT (len);
      return "dext\t%0,%1,0,%2";
    case 5:
      return "#";
    case 6:
      return "and\t%0,%1,%2";
    default:
      gcc_unreachable ();
    }
}
}

static const char *
output_155 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2631 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  switch (which_alternative)
    {
    case 0:
      operands[1] = gen_lowpart (QImode, operands[1]);
      return "lbu\t%0,%1";
    case 1:
      operands[1] = gen_lowpart (HImode, operands[1]);
      return "lhu\t%0,%1";
    case 2:
      operands[1] = gen_lowpart (SImode, operands[1]);
      return "lwu\t%0,%1";
    case 3:
      return "#";
    case 4:
      return "and\t%0,%2";
    default:
      gcc_unreachable ();
    }
}
}

static const char *
output_156 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2631 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  switch (which_alternative)
    {
    case 0:
      operands[1] = gen_lowpart (QImode, operands[1]);
      return "lbu\t%0,%1";
    case 1:
      operands[1] = gen_lowpart (HImode, operands[1]);
      return "lhu\t%0,%1";
    case 2:
      operands[1] = gen_lowpart (SImode, operands[1]);
      return "lwu\t%0,%1";
    case 3:
      return "#";
    case 4:
      return "and\t%0,%2";
    default:
      gcc_unreachable ();
    }
}
}

static const char * const output_157[] = {
  "or\t%0,%1,%2",
  "ori\t%0,%1,%x2",
};

static const char * const output_158[] = {
  "or\t%0,%1,%2",
  "ori\t%0,%1,%x2",
};

static const char * const output_161[] = {
  "xor\t%0,%1,%2",
  "xori\t%0,%1,%x2",
};

static const char * const output_162[] = {
  "xor\t%0,%1,%2",
  "xori\t%0,%1,%x2",
};

static const char * const output_163[] = {
  "xor\t%0,%2",
  "cmpi\t%1,%2",
  "cmp\t%1,%2",
};

static const char * const output_164[] = {
  "xor\t%0,%2",
  "cmpi\t%1,%2",
  "cmp\t%1,%2",
};

static const char * const output_168[] = {
  "sll\t%0,%1,0",
  "sb\t%1,%0",
};

static const char * const output_169[] = {
  "sll\t%0,%1,0",
  "sh\t%1,%0",
};

static const char * const output_170[] = {
  "sll\t%0,%1,0",
  "sw\t%1,%0",
};

static const char * const output_183[] = {
  "#",
  "lwu\t%0,%1",
};

static const char * const output_184[] = {
  "dext\t%0,%1,0,32",
  "lwu\t%0,%1",
};

static const char * const output_185[] = {
  "andi\t%0,%1,0x00ff",
  "lbu\t%0,%1",
};

static const char * const output_186[] = {
  "andi\t%0,%1,0x00ff",
  "lbu\t%0,%1",
};

static const char * const output_187[] = {
  "andi\t%0,%1,0xffff",
  "lhu\t%0,%1",
};

static const char * const output_188[] = {
  "andi\t%0,%1,0xffff",
  "lhu\t%0,%1",
};

static const char * const output_197[] = {
  "andi\t%0,%1,0x00ff",
  "lbu\t%0,%1",
};

static const char *
output_199 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2940 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_MASK (QImode));
  return "andi\t%0,%1,%x2";
}
}

static const char *
output_200 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2940 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_MASK (QImode));
  return "andi\t%0,%1,%x2";
}
}

static const char *
output_201 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2940 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_MASK (HImode));
  return "andi\t%0,%1,%x2";
}
}

static const char *
output_202 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 2940 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_MASK (HImode));
  return "andi\t%0,%1,%x2";
}
}

static const char * const output_204[] = {
  "#",
  "lw\t%0,%1",
};

static const char * const output_205[] = {
  "seb\t%0",
  "lb\t%0,%1",
};

static const char * const output_206[] = {
  "seb\t%0",
  "lb\t%0,%1",
};

static const char * const output_207[] = {
  "seh\t%0",
  "lh\t%0,%1",
};

static const char * const output_208[] = {
  "seh\t%0",
  "lh\t%0,%1",
};

static const char * const output_209[] = {
  "#",
  "lb\t%0,%1",
};

static const char * const output_210[] = {
  "#",
  "lb\t%0,%1",
};

static const char * const output_211[] = {
  "#",
  "lh\t%0,%1",
};

static const char * const output_212[] = {
  "#",
  "lh\t%0,%1",
};

static const char * const output_213[] = {
  "seb\t%0,%1",
  "lb\t%0,%1",
};

static const char * const output_214[] = {
  "seb\t%0,%1",
  "lb\t%0,%1",
};

static const char * const output_215[] = {
  "seh\t%0,%1",
  "lh\t%0,%1",
};

static const char * const output_216[] = {
  "seh\t%0,%1",
  "lh\t%0,%1",
};

static const char * const output_217[] = {
  "seb\t%0",
  "lb\t%0,%1",
};

static const char * const output_218[] = {
  "#",
  "lb\t%0,%1",
};

static const char * const output_219[] = {
  "seb\t%0,%1",
  "lb\t%0,%1",
};

static const char *
output_225 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3148 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_BITSIZE (QImode));
  return "exts\t%0,%1,0,%m2";
}
}

static const char *
output_226 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3148 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_BITSIZE (QImode));
  return "exts\t%0,%1,0,%m2";
}
}

static const char *
output_227 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3148 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_BITSIZE (HImode));
  return "exts\t%0,%1,0,%m2";
}
}

static const char *
output_228 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3148 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (GET_MODE_BITSIZE (HImode));
  return "exts\t%0,%1,0,%m2";
}
}

static const char *
output_232 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3206 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (mips_nomacro.nesting_level > 0)
    return ".set\tmacro\n\ttrunc.w.d %0,%1,%2\n\t.set\tnomacro";
  else
    return "trunc.w.d %0,%1,%2";
}
}

static const char *
output_234 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3243 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (mips_nomacro.nesting_level > 0)
    return ".set\tmacro\n\ttrunc.w.s %0,%1,%2\n\t.set\tnomacro";
  else
    return "trunc.w.s %0,%1,%2";
}
}

static const char *
output_248 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[3] =
    GEN_INT (mask_low_and_shift_len (SImode, operands[3], operands[2]));
  return "cins\t%0,%1,%2,%m3";
}
}

static const char *
output_249 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3635 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[3] =
    GEN_INT (mask_low_and_shift_len (DImode, operands[3], operands[2]));
  return "cins\t%0,%1,%2,%m3";
}
}

static const char *
output_276 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3965 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_277 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3975 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_278 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3985 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_279 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 3995 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_280 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_281 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_282 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_283 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_284 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_285 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_286 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_287 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_288 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_289 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_290 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_291 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_292 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_293 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_294 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_295 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_296 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_297 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4073 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_298 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4144 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_329 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4250 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_330 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4260 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_331 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4325 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_332 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4335 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_333 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4383 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_334 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4393 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_335 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4403 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_336 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4424 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_337 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4434 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_338 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4444 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_343 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4569 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_344 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return ISA_HAS_MACCHI ? "macchi\t%0,%.,%." : "mfhi\t%0"; }
}

static const char *
output_345 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return ISA_HAS_MACCHI ? "dmacchi\t%0,%.,%." : "mfhi\t%0"; }
}

static const char *
output_346 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return ISA_HAS_MACCHI ? "macchi\t%0,%.,%." : "mfhi\t%0"; }
}

static const char *
output_347 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4584 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return ISA_HAS_MACCHI ? "dmacchi\t%0,%.,%." : "mfhi\t%0"; }
}

static const char *
output_352 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_353 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_354 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_355 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_356 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_357 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_358 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4642 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 0);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_359 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_360 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_361 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_362 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_363 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_364 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_365 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4657 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[0] = mips_subword (operands[0], 1);
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_366 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_367 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_368 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_369 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_370 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_371 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_372 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4672 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[1] = mips_subword (operands[1], INTVAL (operands[2]));
  return mips_output_move (operands[0], operands[1]);
}
}

static const char *
output_387 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4715 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_388 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4715 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_389 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4732 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_390 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4732 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_392 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4758 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_393 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4758 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_394 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4779 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_395 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4798 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_396 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4819 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (mips_nomacro.nesting_level > 0 && which_alternative == 1)
    return ".set\tmacro\n\t.cprestore\t%1\n\t.set\tnomacro";
  else
    return ".cprestore\t%1";
}
}

static const char *
output_398 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4863 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_sync (); }
}

static const char *
output_402 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4882 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return "%(%<bal\t1f\n"
         "\tnop\n"
         "1:\taddiu\t$31,$31,12\n"
         "\tjr.hb\t$31\n"
         "\tnop%>%)";
}
}

static const char *
output_403 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4882 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return "%(%<bal\t1f\n"
         "\tnop\n"
         "1:\tdaddiu\t$31,$31,12\n"
         "\tjr.hb\t$31\n"
         "\tnop%>%)";
}
}

static const char *
output_406 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2])
			   & (GET_MODE_BITSIZE (SImode) - 1));

  return "sll\t%0,%1,%2";
}
}

static const char *
output_407 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2])
			   & (GET_MODE_BITSIZE (SImode) - 1));

  return "sra\t%0,%1,%2";
}
}

static const char *
output_408 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2])
			   & (GET_MODE_BITSIZE (SImode) - 1));

  return "srl\t%0,%1,%2";
}
}

static const char *
output_409 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2])
			   & (GET_MODE_BITSIZE (DImode) - 1));

  return "dsll\t%0,%1,%2";
}
}

static const char *
output_410 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2])
			   & (GET_MODE_BITSIZE (DImode) - 1));

  return "dsra\t%0,%1,%2";
}
}

static const char *
output_411 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4972 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2])
			   & (GET_MODE_BITSIZE (DImode) - 1));

  return "dsrl\t%0,%1,%2";
}
}

static const char *
output_412 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4988 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);

  return "sll\t%0,%1,%2";
}
}

static const char *
output_413 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4988 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);

  return "sra\t%0,%1,%2";
}
}

static const char *
output_414 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 4988 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);

  return "srl\t%0,%1,%2";
}
}

static const char *
output_415 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5002 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 0)
    return "sll\t%0,%2";

  operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
  return "sll\t%0,%1,%2";
}
}

static const char *
output_416 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5002 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 0)
    return "sra\t%0,%2";

  operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
  return "sra\t%0,%1,%2";
}
}

static const char *
output_417 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5002 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 0)
    return "srl\t%0,%2";

  operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
  return "srl\t%0,%1,%2";
}
}

static const char *
output_418 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5024 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (which_alternative == 0)
    return "dsll\t%0,%2";

  operands[2] = GEN_INT (INTVAL (operands[2]) & 0x3f);
  return "dsll\t%0,%1,%2";
}
}

static const char *
output_419 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5044 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2]) & 0x3f);

  return "dsra\t%0,%2";
}
}

static const char *
output_420 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5063 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    operands[2] = GEN_INT (INTVAL (operands[2]) & 0x3f);

  return "dsrl\t%0,%2";
}
}

static const char *
output_422 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5118 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    gcc_assert (INTVAL (operands[2]) >= 0
		&& INTVAL (operands[2]) < GET_MODE_BITSIZE (SImode));

  return "ror\t%0,%1,%2";
}
}

static const char *
output_423 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5118 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (CONST_INT_P (operands[2]))
    gcc_assert (INTVAL (operands[2]) >= 0
		&& INTVAL (operands[2]) < GET_MODE_BITSIZE (DImode));

  return "dror\t%0,%1,%2";
}
}

static const char *
output_424 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5146 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%F1", "%Z2%0"),
					 MIPS_BRANCH ("b%W1", "%Z2%0"));
}
}

static const char *
output_425 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5162 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%W1", "%Z2%0"),
					 MIPS_BRANCH ("b%F1", "%Z2%0"));
}
}

static const char *
output_426 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5180 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_order_conditional_branch (insn, operands, false); }
}

static const char *
output_427 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5180 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_order_conditional_branch (insn, operands, false); }
}

static const char *
output_428 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5192 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_order_conditional_branch (insn, operands, true); }
}

static const char *
output_429 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5192 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_order_conditional_branch (insn, operands, true); }
}

static const char *
output_430 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5206 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%C1", "%2,%z3,%0"),
					 MIPS_BRANCH ("b%N1", "%2,%z3,%0"));
}
}

static const char *
output_431 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5206 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%C1", "%2,%z3,%0"),
					 MIPS_BRANCH ("b%N1", "%2,%z3,%0"));
}
}

static const char *
output_432 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5222 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%N1", "%2,%z3,%0"),
					 MIPS_BRANCH ("b%C1", "%2,%z3,%0"));
}
}

static const char *
output_433 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5222 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%N1", "%2,%z3,%0"),
					 MIPS_BRANCH ("b%C1", "%2,%z3,%0"));
}
}

static const char *
output_434 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5240 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (operands[2] != pc_rtx)
    {
      if (which_alternative == 0)
	return "b%C0z\t%1,%2";
      else
	return "bt%C0z\t%2";
    }
  else
    {
      if (which_alternative == 0)
	return "b%N0z\t%1,%3";
      else
	return "bt%N0z\t%3";
    }
}
}

static const char *
output_435 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5240 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (operands[2] != pc_rtx)
    {
      if (which_alternative == 0)
	return "b%C0z\t%1,%2";
      else
	return "bt%C0z\t%2";
    }
  else
    {
      if (which_alternative == 0)
	return "b%N0z\t%1,%3";
      else
	return "bt%N0z\t%3";
    }
}
}

static const char *
output_436 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"));
}
}

static const char *
output_437 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"));
}
}

static const char *
output_438 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"));
}
}

static const char *
output_439 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5304 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"));
}
}

static const char *
output_440 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5324 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"));
}
}

static const char *
output_441 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5324 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"));
}
}

static const char *
output_442 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5324 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"));
}
}

static const char *
output_443 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5324 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  return
    mips_output_conditional_branch (insn, operands,
				    MIPS_BRANCH ("bbit0", "%1,%2,%0"),
				    MIPS_BRANCH ("bbit1", "%1,%2,%0"));
}
}

static const char * const output_452[] = {
  "seq\t%0,%1,%2",
  "sltiu\t%0,%1,1",
  "seqi\t%0,%1,%2",
};

static const char * const output_453[] = {
  "seq\t%0,%1,%2",
  "sltiu\t%0,%1,1",
  "seqi\t%0,%1,%2",
};

static const char * const output_454[] = {
  "seq\t%0,%1,%2",
  "sltiu\t%0,%1,1",
  "seqi\t%0,%1,%2",
};

static const char * const output_455[] = {
  "seq\t%0,%1,%2",
  "sltiu\t%0,%1,1",
  "seqi\t%0,%1,%2",
};

static const char * const output_460[] = {
  "sne\t%0,%1,%2",
  "sltu\t%0,%.,%1",
  "snei\t%0,%1,%2",
};

static const char * const output_461[] = {
  "sne\t%0,%1,%2",
  "sltu\t%0,%.,%1",
  "snei\t%0,%1,%2",
};

static const char * const output_462[] = {
  "sne\t%0,%1,%2",
  "sltu\t%0,%.,%1",
  "snei\t%0,%1,%2",
};

static const char * const output_463[] = {
  "sne\t%0,%1,%2",
  "sltu\t%0,%.,%1",
  "snei\t%0,%1,%2",
};

static const char *
output_504 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%0,%1,%2";
}
}

static const char *
output_505 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%0,%1,%2";
}
}

static const char *
output_506 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%0,%1,%2";
}
}

static const char *
output_507 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%0,%1,%2";
}
}

static const char *
output_508 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%0,%1,%2";
}
}

static const char *
output_509 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%0,%1,%2";
}
}

static const char *
output_510 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%0,%1,%2";
}
}

static const char *
output_511 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5461 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%0,%1,%2";
}
}

static const char *
output_512 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%1,%2";
}
}

static const char *
output_513 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%1,%2";
}
}

static const char *
output_514 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%1,%2";
}
}

static const char *
output_515 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%1,%2";
}
}

static const char *
output_516 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%1,%2";
}
}

static const char *
output_517 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%1,%2";
}
}

static const char *
output_518 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "slt\t%1,%2";
}
}

static const char *
output_519 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5473 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = GEN_INT (INTVAL (operands[2]) + 1);
  return "sltu\t%1,%2";
}
}

static const char *
output_542 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5525 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_ABSOLUTE_JUMP ("%*j\t%l0%/"); }
}

static const char *
output_543 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5532 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (get_attr_length (insn) <= 8)
    return "%*b\t%l0%/";
  else
    {
      mips_output_load_label (operands[0]);
      return "%*jr\t%@%/%]";
    }
}
}

static const char *
output_557 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5779 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_561 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5866 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_562 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5866 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips_must_initialize_gp_p () ? "#" : ""; }
}

static const char *
output_567 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5979 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("j", operands, 0, 1); }
}

static const char *
output_568 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 5999 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("j", operands, 1, 2); }
}

static const char *
output_569 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6010 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("j", operands, 1, 2); }
}

static const char *
output_570 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6065 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_SPLIT_CALLS ? "#" : MIPS_CALL ("jal", operands, 0, 1); }
}

static const char *
output_571 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6080 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("jal", operands, 0, 1); }
}

static const char *
output_572 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6093 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_SPLIT_CALLS ? "#" : MIPS_CALL ("jal", operands, 0, -1); }
}

static const char *
output_573 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("jal", operands, 0, -1); }
}

static const char *
output_574 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6132 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_SPLIT_CALLS ? "#" : MIPS_CALL ("jal", operands, 1, 2); }
}

static const char *
output_575 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6150 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("jal", operands, 1, 2); }
}

static const char *
output_576 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6161 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_SPLIT_CALLS ? "#" : MIPS_CALL ("jal", operands, 1, -1); }
}

static const char *
output_577 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6180 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("jal", operands, 1, -1); }
}

static const char *
output_578 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6193 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return TARGET_SPLIT_CALLS ? "#" : MIPS_CALL ("jal", operands, 1, 2); }
}

static const char *
output_579 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6214 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return MIPS_CALL ("jal", operands, 1, 2); }
}

static const char *
output_580 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6254 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  if (TARGET_LOONGSON_2EF || TARGET_LOONGSON_3A)
    /* Loongson 2[ef] and Loongson 3a use load to $0 to perform prefetching.  */
    return "ld\t$0,%a0";
  operands[1] = mips_prefetch_cookie (operands[1], operands[2]);
  return "pref\t%1,%a0";
}
}

static const char *
output_581 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6269 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = mips_prefetch_cookie (operands[2], operands[3]);
  return "prefx\t%2,%1(%0)";
}
}

static const char *
output_582 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6269 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  operands[2] = mips_prefetch_cookie (operands[2], operands[3]);
  return "prefx\t%2,%1(%0)";
}
}

static const char *
output_584 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6286 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
    if (mips_noreorder.nesting_level > 0)
      return "nop";
    else
      return "#nop";
  }
}

static const char * const output_585[] = {
  "mov%T4\t%0,%z2,%1",
  "mov%t4\t%0,%z3,%1",
};

static const char * const output_586[] = {
  "mov%T4\t%0,%z2,%1",
  "mov%t4\t%0,%z3,%1",
};

static const char * const output_587[] = {
  "mov%T4\t%0,%z2,%1",
  "mov%t4\t%0,%z3,%1",
};

static const char * const output_588[] = {
  "mov%T4\t%0,%z2,%1",
  "mov%t4\t%0,%z3,%1",
};

static const char * const output_589[] = {
  "mov%T4\t%0,%z2,%1",
  "mov%t4\t%0,%z3,%1",
};

static const char * const output_590[] = {
  "mov%T4\t%0,%z2,%1",
  "mov%t4\t%0,%z3,%1",
};

static const char * const output_591[] = {
  "mov%T4.s\t%0,%2,%1",
  "mov%t4.s\t%0,%3,%1",
};

static const char * const output_592[] = {
  "mov%T4.s\t%0,%2,%1",
  "mov%t4.s\t%0,%3,%1",
};

static const char * const output_593[] = {
  "mov%T4.s\t%0,%2,%1",
  "mov%t4.s\t%0,%3,%1",
};

static const char * const output_594[] = {
  "mov%T4.d\t%0,%2,%1",
  "mov%t4.d\t%0,%3,%1",
};

static const char * const output_595[] = {
  "mov%T4.d\t%0,%2,%1",
  "mov%t4.d\t%0,%3,%1",
};

static const char * const output_596[] = {
  "mov%T4.d\t%0,%2,%1",
  "mov%t4.d\t%0,%3,%1",
};

static const char *
output_597 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6365 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  assemble_integer (operands[0], INTVAL (operands[1]),
		    BITS_PER_UNIT * INTVAL (operands[1]), 1);
  return "";
}
}

static const char *
output_598 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6376 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{
  REAL_VALUE_TYPE d;

  gcc_assert (GET_CODE (operands[0]) == CONST_DOUBLE);
  REAL_VALUE_FROM_CONST_DOUBLE (d, operands[0]);
  assemble_real (d, GET_MODE (operands[0]),
		 GET_MODE_BITSIZE (GET_MODE (operands[0])));
  return "";
}
}

static const char *
output_600 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 6415 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md"
{ return mips16e_output_save_restore (operands[0], INTVAL (operands[2])); }
}

static const char *
output_601 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 55 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync (); }
}

static const char *
output_602 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 65 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_603 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 65 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_604 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 97 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_605 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_606 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 112 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_607 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 143 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_608 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 143 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_609 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 143 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_610 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 143 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_611 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 143 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_612 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 184 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_613 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 184 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_614 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 184 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_615 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 184 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_616 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 184 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_617 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 230 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_618 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 230 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_619 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 230 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_620 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 230 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_621 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 230 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_622 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 266 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_623 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 305 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_624 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 349 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_625 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_626 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 366 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_627 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 380 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_628 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 380 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_629 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 395 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_630 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 395 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_631 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 410 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_632 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 410 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_633 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 426 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_634 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 426 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_635 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_636 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_637 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_638 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_639 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_640 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 440 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_641 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 454 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_642 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 454 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_643 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 454 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_644 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 454 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_645 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 454 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_646 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 454 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_647 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 469 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_648 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 469 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_649 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 469 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_650 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 469 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_651 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 469 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_652 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 469 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_653 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 481 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_654 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 481 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_655 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 494 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_656 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 494 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_657 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 508 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_658 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 508 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_659 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 523 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_660 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 523 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char *
output_661 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 552 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md"
{ return mips_output_sync_loop (insn, operands); }
}

static const char * const output_662[] = {
  "mov%T4.ps\t%0,%2,%1",
  "mov%t4.ps\t%0,%3,%1",
};

static const char * const output_663[] = {
  "mov%T4.ps\t%0,%2,%1",
  "mov%t4.ps\t%0,%3,%1",
};

static const char * const output_664[] = {
  "movt.ps\t%0,%1,%3",
  "movf.ps\t%0,%2,%3",
};

static const char *
output_669 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 166 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
{
  if (BYTES_BIG_ENDIAN)
    return "cvt.ps.s\t%0,%1,%2";
  else
    return "cvt.ps.s\t%0,%2,%1";
}
}

static const char *
output_670 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 185 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
{
  if (INTVAL (operands[2]) == !BYTES_BIG_ENDIAN)
    return "cvt.s.pu\t%0,%1";
  else
    return "cvt.s.pl\t%0,%1";
}
}

static const char *
output_698 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 528 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
{
  operands[2]
    = gen_rtx_REG (CCmode, REGNO (operands[2]) + INTVAL (operands[3]));
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%F1", "%2,%0"),
					 MIPS_BRANCH ("b%W1", "%2,%0"));
}
}

static const char *
output_699 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 549 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md"
{
  operands[2]
    = gen_rtx_REG (CCmode, REGNO (operands[2]) + INTVAL (operands[3]));
  return mips_output_conditional_branch (insn, operands,
					 MIPS_BRANCH ("b%W1", "%2,%0"),
					 MIPS_BRANCH ("b%F1", "%2,%0"));
}
}

static const char *
output_742 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2])
	  & ~(unsigned HOST_WIDE_INT) 0xf)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0xf);
      return "shll.ph\t%0,%1,%2";
    }
  return "shllv.ph\t%0,%1,%2";
}
}

static const char *
output_743 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 396 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2])
	  & ~(unsigned HOST_WIDE_INT) 0x7)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x7);
      return "shll.qb\t%0,%1,%2";
    }
  return "shllv.qb\t%0,%1,%2";
}
}

static const char *
output_744 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 418 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2])
          & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "shll_s.w\t%0,%1,%2";
    }
  return "shllv_s.w\t%0,%1,%2";
}
}

static const char *
output_745 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 418 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2])
          & ~(unsigned HOST_WIDE_INT) 0xf)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0xf);
      return "shll_s.ph\t%0,%1,%2";
    }
  return "shllv_s.ph\t%0,%1,%2";
}
}

static const char *
output_746 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 438 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x7)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x7);
      return "shrl.qb\t%0,%1,%2";
    }
  return "shrlv.qb\t%0,%1,%2";
}
}

static const char *
output_747 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 457 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0xf)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0xf);
      return "shra.ph\t%0,%1,%2";
    }
  return "shrav.ph\t%0,%1,%2";
}
}

static const char *
output_748 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 475 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2])
	  & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "shra_r.w\t%0,%1,%2";
    }
  return "shrav_r.w\t%0,%1,%2";
}
}

static const char *
output_749 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 475 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2])
	  & ~(unsigned HOST_WIDE_INT) 0xf)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0xf);
      return "shra_r.ph\t%0,%1,%2";
    }
  return "shrav_r.ph\t%0,%1,%2";
}
}

static const char *
output_770 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 780 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[1]) & ~(unsigned HOST_WIDE_INT) 0xff)
	operands[1] = GEN_INT (INTVAL (operands[1]) & 0xff);
      return "repl.qb\t%0,%1";
    }
  return "replv.qb\t%0,%1";
}
}

static const char * const output_771[] = {
  "repl.ph\t%0,%1",
  "replv.ph\t%0,%1",
};

static const char *
output_784 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 902 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "extr.w\t%0,%q1,%2";
    }
  return "extrv.w\t%0,%q1,%2";
}
}

static const char *
output_785 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 923 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "extr_r.w\t%0,%q1,%2";
    }
  return "extrv_r.w\t%0,%q1,%2";
}
}

static const char *
output_786 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 944 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "extr_rs.w\t%0,%q1,%2";
    }
  return "extrv_rs.w\t%0,%q1,%2";
}
}

static const char *
output_787 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 966 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "extr_s.h\t%0,%q1,%2";
    }
  return "extrv_s.h\t%0,%q1,%2";
}
}

static const char *
output_788 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 989 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "extp\t%0,%q1,%2";
    }
  return "extpv\t%0,%q1,%2";
}
}

static const char *
output_789 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1014 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 0x1f)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x1f);
      return "extpdp\t%0,%q1,%2";
    }
  return "extpdpv\t%0,%q1,%2";
}
}

static const char *
output_790 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 1033 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) < -32 || INTVAL (operands[2]) > 31)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 0x3f);
      return "shilo\t%q0,%2";
    }
  return "shilov\t%q0,%2";
}
}

static const char *
output_806 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 137 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (INTVAL (operands[3]) & ~(unsigned HOST_WIDE_INT) 31)
    operands[2] = GEN_INT (INTVAL (operands[2]) & 31);
  return "append\t%0,%z2,%3";
}
}

static const char *
output_807 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 152 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (INTVAL (operands[3]) & ~(unsigned HOST_WIDE_INT) 3)
    operands[2] = GEN_INT (INTVAL (operands[2]) & 3);
  return "balign\t%0,%z2,%3";
}
}

static const char *
output_820 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 324 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (INTVAL (operands[3]) & ~(unsigned HOST_WIDE_INT) 31)
    operands[2] = GEN_INT (INTVAL (operands[2]) & 31);
  return "precr_sra.ph.w\t%0,%z2,%3";
}
}

static const char *
output_821 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 339 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (INTVAL (operands[3]) & ~(unsigned HOST_WIDE_INT) 31)
    operands[2] = GEN_INT (INTVAL (operands[2]) & 31);
  return "precr_sra_r.ph.w\t%0,%z2,%3";
}
}

static const char *
output_822 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 354 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (INTVAL (operands[3]) & ~(unsigned HOST_WIDE_INT) 31)
    operands[2] = GEN_INT (INTVAL (operands[2]) & 31);
  return "prepend\t%0,%z2,%3";
}
}

static const char *
output_823 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 368 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 7)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 7);
      return "shra.qb\t%0,%z1,%2";
    }
  return "shrav.qb\t%0,%z1,%2";
}
}

static const char *
output_824 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 387 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 7)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 7);
      return "shra_r.qb\t%0,%z1,%2";
    }
  return "shrav_r.qb\t%0,%z1,%2";
}
}

static const char *
output_825 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 405 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md"
{
  if (which_alternative == 0)
    {
      if (INTVAL (operands[2]) & ~(unsigned HOST_WIDE_INT) 15)
	operands[2] = GEN_INT (INTVAL (operands[2]) & 15);
      return "shrl.ph\t%0,%z1,%2";
    }
  return "shrlv.ph\t%0,%z1,%2";
}
}

static const char *
output_901 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_902 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_903 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 110 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{ return mips_output_move (operands[0], operands[1]); }
}

static const char *
output_966 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 508 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("div.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsdiv\t%0,%1,%2", operands);
  }
}

static const char *
output_967 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 508 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("divu.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsdivu\t%0,%1,%2", operands);
  }
}

static const char *
output_968 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 508 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("ddiv.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsddiv\t%0,%1,%2", operands);
  }
}

static const char *
output_969 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 508 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("ddivu.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsddivu\t%0,%1,%2", operands);
  }
}

static const char *
output_970 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 522 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("mod.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsmod\t%0,%1,%2", operands);
  }
}

static const char *
output_971 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 522 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("modu.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsmodu\t%0,%1,%2", operands);
  }
}

static const char *
output_972 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 522 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("dmod.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsdmod\t%0,%1,%2", operands);
  }
}

static const char *
output_973 (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)
{
#line 522 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md"
{
    if (TARGET_LOONGSON_2EF)
      return mips_output_division ("dmodu.g\t%0,%1,%2", operands);
    else
      return mips_output_division ("gsdmodu\t%0,%1,%2", operands);
  }
}



static const struct insn_operand_data operand_data[] = 
{
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    0
  },
  {
    trap_comparison_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    SImode,
    0,
    0,
    1
  },
  {
    trap_comparison_operator,
    "",
    DImode,
    0,
    1,
    0
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,Q",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,Q",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=ks,d,d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "ks,ks,0,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "Q,Q,Q,O,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=ks,d,d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "ks,ks,0,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "Q,Q,Q,O,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,Q",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "Q,O,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=l,X",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d,l",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=l,X",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=l",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=l",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=l",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l*?*?,d?",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,l",
    SImode,
    0,
    0,
    0
  },
  {
    scratch_operand,
    "=X,&d",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l*?*?,d*?,d?",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,l,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,3,l",
    SImode,
    0,
    0,
    0
  },
  {
    scratch_operand,
    "=X,X,&d",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,l",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,3",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,1",
    SImode,
    0,
    0,
    0
  },
  {
    scratch_operand,
    "=d,d",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=l*?*?,d?",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,l",
    SImode,
    0,
    0,
    0
  },
  {
    scratch_operand,
    "=X,&d",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=l,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,l",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=ka",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    TImode,
    0,
    0,
    0
  },
  {
    scratch_operand,
    "=d",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=x",
    TImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=l",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=x",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=ka",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=x",
    TImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    TImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    TImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "+l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    const_1_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    const_1_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    const_1_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=l",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=x",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d,d,d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "o,o,W,d,d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    and_operand,
    "Yb,Yh,Yw,K,Yx,Yw,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d,d,d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "o,o,W,d,d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    and_operand,
    "Yb,Yh,Yw,K,Yx,Yw,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "%o,o,W,d,0",
    SImode,
    0,
    0,
    1
  },
  {
    and_operand,
    "Yb,Yh,Yw,Yw,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "%o,o,W,d,0",
    DImode,
    0,
    0,
    1
  },
  {
    and_operand,
    "Yb,Yh,Yw,Yw,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%d,d",
    SImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "d,K",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%d,d",
    DImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "d,K",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%0",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,t,t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%0,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "d,K,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,t,t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%0,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "d,K,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_arith_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_arith_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_arith_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "d,W",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "d,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "d,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "d,m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "d,m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "d,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    HImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "0,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "0,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "0,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "0,m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "0,m",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "0,m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=d",
    DFmode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=d",
    SFmode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "+d",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "I",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "I",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "+d",
    DImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "I",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "I",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    BLKmode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    BLKmode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    BLKmode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    BLKmode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "=m",
    BLKmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "=m",
    BLKmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+m",
    BLKmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+m",
    BLKmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    absolute_symbolic_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=&d",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    got_page_ofst_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    got_page_ofst_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    stack_operand,
    "=m",
    SImode,
    0,
    0,
    1
  },
  {
    stack_operand,
    "=m",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,d,m,*a,*d,*f,*f,*d,*m,*B*C*D,*B*C*D,*d,*m",
    DImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,i,m,d,*J*d,*a,*J*d,*m,*f,*f,*d,*m,*B*C*D,*B*C*D",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,m,*d",
    DImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,m,d,*x",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*a,*d,*B*C*D,*B*C*D,*d,*m",
    DImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    DImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    SImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V2HImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V2HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V4QImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V4QImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V2HQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V2HQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V2HAmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V2HAmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V4QQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V4QQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,e,d,m,*f,*f,*d,*m,*d,*z,*a,*d,*B*C*D,*B*C*D,*d,*m",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,U,T,m,dJ,*d*J,*m,*f,*f,*z,*d,*J*d,*a,*d,*m,*B*C*D,*B*C*D",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    SImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V2HImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V2HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V4QImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V4QImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V2HQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V2HAmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V2HAmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V4QQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V4QQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,d,d,m,*d",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,U,kf,m,d,*a",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,*d,*d,*m,*d,*f,*f,*f,*m",
    CCmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "z,*d,*m,*d,*f,*d,*f,*m,*f",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,d,m,*a,*d",
    HImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,I,m,dJ,*d*J,*a",
    HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,m,*d",
    HImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,m,d,*a",
    HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,d,m,*a,*d",
    QImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,I,m,dJ,*d*J,*a",
    QImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,m,*d",
    QImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,m,d,*a",
    QImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=f,f,f,m,m,*f,*d,*d,*d,*m",
    SFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "f,G,m,f,G,*d,*f,*G*d,*m,*d",
    SFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,m",
    SFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "Gd,m,d",
    SFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,m",
    SFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,m,d",
    SFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=f,f,f,m,m,*f,*d,*d,*d,*m",
    DFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "f,G,m,f,G,*d,*f,*d*G,*m,*d",
    DFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,m",
    DFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "dG,m,dG",
    DFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,m",
    DFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,m,d",
    DFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,d,m,*a,*d",
    TImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,i,m,dJ,*d*J,*a",
    TImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,d,d,m,*d",
    TImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,K,N,m,d,*a",
    TImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,d,m,f,d,f,m",
    TFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "dG,m,dG,dG,f,m,f",
    TFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,y,d,d,m",
    TFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "d,d,y,m,d",
    TFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=f,f,f,m,m,*f,*d,*d,*d,*m",
    V2SFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "f,YG,m,f,YG,*d,*f,*d*YG,*m,*d",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "x",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "x",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "x",
    TImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "x",
    TImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=x",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=x",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "l",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=x",
    TImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "l",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=x",
    TImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "l",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    DFmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    DImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V2SImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V4HImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V8QImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    TFmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    DFmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    DImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V2SImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V4HImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V8QImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    TFmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "dJ,m",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    TFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    DFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    V2SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    V4HImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    V8QImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,f",
    TFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DFmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V4HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V8QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    TFmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    TFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    TFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=y",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    cprestore_save_slot_operand,
    "=X,X",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "I,i",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=X,&d",
    SImode,
    0,
    0,
    1
  },
  {
    cprestore_load_slot_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    pmode_register_operand,
    "d",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    address_operand,
    "p",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "m",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "I",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "z",
    CCmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    order_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    order_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "d,t",
    SImode,
    0,
    0,
    1
  },
  {
    pc_or_label_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    pc_or_label_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "d,t",
    DImode,
    0,
    0,
    1
  },
  {
    pc_or_label_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    pc_or_label_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_imm10_operand,
    "d,J,YB",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_imm10_operand,
    "d,J,YB",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%d,d,d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_imm10_operand,
    "d,J,YB",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "%d,d,d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_imm10_operand,
    "d,J,YB",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dI",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t,t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t,t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t,t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t,t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "d,I",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=t",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    sle_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    pmode_register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=B,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,B",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=&d",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=&d",
    DImode,
    0,
    0,
    0
  },
  {
    nonimmediate_operand,
    "=d,m",
    SImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "m,d",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=d,m",
    DImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "m,d",
    DImode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "j,S",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "j,S",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "c,S",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "cS",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_call_insn_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "cS",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_call_insn_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "c,S",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    address_operand,
    "p",
    QImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,0",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "0,dJ",
    SImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,0",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "0,dJ",
    DImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,0",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "0,dJ",
    SImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    DImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,0",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "0,dJ",
    DImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    DImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z,z",
    CCmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,0",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "0,dJ",
    SImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    CCmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z,z",
    CCmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,0",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "0,dJ",
    DImode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    CCmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    SFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    SFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    DImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z,z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    SFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    CCmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    DFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    DFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    DImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z,z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    DFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    CCmode,
    0,
    1,
    0
  },
  {
    consttable_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    BLKmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,dJ",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,dJ",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ,dJ",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "d,J",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=&d",
    SImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=&d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=&d",
    SImode,
    0,
    0,
    0
  },
  {
    memory_operand,
    "+R",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    SImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "K,d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    DImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "K,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    SImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "K,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d,&d",
    DImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R,R",
    DImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "K,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "+R",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    DImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "=f,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f,0",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z,z",
    CCV2mode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    const_0_or_1_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=z",
    CCV4mode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=z",
    CCV2mode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z",
    CCV4mode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "z",
    CCV2mode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    equality_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "z",
    CCV2mode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    V2HImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    V4QImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d,d",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=a",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=a",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=a",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    V4QImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_imm10_operand,
    "YB,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "a,a",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=a,a",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0,0",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    const_uimm6_operand,
    "YA",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    const_uimm6_operand,
    "YA",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "I",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V4QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V4QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V4QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=a",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    V4QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dJ",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "n",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    V4QImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG,dYG",
    V4QImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d,d",
    V2HImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "dYG,dYG",
    V2HImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "I,d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    QQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    QQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    QQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    USQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    USQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    USQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    UDQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UDQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UDQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    SAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    DAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    USAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    USAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    USAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    UDAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UDAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    UDAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HAmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    V2HQmode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    HQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    HQmode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SQmode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "=x",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "=a",
    DQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SQmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    DQmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=m,f,d,f,d,m,d",
    V2SImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "f,m,f,dYG,dYG,dYG,m",
    V2SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=m,f,d,f,d,m,d",
    V4HImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "f,m,f,dYG,dYG,dYG,m",
    V4HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "=m,f,d,f,d,m,d",
    V8QImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "f,m,f,dYG,dYG,dYG,m",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "0",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V4HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    V2SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "f",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "d",
    DImode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    reg_or_0_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_0_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    reg_or_0_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    const_0_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    lo_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    lo_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "",
    SImode,
    0,
    0,
    0
  },
  {
    scratch_operand,
    "",
    SImode,
    0,
    0,
    0
  },
  {
    lo_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    macc_msac_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "d",
    SImode,
    0,
    0,
    0
  },
  {
    lo_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    macc_msac_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "d",
    SImode,
    0,
    0,
    0
  },
  {
    lo_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    macc_msac_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    hilo_operand,
    "",
    TImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "",
    DImode,
    0,
    0,
    0
  },
  {
    register_operand,
    "",
    TImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    reg_or_1_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    reg_or_1_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    reg_or_1_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    and_reg_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    and_reg_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    uns_arith_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    absolute_symbolic_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "d",
    DImode,
    0,
    0,
    0
  },
  {
    d_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    absolute_symbolic_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    absolute_symbolic_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "",
    DImode,
    0,
    0,
    0
  },
  {
    d_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    absolute_symbolic_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    got_disp_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    got_page_ofst_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    got_page_ofst_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    splittable_const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    splittable_const_int_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2HImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2HImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4QImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4QImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2HQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2HQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2UHQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2HAmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2HAmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2UHAmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4QQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4QQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4UQQmode,
    0,
    0,
    1
  },
  {
    fcc_reload_operand,
    "=z",
    CCmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&f",
    TFmode,
    0,
    0,
    1
  },
  {
    fcc_reload_operand,
    "=z",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    CCmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "=&f",
    TFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    TImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    TImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    TFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    TFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    V2SImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    V2SImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    V4HImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    V4HImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    V8QImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    V8QImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    TImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    TImode,
    0,
    0,
    1
  },
  {
    nonimmediate_operand,
    "",
    TFmode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    TFmode,
    0,
    0,
    1
  },
  {
    d_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4HImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V4HImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V8QImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V8QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    symbol_ref_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    cprestore_save_slot_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    pmode_register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    pmode_register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    BLKmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    BLKmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    arith_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    immediate_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    nonmemory_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    nonmemory_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    mips_cstore_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    nonmemory_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    mips_cstore_operator,
    "",
    SImode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    nonmemory_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    scratch_operand,
    "",
    VOIDmode,
    0,
    0,
    0
  },
  {
    nonimmediate_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    move_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    call_insn_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    reg_or_0_operand,
    "",
    DImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    DFmode,
    0,
    0,
    1
  },
  {
    small_data_pattern,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    QImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    memory_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    general_operand,
    "",
    HImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    comparison_operator,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    const_0_or_1_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    CCV4mode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    const_int_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    CCV2mode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    1,
    0
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SFmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    pmode_register_operand,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    SImode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V2SImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V4HImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
  {
    register_operand,
    "",
    V8QImode,
    0,
    0,
    1
  },
  {
    0,
    "",
    VOIDmode,
    0,
    0,
    1
  },
};


#if GCC_VERSION >= 2007
__extension__
#endif

const struct insn_data_d insn_data[] = 
{
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md:105 */
  {
    "ls2_alu1_turn_enabled_insn",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_0 },
#else
    { 0, 0, output_0 },
#endif
    (insn_gen_fn) gen_ls2_alu1_turn_enabled_insn,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md:116 */
  {
    "ls2_alu2_turn_enabled_insn",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_1 },
#else
    { 0, 0, output_1 },
#endif
    (insn_gen_fn) gen_ls2_alu2_turn_enabled_insn,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md:127 */
  {
    "ls2_falu1_turn_enabled_insn",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_2 },
#else
    { 0, 0, output_2 },
#endif
    (insn_gen_fn) gen_ls2_falu1_turn_enabled_insn,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson2ef.md:138 */
  {
    "ls2_falu2_turn_enabled_insn",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_3 },
#else
    { 0, 0, output_3 },
#endif
    (insn_gen_fn) gen_ls2_falu2_turn_enabled_insn,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:926 */
  {
    "trap",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_4 },
#else
    { 0, 0, output_4 },
#endif
    (insn_gen_fn) gen_trap,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:950 */
  {
    "*conditional_trapsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "t%C0\t%z1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[1],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:950 */
  {
    "*conditional_trapdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "t%C0\t%z1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[4],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:967 */
  {
    "addsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "add.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addsf3,
    &operand_data[7],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:967 */
  {
    "adddf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "add.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_adddf3,
    &operand_data[10],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:967 */
  {
    "addv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "add.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addv2sf3,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:982 */
  {
    "*addsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_10 },
#else
    { 0, output_10, 0 },
#endif
    0,
    &operand_data[16],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:982 */
  {
    "*adddi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_11 },
#else
    { 0, output_11, 0 },
#endif
    0,
    &operand_data[19],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:993 */
  {
    "*addsi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_12 },
#else
    { 0, output_12, 0 },
#endif
    0,
    &operand_data[22],
    3,
    0,
    5,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:993 */
  {
    "*adddi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_13 },
#else
    { 0, output_13, 0 },
#endif
    0,
    &operand_data[25],
    3,
    0,
    5,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1133 */
  {
    "*addsi3_extended",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_14 },
#else
    { 0, output_14, 0 },
#endif
    0,
    &operand_data[28],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1147 */
  {
    "*addsi3_extended_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[31],
    3,
    0,
    3,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1163 */
  {
    "*baddu_si_eb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "baddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1173 */
  {
    "*baddu_si_el",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "baddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1183 */
  {
    "*baddu_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "baddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1183 */
  {
    "*baddu_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "baddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1201 */
  {
    "subsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sub.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subsf3,
    &operand_data[7],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1201 */
  {
    "subdf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sub.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subdf3,
    &operand_data[10],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1201 */
  {
    "subv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sub.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subv2sf3,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1210 */
  {
    "subsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subsi3,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1210 */
  {
    "subdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsubu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subdi3,
    &operand_data[40],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1219 */
  {
    "*subsi3_extended",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[43],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1244 */
  {
    "*mulsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[7],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1244 */
  {
    "*muldf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[10],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1257 */
  {
    "*mulsf3_r4300",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul.s\t%0,%1,%2\n\tnop",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[7],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1257 */
  {
    "*muldf3_r4300",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul.d\t%0,%1,%2\n\tnop",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[10],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1267 */
  {
    "mulv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulv2sf3,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1341 */
  {
    "mulsi3_mul3_loongson",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_31 },
#else
    { 0, 0, output_31 },
#endif
    (insn_gen_fn) gen_mulsi3_mul3_loongson,
    &operand_data[34],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1341 */
  {
    "muldi3_mul3_loongson",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_32 },
#else
    { 0, 0, output_32 },
#endif
    (insn_gen_fn) gen_muldi3_mul3_loongson,
    &operand_data[40],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1355 */
  {
    "mulsi3_mul3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_33 },
#else
    { 0, 0, output_33 },
#endif
    (insn_gen_fn) gen_mulsi3_mul3,
    &operand_data[46],
    4,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1355 */
  {
    "muldi3_mul3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_34 },
#else
    { 0, 0, output_34 },
#endif
    (insn_gen_fn) gen_muldi3_mul3,
    &operand_data[50],
    4,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1394 */
  {
    "mulsi3_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mult\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulsi3_internal,
    &operand_data[54],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1394 */
  {
    "muldi3_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmult\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_muldi3_internal,
    &operand_data[57],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1403 */
  {
    "mulsi3_r4000",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mult\t%1,%2\n\tmflo\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulsi3_r4000,
    &operand_data[60],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1403 */
  {
    "muldi3_r4000",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmult\t%1,%2\n\tmflo\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_muldi3_r4000,
    &operand_data[64],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1458 */
  {
    "*mul_acc_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_39 },
#else
    { 0, output_39, 0 },
#endif
    0,
    &operand_data[68],
    6,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1475 */
  {
    "*mul_acc_si_r3900",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_40 },
#else
    { 0, output_40, 0 },
#endif
    0,
    &operand_data[74],
    6,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1507 */
  {
    "*macc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_41 },
#else
    { 0, 0, output_41 },
#endif
    0,
    &operand_data[80],
    5,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1528 */
  {
    "*msac",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_42 },
#else
    { 0, 0, output_42 },
#endif
    0,
    &operand_data[85],
    5,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1547 */
  {
    "*msac_using_macc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[85],
    6,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1571 */
  {
    "*macc2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "macc\t%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[91],
    4,
    4,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1585 */
  {
    "*msac2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msac\t%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[91],
    4,
    4,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1687 */
  {
    "*mul_sub_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_46 },
#else
    { 0, output_46, 0 },
#endif
    0,
    &operand_data[95],
    6,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1718 */
  {
    "*muls",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_47 },
#else
    { 0, output_47, 0 },
#endif
    0,
    &operand_data[101],
    4,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1744 */
  {
    "mulsidi3_32bit",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_48 },
#else
    { 0, 0, output_48 },
#endif
    (insn_gen_fn) gen_mulsidi3_32bit,
    &operand_data[105],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1744 */
  {
    "umulsidi3_32bit",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_49 },
#else
    { 0, 0, output_49 },
#endif
    (insn_gen_fn) gen_umulsidi3_32bit,
    &operand_data[105],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1758 */
  {
    "mulsidi3_32bit_r4000",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mult\t%1,%2\n\tmflo\t%L0\n\tmfhi\t%M0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulsidi3_32bit_r4000,
    &operand_data[108],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1758 */
  {
    "umulsidi3_32bit_r4000",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "multu\t%1,%2\n\tmflo\t%L0\n\tmfhi\t%M0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulsidi3_32bit_r4000,
    &operand_data[108],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1769 */
  {
    "mulsidi3_64bit",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulsidi3_64bit,
    &operand_data[112],
    5,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1769 */
  {
    "umulsidi3_64bit",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulsidi3_64bit,
    &operand_data[112],
    5,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1839 */
  {
    "mulsidi3_64bit_hilo",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mult\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulsidi3_64bit_hilo,
    &operand_data[117],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1839 */
  {
    "umulsidi3_64bit_hilo",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "multu\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulsidi3_64bit_hilo,
    &operand_data[117],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1852 */
  {
    "mulsidi3_64bit_dmul",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmul\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulsidi3_64bit_dmul,
    &operand_data[120],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1863 */
  {
    "*muls_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "muls\t$0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[124],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1863 */
  {
    "*mulsu_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulsu\t$0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[124],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1881 */
  {
    "msubsidi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_59 },
#else
    { 0, 0, output_59 },
#endif
    (insn_gen_fn) gen_msubsidi4,
    &operand_data[127],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1881 */
  {
    "umsubsidi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_60 },
#else
    { 0, 0, output_60 },
#endif
    (insn_gen_fn) gen_umsubsidi4,
    &operand_data[127],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1921 */
  {
    "smulsi3_highpart_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_61 },
#else
    { 0, 0, output_61 },
#endif
    (insn_gen_fn) gen_smulsi3_highpart_internal,
    &operand_data[60],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1921 */
  {
    "umulsi3_highpart_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_62 },
#else
    { 0, 0, output_62 },
#endif
    (insn_gen_fn) gen_umulsi3_highpart_internal,
    &operand_data[60],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1954 */
  {
    "smulsi3_highpart_mulhi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulhi\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_smulsi3_highpart_mulhi_internal,
    &operand_data[60],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1954 */
  {
    "umulsi3_highpart_mulhi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulhiu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulsi3_highpart_mulhi_internal,
    &operand_data[60],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1968 */
  {
    "*smulsi3_highpart_neg_mulhi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulshi\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[60],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1968 */
  {
    "*umulsi3_highpart_neg_mulhi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulshiu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[60],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1986 */
  {
    "smuldi3_highpart",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_67 },
#else
    { 0, 0, output_67 },
#endif
    (insn_gen_fn) gen_smuldi3_highpart,
    &operand_data[64],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1986 */
  {
    "umuldi3_highpart",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_68 },
#else
    { 0, 0, output_68 },
#endif
    (insn_gen_fn) gen_umuldi3_highpart,
    &operand_data[64],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2024 */
  {
    "mulditi3_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmult\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulditi3_internal,
    &operand_data[131],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2024 */
  {
    "umulditi3_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmultu\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulditi3_internal,
    &operand_data[131],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2035 */
  {
    "mulditi3_r4000",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmult\t%1,%2\n\tmflo\t%L0\n\tmfhi\t%M0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulditi3_r4000,
    &operand_data[134],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2035 */
  {
    "umulditi3_r4000",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dmultu\t%1,%2\n\tmflo\t%L0\n\tmfhi\t%M0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulditi3_r4000,
    &operand_data[134],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2051 */
  {
    "madsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mad\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_madsi,
    &operand_data[138],
    3,
    1,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2063 */
  {
    "maddsidi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_74 },
#else
    { 0, 0, output_74 },
#endif
    (insn_gen_fn) gen_maddsidi4,
    &operand_data[127],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2063 */
  {
    "umaddsidi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_75 },
#else
    { 0, 0, output_75 },
#endif
    (insn_gen_fn) gen_umaddsidi4,
    &operand_data[127],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2087 */
  {
    "*madd4sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "madd.s\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[141],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2087 */
  {
    "*madd4df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "madd.d\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[145],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2087 */
  {
    "*madd4v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "madd.ps\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[149],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2097 */
  {
    "*madd3sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "madd.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[153],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2097 */
  {
    "*madd3df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "madd.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[157],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2097 */
  {
    "*madd3v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "madd.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[161],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2107 */
  {
    "*msub4sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msub.s\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[141],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2107 */
  {
    "*msub4df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msub.d\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[145],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2107 */
  {
    "*msub4v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msub.ps\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[149],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2117 */
  {
    "*msub3sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msub.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[153],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2117 */
  {
    "*msub3df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msub.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[157],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2117 */
  {
    "*msub3v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "msub.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[161],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2127 */
  {
    "*nmadd4sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.s\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[141],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2127 */
  {
    "*nmadd4df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.d\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[145],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2127 */
  {
    "*nmadd4v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.ps\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[149],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2141 */
  {
    "*nmadd3sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[153],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2141 */
  {
    "*nmadd3df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[157],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2141 */
  {
    "*nmadd3v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[161],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2155 */
  {
    "*nmadd4sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.s\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[141],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2155 */
  {
    "*nmadd4df_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.d\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[145],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2155 */
  {
    "*nmadd4v2sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.ps\t%0,%3,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[149],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2169 */
  {
    "*nmadd3sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[153],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2169 */
  {
    "*nmadd3df_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[157],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2169 */
  {
    "*nmadd3v2sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmadd.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[161],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2183 */
  {
    "*nmsub4sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.s\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[141],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2183 */
  {
    "*nmsub4df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.d\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[145],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2183 */
  {
    "*nmsub4v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.ps\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[149],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2197 */
  {
    "*nmsub3sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[165],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2197 */
  {
    "*nmsub3df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[169],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2197 */
  {
    "*nmsub3v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[173],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2211 */
  {
    "*nmsub4sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.s\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[141],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2211 */
  {
    "*nmsub4df_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.d\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[145],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2211 */
  {
    "*nmsub4v2sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.ps\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[149],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2225 */
  {
    "*nmsub3sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[153],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2225 */
  {
    "*nmsub3df_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[157],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2225 */
  {
    "*nmsub3v2sf_fastmath",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nmsub.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[161],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2270 */
  {
    "*divsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_112 },
#else
    { 0, 0, output_112 },
#endif
    0,
    &operand_data[7],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2270 */
  {
    "*divdf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_113 },
#else
    { 0, 0, output_113 },
#endif
    0,
    &operand_data[10],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2270 */
  {
    "*divv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_114 },
#else
    { 0, 0, output_114 },
#endif
    0,
    &operand_data[13],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2288 */
  {
    "*recipsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_115 },
#else
    { 0, 0, output_115 },
#endif
    0,
    &operand_data[177],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2288 */
  {
    "*recipdf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_116 },
#else
    { 0, 0, output_116 },
#endif
    0,
    &operand_data[180],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2288 */
  {
    "*recipv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_117 },
#else
    { 0, 0, output_117 },
#endif
    0,
    &operand_data[183],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2308 */
  {
    "divmodsi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_divmodsi4,
    &operand_data[91],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2308 */
  {
    "divmoddi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_divmoddi4,
    &operand_data[186],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2340 */
  {
    "udivmodsi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_udivmodsi4,
    &operand_data[91],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2340 */
  {
    "udivmoddi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_udivmoddi4,
    &operand_data[186],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "divmodsi4_hilo_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_122 },
#else
    { 0, 0, output_122 },
#endif
    (insn_gen_fn) gen_divmodsi4_hilo_di,
    &operand_data[124],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "udivmodsi4_hilo_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_123 },
#else
    { 0, 0, output_123 },
#endif
    (insn_gen_fn) gen_udivmodsi4_hilo_di,
    &operand_data[124],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "divmoddi4_hilo_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_124 },
#else
    { 0, 0, output_124 },
#endif
    (insn_gen_fn) gen_divmoddi4_hilo_di,
    &operand_data[190],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "udivmoddi4_hilo_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_125 },
#else
    { 0, 0, output_125 },
#endif
    (insn_gen_fn) gen_udivmoddi4_hilo_di,
    &operand_data[190],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "divmodsi4_hilo_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_126 },
#else
    { 0, 0, output_126 },
#endif
    (insn_gen_fn) gen_divmodsi4_hilo_ti,
    &operand_data[117],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "udivmodsi4_hilo_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_127 },
#else
    { 0, 0, output_127 },
#endif
    (insn_gen_fn) gen_udivmodsi4_hilo_ti,
    &operand_data[117],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "divmoddi4_hilo_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_128 },
#else
    { 0, 0, output_128 },
#endif
    (insn_gen_fn) gen_divmoddi4_hilo_ti,
    &operand_data[131],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2372 */
  {
    "udivmoddi4_hilo_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_129 },
#else
    { 0, 0, output_129 },
#endif
    (insn_gen_fn) gen_udivmoddi4_hilo_ti,
    &operand_data[131],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2393 */
  {
    "sqrtsf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_130 },
#else
    { 0, 0, output_130 },
#endif
    (insn_gen_fn) gen_sqrtsf2,
    &operand_data[7],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2393 */
  {
    "sqrtdf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_131 },
#else
    { 0, 0, output_131 },
#endif
    (insn_gen_fn) gen_sqrtdf2,
    &operand_data[10],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2393 */
  {
    "sqrtv2sf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_132 },
#else
    { 0, 0, output_132 },
#endif
    (insn_gen_fn) gen_sqrtv2sf2,
    &operand_data[13],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2410 */
  {
    "*rsqrtsfa",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_133 },
#else
    { 0, 0, output_133 },
#endif
    0,
    &operand_data[177],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2410 */
  {
    "*rsqrtdfa",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_134 },
#else
    { 0, 0, output_134 },
#endif
    0,
    &operand_data[180],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2410 */
  {
    "*rsqrtv2sfa",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_135 },
#else
    { 0, 0, output_135 },
#endif
    0,
    &operand_data[183],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2428 */
  {
    "*rsqrtsfb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_136 },
#else
    { 0, 0, output_136 },
#endif
    0,
    &operand_data[177],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2428 */
  {
    "*rsqrtdfb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_137 },
#else
    { 0, 0, output_137 },
#endif
    0,
    &operand_data[180],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2428 */
  {
    "*rsqrtv2sfb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_138 },
#else
    { 0, 0, output_138 },
#endif
    0,
    &operand_data[183],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2460 */
  {
    "abssf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "abs.s\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_abssf2,
    &operand_data[7],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2460 */
  {
    "absdf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "abs.d\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_absdf2,
    &operand_data[10],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2460 */
  {
    "absv2sf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "abs.ps\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_absv2sf2,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2476 */
  {
    "clzsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "clz\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_clzsi2,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2476 */
  {
    "clzdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dclz\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_clzdi2,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2492 */
  {
    "popcountsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pop\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_popcountsi2,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2492 */
  {
    "popcountdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpop\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_popcountdi2,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2507 */
  {
    "negsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_146 },
#else
    { 0, 0, output_146 },
#endif
    (insn_gen_fn) gen_negsi2,
    &operand_data[34],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2520 */
  {
    "negdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsubu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_negdi2,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2532 */
  {
    "negsf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "neg.s\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_negsf2,
    &operand_data[7],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2532 */
  {
    "negdf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "neg.d\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_negdf2,
    &operand_data[10],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2532 */
  {
    "negv2sf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "neg.ps\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_negv2sf2,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2540 */
  {
    "one_cmplsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_151 },
#else
    { 0, 0, output_151 },
#endif
    (insn_gen_fn) gen_one_cmplsi2,
    &operand_data[34],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2540 */
  {
    "one_cmpldi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_152 },
#else
    { 0, 0, output_152 },
#endif
    (insn_gen_fn) gen_one_cmpldi2,
    &operand_data[40],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2590 */
  {
    "*andsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_153 },
#else
    { 0, 0, output_153 },
#endif
    0,
    &operand_data[193],
    3,
    0,
    7,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2590 */
  {
    "*anddi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_154 },
#else
    { 0, 0, output_154 },
#endif
    0,
    &operand_data[196],
    3,
    0,
    7,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2626 */
  {
    "*andsi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_155 },
#else
    { 0, 0, output_155 },
#endif
    0,
    &operand_data[199],
    3,
    0,
    5,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2626 */
  {
    "*anddi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_156 },
#else
    { 0, 0, output_156 },
#endif
    0,
    &operand_data[202],
    3,
    0,
    5,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2664 */
  {
    "*iorsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_157 },
#else
    { 0, output_157, 0 },
#endif
    0,
    &operand_data[205],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2664 */
  {
    "*iordi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_158 },
#else
    { 0, output_158, 0 },
#endif
    0,
    &operand_data[208],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2675 */
  {
    "*iorsi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "or\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[211],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2675 */
  {
    "*iordi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "or\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[214],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2691 */
  {
    "*mips.md:2691",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_161 },
#else
    { 0, output_161, 0 },
#endif
    0,
    &operand_data[205],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2691 */
  {
    "*mips.md:2691",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_162 },
#else
    { 0, output_162, 0 },
#endif
    0,
    &operand_data[208],
    3,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2702 */
  {
    "*mips.md:2702",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_163 },
#else
    { 0, output_163, 0 },
#endif
    0,
    &operand_data[217],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2702 */
  {
    "*mips.md:2702",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_164 },
#else
    { 0, output_164, 0 },
#endif
    0,
    &operand_data[220],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2720 */
  {
    "*norsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nor\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2720 */
  {
    "*nordi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "nor\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2738 */
  {
    "truncdfsf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.s.d\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_truncdfsf2,
    &operand_data[223],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2760 */
  {
    "truncdiqi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_168 },
#else
    { 0, output_168, 0 },
#endif
    (insn_gen_fn) gen_truncdiqi2,
    &operand_data[225],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2760 */
  {
    "truncdihi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_169 },
#else
    { 0, output_169, 0 },
#endif
    (insn_gen_fn) gen_truncdihi2,
    &operand_data[227],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2760 */
  {
    "truncdisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_170 },
#else
    { 0, output_170, 0 },
#endif
    (insn_gen_fn) gen_truncdisi2,
    &operand_data[229],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2772 */
  {
    "*ashr_truncqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsra\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[231],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2772 */
  {
    "*ashr_trunchi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsra\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2772 */
  {
    "*ashr_truncsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsra\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[237],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2782 */
  {
    "*lshr32_truncqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsra\t%0,%1,32",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[231],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2782 */
  {
    "*lshr32_trunchi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsra\t%0,%1,32",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2782 */
  {
    "*lshr32_truncsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsra\t%0,%1,32",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2795 */
  {
    "*ashr_truncqi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%2,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[231],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2795 */
  {
    "*lshr_truncqi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%2,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[231],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2795 */
  {
    "*ashr_trunchi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%2,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2795 */
  {
    "*lshr_trunchi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%2,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2795 */
  {
    "*ashr_truncsi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%2,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[237],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2795 */
  {
    "*lshr_truncsi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%2,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[237],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2819 */
  {
    "*zero_extendsidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_183 },
#else
    { 0, output_183, 0 },
#endif
    0,
    &operand_data[240],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2835 */
  {
    "*zero_extendsidi2_dext",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_184 },
#else
    { 0, output_184, 0 },
#endif
    0,
    &operand_data[240],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2874 */
  {
    "*zero_extendqisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_185 },
#else
    { 0, output_185, 0 },
#endif
    0,
    &operand_data[242],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2874 */
  {
    "*zero_extendqidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_186 },
#else
    { 0, output_186, 0 },
#endif
    0,
    &operand_data[244],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2874 */
  {
    "*zero_extendhisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_187 },
#else
    { 0, output_187, 0 },
#endif
    0,
    &operand_data[246],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2874 */
  {
    "*zero_extendhidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_188 },
#else
    { 0, output_188, 0 },
#endif
    0,
    &operand_data[248],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2885 */
  {
    "*zero_extendqisi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "zeb\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[250],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2885 */
  {
    "*zero_extendqidi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "zeb\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[252],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2885 */
  {
    "*zero_extendhisi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "zeh\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[254],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2885 */
  {
    "*zero_extendhidi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "zeh\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[256],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2894 */
  {
    "*zero_extendqisi2_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lbu\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[258],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2894 */
  {
    "*zero_extendqidi2_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lbu\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[260],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2894 */
  {
    "*zero_extendhisi2_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lhu\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[262],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2894 */
  {
    "*zero_extendhidi2_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lhu\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[264],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2915 */
  {
    "*zero_extendqihi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_197 },
#else
    { 0, output_197, 0 },
#endif
    0,
    &operand_data[266],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2925 */
  {
    "*zero_extendqihi2_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lbu\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[268],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2935 */
  {
    "*zero_extendsi_truncqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_199 },
#else
    { 0, 0, output_199 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2935 */
  {
    "*zero_extenddi_truncqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_200 },
#else
    { 0, 0, output_200 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2935 */
  {
    "*zero_extendsi_trunchi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_201 },
#else
    { 0, 0, output_201 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2935 */
  {
    "*zero_extenddi_trunchi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_202 },
#else
    { 0, 0, output_202 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2947 */
  {
    "*zero_extendhi_truncqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "andi\t%0,%1,0xff",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2974 */
  {
    "extendsidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_204 },
#else
    { 0, output_204, 0 },
#endif
    (insn_gen_fn) gen_extendsidi2,
    &operand_data[270],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2995 */
  {
    "*extendqisi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_205 },
#else
    { 0, output_205, 0 },
#endif
    0,
    &operand_data[272],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2995 */
  {
    "*extendqidi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_206 },
#else
    { 0, output_206, 0 },
#endif
    0,
    &operand_data[274],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2995 */
  {
    "*extendhisi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_207 },
#else
    { 0, output_207, 0 },
#endif
    0,
    &operand_data[276],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2995 */
  {
    "*extendhidi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_208 },
#else
    { 0, output_208, 0 },
#endif
    0,
    &operand_data[278],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "*extendqisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_209 },
#else
    { 0, output_209, 0 },
#endif
    0,
    &operand_data[242],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "*extendqidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_210 },
#else
    { 0, output_210, 0 },
#endif
    0,
    &operand_data[244],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "*extendhisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_211 },
#else
    { 0, output_211, 0 },
#endif
    0,
    &operand_data[246],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "*extendhidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_212 },
#else
    { 0, output_212, 0 },
#endif
    0,
    &operand_data[248],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3024 */
  {
    "*extendqisi2_seb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_213 },
#else
    { 0, output_213, 0 },
#endif
    0,
    &operand_data[242],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3024 */
  {
    "*extendqidi2_seb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_214 },
#else
    { 0, output_214, 0 },
#endif
    0,
    &operand_data[244],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3024 */
  {
    "*extendhisi2_seh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_215 },
#else
    { 0, output_215, 0 },
#endif
    0,
    &operand_data[246],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3024 */
  {
    "*extendhidi2_seh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_216 },
#else
    { 0, output_216, 0 },
#endif
    0,
    &operand_data[248],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3040 */
  {
    "*extendqihi2_mips16e",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_217 },
#else
    { 0, output_217, 0 },
#endif
    0,
    &operand_data[280],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3050 */
  {
    "*extendqihi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_218 },
#else
    { 0, output_218, 0 },
#endif
    0,
    &operand_data[266],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3070 */
  {
    "*extendqihi2_seb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_219 },
#else
    { 0, output_219, 0 },
#endif
    0,
    &operand_data[266],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3084 */
  {
    "*extenddi_truncateqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3084 */
  {
    "*extenddi_truncatehi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3104 */
  {
    "*extendsi_truncateqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3104 */
  {
    "*extendsi_truncatehi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3124 */
  {
    "*extendhi_truncateqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3143 */
  {
    "*extendsi_truncateqi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_225 },
#else
    { 0, 0, output_225 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3143 */
  {
    "*extenddi_truncateqi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_226 },
#else
    { 0, 0, output_226 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3143 */
  {
    "*extendsi_truncatehi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_227 },
#else
    { 0, 0, output_227 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3143 */
  {
    "*extenddi_truncatehi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_228 },
#else
    { 0, 0, output_228 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3155 */
  {
    "*extendhi_truncateqi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,0,7",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[234],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3164 */
  {
    "extendsfdf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.d.s\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_extendsfdf2,
    &operand_data[282],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3192 */
  {
    "fix_truncdfsi2_insn",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "trunc.w.d %0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_fix_truncdfsi2_insn,
    &operand_data[284],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3201 */
  {
    "fix_truncdfsi2_macro",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_232 },
#else
    { 0, 0, output_232 },
#endif
    (insn_gen_fn) gen_fix_truncdfsi2_macro,
    &operand_data[284],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3229 */
  {
    "fix_truncsfsi2_insn",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "trunc.w.s %0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_fix_truncsfsi2_insn,
    &operand_data[287],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3238 */
  {
    "fix_truncsfsi2_macro",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_234 },
#else
    { 0, 0, output_234 },
#endif
    (insn_gen_fn) gen_fix_truncsfsi2_macro,
    &operand_data[287],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3255 */
  {
    "fix_truncdfdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "trunc.l.d %0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_fix_truncdfdi2,
    &operand_data[290],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3265 */
  {
    "fix_truncsfdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "trunc.l.s %0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_fix_truncsfdi2,
    &operand_data[292],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3275 */
  {
    "floatsidf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.d.w\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_floatsidf2,
    &operand_data[294],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3285 */
  {
    "floatdidf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.d.l\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_floatdidf2,
    &operand_data[296],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3295 */
  {
    "floatsisf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.s.w\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_floatsisf2,
    &operand_data[298],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3305 */
  {
    "floatdisf2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.s.l\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_floatdisf2,
    &operand_data[300],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3524 */
  {
    "extvsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%3,%m2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_extvsi,
    &operand_data[302],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3524 */
  {
    "extvdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%3,%m2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_extvdi,
    &operand_data[306],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3561 */
  {
    "extzvsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ext\t%0,%1,%3,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_extzvsi,
    &operand_data[302],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3561 */
  {
    "extzvdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dext\t%0,%1,%3,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_extzvdi,
    &operand_data[306],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3572 */
  {
    "*extzv_truncsi_exts",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "exts\t%0,%1,%3,31",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[310],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3610 */
  {
    "insvsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ins\t%0,%z3,%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_insvsi,
    &operand_data[314],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3610 */
  {
    "insvdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dins\t%0,%z3,%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_insvdi,
    &operand_data[318],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3627 */
  {
    "*cinssi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_248 },
#else
    { 0, 0, output_248 },
#endif
    0,
    &operand_data[322],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3627 */
  {
    "*cinsdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_249 },
#else
    { 0, 0, output_249 },
#endif
    0,
    &operand_data[326],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3655 */
  {
    "mov_lwl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwl\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_lwl,
    &operand_data[330],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3655 */
  {
    "mov_ldl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ldl\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_ldl,
    &operand_data[333],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3665 */
  {
    "mov_lwr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwr\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_lwr,
    &operand_data[336],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3665 */
  {
    "mov_ldr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ldr\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_ldr,
    &operand_data[340],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3676 */
  {
    "mov_swl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "swl\t%z1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_swl,
    &operand_data[344],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3676 */
  {
    "mov_sdl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sdl\t%z1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_sdl,
    &operand_data[347],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3686 */
  {
    "mov_swr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "swr\t%z1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_swr,
    &operand_data[350],
    3,
    1,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3686 */
  {
    "mov_sdr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sdr\t%z1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mov_sdr,
    &operand_data[353],
    3,
    1,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3712 */
  {
    "*lea_high64",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[356],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3765 */
  {
    "*lea64",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[356],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3802 */
  {
    "*xgot_hisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[359],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3802 */
  {
    "*xgot_hidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[361],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3817 */
  {
    "*xgot_losi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[363],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3817 */
  {
    "*xgot_lodi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[366],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3832 */
  {
    "*got_dispsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[359],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3832 */
  {
    "*got_dispdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[361],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3845 */
  {
    "*got_pagesi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[369],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3845 */
  {
    "*got_pagedi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[371],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3865 */
  {
    "load_gotsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lw\t%0,%R2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_load_gotsi,
    &operand_data[373],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3865 */
  {
    "load_gotdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ld\t%0,%R2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_load_gotdi,
    &operand_data[376],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3879 */
  {
    "*lowsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addiu\t%0,%1,%R2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[373],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3879 */
  {
    "*lowdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "daddiu\t%0,%1,%R2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[376],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3888 */
  {
    "*lowsi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addiu\t%0,%R2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[379],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3888 */
  {
    "*lowdi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "daddiu\t%0,%R2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[382],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3951 */
  {
    "*movsi_ra",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sw\t$31,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[385],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3951 */
  {
    "*movdi_ra",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sd\t$31,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[386],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3959 */
  {
    "*movdi_32bit",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_276 },
#else
    { 0, 0, output_276 },
#endif
    0,
    &operand_data[387],
    2,
    0,
    14,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3969 */
  {
    "*movdi_32bit_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_277 },
#else
    { 0, 0, output_277 },
#endif
    0,
    &operand_data[389],
    2,
    0,
    8,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3979 */
  {
    "*movdi_64bit",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_278 },
#else
    { 0, 0, output_278 },
#endif
    0,
    &operand_data[391],
    2,
    0,
    15,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3989 */
  {
    "*movdi_64bit_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_279 },
#else
    { 0, 0, output_279 },
#endif
    0,
    &operand_data[393],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movsi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_280 },
#else
    { 0, 0, output_280 },
#endif
    0,
    &operand_data[395],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv2hi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_281 },
#else
    { 0, 0, output_281 },
#endif
    0,
    &operand_data[397],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv4qi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_282 },
#else
    { 0, 0, output_282 },
#endif
    0,
    &operand_data[399],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv2hq_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_283 },
#else
    { 0, 0, output_283 },
#endif
    0,
    &operand_data[401],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv2uhq_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_284 },
#else
    { 0, 0, output_284 },
#endif
    0,
    &operand_data[403],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv2ha_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_285 },
#else
    { 0, 0, output_285 },
#endif
    0,
    &operand_data[405],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv2uha_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_286 },
#else
    { 0, 0, output_286 },
#endif
    0,
    &operand_data[407],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv4qq_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_287 },
#else
    { 0, 0, output_287 },
#endif
    0,
    &operand_data[409],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4057 */
  {
    "*movv4uqq_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_288 },
#else
    { 0, 0, output_288 },
#endif
    0,
    &operand_data[411],
    2,
    0,
    17,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movsi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_289 },
#else
    { 0, 0, output_289 },
#endif
    0,
    &operand_data[413],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv2hi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_290 },
#else
    { 0, 0, output_290 },
#endif
    0,
    &operand_data[415],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv4qi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_291 },
#else
    { 0, 0, output_291 },
#endif
    0,
    &operand_data[417],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv2hq_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_292 },
#else
    { 0, 0, output_292 },
#endif
    0,
    &operand_data[419],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv2uhq_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_293 },
#else
    { 0, 0, output_293 },
#endif
    0,
    &operand_data[421],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv2ha_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_294 },
#else
    { 0, 0, output_294 },
#endif
    0,
    &operand_data[423],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv2uha_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_295 },
#else
    { 0, 0, output_295 },
#endif
    0,
    &operand_data[425],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv4qq_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_296 },
#else
    { 0, 0, output_296 },
#endif
    0,
    &operand_data[427],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4067 */
  {
    "*movv4uqq_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_297 },
#else
    { 0, 0, output_297 },
#endif
    0,
    &operand_data[429],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4140 */
  {
    "movcc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_298 },
#else
    { 0, 0, output_298 },
#endif
    (insn_gen_fn) gen_movcc,
    &operand_data[431],
    2,
    0,
    9,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4195 */
  {
    "*lwxc1_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[433],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4195 */
  {
    "*ldxc1_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ldxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[436],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4195 */
  {
    "*ldxc1_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ldxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[439],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4195 */
  {
    "*lwxc1_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[442],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4195 */
  {
    "*ldxc1_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ldxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[445],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4195 */
  {
    "*ldxc1_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ldxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[448],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4204 */
  {
    "*swxc1_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "swxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[451],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4204 */
  {
    "*sdxc1_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sdxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[454],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4204 */
  {
    "*sdxc1_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sdxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[457],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4204 */
  {
    "*swxc1_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "swxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[460],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4204 */
  {
    "*sdxc1_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sdxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[463],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4204 */
  {
    "*sdxc1_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sdxc1\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[466],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[469],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[472],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[475],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[478],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[481],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[484],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[487],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[490],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[493],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[496],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[499],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[502],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[505],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[508],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[511],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4217 */
  {
    "*lwxs",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwxs\t%0,%1(%2)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[514],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4244 */
  {
    "*movhi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_329 },
#else
    { 0, 0, output_329 },
#endif
    0,
    &operand_data[517],
    2,
    0,
    6,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4254 */
  {
    "*movhi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_330 },
#else
    { 0, 0, output_330 },
#endif
    0,
    &operand_data[519],
    2,
    0,
    8,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4319 */
  {
    "*movqi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_331 },
#else
    { 0, 0, output_331 },
#endif
    0,
    &operand_data[521],
    2,
    0,
    6,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4329 */
  {
    "*movqi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_332 },
#else
    { 0, 0, output_332 },
#endif
    0,
    &operand_data[523],
    2,
    0,
    8,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4377 */
  {
    "*movsf_hardfloat",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_333 },
#else
    { 0, 0, output_333 },
#endif
    0,
    &operand_data[525],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4387 */
  {
    "*movsf_softfloat",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_334 },
#else
    { 0, 0, output_334 },
#endif
    0,
    &operand_data[527],
    2,
    0,
    3,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4397 */
  {
    "*movsf_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_335 },
#else
    { 0, 0, output_335 },
#endif
    0,
    &operand_data[529],
    2,
    0,
    5,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4418 */
  {
    "*movdf_hardfloat",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_336 },
#else
    { 0, 0, output_336 },
#endif
    0,
    &operand_data[531],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4428 */
  {
    "*movdf_softfloat",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_337 },
#else
    { 0, 0, output_337 },
#endif
    0,
    &operand_data[533],
    2,
    0,
    3,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4438 */
  {
    "*movdf_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_338 },
#else
    { 0, 0, output_338 },
#endif
    0,
    &operand_data[535],
    2,
    0,
    5,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4459 */
  {
    "*movti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[537],
    2,
    0,
    6,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4470 */
  {
    "*movti_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[539],
    2,
    0,
    8,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4493 */
  {
    "*movtf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[541],
    2,
    0,
    7,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4504 */
  {
    "*movtf_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[543],
    2,
    0,
    5,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4562 */
  {
    "*movv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_343 },
#else
    { 0, 0, output_343 },
#endif
    0,
    &operand_data[545],
    2,
    0,
    10,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4579 */
  {
    "mfhisi_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_344 },
#else
    { 0, 0, output_344 },
#endif
    (insn_gen_fn) gen_mfhisi_di,
    &operand_data[547],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4579 */
  {
    "mfhidi_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_345 },
#else
    { 0, 0, output_345 },
#endif
    (insn_gen_fn) gen_mfhidi_di,
    &operand_data[549],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4579 */
  {
    "mfhisi_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_346 },
#else
    { 0, 0, output_346 },
#endif
    (insn_gen_fn) gen_mfhisi_ti,
    &operand_data[551],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4579 */
  {
    "mfhidi_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_347 },
#else
    { 0, 0, output_347 },
#endif
    (insn_gen_fn) gen_mfhidi_ti,
    &operand_data[553],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4591 */
  {
    "mthisi_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthi\t%z1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthisi_di,
    &operand_data[555],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4591 */
  {
    "mthidi_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthi\t%z1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthidi_di,
    &operand_data[558],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4591 */
  {
    "mthisi_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthi\t%z1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthisi_ti,
    &operand_data[561],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4591 */
  {
    "mthidi_ti",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthi\t%z1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthidi_ti,
    &operand_data[564],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowdf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_352 },
#else
    { 0, 0, output_352 },
#endif
    (insn_gen_fn) gen_load_lowdf,
    &operand_data[567],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_353 },
#else
    { 0, 0, output_353 },
#endif
    (insn_gen_fn) gen_load_lowdi,
    &operand_data[569],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_354 },
#else
    { 0, 0, output_354 },
#endif
    (insn_gen_fn) gen_load_lowv2sf,
    &operand_data[571],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_355 },
#else
    { 0, 0, output_355 },
#endif
    (insn_gen_fn) gen_load_lowv2si,
    &operand_data[573],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_356 },
#else
    { 0, 0, output_356 },
#endif
    (insn_gen_fn) gen_load_lowv4hi,
    &operand_data[575],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_357 },
#else
    { 0, 0, output_357 },
#endif
    (insn_gen_fn) gen_load_lowv8qi,
    &operand_data[577],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4637 */
  {
    "load_lowtf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_358 },
#else
    { 0, 0, output_358 },
#endif
    (insn_gen_fn) gen_load_lowtf,
    &operand_data[579],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_highdf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_359 },
#else
    { 0, 0, output_359 },
#endif
    (insn_gen_fn) gen_load_highdf,
    &operand_data[581],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_highdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_360 },
#else
    { 0, 0, output_360 },
#endif
    (insn_gen_fn) gen_load_highdi,
    &operand_data[584],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_highv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_361 },
#else
    { 0, 0, output_361 },
#endif
    (insn_gen_fn) gen_load_highv2sf,
    &operand_data[587],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_highv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_362 },
#else
    { 0, 0, output_362 },
#endif
    (insn_gen_fn) gen_load_highv2si,
    &operand_data[590],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_highv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_363 },
#else
    { 0, 0, output_363 },
#endif
    (insn_gen_fn) gen_load_highv4hi,
    &operand_data[593],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_highv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_364 },
#else
    { 0, 0, output_364 },
#endif
    (insn_gen_fn) gen_load_highv8qi,
    &operand_data[596],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4651 */
  {
    "load_hightf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_365 },
#else
    { 0, 0, output_365 },
#endif
    (insn_gen_fn) gen_load_hightf,
    &operand_data[599],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_worddf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_366 },
#else
    { 0, 0, output_366 },
#endif
    (insn_gen_fn) gen_store_worddf,
    &operand_data[602],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_worddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_367 },
#else
    { 0, 0, output_367 },
#endif
    (insn_gen_fn) gen_store_worddi,
    &operand_data[605],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_wordv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_368 },
#else
    { 0, 0, output_368 },
#endif
    (insn_gen_fn) gen_store_wordv2sf,
    &operand_data[608],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_wordv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_369 },
#else
    { 0, 0, output_369 },
#endif
    (insn_gen_fn) gen_store_wordv2si,
    &operand_data[611],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_wordv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_370 },
#else
    { 0, 0, output_370 },
#endif
    (insn_gen_fn) gen_store_wordv4hi,
    &operand_data[614],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_wordv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_371 },
#else
    { 0, 0, output_371 },
#endif
    (insn_gen_fn) gen_store_wordv8qi,
    &operand_data[617],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4666 */
  {
    "store_wordtf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_372 },
#else
    { 0, 0, output_372 },
#endif
    (insn_gen_fn) gen_store_wordtf,
    &operand_data[620],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1df,
    &operand_data[623],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1di,
    &operand_data[626],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1v2sf,
    &operand_data[629],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1v2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1v2si,
    &operand_data[632],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1v4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1v4hi,
    &operand_data[635],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1v8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1v8qi,
    &operand_data[638],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4681 */
  {
    "mthc1tf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthc1\t%z1,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mthc1tf,
    &operand_data[641],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1df,
    &operand_data[644],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1di,
    &operand_data[646],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1v2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1v2sf,
    &operand_data[648],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1v2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1v2si,
    &operand_data[650],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1v4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1v4hi,
    &operand_data[652],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1v8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1v8qi,
    &operand_data[654],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4692 */
  {
    "mfhc1tf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mfhc1\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mfhc1tf,
    &operand_data[656],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4709 */
  {
    "loadgp_newabi_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_387 },
#else
    { 0, 0, output_387 },
#endif
    (insn_gen_fn) gen_loadgp_newabi_si,
    &operand_data[658],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4709 */
  {
    "loadgp_newabi_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_388 },
#else
    { 0, 0, output_388 },
#endif
    (insn_gen_fn) gen_loadgp_newabi_di,
    &operand_data[661],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4728 */
  {
    "loadgp_absolute_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_389 },
#else
    { 0, 0, output_389 },
#endif
    (insn_gen_fn) gen_loadgp_absolute_si,
    &operand_data[664],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4728 */
  {
    "loadgp_absolute_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_390 },
#else
    { 0, 0, output_390 },
#endif
    (insn_gen_fn) gen_loadgp_absolute_di,
    &operand_data[666],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4744 */
  {
    "loadgp_blockage",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loadgp_blockage,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4752 */
  {
    "loadgp_rtp_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_392 },
#else
    { 0, 0, output_392 },
#endif
    (insn_gen_fn) gen_loadgp_rtp_si,
    &operand_data[668],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4752 */
  {
    "loadgp_rtp_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_393 },
#else
    { 0, 0, output_393 },
#endif
    (insn_gen_fn) gen_loadgp_rtp_di,
    &operand_data[671],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4774 */
  {
    "copygp_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_394 },
#else
    { 0, 0, output_394 },
#endif
    (insn_gen_fn) gen_copygp_mips16,
    &operand_data[674],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4791 */
  {
    "potential_cprestore",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_395 },
#else
    { 0, 0, output_395 },
#endif
    (insn_gen_fn) gen_potential_cprestore,
    &operand_data[676],
    4,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4813 */
  {
    "cprestore",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_396 },
#else
    { 0, 0, output_396 },
#endif
    (insn_gen_fn) gen_cprestore,
    &operand_data[676],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4828 */
  {
    "use_cprestore",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_use_cprestore,
    &operand_data[680],
    1,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4860 */
  {
    "sync",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_398 },
#else
    { 0, 0, output_398 },
#endif
    (insn_gen_fn) gen_sync,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4865 */
  {
    "synci",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "synci\t0(%0)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_synci,
    &operand_data[681],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4871 */
  {
    "rdhwr_synci_step_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rdhwr\t%0,$1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_rdhwr_synci_step_si,
    &operand_data[34],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4871 */
  {
    "rdhwr_synci_step_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rdhwr\t%0,$1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_rdhwr_synci_step_di,
    &operand_data[40],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4878 */
  {
    "clear_hazard_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_402 },
#else
    { 0, 0, output_402 },
#endif
    (insn_gen_fn) gen_clear_hazard_si,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4878 */
  {
    "clear_hazard_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_403 },
#else
    { 0, 0, output_403 },
#endif
    (insn_gen_fn) gen_clear_hazard_di,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4892 */
  {
    "mips_cache",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cache\t%X0,%a1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cache,
    &operand_data[682],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4904 */
  {
    "r10k_cache_barrier",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cache\t0x14,0(%$)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_r10k_cache_barrier,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4967 */
  {
    "*ashlsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_406 },
#else
    { 0, 0, output_406 },
#endif
    0,
    &operand_data[684],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4967 */
  {
    "*ashrsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_407 },
#else
    { 0, 0, output_407 },
#endif
    0,
    &operand_data[684],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4967 */
  {
    "*lshrsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_408 },
#else
    { 0, 0, output_408 },
#endif
    0,
    &operand_data[684],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4967 */
  {
    "*ashldi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_409 },
#else
    { 0, 0, output_409 },
#endif
    0,
    &operand_data[687],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4967 */
  {
    "*ashrdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_410 },
#else
    { 0, 0, output_410 },
#endif
    0,
    &operand_data[687],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4967 */
  {
    "*lshrdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_411 },
#else
    { 0, 0, output_411 },
#endif
    0,
    &operand_data[687],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4982 */
  {
    "*ashlsi3_extend",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_412 },
#else
    { 0, 0, output_412 },
#endif
    0,
    &operand_data[690],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4982 */
  {
    "*ashrsi3_extend",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_413 },
#else
    { 0, 0, output_413 },
#endif
    0,
    &operand_data[690],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4982 */
  {
    "*lshrsi3_extend",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_414 },
#else
    { 0, 0, output_414 },
#endif
    0,
    &operand_data[690],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4997 */
  {
    "*ashlsi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_415 },
#else
    { 0, 0, output_415 },
#endif
    0,
    &operand_data[693],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4997 */
  {
    "*ashrsi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_416 },
#else
    { 0, 0, output_416 },
#endif
    0,
    &operand_data[693],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4997 */
  {
    "*lshrsi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_417 },
#else
    { 0, 0, output_417 },
#endif
    0,
    &operand_data[693],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5019 */
  {
    "*ashldi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_418 },
#else
    { 0, 0, output_418 },
#endif
    0,
    &operand_data[696],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5039 */
  {
    "*ashrdi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_419 },
#else
    { 0, 0, output_419 },
#endif
    0,
    &operand_data[699],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5058 */
  {
    "*lshrdi3_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_420 },
#else
    { 0, 0, output_420 },
#endif
    0,
    &operand_data[699],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5099 */
  {
    "*mips.md:5099",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[702],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5113 */
  {
    "rotrsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_422 },
#else
    { 0, 0, output_422 },
#endif
    (insn_gen_fn) gen_rotrsi3,
    &operand_data[684],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5113 */
  {
    "rotrdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_423 },
#else
    { 0, 0, output_423 },
#endif
    (insn_gen_fn) gen_rotrdi3,
    &operand_data[687],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5137 */
  {
    "*branch_fp",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_424 },
#else
    { 0, 0, output_424 },
#endif
    0,
    &operand_data[705],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5153 */
  {
    "*branch_fp_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_425 },
#else
    { 0, 0, output_425 },
#endif
    0,
    &operand_data[705],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5171 */
  {
    "*branch_ordersi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_426 },
#else
    { 0, 0, output_426 },
#endif
    0,
    &operand_data[708],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5171 */
  {
    "*branch_orderdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_427 },
#else
    { 0, 0, output_427 },
#endif
    0,
    &operand_data[711],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5183 */
  {
    "*branch_ordersi_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_428 },
#else
    { 0, 0, output_428 },
#endif
    0,
    &operand_data[708],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5183 */
  {
    "*branch_orderdi_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_429 },
#else
    { 0, 0, output_429 },
#endif
    0,
    &operand_data[711],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5197 */
  {
    "*branch_equalitysi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_430 },
#else
    { 0, 0, output_430 },
#endif
    0,
    &operand_data[714],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5197 */
  {
    "*branch_equalitydi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_431 },
#else
    { 0, 0, output_431 },
#endif
    0,
    &operand_data[718],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5213 */
  {
    "*branch_equalitysi_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_432 },
#else
    { 0, 0, output_432 },
#endif
    0,
    &operand_data[714],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5213 */
  {
    "*branch_equalitydi_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_433 },
#else
    { 0, 0, output_433 },
#endif
    0,
    &operand_data[718],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5231 */
  {
    "*branch_equalitysi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_434 },
#else
    { 0, 0, output_434 },
#endif
    0,
    &operand_data[722],
    4,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5231 */
  {
    "*branch_equalitydi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_435 },
#else
    { 0, 0, output_435 },
#endif
    0,
    &operand_data[726],
    4,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5293 */
  {
    "*branch_bit0si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_436 },
#else
    { 0, 0, output_436 },
#endif
    0,
    &operand_data[730],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5293 */
  {
    "*branch_bit1si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_437 },
#else
    { 0, 0, output_437 },
#endif
    0,
    &operand_data[730],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5293 */
  {
    "*branch_bit0di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_438 },
#else
    { 0, 0, output_438 },
#endif
    0,
    &operand_data[733],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5293 */
  {
    "*branch_bit1di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_439 },
#else
    { 0, 0, output_439 },
#endif
    0,
    &operand_data[733],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5313 */
  {
    "*branch_bit0si_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_440 },
#else
    { 0, 0, output_440 },
#endif
    0,
    &operand_data[730],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5313 */
  {
    "*branch_bit1si_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_441 },
#else
    { 0, 0, output_441 },
#endif
    0,
    &operand_data[730],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5313 */
  {
    "*branch_bit0di_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_442 },
#else
    { 0, 0, output_442 },
#endif
    0,
    &operand_data[733],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5313 */
  {
    "*branch_bit1di_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_443 },
#else
    { 0, 0, output_443 },
#endif
    0,
    &operand_data[733],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5353 */
  {
    "*seq_zero_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5353 */
  {
    "*seq_zero_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5353 */
  {
    "*seq_zero_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[43],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5353 */
  {
    "*seq_zero_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5362 */
  {
    "*seq_zero_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[736],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5362 */
  {
    "*seq_zero_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[738],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5362 */
  {
    "*seq_zero_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[740],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5362 */
  {
    "*seq_zero_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[742],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5372 */
  {
    "*seq_sisi_seq",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_452 },
#else
    { 0, output_452, 0 },
#endif
    0,
    &operand_data[744],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5372 */
  {
    "*seq_disi_seq",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_453 },
#else
    { 0, output_453, 0 },
#endif
    0,
    &operand_data[747],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5372 */
  {
    "*seq_sidi_seq",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_454 },
#else
    { 0, output_454, 0 },
#endif
    0,
    &operand_data[750],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5372 */
  {
    "*seq_didi_seq",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_455 },
#else
    { 0, output_455, 0 },
#endif
    0,
    &operand_data[753],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5384 */
  {
    "*sne_zero_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5384 */
  {
    "*sne_zero_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5384 */
  {
    "*sne_zero_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[43],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5384 */
  {
    "*sne_zero_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5394 */
  {
    "*sne_sisi_sne",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_460 },
#else
    { 0, output_460, 0 },
#endif
    0,
    &operand_data[744],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5394 */
  {
    "*sne_disi_sne",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_461 },
#else
    { 0, output_461, 0 },
#endif
    0,
    &operand_data[747],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5394 */
  {
    "*sne_sidi_sne",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_462 },
#else
    { 0, output_462, 0 },
#endif
    0,
    &operand_data[750],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5394 */
  {
    "*sne_didi_sne",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_463 },
#else
    { 0, output_463, 0 },
#endif
    0,
    &operand_data[753],
    3,
    0,
    3,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgt_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[756],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgtu_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[756],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgt_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[759],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgtu_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[759],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgt_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[762],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgtu_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[762],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgt_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[765],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5406 */
  {
    "*sgtu_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%z2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[765],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgt_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[768],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgtu_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[768],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgt_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[771],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgtu_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[771],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgt_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[774],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgtu_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[774],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgt_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[777],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5415 */
  {
    "*sgtu_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[777],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sge_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sgeu_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sge_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sgeu_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[37],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sge_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[43],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sgeu_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[43],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sge_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5424 */
  {
    "*sgeu_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%.,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[40],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*slt_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[684],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*sltu_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[684],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*slt_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[780],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*sltu_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[780],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*slt_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[690],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*sltu_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[690],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*slt_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[783],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5433 */
  {
    "*sltu_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[783],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*slt_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[786],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*sltu_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[786],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*slt_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[789],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*sltu_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[789],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*slt_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[792],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*sltu_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[792],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*slt_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "slt\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[795],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5442 */
  {
    "*sltu_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "sltu\t%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[795],
    3,
    0,
    2,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sle_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_504 },
#else
    { 0, 0, output_504 },
#endif
    0,
    &operand_data[798],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sleu_sisi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_505 },
#else
    { 0, 0, output_505 },
#endif
    0,
    &operand_data[798],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sle_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_506 },
#else
    { 0, 0, output_506 },
#endif
    0,
    &operand_data[801],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sleu_disi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_507 },
#else
    { 0, 0, output_507 },
#endif
    0,
    &operand_data[801],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sle_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_508 },
#else
    { 0, 0, output_508 },
#endif
    0,
    &operand_data[804],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sleu_sidi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_509 },
#else
    { 0, 0, output_509 },
#endif
    0,
    &operand_data[804],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sle_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_510 },
#else
    { 0, 0, output_510 },
#endif
    0,
    &operand_data[807],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5456 */
  {
    "*sleu_didi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_511 },
#else
    { 0, 0, output_511 },
#endif
    0,
    &operand_data[807],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sle_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_512 },
#else
    { 0, 0, output_512 },
#endif
    0,
    &operand_data[810],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sleu_sisi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_513 },
#else
    { 0, 0, output_513 },
#endif
    0,
    &operand_data[810],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sle_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_514 },
#else
    { 0, 0, output_514 },
#endif
    0,
    &operand_data[813],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sleu_disi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_515 },
#else
    { 0, 0, output_515 },
#endif
    0,
    &operand_data[813],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sle_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_516 },
#else
    { 0, 0, output_516 },
#endif
    0,
    &operand_data[816],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sleu_sidi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_517 },
#else
    { 0, 0, output_517 },
#endif
    0,
    &operand_data[816],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sle_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_518 },
#else
    { 0, 0, output_518 },
#endif
    0,
    &operand_data[819],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5468 */
  {
    "*sleu_didi_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_519 },
#else
    { 0, 0, output_519 },
#endif
    0,
    &operand_data[819],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sunordered_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.un.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunordered_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "suneq_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ueq.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_suneq_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sunlt_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ult.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunlt_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sunle_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ule.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunle_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "seq_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.eq.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_seq_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "slt_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.lt.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_slt_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sle_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.le.s\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sle_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sunordered_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.un.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunordered_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "suneq_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ueq.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_suneq_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sunlt_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ult.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunlt_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sunle_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ule.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunle_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "seq_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.eq.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_seq_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "slt_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.lt.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_slt_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5490 */
  {
    "sle_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.le.d\t%Z0%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sle_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sge_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.le.s\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sge_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sgt_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.lt.s\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sgt_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sunge_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ule.s\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunge_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sungt_sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ult.s\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sungt_sf,
    &operand_data[822],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sge_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.le.d\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sge_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sgt_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.lt.d\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sgt_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sunge_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ule.d\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunge_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5499 */
  {
    "sungt_df",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ult.d\t%Z0%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sungt_df,
    &operand_data[825],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5521 */
  {
    "*jump_absolute",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_542 },
#else
    { 0, 0, output_542 },
#endif
    0,
    &operand_data[705],
    1,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5528 */
  {
    "*jump_pic",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_543 },
#else
    { 0, 0, output_543 },
#endif
    0,
    &operand_data[705],
    1,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5546 */
  {
    "*jump_mips16",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "b\t%l0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[705],
    1,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5565 */
  {
    "indirect_jumpsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*j\t%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_indirect_jumpsi,
    &operand_data[35],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5565 */
  {
    "indirect_jumpdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*j\t%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_indirect_jumpdi,
    &operand_data[38],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5603 */
  {
    "tablejumpsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*j\t%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_tablejumpsi,
    &operand_data[710],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5603 */
  {
    "tablejumpdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*j\t%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_tablejumpdi,
    &operand_data[713],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5681 */
  {
    "blockage",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_blockage,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5712 */
  {
    "*return",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*j\t$31%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5721 */
  {
    "return_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*j\t%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_return_internal,
    &operand_data[828],
    1,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5730 */
  {
    "mips_eret",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "eret",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_eret,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5739 */
  {
    "mips_deret",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "deret",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_deret,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5748 */
  {
    "mips_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "di",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_di,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5756 */
  {
    "mips_ehb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ehb",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_ehb,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5764 */
  {
    "mips_rdpgpr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rdpgpr\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rdpgpr,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5774 */
  {
    "cop0_move",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_557 },
#else
    { 0, 0, output_557 },
#endif
    (insn_gen_fn) gen_cop0_move,
    &operand_data[829],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5800 */
  {
    "eh_set_lr_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_eh_set_lr_si,
    &operand_data[831],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5806 */
  {
    "eh_set_lr_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_eh_set_lr_di,
    &operand_data[833],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5846 */
  {
    "restore_gp",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_restore_gp,
    &operand_data[832],
    1,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5861 */
  {
    "move_gpsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_561 },
#else
    { 0, 0, output_561 },
#endif
    (insn_gen_fn) gen_move_gpsi,
    &operand_data[835],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5861 */
  {
    "move_gpdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_562 },
#else
    { 0, 0, output_562 },
#endif
    (insn_gen_fn) gen_move_gpdi,
    &operand_data[837],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5926 */
  {
    "load_callsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lw\t%0,%R2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_load_callsi,
    &operand_data[373],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5926 */
  {
    "load_calldi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "ld\t%0,%R2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_load_calldi,
    &operand_data[376],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5936 */
  {
    "set_got_version",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_set_got_version,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5943 */
  {
    "update_got_version",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_update_got_version,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5975 */
  {
    "sibcall_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_567 },
#else
    { 0, 0, output_567 },
#endif
    (insn_gen_fn) gen_sibcall_internal,
    &operand_data[839],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5994 */
  {
    "sibcall_value_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_568 },
#else
    { 0, 0, output_568 },
#endif
    (insn_gen_fn) gen_sibcall_value_internal,
    &operand_data[841],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6002 */
  {
    "sibcall_value_multiple_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_569 },
#else
    { 0, 0, output_569 },
#endif
    (insn_gen_fn) gen_sibcall_value_multiple_internal,
    &operand_data[841],
    4,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6060 */
  {
    "call_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_570 },
#else
    { 0, 0, output_570 },
#endif
    (insn_gen_fn) gen_call_internal,
    &operand_data[845],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6074 */
  {
    "call_split",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_571 },
#else
    { 0, 0, output_571 },
#endif
    (insn_gen_fn) gen_call_split,
    &operand_data[847],
    2,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6087 */
  {
    "call_internal_direct",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_572 },
#else
    { 0, 0, output_572 },
#endif
    (insn_gen_fn) gen_call_internal_direct,
    &operand_data[849],
    2,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6103 */
  {
    "call_direct_split",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_573 },
#else
    { 0, 0, output_573 },
#endif
    (insn_gen_fn) gen_call_direct_split,
    &operand_data[849],
    2,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6126 */
  {
    "call_value_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_574 },
#else
    { 0, 0, output_574 },
#endif
    (insn_gen_fn) gen_call_value_internal,
    &operand_data[844],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6143 */
  {
    "call_value_split",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_575 },
#else
    { 0, 0, output_575 },
#endif
    (insn_gen_fn) gen_call_value_split,
    &operand_data[851],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6154 */
  {
    "call_value_internal_direct",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_576 },
#else
    { 0, 0, output_576 },
#endif
    (insn_gen_fn) gen_call_value_internal_direct,
    &operand_data[854],
    3,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6172 */
  {
    "call_value_direct_split",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_577 },
#else
    { 0, 0, output_577 },
#endif
    (insn_gen_fn) gen_call_value_direct_split,
    &operand_data[854],
    3,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6184 */
  {
    "call_value_multiple_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_578 },
#else
    { 0, 0, output_578 },
#endif
    (insn_gen_fn) gen_call_value_multiple_internal,
    &operand_data[857],
    4,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6204 */
  {
    "call_value_multiple_split",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_579 },
#else
    { 0, 0, output_579 },
#endif
    (insn_gen_fn) gen_call_value_multiple_split,
    &operand_data[851],
    4,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6249 */
  {
    "prefetch",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_580 },
#else
    { 0, 0, output_580 },
#endif
    (insn_gen_fn) gen_prefetch,
    &operand_data[861],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6263 */
  {
    "*prefetch_indexed_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_581 },
#else
    { 0, 0, output_581 },
#endif
    0,
    &operand_data[864],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6263 */
  {
    "*prefetch_indexed_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_582 },
#else
    { 0, 0, output_582 },
#endif
    0,
    &operand_data[868],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6275 */
  {
    "nop",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%(nop%)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_nop,
    &operand_data[0],
    0,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6283 */
  {
    "hazard_nop",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_584 },
#else
    { 0, 0, output_584 },
#endif
    (insn_gen_fn) gen_hazard_nop,
    &operand_data[0],
    0,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6296 */
  {
    "*movsi_on_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_585 },
#else
    { 0, output_585, 0 },
#endif
    0,
    &operand_data[872],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6296 */
  {
    "*movdi_on_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_586 },
#else
    { 0, output_586, 0 },
#endif
    0,
    &operand_data[877],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6296 */
  {
    "*movsi_on_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_587 },
#else
    { 0, output_587, 0 },
#endif
    0,
    &operand_data[882],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6296 */
  {
    "*movdi_on_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_588 },
#else
    { 0, output_588, 0 },
#endif
    0,
    &operand_data[887],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6296 */
  {
    "*movsi_on_cc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_589 },
#else
    { 0, output_589, 0 },
#endif
    0,
    &operand_data[892],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6296 */
  {
    "*movdi_on_cc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_590 },
#else
    { 0, output_590, 0 },
#endif
    0,
    &operand_data[897],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6311 */
  {
    "*movsf_on_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_591 },
#else
    { 0, output_591, 0 },
#endif
    0,
    &operand_data[902],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6311 */
  {
    "*movsf_on_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_592 },
#else
    { 0, output_592, 0 },
#endif
    0,
    &operand_data[907],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6311 */
  {
    "*movsf_on_cc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_593 },
#else
    { 0, output_593, 0 },
#endif
    0,
    &operand_data[912],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6311 */
  {
    "*movdf_on_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_594 },
#else
    { 0, output_594, 0 },
#endif
    0,
    &operand_data[917],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6311 */
  {
    "*movdf_on_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_595 },
#else
    { 0, output_595, 0 },
#endif
    0,
    &operand_data[922],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6311 */
  {
    "*movdf_on_cc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_596 },
#else
    { 0, output_596, 0 },
#endif
    0,
    &operand_data[927],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6360 */
  {
    "consttable_int",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_597 },
#else
    { 0, 0, output_597 },
#endif
    (insn_gen_fn) gen_consttable_int,
    &operand_data[932],
    2,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6372 */
  {
    "consttable_float",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_598 },
#else
    { 0, 0, output_598 },
#endif
    (insn_gen_fn) gen_consttable_float,
    &operand_data[932],
    1,
    0,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6388 */
  {
    "align",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    ".align\t%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_align,
    &operand_data[304],
    1,
    0,
    0,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6408 */
  {
    "*mips16e_save_restore",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_600 },
#else
    { 0, 0, output_600 },
#endif
    0,
    &operand_data[934],
    3,
    1,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:51 */
  {
    "*memory_barrier",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_601 },
#else
    { 0, 0, output_601 },
#endif
    0,
    &operand_data[937],
    1,
    1,
    0,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:57 */
  {
    "sync_compare_and_swapsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_602 },
#else
    { 0, 0, output_602 },
#endif
    (insn_gen_fn) gen_sync_compare_and_swapsi,
    &operand_data[938],
    4,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:57 */
  {
    "sync_compare_and_swapdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_603 },
#else
    { 0, 0, output_603 },
#endif
    (insn_gen_fn) gen_sync_compare_and_swapdi,
    &operand_data[942],
    4,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:87 */
  {
    "compare_and_swap_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_604 },
#else
    { 0, 0, output_604 },
#endif
    (insn_gen_fn) gen_compare_and_swap_12,
    &operand_data[946],
    6,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:105 */
  {
    "sync_addsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_605 },
#else
    { 0, 0, output_605 },
#endif
    (insn_gen_fn) gen_sync_addsi,
    &operand_data[952],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:105 */
  {
    "sync_adddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_606 },
#else
    { 0, 0, output_606 },
#endif
    (insn_gen_fn) gen_sync_adddi,
    &operand_data[954],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:133 */
  {
    "sync_add_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_607 },
#else
    { 0, 0, output_607 },
#endif
    (insn_gen_fn) gen_sync_add_12,
    &operand_data[956],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:133 */
  {
    "sync_sub_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_608 },
#else
    { 0, 0, output_608 },
#endif
    (insn_gen_fn) gen_sync_sub_12,
    &operand_data[956],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:133 */
  {
    "sync_ior_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_609 },
#else
    { 0, 0, output_609 },
#endif
    (insn_gen_fn) gen_sync_ior_12,
    &operand_data[956],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:133 */
  {
    "sync_xor_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_610 },
#else
    { 0, 0, output_610 },
#endif
    (insn_gen_fn) gen_sync_xor_12,
    &operand_data[956],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:133 */
  {
    "sync_and_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_611 },
#else
    { 0, 0, output_611 },
#endif
    (insn_gen_fn) gen_sync_and_12,
    &operand_data[956],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:172 */
  {
    "sync_old_add_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_612 },
#else
    { 0, 0, output_612 },
#endif
    (insn_gen_fn) gen_sync_old_add_12,
    &operand_data[961],
    6,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:172 */
  {
    "sync_old_sub_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_613 },
#else
    { 0, 0, output_613 },
#endif
    (insn_gen_fn) gen_sync_old_sub_12,
    &operand_data[961],
    6,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:172 */
  {
    "sync_old_ior_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_614 },
#else
    { 0, 0, output_614 },
#endif
    (insn_gen_fn) gen_sync_old_ior_12,
    &operand_data[961],
    6,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:172 */
  {
    "sync_old_xor_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_615 },
#else
    { 0, 0, output_615 },
#endif
    (insn_gen_fn) gen_sync_old_xor_12,
    &operand_data[961],
    6,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:172 */
  {
    "sync_old_and_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_616 },
#else
    { 0, 0, output_616 },
#endif
    (insn_gen_fn) gen_sync_old_and_12,
    &operand_data[961],
    6,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:214 */
  {
    "sync_new_add_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_617 },
#else
    { 0, 0, output_617 },
#endif
    (insn_gen_fn) gen_sync_new_add_12,
    &operand_data[961],
    5,
    6,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:214 */
  {
    "sync_new_sub_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_618 },
#else
    { 0, 0, output_618 },
#endif
    (insn_gen_fn) gen_sync_new_sub_12,
    &operand_data[961],
    5,
    6,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:214 */
  {
    "sync_new_ior_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_619 },
#else
    { 0, 0, output_619 },
#endif
    (insn_gen_fn) gen_sync_new_ior_12,
    &operand_data[961],
    5,
    6,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:214 */
  {
    "sync_new_xor_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_620 },
#else
    { 0, 0, output_620 },
#endif
    (insn_gen_fn) gen_sync_new_xor_12,
    &operand_data[961],
    5,
    6,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:214 */
  {
    "sync_new_and_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_621 },
#else
    { 0, 0, output_621 },
#endif
    (insn_gen_fn) gen_sync_new_and_12,
    &operand_data[961],
    5,
    6,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:256 */
  {
    "sync_nand_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_622 },
#else
    { 0, 0, output_622 },
#endif
    (insn_gen_fn) gen_sync_nand_12,
    &operand_data[956],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:294 */
  {
    "sync_old_nand_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_623 },
#else
    { 0, 0, output_623 },
#endif
    (insn_gen_fn) gen_sync_old_nand_12,
    &operand_data[961],
    6,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:334 */
  {
    "sync_new_nand_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_624 },
#else
    { 0, 0, output_624 },
#endif
    (insn_gen_fn) gen_sync_new_nand_12,
    &operand_data[961],
    5,
    5,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:359 */
  {
    "sync_subsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_625 },
#else
    { 0, 0, output_625 },
#endif
    (insn_gen_fn) gen_sync_subsi,
    &operand_data[956],
    2,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:359 */
  {
    "sync_subdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_626 },
#else
    { 0, 0, output_626 },
#endif
    (insn_gen_fn) gen_sync_subdi,
    &operand_data[967],
    2,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:371 */
  {
    "sync_old_addsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_627 },
#else
    { 0, 0, output_627 },
#endif
    (insn_gen_fn) gen_sync_old_addsi,
    &operand_data[969],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:371 */
  {
    "sync_old_adddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_628 },
#else
    { 0, 0, output_628 },
#endif
    (insn_gen_fn) gen_sync_old_adddi,
    &operand_data[972],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:386 */
  {
    "sync_old_subsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_629 },
#else
    { 0, 0, output_629 },
#endif
    (insn_gen_fn) gen_sync_old_subsi,
    &operand_data[961],
    3,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:386 */
  {
    "sync_old_subdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_630 },
#else
    { 0, 0, output_630 },
#endif
    (insn_gen_fn) gen_sync_old_subdi,
    &operand_data[975],
    3,
    2,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:401 */
  {
    "sync_new_addsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_631 },
#else
    { 0, 0, output_631 },
#endif
    (insn_gen_fn) gen_sync_new_addsi,
    &operand_data[969],
    3,
    3,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:401 */
  {
    "sync_new_adddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_632 },
#else
    { 0, 0, output_632 },
#endif
    (insn_gen_fn) gen_sync_new_adddi,
    &operand_data[972],
    3,
    3,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:417 */
  {
    "sync_new_subsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_633 },
#else
    { 0, 0, output_633 },
#endif
    (insn_gen_fn) gen_sync_new_subsi,
    &operand_data[961],
    3,
    3,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:417 */
  {
    "sync_new_subdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_634 },
#else
    { 0, 0, output_634 },
#endif
    (insn_gen_fn) gen_sync_new_subdi,
    &operand_data[975],
    3,
    3,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:433 */
  {
    "sync_iorsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_635 },
#else
    { 0, 0, output_635 },
#endif
    (insn_gen_fn) gen_sync_iorsi,
    &operand_data[978],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:433 */
  {
    "sync_xorsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_636 },
#else
    { 0, 0, output_636 },
#endif
    (insn_gen_fn) gen_sync_xorsi,
    &operand_data[978],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:433 */
  {
    "sync_andsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_637 },
#else
    { 0, 0, output_637 },
#endif
    (insn_gen_fn) gen_sync_andsi,
    &operand_data[978],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:433 */
  {
    "sync_iordi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_638 },
#else
    { 0, 0, output_638 },
#endif
    (insn_gen_fn) gen_sync_iordi,
    &operand_data[980],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:433 */
  {
    "sync_xordi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_639 },
#else
    { 0, 0, output_639 },
#endif
    (insn_gen_fn) gen_sync_xordi,
    &operand_data[980],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:433 */
  {
    "sync_anddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_640 },
#else
    { 0, 0, output_640 },
#endif
    (insn_gen_fn) gen_sync_anddi,
    &operand_data[980],
    2,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:445 */
  {
    "sync_old_iorsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_641 },
#else
    { 0, 0, output_641 },
#endif
    (insn_gen_fn) gen_sync_old_iorsi,
    &operand_data[982],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:445 */
  {
    "sync_old_xorsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_642 },
#else
    { 0, 0, output_642 },
#endif
    (insn_gen_fn) gen_sync_old_xorsi,
    &operand_data[982],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:445 */
  {
    "sync_old_andsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_643 },
#else
    { 0, 0, output_643 },
#endif
    (insn_gen_fn) gen_sync_old_andsi,
    &operand_data[982],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:445 */
  {
    "sync_old_iordi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_644 },
#else
    { 0, 0, output_644 },
#endif
    (insn_gen_fn) gen_sync_old_iordi,
    &operand_data[985],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:445 */
  {
    "sync_old_xordi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_645 },
#else
    { 0, 0, output_645 },
#endif
    (insn_gen_fn) gen_sync_old_xordi,
    &operand_data[985],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:445 */
  {
    "sync_old_anddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_646 },
#else
    { 0, 0, output_646 },
#endif
    (insn_gen_fn) gen_sync_old_anddi,
    &operand_data[985],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:460 */
  {
    "sync_new_iorsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_647 },
#else
    { 0, 0, output_647 },
#endif
    (insn_gen_fn) gen_sync_new_iorsi,
    &operand_data[982],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:460 */
  {
    "sync_new_xorsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_648 },
#else
    { 0, 0, output_648 },
#endif
    (insn_gen_fn) gen_sync_new_xorsi,
    &operand_data[982],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:460 */
  {
    "sync_new_andsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_649 },
#else
    { 0, 0, output_649 },
#endif
    (insn_gen_fn) gen_sync_new_andsi,
    &operand_data[982],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:460 */
  {
    "sync_new_iordi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_650 },
#else
    { 0, 0, output_650 },
#endif
    (insn_gen_fn) gen_sync_new_iordi,
    &operand_data[985],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:460 */
  {
    "sync_new_xordi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_651 },
#else
    { 0, 0, output_651 },
#endif
    (insn_gen_fn) gen_sync_new_xordi,
    &operand_data[985],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:460 */
  {
    "sync_new_anddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_652 },
#else
    { 0, 0, output_652 },
#endif
    (insn_gen_fn) gen_sync_new_anddi,
    &operand_data[985],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:476 */
  {
    "sync_nandsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_653 },
#else
    { 0, 0, output_653 },
#endif
    (insn_gen_fn) gen_sync_nandsi,
    &operand_data[978],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:476 */
  {
    "sync_nanddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_654 },
#else
    { 0, 0, output_654 },
#endif
    (insn_gen_fn) gen_sync_nanddi,
    &operand_data[980],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:487 */
  {
    "sync_old_nandsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_655 },
#else
    { 0, 0, output_655 },
#endif
    (insn_gen_fn) gen_sync_old_nandsi,
    &operand_data[982],
    3,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:487 */
  {
    "sync_old_nanddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_656 },
#else
    { 0, 0, output_656 },
#endif
    (insn_gen_fn) gen_sync_old_nanddi,
    &operand_data[985],
    3,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:501 */
  {
    "sync_new_nandsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_657 },
#else
    { 0, 0, output_657 },
#endif
    (insn_gen_fn) gen_sync_new_nandsi,
    &operand_data[982],
    3,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:501 */
  {
    "sync_new_nanddi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_658 },
#else
    { 0, 0, output_658 },
#endif
    (insn_gen_fn) gen_sync_new_nanddi,
    &operand_data[985],
    3,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:516 */
  {
    "sync_lock_test_and_setsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_659 },
#else
    { 0, 0, output_659 },
#endif
    (insn_gen_fn) gen_sync_lock_test_and_setsi,
    &operand_data[969],
    3,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:516 */
  {
    "sync_lock_test_and_setdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_660 },
#else
    { 0, 0, output_660 },
#endif
    (insn_gen_fn) gen_sync_lock_test_and_setdi,
    &operand_data[972],
    3,
    1,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:543 */
  {
    "test_and_set_12",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_661 },
#else
    { 0, 0, output_661 },
#endif
    (insn_gen_fn) gen_test_and_set_12,
    &operand_data[988],
    5,
    1,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:44 */
  {
    "*movcc_v2sf_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_662 },
#else
    { 0, output_662, 0 },
#endif
    0,
    &operand_data[993],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:44 */
  {
    "*movcc_v2sf_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_663 },
#else
    { 0, output_663, 0 },
#endif
    0,
    &operand_data[998],
    5,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:59 */
  {
    "mips_cond_move_tf_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_664 },
#else
    { 0, output_664, 0 },
#endif
    (insn_gen_fn) gen_mips_cond_move_tf_ps,
    &operand_data[1003],
    4,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:93 */
  {
    "mips_pul_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pul.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_pul_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:105 */
  {
    "mips_puu_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "puu.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_puu_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:119 */
  {
    "mips_pll_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pll.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_pll_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:133 */
  {
    "mips_plu_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "plu.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_plu_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:160 */
  {
    "vec_initv2sf_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_669 },
#else
    { 0, 0, output_669 },
#endif
    (insn_gen_fn) gen_vec_initv2sf_internal,
    &operand_data[1007],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:179 */
  {
    "vec_extractv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_670 },
#else
    { 0, 0, output_670 },
#endif
    (insn_gen_fn) gen_vec_extractv2sf,
    &operand_data[1010],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:249 */
  {
    "mips_alnv_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "alnv.ps\t%0,%1,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_alnv_ps,
    &operand_data[1013],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:261 */
  {
    "mips_addr_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addr.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addr_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:272 */
  {
    "mips_cvt_pw_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.pw.ps\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cvt_pw_ps,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:282 */
  {
    "mips_cvt_ps_pw",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cvt.ps.pw\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cvt_ps_pw,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:292 */
  {
    "mips_mulr_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulr.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulr_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:318 */
  {
    "*mips_abs_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "abs.ps\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    0,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:331 */
  {
    "mips_cabs_cond_s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cabs.%Y3.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cabs_cond_s,
    &operand_data[1017],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:331 */
  {
    "mips_cabs_cond_d",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cabs.%Y3.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cabs_cond_d,
    &operand_data[1021],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:347 */
  {
    "mips_c_cond_4s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_c_cond_4s,
    &operand_data[1025],
    6,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:376 */
  {
    "mips_cabs_cond_4s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "#",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cabs_cond_4s,
    &operand_data[1025],
    6,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:410 */
  {
    "mips_c_cond_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.%Y3.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_c_cond_ps,
    &operand_data[1031],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:421 */
  {
    "mips_cabs_cond_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cabs.%Y3.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cabs_cond_ps,
    &operand_data[1031],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "sunordered_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.un.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunordered_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "suneq_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ueq.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_suneq_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "sunlt_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ult.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunlt_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "sunle_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ule.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunle_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "seq_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.eq.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_seq_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "slt_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.lt.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_slt_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:437 */
  {
    "sle_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.le.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sle_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:448 */
  {
    "sge_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.le.ps\t%0,%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sge_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:448 */
  {
    "sgt_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.lt.ps\t%0,%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sgt_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:448 */
  {
    "sunge_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ule.ps\t%0,%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sunge_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:448 */
  {
    "sungt_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "c.ult.ps\t%0,%2,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sungt_ps,
    &operand_data[1031],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:464 */
  {
    "bc1any4t",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*bc1any4t\t%1,%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_bc1any4t,
    &operand_data[1035],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:475 */
  {
    "bc1any4f",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*bc1any4f\t%1,%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_bc1any4f,
    &operand_data[1035],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:486 */
  {
    "bc1any2t",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*bc1any2t\t%1,%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_bc1any2t,
    &operand_data[1037],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:497 */
  {
    "bc1any2f",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*bc1any2f\t%1,%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_bc1any2f,
    &operand_data[1037],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:517 */
  {
    "*branch_upper_lower",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_698 },
#else
    { 0, 0, output_698 },
#endif
    0,
    &operand_data[1039],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:538 */
  {
    "*branch_upper_lower_inverted",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_699 },
#else
    { 0, 0, output_699 },
#endif
    0,
    &operand_data[1039],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:562 */
  {
    "mips_rsqrt1_s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rsqrt1.s\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rsqrt1_s,
    &operand_data[7],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:562 */
  {
    "mips_rsqrt1_d",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rsqrt1.d\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rsqrt1_d,
    &operand_data[10],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:562 */
  {
    "mips_rsqrt1_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rsqrt1.ps\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rsqrt1_ps,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:571 */
  {
    "mips_rsqrt2_s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rsqrt2.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rsqrt2_s,
    &operand_data[7],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:571 */
  {
    "mips_rsqrt2_d",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rsqrt2.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rsqrt2_d,
    &operand_data[10],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:571 */
  {
    "mips_rsqrt2_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rsqrt2.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rsqrt2_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:581 */
  {
    "mips_recip1_s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "recip1.s\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_recip1_s,
    &operand_data[7],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:581 */
  {
    "mips_recip1_d",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "recip1.d\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_recip1_d,
    &operand_data[10],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:581 */
  {
    "mips_recip1_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "recip1.ps\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_recip1_ps,
    &operand_data[13],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:590 */
  {
    "mips_recip2_s",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "recip2.s\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_recip2_s,
    &operand_data[7],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:590 */
  {
    "mips_recip2_d",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "recip2.d\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_recip2_d,
    &operand_data[10],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:590 */
  {
    "mips_recip2_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "recip2.ps\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_recip2_ps,
    &operand_data[13],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:128 */
  {
    "addv2hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addv2hi3,
    &operand_data[1043],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:128 */
  {
    "addv4qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addv4qi3,
    &operand_data[1046],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:140 */
  {
    "mips_addq_s_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addq_s_w,
    &operand_data[34],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:140 */
  {
    "mips_addq_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addq_s_ph,
    &operand_data[1043],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:140 */
  {
    "mips_addu_s_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addu_s_qb,
    &operand_data[1046],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:154 */
  {
    "subv2hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subv2hi3,
    &operand_data[1043],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:154 */
  {
    "subv4qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subv4qi3,
    &operand_data[1046],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:166 */
  {
    "mips_subq_s_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subq_s_w,
    &operand_data[34],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:166 */
  {
    "mips_subq_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subq_s_ph,
    &operand_data[1043],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:166 */
  {
    "mips_subu_s_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subu_s_qb,
    &operand_data[1046],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:180 */
  {
    "mips_addsc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addsc\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addsc,
    &operand_data[34],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:194 */
  {
    "mips_addwc",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addwc\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addwc,
    &operand_data[34],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:209 */
  {
    "mips_modsub",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "modsub\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_modsub,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:220 */
  {
    "mips_raddu_w_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "raddu.w.qb\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_raddu_w_qb,
    &operand_data[1049],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:230 */
  {
    "mips_absq_s_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "absq_s.w\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_absq_s_w,
    &operand_data[34],
    2,
    1,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:230 */
  {
    "mips_absq_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "absq_s.ph\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_absq_s_ph,
    &operand_data[1043],
    2,
    1,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:243 */
  {
    "mips_precrq_qb_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precrq.qb.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precrq_qb_ph,
    &operand_data[1051],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:253 */
  {
    "mips_precrq_ph_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precrq.ph.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precrq_ph_w,
    &operand_data[469],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:263 */
  {
    "mips_precrq_rs_ph_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precrq_rs.ph.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precrq_rs_ph_w,
    &operand_data[469],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:278 */
  {
    "mips_precrqu_s_qb_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precrqu_s.qb.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precrqu_s_qb_ph,
    &operand_data[1051],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:293 */
  {
    "mips_preceq_w_phl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "preceq.w.phl\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_preceq_w_phl,
    &operand_data[1054],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:302 */
  {
    "mips_preceq_w_phr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "preceq.w.phr\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_preceq_w_phr,
    &operand_data[1054],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:312 */
  {
    "mips_precequ_ph_qbl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precequ.ph.qbl\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precequ_ph_qbl,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:321 */
  {
    "mips_precequ_ph_qbr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precequ.ph.qbr\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precequ_ph_qbr,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:330 */
  {
    "mips_precequ_ph_qbla",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precequ.ph.qbla\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precequ_ph_qbla,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:339 */
  {
    "mips_precequ_ph_qbra",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precequ.ph.qbra\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precequ_ph_qbra,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:349 */
  {
    "mips_preceu_ph_qbl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "preceu.ph.qbl\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_preceu_ph_qbl,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:358 */
  {
    "mips_preceu_ph_qbr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "preceu.ph.qbr\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_preceu_ph_qbr,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:367 */
  {
    "mips_preceu_ph_qbla",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "preceu.ph.qbla\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_preceu_ph_qbla,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:376 */
  {
    "mips_preceu_ph_qbra",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "preceu.ph.qbra\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_preceu_ph_qbra,
    &operand_data[1056],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:387 */
  {
    "mips_shll_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_742 },
#else
    { 0, 0, output_742 },
#endif
    (insn_gen_fn) gen_mips_shll_ph,
    &operand_data[1058],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:387 */
  {
    "mips_shll_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_743 },
#else
    { 0, 0, output_743 },
#endif
    (insn_gen_fn) gen_mips_shll_qb,
    &operand_data[1061],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:409 */
  {
    "mips_shll_s_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_744 },
#else
    { 0, 0, output_744 },
#endif
    (insn_gen_fn) gen_mips_shll_s_w,
    &operand_data[1064],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:409 */
  {
    "mips_shll_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_745 },
#else
    { 0, 0, output_745 },
#endif
    (insn_gen_fn) gen_mips_shll_s_ph,
    &operand_data[1058],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:432 */
  {
    "mips_shrl_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_746 },
#else
    { 0, 0, output_746 },
#endif
    (insn_gen_fn) gen_mips_shrl_qb,
    &operand_data[1061],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:451 */
  {
    "mips_shra_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_747 },
#else
    { 0, 0, output_747 },
#endif
    (insn_gen_fn) gen_mips_shra_ph,
    &operand_data[1058],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:469 */
  {
    "mips_shra_r_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_748 },
#else
    { 0, 0, output_748 },
#endif
    (insn_gen_fn) gen_mips_shra_r_w,
    &operand_data[1064],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:469 */
  {
    "mips_shra_r_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_749 },
#else
    { 0, 0, output_749 },
#endif
    (insn_gen_fn) gen_mips_shra_r_ph,
    &operand_data[1058],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:490 */
  {
    "mips_muleu_s_ph_qbl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "muleu_s.ph.qbl\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_muleu_s_ph_qbl,
    &operand_data[1067],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:504 */
  {
    "mips_muleu_s_ph_qbr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "muleu_s.ph.qbr\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_muleu_s_ph_qbr,
    &operand_data[1067],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:519 */
  {
    "mips_mulq_rs_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_rs.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulq_rs_ph,
    &operand_data[1071],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:534 */
  {
    "mips_muleq_s_w_phl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "muleq_s.w.phl\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_muleq_s_w_phl,
    &operand_data[1075],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:548 */
  {
    "mips_muleq_s_w_phr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "muleq_s.w.phr\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_muleq_s_w_phr,
    &operand_data[1075],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:563 */
  {
    "mips_dpau_h_qbl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpau.h.qbl\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpau_h_qbl,
    &operand_data[1079],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:574 */
  {
    "mips_dpau_h_qbr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpau.h.qbr\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpau_h_qbr,
    &operand_data[1079],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:586 */
  {
    "mips_dpsu_h_qbl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsu.h.qbl\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsu_h_qbl,
    &operand_data[1079],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:597 */
  {
    "mips_dpsu_h_qbr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsu.h.qbr\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsu_h_qbr,
    &operand_data[1079],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:609 */
  {
    "mips_dpaq_s_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpaq_s.w.ph\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpaq_s_w_ph,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:625 */
  {
    "mips_dpsq_s_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsq_s.w.ph\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsq_s_w_ph,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:641 */
  {
    "mips_mulsaq_s_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulsaq_s.w.ph\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulsaq_s_w_ph,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:657 */
  {
    "mips_dpaq_sa_l_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpaq_sa.l.w\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpaq_sa_l_w,
    &operand_data[1087],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:673 */
  {
    "mips_dpsq_sa_l_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsq_sa.l.w\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsq_sa_l_w,
    &operand_data[1087],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:689 */
  {
    "mips_maq_s_w_phl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "maq_s.w.phl\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_maq_s_w_phl,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:704 */
  {
    "mips_maq_s_w_phr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "maq_s.w.phr\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_maq_s_w_phr,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:720 */
  {
    "mips_maq_sa_w_phl",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "maq_sa.w.phl\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_maq_sa_w_phl,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:735 */
  {
    "mips_maq_sa_w_phr",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "maq_sa.w.phr\t%q0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_maq_sa_w_phr,
    &operand_data[1083],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:752 */
  {
    "mips_bitrev",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "bitrev\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_bitrev,
    &operand_data[34],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:762 */
  {
    "mips_insv",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "insv\t%0,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_insv,
    &operand_data[1091],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:775 */
  {
    "mips_repl_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_770 },
#else
    { 0, 0, output_770 },
#endif
    (insn_gen_fn) gen_mips_repl_qb,
    &operand_data[1094],
    2,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:792 */
  {
    "mips_repl_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .multi = output_771 },
#else
    { 0, output_771, 0 },
#endif
    (insn_gen_fn) gen_mips_repl_ph,
    &operand_data[1096],
    2,
    0,
    2,
    2
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:805 */
  {
    "mips_cmp_eq_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmp.eq.ph\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmp_eq_ph,
    &operand_data[1044],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:805 */
  {
    "mips_cmpu_eq_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpu.eq.qb\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpu_eq_qb,
    &operand_data[1047],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:816 */
  {
    "mips_cmp_lt_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmp.lt.ph\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmp_lt_ph,
    &operand_data[1044],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:816 */
  {
    "mips_cmpu_lt_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpu.lt.qb\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpu_lt_qb,
    &operand_data[1047],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:827 */
  {
    "mips_cmp_le_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmp.le.ph\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmp_le_ph,
    &operand_data[1044],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:827 */
  {
    "mips_cmpu_le_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpu.le.qb\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpu_le_qb,
    &operand_data[1047],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:838 */
  {
    "mips_cmpgu_eq_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpgu.eq.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpgu_eq_qb,
    &operand_data[1098],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:848 */
  {
    "mips_cmpgu_lt_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpgu.lt.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpgu_lt_qb,
    &operand_data[1098],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:858 */
  {
    "mips_cmpgu_le_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpgu.le.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpgu_le_qb,
    &operand_data[1098],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:869 */
  {
    "mips_pick_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pick.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_pick_ph,
    &operand_data[1043],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:869 */
  {
    "mips_pick_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pick.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_pick_qb,
    &operand_data[1046],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:881 */
  {
    "mips_packrl_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "packrl.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_packrl_ph,
    &operand_data[1043],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:893 */
  {
    "mips_extr_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_784 },
#else
    { 0, 0, output_784 },
#endif
    (insn_gen_fn) gen_mips_extr_w,
    &operand_data[1101],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:914 */
  {
    "mips_extr_r_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_785 },
#else
    { 0, 0, output_785 },
#endif
    (insn_gen_fn) gen_mips_extr_r_w,
    &operand_data[1101],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:935 */
  {
    "mips_extr_rs_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_786 },
#else
    { 0, 0, output_786 },
#endif
    (insn_gen_fn) gen_mips_extr_rs_w,
    &operand_data[1101],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:957 */
  {
    "mips_extr_s_h",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_787 },
#else
    { 0, 0, output_787 },
#endif
    (insn_gen_fn) gen_mips_extr_s_h,
    &operand_data[1101],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:979 */
  {
    "mips_extp",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_788 },
#else
    { 0, 0, output_788 },
#endif
    (insn_gen_fn) gen_mips_extp,
    &operand_data[1101],
    3,
    2,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1001 */
  {
    "mips_extpdp",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_789 },
#else
    { 0, 0, output_789 },
#endif
    (insn_gen_fn) gen_mips_extpdp,
    &operand_data[1101],
    3,
    4,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1027 */
  {
    "mips_shilo",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_790 },
#else
    { 0, 0, output_790 },
#endif
    (insn_gen_fn) gen_mips_shilo,
    &operand_data[1104],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1046 */
  {
    "mips_mthlip",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mthlip\t%2,%q0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mthlip,
    &operand_data[1087],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1062 */
  {
    "mips_wrdsp",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "wrdsp\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_wrdsp,
    &operand_data[1107],
    2,
    10,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1084 */
  {
    "mips_rddsp",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "rddsp\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_rddsp,
    &operand_data[1109],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1115 */
  {
    "mips_lbux_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lbux\t%0,%2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_lbux_si,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1115 */
  {
    "mips_lbux_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lbux\t%0,%2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_lbux_di,
    &operand_data[37],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1139 */
  {
    "mips_lhx_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lhx\t%0,%2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_lhx_si,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1139 */
  {
    "mips_lhx_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lhx\t%0,%2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_lhx_di,
    &operand_data[37],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1163 */
  {
    "mips_lwx_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwx\t%0,%2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_lwx_si,
    &operand_data[34],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1163 */
  {
    "mips_lwx_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "lwx\t%0,%2(%1)",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_lwx_di,
    &operand_data[37],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1174 */
  {
    "mips_bposge",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "%*bposge%1\t%0%/",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_bposge,
    &operand_data[1111],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:73 */
  {
    "mips_absq_s_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "absq_s.qb\t%0,%z1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_absq_s_qb,
    &operand_data[1113],
    2,
    1,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:85 */
  {
    "mips_addu_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addu_ph,
    &operand_data[1115],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:97 */
  {
    "mips_addu_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addu_s_ph,
    &operand_data[1115],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:110 */
  {
    "mips_adduh_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "adduh.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_adduh_qb,
    &operand_data[1118],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:120 */
  {
    "mips_adduh_r_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "adduh_r.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_adduh_r_qb,
    &operand_data[1118],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:130 */
  {
    "mips_append",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_806 },
#else
    { 0, 0, output_806 },
#endif
    (insn_gen_fn) gen_mips_append,
    &operand_data[1121],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:145 */
  {
    "mips_balign",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_807 },
#else
    { 0, 0, output_807 },
#endif
    (insn_gen_fn) gen_mips_balign,
    &operand_data[1121],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:160 */
  {
    "mips_cmpgdu_eq_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpgdu.eq.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpgdu_eq_qb,
    &operand_data[1125],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:175 */
  {
    "mips_cmpgdu_lt_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpgdu.lt.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpgdu_lt_qb,
    &operand_data[1125],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:190 */
  {
    "mips_cmpgdu_le_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "cmpgdu.le.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_cmpgdu_le_qb,
    &operand_data[1125],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:205 */
  {
    "mips_dpa_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpa.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpa_w_ph,
    &operand_data[1128],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:216 */
  {
    "mips_dps_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dps.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dps_w_ph,
    &operand_data[1128],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:227 */
  {
    "mulv2hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulv2hi3,
    &operand_data[1071],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:240 */
  {
    "mips_mul_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mul_s.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mul_s_ph,
    &operand_data[1132],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:254 */
  {
    "mips_mulq_rs_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_rs.w\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulq_rs_w,
    &operand_data[1136],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:268 */
  {
    "mips_mulq_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_s.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulq_s_ph,
    &operand_data[1132],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:282 */
  {
    "mips_mulq_s_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_s.w\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulq_s_w,
    &operand_data[1136],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:296 */
  {
    "mips_mulsa_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulsa.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_mulsa_w_ph,
    &operand_data[1128],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:307 */
  {
    "mips_precr_qb_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "precr.qb.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_precr_qb_ph,
    &operand_data[1140],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:317 */
  {
    "mips_precr_sra_ph_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_820 },
#else
    { 0, 0, output_820 },
#endif
    (insn_gen_fn) gen_mips_precr_sra_ph_w,
    &operand_data[1143],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:332 */
  {
    "mips_precr_sra_r_ph_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_821 },
#else
    { 0, 0, output_821 },
#endif
    (insn_gen_fn) gen_mips_precr_sra_r_ph_w,
    &operand_data[1143],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:347 */
  {
    "mips_prepend",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_822 },
#else
    { 0, 0, output_822 },
#endif
    (insn_gen_fn) gen_mips_prepend,
    &operand_data[1121],
    4,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:362 */
  {
    "mips_shra_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_823 },
#else
    { 0, 0, output_823 },
#endif
    (insn_gen_fn) gen_mips_shra_qb,
    &operand_data[1147],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:381 */
  {
    "mips_shra_r_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_824 },
#else
    { 0, 0, output_824 },
#endif
    (insn_gen_fn) gen_mips_shra_r_qb,
    &operand_data[1147],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:399 */
  {
    "mips_shrl_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_825 },
#else
    { 0, 0, output_825 },
#endif
    (insn_gen_fn) gen_mips_shrl_ph,
    &operand_data[1150],
    3,
    0,
    2,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:417 */
  {
    "mips_subu_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subu_ph,
    &operand_data[1115],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:430 */
  {
    "mips_subu_s_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subu_s_ph,
    &operand_data[1115],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:443 */
  {
    "mips_subuh_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subuh.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subuh_qb,
    &operand_data[1118],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:453 */
  {
    "mips_subuh_r_qb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subuh_r.qb\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subuh_r_qb,
    &operand_data[1118],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:463 */
  {
    "mips_addqh_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addqh.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addqh_ph,
    &operand_data[1115],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:473 */
  {
    "mips_addqh_r_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addqh_r.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addqh_r_ph,
    &operand_data[1115],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:483 */
  {
    "mips_addqh_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addqh.w\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addqh_w,
    &operand_data[1136],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:493 */
  {
    "mips_addqh_r_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addqh_r.w\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_addqh_r_w,
    &operand_data[1136],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:503 */
  {
    "mips_subqh_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subqh.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subqh_ph,
    &operand_data[1115],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:513 */
  {
    "mips_subqh_r_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subqh_r.ph\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subqh_r_ph,
    &operand_data[1115],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:523 */
  {
    "mips_subqh_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subqh.w\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subqh_w,
    &operand_data[1136],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:533 */
  {
    "mips_subqh_r_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subqh_r.w\t%0,%z1,%z2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_subqh_r_w,
    &operand_data[1136],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:543 */
  {
    "mips_dpax_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpax.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpax_w_ph,
    &operand_data[1128],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:554 */
  {
    "mips_dpsx_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsx.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsx_w_ph,
    &operand_data[1128],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:565 */
  {
    "mips_dpaqx_s_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpaqx_s.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpaqx_s_w_ph,
    &operand_data[1128],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:580 */
  {
    "mips_dpaqx_sa_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpaqx_sa.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpaqx_sa_w_ph,
    &operand_data[1128],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:595 */
  {
    "mips_dpsqx_s_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsqx_s.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsqx_s_w_ph,
    &operand_data[1128],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dspr2.md:610 */
  {
    "mips_dpsqx_sa_w_ph",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsqx_sa.w.ph\t%q0,%z2,%z3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mips_dpsqx_sa_w_ph,
    &operand_data[1128],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addqq3,
    &operand_data[1153],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addhq3,
    &operand_data[1156],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addsq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addsq3,
    &operand_data[1159],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "adddq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "daddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_adddq3,
    &operand_data[1162],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "adduqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_adduqq3,
    &operand_data[1165],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "adduhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_adduhq3,
    &operand_data[1168],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addusq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addusq3,
    &operand_data[1171],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addudq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "daddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addudq3,
    &operand_data[1174],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addha3,
    &operand_data[1177],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addsa3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addsa3,
    &operand_data[1180],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addda3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "daddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addda3,
    &operand_data[1183],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "adduha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_adduha3,
    &operand_data[1186],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "addusa3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addusa3,
    &operand_data[1189],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:45 */
  {
    "adduda3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "daddu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_adduda3,
    &operand_data[1192],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:54 */
  {
    "usadduqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usadduqq3,
    &operand_data[1165],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:54 */
  {
    "usadduhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usadduhq3,
    &operand_data[1168],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:54 */
  {
    "usadduha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usadduha3,
    &operand_data[1186],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:54 */
  {
    "usaddv4uqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usaddv4uqq3,
    &operand_data[1195],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:54 */
  {
    "usaddv2uhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usaddv2uhq3,
    &operand_data[1198],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:54 */
  {
    "usaddv2uha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usaddv2uha3,
    &operand_data[1201],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:66 */
  {
    "ssaddhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddhq3,
    &operand_data[1156],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:66 */
  {
    "ssaddsq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddsq3,
    &operand_data[1159],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:66 */
  {
    "ssaddha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddha3,
    &operand_data[1177],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:66 */
  {
    "ssaddsa3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddsa3,
    &operand_data[1180],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:66 */
  {
    "ssaddv2hq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddv2hq3,
    &operand_data[1204],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:66 */
  {
    "ssaddv2ha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "addq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddv2ha3,
    &operand_data[1207],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subqq3,
    &operand_data[1153],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subhq3,
    &operand_data[1156],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subsq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subsq3,
    &operand_data[1159],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subdq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsubu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subdq3,
    &operand_data[1162],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subuqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subuqq3,
    &operand_data[1165],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subuhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subuhq3,
    &operand_data[1168],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subusq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subusq3,
    &operand_data[1171],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subudq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsubu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subudq3,
    &operand_data[1174],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subha3,
    &operand_data[1177],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subsa3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subsa3,
    &operand_data[1180],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subda3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsubu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subda3,
    &operand_data[1183],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subuha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subuha3,
    &operand_data[1186],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subusa3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subusa3,
    &operand_data[1189],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:78 */
  {
    "subuda3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dsubu\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subuda3,
    &operand_data[1192],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:87 */
  {
    "ussubuqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubuqq3,
    &operand_data[1165],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:87 */
  {
    "ussubuhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubuhq3,
    &operand_data[1168],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:87 */
  {
    "ussubuha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubuha3,
    &operand_data[1186],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:87 */
  {
    "ussubv4uqq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.qb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubv4uqq3,
    &operand_data[1195],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:87 */
  {
    "ussubv2uhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubv2uhq3,
    &operand_data[1198],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:87 */
  {
    "ussubv2uha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subu_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubv2uha3,
    &operand_data[1201],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:99 */
  {
    "sssubhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubhq3,
    &operand_data[1156],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:99 */
  {
    "sssubsq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubsq3,
    &operand_data[1159],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:99 */
  {
    "sssubha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubha3,
    &operand_data[1177],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:99 */
  {
    "sssubsa3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubsa3,
    &operand_data[1180],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:99 */
  {
    "sssubv2hq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubv2hq3,
    &operand_data[1204],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:99 */
  {
    "sssubv2ha3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "subq_s.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubv2ha3,
    &operand_data[1207],
    3,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:111 */
  {
    "ssmulv2hq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_rs.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssmulv2hq3,
    &operand_data[1210],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:111 */
  {
    "ssmulhq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_rs.ph\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssmulhq3,
    &operand_data[1214],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:111 */
  {
    "ssmulsq3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "mulq_rs.w\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssmulsq3,
    &operand_data[1218],
    4,
    2,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:124 */
  {
    "ssmaddsqdq4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpaq_sa.l.w\t%q0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssmaddsqdq4,
    &operand_data[1222],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-fixed.md:141 */
  {
    "ssmsubsqdq4",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "dpsq_sa.l.w\t%q0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssmsubsqdq4,
    &operand_data[1222],
    4,
    3,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:106 */
  {
    "movv2si_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_901 },
#else
    { 0, 0, output_901 },
#endif
    (insn_gen_fn) gen_movv2si_internal,
    &operand_data[1226],
    2,
    0,
    7,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:106 */
  {
    "movv4hi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_902 },
#else
    { 0, 0, output_902 },
#endif
    (insn_gen_fn) gen_movv4hi_internal,
    &operand_data[1228],
    2,
    0,
    7,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:106 */
  {
    "movv8qi_internal",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_903 },
#else
    { 0, 0, output_903 },
#endif
    (insn_gen_fn) gen_movv8qi_internal,
    &operand_data[1230],
    2,
    0,
    7,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:128 */
  {
    "vec_pack_ssat_v2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "packsswh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_pack_ssat_v2si,
    &operand_data[1232],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:128 */
  {
    "vec_pack_ssat_v4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "packsshb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_pack_ssat_v4hi,
    &operand_data[1235],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:140 */
  {
    "vec_pack_usat_v4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "packushb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_pack_usat_v4hi,
    &operand_data[1235],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:152 */
  {
    "addv2si3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addv2si3,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:152 */
  {
    "addv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:152 */
  {
    "addv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_addv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:166 */
  {
    "loongson_paddd",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddd\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_paddd,
    &operand_data[1247],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:176 */
  {
    "ssaddv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddsh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:176 */
  {
    "ssaddv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddsb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ssaddv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:185 */
  {
    "usaddv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddush\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usaddv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:185 */
  {
    "usaddv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "paddusb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_usaddv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:194 */
  {
    "loongson_pandn_w",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pandn\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pandn_w,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:194 */
  {
    "loongson_pandn_h",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pandn\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pandn_h,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:194 */
  {
    "loongson_pandn_b",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pandn\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pandn_b,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:194 */
  {
    "loongson_pandn_d",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pandn\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pandn_d,
    &operand_data[1247],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:204 */
  {
    "loongson_pavgh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pavgh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pavgh,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:204 */
  {
    "loongson_pavgb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pavgb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pavgb,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:214 */
  {
    "loongson_pcmpeqw",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pcmpeqw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pcmpeqw,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:214 */
  {
    "loongson_pcmpeqh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pcmpeqh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pcmpeqh,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:214 */
  {
    "loongson_pcmpeqb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pcmpeqb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pcmpeqb,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:224 */
  {
    "loongson_pcmpgtw",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pcmpgtw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pcmpgtw,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:224 */
  {
    "loongson_pcmpgth",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pcmpgth\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pcmpgth,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:224 */
  {
    "loongson_pcmpgtb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pcmpgtb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pcmpgtb,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:234 */
  {
    "loongson_pextrh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pextrh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pextrh,
    &operand_data[1250],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:244 */
  {
    "loongson_pinsrh_0",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pinsrh_0\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pinsrh_0,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:253 */
  {
    "loongson_pinsrh_1",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pinsrh_1\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pinsrh_1,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:262 */
  {
    "loongson_pinsrh_2",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pinsrh_2\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pinsrh_2,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:271 */
  {
    "loongson_pinsrh_3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pinsrh_3\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pinsrh_3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:281 */
  {
    "loongson_pmaddhw",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmaddhw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pmaddhw,
    &operand_data[1253],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:291 */
  {
    "smaxv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmaxsh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_smaxv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:300 */
  {
    "umaxv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmaxub\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umaxv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:309 */
  {
    "sminv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pminsh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sminv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:318 */
  {
    "uminv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pminub\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_uminv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:327 */
  {
    "loongson_pmovmskb",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmovmskb\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pmovmskb,
    &operand_data[1244],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:336 */
  {
    "umulv4hi3_highpart",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmulhuh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_umulv4hi3_highpart,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:346 */
  {
    "smulv4hi3_highpart",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmulhh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_smulv4hi3_highpart,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:356 */
  {
    "mulv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmullh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_mulv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:365 */
  {
    "loongson_pmuluw",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pmuluw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pmuluw,
    &operand_data[1256],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:375 */
  {
    "loongson_pasubub",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pasubub\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pasubub,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:385 */
  {
    "loongson_biadd",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "biadd\t%0,%1",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_biadd,
    &operand_data[1259],
    2,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:394 */
  {
    "loongson_psadbh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pasubub\t%0,%1,%2;biadd\t%0,%0",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_psadbh,
    &operand_data[1259],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:404 */
  {
    "loongson_pshufh",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "pshufh\t%0,%2,%3",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_pshufh,
    &operand_data[1262],
    4,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:415 */
  {
    "ashlv2si3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psllw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ashlv2si3,
    &operand_data[1266],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:415 */
  {
    "ashlv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psllh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ashlv4hi3,
    &operand_data[1250],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:424 */
  {
    "ashrv2si3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psraw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ashrv2si3,
    &operand_data[1266],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:424 */
  {
    "ashrv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psrah\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ashrv4hi3,
    &operand_data[1250],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:433 */
  {
    "lshrv2si3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psrlw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_lshrv2si3,
    &operand_data[1266],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:433 */
  {
    "lshrv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psrlh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_lshrv4hi3,
    &operand_data[1250],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:442 */
  {
    "subv2si3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subv2si3,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:442 */
  {
    "subv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:442 */
  {
    "subv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_subv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:454 */
  {
    "loongson_psubd",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubd\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_loongson_psubd,
    &operand_data[1247],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:464 */
  {
    "sssubv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubsh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:464 */
  {
    "sssubv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubsb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_sssubv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:473 */
  {
    "ussubv4hi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubush\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubv4hi3,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:473 */
  {
    "ussubv8qi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "psubusb\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_ussubv8qi3,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:482 */
  {
    "vec_interleave_highv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "punpckhwd\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_interleave_highv2si,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:482 */
  {
    "vec_interleave_highv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "punpckhhw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_interleave_highv4hi,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:482 */
  {
    "vec_interleave_highv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "punpckhbh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_interleave_highv8qi,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:492 */
  {
    "vec_interleave_lowv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "punpcklwd\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_interleave_lowv2si,
    &operand_data[1238],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:492 */
  {
    "vec_interleave_lowv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "punpcklhw\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_interleave_lowv4hi,
    &operand_data[1241],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:492 */
  {
    "vec_interleave_lowv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { .single =
#else
    {
#endif
    "punpcklbh\t%0,%1,%2",
#if HAVE_DESIGNATED_INITIALIZERS
    },
#else
    0, 0 },
#endif
    (insn_gen_fn) gen_vec_interleave_lowv8qi,
    &operand_data[1244],
    3,
    0,
    1,
    1
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:503 */
  {
    "divsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_966 },
#else
    { 0, 0, output_966 },
#endif
    (insn_gen_fn) gen_divsi3,
    &operand_data[1269],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:503 */
  {
    "udivsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_967 },
#else
    { 0, 0, output_967 },
#endif
    (insn_gen_fn) gen_udivsi3,
    &operand_data[1269],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:503 */
  {
    "divdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_968 },
#else
    { 0, 0, output_968 },
#endif
    (insn_gen_fn) gen_divdi3,
    &operand_data[1272],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:503 */
  {
    "udivdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_969 },
#else
    { 0, 0, output_969 },
#endif
    (insn_gen_fn) gen_udivdi3,
    &operand_data[1272],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:517 */
  {
    "modsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_970 },
#else
    { 0, 0, output_970 },
#endif
    (insn_gen_fn) gen_modsi3,
    &operand_data[1269],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:517 */
  {
    "umodsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_971 },
#else
    { 0, 0, output_971 },
#endif
    (insn_gen_fn) gen_umodsi3,
    &operand_data[1269],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:517 */
  {
    "moddi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_972 },
#else
    { 0, 0, output_972 },
#endif
    (insn_gen_fn) gen_moddi3,
    &operand_data[1272],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:517 */
  {
    "umoddi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { .function = output_973 },
#else
    { 0, 0, output_973 },
#endif
    (insn_gen_fn) gen_umoddi3,
    &operand_data[1272],
    3,
    0,
    1,
    3
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:939 */
  {
    "ctrapsi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_ctrapsi4,
    &operand_data[1275],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:939 */
  {
    "ctrapdi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_ctrapdi4,
    &operand_data[1279],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:976 */
  {
    "addsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_addsi3,
    &operand_data[1283],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:976 */
  {
    "adddi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_adddi3,
    &operand_data[1286],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1027 */
  {
    "adddi3+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1289],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1053 */
  {
    "adddi3+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1291],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1080 */
  {
    "adddi3+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1294],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1106 */
  {
    "mulsf3-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1296],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1147 */
  {
    "mulsf3-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1299],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1237 */
  {
    "mulsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mulsf3,
    &operand_data[1302],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1237 */
  {
    "muldf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_muldf3,
    &operand_data[1305],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1322 */
  {
    "mulsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mulsi3,
    &operand_data[1308],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1322 */
  {
    "muldi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_muldi3,
    &operand_data[1311],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1379 */
  {
    "muldi3+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1314],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1422 */
  {
    "muldi3+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1314],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1493 */
  {
    "muldi3+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1315],
    6,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1547 */
  {
    "muldi3+4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1321],
    6,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1605 */
  {
    "mulsidi3-4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1327],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1632 */
  {
    "mulsidi3-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1330],
    5,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1662 */
  {
    "mulsidi3-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1335],
    5,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1704 */
  {
    "mulsidi3-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1315],
    6,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1730 */
  {
    "mulsidi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mulsidi3,
    &operand_data[1340],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1730 */
  {
    "umulsidi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_umulsidi3,
    &operand_data[1340],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1784 */
  {
    "umulsidi3+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1343],
    5,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1784 */
  {
    "umulsidi3+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1343],
    5,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1804 */
  {
    "smulsi3_highpart-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1343],
    5,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1804 */
  {
    "smulsi3_highpart-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1343],
    5,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1902 */
  {
    "smulsi3_highpart",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_smulsi3_highpart,
    &operand_data[1308],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1902 */
  {
    "umulsi3_highpart",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_umulsi3_highpart,
    &operand_data[1308],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1921 */
  {
    "umulsi3_highpart+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1322],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1921 */
  {
    "umulsi3_highpart+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1322],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1986 */
  {
    "mulditi3-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1348],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:1986 */
  {
    "mulditi3-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1348],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2010 */
  {
    "mulditi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mulditi3,
    &operand_data[1352],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2010 */
  {
    "umulditi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_umulditi3,
    &operand_data[1352],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2247 */
  {
    "divsf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_divsf3,
    &operand_data[1355],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2247 */
  {
    "divdf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_divdf3,
    &operand_data[1358],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2247 */
  {
    "divv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_divv2sf3,
    &operand_data[1361],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2308 */
  {
    "divv2sf3+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1321],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2308 */
  {
    "divv2sf3+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1364],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2340 */
  {
    "andsi3-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1321],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2340 */
  {
    "andsi3-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1364],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2564 */
  {
    "andsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_andsi3,
    &operand_data[1368],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2564 */
  {
    "anddi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_anddi3,
    &operand_data[1371],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2654 */
  {
    "iorsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_iorsi3,
    &operand_data[1374],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2654 */
  {
    "iordi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_iordi3,
    &operand_data[1377],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2684 */
  {
    "xorsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_xorsi3,
    &operand_data[1374],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2684 */
  {
    "xordi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_xordi3,
    &operand_data[1377],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2814 */
  {
    "zero_extendsidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_zero_extendsidi2,
    &operand_data[1380],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2819 */
  {
    "zero_extendsidi2+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1380],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2848 */
  {
    "zero_extendqisi2-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1286],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2858 */
  {
    "zero_extendqisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_zero_extendqisi2,
    &operand_data[1382],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2858 */
  {
    "zero_extendqidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_zero_extendqidi2,
    &operand_data[1384],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2858 */
  {
    "zero_extendhisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_zero_extendhisi2,
    &operand_data[1386],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2858 */
  {
    "zero_extendhidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_zero_extendhidi2,
    &operand_data[1388],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2902 */
  {
    "zero_extendqihi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_zero_extendqihi2,
    &operand_data[1390],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2974 */
  {
    "zero_extendqihi2+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1380],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2990 */
  {
    "extendqisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extendqisi2,
    &operand_data[1382],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2990 */
  {
    "extendqidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extendqidi2,
    &operand_data[1384],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2990 */
  {
    "extendhisi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extendhisi2,
    &operand_data[1386],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:2990 */
  {
    "extendhidi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extendhidi2,
    &operand_data[1388],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "extendhidi2+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1382],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "extendhidi2+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1384],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "extendqihi2-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1386],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3005 */
  {
    "extendqihi2-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1388],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3035 */
  {
    "extendqihi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extendqihi2,
    &operand_data[1390],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3050 */
  {
    "extendqihi2+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1390],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3084 */
  {
    "extendqihi2+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1286],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3084 */
  {
    "extendqihi2+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1286],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3104 */
  {
    "fix_truncdfsi2-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1310],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3104 */
  {
    "fix_truncdfsi2-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1310],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3124 */
  {
    "fix_truncdfsi2-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1392],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3180 */
  {
    "fix_truncdfsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_fix_truncdfsi2,
    &operand_data[1394],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3217 */
  {
    "fix_truncsfsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_fix_truncsfsi2,
    &operand_data[1396],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3315 */
  {
    "fixuns_truncdfsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_fixuns_truncdfsi2,
    &operand_data[1394],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3361 */
  {
    "fixuns_truncdfdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_fixuns_truncdfdi2,
    &operand_data[1398],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3404 */
  {
    "fixuns_truncsfsi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_fixuns_truncsfsi2,
    &operand_data[1396],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3447 */
  {
    "fixuns_truncsfdi2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_fixuns_truncsfdi2,
    &operand_data[1354],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3498 */
  {
    "extv",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extv,
    &operand_data[1400],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3535 */
  {
    "extzv",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_extzv,
    &operand_data[1400],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3584 */
  {
    "insv",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_insv,
    &operand_data[1404],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3712 */
  {
    "insv+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1408],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3737 */
  {
    "insv+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1410],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3765 */
  {
    "insv+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1413],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3790 */
  {
    "insv+4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1416],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3802 */
  {
    "insv+5",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1418],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3802 */
  {
    "insv+6",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1420],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3817 */
  {
    "unspec_gotsi-6",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1422],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3817 */
  {
    "unspec_gotsi-5",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1425],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3832 */
  {
    "unspec_gotsi-4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1418],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3832 */
  {
    "unspec_gotsi-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1420],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3845 */
  {
    "unspec_gotsi-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1428],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3845 */
  {
    "unspec_gotsi-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1430],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3857 */
  {
    "unspec_gotsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_unspec_gotsi,
    &operand_data[1432],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3857 */
  {
    "unspec_gotdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_unspec_gotdi,
    &operand_data[1434],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3900 */
  {
    "unspec_gotdi+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1289],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3900 */
  {
    "unspec_gotdi+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1294],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3909 */
  {
    "unspec_gotdi+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1436],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3909 */
  {
    "movdi-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1439],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3921 */
  {
    "movdi-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1442],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3921 */
  {
    "movdi-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1445],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:3938 */
  {
    "movdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movdi,
    &operand_data[1434],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4003 */
  {
    "movdi+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1294],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movsi,
    &operand_data[1432],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv2hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2hi,
    &operand_data[1448],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv4qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv4qi,
    &operand_data[1450],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv2hq",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2hq,
    &operand_data[1452],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv2uhq",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2uhq,
    &operand_data[1454],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv2ha",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2ha,
    &operand_data[1456],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv2uha",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2uha,
    &operand_data[1458],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv4qq",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv4qq,
    &operand_data[1460],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4045 */
  {
    "movv4uqq",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv4uqq,
    &operand_data[1462],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4081 */
  {
    "movv4uqq+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1289],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4120 */
  {
    "reload_incc-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1289],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4162 */
  {
    "reload_incc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_reload_incc,
    &operand_data[1464],
    3,
    0,
    1,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4172 */
  {
    "reload_outcc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_reload_outcc,
    &operand_data[1467],
    3,
    0,
    1,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4235 */
  {
    "movhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movhi,
    &operand_data[1470],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4268 */
  {
    "movhi+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1472],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4310 */
  {
    "movqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movqi,
    &operand_data[1474],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4343 */
  {
    "movqi+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1476],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4368 */
  {
    "movsf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movsf,
    &operand_data[1478],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4409 */
  {
    "movdf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movdf,
    &operand_data[1480],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4450 */
  {
    "movti",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movti,
    &operand_data[1482],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4483 */
  {
    "movtf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movtf,
    &operand_data[1484],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4515 */
  {
    "movtf+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1486],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4515 */
  {
    "movtf+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1488],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4515 */
  {
    "movtf+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1490],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4515 */
  {
    "movtf+4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1492],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4515 */
  {
    "movtf+5",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1494],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4515 */
  {
    "movv2sf-4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1496],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4526 */
  {
    "movv2sf-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1498],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4526 */
  {
    "movv2sf-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1500],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4538 */
  {
    "movv2sf-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1502],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4553 */
  {
    "movv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2sf,
    &operand_data[1504],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprdf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprdf,
    &operand_data[1480],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprdi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprdi,
    &operand_data[1434],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprv2sf,
    &operand_data[1504],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprv2si,
    &operand_data[1506],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprv4hi,
    &operand_data[1508],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprv8qi,
    &operand_data[1510],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4608 */
  {
    "move_doubleword_fprtf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_move_doubleword_fprtf,
    &operand_data[1484],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4702 */
  {
    "load_const_gp_si",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_load_const_gp_si,
    &operand_data[34],
    1,
    0,
    1,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4702 */
  {
    "load_const_gp_di",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_load_const_gp_di,
    &operand_data[40],
    1,
    0,
    1,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4709 */
  {
    "load_const_gp_di+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1442],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4709 */
  {
    "load_const_gp_di+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1445],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4728 */
  {
    "load_const_gp_di+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1442],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4728 */
  {
    "load_const_gp_di+4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1445],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4752 */
  {
    "clear_cache-4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1512],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4752 */
  {
    "clear_cache-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1515],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4774 */
  {
    "clear_cache-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1283],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4791 */
  {
    "clear_cache-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1518],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4837 */
  {
    "clear_cache",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_clear_cache,
    &operand_data[1522],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4917 */
  {
    "movmemsi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movmemsi,
    &operand_data[1524],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4937 */
  {
    "ashlsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_ashlsi3,
    &operand_data[1283],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4937 */
  {
    "ashrsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_ashrsi3,
    &operand_data[1283],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4937 */
  {
    "lshrsi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_lshrsi3,
    &operand_data[1283],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4937 */
  {
    "ashldi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_ashldi3,
    &operand_data[1528],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4937 */
  {
    "ashrdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_ashrdi3,
    &operand_data[1528],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:4937 */
  {
    "lshrdi3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_lshrdi3,
    &operand_data[1528],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5079 */
  {
    "lshrdi3+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1291],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5079 */
  {
    "lshrdi3+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1291],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5079 */
  {
    "lshrdi3+3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1291],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5079 */
  {
    "lshrdi3+4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1296],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5079 */
  {
    "cbranchsi4-3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1296],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5079 */
  {
    "cbranchsi4-2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1296],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5099 */
  {
    "cbranchsi4-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1531],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5258 */
  {
    "cbranchsi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_cbranchsi4,
    &operand_data[1534],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5258 */
  {
    "cbranchdi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_cbranchdi4,
    &operand_data[1538],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5271 */
  {
    "cbranchsf4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_cbranchsf4,
    &operand_data[1542],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5271 */
  {
    "cbranchdf4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_cbranchdf4,
    &operand_data[1546],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5285 */
  {
    "condjump",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_condjump,
    &operand_data[1549],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5342 */
  {
    "cstoresi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_cstoresi4,
    &operand_data[1551],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5342 */
  {
    "cstoredi4",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_cstoredi4,
    &operand_data[1555],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5517 */
  {
    "jump",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_jump,
    &operand_data[705],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5553 */
  {
    "indirect_jump",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_indirect_jump,
    &operand_data[841],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5572 */
  {
    "tablejump",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_tablejump,
    &operand_data[1559],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5617 */
  {
    "builtin_setjmp_setup",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_builtin_setjmp_setup,
    &operand_data[841],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5632 */
  {
    "builtin_longjmp",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_builtin_longjmp,
    &operand_data[841],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5669 */
  {
    "prologue",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_prologue,
    &operand_data[0],
    0,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5688 */
  {
    "epilogue",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_epilogue,
    &operand_data[0],
    0,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5696 */
  {
    "sibcall_epilogue",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sibcall_epilogue,
    &operand_data[0],
    0,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5707 */
  {
    "return",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_return,
    &operand_data[0],
    0,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5784 */
  {
    "eh_return",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_eh_return,
    &operand_data[1561],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5812 */
  {
    "eh_return+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1562],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5822 */
  {
    "exception_receiver",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_exception_receiver,
    &operand_data[0],
    0,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5835 */
  {
    "nonlocal_goto_receiver",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_nonlocal_goto_receiver,
    &operand_data[0],
    0,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5846 */
  {
    "nonlocal_goto_receiver+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1325],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5861 */
  {
    "nonlocal_goto_receiver+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1564],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5861 */
  {
    "sibcall-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1486],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5963 */
  {
    "sibcall",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sibcall,
    &operand_data[1566],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:5982 */
  {
    "sibcall_value",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sibcall_value,
    &operand_data[1566],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6013 */
  {
    "call",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_call,
    &operand_data[1566],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6060 */
  {
    "call+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1570],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6087 */
  {
    "call_value-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[849],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6113 */
  {
    "call_value",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_call_value,
    &operand_data[1566],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6126 */
  {
    "call_value+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1572],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6154 */
  {
    "call_value+2",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[854],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6184 */
  {
    "untyped_call-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1572],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6219 */
  {
    "untyped_call",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_untyped_call,
    &operand_data[1566],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6328 */
  {
    "movsicc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movsicc,
    &operand_data[1576],
    4,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6328 */
  {
    "movdicc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movdicc,
    &operand_data[1580],
    4,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6340 */
  {
    "movsfcc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movsfcc,
    &operand_data[1584],
    4,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6340 */
  {
    "movdfcc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movdfcc,
    &operand_data[1588],
    4,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md:6394 */
  {
    "movdfcc+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1592],
    1,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:42 */
  {
    "memory_barrier",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_memory_barrier,
    &operand_data[0],
    0,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:72 */
  {
    "sync_compare_and_swapqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_compare_and_swapqi,
    &operand_data[1593],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:72 */
  {
    "sync_compare_and_swaphi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_compare_and_swaphi,
    &operand_data[1597],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_addqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_addqi,
    &operand_data[1594],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_subqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_subqi,
    &operand_data[1594],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_iorqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_iorqi,
    &operand_data[1594],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_xorqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_xorqi,
    &operand_data[1594],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_andqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_andqi,
    &operand_data[1594],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_addhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_addhi,
    &operand_data[1598],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_subhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_subhi,
    &operand_data[1598],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_iorhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_iorhi,
    &operand_data[1598],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_xorhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_xorhi,
    &operand_data[1598],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:117 */
  {
    "sync_andhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_andhi,
    &operand_data[1598],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_addqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_addqi,
    &operand_data[1593],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_subqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_subqi,
    &operand_data[1593],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_iorqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_iorqi,
    &operand_data[1593],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_xorqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_xorqi,
    &operand_data[1593],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_andqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_andqi,
    &operand_data[1593],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_addhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_addhi,
    &operand_data[1597],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_subhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_subhi,
    &operand_data[1597],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_iorhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_iorhi,
    &operand_data[1597],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_xorhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_xorhi,
    &operand_data[1597],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:153 */
  {
    "sync_old_andhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_andhi,
    &operand_data[1597],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_addqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_addqi,
    &operand_data[1593],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_subqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_subqi,
    &operand_data[1593],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_iorqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_iorqi,
    &operand_data[1593],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_xorqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_xorqi,
    &operand_data[1593],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_andqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_andqi,
    &operand_data[1593],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_addhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_addhi,
    &operand_data[1597],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_subhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_subhi,
    &operand_data[1597],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_iorhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_iorhi,
    &operand_data[1597],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_xorhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_xorhi,
    &operand_data[1597],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:194 */
  {
    "sync_new_andhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_andhi,
    &operand_data[1597],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:240 */
  {
    "sync_nandqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_nandqi,
    &operand_data[1594],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:240 */
  {
    "sync_nandhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_nandhi,
    &operand_data[1598],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:276 */
  {
    "sync_old_nandqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_nandqi,
    &operand_data[1593],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:276 */
  {
    "sync_old_nandhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_old_nandhi,
    &operand_data[1597],
    3,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:315 */
  {
    "sync_new_nandqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_nandqi,
    &operand_data[1593],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:315 */
  {
    "sync_new_nandhi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_new_nandhi,
    &operand_data[1597],
    3,
    3,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:530 */
  {
    "sync_lock_test_and_setqi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_lock_test_and_setqi,
    &operand_data[1593],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/sync.md:530 */
  {
    "sync_lock_test_and_sethi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sync_lock_test_and_sethi,
    &operand_data[1597],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:72 */
  {
    "movv2sfcc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2sfcc,
    &operand_data[1601],
    4,
    2,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:149 */
  {
    "vec_initv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_vec_initv2sf,
    &operand_data[1604],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:197 */
  {
    "vec_setv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_vec_setv2sf,
    &operand_data[1606],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:217 */
  {
    "mips_cvt_ps_s",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_cvt_ps_s,
    &operand_data[1609],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:233 */
  {
    "mips_cvt_s_pl",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_cvt_s_pl,
    &operand_data[1611],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:241 */
  {
    "mips_cvt_s_pu",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_cvt_s_pu,
    &operand_data[1611],
    2,
    1,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:303 */
  {
    "mips_abs_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_abs_ps,
    &operand_data[1603],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:347 */
  {
    "mips_abs_ps+1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1613],
    6,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:376 */
  {
    "scc_ps-1",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    0,
    &operand_data[1613],
    6,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:433 */
  {
    "scc_ps",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_scc_ps,
    &operand_data[1619],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:509 */
  {
    "single_cc",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_single_cc,
    &operand_data[1549],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:600 */
  {
    "vcondv2sf",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_vcondv2sf,
    &operand_data[1621],
    6,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:615 */
  {
    "sminv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_sminv2sf3,
    &operand_data[1614],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-ps-3d.md:626 */
  {
    "smaxv2sf3",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_smaxv2sf3,
    &operand_data[1614],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1101 */
  {
    "mips_lbux",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_lbux,
    &operand_data[1627],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1125 */
  {
    "mips_lhx",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_lhx,
    &operand_data[1627],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1149 */
  {
    "mips_lwx",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_lwx,
    &operand_data[1627],
    3,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1184 */
  {
    "mips_madd",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_madd,
    &operand_data[1366],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1184 */
  {
    "mips_maddu",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_maddu,
    &operand_data[1366],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1192 */
  {
    "mips_msub",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_msub,
    &operand_data[1366],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips-dsp.md:1192 */
  {
    "mips_msubu",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_mips_msubu,
    &operand_data[1366],
    4,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:96 */
  {
    "movv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv2si,
    &operand_data[1506],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:96 */
  {
    "movv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv4hi,
    &operand_data[1508],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:96 */
  {
    "movv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_movv8qi,
    &operand_data[1510],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:116 */
  {
    "vec_initv2si",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_vec_initv2si,
    &operand_data[1630],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:116 */
  {
    "vec_initv4hi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_vec_initv4hi,
    &operand_data[1632],
    2,
    0,
    0,
    0
  },
  /* /home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/loongson.md:116 */
  {
    "vec_initv8qi",
#if HAVE_DESIGNATED_INITIALIZERS
    { 0 },
#else
    { 0, 0, 0 },
#endif
    (insn_gen_fn) gen_vec_initv8qi,
    &operand_data[1634],
    2,
    0,
    0,
    0
  },
};


const char *
get_insn_name (int code)
{
  if (code == NOOP_MOVE_INSN_CODE)
    return "NOOP_MOVE";
  else
    return insn_data[code].name;
}
