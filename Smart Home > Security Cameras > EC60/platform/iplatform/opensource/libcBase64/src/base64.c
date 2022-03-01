#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char base64_index[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

int base64_decode(char *in, char *out, int out_len)
{
	unsigned char byte1 = 0; 
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	unsigned char byte4 = 0;
	int in_len = 0;
	
	in_len = ((NULL == in)? 0 : strlen(in));

	if (!in || !out || in_len & 0x11) {
		return -1;
	}

	while(in_len > 0) {		
		byte1 = (unsigned char)(strchr(base64_index, *(in++)) - base64_index);
		byte2 = (unsigned char)(strchr(base64_index, *(in++)) - base64_index);
		byte3 = (unsigned char)(strchr(base64_index, *(in++)) - base64_index);
		byte4 = (unsigned char)(strchr(base64_index, *(in++)) - base64_index);
	
		if(byte1 > 64 || byte2 > 64 || byte3 > 64 || byte4 > 64) {
			return -1;
		}

		if(out_len < 1) {
			return -1;
		}
		*(out++) = ((byte1 << 2) & 0xFC) | ((byte2 >> 4) & 0x03);
		out_len--;
		if(64 == byte3) {
			break;
		}

		if(out_len < 1) {
			return -1;
		}
		*(out++) = ((byte2 << 4) & 0xF0) | ((byte3 >> 2) & 0x0F);
		out_len--;
		if(64 == byte4) {
			break;
		}

		if(out_len < 1) {
			return -1;
		}
		*(out++) = ((byte3 << 6) & 0xC0 ) | ((byte4) & 0x3F);
		out_len--;
		
		in_len -= 4;
	}

	*out = 0;
	return 0;
}

int base64_encode_bin(char *in, int in_len, char *out, int out_len)
{
	unsigned char byte1 = 0;  /*the first char*/
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	unsigned char byte4 = 0;
	
	if (NULL == in || NULL == out || out_len < in_len) {
		return -1;
	}

	while (in_len > 0) {
		if (out_len < 4) {
			return -1;
		}
		
		byte1 = 0x3F & ((*(in) & 0xFC) >> 2);   /*byte1[0]-byte1[5] to byte1[0]-byte1[5]*/
		byte2 = 0x30 & ((*(in++) & 0x03) << 4); /*byte1[6]-byte1[7] to byte2[0]-byte2[1]*/
		byte3 = 64;
		byte4 = 64;

		if (in_len > 1)	{
			byte2 |= (0x0F & ((*(in) & 0xF0) >> 4));
			byte3 = (0x3C & ((*(in++) & 0x0F) << 2));
		}
		if (in_len > 2)	{
			byte3 |= (0x03 & ((*(in) & 0xC0) >> 6));
			byte4 = (0x3F & ((*(in++) & 0x3F ))); 
		}

		*out++ = base64_index[byte1];
		*out++ = base64_index[byte2];
		*out++ = base64_index[byte3];
		*out++ = base64_index[byte4];
		
		out_len -= 4;
		in_len -= 3;
	}
	
	*out = 0;
	return 0;
}

int base64_encode(char *in, char *out, int out_len)
{
	if (NULL == in) {
		return -1;
	}
	return base64_encode_bin(in, strlen(in), out, out_len);
}

