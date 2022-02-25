local uci = require "luci.model.uci"
local sys = require "luci.sys"

local uci_r = uci.cursor()
local CONFIG_NAME = "online"
local UBUS_OBJECT = "online"
local api_shell = ". /lib/online_check/online_api.sh && "

local function load()
	local inface_name
	local rule

	local interval = uci_r:get(CONFIG_NAME, "settings", "interval")
	sys.fork_exec(api_shell.."update_online_interval %s" %
		 {interval})

	uci_r:foreach(CONFIG_NAME, "interface",
		function(section)
			inface_name = section['.name']
			rule = uci_r:get_all(CONFIG_NAME, section['.name'])
			sys.fork_exec(api_shell.."add_online_check %s && update_online_manual_check %s %s %s %s " %
				 {inface_name, inface_name, rule.mode, rule.gateway, rule.dns})
		end
		)
end

local function release()
	local inface_name
	local rule 
	uci_r:foreach(CONFIG_NAME, "interface",
		function(section)
			inface_name = section['.name']
			rule = uci_r:get_all(CONFIG_NAME, section['.name'])
			sys.fork_exec(api_shell.."del_online_check "..inface_name)
		end
		)
	sys.fork_call(api_shell .. " flush_online_check ")
end

if arg[1] == "start" then
	load()
elseif arg[1] == "stop" then
	release()
elseif arg[1] == "reload" then
	release()
	load()
end
