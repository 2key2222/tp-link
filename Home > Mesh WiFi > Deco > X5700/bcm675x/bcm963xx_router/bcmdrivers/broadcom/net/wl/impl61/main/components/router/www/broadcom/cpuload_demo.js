/*
 * Js implementation for cpu load demo page
 *
 * $ Copyright Open Broadcom Corporation $
 *
 *
 * <<Broadcom-WL-IPTag/Open:>>
 *
 * $Id: cpuload_demo.js 748614 2018-02-23 11:21:36Z pj888946 $
 */

var tx_radial;
var radial;
var cpumeter;
var mode = 1;// 1 means hw acceleration on
var output_data;
var timeout_cpuload = [];
var timeout_cpuload_val = 1000;
var TIMER_CPULOAD = 1 << 0;
var page_url;

function initPage()
{
	page_url = window.location.protocol + '//' + window.location.host +'/cpuload.cgi';
}

/* Clear all the timers */
function clearAllTimers(flag)
{
	if (flag & TIMER_CPULOAD) {
		for (i = 0; i < timeout_cpuload.length; i++) {
			clearTimeout(timeout_cpuload[i]);
		}
		timeout_cpuload = [];
	}
}

function loadFunction(){
	tx_radial = new RadialGauge({
		renderTo: 'canv-gauge-tx',
		width: 420,
		height: 420,
		units: 'Mbits/s',
		title: 'Wlan Tx',
		minValue: 0,
		maxValue: 3600,
		borders: true,
		majorTicks: [
		'0','200','400','600','800','1000','1200','1400','1600','1800','2000','2200','2400','2600','2800','3000','3200','3400','3600' 
		],
		minorTicks: 2,
		strokeTicks: false,
		highlights: [
		{ from: 0, to: 1200, color: 'rgba(255,0,0,.6)' },
		{ from: 1200, to: 2400, color: 'rgba(255,102,0,.8)' },
		{ from: 2400, to: 3600, color: 'rgba(40,100,0,1)' }
		],
		fontNumbersSize:14,
		colorPlate: '#333',
		colorMajorTicks: '#f5f5f5',
		colorMinorTicks: '#ddd',
		colorTitle: '#fff',
		colorUnits: '#ccc',
		colorNumbers: '#eee',
		colorNeedle: 'rgba(240, 128, 128, 1)',
		colorNeedleEnd: 'rgba(255, 160, 122, .9)',
		valueBox: true,
		valueTextShadow: true,
		animation: true,
		animationRule: 'linear',
		animationDuration: 700,
		animateOnInit: false,
		value: 0
	});

	radial = new RadialGauge({
		renderTo: 'canv-gauge',
		width: 420,
		height: 420,
		units: 'Mbits/s',
		title: 'Wlan Rx',
		minValue: 0,
		maxValue: 3600,
		borders: true,
		majorTicks: [
		'0','200','400','600','800','1000','1200','1400','1600','1800','2000','2200','2400','2600','2800','3000','3200','3400','3600'
		],
		minorTicks: 2,
		strokeTicks: false,
		highlights: [
		{ from: 0, to: 1200, color: 'rgba(255,0,0,.6)' },
		{ from: 1200, to: 2400, color: 'rgba(255,102,0,.8)' },
		{ from: 2400, to: 3600, color: 'rgba(40,100,0,1)' }
		],
		fontNumbersSize:14,
		colorPlate: '#333',
		colorMajorTicks: '#f5f5f5',
		colorMinorTicks: '#ddd',
		colorTitle: '#fff',
		colorUnits: '#ccc',
		colorNumbers: '#eee',
		colorNeedle: 'rgba(240, 128, 128, 1)',
		colorNeedleEnd: 'rgba(255, 160, 122, .9)',
		valueBox: true,
		valueTextShadow: true,
		animation: true,
		animationRule: 'linear',
		animationDuration: 700,
		animateOnInit: false,
		value: 0
	});


	cpumeter = new RadialGauge({
		renderTo: 'cpu-meter',
		width: 420,
		height: 420,
		units: 'Percentage',
		title: 'CPU Load',
		minValue: 0,
		maxValue: 100,
		borders: true,
		majorTicks: [
		'0','10','20','30','40','50','60','70','80','90','100'],
		minorTicks: 2,
		strokeTicks: false,
		highlights: [
		{ from: 0, to: 20, color: 'rgba(40,100,0,1)' },
		{ from: 20, to: 80, color: 'rgba(255,102,0,.8)' },
		{ from: 80, to: 100, color: 'rgba(255,0,0,.6)' },

		],
		fontNumbersSize:14,
		colorPlate: '#333',
		colorMajorTicks: '#f5f5f5',
		colorMinorTicks: '#ddd',
		colorTitle: '#fff',
		colorUnits: '#ccc',
		colorNumbers: '#eee',
		colorNeedle: 'rgba(240, 128, 128, 1)',
		colorNeedleEnd: 'rgba(255, 160, 122, .9)',
		valueBox: true,
		valueTextShadow: true,
		animation: true,
		animationRule: 'linear',
		animationDuration: 700,
		animateOnInit: false,
		animatedValue:true,
		valueInt:2,
		valueDec:0,
		value: 0
	});

	tx_radial.draw();
	radial.draw();
	cpumeter.draw();
};

function fetchCPULoadFromServer(request) {

	var array = [];

	$.ajax({
		type:'GET',
		url:page_url,
		data:request,
		async:true,
		success:function(result) {
			array = result;
			output_data = array;
			$(document).trigger("data-available", [output_data]);
		}
	});
	array = [];

}

function fetchCPULoad() {
	var request = {"Cmd" : "cpuLoad"};

	clearAllTimers(TIMER_CPULOAD);
	fetchCPULoadFromServer(request);
	timeout_cpuload.push(setTimeout(function(){ fetchCPULoad(); }, timeout_cpuload_val));
}

$(document).on("data-available", function(event, eventdata) {
	tx_radial.value = parseFloat(eventdata.TxTput);
	radial.value = parseFloat(eventdata.RxTput);
	cpumeter.value = parseFloat(eventdata.CpuLoad);
});

function getConfig()
{
        var array = [];
	var request = {"Cmd" : "getConfig"};

        $.ajax({
		type:'GET',
		url:page_url,
		data:request,
		async:true,
		success:function(result) {
			array = result;

			if (array.Timeout != undefined)
				timeout_cpuload_val = parseInt(array.Timeout) * 100;

			if (array.Mode != undefined)
				mode = parseInt(array.Mode);
		}
	});
	array = [];
}

function sendReq(req) {
        $.ajax({
		type:'GET',
		url:page_url,
		data:req,
		async:true,
		success:function(result) {
		}
	});
}

function setConfig(mode) {
	var request = {"Cmd" : "setConfig", "Mode" : mode};

	sendReq(request);
}

$(function() {
	$("#cfgbtn").click(function() {
		if (mode == 1) {
			$("#cfgbtn").html("HW Accel ON");
			$("#status").html("Status : H/W Accel OFF");
			mode = 0;
		} else {
			$("#cfgbtn").html("HW Accel OFF");
			$("#status").html("Status : H/W Accel ON");
			mode = 1;
		}

		setConfig(mode);
	});
});

$(document).ready(function() {
	clearAllTimers(TIMER_CPULOAD);
	initPage();
	getConfig();
	loadFunction();
	fetchCPULoad();
});
