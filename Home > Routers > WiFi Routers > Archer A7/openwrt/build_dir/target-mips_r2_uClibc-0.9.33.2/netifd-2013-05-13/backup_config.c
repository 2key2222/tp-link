#include "backup_config.h"

static struct uci_context *bk_uci_ctx = NULL;
static struct uci_package *bk_uci_pkg = NULL;
static enum conn_mode curr_conn_mode = CONN_MODE_CABLE_ONLY;
static enum network_type current_network = NETWORK_TYPE_WIRED;
static int curr_nw_status = 0;

char *network_type_str[] = {
	"",
	"WIRED",
	"MOBILE",
	""
};

#define CONNECT_IFACE_WAN       	"wan"
#define CONNECT_IFACE_INTERNET  	"internet"
#define CONNECT_IFACE_MOBILE		"mobile"

enum network_type get_network_type(const char* name)
{
	if (strcmp(name, CONNECT_IFACE_WAN) == 0 ||
		strcmp(name, CONNECT_IFACE_INTERNET) == 0)
	{
		return NETWORK_TYPE_WIRED;
	}
	else if (strcmp(name, CONNECT_IFACE_MOBILE) == 0)
	{
		return NETWORK_TYPE_MOBILE;
	}
	return NETWORK_TYPE_MAX;
}

int set_curr_nw_status(int ns)
{
	curr_nw_status = ns;
	return 0;
}

int get_curr_nw_status()
{
	return curr_nw_status;
}

bool backup_auto_dial(const char* ifname)
{
	enum network_type nt = get_network_type(ifname);
	bool ret = true;

	switch (curr_conn_mode)
	{
	case CONN_MODE_CABLE_PREFERRED:
		if (!(curr_nw_status & 0x1))	/* primary connection is online */
		{
			break;
		}
	case CONN_MODE_CABLE_ONLY:
		if (nt == NETWORK_TYPE_MOBILE)
		{
			ret = false;
		}
		break;
	case CONN_MODE_MOBILE_PREFERRED:
		if (!(curr_nw_status & 0x1))
		{
			break;
		}
	case CONN_MODE_MOBILE_ONLY:
		if (nt == NETWORK_TYPE_WIRED)
		{
			ret = false;
		}
		break;
	default:
		break;
	}
	return ret;
}

int set_ubus_curr_nw(enum network_type type)
{
	if (type != NETWORK_TYPE_WIRED && type != NETWORK_TYPE_MOBILE)
	{
		return -1;
	}
	current_network = type;
	return 0;
}

char* get_ubus_curr_nw()
{
	if (current_network < NETWORK_TYPE_NONE || current_network > NETWORK_TYPE_MAX)
	{
		return NULL;
	}
	return network_type_str[current_network];
}

static char* bk_config_option_str(const char *section_name, const char *name)
{
	struct uci_package *pkg = bk_uci_pkg;
	struct uci_section *section = NULL;

	section = uci_lookup_section(bk_uci_ctx, pkg, section_name);
	if (!section)
	{
		return NULL;
	}
	return (char *)uci_lookup_option_string(bk_uci_ctx, section, name);
}

static int config_option_bool(const char *section_name, const char *name, bool *enable)
{
	char *val = bk_config_option_str(section_name, name);
	if (!val)
	{
		return -1;
	}

	if (strcmp(val, "on") == 0)
	{
		*enable = true;
	}
	else
	{
		*enable = false;
	}

	return 0;
}

static int config_option_int(const char *section_name, const char *name, int *val)
{
	char *str = bk_config_option_str(section_name, name);
	unsigned long tmp;

	if (!str)
	{
		return -1;
	}

	tmp = strtoul(str, NULL, 10);
	if (tmp == ULONG_MAX)
	{
		return -1;
	}

	*val = (int)tmp;

	return 0;
}

static int bk_uci_init()
{
	int ret = 0;
	bk_uci_ctx = uci_alloc_context();
	if (bk_uci_ctx == NULL)
	{
		return -1;
	}

	ret = uci_load(bk_uci_ctx, BACKUP_UCI_CFG, &bk_uci_pkg);
	if (ret != 0)
	{
		uci_free_context(bk_uci_ctx);
		bk_uci_ctx = NULL;
	}

	return ret;
}

static void bk_uci_exit()
{
	if (bk_uci_ctx && bk_uci_pkg)
	{
		uci_unload(bk_uci_ctx, bk_uci_pkg);
		bk_uci_pkg = NULL;
		uci_free_context(bk_uci_ctx);
		bk_uci_ctx = NULL;
	}
	return;
}

int uci_bk_cfg_get(struct nw_backup_cfg *bk_cfg)
{
	int ret = 0;
	int tmp = 0;

	if (bk_cfg == NULL)
	{
		return -1;
	}

	memset(bk_cfg, 0, sizeof(struct nw_backup_cfg));

	ret = bk_uci_init();
	if (ret != 0)
	{
		return ret;
	}

	ret = config_option_bool("backup", "enable", &bk_cfg->use_backup);
	if (ret != 0)
	{
		goto exit;
	}

	ret = config_option_int("backup", "preferred", &tmp);
	if (ret != 0)
	{
		goto exit;
	}
	curr_conn_mode = bk_cfg->mode = (enum conn_mode)tmp;

exit:
	bk_uci_exit();

	return ret;
}

