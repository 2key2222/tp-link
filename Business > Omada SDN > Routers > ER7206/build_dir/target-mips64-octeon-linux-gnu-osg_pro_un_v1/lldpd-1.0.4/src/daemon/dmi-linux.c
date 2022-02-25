/* -*- mode: c; c-file-style: "openbsd" -*- */
/*
 * Copyright (c) 2009 Vincent Bernat <bernat@luffy.cx>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "lldpd.h"
#include <unistd.h>
#include "json/json_object.h"
#include "json/json_util.h"
#ifdef ENABLE_LLDPMED
	/* Fill in inventory stuff:
	    - hardware version: /sys/class/dmi/id/product_version
	    - firmware version: /sys/class/dmi/id/bios_version
	    - software version: `uname -r`
	    - serial number: /sys/class/dmi/id/product_serial
	    - manufacturer: /sys/class/dmi/id/sys_vendor
	    - model: /sys/class/dmi/id/product_name
	    - asset: /sys/class/dmi/id/chassis_asset_tag
	*/

static char*
dmi_get(char *file)
{
	int dmi, s;
	char buffer[100] = {};

	log_debug("localchassis", "DMI request for file %s", file);
	if ((dmi = priv_open(file)) < 0) {
		log_debug("localchassis", "cannot get DMI file %s", file);
		return NULL;
	}
	if ((s = read(dmi, buffer, sizeof(buffer))) == -1) {
		log_debug("localchassis", "cannot read DMI file %s", file);
		close(dmi);
		return NULL;
	}
	close(dmi);
	buffer[sizeof(buffer) - 1] = '\0';
	if ((s > 0) && (buffer[s-1] == '\n'))
		buffer[s-1] = '\0';
	if (strlen(buffer))
		return strdup(buffer);
	return NULL;
}

#ifndef TP_CUSTOM
char*
dmi_hw()
{
	return dmi_get(SYSFS_CLASS_DMI "product_version");
}

char*
dmi_fw()
{
	return dmi_get(SYSFS_CLASS_DMI "bios_version");
}

char*
dmi_sn()
{
	return dmi_get(SYSFS_CLASS_DMI "product_serial");
}

char*
dmi_manuf()
{
	return dmi_get(SYSFS_CLASS_DMI "sys_vendor");
}

char*
dmi_model()
{
	return dmi_get(SYSFS_CLASS_DMI "product_name");
}

char*
dmi_asset()
{
	return dmi_get(SYSFS_CLASS_DMI "chassis_asset_tag");
}
#else
#define DEVICE_INFO_PATH	("/tmp/device-info.json")
#define FIRWARE_INFO_PATH	("/tmp/firmware-info.json")

static char* json_get_value(const char *path, const char *key)
{
	struct json_object *pObj = NULL;
	struct json_object *pItem = NULL;
	const char *retStr = NULL;

	if (path == NULL || key == NULL)
	{
		return NULL;
	}
	
	pObj = json_object_from_file(path);
	if (pObj == NULL)
	{
		goto RET;
	}

	json_object_object_get_ex(pObj, key, &pItem);
	if (pItem == NULL)
	{
		goto RET;
	}

	retStr = json_object_get_string(pItem);
	if (retStr == NULL)
	{
		goto RET;
	}
	
	retStr = strdup(retStr);
	
RET:
	if (pObj)
	{
		json_object_put(pObj);
	}

	return retStr;

}

char*
dmi_hw()
{
	return json_get_value(DEVICE_INFO_PATH, "model_version");
}

char*
dmi_fw()
{
	return json_get_value(FIRWARE_INFO_PATH, "software-version");
}

char*
dmi_sn()
{
	return NULL;
}

char*
dmi_manuf()
{
	return json_get_value(DEVICE_INFO_PATH, "manufacturer_name");
}

char*
dmi_model()
{
	return json_get_value(DEVICE_INFO_PATH, "model_name");
}

char*
dmi_asset()
{
	return NULL;
}

#endif

#endif
