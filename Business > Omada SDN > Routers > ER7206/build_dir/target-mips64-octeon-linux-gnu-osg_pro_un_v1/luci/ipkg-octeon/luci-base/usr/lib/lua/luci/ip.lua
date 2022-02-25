module( "luci.ip", package.seeall )

require "nixio"
local bit  = nixio.bit
local util = require "luci.util"
LITTLE_ENDIAN = not util.bigendian()
BIG_ENDIAN    = not LITTLE_ENDIAN
FAMILY_INET4  = 0x04
FAMILY_INET6  = 0x06


local function __bless(x)
	return setmetatable( x, {
		__index	= luci.ip.cidr,
		__add   = luci.ip.cidr.add,
		__sub   = luci.ip.cidr.sub,
		__lt	= luci.ip.cidr.lower,
		__eq	= luci.ip.cidr.equal,
		__le	=
			function(...)
				return luci.ip.cidr.equal(...) or luci.ip.cidr.lower(...)
			end
	} )
end

local function __array16( x, family )
	local list

	if type(x) == "number" then
		list = { bit.rshift(x, 16), bit.band(x, 0xFFFF) }

	elseif type(x) == "string" then
		if x:find(":") then x = IPv6(x) else x = IPv4(x) end
		if x then
			assert( x[1] == family, "Can't mix IPv4 and IPv6 addresses" )
			list = { unpack(x[2]) }
		end

	elseif type(x) == "table" and type(x[2]) == "table" then
		assert( x[1] == family, "Can't mix IPv4 and IPv6 addresses" )
		list = { unpack(x[2]) }

	elseif type(x) == "table" then
		list = { unpack(x) }
	end

	assert( list, "Invalid operand" )

	return list
end

local function __mask16(bits)
	return bit.lshift( bit.rshift( 0xFFFF, 16 - bits % 16 ), 16 - bits % 16 )
end

local function __not16(bits)
	return bit.band( bit.bnot( __mask16(bits) ), 0xFFFF )
end

local function __maxlen(family)
	return ( family == FAMILY_INET4 ) and 32 or 128
end

local function __sublen(family)
	return ( family == FAMILY_INET4 ) and 30 or 127
end
local function __zcompressed(data)
	local str    = nil
	local first  = nil
	local second = nil
	local once   = false
	local i      = 2

	while i < 9 do
		if data[i] == 0 then
			first = first or i
			second = i
		else
			if first and second and (second - first > 0) then
				break
			else
				first = nil
				second = nil
			end
		end

		i = i + 1
	end

	if first and second and (second - first < 1) then
		first = nil
		second = nil
	end

	i = 1
	str = string.format("%X", data[i])
	i = i + 1
	while i < 9 do
		if first and second then
			if i < first or i > second then
				str = str .. string.format(":%X", data[i])
			else
				if not once then
					str = str .. ":"
					once = true
				end
			end
		else
			str = str .. string.format(":%X", data[i])
		end

		i = i + 1
	end

	if second and second == 8 then
		str = str .. ":"
	end

	return str
end
function htons(x)
	if LITTLE_ENDIAN then
		return bit.bor(
			bit.rshift( x, 8 ),
			bit.band( bit.lshift( x, 8 ), 0xFF00 )
		)
	else
		return x
	end
end
function htonl(x)
	if LITTLE_ENDIAN then
		return bit.bor(
			bit.lshift( htons( bit.band( x, 0xFFFF ) ), 16 ),
			htons( bit.rshift( x, 16 ) )
		)
	else
		return x
	end
end
ntohs = htons
ntohl = htonl
function IPv4(address, netmask)
	address = address or "0.0.0.0/0"

	local obj = __bless({ FAMILY_INET4 })

	local data = {}
	local prefix = address:match("/(.+)")
	address = address:gsub("/.+","")
	address = address:gsub("^%[(.*)%]$", "%1"):upper():gsub("^::FFFF:", "")

	if netmask then
		prefix = obj:prefix(netmask)
	elseif prefix then
		prefix = tonumber(prefix)
		if not prefix or prefix < 0 or prefix > 32 then return nil end
	else
		prefix = 32
	end

	local b1, b2, b3, b4 = address:match("^(%d+)%.(%d+)%.(%d+)%.(%d+)$")

	b1 = tonumber(b1)
	b2 = tonumber(b2)
	b3 = tonumber(b3)
	b4 = tonumber(b4)

	if b1 and b1 <= 255 and
	   b2 and b2 <= 255 and
	   b3 and b3 <= 255 and
	   b4 and b4 <= 255 and
	   prefix
	then
		table.insert(obj, { b1 * 256 + b2, b3 * 256 + b4 })
		table.insert(obj, prefix)
		return obj
	end
end
function IPv6(address, netmask)
	address = address or "::/0"

	local obj = __bless({ FAMILY_INET6 })

	local data = {}
	local prefix = address:match("/(.+)")
	address = address:gsub("/.+","")
	address = address:gsub("^%[(.*)%]$", "%1")

	if netmask then
		prefix = obj:prefix(netmask)
	elseif prefix then
		prefix = tonumber(prefix)
		if not prefix or prefix < 0 or prefix > 128 then return nil end
	else
		prefix = 128
	end

	local borderl = address:sub(1, 1) == ":" and 2 or 1
	local borderh, zeroh, chunk, block, i

	if #address > 45 then return nil end

	repeat
		borderh = address:find(":", borderl, true)
		if not borderh then break end

		block = tonumber(address:sub(borderl, borderh - 1), 16)
		if block and block <= 0xFFFF then
			data[#data+1] = block
		else
			if zeroh or borderh - borderl > 1 then return nil end
			zeroh = #data + 1
		end

		borderl = borderh + 1
	until #data == 7

	chunk = address:sub(borderl)
	if #chunk > 0 and #chunk <= 4 then
		block = tonumber(chunk, 16)
		if not block or block > 0xFFFF then return nil end

		data[#data+1] = block
	elseif #chunk > 4 then
		if #data == 7 or #chunk > 15 then return nil end
		borderl = 1
		for i=1, 4 do
			borderh = chunk:find(".", borderl, true)
			if not borderh and i < 4 then return nil end
			borderh = borderh and borderh - 1

			block = tonumber(chunk:sub(borderl, borderh))
			if not block or block > 255 then return nil end

			if i == 1 or i == 3 then
				data[#data+1] = block * 256
			else
				data[#data] = data[#data] + block
			end

			borderl = borderh and borderh + 2
		end
	end

	if zeroh then
		if #data == 8 then return nil end
		while #data < 8 do
			table.insert(data, zeroh, 0)
		end
	end

	if #data == 8 and prefix then
		table.insert(obj, data)
		table.insert(obj, prefix)
		return obj
	end
end
function Hex( hex, prefix, family, swap )
	family = ( family ~= nil ) and family or FAMILY_INET4
	swap   = ( swap   == nil ) and true   or swap
	prefix = prefix or __maxlen(family)

	local len  = __maxlen(family)
	local tmp  = ""
	local data = { }
	local i

	for i = 1, (len/4) - #hex do tmp = tmp .. '0' end

	if swap and LITTLE_ENDIAN then
		for i = #hex, 1, -2 do tmp = tmp .. hex:sub( i - 1, i ) end
	else
		tmp = tmp .. hex
	end

	hex = tmp

	for i = 1, ( len / 4 ), 4 do
		local n = tonumber( hex:sub( i, i+3 ), 16 )
		if n then
			data[#data+1] = n
		else
			return nil
		end
	end

	return __bless({ family, data, prefix })
end
cidr = util.class()
function cidr.is4( self )
	return self[1] == FAMILY_INET4
end
function cidr.is4rfc1918( self )
	if self[1] == FAMILY_INET4 then
		return ((self[2][1] >= 0x0A00) and (self[2][1] <= 0x0AFF)) or
		       ((self[2][1] >= 0xAC10) and (self[2][1] <= 0xAC1F)) or
		        (self[2][1] == 0xC0A8)
	end
	return false
end
function cidr.is4linklocal( self )
	if self[1] == FAMILY_INET4 then
		return (self[2][1] == 0xA9FE)
	end
	return false
end
function cidr.is6( self )
	return self[1] == FAMILY_INET6
end
function cidr.is6linklocal( self )
	if self[1] == FAMILY_INET6 then
		return (self[2][1] >= 0xFE80) and (self[2][1] <= 0xFEBF)
	end
	return false
end
function cidr.string( self )
	local str
	if self:is4() then
		str = string.format(
			"%d.%d.%d.%d",
			bit.rshift(self[2][1], 8), bit.band(self[2][1], 0xFF),
			bit.rshift(self[2][2], 8), bit.band(self[2][2], 0xFF)
		)
		if self[3] < 32 then
			str = str .. "/" .. self[3]
		end
	elseif self:is6() then
		str = string.format( "%X:%X:%X:%X:%X:%X:%X:%X", unpack(self[2]) )
		if self[3] < 128 then
			str = str .. "/" .. self[3]
		end
	end
	return str
end
function cidr.zcstring( self )
	local str
	if self:is4() then
		str = string.format(
			"%d.%d.%d.%d",
			bit.rshift(self[2][1], 8), bit.band(self[2][1], 0xFF),
			bit.rshift(self[2][2], 8), bit.band(self[2][2], 0xFF)
		)
		if self[3] < 32 then
			str = str .. "/" .. self[3]
		end
	elseif self:is6() then
		str = __zcompressed(self[2])

		if self[3] < 128 then
			str = str .. "/" ..self[3]
		end
	end
	return str
end
function cidr.lower( self, addr )
	assert( self[1] == addr[1], "Can't compare IPv4 and IPv6 addresses" )
	local i
	for i = 1, #self[2] do
		if self[2][i] ~= addr[2][i] then
			return self[2][i] < addr[2][i]
		end
	end
	return false
end
function cidr.higher( self, addr )
	assert( self[1] == addr[1], "Can't compare IPv4 and IPv6 addresses" )
	local i
	for i = 1, #self[2] do
		if self[2][i] ~= addr[2][i] then
			return self[2][i] > addr[2][i]
		end
	end
	return false
end
function cidr.equal( self, addr )
	assert( self[1] == addr[1], "Can't compare IPv4 and IPv6 addresses" )
	local i
	for i = 1, #self[2] do
		if self[2][i] ~= addr[2][i] then
			return false
		end
	end
	return true
end
function cidr.prefix( self, mask )
	local prefix = self[3]

	if mask then
		prefix = 0

		local stop = false
		local obj = type(mask) ~= "table"
			and ( self:is4() and IPv4(mask) or IPv6(mask) ) or mask

		if not obj then return nil end

		local _, word
		for _, word in ipairs(obj[2]) do
			if word == 0xFFFF then
				prefix = prefix + 16
			else
				local bitmask = bit.lshift(1, 15)
				while bit.band(word, bitmask) == bitmask do
					prefix  = prefix + 1
					bitmask = bit.lshift(1, 15 - (prefix % 16))
				end

				break
			end
		end
	end

	return prefix
end
function cidr.network( self, bits )
	local data = { }
	bits = bits or self[3]

	local i
	for i = 1, math.floor( bits / 16 ) do
		data[#data+1] = self[2][i]
	end

	if #data < #self[2] then
		data[#data+1] = bit.band( self[2][1+#data], __mask16(bits) )

		for i = #data + 1, #self[2] do
			data[#data+1] = 0
		end
	end

	return __bless({ self[1], data, __maxlen(self[1]) })
end
function cidr.host( self )
	return __bless({ self[1], self[2], __maxlen(self[1]) })
end
function cidr.mask( self, bits )
	local data = { }
	bits = bits or self[3]

	for i = 1, math.floor( bits / 16 ) do
		data[#data+1] = 0xFFFF
	end

	if #data < #self[2] then
		data[#data+1] = __mask16(bits)

		for i = #data + 1, #self[2] do
			data[#data+1] = 0
		end
	end

	return __bless({ self[1], data, __maxlen(self[1]) })
end
function cidr.broadcast( self )
	if self[1] == FAMILY_INET4 then
		local data   = { unpack(self[2]) }
		local offset = math.floor( self[3] / 16 ) + 1

		if offset <= #data then
			data[offset] = bit.bor( data[offset], __not16(self[3]) )
			for i = offset + 1, #data do data[i] = 0xFFFF end

			return __bless({ self[1], data, __maxlen(self[1]) })
		end
	end
end
function cidr.contains( self, addr )
	assert( self[1] == addr[1], "Can't compare IPv4 and IPv6 addresses" )

	if self:prefix() <= addr:prefix() then
		return self:network() == addr:network(self:prefix())
	end

	return false
end
function cidr.add( self, amount, inplace )
	local pos
	local data   = { unpack(self[2]) }
	local shorts = __array16( amount, self[1] )

	for pos = #data, 1, -1 do
		local add = ( #shorts > 0 ) and table.remove( shorts, #shorts ) or 0
		if ( data[pos] + add ) > 0xFFFF then
			data[pos] = ( data[pos] + add ) % 0xFFFF
			if pos > 1 then
				data[pos-1] = data[pos-1] + ( add - data[pos] )
			else
				return nil
			end
		else
			data[pos] = data[pos] + add
		end
	end

	if inplace then
		self[2] = data
		return self
	else
		return __bless({ self[1], data, self[3] })
	end
end
function cidr.sub( self, amount, inplace )
	local pos
	local data   = { unpack(self[2]) }
	local shorts = __array16( amount, self[1] )

	for pos = #data, 1, -1 do
		local sub = ( #shorts > 0 ) and table.remove( shorts, #shorts ) or 0
		if ( data[pos] - sub ) < 0 then
			data[pos] = ( sub - data[pos] ) % 0xFFFF
			if pos > 1 then
				data[pos-1] = data[pos-1] - ( sub + data[pos] )
			else
				return nil
			end
		else
			data[pos] = data[pos] - sub
		end
	end

	if inplace then
		self[2] = data
		return self
	else
		return __bless({ self[1], data, self[3] })
	end
end
function cidr.minhost( self )
	if self[3] <= __sublen(self[1]) then
		return self:network():add(1, true)
	end
end
function cidr.maxhost( self )
	if self[3] <= __sublen(self[1]) then
		local i
		local data   = { unpack(self[2]) }
		local offset = math.floor( self[3] / 16 ) + 1

		data[offset] = bit.bor( data[offset], __not16(self[3]) )
		for i = offset + 1, #data do data[i] = 0xFFFF end
		data = __bless({ self[1], data, __maxlen(self[1]) })
		if data[1] == FAMILY_INET4 then data:sub(1, true) end

		return data
	end
end
