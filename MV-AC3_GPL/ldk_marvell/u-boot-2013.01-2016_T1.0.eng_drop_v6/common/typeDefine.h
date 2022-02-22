#ifndef TYPE_DEFINE_H
#define TYPE_DEFINE_H

typedef unsigned short BignumInt;
typedef unsigned long BignumDblInt;
#define BIGNUM_INT_MASK  0xFFFFU
#define BIGNUM_TOP_BIT   0x8000U
#define BIGNUM_INT_BITS  16
#define MUL_WORD(w1, w2) ((BignumDblInt)w1 * w2)
#define DIVMOD_WORD(q, r, hi, lo, w) do { \
    BignumDblInt n = (((BignumDblInt)hi) << BIGNUM_INT_BITS) | lo; \
    q = n / w; \
    r = n % w; \
} while (0)

typedef BignumInt *Bignum;


#define BIGNUM_INT_BYTES (BIGNUM_INT_BITS / 8)


typedef struct {
    unsigned long hi, lo;
} uint64;

typedef unsigned int uint32;
typedef unsigned int word32;

#endif
