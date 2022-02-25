module("luci.http.protocol", package.seeall)

local ltn12 = require("luci.ltn12")

HTTP_MAX_CONTENT      = 1024*16		-- 16 kB maximum content size
function urldecode( str, no_plus )

	local function __chrdec( hex )
		return string.char( tonumber( hex, 16 ) )
	end

	if type(str) == "string" then
		if not no_plus then
			str = str:gsub( "+", " " )
		end

		str = str:gsub( "%%([a-fA-F0-9][a-fA-F0-9])", __chrdec )
	end

	return str
end
function urldecode_params( url, tbl )

	local params = tbl or { }

	if url:find("?") then
		url = url:gsub( "^.+%?([^?]+)", "%1" )
	end

	for pair in url:gmatch( "[^&;]+" ) do
		local key = urldecode( pair:match("^([^=]+)")     )
		local val = urldecode( pair:match("^[^=]+=(.+)$") )
		if type(key) == "string" and key:len() > 0 then
			if type(val) ~= "string" then val = "" end

			if not params[key] then
				params[key] = val
			elseif type(params[key]) ~= "table" then
				params[key] = { params[key], val }
			else
				table.insert( params[key], val )
			end
		end
	end

	return params
end
function urlencode( str )

	local function __chrenc( chr )
		return string.format(
			"%%%02x", string.byte( chr )
		)
	end

	if type(str) == "string" then
		str = str:gsub(
			"([^a-zA-Z0-9$_%-%.%+!*'(),])",
			__chrenc
		)
	end

	return str
end
function urlencode_params( tbl )
	local enc = ""

	for k, v in pairs(tbl) do
		if type(v) == "table" then
			for i, v2 in ipairs(v) do
				enc = enc .. ( #enc > 0 and "&" or "" ) ..
					urlencode(k) .. "=" .. urlencode(v2)
			end
		else
			enc = enc .. ( #enc > 0 and "&" or "" ) ..
				urlencode(k) .. "=" .. urlencode(v)
		end
	end

	return enc
end
local function __initval( tbl, key )
	if tbl[key] == nil then
		tbl[key] = ""
	elseif type(tbl[key]) == "string" then
		tbl[key] = { tbl[key], "" }
	else
		table.insert( tbl[key], "" )
	end
end
local function __appendval( tbl, key, chunk )
	if type(tbl[key]) == "table" then
		tbl[key][#tbl[key]] = tbl[key][#tbl[key]] .. chunk
	else
		tbl[key] = tbl[key] .. chunk
	end
end
local function __finishval( tbl, key, handler )
	if handler then
		if type(tbl[key]) == "table" then
			tbl[key][#tbl[key]] = handler( tbl[key][#tbl[key]] )
		else
			tbl[key] = handler( tbl[key] )
		end
	end
end
local process_states = { }
process_states['magic'] = function( msg, chunk, err )

	if chunk ~= nil then
		if #chunk == 0 then
			return true, nil
		end
		local method, uri, http_ver = chunk:match("^([A-Z]+) ([^ ]+) HTTP/([01]%.[019])$")
		if method then

			msg.type           = "request"
			msg.request_method = method:lower()
			msg.request_uri    = uri
			msg.http_version   = tonumber( http_ver )
			msg.headers        = { }
			return true, function( chunk )
				return process_states['headers']( msg, chunk )
			end
		else

			local http_ver, code, message = chunk:match("^HTTP/([01]%.[019]) ([0-9]+) ([^\r\n]+)$")
			if code then

				msg.type           = "response"
				msg.status_code    = code
				msg.status_message = message
				msg.http_version   = tonumber( http_ver )
				msg.headers        = { }
				return true, function( chunk )
					return process_states['headers']( msg, chunk )
				end
			end
		end
	end
	return nil, "Invalid HTTP message magic"
end
process_states['headers'] = function( msg, chunk )

	if chunk ~= nil then
		local hdr, val = chunk:match( "^([A-Za-z][A-Za-z0-9%-_]+): +(.+)$" )

		if type(hdr) == "string" and hdr:len() > 0 and
		   type(val) == "string" and val:len() > 0
		then
			msg.headers[hdr] = val
			return true, nil

		elseif #chunk == 0 then
			return false, nil
		else
			return nil, "Invalid HTTP header received"
		end
	else
		return nil, "Unexpected EOF"
	end
end
function header_source( sock )
	return ltn12.source.simplify( function()

		local chunk, err, part = sock:receive("*l")
		if chunk == nil then
			if err ~= "timeout" then
				return nil, part
					and "Line exceeds maximum allowed length"
					or  "Unexpected EOF"
			else
				return nil, err
			end
		elseif chunk ~= nil then
			chunk = chunk:gsub("\r$","")

			return chunk, nil
		end
	end )
end
function mimedecode_message_body( src, msg, filecb )

	if msg and msg.env.CONTENT_TYPE then
		msg.mime_boundary = msg.env.CONTENT_TYPE:match("^multipart/form%-data; boundary=(.+)$")
	end

	if not msg.mime_boundary then
		return nil, "Invalid Content-Type found"
	end


	local tlen   = 0
	local inhdr  = false
	local field  = nil
	local store  = nil
	local lchunk = nil

	local function parse_headers( chunk, field )

		local stat
		repeat
			chunk, stat = chunk:gsub(
				"^([A-Z][A-Za-z0-9%-_]+): +([^\r\n]+)\r\n",
				function(k,v)
					field.headers[k] = v
					return ""
				end
			)
		until stat == 0

		chunk, stat = chunk:gsub("^\r\n","")
		if stat > 0 then
			if field.headers["Content-Disposition"] then
				if field.headers["Content-Disposition"]:match("^form%-data; ") then
					field.name = field.headers["Content-Disposition"]:match('name="(.-)"')
					field.file = field.headers["Content-Disposition"]:match('filename="(.+)"$')
				end
			end

			if not field.headers["Content-Type"] then
				field.headers["Content-Type"] = "text/plain"
			end

			if field.name and field.file and filecb then
				__initval( msg.params, field.name )
				__appendval( msg.params, field.name, field.file )

				store = filecb
			elseif field.name then
				__initval( msg.params, field.name )

				store = function( hdr, buf, eof )
					__appendval( msg.params, field.name, buf )
				end
			else
				store = nil
			end

			return chunk, true
		end

		return chunk, false
	end

	local function snk( chunk )

		tlen = tlen + ( chunk and #chunk or 0 )

		if msg.env.CONTENT_LENGTH and tlen > tonumber(msg.env.CONTENT_LENGTH) + 2 then
			return nil, "Message body size exceeds Content-Length"
		end

		if chunk and not lchunk then
			lchunk = "\r\n" .. chunk

		elseif lchunk then
			local data = lchunk .. ( chunk or "" )
			local spos, epos, found

			repeat
				spos, epos = data:find( "\r\n--" .. msg.mime_boundary .. "\r\n", 1, true )

				if not spos then
					spos, epos = data:find( "\r\n--" .. msg.mime_boundary .. "--\r\n", 1, true )
				end


				if spos then
					local predata = data:sub( 1, spos - 1 )

					if inhdr then
						predata, eof = parse_headers( predata, field )

						if not eof then
							return nil, "Invalid MIME section header"
						elseif not field.name then
							return nil, "Invalid Content-Disposition header"
						end
					end

					if store then
						store( field, predata, true )
					end


					field = { headers = { } }
					found = found or true

					data, eof = parse_headers( data:sub( epos + 1, #data ), field )
					inhdr = not eof
				end
			until not spos

			if found then
				lchunk, data = data, nil
			else
				if inhdr then
					lchunk, eof = parse_headers( data, field )
					inhdr = not eof
				else
					store( field, lchunk, false )
					lchunk, chunk = chunk, nil
				end
			end
		end

		return true
	end

	return ltn12.pump.all( src, snk )
end
function urldecode_message_body( src, msg )

	local tlen   = 0
	local lchunk = nil

	local function snk( chunk )

		tlen = tlen + ( chunk and #chunk or 0 )

		if msg.env.CONTENT_LENGTH and tlen > tonumber(msg.env.CONTENT_LENGTH) + 2 then
			return nil, "Message body size exceeds Content-Length"
		elseif tlen > HTTP_MAX_CONTENT then
			return nil, "Message body size exceeds maximum allowed length"
		end

		if not lchunk and chunk then
			lchunk = chunk

		elseif lchunk then
			local data = lchunk .. ( chunk or "&" )
			local spos, epos

			repeat
				spos, epos = data:find("^.-[;&]")

				if spos then
					local pair = data:sub( spos, epos - 1 )
					local key  = pair:match("^(.-)=")
					local val  = pair:match("=([^%s]*)%s*$")

					if key and #key > 0 then
						__initval( msg.params, key )
						__appendval( msg.params, key, val )
						__finishval( msg.params, key, urldecode )
					end

					data = data:sub( epos + 1, #data )
				end
			until not spos

			lchunk = data
		end

		return true
	end

	return ltn12.pump.all( src, snk )
end
function parse_message_header( src )

	local ok   = true
	local msg  = { }

	local sink = ltn12.sink.simplify(
		function( chunk )
			return process_states['magic']( msg, chunk )
		end
	)
	while ok do
		ok, err = ltn12.pump.step( src, sink )
		if not ok and err then
			return nil, err
		elseif not ok then
			if ( msg.request_method == "get" or msg.request_method == "post" ) and
			   msg.request_uri:match("?")
			then
				msg.params = urldecode_params( msg.request_uri )
			else
				msg.params = { }
			end
			msg.env = {
				CONTENT_LENGTH    = msg.headers['Content-Length'];
				CONTENT_TYPE      = msg.headers['Content-Type'] or msg.headers['Content-type'];
				REQUEST_METHOD    = msg.request_method:upper();
				REQUEST_URI       = msg.request_uri;
				SCRIPT_NAME       = msg.request_uri:gsub("?.+$","");
				SCRIPT_FILENAME   = "";		-- XXX implement me
				SERVER_PROTOCOL   = "HTTP/" .. string.format("%.1f", msg.http_version);
				QUERY_STRING      = msg.request_uri:match("?")
					and msg.request_uri:gsub("^.+?","") or ""
			}
			for i, hdr in ipairs( {
				'Accept',
				'Accept-Charset',
				'Accept-Encoding',
				'Accept-Language',
				'Connection',
				'Cookie',
				'Host',
				'Referer',
				'User-Agent',
			} ) do
				local var = 'HTTP_' .. hdr:upper():gsub("%-","_")
				local val = msg.headers[hdr]

				msg.env[var] = val
			end
		end
	end

	return msg
end
function parse_message_body( src, msg, filecb )
	if msg.env.REQUEST_METHOD == "POST" and msg.env.CONTENT_TYPE and
	   msg.env.CONTENT_TYPE:match("^multipart/form%-data")
	then

		return mimedecode_message_body( src, msg, filecb )
	elseif msg.env.REQUEST_METHOD == "POST" and msg.env.CONTENT_TYPE and
	       msg.env.CONTENT_TYPE:match("^application/x%-www%-form%-urlencoded")
	then
		return urldecode_message_body( src, msg, filecb )
	else

		local sink
		if type(filecb) == "function" then
			sink = filecb
		else
			msg.content = ""
			msg.content_length = 0

			sink = function( chunk, err )
				if chunk then
					if ( msg.content_length + #chunk ) <= HTTP_MAX_CONTENT then
						msg.content        = msg.content        .. chunk
						msg.content_length = msg.content_length + #chunk
						return true
					else
						return nil, "POST data exceeds maximum allowed length"
					end
				end
				return true
			end
		end
		while true do
			local ok, err = ltn12.pump.step( src, sink )

			if not ok and err then
				return nil, err
			elseif not err then
				return true
			end
		end

		return true
	end
end
statusmsg = {
	[200] = "OK",
	[206] = "Partial Content",
	[301] = "Moved Permanently",
	[302] = "Found",
	[304] = "Not Modified",
	[400] = "Bad Request",
	[403] = "Forbidden",
	[404] = "Not Found",
	[405] = "Method Not Allowed",
	[408] = "Request Time-out",
	[411] = "Length Required",
	[412] = "Precondition Failed",
	[416] = "Requested range not satisfiable",
	[500] = "Internal Server Error",
	[503] = "Server Unavailable",
}
