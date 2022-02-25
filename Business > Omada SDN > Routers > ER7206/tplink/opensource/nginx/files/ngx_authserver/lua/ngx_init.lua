sqlite3 = require 'luasql.sqlite3'
local sys = require "luci.sys"
local sql3 = require "ngx_authserver.ngx_sqlApi"

local IPSET_LIMIT  = "AuthIplimit "
local IPSET_LIMIT_IP = "AuthIplimit_IP "

local CUR_AUTH_NUM = "curAuthNum"

function init_ngx()
    local curAuthnumDict = ngx.shared.curAuthnumDict
    local data = {key=CUR_AUTH_NUM,value=0}
    
    --For Auth Num--
    curAuthnumDict:safe_add(data.key, data.value)
    --For worker init--
    curAuthnumDict:safe_add("worker_init", "simple_worker")
    --For idle time--
    curAuthnumDict:safe_add("web_timestamp", os.time().."")
    curAuthnumDict:safe_add("wifi_timestamp", os.time().."")
    curAuthnumDict:safe_add("check_idle_flag", "0")
    --For luci error--
    curAuthnumDict:safe_add("luci_reset", "luci_reset")
    --For identification type--
    local uci_command = "uci get wportal.global_set.identification_type"
    id_type = sys.exec(uci_command)
    
    if id_type and string.find(id_type, "ipmac") ~= nil then 
        curAuthnumDict:safe_add("id_type", "ipmac")
    elseif id_type and string.find(id_type, "ip") ~= nil then
        curAuthnumDict:safe_add("id_type", "ip")
    elseif id_type and string.find(id_type, "mac") ~= nil then
        curAuthnumDict:safe_add("id_type", "mac")
    else
        curAuthnumDict:safe_add("id_type", "ipmac")
    end

    --For authed user with tx/rx limit
    local ipset_command = "ipset -N "..IPSET_LIMIT.." hash:ip,txrate,rxrate -exist"
    sys.exec(ipset_command)
    ipset_command = "ipset flush "..IPSET_LIMIT
    sys.exec(ipset_command)

    --Only save IP of authed user with tx/rx limit
    ipset_command = "ipset create "..IPSET_LIMIT_IP.." hash:ip -exist"
    sys.exec(ipset_command)
    ipset_command = "ipset flush "..IPSET_LIMIT_IP
    sys.exec(ipset_command)

    sql3.updateAuthCfg()
    sql3.updateUserCfg()
end

init_ngx()


