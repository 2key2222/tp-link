#ifndef INIT_TABLES
#define INIT_TABLES

typedef struct {
    enum {
		OP_WR_XSMI,
		OP_RD_XSMI,
        OP_WR_REG, /* write to reg p0 val p1 */
        OP_WR_DFX, /* write to dfx p0 val p1 */
        OP_WR_MNG, /* write to mng p0 val p1 */
        OP_DELAY_START, /* set delay after each command to p0 ms */
        OP_DELAY_END,   /* sent delay to 0 */
        OP_WR_F_REG, /* write to reg p0 val p1 bitoffs p2 len p3 */
        OP_WR_F_DFX, /* write to dfx p0 val p1 bitoffs p2 len p3 */
        OP_WR_F_MNG, /* write to mng p0 val p1 bitoffs p2 len p3 */
        OP_WR_M_REG, /* write to reg p0 val p1 mask p2 */
        OP_COMMENT,  /* print test from str */
        OP_CYCLE_START, /* start cycle count=p0, offset = offset + i*p1 */
        OP_CYCLE_END,
        OP_END
    } op;
    GT_U32 p0;
    GT_U32 p1;
    GT_U32 p2;
    GT_U32 p3;
    const char *str;
} INIT_OP_STC;


#endif
