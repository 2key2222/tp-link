#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#define snewn(n, type) ((type *)smalloc((n)*sizeof(type)))
#define smalloc RSA_safemalloc
#define sfree RSA_safefree

void *RSA_safemalloc(size_t);
void RSA_safefree(void *);


Bignum RSA_newbn(int length);
Bignum RSA_bignum_from_long(unsigned long nn);
Bignum RSA_bignum_from_bytes(const unsigned char *data, int nbytes);
Bignum RSA_bigmod(Bignum a, Bignum b);
void RSA_freebn(Bignum b);
Bignum RSA_modpow(Bignum base, Bignum exp, Bignum mod);
Bignum RSA_modmul(Bignum p, Bignum q, Bignum mod);
Bignum RSA_modinv(Bignum number, Bignum modulus);
Bignum RSA_bigmuladd(Bignum a, Bignum b, Bignum addend);
int RSA_bignum_bitcount(Bignum bn);
int RSA_bignum_byte(Bignum bn, int i);
int RSA_bignum_cmp(Bignum a, Bignum b);

/*extern Bignum Zero, One;*/







#endif
