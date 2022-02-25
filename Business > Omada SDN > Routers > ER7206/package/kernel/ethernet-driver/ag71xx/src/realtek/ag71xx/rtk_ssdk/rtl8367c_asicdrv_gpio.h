#ifndef _RTL8367C_ASICDRV_GPIO_H_
#define _RTL8367C_ASICDRV_GPIO_H_

#include "rtl8367c_asicdrv.h"


#define RTL8367C_GPIOPINNO                  62
#define RTL8367C_GPIOPINMAX                 (RTL8367C_GPIOPINNO-1)
#define RTL8367C_ACLGPIOPINNO               13

extern ret_t rtl8367c_getAsicGpioInput(rtk_uint32 gpioPin, rtk_uint32* pGpioInput);
extern ret_t rtl8367c_setAsicGpioOutput(rtk_uint32 gpioPin, rtk_uint32 gpioOutput);
extern ret_t rtl8367c_getAsicGpioOutput(rtk_uint32 gpioPin, rtk_uint32* pGpioOutput);
extern ret_t rtl8367c_setAsicGpioEn(rtk_uint32 gpioPin, rtk_uint32 gpioEn);
extern ret_t rtl8367c_getAsicGpioEn(rtk_uint32 gpioPin, rtk_uint32* pGpioEn);
extern ret_t rtl8367c_setAsicGpioMode(rtk_uint32 gpioPin, rtk_uint32 mode);
extern ret_t rtl8367c_getAsicGpioMode(rtk_uint32 gpioPin, rtk_uint32 *pMode);
extern ret_t rtl8367c_setAsicGpioAclEnClear(rtk_uint32 gpioPin);
extern ret_t rtl8367c_getAsicGpioAclEnClear(rtk_uint32 gpioPin, rtk_uint32* pGpioEn);

#endif /*#ifndef _RTL8367C_ASICDRV_GPIO_H_*/

