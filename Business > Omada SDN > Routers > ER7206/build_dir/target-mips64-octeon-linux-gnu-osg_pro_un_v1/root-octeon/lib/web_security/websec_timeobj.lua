local uci = require "luci.model.uci"
local sys = require "luci.sys"
local dbg = require "luci.tools.debug"
local uci_r = uci.cursor()

local CONFIG_NAME = "web_security"
local RULE_NAME = "rule"
local websec_file_temp_file = "/tmp/websec_rule.tmp"


local websec_file = io.open (websec_file_temp_file, "w+")
websec_file:close()
websec_file = io.open (websec_file_temp_file, "a+")

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

	local cmd = "iptables -w -t mangle -L websec --line-number | grep \"sec_\" | awk '{for(i=2;i<=NF;i++)if($i~/\\<sec_.*?_sec\\>/)print $i}'"
	local find = false
	local find_pos = false
	local position = 1
	local rule_info = {}
	local line = ""
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
				local fileexts = ""
				for i, fileext in ipairs(section.fileext) do 
					fileexts = fileexts..fileext.." "
				end
				rule_info["fileext"] = fileexts
				rule_info["websubmit"] = section.websubmit
				rule_info["addr"] = section.addr 
				find = true
			end
			if not line then
				position = 0
				return 
			end
			if "sec_"..section.name.."_sec" == line then 
				if find then
					find_pos = true
					return 
				end
				--[[
				local zone_number = table.getn(section.zone) - 1
				while zone_number > 0 
				do
					-- if the rule has mode than one zone, ignore the rule of other zone
					fp:read("*l")
					position = position + 1
					zone_number = zone_number - 1
				end
				]]--
				line = fp:read("*l")
				position = position + 1
			end
		end
		)
	if find == true then 
		rule_info["position"] = position
		websec_file:write(rule_info["fileext"].."\n")
		websec_file:write(rule_info["websubmit"].."\n")
		websec_file:write(rule_info["addr"].."\n")
		websec_file:write(rule_info["position"].."\n")
	end
	websec_file:close()
end


if arg[1] then
	get_other_info(arg[1])
end
