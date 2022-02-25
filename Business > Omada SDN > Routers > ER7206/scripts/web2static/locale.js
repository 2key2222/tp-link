/*!
 * jQuery Cookie Plugin v1.4.1
 * https://github.com/carhartl/jquery-cookie
 *
 * Copyright 2013 Klaus Hartl
 * Released under the MIT license
 */
(function (factory) {
	if (typeof define === 'function' && define.amd) {
		// AMD
		define(['jquery'], factory);
	} else if (typeof exports === 'object') {
		// CommonJS
		factory(require('jquery'));
	} else {
		// Browser globals
		factory(jQuery);
	}
}(function ($) {

	var pluses = /\+/g;

	function encode(s) {
		return config.raw ? s : encodeURIComponent(s);
	}

	function decode(s) {
		return config.raw ? s : decodeURIComponent(s);
	}

	function stringifyCookieValue(value) {
		return encode(config.json ? JSON.stringify(value) : String(value));
	}

	function parseCookieValue(s) {
		if (s.indexOf('"') === 0) {
			// This is a quoted cookie as according to RFC2068, unescape...
			s = s.slice(1, -1).replace(/\\"/g, '"').replace(/\\\\/g, '\\');
		}

		try {
			// Replace server-side written pluses with spaces.
			// If we can't decode the cookie, ignore it, it's unusable.
			// If we can't parse the cookie, ignore it, it's unusable.
			s = decodeURIComponent(s.replace(pluses, ' '));
			return config.json ? JSON.parse(s) : s;
		} catch(e) {}
	}

	function read(s, converter) {
		var value = config.raw ? s : parseCookieValue(s);
		return $.isFunction(converter) ? converter(value) : value;
	}

	var config = $.cookie = function (key, value, options) {

		// Write

		if (value !== undefined && !$.isFunction(value)) {
			options = $.extend({}, config.defaults, options);

			if (typeof options.expires === 'number') {
				var days = options.expires, t = options.expires = new Date();
				t.setTime(+t + days * 864e+5);
			}

			return (document.cookie = [
				encode(key), '=', stringifyCookieValue(value),
				options.expires ? '; expires=' + options.expires.toUTCString() : '', // use expires attribute, max-age is not supported by IE
				options.path    ? '; path=' + options.path : '',
				options.domain  ? '; domain=' + options.domain : '',
				options.secure  ? '; secure' : ''
			].join(''));
		}

		// Read

		var result = key ? undefined : {};

		// To prevent the for loop in the first place assign an empty array
		// in case there are no cookies at all. Also prevents odd result when
		// calling $.cookie().
		var cookies = document.cookie ? document.cookie.split('; ') : [];

		for (var i = 0, l = cookies.length; i < l; i++) {
			var parts = cookies[i].split('=');
			var name = decode(parts.shift());
			var cookie = parts.join('=');

			if (key && key === name) {
				// If second argument (value) is a function it's a converter...
				result = read(cookie, value);
				break;
			}

			// Prevent storing a cookie that we couldn't decode.
			if (!key && (cookie = read(cookie)) !== undefined) {
				result[name] = cookie;
			}
		}

		return result;
	};

	config.defaults = {};

	$.removeCookie = function (key, options) {
		if ($.cookie(key) === undefined) {
			return false;
		}

		// Must not alter options, thus extending a fresh object...
		$.cookie(key, '', $.extend({}, options, { expires: -1 }));
		return !$.cookie(key);
	};

}));

(function($){
$.su = $.su || {};

$.su.url = function(url){
	var url = $.su.url.subs + $.su.url.stok + url;
 	var mappedJson = $.su.url.urlMap[url];
	if(mappedJson){
		return mappedJson;
	}
	//console.log("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEError: url has no mappedJson",url);
	return url;
};

$.su.ozkerurl = function(url){
	var url = $.su.url.ozkersubs + $.su.url.stok + url;
	return url;
};

$.su.url.ozkersubs = "/cgi-bin/ozker/;stok=";

$.su.url.subs = "/cgi-bin/luci/;stok=";
/*$.su.url.stok = (function(){
	var stok = "12345",
		href = top.location.href;
	var stokPos = href.indexOf("stok=");
	if (stokPos >= 0){
		stok = href.substring(stokPos+5);
	};
	return stok;
})();*/

$.su.url.stok = "";

/*************************************************************************
*1228 KYJ : modify to analyse the mapping relationship between url and json file on client side
*$.su.url.urlMapFiles: the json mapping files.(edit it to modify the mapping relation)
*$.su.getUrlList: the function to get the json mapping files and establish the urlMap
*$.su.url.urlMap: inner object to store the mapping relationship.
*********************************start************************************/
$.su.url.urlMap = {};

$.su.url.urlMapFiles = [
	"nat_url_to_json_ljj.txt",
	"url_to_json_cx.txt",
	"url_to_json_szz.txt",
	"url_to_json_ycf.txt"
];

$.su.getUrlList = function(callback_success, callback_failed){
	var me = this;
	
	for (var i in $.su.url.urlMapFiles){
		var urlFileName = ($.su.url.urlMapFiles)[i];
		$.ajax({
			type: "POST",
			url: "./url_to_json/" + urlFileName,
			async: false,
			dataType: "text",
			cache: false,
			data: "",
			success: function(data){
				var items = data.replace(/\#.*$/gm, '').split(/\n+/g);
				for (var j = 0; j < items.length; j++) {
					var item = items[j].replace(/^ +| +$/, '');	//$.trim(items[j])
					if(item.length > 1){
						item = item.split(/\s+/);
						if(item[0]){
							$.su.url.urlMap[item[0]] = './data/' + item[1];
						}
					}
				}
				if (callback_success){
					callback_success.call(me);
				};
			},
			error: function(){
				if (callback_failed){
					callback_failed.call(me);
				};
			}
		});
	}
};

$.su.getUrlList(null, function(){console.log("getUrlList error");});

/********************************end*************************************/
$.su.locale = {

	URL_LAN_CHECK: "./data/lan.json",

    DEFAULT_LAN_TYPE: "en_US",

    URL_JS: "./locale/%LAN_TYPE%/lan.js",
    URL_CSS: "./locale/%LAN_TYPE%/lan.css",
    URL_HELP: "./locale/%LAN_TYPE%/help.js",
    URL_SETTING: "./locale/%LAN_TYPE%/setting.js",

    locale: "en_US"
};

$.su.locale.get = function(callback_success, callback_failed){
    var me = this;

	var URL_LAN_CHECK = this.URL_LAN_CHECK;

	var URL_JS = this.URL_JS;
	var URL_CSS = this.URL_CSS;
	var URL_HELP = this.URL_HELP;
var URL_SETTING = this.URL_SETTING;
	
	var lanType = $.cookie('locale');
	
	if(!! lanType){
		$.su.locale.changeType({'locale' : lanType});
        if (callback_success){
            callback_success.call(me);
        };
	}
	else{
        $.su.locale.setDefault();
        if (callback_failed){
            callback_failed.call(me);
        };
	}
	
/*     $.ajax({
    	type: "POST",
        url: URL_LAN_CHECK,
        async: false,
        dataType: "json",
        data:{
        	"operation": "read"
        },
        success: function(data){
        	if (data.success && data.data && data.data.locale){
        		$.su.locale.changeType(data.data);
        	}else{
                $.su.locale.setDefault();
            };
        	
            if (callback_success){
                callback_success.call(me);
            };
        },
        error: function(){
            $.su.locale.setDefault();
            if (callback_failed){
                callback_failed.call(me);
            };
        }
    }); */
};
$.su.locale.set = function(lanType, callback_success, callback_failed){
    var me = this;
	if (!lanType){
		return;
	}

	var URL_LAN_CHECK = this.URL_LAN_CHECK;

	var URL_JS = this.URL_JS;
	var URL_CSS = this.URL_CSS;
	var URL_HELP = this.URL_HELP;
    var URL_SETTING = this.URL_SETTING;
	
	/*KYJ 1223 : the cookie created here is session cookie, and will be deleted when the broswer is colsed,
	**if it is expected to be stored for a long time, change the sentence like this:
	**$.cookie('locale', lanType, { expires: 7, path: '/' }); '7'is the days num you want to keep the cookie
	**/
	if (!! $.cookie('locale', lanType, {path: '/' })){
       	location.reload();
        if (callback_success){
            callback_success.call(me);
        };
	}
	else{
	    $.su.locale.setDefault();
        if (callback_failed){
            callback_failed.call(me);
        };
	}
	
/*     $.ajax({
    	type: "POST",
        url: URL_LAN_CHECK,
        async: false,
        dataType: "json",
        cache: false,
        data:{
        	"operation": "write",
        	"locale": lanType
        },
        success: function(data){
        	location.reload();
            if (callback_success){
                callback_success.call(me);
            };
        },
        error: function(){
            $.su.locale.setDefault();
            if (callback_failed){
                callback_failed.call(me);
            };
        }
    }); */
};
$.su.locale.changeType = function(data){
	var lanType = data.locale || this.DEFAULT_LAN_TYPE,
        force = data.force === true ? true : false,
        model = data.model || "",
        region = data.region || "",
        radio = data.radio || "0";

	var URL_JS = this.URL_JS.replace("%LAN_TYPE%", lanType);
	var URL_CSS = this.URL_CSS.replace("%LAN_TYPE%", lanType);
	var URL_HELP = this.URL_HELP.replace("%LAN_TYPE%", lanType);
    var URL_SETTING = this.URL_SETTING.replace("%LAN_TYPE%", lanType);

    this.locale = lanType;
    this.force = force;
    this.model = model;
    this.radio = radio;

	$("script#lan-js").remove();
	$("link#lan-css").remove();
	$("script#lan-help").remove();
    $("script#lan-setting").remove();

	$("head").append("<script id=\"lan-js\" type=\"text/javascript\" src=\""+URL_JS+" \"></script>");
	$("head").append("<link id=\"lan-css\" type=\"text/css\" rel=\"stylesheet\" href=\""+URL_CSS+" \"/>");
	$("head").append("<script id=\"lan-help\" type=\"text/javascript\" src=\""+URL_HELP+" \"></script>");
    $("head").append("<script id=\"lan-setting\" type=\"text/javascript\" src=\""+URL_SETTING+" \"></script>");
    $("head").append("<script type=\"text/javascript\" src=\"./locale/language.js\" ></script>");
    //console.log("this", this)
};

$.su.locale.setDefault = function(){
	this.changeType({
        "locale": this.DEFAULT_LAN_TYPE,
        "force": false,
        "model": "",
        "region": "",
        "radio": "0"
    });
};

})(jQuery);