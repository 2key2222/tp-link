local uci = require "luci.model.uci"
local sys = require "luci.sys"
local dbg = require "luci.tools.debug"
local uci_r = uci.cursor()

local CONFIG_NAME = "access_ctl"
local RULE_NAME = "rule_acl_inner"
local acl_file_temp_file = "/tmp/acl_rule.tmp"


local acl_file = io.open (acl_file_temp_file, "w+")
acl_file:close()
acl_file = io.open (acl_file_temp_file, "a+")

function get_position(name)
	local cmd = string.format("iptables -w -n -L access_ctl --line-number | grep \"\\<%s_1acl\\>\" | cut -d ' ' -f 1",name)
	--dbg(cmd)
	local fp=io.popen(cmd,"r")
	if not fp then
		return false
	end
	local position = fp:read("*l")
	if not position then
		fp:close()
		return false
	end
	--dbg(position)
	fp:close()
	return position 
end

function get_other_info(target_name)
	local find = false
	local find_pos = false
	local position = 1
	local rule_info = {}
	local line = ""
	local vnet_prefix = ""
	
	-- choose "vnete iptables" or "iptables"
	uci_r:foreach(CONFIG_NAME, RULE_NAME,
		function(section)
			if section.name == target_name then
				for i, zone in ipairs(section.zone) do
					if (zone == "VNET") then
						vnet_prefix = "vnete "
					end
				end
			end
		end
	)
	local cmd = string.format(vnet_prefix .. "iptables -w -n -L access_ctl --line-number | grep \"1acl\" | awk '{print $(NF-1)}'")
	local fp = io.popen(cmd, "r")
	if not fp then
		return false
	end
	--line = fp:read("*l")  -- ignore the declaration of the reference of the chain in the first line
	--line = fp:read("*l")  -- ignore the declaration of the name of every column
	line = fp:read("*l")  -- get the real first line
	uci_r:foreach(CONFIG_NAME, RULE_NAME,
		function(section)
			if find_pos then
				return 
			end
			if section.name == target_name then
				local zones = ""
				for i, zone in ipairs(section.zone) do 
					zones = zones..zone.." "
				end
				rule_info["zone"] = zones
				rule_info["service"] = section.service
				rule_info["src"] = section.src or ""
				rule_info["dest"] = section.dest or ""
				rule_info["srcIf"] = section.srcIf or ""
				rule_info["destIf"] = section.destIf or ""
				rule_info["srcIfName"] = section.srcIfName or ""
				rule_info["destIfName"] = section.destIfName or ""
				rule_info["policy"] = section.policy
				find = true
			end
			if not line then
				position = 0
				return 
			end
			if section.name.."_1acl" == line then 
				if find then
					find_pos = true
					return 
				end
				--local zone_number = table.getn(section.zone) - 1
				while section.name.."_1acl" == line 
				do
					-- if the rule has mode than one zone, ignore the rule of other zone
					line = fp:read("*l")
					position = position + 1
					--zone_number = zone_number - 1
				end
				-- line = fp:read("*l")
				-- position = position + 1
			end
			
		end
		)
	if find == true then 
		rule_info["position"] = position
		acl_file:write(rule_info["zone"].."\n")
		acl_file:write(rule_info["service"].."\n")
		acl_file:write(rule_info["src"].."\n")
		acl_file:write(rule_info["dest"].."\n")
		acl_file:write(rule_info["srcIf"].."\n")
		acl_file:write(rule_info["destIf"].."\n")
		acl_file:write(rule_info["srcIfName"].."\n")
		acl_file:write(rule_info["destIfName"].."\n")
		acl_file:write(rule_info["policy"].."\n")
		acl_file:write(rule_info["position"].."\n")
	end
	fp:close()
	acl_file:close()
end


if arg[1] then
	get_other_info(arg[1])
end
