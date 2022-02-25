// JavaScript Document
(function($){
var arrayFilter = function(array, obj){
    var returnObj = {};
    /* get instance from array via obj */
    if(!array || array.length === 0 || !obj){
        return returnObj;
    }
    if(!$.isArray(array)){
        array = [array];
    }
    $.each(array, function(i, instance){
        var match = true;
        $.each(obj, function(key, value){
            if(instance[key] != value){
                match = false;
                return false;
            }
        });
        if(!!match){
            returnObj = instance;
            return false;
        }
    });
    return returnObj;
};
$.su.Proxy = function(options){
	var defaults = {
		xtype: "proxy",
		url: null,
        combineKey: null,
		async: true,
		timeout: 240*1000,
		reader: {
			url: null,
			root: "result",
			type: null,
			timeout: null
		},
		writer: {
			url: null,
			root: "result",
			type: null,
			timeout: null
		},
		type: "POST",
		dataType: "json"
	};

	var settings = $.extend(defaults, options);
	
	//reader
	settings.reader.url = settings.reader.url || settings.url;
    settings.reader.combineKey = settings.reader.combineKey || settings.combineKey;
	settings.reader.type = settings.reader.type || settings.type;
	settings.reader.timeout = settings.reader.timeout || settings.timeout;
	settings.reader.type = settings.reader.type.toUpperCase();
	//writer
	settings.writer.url = settings.writer.url || settings.url;
    settings.writer.combineKey = settings.writer.combineKey || settings.combineKey;
	settings.writer.type = settings.writer.type || settings.type;
	settings.writer.timeout = settings.writer.timeout || settings.timeout;
	settings.writer.type = settings.writer.type.toUpperCase();
	

	$.extend(this, settings);
	this.isProxy = true;
};

$.su.Proxy.prototype.read = function(data, callback, callback_fail, callback_error, triggerEvent, scope){
	var data = $.extend({
		"method": "get"
	}, data);
	
	var me = scope || this,
		callback = callback || function(){},
		callback_fail = callback_fail || function(){},
		callback_error = callback_error || function(){},
		triggerEvent = triggerEvent === false ? false: true;

	var url = me.reader.url,
        combineKey = me.reader.combineKey;
    if(!$.isArray(url)){
        return $.ajax({
            url: me.reader.url,
            type: me.reader.type,
            timeout: me.reader.timeout,
            dataType: me.dataType,
            async: me.async,
            cache: false,
            data: {data: $.su.json.toJSONString(data)},
            traditional: true,
            success: function(data, status, xhr){
                if (data.error_code == 0){
                    var root = me.reader.root,
                        result = null;
                    if (root){
                        result = data[root];
                        //console.log(url);
                    }else{
                        result = data;
                        //console.log(url);
                    };
                    //console.log("proxy", data);
                    callback.call(me, result, data.others, status, xhr);
                    if (triggerEvent){
                        $(me).trigger("ev_read", [result, data.others, status, xhr]);
                    };
                }else{
                    //alert(data.error_code);
                    if ("undefined" == typeof(data.error_code)) {
                        data.error_code = 404;
                    }
                    //进入配置失败机制
                    if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.denied){
                        $.su.app.errorOperation.denied(data.error_code);
                    };

                    /*旧的处理机制
                    switch(data.error_code){

                        case "timeout":
                            location.href = "/";
                            break;
                        case "user conflict":
                            if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.userConflict){
                                $.su.app.errorOperation.userConflict();
                            };
                            break;
                        case "permission denied":
                            if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.denied){
                                $.su.app.errorOperation.denied();
                            };
                            break;
                        default:

                    };
                    */

                    callback_fail.call(me, data.error_code, data.others, data.result);
                    $(me).trigger("ev_failed", [data.error_code, data.others, data.result]);
                };
            },
            error: function(xhr, status, type){
                //console.log(url);
                //console.log("proxy", arguments)
                if (!me.preventErrorDefault){
                    //console.log("error", xhr, status, type, url);
                    //alert("Data Error!");
                };
                callback_error.call(me, xhr, status, type, url);
                $(me).trigger("ev_error", [xhr, status, type, url]);
            }
        });
    }
    else{
        var deferredArray = [];
        $.each(url, function(i, obj){
            deferredArray.push($.ajax({
                url: obj,
                type: me.reader.type,
                timeout: me.reader.timeout,
                dataType: me.dataType,
                async: me.async,
                cache: false,
                data: {data: $.su.json.toJSONString(data)},
                traditional: true
            }));
        });
        return $.when.apply($, deferredArray).done(function(){
            var root = me.reader.root,
                result = {},
                others = {},
                error_code = 0,
                status = "success",
                xhr = arguments[0][2];
            //arguments = [[data, status, jqXHR], ..., []]
            if(!combineKey){
                for(var i = arguments.length - 1; i>=0; i--){
                    var dataTemp = arguments[i][0],
                        statusTemp = arguments[i][1];

                    if(dataTemp.error_code != 0){
                        error_code = dataTemp.error_code;
                        break;
                    }
                    if(statusTemp != "success"){
                        status = statusTemp;
                    }
                    if(dataTemp){
                        $.extend(true, result, dataTemp[root]);
                        $.extend(true, others, dataTemp.others);
                    }
                }
                result.length = arguments[0][0][root].length;
                result = Array.prototype.slice.call(result, 0);
            }else{
                if($.isArray(combineKey) && combineKey.length == url.length){
                    result = arguments[0][0][root];
                    if(!result || $.isEmptyObject(result)){
                        result = [];
                    }
                    if(!$.isArray(result)){
                        result = [result];
                    }
                    status = arguments[0][1];
                    error_code = arguments[0][0].error_code;
                    others = arguments[0][0].others;
                    for(var i = arguments.length - 1; i>=1; i--){
                        var dataTemp = arguments[i][0],
                            statusTemp = arguments[i][1];

                        if(dataTemp.error_code != 0){
                            error_code = dataTemp.error_code;
                            break;
                        }
                        if(statusTemp != "success"){
                            status = statusTemp;
                        }
                        $.each(result, function(idx, instance){
                            var obj = {};
                            obj[combineKey[i]] = instance[combineKey[0]];
                            obj = arrayFilter(dataTemp[root], obj);
                            delete obj[combineKey[i]];
                            $.extend(result[idx], obj);
                        });
                    }
                }
            }
            if(error_code == 0){
                callback.call(me, result, others, status, xhr);
                if (triggerEvent) {
                    $(me).trigger("ev_read", [result, others, status, xhr]);
                }
            }else{
                if ("undefined" == typeof(error_code)) {
                        error_code = 404;
                }
                    //进入配置失败机制
                    if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.denied){
                        $.su.app.errorOperation.denied(error_code);
                };
                callback_fail.call(me, error_code, others, result);
                $(me).trigger("ev_failed", [error_code, others, result]);
            }
        }).fail(function(){
            var xhr = arguments[0][0],
                status = arguments[0][1],
                type = arguments[0][1];
            callback_error.call(me, xhr, status, type, url);
            if (triggerEvent) {
                $(me).trigger("ev_error", [xhr, status, type, url]);
            }
        });
    }
};

$.su.Proxy.prototype.write = function(data, callback, callback_fail, callback_error, triggerEvent, scope){
	var data = $.extend({
		"method": "set"
	}, data);
	
	var me = scope || this,
		callback = callback || function(){},
		callback_fail = callback_fail || function(){},
		callback_error = callback_error || function(){},
		triggerEvent = triggerEvent === false ? false: true;

	var url = me.writer.url,
        combineKey = me.writer.combineKey;
    if(!$.isArray(url)) {
	return $.ajax({
		url: me.writer.url,
		type: me.writer.type,
		timeout: me.writer.timeout,
		dataType: me.dataType,
		cache: false,
		async: me.async,
		data: {data: $.su.json.toJSONString(data)},
		traditional: true,
		success: function(data, status, xhr){
			if (data.error_code == 0){
				var root = me.writer.root,
					result = null;
				if (root){
					result = data[root];
				}else{
					result = data;
				}
				callback.call(me, result, data.others, status, xhr);
				if (triggerEvent){
					$(me).trigger("ev_write", [result, data.others, status, xhr]);
				};
			}else{
				//进入配置失败机制
                if ("undefined" == typeof(data.error_code)) {
                    data.error_code = 404;
                }


                if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.denied){
                    $.su.app.errorOperation.denied(data.error_code);
                };
                /*旧的失败处理机制
				switch(data.error_code){
					case "timeout":
						location.href = "/";
						break;
					case "user conflict":
						if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.userConflict){
							$.su.app.errorOperation.userConflict();
						};
						break;
					case "permission denied":
						if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.denied){
							$.su.app.errorOperation.denied();
						};
						break;
					default:
						
				};
                */
				
				callback_fail.call(me, data.error_code, data.others, data.result);
				$(me).trigger("ev_failed", [data.error_code, data.others, data.result]);
			};
		},
		error: function(xhr, status, type){
			if (!me.preventErrorDefault){
				//console.log("error", xhr, status, type);
				//alert("Data Error!");
			};
                callback_error.call(me, xhr, status, type);
                $(me).trigger("ev_error", [xhr, status, type, url]);
            }
        });
    }else{
        var deferredArray = [];
        $.each(url, function(i, obj){
            deferredArray.push($.ajax({
                url: obj,
                type: me.reader.type,
                timeout: me.reader.timeout,
                dataType: me.dataType,
                async: me.async,
                cache: false,
                data: {data: $.su.json.toJSONString(data)},
                traditional: true
            }));
        });
        return $.when.apply($, deferredArray).done(function(){
            var root = me.reader.root,
                result = {},
                others = {},
                error_code = 0,
                status = "success",
                xhr = arguments[0][2];
            //arguments = [[data, status, jqXHR], ..., []]
            if(!combineKey){
                for(var i = arguments.length - 1; i>=0; i--){
                    var dataTemp = arguments[i][0],
                        statusTemp = arguments[i][1];

                    if(dataTemp.error_code != 0){
                        error_code = dataTemp.error_code;
                        break;
                    }
                    if(statusTemp != "success"){
                        status = statusTemp;
                    }
                    if(dataTemp){
                        $.extend(true, result, dataTemp[root]);
                        $.extend(true, others, dataTemp.others);
                    }
                }
                result.length = arguments[0][0][root].length;
                result = Array.prototype.slice.call(result, 0);
            }else{
                if($.isArray(combineKey) && combineKey.length == url.length){
                    result = arguments[0][0][root];
                    if(!result || $.isEmptyObject(result)){
                        result = [];
                    }
                    if(!$.isArray(result)){
                        result = [result];
                    }
                    status = arguments[0][1];
                    error_code = arguments[0][0].error_code;
                    others = arguments[0][0].others;
                    for(var i = arguments.length - 1; i>=1; i--){
                        var dataTemp = arguments[i][0],
                            statusTemp = arguments[i][1];

                        if(dataTemp.error_code != 0){
                            error_code = dataTemp.error_code;
                            break;
                        }
                        if(statusTemp != "success"){
                            status = statusTemp;
                        }
                        $.each(result, function(idx, instance){
                            var obj = {};
                            obj[combineKey[i]] = instance[combineKey[0]];
                            obj = arrayFilter(dataTemp[root], obj);
                            delete obj[combineKey[i]];
                            $.extend(result[idx], obj);
                        });
                    }
                }
            }
            if(error_code == 0){
                callback.call(me, result, others, status, xhr);
                if (triggerEvent) {
                    $(me).trigger("ev_read", [result, others, status, xhr]);
                }
            }else{
                if ("undefined" == typeof(error_code)) {
                        error_code = 404;
                }
                    //进入配置失败机制
                    if ($.su.app && $.su.app.errorOperation && $.su.app.errorOperation.denied){
                        $.su.app.errorOperation.denied(error_code);
                };
                callback_fail.call(me, error_code, others, result);
                $(me).trigger("ev_failed", [error_code, others, result]);
            }
        }).fail(function(){
            var xhr = arguments[0][0],
                status = arguments[0][1],
                type = arguments[0][1];
            callback_error.call(me, xhr, status, type, url);
            if (triggerEvent) {
                $(me).trigger("ev_error", [xhr, status, type, url]);
            }
        });
    }
};


})(jQuery);