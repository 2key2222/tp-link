-- local sys    = require "luci.sys"
-- local socket = require "socket"
local uci    = require "luci.model.uci"
local dbg    = require "luci.tools.debug"
local utl    = require "luci.util"
local uci_r = uci.cursor()

local zone_file = "/tmp/.acl_zone"
CONFIG_NAME="access_ctl"
SECTION_NAME="rule_acl_inner"

local function isVNET(interface)
	return type(interface) ~= "table" and interface == "VNET" or interface[1] == "VNET"
end

local function getNetworkName(name)
	local i,j
	i,j = string.find(name,"_REV")
	if i and j then
		return string.sub(name,1,i-1)
	end
	return name
end

function acl_config_delete_rule()
    local success = {}
    local zones=nil
	local fp_zone = io.open(zone_file, "r")
    zones=fp_zone:read("*a")
    fp_zone:close()
    if not zones or zones == "" then
        return false
    end
    local index=utl.split(zones,"\n")
    index=utl.split(index[1],",")
    zones=(type(index) == "table") and index or {index}

    uci_r:foreach(CONFIG_NAME, SECTION_NAME,
        function(section)
            local interface = section["zone"]
			if isVNET(interface) then
				local srcNetwork = getNetworkName(section["srcIf"]) or ""
				local destNetwork = getNetworkName(section["destIf"]) or ""
				for _,j in pairs(zones) do
					if j == srcNetwork or j == destNetwork then
						success[#success+1] = uci_r:delete(CONFIG_NAME,section[".name"]) and true or false
					end
				end
			end			
        end        
    )

    for _,j in ipairs(success) do
        if j == false then
            return false
        end
    end

    if not uci_r:commit(CONFIG_NAME) then
        return false
    end
	
    return true
end

acl_config_delete_rule()