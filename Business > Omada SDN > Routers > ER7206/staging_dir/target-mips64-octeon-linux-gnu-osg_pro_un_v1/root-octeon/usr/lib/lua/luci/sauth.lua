module("luci.sauth", package.seeall)
require("luci.util")
require("luci.sys")
require("luci.config")
local nixio = require "nixio", require "nixio.util"
local fs = require "nixio.fs"


luci.config.sauth = luci.config.sauth or {}
sessionpath = luci.config.sauth.sessionpath
sessiontime = tonumber(luci.config.sauth.sessiontime) or 15 * 60
maxclients = tonumber(luci.config.sauth.maxclients) or 1
sessionlock = "/var/run/luci-session.lock"
function prepare()
	fs.mkdir(sessionpath, 700)
	if not sane() then
		error("Security Exception: Session path is not sane!")
	end
end

local _lock

local function lock(w)
    _lock = nixio.open(sessionlock, "w", 600)
    _lock:flock(w and "ex" or "sh")
end

local function unlock()
    _lock:close()
    _lock = nil
end

local function _read(id)
	local blob = fs.readfile(sessionpath .. "/" .. id)
	return blob
end

local function _write(id, data)
	local f = nixio.open(sessionpath .. "/" .. id, "w", 600)
	f:writeall(data)
	f:close()
end

local function _checkid(id)
	return not not (id and #id == 32 and id:match("^[a-fA-F0-9]+$"))
end
function write(id, data)
	if not sane() then
		prepare()
	end

	assert(_checkid(id), "Security Exception: Session ID is invalid!")
	assert(type(data) == "table", "Security Exception: Session data invalid!")

	data.atime = luci.sys.uptime()

	_write(id, luci.util.get_bytecode(data))
end
function read(id)
	if not id or #id == 0 then
		return nil
	end

	assert(_checkid(id), "Security Exception: Session ID is invalid!")

	if not sane(sessionpath .. "/" .. id) then
		return nil
	end

	local blob = _read(id)
	local func = loadstring(blob)
	setfenv(func, {})

	local sess = func()
	assert(type(sess) == "table", "Session data invalid!")

	if sess.atime and sess.atime + sessiontime < luci.sys.uptime() then
		kill(id)
		return nil
	end

    return sess
end
function touch(id, sess)
	write(id, sess)
end
function sane(file)
    local mode = fs.stat(file or sessionpath, "modestr")
	return luci.sys.process.info("uid")
			== fs.stat(file or sessionpath, "uid")
        and (mode == (file and "rw-------" or "rwx------")
        or mode == (file and "rw-------" or "rwx--S---"))
end
function kill(id)
	assert(_checkid(id), "Security Exception: Session ID is invalid!")
	fs.unlink(sessionpath .. "/" .. id)
end
function reap()
	if sane() then
		local id
		for id in nixio.fs.dir(sessionpath) do
			if _checkid(id) then
				read(id)
			end
		end
	end
end
function limit(addr, remote)
    if sane() then
        local sid
        local sdat
        local clients = 0
        for id in nixio.fs.dir(sessionpath) do
            if _checkid(id) then
                sid = id
                sdat = read(id)
                if sdat then
                    clients = clients + 1
                    if sdat.remote == remote then
                        if sdat.addr == addr then
                            return true, sid, sdat
                        end
                    end
                end
            end
        end

        if clients < maxclients then
            return true
        else
            return false, sid, sdat
        end
    else
        return true
    end
end
