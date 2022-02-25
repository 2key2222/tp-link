module("ngx_authserver.ngx_sqlApi", package.seeall)

sqlite3 = require 'luasql.sqlite3'
local sys = require "luci.sys"
local uci = require "luci.model.uci"
local uci_r = uci.cursor()
local dbg = require "luci.tools.debug"
--local serverDbPath = "/tmp/portal.db"
--local authlistDbPath = "/tmp/portal.db"
--local userDbPath = "/tmp/usermngr.db"
local serverDbPath = "/etc/config/portal.db"
local authlistDbPath = "/tmp/authlist.db"
local userDbPath = "/etc/config/user.db"

local serverTable = "wportal"
local wechatTableName = "wechat"
local authlistTable = "authlist"
local userTable = "usermngr"
local curuserTable = "curuser"
local wifiTableName = "wifi"

local dbenv = sqlite3.sqlite3()
local usermgrConn = dbenv:connect(userDbPath)
local authsvrConn = dbenv:connect(serverDbPath)
local authlistConn = dbenv:connect(authlistDbPath)

local AUTHENTRY_ENUM_TOKEN      = 1
local AUTHENTRY_ENUM_GWID       = 2
local AUTHENTRY_ENUM_GWADDR     = 3
local AUTHENTRY_ENUM_GWPORT     = 4
local AUTHENTRY_ENUM_UNAME      = 5
local AUTHENTRY_ENUM_IP         = 6
local AUTHENTRY_ENUM_MAC        = 7
local AUTHENTRY_ENUM_URL        = 8
local AUTHENTRY_ENUM_UPTIME     = 9
local AUTHENTRY_ENUM_EXTIME     = 10
local AUTHENTRY_ENUM_INDATA     = 11
local AUTHENTRY_ENUM_OUDATA     = 12
local AUTHENTRY_ENUM_AUTHTYPE   = 13
local AUTHENTRY_ENUM_STATUS     = 14
local AUTHENTRY_ENUM_REMINDFLAG = 15
local AUTHENTRY_ENUM_PKT_COUNTER = 16

local CURUSERENTRY_ENUM_USERNAME = 1
local CURUSERENTRY_ENUM_REFER    = 2

local USERENTRY_ENUM_USERTYPE    = 1
local USERENTRY_ENUM_USERNAME    = 2
local USERENTRY_ENUM_PASSWORD    = 3
local USERENTRY_ENUM_EXPIRETIME  = 4
local USERENTRY_ENUM_VALIDPERIOD = 5
local USERENTRY_ENUM_MAXUSER     = 6
local USERENTRY_ENUM_UPBAND      = 7
local USERENTRY_ENUM_DOWNBAND    = 8
local USERENTRY_ENUM_MACBINDTYPE = 9
local USERENTRY_ENUM_MACBINDADDR = 10
local USERENTRY_ENUM_ENABLE      = 11
local USERENTRY_ENUM_CURUSER     = 12

local SERVERENTRY_ENUM_NAME                     = 1
local SERVERENTRY_ENUM_GWID                     = 2
local SERVERENTRY_ENUM_ENABLE                   = 3
local SERVERENTRY_ENUM_INTERFACE                = 4
local SERVERENTRY_ENUM_PAGETYPE                 = 5
local SERVERENTRY_ENUM_PAGETITLE                = 6
local SERVERENTRY_ENUM_WELINFO                  = 7
local SERVERENTRY_ENUM_COPYRIGHT                = 8
local SERVERENTRY_ENUM_BACKGROUND               = 9
local SERVERENTRY_ENUM_EXTERNALURL              = 10
local SERVERENTRY_ENUM_EXTERNALURLSUCC          = 11
local SERVERENTRY_ENUM_EXTERNALURLFAIL          = 12
local SERVERENTRY_ENUM_WPORTALTYPE              = 13
local SERVERENTRY_ENUM_REMINDENABLE             = 14
local SERVERENTRY_ENUM_REMINDTIME               = 15
local SERVERENTRY_ENUM_REMINDTYPE               = 16
local SERVERENTRY_ENUM_REMINDINTERVAL           = 17
local SERVERENTRY_ENUM_REMINDPAGETITLE          = 18
local SERVERENTRY_ENUM_REMINDPAGECONTENT        = 19
local SERVERENTRY_ENUM_FIRSTSERVERIP            = 20
local SERVERENTRY_ENUM_SECONDSERVERIP           = 21
local SERVERENTRY_ENUM_PORTALPORT               = 22
local SERVERENTRY_ENUM_SHAREKEY                 = 23
local SERVERENTRY_ENUM_SENDCOUNT                = 24
local SERVERENTRY_ENUM_EXPIRETIME               = 25
local SERVERENTRY_ENUM_AUTHTYPE                 = 26
local SERVERENTRY_ENUM_FREEINTERVAL             = 27
local SERVERENTRY_ENUM_PORTALTYPE               = 28
local SERVERENTRY_ENUM_WIREDAUTH                = 29

local SERVERENTRY_ENUM_WECHAT_NAME              = 1
local SERVERENTRY_ENUM_WECHAT_GWID              = 2
local SERVERENTRY_ENUM_WECHAT_ENABLE            = 3
local SERVERENTRY_ENUM_WECHAT_INTERFACE         = 4
local SERVERENTRY_ENUM_WECHAT_FREEINTERVAL      = 5
local SERVERENTRY_ENUM_WECHAT_AUTHTOKEN         = 6
local SERVERENTRY_ENUM_WECHAT_PUBLICNAME        = 7
local SERVERENTRY_ENUM_WECHAT_QRCODEIMAGE       = 8
local SERVERENTRY_ENUM_WECHAT_WECHATINFO        = 9
local SERVERENTRY_ENUM_WECHAT_JUMPPAGETYPE      = 10
local SERVERENTRY_ENUM_WECHAT_PORTALTYPE        = 11
local SERVERENTRY_ENUM_WECHAT_ADIMAGE           = 12
local SERVERENTRY_ENUM_WECHAT_REMOTEURL         = 13
local SERVERENTRY_ENUM_WECHAT_COPYRIGHT         = 14
local SERVERENTRY_ENUM_WECHAT_PCFREE            = 15

local SERVERENTRY_ENUM_WIFI_NAME                = 1
local SERVERENTRY_ENUM_WIFI_GWID                = 2
local SERVERENTRY_ENUM_WIFI_ENABLE              = 3
local SERVERENTRY_ENUM_WIFI_INTERFACE           = 4
local SERVERENTRY_ENUM_WIFI_SSID                = 5
local SERVERENTRY_ENUM_WIFI_FREEINTERVAL        = 6
local SERVERENTRY_ENUM_WIFI_AUTHTOKEN           = 7
local SERVERENTRY_ENUM_WIFI_WELINFO             = 8
local SERVERENTRY_ENUM_WIFI_LOGOINFO            = 9
local SERVERENTRY_ENUM_WIFI_BTNINFO             = 10
local SERVERENTRY_ENUM_WIFI_APPID               = 11
local SERVERENTRY_ENUM_WIFI_SHOPID              = 12
local SERVERENTRY_ENUM_WIFI_SECRETKEY           = 13
local SERVERENTRY_ENUM_WIFI_EXTEND              = 14
local SERVERENTRY_ENUM_WIFI_MAC                 = 15
local SERVERENTRY_ENUM_WIFI_BSSID               = 16
local SERVERENTRY_ENUM_WIFI_PORTALTYPE          = 17
local SERVERENTRY_ENUM_WIFI_BACKGROUND          = 18
local SERVERENTRY_ENUM_WIFI_LOGO                = 19
local SERVERENTRY_ENUM_WIFI_COPYRIGHT           = 20
local SERVERENTRY_ENUM_WIFI_WIREDAUTH           = 21
local SERVERENTRY_ENUM_WIFI_LOGONAME            = 22
local SERVERENTRY_ENUM_WIFI_BGDNAME             = 23

local DFT_WIFIENTRY_NAME = "dft_wifi"

local IOSCLIENTENTRY_ENUM_IP                    = 1
local IOSCLIENTENTRY_ENUM_UPTIME                = 2

local USERSTATUS_AUTHED  = 9

local RULE_KNOWN_IP = "Authed_out_ip "
local RULE_KNOWN_MAC = "Authed_out_mac "
local RULE_KNOWN_IPMAC = "Authed_out_ipmac "
local RULE_INCOM_KNOWN_IP = "Authed_in_ip "
local RULE_INCOM_KNOWN_MAC = "Authed_in_mac "
local RULE_INCOM_KNOWN_IPMAC = "Authed_in_ipmac "
local RULE_REMIND = "Authed_Remind_ip "
local RULE_REMIND_MAC = "Authed_Remind_mac "
local RULE_REMIND_IPMAC = "Authed_Remind_ipmac "
local IPSET_LIMIT  = "AuthIplimit "
local IPSET_LIMIT_IP = "AuthIplimit_IP "

local WIFIDOG_IPSETMSG_KEY = 12063
local WIFIDOG_IPSET_OPTION = 2

local CUR_AUTH_NUM = "curAuthNum"
local MAX_AUTH_NUM = 1024

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
local AUTH_RES_MAX          = 11   --Max ele num of string

local split = ','

function sfe_flush()
    local sfe_switch = uci_r:get("sfe", "setting", "switch") or "off"
    local nss_switch = uci_r:get("ecm", "global", "enable") or "off"
    if sfe_switch == 'on' then
        sys.fork_exec("dnete xfwdm -F")
    end
    if nss_switch == 'on' then
        sys.fork_exec("echo 1 > /sys/kernel/debug/ecm/ecm_db/defunct_all")
    end
   
    sys.fork_exec("[ -e \"/etc/init.d/hwnat\" ] && dnete hwnat -y")
    return true
end

function encodeURI(s)
    s = string.gsub(s, "([^%w%.%- ])", function(c) return string.format("%%%02X", string.byte(c)) end)
    return string.gsub(s, " ", "+")
end

function decodeURI(s)
    s = string.gsub(s, '%%(%x%x)', function(h) return string.char(tonumber(h, 16)) end)
    return s
end

function string.split(str, delimiter)
	if str==nil or str=='' or delimiter==nil then
		return nil
	end
	
    local result = {}
    for match in (str..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match)
    end
    return result
end

function lua_string_split(str, split_char)
    local sub_str_tab = {};
    --[[
    if str ~= nil then
        while (true) do
            
            local pos = string.find(str, split_char);
            if (not pos) then
                sub_str_tab[length + 1] = str;
                break;
            end
            
            local sub_str = string.sub(str, 1, pos - 1);            
            sub_str_tab[length + 1] = sub_str;
            str = string.sub(str, pos + 1, #str);
                                      
            length = length + 1
        end
    end
    --]]
    --gmatch is more quick--
    if str ~= nil then
        for match in (str..split_char):gmatch("(.-)"..split_char) do
            table.insert(sub_str_tab, match)
        end

    end

    return sub_str_tab;
end

--[[
--return mac (XX:XX:XX:XX:XX:XX)--
function getMacByIp(ip)
    local arptable = luci.sys.net.arptable()
    local mac = "00:00:00:00:00:00"
    for _, arpEntry in pairs(arptable) do
        if arpEntry["IP address"] == ip then
            mac = string.upper(arpEntry["HW address"])
            break
        end
    end
    return mac
end
]]--
function getMacByIp(ip)
    local mac = "00:00:00:00:00:00"
    local authCfgDict = ngx.shared.authCfgDict
    local serverlistKeys = authCfgDict:get_keys(0)
    for index,item in pairs(serverlistKeys) do
        if item:find("^wifi_") then
            local entryString = authCfgDict:get(item)
            if entryString then
                local data = {key = item}
                serverEntry = getServerentry(data,"wifi")
                if serverEntry and "on" == serverEntry.enable then
                    mac = ngx.getMac(ip,serverEntry.gw_id)
                    if mac and "00:00:00:00:00:00" ~= mac then
                        break;
                    end
                end
            end
        elseif item:find("^wechat_") then
            local entryString = authCfgDict:get(item)
            if entryString then
                local data = {key = item}
                serverEntry = getServerentry(data,"wechat")
                if serverEntry and "on" == serverEntry.enable then
                    mac = ngx.getMac(ip,serverEntry.gw_id)
                    if mac and "00:00:00:00:00:00" ~= mac then
                        break;
                    end
                end
            end
        else
            local entryString = authCfgDict:get(item)
            if entryString then
                local data = {key = item}
                serverEntry = getServerentry(data,"web")
                if serverEntry and "on" == serverEntry.enable then
                    mac = ngx.getMac(ip,serverEntry.gw_id)
                    if mac and "00:00:00:00:00:00" ~= mac then
                        break;
                    end
                end
            end
        end
    end

    return mac
end

function createUsermgrDB(tableName)
    local sql
    local dbcon = usermgrConn
    
    sql = string.format([[CREATE TABLE %s(
    userType    VARCHAR(10),
    userName     VARCHAR(100) PRIMARY KEY,
    password       VARCHAR(100),
    expireTime    INTEGER,
    validPeriod VARCHAR(20),
    maxUser        INTEGER,
    upBand        INTEGER,
    downBand    INTEGER,
    macBindType    VARCHAR(10),
    macBindAddr        VARCHAR(50),    
    noteName       VARCHAR(50),
    noteTel       VARCHAR(50),
    noteNote           VARCHAR(50),
    enable        VARCHAR(10)
    )]],tableName)
    
    status,errorString = dbcon:execute(sql)
    sql = string.format([[create index index_usermngr on %s(userName)]],tableName)
    status,errorString = dbcon:execute(sql);
end

function createAuthDBauthserver(tableName)
    local dbcon = authsvrConn
    
    sql = string.format([[CREATE TABLE %s(
    gw_id               VARCHAR(32) PRIMARY KEY,
    authtype           VARCHAR(16),
    logontype          VARCHAR(16),
    title              VARCHAR(300),
    banner             VARCHAR(300),
    copyright          VARCHAR(300),
    background         VARCHAR(64),
    failurl            VARCHAR(256),
    succurl            VARCHAR(256),
    remoteLogonUrl     VARCHAR(256),
    remindType         VARCHAR(16),
    remindTitle        VARCHAR(300),
    remindContent      VARCHAR(300),
    remindGoUrl        VARCHAR(300),
    freetime           INTEGER,
    authsvrtype        INTEGER,
    authsvrgrp         INTEGER,
    enable             INTEGER
    )]],tableName)
    
    status,errorString = dbcon:execute(sql)
    sql = string.format([[create index index_svrlist on %s(gw_id)]],tableName)
    status,errorString = dbcon:execute(sql);
end

function createAuthDBauthlist(tableName)
    local dbcon = authsvrConn
    
    sql = string.format([[CREATE TABLE %s(
        token          VARCHAR(32) PRIMARY KEY,
        gw_id          VARCHAR(16),
        gw_address     VARCHAR(18),
        gw_port        INTEGER,
        username       VARCHAR(100),
        ip             VARCHAR(18),
        mac            VARCHAR(18),
        url            VARCHAR(256),
        uptime         INTEGER,
        expiretime     INTEGER,
        indata         INTEGER,
        outdata        INTEGER,
        authtype       VARCHAR(16),
        status         INTEGER
    )]],tableName)
    
    status,errorString = dbcon:execute(sql)
    sql = string.format([[create index index_authlist on %s(token)]],tableName)
    status,errorString = dbcon:execute(sql);
    
    sql = string.format([[create index index_ip on %s(ip)]],tableName)
    status,errorString = dbcon:execute(sql);
end

function getEntry(dbname,tablename,data)
    local dbcon
    local sql,cur,row
    
    if serverDbPath == dbname then
        dbcon = authsvrConn
    elseif authlistDbPath == dbname then
        dbcon = authlistConn
    elseif userDbPath == dbname then
        dbcon = usermgrConn
    else
        return nil
    end
    
    sql = string.format([[SELECT *FROM %s WHERE %s = '%s']],tablename,data.key,data.value)
    cur = dbcon:execute(sql)

    if cur then
        row = cur:fetch ({}, "a")
        cur:close()
    end
    return row
end

function insertEntry(dbname,tablename,data)
    local dbcon
    local sql,res

    if serverDbPath == dbname then
        dbcon = authsvrConn
    elseif authlistDbPath == dbname then
        dbcon = authlistConn
    elseif userDbPath == dbname then
        dbcon = usermgrConn
    else
        return nil
    end
    
    sql = string.format([[INSERT INTO %s VALUES (%s)]],tablename,data)
    
    res = dbcon:execute(sql)

    return res
end

function delEntry(dbname,tablename,data)
    local dbcon
    local sql,res
    
    if serverDbPath == dbname then
        dbcon = authsvrConn
    elseif authlistDbPath == dbname then
        dbcon = authlistConn
    elseif userDbPath == dbname then
        dbcon = usermgrConn
    else
        return nil
    end
    
    sql = string.format([[delete FROM %s WHERE %s = '%s']],tablename,data.key,data.value)
    res = dbcon:execute(sql)

    return res
end

function updateEntry(dbname,tablename,data)
    local dbcon
    local sql,res
    
    if serverDbPath == dbname then
        dbcon = authsvrConn
    elseif authlistDbPath == dbname then
        dbcon = authlistConn
    elseif userDbPath == dbname then
        dbcon = usermgrConn
    else
        return nil
    end
    
    sql = string.format([[update %s set %s='%s' where %s='%s']],tablename,data.key,data.value,data.priKey,data.priVal)
    res,errStr = dbcon:execute(sql)

    return res,errStr
end

function copyTbl(oriTbl)
    local tab = {}
    for k, v in pairs(oriTbl or {}) do
        if type(v) ~= "table" then
            tab[k] = v
        else
            tab[k] = copyTab(v)
        end
    end
    return tab
end

function getAllByCmd(dbname,tablename,cmd)
    local dbcon
    local cur,row
    
    if serverDbPath == dbname then
        dbcon = authsvrConn
    elseif authlistDbPath == dbname then
        dbcon = authlistConn
    elseif userDbPath == dbname then
        dbcon = usermgrConn
    else
        return nil
    end

    cur,errStr = dbcon:execute(cmd)
    
    if not cur then
        return nil,errStr
    end
    
    row = cur:fetch ({}, "a")
    if tonumber(row) ~= 0 and row ~= nil then
        while row do
            table.insert(entry, copyTbl(row))
            row = cur:fetch (row, "a")
        end
    end
    cur:close()
    return entry
end

function getValidPeriod(validPeriod)
	local timeArray = string.split(validPeriod,'-')
	local startTime = string.split(timeArray[1],':')
	local endTime   = string.split(timeArray[2],':')
	
	local validTime = {}
	
	validTime.startHour = tonumber(startTime[1])
	validTime.startMin	= tonumber(startTime[2])
	validTime.startSec	= 0
	validTime.endHour	= tonumber(endTime[1])
	validTime.endMin	= tonumber(endTime[2])
	validTime.endSec	= 0
	
	--dbg.dumptable(validTime)
	return validTime
end

function checkAuthPeriod(validPeriod)

	local res = true
	local curTime = {}
	curTime.hour	 = tonumber(os.date('%H'))
	curTime.min	 = tonumber(os.date('%M'))
	curTime.sec	 = tonumber(os.date('%S'))
	
	--dbg.dumptable(curTime)
	
	local validTime = getValidPeriod(validPeriod)

	if validTime.startHour < validTime.endHour or (validTime.startHour == validTime.endHour and validTime.startMin < validTime.endMin) then
		if curTime.hour < validTime.startHour or (curTime.hour == validTime.startHour and curTime.min < validTime.startMin)
			or (curTime.hour > validTime.endHour) or (curTime.hour == validTime.endHour and curTime.min > validTime.endMin) then
			--dbg('not in the valid auth period')
			res = false
		else
			--dbg('in the valid auth period')
			res = true
		end
	else
		if curTime.hour > validTime.startHour or (curTime.hour == validTime.startHour and curTime.min > validTime.startMin)
			or (curTime.hour < validTime.endHour) or (curTime.hour == validTime.endHour and curTime.min < validTime.endMin) then
			--dbg('in the valid auth period')
			res = true
		else
			--dbg('not in the valid auth period')
			res = false
		end
	end
	
	return res

end

function checkUser(username,password,ip,mac)
    local mres = AUTH_RES_NO_USER
    local data = {key = username}
    local userEntry = getUserentry(data)

    if userEntry == nil then
        return mres
    end

    if userEntry.enable == 'on' and password == userEntry.password then
        local curUser = 0
        local data = {key = userEntry.userName} 
        local curuserEntry = getCuruserEntry(data)
        if curuserEntry then
            curUser = curuserEntry.curUser
        end
        if checkAuthPeriod(userEntry.validPeriod) == true then
            if tonumber(userEntry.maxUser) > curUser then
                if userEntry.userType == 'formal' then
                    local curTime = os.time()
                    if curTime > tonumber(userEntry.expireTime) then 
                        mres = AUTH_RES_USER_EXPIRE
                    elseif userEntry.macBindType == 'static' then 
                        if string.upper(mac:gsub(":", "%-")) == string.upper(userEntry.macBindAddr:gsub(":", "%-")) then
                            mres = AUTH_RES_SUCC
                        else
                            mres = AUTH_RES_MAC_ERR
                        end
                    elseif userEntry.macBindType == 'dynamic' then
                        if userEntry.macBindAddr ~= '00:00:00:00:00:00' then 
                            if string.upper(mac:gsub(":", "%-")) == string.upper(userEntry.macBindAddr:gsub(":", "%-")) then
                                if curUser ~= 0 then
                                    mres = AUTH_RES_USER_FULL
                                else
                                    mres = AUTH_RES_SUCC
                                end
                            else
                                mres = AUTH_RES_MAC_ERR
                            end
                        elseif curUser == 0 then
                            if not mac then
                                mac = '00:00:00:00:00:00'
                            end
                            userEntry.macBindAddr = mac
                            setUserEntry(userEntry)
                            mres = AUTH_RES_SUCC
                        else
                            mres = AUTH_RES_MAC_ERR
                        end
                    else
                        mres = AUTH_RES_SUCC
                    end
                else 
                     mres = AUTH_RES_SUCC
                end
            else
                mres = AUTH_RES_USER_FULL
            end
        else
            mres = AUTH_RES_INVAL_PERIOD
        end
    elseif userEntry.enable == 'off' then
        mres = AUTH_RES_USER_DISABLED
    else
        mres = AUTH_RES_USER_PWD_ERR
    end 

    return mres
end

--[[
function userCheck(dbname,tableName,clientEntry)
    local mres = AUTH_RES_NO_USER
    local sql
    
    if serverDbPath == dbname then
        dbcon = authsvrConn
    elseif authlistDbPath == dbname then
        dbcon = authlistConn
    elseif userDbPath == dbname then
        dbcon = usermgrConn
    else
        return mres
    end
    
    cur = dbcon:execute(string.format("
        SELECT *FROM %s WHERE userName = '%s'
    ",tableName,clientEntry.userName))
    
    if not cur then
        return mres
    end
    
    local row = cur:fetch ({}, "a")
    if tonumber(row) ~= 0 and row ~= nil then
        --print(string.format("the same item found."))
        while row do
            if row.enable == 'on' and clientEntry.password == row.password then
                print('entry enable,password equals')
                local curUser = 0
                local data = {key = "userName", value = row.userName} 
                local curuserEntry = getEntry(authlistDbPath,curuserTable,data)
                if curuserEntry then
                    curUser = curuserEntry.curUser
                end
				if checkAuthPeriod(row.validPeriod) == true then
					if tonumber(row.maxUser) > tonumber(curUser) then
						print('maxUser > curUser,still can be used')
						if row.userType == 'formal' then
							print('form user')
							local curTime = os.time()
							if curTime > tonumber(row.expireTime) then 
                                mres = AUTH_RES_USER_EXPIRE
								print('the user is out of date!')
							elseif row.macBindType == 'static' then 
								print('mac bind static')
								if clientEntry.macAddr == row.macBindAddr then
									print('macAddr equals,pass!')
									mres = AUTH_RES_SUCC
                                else
                                    mres = AUTH_RES_MAC_ERR
								end
							elseif row.macBindType == 'dynamic' then
								print('mac bind dynamic')
								if row.macBindAddr ~= '00:00:00:00:00:00' then 
									if clientEntry.macAddr == row.macBindAddr then
										if curUser ~= 0 then
                                            mres = AUTH_RES_MAC_ERR
											print('macAddr equals,but has been used,fail')
										else
											print('macAddr equals,and has not been used,pass')
											mres = AUTH_RES_SUCC                                        
										end
									end
								elseif curUser == 0 then
									print('row.macBindAddr == 00:00:00:00:00:00 and row.curUser == 0,pass!')
									sql = string.format("update %s set macBindAddr= '%s' where userName='%s'",tableName,clientEntry.macAddr,row.userName)
									mres = AUTH_RES_SUCC
                                else
                                    mres = AUTH_RES_MAC_ERR
								end
							else
								print('mac bind none,pass')
								mres = AUTH_RES_SUCC
							end
						else 
							print('form user,pass')
							 mres = AUTH_RES_SUCC
						end
                    else
                        mres = AUTH_RES_USER_FULL
					end
                else
                    mres = AUTH_RES_INVAL_PERIOD
				end
            else
                print('wrong password,deny!')
                mres = AUTH_RES_USER_PWD_ERR
            end
            
                
            if mres == AUTH_RES_SUCC then
                local data = {key = "userName", value = row.userName} 
                local curuserEntry = getEntry(authlistDbPath,curuserTable,data)
                if curuserEntry then
                    sql = string.format("update %s set curUser= %d where userName='%s'",curuserTable,curuserEntry.curUser+1,curuserEntry.userName)
                    res,errorString = authlistConn:execute(sql)
                    print('errorString: ',errorString)
                else
                    sql = string.format("INSERT INTO %s VALUES ('%s','%d')",curuserTable,row.userName,1)
                    res,errorString = authlistConn:execute(sql)
                    if not res then
                        ngx.log(ngx.ERR,"Insert into curusertable err:",errorString)
                    end
                end
                
                cur:close()
                return mres
            end

            row = cur:fetch (row, "a")
            
        end
    else
        print('the user does not exist,deny!')
        mres = AUTH_RES_NO_USER
    end
    
    cur:close()    
    return mres
end
]]--

function getCuruserEntry(data)
    local curuserEntry = {}
    local authUserDict = ngx.shared.authUserDict
    local entryString, errMsg
    entryString = authUserDict:get(data.key)

    if entryString then
        local entryTable = lua_string_split(entryString, split)
        curuserEntry.userName           = entryTable[CURUSERENTRY_ENUM_USERNAME]
        curuserEntry.curUser            = tonumber(entryTable[CURUSERENTRY_ENUM_REFER])
        return curuserEntry        
    else
        return nil
    end
end

function addCuruserEntry(data)
    local authUserDict = ngx.shared.authUserDict
    return authUserDict:safe_add(data.key, data.value)
end

function setCuruserEntry(userEntry)
    local authUserDict = ngx.shared.authUserDict

    local authEntryString = string.format("%s,%d", userEntry.userName, userEntry.curUser)

    return authUserDict:replace(userEntry.userName, authEntryString)
end

function delCuruserEntry(username)
    local authUserDict = ngx.shared.authUserDict
    return authUserDict:delete(username)
end

updateUserCfg = function ()
    local dbenv = sqlite3.sqlite3()
    local svrCon = dbenv:connect(userDbPath)
    local ok, err,sql,userEntry,cur,res
    local userEntry = {}
    local userCfgDict = ngx.shared.userCfgDict
    local keys = userCfgDict:get_keys(0)

    sql = string.format([[SELECT *FROM %s ]],userTable)
    cur = svrCon:execute(sql)
    
    if cur then
        userEntry = cur:fetch ({}, "a")
        if tonumber(userEntry) ~= 0 and userEntry ~= nil then
            while userEntry do

            for index,item in pairs(keys) do
                if item == userEntry.userName then
                    --ngx.log(ngx.ERR, "Auth server update...", keys[index], item, key)
                    keys[index] = ""
                end
            end

            local serverString = string.format("%s,%s,%s,%d,%s,%d,%d,%d,%s,%s,%s,%d",
                                                    userEntry.userType,
                                                    userEntry.userName,
                                                    userEntry.password,
                                                    userEntry.expireTime,
                                                    userEntry.validPeriod,
                                                    userEntry.maxUser,
                                                    userEntry.upBand,
                                                    userEntry.downBand,
                                                    userEntry.macBindType,
                                                    userEntry.macBindAddr,
                                                    userEntry.enable,
                                                    userEntry.curUser)
                --ngx.log(ngx.ERR, "update server auth----{{{{", serverString)
                userCfgDict:safe_set(userEntry.userName, serverString)

                userEntry = cur:fetch (userEntry, "a")
            end
        end
        cur:close()            
        svrCon:close()
        dbenv:close()

        for index,item in pairs(keys) do
            if item ~= "" then
                --ngx.log(ngx.ERR, "Delete item key...", item)
                userCfgDict:delete(item)
            end
        end
    end
end

function getUserentry(data)
    local userEntry = {}
    local userCfgDict = ngx.shared.userCfgDict
    local entryString, errMsg
    entryString = userCfgDict:get(data.key)

    if entryString then
        local entryTable = lua_string_split(entryString, split)
        userEntry.userType      =   entryTable[USERENTRY_ENUM_USERTYPE]
        userEntry.userName      =   entryTable[USERENTRY_ENUM_USERNAME]
        userEntry.password      =   entryTable[USERENTRY_ENUM_PASSWORD]
        userEntry.expireTime    =   tonumber(entryTable[USERENTRY_ENUM_EXPIRETIME])
        userEntry.validPeriod   =   entryTable[USERENTRY_ENUM_VALIDPERIOD]
        userEntry.maxUser       =   tonumber(entryTable[USERENTRY_ENUM_MAXUSER])
        userEntry.upBand        =   tonumber(entryTable[USERENTRY_ENUM_UPBAND])
        userEntry.downBand      =   tonumber(entryTable[USERENTRY_ENUM_DOWNBAND])
        userEntry.macBindType   =   entryTable[USERENTRY_ENUM_MACBINDTYPE]
        userEntry.macBindAddr   =   entryTable[USERENTRY_ENUM_MACBINDADDR]
        userEntry.enable        =   entryTable[USERENTRY_ENUM_ENABLE]
        userEntry.curUser       =   tonumber(entryTable[USERENTRY_ENUM_CURUSER])

        return userEntry        
    else
        return nil
    end
end

function setUserEntry(userEntry)
    local userCfgDict = ngx.shared.userCfgDict

    local userEntryString = string.format("%s,%s,%s,%d,%s,%d,%d,%d,%s,%s,%s,%d",
                                                    userEntry.userType,
                                                    userEntry.userName,
                                                    userEntry.password,
                                                    userEntry.expireTime,
                                                    userEntry.validPeriod,
                                                    userEntry.maxUser,
                                                    userEntry.upBand,
                                                    userEntry.downBand,
                                                    userEntry.macBindType,
                                                    userEntry.macBindAddr,
                                                    userEntry.enable,
                                                    userEntry.curUser)
                --ngx.log(ngx.ERR, "new userCfg:", userEntryString)

    return userCfgDict:replace(userEntry.userName, userEntryString)  
end

function getEntryByKey(args)
    local ip = args["ip"]
    local mac = args["mac"]
    
    if not ip or not mac then
        ngx.say("{}")
        return
    end
    
    if ip and mac then
        local data = {key = ip .."_".. mac}
        local authEntry = getAuthentry(data)
        if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
            local entryString = string.format([[token='%s',gw_id='%s',gw_address='%s',gw_port='%s',username='%s',ip='%s',mac='%s',url='%s',uptime='%s',expiretime=%d,indata=%d,outdata=%d,authtype='%s',status=%d,remindflag=%d]],
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
            entryString = string.format([[%s%s%s]],"{",entryString,"}")
            ngx.say(entryString)
        else
            ngx.say("{}")
        end
        
    else
        ngx.say("{}")
    end
end

function getAuthentry(data)
    local authEntry = {}
    local authListDict = ngx.shared.authListDict
    local entryString, errMsg
    
    entryString, errMsg = authListDict:get(data.key)
    if entryString then
        local entryTable = lua_string_split(entryString, split)
        authEntry.token             = entryTable[AUTHENTRY_ENUM_TOKEN]
        authEntry.gw_id             = entryTable[AUTHENTRY_ENUM_GWID]
        authEntry.gw_address        = entryTable[AUTHENTRY_ENUM_GWADDR]
        authEntry.gw_port           = tonumber(entryTable[AUTHENTRY_ENUM_GWPORT])
        authEntry.username          = entryTable[AUTHENTRY_ENUM_UNAME]
        authEntry.ip                = entryTable[AUTHENTRY_ENUM_IP]
        authEntry.mac               = entryTable[AUTHENTRY_ENUM_MAC]
        authEntry.url               = entryTable[AUTHENTRY_ENUM_URL]
        authEntry.uptime            = tonumber(entryTable[AUTHENTRY_ENUM_UPTIME])
        authEntry.expiretime        = tonumber(entryTable[AUTHENTRY_ENUM_EXTIME])
        authEntry.indata            = tonumber(entryTable[AUTHENTRY_ENUM_INDATA])
        authEntry.outdata           = tonumber(entryTable[AUTHENTRY_ENUM_OUDATA])
        authEntry.authtype          = entryTable[AUTHENTRY_ENUM_AUTHTYPE]
        authEntry.status            = tonumber(entryTable[AUTHENTRY_ENUM_STATUS])
        authEntry.remindflag        = tonumber(entryTable[AUTHENTRY_ENUM_REMINDFLAG])
        authEntry.pkt_counter       = tonumber(entryTable[AUTHENTRY_ENUM_PKT_COUNTER])        

        return authEntry

    else
        return nil
    end
end

function checkAuthEntryNumMax()
    local curAuthnumDict = ngx.shared.curAuthnumDict
    local ok, err,curAuthNum
    
    curAuthNum = curAuthnumDict:get(CUR_AUTH_NUM)

    if tonumber(curAuthNum) >= MAX_AUTH_NUM then
        return 0
    else
        return 1
    end
end

function addAuthentry(data)
    local authListDict = ngx.shared.authListDict
    local curAuthnumDict = ngx.shared.curAuthnumDict
    local ok, err,curAuthNum
    
    curAuthNum = curAuthnumDict:get(CUR_AUTH_NUM)
    if tonumber(curAuthNum) >= MAX_AUTH_NUM then
        ngx.log(ngx.ERR,"authlist full. Failed to add key:",data.value)
        return nil,"authlist full"
    end
    ok, err = authListDict:safe_add(data.key, data.value)
    if not ok then
        ngx.log(ngx.ERR,"add authentry to auth dict failed.Err:",err)
        return ok,err
    end
    
    return incAuthlistNum()
end

function setAuthentry(authEntry)
    local authListDict = ngx.shared.authListDict

    local authEntryString = string.format("%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%s,%d,%d,%d",
                                                authEntry.token,
                                                authEntry.gw_id,
                                                authEntry.gw_address,
                                                authEntry.gw_port,
                                                authEntry.username,
                                                authEntry.ip,
                                                authEntry.mac,
                                                decodeURI(authEntry.url),
                                                authEntry.uptime,
                                                authEntry.expiretime,
                                                authEntry.indata,
                                                authEntry.outdata,
                                                authEntry.authtype,
                                                authEntry.status,
                                                authEntry.remindflag,
                                                authEntry.pkt_counter)

    return authListDict:replace(authEntry.ip.."_"..authEntry.mac, authEntryString)    
end

function delAuthentry(key)
    local authListDict = ngx.shared.authListDict
    local ok, err = authListDict:delete(key)
    
    if not ok then
        ngx.log(ngx.ERR,"del authentry to auth dict failed.Err:",err)
        return ok,err
    end
    
    return decAuthlistNum()
end

function incAuthlistNum()
    local curAuthnumDict = ngx.shared.curAuthnumDict
    return curAuthnumDict:incr(CUR_AUTH_NUM, 1)
end

function decAuthlistNum()
    local curAuthnumDict = ngx.shared.curAuthnumDict
    return curAuthnumDict:incr(CUR_AUTH_NUM, -1)
end

function addIOSClientEntry(data)
    local iosDict = ngx.shared.iosClientDict
    return iosDict:safe_add(data.key, data.value)
end

function getIOSClientEntry(data)
    local iosDict = ngx.shared.iosClientDict
    local ok,err
    local iosClient = {}

    entryString, errMsg = iosDict:get(data.key)
    if entryString then
        local entryTable = lua_string_split(entryString, split)
        iosClient.ip             = entryTable[IOSCLIENTENTRY_ENUM_IP]
        iosClient.expireTime     = tonumber(entryTable[IOSCLIENTENTRY_ENUM_UPTIME])
        return iosClient
    else
        return nil
    end
end

function delIOSClientEntry(ip)
    local iosDict = ngx.shared.iosClientDict
    return iosDict:delete(ip )    
end

updateAuthCfg = function ()
    local dbenv = sqlite3.sqlite3()
    local svrCon = dbenv:connect(serverDbPath)
    local ok, err,sql,serverEntry,cur,res
    local serverEntry = {}
    local authCfgDict = ngx.shared.authCfgDict
    local keys = authCfgDict:get_keys(0)
    local keyName   --web+gw_id (web onekey) or wechat+gw_id or wifi+gw_id
    local wifiEntry = {}

    sql = string.format([[SELECT *FROM %s ]],serverTable)
    cur = svrCon:execute(sql)
    
    if cur then
        serverEntry = cur:fetch ({}, "a")
        if tonumber(serverEntry) ~= 0 and serverEntry ~= nil then
            while serverEntry do

            for index,item in pairs(keys) do
                if item == "web_"..serverEntry.gw_id then
                    ngx.log(ngx.ERR, "Auth server update...", keys[index], item, index)
                    keys[index] = ""
                end
            end

            local serverString
            if serverEntry.portal_type == "web" or serverEntry.portal_type == "onekey" then
                keyName = "web_"..serverEntry.gw_id
                serverString = string.format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%s,%s,%s,%d,%s,%d,%d,%s,%d,%s,%s",
                                                        serverEntry.name,
                                                        serverEntry.gw_id,
                                                        serverEntry.enable,
                                                        serverEntry.interface,
                                                        serverEntry.wportal_page_type,
                                                        serverEntry.page_title,
                                                        serverEntry.wel_info,
                                                        serverEntry.copyright,
                                                        serverEntry.background,
                                                        serverEntry.external_url,
                                                        serverEntry.external_url_succ,
                                                        serverEntry.external_url_fail,
                                                        serverEntry.wportal_type,
                                                        serverEntry.remind_enable,
                                                        serverEntry.remind_time,
                                                        serverEntry.remind_type,
                                                        serverEntry.remind_interval,
                                                        serverEntry.remind_page_title,
                                                        serverEntry.remind_page_content,
                                                        serverEntry.first_server_ip,
                                                        serverEntry.second_server_ip,
                                                        serverEntry.portal_port,
                                                        serverEntry.share_key,
                                                        serverEntry.send_count,
                                                        serverEntry.expire_time,
                                                        serverEntry.auth_type,
                                                        serverEntry.free_interval,
                                                        serverEntry.portal_type,
                                                        serverEntry.wired_auth)
                ngx.log(ngx.ERR, "update server auth----{{{{", serverString, "}}}----")
                authCfgDict:safe_set(keyName, serverString)
                
                if serverEntry.wportal_type == 'radius' then
                    if "on" == serverEntry.enable then
                        local cmd = string.format([[radius_generate_config_file.sh "%s" "%s" "%s" "%s" "%s" %d %d]],serverEntry.interface,serverEntry.first_server_ip,serverEntry.second_server_ip,serverEntry.portal_port,serverEntry.share_key,serverEntry.send_count+1,serverEntry.expire_time)
                        sys.fork_exec(cmd)
                    else
                        local radiusCfgFile = "/etc/radiusclient-ng/radiusclient_"..serverEntry.interface..".conf"
                        if nixio.fs.access(radiusCfgFile) then
                            sys.fork_exec("rm -f " .. radiusCfgFile)
                        end
                    end
                end
            else
                ngx.log(ngx.ERR, "error portal_type when add wportal dict")
            end
                serverEntry = cur:fetch (serverEntry, "a")
            end
        end
        cur:close()

        for index,item in pairs(keys) do
            if item ~= "" then
                ngx.log(ngx.ERR, "Delete item key...", item)
                authCfgDict:delete(item)
            end
        end
    end
    
    sql = string.format([[SELECT *FROM %s ]],wechatTableName)
    cur = svrCon:execute(sql)
    
    if cur then
        serverEntry = cur:fetch ({}, "a")
        if tonumber(serverEntry) ~= 0 and serverEntry ~= nil then
            while serverEntry do

            for index,item in pairs(keys) do
                if item == "wechat_"..serverEntry.gw_id then
                    ngx.log(ngx.ERR, "Auth server update...", keys[index], item, index)
                    keys[index] = ""
                end
            end

            local serverString
            if serverEntry.portal_type == "wechat" then
                keyName = "wechat_"..serverEntry.gw_id
                serverString = string.format("%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                                                        serverEntry.name,
                                                        serverEntry.gw_id,
                                                        serverEntry.enable,
                                                        serverEntry.interface,                                                   
                                                        serverEntry.free_interval,
                                                        serverEntry.authToken,
                                                        serverEntry.publicName,
                                                        serverEntry.qrcodeImage,
                                                        serverEntry.wechatInfo,
                                                        serverEntry.jumpPageType,
                                                        serverEntry.portal_type,
                                                        serverEntry.adImage,
                                                        serverEntry.remoteUrl,
                                                        serverEntry.copyright,
                                                        serverEntry.pcfree)
                ngx.log(ngx.ERR, "update server auth----{{{{", serverString, "}}}----")
                authCfgDict:safe_set(keyName, serverString)
            else
                ngx.log(ngx.ERR, "error portal_type when add wechat dict")
            end
                serverEntry = cur:fetch (serverEntry, "a")
            end
        end
        cur:close()

        for index,item in pairs(keys) do
            if item ~= "" then
                ngx.log(ngx.ERR, "Delete item key...", item)
                authCfgDict:delete(item)
            end
        end
    end
    
    sql = string.format([[SELECT *FROM %s ]],wifiTableName)
    cur = svrCon:execute(sql)
    
    if cur then
        wifiEntry = cur:fetch ({}, "a")
        if tonumber(wifiEntry) ~= 0 and wifiEntry ~= nil then
            while wifiEntry do

            for index,item in pairs(keys) do
                if item == "wifi_"..wifiEntry.gw_id then
                    ngx.log(ngx.ERR, "Auth server update...", keys[index], item, index)
                    keys[index] = ""
                end
            end

            local serverString
            if wifiEntry.portal_type == "wifi" then
                keyName = "wifi_"..wifiEntry.gw_id
                serverString = string.format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
                                                        wifiEntry.name,
                                                        wifiEntry.gw_id,
                                                        wifiEntry.enable,
                                                        wifiEntry.interface,
                                                        wifiEntry.ssid,
                                                        wifiEntry.free_interval,
                                                        wifiEntry.authToken,
                                                        wifiEntry.welinfo,
                                                        wifiEntry.logoinfo,
                                                        wifiEntry.btninfo,
                                                        wifiEntry.appid,
                                                        wifiEntry.shopid,
                                                        wifiEntry.secretkey,
                                                        wifiEntry.extend,
                                                        wifiEntry.mac,
                                                        wifiEntry.bssid,
                                                        wifiEntry.portal_type,
                                                        wifiEntry.background,
                                                        wifiEntry.logo,
                                                        wifiEntry.copyright,
                                                        wifiEntry.wired_auth,
                                                        wifiEntry.logoname,
                                                        wifiEntry.bgdname)
                ngx.log(ngx.ERR, "update server auth----{{{{", serverString, "}}}----")
                authCfgDict:safe_set(keyName, serverString)
            else
                ngx.log(ngx.ERR, "error portal_type when add auth dict")
            end
                wifiEntry = cur:fetch (wifiEntry, "a")
            end
        end
        cur:close()

        for index,item in pairs(keys) do
            if item ~= "" then
                ngx.log(ngx.ERR, "Delete item key...", item)
                authCfgDict:delete(item)
            end
        end
    end
    
    svrCon:close()
    dbenv:close()
end

function formatWportalEntry(entryTable)
    local serverEntry = {}
    serverEntry.name                    = entryTable[SERVERENTRY_ENUM_NAME]
    serverEntry.gw_id                   = entryTable[SERVERENTRY_ENUM_GWID]
    serverEntry.enable                  = entryTable[SERVERENTRY_ENUM_ENABLE]
    serverEntry.interface               = entryTable[SERVERENTRY_ENUM_INTERFACE]
    serverEntry.wportal_page_type       = entryTable[SERVERENTRY_ENUM_PAGETYPE]
    serverEntry.page_title              = entryTable[SERVERENTRY_ENUM_PAGETITLE]
    serverEntry.wel_info                = entryTable[SERVERENTRY_ENUM_WELINFO]
    serverEntry.copyright               = entryTable[SERVERENTRY_ENUM_COPYRIGHT]
    serverEntry.background              = entryTable[SERVERENTRY_ENUM_BACKGROUND]
    serverEntry.external_url            = entryTable[SERVERENTRY_ENUM_EXTERNALURL]
    serverEntry.external_url_succ       = entryTable[SERVERENTRY_ENUM_EXTERNALURLSUCC]
    serverEntry.external_url_fail       = entryTable[SERVERENTRY_ENUM_EXTERNALURLFAIL]
    serverEntry.wportal_type            = entryTable[SERVERENTRY_ENUM_WPORTALTYPE]
    serverEntry.remind_enable           = entryTable[SERVERENTRY_ENUM_REMINDENABLE]
    serverEntry.remind_time             = entryTable[SERVERENTRY_ENUM_REMINDTIME]
    serverEntry.remind_type             = entryTable[SERVERENTRY_ENUM_REMINDTYPE]
    serverEntry.remind_interval         = entryTable[SERVERENTRY_ENUM_REMINDINTERVAL]
    serverEntry.remind_page_title       = entryTable[SERVERENTRY_ENUM_REMINDPAGETITLE]
    serverEntry.remind_page_content     = entryTable[SERVERENTRY_ENUM_REMINDPAGECONTENT]
    serverEntry.first_server_ip         = entryTable[SERVERENTRY_ENUM_FIRSTSERVERIP]
    serverEntry.second_server_ip        = entryTable[SERVERENTRY_ENUM_SECONDSERVERIP]
    serverEntry.portal_port             = entryTable[SERVERENTRY_ENUM_PORTALPORT]
    serverEntry.share_key               = entryTable[SERVERENTRY_ENUM_SHAREKEY]
    serverEntry.send_count              = entryTable[SERVERENTRY_ENUM_SENDCOUNT]
    serverEntry.expire_time             = entryTable[SERVERENTRY_ENUM_EXPIRETIME]
    serverEntry.auth_type               = entryTable[SERVERENTRY_ENUM_AUTHTYPE]
    serverEntry.free_interval           = entryTable[SERVERENTRY_ENUM_FREEINTERVAL]
    serverEntry.portal_type             = entryTable[SERVERENTRY_ENUM_PORTALTYPE]
    serverEntry.wired_auth              = entryTable[SERVERENTRY_ENUM_WIREDAUTH]
                
    return serverEntry
end

function formatWechatEntry(entryTable)
    local serverEntry = {}
    
    serverEntry.name                    = entryTable[SERVERENTRY_ENUM_WECHAT_NAME]
    serverEntry.gw_id                   = entryTable[SERVERENTRY_ENUM_WECHAT_GWID]
    serverEntry.enable                  = entryTable[SERVERENTRY_ENUM_WECHAT_ENABLE]
    serverEntry.interface               = entryTable[SERVERENTRY_ENUM_WECHAT_INTERFACE]
    serverEntry.free_interval           = entryTable[SERVERENTRY_ENUM_WECHAT_FREEINTERVAL]
    serverEntry.authToken               = entryTable[SERVERENTRY_ENUM_WECHAT_AUTHTOKEN]
    serverEntry.publicName              = entryTable[SERVERENTRY_ENUM_WECHAT_PUBLICNAME]
    serverEntry.qrcodeImage             = entryTable[SERVERENTRY_ENUM_WECHAT_QRCODEIMAGE]
    serverEntry.wechatInfo              = entryTable[SERVERENTRY_ENUM_WECHAT_WECHATINFO]
    serverEntry.jumpPageType            = entryTable[SERVERENTRY_ENUM_WECHAT_JUMPPAGETYPE]
    serverEntry.portal_type             = entryTable[SERVERENTRY_ENUM_WECHAT_PORTALTYPE]
    serverEntry.adImage                 = entryTable[SERVERENTRY_ENUM_WECHAT_ADIMAGE]
    serverEntry.remoteUrl               = entryTable[SERVERENTRY_ENUM_WECHAT_REMOTEURL]
    serverEntry.copyright               = entryTable[SERVERENTRY_ENUM_WECHAT_COPYRIGHT]
    serverEntry.pcfree                  = entryTable[SERVERENTRY_ENUM_WECHAT_PCFREE]
                
    return serverEntry
end

function formatWifiEntry(entryTable)
    local serverEntry = {}
    
    serverEntry.name                    = entryTable[SERVERENTRY_ENUM_WIFI_NAME]
    serverEntry.gw_id                   = entryTable[SERVERENTRY_ENUM_WIFI_GWID]
    serverEntry.enable                  = entryTable[SERVERENTRY_ENUM_WIFI_ENABLE]
    serverEntry.interface               = entryTable[SERVERENTRY_ENUM_WIFI_INTERFACE]
    serverEntry.ssid                    = entryTable[SERVERENTRY_ENUM_WIFI_SSID]
    serverEntry.free_interval           = entryTable[SERVERENTRY_ENUM_WIFI_FREEINTERVAL]
    serverEntry.authToken               = entryTable[SERVERENTRY_ENUM_WIFI_AUTHTOKEN]
    serverEntry.welinfo                 = entryTable[SERVERENTRY_ENUM_WIFI_WELINFO]
    serverEntry.logoinfo                = entryTable[SERVERENTRY_ENUM_WIFI_LOGOINFO]
    serverEntry.btninfo                 = entryTable[SERVERENTRY_ENUM_WIFI_BTNINFO]
    serverEntry.appid                   = entryTable[SERVERENTRY_ENUM_WIFI_APPID]
    serverEntry.shopid                  = entryTable[SERVERENTRY_ENUM_WIFI_SHOPID]
    serverEntry.secretkey               = entryTable[SERVERENTRY_ENUM_WIFI_SECRETKEY]
    serverEntry.extend                  = entryTable[SERVERENTRY_ENUM_WIFI_EXTEND]
    serverEntry.mac                     = entryTable[SERVERENTRY_ENUM_WIFI_MAC]
    serverEntry.bssid                   = entryTable[SERVERENTRY_ENUM_WIFI_BSSID]
    serverEntry.portal_type             = entryTable[SERVERENTRY_ENUM_WIFI_PORTALTYPE]
    serverEntry.background              = entryTable[SERVERENTRY_ENUM_WIFI_BACKGROUND]
    serverEntry.logo                    = entryTable[SERVERENTRY_ENUM_WIFI_LOGO]
    serverEntry.copyright               = entryTable[SERVERENTRY_ENUM_WIFI_COPYRIGHT]
    serverEntry.wired_auth              = entryTable[SERVERENTRY_ENUM_WIFI_WIREDAUTH]
    serverEntry.logoname                = entryTable[SERVERENTRY_ENUM_WIFI_LOGONAME]
    serverEntry.bgdname                 = entryTable[SERVERENTRY_ENUM_WIFI_BGDNAME]
                
    return serverEntry
end

function getServerentry(data,authtype)
    local serverEntry = {}
    local authCfgDict = ngx.shared.authCfgDict
    local entryString, errMsg
    entryString = authCfgDict:get(data.key)

    if entryString then
        local entryTable = lua_string_split(entryString, split)
        if ('on' ~= entryTable[SERVERENTRY_ENUM_ENABLE]) then
            return nil
        end
        
        if entryTable[SERVERENTRY_ENUM_PORTALTYPE] == "web" or entryTable[SERVERENTRY_ENUM_PORTALTYPE] == "onekey" then
            if authtype and authtype ~= entryTable[SERVERENTRY_ENUM_PORTALTYPE] then
                return nil
            else
                serverEntry = formatWportalEntry(entryTable)
            end
        elseif entryTable[SERVERENTRY_ENUM_WIFI_PORTALTYPE] == "wifi" then
            if authtype and authtype ~= entryTable[SERVERENTRY_ENUM_WIFI_PORTALTYPE] then
                return nil
            else
                serverEntry = formatWifiEntry(entryTable)
            end
        elseif entryTable[SERVERENTRY_ENUM_WECHAT_PORTALTYPE] == "wechat" then
            if authtype and authtype ~= entryTable[SERVERENTRY_ENUM_WECHAT_PORTALTYPE] then
                return nil
            else
                serverEntry = formatWechatEntry(entryTable)
            end
        else 
            -- to be determined
        end

        return serverEntry
    else
        return nil
    end
end

function logoutUser(ip,mac)
    local data = {key = ip.."_"..mac}
    local authEntry = getAuthentry(data)

    if authEntry and USERSTATUS_AUTHED == tonumber(authEntry.status) then
        if 1 == tonumber(authEntry.remindflag) then
            if not authEntry.mac or "00:00:00:00:00:00" == authEntry.mac then
                ipset_command = "del "..RULE_REMIND_IP..authEntry.ip.." -exist \n"
            elseif not authEntry.ip or "0.0.0.0" == authEntry.ip then
                ipset_command = "del "..RULE_REMIND_MAC..authEntry.mac.." -exist \n"
            else
                ipset_command = "del "..RULE_REMIND_IPMAC..authEntry.ip..","..authEntry.mac.." -exist \n"
            end 
			
            res  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
            if res ~= "OK" then
                ngx.log(ngx.ERR, "ngx_sendMsg failed:", res)               
            end
        end

        --SEND IPSET MSG--
        local ipset_command,res_out,res_in
        if not authEntry.mac or "00:00:00:00:00:00" == authEntry.mac then
            ipset_command = "del "..RULE_KNOWN_IP..authEntry.ip.." -exist \n"
        elseif not authEntry.ip or "0.0.0.0" == authEntry.ip then
            ipset_command = "del "..RULE_KNOWN_MAC..authEntry.mac.." -exist \n"
        else
            ipset_command = "del "..RULE_KNOWN_IPMAC..authEntry.ip..","..authEntry.mac.." -exist \n"
        end 
        
        res_out = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
        if res_out ~= "OK" then
            ngx.log(ngx.ERR, "ngx_sendMsg failed:", res_out)
        end
        if not authEntry.mac or "00:00:00:00:00:00" == authEntry.mac then
            ipset_command = "del "..RULE_INCOM_KNOWN_IP..authEntry.ip.." -exist \n"
        elseif not authEntry.ip or "0.0.0.0" == authEntry.ip then
            ipset_command = "del "..RULE_INCOM_KNOWN_MAC..authEntry.mac.." -exist \n"
        else
            ipset_command = "del "..RULE_INCOM_KNOWN_IPMAC..authEntry.ip..","..authEntry.mac.." -exist \n"
        end
		
        res_in  = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
        if res_in ~= "OK" then
            ngx.log(ngx.ERR, "ngx_sendMsg failed:", res_in)
        end  
        --DEL AUTH ENTRY--  
        if res_out == "OK" and res_in == "OK" then              
            delAuthentry(authEntry.ip.."_"..authEntry.mac)
            data = {key = authEntry.username} 
            local curuserEntry = getCuruserEntry(data)

            if curuserEntry and tonumber(curuserEntry.curUser) > 0 then
                curuserEntry.curUser = curuserEntry.curUser-1
                if tonumber(curuserEntry.curUser) == 0 then
                    delCuruserEntry(curuserEntry.userName)
                else
                    setCuruserEntry(curuserEntry)
                end
            end
            
            if 0 ~= authEntry.outdata or authEntry.indata ~= 0 then
                ipset_command = "-D "..IPSET_LIMIT.." "..ip..","..authEntry.outdata..","..authEntry.indata.." -exist \n"
				
                msg_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if msg_res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_res)
                    return false
                end

                ipset_command = "-D "..IPSET_LIMIT_IP.." "..ip.." -exist \n"
				
                msg_res = ngx.sendMsg(WIFIDOG_IPSETMSG_KEY, WIFIDOG_IPSET_OPTION, ipset_command)
                if msg_res ~= "OK" then
                    ngx.log(ngx.ERR, "ngx_sendMsg failed:", msg_res)
                    return false
                end
            end

            -- sfe flush
            sfe_flush()

            return ture
        end
    else
        return false
    end
end

function cleanItems()
    local authListDict = ngx.shared.authListDict
    local authlistKeys = authListDict:get_keys(0)
    
    if authlistKeys then
        for index,item in pairs(authlistKeys) do
            data = {key = item}
            local authEntry = getAuthentry(data)
            logoutUser(authEntry.ip, authEntry.mac)
        end
    end
end

--[[
function addAuthList()
    local quit = 0

    for i=1,255 do
        for j=1,255 do
            for k=1,255 do
                local ip = "172."..i.."."..j.."."..k
                local data = string.format("%s,%s,%s,%d,%s,%s,%s,%s,%d,%d,%d,%d,%s,%d,%d",
                                                "01234567890123456",
                                                "eth0",
                                                "111.111.111.111",
                                                2060,
                                                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
                                                "111.111.111.111",
                                                "00-11-22-33-44-55",
                                                decodeURI("www.baidu.com"),
                                                os.time(),
                                                os.time()+3600,
                                                0,
                                                0,
                                                "web",
                                                9,
                                                0)
                local item = {key = ip.."_00-11-22-33-44-55", value = data}

                local ok,err = addAuthentry(item)
                if not ok then
                    ngx.log(ngx.ERR, "i is ",i," j is ", j, " k is ", k)
                    quit = 1
                    break
                end
            end
            if quit == 1 then
                break
            end
        end
        if quit == 1 then
            break
        end
    end
end

function addCurUserList()
    for i=0,65535 do
        local user = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456"..i
        local curUserString = string.format("%s,%d", user, 1)
        local newItem = {key = user, value = curUserString}
        
        local ok,err = addCuruserEntry(newItem)

        if not ok then
            ngx.log(ngx.ERR, "i is ",i)
            break
        end
    end
end

function addUserCfgList()

    local userCfgDict = ngx.shared.userCfgDict
    for i=0,2048 do
        local userName = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456"..i
        local serverString = string.format("%s,%s,%s,%d,%s,%d,%d,%d,%s,%s,%s,%s,%s,%s,%d",
                                                "web",
                                                userName,
                                                userName,
                                                os.time()+3600,
                                                "2016-12-12",
                                                8192,
                                                1000,
                                                1000,
                                                "none",
                                                "00-11-22-33-44-55",
                                                "01234567890123456789012345678901234567890123456789",
                                                "01234567890123456789012345678901234567890123456789",
                                                "01234567890123456789012345678901234567890123456789",
                                                "on",
                                                0)
            --ngx.log(ngx.ERR, "update server auth----{{{{", serverString)
        local ok,err = userCfgDict:safe_set(userName, serverString)
        if not ok then
            ngx.log(ngx.ERR, "i is ",i)
            break
        end

    end
end

function addIOSClientList()
    local quit = 0
    for i=1,255 do
        for j=1,255 do
            for k=1,255 do
                local ip = "172."..i.."."..j.."."..k    
                local data = string.format("%s,%d",
                                                ip,
                                                os.time()+4600)
                local item = {key=ip, value = data}

                local ok,err = addIOSClientEntry(item)
                if not ok then
                    ngx.log(ngx.ERR, "i is ",i," j is ", j, " k is ", k)
                    quit = 1
                    break
                end
            end
            if quit == 1 then
                break
            end
        end
        if quit == 1 then
            break
        end        
    end
end
]]--
