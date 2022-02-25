module("luci.http.protocol.conditionals", package.seeall)

local date = require("luci.http.protocol.date")
function mk_etag( stat )
	if stat ~= nil then
		return string.format( '"%x-%x-%x"', stat.ino, stat.size, stat.mtime )
	end
end
function if_match( req, stat )
	local h    = req.headers
	local etag = mk_etag( stat )
	if type(h['If-Match']) == "string" then
		for ent in h['If-Match']:gmatch("([^, ]+)") do
			if ( ent == '*' or ent == etag ) and stat ~= nil then
				return true
			end
		end

		return false, 412
	end

	return true
end
function if_modified_since( req, stat )
	local h = req.headers
	if type(h['If-Modified-Since']) == "string" then
		local since = date.to_unix( h['If-Modified-Since'] )

		if stat == nil or since < stat.mtime then
			return true
		end

		return false, 304, {
			["ETag"]          = mk_etag( stat );
			["Date"]          = date.to_http( os.time() );
			["Last-Modified"] = date.to_http( stat.mtime )
		}
	end

	return true
end
function if_none_match( req, stat )
	local h      = req.headers
	local etag   = mk_etag( stat )
	local method = req.env and req.env.REQUEST_METHOD or "GET"
	if type(h['If-None-Match']) == "string" then
		for ent in h['If-None-Match']:gmatch("([^, ]+)") do
			if ( ent == '*' or ent == etag ) and stat ~= nil then
				if method == "GET" or method == "HEAD" then
					return false, 304, {
						["ETag"]          = etag;
						["Date"]          = date.to_http( os.time() );
						["Last-Modified"] = date.to_http( stat.mtime )
					}
				else
					return false, 412
				end
			end
		end
	end

	return true
end
function if_range( req, stat )
	return false, 412
end
function if_unmodified_since( req, stat )
	local h = req.headers
	if type(h['If-Unmodified-Since']) == "string" then
		local since = date.to_unix( h['If-Unmodified-Since'] )

		if stat ~= nil and since <= stat.mtime then
			return false, 412
		end
	end

	return true
end
