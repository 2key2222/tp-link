local uci    = require "luci.model.uci"
local dbg    = require "luci.tools.debug"
local sys    = require "luci.sys"
--local socket = require "socket"

local uci_r = uci.cursor()

local CONFIG_NAME="url_filter"

local CONFIG_TYPE="url"

function attach_timeobj_rule()
    uci_r:foreach(CONFIG_NAME, CONFIG_TYPE,
        function(section)
            if section["enable"] == "on" and section["time"] ~= "Any" then
                local rulename = section["urlgroupname"]
                local time = section["time"]
                sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_add "..time.." url_filter "..rulename)
            end
        end        
    )
    sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_commit url_filter")
    return
end


attach_timeobj_rule()
