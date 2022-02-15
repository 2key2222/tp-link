#include <common.h>
#include <atheros.h>

/* This register defination is not found in each SoC's register defination header file,
 * For AR9344, AR9341 and QCA9558, this register has the same address. */
#define GPIO_IN_ADDRESS			0x18040004

#ifndef FIRMWARE_RECOVERY_GPIO_SCHEME
#error "Please select/create a firmware recovery gpio scheme for your board."
#endif

typedef struct _FW_RECOVERY_GPIO_SCHEME
{
    const char *schemeName;
    void (*schemeInit)  (void);
    int  (*isKeyPressed)(void); /* return 1 means key pressed. */
    void (*turnLedOn)   (void);
    void (*turnLedOff)  (void);
}FW_RECOVERY_GPIO_SCHEME;


static int getKeyValueByGPIO(int gpio)
{
	int val;
	int old_val;

	udelay(1000); /* delay 1ms for input value stabile. by HouXB, 27Apr11 */
	old_val = ath_reg_rd(GPIO_IN_ADDRESS);
	old_val = ((old_val & (1 << gpio)) >> gpio);

	udelay(100);
	val = ath_reg_rd(GPIO_IN_ADDRESS);
	val = ((val & (1 << gpio)) >> gpio);

	/* make sure the btn was pressed. by HouXB, 27Apr11 */
	if(old_val != val)
	{
		return -1;
	}

    return val;
}

static void wr841ndSchemeInit(void)
{
	ath_reg_rmw_set(GPIO_OE_ADDRESS,  (1 << 12));/* Wr841v11 use FactoryResetButton(GPIO12) as input indicator */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS,(1 << 3));/* use WPSLED(GPIO3) as output indicator */
}

static int wr841ndKeyPressed(void)
{
    int ret = 0;
    ret = getKeyValueByGPIO(12);  /* Wr841v11 use FactoryResetButton(GPIO12) as FW Recovery Button */
	if (ret < 0) return 0;        /* No Key Pressed Dectected. */
	return (1-ret);               /* When the key is pressed, the key value is 0 */
}

static void wr841ndTurnLedOn(void)
{
    /* Clear GPIO 15 to turn on WPS LED. */
    ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 << 3));
}

static void wr841ndTurnLedOff(void)
{
    /* Set GPIO 15 to turn off WPS LED. */
    ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 << 3));
}


static FW_RECOVERY_GPIO_SCHEME FWRecoveryWr841ndScheme =
{
    .schemeName   = "WR841V11",
    .schemeInit   = wr841ndSchemeInit,
    .isKeyPressed = wr841ndKeyPressed,
    .turnLedOn    = wr841ndTurnLedOn,
    .turnLedOff   = wr841ndTurnLedOff,
};

static void wr842ndSchemeInit(void)
{
	ath_reg_rmw_set(GPIO_OE_ADDRESS,  (1 << 0)); /* use FactoryResetButton(GPIO0) as input indicator */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS,(1 << 17));/* use WPSLED(GPIO17) as output indicator */
}

static int wr842ndKeyPressed(void)
{
    int ret = 0;
    ret = getKeyValueByGPIO(0);  /* wr842nd use FactoryResetButton(GPIO0) as FW Recovery Button */
	if (ret < 0) return 0;        /* No Key Pressed Dectected. */
	return (1-ret);               /* When the key is pressed, the key value is 0 */
}

static void wr842ndTurnLedOn(void)
{
    /* Clear GPIO 17 to turn on WPS LED. */
    ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 << 17));
}

static void wr842ndTurnLedOff(void)
{
    /* Set GPIO 17 to turn off WPS LED. */
    ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 << 17));
}


static FW_RECOVERY_GPIO_SCHEME FWRecoveryWr842ndScheme =
{
    .schemeName   = "WR842V3",
    .schemeInit   = wr842ndSchemeInit,
    .isKeyPressed = wr842ndKeyPressed,
    .turnLedOn    = wr842ndTurnLedOn,
    .turnLedOff   = wr842ndTurnLedOff,
};


static void wr942ndSchemeInit(void)
{
	ath_reg_rmw_set(GPIO_OE_ADDRESS,  (1 << 1)); /* use FactoryResetButton(GPIO1) as input indicator */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS,(1 << 21));/* use WPSLED(GPIO21) as output indicator */
}

static int wr942ndKeyPressed(void)
{
    int ret = 0;
    ret = getKeyValueByGPIO(1);  /* wr942nd use FactoryResetButton(GPIO0) as FW Recovery Button */
	if (ret < 0) return 0;        /* No Key Pressed Dectected. */
	return (1-ret);               /* When the key is pressed, the key value is 0 */
}

static void wr942ndTurnLedOn(void)
{
    /* Clear GPIO 17 to turn on WPS LED. */
    ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 << 21));
}

static void wr942ndTurnLedOff(void)
{
    /* Set GPIO 17 to turn off WPS LED. */
    ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 << 21));
}


static FW_RECOVERY_GPIO_SCHEME FWRecoveryWr942ndScheme =
{
    .schemeName   = "WR942V1",
    .schemeInit   = wr942ndSchemeInit,
    .isKeyPressed = wr942ndKeyPressed,
    .turnLedOn    = wr942ndTurnLedOn,
    .turnLedOff   = wr942ndTurnLedOff,
};

#if defined(CONFIG_PRODUCT_C7V4)
/* Archer C7 v4 */
#define AP151_GPIO_SHIFT_OE     1
#define AP151_GPIO_SHIFT_SER    14
#define AP151_GPIO_SHIFT_SRCLK  15
#define AP151_GPIO_SHIFT_RCLK   16
#define AP151_GPIO_SHIFT_SRCLR  21

static void c7v4SchemeInit(void)
{
	ath_reg_rmw_set(GPIO_OE_ADDRESS,  (1 << 5));   /* use FactoryResetButton(GPIO5) as input indicator */
	//ath_reg_rmw_clear(GPIO_OE_ADDRESS,(1 << 21));/* use WPSLED(GPIO21) as output indicator */
	ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 <<  AP151_GPIO_SHIFT_OE));
	ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 <<  AP151_GPIO_SHIFT_SER) | \
		(1 <<  AP151_GPIO_SHIFT_SRCLK) | (1 << AP151_GPIO_SHIFT_SRCLR) | (1 <<  AP151_GPIO_SHIFT_RCLK));
	ath_reg_rmw_clear(GPIO_OE_ADDRESS, (1 << 1) | (1 << 14) | (1 << 15) | (1 << 16) | (1 << 21));

	udelay(1);
	ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 <<  AP151_GPIO_SHIFT_SRCLR));
	udelay(1);
}

static int c7v4KeyPressed(void)
{
    int ret = 0;
    ret = getKeyValueByGPIO(5);   /* c7v4 use FactoryResetButton(GPIO5) as FW Recovery Button */
    if (ret < 0) return 0;        /* No Key Pressed Dectected. */
    return (1-ret);               /* When the key is pressed, the key value is 0 */
}

static void c7v4TurnLedOn(void)
{
    /* Clear GPIO 17 to turn on WPS LED. */
    //ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 << 21));
    shift_register_set(0x7f);
	ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 <<  AP151_GPIO_SHIFT_OE));
}

static void c7v4TurnLedOff(void)
{
    /* Set GPIO 17 to turn off WPS LED. */
    //ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 << 21));
    ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 <<  AP151_GPIO_SHIFT_OE));
    shift_register_set(0xff);
}

static FW_RECOVERY_GPIO_SCHEME FWRecoveryC7V4Scheme =
{
	.schemeName   = "C7V4",
	.schemeInit   = NULL,
	.isKeyPressed = NULL,
	.turnLedOn	  = NULL,
	.turnLedOff   = NULL,
};

#endif

#if defined(CONFIG_PRODUCT_C7V5)
static void c7v5SchemeInit(void)
{
	ath_reg_rmw_set(GPIO_OE_ADDRESS,  (1 << 5)); /* use FactoryResetButton(GPIO1) as input indicator */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS,(1 << 1));/* use WPSLED(GPIO1) as output indicator */
}

static int c7v5KeyPressed(void)
{
    int ret = 0;
    ret = getKeyValueByGPIO(5);   /* c7v4/c7v5 use FactoryResetButton(GPIO5) as FW Recovery Button */
    if (ret < 0) return 0;        /* No Key Pressed Dectected. */
    return (1-ret);               /* When the key is pressed, the key value is 0 */
}

static void c7v5TurnLedOn(void)
{
    /* Clear GPIO 1 to turn on WPS LED. */
    ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 << 1));
}

static void c7v5TurnLedOff(void)
{
    /* Set GPIO 1 to turn off WPS LED. */
    ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 << 1));
}


static FW_RECOVERY_GPIO_SCHEME FWRecoveryC7V5Scheme =
{
    .schemeName   = "C7V5",
    .schemeInit   = NULL,
    .isKeyPressed = NULL,
    .turnLedOn    = NULL,
    .turnLedOff   = NULL,
};
#endif

#if defined(CONFIG_PRODUCT_WR1043NV5)
static void wr1043nv5SchemeInit(void)
{
	ath_reg_rmw_set(GPIO_OE_ADDRESS,  (1 << 2)); /* use FactoryResetButton(GPIO1) as input indicator */
	ath_reg_rmw_clear(GPIO_OE_ADDRESS,(1 << 1));/* use WPSLED(GPIO21) as output indicator */
}

static int wr1043nv5KeyPressed(void)
{
    int ret = 0;
    ret = getKeyValueByGPIO(2);  /* use FactoryResetButton(GPIO0) as FW Recovery Button */
	if (ret < 0) return 0;        /* No Key Pressed Dectected. */
	return (1-ret);               /* When the key is pressed, the key value is 0 */
}

static void wr1043nv5TurnLedOn(void)
{
    /* Clear GPIO 1 to turn on WPS LED. */
    ath_reg_rmw_clear(GPIO_OUT_ADDRESS, (1 << 1));
}

static void wr1043nv5TurnLedOff(void)
{
    /* Set GPIO 1 to turn off WPS LED. */
    ath_reg_rmw_set(GPIO_OUT_ADDRESS, (1 << 1));
}


static FW_RECOVERY_GPIO_SCHEME FWRecoveryWr1043nv5Scheme =
{
    .schemeName   = "WR1043NV5",
    .schemeInit   = NULL,
    .isKeyPressed = NULL,
    .turnLedOn    = NULL,
    .turnLedOff   = NULL,
};
#endif

FW_RECOVERY_GPIO_SCHEME *FWRecoverySchemeTbl[] =
{
    &FWRecoveryWr841ndScheme,
    &FWRecoveryWr842ndScheme,
    &FWRecoveryWr942ndScheme,
    NULL,
};

static FW_RECOVERY_GPIO_SCHEME *FW_recovery_scheme = NULL;


static void FWRecoverySchemeInit(void)
{
    int   i = 0;
    const char *pSchemeName = NULL;

	if (FW_recovery_scheme) return;

/* 
 * In double boot mode, factory boot has loaded second boot to the 
 * 0x80010000, so can't use static func address in compiling process
 */
#if defined(CONFIG_PRODUCT_C7V4)
	if (!strcmp(FWRecoveryC7V4Scheme.schemeName, FIRMWARE_RECOVERY_GPIO_SCHEME))
	{
		FWRecoveryC7V4Scheme.schemeInit = c7v4SchemeInit;
		FWRecoveryC7V4Scheme.isKeyPressed = c7v4KeyPressed;
		FWRecoveryC7V4Scheme.turnLedOn  = c7v4TurnLedOn;
		FWRecoveryC7V4Scheme.turnLedOff = c7v4TurnLedOff;
		FW_recovery_scheme = &FWRecoveryC7V4Scheme;
		return;
	}
#endif

#if defined(CONFIG_PRODUCT_C7V5)
	if (!strcmp(FWRecoveryC7V5Scheme.schemeName, FIRMWARE_RECOVERY_GPIO_SCHEME))
	{
		FWRecoveryC7V5Scheme.schemeInit = c7v5SchemeInit;
		FWRecoveryC7V5Scheme.isKeyPressed = c7v5KeyPressed;
		FWRecoveryC7V5Scheme.turnLedOn  = c7v5TurnLedOn;
		FWRecoveryC7V5Scheme.turnLedOff = c7v5TurnLedOff;
		FW_recovery_scheme = &FWRecoveryC7V5Scheme;
		return;
	}
#endif

#if defined(CONFIG_PRODUCT_WR1043NV5)
	if (!strcmp(FWRecoveryWr1043nv5Scheme.schemeName, FIRMWARE_RECOVERY_GPIO_SCHEME))
	{
		FWRecoveryWr1043nv5Scheme.schemeInit = wr1043nv5SchemeInit;
		FWRecoveryWr1043nv5Scheme.isKeyPressed = wr1043nv5KeyPressed;
		FWRecoveryWr1043nv5Scheme.turnLedOn  = wr1043nv5TurnLedOn;
		FWRecoveryWr1043nv5Scheme.turnLedOff = wr1043nv5TurnLedOff;
		FW_recovery_scheme = &FWRecoveryWr1043nv5Scheme;
		return;
	}
#endif

    for (i = 0; FWRecoverySchemeTbl[i] != NULL; i++)
    {
        pSchemeName = FWRecoverySchemeTbl[i]->schemeName;
        if (!strcmp(pSchemeName, FIRMWARE_RECOVERY_GPIO_SCHEME))
        {
            FW_recovery_scheme = FWRecoverySchemeTbl[i];
            break;
        }
    }

    if (!FW_recovery_scheme)
    {
        printf("Firmware Recovery GPIO Scheme Init Failed.\n");
    }

    return;
}


void fwrecovery_gpio_init(void)
{
    void (*initHandle)(void) = NULL;

    FWRecoverySchemeInit();

    if (!FW_recovery_scheme) return;
    
    initHandle = FW_recovery_scheme->schemeInit;
    if (initHandle) initHandle();

    return;
}

int fwrecovery_rst_btn_pressed(void)
{
    int (*isKeyPressedHandle)(void) = NULL;
    int ret = 0;

    if (!FW_recovery_scheme) return 0;
    
    isKeyPressedHandle = FW_recovery_scheme->isKeyPressed;
    if (isKeyPressedHandle) ret = isKeyPressedHandle();

    return ret;
}


void fwrecovery_led_on(void)
{	
    void (*turnLedOnHandle)(void) = NULL;

    FWRecoverySchemeInit();

    if (!FW_recovery_scheme) return;
    
    turnLedOnHandle = FW_recovery_scheme->turnLedOn;
    if (turnLedOnHandle) turnLedOnHandle();

    return;
}

void fwrecovery_led_off(void)
{
    void (*turnLedOffHandle)(void) = NULL;

    FWRecoverySchemeInit();

    if (!FW_recovery_scheme) return;
    
    turnLedOffHandle = FW_recovery_scheme->turnLedOff;
    if (turnLedOffHandle) turnLedOffHandle();

    return;
}
