local uci = require "luci.model.uci"
local sys = require "luci.sys"
local dbg = require "luci.tools.debug"
local uci_r = uci.cursor()

local CONFIG_NAME = "webfilter"
local RULE_NAME = "webfilter"
local acl_file_temp_file = "/tmp/web_rule.tmp"


local acl_file = io.open (acl_file_temp_file, "w")

function get_other_info(target_name)

	local cmd = "iptables -w -t mangle -L webfilter | awk '{if(NR>2) print}' | cut -d / -f 2 | awk '{print $2}'"
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
			if section.rulename == target_name then
				rule_info["group"] = section["group"]
				rule_info["rule_type"] = section.rule_type 
				local content = section.action
				content = (type(content)=="table") and content or {content}
				local tmp_con = ""
				for _,i in pairs(content) do
					tmp_con = tmp_con..i.." "
				end
				rule_info["action"] = tmp_con

				content = section.website
				content = (type(content)=="table") and content or {content}
				tmp_con = ""
				for _,i in pairs(content) do
					tmp_con = tmp_con..i.." "
				end
				rule_info["website"] = tmp_con
				if section["redirect"] then
					rule_info["redirect"] = section["redirect"]
				end
				find = true
			end
			if not line then
				position = 0
				return 
			end
			if "url_"..section.rulename.."_url" == line then 
				if find then
					find_pos = true
					return 
				end
				line = fp:read("*l")
				position = position + 1
			end
		end
		)
	if find == true then 
		rule_info["position"] = position
		acl_file:write(rule_info["position"].."\n")
		acl_file:write(rule_info["group"].."\n")
		acl_file:write(rule_info["rule_type"].."\n")
		acl_file:write(rule_info["action"].."\n")
		acl_file:write(rule_info["website"].."\n")
		if rule_info["redirect"] then
			acl_file:write(rule_info["redirect"].."\n")
		end
	end
	acl_file:close()
end


if arg[1] then
	get_other_info(arg[1])
end
