/*
 * netifd - network interface daemon
 * Copyright (C) 2012 Felix Fietkau <nbd@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <libubox/blobmsg_json.h>

#include "netifd.h"
#include "interface.h"
#include "interface-ip.h"
#include "proto.h"
#include "system.h"

static int proto_fd = -1;

#define PROTO_3G_NAME "3g"

enum proto_shell_sm {
	S_IDLE,
	S_SETUP,
	S_SETUP_ABORT,
	S_TEARDOWN,
};

struct proto_shell_handler {
	struct list_head list;
	struct proto_handler proto;
	struct config_param_list config;
	char *config_buf;
	bool init_available;
	char script_name[];
};

struct proto_shell_dependency {
	struct list_head list;

	struct proto_shell_state *proto;
	struct interface_user dep;

	union if_addr host;
	bool v6;

	char interface[];
};

struct proto_shell_state {
	struct interface_proto_state proto;
	struct proto_shell_handler *handler;
	struct blob_attr *config;

	struct uloop_timeout teardown_timeout;

	struct netifd_process script_task;
	struct netifd_process proto_task;

	enum proto_shell_sm sm;
	bool proto_task_killed;

	int last_error;

	struct list_head deps;
};

static void
proto_shell_check_dependencies(struct proto_shell_state *state)
{
	struct proto_shell_dependency *dep;
	bool available = true;

	list_for_each_entry(dep, &state->deps, list) {
		if (dep->dep.iface)
			continue;

		available = false;
		break;
	}

	interface_set_available(state->proto.iface, available);
}

static void
proto_shell_if_up_cb(struct interface_user *dep, struct interface *iface,
		     enum interface_event ev);
static void
proto_shell_if_down_cb(struct interface_user *dep, struct interface *iface,
		       enum interface_event ev);

static void
proto_shell_update_host_dep(struct proto_shell_dependency *dep)
{
	struct interface *iface = NULL;

	if (dep->dep.iface)
		goto out;

	if (dep->interface[0])
		iface = vlist_find(&interfaces, dep->interface, iface, node);

	iface = interface_ip_add_target_route(&dep->host, dep->v6, iface);
	if (!iface)
		goto out;

	interface_remove_user(&dep->dep);
	dep->dep.cb = proto_shell_if_down_cb;
	interface_add_user(&dep->dep, iface);

out:
	proto_shell_check_dependencies(dep->proto);
}

static void
proto_shell_clear_host_dep(struct proto_shell_state *state)
{
	struct proto_shell_dependency *dep, *tmp;

	list_for_each_entry_safe(dep, tmp, &state->deps, list) {
		interface_remove_user(&dep->dep);
		list_del(&dep->list);
		free(dep);
	}
}

static int
proto_shell_handler(struct interface_proto_state *proto,
		    enum interface_proto_cmd cmd, bool force)
{
	struct proto_shell_state *state;
	struct proto_shell_handler *handler;
	struct netifd_process *proc;
	static char error_buf[32];
	const char *argv[7];
	char *envp[2];
	const char *action;
	char *config;
	int ret, i = 0, j = 0;

	state = container_of(proto, struct proto_shell_state, proto);
	handler = state->handler;
	proc = &state->script_task;

	if (cmd == PROTO_CMD_SETUP) {
		action = "setup";
		state->last_error = -1;
		proto_shell_clear_host_dep(state);
		state->sm = S_SETUP;
	} else {
		if (state->sm == S_TEARDOWN)
			return 0;

		if (state->script_task.uloop.pending) {
			if (state->sm != S_SETUP_ABORT) {
				uloop_timeout_set(&state->teardown_timeout, 1000);
				kill(state->script_task.uloop.pid, SIGTERM);
				if (state->proto_task.uloop.pending)
				{
					/* ugly.... just for 3g dail to avoid pppd send SIGTERM back to netifd and kill netifd */
					if (strcmp(handler->proto.name, PROTO_3G_NAME) == 0)
					{
						kill(state->proto_task.uloop.pid, SIGKILL);
					}
					else
					{
						kill(state->proto_task.uloop.pid, SIGTERM);
					}
				}
				state->sm = S_SETUP_ABORT;
			}
			return 0;
		}

		action = "teardown";
		state->sm = S_TEARDOWN;
		if (state->last_error >= 0) {
			snprintf(error_buf, sizeof(error_buf), "ERROR=%d", state->last_error);
			envp[j++] = error_buf;
		}
		uloop_timeout_set(&state->teardown_timeout, 5000);
	}

	config = blobmsg_format_json(state->config, true);
	if (!config)
		return -1;

	argv[i++] = handler->script_name;
	argv[i++] = handler->proto.name;
	argv[i++] = action;
	argv[i++] = proto->iface->name;
	argv[i++] = config;
	if (proto->iface->main_dev.dev)
		argv[i++] = proto->iface->main_dev.dev->ifname;
	argv[i] = NULL;
	envp[j] = NULL;

	ret = netifd_start_process(argv, envp, proc);
	free(config);

	return ret;
}

static void
proto_shell_if_up_cb(struct interface_user *dep, struct interface *iface,
		     enum interface_event ev)
{
	struct proto_shell_dependency *pdep;

	if (ev != IFEV_UP)
		return;

	pdep = container_of(dep, struct proto_shell_dependency, dep);
	proto_shell_update_host_dep(pdep);
}

static void
proto_shell_if_down_cb(struct interface_user *dep, struct interface *iface,
		       enum interface_event ev)
{
	struct proto_shell_dependency *pdep;
	struct proto_shell_state *state;

	if (ev == IFEV_UP)
		return;

	pdep = container_of(dep, struct proto_shell_dependency, dep);
	interface_remove_user(dep);
	dep->cb = proto_shell_if_up_cb;
	interface_add_user(dep, NULL);

	state = pdep->proto;
	if (state->sm == S_IDLE) {
		state->proto.proto_event(&state->proto, IFPEV_LINK_LOST);
		proto_shell_handler(&state->proto, PROTO_CMD_TEARDOWN, false);
	}
}

static void
proto_shell_task_finish(struct proto_shell_state *state,
			struct netifd_process *task)
{
	switch (state->sm) {
	case S_IDLE:
		if (task == &state->proto_task)
			state->proto.proto_event(&state->proto, IFPEV_LINK_LOST);
		/* fall through */
	case S_SETUP:
		if (task == &state->proto_task)
			proto_shell_handler(&state->proto, PROTO_CMD_TEARDOWN,
					    false);
		break;

	case S_SETUP_ABORT:
		if (state->script_task.uloop.pending ||
		    state->proto_task.uloop.pending)
			break;

		uloop_timeout_cancel(&state->teardown_timeout);
		state->sm = S_IDLE;
		proto_shell_handler(&state->proto, PROTO_CMD_TEARDOWN, false);
		break;

	case S_TEARDOWN:
		if (state->script_task.uloop.pending)
			break;

		if (state->proto_task.uloop.pending) {
			if (!state->proto_task_killed)
				kill(state->proto_task.uloop.pid, SIGTERM);
			break;
		}

		uloop_timeout_cancel(&state->teardown_timeout);
		state->sm = S_IDLE;
		state->proto.proto_event(&state->proto, IFPEV_DOWN);
		break;
	}
}

static void
proto_shell_teardown_timeout_cb(struct uloop_timeout *timeout)
{
	struct proto_shell_state *state;

	state = container_of(timeout, struct proto_shell_state, teardown_timeout);

	netifd_kill_process(&state->script_task);
	netifd_kill_process(&state->proto_task);
	proto_shell_task_finish(state, NULL);
}

static void
proto_shell_script_cb(struct netifd_process *p, int ret)
{
	struct proto_shell_state *state;

	state = container_of(p, struct proto_shell_state, script_task);
	proto_shell_task_finish(state, p);
}

static void
proto_shell_task_cb(struct netifd_process *p, int ret)
{
	struct proto_shell_state *state;

	state = container_of(p, struct proto_shell_state, proto_task);

	if (state->sm == S_IDLE || state->sm == S_SETUP)
		state->last_error = WEXITSTATUS(ret);

	proto_shell_task_finish(state, p);
}

static void
proto_shell_free(struct interface_proto_state *proto)
{
	struct proto_shell_state *state;

	state = container_of(proto, struct proto_shell_state, proto);
	uloop_timeout_cancel(&state->teardown_timeout);
	proto_shell_clear_host_dep(state);
	netifd_kill_process(&state->script_task);
	netifd_kill_process(&state->proto_task);
	free(state->config);
	free(state);
}

static void
proto_shell_parse_route_list(struct interface *iface, struct blob_attr *attr,
			     bool v6)
{
	struct blob_attr *cur;
	int rem;

	blobmsg_for_each_attr(cur, attr, rem) {
		if (blobmsg_type(cur) != BLOBMSG_TYPE_TABLE) {
			DPRINTF("Ignore wrong route type: %d\n", blobmsg_type(cur));
			continue;
		}

		interface_ip_add_route(iface, cur, v6);
	}
}

static void
proto_shell_parse_data(struct interface *iface, struct blob_attr *attr)
{
	struct blob_attr *cur;
	int rem;

	blobmsg_for_each_attr(cur, attr, rem)
		interface_add_data(iface, cur);
}

static struct device *
proto_shell_create_tunnel(const char *name, struct blob_attr *attr)
{
	struct device *dev;
	struct blob_buf b;

	memset(&b, 0, sizeof(b));
	blob_buf_init(&b, 0);
	blob_put(&b, 0, blobmsg_data(attr), blobmsg_data_len(attr));
	dev = device_create(name, &tunnel_device_type, blob_data(b.head));
	blob_buf_free(&b);

	return dev;
}

enum {
	NOTIFY_ACTION,
	NOTIFY_ERROR,
	NOTIFY_COMMAND,
	NOTIFY_ENV,
	NOTIFY_SIGNAL,
	NOTIFY_AVAILABLE,
	NOTIFY_LINK_UP,
	NOTIFY_IFNAME,
	NOTIFY_ADDR_EXT,
	NOTIFY_ROUTES,
	NOTIFY_ROUTES6,
	NOTIFY_TUNNEL,
	NOTIFY_DATA,
	NOTIFY_KEEP,
	NOTIFY_HOST,
	NOTIFY_DNS,
	NOTIFY_DNS_SEARCH,
	__NOTIFY_LAST
};

static const struct blobmsg_policy notify_attr[__NOTIFY_LAST] = {
	[NOTIFY_ACTION] = { .name = "action", .type = BLOBMSG_TYPE_INT32 },
	[NOTIFY_ERROR] = { .name = "error", .type = BLOBMSG_TYPE_ARRAY },
	[NOTIFY_COMMAND] = { .name = "command", .type = BLOBMSG_TYPE_ARRAY },
	[NOTIFY_ENV] = { .name = "env", .type = BLOBMSG_TYPE_ARRAY },
	[NOTIFY_SIGNAL] = { .name = "signal", .type = BLOBMSG_TYPE_INT32 },
	[NOTIFY_AVAILABLE] = { .name = "available", .type = BLOBMSG_TYPE_BOOL },
	[NOTIFY_LINK_UP] = { .name = "link-up", .type = BLOBMSG_TYPE_BOOL },
	[NOTIFY_IFNAME] = { .name = "ifname", .type = BLOBMSG_TYPE_STRING },
	[NOTIFY_ADDR_EXT] = { .name = "address-external", .type = BLOBMSG_TYPE_BOOL },
	[NOTIFY_ROUTES] = { .name = "routes", .type = BLOBMSG_TYPE_ARRAY },
	[NOTIFY_ROUTES6] = { .name = "routes6", .type = BLOBMSG_TYPE_ARRAY },
	[NOTIFY_TUNNEL] = { .name = "tunnel", .type = BLOBMSG_TYPE_TABLE },
	[NOTIFY_DATA] = { .name = "data", .type = BLOBMSG_TYPE_TABLE },
	[NOTIFY_KEEP] = { .name = "keep", .type = BLOBMSG_TYPE_BOOL },
	[NOTIFY_HOST] = { .name = "host", .type = BLOBMSG_TYPE_STRING },
	[NOTIFY_DNS] = { .name = "dns", .type = BLOBMSG_TYPE_ARRAY },
	[NOTIFY_DNS_SEARCH] = { .name = "dns_search", .type = BLOBMSG_TYPE_ARRAY },
};

static int
proto_shell_update_link(struct proto_shell_state *state, struct blob_attr *data, struct blob_attr **tb)
{
	struct interface *iface = state->proto.iface;
	struct blob_attr *cur;
	struct device *dev;
	const char *devname;
	int dev_create = 1;
	bool addr_ext = false;
	bool keep = false;
	bool up;

	if (!tb[NOTIFY_LINK_UP])
		return UBUS_STATUS_INVALID_ARGUMENT;

	up = blobmsg_get_bool(tb[NOTIFY_LINK_UP]);
	if (!up) {
		state->proto.proto_event(&state->proto, IFPEV_LINK_LOST);
		return 0;
	}

	if ((cur = tb[NOTIFY_KEEP]) != NULL)
		keep = blobmsg_get_bool(cur);

	if ((cur = tb[NOTIFY_ADDR_EXT]) != NULL) {
		addr_ext = blobmsg_get_bool(cur);
		if (addr_ext)
			dev_create = 2;
	}

	if (!tb[NOTIFY_IFNAME]) {
		if (!iface->main_dev.dev)
			return UBUS_STATUS_INVALID_ARGUMENT;
	} else if (!keep || iface->state != IFS_UP) {
		keep = false;
		devname = blobmsg_data(tb[NOTIFY_IFNAME]);
		if (tb[NOTIFY_TUNNEL]) {
			dev = proto_shell_create_tunnel(devname,
				tb[NOTIFY_TUNNEL]);
			if (!dev)
				return UBUS_STATUS_INVALID_ARGUMENT;
		} else {
			dev = device_get(devname, dev_create);
			if (!dev)
				return UBUS_STATUS_NOT_FOUND;
		}

		interface_set_l3_dev(iface, dev);
		device_claim(&iface->l3_dev);
		device_set_present(dev, true);
	}

	if (!keep)
		interface_update_start(iface);

	proto_apply_ip_settings(iface, data, addr_ext);

	if ((cur = tb[NOTIFY_ROUTES]) != NULL)
		proto_shell_parse_route_list(state->proto.iface, cur, false);

	if ((cur = tb[NOTIFY_ROUTES6]) != NULL)
		proto_shell_parse_route_list(state->proto.iface, cur, true);

	if ((cur = tb[NOTIFY_DNS]))
		interface_add_dns_server_list(&iface->proto_ip, cur);

	if ((cur = tb[NOTIFY_DNS_SEARCH]))
		interface_add_dns_search_list(&iface->proto_ip, cur);

	interface_update_complete(state->proto.iface);

	if (!keep)
		state->proto.proto_event(&state->proto, IFPEV_UP);
	state->sm = S_IDLE;

	if ((cur = tb[NOTIFY_DATA]))
		proto_shell_parse_data(state->proto.iface, cur);

	return 0;
}

static bool
fill_string_list(struct blob_attr *attr, char **argv, int max)
{
	struct blob_attr *cur;
	int argc = 0;
	int rem;

	if (!attr)
		goto out;

	blobmsg_for_each_attr(cur, attr, rem) {
		if (blobmsg_type(cur) != BLOBMSG_TYPE_STRING)
			return false;

		if (!blobmsg_check_attr(cur, NULL))
			return false;

		argv[argc++] = blobmsg_data(cur);
		if (argc == max - 1)
			return false;
	}

out:
	argv[argc] = NULL;
	return true;
}

static int
proto_shell_run_command(struct proto_shell_state *state, struct blob_attr **tb)
{
	static char *argv[64];
	static char *env[32];

	if (!tb[NOTIFY_COMMAND])
		goto error;

	if (!fill_string_list(tb[NOTIFY_COMMAND], argv, ARRAY_SIZE(argv)))
		goto error;

	if (!fill_string_list(tb[NOTIFY_ENV], env, ARRAY_SIZE(env)))
		goto error;

	netifd_start_process((const char **) argv, (char **) env, &state->proto_task);

	return 0;

error:
	return UBUS_STATUS_INVALID_ARGUMENT;
}

static int
proto_shell_kill_command(struct proto_shell_state *state, struct blob_attr **tb)
{
	unsigned int signal = ~0;

	if (tb[NOTIFY_SIGNAL])
		signal = blobmsg_get_u32(tb[NOTIFY_SIGNAL]);

	if (signal > 31)
		signal = SIGTERM;

	if (state->proto_task.uloop.pending) {
		state->proto_task_killed = true;
		/* ugly.... just for 3g dail to avoid pppd send SIGTERM back to netifd and kill netifd */
		if (strcmp(state->handler->proto.name, PROTO_3G_NAME) == 0)
		{
			kill(state->proto_task.uloop.pid, SIGKILL);
		}
		else
		{
			kill(state->proto_task.uloop.pid, signal);
		}
	}

	return 0;
}

static int
proto_shell_notify_error(struct proto_shell_state *state, struct blob_attr **tb)
{
	struct blob_attr *cur;
	char *data[16];
	int n_data = 0;
	int rem;

	if (!tb[NOTIFY_ERROR])
		return UBUS_STATUS_INVALID_ARGUMENT;

	blobmsg_for_each_attr(cur, tb[NOTIFY_ERROR], rem) {
		if (n_data + 1 == ARRAY_SIZE(data))
			goto error;

		if (blobmsg_type(cur) != BLOBMSG_TYPE_STRING)
			goto error;

		if (!blobmsg_check_attr(cur, NULL))
			goto error;

		data[n_data++] = blobmsg_data(cur);
	}

	if (!n_data)
		goto error;

	interface_add_error(state->proto.iface, state->handler->proto.name,
			data[0], (const char **) &data[1], n_data - 1);

	return 0;

error:
	return UBUS_STATUS_INVALID_ARGUMENT;
}

static int
proto_shell_block_restart(struct proto_shell_state *state, struct blob_attr **tb)
{
	state->proto.iface->autostart = false;
	return 0;
}

static int
proto_shell_set_available(struct proto_shell_state *state, struct blob_attr **tb)
{
	if (!tb[NOTIFY_AVAILABLE])
		return UBUS_STATUS_INVALID_ARGUMENT;

	interface_set_available(state->proto.iface, blobmsg_get_bool(tb[NOTIFY_AVAILABLE]));
	return 0;
}

static int
proto_shell_add_host_dependency(struct proto_shell_state *state, struct blob_attr **tb)
{
	struct proto_shell_dependency *dep;
	struct blob_attr *host = tb[NOTIFY_HOST];
	struct blob_attr *ifname = tb[NOTIFY_IFNAME];
	size_t ifnamelen = (ifname) ? blobmsg_data_len(ifname) : 1;

	if (!host)
		return UBUS_STATUS_INVALID_ARGUMENT;

	dep = calloc(1, sizeof(*dep) + ifnamelen);
	if (inet_pton(AF_INET, blobmsg_data(host), &dep->host) < 1) {
		if (inet_pton(AF_INET6, blobmsg_data(host), &dep->host) < 1) {
			free(dep);
			return UBUS_STATUS_INVALID_ARGUMENT;
		} else {
			dep->v6 = true;
		}
	}

	dep->proto = state;
	if (ifname)
		memcpy(dep->interface, blobmsg_data(ifname), ifnamelen);
	else
		dep->interface[0] = 0;

	dep->dep.cb = proto_shell_if_up_cb;
	interface_add_user(&dep->dep, NULL);
	list_add(&dep->list, &state->deps);
	proto_shell_update_host_dep(dep);
	if (!dep->dep.iface)
		return UBUS_STATUS_NOT_FOUND;

	return 0;
}

static int
proto_shell_setup_failed(struct proto_shell_state *state)
{
	switch (state->sm) {
	case S_IDLE:
		state->proto.proto_event(&state->proto, IFPEV_LINK_LOST);
		/* fall through */
	case S_SETUP:
		proto_shell_handler(&state->proto, PROTO_CMD_TEARDOWN, false);
		break;
	default:
		break;
	}
	return 0;
}

static int
proto_shell_notify(struct interface_proto_state *proto, struct blob_attr *attr)
{
	struct proto_shell_state *state;
	struct blob_attr *tb[__NOTIFY_LAST];

	state = container_of(proto, struct proto_shell_state, proto);

	blobmsg_parse(notify_attr, __NOTIFY_LAST, tb, blob_data(attr), blob_len(attr));
	if (!tb[NOTIFY_ACTION])
		return UBUS_STATUS_INVALID_ARGUMENT;

	switch(blobmsg_get_u32(tb[NOTIFY_ACTION])) {
	case 0:
		return proto_shell_update_link(state, attr, tb);
	case 1:
		return proto_shell_run_command(state, tb);
	case 2:
		return proto_shell_kill_command(state, tb);
	case 3:
		return proto_shell_notify_error(state, tb);
	case 4:
		return proto_shell_block_restart(state, tb);
	case 5:
		return proto_shell_set_available(state, tb);
	case 6:
		return proto_shell_add_host_dependency(state, tb);
	case 7:
		return proto_shell_setup_failed(state);
	default:
		return UBUS_STATUS_INVALID_ARGUMENT;
	}
}

static struct interface_proto_state *
proto_shell_attach(const struct proto_handler *h, struct interface *iface,
		   struct blob_attr *attr)
{
	struct proto_shell_state *state;

	state = calloc(1, sizeof(*state));
	INIT_LIST_HEAD(&state->deps);

	state->config = malloc(blob_pad_len(attr));
	if (!state->config)
		goto error;

	memcpy(state->config, attr, blob_pad_len(attr));
	state->proto.free = proto_shell_free;
	state->proto.notify = proto_shell_notify;
	state->proto.cb = proto_shell_handler;
	state->teardown_timeout.cb = proto_shell_teardown_timeout_cb;
	state->script_task.cb = proto_shell_script_cb;
	state->script_task.dir_fd = proto_fd;
	state->script_task.log_prefix = iface->name;
	state->proto_task.cb = proto_shell_task_cb;
	state->proto_task.dir_fd = proto_fd;
	state->proto_task.log_prefix = iface->name;
	state->handler = container_of(h, struct proto_shell_handler, proto);

	return &state->proto;

error:
	free(state);
	return NULL;
}

static json_object *
check_type(json_object *obj, json_type type)
{
	if (!obj)
		return NULL;

	if (json_object_get_type(obj) != type)
		return NULL;

	return obj;
}

static inline json_object *
get_field(json_object *obj, const char *name, json_type type)
{
	return check_type(json_object_object_get(obj, name), type);
}

static char *
proto_shell_parse_config(struct config_param_list *config, json_object *obj)
{
	struct blobmsg_policy *attrs;
	char *str_buf, *str_cur;
	int str_len = 0;
	int i;

	config->n_params = json_object_array_length(obj);
	attrs = calloc(1, sizeof(*attrs) * config->n_params);
	if (!attrs)
		return NULL;

	config->params = attrs;
	for (i = 0; i < config->n_params; i++) {
		json_object *cur, *name, *type;

		cur = check_type(json_object_array_get_idx(obj, i), json_type_array);
		if (!cur)
			goto error;

		name = check_type(json_object_array_get_idx(cur, 0), json_type_string);
		if (!name)
			goto error;

		type = check_type(json_object_array_get_idx(cur, 1), json_type_int);
		if (!type)
			goto error;

		attrs[i].name = json_object_get_string(name);
		attrs[i].type = json_object_get_int(type);
		if (attrs[i].type > BLOBMSG_TYPE_LAST)
			goto error;

		str_len += strlen(attrs[i].name) + 1;
	}

	str_buf = malloc(str_len);
	if (!str_buf)
		goto error;

	str_cur = str_buf;
	for (i = 0; i < config->n_params; i++) {
		const char *name = attrs[i].name;

		attrs[i].name = str_cur;
		str_cur += sprintf(str_cur, "%s", name) + 1;
	}

	return str_buf;

error:
	free(attrs);
	config->n_params = 0;
	return NULL;
}

static void
proto_shell_add_handler(const char *script, json_object *obj)
{
	struct proto_shell_handler *handler;
	struct proto_handler *proto;
	json_object *config, *tmp;
	const char *name;
	char *str;

	if (!check_type(obj, json_type_object))
		return;

	tmp = get_field(obj, "name", json_type_string);
	if (!tmp)
		return;

	name = json_object_get_string(tmp);

	handler = calloc_a(sizeof(*handler) + strlen(script) + 1,
			   &str, strlen(name) + 1);
	if (!handler)
		return;

	strcpy(handler->script_name, script);
	strcpy(str, name);

	proto = &handler->proto;
	proto->name = str;
	proto->config_params = &handler->config;
	proto->attach = proto_shell_attach;

	tmp = get_field(obj, "no-device", json_type_boolean);
	if (tmp && json_object_get_boolean(tmp))
		handler->proto.flags |= PROTO_FLAG_NODEV;

	tmp = get_field(obj, "available", json_type_boolean);
	if (tmp && json_object_get_boolean(tmp))
		handler->proto.flags |= PROTO_FLAG_INIT_AVAILABLE;

	config = get_field(obj, "config", json_type_array);
	if (config)
		handler->config_buf = proto_shell_parse_config(&handler->config, config);

	DPRINTF("Add handler for script %s: %s\n", script, proto->name);
	add_proto_handler(proto);
}

static void proto_shell_add_script(const char *name)
{
	struct json_tokener *tok = NULL;
	json_object *obj;
	static char buf[512];
	char *start, *cmd;
	FILE *f;
	int len;

#define DUMP_SUFFIX	" '' dump"

	cmd = alloca(strlen(name) + 1 + sizeof(DUMP_SUFFIX));
	sprintf(cmd, "%s" DUMP_SUFFIX, name);

	f = popen(cmd, "r");
	if (!f)
		return;

	do {
		start = fgets(buf, sizeof(buf), f);
		if (!start)
			continue;

		len = strlen(start);

		if (!tok)
			tok = json_tokener_new();

		obj = json_tokener_parse_ex(tok, start, len);
		if (!is_error(obj)) {
			proto_shell_add_handler(name, obj);
			json_object_put(obj);
			json_tokener_free(tok);
			tok = NULL;
		} else if (start[len - 1] == '\n') {
			json_tokener_free(tok);
			tok = NULL;
		}
	} while (!feof(f) && !ferror(f));

	if (tok)
		json_tokener_free(tok);

	pclose(f);
}

static void __init proto_shell_init(void)
{
	glob_t g;
	int main_fd;
	int i;

	main_fd = open(".", O_RDONLY | O_DIRECTORY);
	if (main_fd < 0)
		return;

	if (chdir(main_path)) {
		perror("chdir(main path)");
		goto close_cur;
	}

	if (chdir("./proto"))
		goto close_cur;

	proto_fd = open(".", O_RDONLY | O_DIRECTORY);
	if (proto_fd < 0)
		goto close_cur;

	system_fd_set_cloexec(proto_fd);
	glob("./*.sh", 0, NULL, &g);
	for (i = 0; i < g.gl_pathc; i++)
		proto_shell_add_script(g.gl_pathv[i]);

close_cur:
	fchdir(main_fd);
	close(main_fd);
}
