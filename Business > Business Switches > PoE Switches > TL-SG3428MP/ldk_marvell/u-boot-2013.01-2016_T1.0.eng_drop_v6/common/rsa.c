
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include<common.h>
#include<vsprintf.h>
/*
#ifdef WIN32
#include <crtdbg.h>
#endif
*/
#include "typeDefine.h"
#include "shaAndSha512.h"
#include "bigNumber.h"
#include "rsa.h"

//#define TEST_RSA

typedef struct _MY_PUBLICKEYSTRUC {
	char bType;
	char bVersion;
	short reserved;
	unsigned long aiKeyAlg;
}MY_BLOBHEADER, MY_PUBLICKEYSTRUC;

typedef struct _MY_RSAPUBKEY {
	unsigned long magic;
	unsigned long bitlen;
	unsigned long pubexp;
} MY_RSAPUBKEY;

typedef struct _MY_RSA_PUBLICK_BLOB{
	MY_PUBLICKEYSTRUC blob_header;
	MY_RSAPUBKEY      rsa_pub_key;
}MY_RSA_PUBLICK_BLOB;


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


unsigned long rsa_read_long_from_public_key(char *bit)
{
    unsigned long re =0;
	re = ((bit[0])&(0xFF)) |
		(((bit[1])&(0xFF))<<8) |
		(((bit[2])&(0xFF))<<16) |
		(((bit[3])&(0xFF))<<24);
   return re;
}


static void *rsa2_newkey_ex(char *data, int len)
{
    char *p;
    unsigned long bit_len;
    struct RSAKey *rsa;
	char temp_buf[256];
	int i;
	MY_RSA_PUBLICK_BLOB *rsa_pub_blob;
	rsa_pub_blob = (MY_RSA_PUBLICK_BLOB *)data;
	
    rsa = snewn(1,struct RSAKey);
    if (!rsa)
		return NULL;
	//下面这段代码是专进MS PUBKEYBLOB 结构用的,请注意
    
	p = data + sizeof(MY_PUBLICKEYSTRUC);           //RSAPUBKEY
	if(memcmp(p, "RSA1", 4))
	{
		goto error_exit;
	}

	bit_len = rsa_read_long_from_public_key((char*)&(rsa_pub_blob->rsa_pub_key.bitlen));
	
	rsa->exponent = RSA_bignum_from_long(rsa_read_long_from_public_key((char*)(&(rsa_pub_blob->rsa_pub_key.pubexp))));

	p=data + sizeof(MY_RSA_PUBLICK_BLOB);
	
	memset(temp_buf,0,sizeof(temp_buf));
	for(i=0; (i<(int)(bit_len/8))&&(i<sizeof(temp_buf)); i++)
	{
		temp_buf[i] = p[(bit_len/8)-1 -i];
	}

    rsa->modulus = RSA_bignum_from_bytes((unsigned char *)temp_buf, bit_len/8);

    rsa->private_exponent = NULL;

    rsa->comment = NULL;
	
    return rsa;
error_exit:
	sfree(rsa);
	return NULL;
}

static const unsigned char asn1_weird_stuff[] = {
    0x00, 0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2B,
		0x0E, 0x03, 0x02, 0x1A, 0x05, 0x00, 0x04, 0x14,
};

#define ASN1_LEN ( (int) sizeof(asn1_weird_stuff) )

static int rsa2_verifysig(void *key, char *sig, int siglen,
			   char *data, int datalen)
{
    struct RSAKey *rsa = (struct RSAKey *) key;
    Bignum in, out;
    int slen;
    int bytes, i, j, ret;
    unsigned char hash[20];
   
	in = RSA_bignum_from_bytes((unsigned char *)sig, siglen);

    out = RSA_modpow(in, rsa->exponent, rsa->modulus);

    RSA_freebn(in);

    ret = 1;

	slen = (int)(out[0]);

#ifdef TEST_RSA
	printf("slen %d\n",slen);
	for(i = 1; i <=slen; i++)
	{
		printf("%02x",out[i]);
	}
	printf("\n");
#endif 
    bytes = (RSA_bignum_bitcount(rsa->modulus)+7) / 8;
    /* Top (partial) byte should be zero. */
    if (RSA_bignum_byte(out, bytes - 1) != 0)
	ret = 0;
    /* First whole byte should be 1. */
    if (RSA_bignum_byte(out, bytes - 2) != 1)
	ret = 0;
    /* Most of the rest should be FF. */
    for (i = bytes - 3; i >= 20 + ASN1_LEN; i--) {
	if (RSA_bignum_byte(out, i) != 0xFF)
	    ret = 0;
    }
    /* Then we expect to see the asn1_weird_stuff. */
    for (i = 20 + ASN1_LEN - 1, j = 0; i >= 20; i--, j++) {
	if (RSA_bignum_byte(out, i) != asn1_weird_stuff[j])
	    ret = 0;
    }
    /* Finally, we expect to see the SHA-1 hash of the signed data. */
    //这里,我们要变一下,这里要用MD5算法解一下.
	//也可以用它来做HASH
    RSA_SHA_Simple(data, datalen, hash);
#ifdef TEST_RSA
	printf("\n");
	for(i = 0; i < 20; i++)
	{
		printf("%2x ",hash[i]);
	}
	printf("\n");
#endif
    for (i = 19, j = 0; i >= 0; i--, j++) {
	if (RSA_bignum_byte(out, i) != hash[j])
	    ret = 0;
    }
    RSA_freebn(out);

    return ret;
}
//base 64 解密
#define CHAR64(c) (((c) < 0 || (c) > 127) ? -1 : index_64[(c)])
static int app_base64decode(const char *in, unsigned inlen, char *out)
{
    unsigned  len = 0, lup;
    int    c1,c2,c3,c4;
	static char     index_64[128] = {
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
			52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
			-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
			15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
			-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
			41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
	};
	
	/* xxx these necessary? */
    if (in[0] == '+' && in[1] == ' ')
        in += 2;
	
    if (*in == '\0')
        return 0;
	
    for (lup = 0; lup < inlen / 4; lup++)
    {
        c1 = in[0];
        if (CHAR64(c1) == -1)
            return 0;
        c2 = in[1];
        if (CHAR64(c2) == -1)
            return 0;
        c3 = in[2];
        if (c3 != '=' && CHAR64(c3) == -1)
            return 0;
        c4 = in[3];
        if (c4 != '=' && CHAR64(c4) == -1)
            return 0;
        in += 4;
        *out++ = (CHAR64(c1) << 2) | (CHAR64(c2) >> 4);
        ++len;
        if (c3 != '=')
        {
            *out++ = ((CHAR64(c2) << 4) & 0xf0) | (CHAR64(c3) >> 2);
            ++len;
            if (c4 != '=')
            {
                *out++ = ((CHAR64(c3) << 6) & 0xc0) | CHAR64(c4);
                ++len;
            }
        }
    }
	
    *out = 0; 
	return len;
}


int rsaVerifySign(
	unsigned char *public_key_blob,
	unsigned long        public_key_blob_len,
    unsigned char *in_data,      
	unsigned long        in_data_len,		   
    unsigned char *in_Signature,   
	unsigned long        in_Signature_len)
{
	char signBuf[256];
    struct RSAKey *rsa=NULL;
	int re=0;
	unsigned long i=0;
	if(sizeof(signBuf)<in_Signature_len)
	{
		re = 0;
		goto err;
	}
	if(!public_key_blob || !in_data || !in_Signature)
	{
		re = 0;
		goto err;
	}

    rsa = rsa2_newkey_ex(public_key_blob, public_key_blob_len);
	if(rsa==NULL)
	{   
		re = 0;
		goto err;
	}
	memset(signBuf, 0 ,sizeof(signBuf));
	for(i=0;i<in_Signature_len; i++)
	{
		signBuf[i] = in_Signature[in_Signature_len-1 - i];
	}


    re = rsa2_verifysig(rsa,signBuf,
				   in_Signature_len,
				  in_data,
		          in_data_len
				  );
err:
	if(rsa)
	{
		if(rsa->exponent)
		{
			RSA_freebn(rsa->exponent);
		}
		
		if (rsa->modulus)
		{
			RSA_freebn(rsa->modulus);
		}
		sfree(rsa);
	}
	return re;   
}

int  rsaVerifySignByBase64EncodePublicKeyBlob(
	unsigned char *public_key_blob,
	unsigned long  public_key_blob_len,
	unsigned char *in_data,      
	unsigned long  in_data_len,		   
	unsigned char *in_Signature,   
	unsigned long  in_Signature_len)
{
	unsigned char buf[256];                
	int len;
	if(public_key_blob_len> sizeof(buf))
	{
		goto error_exit;
	}
	len = app_base64decode(public_key_blob,public_key_blob_len,buf);
	if(len<=0)
	{
		goto error_exit;
	}
	return  rsaVerifySign(buf,
						  len,
						  in_data,      
						  in_data_len,		   
						  in_Signature,   
						  in_Signature_len);

error_exit:
	return 0;
}


#ifdef TEST_RSA


char    publickeyBuf2[] ="BgIAAACkAABSU0ExAAQAAAEAAQBvDl7svGyTKAaVCkaaGzMOkK1rdQiS1v3SyrVRVE/ee8N/9POQRxYIzr2+hARJUo31SuNjFleoge2NaIiuYEtIYjSmxR7NbLkx+nIztZqmhZy9qNbjsPNnmEMBtsMm1iFIqFQgFg61i+sAV3FW7hvXbZCoCWI3J7/JsslPEsO07A==";
int     publicKeyLen2 = sizeof(publickeyBuf2)-1;

char	dataBuf[] = "12345678";
int  	dataLen = sizeof(dataBuf) - 1;

char	rsaSignBuf[128] = {
	    0xa3, 0xd9, 0x32, 0xca, 0xd3, 0x71, 0x47, 0x25,  0xdd, 0x2c, 0xa9, 0xab, 0x08, 0xce, 0x26, 0x81,
		0x86, 0xc9, 0x3d, 0xe8, 0x5f, 0x35, 0x9d, 0xa5,  0xc1, 0x2c, 0x83, 0x42, 0x51, 0x91, 0xb9, 0x35,
		0x44, 0x3c, 0x48, 0x3f, 0x94, 0xda, 0x5f, 0x3d,  0x6c, 0xb5, 0xd7, 0x3b, 0x32, 0x6d, 0x77, 0x12,
		0x45, 0x10, 0xe0, 0xba, 0xe1, 0xcb, 0x1a, 0x16,  0xec, 0x49, 0xb0, 0x1c, 0x21, 0xbc, 0x64, 0x34,
		0x0d, 0x60, 0x98, 0xc0, 0xe1, 0xd4, 0x3d, 0xd9,  0xb7, 0x90, 0xff, 0x94, 0xd5, 0x14, 0xa2, 0x70,
		0x14, 0xae, 0xad, 0x49, 0x71, 0x1d, 0x66, 0x07,  0xff, 0x86, 0x08, 0xf5, 0xe0, 0x28, 0xe3, 0x45,
		0x0b, 0x9e, 0x2d, 0xa0, 0x6a, 0x2a, 0xc7, 0xb7,  0xf4, 0xb8, 0xeb, 0x7d, 0x75, 0x79, 0x68, 0xa5,
		0xee, 0x22, 0xe2, 0x78, 0xc3, 0x5c, 0x76, 0x4c,  0xb8, 0x5f, 0x8f, 0xf4, 0xcf, 0x9b, 0x63, 0x94
};

int 	rsaSignLen = 128;

int testRsaSign()
{

	if(!rsaVerifySignByBase64EncodePublicKeyBlob(
		publickeyBuf2,
		publicKeyLen2,
		dataBuf,
		dataLen,
		rsaSignBuf,
		rsaSignLen))
	{
		printf("rsa VerifySign error \n");
	}else
	{
		printf("rsa VerifySign OK \n");
	}
	printf("end rsa verify sign\n");
	

}



void main(void)
{		
	testRsaSign();	

    return ;
}

#endif























