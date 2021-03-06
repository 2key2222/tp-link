/*
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
*/

#ifndef __PROC_CMD__
#define __PROC_CMD__
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_CMD_STRING_SIZE	200
#define PROC_CMD_ARGS_MAX	20
#define PROC_CMD_TABLE_SIZE_MAX	20

struct proc_cmd_ops {
	const char *name;
	int (*do_command)(int argc, char *argv[]);
};

struct proc_cmd_table {
	const char *module_name;
	int size;
	struct proc_cmd_ops *ops;
};

static int proc_cmd_open(struct inode *inode, struct file *f)
{
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,8,0)
	f->private_data = PDE_DATA(inode);
#else
	f->private_data = PDE(inode)->data;
#endif
	if (!f->private_data)
		return -EPERM;
	return 0;
}

static ssize_t proc_cmd_write(struct file *file, const char __user *buffer,
			  size_t count, loff_t *pos)
{
	char cmd_line[PROC_CMD_STRING_SIZE];
	char *ptr = cmd_line;
	char *argv[PROC_CMD_ARGS_MAX];
	int  i, argc = 0;
	struct proc_cmd_table *table;
	table = (struct proc_cmd_table *) file->private_data;
	if ((count <= 1) || (buffer == NULL))
		goto help;
	if (count > PROC_CMD_STRING_SIZE)
		count = PROC_CMD_STRING_SIZE;
	memset(cmd_line, 0, PROC_CMD_STRING_SIZE);
	if (copy_from_user(cmd_line, buffer, count))
		return count;

	if (table && table->module_name)
		pr_info("%s: proc cmd - %s",
			table->module_name, cmd_line);

	/* Parse command line */
	while ((argc < PROC_CMD_ARGS_MAX) &&
	       ((argv[argc] = strsep(&ptr, " ")) != NULL)) {
		if ((argv[argc][0] != 0x00) &&
		    (argv[argc][0] != 0x0A)) {
			/* Ignore white spaces and newline*/
			argc++;
		}
	}

	/* last argument may contain newline, remove it */
	if (argc) {
		ptr = strstr(argv[argc-1], "\n");
		if (ptr)
			*ptr = 0x00;
	}

	if (!argc)
		goto help;

	if (!table)
		return count;

	for (i = 0; table && i < table->size; i++) {
		if (strcasecmp(table->ops[i].name, argv[0]) == 0) {
			if (table->ops[i].do_command)
				table->ops[i].do_command(argc, argv);
			goto done;
		}
	}
help:
	if (table) {
		pr_info("List of Commands:\n");
		for (i = 0; i < table->size; i++)
			pr_info("%s\n", table->ops[i].name);
	}
done:
	return count;

}

static const struct file_operations proc_cmd_fops = {
	.owner    = THIS_MODULE,
	.open     = proc_cmd_open,
	.write    = proc_cmd_write,
};

static inline
struct proc_dir_entry *proc_create_cmd(const char *name,
				       struct proc_dir_entry *parent,
				       struct proc_cmd_table *table)
{
	if (!table || !name || !parent)
		return NULL;
	if (table->size > PROC_CMD_TABLE_SIZE_MAX)
		return NULL;
	return proc_create_data(name,
				S_IRUGO | S_IWUGO,
				parent,
				&proc_cmd_fops,
				table);
}
#endif
