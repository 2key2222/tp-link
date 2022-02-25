/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2013 Cavium, Inc.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

#include <asm/mipsregs.h>

#include <asm/octeon/octeon-hw-status.h>
#include <asm/octeon/octeon.h>

/* Module parameter to disable error reporting */
static int disable;
module_param(disable, int, S_IRUGO);

static struct cvmx_error_muxchild *octeon_error_tree_current;

static void octeon_error_tree_remove(int idx, int max_idx, struct cvmx_error_muxchild *n,
				     enum cvmx_error_groups group, int unit)
{
	struct cvmx_error_regbit *bit;
	struct cvmx_error_childbit *child;
	bit = n->bits;

	while (bit && bit->valid) {
		if ( bit->group == group && (unit < 0 || unit == bit->unit)) {
			struct octeon_hw_status_reg r;

			memset(&r, 0, sizeof(r));
			r.reg = n->reg;
			r.mask_reg = n->mask_reg;
			r.bit = bit->bit;
			r.ack_w1c = bit->w1c;
			octeon_hw_status_remove_source(&r);
		}
		bit++;
	}

	child = n->children;

	while (child && child->valid) {
		struct cvmx_error_muxchild *child_bit;
		child_bit = child->children;
		while (child_bit && child_bit->reg) {
			if (WARN(idx + 1 > max_idx, "Maximum depth exceeded: %d", max_idx))
				return;

			octeon_error_tree_remove(idx + 1, max_idx, child_bit, group, unit);
			child_bit++;
		}
		child++;
	}
}

static void octeon_error_tree_add(struct octeon_hw_status_reg *sr,
				  int idx, int max_idx, struct cvmx_error_muxchild *n,
				  enum cvmx_error_groups group, int unit)
{
	struct cvmx_error_regbit *bit;
	struct cvmx_error_childbit *child;
	bit = n->bits;
	memset(&sr[idx], 0, sizeof (sr[idx]));
	sr[idx].reg = n->reg;
	sr[idx].mask_reg = n->mask_reg;

	while (bit && bit->valid) {
		if (bit->group == group && (unit < 0 || unit == bit->unit)) {
			sr[idx].bit = bit->bit;
			sr[idx].ack_w1c = bit->w1c;
			sr[idx].has_child = 0;
			octeon_hw_status_add_source(sr);
			/* Enable it now. */
			octeon_hw_status_enable(n->reg, 1ull << bit->bit);
		}
		bit++;
	}

	sr[idx].ack_w1c = 0;
	child = n->children;

	while (child && child->valid) {
		struct cvmx_error_muxchild *child_bit;
		child_bit = child->children;
		sr[idx].bit = child->bit;
		sr[idx].has_child = 1;
		while (child_bit && child_bit->reg) {
			if (WARN(idx + 1 > max_idx, "Maximum depth exceeded: %d", max_idx))
				return;

			octeon_error_tree_add(sr, idx + 1, max_idx, child_bit, group, unit);
			child_bit++;
		}
		child++;
	}
}

static int octeon_error_tree_map_irq_reg(u64 r)
{
	if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
		if ((0xf8fff & r) == 0x80000)
			return (r & 0x7000) >> 12;
	} else {
		r &= 0xffffffffull;
		switch (r) {
		case 0:
			return 0;
		case 0x108:
		case 0x8000:
			return 1;
		default:
			break;
		}
	}
	WARN(1, "Error: Unknown error tree base: %lx", (unsigned long)r);
	return -ENODEV;
}

static bool octeon_error_tree_find_print(struct cvmx_error_muxchild *r, u64 reg, u8 reg_bit)
{
	struct cvmx_error_childbit *childbit;

	if (reg == r->reg) {
		struct cvmx_error_regbit *bit = r->bits;

		/* found the register. */
		if (WARN(!bit, "Empty bits\n"))
			return false;

		while (bit->valid) {
			if (bit->bit == reg_bit) {
				if (bit->desc)
					pr_err("Error: %s\n", bit->desc);
				else
					pr_err("Error: Status bit %016lx:%u\n", (unsigned long)reg, reg_bit);
				return true;
			}
			bit++;
		}
		return false;
	}
	childbit = r->children;
	while (childbit && childbit->valid) {
		struct cvmx_error_muxchild *children = childbit->children;
		while (children && children->reg) {
			if (octeon_error_tree_find_print(children, reg, reg_bit))
				return true;
			children++;
		}
		childbit++;
	}
	return false;
}

static int octeon_error_tree_hw_status(struct notifier_block *nb, unsigned long val, void *v)
{
	struct octeon_hw_status_data *d = v;
	if (val == OCTEON_HW_STATUS_SOURCE_ASSERTED) {
		bool v = octeon_error_tree_find_print(octeon_error_tree_current, d->reg, d->bit);
		return v ? NOTIFY_STOP : NOTIFY_DONE;
	}
	return NOTIFY_DONE;
}

static struct notifier_block octeon_error_tree_notifier;

int octeon_error_tree_disable(enum cvmx_error_groups group, int unit)
{
	struct cvmx_error_muxchild *base;
	struct cvmx_error_childbit *line;
	int irq_reg;

	if (disable)
		return 0;

	if (!octeon_error_tree_current)
		return -ENODEV;

	base = octeon_error_tree_current->children->children;

	while (base->reg) {
		irq_reg = octeon_error_tree_map_irq_reg(base->reg);
		if (irq_reg < 0)
			return irq_reg;

		line = base->children;
		while (line && line->valid) {
			struct cvmx_error_muxchild *child = line->children;
			while (child->reg) {
				octeon_error_tree_remove(1, 5, child, group, unit);
				child++;
			}
			line++;
		}
		base++;
	}

	return 0;
}
EXPORT_SYMBOL(octeon_error_tree_disable);

int octeon_error_tree_enable(enum cvmx_error_groups group, int unit)
{
	struct octeon_hw_status_reg sr[6];
	struct cvmx_error_muxchild *base;
	struct cvmx_error_childbit *line;
	int irq_reg;

	if (disable)
		return 0;

	if (!octeon_error_tree_current)
		return -ENODEV;

	memset(sr, 0, sizeof(sr));
	base = octeon_error_tree_current->children->children;

	while (base->reg) {
		irq_reg = octeon_error_tree_map_irq_reg(base->reg);
		if (irq_reg < 0)
			return irq_reg;

		line = base->children;
		while (line && line->valid) {
			struct cvmx_error_muxchild *child = line->children;
			sr[0].reg = irq_reg << 6 | line->bit;
			sr[0].reg_is_hwint = 1;
			sr[0].has_child = 1;
			while (child->reg) {
				octeon_error_tree_add(sr, 1, ARRAY_SIZE(sr) - 1, child,
						      group, unit);
				child++;
			}
			line++;
		}
		base++;
	}

	return 0;
}
EXPORT_SYMBOL(octeon_error_tree_enable);

static int __init octeon_error_tree_init(void)
{
	u32 prid = read_c0_prid();
	struct cvmx_error_tree *tree = octeon_error_trees;

	if (disable)
		return 0;

	while (tree->tree) {
		if ((prid & tree->prid_mask) == tree->prid_val) {
			break;
		}
		tree++;
	}
	if (!tree->tree) {
		pr_err("Error: No error tree for prid = 0x%08x\n", prid);
		return -ENODEV;
	}
	pr_notice("Installing handlers for error tree at: %p\n", tree->tree);

	octeon_error_tree_current = tree->tree;

	octeon_error_tree_notifier.notifier_call = octeon_error_tree_hw_status;
	octeon_error_tree_notifier.priority = 0;
	octeon_hw_status_notifier_register(&octeon_error_tree_notifier);

	return octeon_error_tree_enable(CVMX_ERROR_GROUP_INTERNAL, -1);
}
arch_initcall(octeon_error_tree_init);
