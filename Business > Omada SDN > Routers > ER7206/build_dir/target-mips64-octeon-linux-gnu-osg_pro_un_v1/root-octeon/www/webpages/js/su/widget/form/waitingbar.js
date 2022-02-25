// JavaScript Document
(function($){

$.su.Widget("waitingbar", {
	defaults: {
		text:"",
		fieldLabel: $.su.CHAR.ACCOUNT.WAIT,//"请稍后",
		timeout: 0,
		url: "",
		fn: null,	//function
		widgetName: "waitingbar",
		barWidth:370,
		barHeight:8,
		innerWidth:50,
		innerHeight:8,
		isRunning:false,
		interval:0
	},
	create: function(defaults, options){
		var me = this;
		me.each(function(i, obj){
			var tar = $(obj);
			$.extend(obj, defaults, options);			
			
			var	inHTML = 	"<div class=\"container widget-container progressbar-container progressbar " +obj.cls+"\">";

			if (obj.fieldLabel !== null){
				inHTML +=		"<div class=\"widget-fieldlabel-wrap "+obj.labelCls+"\">";
				inHTML +=			"<label class=\"widget-fieldlabel processbar-fieldlabel\">"+obj.fieldLabel+"</label>";
				inHTML +=		"</div>";
			};

				inHTML +=		"<div class=\"widget-wrap-outer progressbar-wrap-outer\" >";
				inHTML +=			"<div class=\"widget-wrap progressbar-wrap\">";
				inHTML +=				"<div class=\"widget-wrap progressbar-content\" style=\"width:"+ obj.barWidth + "px;height:" + obj.barHeight + "px;\">";
				inHTML +=					"<div class=\"progressbar-value\" style=\"width:"+ obj.innerWidth + "px;height:" + obj.innerHeight + "px;left:0;\"></div>"
				inHTML +=				"</div>";
				inHTML +=				"<div class=\"progressbar-text\">";

			if (obj.text != ""){
				inHTML +=					"<span class=\"progressbar-text\">" + obj.text + "</span>";
			};
						
				inHTML += 				"</div>";
				inHTML +=			"</div>";
				
			if (this.tips != null && this.tips != undefined){
				inHTML +=			"<div class=\"widget-tips textbox-tips "+obj.tipsCls+"\">";
				inHTML +=				"<div class=\"content tips-content\"></div>";
				inHTML +=			"</div>";
			};
				
				inHTML +=		"</div>";
				inHTML +=	"</div>";

			var container = $(inHTML);
			tar.replaceWith(container);
			container.append(tar.addClass("hidden"));
		});

		me.password("setTips", options.tips);
		return me;
	},
	run: function(me){
		var me = me || this,
			obj = me.get(0),
			container = me.closest("div.progressbar-container");

		var progressbarBox = container.find("div.progressbar-content"),
			progressbar = progressbarBox.children("div.progressbar-value"),
			percentageBox = container.find("span.progressbar-percentage");

		if(obj.isRunning){
			return me;
		}

		clearInterval(obj.interval);
		obj.interval = setInterval(function(){
			var currentLeft = progressbar.css("left").match(/\d*/);
			currentLeft = parseInt(currentLeft);
			if(currentLeft + obj.innerWidth + 1 <= obj.barWidth){
				progressbar.css("left", currentLeft + 1);
			}else{
				progressbar.css("left", 0);
			}
			
		}, 10);

		obj.isRunning = true;

		if(obj.timeout != 0){
			setTimeout(function(){
				me.waitingbar("stop");
				me.waitingbar("hide");
			}, obj.timeout);
		}

		return me;
	},
	reset: function(me){
		var me = me || this,
			obj = me.get(0),
			container = me.closest("div.progressbar-container");


		var progressbarBox = container.find("div.progressbar-content"),
			progressbar = progressbarBox.children("div.progressbar-value"),
			percentageBox = container.find("span.progressbar-percentage");



		progressbar.css("left", 0);

		if(!obj.isRunning){
			return me;
		}

		clearInterval(obj.interval);
		obj.interval = setInterval(function(){
			var currentLeft = progressbar.css("left").match(/\d*/);
			currentLeft = parseInt(currentLeft);
			if(currentLeft + obj.innerWidth + 1 <= obj.barWidth){
				progressbar.css("left", currentLeft + 1);
			}else{
				progressbar.css("left", 0);
			}
			
		}, 10);

		obj.isRunning = true;

		
		return me;
	},
	stop: function(me){
		var me = me || this,
			obj = me.get(0),
			container = me.closest("div.progressbar-container");


		var progressbarBox = container.find("div.progressbar-content"),
			progressbar = progressbarBox.children("div.progressbar-value"),
			percentageBox = container.find("span.progressbar-percentage");

		if(!obj.isRunning){
			return me;
		}

		clearInterval(obj.interval);

		obj.isRunning = false;

		return me;
	},
	
	hide: function(me){
		var me = me || this,
			container = me.closest("div.progressbar-container");
		container.css("display", "none");
		return me;
	},
	show: function(me){
		var me = me || this,
			container = me.closest("div.progressbar-container");
		container.fadeIn(150);
		return me;
	}
});


})(jQuery);