

local config = require "luci.config"
local ccache = require "luci.ccache"

module "luci.cacheloader"

if config.ccache and config.ccache.enable == "1" then
	ccache.cache_ondemand()
end