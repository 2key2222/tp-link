// JavaScript Document
(function($){
$.su.Widget("portrange", {
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
                inputStartPort = $('<input />'),
                inputEndPort = $('<input />');
			if (!input.is("input")){
				return null;
			};
			$.extend(this, defaults, options);
			
			var id = options.id || this.id || $.su.randomId("portrange"),
				value = options.value || input.val() || input.attr("value") || defaults.value,
				name = options.name || input.attr("name") || this.name || defaults.name;
			//重新初始化属性
            input.attr({
                name: name,
                id: id,
                value: value
            }).val(value).addClass("subnet-value hidden");

            inputStartPort.addClass("text-text text-sport-range "+this.inputCls);

            inputEndPort.addClass("text-text text-dport-range "+this.inputCls);
			
			if(this._maxLength){
				input.attr("maxlength", this._maxLength);
			};
            inputEndPort.attr("maxlength", 5);

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
                inHTML +=			"<span>&nbsp;—&nbsp;</span>";
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
			container.find("span.text-wrap:eq(0)").append(inputStartPort);
            container.find("span.text-wrap:eq(1)").append(inputEndPort);
            container.append(input);


			if (this.readOnly){
				container.addClass("read-only");
                inputStartPort.prop("readOnly", true);
                inputEndPort.prop("readOnly", true);
			};
		});

		
		var container = me.closest("div.widget-container");
		container.delegate("input.text-text", "click", function(e){
			e.stopPropagation();
		}).delegate("input.text-text", "focus", function(e){
			me.portrange("setFocus");
		}).delegate("input.text-text", "blur", function(e){
			me.portrange("removeFocus").portrange("validate");
		}).delegate("input.text-text", "keyup", function(e){
			me.trigger("ev_change", [me.portrange("getValue")]);
		}).delegate("input.text-text", "setValue", function(e){
			me.portrange("validate");
		}).delegate("input.text-text", "ev_validatechange", function(e, isvalid, tips){
			e.stopPropagation();
			if (isvalid){
				me.portrange("setValid");
			}else{
				me.portrange("setError", tips);
			}
		});



		me.portrange("setTips", options.tips);
		
		return me;
	},
	validate: function(me, flag){
		var me = me || this,
            $startPort = me.portrange("getContainer").find(".text-sport-range"),
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
			tar = me.get(0),
            tarStartPort = $startPort.get(0),
            tarEndPort = $endPort.get(0),
			flag = (flag[1] === false) ? false : true;

		var result = false,
			valueStartPort = tar.autoTrim ? $.trim(tarStartPort.value) : tarStartPort.value,
            valueEndPort = tar.autoTrim ? $.trim(tarEndPort.value) : tarEndPort.value;

/*		if ($.type(tar.textFormat) == "function"){
			value = tar.textFormat(value);
			$(tar).val(value);
		};*/

		var returnResult = function(resultText, val){
			if (resultText === true){
				if (flag){
					$startPort.trigger("ev_validatechange", [true, tar.tips]);
				};
				return true;
			}else{
				if (!resultText){
					resultText = tar.tips;
				};
				if (flag){
					$startPort.trigger("ev_validatechange", [false, resultText]);
				};
				return false;
			};
		};

		if (tarStartPort && tarEndPort){
			//空白验证
			if (valueStartPort === "" || valueEndPort === ""){
				if (tar.allowBlank !== true){
					result = false;
					return returnResult(tar.blankText);
				}
			}else{
				//validator验证
				if (tar.validator){
					result = tar.validator(me.portrange("getValue"));
					if ($.type(result) !== "boolean"){
						//result = false;
						return returnResult(result);
					};
					if (result !== true){
						return returnResult(tar.invalidText);
					};
				}else{
                    result = new $.su.vtype({vtype:'number', min:0, max: 65535}).validate(valueStartPort);
                    if(result === true){
						result = new $.su.vtype({vtype:'number', min:0, max: 65535}).validate(valueEndPort);
                    }
					if(parseInt(valueStartPort) > parseInt(valueEndPort))
					{
						result = false;
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
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range'),
			container = me.closest(".widget-container");

		container.addClass("disabled");
		me.prop("disabled", true);
        $startPort.prop("disabled", true);
        $endPort.prop("disabled", true);
	

		return me;
	},
	enable: function(me){
		var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range'),
			container = me.closest(".widget-container");

		container.removeClass("disabled");
		me.prop("disabled", false);
        $startPort.prop("disabled", false);
        $endPort.prop("disabled", false);
		
		return me;
	},
	setReadonly: function(me){
		var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range'),
			container = me.portrange("getContainer");

		container.addClass("read-only");
		me.attr("readonly", 'readonly');
        $startPort.attr("readonly", 'readonly');
        $endPort.attr("readonly", 'readonly');
	

		return me;
	},
	removeReadonly: function(me){
		var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range'),
			container = me.portrange("getContainer");

		container.removeClass("read-only");
		me.removeAttr("readonly");
        $startPort.removeAttr("readonly");
        $endPort.removeAttr("readonly");

        return me;
	},
	setTitle: function(me, _value){
		var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range');

		if (_value){
			$startPort.get(0).title = _value[1];
            $endPort.get(0).title = _value[2];
		};
		
		return me;
	},
	setValue: function(me, _value){
		var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range'),
			value = _value[1];


		me.attr("snapshot", value);
		if (value === "" || value === undefined || value === null || value.indexOf("-") == -1){
			me.val("");
            $endPort.val("");
            $startPort.val("");
		}else{
            var portrange = value.split("-");
			$startPort.val(portrange[0]);
            $endPort.val(portrange[1]);
            me.val(value);
		};

		return me;
	},
	getValue: function(me){
		var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range');

        me.val($startPort.val()+"-"+$endPort.val());
		return me.val();
	},
    reset: function(me){
        var me = me || this,
            $endPort = me.portrange("getContainer").find('.text-dport-range'),
            $startPort = me.portrange("getContainer").find('.text-sport-range');

        me.val("");
        $endPort.val("");
        $startPort.val("");
    },
	getContainer: function(me){
		var me = me || this;
		return me.closest("div.text-container");
	}
});

})(jQuery);