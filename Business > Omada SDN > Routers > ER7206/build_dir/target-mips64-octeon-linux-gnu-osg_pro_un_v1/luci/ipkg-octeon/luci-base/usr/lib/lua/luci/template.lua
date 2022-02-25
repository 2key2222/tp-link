

local util = require "luci.util"
local config = require "luci.config"
local tparser = require "luci.template.parser"

local tostring, pairs, loadstring = tostring, pairs, loadstring
local setmetatable, loadfile = setmetatable, loadfile
local getfenv, setfenv, rawget = getfenv, setfenv, rawget
local assert, type, error = assert, type, error
module "luci.template"

config.template = config.template or {}
viewdir = config.template.viewdir or util.libpath() .. "/view"
context = util.threadlocal()
function render(name, scope)
	return Template(name):render(scope or getfenv(2))
end
Template = util.class()
Template.cache = setmetatable({}, {__mode = "v"})
function Template.__init__(self, name)	

	self.template = self.cache[name]
	self.name = name
	self.viewns = context.viewns
	if not self.template then
		local err
		local sourcefile = viewdir .. "/" .. name .. ".htm"

		self.template, _, err = tparser.parse(sourcefile)
		if not self.template then
			error("Failed to load template '" .. name .. "'.\n" ..
			      "Error while parsing template '" .. sourcefile .. "':\n" ..
			      (err or "Unknown syntax error"))
		else
			self.cache[name] = self.template
		end
	end
end
function Template.render(self, scope)
	scope = scope or getfenv(2)
	setfenv(self.template, setmetatable({}, {__index =
		function(tbl, key)
			return rawget(tbl, key) or self.viewns[key] or scope[key]
		end}))
	local stat, err = util.copcall(self.template)
	if not stat then
		error("Failed to execute template '" .. self.name .. "'.\n" ..
		      "A runtime error occured: " .. tostring(err or "(nil)"))
	end
end
