#ifndef _LINUX_SN_LED_H
#define _LINUX_SN_LED_H

struct sn_led_data {
	int led_num;
	int total_led_num;
	unsigned char *led_order;
	unsigned char *led_startup;
	int led_startup_len;
	int led_startup_current;
    struct delayed_work work;
    int startup_enable;
    int startup_step;
    int startup_mode;
    int count;
    int leds_rgb;
    int leds_pwm;
    int leds_startup_rgb;
    int sdb_pin;
};

#endif

