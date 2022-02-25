local sqlite3 = require 'luasql.sqlite3'
local sql3 = require 'ngx_authserver.ngx_sqlApi'
local sys = require "luci.sys"
local log = require "luci.model.log"

local LOG_MODULE_PORTAL = 22
local LOG_USER_EXPIRED = 12875
local LOG_RADIUS_NO_RESPONSE = 12863

local AUTHTYPE_WEB = "web"
local AUTHTYPE_WECHAT = "wechat"
local AUTHTYPE_WEBWECHAT = "webwechat"
local AUTHTYPE_ONEKEY = "onekey"
local AUTHTYPE_RADIUS = "radius"
local AUTHTYPE_WIFI   = "wifi"

local checkIOSInterval = 5

local checkInterval = 15

local updateInterval = 20

local IDLE_MIN_TIME_SEC = 25

local USERSTATUS_INIT    = 0
local USERSTATUS_AUTHING = 1
local USERSTATUS_AUTHED  = 9

local WIFIDOG_IPSETMSG_KEY = 12063
local WIFIDOG_IOSMSG_KEY   = 12062

local RULE_KNOWN_IP = "Authed_out_ip "
local RULE_KNOWN_MAC = "Authed_out_mac "
local RULE_KNOWN_IPMAC = "Authed_out_ipmac "
local RULE_REMIND           = "Authed_Remind_ip "
local RULE_REMIND_IPMAC     = "Authed_Remind_ipmac "
local RULE_REMIND_MAC       = "Authed_Remind_mac"
local IPSET_LIMIT           = "AuthIplimit"

local WIFIDOG_IPSET_OPTION = 2
local WIFIDOG_IOS_ADD_OPTION = 1
local WIFIDOG_IOS_DEL_OPTION = 2

function checkAuthlist()
    local authlistKeys = ngx.shared.authListDict:get_keys(0)
    
    for index,item in pairs(authlistKeys) do
        local data = {key=item}
        local authEntry = sql3.getAuthentry(data)
        
        if authEntry then
            local curTime = os.time()
            if USERSTATUS_AUTHED == tonumber(authEntry.status) and tonumber(authEntry.expiretime) < curTime then
                log.logger_reg(LOG_MODULE_PORTAL, LOG_USER_EXPIRED, authEntry.ip)
                sql3.logoutUser(authEntry.ip,authEntry.mac)
            end

            if USERSTATUS_AUTHING == tonumber(authEntry.status) and tonumber(authEntry.expiretime) < curTime then
                if authEntry.authtype == AUTHTYPE_RADIUS then
                    log.logger_reg(LOG_MODULE_PORTAL, LOG_RADIUS_NO_RESPONSE, authEntry.ip)
                end
                --DEL AUTH ENTRY--      
                sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)         
            end
            
            if AUTHTYPE_WEB == authEntry.authtype then
                local serverData = {key="web_"..authEntry.gw_id}
                local serverEntry = sql3.getServerentry(serverData)
                
                if serverEntry and ("on" == serverEntry.enable) and ("web" == serverEntry.portal_type) and ("on" == serverEntry.remind_enable) and (1 == tonumber(serverEntry.remind_type)) then
                    local expireDay = (tonumber(authEntry.expiretime) - curTime)/3600/24
                    local onlinetime = curTime - tonumber(authEntry.uptime)
                    local interval = onlinetime%(60*tonumber(serverEntry.remind_interval))
                    
                    if 0 == tonumber(authEntry.remindflag) and expireDay < tonumber(serverEntry.remind_time)+1 and interval < checkInterval then
                        if authEntry.mac and "00:00:00:00:00:00" == authEntry.mac then
                            ipset_command = "add "..RULE_REMIND..authEntry.ip.." -exist \n"
                        elseif authEntry.ip and "0.0.0.0" == authEntry.ip then 
                            ipset_command = "add "..RULE_REMIND_MAC..authEntry.mac.." -exist \n"
                        else
                            ipset_command = "add "..RULE_REMIND_IPMAC..authEntry.ip..","..authEntry.mac.." -exist \n"
                        end
                        
                        res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        if res ~= "OK" then
                            ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)                       
                        end
                        authEntry.remindflag = 1
                        sql3.setAuthentry(authEntry)

                        -- sfe flush for remind
                        sql3.sfe_flush()
                    end
                elseif not serverEntry or "on" ~= serverEntry.enable then
                    if 1 == tonumber(authEntry.remindflag) then
                        if authEntry.mac and "00:00:00:00:00:00" == authEntry.mac then
                            ipset_command = "del "..RULE_REMIND..authEntry.ip.." -exist \n"
                        elseif authEntry.ip and "0.0.0.0" == authEntry.ip then 
                            ipset_command = "del "..RULE_REMIND_MAC..authEntry.mac.." -exist \n"
                        else
                            ipset_command = "del "..RULE_REMIND_IPMAC..authEntry.ip..","..authEntry.mac.." -exist \n"
                        end
                        
                        res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        if res ~= "OK" then
                            ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)                       
                        end
                        authEntry.remindflag = 0
                        sql3.setAuthentry(authEntry)
                    end
                else
                    --Do nothing
                end
            end
        end
    end

    ok, err = ngx.timer.at(checkInterval, checkAuthlist)
    
    if not ok then
        ngx.log(ngx.ERR, "failed to startup checkAuthlist worker...", err)
    end

end

function checkIOSClient()
    local iosListKeys = ngx.shared.iosClientDict:get_keys(0)

    for index,item in pairs(iosListKeys) do
        local data = {key=item}
        local iosClient = sql3.getIOSClientEntry(data)
        local curTime = os.time()

        if iosClient.expireTime < curTime then
            local res_msg = ngx.sendMsg(WIFIDOG_IOSMSG_KEY, WIFIDOG_IOS_DEL_OPTION, iosClient.ip)
            if res_msg ~= "OK" then
                ngx.log(ngx.ERR, "checkIOSClient failed to send msg to wifidog")
            else
                sql3.delIOSClientEntry(iosClient.ip)
            end
        end
    end

    ok, err = ngx.timer.at(checkIOSInterval, checkIOSClient)
    
    if not ok then
        ngx.log(ngx.ERR, "failed to startup checkIOSClient worker...", err)
    end

end

function checkIdleUserLogout()
    local authlistKeys = ngx.shared.authListDict:get_keys(0)
    local curAuthnumDict = ngx.shared.curAuthnumDict
    local curTime = os.time()
    local prevWebTime = tonumber(curAuthnumDict:get("web_timestamp"))
    local prevWifiTime = tonumber(curAuthnumDict:get("wifi_timestamp"))
    local web_idle_time = sys.exec("uci get wportal.global_set.web_idle_time")
    local web_idle_time_half = 0
    local web_idle_time_check = 0
    local wifi_idle_time = sys.exec("uci get wportal.global_set.wifi_idle_time")
    local web_interval = curTime - prevWebTime;
    local wifi_interval = curTime - prevWifiTime;
    local id_type = curAuthnumDict:get("id_type")
    local check_idle_flag = tonumber(curAuthnumDict:get("check_idle_flag"))

    if not web_idle_time or web_idle_time == "" then
        web_idle_time = 0
    else
        web_idle_time = tonumber(web_idle_time) * 60
        web_idle_time_half = web_idle_time / 2
    end

    if not wifi_idle_time or wifi_idle_time == ""then
        wifi_idle_time = 0
    else
        wifi_idle_time = tonumber(wifi_idle_time) * 60
    end

    if check_idle_flag == 0 then
        web_idle_time_check = web_idle_time_half
    else
        web_idle_time_check = web_idle_time
    end

    if ( (web_idle_time ~= 0 and web_interval >= web_idle_time_check) or (wifi_idle_time ~= 0 and wifi_interval >= wifi_idle_time) ) then

        if web_interval >= web_idle_time then
            curAuthnumDict:replace("check_idle_flag", "0")
        else
            curAuthnumDict:replace("check_idle_flag", "1")
        end

        for index,item in pairs(authlistKeys) do
            local data = {key=item}
            local authEntry = sql3.getAuthentry(data)
            
            if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
                local command
                if "ipmac" == id_type then
                    command = string.format([[ipset list %s|grep -E "%s|%s"|awk '{print $3}']], RULE_KNOWN_IPMAC, authEntry.ip, string.upper(authEntry.mac))
                elseif "ip" == ip_type then
                    command = string.format([[ipset list %s|grep %s|awk '{print $3}']], RULE_KNOWN_IP, authEntry.ip)
                else
                    command = string.format([[ipset list %s|grep %s|awk '{print $3}']], RULE_KNOWN_MAC, string.upper(authEntry.mac))
                end
                pkt_counter = tonumber(sys.exec(command))

                if pkt_counter then
                    if AUTHTYPE_WIFI ~= authEntry.authtype and (web_idle_time ~= 0 and web_interval >= web_idle_time_half) then
                        -- check AUTHTYPE_WEB, AUTHTYPE_ONEKEY, AUTHTYPE_RADIUS
                        if pkt_counter == authEntry.pkt_counter and web_interval >= web_idle_time then
                            sql3.logoutUser(authEntry.ip,authEntry.mac)
                        else
                            authEntry.pkt_counter = pkt_counter
                            sql3.setAuthentry(authEntry)                                
                        end
                        if web_interval >= web_idle_time then
                            curAuthnumDict:replace("web_timestamp", curTime.."")
                        end
                    elseif AUTHTYPE_WIFI == authEntry.authtype and (wifi_idle_time ~= 0 and wifi_interval >= wifi_idle_time) then
                        if pkt_counter == authEntry.pkt_counter then
                            sql3.logoutUser(authEntry.ip,authEntry.mac)
                        else
                            authEntry.pkt_counter = pkt_counter
                            sql3.setAuthentry(authEntry)                                
                        end           
                        curAuthnumDict:replace("wifi_timestamp", curTime.."")
                    end
                else
                    ngx.log(ngx.ERR, "Unable to get pkt_counter from [%s,%s]", authEntry.ip, authEntry.mac)
                end
            end
        end
    end

    
    ok, err = ngx.timer.at(IDLE_MIN_TIME_SEC, checkIdleUserLogout)    
    if not ok then
        ngx.log(ngx.ERR, "failed to startup checkIOSClient worker...", err)
    end    

end



local entryString, errMsg
local curAuthnumDict = ngx.shared.curAuthnumDict
entryString, errMsg = curAuthnumDict:get("worker_init")
if entryString then
    --Only the first nginx-worker run the timer--
    curAuthnumDict:delete("worker_init")
    checkAuthlist()
    checkIOSClient()
    checkIdleUserLogout()
end
