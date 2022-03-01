module("luci.soap", package.seeall)

require "luci.http"
local lom = require"lxp.lom"

local tescape = {
	['&'] = '&amp;',
	['<'] = '&lt;',
	['>'] = '&gt;',
	['"'] = '&quot;',
	["'"] = '&apos;',
	[' '] = '&#160;',
}

local tunescape = {
	['&amp;'] = '&',
	['&lt;'] = '<',
	['&gt;'] = '>',
	['&quot;'] = '"',
	['&apos;'] = "'",
	['&#160;'] = " ",
}

function tosoap(obj, tag)
	local att = ""
	local str = ""
	local tt = type(obj)
	if tt == "string" then
		if #obj == 0 then
			return obj
		elseif #obj:gsub("[%z\1-\127\194-\244][\128-\191]*", "") > 0 then
			local o = {}
			for i = 1, #obj do
				o[i] = obj:sub(i, i):byte()
			end
			str = "&#"..table.concat(o, ";&#")..";"
		else
			str = obj:gsub("([&<>'\" ])", tescape)
		end
	elseif tt == "number"  then
		str = obj
	elseif tt == "boolean" then
		str = obj and "true" or "false"
	elseif tt == "table"   then
		if _G.next(obj) == nil then
			return str
		else
			local c = {"\n"}
			for k, v in pairs(obj) do
				if k == "_attr_" then
					for k, v in pairs(v) do
						att = att .. string.format(" %s=%q",k, v)
					end
				elseif type(v) == "table" and #v > 0 then
					for _, v in ipairs(v) do
						c[#c + 1] = tosoap(v, k)
					end
				else
					c[#c + 1] = tosoap(v, k)
				end
			end
			str = table.concat(c)
		end
	end
	return string.format("<%s%s>%s</%s>\n", tag, att, str, tag)
end

function fromsoap(soap)
	local tt = type(soap)
	if tt == "table" then
		local obj = {}
		for _, v in ipairs(soap) do
			tag, v = fromsoap(v)
			if tag then
				local o = obj[tag]
				if o then
					if type(o) ~= "table" or #o == 0 then
						obj[tag] = {o, v}
					else
						o[#o + 1] = v
					end
				elseif type(v) ~= "table" or _G.next(v) ~= nil then
					obj[tag] = v
				end
			else
				return soap.tag, v
			end
		end
		local attr = soap.attr
		if attr and #attr > 0 then
			obj._attr_ = {}
			for k, v in ipairs(attr) do
				obj._attr_[v] = attr[v]
			end
		end
		return soap.tag, obj
	elseif tt == "string" then
		return nil, soap:gsub("([&<>'\" ])", tunescape)
	else
		return nil, "SOAP-ERROR-XML"
	end
end

function read_soap()
	local doc = luci.http.content():gsub("(</[^<>]*>)%s*", "%1")
		:gsub("%s*(<[^/<>][^<>]*>)%s*(<[^/<>][^<>]*>)", "%1%2")
	local tag, envelope = fromsoap(lom.parse(doc))
	if tag == "Envelope" and type(envelope) == "table" then
		local body = envelope.Body
		local head = envelope.Header
		if type(body) == "table"  then
			for k, obj in pairs(body) do
				local name = obj._attr_ and obj._attr_.xmlns
				local method = k:match ("%:([^:]*)$") or k
				-- os.execute("echo '%s' &>/dev/console" % (require("luka.table_print").table_tostring(obj)))
				return obj, method, name
			end
		end
	end
	return {}, nil, nil
end

function write_soap(api, data)
	luci.http.prepare_content('text/xml; charset="UTF-8"')
	if type(data) == "table" then
		if data[api.."Result"] == nil then
			local result = data.success and "OK" or "ERROR"
			local status = {code = data.errorcode or 0, message = data.message}
			data = data.data or {}
			data.ActionStatus = status
			data[api.."Result"] = result
		end

		local soap = {Body = {[api.."Response"] = data}}
		data._attr_ = {xmlns = "http://iot.tpri.tp-link.com/"}
		soap._attr_ = {xmlns = "http://schemas.xmlsoap.org/soap/envelope/"}

		local httpbody = '<?xml version="1.0" encoding="utf-8"?>\n' .. tosoap(soap, "Envelope")
		luci.http.header("Content-Length", #httpbody)
		-- os.execute("echo '%s' &>/dev/console" % (httpbody))
		luci.http.write(httpbody)
	end
end

