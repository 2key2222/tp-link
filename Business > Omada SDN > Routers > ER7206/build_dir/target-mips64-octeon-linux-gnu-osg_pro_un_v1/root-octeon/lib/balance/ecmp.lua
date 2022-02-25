function string.split(str, delimiter)
    if str==nil or str=='' or delimiter==nil then
		return nil
	end
	
    local result = {}
    for match in (str..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match)
    end
    return result
end

local FILE="/tmp/.route_flag"
local RET_FILE="/tmp/.route_ret"

local fp = io.open(FILE, "r")
local all_info = {}
local flag = 0
local ex = 1

ll = fp:read("*l")
while(ll)
do
	local ret = {}
	non_blank=string.gsub(ll, "%s+", ",")
	ret = string.split(non_blank, ",")

	for i, value in ipairs(all_info) do		
		if ret[2] == value.gw and ret[5] == value.metric then
			value.dev = value.dev.." "..ret[8]
			value.flag = 1	
			ex = 1
			break
		end
	end

	if ex == 0 then
		table.insert(all_info, {gw=ret[2], metric=ret[5], flag=0, dev=ret[8]})
	end

	ex = 0
	if flag == 0 then
		table.insert(all_info, {gw=ret[2], metric=ret[5], flag=0, dev=ret[8]})
		flag = 1
	end
		
	ll = fp:read("*l")
end

fp:close()

local ff
local file = 0
local cmd = "%s,%s\n"

for i,value in ipairs(all_info) do
	if value.flag == 1 then
		ff = io.open(RET_FILE, "a+")
		ff:write(string.format(cmd, value.gw, value.dev))  
		file = 1	
	end
end
  
if file == 1 then
	ff:close()
end
