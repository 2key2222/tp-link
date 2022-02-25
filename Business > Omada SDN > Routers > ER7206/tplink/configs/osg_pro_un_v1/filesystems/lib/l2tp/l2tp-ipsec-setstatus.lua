-- now, this script can only modify the status of ipsec
-- usage: lua <this script> <l2tpname> [on|off]
-- for example: lua l2tp-ipsec-operate.lua client1 on

local dbg = require "luci.tools.debug"
local ipsec_utility= require "luci.controller.admin.ipsec"
local uci = require "luci.model.uci"
local uci_r = uci.cursor()

local l2tp_ipsec_prefix = "X_l2tp_"
local ipsec_config = "ipsec"
local l2tp_config = "l2tp-client"
local ipsec_name = ""
local status = ""

local function get_old_section(sname)
    local ret = nil
    uci_r:foreach(ipsec_config, "connection", function(section)
            if section.name == sname then
                ret = section
            end
            return true
        end
        )

    return ret
end

if #arg < 3 then
    return false
end

if arg[2] ~= "on" and arg[2] ~= "off" then
    return false
end

ipsec_name = l2tp_ipsec_prefix .. arg[1]
status = arg[2]


dbg("make " .. ipsec_name .. " " .. status)
local old = get_old_section(ipsec_name)
if not old then
    return false
end


old.status = old.status == "enable" and "on" or "off"
if old.status == status then
    return true
end
old.psk = uci_r:get(l2tp_config, arg[3], "presharekey")

local res = ipsec_utility.modify_an_ipsec_conn_by_l2tp(old.name, old.remote_peer, 
    old.local_binding, old.local_network, old.remote_network, old.psk,
    old.status, old.connection_type, old.local_port, old.protocol, old.remote_port, 
    old.name, old.remote_peer, old.local_binding, old.local_network, old.remote_network, 
    old.psk, status, old.connection_type, old.local_port, old.protocol, old.remote_port)

if not res then
    return false
else
    return true
end

