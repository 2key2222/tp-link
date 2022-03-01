-- Copyright 2008 Steven Barth <steven@midlink.org>
-- Licensed to the public under the Apache License 2.0.

local fs = require "nixio.fs"
local sys = require "luci.sys"
local util = require "luci.util"
local http = require "luci.http"
local nixio = require "nixio", require "nixio.util"
local soap = require "luci.soap"

module("luci.dispatcher", package.seeall)
context = util.threadlocal()
uci = require "luci.model.uci".cursor()
i18n = require "luci.i18n"
_M.fs = fs

authenticator = {}

-- Index table
local luka_index = nil
local luci_index = nil

-- Fastindex
local fi

luci_prefetch_tree = {}
luka_prefetch_tree = {}

function build_url(...)
	local path = {...}
	local sname = http.getenv("SCRIPT_NAME") or ""
	local reurl = http.getenv("REQUEST_URI") or ""
	local url = { "" }

	if string.find(reurl, sname, 1, true) then
		url = { sname }
	end

	local p
	for _, p in ipairs(path) do
		if p:match("^[a-zA-Z0-9_%-%.%%/,;]+$") then
			url[#url+1] = "/"
			url[#url+1] = p
		end
	end

	if #path == 0 then
		url[#url+1] = "/"
	end

	return table.concat(url, "")
end

function node_visible(node)
   if node then
	  return not (
		 (not node.title or #node.title == 0) or
		 (not node.target or node.hidden == true) or
		 (type(node.target) == "table" and node.target.type == "firstchild" and
		  (type(node.nodes) ~= "table" or not next(node.nodes)))
	  )
   end
   return false
end

function node_childs(node)
	local rv = { }
	if node then
		local k, v
		for k, v in util.spairs(node.nodes,
			function(a, b)
				return (node.nodes[a].order or 100)
				     < (node.nodes[b].order or 100)
			end)
		do
			if node_visible(v) then
				rv[#rv+1] = k
			end
		end
	end
	return rv
end

function error404(message)
	http.status(404, "Not Found")
	message = message or "Not Found"

	require("luci.template")
	if not util.copcall(luci.template.render, "error404") then
		http.prepare_content("text/plain")
		http.write(message)
	end
	return false
end

function error403(message)
	http.status(403, "Forbidden")
	message = message or "Forbidden"

	require("luci.template")
	if not util.copcall(luci.template.render, "error403") then
		http.prepare_content("text/plain")
		http.write(message)
	end
	return false
end

function error401(message)

	message = message or "{ \"err_code\": -10007, \"err_msg\": \"Unauthorized Error\"}"
	http.status(401, message)

	require("luci.template")
	if not util.copcall(luci.template.render, "error401") then
		http.prepare_content("text/plain")
		http.write(message)
	end
	return false
end

function error500(message)
	util.perror(message)
	if not context.template_header_sent then
		http.status(500, "Internal Server Error")
		http.prepare_content("text/plain")
		http.write(message)
	else
		require("luci.template")
		if not util.copcall(luci.template.render, "error500", {message=message}) then
			http.prepare_content("text/plain")
			http.write(message)
		end
	end
	return false
end

function authenticator.htmlauth(validator, accs, default)
	local user = http.formvalue("luci_username")
	local pass = http.formvalue("luci_password")

	if user and validator(user, pass) then
		return user
	end

	require("luci.i18n")
	require("luci.template")
	context.path = {}
	http.status(403, "Forbidden")
	luci.template.render("sysauth", {duser=default, fuser=user})

	return false

end

local base64 = require "luci.tools.base64"
local md5 = require "luci.tools.md5"
function auth_user(user, password)
	local login_password = md5.md5(password)
	local ipc_password = base64.encode(password)

	device_user = uci:get("account", "account", "user")
	device_password = uci:get("account", "account", "password")
	if device_user == user and (device_password:upper() == login_password:upper()
			or device_password == ipc_password) then
		return true
	else
		return false
	end
end

function soap_error(name)
	local rspMethod = {}
	rspMethod[name.."Result"] = "ERROR"
	soap.write_soap(name, rspMethod)
	return
end

function httpdispatch(request, prefix)
	http.context.request = request

	local r = {}
	context.request = r

	local soapaction = request:getenv("HTTP_SOAPACTION") or nil
	local pathinfo
	if soapaction ~= nil then
		pathinfo = http.urldecode(soapaction:match("/([^/]-)$"), true)
	else
		pathinfo = http.urldecode(request:getenv("PATH_INFO") or "", true)
	end

	if prefix then
		for _, node in ipairs(prefix) do
			r[#r+1] = node
		end
	end

	for node in pathinfo:gmatch("[^/]+") do
		r[#r+1] = node
	end

	local stat, err = util.coxpcall(function()
		dispatch(context.request, soapaction, request)
	end, error500)

	http.close()

	--context._disable_memtrace()
end

-- added by chenjianfeng, to dispatch the module function
function linkieDispatch(module_name, method_name, method_params)
	local rspMethod = {}
	local ctx = context
	ctx.path = method_name
	local c = ctx.tree
	if not c then
		c = luka_prefetch_tree
	end

	local target = nil
	local method_node = string.format("%s_%s", module_name, method_name)
	c = c.nodes[method_node]

	if not c then
		return -1, nil
		--c = luka_prefetch_tree
		--c = c.nodes["system_not_support"]
	end

	if c then
		if type(c.target) == "function" then
			target = c.target
		elseif type(c.target) == "table" then
			target = c.target.target
		end
	end

	if c and (c.index or type(target) == "function") then
		ctx.dispatched = c
	end

	util.copcall(function()
			local oldenv = getfenv(target)
			local module = require(c.module)
			local env = setmetatable({}, {__index=

			function(tbl, key)
				return rawget(tbl, key) or module[key] or oldenv[key]
			end})

			setfenv(target, env)
		end)

	local ok, err
	if type(c.target) == "table" then
		if not method_params or method_params == "" then
			ok, rspMethod = util.copcall(target, c.target, nil)
		else
			ok, rspMethod = util.copcall(target, c.target, method_params)
		end
	else
		ok, rspMethod = util.copcall(target, method_params)
	end
	return 0, rspMethod
end

function dispatch(request, luka_flag, ori_request)
	--context._disable_memtrace = require "luci.debug".trap_memtrace("l")
	local ctx = context
	ctx.path = request

	local conf = require "luci.config"
	assert(conf.main,
		"/etc/config/luci seems to be corrupt, unable to find section 'main'")

	local lang = conf.main.lang or "auto"
	if lang == "auto" then
		local aclang = http.getenv("HTTP_ACCEPT_LANGUAGE") or ""
		for lpat in aclang:gmatch("[%w-]+") do
			lpat = lpat and lpat:gsub("-", "_")
			if conf.languages[lpat] then
				lang = lpat
				break
			end
		end
	end
	require "luci.i18n".setlanguage(lang)

	local c = ctx.tree
	local stat
	if not c then
		if luka_flag == nil then
			c = luci_prefetch_tree
		else
			c = luka_prefetch_tree
		end
	end

	local track = {}
	local args = {}
	ctx.args = args
	ctx.requestargs = ctx.requestargs or args
	local n
	local preq = {}
	local freq = {}
	local api_name = ""

	for i, s in ipairs(request) do
		preq[#preq+1] = s
		freq[#freq+1] = s
		c = c.nodes[s]
		n = i
		if not c then
			break
		end

		util.update(track, c)
		api_name = s
		if c.leaf then
			break
		end
	end

	if c and c.leaf then
		for j=n+1, #request do
			args[#args+1] = request[j]
			freq[#freq+1] = request[j]
		end
	elseif luka_flag ~= nil then
		return soap_error(api_name)
	else
		return error404()
	end

	ctx.requestpath = ctx.requestpath or freq
	ctx.path = preq

	if track.i18n then
		i18n.loadc(track.i18n)
	end
-- We don't use template
--[[	
	-- Init template engine
	if (c and c.index) or not track.notemplate then
		local tpl = require("luci.template")
		local media = track.mediaurlbase or luci.config.main.mediaurlbase
		if not pcall(tpl.Template, "themes/%s/header" % fs.basename(media)) then
			media = nil
			for name, theme in pairs(luci.config.themes) do
				if name:sub(1,1) ~= "." and pcall(tpl.Template,
				 "themes/%s/header" % fs.basename(theme)) then
					media = theme
				end
			end
			assert(media, "No valid theme found")
		end

		local function _ifattr(cond, key, val)
			if cond then
				local env = getfenv(3)
				local scope = (type(env.self) == "table") and env.self
				return string.format(
					' %s="%s"', tostring(key),
					util.pcdata(tostring( val
					 or (type(env[key]) ~= "function" and env[key])
					 or (scope and type(scope[key]) ~= "function" and scope[key])
					 or "" ))
				)
			else
				return ''
			end
		end

		tpl.context.viewns = setmetatable({
		   write       = http.write;
		   include     = function(name) tpl.Template(name):render(getfenv(2)) end;
		   translate   = i18n.translate;
		   translatef  = i18n.translatef;
		   export      = function(k, v) if tpl.context.viewns[k] == nil then tpl.context.viewns[k] = v end end;
		   striptags   = util.striptags;
		   pcdata      = util.pcdata;
		   media       = media;
		   theme       = fs.basename(media);
		   resource    = luci.config.main.resourcebase;
		   ifattr      = function(...) return _ifattr(...) end;
		   attr        = function(...) return _ifattr(true, ...) end;
		}, {__index=function(table, key)
			if key == "controller" then
				return build_url()
			elseif key == "REQUEST_URI" then
				return build_url(unpack(ctx.requestpath))
			else
				return rawget(table, key) or _G[key]
			end
		end})
	end
	]]--

	track.dependent = (track.dependent ~= false)
	assert(not track.dependent or not track.auto,
		"Access Violation\nThe page at '" .. table.concat(request, "/") .. "/' " ..
		"has no parent node so the access to this location has been denied.\n" ..
		"This is a software bug, please report this message at " ..
		"http://luci.subsignal.org/trac/newticket"
	)

	local auth_str_ori = ori_request:getenv("HTTP_AUTHORIZATION") or ""
	if auth_str_ori ~= "" then
		local auth_str_base64 = string.gsub(auth_str_ori, "Basic ", "")
		local auth_str = base64.decode(auth_str_base64)
		local d_num = string.find(auth_str, ":")

		if d_num == nil then
			args = {401}
		else
			local user = string.sub(auth_str, 1, d_num - 1)
			local password = string.sub(auth_str, d_num + 1)
			if false == auth_user(user, password) then
				args = {401}
			end
		end
	elseif track.sysauth then
		local authen = type(track.sysauth_authenticator) == "function"
		 and track.sysauth_authenticator
		 or authenticator[track.sysauth_authenticator]

		local def  = (type(track.sysauth) == "string") and track.sysauth
		local accs = def and {track.sysauth} or track.sysauth
		local sess = ctx.authsession
		if not sess then
			sess = http.getcookie(luci.config.extra.sysauth_alias or "sysauth")
			sess = sess and sess:match("^[a-f0-9]*$")
		end

		local sdat = (util.ubus("session", "get", { ubus_rpc_session = sess }) or { }).values
		local user, token

		if sdat then
			user = sdat.user
			token = sdat.token
		else
			local eu = http.getenv("HTTP_AUTH_USER")
			local ep = http.getenv("HTTP_AUTH_PASS")
			if eu and ep and sys.user.checkpasswd(eu, ep) then
				authen = function() return eu end
			end
		end

		if luci.config.extra.auth_rpt then
			local function error_json(e)
				http.prepare_content("application/json")
				http.write_json({ success = false, errorcode = e})
			end
			--Disable ip-check for keep-cookie when ip changes.
			--if not user or sdat.ipaddr ~= sys.getenv("REMOTE_ADDR") then
			if not user then
				local reurl = http.getenv("REQUEST_URI") or ""
				if reurl == "/" or reurl == "/index.html" or reurl == "/index2.html" then
					local l12 = require "luci.ltn12"
					local loginpage = reurl == "/index2.html" and "/login2.html" or "/login.html"
					local fd = io.open(luci.sys.getenv("DOCUMENT_ROOT") .. loginpage, "r")
					if fd then
						luci.http.prepare_content("text/html")
						l12.pump.all(l12.source.file(fd), luci.http.write)
					end
					return
				else
					return error_json("timeout")
				end
			else
				ctx.authsession = sess
			end
		elseif not util.contains(accs, user) then
			if authen then
				local user, sess = authen(sys.user.checkpasswd, accs, def)
				local token
				if not user or not util.contains(accs, user) then
					return
				else
					if not sess then
						local sdat = util.ubus("session", "create", { timeout = tonumber(luci.config.sauth.sessiontime) })
						if sdat then
							token = sys.uniqueid(16)
							util.ubus("session", "set", {
								ubus_rpc_session = sdat.ubus_rpc_session,
								values = {
									user = user,
									token = token,
									section = sys.uniqueid(16)
								}
							})
							sess = sdat.ubus_rpc_session
						end
					end

					if sess and token then
						http.header("Set-Cookie", 'sysauth=%s; path=%s/' %{
						   sess, build_url()
						})

						ctx.authsession = sess
						ctx.authtoken = token
						ctx.authuser = user

						http.redirect(build_url(unpack(ctx.requestpath)))
					end
				end
			else
				http.status(403, "Forbidden")
				return
			end
		else
			ctx.authsession = sess
			ctx.authtoken = token
			ctx.authuser = user
		end
	end

	if track.setgroup then
		sys.process.setgroup(track.setgroup)
	end

	if track.setuser then
		-- trigger ubus connection before dropping root privs
		util.ubus()

		sys.process.setuser(track.setuser)
	end

	local target = nil
	if c then
		if type(c.target) == "function" then
			target = c.target
		elseif type(c.target) == "table" then
			target = c.target.target
		end
	end

	if c and (c.index or type(target) == "function") then
		ctx.dispatched = c
		ctx.requested = ctx.requested or ctx.dispatched
	end

	if c and c.index then
		local tpl = require "luci.template"

		if util.copcall(tpl.render, "indexer", {}) then
			return true
		end
	end

	if type(target) == "function" then
		util.copcall(function()
			local oldenv = getfenv(target)
			local module = require(c.module)
			local env = setmetatable({}, {__index=

			function(tbl, key)
				return rawget(tbl, key) or module[key] or oldenv[key]
			end})

			setfenv(target, env)
		end)

		if luka_flag ~= nil then
			local params = soap.read_soap()

			if params then
				args[#args+1] = params
			end
		end

		local ok, rsp
		if type(c.target) == "table" then
			ok, rsp = util.copcall(target, c.target, unpack(args))
		else
			ok, rsp = util.copcall(target, unpack(args))
		end

		if luka_flag ~= nil and rsp ~= nil then
			soap.write_soap(api_name, rsp)
		end


		assert(ok,
		       "Failed to execute " .. (type(c.target) == "function" and "function" or c.target.type or "unknown") ..
		       " dispatcher target for entry '/" .. table.concat(request, "/") .. "'.\n" ..
		       "The called action terminated with an exception:\n" .. tostring(rsp or "(unknown)"))
	else
		local root = node()
		if not root or not root.target then
			error404("No root node was registered, this usually happens if no module was installed.\n" ..
			         "Install luci-mod-admin-full and retry. " ..
			         "If the module is already installed, try removing the /tmp/luci-indexcache file.")
		else
			error404("No page is registered at '/" .. table.concat(request, "/") .. "'.\n" ..
			         "If this url belongs to an extension, make sure it is properly installed.\n" ..
			         "If the extension was recently installed, try removing the /tmp/luci-indexcache file.")
		end
	end
end

function createindex(base, prefix)
	local controllers = { }

	local _, path
	local index

	for path in (fs.glob("%s*.lua" % base) or function() end) do
		controllers[#controllers+1] = path
	end

	for path in (fs.glob("%s*/*.lua" % base) or function() end) do
		controllers[#controllers+1] = path
	end

	if indexcache then
		local cachedate = fs.stat(indexcache, "mtime")
		if cachedate then
			local realdate = 0
			for _, obj in ipairs(controllers) do
				local omtime = fs.stat(obj, "mtime")
				realdate = (omtime and omtime > realdate) and omtime or realdate
			end

			if cachedate > realdate and sys.process.info("uid") == 0 then
				assert(
					sys.process.info("uid") == fs.stat(indexcache, "uid")
					and fs.stat(indexcache, "modestr") == "rw-------",
					"Fatal: Indexcache is not sane!"
				)

				index = loadfile(indexcache)()
				return index
			end
		end
	end

	index = {}

	for _, path in ipairs(controllers) do
		local modname = prefix .. path:sub(#base+1, #path-4):gsub("/", ".")
		local mod = require(modname)
		assert(mod ~= true,
		       "Invalid controller file found\n" ..
		       "The file '" .. path .. "' contains an invalid module line.\n" ..
		       "Please verify whether the module name is set to '" .. modname ..
		       "' - It must correspond to the file path!")

		local idx = mod.index
		assert(type(idx) == "function",
		       "Invalid controller file found\n" ..
		       "The file '" .. path .. "' contains no index() function.\n" ..
		       "Please make sure that the controller contains a valid " ..
		       "index function and verify the spelling!")

		index[modname] = idx
	end

	if indexcache then
		local f = nixio.open(indexcache, "w", 600)
		f:writeall(util.get_bytecode(index))
		f:close()
	end
	return index
end

-- Build the index before if it does not exist yet.
function createtree(index)
	local ctx  = context
	local tree = {nodes={}, inreq=true}
	local modi = {}

	ctx.treecache = setmetatable({}, {__mode="v"})
	ctx.tree = tree
	ctx.modifiers = modi

	-- Load default translation
	require "luci.i18n".loadc("base")

	local scope = setmetatable({}, {__index = luci.dispatcher})

	--local scope = setmetatable({}, {__index = luka.dispatcher})

	for k, v in pairs(index) do
		scope._NAME = k
		setfenv(v, scope)
		v()
	end

	local function modisort(a,b)
		return modi[a].order < modi[b].order
	end

	for _, v in util.spairs(modi, modisort) do
		scope._NAME = v.module
		setfenv(v.func, scope)
		v.func()
	end

	return tree
end

function modifier(func, order)
	context.modifiers[#context.modifiers+1] = {
		func = func,
		order = order or 0,
		module
			= getfenv(2)._NAME
	}
end

function assign(path, clone, title, order)
	local obj  = node(unpack(path))
	obj.nodes  = nil
	obj.module = nil

	obj.title = title
	obj.order = order

	setmetatable(obj, {__index = _create_node(clone)})

	return obj
end

function entry(path, target, title, order)
	local c = node(unpack(path))

	c.target = target
	c.title  = title
	c.order  = order
	c.module = getfenv(2)._NAME

	return c
end

function secure_entry(path, target, title, order)
	local c = entry(path, target, title, order)
	c.module = getfenv(2)._NAME
	c.sysauth = 'root'
	return c
end

-- enabling the node.
function get(...)
	return _create_node({...})
end

function node(...)
	local c = _create_node({...})

	c.module = getfenv(2)._NAME
	c.auto = nil

	return c
end

function _create_node(path)
	if #path == 0 then
		return context.tree
	end

	local name = table.concat(path, ".")
	local c = context.treecache[name]

	if not c then
		local last = table.remove(path)
		local parent = _create_node(path)

		c = {nodes={}, auto=true}
		-- the node is "in request" if the request path matches
		-- at least up to the length of the node path
		if context.path ~= nil and parent.inreq and context.path[#path+1] == last then
		  c.inreq = true
		end
		parent.nodes[last] = c
		context.treecache[name] = c
	end
	return c
end

-- Subdispatchers --

function _firstchild()
   local path = { unpack(context.path) }
   local name = table.concat(path, ".")
   local node = context.treecache[name]

   local lowest
   if node and node.nodes and next(node.nodes) then
	  local k, v
	  for k, v in pairs(node.nodes) do
		 if not lowest or
			(v.order or 100) < (node.nodes[lowest].order or 100)
		 then
			lowest = k
		 end
	  end
   end

   assert(lowest ~= nil,
		  "The requested node contains no childs, unable to redispatch")

   path[#path+1] = lowest
   dispatch(path)
end

function firstchild()
   return { type = "firstchild", target = _firstchild }
end

function alias(...)
	local req = {...}
	return function(...)
		for _, r in ipairs({...}) do
			req[#req+1] = r
		end

		dispatch(req)
	end
end

function rewrite(n, ...)
	local req = {...}
	return function(...)
		local dispatched = util.clone(context.dispatched)

		for i=1,n do
			table.remove(dispatched, 1)
		end

		for i, r in ipairs(req) do
			table.insert(dispatched, i, r)
		end

		for _, r in ipairs({...}) do
			dispatched[#dispatched+1] = r
		end

		dispatch(dispatched)
	end
end


local function _call(self, ...)
	local func = getfenv()[self.name]
	assert(func ~= nil,
	       'Cannot resolve function "' .. self.name .. '". Is it misspelled or local?')

	assert(type(func) == "function",
	       'The symbol "' .. self.name .. '" does not refer to a function but data ' ..
	       'of type "' .. type(func) .. '".')

	if #self.argv > 0 then
		return func(unpack(self.argv), ...)
	else
		return func(...)
	end
end

function call(name, ...)
	return {type = "call", argv = {...}, name = name, target = _call}
end


local _template = function(self, ...)
	require "luci.template".render(self.view)
end

function template(name)
	return {type = "template", view = name, target = _template}
end


local function _cbi(self, ...)
	local cbi = require "luci.cbi"
	local tpl = require "luci.template"
	local http = require "luci.http"

	local config = self.config or {}
	local maps = cbi.load(self.model, ...)

	local state = nil

	for i, res in ipairs(maps) do
		res.flow = config
		local cstate = res:parse()
		if cstate and (not state or cstate < state) then
			state = cstate
		end
	end

	local function _resolve_path(path)
		return type(path) == "table" and build_url(unpack(path)) or path
	end

	if config.on_valid_to and state and state > 0 and state < 2 then
		http.redirect(_resolve_path(config.on_valid_to))
		return
	end

	if config.on_changed_to and state and state > 1 then
		http.redirect(_resolve_path(config.on_changed_to))
		return
	end

	if config.on_success_to and state and state > 0 then
		http.redirect(_resolve_path(config.on_success_to))
		return
	end

	if config.state_handler then
		if not config.state_handler(state, maps) then
			return
		end
	end

	http.header("X-CBI-State", state or 0)

	if not config.noheader then
		tpl.render("cbi/header", {state = state})
	end

	local redirect
	local messages
	local applymap   = false
	local pageaction = true
	local parsechain = { }

	for i, res in ipairs(maps) do
		if res.apply_needed and res.parsechain then
			local c
			for _, c in ipairs(res.parsechain) do
				parsechain[#parsechain+1] = c
			end
			applymap = true
		end

		if res.redirect then
			redirect = redirect or res.redirect
		end

		if res.pageaction == false then
			pageaction = false
		end

		if res.message then
			messages = messages or { }
			messages[#messages+1] = res.message
		end
	end

	for i, res in ipairs(maps) do
		res:render({
			firstmap   = (i == 1),
			applymap   = applymap,
			redirect   = redirect,
			messages   = messages,
			pageaction = pageaction,
			parsechain = parsechain
		})
	end

	if not config.nofooter then
		tpl.render("cbi/footer", {
			flow       = config,
			pageaction = pageaction,
			redirect   = redirect,
			state      = state,
			autoapply  = config.autoapply
		})
	end
end

function cbi(model, config)
	return {type = "cbi", config = config, model = model, target = _cbi}
end


local function _arcombine(self, ...)
	local argv = {...}
	local target = #argv > 0 and self.targets[2] or self.targets[1]
	setfenv(target.target, self.env)
	target:target(unpack(argv))
end

function arcombine(trg1, trg2)
	return {type = "arcombine", env = getfenv(), target = _arcombine, targets = {trg1, trg2}}
end


local function _form(self, ...)
	local cbi = require "luci.cbi"
	local tpl = require "luci.template"
	local http = require "luci.http"

	local maps = luci.cbi.load(self.model, ...)
	local state = nil

	for i, res in ipairs(maps) do
		local cstate = res:parse()
		if cstate and (not state or cstate < state) then
			state = cstate
		end
	end

	http.header("X-CBI-State", state or 0)
	tpl.render("header")
	for i, res in ipairs(maps) do
		res:render()
	end
	tpl.render("footer")
end

function form(model)
	return {type = "cbi", model = model, target = _form}
end

translate = i18n.translate

-- This function does not actually translate the given argument but
-- is used by build/i18n-scan.pl to find translatable entries.
function _(text)
	return text
end

function file_exists(path)
	local file = io.open(path, "rb")
	if file then
		file:close()
	end
	return file ~= nil
end

if next(luci_prefetch_tree) == nil then
	if file_exists("/usr/lib/lua/luci/controller/") then
		luci_index = createindex("/usr/lib/lua/luci/controller/", "luci.controller.")
		luci_prefetch_tree = createtree(luci_index)
	end
end

if next(luka_prefetch_tree) == nil then
	if file_exists("/usr/lib/lua/luka/controller/") then
		luka_index = createindex("/usr/lib/lua/luka/controller/", "luka.controller.")
		luka_prefetch_tree = createtree(luka_index)
	end
end

