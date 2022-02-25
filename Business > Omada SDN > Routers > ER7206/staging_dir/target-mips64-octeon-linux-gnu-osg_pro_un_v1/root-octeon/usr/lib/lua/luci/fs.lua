

local io    = require "io"
local os    = require "os"
local ltn12 = require "luci.ltn12"
local fs	= require "nixio.fs"
local nutil = require "nixio.util"

local type  = type
module "luci.fs"
access = fs.access
function glob(...)
	local iter, code, msg = fs.glob(...)
	if iter then
		return nutil.consume(iter)
	else
		return nil, code, msg
	end
end
function isfile(filename)
	return fs.stat(filename, "type") == "reg"
end
function isdirectory(dirname)
	return fs.stat(dirname, "type") == "dir"
end
readfile = fs.readfile
writefile = fs.writefile
copy = fs.datacopy
rename = fs.move
function mtime(path)
	return fs.stat(path, "mtime")
end
function utime(path, mtime, atime)
	return fs.utimes(path, atime, mtime)
end
basename = fs.basename
dirname = fs.dirname
function dir(...)
	local iter, code, msg = fs.dir(...)
	if iter then
		local t = nutil.consume(iter)
		t[#t+1] = "."
		t[#t+1] = ".."
		return t
	else
		return nil, code, msg
	end
end
function mkdir(path, recursive)
	return recursive and fs.mkdirr(path) or fs.mkdir(path)
end
rmdir = fs.rmdir

local stat_tr = {
	reg = "regular",
	dir = "directory",
	lnk = "link",
	chr = "character device",
	blk = "block device",
	fifo = "fifo",
	sock = "socket"
}
function stat(path, key)
	local data, code, msg = fs.stat(path)
	if data then
		data.mode = data.modestr
		data.type = stat_tr[data.type] or "?"
	end
	return key and data and data[key] or data, code, msg
end
chmod = fs.chmod
function link(src, dest, sym)
	return sym and fs.symlink(src, dest) or fs.link(src, dest)
end
unlink = fs.unlink
readlink = fs.readlink
