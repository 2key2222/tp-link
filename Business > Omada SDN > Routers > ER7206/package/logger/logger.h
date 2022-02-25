/*! Copyright(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 *\file     logger.h
 *\brief    
 *\details  
 *
 *\author   Yuan Fengjia
 *\version  0.0.1
 *\date     12Dec15
 *
 *\warning    
 *
 *\history  \arg    0.0.1, 12Dec15, Yuan Fengjia, Create the file.
 */


#ifndef __LOGGER_H__
#define __LOGGER_H__
/**************************************************************************************************/
/*                                      CONFIGURATIONS                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/
#ifdef __cplusplus
extern "C" 
{
#endif  /* __cplusplus */

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/
#define LOGGER_MODULE_ID_COMMON         (0)
#define LOGGER_MODULE_ID_AC             (10)
#define LOGGER_MODULE_ID_ACCOUNT_MNGT   (11)
#define LOGGER_MODULE_ID_ADCAST         (12)
#define LOGGER_MODULE_ID_BALANCE        (13)
#define LOGGER_MODULE_ID_BEHAVIOR_CTL   (14)
#define LOGGER_MODULE_ID_CMXDDNS        (15)
#define LOGGER_MODULE_ID_DHCP_CLIENT    (16)
#define LOGGER_MODULE_ID_DHCP_SERVER    (17)
#define LOGGER_MODULE_ID_DYNDDNS        (18)
#define LOGGER_MODULE_ID_FIREWALL       (51)
#define LOGGER_MODULE_ID_IPSEC          (19)
#define LOGGER_MODULE_ID_LOGGER         (20)
#define LOGGER_MODULE_ID_PHDDNS         (21)
#define LOGGER_MODULE_ID_PORTAL         (22)
#define LOGGER_MODULE_ID_PPP            (23)
#define LOGGER_MODULE_ID_REMOTE_MNGT    (24)
#define LOGGER_MODULE_ID_TIME_MNGT      (71)
#define LOGGER_MODULE_ID_TIME_SETTING   (27)
#define LOGGER_MODULE_ID_UPNP           (28)
#define LOGGER_MODULE_ID_TPLOGIN        (72)
#define LOGGER_MODULE_ID_SWITCH         (25)
#define LOGGER_MODULE_ID_L2TP           (80)
#define LOGGER_MODULE_ID_PPTP           (81)
#define LOGGER_MODULE_ID_PPPOE_CLIENT   (82)
#define LOGGER_MODULE_ID_LINE_BACKUP    (29)
#define LOGGER_MODULE_ID_BPALOGIN       (30)

#define LOGGER_PARAM_END       (0)
#define LOGGER_PARAM_STRING    (1)
#define LOGGER_PARAM_INT32     (2)
#define LOGGER_PARAM_UINT32    (3)
#define LOGGER_PARAM_UINT32HEX (4)
#define LOGGER_PARAM_IPV4      (5)

#ifndef __KERNEL__
extern void 
loggervp(unsigned int module_id, unsigned int info_id,
                    unsigned int pid, const char *argv[]);
#endif
extern void 
loggerv(unsigned int module_id, unsigned int info_id,
                   const char *argv[]);
extern void 
loggerk_reg(unsigned int module_id, unsigned int info_id, ...);

/*extern void 
_loggerk_reg(unsigned int module_id, unsigned int info_id, ...);*/

#define logger_reg(module_id, info_id, ...)                   \
    loggerk_reg(module_id, info_id, ##__VA_ARGS__, LOGGER_PARAM_END)

#define LOGGER_REG(info_id, ...)                        \
    logger_reg(LOG_PROJ_ID, info_id, ##__VA_ARGS__)
/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      FUNCTIONS                                                 */
/**************************************************************************************************/


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __LOGGER_H__ */

