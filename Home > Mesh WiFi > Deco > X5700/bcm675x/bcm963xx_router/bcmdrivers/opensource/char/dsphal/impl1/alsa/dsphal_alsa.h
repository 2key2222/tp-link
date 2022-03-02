/****************************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:standard
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
#ifndef _DSPHAL_PCM_H
#define _DSPHAL_PCM_H

#include <dsphal.h>
#include <linux/list.h>

/****************************************************************************
* Typedefs and Constants
****************************************************************************/
#define NO_PITCH 100000


#define DH_ALSA_CAPTURE_MASK   0x0002
#define DH_ALSA_PLAYBACK_MASK  0x0001

#define DH_ALSA_EG_SHIFT       0x0003
#define DH_ALSA_IN_SHIFT       0x0002
#define DH_ALSA_CAPTURE_SHIFT  0x0001
#define DH_ALSA_PLAYBACK_SHIFT 0x0000

#define MIXER_ADDR_MASTER    0
#define MIXER_ADDR_LINE        1
#define MIXER_ADDR_MIC        2
#define MIXER_ADDR_SYNTH    3
#define MIXER_ADDR_CD        4
#define MIXER_ADDR_LAST        4

#define ASSERT(x)                                                       \
do {    if (x) break;                                                   \
        printk(KERN_EMERG "### ASSERTION FAILED %s: %s: %d: %s\n",      \
               __FILE__, __func__, __LINE__, #x); dump_stack(); BUG();  \
} while (0)


struct dummy_timer_ops {
    int (*create)(struct snd_pcm_substream *);
    void (*free)(struct snd_pcm_substream *);
    int (*prepare)(struct snd_pcm_substream *);
    int (*start)(struct snd_pcm_substream *);
    int (*stop)(struct snd_pcm_substream *);
    snd_pcm_uframes_t (*pointer)(struct snd_pcm_substream *);
};

#define get_dummy_ops(substream) \
    (*(const struct dummy_timer_ops **)(substream)->runtime->private_data)

struct dummy_model {
    const char *name;
    int (*playback_constraints)(struct snd_pcm_runtime *runtime);
    int (*capture_constraints)(struct snd_pcm_runtime *runtime);
    u64 formats;
    size_t buffer_bytes_max;
    size_t period_bytes_min;
    size_t period_bytes_max;
    unsigned int periods_min;
    unsigned int periods_max;
    unsigned int rates;
    unsigned int rate_min;
    unsigned int rate_max;
    unsigned int channels_min;
    unsigned int channels_max;
};

struct snd_dummy {
    struct snd_card *card;
    struct dummy_model *model;
    struct snd_pcm *pcm;
    struct snd_pcm_hardware pcm_hw;
    spinlock_t mixer_lock;
    int mixer_volume[MIXER_ADDR_LAST+1][2];
    int capture_source[MIXER_ADDR_LAST+1][2];
    int iobox;
    struct snd_kcontrol *cd_volume_ctl;
    struct snd_kcontrol *cd_switch_ctl;
};

/*
 * system timer interface
 */

struct alsa_dsp_pcm {
    /* ops must be the first item */
    const struct dummy_timer_ops *timer_ops;
    spinlock_t lock;
    struct timer_list timer;
    unsigned long base_time;
    unsigned int frac_pos;            /* fractional sample position (based HZ) */
    unsigned int frac_period_rest;
    unsigned int frac_buffer_size;    /* buffer_size * HZ */
    unsigned int frac_period_size;    /* period_size * HZ */
    unsigned int rate;
    int elapsed;
    struct snd_pcm_substream *substream;
    struct dh_alsa_chan_cfg *cfg;
    struct list_head open_list;
    struct list_head active_list;
};

struct dh_alsa_chan_priv
{
    int chan_id;
    volatile unsigned long valid;
    struct task_struct *tick_task;
    struct dhchancfg *cfg;
    struct list_head open_alsa_pcm_list;
    struct list_head active_alsa_pcm_list;
};

struct dh_alsa_pcm_substream {
    atomic_t valid;
    struct snd_pcm_substream *substream;
};

/****************************************************************************
* Function Definitions
****************************************************************************/
int  alsa_card_dummy_init(void);
void alsa_card_dummy_exit(void);

#endif /* _DSPHAL_PCM_H */
