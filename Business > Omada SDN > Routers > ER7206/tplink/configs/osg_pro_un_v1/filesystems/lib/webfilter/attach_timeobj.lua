local uci    = require "luci.model.uci"
local dbg    = require "luci.tools.debug"
local sys    = require "luci.sys"

local uci_r = uci.cursor()

local CONFIG_NAME="webfilter"

local CONFIG_TYPE="webfilter"

function attach_timeobj_rule()
    uci_r:foreach(CONFIG_NAME, CONFIG_TYPE,
        function(section)
            if section["state"] == "on" and section["time"] ~= "Any" then
                local rulename = section["rulename"]
                local time = section["time"]
                sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_add "..time.." webfilter "..rulename)
            end
        end        
    )
    sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_commit webfilter")
end

attach_timeobj_rule()
