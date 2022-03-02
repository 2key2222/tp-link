/* this is an automatically generated file.  Do not modify. */
#define BRCM_DHCP_CONFIG_KEY    "893069998"
static int dhcpEncryptCfgFile(char *buff, int buffLen, const char *key) { 
    int i, k, keyLen = strlen(key);                                       
    for (i = 0; i < buffLen; i++) {                                       
        for (k = 0; k < keyLen; k++) {                                    
            buff[i] = buff[i] ^ key[k];                                   
        }                                                                 
    }                                                                     
    return 0;                                                             
}                                                                         
