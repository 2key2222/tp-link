
#ifndef __RSA_H__
#define __RSA_H__

#ifdef __cplusplus
extern "C" {
#endif

int  rsaVerifySignByBase64EncodePublicKeyBlob(
	unsigned char *public_key_blob,
	unsigned long  public_key_blob_len,
	unsigned char *in_data,      
	unsigned long  in_data_len,		   
	unsigned char *in_Signature,   
	unsigned long  in_Signature_len);
	

int  rsaVerifySign(
     unsigned char *public_key_blob,
	 unsigned long  public_key_blob_len,
	 unsigned char *in_data,      
  	 unsigned long  in_data_len,		   
	 unsigned char *in_Signature,   
	 unsigned long  in_Signature_len);

#ifdef __cplusplus
}
#endif

#endif	/* __DSA_H__ */

