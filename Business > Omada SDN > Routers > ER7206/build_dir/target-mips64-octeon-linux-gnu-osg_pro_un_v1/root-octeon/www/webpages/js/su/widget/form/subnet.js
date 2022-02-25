// JavaScript Document
(function($){
$.su.Widget("subnet", {
	defaults: {
		readOnly: false,

		isvalid: false,

		fieldLabel: "",

		tips: "",
		validator: null,
		invalidText: $.su.CHAR.VTYPETEXT.INVALIDTEXT,
		allowBlank: false,
		blankText: $.su.CHAR.VTYPETEXT.BLANKTEXT,
		cls: "",
		validateIcon: false,

		textFormat: null,

		autoTrim: true
	},

	create: function(defaults, options){
		var me = this;
		me.each(function(i, obj){
			var input = $(this),
                inputIp = $('<input />'),
                inputMask = $('<input />');
			if (!input.is("input")){
				return null;
			};
			$.extend(this, defaults, options);
			
			var id = options.id || this.id || $.su.randomId("subnet"),
				value = options.value || input.val() || input.attr("value") || defaults.value,
				name = options.name || input.attr("name") || this.name || defaults.name;
			//重新初始化属性
            input.attr({
                name: name,
                id: id,
                value: value
            }).val(value).addClass("subnet-value hidden");

            inputIp.addClass("text-text text-subnet-ip "+this.inputCls);

            inputMask.addClass("text-text text-subnet-mask "+this.inputCls);
			
			if(this._maxLength){
				input.attr("maxlength", this._maxLength);
			};
            inputMask.attr("maxlength", 2);

            var inHTML = 	"<div class=\"container widget-container text-container "+this.cls+"\">";
				
			if (this.fieldLabel !== null){
				inHTML +=		"<div class=\"widget-fieldlabel-wrap "+this.labelCls+"\">";
				inHTML +=			"<label class=\"widget-fieldlabel text-fieldlabel\">"+this.fieldLabel+"</label>";
				if (this.fieldLabel !== ""){
					inHTML +=		"<span class=\"widget-separator\">"+this.separator+"</span>";
				};
				inHTML +=		"</div>";
			};

				inHTML +=		"<div class=\"widget-wrap-outer text-wrap-outer\">";
				inHTML +=			"<div class=\"widget-wrap text-wrap\">";
				inHTML +=				"<span class=\"text-wrap\"></span>";
				inHTML +=			"</div>";
                inHTML +=			"<span>&nbsp;/&nbsp;</span>";
                inHTML +=			"<div class=\"widget-wrap text-wrap\">";
                inHTML +=				"<span class=\"text-wrap\"></span>";
                inHTML +=			"</div>";

			if (this.validateIcon){
				inHTML +=			"<span class=\"widget-validate-icon\"></span>";
			};

			if (this.tips != null && this.tips != undefined){
				inHTML +=			"<div class=\"widget-tips textbox-tips "+this.tipsCls+"\">";
				inHTML +=				"<div class=\"content tips-content\"></div>";
				inHTML +=			"</div>";
			};

				inHTML +=			"<div class=\"widget-error-tips textbox-error-tips "+this.errorTipsCls+"\">";
				inHTML +=				"<span class=\"widget-error-tips-delta\"></span>";
				inHTML +=				"<div class=\"widget-error-tips-wrap\">";
				inHTML +=					"<div class=\"content error-tips-content\"></div>";
				inHTML +=				"</div>";
				inHTML +=			"</div>";

				inHTML += 		"</div>";
				inHTML += 	"</div>";

			var container = $(inHTML);
			input.replaceWith(container);
			container.find("span.text-wrap:eq(0)").append(inputIp);
            container.find("span.text-wrap:eq(1)").append(inputMask);
            container.append(input);


			if (this.readOnly){
				container.addClass("read-only");
                inputIp.prop("readOnly", true);
                inputMask.prop("readOnly", true);
			};
		});

		
		var container = me.closest("div.widget-container");
		container.delegate("input.text-text", "click", function(e){
			e.stopPropagation();
		}).delegate("input.text-text", "focus", function(e){
			me.subnet("setFocus");
		}).delegate("input.text-text", "blur", function(e){
			me.subnet("removeFocus").subnet("validate");
		}).delegate("input.text-text", "keyup", function(e){
			me.trigger("ev_change", [me.subnet("getValue")]);
		}).delegate("input.text-text", "setValue", function(e){
			me.subnet("validate");
		}).delegate("input.text-text", "ev_validatechange", function(e, isvalid, tips){
			e.stopPropagation();
			if (isvalid){
				me.subnet("setValid");
			}else{
				me.subnet("setError", tips);
			}
		});



		me.subnet("setTips", options.tips);
		
		return me;
	},
	validate: function(me, flag){
		var me = me || this,
            $ip = me.subnet("getContainer").find(".text-subnet-ip"),
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
			tar = me.get(0),
            tarIp = $ip.get(0),
            tarMask = $mask.get(0),
			flag = (flag[1] === false) ? false : true;

		var result = false,
			valueIp = tar.autoTrim ? $.trim(tarIp.value) : tarIp.value,
            valueMask = tar.autoTrim ? $.trim(tarMask.value) : tarMask.value;

/*		if ($.type(tar.textFormat) == "function"){
			value = tar.textFormat(value);
			$(tar).val(value);
		};*/

		var returnResult = function(resultText, val){
			if (resultText === true){
				if (flag){
					$ip.trigger("ev_validatechange", [true, tar.tips]);
				};
				return true;
			}else{
				if (!resultText){
					resultText = tar.tips;
				};
				if (flag){
					$ip.trigger("ev_validatechange", [false, resultText]);
				};
				return false;
			};
		};

		if (tarIp && tarMask){
			//空白验证
			if (valueIp === "" || valueMask === ""){
				if (tar.allowBlank !== true){
					result = false;
					return returnResult(tar.blankText);
				}
			}else{
				//validator验证
				if (tar.validator){
					result = tar.validator(me.subnet("getValue"));
					if ($.type(result) !== "boolean"){
						//result = false;
						return returnResult(result);
					};
					if (result !== true){
						return returnResult(tar.invalidText);
					};
				}else{
                    result = new $.su.vtype({vtype:'ip'}).validate(valueIp);
					//console.log(valueIp)
					//对于该控件,0.0.0.0也是合法的输入，虽然也许是非法的IP。
					if (valueIp === "0.0.0.0" ){
						result=true
					}
					
                    if(result === true){
                        result = new $.su.vtype({vtype:'number', min:0, max: 32}).validate(valueMask);
                    }
                    if (result !== true){
                        return returnResult(tar.invalidText);
                    }
                }
			};

			return returnResult(true);
		};

		return result;
	},
	disable: function(me){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip'),
			container = me.closest(".widget-container");

		container.addClass("disabled");
		me.prop("disabled", true);
        $ip.prop("disabled", true);
        $mask.prop("disabled", true);
	

		return me;
	},
	enable: function(me){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip'),
			container = me.closest(".widget-container");

		container.removeClass("disabled");
		me.prop("disabled", false);
        $ip.prop("disabled", false);
        $mask.prop("disabled", false);
		
		return me;
	},
	setReadonly: function(me){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip'),
			container = me.subnet("getContainer");

		container.addClass("read-only");
		me.attr("readonly", 'readonly');
        $ip.attr("readonly", 'readonly');
        $mask.attr("readonly", 'readonly');
	

		return me;
	},
	removeReadonly: function(me){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip'),
			container = me.subnet("getContainer");

		container.removeClass("read-only");
		me.removeAttr("readonly");
        $ip.removeAttr("readonly");
        $mask.removeAttr("readonly");

        return me;
	},
	setTitle: function(me, _value){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip');

		if (_value){
			$ip.get(0).title = _value[1];
            $mask.get(0).title = _value[2];
		};
		
		return me;
	},
	setValue: function(me, _value){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip'),
			value = _value[1];


		me.attr("snapshot", value);
		if (value === "" || value === undefined || value === null || value.indexOf("/") == -1){
			me.val("");
            $mask.val("");
            $ip.val("");
		}else{
            var subnet = value.split("/");
			$ip.val(subnet[0]);
            $mask.val(subnet[1]);
            me.val(value);
		};

		return me;
	},
	getValue: function(me){
		var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip');

        me.val($ip.val()+"/"+$mask.val());
		return me.val();
	},
    reset: function(me){
        var me = me || this,
            $mask = me.subnet("getContainer").find('.text-subnet-mask'),
            $ip = me.subnet("getContainer").find('.text-subnet-ip');

        me.val("");
        $mask.val("");
        $ip.val("");
    },
	getContainer: function(me){
		var me = me || this;
		return me.closest("div.text-container");
	}
});

})(jQuery);