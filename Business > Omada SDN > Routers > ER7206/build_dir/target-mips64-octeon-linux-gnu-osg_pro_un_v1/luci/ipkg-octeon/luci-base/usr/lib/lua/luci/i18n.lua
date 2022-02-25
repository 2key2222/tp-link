module("luci.i18n", package.seeall)
require("luci.util")

local tparser = require "luci.template.parser"

table   = {}
i18ndir = luci.util.libpath() .. "/i18n/"
loaded  = {}
context = luci.util.threadlocal()
default = "en"
function clear()
end
function load(file, lang, force)
end
function loadc(file, force)
end
function setlanguage(lang)
	context.lang   = lang:gsub("_", "-")
	context.parent = (context.lang:match("^([a-z][a-z])_"))
	if not tparser.load_catalog(context.lang, i18ndir) then
		if context.parent then
			tparser.load_catalog(context.parent, i18ndir)
			return context.parent
		end
	end
	return context.lang
end
function translate(key)
	return tparser.translate(key) or key
end
function translatef(key, ...)
	return tostring(translate(key)):format(...)
end
function string(key)
	return tostring(translate(key))
end
function stringf(key, ...)
	return tostring(translate(key)):format(...)
end
