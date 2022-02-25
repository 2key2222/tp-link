local dbg = require "luci.tools.debug"
local sys = require "luci.sys"
local uci = require "luci.model.uci"
local uci_r = uci.cursor()

module("pppox_functions", package.seeall)

local user_config = "user-secrets"
local pppox_l2tptype = "l2tp"
local pppox_pptptype = "pptp"
local pppox_pppoetype = "pppoe"
local pppox_path = "/tmp/pppox/"
local pppox_l2tp_path = pppox_path .. "l2tp/"
local pppox_pptp_path = pppox_path .. "pptp/"
local pppox_pppoe_path= pppox_path .. "pppoe/"
local pppox_if_config = "if-config"
local pppox_user_secrets = "user-secrets"
local pppox_profile = "-profile"
local pppox_profilex = "-profilex"

local initl2tp = false
local initpptp = false
local initpppoe = false

local function to_ascii(str)
	local len = string.len(str)
	local res = ""
	
	for i = 1, len do
		res = res .. string.format("%X", string.byte(str, i, i))
	end
	return res
end

local function  _echo_info(path, username, password, localip, ippool, ms_dns, maxsessions, netmode, remotesubnet)
	local password1=string.gsub(password, "\\", "\\\\")
	password1=string.gsub(password1, "\'", "\\\'")
	local username1=string.gsub(username, "\\", "\\\\")
	username1=string.gsub(username1, "\'", "\\\'")
	
	local username2=to_ascii(username)
	
	local filepath = path .. pppox_user_secrets
	local ff = io.open(filepath, "a")
	ff:write("'" .. username1 .. "' * '" .. password1 .. "' *\n")
	ff:close()
	
	filepath = path .. username2 .. pppox_profile
	ff = io.open(filepath, "a")
	ff:write(localip .. ":\nippool " .. ippool .. "\nms-dns " .. ms_dns .. "\n")
	ff:close()
	
	filepath = path .. username2 .. pppox_profilex
	ff = io.open(filepath, "a")
	ff:write("maxsessions " ..  maxsessions .. "\n")
	ff:close()
	
	filepath = path .. pppox_if_config
	ff = io.open(filepath, "a")
	ff:write("config if " ..  username2 .. "\n\toption netmode " .. netmode .. "\n\toption remotesubnet " .. remotesubnet .. "\n")
	ff:close()
	return true
end


local function _load_one_user(section)
	if section.type == pppox_l2tptype and initl2tp then
		_echo_info(pppox_l2tp_path, section.username, section.password, section.localip, 
			section.ippool, section.ms_dns, section.maxsessions, section.netmode, section.remotesubnet)
	elseif section.type == pppox_pptptype and initpptp then
		_echo_info(pppox_pptp_path, section.username, section.password, section.localip, 
			section.ippool, section.ms_dns, section.maxsessions, section.netmode, section.remotesubnet)
	--[[
	elseif	section.type == pppox_pppoetype and initpppoe then
		_echo_info(pppox_pppoe_path, section.username, section.password, section.localip, 
			section.ippool, section.ms_dns, section.maxsessions, section.netmode, section.remotesubnet)
	]]--
	elseif	section.type == "auto"  then
		if initl2tp then
			_echo_info(pppox_l2tp_path, section.username, section.password, section.localip, 
			section.ippool, section.ms_dns, section.maxsessions, section.netmode, section.remotesubnet)
		end
		if initpptp then
			_echo_info(pppox_pptp_path, section.username, section.password, section.localip, 
			section.ippool, section.ms_dns, section.maxsessions, section.netmode, section.remotesubnet)
		end
		--[[ 
		if initpppoe then
			_echo_info(pppox_pppoe_path, section.username, section.password, section.localip, 
			section.ippool, section.ms_dns, section.maxsessions, section.netmode, section.remotesubnet)
		end
		]]--
	end
	
	return true
end

function pppox_load_user()
	uci_r:foreach(user_config, "user", function(section)
			_load_one_user(section)
            return true
        end
        )
	return true
end

if arg[1] ~= "0" then
	initl2tp = true
end

if arg[2] ~= "0" then
	initpptp = true
end

--[[
if arg[3] ~= "0" then
	initpppoe = true
end
]]--

pppox_load_user()

