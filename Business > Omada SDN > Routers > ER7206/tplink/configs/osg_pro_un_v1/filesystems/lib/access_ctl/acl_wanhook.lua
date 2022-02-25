local uci    = require "luci.model.uci"
local dbg    = require "luci.tools.debug"
local sys    = require "luci.sys"
local ipgroup = require "luci.model.ipgroup"
local form = require "luci.tools.form"

local uci_r = uci.cursor()
form = form.Form(uci_r, {"access_ctl"})

local CONFIG_NAME = "access_ctl"
local ACL_KEYS = {"name", "zone", "policy", "service", "src", "dest", "time", "flag", "user"}

function getGroupName(name)
	local i,j
	i,j = string.find(name,"_REV")
	if i and j then
		return string.sub(name,1,i-1)
	end
	return name
end

function del_acl(zones)	
	local zone_table = string.split(zones, ' ')
	local zone_dict = {}
	local del_section = {}
	for i, j in ipairs(zone_table) do 
		zone_dict[j] = j
	end
	uci_r:foreach(CONFIG_NAME, "rule_acl_inner", 
		function(section)
			local rule = uci_r:get_all(CONFIG_NAME, section[".name"])
			local zone_in = {}
			local zone_no_in = {}
			local del_zone = false
			if type(rule.zone) ~= "table" then
				rule.zone = {rule.zone}
			end
			for _, zone in ipairs(rule.zone) do
				if zone_dict[zone] then
					zone_in[#zone_in+1] = zone
				else
					zone_no_in[#zone_no_in+1] = zone
				end
			end
			if next(zone_in) == nil then
				return true
			end
			if #zone_in == #rule.zone then
				del_zone = true
			end
			if not del_zone then
				uci_r:delete(CONFIG_NAME, section[".name"], "zone")
				uci_r:set(CONFIG_NAME, section[".name"], "zone", zone_no_in)
			else
				local src_address = rule.src 
				local dst_address = rule.dest
				local time = rule.time
				ipgroup.ref_dec(getGroupName(src_address))
				ipgroup.ref_dec(getGroupName(dst_address))
				if time ~= "Any" then
					sys.fork_exec(". /lib/access_ctl/time.sh && del_timeobj "..time.." "..rule.name)
				end
				del_section[#del_section+1] = section[".name"]
				local command = string.format("rm /tmp/access_ctl/%s",rule.name)
				--dbg("command:",command)
				sys.fork_exec(command)
			end
		end
	)

	uci_r:commit(CONFIG_NAME)

	for i, j in ipairs(del_section) do 
		uci_r:delete(CONFIG_NAME, j)
	end
	uci_r:commit(CONFIG_NAME)
end 

function add_acl(zones)
	local acl = {}
	acl.zone = {}
	acl.flag = "1"
	acl.policy = "DROP"
	acl.src = "IPGROUP_ANY"
	acl.time = "Any"
	acl.dst = ""
	acl.name = ""
	acl.service = "ALL"
	acl.user = "0"
	local name = ""

	local zone_table = string.split(zones, ' ')
	if type(zone_table) ~= "table" then
		zone_table = {zone_table}
	end
	for _, zone in ipairs(zone_table) do 
		local position = tonumber(string.sub(zone, -1))
		acl.zone[#acl.zone+1] = zone
		acl.dest = "IPGROUP_LAN"
		acl.name = "acl-"..zone.."-1"
		ipgroup.ref_inc(acl.src)
		ipgroup.ref_inc(acl.dest)
		--form:insert_position(CONFIG_NAME, "rule_acl_inner", acl, position*2-1, ACL_KEYS)
		name = uci_r:add(CONFIG_NAME, "rule_acl_inner")
		uci_r:section(CONFIG_NAME, "rule_acl_inner", name, acl)
		uci_r:commit(CONFIG_NAME)

		acl.dest = "Me"
		acl.name = "acl-"..zone.."-2"
		ipgroup.ref_inc(acl.src)
		ipgroup.ref_inc(acl.dest)
		name = uci_r:add(CONFIG_NAME, "rule_acl_inner")
		--form:insert_position(CONFIG_NAME, "rule_acl_inner", acl, position*2, ACL_KEYS)
		uci_r:section(CONFIG_NAME, "rule_acl_inner", name, acl)
		uci_r:commit(CONFIG_NAME)
		acl.zone = {}
	end
end

if arg[1] == "add" then
	add_acl(arg[2])
elseif arg[1] == "del" then
	del_acl(arg[2])
end