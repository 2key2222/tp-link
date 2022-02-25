/******************************************************************************
*
* Copyright (c) 2010 TP-LINK Technologies CO.,LTD.
* All rights reserved.
*
* file name  :   flashAppFsImage.c
* version    :   V1.0
* description:   定义解析镜像的接口.
*
* author     :   LiuZenglin <LiuZenglin@tp-link.net>
* data       :   06/25/2013
*
* history    :
* 01   06/25/2013  LiuZenglin     Create.
*
* refresh option:
* 1、更新switch.tp 和 webImage.z
* 2、不删除原内部区的项，直接写入镜像中的内部项，如果有则覆盖，底层会处理
*    profile中mac和RSA的；

* 4、删除内部区中的除gev和profile的项，删除非必须的gev项，再写入镜像中的内部项；
*
* 记镜像中版本号为V1 A.B.C, flash中版本号为V2 A.B.C
* if ((A1 == A1) && (B1 <= B2) && (C1 <= C2))   执行操作1
* if ((A1 == A1) && (B1 <= B2) && (C1 > C2))    执行操作1和操作2
* if ((A1 == A1) && (B1 > B2))                  执行操作2和操作3
* if (A1 != A1)                                 执行操作3和操作4
*
******************************************************************************/
#include<common.h>
#include<vsprintf.h>
#include <tplink/flashApp.h>
#include <tplink/flashAppInner.h>
#include <tplink/flashAppInnerGev.h>
#include <tplink/flashAppInnerProfile.h>
#include <tplink/flashAppFsImage.h>
#include <linux/ctype.h>
#include <tplink/flashUtil.h>

int flash_fs_image_debug = 0;
    
#define DBG(arg...) do{if(flash_fs_image_debug){printf("%s,%d:",__FUNCTION__, __LINE__);printf(arg);}}while(0)


/* 签名信息长度 */
#define RSA_SIGN_LEN	(128)
/* 用于检验升级文件签名的公钥文件 */
static char pubKey[] = "BgIAAACkAABSU0ExAAQAAAEAAQBhVXK3wF79A6cXXFu0Y0wKz0dPQWi2dWPE7p8eY9e6PAqc5BBTQPxi2/N1OotrUN11Q6cBXA0gmflRusUiJtdARng43tSWz2pZueskCC5kH9/+1/ACi2ZY1WlK5TVu5Bh0YCzAfvlmsbuPjk/W4S3Jco+ISDOrpF5wwuxlCHI2vQ==";
/*
 * 该函数用于检查升级文件的签名是否正确
 * note:
 * 1,签名信息位于升级文件的最后128bytes
 * 2,签名信息生成规则:对整个升级文件计算md5,根据md5值计算128bytes的RSA签名信息
 * 
*/



