/*
 * aw9163.c   aw9163 touch key module
 *
 * Version: v1.1.4
 *
 * Copyright (c) 2017 AWINIC Technology CO., LTD
 *
 *  Author: Nick Li <liweilei@awinic.com.cn>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/firmware.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/debugfs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/regmap.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/hrtimer.h>
//#include <linux/wakelock.h>
#include <linux/mutex.h>
#include <linux/cdev.h>
#include <linux/leds.h>
#include <board.h>
#include <boardparms.h>
#include <bcm_intr.h>
#include "aw9163.h"
#include "aw9163_reg.h"
#include "aw9163_para.h"


/******************************************************
 *
 * Marco
 *
 ******************************************************/
#define AW9163_I2C_NAME "aw9163_ts"

#define AW9163_VERSION "v1.1.4"

#define AW_I2C_RETRIES 2
#define AW_I2C_RETRY_DELAY 2
#define AW_READ_CHIPID_RETRIES 5
#define AW_READ_CHIPID_RETRY_DELAY 2


/******************************************************
 *
 * aw9163 led parameter
 *
 ******************************************************/
/* The definition of each time described as shown in figure.
 *        /-----------\
 *       /      |      \
 *      /|      |      |\
 *     / |      |      | \-----------
 *       |hold_time_ms |      |
 *       |             |      |
 * rise_time_ms  fall_time_ms |
 *                       off_time_ms
 */
#define ROM_CODE_MAX 255

/*
 * rise_time_ms = 1500
 * hold_time_ms = 500
 * fall_time_ms = 1500
 * off_time_ms = 1500
 */
static int led_code_len = 7;
static int led_code[ROM_CODE_MAX] = {
  0xbf00,0x9f05,0xfffa,0x3c7d,0xdffa,0x3cbb,0x2,
};


 /******************************************************
 *
 * aw9163 i2c write/read
 *
 ******************************************************/
static int i2c_write(struct aw9163 *aw9163,
        unsigned char addr, unsigned int reg_data)
{
    int ret;
    u8 wbuf[512] = {0};

    struct i2c_msg msgs[] = {
        {
            .addr = aw9163->i2c->addr,
            .flags = 0,
            .len = 3,
            .buf = wbuf,
        },
    };

    wbuf[0] = addr;
    wbuf[1] = (unsigned char)((reg_data & 0xff00)>>8);
    wbuf[2] = (unsigned char)(reg_data & 0x00ff);

    ret = i2c_transfer(aw9163->i2c->adapter, msgs, 1);
    if (ret < 0) {
        pr_err("%s: i2c write error: %d\n", __func__, ret);
    }

    return ret;
}

static int i2c_read(struct aw9163 *aw9163,
        unsigned char addr, unsigned int *reg_data)
{
    int ret;
    unsigned char rbuf[512] = {0};
    unsigned int get_data;

    struct i2c_msg msgs[] = {
        {
            .addr = aw9163->i2c->addr,
            .flags = 0,
            .len = 1,
            .buf = &addr,
        },
        {
            .addr = aw9163->i2c->addr,
            .flags = I2C_M_RD,
            .len = 2,
            .buf = rbuf,
        },
    };

    ret = i2c_transfer(aw9163->i2c->adapter, msgs, 2);
    if (ret < 0) {
        pr_err("%s: i2c read error: %d\n", __func__, ret);
        return ret;
    }

    get_data = (unsigned int)(rbuf[0] & 0x00ff);
    get_data <<= 8;
    get_data |= (unsigned int)rbuf[1];

    *reg_data = get_data;

    return ret;
}

static int aw9163_i2c_write(struct aw9163 *aw9163,
         unsigned char reg_addr, unsigned int reg_data)
{
    int ret = -1;
    unsigned char cnt = 0;

    while(cnt < AW_I2C_RETRIES) {
        ret = i2c_write(aw9163, reg_addr, reg_data);
        if(ret < 0) {
            pr_err("%s: i2c_write cnt=%d error=%d\n", __func__, cnt, ret);
        } else {
            break;
        }
        cnt ++;
    }

    return ret;
}

static int aw9163_i2c_read(struct aw9163 *aw9163,
        unsigned char reg_addr, unsigned int *reg_data)
{
    int ret = -1;
    unsigned char cnt = 0;

    while(cnt < AW_I2C_RETRIES) {
        ret = i2c_read(aw9163, reg_addr, reg_data);
        if(ret < 0) {
            pr_err("%s: i2c_read cnt=%d error=%d\n", __func__, cnt, ret);
        } else {
            break;
        }
        cnt ++;
    }
    return ret;
}
#if 0
static int aw9163_i2c_write_bits(struct aw9163 *aw9163, 
         unsigned char reg_addr, unsigned int mask, unsigned int reg_data)
{
    unsigned int reg_val;

    aw9163_i2c_read(aw9163, reg_addr, &reg_val);
    reg_val &= mask;
    reg_val |= reg_data;
    aw9163_i2c_write(aw9163, reg_addr, reg_val);

    return 0;
}

static int aw9163_i2c_writes(struct aw9163 *aw9163,
        unsigned char reg_addr, unsigned char *buf, unsigned int len)
{
    int ret = -1;
    unsigned char *data;

    data = kmalloc(len+1, GFP_KERNEL);
    if (data == NULL) {
        pr_err("%s: can not allocate memory\n", __func__);
        return  -ENOMEM;
    }

    data[0] = reg_addr;
    memcpy(&data[1], buf, len);

    ret = i2c_master_send(aw9163->i2c, data, len+1);
    if (ret < 0) {
        pr_err("%s: i2c master send error\n", __func__);
    }

    kfree(data);

    return ret;
}
#endif

/******************************************************
 *
 * auto cali
 *
 ******************************************************/
#ifdef AW_AUTO_CALI
static int aw9163_auto_cali(struct aw9163 *aw9163)
{
    unsigned char i;
    unsigned char cali_dir[6];

    unsigned int buf[6];
    unsigned int ofr_cfg[6];
    unsigned int sen_num;
    unsigned int reg_val;

    if(aw9163->cali_num == 0){
        aw9163_i2c_read(aw9163, AW9163_REG_OFR1, &reg_val);
        ofr_cfg[0] = reg_val;
        aw9163_i2c_read(aw9163, AW9163_REG_OFR2, &reg_val);
        ofr_cfg[1] = reg_val;
        aw9163_i2c_read(aw9163, AW9163_REG_OFR3, &reg_val);
        ofr_cfg[2] = reg_val;
    }else{
        for(i=0; i<3; i++){
            ofr_cfg[i] = aw9163->old_ofr_cfg[i];
        }
    }

    aw9163_i2c_write(aw9163, AW9163_REG_MCR,0x3);
    for(i=0; i<6; i++){
        aw9163_i2c_read(aw9163, AW9163_REG_KDATA0+i, &reg_val);
        buf[i] = reg_val;
    }
    aw9163_i2c_read(aw9163, AW9163_REG_SLPR, &sen_num);

    for(i=0; i<6; i++) 
        aw9163->rawdata_sum[i] = (aw9163->cali_cnt==0)?
                (0) : (aw9163->rawdata_sum[i] + buf[i]);

    if(aw9163->cali_cnt==4){
        for(i=0; i<6; i++){
            if((sen_num & (1<<i)) == 0) {    // sensor used
                if((aw9163->rawdata_sum[i]>>2) < CALI_RAW_MIN){
                    if((i%2) && ((ofr_cfg[i>>1]&0xFF00)==0x1000)){
                        // 0x10** -> 0x00**
                        ofr_cfg[i>>1] = ofr_cfg[i>>1] & 0x00FF;
                        cali_dir[i] = 2;
                    }else if((i%2) && ((ofr_cfg[i>>1]&0xFF00)==0x0000)){
                        // 0x00**    no calibration
                        cali_dir[i] = 0;
                    }else if (((i%2)==0) && ((ofr_cfg[i>>1]&0x00FF)==0x0010)){
                        // 0x**10 -> 0x**00
                        ofr_cfg[i>>1] = ofr_cfg[i>>1] & 0xFF00;
                        cali_dir[i] = 2;
                    }else if (((i%2)==0) && ((ofr_cfg[i>>1]&0x00FF)==0x0000)){
                        // 0x**00 no calibration
                        cali_dir[i] = 0;
                    }else{
                        ofr_cfg[i>>1] = ofr_cfg[i>>1] - ((i%2)? (1<<8):1);
                        cali_dir[i] = 2;
                    }
                }else if((aw9163->rawdata_sum[i]>>2) > CALI_RAW_MAX){
                    if((i%2) && ((ofr_cfg[i>>1]&0xFF00)==0x1F00)){
                        // 0x1F** no calibration
                        cali_dir[i] = 0;
                    }else if (((i%2)==0) && ((ofr_cfg[i>>1]&0x00FF)==0x001F)){
                        // 0x**1F no calibration
                        cali_dir[i] = 0;
                    }else if((i%2) && ((ofr_cfg[i>>1]&0xFF00)==0x0000)){
                        // 0x00** -> 0x1000
                        ofr_cfg[i>>1] = ofr_cfg[i>>1] | 0x1000;
                        cali_dir[i] = 1;
                    }else if (((i%2)==0) && ((ofr_cfg[i>>1]&0x00FF)==0x0000)){
                        // 0x**00 -> 0x**10
                        ofr_cfg[i>>1] = ofr_cfg[i>>1] | 0x0010;
                        cali_dir[i] = 1;
                    }else{
                        ofr_cfg[i>>1] = ofr_cfg[i>>1] + ((i%2)? (1<<8):1);
                        cali_dir[i] = 1;
                    }
                }else{
                    cali_dir[i] = 0;
                }

                if(aw9163->cali_num > 0){
                    if(cali_dir[i] != aw9163->old_cali_dir[i]){
                        cali_dir[i] = 0;
                        ofr_cfg[i>>1] = aw9163->old_ofr_cfg[i>>1];
                    }
                }
            }
        }

        aw9163->cali_flag = 0;
        for(i=0; i<6; i++){
            if((sen_num & (1<<i)) == 0) {    // sensor used
                if(cali_dir[i] != 0){
                    aw9163->cali_flag = 1;
                }
            }
        }
        if((aw9163->cali_flag==0) && (aw9163->cali_num==0)){
            aw9163->cali_used = 0;
        }else{
            aw9163->cali_used = 1;
        }

        if(aw9163->cali_flag == 0){
            aw9163->cali_num = 0;
            aw9163->cali_cnt = 0;
            return 0;
        }

        // touch disbale
        aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
        reg_val &= 0xFFFD;
        aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);
        for(i=0; i<3; i++){
            aw9163_i2c_write(aw9163, AW9163_REG_OFR1+i, ofr_cfg[i]);
        }
        aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
        reg_val |= 0x0002;
        aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);

        if(aw9163->cali_num == (CALI_NUM -1)){    // no calibration
            aw9163->cali_flag = 0;
            aw9163->cali_num = 0;
            aw9163->cali_cnt = 0;
            return 0;
        }

        for(i=0; i<6; i++){
            aw9163->old_cali_dir[i] = cali_dir[i];
        }

        for(i=0; i<3; i++){
            aw9163->old_ofr_cfg[i] = ofr_cfg[i];
        }

        aw9163->cali_num ++;
    }

    if(aw9163->cali_cnt < 4){
        aw9163->cali_cnt ++;
    }else{
        aw9163->cali_cnt = 0;
    }

    return 0;
}
#endif

/******************************************************
 *
 * aw9163 touch
 *
 ******************************************************/
static void aw9163_cali_init(struct aw9163 *aw9163)
{
    aw9163->cali_flag = 1;
    aw9163->cali_num = 0;
    aw9163->cali_cnt = 0;
}

static void aw9163_normal_mode_init(struct aw9163 *aw9163)
{
    unsigned int reg_val;

    aw9163_cali_init(aw9163);

    // touch disbale
    aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
    reg_val &= 0xFFFD;
    aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);                      // disable chip

    // cap-touch config
    aw9163_i2c_write(aw9163, AW9163_REG_SLPR, AW9163_NORMAL_SLPR);          // touch key enable
    aw9163_i2c_write(aw9163, AW9163_REG_SCFG1, AW9163_NORMAL_SCFG1);        // scan time setting
    aw9163_i2c_write(aw9163, AW9163_REG_SCFG2, AW9163_NORMAL_SCFG2);        // bit0~3 is sense seting

    aw9163_i2c_write(aw9163, AW9163_REG_OFR1, AW9163_NORMAL_OFR1);          // offset
    aw9163_i2c_write(aw9163, AW9163_REG_OFR2, AW9163_NORMAL_OFR2);          // offset
    aw9163_i2c_write(aw9163, AW9163_REG_OFR3, AW9163_NORMAL_OFR3);          // offset

    aw9163_i2c_write(aw9163, AW9163_REG_THR2, AW9163_NORMAL_THR2);          // s1 press thred setting
    aw9163_i2c_write(aw9163, AW9163_REG_THR3, AW9163_NORMAL_THR3);          // s2 press thred setting
    aw9163_i2c_write(aw9163, AW9163_REG_THR4, AW9163_NORMAL_THR4);          // s3 press thred setting

    aw9163_i2c_write(aw9163, AW9163_REG_SETCNT, AW9163_NORMAL_SETCNT);      // debounce
    aw9163_i2c_write(aw9163, AW9163_REG_BLCTH, AW9163_NORMAL_BLCTH);        // base trace rate

    aw9163_i2c_write(aw9163, AW9163_REG_AKSR, AW9163_NORMAL_AKSR);          // aks
#ifndef AW_AUTO_CALI
    aw9163_i2c_write(aw9163, AW9163_REG_INTER, AW9163_NORMAL_INTER);        // signel click interrupt
#else
    aw9163_i2c_write(aw9163, AW9163_REG_INTER, 0x0080);                     // frame interrupt
#endif

    aw9163_i2c_write(aw9163, AW9163_REG_MPTR, AW9163_NORMAL_MPTR);          // long press time
    aw9163_i2c_write(aw9163, AW9163_REG_GDTR, AW9163_NORMAL_GDTR);          // gesture time setting
    aw9163_i2c_write(aw9163, AW9163_REG_GDCFGR, AW9163_NORMAL_GDCFGR);      // gesture key select
    aw9163_i2c_write(aw9163, AW9163_REG_TAPR1, AW9163_NORMAL_TAPR1);        // double click 1
    aw9163_i2c_write(aw9163, AW9163_REG_TAPR2, AW9163_NORMAL_TAPR2);        // double click 2
    aw9163_i2c_write(aw9163, AW9163_REG_TDTR, AW9163_NORMAL_TDTR);          // double click time
    aw9163_i2c_write(aw9163, AW9163_REG_IDLECR, AW9163_NORMAL_IDLECR);      // IDLE time setting

#ifndef AW_AUTO_CALI
    aw9163_i2c_write(aw9163, AW9163_REG_GIER, AW9163_NORMAL_GIER);          // gesture and double click enable
#else
    aw9163_i2c_write(aw9163, AW9163_REG_GIER, 0x0000);                      // gesture and double click disable
#endif

    // chip enable
    aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
    reg_val |= 0x0002;
    aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);                      // enable chip
}


/******************************************************
 *
 * irq
 *
 ******************************************************/
static void aw9163_interrupt_clear(struct aw9163 *aw9163)
{
    unsigned int reg_val;
    pr_info("%s enter\n", __func__);
    aw9163_i2c_read(aw9163, AW9163_REG_ISR, &reg_val);
    pr_info("%s: reg ISR=0x%x\n", __func__, reg_val);
}

static void aw9163_interrupt_setup(struct aw9163 *aw9163)
{
    pr_info("%s enter\n", __func__);
    aw9163_interrupt_clear(aw9163);
}

static irqreturn_t aw9163_irq(int irq, void *data)
{
    struct aw9163 *aw9163 = data;
#ifdef AW_AUTO_CALI
    unsigned int reg_val;
#endif
    unsigned int reg_kst;
    unsigned int reg_kisr;

    pr_info("%s enter\n", __func__);

#ifdef AW_AUTO_CALI
    if(aw9163->cali_flag)
    {
        aw9163_auto_cali(aw9163);
        if(aw9163->cali_flag == 0)
        {
            if(aw9163->cali_used){
                aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
                reg_val &= 0xFFFD;
                aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);
            }
            aw9163_i2c_write(aw9163, AW9163_REG_INTER, AW9163_NORMAL_INTER);
            aw9163_i2c_write(aw9163, AW9163_REG_GIER, AW9163_NORMAL_GIER);
            if(aw9163->cali_used){
                aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
                reg_val |= 0x0002;
                aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);
            }
        }
        aw9163_interrupt_clear(aw9163);
        return IRQ_HANDLED;
    }
#endif

    aw9163_i2c_read(aw9163, AW9163_REG_ISR, &reg_kisr);
    aw9163_i2c_read(aw9163, AW9163_REG_AKSST, &reg_kst);
    pr_info("%s: kisr=0x%04x, kst=0x%04x\n", __func__, reg_kisr, reg_kst);

    if(reg_kisr & 0x0020) {
        if(reg_kst & 0x0020) {
            input_report_key(aw9163->input, KEY_VOLUMEUP, 1);
        } else {
            input_report_key(aw9163->input, KEY_VOLUMEUP, 0);
        }
        input_sync(aw9163->input);
    } else if(reg_kisr & 0x0010) {
        if(reg_kst & 0x0010) {
            input_report_key(aw9163->input, KEY_MENU, 1);
        } else {
            input_report_key(aw9163->input, KEY_MENU, 0);
        }
        input_sync(aw9163->input);
    } else if(reg_kisr & 0x0008) {
        if(reg_kst & 0x0008) {
            input_report_key(aw9163->input, KEY_VOLUMEDOWN, 1);
        } else {
            input_report_key(aw9163->input, KEY_VOLUMEDOWN, 0);
        }
        input_sync(aw9163->input);
    }

    aw9163_interrupt_clear(aw9163);
#if !defined(CONFIG_ARM) && !defined(CONFIG_ARM64)
    BcmHalInterruptEnable(irq);
#else
    BcmHalExternalIrqClear(irq);
#endif
    pr_info("%s exit\n", __func__);

    return IRQ_HANDLED;
}


/*****************************************************
 *
 * device tree
 *
 *****************************************************/
#if 0
static int aw9163_parse_dt(struct device *dev, struct aw9163 *aw9163,
        struct device_node *np) {
    aw9163->reset_gpio =  of_get_named_gpio(np, "reset-gpio", 0);
    if (aw9163->reset_gpio < 0) {
        dev_err(dev, "%s: no reset gpio provided.\n", __func__);
    } else {
        dev_info(dev, "%s: reset gpio provided ok.\n", __func__);
    }

    aw9163->irq_gpio =  of_get_named_gpio(np, "irq-gpio", 0);
    if (aw9163->irq_gpio < 0) {
        dev_err(dev, "%s: no irq gpio provided.\n", __func__);
    } else {
        dev_info(dev, "%s: irq gpio provided ok.\n", __func__);
    }

    return 0;
}
#endif

int aw9163_hw_reset(struct aw9163 *aw9163)
{
    pr_info("%s enter\n", __func__);

#if 0
    if (aw9163 && gpio_is_valid(aw9163->reset_gpio)) {
        gpio_set_value_cansleep(aw9163->reset_gpio, 0);
	usleep_range(2000, 2500);
        gpio_set_value_cansleep(aw9163->reset_gpio, 1);
	usleep_range(5000, 5500);
    } else {
        dev_err(aw9163->dev, "%s:  failed\n", __func__);
    }
#else
    if (aw9163) {
        kerSysSetGpioDir(aw9163->reset_gpio);
        kerSysSetGpioState(aw9163->reset_gpio, 0);
        pr_info("%s: reset_gpio = %d\n", __func__, kerSysGetGpioValue(aw9163->reset_gpio));
        usleep_range(2000, 2500);
        kerSysSetGpioState(aw9163->reset_gpio, 1);
        pr_info("%s: reset_gpio = %d\n", __func__, kerSysGetGpioValue(aw9163->reset_gpio));
        usleep_range(5000, 5500);
    } else {
        dev_err(aw9163->dev, "%s:  failed\n", __func__);
    }
#endif
    return 0;
}

int aw9163_hw_off(struct aw9163 *aw9163)
{
    pr_info("%s enter\n", __func__);

#if 0
    if (aw9163 && gpio_is_valid(aw9163->reset_gpio)) {
        gpio_set_value_cansleep(aw9163->reset_gpio, 0);
	usleep_range(2000, 2500);
    } else {
        dev_err(aw9163->dev, "%s:  failed\n", __func__);
    }
#else
    if (aw9163) {
        kerSysSetGpioState(aw9163->reset_gpio, 0);
        usleep_range(2000, 2500);
	} else {
        dev_err(aw9163->dev, "%s:  failed\n", __func__);
    }
#endif
    return 0;
}

/*****************************************************
 *
 * check chip id
 *
 *****************************************************/
int aw9163_read_chipid(struct aw9163 *aw9163)
{
    int ret = -1;
    unsigned char cnt = 0;
    unsigned int reg_val = 0;

    while(cnt < AW_READ_CHIPID_RETRIES) {
        ret = aw9163_i2c_read(aw9163, AW9163_REG_RSTR, &reg_val);
        if (ret < 0) {
            dev_err(aw9163->dev, "%s: failed to read register AW9163_REG_RSTR: %d\n", __func__, ret);
        }
        switch (reg_val) {
        case 0xb223:
            pr_info("%s aw9163 detected\n", __func__);
            //aw9163->flags |= AW9163_FLAG_SKIP_INTERRUPTS;
            return 0;
        default:
            pr_info("%s unsupported device revision (0x%x)\n", __func__, reg_val);
            break;
        }
        cnt ++;
	usleep_range(AW_READ_CHIPID_RETRY_DELAY * 1000,
		     AW_READ_CHIPID_RETRY_DELAY * 1000 + 500);
    }

    return -EINVAL;
}


/******************************************************
 *
 * sys group attribute: reg
 *
 ******************************************************/
static ssize_t aw9163_i2c_reg_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);

    unsigned int databuf[2] = {0, 0};

    if(2 == sscanf(buf, "%x %x", &databuf[0], &databuf[1])) {
        aw9163_i2c_write(aw9163, (unsigned char)databuf[0], (unsigned int)databuf[1]);
    }

    return count;
}

static ssize_t aw9163_i2c_reg_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);
    ssize_t len = 0;
    unsigned char i = 0;
    unsigned int reg_val = 0;
    for(i = 0; i < AW9163_REG_MAX; i ++) {
        if(!(aw9163_reg_access[i]&REG_RD_ACCESS))
           continue;
        aw9163_i2c_read(aw9163, i, &reg_val);
        len += snprintf(buf+len, PAGE_SIZE-len, "reg:0x%02x=0x%04x \n", i, reg_val);
    }
    return len;
}

static ssize_t aw9163_i2c_hwen_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);

    unsigned int databuf[1] = {0};

    if(1 == sscanf(buf, "%x", &databuf[0])) {
        if(1 == databuf[0]) {
            aw9163_hw_reset(aw9163);
        } else {
            aw9163_hw_off(aw9163);
        }
    }

    return count;
}

static ssize_t aw9163_i2c_hwen_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);
    ssize_t len = 0;
#if 0
    len += snprintf(buf+len, PAGE_SIZE-len, "hwen=%d\n",
            gpio_get_value(aw9163->reset_gpio));
#else
    len += snprintf(buf+len, PAGE_SIZE-len, "hwen=%d\n",
            kerSysGetGpioValue(aw9163->reset_gpio));
#endif

    return len;
}


static ssize_t aw9163_i2c_rawdata_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    //struct aw9163 *aw9163 = dev_get_drvdata(dev);
    return count;
}

static ssize_t aw9163_i2c_rawdata_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);
    ssize_t len = 0;
    unsigned int reg_val = 0;
    unsigned char i;

    aw9163_i2c_write(aw9163, AW9163_REG_MCR, 0x0003);
    len += snprintf(buf+len, PAGE_SIZE-len, "rawdata:\n");
    for(i=0; i<6; i++) {
        aw9163_i2c_read(aw9163, AW9163_REG_KDATA0+i, &reg_val);
        len += snprintf(buf+len, PAGE_SIZE-len, "%d, ", reg_val);
    }
    len += snprintf(buf+len, PAGE_SIZE-len, "\n");


    return len;
}

static ssize_t aw9163_i2c_base_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    //struct aw9163 *aw9163 = dev_get_drvdata(dev);
    return count;
}

static ssize_t aw9163_i2c_base_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);
    ssize_t len = 0;
    unsigned int reg_val = 0;
    unsigned char i;

    aw9163_i2c_write(aw9163, AW9163_REG_MCR, 0x0002);
    len += snprintf(buf+len, PAGE_SIZE-len, "baseline:\n");
    for(i=0; i<6; i++) {
        aw9163_i2c_read(aw9163, AW9163_REG_KDATA0+i, &reg_val);
        len += snprintf(buf+len, PAGE_SIZE-len, "%d, ", reg_val);
    }
    len += snprintf(buf+len, PAGE_SIZE-len, "\n");

    return len;
}

static ssize_t aw9163_i2c_delta_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    //struct aw9163 *aw9163 = dev_get_drvdata(dev);
    return count;
}

static ssize_t aw9163_i2c_delta_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);
    ssize_t len = 0;
    unsigned int reg_val = 0;
    unsigned char i;

    aw9163_i2c_write(aw9163, AW9163_REG_MCR, 0x0001);
    len += snprintf(buf+len, PAGE_SIZE-len, "delta:\n");
    for(i=0; i<6; i++) {
        aw9163_i2c_read(aw9163, AW9163_REG_KDATA0+i, &reg_val);
        if(reg_val & 0x8000) {
            reg_val = 0;
        }
        len += snprintf(buf+len, PAGE_SIZE-len, "%d, ", reg_val);
    }
    len += snprintf(buf+len, PAGE_SIZE-len, "\n");

    return len;
}

static ssize_t aw9163_i2c_irqstate_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    //struct aw9163 *aw9163 = dev_get_drvdata(dev);
    return count;
}

static ssize_t aw9163_i2c_irqstate_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct aw9163 *aw9163 = dev_get_drvdata(dev);
    ssize_t len = 0;
    unsigned int reg_val = 0;
    unsigned int tmp_val = 0;
    unsigned char i;

    len += snprintf(buf+len, PAGE_SIZE-len, "touch:\n");
    aw9163_i2c_read(aw9163, AW9163_REG_AKSST, &reg_val);
    for(i=0; i<6; i++) {
        tmp_val = (reg_val>>i)&0x01;
        len += snprintf(buf+len, PAGE_SIZE-len, "%d, ", tmp_val);
    }
    len += snprintf(buf+len, PAGE_SIZE-len, "\n");
    len += snprintf(buf+len, PAGE_SIZE-len, "gesture:\n");
    aw9163_i2c_read(aw9163, AW9163_REG_GISR, &reg_val);
    for(i=0; i<5; i++) {
        tmp_val = (reg_val>>i)&0x01;
        len += snprintf(buf+len, PAGE_SIZE-len, "%d, ", tmp_val);
    }
    len += snprintf(buf+len, PAGE_SIZE-len, "\n");

    return len;
}

static DEVICE_ATTR(reg, S_IWUSR | S_IRUGO, aw9163_i2c_reg_show, aw9163_i2c_reg_store);
static DEVICE_ATTR(hwen, S_IWUSR | S_IRUGO, aw9163_i2c_hwen_show, aw9163_i2c_hwen_store);
static DEVICE_ATTR(rawdata, S_IWUSR | S_IRUGO, aw9163_i2c_rawdata_show, aw9163_i2c_rawdata_store);
static DEVICE_ATTR(base, S_IWUSR | S_IRUGO, aw9163_i2c_base_show, aw9163_i2c_base_store);
static DEVICE_ATTR(delta, S_IWUSR | S_IRUGO, aw9163_i2c_delta_show, aw9163_i2c_delta_store);
static DEVICE_ATTR(irqstate, S_IWUSR | S_IRUGO, aw9163_i2c_irqstate_show, aw9163_i2c_irqstate_store);

static struct attribute *aw9163_attributes[] = {
    &dev_attr_reg.attr,
    &dev_attr_hwen.attr,
    &dev_attr_rawdata.attr,
    &dev_attr_base.attr,
    &dev_attr_delta.attr,
    &dev_attr_irqstate.attr,
    NULL
};

static struct attribute_group aw9163_attribute_group = {
    .attrs = aw9163_attributes
};

/******************************************************
 *
 * aw9163 led
 *
 ******************************************************/
static void aw9163_brightness_work(struct work_struct *work)
{
    struct aw9163 *aw9163 = container_of(work, struct aw9163,
          brightness_work);

    unsigned int imax = 0;
    unsigned int reg_val;

    imax = (aw9163->imax<<12) | (aw9163->imax<<8) |
            (aw9163->imax<<4) | (aw9163->imax<<0);

    if(aw9163->cdev.brightness > aw9163->cdev.max_brightness) {
        aw9163->cdev.brightness = aw9163->cdev.max_brightness;
    }

    //Disable LED Module
    aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
    reg_val &= 0xFFFE;
    aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);     // GCR-Disable LED Module

    if(aw9163->cdev.brightness) {
        //Enable LED Module
        reg_val |= 0x0001;
        aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);     // GCR-Enable LED Module

        //LED Config
        aw9163_i2c_write(aw9163, AW9163_REG_LER1, 0x001C);     // LER1-LED1~LED3 Enable
        aw9163_i2c_write(aw9163, AW9163_REG_IMAX1, imax);      // IMAX1-LED1~LED2 Current
        aw9163_i2c_write(aw9163, AW9163_REG_IMAX2, imax);      // IMAX1-LED3 Current
        aw9163_i2c_write(aw9163, AW9163_REG_CTRS1, 0x001C);    // CTRS1-LED1~LED3: i2c Control

        // LED Control
        aw9163_i2c_write(aw9163, AW9163_REG_CMDR,
                0xBF00|aw9163->cdev.brightness);               // CMDR-LED1~LED20 PWM=0xFF
    }
}

static void aw9163_set_brightness(struct led_classdev *cdev,
           enum led_brightness brightness)
{
    struct aw9163 *aw9163 = container_of(cdev, struct aw9163, cdev);

    aw9163->cdev.brightness = brightness;

    schedule_work(&aw9163->brightness_work);
}

static void aw9163_led_blink(struct aw9163 *aw9163, unsigned char blink)
{
    unsigned char i;
    unsigned int reg_val;
    unsigned int imax = 0;

    imax = (aw9163->imax<<12) | (aw9163->imax<<8) |
            (aw9163->imax<<4) | (aw9163->imax<<0);

    //Disable LED Module
    aw9163_i2c_read(aw9163, AW9163_REG_GCR, &reg_val);
    reg_val &= 0xFFFE;
    aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);         // GCR-Disable LED Module

    if(blink) {
        //Enable LED Module
        reg_val |= 0x0001;
        aw9163_i2c_write(aw9163, AW9163_REG_GCR, reg_val);     // GCR-Enable LED Module

        //LED Config
        aw9163_i2c_write(aw9163, AW9163_REG_LER1, 0x001C);     // LER1-LED1~LED3 Enable
        aw9163_i2c_write(aw9163, AW9163_REG_IMAX1, imax);      // IMAX1-LED1~LED2 Current
        aw9163_i2c_write(aw9163, AW9163_REG_IMAX2, imax);      // IMAX1-LED3 Current
        aw9163_i2c_write(aw9163, AW9163_REG_CTRS1, 0x0000);    // CTRS1-LED1~LED3: SRAM Control

        // LED SRAM Hold Mode
        aw9163_i2c_write(aw9163, AW9163_REG_PMR, 0x0000);      // PMR-Load SRAM with I2C
        aw9163_i2c_write(aw9163, AW9163_REG_RMR, 0x0000);      // RMR-Hold Mode

        // Load LED SRAM
        aw9163_i2c_write(aw9163, AW9163_REG_WADDR, 0x0000);    // WADDR-SRAM Load Addr
        for(i=0; i<led_code_len; i++)
        {
            aw9163_i2c_write(aw9163, AW9163_REG_WDATA, led_code[i]);
        }

        // LED SRAM Run
        aw9163_i2c_write(aw9163, AW9163_REG_SADDR, 0x0000);    // SADDR-SRAM Run Start Addr:0
        aw9163_i2c_write(aw9163, AW9163_REG_PMR, 0x0001);      // PMR-Reload and Excute SRAM
        aw9163_i2c_write(aw9163, AW9163_REG_RMR, 0x0002);      // RMR-Run
    }
}

/******************************************************
 *
 * sys group attribute: reg
 *
 ******************************************************/
static ssize_t aw9163_reg_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct aw9163 *aw9163 = container_of(led_cdev, struct aw9163, cdev);

    unsigned int databuf[2] = {0, 0};

    if(2 == sscanf(buf, "%x %x", &databuf[0], &databuf[1])) {
        aw9163_i2c_write(aw9163, databuf[0], databuf[1]);
    }

    return count;
}

static ssize_t aw9163_reg_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct aw9163 *aw9163 = container_of(led_cdev, struct aw9163, cdev);
    ssize_t len = 0;
    unsigned char i = 0;
    unsigned int reg_val = 0;
    for(i = 0; i < AW9163_REG_MAX; i ++) {
        if(!(aw9163_reg_access[i]&REG_RD_ACCESS))
           continue;
        aw9163_i2c_read(aw9163, i, &reg_val);
        len += snprintf(buf+len, PAGE_SIZE-len, "reg:0x%02x=0x%04x \n", i, reg_val);
    }
    return len;
}

static ssize_t aw9163_hwen_store(struct device *dev, struct device_attribute *attr,
                const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct aw9163 *aw9163 = container_of(led_cdev, struct aw9163, cdev);

    unsigned int databuf[1] = {0};

    if(1 == sscanf(buf, "%x", &databuf[0])) {
        if(1 == databuf[0]) {
            aw9163_hw_reset(aw9163);
        } else {
            aw9163_hw_off(aw9163);
        }
    }

    return count;
}

static ssize_t aw9163_hwen_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct aw9163 *aw9163 = container_of(led_cdev, struct aw9163, cdev);
    ssize_t len = 0;
#if 0
    len += snprintf(buf+len, PAGE_SIZE-len, "hwen=%d\n",
            gpio_get_value(aw9163->reset_gpio));
#else
    len += snprintf(buf+len, PAGE_SIZE-len, "hwen=%d\n",
            kerSysGetGpioValue(aw9163->reset_gpio));
#endif

    return len;
}

static ssize_t aw9163_blink_store(struct device* dev, struct device_attribute *attr,
                const char* buf, size_t len)
{
    unsigned int databuf[1];
    struct led_classdev *led_cdev = dev_get_drvdata(dev);
    struct aw9163 *aw9163 = container_of(led_cdev, struct aw9163, cdev);

    sscanf(buf,"%d",&databuf[0]);
    aw9163_led_blink(aw9163, databuf[0]);

    return len;
}

static ssize_t aw9163_blink_show(struct device* dev,struct device_attribute *attr, char* buf)
{
    ssize_t len = 0;
    len += snprintf(buf+len, PAGE_SIZE-len, "aw9163_blink()\n");
    len += snprintf(buf+len, PAGE_SIZE-len, "echo 0 > blink\n");
    len += snprintf(buf+len, PAGE_SIZE-len, "echo 1 > blink\n");

    return len;
}


static DEVICE_ATTR(register, S_IWUSR | S_IRUGO, aw9163_reg_show, aw9163_reg_store);
static DEVICE_ATTR(hw_en, S_IWUSR | S_IRUGO, aw9163_hwen_show, aw9163_hwen_store);
static DEVICE_ATTR(blink, S_IWUSR | S_IRUGO, aw9163_blink_show, aw9163_blink_store);

static struct attribute *aw9163_led_attributes[] = {
    &dev_attr_register.attr,
    &dev_attr_hw_en.attr,
    &dev_attr_blink.attr,
    NULL
};

static struct attribute_group aw9163_led_attribute_group = {
    .attrs = aw9163_led_attributes
};
/******************************************************
 *
 * led class dev
 *
 ******************************************************/
static int aw9163_parse_led_cdev(struct aw9163 *aw9163,
        struct device_node *np)
{
    struct device_node *temp;
    int ret = -1;

    for_each_child_of_node(np, temp) {
        ret = of_property_read_string(temp, "aw9163,name",
            &aw9163->cdev.name);
        if (ret < 0) {
            dev_err(aw9163->dev,
                "Failure reading led name, ret = %d\n", ret);
            goto free_pdata;
        }
        ret = of_property_read_u32(temp, "aw9163,imax",
            &aw9163->imax);
        if (ret < 0) {
            dev_err(aw9163->dev,
                "Failure reading imax, ret = %d\n", ret);
            goto free_pdata;
        }
        ret = of_property_read_u32(temp, "aw9163,brightness",
            &aw9163->cdev.brightness);
        if (ret < 0) {
            dev_err(aw9163->dev,
                "Failure reading brightness, ret = %d\n", ret);
            goto free_pdata;
        }
        ret = of_property_read_u32(temp, "aw9163,max_brightness",
            &aw9163->cdev.max_brightness);
        if (ret < 0) {
            dev_err(aw9163->dev,
                "Failure reading max brightness, ret = %d\n", ret);
            goto free_pdata;
        }
    }

    INIT_WORK(&aw9163->brightness_work, aw9163_brightness_work);

    aw9163->cdev.brightness_set = aw9163_set_brightness;
    ret = led_classdev_register(aw9163->dev, &aw9163->cdev);
    if (ret) {
        dev_err(aw9163->dev,
            "unable to register led ret=%d\n", ret);
        goto free_pdata;
    }

    ret = sysfs_create_group(&aw9163->cdev.dev->kobj,
            &aw9163_led_attribute_group);
    if (ret) {
        dev_err(aw9163->dev, "led sysfs ret: %d\n", ret);
        goto free_class;
    }

    return 0;

free_class:
    led_classdev_unregister(&aw9163->cdev);
free_pdata:
    return ret;
}

/******************************************************
 *
 * i2c driver
 *
 ******************************************************/
static int aw9163_i2c_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
    struct aw9163 *aw9163;
    //struct device_node *np = i2c->dev.of_node;
    struct input_dev *input_dev;
#if 0
    int irq_flags;
#else
    unsigned short gpio;
    unsigned short intr;
#endif
    int ret = -1;

    pr_info("%s enter\n", __func__);

    if (!i2c_check_functionality(i2c->adapter, I2C_FUNC_I2C)) {
        dev_err(&i2c->dev, "check_functionality failed\n");
        return -EIO;
    }

    aw9163 = devm_kzalloc(&i2c->dev, sizeof(struct aw9163), GFP_KERNEL);
    if (aw9163 == NULL)
        return -ENOMEM;

    aw9163->dev = &i2c->dev;
    aw9163->i2c = i2c;


    i2c_set_clientdata(i2c, aw9163);

#if 0
    /* aw9163 int */
    if (np) {
        ret = aw9163_parse_dt(&i2c->dev, aw9163, np);
        if (ret) {
            dev_err(&i2c->dev, "%s: failed to parse device tree node\n", __func__);
            goto err;
        }
    } else {
        aw9163->reset_gpio = -1;
        aw9163->irq_gpio = -1;
    }

    if (gpio_is_valid(aw9163->reset_gpio)) {
        ret = devm_gpio_request_one(&i2c->dev, aw9163->reset_gpio,
            GPIOF_OUT_INIT_LOW, "aw9163_rst");
        if (ret){
            dev_err(&i2c->dev, "%s: rst request failed\n", __func__);
            goto err;
        }
    }

    if (gpio_is_valid(aw9163->irq_gpio)) {
        ret = devm_gpio_request_one(&i2c->dev, aw9163->irq_gpio,
            GPIOF_DIR_IN, "aw9163_int");
        if (ret){
            dev_err(&i2c->dev, "%s: int request failed\n", __func__);
            goto err;
        }
    }
#else
    if ( BpGetMiscButtonResetGpio( &gpio ) != BP_SUCCESS ) {
         dev_err(&i2c->dev, "%s: get reset gpio failed\n", __func__);
         goto err;
    }
    aw9163->reset_gpio = gpio;
    if ( BpGetMiscButtonExtIntrGpio( &gpio ) != BP_SUCCESS ) {
        dev_err(&i2c->dev, "%s: get irq gpio failed\n", __func__);
        goto err;
    }
    aw9163->irq_gpio = gpio;
    pr_info("%s: reset_gpio = %d, irq_gpio = %d\n", __func__, aw9163->reset_gpio, aw9163->irq_gpio);
#endif

    /* aw9163 hardware reset */
    aw9163_hw_reset(aw9163);

    /* aw9163 chip id */
    ret = aw9163_read_chipid(aw9163);
    if (ret < 0) {
        dev_err(&i2c->dev, "%s: aw9163_read_chipid failed ret=%d\n",
                __func__, ret);
        goto err_id;
    }

#if 0
    /* aw9163 irq */
    if (gpio_is_valid(aw9163->irq_gpio) &&
        !(aw9163->flags & AW9163_FLAG_SKIP_INTERRUPTS)) {
        /* register irq handler */
        aw9163_interrupt_setup(aw9163);
        irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;
        ret = devm_request_threaded_irq(&i2c->dev,
                gpio_to_irq(aw9163->irq_gpio),
                NULL, aw9163_irq, irq_flags,
                "aw9163", aw9163);
        if (ret != 0) {
            dev_err(&i2c->dev, "%s: failed to request IRQ %d: %d\n",
                    __func__, gpio_to_irq(aw9163->irq_gpio), ret);
            goto err_irq;
        }
    } else {
        dev_info(&i2c->dev, "%s skipping IRQ registration\n", __func__);
        /* disable feature support if gpio was invalid */
        aw9163->flags |= AW9163_FLAG_SKIP_INTERRUPTS;
    }
#else
    if (!(aw9163->flags & AW9163_FLAG_SKIP_INTERRUPTS)) {
        /* register irq handler */
        aw9163_interrupt_setup(aw9163);
        kerSysSetGpioDirInput(aw9163->irq_gpio);
        if ( BpGetMiscButtonExtIntr(&intr) != BP_SUCCESS ) {
            dev_err(&i2c->dev, "%s: failed to get irq_flags\n", __func__);
			goto err_irq;
        }
        ret = ext_irq_connect(intr, (void *)aw9163, (FN_HANDLER)aw9163_irq);
        if (ret != 0) {
            dev_err(&i2c->dev, "%s: failed to request IRQ: %d\n",
                    __func__, ret);
            goto err_irq;
        }
    } else {
        dev_info(&i2c->dev, "%s skipping IRQ registration\n", __func__);
        /* disable feature support if gpio was invalid */
        aw9163->flags |= AW9163_FLAG_SKIP_INTERRUPTS;
    }
#endif

    dev_set_drvdata(&i2c->dev, aw9163);


    /* input device */
    input_dev = input_allocate_device();
    if (!input_dev) {
        ret = -ENOMEM;
        dev_err(&i2c->dev, "failed to allocate input device\n");
        goto exit_input_dev_alloc_failed;
    }
    __set_bit(EV_KEY, input_dev->evbit);
    __set_bit(EV_SYN, input_dev->evbit);
    __set_bit(KEY_MENU, input_dev->keybit);
    __set_bit(KEY_VOLUMEUP, input_dev->keybit);
    __set_bit(KEY_VOLUMEDOWN, input_dev->keybit);

    input_dev->name = AW9163_I2C_NAME;
    ret = input_register_device(input_dev);
    if (ret) {
        dev_err(&i2c->dev,
        "%s: failed to register input device: %s\n",
        __func__, dev_name(&i2c->dev));
        goto exit_input_register_device_failed;
    }
    aw9163->input = input_dev;

    /* attribute */
    ret = sysfs_create_group(&i2c->dev.kobj, &aw9163_attribute_group);
    if (ret < 0) {
        dev_info(&i2c->dev, "%s error creating sysfs attr files\n", __func__);
        goto err_sysfs;
    }

    /* led cdev */
    /*ret = aw9163_parse_led_cdev(aw9163, np);
    if (ret < 0) {
        dev_err(&i2c->dev, "%s error creating led class dev\n", __func__);
        goto err_led;
    }*/

    /* aw9163 cfg */
    aw9163_normal_mode_init(aw9163);

    pr_info("%s probe completed successfully!\n", __func__);

    return 0;

//err_led:
    sysfs_remove_group(&i2c->dev.kobj, &aw9163_attribute_group);
err_sysfs:
    input_unregister_device(input_dev);
exit_input_register_device_failed:
    input_free_device(input_dev);
exit_input_dev_alloc_failed:
err_irq:
err_id:
    if (gpio_is_valid(aw9163->irq_gpio))
        devm_gpio_free(&i2c->dev, aw9163->irq_gpio);
err:
    return ret;
}

static int aw9163_i2c_remove(struct i2c_client *i2c)
{
    struct aw9163 *aw9163 = i2c_get_clientdata(i2c);

    pr_info("%s enter\n", __func__);

    sysfs_remove_group(&i2c->dev.kobj, &aw9163_attribute_group);

    if (gpio_is_valid(aw9163->irq_gpio))
        devm_gpio_free(&i2c->dev, aw9163->irq_gpio);

    return 0;
}

#ifdef CONFIG_PM_SLEEP
static int aw9163_suspend(struct device *dev)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct aw9163 *aw9163 = i2c_get_clientdata(client);

    aw9163_hw_off(aw9163);

    return 0;
}

static int aw9163_resume(struct device *dev)
{
    struct i2c_client *client = to_i2c_client(dev);
    struct aw9163 *aw9163 = i2c_get_clientdata(client);

    aw9163_hw_reset(aw9163);
    aw9163_normal_mode_init(aw9163);

    return 0;
}
static SIMPLE_DEV_PM_OPS(aw9163_pm, aw9163_suspend, aw9163_resume);
#endif

static const struct i2c_device_id aw9163_i2c_id[] = {
    { AW9163_I2C_NAME, 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, aw9163_i2c_id);

static struct of_device_id aw9163_dt_match[] = {
    { .compatible = "awinic,aw9163_ts"},
    { },
};

static struct i2c_driver aw9163_i2c_driver = {
    .driver = {
        .name = AW9163_I2C_NAME,
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(aw9163_dt_match),
#ifdef CONFIG_PM_SLEEP
        .pm = &aw9163_pm,
#endif
    },
    .probe = aw9163_i2c_probe,
    .remove = aw9163_i2c_remove,
    .id_table = aw9163_i2c_id,
};


static int __init aw9163_i2c_init(void)
{
    int ret = 0;

    pr_info("aw9163 driver version %s\n", AW9163_VERSION);

    ret = i2c_add_driver(&aw9163_i2c_driver);
    if(ret){
        pr_err("fail to add aw9163 device into i2c\n");
        return ret;
    }

    return 0;
}
module_init(aw9163_i2c_init);


static void __exit aw9163_i2c_exit(void)
{
    i2c_del_driver(&aw9163_i2c_driver);
}
module_exit(aw9163_i2c_exit);


MODULE_DESCRIPTION("AW9163 Touch Key Driver");
MODULE_LICENSE("GPL v2");
