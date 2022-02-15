/*!Copyright(c) 2013-2014 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 *\file     xt_pctl.h
 *\brief    kernel/netfilter part for http host filter. 
 *
 *\author   Hu Luyao
 *\version  1.0.0
 *\date     23Dec13
 *
 *\history  \arg 1.0.0, creat this based on "multiurl" mod from soho.  
 *                  
 */
/***************************************************************************/
/*                      CONFIGURATIONS                   */
/***************************************************************************/
#ifndef _XT_PCTL_H_
#define _XT_PCTL_H_


/***************************************************************************/
/*                      INCLUDE_FILES                    */
/***************************************************************************/


/***************************************************************************/
/*                      DEFINES                      */
/***************************************************************************/
#define     PCTL_OWNER_NUM                    (4)
#define     PCTL_OWNER_ID_ALL                 0xffff

#define     PCTL_URL_NUM                        (32)
#define     PCTL_URL_LEN                        (32)
#define     PCTL_MAX_DNS_SIZE                   (256)

#define     TRUE                                (1)
#define     FALSE                               (0)


/***************************************************************************/
/*                      TYPES                            */
/***************************************************************************/
typedef struct _xt_pctl_info
{
    int id; /* owner id */

    bool blocked;    /* paused */

    bool workday_limit;
    unsigned int workday_time;

    bool workday_bedtime;
    unsigned int workday_begin;
    unsigned int workday_end;

    bool weekend_limit;
    unsigned int weekend_time;

    bool weekend_bedtime;
    unsigned int weekend_begin;
    unsigned int weekend_end;

    int num; 
    char hosts[PCTL_URL_NUM][PCTL_URL_LEN]; /* hosts */

} xt_pctl_info;

/***************************************************************************/
/*                      VARIABLES                        */
/***************************************************************************/


/***************************************************************************/
/*                      FUNCTIONS                        */
/***************************************************************************/
#endif