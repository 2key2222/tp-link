-- now, this script can only modify the status of ipsec
-- usage: lua <this script> <l2tpname>
-- for example: lua l2tp-ipsec-delete.lua client1

local dbg = require "luci.tools.debug"
local ipsec_utility= require "luci.controller.admin.ipsec"

local l2tp_ipsec_prefix = "X_l2tp_"

if #arg < 1 then
    return false
end

ipsec_name = l2tp_ipsec_prefix .. arg[1]

ipsec_utility.delete_all_ipsec_conn_by_l2tp(ipsec_name)

