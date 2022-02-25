

local ltn12 = require "luci.ltn12"
local protocol = require "luci.http.protocol"
local util  = require "luci.util"
local string = require "string"
local coroutine = require "coroutine"
local table = require "table"

local ipairs, pairs, next, type, tostring, error =
	ipairs, pairs, next, type, tostring, error
module "luci.http"

context = util.threadlocal()

local BUFFER_SIZE_LIMIT = 4096
local buffer = {}
local buffer_size = 0

Request = util.class()
function Request.__init__(self, env, sourcein, sinkerr)
	self.input = sourcein
	self.error = sinkerr
	self.filehandler = function() end
	self.message = {
		env = env,
		headers = {},
		params = protocol.urldecode_params(env.QUERY_STRING or ""),
	}

	self.parsed_input = false
end

function Request.formvalue(self, name, noparse)
	if not noparse and not self.parsed_input then
		self:_parse_input()
	end

	if name then
		return self.message.params[name]
	else
		return self.message.params
	end
end

function Request.formvaluetable(self, prefix)
	local vals = {}
	prefix = prefix and prefix .. "." or "."

	if not self.parsed_input then
		self:_parse_input()
	end

	local void = self.message.params[nil]
	for k, v in pairs(self.message.params) do
		if k:find(prefix, 1, true) == 1 then
			vals[k:sub(#prefix + 1)] = tostring(v)
		end
	end

	return vals
end

function Request.content(self)
	if not self.parsed_input then
		self:_parse_input()
	end

	return self.message.content, self.message.content_length
end

function Request.getcookie(self, name)
  local c = string.gsub(";" .. (self:getenv("HTTP_COOKIE") or "") .. ";", "%s*;%s*", ";")
  local p = ";" .. name .. "=(.-);"
  local i, j, value = c:find(p)
  return value and urldecode(value)
end

function Request.getenv(self, name)
	if name then
		return self.message.env[name]
	else
		return self.message.env
	end
end

function Request.setfilehandler(self, callback)
	self.filehandler = callback
end

function Request._parse_input(self)
	protocol.parse_message_body(
		 self.input,
		 self.message,
		 self.filehandler
	)
	self.parsed_input = true
end
function close()
	if not context.eoh then
		flush_header()
	end
	flush()

	if not context.closed then
		context.closed = true
		coroutine.yield(5)
	end
end
function content()
	return context.request:content()
end
function formvalue(name, noparse)
	return context.request:formvalue(name, noparse)
end
function formvaluetable(prefix)
	return context.request:formvaluetable(prefix)
end
function getcookie(name)
	return context.request:getcookie(name)
end
function getenv(name)
	return context.request:getenv(name)
end
function setfilehandler(callback)
	return context.request:setfilehandler(callback)
end
function header(key, value)
	if not context.headers then
		context.headers = {}
	end
	context.headers[key:lower()] = value
	coroutine.yield(2, key, value)
end
function prepare_content(mime)
	if not context.headers or not context.headers["content-type"] then
		if mime == "application/xhtml+xml" then
			if not getenv("HTTP_ACCEPT") or
			  not getenv("HTTP_ACCEPT"):find("application/xhtml+xml", nil, true) then
				mime = "text/html; charset=UTF-8"
			end
			header("Vary", "Accept")
		end
		header("Content-Type", mime)
	end
end
function source()
	return context.request.input
end
function status(code, message)
	code = code or 200
	message = message or "OK"
	context.status = code
	coroutine.yield(1, code, message)
end

function flush()
	if buffer_size > 0 then
		coroutine.yield(4, table.concat(buffer))
		buffer = {}
		buffer_size = 0
	end
end

function flush_header()
	if not context.status then
		status()
	end
	if not context.headers or not context.headers["content-type"] then
		header("Content-Type", "text/html; charset=utf-8")
	end
	if not context.headers["cache-control"] then
		header("Cache-Control", "no-cache")
		header("Expires", "0")
	end
	context.eoh = true
	coroutine.yield(3)
end
function write(content, src_err)
	if not content then
		if src_err then
			flush()
			error(src_err)
		else
			close()
		end
		return true
	else
		local len = #content
		if len == 0 then
		return true
		end

		buffer[#buffer + 1] = content
		buffer_size = buffer_size + len
		if buffer_size > BUFFER_SIZE_LIMIT then
		if not context.eoh then
				flush_header()
			end
			flush()
			end

		return true
	end
end
function splice(fd, size)
	coroutine.yield(6, fd, size)
end
function redirect(url)
	status(302, "Found")
	header("Location", url)
	close()
end
function build_querystring(q)
	local s = { "?" }

	for k, v in pairs(q) do
		if #s > 1 then s[#s+1] = "&" end

		s[#s+1] = urldecode(k)
		s[#s+1] = "="
		s[#s+1] = urldecode(v)
	end

	return table.concat(s, "")
end
urldecode = protocol.urldecode
urlencode = protocol.urlencode
function write_json(x)
	if x == nil then
		write("null")
	elseif type(x) == "table" then
		local k, v
		if type(next(x)) == "number" then
			write("[ ")
			for k, v in ipairs(x) do
				write_json(v)
				if next(x, k) then
					write(", ")
				end
			end
			write(" ]")
		else
			write("{ ")
			for k, v in pairs(x) do
				write(string.format("%q:", k))
				write_json(v)
				if next(x, k) then
					write(", ")
				end
			end
			write(" }")
		end
	elseif type(x) == "number" or type(x) == "boolean" then
		if (x ~= x) then
			write("Number.NaN")
		else
			write(tostring(x))
		end
	else
		write(string.format('"%s"',
							tostring(x):gsub(
								'["%z\1-\31\\]',
								function(c)
			return '\\u%04x' % c:byte(1)
								end
		)))
	end
end
