/******************************************************************************
 *
 * Copyright (c) 2013 TP-LINK Technologies CO.,LTD.
 * All rights reserved.
 *
 * FILE NAME  :    DESLIB.h
 * VERSION    :    1.0
 * DESCRIPTION:    interfaces of DES encryption/decryption
 *
 * 01	30/9/2013	zj	create
 ******************************************************************************/

#ifndef	__DESLIB_H__
#define	__DESLIB_H__

int DES_Encrypt(char *plainFile, char *keyStr,char *cipherFile);
int DES_Decrypt(char *cipherFile, char *keyStr,char *plainFile);

#endif

