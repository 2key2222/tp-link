

local os   = require "os"
local io   = require "io"
local fs   = require "nixio.fs"
local util = require "luci.util"

local type  = type
local pairs = pairs
local error = error
local table = table

local ipkg = "opkg --force-removal-of-dependent-packages --force-overwrite --nocase"
local icfg = "/etc/opkg.conf"
module "luci.model.ipkg"
local function _action(cmd, ...)
	local pkg = ""
	for k, v in pairs({...}) do
		pkg = pkg .. " '" .. v:gsub("'", "") .. "'"
	end

	local c = "%s %s %s >/tmp/opkg.stdout 2>/tmp/opkg.stderr" %{ ipkg, cmd, pkg }
	local r = os.execute(c)
	local e = fs.readfile("/tmp/opkg.stderr")
	local o = fs.readfile("/tmp/opkg.stdout")

	fs.unlink("/tmp/opkg.stderr")
	fs.unlink("/tmp/opkg.stdout")

	return r, o or "", e or ""
end
local function _parselist(rawdata)
	if type(rawdata) ~= "function" then
		error("OPKG: Invalid rawdata given")
	end

	local data = {}
	local c = {}
	local l = nil

	for line in rawdata do
		if line:sub(1, 1) ~= " " then
			local key, val = line:match("(.-): ?(.*)%s*")

			if key and val then
				if key == "Package" then
					c = {Package = val}
					data[val] = c
				elseif key == "Status" then
					c.Status = {}
					for j in val:gmatch("([^ ]+)") do
						c.Status[j] = true
					end
				else
					c[key] = val
				end
				l = key
			end
		else
			c[l] = c[l] .. "\n" .. line
		end
	end

	return data
end
local function _lookup(act, pkg)
	local cmd = ipkg .. " " .. act
	if pkg then
		cmd = cmd .. " '" .. pkg:gsub("'", "") .. "'"
	end
	local tmpfile = os.tmpname()
	os.execute(cmd .. (" >%s 2>/dev/null" % tmpfile))

	local data = _parselist(io.lines(tmpfile))
	os.remove(tmpfile)
	return data
end
function info(pkg)
	return _lookup("info", pkg)
end
function status(pkg)
	return _lookup("status", pkg)
end
function install(...)
	return _action("install", ...)
end
function installed(pkg)
	local p = status(pkg)[pkg]
	return (p and p.Status and p.Status.installed)
end
function remove(...)
	return _action("remove", ...)
end
function update()
	return _action("update")
end
function upgrade()
	return _action("upgrade")
end
function _list(action, pat, cb)
	local fd = io.popen(ipkg .. " " .. action ..
		(pat and (" '%s'" % pat:gsub("'", "")) or ""))

	if fd then
		local name, version, desc
		while true do
			local line = fd:read("*l")
			if not line then break end

			name, version, desc = line:match("^(.-) %- (.-) %- (.+)")

			if not name then
				name, version = line:match("^(.-) %- (.+)")
				desc = ""
			end

			cb(name, version, desc)

			name    = nil
			version = nil
			desc    = nil
		end

		fd:close()
	end
end
function list_all(pat, cb)
	_list("list", pat, cb)
end
function list_installed(pat, cb)
	_list("list_installed", pat, cb)
end
function find(pat, cb)
	_list("find", pat, cb)
end
function overlay_root()
	local od = "/"
	local fd = io.open(icfg, "r")

	if fd then
		local ln

		repeat
			ln = fd:read("*l")
			if ln and ln:match("^%s*option%s+overlay_root%s+") then
				od = ln:match("^%s*option%s+overlay_root%s+(%S+)")

				local s = fs.stat(od)
				if not s or s.type ~= "dir" then
					od = "/"
				end

				break
			end
		until not ln

		fd:close()
	end

	return od
end
