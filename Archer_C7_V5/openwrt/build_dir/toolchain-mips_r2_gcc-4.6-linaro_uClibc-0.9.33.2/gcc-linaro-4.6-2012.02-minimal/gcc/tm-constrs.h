/* Generated automatically by the program 'build/genpreds'
   from the machine description file '/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/mips.md'.  */

#ifndef GCC_TM_CONSTRS_H
#define GCC_TM_CONSTRS_H

static inline bool
satisfies_constraint_kf (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return force_to_mem_operand (op, mode);
}
static inline bool
satisfies_constraint_ks (rtx op)
{
  return (GET_CODE (op) == REG) && (
#line 101 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(REGNO (op) == STACK_POINTER_REGNUM));
}
static inline bool
satisfies_constraint_I (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 108 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(SMALL_OPERAND (ival)));
}
static inline bool
satisfies_constraint_J (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 113 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(ival == 0));
}
static inline bool
satisfies_constraint_K (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 118 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(SMALL_OPERAND_UNSIGNED (ival)));
}
static inline bool
satisfies_constraint_L (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 124 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(LUI_OPERAND (ival)));
}
static inline bool
satisfies_constraint_M (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && ((
#line 130 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(!SMALL_OPERAND (ival))) && ((
#line 131 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(!SMALL_OPERAND_UNSIGNED (ival))) && (
#line 132 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(!LUI_OPERAND (ival)))));
}
static inline bool
satisfies_constraint_N (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 137 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(ival >= -0xffff && ival < 0));
}
static inline bool
satisfies_constraint_O (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 142 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(ival >= -0x4000 && ival < 0x4000));
}
static inline bool
satisfies_constraint_P (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 147 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(ival > 0 && ival < 0x10000));
}
static inline bool
satisfies_constraint_G (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (GET_CODE (op) == CONST_DOUBLE) && (
#line 154 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(op == CONST0_RTX (mode)));
}
static inline bool
satisfies_constraint_Q (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return const_arith_operand (op, mode);
}
static inline bool
satisfies_constraint_R (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (GET_CODE (op) == MEM) && (
#line 165 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(mips_address_insns (XEXP (op, 0), mode, false) == 1));
}
static inline bool
satisfies_constraint_S (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (call_insn_operand (op, mode)) && (
#line 171 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(CONSTANT_P (op)));
}
static inline bool
satisfies_constraint_T (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (move_operand (op, mode)) && ((
#line 178 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(CONSTANT_P (op))) && (
#line 179 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(mips_dangerous_for_la25_p (op))));
}
static inline bool
satisfies_constraint_U (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (move_operand (op, mode)) && ((
#line 186 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(CONSTANT_P (op))) && (
#line 187 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(!mips_dangerous_for_la25_p (op))));
}
static inline bool
satisfies_constraint_W (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (GET_CODE (op) == MEM) && ((memory_operand (op, mode)) && ((
#line 197 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(!TARGET_MIPS16)) || ((!(stack_operand (op, mode))) && (!(
#line 199 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(CONSTANT_P (XEXP (op, 0))))))));
}
static inline bool
satisfies_constraint_YG (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return (GET_CODE (op) == CONST_VECTOR) && (
#line 205 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(op == CONST0_RTX (mode)));
}
static inline bool
satisfies_constraint_YA (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 211 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(UIMM6_OPERAND (ival)));
}
static inline bool
satisfies_constraint_YB (rtx op)
{
  HOST_WIDE_INT ival = 0;
  if (CONST_INT_P (op))
    ival = INTVAL (op);
  return (GET_CODE (op) == CONST_INT) && (
#line 217 "/home/ubuntu/Archer_C7_V5/openwrt/build_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/gcc-linaro-4.6-2012.02/gcc/config/mips/constraints.md"
(IMM10_OPERAND (ival)));
}
static inline bool
satisfies_constraint_Yb (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return qi_mask_operand (op, mode);
}
static inline bool
satisfies_constraint_Yh (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return hi_mask_operand (op, mode);
}
static inline bool
satisfies_constraint_Yw (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return si_mask_operand (op, mode);
}
static inline bool
satisfies_constraint_Yx (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  return low_bitmask_operand (op, mode);
}
#endif /* tm-constrs.h */
