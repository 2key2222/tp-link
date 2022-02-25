

local io = require "io"
local math = require "math"
local table = require "table"
local debug = require "debug"
local ldebug = require "luci.debug"
local string = require "string"
local coroutine = require "coroutine"
local tparser = require "luci.template.parser"

local getmetatable, setmetatable = getmetatable, setmetatable
local rawget, rawset, unpack = rawget, rawset, unpack
local tostring, type, assert = tostring, type, assert
local ipairs, pairs, next, loadstring = ipairs, pairs, next, loadstring
local require, pcall, xpcall = require, pcall, xpcall
local collectgarbage, get_memory_limit = collectgarbage, get_memory_limit
module "luci.util"
getmetatable("").__mod = function(a, b)
	if not b then
		return a
	elseif type(b) == "table" then
		for k, _ in pairs(b) do if type(b[k]) == "userdata" then b[k] = tostring(b[k]) end end
		return a:format(unpack(b))
	else
		if type(b) == "userdata" then b = tostring(b) end
		return a:format(b)
	end
end
local function _instantiate(class, ...)
	local inst = setmetatable({}, {__index = class})

	if inst.__init__ then
		inst:__init__(...)
	end

	return inst
end
function class(base)
	return setmetatable({}, {
		__call  = _instantiate,
		__index = base
	})
end
function instanceof(object, class)
	local meta = getmetatable(object)
	while meta and meta.__index do
		if meta.__index == class then
			return true
		end
		meta = getmetatable(meta.__index)
	end
	return false
end

local tl_meta = {
	__mode = "k",

	__index = function(self, key)
		local t = rawget(self, coxpt[coroutine.running()]
		 or coroutine.running() or 0)
		return t and t[key]
	end,

	__newindex = function(self, key, value)
		local c = coxpt[coroutine.running()] or coroutine.running() or 0
		if not rawget(self, c) then
			rawset(self, c, { [key] = value })
		else
			rawget(self, c)[key] = value
		end
	end
}
function threadlocal(tbl)
	return setmetatable(tbl or {}, tl_meta)
end
function perror(obj)
	return io.stderr:write(tostring(obj) .. "\n")
end
function dumptable(t, maxdepth, i, seen)
	i = i or 0
	seen = seen or setmetatable({}, {__mode="k"})

	for k,v in pairs(t) do
		perror(string.rep("\t", i) .. tostring(k) .. "\t" .. tostring(v))
		if type(v) == "table" and (not maxdepth or i < maxdepth) then
			if not seen[v] then
				seen[v] = true
				dumptable(v, maxdepth, i+1, seen)
			else
				perror(string.rep("\t", i) .. "*** RECURSION ***")
			end
		end
	end
end
function pcdata(value)
	return value and tparser.pcdata(tostring(value))
end
function striptags(value)
	return value and tparser.striptags(tostring(value))
end
function split(str, pat, max, regex)
	pat = pat or "\n"
	max = max or #str

	local t = {}
	local c = 1

	if #str == 0 then
		return {""}
	end

	if #pat == 0 then
		return nil
	end

	if max == 0 then
		return str
	end

	repeat
		local s, e = str:find(pat, c, not regex)
		max = max - 1
		if s and max < 0 then
			t[#t+1] = str:sub(c)
		else
			t[#t+1] = str:sub(c, s and s - 1)
		end
		c = e and e + 1 or #str + 1
	until not s or max < 0

	return t
end
function trim(str)
	return (str:gsub("^%s*(.-)%s*$", "%1"))
end
function cmatch(str, pat)
	local count = 0
	for _ in str:gmatch(pat) do count = count + 1 end
	return count
end
function imatch(v)
	if type(v) == "table" then
		local k = nil
		return function()
			k = next(v, k)
			return v[k]
		end

	elseif type(v) == "number" or type(v) == "boolean" then
		local x = true
		return function()
			if x then
				x = false
				return tostring(v)
			end
		end

	elseif type(v) == "userdata" or type(v) == "string" then
		return tostring(v):gmatch("%S+")
	end

	return function() end
end
function parse_units(ustr)

	local val = 0
	local map = {
		y   = 60 * 60 * 24 * 366,
		m   = 60 * 60 * 24 * 31,
		w   = 60 * 60 * 24 * 7,
		d   = 60 * 60 * 24,
		h   = 60 * 60,
		min = 60,
		kb  = 1024,
		mb  = 1024 * 1024,
		gb  = 1024 * 1024 * 1024,
		kib = 1000,
		mib = 1000 * 1000,
		gib = 1000 * 1000 * 1000
	}
	for spec in ustr:lower():gmatch("[0-9%.]+[a-zA-Z]*") do

		local num = spec:gsub("[^0-9%.]+$","")
		local spn = spec:gsub("^[0-9%.]+", "")

		if map[spn] or map[spn:sub(1,1)] then
			val = val + num * ( map[spn] or map[spn:sub(1,1)] )
		else
			val = val + num
		end
	end


	return val
end
string.pcdata      = pcdata
string.striptags   = striptags
string.split       = split
string.trim        = trim
string.cmatch      = cmatch
string.parse_units = parse_units
function append(src, ...)
	for i, a in ipairs({...}) do
		if type(a) == "table" then
			for j, v in ipairs(a) do
				src[#src+1] = v
			end
		else
			src[#src+1] = a
		end
	end
	return src
end
function combine(...)
	return append({}, ...)
end
function contains(table, value)
	for k, v in pairs(table) do
		if value == v then
			return k
		end
	end
	return false
end
function update(t, updates)
	for k, v in pairs(updates) do
		t[k] = v
	end
end
function update_prefix(t, updates, prefix)
    for k, v in pairs(updates) do
        t[prefix .. k] = v
    end
end
function updateonly(t, updates, keys)
    for _, k in ipairs(keys) do
        t[k] = updates[k]
    end
end
function keys(t)
	local keys = { }
	if t then
		for k, _ in kspairs(t) do
			keys[#keys+1] = k
		end
	end
	return keys
end
function clone(object, deep)
	local copy = {}

	for k, v in pairs(object) do
		if deep and type(v) == "table" then
			v = clone(v, deep)
		end
		copy[k] = v
	end

	return setmetatable(copy, getmetatable(object))
end
function dtable()
        return setmetatable({}, { __index =
                function(tbl, key)
                        return rawget(tbl, key)
                         or rawget(rawset(tbl, key, dtable()), key)
                end
        })
end
function _serialize_table(t, seen)
	assert(not seen[t], "Recursion detected.")
	seen[t] = true

	local data  = ""
	local idata = ""
	local ilen  = 0

	for k, v in pairs(t) do
		if type(k) ~= "number" or k < 1 or math.floor(k) ~= k or ( k - #t ) > 3 then
			k = serialize_data(k, seen)
			v = serialize_data(v, seen)
			data = data .. ( #data > 0 and ", " or "" ) ..
				'[' .. k .. '] = ' .. v
		elseif k > ilen then
			ilen = k
		end
	end

	for i = 1, ilen do
		local v = serialize_data(t[i], seen)
		idata = idata .. ( #idata > 0 and ", " or "" ) .. v
	end

	return idata .. ( #data > 0 and #idata > 0 and ", " or "" ) .. data
end
function serialize_data(val, seen)
	seen = seen or setmetatable({}, {__mode="k"})

	if val == nil then
		return "nil"
	elseif type(val) == "number" then
		return val
	elseif type(val) == "string" then
		return "%q" % val
	elseif type(val) == "boolean" then
		return val and "true" or "false"
	elseif type(val) == "function" then
		return "loadstring(%q)" % get_bytecode(val)
	elseif type(val) == "table" then
		return "{ " .. _serialize_table(val, seen) .. " }"
	else
		return '"[unhandled data type:' .. type(val) .. ']"'
	end
end
function restore_data(str)
	return loadstring("return " .. str)()
end
function get_bytecode(val)
	local code

	if type(val) == "function" then
		code = string.dump(val)
	else
		code = string.dump( loadstring( "return " .. serialize_data(val) ) )
	end

	return code -- and strip_bytecode(code)
end
function strip_bytecode(code)
	local version, format, endian, int, size, ins, num, lnum = code:byte(5, 12)
	local subint
	if endian == 1 then
		subint = function(code, i, l)
			local val = 0
			for n = l, 1, -1 do
				val = val * 256 + code:byte(i + n - 1)
			end
			return val, i + l
		end
	else
		subint = function(code, i, l)
			local val = 0
			for n = 1, l, 1 do
				val = val * 256 + code:byte(i + n - 1)
			end
			return val, i + l
		end
	end

	local function strip_function(code)
		local count, offset = subint(code, 1, size)
		local stripped = { string.rep("\0", size) }
		local dirty = offset + count
		offset = offset + count + int * 2 + 4
		offset = offset + int + subint(code, offset, int) * ins
		count, offset = subint(code, offset, int)
		for n = 1, count do
			local t
			t, offset = subint(code, offset, 1)
			if t == 1 then
				offset = offset + 1
			elseif t == 4 then
				offset = offset + size + subint(code, offset, size)
			elseif t == 3 then
				offset = offset + num
			elseif t == 254 or t == 9 then
				offset = offset + lnum
			end
		end
		count, offset = subint(code, offset, int)
		stripped[#stripped+1] = code:sub(dirty, offset - 1)
		for n = 1, count do
			local proto, off = strip_function(code:sub(offset, -1))
			stripped[#stripped+1] = proto
			offset = offset + off - 1
		end
		offset = offset + subint(code, offset, int) * int + int
		count, offset = subint(code, offset, int)
		for n = 1, count do
			offset = offset + subint(code, offset, size) + size + int * 2
		end
		count, offset = subint(code, offset, int)
		for n = 1, count do
			offset = offset + subint(code, offset, size) + size
		end
		stripped[#stripped+1] = string.rep("\0", int * 3)
		return table.concat(stripped), offset
	end

	return code:sub(1,12) .. strip_function(code:sub(13,-1))
end

function _sortiter( t, f )
	local keys = { }

	local k, v
	for k, v in pairs(t) do
		keys[#keys+1] = k
	end

	local _pos = 0

	table.sort( keys, f )

	return function()
		_pos = _pos + 1
		if _pos <= #keys then
			return keys[_pos], t[keys[_pos]], _pos
		end
	end
end
function spairs(t,f)
	return _sortiter( t, f )
end
function kspairs(t)
	return _sortiter( t )
end
function vspairs(t)
	return _sortiter( t, function (a,b) return t[a] < t[b] end )
end
function bigendian()
	return string.byte(string.dump(function() end), 7) == 0
end
function exec(command)
	local pp   = io.popen(command)
	local data = pp:read("*a")
	pp:close()

	return data
end
function execi(command)
	local pp = io.popen(command)

	return pp and function()
		local line = pp:read()

		if not line then
			pp:close()
		end

		return line
	end
end
function execl(command)
	local pp   = io.popen(command)
	local line = ""
	local data = {}

	while true do
		line = pp:read()
		if (line == nil) then break end
		data[#data+1] = line
	end
	pp:close()

	return data
end
function libpath()
	return require "nixio.fs".dirname(ldebug.__file__)
end

local performResume, handleReturnValue
local oldpcall, oldxpcall = pcall, xpcall
coxpt = {}
setmetatable(coxpt, {__mode = "kv"})
local function copcall_id(trace, ...)
  return ...
end
function coxpcall(f, err, ...)
	local res, co = oldpcall(coroutine.create, f)
	if not res then
		local params = {...}
		local newf = function() return f(unpack(params)) end
		co = coroutine.create(newf)
	end
	local c = coroutine.running()
	coxpt[co] = coxpt[c] or c or 0

	return performResume(err, co, ...)
end
function copcall(f, ...)
	return coxpcall(f, copcall_id, ...)
end
function handleReturnValue(err, co, status, ...)
	if not status then
		return false, err(debug.traceback(co, (...)), ...)
	end

	if coroutine.status(co) ~= 'suspended' then
		return true, ...
	end

	return performResume(err, co, coroutine.yield(...))
end
function performResume(err, co, ...)
	return handleReturnValue(err, co, coroutine.resume(co, ...))
end
