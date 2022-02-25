local uci = require "luci.model.uci"
local sys = require "luci.sys"
local dbg = require "luci.tools.debug"
local uci_r = uci.cursor()

local MODULE_UCI = "qos"
local STYPE_RULE = "rule"
local state_file = "/tmp/.qos/insert_index"
local installed_file = "/tmp/.qos/installed_file"

local insert_index_fp = io.open(state_file, "w+")
local installed_fp = io.open(installed_file, "r")

function find_insert_index(insert_rule)
	local find = false
	local position = 1
	local installed = installed_fp:read()
	uci_r:foreach(MODULE_UCI, STYPE_RULE,
		function(section)
			if not installed then
				position = 0
			end
			if find == true then
				return
			end
			if section.name == insert_rule then
				find = true
				return
			end
			if section.name == installed then
				position = position + 1
				installed = installed_fp:read()
				return
			end
		end
		)
	--dbg(position)
	insert_index_fp:write(position)
	insert_index_fp:close()
	installed_fp:close()
end

if arg[1] then
	find_insert_index(arg[1])
end