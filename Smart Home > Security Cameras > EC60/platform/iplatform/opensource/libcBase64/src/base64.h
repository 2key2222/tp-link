
#ifndef __BASE64_H__
#define __BASE64_h__

#ifdef __cplusplus
extern "C" {
#endif

int base64_decode(char *in, char *out, int out_len);

/* data to be encoded specified by `in' must be terminated with '\0' */
int base64_encode(char *in, char *out, int out_len);

/* data to be encoded specified by `in' can be binary data, 
 * that's to say, '\0' can appear in the data */
int base64_encode_bin(char *in, int in_len, char *out, int out_len);

#ifdef __cplusplus
}
#endif

#endif // __BASE64_H__
