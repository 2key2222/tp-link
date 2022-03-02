#include <linux/version.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/tlv.h>
#include <linux/pm.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
#include <linux/proc_fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <boardparms.h>
#include <bcm_gpio.h>
#include "ad82584f.h"
//#include "../../../../drivers/gpio/gpiolib.h"
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
static void ad82584f_early_suspend(struct early_suspend *h);
static void ad82584f_late_resume(struct early_suspend *h);
#endif

#define AD82584F_RATES (SNDRV_PCM_RATE_32000 | \
		       SNDRV_PCM_RATE_44100 | \
		       SNDRV_PCM_RATE_48000 | \
		       SNDRV_PCM_RATE_64000 | \
		       SNDRV_PCM_RATE_88200 | \
		       SNDRV_PCM_RATE_96000 | \
		       SNDRV_PCM_RATE_176400 | \
		       SNDRV_PCM_RATE_192000)

#define AD82584F_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
	 SNDRV_PCM_FMTBIT_S24_LE | \
	 SNDRV_PCM_FMTBIT_S32_LE)

static const DECLARE_TLV_DB_SCALE(mvol_tlv, -10300, 50, 1);
static const DECLARE_TLV_DB_SCALE(chvol_tlv, -10300, 50, 1);

static const struct snd_kcontrol_new ad82584f_snd_controls[] = {
	SOC_SINGLE_TLV("Master Volume", MVOL, 0,
				0xff, 1, mvol_tlv),
	SOC_SINGLE_TLV("Ch1 Volume", C1VOL, 0,
				0xff, 1, chvol_tlv),
	SOC_SINGLE_TLV("Ch2 Volume", C2VOL, 0,
			0xff, 1, chvol_tlv),
};

static struct snd_soc_codec *ad82584f_codec;
//1. if set the amp Work in mono mode, 0x02 register in flow array value must set 0x7f;
//2. set MONO_EN(0x1a.bit6) ==1 and MONO_KEY(0x74&0x75)== 3006(hex ) ,amp will Work in mono mode;

static int m_reg_tab[AD82584F_REGISTER_COUNT][2] = {
                     {0x00, 0x04},//##State_Control_1
                     {0x01, 0x81},//##State_Control_2
                     {0x02, 0x40},//##State_Control_3
                     {0x03, 0x21},//##Master_volume_control
                     {0x04, 0x18},//##Channel_1_volume_control
                     {0x05, 0x18},//##Channel_2_volume_control
                     {0x06, 0x18},//##Channel_3_volume_control
                     {0x07, 0x18},//##Channel_4_volume_control
                     {0x08, 0x18},//##Channel_5_volume_control
                     {0x09, 0x18},//##Channel_6_volume_control
                     {0x0a, 0x10},//##Bass_Tone_Boost_and_Cut
                     {0x0b, 0x10},//##treble_Tone_Boost_and_Cut
                     {0x0c, 0x90},//##State_Control_4
                     {0x0d, 0x00},//##Channel_1_configuration_registers
                     {0x0e, 0x00},//##Channel_2_configuration_registers
                     {0x0f, 0x00},//##Channel_3_configuration_registers
                     {0x10, 0x00},//##Channel_4_configuration_registers
                     {0x11, 0x00},//##Channel_5_configuration_registers
                     {0x12, 0x00},//##Channel_6_configuration_registers
                     {0x13, 0x00},//##Channel_7_configuration_registers
                     {0x14, 0x00},//##Channel_8_configuration_registers
                     {0x15, 0x6a},//##DRC1_limiter_attack/release_rate
                     {0x16, 0x6a},//##DRC2_limiter_attack/release_rate
                     {0x17, 0x6a},//##DRC3_limiter_attack/release_rate
                     {0x18, 0x6a},//##DRC4_limiter_attack/release_rate
                     {0x19, 0x06},//##Error_Delay
                     {0x1a, 0x72},//##State_Control_5
                     {0x1b, 0x01},//##HVUV_selection
                     {0x1c, 0x00},//##State_Control_6
                     {0x1d, 0x7f},//##Coefficient_RAM_Base_Address
                     {0x1e, 0x00},//##Top_8-bits_of_coefficients_A1
                     {0x1f, 0x00},//##Middle_8-bits_of_coefficients_A1
                     {0x20, 0x00},//##Bottom_8-bits_of_coefficients_A1
                     {0x21, 0x00},//##Top_8-bits_of_coefficients_A2
                     {0x22, 0x00},//##Middle_8-bits_of_coefficients_A2
                     {0x23, 0x00},//##Bottom_8-bits_of_coefficients_A2
                     {0x24, 0x00},//##Top_8-bits_of_coefficients_B1
                     {0x25, 0x00},//##Middle_8-bits_of_coefficients_B1
                     {0x26, 0x00},//##Bottom_8-bits_of_coefficients_B1
                     {0x27, 0x00},//##Top_8-bits_of_coefficients_B2
                     {0x28, 0x00},//##Middle_8-bits_of_coefficients_B2
                     {0x29, 0x00},//##Bottom_8-bits_of_coefficients_B2
                     {0x2a, 0x40},//##Top_8-bits_of_coefficients_A0
                     {0x2b, 0x00},//##Middle_8-bits_of_coefficients_A0
                     {0x2c, 0x00},//##Bottom_8-bits_of_coefficients_A0
                     {0x2d, 0x40},//##Coefficient_R/W_control
                     {0x2e, 0x00},//##Protection_Enable/Disable
                     {0x2f, 0x00},//##Memory_BIST_status
                     {0x30, 0x00},//##Power_Stage_Status(Read_only)
                     {0x31, 0x00},//##PWM_Output_Control
                     {0x32, 0x00},//##Test_Mode_Control_Reg.
                     {0x33, 0x6d},//##Qua-Ternary/Ternary_Switch_Level
                     {0x34, 0x00},//##Volume_Fine_tune
                     {0x35, 0x00},//##Volume_Fine_tune
                     {0x36, 0x60},//##OC_bypass_&_GVDD_selection
                     {0x37, 0x52},//##Device_ID_register
                     {0x38, 0x00},//##RAM1_test_register_address
                     {0x39, 0x00},//##Top_8-bits_of_RAM1_Data
                     {0x3a, 0x00},//##Middle_8-bits_of_RAM1_Data
                     {0x3b, 0x00},//##Bottom_8-bits_of_RAM1_Data
                     {0x3c, 0x00},//##RAM1_test_r/w_control
                     {0x3d, 0x00},//##RAM2_test_register_address
                     {0x3e, 0x00},//##Top_8-bits_of_RAM2_Data
                     {0x3f, 0x00},//##Middle_8-bits_of_RAM2_Data
                     {0x40, 0x00},//##Bottom_8-bits_of_RAM2_Data
                     {0x41, 0x00},//##RAM2_test_r/w_control
                     {0x42, 0x00},//##Level_Meter_Clear
                     {0x43, 0x00},//##Power_Meter_Clear
                     {0x44, 0x00},//##TOP_of_C1_Level_Meter
                     {0x45, 0x00},//##Middle_of_C1_Level_Meter
                     {0x46, 0x00},//##Bottom_of_C1_Level_Meter
                     {0x47, 0x00},//##TOP_of_C2_Level_Meter
                     {0x48, 0x00},//##Middle_of_C2_Level_Meter
                     {0x49, 0x00},//##Bottom_of_C2_Level_Meter
                     {0x4a, 0x00},//##TOP_of_C3_Level_Meter
                     {0x4b, 0x00},//##Middle_of_C3_Level_Meter
                     {0x4c, 0x00},//##Bottom_of_C3_Level_Meter
                     {0x4d, 0x00},//##TOP_of_C4_Level_Meter
                     {0x4e, 0x00},//##Middle_of_C4_Level_Meter
                     {0x4f, 0x00},//##Bottom_of_C4_Level_Meter
                     {0x50, 0x00},//##TOP_of_C5_Level_Meter
                     {0x51, 0x00},//##Middle_of_C5_Level_Meter
                     {0x52, 0x00},//##Bottom_of_C5_Level_Meter
                     {0x53, 0x00},//##TOP_of_C6_Level_Meter
                     {0x54, 0x00},//##Middle_of_C6_Level_Meter
                     {0x55, 0x00},//##Bottom_of_C6_Level_Meter
                     {0x56, 0x00},//##TOP_of_C7_Level_Meter
                     {0x57, 0x00},//##Middle_of_C7_Level_Meter
                     {0x58, 0x00},//##Bottom_of_C7_Level_Meter
                     {0x59, 0x00},//##TOP_of_C8_Level_Meter
                     {0x5a, 0x00},//##Middle_of_C8_Level_Meter
                     {0x5b, 0x00},//##Bottom_of_C8_Level_Meter
                     {0x5c, 0x06},//##I2S_Data_Output_Selection_Register
                     {0x5d, 0x00},//##Reserve
                     {0x5e, 0x00},//##Reserve
                     {0x5f, 0x00},//##Reserve
                     {0x60, 0x00},//##Reserve
                     {0x61, 0x00},//##Reserve
                     {0x62, 0x00},//##Reserve
                     {0x63, 0x00},//##Reserve
                     {0x64, 0x00},//##Reserve
                     {0x65, 0x00},//##Reserve
                     {0x66, 0x00},//##Reserve
                     {0x67, 0x00},//##Reserve
                     {0x68, 0x00},//##Reserve
                     {0x69, 0x00},//##Reserve
                     {0x6a, 0x00},//##Reserve
                     {0x6b, 0x00},//##Reserve
                     {0x6c, 0x00},//##Reserve
                     {0x6d, 0x00},//##Reserve
                     {0x6e, 0x00},//##Reserve
                     {0x6f, 0x00},//##Reserve
                     {0x70, 0x00},//##Reserve
                     {0x71, 0x00},//##Reserve
                     {0x72, 0x00},//##Reserve
                     {0x73, 0x00},//##Reserve
                     {0x74, 0x30},//##Mono_Key_High_Byte
                     {0x75, 0x06},//##Mono_Key_Low_Byte
                     {0x76, 0x00},//##Boost_Control
                     {0x77, 0x07},//##Hi-res_Item
                     {0x78, 0x40},//##Test_Mode_register
                     {0x79, 0x62},//##Boost_Strap_OV/UV_Selection
                     {0x7a, 0x8c},//##OC_Selection_2
                     {0x7b, 0x55},//##MBIST_User_Program_Top_Byte_Even
                     {0x7c, 0x55},//##MBIST_User_Program_Middle_Byte_Even
                     {0x7d, 0x55},//##MBIST_User_Program_Bottom_Byte_Even
                     {0x7e, 0x55},//##MBIST_User_Program_Top_Byte_Odd
                     {0x7f, 0x55},//##MBIST_User_Program_Middle_Byte_Odd
                     {0x80, 0x55},//##MBIST_User_Program_Bottom_Byte_Odd
                     {0x81, 0x00},//##ERROR_clear_register
                     {0x82, 0x0c},//##Minimum_duty_test
                     {0x83, 0x06},//##Reserve
                     {0x84, 0xfe},//##Reserve
                     {0x85, 0xfe},//##Reserve

};

static int m_ram1_tab[][4] = {
                     {0x00, 0x00, 0x00, 0x00},//##Channel_1_EQ1_A1
                     {0x01, 0x00, 0x00, 0x00},//##Channel_1_EQ1_A2
                     {0x02, 0x00, 0x00, 0x00},//##Channel_1_EQ1_B1
                     {0x03, 0x00, 0x00, 0x00},//##Channel_1_EQ1_B2
                     {0x04, 0x20, 0x00, 0x00},//##Channel_1_EQ1_A0
                     {0x05, 0x00, 0x00, 0x00},//##Channel_1_EQ2_A1
                     {0x06, 0x00, 0x00, 0x00},//##Channel_1_EQ2_A2
                     {0x07, 0x00, 0x00, 0x00},//##Channel_1_EQ2_B1
                     {0x08, 0x00, 0x00, 0x00},//##Channel_1_EQ2_B2
                     {0x09, 0x20, 0x00, 0x00},//##Channel_1_EQ2_A0
                     {0x0a, 0x00, 0x00, 0x00},//##Channel_1_EQ3_A1
                     {0x0b, 0x00, 0x00, 0x00},//##Channel_1_EQ3_A2
                     {0x0c, 0x00, 0x00, 0x00},//##Channel_1_EQ3_B1
                     {0x0d, 0x00, 0x00, 0x00},//##Channel_1_EQ3_B2
                     {0x0e, 0x20, 0x00, 0x00},//##Channel_1_EQ3_A0
                     {0x0f, 0x00, 0x00, 0x00},//##Channel_1_EQ4_A1
                     {0x10, 0x00, 0x00, 0x00},//##Channel_1_EQ4_A2
                     {0x11, 0x00, 0x00, 0x00},//##Channel_1_EQ4_B1
                     {0x12, 0x00, 0x00, 0x00},//##Channel_1_EQ4_B2
                     {0x13, 0x20, 0x00, 0x00},//##Channel_1_EQ4_A0
                     {0x14, 0x00, 0x00, 0x00},//##Channel_1_EQ5_A1
                     {0x15, 0x00, 0x00, 0x00},//##Channel_1_EQ5_A2
                     {0x16, 0x00, 0x00, 0x00},//##Channel_1_EQ5_B1
                     {0x17, 0x00, 0x00, 0x00},//##Channel_1_EQ5_B2
                     {0x18, 0x20, 0x00, 0x00},//##Channel_1_EQ5_A0
                     {0x19, 0x00, 0x00, 0x00},//##Channel_1_EQ6_A1
                     {0x1a, 0x00, 0x00, 0x00},//##Channel_1_EQ6_A2
                     {0x1b, 0x00, 0x00, 0x00},//##Channel_1_EQ6_B1
                     {0x1c, 0x00, 0x00, 0x00},//##Channel_1_EQ6_B2
                     {0x1d, 0x20, 0x00, 0x00},//##Channel_1_EQ6_A0
                     {0x1e, 0x00, 0x00, 0x00},//##Channel_1_EQ7_A1
                     {0x1f, 0x00, 0x00, 0x00},//##Channel_1_EQ7_A2
                     {0x20, 0x00, 0x00, 0x00},//##Channel_1_EQ7_B1
                     {0x21, 0x00, 0x00, 0x00},//##Channel_1_EQ7_B2
                     {0x22, 0x20, 0x00, 0x00},//##Channel_1_EQ7_A0
                     {0x23, 0x00, 0x00, 0x00},//##Channel_1_EQ8_A1
                     {0x24, 0x00, 0x00, 0x00},//##Channel_1_EQ8_A2
                     {0x25, 0x00, 0x00, 0x00},//##Channel_1_EQ8_B1
                     {0x26, 0x00, 0x00, 0x00},//##Channel_1_EQ8_B2
                     {0x27, 0x20, 0x00, 0x00},//##Channel_1_EQ8_A0
                     {0x28, 0x00, 0x00, 0x00},//##Channel_1_EQ9_A1
                     {0x29, 0x00, 0x00, 0x00},//##Channel_1_EQ9_A2
                     {0x2a, 0x00, 0x00, 0x00},//##Channel_1_EQ9_B1
                     {0x2b, 0x00, 0x00, 0x00},//##Channel_1_EQ9_B2
                     {0x2c, 0x20, 0x00, 0x00},//##Channel_1_EQ9_A0
                     {0x2d, 0x00, 0x00, 0x00},//##Channel_1_EQ10_A1
                     {0x2e, 0x00, 0x00, 0x00},//##Channel_1_EQ10_A2
                     {0x2f, 0x00, 0x00, 0x00},//##Channel_1_EQ10_B1
                     {0x30, 0x00, 0x00, 0x00},//##Channel_1_EQ10_B2
                     {0x31, 0x20, 0x00, 0x00},//##Channel_1_EQ10_A0
                     {0x32, 0x00, 0x00, 0x00},//##Channel_1_EQ11_A1
                     {0x33, 0x00, 0x00, 0x00},//##Channel_1_EQ11_A2
                     {0x34, 0x00, 0x00, 0x00},//##Channel_1_EQ11_B1
                     {0x35, 0x00, 0x00, 0x00},//##Channel_1_EQ11_B2
                     {0x36, 0x20, 0x00, 0x00},//##Channel_1_EQ11_A0
                     {0x37, 0x00, 0x00, 0x00},//##Channel_1_EQ12_A1
                     {0x38, 0x00, 0x00, 0x00},//##Channel_1_EQ12_A2
                     {0x39, 0x00, 0x00, 0x00},//##Channel_1_EQ12_B1
                     {0x3a, 0x00, 0x00, 0x00},//##Channel_1_EQ12_B2
                     {0x3b, 0x20, 0x00, 0x00},//##Channel_1_EQ12_A0
                     {0x3c, 0x00, 0x00, 0x00},//##Channel_1_EQ13_A1
                     {0x3d, 0x00, 0x00, 0x00},//##Channel_1_EQ13_A2
                     {0x3e, 0x00, 0x00, 0x00},//##Channel_1_EQ13_B1
                     {0x3f, 0x00, 0x00, 0x00},//##Channel_1_EQ13_B2
                     {0x40, 0x20, 0x00, 0x00},//##Channel_1_EQ13_A0
                     {0x41, 0x00, 0x00, 0x00},//##Channel_1_EQ14_A1
                     {0x42, 0x00, 0x00, 0x00},//##Channel_1_EQ14_A2
                     {0x43, 0x00, 0x00, 0x00},//##Channel_1_EQ14_B1
                     {0x44, 0x00, 0x00, 0x00},//##Channel_1_EQ14_B2
                     {0x45, 0x20, 0x00, 0x00},//##Channel_1_EQ14_A0
                     {0x46, 0x00, 0x00, 0x00},//##Channel_1_EQ15_A1
                     {0x47, 0x00, 0x00, 0x00},//##Channel_1_EQ15_A2
                     {0x48, 0x00, 0x00, 0x00},//##Channel_1_EQ15_B1
                     {0x49, 0x00, 0x00, 0x00},//##Channel_1_EQ15_B2
                     {0x4a, 0x20, 0x00, 0x00},//##Channel_1_EQ15_A0
                     {0x4b, 0x40, 0x00, 0x00},//##Channel_1_Mixer1
                     {0x4c, 0x40, 0x00, 0x00},//##Channel_1_Mixer2
                     {0x4d, 0x7f, 0xff, 0xff},//##Channel_1_Prescale
                     {0x4e, 0x7f, 0xff, 0xff},//##Channel_1_Postscale
                     {0x4f, 0xc7, 0xb6, 0x91},//##A0_of_L_channel_SRS_HPF
                     {0x50, 0x38, 0x49, 0x6e},//##A1_of_L_channel_SRS_HPF
                     {0x51, 0x0c, 0x46, 0xf8},//##B1_of_L_channel_SRS_HPF
                     {0x52, 0x0e, 0x81, 0xb9},//##A0_of_L_channel_SRS_LPF
                     {0x53, 0xf2, 0x2c, 0x12},//##A1_of_L_channel_SRS_LPF
                     {0x54, 0x0f, 0xca, 0xbb},//##B1_of_L_channel_SRS_LPF
                     {0x55, 0x20, 0x00, 0x00},//##CH1.2_Power_Clipping
                     {0x56, 0x09, 0x48, 0x3c},//##CCH1.2_DRC1_Attack_threshold
                     {0x57, 0x09, 0x04, 0xd1},//##CH1.2_DRC1_Release_threshold
                     {0x58, 0x20, 0x00, 0x00},//##CH3.4_DRC2_Attack_threshold
                     {0x59, 0x08, 0x00, 0x00},//##CH3.4_DRC2_Release_threshold
                     {0x5a, 0x20, 0x00, 0x00},//##CH5.6_DRC3_Attack_threshold
                     {0x5b, 0x08, 0x00, 0x00},//##CH5.6_DRC3_Release_threshold
                     {0x5c, 0x20, 0x00, 0x00},//##CH7.8_DRC4_Attack_threshold
                     {0x5d, 0x08, 0x00, 0x00},//##CH7.8_DRC4_Release_threshold
                     {0x5e, 0x00, 0x00, 0x1a},//##Noise_Gate_Attack_Level
                     {0x5f, 0x00, 0x00, 0x53},//##Noise_Gate_Release_Level
                     {0x60, 0x00, 0x80, 0x00},//##DRC1_Energy_Coefficient
                     {0x61, 0x00, 0x20, 0x00},//##DRC2_Energy_Coefficient
                     {0x62, 0x00, 0x80, 0x00},//##DRC3_Energy_Coefficient
                     {0x63, 0x00, 0x80, 0x00},//##DRC4_Energy_Coefficient
                     {0x64, 0x00, 0x00, 0x00},//DRC1_Power_Meter
                     {0x65, 0x00, 0x00, 0x00},//DRC3_Power_Mete
                     {0x66, 0x00, 0x00, 0x00},//DRC5_Power_Meter
                     {0x67, 0x00, 0x00, 0x00},//DRC7_Power_Meter
                     {0x68, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_A1
                     {0x69, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_A2
                     {0x6a, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_B1
                     {0x6b, 0x00, 0x00, 0x00},//##Channel_1_DEQ1_B2
                     {0x6c, 0x20, 0x00, 0x00},//##Channel_1_DEQ1_A0
                     {0x6d, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_A1
                     {0x6e, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_A2
                     {0x6f, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_B1
                     {0x70, 0x00, 0x00, 0x00},//##Channel_1_DEQ2_B2
                     {0x71, 0x20, 0x00, 0x00},//##Channel_1_DEQ2_A0
                     {0x72, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_A1
                     {0x73, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_A2
                     {0x74, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_B1
                     {0x75, 0x00, 0x00, 0x00},//##Channel_1_DEQ3_B2
                     {0x76, 0x20, 0x00, 0x00},//##Channel_1_DEQ3_A0
                     {0x77, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_A1
                     {0x78, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_A2
                     {0x79, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_B1
                     {0x7a, 0x00, 0x00, 0x00},//##Channel_1_DEQ4_B2
                     {0x7b, 0x20, 0x00, 0x00},//##Channel_1_DEQ4_A0
                     {0x7c, 0x00, 0x00, 0x00},//##Reserve
                     {0x7d, 0x00, 0x00, 0x00},//##Reserve
                     {0x7e, 0x00, 0x00, 0x00},//##Reserve
                     {0x7f, 0x00, 0x00, 0x00},//##Reserve

};

static int m_ram2_tab[][4] = {
                     {0x00, 0x00, 0x00, 0x00},//##Channel_2_EQ1_A1
                     {0x01, 0x00, 0x00, 0x00},//##Channel_2_EQ1_A2
                     {0x02, 0x00, 0x00, 0x00},//##Channel_2_EQ1_B1
                     {0x03, 0x00, 0x00, 0x00},//##Channel_2_EQ1_B2
                     {0x04, 0x20, 0x00, 0x00},//##Channel_2_EQ1_A0
                     {0x05, 0x00, 0x00, 0x00},//##Channel_2_EQ2_A1
                     {0x06, 0x00, 0x00, 0x00},//##Channel_2_EQ2_A2
                     {0x07, 0x00, 0x00, 0x00},//##Channel_2_EQ2_B1
                     {0x08, 0x00, 0x00, 0x00},//##Channel_2_EQ2_B2
                     {0x09, 0x20, 0x00, 0x00},//##Channel_2_EQ2_A0
                     {0x0a, 0x00, 0x00, 0x00},//##Channel_2_EQ3_A1
                     {0x0b, 0x00, 0x00, 0x00},//##Channel_2_EQ3_A2
                     {0x0c, 0x00, 0x00, 0x00},//##Channel_2_EQ3_B1
                     {0x0d, 0x00, 0x00, 0x00},//##Channel_2_EQ3_B2
                     {0x0e, 0x20, 0x00, 0x00},//##Channel_2_EQ3_A0
                     {0x0f, 0x00, 0x00, 0x00},//##Channel_2_EQ4_A1
                     {0x10, 0x00, 0x00, 0x00},//##Channel_2_EQ4_A2
                     {0x11, 0x00, 0x00, 0x00},//##Channel_2_EQ4_B1
                     {0x12, 0x00, 0x00, 0x00},//##Channel_2_EQ4_B2
                     {0x13, 0x20, 0x00, 0x00},//##Channel_2_EQ4_A0
                     {0x14, 0x00, 0x00, 0x00},//##Channel_2_EQ5_A1
                     {0x15, 0x00, 0x00, 0x00},//##Channel_2_EQ5_A2
                     {0x16, 0x00, 0x00, 0x00},//##Channel_2_EQ5_B1
                     {0x17, 0x00, 0x00, 0x00},//##Channel_2_EQ5_B2
                     {0x18, 0x20, 0x00, 0x00},//##Channel_2_EQ5_A0
                     {0x19, 0x00, 0x00, 0x00},//##Channel_2_EQ6_A1
                     {0x1a, 0x00, 0x00, 0x00},//##Channel_2_EQ6_A2
                     {0x1b, 0x00, 0x00, 0x00},//##Channel_2_EQ6_B1
                     {0x1c, 0x00, 0x00, 0x00},//##Channel_2_EQ6_B2
                     {0x1d, 0x20, 0x00, 0x00},//##Channel_2_EQ6_A0
                     {0x1e, 0x00, 0x00, 0x00},//##Channel_2_EQ7_A1
                     {0x1f, 0x00, 0x00, 0x00},//##Channel_2_EQ7_A2
                     {0x20, 0x00, 0x00, 0x00},//##Channel_2_EQ7_B1
                     {0x21, 0x00, 0x00, 0x00},//##Channel_2_EQ7_B2
                     {0x22, 0x20, 0x00, 0x00},//##Channel_2_EQ7_A0
                     {0x23, 0x00, 0x00, 0x00},//##Channel_2_EQ8_A1
                     {0x24, 0x00, 0x00, 0x00},//##Channel_2_EQ8_A2
                     {0x25, 0x00, 0x00, 0x00},//##Channel_2_EQ8_B1
                     {0x26, 0x00, 0x00, 0x00},//##Channel_2_EQ8_B2
                     {0x27, 0x20, 0x00, 0x00},//##Channel_2_EQ8_A0
                     {0x28, 0x00, 0x00, 0x00},//##Channel_2_EQ9_A1
                     {0x29, 0x00, 0x00, 0x00},//##Channel_2_EQ9_A2
                     {0x2a, 0x00, 0x00, 0x00},//##Channel_2_EQ9_B1
                     {0x2b, 0x00, 0x00, 0x00},//##Channel_2_EQ9_B2
                     {0x2c, 0x20, 0x00, 0x00},//##Channel_2_EQ9_A0
                     {0x2d, 0x00, 0x00, 0x00},//##Channel_2_EQ10_A1
                     {0x2e, 0x00, 0x00, 0x00},//##Channel_2_EQ10_A2
                     {0x2f, 0x00, 0x00, 0x00},//##Channel_2_EQ10_B1
                     {0x30, 0x00, 0x00, 0x00},//##Channel_2_EQ10_B2
                     {0x31, 0x20, 0x00, 0x00},//##Channel_2_EQ10_A0
                     {0x32, 0x00, 0x00, 0x00},//##Channel_2_EQ11_A1
                     {0x33, 0x00, 0x00, 0x00},//##Channel_2_EQ11_A2
                     {0x34, 0x00, 0x00, 0x00},//##Channel_2_EQ11_B1
                     {0x35, 0x00, 0x00, 0x00},//##Channel_2_EQ11_B2
                     {0x36, 0x20, 0x00, 0x00},//##Channel_2_EQ11_A0
                     {0x37, 0x00, 0x00, 0x00},//##Channel_2_EQ12_A1
                     {0x38, 0x00, 0x00, 0x00},//##Channel_2_EQ12_A2
                     {0x39, 0x00, 0x00, 0x00},//##Channel_2_EQ12_B1
                     {0x3a, 0x00, 0x00, 0x00},//##Channel_2_EQ12_B2
                     {0x3b, 0x20, 0x00, 0x00},//##Channel_2_EQ12_A0
                     {0x3c, 0x00, 0x00, 0x00},//##Channel_2_EQ13_A1
                     {0x3d, 0x00, 0x00, 0x00},//##Channel_2_EQ13_A2
                     {0x3e, 0x00, 0x00, 0x00},//##Channel_2_EQ13_B1
                     {0x3f, 0x00, 0x00, 0x00},//##Channel_2_EQ13_B2
                     {0x40, 0x20, 0x00, 0x00},//##Channel_2_EQ13_A0
                     {0x41, 0x00, 0x00, 0x00},//##Channel_2_EQ14_A1
                     {0x42, 0x00, 0x00, 0x00},//##Channel_2_EQ14_A2
                     {0x43, 0x00, 0x00, 0x00},//##Channel_2_EQ14_B1
                     {0x44, 0x00, 0x00, 0x00},//##Channel_2_EQ14_B2
                     {0x45, 0x20, 0x00, 0x00},//##Channel_2_EQ14_A0
                     {0x46, 0x00, 0x00, 0x00},//##Channel_2_EQ15_A1
                     {0x47, 0x00, 0x00, 0x00},//##Channel_2_EQ15_A2
                     {0x48, 0x00, 0x00, 0x00},//##Channel_2_EQ15_B1
                     {0x49, 0x00, 0x00, 0x00},//##Channel_2_EQ15_B2
                     {0x4a, 0x20, 0x00, 0x00},//##Channel_2_EQ15_A0
                     {0x4b, 0x40, 0x00, 0x00},//##Channel_2_Mixer1
                     {0x4c, 0x40, 0x00, 0x00},//##Channel_2_Mixer2
                     {0x4d, 0x7f, 0xff, 0xff},//##Channel_2_Prescale
                     {0x4e, 0x7f, 0xff, 0xff},//##Channel_2_Postscale
                     {0x4f, 0xc7, 0xb6, 0x91},//##A0_of_R_channel_SRS_HPF
                     {0x50, 0x38, 0x49, 0x6e},//##A1_of_R_channel_SRS_HPF
                     {0x51, 0x0c, 0x46, 0xf8},//##B1_of_R_channel_SRS_HPF
                     {0x52, 0x0e, 0x81, 0xb9},//##A0_of_R_channel_SRS_LPF
                     {0x53, 0xf2, 0x2c, 0x12},//##A1_of_R_channel_SRS_LPF
                     {0x54, 0x0f, 0xca, 0xbb},//##B1_of_R_channel_SRS_LPF
                     {0x55, 0x00, 0x00, 0x00},//##Reserve
                     {0x56, 0x00, 0x00, 0x00},//##Reserve
                     {0x57, 0x00, 0x00, 0x00},//##Reserve
                     {0x58, 0x00, 0x00, 0x00},//##Reserve
                     {0x59, 0x00, 0x00, 0x00},//##Reserve
                     {0x5a, 0x00, 0x00, 0x00},//##Reserve
                     {0x5b, 0x00, 0x00, 0x00},//##Reserve
                     {0x5c, 0x00, 0x00, 0x00},//##Reserve
                     {0x5d, 0x00, 0x00, 0x00},//##Reserve
                     {0x5e, 0x00, 0x00, 0x00},//##Reserve
                     {0x5f, 0x00, 0x00, 0x00},//##Reserve
                     {0x60, 0x00, 0x00, 0x00},//##Reserve
                     {0x61, 0x00, 0x00, 0x00},//##Reserve
                     {0x62, 0x00, 0x00, 0x00},//##Reserve
                     {0x63, 0x00, 0x00, 0x00},//##Reserve
                     {0x64, 0x00, 0x00, 0x00},//DRC2_Power_Meter
                     {0x65, 0x00, 0x00, 0x00},//DRC4_Power_Mete
                     {0x66, 0x00, 0x00, 0x00},//DRC6_Power_Meter
                     {0x67, 0x00, 0x00, 0x00},//DRC8_Power_Meter
                     {0x68, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_A1
                     {0x69, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_A2
                     {0x6a, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_B1
                     {0x6b, 0x00, 0x00, 0x00},//##Channel_2_DEQ1_B2
                     {0x6c, 0x20, 0x00, 0x00},//##Channel_2_DEQ1_A0
                     {0x6d, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_A1
                     {0x6e, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_A2
                     {0x6f, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_B1
                     {0x70, 0x00, 0x00, 0x00},//##Channel_2_DEQ2_B2
                     {0x71, 0x20, 0x00, 0x00},//##Channel_2_DEQ2_A0
                     {0x72, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_A1
                     {0x73, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_A2
                     {0x74, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_B1
                     {0x75, 0x00, 0x00, 0x00},//##Channel_2_DEQ3_B2
                     {0x76, 0x20, 0x00, 0x00},//##Channel_2_DEQ3_A0
                     {0x77, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_A1
                     {0x78, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_A2
                     {0x79, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_B1
                     {0x7a, 0x00, 0x00, 0x00},//##Channel_2_DEQ4_B2
                     {0x7b, 0x20, 0x00, 0x00},//##Channel_2_DEQ4_A0
                     {0x7c, 0x00, 0x00, 0x00},//##Reserve
                     {0x7d, 0x00, 0x00, 0x00},//##Reserve
                     {0x7e, 0x00, 0x00, 0x00},//##Reserve
                     {0x7f, 0x00, 0x00, 0x00},//##Reserve

};

/* codec private data */
struct ad82584f_priv {
	struct regmap *regmap;
	struct snd_soc_codec *codec;
	struct ad82584f_platform_data *pdata;
#ifdef CONFIG_HAS_EARLYSUSPEND
	struct early_suspend early_suspend;
#endif

   struct i2c_client *control_data;
};

struct ad82584f_priv *ad82584f;
static int ad82584f_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				  int clk_id, unsigned int freq, int dir)
{
	return 0;
}

static int ad82584f_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return 0;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_RIGHT_J:
	case SND_SOC_DAIFMT_LEFT_J:
		break;
	default:
		return 0;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_NB_IF:
		break;
	default:
		return 0;
	}

	return 0;
}

static int ad82584f_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	unsigned int rate;

	rate = params_rate(params);
	pr_debug("rate: %u\n", rate);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S24_LE:
	case SNDRV_PCM_FORMAT_S24_BE:
		pr_debug("24bit\n");

		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		pr_debug("32bit\n");

		break;

	case SNDRV_PCM_FORMAT_S20_3LE:
	case SNDRV_PCM_FORMAT_S20_3BE:
		pr_debug("20bit\n");

		break;
	case SNDRV_PCM_FORMAT_S16_LE:
	case SNDRV_PCM_FORMAT_S16_BE:
		pr_debug("16bit\n");

		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int ad82584f_set_bias_level(struct snd_soc_codec *codec,
				  enum snd_soc_bias_level level)
{
	pr_debug("level = %d\n", level);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* Full power on */
		break;

	case SND_SOC_BIAS_STANDBY:
		break;

	case SND_SOC_BIAS_OFF:
		/* The chip runs through the power down sequence for us. */
		break;
	}
 //      codec->dapm.bias_level = level;
	//codec->component.dapm.bias_level = level;

	return 0;
}

static int ad82584f_startup(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	//int ret;
	struct snd_soc_codec *codec = dai->codec;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {

		printk("%s---------------%d\n", __func__,__LINE__);

		//ret=gpio_request(122,NULL);				// request amp PD pin control GPIO
		//printk(" gpio 122 ret=%d\n",ret);
		//gpio_direction_output(122, 1);		// pull high amp PD pin
		mdelay(20);
		//ad82584f_init(codec);							// init amp again
		snd_soc_write(codec, 0x02, 0x00);   //--unmute amp
	}

  return 0;
}

static void ad82584f_shutdown(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	//int ret;
	struct snd_soc_codec *codec = dai->codec;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		printk("%s---------------%d\n", __func__,__LINE__);
		snd_soc_write(codec, 0x02, 0x7f);					//--mute amp
		//ret=gpio_request(122,NULL);								// request amp PD pin control GPIO
		//printk(" gpio 122 ret=%d\n",ret);
		//gpio_direction_output(122, 0);						// pull low amp PD pin
	}
	return;
}

static const struct snd_soc_dai_ops ad82584f_dai_ops = {
	.startup = ad82584f_startup,
	.shutdown = ad82584f_shutdown,
	.hw_params = ad82584f_hw_params,
	.set_sysclk = ad82584f_set_dai_sysclk,
	.set_fmt = ad82584f_set_dai_fmt,
};

static struct snd_soc_dai_driver ad82584f_dai = {
	.name = "ad82584f",
	.playback = {
		.stream_name = "HIFI Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = AD82584F_RATES,
		.formats = AD82584F_FORMATS,
	},
	.capture = {
		.stream_name ="HIFI Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = AD82584F_RATES,
		.formats = AD82584F_FORMATS,
	},
	.ops = &ad82584f_dai_ops,
};

static int ad82584f_set_eq_drc(struct snd_soc_codec *codec)
{
	u8 i;
	// ch1 ram
	for (i = 0; i < AD82584F_RAM_TABLE_COUNT; i++) {
		snd_soc_write(codec, CFADDR, m_ram1_tab[i][0]);
		snd_soc_write(codec, A1CF1, m_ram1_tab[i][1]);
		snd_soc_write(codec, A1CF2, m_ram1_tab[i][2]);
		snd_soc_write(codec, A1CF3, m_ram1_tab[i][3]);
		snd_soc_write(codec, CFUD, 0x01);
	}
	// ch2 ram
	for (i = 0; i < AD82584F_RAM_TABLE_COUNT; i++) {
		snd_soc_write(codec, CFADDR, m_ram2_tab[i][0]);
		snd_soc_write(codec, A1CF1, m_ram2_tab[i][1]);
		snd_soc_write(codec, A1CF2, m_ram2_tab[i][2]);
		snd_soc_write(codec, A1CF3, m_ram2_tab[i][3]);
		snd_soc_write(codec, CFUD, 0x41);
	}
	return 0;
}
static int ad82584f_reg_init(struct snd_soc_codec *codec)
{
	int i = 0;
	for (i = 0; i < AD82584F_REGISTER_COUNT; i++) {
    if(m_reg_tab[i][0] == 0x02)
    	continue;
		snd_soc_write(codec, m_reg_tab[i][0], m_reg_tab[i][1]);
	};

	return 0;

}
#ifdef	AD82584F_REG_RAM_CHECK
static int ad82584f_reg_check(struct snd_soc_codec *codec)
{
	int i = 0;
	int reg_data = 0;

	for (i = 0; i < AD82584F_REGISTER_COUNT; i++) {
		reg_data = snd_soc_read(codec, m_reg_tab[i][0]);
		printk("ad82584f_reg_init  write 0x%x = 0x%x\n", m_reg_tab[i][0], reg_data);
	};
	return 0;
}

static int ad82584f_eqram1_check(struct snd_soc_codec *codec)
{
	int i = 0;
	int H8_data = 0, M8_data = 0, L8_data = 0;

	for (i = 0; i < AD82584F_RAM_TABLE_COUNT; i++) {
		snd_soc_write(codec, CFADDR, m_ram1_tab[i][0]);			// write ram addr
		snd_soc_write(codec, CFUD, 0x04);										// write read ram cmd

		H8_data = snd_soc_read(codec, A1CF1);
		M8_data = snd_soc_read(codec, A1CF2);
		L8_data = snd_soc_read(codec, A1CF3);
		printk("ad82584f_set_eq_drc ram1  write 0x%x = 0x%x , 0x%x , 0x%x\n", m_ram1_tab[i][0], H8_data,M8_data,L8_data);
	};
	return 0;
}
#endif

static int ad82584f_init(struct snd_soc_codec *codec)
{
	struct ad82584f_platform_data *pdata =NULL;
	int ret;
	unsigned short gpio;

	printk("%s\n", __func__);
	pdata=ad82584f->pdata;

#if  0
	ret = devm_gpio_request_one(codec->dev,pdata->mute_pin, \
                                 GPIOF_OUT_INIT_LOW, \
                                 "ad82584f-mute-pin");				// request AMP_SDB pin control GPIO
	printk(" gpio %d ret=%d\n", pdata->mute_pin, ret);
#endif
	if ( BpGetSpeakerEnGpio( &gpio ) != BP_SUCCESS ) {
		printk("%s: get speaker_en gpio failed\n");
	}
	pdata->amp_power = gpio;
	bcm_gpio_set_dir(pdata->amp_power, 1);
	bcm_gpio_set_data(pdata->amp_power, 1);
#if 0
	mdelay(200);
	gpio_direction_output(pdata->mute_pin,GPIOF_OUT_INIT_HIGH);		// pull high AMP_SDB pin
#endif
	mdelay(20);

    printk("%s---------------%d\n", __func__,__LINE__);

  // software reset amp , if no have hardware reset pin(24pin's ad82584f)
	snd_soc_write(codec, 0x1a, 0x12);//--reset amp
	mdelay(5);
	// set mono
	dev_info(codec->dev, "set ad82584f work in mono mode!\n");
	snd_soc_write(codec, 0x1a, 0x72);//--MONO_EN=1,Normal operation
	mdelay(20);
	snd_soc_write(codec, 0x74, 0x30);//--MONO_KEY hi-byte
	snd_soc_write(codec, 0x75, 0x06);//--MONO_KEY low-byte

	// init AMP
	dev_info(codec->dev, "ad82584f_init!\n");

 	snd_soc_write(codec, 0x02, 0x7f);//--mute amp

	// write amp register
	ad82584f_reg_init(codec);

	snd_soc_write(codec, 0x02, 0x7f);//--mute amp
  udelay(100);
	// write amp ram (eq and drc ... )
	ad82584f_set_eq_drc(codec);
	udelay(100);

#ifdef	AD82584F_REG_RAM_CHECK
	// Please note that the register from 0x1d to 0x2d, from 0x44 to 0x5b, the value what you read(as below)may be different from what you wrote.
	ad82584f_reg_check(codec);
	// Please note that ram1 from 0x64 to 0x67,the value what you read(as below)may be different from what you wrote.
	ad82584f_eqram1_check(codec);
#endif

	snd_soc_write(codec, 0x02, 0x00);//--unmute amp

	return 0;
}

static int ad82584f_probe(struct snd_soc_codec *codec)
{
   //int ret = 0;
   struct ad82584f_priv *ad82584f=NULL;
 	if (codec == NULL) {
	      dev_err(codec->dev, "Codec device not registered\n");
	      return -ENODEV;
	}

	ad82584f= snd_soc_codec_get_drvdata(codec);
	printk("%s enter\n", __func__);


#ifdef CONFIG_HAS_EARLYSUSPEND
//	struct ad82584f_priv *ad82584f = snd_soc_codec_get_drvdata(codec);

	ad82584f->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN;
	ad82584f->early_suspend.suspend = ad82584f_early_suspend;
	ad82584f->early_suspend.resume = ad82584f_late_resume;
	//ad82584f->early_suspend.param = codec;
	register_early_suspend(&(ad82584f->early_suspend));
#endif

	ad82584f_codec = codec;

	//ad82584f->codec = codec;
	codec->control_data = ad82584f->control_data;
	ad82584f_init(codec);
	printk("%s end\n", __func__);
	return 0;
}

static int ad82584f_remove(struct snd_soc_codec *codec)
{
#ifdef CONFIG_HAS_EARLYSUSPEND
	struct ad82584f_priv *ad82584f = snd_soc_codec_get_drvdata(codec);

	unregister_early_suspend(&(ad82584f->early_suspend));
#endif
	return 0;
}

static int ad82584f_suspend(struct snd_soc_codec *codec)
{
	dev_info(codec->dev, "ad82584f_suspend!\n");

	snd_soc_write(codec, 0x02, 0x7f);		// mute

	return 0;
}

static int ad82584f_resume(struct snd_soc_codec *codec)
{
	dev_info(codec->dev, "ad82584f_resume!\n");

	// init ad82584f again
	//ad82584f_init(codec);

	snd_soc_write(codec, 0x02, 0x00);			// unmute

	return 0;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void ad82584f_early_suspend(struct early_suspend *h)
{
}

static void ad82584f_late_resume(struct early_suspend *h)
{
}
#endif

static const struct snd_soc_dapm_widget ad82584f_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", "HIFI Playback", SND_SOC_NOPM, 0, 0),
};



/*
 * I2C Read/Write Functions
 */
static int ad82584f_i2c_read(struct i2c_client *ad82584f_client,
                u8 reg, u8 *value, int len)
{
    int err;
    int tries = 0;

    struct i2c_msg msgs[] = {
        {
         .addr = ad82584f_client->addr,
         .flags = 0,
         .len = 1,
         .buf = &reg,
         },
        {
         .addr = ad82584f_client->addr,
         .flags = I2C_M_RD,
         .len = len,
         .buf = value,
         },
    };

    do {
        err = i2c_transfer(ad82584f_client->adapter, msgs,
                            ARRAY_SIZE(msgs));
        if (err != ARRAY_SIZE(msgs))
            msleep_interruptible(I2C_RETRY_DELAY);
    } while ((err != ARRAY_SIZE(msgs)) && (++tries < I2C_RETRIES));

    if (err != ARRAY_SIZE(msgs)) {
        dev_err(&ad82584f_client->dev, "read transfer error %d\n"
                , err);
        err = -EIO;
    } else {
        err = 0;
    }

    return err;
}
static unsigned int ad82584f_read(struct snd_soc_codec *codec, unsigned int reg)
{
   // struct ad82584f_priv *ad82584f  = snd_soc_codec_get_drvdata(codec);
    u8 data;
    int len = 1;
    int val = -EIO;

    if (ad82584f_i2c_read(codec->control_data, reg & 0xff, &data, len) == 0) {
        val = data;		//(buf[0] << 8 | buf[1]);
    }

    return val;
}
static int ad82584f_i2c_write(struct i2c_client *ad82584f_client,
                u8 *value, u8 len)
{
    int err;
    int tries = 0;
    struct i2c_msg msgs[] = {
        {
         .addr = ad82584f_client->addr,
         .flags = 0,
         .len = len,
         .buf = value,
         },
    };

    do {
        err = i2c_transfer(ad82584f_client->adapter, msgs,
                    ARRAY_SIZE(msgs));
        if (err != ARRAY_SIZE(msgs))
            msleep_interruptible(I2C_RETRY_DELAY);
    } while ((err != ARRAY_SIZE(msgs)) && (++tries < I2C_RETRIES));

    if (err != ARRAY_SIZE(msgs)) {
        dev_err(&ad82584f_client->dev, "write transfer error\n");
        err = -EIO;
    } else {
        err = 0;
    }

    return err;
}
static int ad82584f_write(struct snd_soc_codec *codec, unsigned int reg,
                unsigned int val)
{
    u8 buf[2] = {0, 0};
    int ret;
    buf[0] = (reg & 0xff);
    buf[1] = (val & 0xff);

    ret = ad82584f_i2c_write(codec->control_data, buf, ARRAY_SIZE(buf));

    return ret;
}

static const struct snd_soc_codec_driver soc_codec_dev_ad82584f = {
    .probe   = ad82584f_probe,
    .remove  = ad82584f_remove,
    .suspend = ad82584f_suspend,
    .resume  = ad82584f_resume,
    .read    = ad82584f_read,
    .write   = ad82584f_write,
    .set_bias_level = ad82584f_set_bias_level,
    .reg_cache_size = ARRAY_SIZE(m_reg_tab),
    .reg_word_size  = sizeof(u16),
    .reg_cache_default = m_reg_tab,
#if (KERNEL_VERSION(4, 0, 0) <= LINUX_VERSION_CODE)
    .component_driver = {
#endif
    .controls = ad82584f_snd_controls,
    .num_controls = ARRAY_SIZE(ad82584f_snd_controls),
    .dapm_widgets = ad82584f_dapm_widgets,
    .num_dapm_widgets = ARRAY_SIZE(ad82584f_dapm_widgets),
#if (KERNEL_VERSION(4, 0, 0) <= LINUX_VERSION_CODE)
    }
#endif
};

static int ad82584f_parse_dt(
        struct ad82584f_priv *ad82584f,
        struct device_node *np)
{
    int ret = 0;
//TODO
#if 0
    int amp_power = -1;
    int amp_mute = -1;
	struct gpio_desc *desc;

    amp_power = of_get_named_gpio(np,"amp_power",0);
    if (amp_power < 0){
        pr_err("%s fail to get mute pin from dts!\n", __func__);
        ret = -1;
    }
    ad82584f->pdata->amp_power = amp_power;
    printk("%s pdata->amp_power = %d!\n",__func__,
            ad82584f->pdata->amp_power);

    desc = of_get_named_gpiod_flags(np,"amp_power",  0,  NULL);
	gpiod_set_pull(desc, GPIOD_PULL_UP);

    amp_mute = of_get_named_gpio(np,"amp_mute",0);
    if(amp_mute < 0 ){
        pr_err("%s fail to get amp_mute from dts!\n", __func__);
        ret = -1;
    }
    ad82584f->pdata->mute_pin = amp_mute;
    printk("%s pdata->mute_pin = %d!\n",__func__,
            ad82584f->pdata->mute_pin);
#endif
    return ret;
}
static int ad82584f_i2c_probe(struct i2c_client *i2c,
            const struct i2c_device_id *id)
{
    struct ad82584f_platform_data *pdata;
    int ret;
    printk("%s---------------%d\n", __func__,__LINE__);
    ad82584f = devm_kzalloc(&i2c->dev, sizeof(struct ad82584f_priv),
                   GFP_KERNEL);
    if (!ad82584f)
        return -ENOMEM;
    i2c_set_clientdata(i2c, ad82584f);
    pdata = devm_kzalloc(&i2c->dev, sizeof(struct ad82584f_platform_data), GFP_KERNEL);
    if (!pdata) {
        pr_err("%s failed to kzalloc for ad82584f pdata\n", __func__);
        return -ENOMEM;
    }
    ad82584f->pdata = pdata;
    ad82584f->control_data = i2c;
    ad82584f_parse_dt(ad82584f, i2c->dev.of_node);
    ret = snd_soc_register_codec(&i2c->dev, &soc_codec_dev_ad82584f, &ad82584f_dai, 1);
    if (ret != 0)
       {
        printk("Failed to register codec (%d)\n", ret);
       }
    printk("%s---------------%d probe end\n", __func__,__LINE__);
    return 0;
}

static int ad82584f_i2c_remove(struct i2c_client *client)
{
    snd_soc_unregister_codec(&client->dev);
    return 0;
}

static const struct i2c_device_id ad82584f_i2c_id[] = {
    { "ad82584f", 0 },
    {},
};

MODULE_DEVICE_TABLE(i2c, ad82584f_i2c_id);

static const struct of_device_id ad82584f_of_id[] = {
    { .compatible = "ESMT, ad82584f"},
    { },
};

static struct i2c_driver ad82584f_i2c_driver = {
	.driver = {
		.name = "ad82584f",
		.of_match_table = ad82584f_of_id,
		.owner = THIS_MODULE,
	},
	//.shutdown = ad82584f_i2c_shutdown,
	.probe = ad82584f_i2c_probe,
	.remove = ad82584f_i2c_remove,
	.id_table = ad82584f_i2c_id,
};

static int __init ad82584f_i2c_init(void)
{
	printk("%s\n", __func__);
	return i2c_add_driver(&ad82584f_i2c_driver);
}

static void __exit ad82584f_i2c_exit(void)
{
	i2c_del_driver(&ad82584f_i2c_driver);
}

module_init(ad82584f_i2c_init);
module_exit(ad82584f_i2c_exit);

MODULE_DESCRIPTION("ASoC ad82584f driver");
MODULE_AUTHOR("ESMT Jamie_Wei");
MODULE_LICENSE("GPL");
