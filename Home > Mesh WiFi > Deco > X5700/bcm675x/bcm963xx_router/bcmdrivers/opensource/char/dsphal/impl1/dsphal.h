/****************************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:voice
 * 
 *    Copyright (c) 2015 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 *
 ***************************************************************************/
#ifndef _DSPHAL_H
#define _DSPHAL_H

#ifdef _CFE_
#include <cfe_env.h>
#else
#include <generated/autoconf.h>
#include <linux/cdev.h>
#include <linux/circ_buf.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/bcm_colors.h>
#endif

#include <boardparms.h>
#include <boardparms_voice.h>
#include <bcm_dsphal.h>


/****************************************************************************
* Typedefs and Constants
****************************************************************************/

/*
 * Since we are using tricks to make our circular buffers quicker, the buffer
 * sizes must be powers of 2. From the HAL's perspective this doesn't matter
 * since these buffers must simply be big enough to store currently 2 frames
 * worth of samples (since we ideally would like to double buffer).
 *
 * Note that each sample is 16-bits and we use double-buffering, so multiply
 * the number of samples rounded up to the nearest 2's power by 4.
 */
#define BUF_SIZE         (512 * sizeof(int16_t))
#define BUF_SIZE_WB      (512 * sizeof(int32_t))

/* How many time stats to keep. Must be a power of 2 */
#define DEBUG_STATS_RINGBUF_SIZE    256

#define CLRbr          BCMCOLOR("\e[0;31;1m")
#define DHLOG_PRINT(level,x,...)    do { \
     if(level <= loglevel)               \
        printk(x, ##__VA_ARGS__);        \
   } while(0)
#define DHLOG_ALERT(x,...)   DHLOG_PRINT(1, KERN_ALERT    CLRyr "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)
#define DHLOG_CRIT(x,...)    DHLOG_PRINT(2, KERN_CRIT     CLRbr "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)
#define DHLOG_ERR(x,...)     DHLOG_PRINT(3, KERN_ERR      CLRr  "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)
#define DHLOG_WARNING(x,...) DHLOG_PRINT(4, KERN_WARNING  CLRy  "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)
#define DHLOG_NOTICE(x,...)  DHLOG_PRINT(5, KERN_NOTICE   CLRc  "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)
#define DHLOG_INFO(x,...)    DHLOG_PRINT(6, KERN_INFO     CLRm  "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)
#define DHLOG_DEBUG(x,...)   DHLOG_PRINT(7, KERN_DEBUG    CLRg  "[DSPHAL] " CLRnorm x, ##__VA_ARGS__)

#define DH_INVALID     0xCAFEBEEF

struct med_buf
{
   char     *buf;
   int       size;
   atomic_t  head;
   atomic_t  tail;
   int       watermark;

};

/* Channel configuration structure */
struct dhchancfg
{
   unsigned int        id;
   unsigned int        enabled;
   unsigned int        initialized;
   wait_queue_head_t   queue;
   spinlock_t          lock;

   /* internal channel configuration */
   enum dh_type        type;
   enum dh_intf        interface;
   enum dh_sample_rate rate;
   unsigned int        clearchan;

   /* index of channel in voice boardparms */
   int                 vp_dev;
   int                 vp_chan;

   /* Egress and ingress buffers */
   struct med_buf      eg_buf;
   struct med_buf      ing_buf;

   void                (*direct_eg)(struct dhchancfg *cfg);

   /* Interface-specific data */
   void               *priv;

};

struct dhpriv
{
   struct dhchancfg *chancfg;

   /* Set to 1 if this file handles the DECT status */
   unsigned int      dect_handle;
};

struct dhdev
{
   struct cdev     dh_cdev;  /* driver char dev struct */
   struct device  *device;
   struct class   *class;
   atomic_t        open_count;

};

struct ioctl_hdlr
{
   unsigned int  cmd;
   long          (*hdlr)(struct dhpriv* priv, unsigned long arg);
   unsigned int  needs_lock;
};

struct intf_hdlrs
{
   int (*init)(void);
   int (*deinit)(void);
   int (*config)(struct dhchancfg *cfg);
   int (*deconfig)(struct dhchancfg *cfg);
   int (*open)(struct dhchancfg *cfg, int count);
   int (*release)(struct dhchancfg *cfg, int count);
};

struct isr_hdlrs
{
   void (*idle)(int idle);
};

enum direction
{
   DH_EGRESS,
   DH_INGRESS
};

enum ticksource
{
   /* Tick sources from lowest to highest priority */
   DH_TICK_SOURCE_NONE,
   DH_TICK_SOURCE_TIMER,
   DH_TICK_SOURCE_IUDMA,
   DH_TICK_SOURCE_DECT,

   DH_TICK_SOURCE_MAX
};

struct map
{
   long item;
   long value;
};

struct map_ptr
{
   long  item;
   void* ptr;
};

struct dma_addr
{
   char*       cpu; /* virtual address */
   dma_addr_t  dma; /* physical address */
};


struct debug_time_ringbuf
{
   unsigned long time[DEBUG_STATS_RINGBUF_SIZE];
   atomic_t      head;
};

struct debug_stats
{
   uint64_t total_overruns;
   uint64_t total_underruns;
   uint64_t dsp_underruns;
   uint64_t dsp_underruns_peak;
   uint64_t hal_tick_count;
   uint64_t dsp_tick_count;
   uint64_t isr_counts[DH_TICK_SOURCE_MAX];
   uint64_t dma_realigns[DH_TICK_SOURCE_MAX];
   uint64_t dma_restarts[DH_TICK_SOURCE_MAX];
#if defined(CONFIG_BCM96858)
   unsigned int tx_underflow_counter;
   unsigned int rx_overflow_counter;
#endif
   /* stats after this point are extended and will be disabled when the
    * enable_extended_stats variable is 0 */
   unsigned int              enable_extended_stats;
   struct debug_time_ringbuf hal_tick;
   struct debug_time_ringbuf dsp_start;
   struct debug_time_ringbuf dsp_end;
};


/****************************************************************************
* Externed Variables
****************************************************************************/
extern struct dhdev       dhdev;
extern unsigned int       loglevel;
extern VOICE_BOARD_PARMS  vp;
extern struct dhchancfg   chan_cfg[BP_MAX_VOICE_CHAN];
extern atomic_t           open_cnt[DSPHAL_INTF_MAX];
extern unsigned int       num_ept;

extern unsigned int       dsp_rate;
extern volatile int       tick_enabled;
extern enum ticksource    tick_owner;
extern unsigned int       tick_rate;
extern wait_queue_head_t  tick_q;
extern atomic_t           tick;
extern struct debug_stats debug_stats;

extern const struct ioctl_hdlr ioctl_hdlr_table[];

/* Interface function handlers */
extern struct intf_hdlrs pcm_hdlr_table;
extern struct intf_hdlrs apm_hdlr_table;
extern struct intf_hdlrs dect_hdlr_table;
extern struct intf_hdlrs alsa_hdlr_table;

/* ISR control handlers */
extern struct isr_hdlrs dect_isr_table;
extern struct isr_hdlrs iudma_isr_table;


/****************************************************************************
* Functions
****************************************************************************/
int  dh_init_interfaces(void);
int  dh_deinit_interfaces(void);
void dh_idle_interfaces(int idle);
int  dh_configure_channel(int dev, int chan);
int  dh_deconfigure_channel(int id);
int  dh_enable_channel(int id);
int  dh_disable_channel(int id);
void dh_intf_open_handler(struct dhchancfg *cfg);
void dh_intf_release_handler(struct dhchancfg *cfg);
void dh_copy_ingress(struct dhchancfg *cfg, char *buf, size_t size);
void dh_copy_ingress_out(struct dhchancfg *cfg, char *buf, size_t size);
void dh_copy_egress(struct dhchancfg *cfg, char *buf, size_t size);
int  dh_get_boardparms(void);
long dh_map(const struct map *map, long item);
void* dh_map_ptr(const struct map_ptr *map, long item);
void dh_swap_word (uint16_t* bufp, int size);
void dh_swap_byte (uint16_t* bufp, int size);
void dh_reg_tick_source(enum ticksource source, unsigned int rate);
void dh_unreg_tick_source(enum ticksource source);
void dh_tick(enum ticksource source);

void dh_debug_init(void);
void dh_debug_deinit(void);
void dh_debug_setup_channel(struct dhchancfg *cfg);
void dh_debug_close_channel(struct dhchancfg *cfg);
void dh_debug_egress(struct dhchancfg *cfg, char *buf, size_t size);
void dh_debug_ingress(struct dhchancfg *cfg, char *buf, size_t size);
void dh_debug_bufslip(struct dhchancfg *cfg, enum direction dir);
void dh_debug_record_time(struct debug_time_ringbuf *buf);
void dh_debug_isr(enum ticksource src);
void dh_debug_reg_mem(void *mem, int size, int groupsize, char *namefmt, ...);
void dh_debug_unreg_mem(void *mem);
int alsa_tick_handler(void);

#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
int dh_add_boardparm_channel(void);
#endif
#endif /* _DSPHAL_H */
