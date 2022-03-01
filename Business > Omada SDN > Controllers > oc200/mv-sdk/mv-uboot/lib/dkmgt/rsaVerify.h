#ifndef RSA_VERIFY_H_
#define RSA_VERIFY_H_

#include "bigNumber.h"

typedef struct _MY_PUBLICKEYSTRUC {
	char bType;
	char bVersion;
	short reserved;
	unsigned int aiKeyAlg;
} __attribute__((packed)) MY_BLOBHEADER, MY_PUBLICKEYSTRUC;

typedef struct _MY_RSAPUBKEY {
	unsigned int magic;
	unsigned int bitlen;
	unsigned int pubexp;
} __attribute__((packed)) MY_RSAPUBKEY;

typedef struct _MY_RSA_PUBLICK_BLOB{
	MY_PUBLICKEYSTRUC blob_header;
	MY_RSAPUBKEY      rsa_pub_key;
} __attribute__((packed)) MY_RSA_PUBLICK_BLOB;


struct RSAKey {
	int bits;
	int bytes;
	Bignum modulus;
	Bignum exponent;
	Bignum private_exponent;
	Bignum p;
	Bignum q;
	Bignum iqmp;
	char *comment;
};


#define CHAR64(c) (((c) < 0 || (c) > 127) ? -1 : index_64[(c)])


/* 
 * fn		int rsaVerifySignByBase64EncodePublicKeyBlob(unsigned char *pPublicKeyBlob,
 *			 												 unsigned long PublicKeyBlobLen,
 *			 												 unsigned char *pInData,      
 *			 												 unsigned long inDataLen,		   
 *			 												 unsigned char *PInSignature,   
 *			 												 unsigned long inSignatureLen)
 * brief	Check signature with public key
 * details	
 *
 * param[in]	pPublicKeyBlob - public key	
 * param[in]	PublicKeyBlobLen - public key length
 * param[in]	pInData	- mod number
 * param[in]	inDataLen - mod number length
 * param[in]	PInSignature - signature	
 * param[in]	inSignatureLen - signature length
 *
 * return	1 is returned if signature is OK, otherwise the return value is 0 		
 */
int rsaVerifySignByBase64EncodePublicKeyBlob(unsigned char *pPublicKeyBlob,
 												 unsigned long PublicKeyBlobLen,
 												 unsigned char *pInData,      
 												 unsigned long inDataLen,		   
 												 unsigned char *PInSignature,   
 												 unsigned long inSignatureLen);

#endif

