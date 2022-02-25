--[[
file: ngx_wdas.lua
wifidog auth server on lua-nginx
]]--

local nixio = require "nixio"
local fs = require "nixio.fs"
local sys = require "luci.sys"
local sql3 = require 'ngx_authserver.ngx_sqlApi'
local dbg = require "luci.tools.debug"
local uci = require "luci.model.uci"
local uci_r = uci.cursor()
local log = require "luci.model.log"

local LOG_MODULE_PORTAL = 22
local LOG_AUTH_SUCC = 12851
local LOG_AUTH_USER_PWD_ERR = 12852
local LOG_AUTH_USER_DISABLED = 12853
local LOG_AUTH_USER_EXPIRE = 12854
local LOG_AUTH_INVAL_PERIOD = 12855
local LOG_AUTH_USER_FULL = 12856
local LOG_AUTH_MAC_ERR = 12857
local LOG_USER_LOGOUT = 12874
local LOG_RADIUS_AUTH_SUCC = 12862
local LOG_RADIUS_NO_RESPONSE = 12863
local LOG_RADIUS_USER_PWD_ERR = 12864


local IPSET_LIMIT  = "AuthIplimit "
local IPSET_LIMIT_IP = "AuthIplimit_IP "

local webLoginPath = "/www/luci-static/resources/authserver/web_login.html"
local wechatFilePath = "/www/luci-static/resources/authserver/wechat.html"
local pcwifiPath = "/www/luci-static/resources/authserver/pc_wifi.html"
local mobilewifiPath = "/www/luci-static/resources/authserver/mobile_wifi.html"

local radius_result_file = "radius_query_result"

local PC_WIFI_FILE_LEN = 25 * 1024
local MOBILE_WIFI_FILE_LEN = 25*1024
local WEB_PAGE_FILE_LEN = 50*1024
local pc_wifi_str = fs.readfile(pcwifiPath,PC_WIFI_FILE_LEN)
local mobile_wifi_str = fs.readfile(mobilewifiPath,MOBILE_WIFI_FILE_LEN)
local web_page_str = fs.readfile(webLoginPath,WEB_PAGE_FILE_LEN)

local USERSTATUS_INIT    = 0
local USERSTATUS_AUTHING = 1
local USERSTATUS_AUTHED  = 9

local AUTHTYPE_WEB = "web"
local AUTHTYPE_WECHAT = "wechat"
local AUTHTYPE_WEBWECHAT = "webwechat"
local AUTHTYPE_ONEKEY = "onekey"
local AUTHTYPE_RADIUS = "radius"
local AUTHTYPE_WIFI   = "wifi"

local AUTH_RES_SUCC         = 9
local AUTH_RES_REFRESH      = 1
local AUTH_RES_USER_PWD_ERR = 2
local AUTH_RES_INVAL_PERIOD = 3
local AUTH_RES_MAC_ERR      = 4
local AUTH_RES_USER_FULL    = 5
local AUTH_RES_NO_USER      = 6
local AUTH_RES_USER_EXPIRE  = 7
local AUTH_RES_AUTH_FAILED  = 8
local AUTH_RES_USER_DISABLED= 10
local AUTH_RES_MAX          = 11   --Max ele num of local auth string

local authResStr = {
"authenticating",
"ErrorUserOrPassword",
"InvalidTimePeriod",
"MacNotMatch",
"UserReachedMax",
"UserNotExist",
"UserExpired",
"AuthFailed",
"Success",
"UserDisabled"}

local DFT_WIFI_INTERFACE = "br-lan"

local NGINX_PORT = uci_r:get("wportal", "global_set", "auth_port") or 8080

local WIFIDOG_IPSETMSG_KEY = 12063
local WIFIDOG_IOSMSG_KEY   = 12062

local WIFIDOG_IPSET_OPTION = 2
local WIFIDOG_IOS_ADD_OPTION = 1
local WIFIDOG_IOS_DEL_OPTION = 2

local RULE_KNOWN_IP = "Authed_out_ip "
local RULE_KNOWN_MAC = "Authed_out_mac "
local RULE_KNOWN_IPMAC = "Authed_out_ipmac "
local RULE_INCOM_KNOWN_IP = "Authed_in_ip "
local RULE_INCOM_KNOWN_MAC = "Authed_in_mac "
local RULE_INCOM_KNOWN_IPMAC = "Authed_in_ipmac "
local RULE_REMIND = "Authed_Remind_ip "
local RULE_REMIND_MAC = "Authed_Remind_mac "
local RULE_REMIND_IPMAC = "Authed_Remind_ipmac "

local WEB_DOMAIN_NAME = "wportal.tplogin.cn"
local WECHAT_DOMAIN_NAME = "weixin.tplogin.cn"
local USE_LOCAL_IP_ADDRESS = 1

local IOS_CLIENT_EXPIRETIME = 10
local AUTHING_CLIENT_EXPIRETIME = 300
local t1 = 0
local t2 = 0

function js_redirect(url)
    local data
    if not string.match(url,"\^https?://") then
        url = "http://"..url
    end
    data = "<html><head></head><body><script type=\"text/javascript\" language=\"javascript\">top.location.href=\""..url.."\";</script></body></html>" 
    ngx.header['Content-Type'] = "text/html"
    ngx.header['Content-Length'] = string.len(data)
    ngx.print(data)
end

function sleep(n)
   os.execute("sleep "..n)
end

function newtoken(bytes)
    local rand = fs.readfile("/dev/urandom", bytes)
    return rand and nixio.bin.hexlify(rand)
end

function str4page(oriStr)
    local newStr
    newStr = string.gsub(oriStr,"\t",",")
    newStr = string.gsub(newStr,'\\','\\\\')
    newStr = string.gsub(newStr,'"','\\\"')
    return newStr
end

function setHttpHeader()
    local headerStr = '<!DOCTYPE html>\r\n' ..  
                      '<html>\r\n' ..  
                      '<head>\r\n' ..  
                      '<meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0,\r\n user-scalable=yes" />\r\n' ..  
                      '<meta name="apple-mobile-web-app-capable" content="yes" />\r\n' ..  
                      '<meta name="format-detection" content="telephone=yes" />\r\n' ..  
                      '<meta charset="utf-8"/>\r\n' ..  
                      '<meta http-equiv="Pragma" content="no-cache" />\r\n' ..  
                      '<meta http-equiv="Cache-Control" content="no-cache" />\r\n' ..  
                      '<meta http-equiv="Expires" content="0" />\r\n'
    return headerStr
end

function setWechatArray(serverEntry,pagetype)
    local arrayStr,data
    local image,remindinfo
    
    if "remind" == pagetype then
        --image = serverEntry.qrcodeImage
        remindinfo = serverEntry.wechatInfo
    else
        --image = serverEntry.adImage
        remindinfo = serverEntry.free_interval
    end
    serverEntry.publicName = str4page(serverEntry.publicName)
    remindinfo = str4page(remindinfo)
    serverEntry.copyright = str4page(serverEntry.copyright)
    arrayStr = string.format([[var cfgPara = {"pagetype":"%s","background":"%s","image":"%s","account":"%s","remindinfo":"%s","welinfo":"%s","authToken":"%s","copyright":"%s","pcfree":"%s"};]],
        pagetype,
        "/"..serverEntry.adImage,
        "/"..serverEntry.qrcodeImage,
        serverEntry.publicName,
        remindinfo,
        "Welcome to use free WiFi",
        serverEntry.authToken,
        serverEntry.copyright,
        serverEntry.pcfree
    )
    
    data = '<script type="text/javascript">' .. 
           arrayStr .. 
           '</script>'
                                               
    return data
end

function sendWechatPage(serverEntry,pagetype)
    local data, arrStr, header,fp
    header = setHttpHeader()
    arrStr = setWechatArray(serverEntry,pagetype)

    data = header..arrStr
    ngx.header['Content-Type'] = "text/html"
    
    fp = io.open(wechatFilePath, "rb")
    if fp then
        ngx.header['Content-Length'] = string.len(data) + fp:seek("end") 
        fp:close()
    end
    
    ngx.print(data)
    ngx.sendfile(wechatFilePath, -1, -1)
end

function setPcWifiArray(serverEntry,pagetype)
    local arrayStr,data
    
    serverEntry.copyright = str4page(serverEntry.copyright)
    serverEntry.welinfo = str4page(serverEntry.welinfo)
    serverEntry.logoname = str4page(serverEntry.logoname)
    serverEntry.bgdname = str4page(serverEntry.bgdname)

    arrayStr = string.format([[var cfgPara = {"pagetype":"%s","shopId":"%s","appId":"%s","extend":"%s","authUrl":"%s","background":"%s","logo":"%s","copyright":"%s","freetime":"%s","welinfo":"%s","wired_auth":"%s","bgdname":"%s","logoname":"%s"};]],
        pagetype,
        serverEntry.shopid,
        serverEntry.appid,
        serverEntry.extend,
        "http://"..WECHAT_DOMAIN_NAME..":8080/weixin/?tplogin_token="..serverEntry.authToken,
        "/"..serverEntry.background,
        "/"..serverEntry.logo,
        serverEntry.copyright,
        serverEntry.free_interval,
        serverEntry.welinfo,
        serverEntry.wired_auth,
        serverEntry.bgdname,
        serverEntry.logoname
    )
    
    data = '<script type="text/javascript">' .. 
           arrayStr .. 
           '</script>'
                                               
    return data
end

function sendPcwifiPage(serverEntry,pagetype)
    local data, arrStr, header,fp
    header = setHttpHeader()
    arrStr = setPcWifiArray(serverEntry,pagetype)

    data = header..arrStr..pc_wifi_str
    ngx.header['Content-Type'] = "text/html"
    ngx.header['Content-Length'] = string.len(data)
--[[
    fp = io.open(pcwifiPath, "rb")
    if fp then
        ngx.header['Content-Length'] = string.len(data) + fp:seek("end") 
        fp:close()
    end
]]--
    ngx.print(data)
    --ngx.sendfile(pcwifiPath, -1, -1)
end

function setMobileWifiArray(args,serverEntry,pagetype)
    local arrayStr,data,sign,timestamp,authUrl,signStr
    
    serverEntry.ssid = str4page(serverEntry.ssid)
    serverEntry.welinfo = str4page(serverEntry.welinfo)
    serverEntry.logoinfo = str4page(serverEntry.logoinfo)
    serverEntry.btninfo = str4page(serverEntry.btninfo)
    serverEntry.logoname = str4page(serverEntry.logoname)
    serverEntry.bgdname = str4page(serverEntry.bgdname)
    serverEntry.copyright = str4page(serverEntry.copyright)
    
    timestamp = os.time() * 1000;
    authUrl = "http://"..WECHAT_DOMAIN_NAME..":8080/weixin/?tplogin_token="..serverEntry.authToken
    signStr = serverEntry.appid..serverEntry.shopid..authUrl..serverEntry.extend..timestamp..serverEntry.secretkey
    sign=ngx.md5(signStr)
    
    arrayStr = string.format([[var cfgPara = {"pagetype":"%s","ssid":"%s","shopId":"%s","appId":"%s","timestamp":"%s","sign":"%s", "extend":"%s","mac":"%s","bssid":"%s","authUrl":"%s","background":"%s","logo":"%s","welinfo":"%s","logoinfo":"%s","btninfo":"%s","wired_auth":"%s","bgdname":"%s","logoname":"%s","copyright":"%s","auth_port":"%d"};]],
        pagetype,
        serverEntry.ssid,
        serverEntry.shopid,
        serverEntry.appid,
        timestamp,
        sign,
        serverEntry.extend,
        args.mac,
        serverEntry.bssid,
        authUrl,
        "/"..serverEntry.background,
        "/"..serverEntry.logo,
        serverEntry.welinfo,
        serverEntry.logoinfo,
        serverEntry.btninfo,
        serverEntry.wired_auth,
        serverEntry.bgdname,
        serverEntry.logoname,
        serverEntry.copyright,
        NGINX_PORT
    )
    
    data = '<script type="text/javascript">' .. 
           arrayStr .. 
           '</script>'
                                               
    return data
end

function sendMobilewifiPage(args,serverEntry,pagetype)
    local data, arrStr, header,fp
    header = setHttpHeader()
    arrStr = setMobileWifiArray(args,serverEntry,pagetype)

    data = header..arrStr..mobile_wifi_str
    ngx.header['Content-Type'] = "text/html"
    ngx.header['Content-Length'] = string.len(data)
--[[
    fp = io.open(mobilewifiPath, "rb")
    if fp then
        ngx.header['Content-Length'] = string.len(data) + fp:seek("end") 
        fp:close()
    end
]]--
    ngx.print(data)
    --ngx.sendfile(mobilewifiPath, -1, -1)
end

function sendWebJsonArray(serverEntry,authEntry,remindFlag,args)
    local arrayStr
    local status,onlineTime,expireTime,token,mac,tmp_date
    
    if authEntry then
        temp_date = os.date("*t",authEntry.expiretime)
        
        status = authEntry.status
        onlineTime = os.time() - authEntry.uptime
        expireTime = temp_date.year .. "-" .. temp_date.month.."-" .. temp_date.day
        token = authEntry.token
        ip = authEntry.ip
        mac = authEntry.mac
        url = authEntry.url
        gw_address = authEntry.gw_address
        gw_port = authEntry.gw_port
        gw_id = authEntry.gw_id
    else
        status = USERSTATUS_INIT
        onlineTime = 0
        expireTime = ""
        token = ""
        ip = args.ip
        mac = args.mac
        url = args.url
        gw_address = args.gw_address
        gw_port = args.gw_port
        gw_id = args.gw_id
    end
    
    serverEntry.page_title = str4page(serverEntry.page_title)
    serverEntry.wel_info = str4page(serverEntry.wel_info)
    serverEntry.copyright = str4page(serverEntry.copyright)
    serverEntry.remind_page_title = str4page(serverEntry.remind_page_title)
    serverEntry.remind_page_content = str4page(serverEntry.remind_page_content)
    arrayStr = string.format([[{"remindFlag":%d,"wportal_page_type":"%s","page_title":"%s","wel_info":"%s","copyright":"%s","background":"%s","external_url":"%s","remind_type":"%s","remind_page_title":"%s","remind_page_content":"%s","remindGoUrl":"%s","authtype":"%s","token":"%s","mac":"%s","ip":"%s","url":"%s","status":%d,"onlineTime":%d,"expireTime":"%s","gw_address":"%s","gw_port":"%s","gw_id":"%s","auth_port":"%d"}]],
    remindFlag,
    serverEntry.wportal_page_type,
    serverEntry.page_title,
    serverEntry.wel_info,
    serverEntry.copyright,
    "/"..serverEntry.background,
    serverEntry.external_url,
    'local',--serverEntry.remind_type,
    serverEntry.remind_page_title,
    serverEntry.remind_page_content,
    '',--serverEntry.remindGoUrl,
    serverEntry.portal_type,
    token,
    mac,
    ip,
    url,
    status,
    onlineTime,
    expireTime,
    gw_address,
    gw_port,
    serverEntry.gw_id,
    NGINX_PORT)
    
    ngx.header['Content-Type'] = "text/html"
    ngx.header['Content-Length'] = string.len(arrayStr)
    ngx.print(arrayStr)
end

function setWebArray(serverEntry,authEntry,remindFlag,args)
    local arrayStr,data
    local status,onlineTime,expireTime,token,mac,tmp_date
    
    if authEntry then
        temp_date = os.date("*t",authEntry.expiretime)
        
        status = authEntry.status
        onlineTime = os.time() - authEntry.uptime
        expireTime = temp_date.year .. "-" .. temp_date.month.."-" .. temp_date.day
        token = authEntry.token
        ip = authEntry.ip
        mac = authEntry.mac
        url = authEntry.url
        gw_address = authEntry.gw_address
        gw_port = authEntry.gw_port
        gw_id = authEntry.gw_id
    else
        status = USERSTATUS_INIT
        onlineTime = 0
        expireTime = ""
        token = ""
        ip = args.ip
        mac = args.mac
        url = args.url
        gw_address = args.gw_address
        gw_port = args.gw_port
        gw_id = args.gw_id
    end
    
    serverEntry.page_title = str4page(serverEntry.page_title)
    serverEntry.wel_info = str4page(serverEntry.wel_info)
    serverEntry.copyright = str4page(serverEntry.copyright)
    serverEntry.remind_page_title = str4page(serverEntry.remind_page_title)
    serverEntry.remind_page_content = str4page(serverEntry.remind_page_content)
    arrayStr = string.format([[var wportalPara = {"remindFlag":%d,"wportal_page_type":"%s","page_title":"%s","wel_info":"%s","copyright":"%s","background":"%s","external_url":"%s","remind_type":"%s","remind_page_title":"%s","remind_page_content":"%s","remindGoUrl":"%s","authtype":"%s","token":"%s","mac":"%s","ip":"%s","url":"%s","status":%d,"onlineTime":%d,"expireTime":"%s","gw_address":"%s","gw_port":"%s","gw_id":"%s","auth_port":"%d"};]],
    remindFlag,
    serverEntry.wportal_page_type,
    serverEntry.page_title,
    serverEntry.wel_info,
    serverEntry.copyright,
    "/"..serverEntry.background,
    serverEntry.external_url,
    'local',--serverEntry.remind_type,
    serverEntry.remind_page_title,
    serverEntry.remind_page_content,
    '',--serverEntry.remindGoUrl,
    serverEntry.portal_type,
    token,
    mac,
    ip,
    url,
    status,
    onlineTime,
    expireTime,
    gw_address,
    gw_port,
    serverEntry.gw_id,
    NGINX_PORT)
    
    data = '<script type="text/javascript">' .. 
           arrayStr .. 
           '</script>'
                                               
    return data
end

function sendWebLogin(serverEntry,authEntry,remindFlag,args)
    local data, arrStr, header,pf
    header = setHttpHeader()
    arrStr = setWebArray(serverEntry,authEntry,remindFlag,args)

    data = header..arrStr..web_page_str
    ngx.header['Content-Type'] = "text/html"
    ngx.header['Content-Length'] = string.len(data)
--[[    
    fp = io.open(webLoginPath, "rb")
    if fp then
        ngx.header['Content-Length'] = string.len(data) + fp:seek("end") 
        fp:close()
    end
]]--
    ngx.print(data)
    --ngx.sendfile(webLoginPath, -1, -1)
end

function isMobile()
    local UserAgent = ngx.req.get_headers()["user-agent"]
    
    if nil == UserAgent then
        return false
    end

    if string.find(UserAgent,"Phone") or
       string.find(UserAgent,"Android") or
       string.find(UserAgent,"webOS") or
       string.find(UserAgent,"iPhone") or
       string.find(UserAgent,"iPod") or
       string.find(UserAgent,"BlackBerry") then
            return true
    else
            return false
    end
end

function isMicroMessenger()
    local UserAgent = ngx.req.get_headers()["user-agent"]
    
    if nil == UserAgent then
        return false
    end

    if string.find(UserAgent,"micromessenger") then
            return true
    else
            return false
    end
end

function login(args)
    local ip,data,gw_id, gw_address, gw_port,mac,url,authtype
    local serverEntry,authEntry
    local entryString
    local curAuthnumDict = ngx.shared.curAuthnumDict

    ip          = args["ip"]
    gw_id       = args["gw_id"]
    gw_address = args["gw_address"]
    gw_port     = args["gw_port"]
    mac         = args["mac"]
    url         = args["url"]
    
    entryString = curAuthnumDict:get("id_type")
    if entryString then
        if entryString == "mac" then
            ip = "0.0.0.0"
        elseif entryString == "ip" then
            mac = "00:00:00:00:00:00"
        end
    end

    if not ip then
        ip = ngx.var.remote_addr
    end
    
    if not mac then
        mac = "00:00:00:00:00:00"
    end

    data = {key = ip.."_"..mac}
    authEntry = sql3.getAuthentry(data)
    if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status)  then
        authtype = authEntry.authtype
        gw_id = authEntry.gw_id
        
        if AUTHTYPE_WIFI == authtype then
            data = {key = "wifi_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
        elseif AUTHTYPE_WECHAT == authtype then
            data = {key = "wechat_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
        elseif AUTHTYPE_ONEKEY == authtype then
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_ONEKEY)
        else
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WEB)
        end
    else
        data = {key = "web_"..gw_id}
        serverEntry = sql3.getServerentry(data)
        if not serverEntry then
            data = {key = "wifi_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
            if not serverEntry then
                data = {key = "wechat_"..gw_id}
                serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
            end
        end
    end
    
    if not serverEntry then
        ngx.say("{error:noServerLogin}")
        return
    end

    if not authtype then
        authtype = serverEntry.portal_type
    end
    
    if ip and mac and url and gw_address and gw_port and gw_id then
        if AUTHTYPE_WEB == authtype or AUTHTYPE_RADIUS == authtype then
            if authEntry and tonumber(authEntry.status) == USERSTATUS_AUTHED then
                args.stage = "loginpage"
                portal(serverEntry,authEntry,args)
            else
                if serverEntry.wportal_page_type == 'remote' and serverEntry.external_url and serverEntry.external_url ~= "" then
                    local request_uri 
                    if string.find(serverEntry.external_url,'?') then
                        request_uri = serverEntry.external_url .."&gw_address="..gw_address.."&gw_port="..gw_port.."&gw_id="..gw_id.."&ip="..ip.."&mac="..mac.."&url="..url
                    else
                        request_uri = serverEntry.external_url .."?gw_address="..gw_address.."&gw_port="..gw_port.."&gw_id="..gw_id.."&ip="..ip.."&mac="..mac.."&url="..url
                    end
                    --ngx.redirect(request_uri)
                    js_redirect(request_uri);
                else
                    sendWebLogin(serverEntry,authEntry,0,args)
                end
            end
        elseif AUTHTYPE_ONEKEY == authtype then
            sendWebLogin(serverEntry,authEntry,0,args)
        elseif AUTHTYPE_WECHAT == authtype or AUTHTYPE_WEBWECHAT == authtype or AUTHTYPE_WIFI == authtype then
            if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
                return portal(serverEntry,authEntry,args)
            end
            
            local getData = {key=ip}
            local iosClient = sql3.getIOSClientEntry(getData)
            if nil == iosClient then
                local UserAgent = ngx.req.get_headers()["user-agent"]
                if UserAgent and string.find(UserAgent, "iPhone") then
                    local expireTime = os.time() + IOS_CLIENT_EXPIRETIME
                    local data = string.format("%s,%d",
                                                    ip,
                                                    expireTime)
                    local item = {key=ip, value = data}
                    local ok,err = sql3.addIOSClientEntry(item)
                    if ok then
                        ngx.sendMsg(WIFIDOG_IOSMSG_KEY, WIFIDOG_IOS_ADD_OPTION, ip)
                    end
                end
            end
            --Add temp authing client
            if not authEntry then
                authEntry = {}
                authEntry.token = ""
                authEntry.gw_id = serverEntry.gw_id
                authEntry.gw_address = ""
                authEntry.gw_port = 0
                authEntry.ip = ip
                authEntry.mac = mac
                authEntry.url = ""
                authEntry.uptime = os.time()
                authEntry.expiretime = os.time() + AUTHING_CLIENT_EXPIRETIME
                authEntry.username = ""
                authEntry.indata = 0
                authEntry.outdata = 0
                authEntry.authtype = authtype
                authEntry.status = USERSTATUS_AUTHING
                authEntry.remindflag = 0
                authEntry.pkt_counter = 0
                
                local data = string.format("%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%s,%d,%d,%d",
                                                authEntry.token,
                                                authEntry.gw_id,
                                                authEntry.gw_address,
                                                authEntry.gw_port,
                                                authEntry.username,
                                                authEntry.ip,
                                                authEntry.mac,
                                                sql3.decodeURI(authEntry.url),
                                                authEntry.uptime,
                                                authEntry.expiretime,
                                                authEntry.indata,
                                                authEntry.outdata,
                                                authEntry.authtype,
                                                authEntry.status,
                                                authEntry.remindflag,
                                                authEntry.pkt_counter)
                local item = {key=authEntry.ip.."_"..authEntry.mac, value = data}
                    
                local ok,err = sql3.addAuthentry(item)
                if not ok then
                    local UserAgent = ngx.req.get_headers()["user-agent"]
                    if UserAgent and string.find(UserAgent, "iPhone") then
                        ngx.sendMsg(WIFIDOG_IOSMSG_KEY, WIFIDOG_IOS_DEL_OPTION, ip)
                    end
                end
            end
            
            if AUTHTYPE_WIFI == authtype then
                if isMobile() then
                    sendMobilewifiPage(args,serverEntry,"portal")
                else
                    sendPcwifiPage(serverEntry,"portal")
                end
            else
                --Send wechat page
                sendWechatPage(serverEntry,"remind")
            end
        else
            ngx.say("{error: invalid authtype}")
        end
    else
        ngx.say("{error: invalid args}")
    end
end

function logincheck(args,inType)
    local post_args = {}
    local user, pwd, gw_id, gw_address, gw_port, ip,mac, url, token,authtype,curTime,remindflag
    local authEntry
    local serverEntry
    local expiretime = 0
    local curAuthnumDict = ngx.shared.curAuthnumDict
                    
    user = args["user"]
    pwd = args["pwd"]
    gw_id = args["gw_id"]
    gw_address = args["gw_address"]
    gw_port = args["gw_port"]
    mac = args["mac"]
    ip = args["ip"]
    url = args["url"]
    authtype = args["authtype"]

    if sql3.checkAuthEntryNumMax() ~= 1 then
        ngx.say('{error: item full.}')
        return 
    end

    entryString = curAuthnumDict:get("id_type")
    if entryString then
        if entryString == "mac" then
            ip = "0.0.0.0"
        elseif entryString == "ip" then
            mac = "00:00:00:00:00:00"
        end
    end
    
    if not authtype then
        authtype = inType
    end
    
    if not ip then
        ip = ngx.var.remote_addr
    end
    
    if not mac then
        mac = "00:00:00:00:00:00"
    end    

    data = {key = ip.."_"..mac}
    authEntry = sql3.getAuthentry(data)
    if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status)  then
        authtype = authEntry.authtype
        gw_id = authEntry.gw_id

        if AUTHTYPE_WIFI == authtype then
            data = {key = "wifi_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
        elseif AUTHTYPE_WECHAT == authtype then
            data = {key = "wechat_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
        elseif AUTHTYPE_ONEKEY == authtype then
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_ONEKEY)
        else
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WEB)
        end
    else
        
        if AUTHTYPE_WIFI == authtype then
            data = {key = "wifi_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
        elseif AUTHTYPE_WECHAT == authtype then
            data = {key = "wechat_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
        else
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data)
            if not serverEntry then
                data = {key = "wifi_"..gw_id}
                serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
                if not serverEntry then
                    data = {key = "wechat_"..gw_id}
                    serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
                end
            end
        end
    end
    
    if not serverEntry then
        ngx.say("{error:noServerLogincheck}")
        return
    end

    if gw_port == nil then
        --unused now--
        gw_port = 2060 
    end

    if gw_address == nil then
        if AUTHTYPE_WECHAT == authtype then
            gw_address = WECHAT_DOMAIN_NAME
        else
            gw_address = WEB_DOMAIN_NAME
        end
    end

    if url == nil then
        url = ngx.var.request_uri
    end

    if AUTHTYPE_WEB == authtype then
        if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
            args.stage = "loginpage"
            portal(serverEntry,authEntry,args)
            return
        end
        if gw_address and gw_port and mac and ip and user then
            if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
                --handled before
                --[[
                if serverEntry.wportal_page_type == 'remote' then
                    if serverEntry.external_url_succ and  serverEntry.external_url_succ ~= ""  then
                        --ngx.redirect(serverEntry.external_url_succ)
                        js_redirect(serverEntry.external_url_succ)
                    else
                        js_redirect(authEntry.url)
                    end
                else
                    sendWebLogin(serverEntry,authEntry,0,args)
                end
                ]]--
            else
                local res,msg_res,indata,outdata
                remindflag = 0
                indata = 0
                outdata = 0


                if authEntry then
                    sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)
                end
                
                authEntry = {}
                
                token = newtoken(16)
                if "radius" == serverEntry.wportal_type then
                    local cmd = string.format([[%s %s %s %s %s %s]],"radius_query.sh",user,pwd,string.upper(serverEntry.auth_type),serverEntry.interface,token)
                    sys.fork_exec(cmd)
                    res = USERSTATUS_AUTHING
                    authEntry.authtype = AUTHTYPE_RADIUS
                    expiretime = os.time() + 30
                else
                    res = sql3.checkUser(user,pwd,ip,mac)
                    authEntry.authtype = AUTHTYPE_WEB
                    if res == AUTH_RES_SUCC then
                        ---Send ipset msg---                
                        local userEntry = {}
                        data = {key = user}
                        userEntry = sql3.getUserentry(data)
                        
                        if not mac or "00:00:00:00:00:00" == mac then
                            ipset_command = "add "..RULE_KNOWN_IP..ip.." -exist \n"
                        elseif not ip or "0.0.0.0" == ip then
                            ipset_command = "add "..RULE_KNOWN_MAC..mac.." -exist \n"
                        else
                            ipset_command = "add "..RULE_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                        end
                        
                        msg_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        if msg_res ~= "OK" then
                            ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_res)
                            --sendWebLogin(serverEntry, nil, 0,args)
                            sendWebJsonArray(serverEntry, nil, 0,args)
                            return
                        end
                        if not mac or "00:00:00:00:00:00" == mac then
                            ipset_command = "add "..RULE_INCOM_KNOWN_IP..ip.." -exist \n"
                        elseif not ip or "0.0.0.0" == ip then
                            ipset_command = "add "..RULE_INCOM_KNOWN_MAC..mac.." -exist \n"
                        else
                            ipset_command = "add "..RULE_INCOM_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                        end
                        
                        msg_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        if msg_res ~= "OK" then
                            ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_res)
                            --sendWebLogin(serverEntry, nil, 0,args)
                            sendWebJsonArray(serverEntry, nil, 0,args)
                            return                        
                        end

                        if nil~=userEntry and (0 ~= userEntry.upBand or userEntry.downBand ~= 0) then                          
                            ipset_command = "-A "..IPSET_LIMIT.." "..ip..","..userEntry.upBand..","..userEntry.downBand.." -exist \n"
                            msg_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                            if msg_res ~= "OK" then
                                ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_res)
                                --sendWebLogin(serverEntry, nil, 0,args)
                                sendWebJsonArray(serverEntry, nil, 0,args)
                                return
                            end

                            ipset_command = "-A "..IPSET_LIMIT_IP.." "..ip.." -exist \n"
                            msg_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                            if msg_res ~= "OK" then
                                ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_res)
                                --sendWebLogin(serverEntry, nil, 0,args)
                                sendWebJsonArray(serverEntry, nil, 0,args)
                                return
                            end
                            indata = userEntry.downBand
                            outdata = userEntry.upBand
                        end                  
                        ---0.000904   
                        ---Set cur user entry---                   
                        local data = {key = user}
                        local curuserEntry = sql3.getCuruserEntry(data)
                        if curuserEntry then
                            curuserEntry.curUser = curuserEntry.curUser+1
                            sql3.setCuruserEntry(curuserEntry)
                        else
                            local curUserString = string.format("%s,%d", user, 1)
                            local newItem = {key = user, value = curUserString}
                            sql3.addCuruserEntry(newItem)
                        end
                        ---Set expire time---                        
                        if nil~= userEntry and "free" == userEntry.userType then
                            expiretime = os.time() + userEntry.expireTime * 60
                        elseif nil ~= userEntry then
                            expiretime = userEntry.expireTime
                            if "formal" == userEntry.userType then
                                curTime = os.time()
                                if ("on" == serverEntry.remind_enable) and  (0 == tonumber(serverEntry.remind_type)) then
                                    local expireDay = (tonumber(expiretime) - curTime)/3600/24
                                    if expireDay < tonumber(serverEntry.remind_time)+1 then
                                        remindflag = 1
                                    end
                                end
                            end
                        else
                            expiretime = AUTHING_CLIENT_EXPIRETIME
                            ngx.log(ngx.ERR, "Can't find userEntry")
                        end       
                    end                    
                end

                authEntry.token = token
                authEntry.gw_id = gw_id
                authEntry.gw_address = gw_address
                authEntry.gw_port = gw_port
                authEntry.ip = ip
                authEntry.mac = mac
                authEntry.url = url
                authEntry.uptime = os.time()
                authEntry.expiretime = expiretime
                authEntry.username = user
                authEntry.indata = indata
                authEntry.outdata = outdata
                authEntry.status = tonumber(res)
                authEntry.remindflag = remindflag
                authEntry.pkt_counter = 0

                if string.len(authEntry.url) > 240 then
                    authEntry.url = 'http://' .. WEB_DOMAIN_NAME .. ':' .. NGINX_PORT ..'/wifidog/login/?gw_id='..authEntry.gw_id
                end

                authEntry.url = sql3.decodeURI(authEntry.url)
                local data = string.format("%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%s,%d,%d,%d",
                                                authEntry.token,
                                                authEntry.gw_id,
                                                authEntry.gw_address,
                                                authEntry.gw_port,
                                                authEntry.username,
                                                authEntry.ip,
                                                authEntry.mac,
                                                authEntry.url,
                                                authEntry.uptime,
                                                authEntry.expiretime,
                                                authEntry.indata,
                                                authEntry.outdata,
                                                authEntry.authtype,
                                                authEntry.status,
                                                authEntry.remindflag,
                                                authEntry.pkt_counter)
				
                local item = {key=authEntry.ip.."_"..authEntry.mac, value = data}
                
                if "radius" == serverEntry.wportal_type then
                    local ok,err = sql3.addAuthentry(item)
                    if ok then
                        args.token = token
                        args.stage = "login"
                        auth(serverEntry,authEntry,args)
                    else
                        authEntry.status = AUTH_RES_AUTH_FAILED
                        args.message = "denied"
                        gw_message(serverEntry,authEntry,args)
                    end
                else
                    if res == AUTH_RES_SUCC then 
                        local ok,err = sql3.addAuthentry(item)
                        if not ok then
                            authEntry.status = AUTH_RES_AUTH_FAILED
                            args.message = "denied"
                            gw_message(serverEntry,authEntry,args)
                        else
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_SUCC, authEntry.ip)
                            portal(serverEntry,authEntry,args)
                        end
                    else
                        -- LOG
                        if res == AUTH_RES_USER_DISABLED then
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_USER_DISABLED, authEntry.ip)
                        elseif res == AUTH_RES_USER_EXPIRE then
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_USER_EXPIRE, authEntry.ip)
                        elseif res == AUTH_RES_INVAL_PERIOD then
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_INVAL_PERIOD, authEntry.ip)
                        elseif res == AUTH_RES_USER_FULL then
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_USER_FULL, authEntry.ip)
                        elseif res == AUTH_RES_MAC_ERR then
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_MAC_ERR, authEntry.ip)
                        else
                            -- res == AUTH_RES_USER_PWD_ERR or res == AUTH_RES_NO_USER
                            log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_USER_PWD_ERR, authEntry.ip)
                        end
                        args.message = "denied"
                        gw_message(serverEntry,authEntry,args)
                    end
                end
            end
        else
            ngx.say('{error: invalid parameter.}')
        end
    elseif AUTHTYPE_ONEKEY == authtype then
        if gw_address and gw_port and mac then
            if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
                if serverEntry.wportal_page_type == 'remote' then
                    if serverEntry.external_url_succ and  serverEntry.external_url_succ ~= ""  then
                        --ngx.redirect(serverEntry.external_url_succ)
                        js_redirect(serverEntry.external_url_succ)
                    else
                        js_redirect(authEntry.url)
                    end
                else
                    sendWebLogin(serverEntry,authEntry,0,args)
                end
            else
                if authEntry then
                    sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)
                end

                local msg_out_res,msg_in_res
                if not mac or "00:00:00:00:00:00" == mac then
                    ipset_command = "add "..RULE_KNOWN_IP..ip.." -exist \n"
                elseif not ip or "0.0.0.0" == ip then
                    ipset_command = "add "..RULE_KNOWN_MAC..mac.." -exist \n"
                else
                    ipset_command = "add "..RULE_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                end
                msg_out_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if msg_out_res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_out_res)
                    ngx.say("{error:iptables set failed}")
                    return
                end
                
                if not mac or "00:00:00:00:00:00" == mac then
                    ipset_command = "add "..RULE_INCOM_KNOWN_IP..ip.." -exist \n"
                elseif not ip or "0.0.0.0" == ip then
                    ipset_command = "add "..RULE_INCOM_KNOWN_MAC..mac.." -exist \n"
                else
                    ipset_command = "add "..RULE_INCOM_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                end
                msg_in_res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if msg_in_res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_in_res)
                    ngx.say("{error:iptables set failed}")
                    return                        
                end                 
                
                authEntry = {}
                token = newtoken(16)
                authEntry.token = token
                authEntry.gw_id = gw_id
                authEntry.gw_address = gw_address
                authEntry.gw_port = gw_port
                authEntry.ip = ip
                authEntry.mac = mac
                authEntry.url = url
                authEntry.uptime = os.time()
                authEntry.expiretime = serverEntry.free_interval*60 + os.time()
                authEntry.username = ""
                authEntry.indata = 0
                authEntry.outdata = 0
                authEntry.authtype = AUTHTYPE_ONEKEY
                authEntry.status = USERSTATUS_AUTHED
                authEntry.remindflag = 0
                authEntry.pkt_counter = 0

                if string.len(authEntry.url) > 240 then
                    authEntry.url = 'http://' .. WEB_DOMAIN_NAME .. ':' .. NGINX_PORT ..'/wifidog/login/?gw_id='..authEntry.gw_id
                end
                authEntry.url = sql3.decodeURI(authEntry.url)
                local data = string.format("%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%s,%d,%d,%d",
                                                authEntry.token,
                                                authEntry.gw_id,
                                                authEntry.gw_address,
                                                authEntry.gw_port,
                                                authEntry.username,
                                                authEntry.ip,
                                                authEntry.mac,
                                                authEntry.url,
                                                authEntry.uptime,
                                                authEntry.expiretime,
                                                authEntry.indata,
                                                authEntry.outdata,
                                                authEntry.authtype,
                                                authEntry.status,
                                                authEntry.remindflag,
                                                authEntry.pkt_counter)
                local item = {key=authEntry.ip.."_"..authEntry.mac, value = data}

                local ok,err = sql3.addAuthentry(item)
                if ok then
                    --local redirectUrl = 'http://' .. gw_address .. ':' .. NGINX_PORT ..'/wifidog/portal/?gw_id='..gw_id
                    --ngx.redirect(redirectUrl )
                    --js_redirect(redirectUrl )
                    --sendWebLogin(serverEntry,authEntry,0,args)
                    log.logger_reg(LOG_MODULE_PORTAL, LOG_AUTH_SUCC, authEntry.ip)
                    sendWebJsonArray(serverEntry,authEntry,0,args)
                else
                    ngx.say("{error:auth failed}")
                end
            end
            
        else
            ngx.say('{error: invalid parameter.}')
        end
    elseif AUTHTYPE_WECHAT == authtype or AUTHTYPE_WIFI == authtype then
        if gw_address and gw_port and mac and url then
            if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
                if AUTHTYPE_WIFI == authtype then
                    if isMobile() then
                        sendMobilewifiPage(args,serverEntry,"portal")
                    else
                        sendPcwifiPage(serverEntry,"success")
                    end
                else
                    if "remote" == serverEntry.jumpPageType and serverEntry.remoteUrl and  serverEntry.remoteUrl ~= ""  then
                        --ngx.redirect(serverEntry.remoteUrl)
                        js_redirect(serverEntry.remoteUrl)
                    else
                        sendWechatPage(serverEntry,"success")
                    end
                end
            else
                local wechatToken
                if string.find(url,"/weixin/%?tplogin_token=") then
                    wechatToken = string.match(url,"/weixin/%?tplogin_token=([A-Za-z0-9]+)")
                else
                    wechatToken = args["tplogin_token"]
                    if not wechatToken then
                        ngx.say('{error:invalid token.}')
                        return
                    end  

                    if not isMicroMessenger() then
                        ngx.say('{error:invalid useragent.}')
                        return
                    end           
                end

                if not wechatToken or (wechatToken ~= serverEntry.authToken and wechatToken ~= "micromessenger") then
                    ngx.say('{error:invalid token.}')
                    return
                end
                
                if authEntry then
                    sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)
                end

                local msg_out_res,msg_in_res
                local ipset_command
                if not mac or "00:00:00:00:00:00" == mac then
                    ipset_command = "add "..RULE_KNOWN_IP..ip.." -exist \n"
                elseif not ip or "0.0.0.0" == ip then
                    ipset_command = "add "..RULE_KNOWN_MAC..mac.." -exist \n"
                else
                    ipset_command = "add "..RULE_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                end
                msg_out_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if msg_out_res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_out_res)
                    if AUTHTYPE_WIFI == authtype then
                        if isMobile() then
                            sendMobilewifiPage(args,serverEntry,"portal")
                        else
                            sendPcwifiPage(serverEntry,"portal")
                        end
                    else
                        sendWechatPage(serverEntry,"remind")
                    end
                    return
                end
                
                if not mac or "00:00:00:00:00:00" == mac then
                    ipset_command = "add "..RULE_INCOM_KNOWN_IP..ip.." -exist \n"
                elseif not ip or "0.0.0.0" == ip then
                    ipset_command = "add "..RULE_INCOM_KNOWN_MAC..mac.." -exist \n"
                else
                    ipset_command = "add "..RULE_INCOM_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                end 

                msg_in_res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if msg_in_res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_in_res)
                    if AUTHTYPE_WIFI == authtype then
                        if isMobile() then
                            sendMobilewifiPage(args,serverEntry,"portal")
                        else
                            sendPcwifiPage(serverEntry,"portal")
                        end
                    else
                        sendWechatPage(serverEntry,"remind")
                    end
                    return                        
                end 
                
                authEntry = {}
                token = newtoken(16)
                authEntry.token = token
                authEntry.gw_id = gw_id
                authEntry.gw_address = gw_address
                authEntry.gw_port = gw_port
                authEntry.ip = ip
                authEntry.mac = mac
                authEntry.url = url
                authEntry.uptime = os.time()
                authEntry.expiretime = serverEntry.free_interval*60 + os.time()
                authEntry.username = ""
                authEntry.indata = 0
                authEntry.outdata = 0
                authEntry.authtype = serverEntry.portal_type
                authEntry.status = USERSTATUS_AUTHED
                authEntry.remindflag = 0
                authEntry.pkt_counter = 0

                if string.len(authEntry.url) > 240 then
                    authEntry.url = 'http://' .. WECHAT_DOMAIN_NAME .. ':' .. NGINX_PORT ..'/wifidog/login/?gw_id='..authEntry.gw_id
                end
                
                authEntry.url = sql3.decodeURI(authEntry.url)
                local data = string.format("%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%s,%d,%d,%d",
                                                authEntry.token,
                                                authEntry.gw_id,
                                                authEntry.gw_address,
                                                authEntry.gw_port,
                                                authEntry.username,
                                                authEntry.ip,
                                                authEntry.mac,
                                                authEntry.url,
                                                authEntry.uptime,
                                                authEntry.expiretime,
                                                authEntry.indata,
                                                authEntry.outdata,
                                                authEntry.authtype,
                                                authEntry.status,
                                                authEntry.remindflag,
                                                authEntry.pkt_counter)
                local item = {key=authEntry.ip.."_"..authEntry.mac, value = data}
                    
                local ok,err = sql3.addAuthentry(item)
                    
                if ok then
                    if AUTHTYPE_WIFI == serverEntry.portal_type then
                        if isMobile() then
                            ngx.say("Auth Success")
                        else
                            sendPcwifiPage(serverEntry,"success")
                        end
                    else
                        if "local" == serverEntry.jumpPageType then
                            sendWechatPage(serverEntry,"success")
                        else
                            if serverEntry.remoteUrl and  serverEntry.remoteUrl ~= ""  then
                                --ngx.redirect(serverEntry.remoteUrl)
                                js_redirect(serverEntry.remoteUrl)
                            else
                                ngx.say("{error:remote url null}")
                            end
                        end
                    end
                else
                        if not mac or "00:00:00:00:00:00" == mac then
                            ipset_command = "del "..RULE_INCOM_KNOWN_IP..ip.." -exist \n"
                        elseif not ip or "0.0.0.0" == ip then
                            ipset_command = "del "..RULE_INCOM_KNOWN_MAC..mac.." -exist \n"
                        else
                            ipset_command = "del "..RULE_INCOM_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                        end
                    ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)                    
                        if not mac or "00:00:00:00:00:00" == mac then
                            ipset_command = "del "..RULE_KNOWN_IP..ip.." -exist \n"
                        elseif not ip or "0.0.0.0" == ip then
                            ipset_command = "del "..RULE_KNOWN_MAC..mac.." -exist \n"
                        else
                            ipset_command = "del "..RULE_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                        end
                    ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)

                    ngx.say("{error:auth failed item full.}")
                end
            end
        else
            ngx.say('{error: invalid parameter.}')
        end
    else
        return ngx.say("{error:invalid authtype}")
    end
end

function auth(serverEntry,authEntry, args)
    --auth/?stage=&ip=&mac=&token=
    local stage, ip, mac, url,token, gw_address,gw_id,incoming, outgoing,authtype,authres
    local std = {}
    local ipset_command
    local res
    local curAuthnumDict = ngx.shared.curAuthnumDict
    
    local reloadFlag = args["reloadFlag"]
    stage = args["stage"]
    ip = args["ip"]
    mac = args["mac"]
    url = args["url"]
    token = args["token"]
    token = token and token:match("^[a-f0-9]*$")
    gw_address = args["gw_address"]
    gw_id = args["gw_id"]
    gw_port = args["gw_port"]
    
    entryString = curAuthnumDict:get("id_type")
    if entryString then
        if entryString == "mac" then
            ip = "0.0.0.0"
        elseif entryString == "ip" then
            mac = "00:00:00:00:00:00"
        end
    end
    
    if not ip then
        ip = ngx.var.remote_addr
    end
    
    data = {key = ip.."_"..mac}
    authEntry = sql3.getAuthentry(data)
    if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status)  then
        authtype = authEntry.authtype
        gw_id = authEntry.gw_id
        
        if AUTHTYPE_WIFI == authtype then
            data = {key = "wifi_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
        elseif AUTHTYPE_WECHAT == authtype then
            data = {key = "wechat_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
        elseif AUTHTYPE_ONEKEY == authtype then
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_ONEKEY)
        else
            data = {key = "web_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WEB)
        end
    else
        data = {key = "web_"..gw_id}
        serverEntry = sql3.getServerentry(data)
        if not serverEntry then
            data = {key = "wechat_"..gw_id}
            serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
        end
    end
    
    if not serverEntry then
        ngx.say("{error:noServerAuth}")
        return
    end

    if ip and token and token:match("^[a-f0-9]*$") then
        if "logout" == stage then
            if nil == authEntry then
                --sendWebLogin(serverEntry,nil,0,args)
                sendWebJsonArray(serverEntry,nil,0,args)
                return
            end
            if authEntry.token == token then                
                if authEntry and ((AUTHTYPE_WEB == authEntry.authtype) or (AUTHTYPE_RADIUS == authEntry.authtype)) then
                    if authEntry and "radius" ~= serverEntry.wportal_type then
                        sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)
                        
                        data = {key = authEntry.username} 
                        local curuserEntry = sql3.getCuruserEntry(data)
                        local userEntry = sql3.getUserentry(data)
                        
                        if 1 == tonumber(authEntry.remindflag) then
                            if authEntry.mac and "00:00:00:00:00:00" == authEntry.mac then
                                ipset_command = "del "..RULE_REMIND..authEntry.ip.." -exist \n"
                            elseif authEntry.ip and "0.0.0.0" == authEntry.ip then 
                                ipset_command = "del "..RULE_REMIND_MAC..authEntry.mac.." -exist \n"
                            else
                                ipset_command = "del "..RULE_REMIND_IPMAC..authEntry.ip..","..authEntry.mac.." -exist \n"
                            end
                            
                            res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        end

                        if 0 ~= authEntry.outdata or authEntry.indata ~= 0 then
                            ipset_command = "-D "..IPSET_LIMIT.." "..ip..","..authEntry.outdata..","..authEntry.indata.." -exist \n"
                            res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                            if res ~= "OK" then
                                ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)
                                if ("127.0.0.1" ~= ngx.var.remote_addr)  and ("169.254.11.21" ~= ngx.var.remote_addr) then
                                    ngx.header['Cookie'] = "wdastok=" .. token .. ";"
                                    local redirectUrl = 'http://' .. WEB_DOMAIN_NAME .. ':' .. NGINX_PORT ..'/wifidog/auth/?stage=logout&token='..token..'&mac='..mac..'&ip='..ip..'&refresh=1'
                                    --ngx.redirect(redirectUrl )
                                    js_redirect(redirectUrl )
                                else 
                                    ngx.say("Auth 1")
                                end             
                                return                        
                            else
                                ngx.log(ngx.ERR, "ngx_sendMsg incom Success")
                                ipset_command = "-D "..IPSET_LIMIT_IP.." "..ip.." -exist \n"
                                res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                            end
                        end

                        if USERSTATUS_AUTHED == tonumber(authEntry.status) and curuserEntry and tonumber(curuserEntry.curUser) > 0 then
                            curuserEntry.curUser = curuserEntry.curUser-1
                            if tonumber(curuserEntry.curUser) == 0 then
                                sql3.delCuruserEntry(curuserEntry.userName)
                            else
                                sql3.setCuruserEntry(curuserEntry)
                            end
                        end

                        data = {key = authEntry.username}
                    else
                        sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)
                    end
                else
                    sql3.delAuthentry(ip.."_"..mac)
                end
                --SEND IPSET MSG--

                if not mac or "00:00:00:00:00:00" == mac then
                    ipset_command = "del "..RULE_KNOWN_IP..ip.." -exist \n"
                elseif not ip or "0.0.0.0" == ip then
                    ipset_command = "del "..RULE_KNOWN_MAC..mac.." -exist \n"
                else
                    ipset_command = "del "..RULE_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                end
                
                res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)
                    ngx.say("{error:iptables set failed}")
                    return
                end
                if not mac or "00:00:00:00:00:00" == mac then
                    ipset_command = "del "..RULE_INCOM_KNOWN_IP..ip.." -exist \n"
                elseif not ip or "0.0.0.0" == ip then
                    ipset_command = "del "..RULE_INCOM_KNOWN_MAC..mac.." -exist \n"
                else
                    ipset_command = "del "..RULE_INCOM_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                end 
                res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)
                    ngx.say("{error:iptables set failed}")
                    return                        
                end 
            end
            if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
                if AUTHTYPE_WECHAT == authEntry.authtype then
                    --local redirectUrl = 'http://' .. WECHAT_DOMAIN_NAME .. ':' .. NGINX_PORT ..'/wifidog/login/?gw_id='..authEntry.gw_id..'&gw_address='..authEntry.gw_address..'&gw_port='..authEntry.gw_port..'&mac='..authEntry.mac..'&ip='..authEntry.ip..'&url='..authEntry.url
                    --ngx.redirect(redirectUrl)  
                    --js_redirect(redirectUrl )
                    if reloadFlag then
                        login(serverEntry,authEntry,args)
                    else
                        sendWebJsonArray(serverEntry,authEntry,0,args)
                    end
                else
                    --local redirectUrl = 'http://' .. WEB_DOMAIN_NAME .. ':' .. NGINX_PORT ..'/wifidog/login/?gw_id='..authEntry.gw_id..'&gw_address='..authEntry.gw_address..'&gw_port='..authEntry.gw_port..'&mac='..authEntry.mac..'&ip='..authEntry.ip..'&url='..authEntry.url
                    --ngx.redirect(redirectUrl)  
                    --js_redirect(redirectUrl )
                    if reloadFlag then
                        login(serverEntry,nil,args)
                    else
                        sendWebJsonArray(serverEntry,nil,0,args)
                    end
                end
            else
                ngx.say("Auth 0")
            end
            
        elseif "login" == stage then
            if authEntry and (ip == authEntry.ip) then
                authtype = authEntry.authtype
                if AUTHTYPE_RADIUS == authtype then
                    if "radius" == serverEntry.wportal_type then				
                        local radiusStatus,radiusTimeout
						uci_r:load(radius_result_file)
                        radiusStatus = uci_r:get(radius_result_file,authEntry.token,"status")
						--dbg("radiusStatus: " .. authEntry.token .." ".. type(radiusStatus))
                        if type(radiusStatus) == "string" then
                            local cmd
                            radiusTimeout = uci_r:get(radius_result_file,authEntry.token,"timeout") or ""
                            res = {status = radiusStatus, timeout = radiusTimeout}
                            if "fail" == radiusStatus or "success" == radiusStatus then
                                cmd = string.format([[%s %s]],"radius_check_result.sh",authEntry.token)
                                sys.fork_exec(cmd)
                            end
                        end
                        
                        if type(res) == "table" then
                            if "success" == res.status then
                                local timeout = res.timeout
                                authEntry.status = USERSTATUS_AUTHED
                                
                                local uptime = os.time()
                                authEntry.uptime = uptime
                                
                                if timeout and timeout ~="" then
                                    local expiretime
                                    expiretime = tonumber(timeout) + os.time()
                                    authEntry.expiretime = expiretime
                                else
                                    local expiretime
                                    expiretime = 15*60 + os.time()
                                    authEntry.expiretime = expiretime
                                end

                                sql3.setAuthentry(authEntry)
                                portal(serverEntry, authEntry,args)
                                ---SEND IPSET MSG---
                                if not mac or "00:00:00:00:00:00" == mac then
                                    ipset_command = "add "..RULE_KNOWN_IP..ip.." -exist \n"
                                elseif not ip or "0.0.0.0" == ip then
                                    ipset_command = "add "..RULE_KNOWN_MAC..mac.." -exist \n"
                                else
                                    ipset_command = "add "..RULE_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                                end
                                res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                                if res ~= "OK" then
                                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)
                                    ngx.say("{error:iptables set failed}")
                                    return
                                end
                                
                                if not mac or "00:00:00:00:00:00" == mac then
                                    ipset_command = "add "..RULE_INCOM_KNOWN_IP..ip.." -exist \n"
                                elseif not ip or "0.0.0.0" == ip then
                                    ipset_command = "add "..RULE_INCOM_KNOWN_MAC..mac.." -exist \n"
                                else
                                    ipset_command = "add "..RULE_INCOM_KNOWN_IPMAC..ip..","..mac.." -exist \n"
                                end 
                                res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                                if res ~= "OK" then
                                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)
                                    ngx.say("{error:iptables set failed}")
                                    return                        
                                end
                                log.logger_reg(LOG_MODULE_PORTAL, LOG_RADIUS_AUTH_SUCC, authEntry.ip)
                            elseif "fail" == res.status then
                                authEntry.status = AUTH_RES_AUTH_FAILED
                                args.message = "denied"
                                gw_message(serverEntry,authEntry,args)
                                log.logger_reg(LOG_MODULE_PORTAL, LOG_RADIUS_NO_RESPONSE, authEntry.ip)
                                sql3.delAuthentry(authEntry.ip.."_"..authEntry.mac)
                            else
                                --Try again
                                if serverEntry.wportal_page_type == 'local' then
                                    --login(serverEntry,authEntry,args)
                                    sendWebJsonArray(serverEntry,authEntry,0,args)
                                else
                                    ngx.header['Cookie'] = "wdastok=" .. token .. ";"
                                    local redirectUrl = 'http://' .. gw_address .. ':' .. NGINX_PORT ..'/wifidog/auth/?stage=login&token='..token..'&mac='..mac..'&ip='..ip..'&url='..url..'&refresh=1'..'&gw_id='..gw_id..'&gw_address='..gw_address..'&gw_port='..gw_port..'&authtype=web'
                                    --ngx.redirect(redirectUrl )
                                    js_redirect(redirectUrl )
                                end
                                return 
                            end
                        else
                            --Try again
                            if serverEntry.wportal_page_type == 'local' then
                                --login(serverEntry,authEntry,args)
                                sendWebJsonArray(serverEntry,authEntry,0,args)
                            else
                                ngx.header['Cookie'] = "wdastok=" .. token .. ";"
                                local redirectUrl = 'http://' .. gw_address .. ':' .. NGINX_PORT ..'/wifidog/auth/?stage=login&token='..token..'&mac='..mac..'&ip='..ip..'&url='..url..'&refresh=1'..'&gw_id='..gw_id..'&gw_address='..gw_address..'&gw_port='..gw_port..'&authtype=web'
                                --ngx.redirect(redirectUrl )
                                js_redirect(redirectUrl )
                            end
                            return
                        end
                    end
                else
                    return ngx.say("{error:invalid authtype}")
                end

            else
                authEntry = {}
                authEntry.token = ""
                authEntry.gw_id = serverEntry.gw_id
                authEntry.gw_address = ""
                authEntry.gw_port = 0
                authEntry.ip = ip
                authEntry.mac = ""
                authEntry.url = ""
                authEntry.uptime = os.time()
                authEntry.expiretime = 0
                authEntry.username = ""
                authEntry.indata = 0
                authEntry.outdata = 0
                authEntry.authtype = AUTHTYPE_WECHAT
                authEntry.remindflag = 0
                authEntry.status = AUTH_RES_AUTH_FAILED
                args.message = "denied"
                gw_message(serverEntry,authEntry,args)
            end
        else
            ngx.say("{error:unknown stage}")
        end
    else
        ngx.say("{error:invalid token}")
    end
end

function ping(args)
    --ping/?gw_id=&sys_load=&sys_memfree=&sys_load=&wifidog_uptime=
    local id, sys_uptime, sys_memfree, sys_load, wifidog_uptime
    id = args["gw_id"]
    sys_uptime = args["sys_uptime"]
    sys_memfree = args["sys_memfree"]
    sys_load = args["sys_load"]
    wifidog_uptime = args["wifidog_uptime"]
    if id and sys_uptime and sys_memfree and sys_load and wifidog_uptime then
        ngx.say("Pong")
    else
        ngx.say("{error:2}")
    end
end

function portal(serverEntry,authEntry,args)
    --portal/?gw_id=%s
    local gw_id,data,authtype
    local reloadFlag = args["reloadFlag"]
    local ip = args["ip"]
    local mac = args["mac"]
    local curAuthnumDict = ngx.shared.curAuthnumDict

    entryString = curAuthnumDict:get("id_type")
    if entryString then
        if entryString == "mac" then
            ip = "0.0.0.0"
        elseif entryString == "ip" then
            mac = "00:00:00:00:00:00"
        end
    end
    
    if not authEntry and not serverEntry then
        if not ip then
            ip = ngx.var.remote_addr
        end
        
        if not mac then
            mac = "00:00:00:00:00:00"
        end
        
        data = {key = ip.."_"..mac}
        authEntry = sql3.getAuthentry(data)
        if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status)  then
            authtype = authEntry.authtype
            gw_id = authEntry.gw_id
            
            if AUTHTYPE_WIFI == authtype then
                data = {key = "wifi_"..gw_id}
                serverEntry = sql3.getServerentry(data,AUTHTYPE_WIFI)
            elseif AUTHTYPE_WECHAT == authtype then
                data = {key = "wechat_"..gw_id}
                serverEntry = sql3.getServerentry(data,AUTHTYPE_WECHAT)
            elseif AUTHTYPE_ONEKEY == authtype then
                data = {key = "web_"..gw_id}
                serverEntry = sql3.getServerentry(data,AUTHTYPE_ONEKEY)
            else
                data = {key = "web_"..gw_id}
                serverEntry = sql3.getServerentry(data,AUTHTYPE_WEB)
            end
        else
            ngx.say("{error:noAuthEntry}")
            return
        end
        
        if not serverEntry then
            ngx.say("{error:noServerEntryPortal}")
            return
        end
    end
    
    if serverEntry and authEntry then
        authtype = authEntry.authtype
        if AUTHTYPE_WEB == authtype or AUTHTYPE_RADIUS == authtype then
            if serverEntry.wportal_page_type == 'local' then
                if 1 == tonumber(authEntry.remindflag) then
                    if reloadFlag then
                        sendWebLogin(serverEntry,authEntry,1,args)
                    else
                        if "loginpage" == args["stage"] then
                            sendWebLogin(serverEntry,authEntry,1,args)
                        else
                            sendWebJsonArray(serverEntry,authEntry,1,args)
                        end
                    end
                    if (0 == tonumber(serverEntry.remind_type)) then
                        if reloadFlag then
                            local ipset_command
                            authEntry.remindflag = 0
                            sql3.setAuthentry(authEntry)

                            if not mac or "00:00:00:00:00:00" == mac then
                                ipset_command = "del "..RULE_REMIND_IP..ip.." -exist \n"
                            elseif not ip or "0.0.0.0" == ip then
                                ipset_command = "del "..RULE_REMIND_MAC..mac.." -exist \n"
                            else
                                ipset_command = "del "..RULE_REMIND_IPMAC..ip..","..mac.." -exist \n"
                            end
                            ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        end
                    else
                        local ipset_command
                        if not mac or "00:00:00:00:00:00" == mac then
                            ipset_command = "del "..RULE_REMIND_IP..ip.." -exist \n"
                        elseif not ip or "0.0.0.0" == ip then
                            ipset_command = "del "..RULE_REMIND_MAC..mac.." -exist \n"
                        else
                            ipset_command = "del "..RULE_REMIND_IPMAC..ip..","..mac.." -exist \n"
                        end
                        ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                        authEntry.remindflag = 0
                        sql3.setAuthentry(authEntry)
                    end
                else
                    if reloadFlag then
                        sendWebLogin(serverEntry,authEntry,0,args)
                    else
                        if "loginpage" == args["stage"] then
                            sendWebLogin(serverEntry,authEntry,0,args)
                        else
                            sendWebJsonArray(serverEntry,authEntry,0,args)
                        end
                    end
                end
            else
                if 1 == tonumber(authEntry.remindflag) then
                    local ipset_command
                    sendWebLogin(serverEntry,authEntry,1,args)
                    authEntry.remindflag = 0
                    sql3.setAuthentry(authEntry)
                    if not mac or "00:00:00:00:00:00" == mac then
                        ipset_command = "del "..RULE_REMIND_IP..ip.." -exist \n"
                    elseif not ip or "0.0.0.0" == ip then
                        ipset_command = "del "..RULE_REMIND_MAC..mac.." -exist \n"
                    else
                        ipset_command = "del "..RULE_REMIND_IPMAC..ip..","..mac.." -exist \n"
                    end
                    
                    ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                else
                    if serverEntry.external_url_succ and  serverEntry.external_url_succ ~= ""  then
                        js_redirect(serverEntry.external_url_succ)
                    else
                        js_redirect(args["url"])
                    end
                end
                
            end
        elseif AUTHTYPE_ONEKEY == authtype then
            if reloadFlag then
                sendWebLogin(serverEntry,authEntry,0,args)
            else
                sendWebJsonArray(serverEntry,authEntry,0,args)
            end
        elseif AUTHTYPE_WIFI == authtype then
            if isMobile() then
                ngx.say("Portal Success")
            else
                sendPcwifiPage(serverEntry,"success")
            end
        elseif AUTHTYPE_WECHAT == authtype then
            if "local" == serverEntry.jumpPageType then
                sendWechatPage(serverEntry,"success")
            else
                if "remote" == serverEntry.jumpPageType and serverEntry.remoteUrl and  serverEntry.remoteUrl ~= ""  then
                    --ngx.redirect(serverEntry.remoteUrl)
                    js_redirect(serverEntry.remoteUrl)
                else
                    ngx.say("{error:remote url null}")
                end
            end
        else
            return ngx.say("{error:invalid authtype}")
        end
    else
        ngx.say("{error:get entry error}")
    end

end

function luci_error_handle()

    local entryString
    local curAuthnumDict = ngx.shared.curAuthnumDict
    entryString = curAuthnumDict:get("luci_reset")
    if entryString then
        curAuthnumDict:delete("luci_reset")
        local ipset_command = "rm -rf /tmp/luci-*"
        sys.exec(ipset_command) 
        local url = "http://"..WEB_DOMAIN_NAME.."/webpages/login.html"
        return ngx.redirect(url)
    end
end
    

function gw_message(serverEntry,authEntry,args)
    local msg = args["message"]

    if not authEntry or not serverEntry then
        ngx.say("{error:gwmessage_param_invalid}")
        return 
    end
    if "activate" == msg then
        if authEntry then
            sleep(1)
            ngx.header['Cookie'] = "wdastok=" .. authEntry.token .. ";"
            local redirectUrl = 'http://' .. authEntry.gw_address .. ':' .. authEntry.gw_port ..'/wifidog/auth?token=' .. authEntry.token..'&mac='..authEntry.mac
            --ngx.redirect(redirectUrl )
            js_redirect(redirectUrl )
        else
            ngx.say("{error:entry not exist}")
        end
    elseif "denied" == msg then
        if authEntry then
            if serverEntry.wportal_page_type == 'local' then
                --sendWebLogin(serverEntry,authEntry,0,args)
                sendWebJsonArray(serverEntry,authEntry,0,args)
            else
                if serverEntry.external_url_fail and serverEntry.external_url_fail ~= "" then
                    local redirectUrl
                    
                    if string.find(serverEntry.external_url_fail,'?') then
                        redirectUrl = serverEntry.external_url_fail .."&gw_address="..args.gw_address.."&gw_port="..args.gw_port.."&gw_id="..args.gw_id.."&ip="..args.ip.."&mac="..args.mac.."&url="..args.url.."&error="..authResStr[tonumber(authEntry.status)]
                    else
                        redirectUrl = serverEntry.external_url_fail .."?gw_address="..args.gw_address.."&gw_port="..args.gw_port.."&gw_id="..args.gw_id.."&ip="..args.ip.."&mac="..args.mac.."&url="..args.url.."&error="..authResStr[tonumber(authEntry.status)]
                    end

                    --ngx.redirect(redirectUrl )
                    js_redirect(redirectUrl )
                else
                    local redirectUrl
                    if string.find(serverEntry.external_url,'?') then
                        redirectUrl = serverEntry.external_url .."&gw_address="..args.gw_address.."&gw_port="..args.gw_port.."&gw_id="..args.gw_id.."&ip="..args.ip.."&mac="..args.mac.."&url="..args.url.."&error="..authResStr[tonumber(authEntry.status)]
                    else
                        redirectUrl = serverEntry.external_url .."?gw_address="..args.gw_address.."&gw_port="..args.gw_port.."&gw_id="..args.gw_id.."&ip="..args.ip.."&mac="..args.mac.."&url="..args.url.."&error="..authResStr[tonumber(authEntry.status)]
                    end
                    --ngx.redirect(redirectUrl )
                    js_redirect(redirectUrl )
                end
            end
        else
            ngx.say("{error:auth failed}")
        end
    else
        ngx.say(msg)
    end
end

function getAuthedStatus()
    local authListDict = ngx.shared.authListDict
    local authlistKeys = authListDict:get_keys(0)
    local listString
    
    if authlistKeys then
        for index,item in pairs(authlistKeys) do
                data = {key = item}
                local authEntry = sql3.getAuthentry(data)
                if authEntry and tonumber(authEntry.status) == USERSTATUS_AUTHED then
                    entryString = string.format([[token='%s',gw_id='%s',gw_address='%s',gw_port='%s',username='%s',ip='%s',mac='%s',url='%s',uptime='%s',expiretime=%d,indata=%d,outdata=%d,authtype='%s',status=%d,remindflag=%d]],
                    authEntry.token,
                    authEntry.gw_id,
                    authEntry.gw_address,
                    authEntry.gw_port,
                    authEntry.username,
                    authEntry.ip,
                    authEntry.mac,
                    authEntry.url,
                    authEntry.uptime,
                    authEntry.expiretime,
                    authEntry.indata,
                    authEntry.outdata,
                    authEntry.authtype,
                    authEntry.status,
                    authEntry.remindflag
                    )
                    
                    if not listString then
                        listString = string.format([[%s%s%s]],"{",entryString,"}")
                    else
                        listString = string.format([[%s%s%s%s%s]],listString,",","{",entryString,"}")
                    end
                end
        end
    end
    
    if listString then
        ngx.say("{"..listString.."}")
    else
        ngx.say("{}")
    end
end

function delAuthedEntryByGwid(gw_id,authtype)
    local authListDict = ngx.shared.authListDict
    local authlistKeys = authListDict:get_keys(0)
    local listString
    
    if authlistKeys then
        for index,item in pairs(authlistKeys) do
				
                data = {key = item}
                local authEntry = sql3.getAuthentry(data)
				
                if authEntry and gw_id == authEntry.gw_id and authtype == authEntry.authtype and tonumber(authEntry.status) == USERSTATUS_AUTHED then
					
                    sql3.logoutUser(authEntry.ip,authEntry.mac)
                end
        end
    end
end

function wdas_handle()
    local request_uri = ngx.var.request_uri
    local args = ngx.req.get_uri_args()
    local url = args["url"]    --for weixin login
    local gw_address = args["gw_address"]
    local curAuthnumDict = ngx.shared.curAuthnumDict
    
    if USE_LOCAL_IP_ADDRESS == 1 then
        if gw_address then
            WEB_DOMAIN_NAME = gw_address
            WECHAT_DOMAIN_NAME = gw_address
        else
            WEB_DOMAIN_NAME = ngx.var.host
            WECHAT_DOMAIN_NAME = ngx.var.host
        end
    end
	
	--dbg("request_uri: " .. request_uri)

    if string.find(request_uri,'/ping/') then 
		
        return ping(args)
    elseif string.find(request_uri,'/status') then
        if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
            ngx.say("{error:ILLEGAL ACCESS!}")
            return
        end
		
        getAuthedStatus()
    elseif string.find(request_uri,'/getentry') then
        if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
            ngx.say("{error:ILLEGAL ACCESS!}")
            return
        end
		
        sql3.getEntryByKey(args)
    elseif string.find(request_uri,'/updateusercfg') then
        if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
            ngx.say("{error:ILLEGAL ACCESS!}")
            return
        end
		
        sql3.updateUserCfg()
    elseif string.find(request_uri,'/updateauthcfg') then
        if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
            ngx.say("{error:ILLEGAL ACCESS!}")
            return
        end
		
        sql3.updateAuthCfg()
    elseif string.find(request_uri,'/delServerByGwID') then
        if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
            ngx.say("{error:ILLEGAL ACCESS!}")
            return
        end
        local gw_id = args["gw_id"]
        local authtype = args["authtype"]
		
        delAuthedEntryByGwid(gw_id,authtype)
    elseif string.find(request_uri, '/weixin/') then
		
        local ip = ngx.var.remote_addr
        local mac = sql3.getMacByIp(ip)
        if not mac then
            mac = "00:00:00:00:00:00"
        end

        entryString = curAuthnumDict:get("id_type")
        if entryString then
            if entryString == "mac" then
                ip = "0.0.0.0"
            elseif entryString == "ip" then
                mac = "00:00:00:00:00:00"
            end
        end        

        local data = {key = ip.."_"..mac}
        authEntry = sql3.getAuthentry(data)
        if authEntry and tonumber(authEntry.status) == USERSTATUS_AUTHED then
            args["ip"] = ip
            args["mac"] = mac
            args["reloadFlag"] = "reload"
            portal(nil,nil,args)
        elseif authEntry and tonumber(authEntry.status) == USERSTATUS_AUTHING then
            args["ip"] = authEntry.ip
            args["mac"] = authEntry.mac
            args["gw_id"] = authEntry.gw_id
            logincheck(args,authEntry.authtype)
        else
            if string.match(request_uri,"/weixin/%?tplogin_token=[A-Za-z0-9]+$") then
                local pos = string.find(request_uri, '/weixin/%?tplogin_token')
                --58.20.132.56 ===> www.tp-link.com.cn or use any other ip address here
                url = 'http://58.20.132.56/?domain='..sql3.encodeURI(WECHAT_DOMAIN_NAME)..'&token='..string.sub(request_uri, pos+string.len("/weixin/?tplogin_token")+1, -1)
                js_redirect(url)
            else
                args["ip"] = ip
                args["mac"] = mac
                args["gw_id"] = DFT_WIFI_INTERFACE
                logincheck(args,"wifi")
            end
        end
    elseif url and string.find(url,WECHAT_DOMAIN_NAME) then
		
        if string.match(url,"/weixin/%?tplogin_token=[A-Za-z0-9]+$") then
            logincheck(args,"wechat")
        else
            logincheck(args,"wifi")
        end
    elseif string.find(request_uri,'/login/') then
		
        login(args)
    elseif string.find(request_uri,'/logincheck/') then
		
        logincheck(args)
    elseif string.find(request_uri,'/auth/') then
		
        auth(nil,nil,args)
    elseif string.find(request_uri,'/portal/') then
		
        portal(nil,nil,args)
    elseif string.find(request_uri, '/logoutuser') then
		
        local ip = args["ip"]
        local mac = args["mac"]
        log.logger_reg(LOG_MODULE_PORTAL, LOG_USER_LOGOUT, ip)
        sql3.logoutUser(ip,mac)
        if ("127.0.0.1" ~= ngx.var.remote_addr) and ("169.254.11.21" ~= ngx.var.remote_addr) then
            arrayStr = '{"stage":"logout"}'
            ngx.header['Content-Type'] = "text/html"
            ngx.header['Content-Length'] = string.len(arrayStr)
            ngx.print(arrayStr)
        end
    elseif string.find(request_uri, '/stopAllServ') then
		
        sql3.cleanItems()
    elseif string.find(request_uri, '/luci/') then
		
        luci_error_handle()    
    else
        ngx.say("{error:unknow_request}")
    end
end    

    wdas_handle()