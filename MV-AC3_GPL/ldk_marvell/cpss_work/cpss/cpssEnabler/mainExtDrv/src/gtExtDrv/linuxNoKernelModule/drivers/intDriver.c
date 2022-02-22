/*******************************************************************************
Copyright (C) Marvell International Ltd. and its affiliates

This software file (the "File") is owned and distributed by Marvell
International Ltd. and/or its affiliates ("Marvell") under the following
alternative licensing terms.  Once you have made an election to distribute the
File under one of the following license alternatives, please (i) delete this
introductory statement regarding license alternatives, (ii) delete the two
license alternatives that you have not elected to use and (iii) preserve the
Marvell copyright notice above.


********************************************************************************
Marvell GPL License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File in accordance with the terms and conditions of the General
Public License Version 2, June 1991 (the "GPL License"), a copy of which is
available along with the File in the license.txt file or by writing to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 or
on the worldwide web at http://www.gnu.org/licenses/gpl.txt.

THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE IMPLIED
WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY
DISCLAIMED.  The GPL License provides additional details about this warranty
disclaimer.
********************************************************************************
* intDriver.c
*
* DESCRIPTION:
*       mvIntDrv - A simple driver which passes interrupts to user-space
*                  Usage:
*                     fd=open("/dev/mvIntDrv",O_RDWR);
*                     write(fd, "eI", 2)    will enable irq I (0..255)
*                     write(fd, "dI", 2)    will disable irq I (0..255)
*                     write(fd, "EIIII", 5) will enable irq I (0..0xffffffff)
*                     write(fd, "DIIII", 5) will disable irq I (0..0xffffffff)
*                     write(fd, "mBDF",4)   will enable MSI interrupts
*                                           Here B=PCI bus (binary)
*                                           Here D=PCI device (binary)
*                                           Here F=PCI device functin (binary)
*                     write(fd, "MddBDF",6) will enable MSI interrupts
*                                           Here dd=PCI domain, LE
*                                           Here B=PCI bus (binary)
*                                           Here D=PCI device (binary)
*                                           Here F=PCI device functin (binary)
*                     X=write(fd, "cI", 2) will connect irq I (0..255)
*                     X=write(fd, "CIIII", 5) will connect irq I (0..0xffffffff)
*
*                     read(fd,NULL,X) will wait for irq
*
* DEPENDENCIES:
*
*       $Revision: 1 $
*******************************************************************************/
#define MV_DRV_NAME     "mvIntDrv"
#define MV_DRV_MAJOR    244
#define MV_DRV_MINOR    4
#define MV_DRV_FOPS     mvIntDrv_fops
#define MV_DRV_POSTINIT mvIntDrv_postInitDrv
#define MV_DRV_RELEASE  mvIntDrv_releaseDrv
#include "mvDriverTemplate.h"

#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/io.h>

static int                  mvIntDrvNumOpened = 0;


struct interrupt_slot {
	int						used;
	unsigned int            irq;
	struct semaphore        sem;        /* the semaphore on which the user waits */
	struct tasklet_struct	tasklet;
};
#define MAX_INTERRUPTS  32
static struct interrupt_slot mvIntDrv_slots[MAX_INTERRUPTS];


static irqreturn_t prestera_tl_ISR(int irq, void *tl)
{
	/* disable the interrupt vector */
	disable_irq_nosync(irq);
	/* enqueue the PP task BH in the tasklet */
	tasklet_hi_schedule((struct tasklet_struct *)tl);

	return IRQ_HANDLED;
}

void mvPresteraBh (unsigned long data)
{
	/* awake any reading process */
	up(&((struct interrupt_slot *)data)->sem);
}


static int intConnect(unsigned int irq)
{
	int                     slot;
	struct interrupt_slot	*sl;

	/* search for slot */
	for (slot = 0; slot < MAX_INTERRUPTS; slot++)
		if (!mvIntDrv_slots[slot].used)
			break;
	if (slot == MAX_INTERRUPTS) {
		printk(KERN_ERR "intConnect: no free slots\n");
		return -EFAULT;
	}

	sl = &(mvIntDrv_slots[slot]);
	sl->used = 1;
	sl->irq = irq;
	sema_init(&sl->sem, 0);

	tasklet_init(&sl->tasklet, mvPresteraBh, (unsigned long)sl);

	if (request_irq(irq, prestera_tl_ISR,
			IRQF_SHARED,
			"mvIntDrv",
			(void *)&sl->tasklet) != 0) {
		panic("Can not assign IRQ %u to mvIntDrv\n", irq);
		return -EFAULT;
	}

	printk(KERN_DEBUG "intConnect: connected IRQ - %u slot %d\n", irq, slot);
	disable_irq(irq);

	return slot + 1;
}

static int intDisConnect(unsigned int irq)
{

    int slot;
    struct interrupt_slot	*sl;

    for (slot = 0; slot < MAX_INTERRUPTS; slot++) {
        sl = &(mvIntDrv_slots[slot]);
        if (sl->irq==irq) {
            disable_irq_nosync(sl->irq);
            free_irq(sl->irq, (void*)&(sl->tasklet));
            tasklet_kill(&(sl->tasklet));
            sl->used = 0;
            printk(KERN_DEBUG "intDisConnect: disconnected IRQ - %u slot %d\n", irq, slot);
            return slot;
        }
    }
    return 0;
}

static ssize_t mvIntDrv_write(struct file *f, const char *buf, size_t siz, loff_t *off)
{
	char cmdBuf[6];
	unsigned int irq;
	/* write 2 bytes:
	 *  'c' intNo       - connect interrupt, returns slot+1
	 *  'd' intNo       - disable interrupt
	 *  'e' intNo       - enable interrupt
	 *  'C' i i i i     - connect interrupt, returns slot+1
	 *  'R' i i i i     - remove interrupt, returns slot+1
	 *  'D' i i i i     - disable interrupt
	 *  'E' i i i i     - enable interrupt
	 *  'm' bus dev sel - enable MSI interrupts for pci device
	 *
	 * return <1 - error, slot for connect, 0 for enable/disable
	 */
	if (copy_from_user(cmdBuf, buf, ((siz < 6) ? siz : 6))) {
		printk(KERN_ERR "mvIntDrv_write: EFAULT\n");
		return -EFAULT;
	}
        switch (cmdBuf[0]) {
        case 'c': case 'd': case 'e': case 'r':
            irq = (unsigned int)cmdBuf[1];
            break;
        case 'C': case 'D': case 'E': case 'R':
            memcpy(&irq, cmdBuf+1, 4);
            break;
        }

	if (cmdBuf[0] == 'c' || cmdBuf[0] == 'C')
		return intConnect(irq);
	if (cmdBuf[0] == 'r' || cmdBuf[0] == 'R')
		return intDisConnect(irq);
	if (cmdBuf[0] == 'd' || cmdBuf[0] == 'D') {
		disable_irq(irq);
		return 0;
	}
	if (cmdBuf[0] == 'e' || cmdBuf[0] == 'E') {
		enable_irq(irq);
		return 0;
	}
	if (cmdBuf[0] == 'm') {
#ifdef CONFIG_PCI_MSI
		struct pci_dev *pdev;
		pdev = pci_get_bus_and_slot((unsigned)cmdBuf[1],
				PCI_DEVFN((unsigned)cmdBuf[2],(unsigned)cmdBuf[3]));
		if (pdev != NULL) {
			int rc;
			if (pci_dev_msi_enabled(pdev))
				return 0;
			rc = pci_enable_msi(pdev);
			printk("MSI interrupts for device %s %senabled\n",
					pdev->dev.kobj.name, (rc < 0) ? "not " : "");
			return rc;
		}
#else
		return -1;
#endif
	}
	if (cmdBuf[0] == 'M') {
#ifdef CONFIG_PCI_MSI
		struct pci_dev *pdev;
		pdev = pci_get_domain_bus_and_slot(
				(((cmdBuf[2]<<8)&0xff00)|(cmdBuf[1]&0xff)), /* domain */
				(unsigned)cmdBuf[3], /* bus */
				PCI_DEVFN((unsigned)cmdBuf[4],(unsigned)cmdBuf[5]));
		if (pdev != NULL) {
			int rc;
			if (pci_dev_msi_enabled(pdev))
				return 0;
			rc = pci_enable_msi(pdev);
			printk("MSI interrupts for device %s %senabled\n",
					pdev->dev.kobj.name, (rc < 0) ? "not " : "");
			return rc;
		}
#else
		return -1;
#endif
	}

	return -EINVAL;
}

static ssize_t mvIntDrv_read(struct file *f, char *buf, size_t siz, loff_t *off)
{
	struct interrupt_slot	*sl;
	int slot = (int)siz - 1;

	if (slot < 0 || slot >= MAX_INTERRUPTS)
		return -EINVAL;

	sl = &(mvIntDrv_slots[slot]);
	if (!sl->used)
		return -EINVAL;

	/* enable the interrupt vector */
	enable_irq(sl->irq);

	if (down_interruptible(&sl->sem)) {
		disable_irq(sl->irq);
		return -EINTR;
	}

	return 0;
}
static int mvIntDrv_open(struct inode *inode, struct file *file)
{
	mvIntDrvNumOpened++;
	file->private_data = NULL;

	return 0;
}

static int mvIntDrv_release(struct inode *inode, struct file *file)
{
	mvIntDrvNumOpened--;
	if (mvIntDrvNumOpened == 0) {
		/* cleanup */
		int slot;
		struct interrupt_slot *sl;

		for (slot = 0; slot < MAX_INTERRUPTS; slot++) {
			sl = &(mvIntDrv_slots[slot]);
			if (!sl->used)
				continue;
			disable_irq_nosync(sl->irq);
			free_irq(sl->irq, (void*)&(sl->tasklet));
			tasklet_kill(&(sl->tasklet));
			sl->used = 0;
		}
	}
	return 0;
}

static struct file_operations mvIntDrv_fops = {
	.read    = mvIntDrv_read,
	.write   = mvIntDrv_write,
	.open    = mvIntDrv_open,
	.release = mvIntDrv_release /* A.K.A close */
};


static void mvIntDrv_releaseDrv(void)
{
	/* will be called whan all descriptors are closed */
}

static void mvIntDrv_postInitDrv(void)
{
	memset(mvIntDrv_slots, 0, sizeof(mvIntDrv_slots));
	printk(KERN_DEBUG "mvIntDrv major=%d minor=%d\n", major, minor);
}

