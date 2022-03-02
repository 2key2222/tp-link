--[[
Copyright(c) 2018-2026 Shenzhen TP-Link Technologies Co.Ltd.

File    :  service.lua
Details :  Used for special service of TP
Author  :  Zeng Wei <zengwei@tp-link.com.cn>
Version :  1.0.0
Date    :  18 May, 2018
]]--

module("luci.service", package.seeall)

-- local sys		= require "luci.sys"
local luarsa	= require "luarsa"
local fs		= require "luci.fs"
-- local ltn12 	= require "luci.ltn12"
local dbg 		= require "luci.tools.debug"
local nixio 	= require "nixio"
local luaaes = require "luaaes"

--- check if http data need encrypt according to noencrypt_list.
-- @param minnum    minimal number in random
-- @param reqform   maximum number in random
-- @param reqform   base number for seed
function gen_random(minnum, maxnum, basenum)
    local math   = require "math"
    local seed = 0

    if not minnum then
        minnum = 100000
    end

    if not minnum then
        maxnum = 999999
    end

    if not basenum then
        basenum = 10000000
    end

    local file = io.open("/dev/urandom", "rb")

    if file then
        local data = file:read(4)
        file:close()
        for i = 1, 4 do
            seed = seed * 256 + data:byte(i)
        end
    else
        seed = os.time()
    end

    math.randomseed(seed % basenum)
    return math.random(minnum, maxnum)
end

--process http data auth which only support one client a time
rsakeyfile = "/tmp/rsakey"

-- aeskeyfile = "/tmp/aeskey"
-- aeskeylock = "/var/run/luci-aeskey.lock"
-- aeslock = nil

seqnumfile = "/tmp/luci-seqnum"
seqnumlock = "/var/run/luci-seqnum.lock"
seqlock = nil

function lock(lockname, w)
    -- if lockname == "aes" then
    --     aeslock = nixio.open(aeskeylock, "w", 600)
    --     aeslock:flock(w and "ex" or "sh")
    -- elseif lockname == "seq" then
    --     seqlock = nixio.open(seqnumlock, "w", 600)
    --     seqlock:flock(w and "ex" or "sh")
    -- end
    if lockname == "seq" then
        seqlock = nixio.open(seqnumlock, "w", 600)
        seqlock:flock(w and "ex" or "sh")
    end
end

function unlock(lockname)
    -- if lockname == "aes" then
    --     aeslock:close()
    --     aeslock = nil
    -- elseif lockname == "seq" then
    --     seqlock:close()
    --     seqlock = nil
    -- end
    if lockname == "seq" then
        seqlock:close()
        seqlock = nil
    end
end

--get the aes key from file for http data encrypt/decrypt
function read_rsakey()
    local n = nil
    local e = nil
    local d = nil
    local rsakey = nil
    local content = fs.readfile(rsakeyfile)
    if content then
        n, e, d = string.match(content, "n=(.-)\ne=(.-)\nd=(.-)\n")
    end

    if n and e and d then
        rsakey = {n = n, e = e, d = d}
    else
        n, e, d = luarsa.gen_keys(512)
        if n and e and d then
            fs.writefile(rsakeyfile, "n=%s\ne=%s\nd=%s\n" % {n, e, d})
            rsakey = {n = n, e = e, d = d}
        end
    end
    return rsakey
end

function save_seqnum(seqnum)
	local stat

    lock("seq", true)
    stat = fs.writefile(seqnumfile, seqnum)
    unlock("seq")

    if not stat then
        return false
    end

    return true
end

function remove_seqnum()
    fs.unlink(seqnumfile)
end

function read_seqnum()
    lock("seq")
    local seqnum = fs.readfile(seqnumfile)
    unlock("seq")    

    if not seqnum then
        return nil
    end

    return tonumber(seqnum)
end

function gen_seqnum()
    local random = gen_random(0, 1000000000, 1000000000)

    if not save_seqnum(random) then
        return nil
    end

    return random
end

--check the aes key for http data encrypt/decrypt
function check_aeskey(aeskey)
    if not aeskey or type(aeskey) ~= "table" then
        return false
    end

    if not aeskey.key or not string.match(aeskey.key, "^%w+$") then
        return false
    end

    --only number or charactor allowed
    if not aeskey.iv or not string.match(aeskey.iv, "^%w+$") then
        return false
    end

    return true
end

--[[
--save the aes key for http data encrypt/decrypt
function save_aeskey(aeskey)
    local data = {}

    if not aeskey or not aeskey.key then
        return false
    end

    data.key = aeskey.key

    if aeskey.iv then
        data.iv = aeskey.iv
    end

    lock("aes", true)
    local stat = fs.writefile(aeskeyfile, luci.util.get_bytecode(data))
    unlock("aes")

    if not stat then
    	return false
    end

    return true
end

--remove the aes key for http data encrypt/decrypt
function remove_aeskey()
    fs.unlink(aeskeyfile)
end

--get the aes key from file for http data encrypt/decrypt
function read_aeskey()
    lock("aes")
    local blob = fs.readfile(aeskeyfile)
    unlock("aes")

    if not blob then
    	return nil
    end

    local func = loadstring(blob)
    if not func then
        return nil
    end
    setfenv(func, {})

    local aes_key = func()
    if type(aes_key) ~= "table" then
        dbg("read aeskey data from file invalid!")
        return nil
    end

    return aes_key
end
--]]

noencrypt_list = {
	{path="admin.system", form="envar"},
	{path="login", form="check_factory_default"},
	{path="login", form="auth"},
	{path="login", form="keys"},
	{path="login", form="mini_login"},
	{path="admin.log_export", form="save_log"},
	{path="admin.cloud", form="firmware"},
	{path="admin.cloud", form="mini_firmware"},
	{path="admin.device", form="mini_device_list"},
	{path="blocking", form="vercode"}
}

renew_aeskey_list = {
	{path="login", form="login"}
}

--- check if http data need encrypt according to noencrypt_list.
-- @param reqpath	http request path from url as admin.ddns
-- @param reqform	http request form from url
function data_need_encrypt(reqpath, reqform)
	if not reqform or not reqform then
		return true
	end

	for i, t in ipairs(noencrypt_list) do
		if reqpath == t.path and reqform == t.form then
			return false
		end
	end

	return true
end

--- check if need to get aeskey from payload according to renew_aeskey_list.
-- @param reqpath	http request path from url
-- @param reqform	http request form from url
function data_renew_aeskey(reqpath, reqform)
	if not reqform or not reqform then
		return false
	end

	for i, t in ipairs(renew_aeskey_list) do
		if reqpath == t.path and reqform == t.form then
			return true
		end
	end

	return false
end

--rsa decode
-- @param str	input str
-- @param n		rsa key n
-- @param e		rsa key e
-- @param d		rsa key d
function rsa_dec(str, n, e, d)
	if not str then
		return nil
	end

	if not n or not e or not d then
		return nil
	end

	local str_tollen = #str
	local dec_len = #n
	local dec_tollen = 0
	local result = nil
	local tmp = nil
	if str_tollen <= 0 or dec_len <= 0 or (str_tollen % dec_len) ~= 0  then
		return nil
	end

	while dec_tollen < str_tollen do
		tmp = luarsa.decrypt(str:sub(dec_tollen + 1, dec_tollen + dec_len), n, e, d)
		if not tmp then
			return nil
		end

		if result then
			result = result .. tmp
		else
			result = tmp
		end

		dec_tollen = dec_tollen + dec_len
	end
	
	return result
end

--analyze the signature data and return
-- @param sig		http request signature
function analyze_signature(sig, hasaeskey)
	if not sig then
		return false
	end

	local rsakey = read_rsakey()
	if not rsakey then
		return false
	end

	local str = rsa_dec(sig, rsakey.n, rsakey.e, rsakey.d)
	if not str then
		return false
	end

	local aeskey, aesiv, hash, seq
	local data
	if hasaeskey then
		aeskey, aesiv, hash, seq = string.match(str, "k=(.-)&i=(.-)&h=(.-)&s=(.+)")
		if not aeskey or not aesiv or not hash or not seq then
			return false
		end
		data = {key=aeskey, iv=aesiv, hash=hash, seq=seq}
	else
		hash, seq = string.match(str, "h=(.-)&s=(.+)")
		if not hash or not seq then
			return false
		end
		data = {hash=hash, seq=seq}
	end

	return true, data
end

--check the signature hash code by username and password not encrypted
-- @param hash		hash code from signature
function check_hash(hash)
	local accmnt = require "luci.model.accountmgnt"

	if not hash then
		return false
	end

	local password_hash = accmnt.get_password_hash()

	-- check hash value
	if password_hash ~= hash then
		return false
	end

	return true
end

--check the signature sequence number
-- @param seqnum	sequence number from signature
-- @param datalen	http data len
function check_seqnum(seqnum, datalen, islogin)
	if not seqnum or not datalen then
		return false
	end

	local saved_seqnum = read_seqnum(islogin)
	if not saved_seqnum then
		return false 
	end

	if (seqnum - datalen) ~= saved_seqnum then
		return false
	end

	return true
end

--format the sting from ascii charactor to hex string
function format_strtohexstr(str)
	if not str or #str == 0 then
		return nil
	end

	local data = nil

	for i = 1, #str do
		if data then
			data = string.format("%s%02x", data, string.byte(str, i))
		else
			data = string.format("%02x", string.byte(str, i))
		end
	end

	return data
end

--[[
--- AES encrypt data to iterrator
-- @param data    data to be encrypted
-- @param aeskey  aes key
-- @return        nil on error, or an iterator function. 
function aes_enc_data(data, aeskey)
	if not data then
		return nil
	end

	if not aeskey then
		return nil
	end

	if not check_aeskey(aeskey) then
		return nil
	end

	local key = format_strtohexstr(aeskey.key)
	local iv = format_strtohexstr(aeskey.iv)
	if not key or not iv then
		return nil
	end

	local cmd = "openssl enc -e -aes-128-cbc -K %s -iv %s -nosalt -a -A" % {key, iv}
	local src = sys.ltn12_popen(cmd, data)

	return src
end

--- AES decrypt data to iterrator
-- @param data    data to be decrypted
-- @param aeskey  aes key
-- @return        nil on error, or an iterator function. 
function aes_dec_data(data, aeskey)
	if not data then
		return nil
	end

	if not aeskey then
		return nil
	end

	if not check_aeskey(aeskey) then
		return nil
	end

	local key = format_strtohexstr(aeskey.key)
	local iv = format_strtohexstr(aeskey.iv)
	if not key or not iv then
		return nil
	end

	local cmd = "openssl enc -d -aes-128-cbc -K %s -iv %s -nosalt -a -A" % {key, iv}
	local src = sys.ltn12_popen(cmd, data)

	return src
end


--- AES encrypt data to memory
-- @param data    data to be encrypted
-- @param aeskey  aes key
-- @return        nil on error, or encrypted data. 
function aes_enc_tomem(data, aeskey)
	local src = aes_enc_data(data, aeskey)
	if not src then
		return nil
	end

	local ret_data = nil
	local function snk(chunk)
		if not ret_data then
			ret_data = chunk
		elseif chunk then
			ret_data = ret_data .. chunk
		end
		
		return true
	end

	ltn12.pump.all(src, snk)

	return ret_data
end

--- AES decrypt data to memory
-- @param data    data to be decrypted
-- @param aeskey  aes key
-- @return        nil on error, or decryped data.
function aes_dec_tomem(data, aeskey)
	local src = aes_dec_data(data, aeskey)
	if not src then
		return nil
	end

	local ret_data = nil
	local function snk(chunk)
		if not ret_data then
			ret_data = chunk
		elseif chunk then
			ret_data = ret_data .. chunk
		end

		return true
	end

	ltn12.pump.all(src, snk)

	return ret_data
end
]]--

--- get a file path from random file name by random number and given path
-- @param path    derectory for the file
-- @return        nil on error, or encrypted data. 
function get_filepath(path)
	if not path then
		return nil
	end

	local rannum = gen_random(100000, 999999, 1000000) or os.time()
	if not rannum then
		return nil
	end

	path = path .. "/"

	local filepath = path .. rannum

	while fs.isfile(filepath) do
		rannum = rannum + 1
		filepath = path .. rannum
	end

	return filepath
end

--- AES encrypt data
-- @param data    data to be encrypted
-- @param aeskey  aes key
-- @return        nil on error, or encrypted data. 
function aes_enc_data(data, aeskey)
	if not data then
		dbg.print("no data")
		return nil
	end

	if not aeskey then
		dbg.print("no aeskey")
		return nil
	end

	if not check_aeskey(aeskey) then
		dbg.print("no check_aeskey")
		return nil
	end

	--use file for input/output data when encrypt in aes
	local path = "/tmp/crypto"
	if not fs.isdirectory(path) then
		fs.mkdir(path)
	end

	local filepath = get_filepath(path)
	if not filepath then
		return nil
	end

	if not fs.writefile(filepath, data) then
		fs.unlink(filepath)
		return nil
	end

	local outfile = filepath .. ".enc"
	local ret, _ = luaaes.encryptf(filepath, aeskey.key, aeskey.iv, outfile)  
	if not ret then
		fs.unlink(filepath)
		fs.unlink(outfile)
		return nil
	end

	local src = fs.readfile(outfile)
	fs.unlink(filepath)
	fs.unlink(outfile)
	if not src then
		return nil
	end

--[[
	-- input/output data directly when encrypt in aes
	local ret, src = luaaes.encrypt(data, aeskey.key, aeskey.iv)  
	if not ret then
		return nil
	end
]]--

	src = nixio.bin.b64encode(src)	
	return src
end

--- AES decrypt data to iterrator
-- @param data    data to be decrypted
-- @param aeskey  aes key
-- @return        nil on error, or decrypted data. 
function aes_dec_data(data, aeskey)
	if not data then
		return nil
	end

	if not aeskey then
		return nil
	end

	if not check_aeskey(aeskey) then
		return nil
	end

	local b64data = nixio.bin.b64decode(data)
	if not b64data then
		return nil
	end

	--input/output data directly when decrypt in aes
	local path = "/tmp/crypto"
	if not fs.isdirectory(path) then
		fs.mkdir(path)
	end

	local filepath = get_filepath(path)
	if not filepath then
		return nil
	end

	if not fs.writefile(filepath, b64data) then
		fs.unlink(filepath)
		return nil
	end

	local outfile = filepath .. ".dec"
	local ret, _ = luaaes.decryptf(filepath, aeskey.key, aeskey.iv, outfile)  
	if not ret then
		fs.unlink(filepath)
		fs.unlink(outfile)
		return nil
	end

	local src = fs.readfile(outfile)
	fs.unlink(filepath)
	fs.unlink(outfile)
	if not src then
		return nil
	end

--[[
	-- input/output data directly when decrypt in aes
	local ret, src = luaaes.decrypt(b64data, aeskey.key, aeskey.iv)
	if not ret then
		return nil
	end
]]--

	return src
end

