local uci    = require "luci.model.uci"
local dbg    = require "luci.tools.debug"
local sys    = require "luci.sys"

local uci_r = uci.cursor()

local CONFIG_NAME="access_ctl"

local CONFIG_TYPE="rule_acl_inner"

function attach_timeobj_rule()
    uci_r:foreach(CONFIG_NAME, CONFIG_TYPE,
        function(section)
            if section["time"] ~= "Any" then
                local rulename = section["name"]
                local time = section["time"]
                sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_add "..time.." access_control "..rulename)
            end
        end        
    )
    sys.fork_call(". /lib/time_mngt/timeobj_api.sh && timeobj_api_commit access_control")

end

attach_timeobj_rule()
