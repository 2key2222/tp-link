#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/reboot.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include "sn_led.h"

//#define DEBUG
#ifdef DEBUG
#define debug(fmt, ...) \
	do { printk(KERN_ALERT "%d:%s(): " fmt "\n", \
			__LINE__, __func__, ##__VA_ARGS__); } while (0)
#else
#define debug(...) do {} while (0)
#endif

#define CONFIG_SN3236
#ifdef CONFIG_SN3236
#define MAX_LED_NUM 12
#define MAX_LED_LEN (3 * MAX_LED_NUM)
#endif

static char startup_buf[MAX_LED_LEN];
static struct i2c_client *client;

static int i2c_write_bytes(struct i2c_client *client,
		uint8_t *data, uint16_t len) {
	struct i2c_msg msg;
	int ret = -1;
	int retry = 3;

	msg.flags = 0;
	msg.addr = client->addr;
	msg.len = len;
	msg.buf = data;
	do {
		ret = i2c_transfer(client->adapter, &msg, 1);
		retry--;
		if(ret < 0)
		{
			mdelay(30);
			pr_info("####retry = %d, err = %d\n", retry, ret);
		}
	} while((ret < 0) && (retry > 0));

	return ret;
}

static int sn3236_reset(struct i2c_client *client) {
	uint8_t	cmd[] = {0x4F, 0x00};
	return i2c_write_bytes(client, cmd, sizeof(cmd));
}

static int sn3236_enable(struct i2c_client *client, bool onoff) {
	uint8_t cmd[2] = {0x00, 0x00};
	cmd[1] = (uint8_t)onoff;
	return i2c_write_bytes(client, cmd, sizeof(cmd));
}

static int sn3236_all_leds_pwm(uint8_t *leds_pwm, int num)
{
	uint8_t cmd[MAX_LED_LEN + 1] = {0x01};
	struct device *dev = &client->dev;
	struct sn_led_data *sn_data = dev->platform_data;
	int i;

	if (num != sn_data->led_num * 3) {
		pr_err("%s: num(%d) != led_num(%d)\n", __func__, num, sn_data->led_num * 3);
		return -1;
	}

	cmd[0] = 0x01;
	for (i = 0; i < num; i++)
		cmd[sn_data->led_order[i]] = leds_pwm[i];

	i2c_write_bytes(client, cmd, num+1);

	cmd[0] = 0x25; cmd[1] = 0x00;
	i2c_write_bytes(client, cmd, 2);

	return 0;
}

static int sn3236_all_leds(uint8_t *leds, int num)
{
	int i, total_led_num;
	uint8_t cmd[MAX_LED_LEN + 1] = {0x01};
	struct device *dev = &client->dev;
	struct sn_led_data *sn_data = dev->platform_data;

	if (num != sn_data->led_num * 3) {
		pr_err("%s: num(%d) != led_num(%d)\n", __func__, num, sn_data->led_num * 3);
		return -1;
	}

	total_led_num = sn_data->total_led_num;
	if (num > MAX_LED_LEN) {
		pr_err("%s: num(%d) > MAX_LED_LEN(%d)\n", __func__, num, MAX_LED_LEN);
		return -1;
	}
	if (total_led_num > MAX_LED_LEN) {
		pr_err("%s: total_led_num(%d) > MAX_LED_LEN(%d)\n", __func__, total_led_num, MAX_LED_LEN);
		return -1;
	}
#if 0
	printk(">>>> {%s, %s, %d} ", __FILE__, __func__, __LINE__);
	for (i = 0; i < sn_data->led_num; i++)
		printk("%03u %03u %03u | ", leds[i * 3 + 0], leds[i * 3 + 1], leds[i * 3 + 2]);
	printk("\n");
#endif
	cmd[0] = 0x1;
	for (i = 0; i < num; i++){
		cmd[sn_data->led_order[i]] = leds[i];
	}
	i2c_write_bytes(client, cmd, total_led_num * 3 + 1);
	cmd[0] = 0x26;
	for (i = 0; i < total_led_num * 3; i++){
		cmd[i + 1] = !!cmd[i+1];
		cmd[i + 1] |= 0x06;/* Imax/4 */
	}
	i2c_write_bytes(client, cmd, total_led_num * 3 + 1);

	cmd[0] = 0x25;
	i2c_write_bytes(client, cmd, 2);
	return 0;
}

static void sn3236_stop_startup(struct sn_led_data *sn_data)
{
	if(sn_data->startup_enable){
		int i, num = sn_data->led_num;
		for(i=0; i < num; i++){
			// off
			startup_buf[3*i + 0] = 0;
			startup_buf[3*i + 1] = 0;
			startup_buf[3*i + 2] = 0;
		}

		sn_data->startup_enable = 0;
		sn3236_all_leds(startup_buf, num*3);
		pr_info("====================\n");
		pr_info("leds startup stoped!\n");
		pr_info("====================\n");
	}
}
static int sn3236_open(struct inode *inode, struct file *filp)
{
	struct device *dev = &client->dev;
	struct sn_led_data *sn_data = dev->platform_data;
	debug("sn3236_open");

	if(sn_data->startup_mode == 2){
		sn3236_stop_startup(sn_data);
	}

	return 0;
}

static ssize_t sn3236_write(struct file *filp, const char __user *buf,
		     size_t size, loff_t *ppos)
{
	int led_num;
	uint8_t leds[MAX_LED_LEN] = {};
	struct device *dev = &client->dev;
	struct sn_led_data *sn_data = dev->platform_data;
	led_num = sn_data->led_num;
	if(sn_data->startup_enable){
		sn3236_stop_startup(sn_data);
	}
	if (led_num * 3 > MAX_LED_LEN || copy_from_user(leds, buf, led_num * 3))
		return -EFAULT;
	if (sn3236_all_leds(leds, led_num * 3))
		return -EFAULT;
	return size;
}

static ssize_t sn3236_read(struct file *filp, char __user *buf,
			   size_t size, loff_t *ppos)
{
	int info;
	struct device *dev = &client->dev;
	struct sn_led_data *sn_data = dev->platform_data;

	if (size != 4)
		return -EFAULT;

	info = sn_data->led_num;

	if(copy_to_user(buf, &info, 4))
		return -EFAULT;

	return size;
}

static const struct file_operations sn3236_fops = {
	.write= sn3236_write,
	.read = sn3236_read,
	.open = sn3236_open,
};

static struct miscdevice sn3236_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "led",
	.fops = &sn3236_fops,
};

static void start_led_timeout(unsigned long data);
static DEFINE_TIMER(start_led_timer, start_led_timeout, 0, 0);

static void start_led_timeout(unsigned long data)
{
	struct device *dev = &client->dev;
	struct sn_led_data *sn_data = dev->platform_data;

	sn3236_all_leds(sn_data->led_startup + sn_data->led_startup_current++ * sn_data->led_num * 3, sn_data->led_num * 3);

	if (sn_data->led_startup_len - sn_data->led_startup_current > 0)
		mod_timer(&start_led_timer, jiffies + msecs_to_jiffies(2000));
}

static int sn3236_reboot_handler(struct notifier_block *this,
			       unsigned long         code,
			       void                  *unused) {
	sn3236_reset(client);
	sn3236_enable(client, false);

	return 0;
}
static struct notifier_block sn3236_reboot_notifier = {
	.notifier_call	= sn3236_reboot_handler,
	.next		= NULL,
	.priority	= 0
};

static struct sn_led_data *sn3236_get_platdata(struct device *dev){

	struct device_node *np = dev->of_node;
	struct sn_led_data *sn_pdata;
	int i;

	sn_pdata = devm_kzalloc(dev, sizeof(*sn_pdata), GFP_KERNEL);

	if(!sn_pdata){
		debug("devm_kzalloc sn_pdata failed");
		return NULL;
	}

	sn_pdata->led_order = devm_kzalloc(dev, 36, GFP_KERNEL);

	if(!sn_pdata->led_order){
                debug("devm_kzalloc sn_pdata->led_order failed");
                return NULL;
        }

	sn_pdata->led_startup = devm_kzalloc(dev, 72, GFP_KERNEL);

	if(!sn_pdata->led_startup){
                debug("devm_kzalloc sn_pdata->led_startup failed");
                return NULL;
        }
	of_property_read_u32(np, "sn3236,led-num", &sn_pdata->led_num);
	of_property_read_u32(np, "sn3236,total-led-num", &sn_pdata->total_led_num);
	of_property_read_u32(np, "sn3236,led-startup-current", &sn_pdata->led_startup_current);
	of_property_read_u32(np, "sn3236,sdb-pin", &sn_pdata->sdb_pin);
	of_property_read_u8_array(np, "sn3236,led-order", sn_pdata->led_order, 36);
	of_property_read_u8_array(np, "sn3236,led-startup", sn_pdata->led_startup, 72);
	of_property_read_u32(np, "sn3236,led-startup-len", &sn_pdata->led_startup_len);

	pr_info("of property led-num = %d\n", sn_pdata->led_num);
	pr_info("of property total-led-num = %d\n", sn_pdata->total_led_num);
	pr_info("of property led-startup-current = %d\n", sn_pdata->led_startup_current);
	pr_info("of property sdb-pin = %d\n", sn_pdata->sdb_pin);
	pr_info("of property led-startup-len = %d\n", sn_pdata->led_startup_len);

	pr_info("of property leds order:\n");
	for(i=0; i<sn_pdata->led_num; i++){
		pr_info("%d %d %d \n", sn_pdata->led_order[i*3], sn_pdata->led_order[i*3 +1],
				sn_pdata->led_order[i*3 +2]);
	}
	pr_info("of property leds startup:\n");
	for(i=0; i<sn_pdata->led_num; i++){
		pr_info("%d %d %d %d %d %d\n", sn_pdata->led_startup[i*6], sn_pdata->led_startup[i*6 +1],
				sn_pdata->led_startup[i*6 +2], sn_pdata->led_startup[i*6 +3],
				sn_pdata->led_startup[i*6 +4], sn_pdata->led_startup[i*6 +5]);
	}
	return sn_pdata;
}

static int sn3236_check(struct i2c_client *client) {
	return sn3236_enable(client, false);
}

static void sn3236_work_handler(struct work_struct *work){
	struct sn_led_data *sn_data =  container_of(work, struct sn_led_data, work.work);
	int i, delayms = 0;
	int num = sn_data->led_num;
	int rgb = sn_data->leds_startup_rgb;
	if(sn_data->startup_enable){
		if(sn_data->startup_mode == 0){
			// boot normal mode
			if(sn_data->startup_step == 1){
				// step 1
				sn_data->count++;
				if(sn_data->count == 1){
					for(i=0; i< num; i++){
						// white or orange
						startup_buf[3*i + 0] = (char)(rgb & 0x0000ff);
						startup_buf[3*i + 1] = (char)((rgb & 0x00ff00) >> 8);
						startup_buf[3*i + 2] = (char)((rgb & 0xff0000) >> 16);
					}
					delayms = 1000;
				}else if(sn_data->count == 2){
					for(i=0; i< num; i++){
						// off
						startup_buf[3*i + 0] = 0;
						startup_buf[3*i + 1] = 0;
						startup_buf[3*i + 2] = 0;
					}
					sn_data->count = 0;
					//approximately 1s
					delayms = 950;
					//because 12:00 direction is 9th led_,so 10
					sn_data->led_startup_current = 10;
					sn_data->startup_step++;
				}
			}else if(sn_data->startup_step == 2){
				// step 2: 3 white leds flow
				int inx;
				int start = sn_data->led_startup_current;
				// turn off 10th led
				startup_buf[3*start + 0] = 0;
				startup_buf[3*start + 1] = 0;
				startup_buf[3*start + 2] = 0;

				for(i=0; i< 3; i++){
				if(sn_data->sdb_pin == 1){
					// anticlockwise white 3 leds
					inx = (start + i + 1)%num;
				}
				else{
					// clockwise white 3 leds
					inx = (num+start - i - 1)%num;
				}
					startup_buf[3*inx + 0] = (char)(rgb & 0x0000ff);
					startup_buf[3*inx + 1] = (char)((rgb & 0x00ff00) >> 8);
					startup_buf[3*inx + 2] = (char)((rgb & 0xff0000) >> 16);
				}
				delayms = 200;
				sn_data->count++;

				if(sn_data->sdb_pin == 1){
					//antilockwise
					start++;
					sn_data->led_startup_current = start % num;
				}
				else{
					//clockwise
					start--;
					sn_data->led_startup_current = ( num+start ) % num;
				}

				//if(sn_data->count > 180){
					//sn_data->startup_step++;
				//}
			}else if(sn_data->startup_step == 3){
				pr_info("leds startup count[%d] end!\n", sn_data->count);
				sn3236_stop_startup(sn_data);
				delayms = 0;
			}
		}else if(sn_data->startup_mode == 1){
			// boot charger mode
			int start = 7; // led7 position
			int inx, off = sn_data->count%2;
			for(i=0; i< num; i++){
				//inx = (start + i)%3;
				inx = (start + i)%12;
				if( !off && inx == 0){
					// orange or white
					startup_buf[3*i + 0] = (char)(rgb & 0x0000ff);
					startup_buf[3*i + 1] = (char)((rgb & 0x00ff00) >> 8);
					startup_buf[3*i + 2] = (char)((rgb & 0xff0000) >> 16);
				}else{
					// off
					startup_buf[3*i + 0] = 0;
					startup_buf[3*i + 1] = 0;
					startup_buf[3*i + 2] = 0;
				}
			}
			if(off)
				delayms = 2000;
			else
				delayms = 1000;
			sn_data->count++;
		}else if(sn_data->startup_mode == 2){
			// boot ptest mode
			int start = 7; // led7 position
			int inx, off = sn_data->count%2;
			rgb = 0x000832; // yellow
			for(i=0; i< num; i++){
				inx = (start + i)%4;
				if( !off && inx == 0){
					// orange or white
					startup_buf[3*i + 0] = (char)(rgb & 0x0000ff);
					startup_buf[3*i + 1] = (char)((rgb & 0x00ff00) >> 8);
					startup_buf[3*i + 2] = (char)((rgb & 0xff0000) >> 16);
				}else{
					// off
					startup_buf[3*i + 0] = 0;
					startup_buf[3*i + 1] = 0;
					startup_buf[3*i + 2] = 0;
				}
			}
			if(off)
				delayms = 2000;
			else
				delayms = 1000;
			sn_data->count++;
		}else if(sn_data->startup_mode == 3){
			int inx;
			int start = sn_data->led_startup_current;
			for(i=0;i<36;i++){
				if(i%3 == 2){
					//joy1:== 2 is blue
					startup_buf[i] = 0xff;
				}
				else{
					startup_buf[i] = 0x00;
				}
			}

			//in joy1 ,from 12 o'clock need +6
			inx = (start)%12;

			for(i=0;i<9;i++){
				if(i%3 == 1){
					//joy1: == 1 is red
					startup_buf[(3*inx + i)%36] = 0x00;
				}
				else{
					startup_buf[(3*inx + i)%36] = 0xff;
				}
			}

			delayms = 200;

			start++;
			sn_data->led_startup_current = start % num;
		}

		sn3236_all_leds(startup_buf, num*3);
	}

	if(delayms > 0)
		schedule_delayed_work(&sn_data->work, msecs_to_jiffies(delayms));

}

static void sn32xx_leds_rgb_set(struct sn_led_data *sn_data, int val)
{
	int i, num = sn_data->led_num;

	if(sn_data->startup_enable){
		sn3236_stop_startup(sn_data);
	}

	for(i=0; i< num; i++){
		startup_buf[3*i + 0] = (char)(val & 0x0000ff);
		startup_buf[3*i + 1] = (char)((val & 0x00ff00) >> 8);
		startup_buf[3*i + 2] = (char)((val & 0xff0000) >> 16);
	}
	sn3236_all_leds(startup_buf, num*3);
	sn_data->leds_rgb = val;
}

static void sn32xx_leds_pwm_set(struct sn_led_data *sn_data, int val)
{
	int i, num = sn_data->led_num;

	for(i=0; i< num; i++){
		startup_buf[3*i + 0] = (char)(val & 0x0000ff);
		startup_buf[3*i + 1] = (char)((val & 0x00ff00) >> 8);
		startup_buf[3*i + 2] = (char)((val & 0xff0000) >> 16);
	}
	sn3236_all_leds_pwm(startup_buf, num*3);
	sn_data->leds_pwm = val;
}

static ssize_t sn32xx_leds_rgb_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct sn_led_data *sn_data = i2c_get_clientdata(client);
	char *left;
	int val = (int)simple_strtol(buf, &left, 0);

	pr_err("sn32xx set RGB val: 0x%06x\n", val);
	sn32xx_leds_rgb_set(sn_data, val);

	return count;
}

static ssize_t sn32xx_leds_rgb_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct sn_led_data *sn_data = i2c_get_clientdata(client);
	int cnt = 0;

	pr_err("sn32xx RGB val: 0x%06x\n", sn_data->leds_rgb);
	cnt += sprintf(buf, "RGB val: 0x%06x\n", sn_data->leds_rgb);

	return cnt;
}

static ssize_t sn32xx_leds_pwm_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct sn_led_data *sn_data = i2c_get_clientdata(client);
	char *left;
	int val = (int)simple_strtol(buf, &left, 0);

	pr_err("sn32xx set PWM val: 0x%06x\n", val);
	sn32xx_leds_pwm_set(sn_data, val);

	return count;
}

static ssize_t sn32xx_leds_pwm_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct sn_led_data *sn_data = i2c_get_clientdata(client);
	int cnt = 0;

	pr_err("sn32xx PWM val: 0x%06x\n", sn_data->leds_pwm);
	cnt += sprintf(buf, "PWM val: 0x%06x\n", sn_data->leds_pwm);

	return cnt;
}

static DEVICE_ATTR(all_leds_pwm, 0664, sn32xx_leds_pwm_show, sn32xx_leds_pwm_store);
static DEVICE_ATTR(all_leds_rgb, 0664, sn32xx_leds_rgb_show, sn32xx_leds_rgb_store);
static struct attribute *sn32xx_attributes[] = {
	&dev_attr_all_leds_rgb.attr,
	&dev_attr_all_leds_pwm.attr,
	NULL,
};
static const struct attribute_group sn32xx_attr_group = {
	.attrs = sn32xx_attributes,
};
static int sn3236_i2c_probe(struct i2c_client *i2c,
		const struct i2c_device_id *id) {
	int ret;
	struct device *dev = &i2c->dev;
#ifdef CONFIG_SN3236
	struct sn_led_data *sn_data = sn3236_get_platdata(dev);
	dev->platform_data = sn_data;
#else
	//struct sn_led_data *sn_data = dev->platform_data;
	struct sn_led_data *sn_data = sn3236_get_platdata(dev);
	dev->platform_data = sn_data;
#endif
	if (!i2c_check_functionality(i2c->adapter, I2C_FUNC_I2C)) {
		debug("error");
		return -1;
	}

	if(sn3236_check(i2c) < 0){
		pr_err("%s: i2c error!\n", __func__);
		return -1;
	}

	ret = misc_register(&sn3236_miscdev);
	if (ret < 0) {
		dev_err(&i2c->dev, "char dev register fail\n");
		return -1;
	}

	register_reboot_notifier(&sn3236_reboot_notifier);
	client = i2c;

	sn3236_reset(i2c);
	sn3236_enable(i2c, true);

	//sn_data->led_startup_current = 0;
	sn_data->startup_enable = 1;
	sn_data->startup_step = 2;
	sn_data->count = 0;
	sn_data->leds_rgb = 0;
	sn_data->leds_pwm = 0x101010;
	sn_data->leds_startup_rgb = 0xffffff;

	/* cmdline read */
	if (strstr(saved_command_line, "recovery_part")) {
		pr_info("%s: leds charger mode!\n", __func__);
		if(sn_data->sdb_pin == 1){
			sn_data->startup_mode = -1;
		}
		else{
			sn_data->startup_mode = 1;
		}
	}else if (strstr(saved_command_line, "ptest")) {
		pr_info("%s: leds normal mode!\n", __func__);
		sn_data->startup_mode = 2;
	}else{
		pr_info("%s: leds no mode!\n", __func__);
		if(sn_data->sdb_pin == 1){
			sn_data->startup_mode = 3;
		}
		else{
			sn_data->startup_mode = 0;
		}
	}


#if 0
	if (sn_data->led_startup_len - sn_data->led_startup_current > 0)
		start_led_timeout((unsigned long)client);
#else
	INIT_DELAYED_WORK(&sn_data->work, sn3236_work_handler);
	schedule_delayed_work(&sn_data->work, msecs_to_jiffies(300));
#endif

	i2c_set_clientdata(i2c, sn_data);

	ret = sysfs_create_group(&i2c->dev.kobj, &sn32xx_attr_group);
	if (ret){
		pr_err("%s:unable to create sysfs!\n",__func__);
	}

	pr_info("%s done\n", __func__);

	return 0;
}

static int sn3236_i2c_remove(struct i2c_client *client) {
	sn3236_enable(client, false);
	misc_deregister(&sn3236_miscdev);
	unregister_reboot_notifier(&sn3236_reboot_notifier);
	debug("i2c remove");
	return 0;
}


static const struct of_device_id sn32xx_of_match[] = {
	{ .compatible = "sugr, sn3236", 0 },
	{ .compatible = "sugr, sn3236", 0 },
	{ }
};

MODULE_DEVICE_TABLE(of, sn32xx_of_match);

static const struct i2c_device_id sn3236_id[] = {
	{ "sn3236", (kernel_ulong_t) 0 },
	{ "sn3236", (kernel_ulong_t) 0 },
};

static struct i2c_driver sn3236_driver={
	.probe    = sn3236_i2c_probe,
	.remove   = sn3236_i2c_remove,
	.id_table = sn3236_id,
	.driver = {
		.name = "sn3236",
		.of_match_table = of_match_ptr(sn32xx_of_match),
	},
};

int __init sn3236_init(void) {
	debug("init");
	i2c_add_driver(&sn3236_driver);
	return 0;
}

void __exit sn3236_exit(void) {
	debug("exit");
	i2c_del_driver(&sn3236_driver);
}

module_init(sn3236_init);
module_exit(sn3236_exit);

MODULE_LICENSE("GPL");
