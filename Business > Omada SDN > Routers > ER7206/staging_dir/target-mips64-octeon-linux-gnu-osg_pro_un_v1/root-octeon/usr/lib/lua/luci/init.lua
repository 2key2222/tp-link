

local require = require
if not _G.bit then
	_G.bit = require "bit"
end

module "luci"

local v = require "luci.version"

__version__ = v.luciversion or "trunk"
__appname__ = v.luciname    or "LuCI"
