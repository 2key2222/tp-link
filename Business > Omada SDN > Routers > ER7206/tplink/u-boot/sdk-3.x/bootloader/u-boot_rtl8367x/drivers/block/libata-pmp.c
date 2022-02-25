/*
 * libata-pmp.c - libata port multiplier support
 *
 * Copyright (c) 2007  SUSE Linux Products GmbH
 * Copyright (c) 2007  Tejun Heo <teheo@suse.de>
 * Copyright (c) 2013  Cavium, Inc. <support@cavium.com>
 *
 * This file is released under the GPLv2.
 */
#define DEBUG
#include <common.h>
#include <malloc.h>
#include <linux/dma-direction.h>
#include <libata.h>
#include <ata.h>
#ifdef CONFIG_AHCI
#include <ahci.h>
#endif

extern struct ata_port_operations sata_port_ops;

const struct ata_port_operations sata_pmp_port_ops = {
	.inherits		= &sata_port_ops,
	.pmp_hardreset		= sata_std_hardreset,
	.pmp_postreset		= ata_std_postreset,
};

/**
 *	sata_pmp_read - read PMP register
 *	@link: link to read PMP register for
 *	@reg: register to read
 *	@r_val: resulting value
 *
 *	Read PMP register.
 *
 *	LOCKING:
 *	Kernel thread context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask on failure.
 */
static unsigned int sata_pmp_read(struct ata_link *link, int reg, u32 *r_val)
{
	struct ata_port *ap = link->ap;
	struct ata_taskfile tf;
	struct ata_device *pmp_dev = &link->device[0];
	unsigned int err_mask;

	debug("%s(%d, 0x%x, 0x%p)\n", __func__, ap->port_no, reg, r_val);

	ata_tf_init(pmp_dev, &tf);
	tf.command = ATA_CMD_PMP_READ;
	tf.protocol = ATA_PROT_NODATA;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;
	tf.feature = reg;
	tf.device = link->pmp;
	debug("  map: 0x%x\n", link->pmp);

	err_mask = ata_exec_internal(pmp_dev, &tf, NULL, 0, DMA_NONE, NULL, 0,
				     SATA_PMP_RW_TIMEOUT);
	if (err_mask) {
		debug("%s: err mask: 0x%x\n", __func__, err_mask);
		return err_mask;
	}

	*r_val = tf.nsect | (tf.lbal << 8) | (tf.lbam << 16) | (tf.lbah << 24);
	debug("%s: rval: 0x%x\n", __func__, *r_val);
	return 0;
}

/**
 *	sata_pmp_write - write PMP register
 *	@link: link to write PMP register for
 *	@reg: register to write
 *	@r_val: value to write
 *
 *	Write PMP register.
 *
 *	LOCKING:
 *	Kernel thread context (may sleep).
 *
 *	RETURNS:
 *	0 on success, AC_ERR_* mask on failure.
 */
static unsigned int sata_pmp_write(struct ata_link *link, int reg, u32 val)
{
	struct ata_port *ap = link->ap;
	struct ata_device *pmp_dev = ap->link.device;
	struct ata_taskfile tf;

	debug("%s(%d, 0x%x, 0x%x)\n", __func__, ap->port_no, reg, val);
	ata_tf_init(pmp_dev, &tf);
	tf.command = ATA_CMD_PMP_WRITE;
	tf.protocol = ATA_PROT_NODATA;
	tf.flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48;
	tf.feature = reg;
	tf.device = link->pmp;
	tf.nsect = val & 0xff;
	tf.lbal = (val >> 8) & 0xff;
	tf.lbam = (val >> 16) & 0xff;
	tf.lbah = (val >> 24) & 0xff;

	return ata_exec_internal(pmp_dev, &tf, NULL, 0, DMA_NONE, NULL, 0,
				 SATA_PMP_RW_TIMEOUT);
}

/**
 *	sata_pmp_scr_read - read PSCR
 *	@link: ATA link to read PSCR for
 *	@reg: PSCR to read
 *	@r_val: resulting value
 *
 *	Read PSCR @reg into @r_val for @link, to be called from
 *	ata_scr_read().
 *
 *	LOCKING:
 *	Kernel thread context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -errno on failure.
 */
int sata_pmp_scr_read(struct ata_link *link, int reg, u32 *r_val)
{
	unsigned int err_mask;

	debug("%s(%d, %d, 0x%x\n", __func__, link->ap->port_no, reg, r_val);
	if (reg > SATA_PMP_PSCR_CONTROL)
		return -EINVAL;

	err_mask = sata_pmp_read(link, reg, r_val);
	debug("%s(%d, 0x%x) = 0x%x\n", __func__, link->ap->port_no, reg, *r_val);
	if (err_mask) {
		printf("failed to read SCR %d (Emask=0x%x)\n", reg, err_mask);
		return -EIO;
	}
	debug("%s: r_val: 0x%x\n", __func__, *r_val);
	return 0;
}

/**
 *	sata_pmp_scr_write - write PSCR
 *	@link: ATA link to write PSCR for
 *	@reg: PSCR to write
 *	@val: value to be written
 *
 *	Write @val to PSCR @reg for @link, to be called from
 *	ata_scr_write() and ata_scr_write_flush().
 *
 *	LOCKING:
 *	Kernel thread context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -errno on failure.
 */
int sata_pmp_scr_write(struct ata_link *link, int reg, u32 val)
{
	unsigned int err_mask;

	if (reg > SATA_PMP_PSCR_CONTROL)
		return -EINVAL;

	debug("%s(%d, 0x%x, 0x%x)\n", __func__, link->ap->port_no, reg, val);
	err_mask = sata_pmp_write(link, reg, val);
	if (err_mask) {
		printf("failed to write SCR %d (Emask=0x%x)\n",
		       reg, err_mask);
		return -EIO;
	}
	return 0;
}
/**
 *	sata_pmp_read_gscr - read GSCR block of SATA PMP
 *	@link: PMP device link
 *	@gscr: buffer to read GSCR block into
 *
 *	Read selected PMP GSCRs from the PMP at @dev.  This will serve
 *	as configuration and identification info for the PMP.
 *
 *	LOCKING:
 *	Kernel thread context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -errno on failure.
 */
static int sata_pmp_read_gscr(struct ata_link *link, u32 *gscr)
{
	static const int gscr_to_read[] = { 0, 1, 2, 32, 33, 64, 96 };
	int i;

	debug("%s(0x%p (%d), 0x%p)\n", __func__, link, link->ap->port_no, gscr);
	for (i = 0; i < ARRAY_SIZE(gscr_to_read); i++) {
		int reg = gscr_to_read[i];
		unsigned int err_mask;

		debug(" reg[%d]: 0x%x\n", i, reg);
		err_mask = sata_pmp_read(link, reg, &gscr[reg]);
		if (err_mask) {
			printf("failed to read PMP GSCR[%d] (Emask=0x%x)\n",
			       reg, err_mask);
			return -EIO;
		}
	}
	debug("%s EXIT\n", __func__);
	return 0;
}

static const char *sata_pmp_spec_rev_str(const u32 *gscr)
{
	u32 rev = gscr[SATA_PMP_GSCR_REV];

	if (rev & (1 << 3))
		return "1.2";
	if (rev & (1 << 2))
		return "1.1";
	if (rev & (1 << 1))
		return "1.0";
	return "<unknown>";
}

#define PMP_GSCR_SII_POL 129

static int sata_pmp_configure(struct ata_device *dev, int print_info)
{
	struct ata_port *ap = dev->link->ap;
	u32 *gscr = dev->gscr;
	u16 vendor = sata_pmp_gscr_vendor(gscr);
	u16 devid = sata_pmp_gscr_devid(gscr);
	unsigned int err_mask = 0;
	const char *reason;
	int nr_ports, rc;

	debug("%s(%d, %d)\n", __func__, ap->port_no, print_info);
	nr_ports = sata_pmp_gscr_ports(gscr);
	debug("  %d total ports\n", nr_ports);
	debug("  gscr: %p\n", gscr);

	if (nr_ports <= 0 || nr_ports > SATA_PMP_MAX_PORTS) {
		debug("  nr_ports %d is invalid\n", nr_ports);
		rc = -EINVAL;
		reason = "invalid nr_ports";
		goto fail;
	}

	if ((ap->flags & ATA_FLAG_AN) &&
	    (gscr[SATA_PMP_GSCR_FEAT] & SATA_PMP_FEAT_NOTIFY))
		dev->flags |= ATA_DFLAG_AN;

	/* monitor SERR_PHYRDY_CHG on fan-out ports */
	err_mask = sata_pmp_write(dev->link, SATA_PMP_GSCR_ERROR_EN,
				  SERR_PHYRDY_CHG);
	if (err_mask) {
		rc = -EIO;
		reason = "failed to write GSCR_ERROR_EN";
		goto fail;
	}

	/* Disable sending Early R_OK.
	 * With "cached read" HDD testing and multiple ports busy on a SATA
	 * host controller, 3726 PMP will very rarely drop a deferred
	 * R_OK that was intended for the host. Symptom will be all
	 * 5 drives under test will timeout, get reset, and recover.
	 */
	if (vendor == 0x1095 && devid == 0x3726) {
		u32 reg;
		debug(" Handling device Silicon Image 1095:3726\n");
		err_mask = sata_pmp_read(&ap->link, PMP_GSCR_SII_POL, &reg);
		if (err_mask) {
			rc = -EIO;
			reason = "failed to read Sil3726 Private Register";
			goto fail;
		}
		reg &= ~0x1;
		err_mask = sata_pmp_write(&ap->link, PMP_GSCR_SII_POL, reg);
		if (err_mask) {
			rc = -EIO;
			reason = "failed to write Sil3726 Private Register";
			goto fail;
		}
	}

	if (print_info || 1) {
		printf("Port Multiplier %s, "
		       "0x%04x:0x%04x r%d, %d ports, feat 0x%x/0x%x\n",
		       sata_pmp_spec_rev_str(gscr), vendor, devid,
		       sata_pmp_gscr_rev(gscr),
		       nr_ports, gscr[SATA_PMP_GSCR_FEAT_EN],
		       gscr[SATA_PMP_GSCR_FEAT]);

		if (!(dev->flags & ATA_DFLAG_AN))
			printf("Asynchronous notification not supported, "
			       "hotplug won't work on fan-out ports. Use warm-plug instead.\n");
	}

	return 0;

 fail:
	printf("failed to configure Port Multiplier (%s, Emask=0x%x)\n",
	       reason, err_mask);
	return rc;
}

static int sata_pmp_init_links (struct ata_port *ap, int nr_ports)
{
	struct ata_link *pmp_link = ap->pmp_link;
	int i, err = 0;

	debug("%s(%d, %d)\n", __func__, ap->port_no, nr_ports);
	if (!pmp_link) {
		debug("  allocating link info\n");
		pmp_link = calloc(sizeof(pmp_link[0]), SATA_PMP_MAX_PORTS);
		if (!pmp_link)
			return -ENOMEM;

		for (i = 0; i < SATA_PMP_MAX_PORTS; i++)
			ata_link_init(ap, &pmp_link[i], i);

		ap->pmp_link = pmp_link;
		debug("  ap(%d) pmp_link = 0x%p\n", ap->port_no, pmp_link);
		for (i = 0; i < SATA_PMP_MAX_PORTS; i++) {
#warning TODO?
#if 0
			err = ata_tlink_add(&pmp_link[i]);
			if (err) {
				goto err_tlink;
			}
#endif
		}
	}

	for (i = 0; i < nr_ports; i++) {
		struct ata_link *link = &pmp_link[i];

		link->flags = 0;
		/* Should now reset all links */
	}

	return 0;

#if 0
err_tlink:
	while (--i >= 0)
		ata_tlink_delete(&pmp_link[i]);
	free(pmp_link);
	ap->pmp_link = NULL;
	return err;
#endif
}

/**
 *	sata_pmp_attach - attach a SATA PMP device
 *	@dev: SATA PMP device to attach
 *
 *	Configure and attach SATA PMP device @dev.  This function is
 *	also responsible for allocating and initializing PMP links.
 *
 *	LOCKING:
 *	Kernel thread context (may sleep).
 *
 *	RETURNS:
 *	0 on success, -errno on failure.
 */
int sata_pmp_attach(struct ata_device *dev)
{
	struct ata_link *link = dev->link;
	struct ata_port *ap = link->ap;
	unsigned long flags;
	struct ata_link *tlink;
	int rc;

	debug("%s(%d)\n", __func__, ap->port_no);
	/* is it hanging off the right place? */
	if (!sata_pmp_supported(ap)) {
		printf("AHCI host does not support Port Multiplier\n");
		return -EINVAL;
	}

	if (!ata_is_host_link(link)) {
		printf("Port Multipliers cannot be nested\n");
		return -EINVAL;
	}

	if (link->pmp) {
		printf("Port Multiplier must be the first device\n");
		return -EINVAL;
	}

	link->pmp = SATA_PMP_CTRL_PORT;
	debug("%s: pmp: 0x%x\n", __func__, link->pmp);
	/* read GSCR block */
	rc = sata_pmp_read_gscr(link, dev->gscr);
	if (rc)
		goto fail;

	/* config PMP */
	debug("%s: Configuring PMP\n", __func__);
	rc = sata_pmp_configure(dev, 1);
	if (rc)
		goto fail;

	debug("%s: pmp: 0x%x\n", __func__, link->pmp);
	debug("%s: initializing links\n", __func__);
	rc = sata_pmp_init_links(ap, sata_pmp_gscr_ports(dev->gscr));
	if (rc) {
		printf("failed to initialize PMP links\n");
		goto fail;
	}

	/* attach it */
	debug("%s: pmp: 0x%x\n", __func__, link->pmp);
	ap->nr_pmp_links = sata_pmp_gscr_ports(dev->gscr);
	debug("%s: %d links\n", __func__, ap->nr_pmp_links);
	if (ap->ops->pmp_attach) {
		debug("%s: Calling pmp_attach %p\n", __func__,
		      ap->ops->pmp_attach);
		ap->ops->pmp_attach(ap);
	} else {
		debug("No pmp attach op\n");
	}

	debug("%s: pmp: 0x%x\n", __func__, link->pmp);
	debug("%s: Initializing speed\n", __func__);
	ata_for_each_link(tlink, ap, EDGE)
		sata_link_init_spd(tlink);

	debug("%s: pmp: 0x%x\n", __func__, link->pmp);
	debug("%s: EXIT\n", __func__);
	return 0;

 fail:
	printf("%s: failed, rc: %d\n", __func__, rc);
	link->pmp = 0;
	return rc;
}
