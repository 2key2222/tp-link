

local luci  = {}
luci.util   = require "luci.util"
luci.sys    = require "luci.sys"
luci.ip     = require "luci.ip"

local tonumber, ipairs, table = tonumber, ipairs, table
module("luci.sys.iptparser")
IptParser = luci.util.class()

function IptParser.__init__( self, family )
	self._family = (tonumber(family) == 6) and 6 or 4
	self._rules  = { }
	self._chains = { }

	if self._family == 4 then
		self._nulladdr = "0.0.0.0/0"
		self._tables   = { "filter", "nat", "mangle", "raw" }
		self._command  = "iptables -t %s --line-numbers -nxvL"
	else
		self._nulladdr = "::/0"
		self._tables   = { "filter", "mangle", "raw" }
		self._command  = "ip6tables -t %s --line-numbers -nxvL"
	end

	self:_parse_rules()
end
function IptParser.find( self, args )

	local args = args or { }
	local rv   = { }

	args.source      = args.source      and self:_parse_addr(args.source)
	args.destination = args.destination and self:_parse_addr(args.destination)

	for i, rule in ipairs(self._rules) do
		local match = true
		if not ( not args.table or args.table:lower() == rule.table ) then
			match = false
		end
		if not ( match == true and (
			not args.chain or args.chain == rule.chain
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.target or args.target == rule.target
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.protocol or rule.protocol == "all" or
			args.protocol:lower() == rule.protocol
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.source or rule.source == self._nulladdr or
			self:_parse_addr(rule.source):contains(args.source)
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.destination or rule.destination == self._nulladdr or
			self:_parse_addr(rule.destination):contains(args.destination)
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.inputif or rule.inputif == "*" or
			args.inputif == rule.inputif
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.outputif or rule.outputif == "*" or
			args.outputif == rule.outputif
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.flags or rule.flags == args.flags
		) ) then
			match = false
		end
		if not ( match == true and (
			not args.options or
			self:_match_options( rule.options, args.options )
		) ) then
			match = false
		end
		if match == true then
			rv[#rv+1] = rule
		end
	end

	return rv
end
function IptParser.resync( self )
	self._rules = { }
	self._chain = nil
	self:_parse_rules()
end
function IptParser.tables( self )
	return self._tables
end
function IptParser.chains( self, table )
	local lookup = { }
	local chains = { }
	for _, r in ipairs(self:find({table=table})) do
		if not lookup[r.chain] then
			lookup[r.chain]   = true
			chains[#chains+1] = r.chain
		end
	end
	return chains
end
function IptParser.chain( self, table, chain )
	return self._chains[table:lower()] and self._chains[table:lower()][chain]
end
function IptParser.is_custom_target( self, target )
	for _, r in ipairs(self._rules) do
		if r.chain == target then
			return true
		end
	end
	return false
end
function IptParser._parse_addr( self, addr )
	if self._family == 4 then
		return luci.ip.IPv4(addr)
	else
		return luci.ip.IPv6(addr)
	end
end
function IptParser._parse_rules( self )

	for i, tbl in ipairs(self._tables) do

		self._chains[tbl] = { }

		for i, rule in ipairs(luci.util.execl(self._command % tbl)) do

			if rule:find( "^Chain " ) == 1 then

				local crefs
				local cname, cpol, cpkt, cbytes = rule:match(
					"^Chain ([^%s]*) %(policy (%w+) " ..
					"(%d+) packets, (%d+) bytes%)"
				)

				if not cname then
					cname, crefs = rule:match(
						"^Chain ([^%s]*) %((%d+) references%)"
					)
				end

				self._chain = cname
				self._chains[tbl][cname] = {
					policy     = cpol,
					packets    = tonumber(cpkt or 0),
					bytes      = tonumber(cbytes or 0),
					references = tonumber(crefs or 0),
					rules      = { }
				}

			else
				if rule:find("%d") == 1 then

					local rule_parts   = luci.util.split( rule, "%s+", nil, true )
					local rule_details = { }
					if rule:match("^%d+%s+%d+%s+%d+%s%s") then
						table.insert(rule_parts, 4, nil)
					end
					if self._family == 6 then
						table.insert(rule_parts, 6, "--")
					end

					rule_details["table"]       = tbl
					rule_details["chain"]       = self._chain
					rule_details["index"]       = tonumber(rule_parts[1])
					rule_details["packets"]     = tonumber(rule_parts[2])
					rule_details["bytes"]       = tonumber(rule_parts[3])
					rule_details["target"]      = rule_parts[4]
					rule_details["protocol"]    = rule_parts[5]
					rule_details["flags"]       = rule_parts[6]
					rule_details["inputif"]     = rule_parts[7]
					rule_details["outputif"]    = rule_parts[8]
					rule_details["source"]      = rule_parts[9]
					rule_details["destination"] = rule_parts[10]
					rule_details["options"]     = { }

					for i = 11, #rule_parts  do
						if #rule_parts[i] > 0 then
							rule_details["options"][i-10] = rule_parts[i]
						end
					end

					self._rules[#self._rules+1] = rule_details

					self._chains[tbl][self._chain].rules[
						#self._chains[tbl][self._chain].rules + 1
					] = rule_details
				end
			end
		end
	end

	self._chain = nil
end
function IptParser._match_options( self, o1, o2 )
	local oh = { }
	for i, opt in ipairs( o1 ) do oh[opt] = true end
	for i, opt in ipairs( o2 ) do
		if not oh[opt] then
			return false
		end
	end

	return true
end
