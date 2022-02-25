local uci    = require "luci.model.uci"
local dbg    = require "luci.tools.debug"
local sys    = require "luci.sys"

local uci_r = uci.cursor()

local CONFIG_NAME="web_security"

local CONFIG_TYPE="rule"

function detach_timeobj_rule()
    uci_r:foreach(CONFIG_NAME, CONFIG_TYPE,
        function(section)
            if section["state"] == "on" and section["timeobj"] ~= "Any" then
                local rulename = section["name"]
                local time = section["timeobj"]
                sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_delete "..time.." web_security "..rulename)
            end
        end        
    )

    sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_commit web_security")
    
end

detach_timeobj_rule()
