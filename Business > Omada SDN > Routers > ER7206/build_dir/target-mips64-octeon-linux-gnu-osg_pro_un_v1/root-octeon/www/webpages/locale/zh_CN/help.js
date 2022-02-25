(function($){

    $.su = $.su || {};   $.su.CHAR = $.su.CHAR||{};
 $.su.CHAR.HELP ={
	 WIRELESS_BASIC:{
		 TITLE: "2.4G无线基本设置",
		 CONTENT:[{
			 type: "paragraph",
			 content: "您可以通过本页面设置2.4G无线功能的基本参数。"
		 },{
			 type:"name",
			 title:"无线功能",
			 content:"您可以勾选此项，选择是否开启2.4G无线功能。如果开启，接入本无线网络的主机将可以访问有线网络。"
		 },{
			 type:"name",
			 title:"信道",
			 content:"以无线信号作为传输媒体的数据信号传送的通道，选择范围从1到13。如果您选择的是自动，则AP会自动根据周围的环境选择一个最好的信道，WDS开启时无法配置。"
		 },{
			 type:"name",
			 title:"模式",
			 content:"选择不同的无线模式，无线路由器将选择不同的传输模式，如果所有与无线路由器连接的无线设备都使用同一种传输模式(例如802.11b)，可以选择only模式(例如11b only)，否则需要选择mixed模式，WDS开启时无法配置，当使用11n only或11bgn mixed无线模式时会自动启用<高级设置>页面的WMM功能。"
		 },{
			 type:"name",
			 title:"频段带宽",
			 content:"可以选择20M、40M和自动，WDS开启时无法配置。"
		 }
     ]},
     WIRELESS_BASIC_5G:{
         TITLE: "5G无线基本设置",
         CONTENT:[{
             type: "paragraph",
             content: "您可以通过本页面设置5G无线功能的基本参数。"
         },{
             type:"name",
             title:"无线功能",
             content:"您可以勾选此项，选择是否开启5G无线功能。如果开启，接入本无线网络的主机将可以访问有线网络。"
         },{
             type:"name",
             title:"信道",
             content:"以无线信号作为传输媒体的数据信号传送的通道，选择范围为36、40、44、48、149、153、157、161、165。如果您选择的是自动，则AP会自动根据周围的环境选择一个最好的信道，WDS开启时无法配置。"
         },{
             type:"name",
             title:"模式",
             content:"选择不同的无线模式，无线路由器将选择不同的传输模式，如果所有与无线路由器连接的无线设备都使用同一种传输模式(例如802.11a)，可以选择only模式(例如11a only)，否则需要选择mixed模式，WDS开启时无法配置，当使用11n only、11an mixed或11anac mixed无线模式时会自动启用<高级设置>页面的WMM功能。"
         },{
             type:"name",
             title:"频段带宽",
             content:"可以选择20M、40M、80M和自动，WDS开启时无法配置。"
         }
         ]},
     WIRELESS_BASIC_PARAM:{
         TITLE: "无线参数",
         CONTENT: [{
			 type:"name",
			 title:"SSID",
			 content:"无线局域网用于身份验证的登录名，只有通过身份验证的用户才可以访问本无线网络。"
		 },{
             type:"name",
             title:"描述",
             content:"您对该SSID的描述。"
         },{
			 type:"name",
			 title:"SSID广播",
			 content:"您可以勾选此项，选择是否开启SSID广播。如果开启，本无线路由器将向无线网络中的主机广播SSID。"
		 },{
			 type:"name",
			 title:"AP内部隔离",
			 content:"启用AP内部隔离，选择此项可以隔离关联到AP的各个无线站点。"
		 },{
			 type:"name",
			 title:"安全选项",
			 content:"设置该SSID的安全选项。",
			 children:[{
				 type: "step",
				 content:[
					 "关闭无线安全选项。",
					 "WPA-PSK/WPA2-PSK：基于共享密钥的WPA模式。",
					 "WPA/WPA2：用Radius服务器进行身份认证并得到密钥的WPA或WPA2模式。"
				 ]
			 }]
		 },{
			 type:"name",
			 title:"认证类型",
			 children:[{
				 type:"step",
				 content:[
					"自动选择：根据主机请求自动选择和安全选项类型使用哪种安全模式。",
			        "WPA-PSK：使用WPA-PSK的安全模式,对应安全选项为WPA-PSK/WPA2-PSK。",
			        "WPA2-PSK：使用WPA2-PSK的安全模式,对应安全选项为WPA-PSK/WPA2-PSK。",
			        "WPA：使用WPA的安全模式,对应安全选项为WPA/WPA2。",
			        "WPA2：使用WPA2的安全模式,对应安全选项为WPA/WPA2。"
			     ]
		     }]
		 },{
			 type:"name",
			 title:"加密算法",
			 content:"WPA或WPA-PSK的加密方式，包括自动选择、TKIP和AES。"
		 },{
			 type:"name",
			 title:"PSK密码",
			 content:"WPA-PSK的初始密码，由8-63个ASCII码字符或8-64个十六进制字符组成。"
		 },{
			 type:"name",
			 title:"组密钥更新周期",
			 content:"定时更新用于广播和组播的密钥的周期，以秒为单位，最小值为30，不更新则为0。"
		 },{
			 type:"name",
			 title:"Radius服务器IP",
			 content:"进行身份认证的Radius服务器的IP地址。"
		 },{
			 type:"name",
			 title:"Radius端口",
			 content:"Radius服务使用的端口。"
		 },{
			 type:"name",
			 title:"Radius密码",
			 content:"访问Radius服务的密码。"
		 }]
	 },
     WIRELESS_ADVANCED:{
         TITLE: "功能设置",
         CONTENT:[{
             type: "paragraph",
             content: "您可以通过本页面设置无线功能的高级参数。"
         },{
             type:"name",
             title:"WMM",
             content:"启用该选项将使路由器可以处理带有优先级信息的数据包，建议选择此选项。"
         },{
             type:"name",
             title:"发射功率",
             content:"设置路由器发射功率的大小。"
         },{
             type:"name",
             title:"Beacon时槽",
             content:"设置Beacon帧的发包间隔，可以设置为(40～1000)内的值，单位为毫秒(ms)，默认值为100。"
         }]
     },
     WIRELESS_MAC_FILTERING: {
         TITLE: "功能设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置，对MAC地址进行过滤。"
         },
         {
            type: "name",
            title: "作用域",
            content:"MAC过滤对选中的无线网络生效。"
         },
         {
             type: "name",
             title: "MAC地址过滤",
             content: "如果您勾选此项，可启用MAC地址过滤功能。MAC过滤有以下两种方式：",
             children:[{
                 type: "step",
                 content: ["允许规则列表中生效的MAC地址访问本无线网络：表示路由器将只允许MAC地址在过滤规则列表中的主机连接本无线网络。", "禁止规则列表中生效的MAC地址访问本无线网络：表示路由器将禁止MAC地址在过滤规则列表中的主机连接本无线网络。"]
             }]
         }]
     },
     WIRELESS_MAC_FILTERING_LIST: {
         TITLE: "MAC地址过滤规则",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看MAC地址过滤条目，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "MAC地址",
             content: "过滤的MAC地址。"
         },{
             type: "name",
             title: "备注",
             content: "您可以设置MAC地址过滤条目的备注，以方便您管理和查找。备注最多支持50个字符。"
         },{
             type: "note",
             title: "举例",
             content: "如果您想禁止MAC地址为00-00-11-11-11-F2的主机访问本无线网络，您可以添加MAC地址为00-00-11-11-11-F2的MAC过滤规则条目，点击<新增>。然后启用MAC地址过滤功能，选择禁止规则列表中生效的MAC地址访问本无线网络。"
         }]
     },
     WIRELESS_WDS: {
         TITLE: "功能设置",
         CONTENT: [{
             type: "paragraph",
             content: "通过WDS功能您可以桥接无线局域网。"
         },{
             type: "name",
             title: "WDS",
             content: "可以选择这一项启用WDS功能。"
         },{
             type: "name",
             title: "连接状态",
             content: "显示当前的连接状态。"
         },{
             type: "name",
             title: "(桥接的)SSID",
             content: "您要桥接的AP的SSID。"
         },{
             type: "name",
             title: "(桥接的)BSSID",
             content: "您要桥接的AP的BSSID。"
         },{
             type: "name",
             title: "扫描",
             content: "可以通过这个按钮扫描您路由器周围的无线局域网。"
         },{
             type: "name",
             title: "密钥类型",
             content: "这个选项需要根据您桥接的AP的加密类型来设定，注意：最好情况下应该保持这个加密方式和您AP设定的加密方式相同。"
         },{
             type: "name",
             title: "密钥",
             content: "根据您桥接的AP的密钥设置来设置该项。"
         },{
             type: "note",
             title: "注意",
             content: "如果您开启了WDS功能，Multi-SSID将不能使用。"
         }]
     },
     WIRELESS_MSSID: {
         TITLE: "功能设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面查看Multi-SSID设置的相关信息。"
         },{
             type: "name",
             title: "Multi-SSID",
             content: "您可以勾选此项，选择是否开启Multi-SSID功能。如果开启，路由器则可以建立多个无线局域网，启用后WDS功能将失效。"
         },{
             type: "name",
             title: "SSID间隔离",
             content: "您可以勾选此项，选择是否开启SSID间隔离功能。如果开启，连接在不同的SSID上的主机之间不能互相通信。"
         }]
     },
     WIRELESS_MSSID_LIST: {
         TITLE: "Multi-SSID设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看SSID条目，还可以通过表格按钮对条目进行操作。第一个是主SSID，不允许被删除或禁用。"
         },{
             type: "name",
             title: "SSID",
             content: "本无线网络服务用于身份验证的ID号，只有SSID相同的无线主机才可以访问本无线网络。"
         },{
             type: "name",
             title: "描述",
             content: "您对该SSID的描述。"
         },{
             type: "name",
             title: "SSID广播",
             content: "您可以勾选此项，选择是否开启SSID广播。如果开启，本无线路由器将向无线网络中的主机广播SSID。"
         },{
             type: "name",
             title: "AP内部隔离",
             content: "启用AP内部隔离，选择此项可以隔离关联到AP的各个无线站点。"
         },{
             type: "name",
             title: "访客网络",
             content: "您可以勾选此项，选择该SSID是否为访客网络。访客网络中的主机将不能与LAN口或其他SSID的主机通信。"   
         },{
             type: "name",
             title: "启用/禁用此SSID",
             content: "您可以勾选此项，选择是否开启此SSID。如果开启，路由器允许通过验证的主机连接到此SSID上，否则拒绝该主机的连接请求。"
         },{
             type:"name",
             title:"安全选项",
             content: "设置该SSID的安全选项。",
             children:[{
                 type:"step",
                 content:[
                     "关闭无线安全选项。",
                     "WPA-PSK/WPA2-PSK：基于共享密钥的WPA模式。",
                     "WPA/WPA2：用Radius服务器进行身份认证并得到密钥的WPA或WPA2模式。"
                 ]
             }]
         },{
             type:"name",
             title:"认证类型",
             children:[{
                 type:"step",
                 content:[
                     "自动选择：根据主机请求自动选择和安全选项类型使用哪种安全模式。",
                     "WPA-PSK：使用WPA-PSK的安全模式,对应安全选项为WPA-PSK/WPA2-PSK。",
                     "WPA2-PSK：使用WPA2-PSK的安全模式,对应安全选项为WPA-PSK/WPA2-PSK。",
                     "WPA：使用WPA的安全模式,对应安全选项为WPA/WPA2。",
                     "WPA2：使用WPA2的安全模式,对应安全选项为WPA/WPA2。"
                 ]
             }]
         },{
             type: "name",
             title: "加密算法",
             content: "WPA或WPA-PSK的加密方式，包括自动选择、TKIP和AES。"
         },{
             type: "name",
             title: "PSK密码",
             content: "WPA-PSK的初始密码，由8-63个ASCII码字符或8-64个十六进制字符组成。"
         },{
             type: "name",
             title: "组密钥更新周期",
             content: "定时更新用于广播和组播的密钥的周期，以秒为单位，最小值为30，不更新则为0。"
         },{
             type: "name",
             title: "Radius服务器IP",
             content: "进行身份认证的Radius服务器的IP地址。"
         },{
             type: "name",
             title: "Radius端口",
             content: "Radius服务使用的端口。"
         },{
             type: "name",
             title: "Radius密码",
             content: "访问Radius服务的密码。"
         }]
     },
     WIRELESS_HOST: {
         TITLE: "功能设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面查看所有通过无线连接到路由器的主机信息。"
         },{
             type: "name",
             title: "主机状态列表显示范围",
             content: "SSID名称。"
         }]
     },
     WIRELESS_HOST_STATUS: {
         TITLE: "主机状态",
         CONTENT: [{
             type: "name",
             title: "MAC地址",
             content: "通过无线连接到路由器的客户端主机的MAC地址。"
         },{
             type: "name",
             title: "所属SSID",
             content: "客户端主机所连接的无线SSID名称。"
         },{
             type: "name",
             title: "当前状态",
             content: "通过无线连接到路由器的连接状态。"
         },{
             type: "name",
             title: "发送总包数",
             content: "客户端主机到目前为止所发送的数据包数。"
         },{
             type: "name",
             title: "接收总包数",
             content: "客户端主机到目前为止所接收的数据包数。"
         },{
             type: "name",
             title: "发送总字节数",
             content: "客户端主机到目前为止所发送的字节数。"
         },{
             type: "name",
             title: "接收总字节数",
             content: "客户端主机到目前为止所接收的字节数。"
         },{
             type: "name",
             title: "上传速率",
             content: "客户端主机当前上传速率。"
         },{
             type: "name",
             title: "下载速率",
             content: "客户端主机当前下载速率。"
         }]
     },
     NAPT: {
         TITLE: "NAPT规则列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看选路规则，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "规则名称",
             content: "您可以设置规则条目名称。"
         },{
             type: "name",
             title: "出接口",
             content: "您可以选择规则生效的出接口。"
         },{
             type: "name",
             title: "源地址范围",
             content: "您可以选择规则生效的地址对象。"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择规则是否生效。"
         },{
             type: "name",
             title: "备注",
             content: "您可以设置条目的备注，以方便您管理和查找。"
         }]
     },

	ONE_NAT: {
         TITLE: "一对一NAT规则列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看规则条目，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "规则名称",
             content: "您可以设置规则条目名称。"
         },{
             type: "name",
             title: "出接口",
             content: "您可以选择规则生效的出接口。"
         },{
             type: "name",
             title: "映射前地址",
             content: "您可以选择规则生效的地址对象。映射前地址不能为各个接口的广播，网段和接口IP地址。"
         },{
             type: "name",
             title: "映射后地址",
             content: "您可以选择规则生效的地址对象。映射后地址不能为各个接口的广播，网段和接口IP地址。"
         },{
             type: "name",
             title: "DMZ转发",
             content: "您可以选择勾选\"启用\"来使DMZ转发功能生效，即将发送到映射后的地址的报文全部转发到映射前的地址主机。"
         },{
             type: "name",
             title: "备注",
             content: "您可以设置条目的备注，以方便您管理和查找。"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择规则是否生效。"
         }]
     },
	VIRTUAL_SERVER: {
         TITLE: "虚拟服务器规则列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看规则条目，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "规则名称",
             content: "您可以设置服务条目名称。"
         },{
             type: "name",
             title: "生效接口",
             content: "您可以选择规则生效的出接口。"
         },{
             type: "name",
             title: "外部端口",
             content: "路由器提供给广域网的服务端口（范围）。端口组之间不允许重叠。"
         },{
             type: "name",
             title: "内部端口",
             content: "局域网主机的服务端口。"
         },{
             type: "name",
             title: "内部服务器IP",
             content: "建立服务的局域网主机地址。"
         },{
             type: "name",
             title: "服务协议",
             content: "触发条目生效的协议类型。"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择规则是否生效。"
         }]
     },

	PORT_TRIGGERING: {
         TITLE: "触发列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看规则条目，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "接口",
             content: "您可以选择规则生效的出接口。"
         },{
             type: "name",
             title: "服务名称",
             content: "您可以设置端口触发条目的服务名称，以方便您管理和查找。"
         },{
             type: "name",
             title: "触发端口",
             content: "使开放端口生效的触发端口（范围）。触发端口最多允许5组，每个端口组可以为单个端口，可以为端口范围，但端口组之间不允许重叠。"
         },{
             type: "name",
             title: "触发协议",
             content: "触发端口被触发时所需要的协议。"
         },{
             type: "name",
             title: "开放端口",
             content: "开放的端口（范围）。开放端口最多允许5组，每个端口组可以为单个端口，可以为端口范围，但端口组之间不允许重叠。"
         },{
             type: "name",
             title: "开放协议",
             content: "开放端口所需要的协议。"
         },{
             type: "name",
             title: "启用/禁用",
             content: "您可以选择规则是否生效。"
         }]
     },

	ALG: {
         TITLE: "ALG服务",
         CONTENT: [{
             type: "paragraph",
             content: "为了适应NAT协议本身的特点，FTP、H.323、SIP、PPTP等特殊协议需要启用ALG才能正常工作。"
         },{
             type: "name",
             title: "FTP ALG",
             content: "您可以选择启用，使FTP服务正常运行。"
         },{
             type: "name",
             title: "H.323 ALG",
             content: "您可以选择启用，使H.323服务正常运行。"
         },{
             type: "name",
             title: "PPTP ALG",
             content: "您可以选择启用，使PPTP服务正常运行。"
         },{
             type: "name",
             title: "SIP ALG",
             content: "您可以选择启用，使SIP服务正常运行。"
         }]
     },

	NAT_DMZ: {
         TITLE: "NAT-DMZ规则列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看规则条目，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "规则名称",
             content: "您可以设置条目的规则名称，以方便您管理和查找。"
         },{
             type: "name",
             title: "出接口",
             content: "您可以选择规则生效的出接口。"
         },{
             type: "name",
             title: "主机地址",
             content: "NAT DMZ服务指向的主机地址。"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择规则是否生效。"
         }]
     },
     IPSEC_TUNNEL_SETTING: {
         TITLE: "IPSec安全策略设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置IPSec安全策略，安全策略规定了对什么样的数据流采用什么样的安全提议。安全策略设置分为必要设置和高级设置两个部分，其中高级设置是可选部分。"
         },
		 {
             type: "paragraph",
			 title:"必要设置",
			 content:"对于新建的安全策略，必要设置是必须提供的，不能省略。"
         },
		 {
             type: "name",
             title: "安全策略名称",
             content: "设置IPSec安全策略的名称，名称最多支持32个字符。"
         },
         {
             type: "name",
             title: "对端网关",
             content: "设置对端网关，可以填写对端的IP地址或域名，作为响应者的时候可以将对端网关设为“0.0.0.0”,表示对端地址可以任意。"
         },
		 {
             type: "name",
             title: "绑定接口",
             content: "从下拉列表中指定本地使用的WAN口；对端网关设置的\"对端网关地址\"必须与该WAN口的IP地址相同。"
         },
		 {
             type: "name",
             title: "本地子网范围",
             content: "设置受保护的数据流的本地子网范围，由IP地址和子网掩码来确定。"
         },
		 {
             type: "name",
             title: "对端子网范围",
             content: "设置受保护的数据流的对端子网范围，由IP地址和子网掩码来确定。"
         },
		 
		 
		 {
             type: "name",
             title: "预共享密钥",
             content: "对于每对<绑定接口，对端网关>，都必须指定唯一的预共享密钥作为它们之间相互认证的凭证。"
         },
         {
             type: "name",
             title: "状态",
             content: "设置勾选启用时，当前策略生效。"
         },
		 {
             type: "paragraph",
			 title:"高级设置",
             content: "高级设置包括两个部分：阶段1设置和阶段2设置。一般地，用户不需要配置高级设置，采用默认值即可。"
         },
		 {
             type: "name",
			 title:"高级设置-阶段1设置",
             content: "设定IKEv1的第一阶段的相关参数"
         },
		 {
             type: "name",
             title: "安全提议",
             content: "用于IKE协商方式下选择IPSec安全提议，在IKE协商模式下可以最多选择四条不同安全提议，主模式协商可以选择4条，野蛮模式协商可以选择1条。"
         },
		 {
             type: "name",
             title: "交换模式",
             content: "IKEv1版本支持两种模式：主模式和野蛮模式，默认是选择主模式。"
         },
		 {
             type: "name",
             title: "协商模式",
             content: "初始者模式会主动向对端发起连接，此时要求对端网关是路由可达，而响应者模式仅仅会等待对端发起连接。"
         },
         {
             type: "name",
             title: "本地ID类型",
             content: "作为对端的身份标识，支持两种类型：IP地址和NAME，默认选择\"IP地址\",如果选择NAME类型，则需要输入任意的字符串。"
         },
		 {
             type: "name",
             title: "本地ID",
             content: "仅仅在本地ID类型选择NAME的时候生效，用于存储用户输入对应的字符串。"
         },
		 {
             type: "name",
             title: "对端ID类型",
             content: "作为对端的身份标识，支持两种类型：IP地址和NAME，默认选择\"IP地址\",如果选择NAME类型，则需要输入任意的字符串。"
         },
		 {
             type: "name",
             title: "对端ID",
             content: "仅仅在对端ID类型选择NAME的时候生效，用于存储用户输入对应的字符串。"
         },
		 {
             type: "name",
             title: "生存时间",
             content: "用于IKE协商方式下设置第一阶段IPSec会话密钥的生存时间。"
         },
		 {
             type: "name",
             title: "DPD检测开启",
             content: "选择是否开启DPD检测功能，开启该功能会定时发送DPD数据包以快速发现对端是否在线。"
         },
		 {
             type: "name",
             title: "DPD检测周期",
             content: "仅在DPD检测开启启用之后生效，用于指定相邻两次发送DPD检测数据包的时间间隔。"
         },

		 {
             type: "name",
             title: "高级设置-阶段2设置",
             content: "设定IKEv1的第二阶段的相关参数"
         },
         {
             type: "name",
             title: "封装模式",
             content: "指定该策略是隧道模式还是传输模式，两者的区别在于：前者会在原始IP报文外多增加一个IP头，后者则不会。"
         },
		 {
             type: "name",
             title: "安全提议",
             content: "用于IKE协商方式下选择IPSec安全提议，在IKE协商模式下可以最多选择四条不同安全提议。"
         },
		 
		 {
             type: "name",
             title: "PFS",
             content: "用于IKE协商方式下设置IPSec会话密钥的PFS属性，对端的PFS属性必须与本地的PFS属性一致。"
         },
		 {
             type: "name",
             title: "生存时间",
             content: "用于IKE协商方式下设置第二阶段IPSec会话密钥的生存时间。"
         }
		 ]
     },

     IPSEC_TUNNEL_LISTS: {
         TITLE: "IPSec安全策略列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看已经配置的IPSec安全策略条目，还可以通过表格按钮对条目进行操作。"
         }]
     },

     IPSEC_SA: {
         TITLE: "IPSec安全联盟列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面查看当前建立的安全联盟。"
         },
		 {
             type: "name",
             title: "名称",
             content: "显示安全联盟的名称，一般地，该名称和安全策略名称相同。"
         },
		 {
             type: "name",
             title: "SPI",
             content: "显示安全联盟的SPI（Security Parameter Index，安全性参数索引），注意每一个安全联盟的SPI都不相同。"
         },
		 {
             type: "name",
             title: "方向",
             content: "显示安全联盟的方向（in:流入/out:流出）。"
         },
		 {
             type: "name",
             title: "隧道两端",
             content: "显示安全联盟的两端的网关地址。"
         },
		 {
             type: "name",
             title: "数据流",
             content: "显示安全联盟的两端的子网范围。"
         }	,
		 {
             type: "name",
             title: "安全协议",
             content: "显示安全联盟使用的安全协议。"
         }	,
		 {
             type: "name",
             title: "AH验证算法",
             content: "显示安全联盟使用的AH验证算法。"
         }	,
		 {
             type: "name",
             title: "ESP验证算法",
             content: "显示安全联盟使用的ESP验证算法。"
         }	,
		 {
             type: "name",
             title: "ESP加密算法",
             content: "显示安全联盟使用的ESP加密算法。"
         }
		 ]
     },


	IMB_ENABLE:{
        TITLE:"功能设置",
        CONTENT:[{
            type:"name",
            title:"ARP防欺骗功能",
            content:"启用或关闭ARP的防欺骗功能。若关闭，防ARP欺骗，IP-MAC，ARP功能等功能都不会生效"
        },{
            type:"name",
            title:"仅允许IP-MAC绑定的数据包通过",
            content:"开启该功能，则路由器只会放过在IP-MAC绑定规则中的数据包。<br>注意，要开启该功能，需要先开启ARP防欺骗功能"
        },{
            type:"name",
            title:"允许路由器在发现ARP攻击时发送GARP包",
            content:"开启该功能，路由器收到与IP-MAC绑定列表中不一致的报文时，会发送GARP。<br>注意，要开启该功能，需要先开启ARP防欺骗功能"
        }]
    },

    IMB_IMPORT:{
        TITLE:"导入到静态地址分配列表",
        CONTENT:[{
            type:"name",
            title:"导入",
            content:"点击导入将列表中勾选的IP-MAC绑定条目导入到静态地址分配列表，您可以在 基本设置-LAN设置-静态地址分配 中查看。"
        }]
    },

    IMB_LIST:{
        TITLE:"IP-MAC绑定规则列表",
        CONTENT:[{
        type:"paragraph",
        content:"您可以查看IP-MAC绑定规则，还可以通过表格按钮对条目进行操作。"},
        {
            type:"name",
            title:"IP地址",
            content:"您可以输入待绑定的IP地址"
        },
        {
            type:"name",
            title:"MAC地址",
            content:"您可以输入待绑定的MAC地址，格式为xx-xx-xx-xx-xx-xx"
        },{
            type:"name",
            title:"生效域",
            content:"您可以选择生效的接口"
        }]
    },

     MAC_FILTERING_SETTING: {
         TITLE: "功能设置",
         CONTENT: [{
             type: "name",
             title: "MAC地址过滤",
             content: "可启用或关闭MAC地址过滤功能。"
         },{
             type: "name",
             title: "过滤模式",
             content: "仅允许规则列表的MAC地址访问外网：表示路由器将只允许源MAC地址在过滤规则列表中的数据帧通过。<br>仅禁止规则列表的MAC地址访问外网：表示路由器将禁止源MAC地址在过滤规则列表中的数据帧通过。"
         },{
             type: "step",
             title: "举例：禁止LAN网段上MAC地址为 00-00-11-11-11-F2 的主机访问外网",
             content: [
                 "1、点击<增加>添加MAC地址为00-00-11-11-11-F2的MAC过滤规则条目。",
                 "2、启用MAC地址过滤功能。",
                 "3、选择仅禁止规则列表的MAC地址访问外网。"
             ]
         }]
     },

     MAC_FILTERING_LIST: {
         TITLE: "MAC过滤规则列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以查看MAC地址过滤条目，还可以通过表格按钮对条目进行操作。"
         },{
             type: "name",
             title: "名称",
             content: "您可以设置规则的名称。"
         },{
             type: "name",
             title: "MAC地址",
             content: "过滤的MAC地址，格式为xx-xx-xx-xx-xx-xx。"
         }]
     },

     ARPSCAN_SCAN:{
        TITLE:"ARP扫描",
        CONTENT:[{
            type:"name",
            title:"扫描范围",
            content:"输入扫描的IP地址范围，路由器会对该范围的IP地址进行ARP查询。"
        },{
            type:"name",
            title:"导入IP-MAC绑定",
            content:"您可以将扫描结果中的IP-MAC对导入IP-MAC绑定页面中"
        },{
            type:"name",
            title:"扫描结果",
            content:"扫描结束后，扫描得到的结果会出现在这个列表中"
        }]
     },

     ARPLIST_SCAN:{
        TITLE:"ARP列表",
        CONTENT:[{
            type:"name",
            title:"导入IP-MAC绑定",
            content:"您可以将ARP列表中的IP-MAC对导入到IP-MAC绑定页面中"
        },{
            type:"name",
            title:"ARP列表",
            content:"路由器会将系统中的ARP列表展现在此列表中"
        }]
     },

    /* DEFENSE_ENABLE:{
        TITLE:"全局设置",
        CONTENT:[{
            type:"name",
            title:"启用防护攻击日志",
            content:"开启或者关闭攻击防护的日志"
        }]
     },*/

     DEFENSE_FLOOD:{
        TITLE:"防Flood类攻击",
        CONTENT:[{
          type:"name",
          title:"启用防多连接的TCP SYN Flood攻击",
          content:"开启TCP的连接限制，将TCP连接限制在给定值"
        },{
            type:"name",
            title:"启用防多连接的UDP Flood攻击",
            content:"开启UDP的连接限制，将UDP连接限制在给定值"
        },{
            type:"name",
            title:"启用防多连接的ICMP Flood攻击",
            content:"开启ICMP的连接限制，将ICMP连接限制在给定值"
        },{
            type:"name",
            title:"启用防固定源的TCP SYN Flood攻击",
            content:"将某个IP的TCP的连接限制在给定值之内"
        },{
            type:"name",
            title:"启用防固定源的UDP Flood攻击",
            content:"将某个IP的UDP的连接限制在给定值之内"
        },{
            type:"name",
            title:"启用防固定源的ICMP Flood攻击",
            content:"将某个IP的ICMP的连接限制在给定值之内"
        }]
     },

     DEFENSE_DOS:{
        TITLE:"防可疑包攻击",
        CONTENT:[{
            type:"name",
            title:"启用防碎片包攻击",
            content:"开启该功能，路由器会过滤掉碎片包"
        },{
            type:"name",
            title:"启用防TCP Scan(Strealth FIN/Xmas/Null)",
            content:"开启该功能，路由器会过滤掉三种工具的tcp scan包"
        },{
            type:"name",
            title:"启用防ping of Death",
            content:"开启该功能，路由器会过滤掉异常的ping包"
        },{
            type:"name",
            title:"启用防Large Ping",
            content:"开启该功能，路由器会过滤掉大ping包"
        },{
            type:"name",
            title:"启用WinNuke攻击",
            content:"开启该功能，防止winNuke攻击"
        },
        {
            type:"name",
            title:"阻止同时设置FIN和SYN的TCP包",
            content:"开启该功能，路由器会过滤掉同时包含FIN和SYN的TCP报文"
        },{
            type:"name",
            title:"阻止仅设置FIN未设置ACK的TCP包",
            content:"开启该功能，路由器会过滤掉设置了FIN未设置ACK的TCP报文"
        },{
            type:"name",
            title:"阻止带选项的包",
            content:"开启该功能，路由器会过滤掉设置某些IP选项中的报文"
        }]
     },

     ACL_LIST:{
        TITLE:"访问控制列表",
        CONTENT:[{
            type:"name",
            title:"规则名称",
            content:"为添加的规则命名，字符数限制在50个字符以内，且任意两条规则不能重名"
        },{
            type:"name",
            title:"策略类型",
            content:"指明这条规则对符合条件的数据包放行还是丢弃"
        },{
            type:"name",
            title:"服务类型",
            content:"选择生效的协议，ALL表示所有协议"
        },{
            type:"name",
            title:"生效接口域",
            content:"在路由器接口中选择生效的接口，ALL表示所有的接口"
        },{
            type:"name",
            title:"源地址范围",
            content:"选择地址对象，以建立访问规则条目的源地址范围"
        },{
            type:"name",
            title:"目的地址范围",
            content:"选择地址对象，以建立访问规则条目的目的地址范围"
        },{
            type:"name",
            title:"生效时间",
            content:"选择规则生效的时间"
        },{
            type:"name",
            title:"添加到指定位置(第几条)",
            content:"指定添加的规则的位置，排在前面的规则比后面规则优先级高"
        }]
     },

     WEB_GROUP:{
        TITLE:"网站分组",
        CONTENT:[{
            type:"name",
            title:"组名称",
            content:"为网站分组添加名称，字符限制在28个字符以内，且两个分组不能重名"
        },{
            type:"name",
            title:"组成员",
            content:"网站分组成员，您可以同时输入多个网站进行批量添加。<br>组成员可以为域名，如www.tp-link.com.cn,也可以在域名前面加通配符'*'，如*.tp-link.com.cn。但是'*'只允许输入在最前面，而不能夹杂在域名中间或后面。"
        },
        {
            type:"name",
            title:"清空",
            content:"您可以清空组成员中输入的内容"
        },
        {
            type:"name",
            title:"文件路径",
            content:"您可以通过文件导入的形式为网站分组添加成员，文件格式为txt格式"
        },{
            type:"name",
            title:"备注",
            content:"您可以为分组添加50字符以内的备注"
        }]
     },

     WEB_FILTER_ENABLE:{
        TITLE:"功能设置",
        CONTENT:[{
            type:"name",
            title:"启用网站过滤功能",
            content:"您可以选择开启或关闭网站过滤功能"
        }]
     },

     WEB_FILTER:{
        TITLE:"规则列表",
        CONTENT:[{
            type:"name",
            title:"受控地址组",
            content:"选择地址对象，以建立过滤规则条目的地址范围"
        },{
            type:"name",
            title:"规则类型",
            content:"对符合规则的网站放行或禁止"
        },{
            type:"name",
            title:"选择网站",
            content:"选择网站分组对象，其中所有网站表示对所有网站都生效"
        },{
            type:"name",
            title:"规则生效时间",
            content:"选择规则生效的时间"
        },{
            type:"name",
            title:"备注",
            content:"您可以为该规则添加备注，50字符以内"
        },{
            type:"name",
            title:"添加到指定位置(第几条)",
            content:"指定添加的规则的位置，排在前面的规则比后面规则优先级高"
        },{
            type:"name",
            title:"状态",
            content:"表示是否启用该规则"
        }]
     },

     URLFILTER_ENABLE:{
        TITLE:"全局设置",
        CONTENT:[{
            type:"name",
            title:"启用URL过滤功能",
            content:"您可以选择是否开启URL过滤功能"
        }]
     },

 URLFILTER_LIST:{
        TITLE:"URL过滤规则列表",
        CONTENT:[{
            type:"name",
            title:"受控地址组",
            content:"选择地址对象，以建立过滤规则条目的地址范围"
        },{
            type:"name",
            title:"策略类型",
            content:"对符合规则的网址放行或禁止"
        },{
            type:"name",
            title:"过滤方式",
            content:"关键字为部分匹配，完整URL表示完全匹配"
        },{
            type:"name",
            title:"过滤内容列表",
            content:"填写需要过滤的内容。其中单独符号.表示任意URL，也就是与任意URL匹配。<br>.规则只能配置一条，表示对任意的URL禁止或者允许，并且该规则只能在规则列表最后面"
        },{
            type:"name",
            title:"生效时间",
            content:"选择规则生效的时间"
        },
        {
            type:"name",
            title:"状态",
            content:"表示是否启用该规则"
        },{
            type:"name",
            title:"备注",
            content:"您可以为该规则添加备注，50字符以内"
        },{
            type:"name",
            title:"添加到指定位置(第几条)",
            content:"指定添加的规则的位置，排在前面的规则比后面规则优先级高"
        }]
     },

     WEBSEC_ENABLE:{
        TITLE:"功能设置",
        CONTENT:[{
            type:"name",
            title:"启用网页安全功能",
            content:"您可以开启或关闭网页安全功能"
        }]
     },

     WEBSEC_SETTING:{
        TITLE:"规则列表",
        CONTENT:[{
            type:"name",
            title:"受控地址组",
            content:"选择地址对象，以建立网页安全规则条目的地址范围"
        },{
            type:"name",
            title:"禁止网页提交",
            content:"是否开启禁止网页提交功能"
        },{
            type:"name",
            title:"过滤文件拓展类型",
            content:"添加待过滤的文件后缀，各个后缀之间以换行隔开"
        },{
            type:"name",
            title:"生效时间",
            content:"选择规则生效的时间"
        },{
            type:"name",
            title:"备注",
            content:"您可以为该规则添加备注，50字符以内"
        },{
             type:"name",
            title:"状态",
            content:"表示是否启用该规则"
        }]
     },

     ISP_ROUTING_SETTING:{
        TITLE: "ISP选路",
        CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置进行ISP选路设置，导入ISP数据库。"
        },
        {
             type: "name",
             title: "启用ISP地址段选路功能",
             content: "选中<启用ISP地址段选路功能>，将根据ISP进行选路。"
        }]
     },
     ISP_IMPORT:{
        TITLE: "导入ISP数据库",
        CONTENT: [{
             type: "name",
             title: "导入",
             content: "可以导入ISP数据库对系统预设的ISP选路进行升级。"
        }]
     },

     ISP_USER_DEFINE_HELP:{
        TITLE: "用户自定义数据库",
        CONTENT: [
        {
             type: "name",
             title: "导入",
             content: "自定义数据库文件格式为每行由“IP/mask”组成，如“12.12.12.12/24”，总个数不超过2048条。文件格式为txt格式。"
        }]
     },

     ISP_ROUTING_LIST:{
        TITLE: "选路列表",
        CONTENT: [{
             type: "paragraph",
             content: "您可以查看选路条目，还可以通过表格按钮对条目进行操作。"
        },
        {
             type: "name",
             title: "接口",
             content: "选择ISP选路的出接口。"
         },
        {
             type: "name",
             title: "ISP",
             content: "选择ISP（Internet Service Provider，网络服务提供商）。"
         }]
     },
    LINE_BACKUP_SETTING:{
        TITLE: "线路备份",
        CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置，对线路数据进行备份。"
        },
        {
             type: "name",
             title: "主接口",
             content: "您可以选择一个接口作为主接口。"
        },
        {
             type: "name",
             title: "备接口",
             content: "您可以选择一个接口作为备用接口用来备份主接口的流量。"
         },
         {
             type: "name",
             title: "备份模式",
             content: "您可以选择定时备份或故障备份。"
         },
         {
             type: "name",
             title: "生效时间",
             content: "您可以选择规则备份生效时间。"
         },
         {
             type: "name",
             title: "状态",
             content: "您可以选择备份策略是否生效。"
         }
         ]
     },
     LINE_BACKUP_LIST:{
        TITLE: "主备组列表",
        CONTENT: [{
             type: "paragraph",
             content: "您可以查看备份策略，还可以通过表格按钮对条目进行操作。"
        }]
     },
    BALANCE_GLOBAL_SETTING:{
        TITLE: "全局设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以在本页面进行流量均衡的基本设置。"
        },
        {
             type: "name",
             title: "启用流量均衡",
             content: "流量均衡的全局开关，勾选以启用流量均衡功能。"
        }]
    },
    BALANCE_BASIC_SETTING:{
        TITLE: "功能设置",
        CONTENT: [
        {
             type: "name",
             title: "启用特殊应用程序选路功能",
             content: "选中<启用特殊应用程序选路功能>，路由器将把属于同一个网络应用的多条连接通过同一个出接口转发，避免多出接口下由于该应用的多条连接通过不同出接口转发导致应用异常的问题。例如某内网主机访问某外网服务器，启用特殊应用程序选路后，可以保证该内网主机发往服务器的所有数据通过同一个出接口转发，避免因流量均衡导致数据通过多个出接口转发而引起服务异常。"
        },
        {
             type: "name",
             title: "启用智能均衡",
             content: "您可以在复选框中选择需要启用智能均衡的接口。"
         }
         ]
     },
     ONLINE_SETTING: {
        TITLE: "在线检测",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置不同的检测方式，并查看路由器接口是否已经连接外网。"
        },
        {
            type: "name",
            title: "接口名",
            content: "进行在线检测的接口。对所有WAN口以及参与流量均衡的接口，均会进行在线检测。"
        },
        {
            type: "name",
            title: "自动模式",
            content: "自动模式通过使用在设置接口时设置的DNS服务器进行DNS检测判断是否连接外网。"
        },
        {
            type: "name",
            title: "手动模式",
            content: "手动模式通过使用在本页面上手动设置的DNS服务器和IP地址进行DNS检测和PING检测判断是否连接外网。"
        },
        {
            type: "name",
            title: "永远在线",
            content: "永远在线模式不进行检测，而在页面上永远显示为在线状态。"
        },
        {
            type: "name",
            title: "PING检测",
            content: "您可以指定一个IP地址，让对应的接口去ping这个地址，从而判断是否连接外网，只能在手动模式下设置。"
        },
        {
            type: "name",
            title: "DNS检测",
            content: "您可以指定一个DNS服务器的IP地址，让对应的接口通过这个DNS服务器使用默认的域名进行DNS查询，从而判断是否连接外网，只能在手动模式下中设置。"
        }
        ]
     },
    POLICY_ROUTING_SETTING:{
        TITLE: "策略路由",
        CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置，对数据包出接口进行选择。"
        }
         ]
     },
    POLICY_ROUTING_LIST:{
        TITLE: "规则列表",
        CONTENT: [{
             type: "paragraph",
             content: "您可以查看选路规则，还可以通过表格按钮对条目进行操作。"
        },
        {
             type: "name",
             title: "策略名称",
             content: "您可以设置策略选路规则条目名称。"
         },
          {
             type: "name",
             title: "服务类型",
             content: "您可以选择服务类型，以建立选路规则条目的协议、源端口范围（协议为TCP、UDP、TCP/UDP）、目的端口范围（协议为TCP、UDP、TCP/UDP）。"
         },
          {
             type: "name",
             title: "源地址",
             content: "您可以选择地址对象，以建立选路规则条目的源地址范围。"
         },
          {
             type: "name",
             title: "目的地址",
             content: "您可以选择地址对象，以建立选路规则条目的目的地址范围。"
         },
          {
             type: "name",
             title: "生效接口",
             content: "您可以选择符合此选路规则条目数据包的出接口。"
         },
          {
             type: "name",
             title: "生效时间",
             content: "您可以选择规则生效时间。"
         },
          {
             type: "name",
             title: "备注",
             content: "您可以设置条目的备注，以方便您管理和查找。"
         },
          {
             type: "name",
             title: "状态",
             content: "您可以选择规则是否生效。"
         }
        ]
     },

    ADVANCED_ROUTING_STATIC_ROUTING:{
        TITLE: "静态路由规则",
        CONTENT: [
            {
                 type: "paragraph",
                 content: "您可以通过本页面设置静态路由条目。当数据包与静态路由匹配成功时，将按照指定的转发方式进行转发。"
            },
            {
                 type: "name",
                 title: "名称",
                 content: "路由条目的名称，不能和已有的路由条目名称重复。"
            },
            {
                 type: "name",
                 title: "目的地址",
                 content: "数据包需要到达的地址。"
            },
            {
                 type: "name",
                 title: "子网掩码",
                 content: "目的地址的子网掩码。"
            },
            {
                 type: "name",
                 title: "下一跳",
                 content: "数据包将发往的下一个路由点。"
            },
            {
                 type: "name",
                 title: "出接口",
                 content: "数据包进行转发的接口。"
            },
            {
                 type: "name",
                 title: "metric",
                 content: "路由条目的优先级，其数值越低优先级越高。默认值为0，一般不需要修改。"
            },
            {
                 type: "name",
                 title: "备注",
                 content: "您可以设置静态路由条目备注，以方便您管理和查找。备注最多支持50个字符。"
            },
            {
                 type: "name",
                 title: "启用/禁用规则",
                 content: "设置路由条目生效或不生效。"
            }
         ]
     },
    ADVANCED_ROUTING_STATIC_RULE:{
        TITLE: "规则列表",
        CONTENT: [{
             type: "paragraph",
             content: "您可以查看路由条目，还可以通过表格按钮对条目进行操作。"
        }
         ]
     },
     ADVANCED_ROUTING_SYSTEM_ROUTING_TABLE:{
        TITLE: "系统路由表",
        CONTENT: [
            {
                 type: "paragraph",
                 content: "您可以通过本页面查看系统路由表。"
            },
            {
                 type: "name",
                 title: "目的地址",
                 content: "数据包需要到达的地址。"
            },
            {
                 type: "name",
                 title: "子网掩码",
                 content: "目的地址的子网掩码。"
            },
            {
                 type: "name",
                 title: "下一跳",
                 content: "数据包到达目的地址前可以直接转发的下一个路由器地址。"
            },
            {
                 type: "name",
                 title: "出接口",
                 content: "数据包进行转发的接口。"
            },
            {
                 type: "name",
                 title: "metric",
                 content: "数据包到达目的需要的跳数。"
            }
        ]
     },
    QOS_SETTING:{
        TITLE: "功能设置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以全局开启或关闭带宽控制功能，或设置为仅当带宽利用率达到一定值以上才开启带宽控制功能"
        },
        {
            type: "name",
            title: "启用带宽控制",
            content: "您可以全局开启或关闭带宽控制功能"
        },
        {
            type: "name",
            title: "带宽利用率条件",
            content: "在全局开启带宽控制功能的情况下，您可以设置一个百分比值，仅当带宽利用率高于这个值，带宽控制功能才会开启"
        }]
    },
    QOS_LIST:{
        TITLE: "带宽控制规则列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以查看带宽控制的用户规则，还可以通过表格按钮对每条规则进行操作。"
        },
        {
            type: "name",
            title: "规则名称",
            content: "您可以设置带宽控制规则的条目名称。"
        },
        {
            type: "name",
            title: "数据流向",
            content: "您可以选择规则控制的数据流向。"
        },
        {
            type: "name",
            title: "受控地址组",
            content: "您可以选择IP地址组对象，以建立规则条目作用的LAN地址范围。"
        },
        {
            type: "name",
            title: "最大上行带宽",
            content: "您可以选择规则定义的数据流的最大上行带宽（单位为 Kbps）。"
        },
        {
            type: "name",
            title: "最大下行带宽",
            content: "您可以选择规则定义的数据流的最大下行带宽（单位为 Kbps）。"
        },
        {
            type: "name",
            title: "带宽模式",
            content: "您可以设置地址组的带宽控制模式：共享表示地址组内IP共用带宽；独立表示地址组内IP独占带宽。"
        },
        {
            type: "name",
            title: "生效时间",
            content: "您可以选择规则生效的时间，Any表示立即生效。"
        },
        {
            type: "name",
            title: "备注",
            content: "您可以为规则创建描述信息，以便于记忆。"
        },
        {
            type: "name",
            title: "添加到指定位置",
            content: "您可以将规则设置到指定的位置，从而配置规则的优先级。"
        },
        {
            type: "name",
            title: "状态",
            content: "您可以选择此规则是否启用"
        }]
    },
     IPGROUP_ADDRESS_SETTING: {
        TITLE: "地址列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置地址对象，进行地址对象的管理。"
        },
        {
            type: "name",
            title: "地址名称",
            content: "标志地址的名称。"
        },
        {
            type: "name",
            title: "IP类型",
            content: "用于设置地址对象的类型，不同类型计算得到IP集合的方式不同，有下面两种类型：",
             children:[{
                 type:"step",
                 content:[
                    "IP段：设置一个起始地址和一个结束地址，引用包含该地址对象地址组的规则在该地址段内均会生效。",
                    "IP/MASK：设置一个网络标识和一个子网掩码，得到IP网段，引用包含该地址对象地址组的规则在该网段内均会生效。"
                 ]
             }]
        },
        {
            type: "name",
            title: "备注",
            content: "您可以设置地址对象的备注，以方便您管理和查找。备注最多支持50个字符。"
        }
        ]
     },
     IPGROUP_GROUP_SETTING: {
        TITLE: "地址组列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置地址组对象，进行地址组对象的管理。"
        },
        {
            type: "name",
            title: "组名称",
            content: "标志地址组的名称。"
        },
        {
            type: "name",
            title: "地址名称",
            content: "地址组所引用的地址对象(可多选)，引用了该地址组的规则，对所有地址对象所包含的IP地址均会生效。"
        },
        {
            type: "name",
            title: "备注",
            content: "您可以设置地址组的备注，以方便您管理和查找。备注最多支持50个字符。"
        },
        {
            type: "note",
            title: "注意",
             content:[
                "地址组对象一旦在其他地方被引用则无法在本页面被删除，除非解除引用。",
                "地址组可以为空(即不选择任何地址对象)，引用该地址组的规则对所有地址均不生效。"
             ]
        }
        ]
     },
     TIME_MNGT_SETTING: {
        TITLE: "时间对象列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置时间对象，进行时间对象的管理。注意时间对象只能设置生效星期和无法设置具体日期。"
        },
        {
            type: "name",
            title: "时间对象名称",
            content: "标志时间对象的名称。"
        },
        {
            type: "name",
            title: "时间设置",
            content: "用于设置时间对象所包含的时间段，有两种设置方式。",
             children:[{
                 type:"step",
                 content:[
                    "工作日历：通过在日历上划分矩形覆盖对应的时间区域来设置包含的时间段，只能精确到小时。",
                    "手动设置：通过手动输入生效时间段并勾选生效星期来设置一个时间段，精确到分钟，但一个对象最多只能设置12个时间段。"
                 ]
             }]
        },
        {
            type: "name",
            title: "备注",
            content: "您可以设置时间对象的备注，以方便您管理和查找。备注最多支持32个字符。"

        },
        {
            type: "note",
            title: "注意",
            content: "时间对象一旦在其他地方被引用则无法在本页面被删除，除非解除引用。"
        }
        ]
     },
     IP_POOL_LIST: {
         TITLE: "IP 地址池列表",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置地址池条目，进行地址池的管理。"
         },{
             type: "name",
             title: "地址池名称",
             content: "标志地址池的名称。"
         },{
             type: "name",
             title: "起始IP地址",
             content: "设置地址池起始地址"
         },{
             type: "name",
             title: "结束IP地址",
             content: "设置地址池结束地址"
         },{
             type: "note",
             title: "注意",
             content: "由地址池起始IP和地址池结束IP组成，且地址池起始IP必须不大于地址池结束IP，而且不能与已有的地址池范围重叠。"
         }]
     },
     SESSIONLIMIT_ENABLE: {
         TITLE: "功能设置",
         CONTENT: [{
             type: "name",
             title: "启用连接数限制",
             content: "您可以勾选此项，使连接数限制功能生效。"
         }]
     },
     SESSIONLIMIT_LIST: {
         TITLE: "连接数规则列表",
         CONTENT: [{
             type: "name",
             title: "名称",
             content: "设置规则的名称。"
         },{
             type: "name",
             title: "受控地址组",
             content: "设置受限的IP地址范围。"
         },{
             type: "name",
             title: "最大连接数",
             content: "设置受限IP的最大连接数。"
         },{
             type: "name",
             title: "是否启用",
             content: "您可以勾选此项，使规则生效。"
         }]
     },
     SESSION_LIMITS: {
        TITLE: "连接数监控",
        CONTENT: [{
            type: "paragraph",
            content: "您可通过本页面查看已设置连接数限制规则的地址组内IP地址已建立的连接数。"
        }, {
            type: "name",
            title: "IP",
            content: "已被设置连接数限制规则的地址组中已被监控到的IP地址。"
        }, {
            type: "name",
            title: "最大连接数",
            content: "设置受限IP的最大连接数。"
        }, {
            type: "name",
            title: "当前连接数",
            content: "受限IP当前的连接数。"
        }
        ]
     },
	 APPDIST_SETTING:{
        TITLE: "功能设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面进行相应的应用限制。"
        },
        {
             type: "name",
             title: "启用应用控制功能",
             content: "选中<启用应用控制功能>，将开启该功能。"
        }]
     },
     APPDIST_LIST:{
        TITLE: "应用控制规则列表",
        CONTENT: [
        {
             type: "name",
             title: "受控控制组",
             content: "设置地址组。"
         },
         {
             type: "name",
             title: "禁用列表",
             content: "设置需要禁止的应用。"
         },
        {
             type: "name",
             title: "生效时间",
             content: "选择时间信息，在此时间之内，方可生效。"
         },
         {
             type: "name",
             title: "备注",
             content: "设置备注信息。"
         },
          {
             type: "name",
             title: "状态",
             content: "设置启用/禁用。"
         }]
     },
	 BWLIST_SETTING:{
        TITLE: "功能设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置QQ黑白名单。"
        },
        {
             type: "name",
             title: "启用QQ黑白名单",
             content: "选中<启用QQ黑白名单>，将开启该功能。"
        }]
     },
     BWLIST:{
        TITLE: "规则列表",
        CONTENT: [{
             type: "name",
             title: "受控控制组",
             content: "设置地址组。"
         },
         {
             type: "name",
             title: "规则类型",
             content: "设置QQ白名单或QQ黑名单。"
         },
        {
             type: "name",
             title: "QQ号码",
             content: "设置相应的QQ信息。"
         },
         {
             type: "name",
             title: "生效时间",
             content: "选择时间信息，在此时间之内，方可生效。"
         },
         {
             type: "name",
             title: "备注",
             content: "设置备注信息。"
         },
          {
             type: "name",
             title: "状态",
             content: "设置启用/禁用。"
         },
          {
             type: "name",
             title: "添加到指定位置",
             content: "将规则设置到指定的位置。"
         }]
     },
	 APPDIST_DB:{
        TITLE: "策略库升级",
        CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面升级策略库。"
        },
        {
             type: "name",
             title: "当前数据库版本",
             content: "显示当前数据库的版本信息。"
        },
        {
             type: "name",
             title: "数据库路径",
             content: "选择需要导入的策略库。"
         }]
     },
    UPNP_SETTING:{
        TITLE: "功能设置",
        CONTENT: [{
             type: "paragraph",
             content: "如果您启用UPnP服务，则本地应用程序可以通过UPnP协议与路由器协商相关功能（如端口映射）设置。"
        },
        {
             type: "name",
             title: "对外生效接口",
             content: "您可以指定一组接口集，该集合包含的接口将被配置以端口映射的功能。"
         },
         {
             type: "name",
             title: "启用/禁用服务",
             content: "您可以选择启/禁用UPnP服务。"
         }]
     },
     UPNP_LIST:{
        TITLE: "服务列表",
        CONTENT: [{
             type: "paragraph",
             content: "在服务列表中，您会看到通过UPnP协议向路由器请求的端口映射条目。您可以通过表格按钮对这些条目进行操作。"
        },
        {
             type: "name",
             title: "服务名称",
             content: "对应用程序所配置的端口映射的描述信息。"
        },
        {
             type: "name",
             title: "协议类型",
             content: "表示对何种协议（TCP、UDP或TCP/UDP）进行端口映射。"
        },
        {
             type: "name",
             title: "接口",
             content: "显示需要进行端口转换的路由器接口集。"
        },
        {
             type: "name",
             title: "服务IP地址",
             content: "显示需要进行端口转换的主机IP地址。"
        },
        {
             type: "name",
             title: "外部端口",
             content: "显示端口映射配置的外部端口。"
        },
        {
             type: "name",
             title: "内部端口",
             content: "显示端口映射配置的内部端口。"
        },
        {
             type: "name",
             title: "状态",
             content: [
                "已启用：表示请求的端口映射功能被开启； 已禁用：表示请求的端口映射功能未生效。"
                ]
        }]
     },
     INTERFACE_MODE:{
         TITLE: "接口模式选择",
         CONTENT: [{
             type: "paragraph",
             content: "设置WAN口的数目，当增加接口时，会自动增加接口相关的条目；当删除接口时，会相应的删除相关的条目。"
         },
             {
                 type: "name",
                 title: "单WAN口",
                 content: "路由器将将物理端口1配置为WAN1口。"
             },
             {
                 type: "name",
                 title: "双WAN口",
                 content: "路由器将将物理端口1、2分别配置为WAN1口、WAN2口。"
             },
             {
                 type: "name",
                 title: "三WAN口",
                 content: "路由器将将物理端口1、2、3分别配置为WAN1口、WAN2口、WAN3口。"
             },
             {
                 type: "name",
                 title: "四WAN口",
                 content: "路由器将将物理端口1、2、3、4分别配置为WAN1口、WAN2口、WAN3口、WAN4口。"
             },{
                 type: "name",
                 title: "设置",
                 content: "点击<设置>按钮进行设置。"
             },{
                 type: "note",
                 title: "注意",
                 content: "切换接口模式后会重启系统，在此过程中请不要做任何其他操作，否则可能导致设备功能异常。"
             }]
     },
     
     INTERFACE_MAC: {
         TITLE: "MAC设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面进行路由器接口的MAC配置。"
         },{
             type: "name",
             title: "接口",
             content: "路由器的WAN、LAN口。"
         },{
             type: "name",
             title: "当前MAC地址",
             content: "接口对应的MAC地址。"
         },{
             type: "name",
             title: "恢复出厂MAC",
             content: "单击此按钮并进行保存，恢复MAC为出厂时设置的MAC地址。"
         },{
             type: "name",
             title: "克隆管理主机MAC",
             content: "单击此按钮并进行保存，设置MAC为当前管理主机的MAC地址。"
         },{
             type: "note",
             title: "提示",
             content: [
                 "使用WAN口的克隆管理主机MAC功能时，管理主机必须位于LAN口。",
                 "如果WAN口连接方式为PPPoE，修改WAN口MAC地址可能会导致连接断开（手动连接）或接口重新连接（自动连接）。"
             ]
         }]
     },
     INTERFACE_LAN: {
         TITLE: "接口设置",
         CONTENT: [{
             type: "paragraph",
             content: "您可以通过本页面设置一个LAN接口。"
         },{
             type: "name",
             title: "IP地址",
             content: "本路由器对局域网的IP地址，局域网中所有计算机的默认网关必须设置为该IP地址。"
         },{
             type: "name",
             title: "子网掩码",
             content: "本路由器对局域网的子网掩码，一般为255.255.255.0，局域网中所有计算机的子网掩码必须与此处设置相同。"
         }]
     },
     SWITCH_MONITOR_ENABLE: {
        TITLE: "启用端口监控",
        CONTENT: [{
            type: "paragraph",
            content: "您可以勾选此项，启用端口监控的监控模式。端口监控有下面三种监控模式：",
             children:[{
                 type: "step",
                 content:[
                     "输出输入监控：流入流出被监控端口的数据帧将被复制到监控端口。",
                     "输入监控：流入被监控端口的数据帧将被复制到监控端口。",
                     "输出监控：流出被监控端口的数据帧将被复制到监控端口。"
                 ]
             }]
        }]
     },
     SWITCH_MONITOR_SETTING: {
        TITLE: "监控列表",
        CONTENT: [{
            type: "name",
            title: "监控端口",
            content: "被监控端口的数据帧将被复制到该端口。"
        }, {
            type: "name",
            title: "被监控端口",
            content: "经过该端口的数据帧将被复制到监控端口。"
        }, {
            type: "note",
            title: "提示",
            content: [
                "一个端口不能同时作为监控端口和被监控端口。",
                "只能设置一个监控端口"
            ]
        }
        ]
     },
     SWITCH_PORTLIMIT: {
        TITLE: "端口流量限制",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面对流经端口的特定类型数据帧的速率进行控制。"
        }, {
            type: "name",
            title: "入口限制",
            content: "对端口的入口流量限制是否启用。"
        }, {
            type: "name",
            title: "入口限制速率(Mbps)",
            content: "对端口的入口流量的限制速率。"
        }, {
            type: "name",
            title: "出口限制",
            content: "对端口的出口流量限制是否启用。"
        }, {
            type: "name",
            title: "出口限制速率(Mbps)",
            content: "对端口的出口流量的限制速率。"
        }
        ]
     },
     SWICH_PARAMETER: {
        TITLE: "端口参数",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置各个端口的工作参数。"
        }, {
            type: "name",
            title: "流量控制",
            content: "您可以勾选此项，端口将启用流量控制功能。"
        }, {
            type: "name",
            title: "协商模式",
            content: "端口的协商模式，包括自协商和双工方式"
        }
        ]
     },
     SWITCH_STATUS: {
        TITLE: "端口状态",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面查看当前各个端口的工作状态。"
        }, {
            type: "name",
            title: "端口状态",
            content: "端口的连接状态，有以下三种状态：",
            children: [{
               type: "step",
               content: [
                    "已禁用：端口处于禁用状态。",
                    "已断开：端口处于启用状态但物理网络未就绪。",
                    "已连接：端口处于启用状态并已正常连接。"
               ]
            }]
        }, {
            type: "name",
            title: "连接速率(Mbps)",
            content: "端口的连接速率。"
        }, {
            type: "name",
            title: "双工模式",
            content: "端口的双工模式，包括：全双工和半双工。"
        }, {
            type: "name",
            title: "流量控制",
            content: "端口的流量控制是否开启。"
        }
        ]
     },
		SERVICE_TYPE: {
         TITLE: "服务类型",
         CONTENT: [{
             type: "paragraph",
             content: "您可以在本页面设置自定义服务类型。"
         },{
             type: "name",
             title: "服务名称",
             content: "您将要设置的服务类型的名称，注意不能与系统预定义服务类型名称重复。"
         },{
             type: "name",
             title: "协议类型",
             content: "服务所使用的协议。您可以选择TCP，UDP，TCP/UDP或ICMP，也可以选择other并输入协议号(0-255)。"
         },{
             type: "name",
             title: "源端口范围",
             content: "服务所使用的源端口范围，仅TCP或UDP协议需要设置。"
         },{
             type: "name",
             title: "目的端口范围",
             content: "服务所使用的目的端口范围，仅TCP或UDP协议需要设置。"
         },{
             type: "name",
             title: "ICMP",
             content: "ICMP协议的类型(type)和编码(code)，填充255时表明所有类型/编码。"
         } ,{
             type: "name",
             title: "备注",
             content: "您可以对服务类型进行描述。"
         }]
     },

	CMXDDNS: {
         TITLE: "科迈动态域名",
         CONTENT: [{
             type: "paragraph",
             content: "通过DDNS（Dynamic DNS，动态域名解析服务），您可以将固定域名与动态IP进行绑定，使Internet用户可以通过域名来访问路由器或内网主机。您可以通过本页面登录科迈动态域名服务器，开启科迈动态域名服务。"
         },{
             type: "name",
             title: "服务接口",
             content: "科迈动态域名服务生效的接口。"
         },{
             type: "name",
             title: "用户名",
             content: "科迈动态域名服务账户的用户名。"
         },{
             type: "name",
             title: "密码",
             content: "科迈动态域名服务账户的密码。"
         },{
             type: "name",
             title: "启用/禁用",
             content: "选择是否在添加该账户后立即登录科迈动态域名服务器，开启动态域名服务。"
         },{
             type: "name",
             title: "域名",
             content: "从DDNS服务器获取的域名服务列表，最多可以显示16条域名信息。"
         } ]
     },

	 	PHDDNS: {
         TITLE: "花生壳动态域名",
         CONTENT: [{
             type: "paragraph",
             content: "通过DDNS（Dynamic DNS，动态域名解析服务），您可以将固定域名与动态IP进行绑定，使Internet用户可以通过域名来访问路由器或内网主机。您可以通过本页面登录花生壳动态域名服务器，开启花生壳动态域名服务。"
         },{
             type: "name",
             title: "服务接口",
             content: "花生壳动态域名服务生效的接口。"
         },{
             type: "name",
             title: "用户名",
             content: "花生壳动态域名服务账户的用户名。"
         },{
             type: "name",
             title: "密码",
             content: "花生壳动态域名服务账户的密码。"
         },{
             type: "name",
             title: "启用/禁用",
             content: "选择是否在添加该账户后立即登录花生壳动态域名服务器，开启动态域名服务。"
         },{
             type: "name",
             title: "域名",
             content: "从DDNS服务器获取的域名服务列表，最多可以显示16条域名信息。"
         } ]
     },
	 	 	DYN3322DDNS: {
         TITLE: "3322动态域名",
         CONTENT: [{
             type: "paragraph",
             content: "通过DDNS（Dynamic DNS，动态域名解析服务），您可以将固定域名与动态IP进行绑定，使Internet用户可以通过域名来访问路由器或内网主机。您可以通过本页面登录3322动态域名服务器，开启3322动态域名服务。"
         },{
             type: "name",
             title: "服务接口",
             content: "3322动态域名服务生效的接口。"
         },{
             type: "name",
             title: "用户名",
             content: "3322动态域名服务账户的用户名。"
         },{
             type: "name",
             title: "密码",
             content: "3322动态域名服务账户的密码。"
         },{
             type: "name",
             title: "启用/禁用",
             content: "选择是否在添加该账户后立即登录3322动态域名服务器，开启动态域名服务。"
         },{
             type: "name",
             title: "域名",
             content: "从DDNS服务器获取的域名服务列表，最多可以显示16条域名信息。"
         } ]
     },
	 VPNUSER : {
        TITLE: "VPN用户管理",
        CONTENT: [{
             type: "paragraph",
             content: "您可以配置L2TP/PPTP服务器的用户信息。"
         },{
             type: "name",
             title: "用户名",
             content: "允许拨入的用户名称。"
         },{
             type: "name",
             title: "密码",
             content: "用户名称对应的密码。"
         },{
             type: "name",
             title: "服务类型",
             content: "L2TP：本用户只用于L2TP；PPTP：本用户只用于PPTP；自动：本用户既可用于L2TP也可用于PPTP。"
         },{
             type: "name",
             title: "本地地址",
             content: "VPN隧道的本地虚拟IP地址。"
         },{
             type: "name",
             title: "地址池",
             content: "L2TP/PPTP服务器分配给客户端的IP地址从地址池内获取。"
         },{
             type: "name",
             title: "DNS地址",
             content: "L2TP/PPTP服务器分配给客户端的DNS地址，如8.8.8.8。"
         },{
             type: "name",
             title: "组网模式",
             content: "PC到站点：拨入的客户端是个人用户，往往由单个计算机拨入实现远端计算机与本地局域网的通信；站点到站点：拨入的客户端是一个网段的用户，往往通过一个路由器拨入，实现隧道两端局域网的通信。"
         },{
             type: "name",
             title: "最大会话数",
             content: "每个用户允许接入的最大客户端数量。"
         },{
             type: "name",
             title: "对端子网",
             content: "L2TP/PPTP隧道对端局域网使用的IP地址范围（一般可以填隧道对端设备LAN口的IP地址范围），由IP和子网掩码组成。"
         }
        ]
     },
    L2TP_CLIENT_GLOBAL : {
        TITLE: "全局设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以设置L2TP客户端的全局配置。"
         },{
             type: "name",
             title: "L2TP链路维护时间间隔",
             content: "发送L2TP链路维护检测报文的时间间隔。"
         },{
             type: "name",
             title: "PPP链路维护时间间隔",
             content: "发送PPP链路维护检测报文的时间间隔。"
         }
        ]
     },
    L2TP_CLIENT_SET : {
        TITLE: "客户端设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以配置L2TP的客户端。"
         },{
             type: "name",
             title: "隧道名称",
             content: "L2TP隧道的名称，用于区分不同的隧道。"
         },{
             type: "name",
             title: "用户名",
             content: "L2TP隧道用于身份认证的用户名。"
         },{
             type: "name",
             title: "密码",
             content: "L2TP的用户密码。"
         },{
             type: "name",
             title: "出接口",
             content: "L2TP报文收发的接口。"
         },{
             type: "name",
             title: "服务器地址",
             content: "L2TP服务器的地址，可以为IP或域名。"
         },{
             type: "name",
             title: "IPSec加密",
             content: "是否对隧道进行加密。若启用，则使用IPSec对L2TP隧道加密。"
         },{
             type: "name",
             title: "预共享密钥",
             content: "设置IPSec加密时的预共享密钥。"
         },{
             type: "name",
             title: "对端子网",
             content: "L2TP隧道对端局域网使用的IP地址范围（一般可以填隧道对端设备LAN口的IP地址范围），由IP和子网掩码组成。"
         },{
             type: "name",
             title: "工作模式",
             content: "NAT：对经过此L2TP隧道的数据包进行NAT转换（数据包的源IP替换为L2TP隧道的本地虚拟IP）；路由：对经过此L2TP隧道的数据包只进行路由转发"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择启用来使隧道生效。"
         },{
             type: "name",
             title: "参与流量均衡",
             content: "您可以点选此项使隧道参与流量均衡。"
         }
        ]
     },

    L2TP_SERVER_GLOBAL : {
        TITLE: "全局设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以设置L2TP服务器的全局配置。"
         },{
             type: "name",
             title: "L2TP链路维护时间间隔",
             content: "发送L2TP链路维护检测报文的时间间隔。"
         },{
             type: "name",
             title: "PPP链路维护时间间隔",
             content: "发送PPP链路维护检测报文的时间间隔。"
         }
        ]
     },
    L2TP_SERVER_SET : {
        TITLE: "服务器设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以配置L2TP的服务器。"
         },{
             type: "name",
             title: "服务接口",
             content: "L2TP服务器监听的接口，只有来自服务接口的报文才会被处理。"
         },{
             type: "name",
             title: "IPSec加密",
             content: "是否对隧道进行加密。若启用，则使用IPSec对L2TP隧道加密。"
         },{
             type: "name",
             title: "预共享密钥",
             content: "设置IPSec加密时的预共享密钥。"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择启用来使隧道生效。"
         }
        ]
     },

     L2TP_TUNNEL : {
        TITLE: "隧道信息列表",
        CONTENT: [{
             type: "paragraph",
             content: "您可以获得L2TP隧道的信息。"
         },{
             type: "name",
             title: "用户名",
             content: "L2TP隧道建立时用于认证身份使用的用户名称。"
         },{
             type: "name",
             title: "服务器/客户端",
             content: "建立隧道时，本端是作为服务器还是客户端。"
         },{
             type: "name",
             title: "虚拟接口名称",
             content: "隧道使用的虚拟接口名称。"
         },{
             type: "name",
             title: "虚拟本地IP",
             content: "隧道的本地虚拟IP地址。"
         },{
             type: "name",
             title: "接入服务IP",
             content: "隧道的对端实际IP地址。"
         },{
             type: "name",
             title: "对端虚拟IP",
             content: "隧道的对端虚拟IP地址。"
         },{
             type: "name",
             title: "DNS",
             content: "隧道的DNS地址。"
         }
        ]
     },

     PPTP_CLIENT_GLOBAL : {
        TITLE: "全局设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以设置PPTP客户端的全局配置。"
         },{
             type: "name",
             title: "PPTP链路维护时间间隔",
             content: "发送PPTP链路维护检测报文的时间间隔。"
         },{
             type: "name",
             title: "PPP链路维护时间间隔",
             content: "发送PPP链路维护检测报文的时间间隔。"
         }
        ]
     },
    PPTP_CLIENT_SET : {
        TITLE: "客户端设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以配置PPTP的客户端。"
         },{
             type: "name",
             title: "隧道名称",
             content: "PPTP隧道的名称，用于区分不同的隧道。"
         },{
             type: "name",
             title: "用户名",
             content: "PPTP隧道用于身份认证的用户名。"
         },{
             type: "name",
             title: "密码",
             content: "PPTP的用户密码。"
         },{
             type: "name",
             title: "出接口",
             content: "PPTP报文收发的接口。"
         },{
             type: "name",
             title: "服务器地址",
             content: "PPTP服务器的地址，可以为IP或域名。"
         },{
             type: "name",
             title: "MPPE加密",
             content: "是否对隧道进行加密。若启用，则使用MPPE对PPTP隧道加密。"
         },{
             type: "name",
             title: "对端子网",
             content: "PPTP隧道对端局域网使用的IP地址范围（一般可以填隧道对端设备LAN口的IP地址范围），由IP和子网掩码组成。"
         },{
             type: "name",
             title: "工作模式",
             content: "NAT：对经过此PPTP隧道的数据包进行NAT转换（数据包的源IP替换为PPTP隧道的本地虚拟IP）；路由：对经过此PPTP隧道的数据包只进行路由转发"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择启用来使隧道生效。"
         },{
             type: "name",
             title: "参与流量均衡",
             content: "您可以点选此项使隧道参与流量均衡。"
         }
        ]
     },

    PPTP_SERVER_GLOBAL : {
        TITLE: "全局设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以设置PPTP服务器的全局配置。"
         },{
             type: "name",
             title: "PPTP链路维护时间间隔",
             content: "发送PPTP链路维护检测报文的时间间隔。"
         },{
             type: "name",
             title: "PPP链路维护时间间隔",
             content: "发送PPP链路维护检测报文的时间间隔。"
         }
        ]
     },
    PPTP_SERVER_SET : {
        TITLE: "服务器设置",
        CONTENT: [{
             type: "paragraph",
             content: "您可以配置PPTP的服务器。"
         },{
             type: "name",
             title: "服务接口",
             content: "PPTP服务器监听的接口，只有来自服务接口的报文才会被处理。"
         },{
             type: "name",
             title: "MPPE加密",
             content: "是否对隧道进行加密。若启用，则使用MPPE对PPTP隧道加密。"
         },{
             type: "name",
             title: "状态",
             content: "您可以选择启用来使隧道生效。"
         }
        ]
     },

     PPTP_TUNNEL : {
        TITLE: "隧道信息列表",
        CONTENT: [{
             type: "paragraph",
             content: "您可以获得PPTP隧道的信息。"
         },{
             type: "name",
             title: "用户名",
             content: "PPTP隧道建立时用于认证身份使用的用户名称。"
         },{
             type: "name",
             title: "服务器/客户端",
             content: "建立隧道时，本端是作为服务器还是客户端。"
         },{
             type: "name",
             title: "虚拟接口名称",
             content: "隧道使用的虚拟接口名称。"
         },{
             type: "name",
             title: "虚拟本地IP",
             content: "隧道的本地虚拟IP地址。"
         },{
             type: "name",
             title: "接入服务IP",
             content: "隧道的对端实际IP地址。"
         },{
             type: "name",
             title: "对端虚拟IP",
             content: "隧道的对端虚拟IP地址。"
         },{
             type: "name",
             title: "DNS",
             content: "隧道的DNS地址。"
         }
        ]
     },
     REMOTE_MNGT: {
        TITLE: "远程管理",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置进行远程管理的IP地址。"
        }, {
            type: "name",
            title: "远程地址范围",
            content: "远程管理主机的地址范围。"
        }, {
            type: "name",
            title: "状态",
            content: "您可以通过勾选改项来设置是否规则对应的地址范围内的主机进行远程管理。"
        }, {
            type: "note",
            title: "举例",
            content: "如果您想让地址段为102.31.70.0/24的主机（非LAN口网段）对路由器进行远程管理，您可以建立远程管理地址条目，点击<新增>，设置远程地址范围102.31.70.0/24，状态勾选设置为启用。"
        }, {
            type: "note",
            title: "注意",
            content: [
                "包含局域网地址的远程管理地址条目无效（局域网地址包括LAN口合法地址）。",
                "如果添加0.0.0.0/0的条目，将允许所有远程计算机访问路由器，有可能在非法攻击情况下无法访问路由器。"
            ]
        }
        ]
     },
    IFSTAT:{
        TITLE: "流量统计列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来查看路由器各接口的流量信息。"
         },{
            type: "name",
            title: "刷新",
            content: "点击刷新按钮可以查看路由器各接口的最新流量统计信息。"
         },{
            type: "name",
            title: "排序",
            content: "点击表头中的文字，可以对该列进行升序/降序排序。"
         }]
     },
     IP_STATS_SETTING:{
        TITLE: "IP流量统计功能设置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以设置启用IP流量统计以及监控的IP地址范围。"
         },{
            type: "name",
            title: "启用IP流量统计",
            content: "您可以通过选择此选项来启用IP流量统计功能。"
         },{
            type: "name",
            title: "监控IP范围",
            content: "监控IP范围内的流量统计信息将会显示在本页的列表当中。"
         }]
     },
     IP_STATS_LIST:{
        TITLE: "流量统计列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来查看路由器各IP的流量信息。"
         },{
            type: "name",
            title: "刷新",
            content: "点击刷新按钮可以查看路由器各接口的最新流量统计信息。"
         },{
            type: "name",
            title: "排序",
            content: "点击表头中的文字，可以对该列进行升序/降序排序。"
         }]
     },
     ADMIN_ACCOUNT:{
        TITLE: "修改管理账户",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来修改管理账户的用户名和密码。"
         },{
            type: "name",
            title: "原用户名",
            content: "原用户名为您本次登录使用的用户名。"
         },{
            type: "name",
            title: "原密码",
            content: "原密码为您本次登录使用的密码。"
         },{
            type: "name",
            title: "新用户名",
            content: "您可以设置一个新的用户名。可以使用字母、数字及常用符号的组合，不能使用中文及特殊符号。"
         },{
            type: "name",
            title: "新密码",
            content: "您可以设置一个新的密码。推荐使用强度较高的密码以保证设备及网络的安全。"
         },{
            type: "name",
            title: "确认新密码",
            content: "请您再输入一遍新设置的密码，来确认新密码。"
         },{
            type: "name",
            title: "密码强度",
            content: "在新密码输入框下的密码强度控件会提示您密码的强度，建议您使用字母、数字及常用符号的组合来提升密码的强度和安全性。"
         }]
     },
     ADMIN_CONFIG:{
        TITLE: "系统管理设置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面进行服务端口和会话超时时间的管理。"
         },{
            type: "name",
            title: "Http服务端口",
            content: "用于Web管理界面的服务端口，默认为80端口。不能与其他的服务端口重复。"
         },{
            type: "name",
            title: "Https服务端口",
            content: "用于Web管理界面的Https服务端口，默认为443端口。不能与其他的服务端口重复。"
         },{
            type: "name",
            title: "Web会话超时时间",
            content: "如果在会话超时时间内都没有进行操作，系统将自动退出登录，以保证设备和网络的安全。"
         }]
     },
     SWITCH_PORTVLAN:{
        TITLE: "Port VLAN",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过基于端口的VLAN划分，控制端口之间是否可以进行通信，从而灵活地部署网络环境。"
         },{
            type: "name",
            title: "网络",
            content: "用于标识各个物理端口此时属于的逻辑网络。"
         },{
            type: "name",
            title: "VLAN",
            content: "您可以将端口划分入不同的VLAN。"
         },{
            type: "note",
            title: "提示",
            content: [
                "Port VLAN的划分只能在LAN口中进行。",
                "只有位于同一个Port VLAN中的端口之间才能进行通信，位于不同Port VLAN的端口之间无法进行通信。"
            ]
         }]
     },
     SWITCH_PORT_STATISTICS:{
        TITLE: "端口统计列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过端口统计查看各个端口收发数据帧的统计信息。"
         },{
            type: "name",
            title: "单播帧",
            content: "接收/发送目的MAC地址为单播MAC地址的正常数据帧数目。"
         },{
            type: "name",
            title: "广播帧",
            content: "接收/发送目的MAC地址为广播MAC地址的正常数据帧数目。"
         },{
            type: "name",
            title: "流控帧",
            content: "接收/发送的流控帧（起流量控制作用的数据帧）数目。"
         },
         {
            type: "name",
            title: "多播帧",
            content: "接收/发送目的MAC地址为多播MAC地址的正常数据帧数目。"
         },
        {
            type: "name",
            title: "所有帧",
            content: "接收/发送数据帧的总字节数（包括错误帧）。"
         },
         {
            type: "name",
            title: "过小帧",
            content: "接收的长度小于64字节的数据帧数目（包含错误帧）。"
         },
         {
            type: "name",
            title: "正常帧",
            content: "接收的长度在64字节到最大帧长的数据帧数目（包含错误帧）。"
         },
         {
            type: "name",
            title: "过大帧",
            content: "接收的长度大于最大帧长的数据帧数目（包含错误帧）。"
         },
         {
            type: "name",
            title: "刷新",
            content: "点击<刷新>按钮以获取最新的统计结果。"
        },{
            type: "name",
            title: "清空",
            content: "点击<清空>按钮以清空统计结果。"
        },{
            type: "note",
            title: "提示",
            content: [
                "错误帧：指校验和错误的帧。",
                "最大帧长：路由器支持的最大帧的大小，对于不带Tag标签的帧该值为1518字节，对于带Tag标签的帧该值为1522字节。"
            ]
        }]
     },
     
     INTERFACE_WAN:{
        TITLE: "连接设置",
        CONTENT: [{
                type: "paragraph",
                content: "您可以通过本页面设置WAN接口。"
            },{
                type: "name",
                title: "连接方式",
                content: "如果ISP（Internet Service Provider，网络服务提供商）提供ADSL虚拟拨号方式，请选择\"PPPoE拨号\";</br>如果提供自动获取IP地址方式，请选择\"自动获取IP地址\";</br>否则，请选择\"固定IP地址\"。"
            },{
                type: "name",
                title: "用户名",
                content: "ISP提供ADSL虚拟拨号方式的帐号，若您不了解或遗忘账号密码，请向ISP询问。"
            },
            {
                type: "name",
                title: "密码",
                content: "ISP提供ADSL虚拟拨号方式的密码，若您不了解或遗忘账号密码，请向ISP询问。"
            },
            {
                type: "name",
                title: "连接模式",
                content:"您可以根据不同的网络环境需求选择合适的连接模式。</br>手动连接：手动进行PPPoE的连接和断开。</br>自动连接：在重新启动路由器或PPPoE未连接时，将自动进行PPPoE连接。</br>定时连接：在连接时段内，路由器将自动进行PPPoE连接。"
            },
            {
                type: "name",
                title: "上行/下行带宽",
                content: "接口的上行/下行带宽。"
            },
            {
                type: "name",
                title: "MTU",
                content: "MTU（Maximum Transmission Unit，最大传输单元），在一定物理网络中能传送的最大数据单元。</br>连接方式为“PPPoE拨号”时，MTU范围为576-1492，缺省为1492。</br> 连接方式为“自动获取IP地址”或“固定IP地址”时，MTU范围为576-1500，缺省为1500。"
            },
            {
                type: "name",
                title: "服务名",
                content: "可选项，填入ISP提供的服务名称。缺省为空。"
            },
            {
                type: "name",
                title: "首选/备用DNS服务器",
                content: "可选项，请填入ISP提供的DNS服务器，若您不了解，请向ISP询问。"
            },
            {
                type: "name",
                title: "主机名",
                content: "可选项，网络中其他设备看到的路由器的名称，缺省为空。"
            },
            {
                type: "name",
                title: "IP地址",
                content: "ISP提供的广域网IP地址。"
            },{
                type: "name",
                title: "子网掩码",
                content: "ISP提供的子网掩码。"
            },{
                type: "name",
                title: "网关地址",
                content: "可选项，ISP提供的网关地址。"
            },{
                type: "name",
                title: "设置",
                content: "点击<设置>按钮保存并提交设置。"
            },{
                type: "name",
                title: "连接",
                content: "点击<连接>按钮立刻进行连接。"
            },{
                type: "name",
                title: "断开",
                content: "点击<断开>按钮立刻断开连接。"
            }]
     },
     WAN_STATUS:{
        TITLE: "连接状态",
        CONTENT: [{
            type: "paragraph",
            content: "您可以查看到当前WAN口的状态。"
        }]
     },
     DHCP_SERVER_SETTINGS:{
        TITLE: "DHCP服务设置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以在本页面对DHCP服务进行设置。"
        },{
            type: "name",
            title: "开始地址",
            content: "用于DHCP分配地址的开始地址。"
        },{
            type: "name",
            title: "结束地址",
            content: "用于DHCP分配地址的结束地址，结束地址需要大于开始地址。"
        },{
            type: "name",
            title: "地址租期",
            content: "DHCP服务器所分配IP地址的有效使用时间，超时将重新分配。"
        },{
            type: "name",
            title: "网关地址",
            content: "可选项，建议填入当前DHCP服务生效接口的IP地址。"
        },{
            type: "name",
            title: "缺省域名",
            content: "可选项，填入本地网域名。"
        },{
            type: "name",
            title: "首选/备用DNS服务器",
            content: "可选项，请填入ISP提供的DNS服务器，若不清楚可以向ISP询问。"
        },{
            type: "name",
            title: "Option60",
            content: "可选项，请填入厂商信息。具体厂商信息请咨询相关厂商，例如TP-LINK的厂商信息为TP-LINK。"
        },{
            type: "name",
            title: "Option138",
            content: "可选项，请填入AC（无线控制器）IP地址。"
        },{
            type: "name",
            title: "状态",
            content: "勾选后开启DHCP服务。"
        }]
     },
     DHCP_CLIENT_LIST:{
        TITLE: "DHCP客户端列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以在本页面查看DHCP的客户端相关信息。"
        },{
            type: "name",
            title: "主机名",
            content: "由DHCP服务器分配IP的客户端主机名。"
        },{
            type: "name",
            title: "MAC地址",
            content: "分配到IP地址的客户端主机的MAC地址。"
        },{
            type: "name",
            title: "IP地址",
            content: "DHCP服务器分配给客户端主机的IP地址。"
        },{
            type: "name",
            title: "剩余租期",
            content: "DHCP服务器所分配IP地址的剩余有效使用时间，超时将重新分配。"
        }]
     },
     DHCP_STATIC:{
        TITLE: "DHCP静态地址分配",
        CONTENT: [{
            type: "paragraph",
            content: "您可以在本页面为指定的MAC地址预留IP地址。当该主机向DHCP服务器请求分配IP时，服务器将为其分配预留的IP地址。"
        },{
            type: "name",
            title: "MAC地址",
            content: "预留IP地址的主机MAC地址。"
        },{
            type: "name",
            title: "IP地址",
            content: "为指定主机预留的IP地址。"
        },{
            type: "name",
            title: "备注",
            content: "您可以设置静态地址分配条目备注，以方便您管理和查找。备注最多支持32个字符。"
        },{
            type: "name",
            title: "状态",
            content: "您可以通过启用/禁用来选择是否使该条目生效。"
        }]
     },
     FACTORY: {
        TITLE: "恢复出厂配置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过恢复出厂配置，将路由器的所有配置重置为出厂时的默认配置。"
        }, {
            type: "name",
            title: "恢复出厂配置",
            content: "点击<恢复出厂配置>来进行路由器恢复出厂配置。"
        }, {
            type: "note",
            title: "注意",
            content: [
                "恢复出厂配置后，当前的配置信息将会丢失。如果您想保留当前配置，请注意备份。",
                "恢复出厂配置后，路由器将自动重启。"
            ]
        }]
     },
     BACKUP_RESTORE: {
        TITLE: "备份与导入配置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面保存或恢复您的配置。"
        }, {
            type: "name",
            title: "备份配置信息",
            content: "您可以通过点击<备份>按钮来保存您当前的配置信息。路由器将以文件的形式保存您的设置，建议您在进行软件升级前进行备份。"
        }, {
            type: "name",
            title: "导入配置信息",
            content: "您可以通过浏览选择配置文件后点击<导入>按钮，导入配置文件来恢复您的配置信息。"
        }, {
            type: "note",
            title: "注意",
            content: [
                "如果您导入的配置文件版本与现有版本差距过大，有可能导致配置信息丢失。",
                "导入配置信息后，路由器将自动重启。"
            ]
        }]

     },
     REBOOT: {
        TITLE: "重启路由器",
        CONTENT: [{
            type: "paragraph",
            content: "路由器的部分配置修改需要重启路由器才能生效，您可以通过本页面来重启路由器。"
        }, {
            type: "name",
            title: "重启路由器",
            content: "点击<重启路由器>按钮来完成路由器的重启。"
        }, {
            type: "note",
            title: "注意",
            content: "在路由器重启过程中，请不要将路由器断电！"
        }]
     },
     FIRMWARE: {
        TITLE: "软件升级",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来进行软件升级。建议您进行软件升级前，先备份您的配置信息。"
        }, {
            type: "name",
            title: "当前软件版本",
            content: "路由器的软件版本。"
        }, {
            type: "name",
            title: "当前硬件版本",
            content: "路由器的硬件版本。"
        }, {
            type: "name",
            title: "升级文件路径",
            content: "您可以在此选择升级文件后点击<升级>按钮来进行软件升级。"
        }, {
            type: "note",
            title: "提示",
            content: [
                "请确保在路由器升级过程中，不要将路由器断电，不要对页面进行刷新。升级完毕，路由器将自动重启。",
                "您可以到网址<a href=\"http:\/\/www.tp-link.com.cn\" target=\"_blank\">www.tp-link.com.cn</a>下载最新的升级软件。"
            ]
        }, {
            type: "note",
            title: "注意",
            content: [
                "在路由器升级过程中，请不要将路由器断电。",
                "进行软件升级后，当前的配置信息可能会丢失。请您在升级前备份产品配置信息。"
            ]
        }]
     },
     TIME_SETTING: {
        TITLE: "时间设置",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来查看和设置系统时间。"
        }, {
            type: "name",
            title: "当前时间",
            content: "当前系统的时间。"
        }, {
            type: "name",
            title: "设置时间",
            content: "设置路由器系统时间的方式，分为通过网络获取系统时间和手动设置系统时间，其中手动设置系统时间也可以通过获取管理主机时间的方式进行设置。"
        }, {
            type: "name",
            title: "通过网络获取系统时间",
            content: "选中<通过网络获取系统时间>，路由器将通过网络获取GMT时间。",
            children: [{
                type: "step",
                content: [
                    "时区：路由器所在的时区。",
                    "首选/备用NTP服务器：您可以自行指定NTP服务器地址。"
                ]
            }]
        }, {
            type: "name",
            title: "手动设置系统时间",
            content: "选中<手动设置系统时间>，您可以通过手动输入的方式来设置路由器日期和时间。"
        }, {
            type: "name",
            title: "获取管理主机时间",
            content: "点击<获取管理主机时间>，系统将获取当前管理主机的时间并路由器的系统时间设置为该时间。"
        }]
     },
     SYSTEM_LOG: {
        TITLE: "系统日志",
        CONTENT:[{
            type: "paragraph",
            content: "您可以通过本页面来查看系统运行状况。"
        }
        ]
     },
     SYSTEM_LOG_SETTING: {
        TITLE: "日志设置",
        CONTENT: [{
            type: "name",
            title: "启用自动刷新",
            content: "选中<启用自动刷新>，页面将每隔10秒自动刷新一次。"
        }, {
            type: "name",
            title: "选择日志等级",
            content: "选中<选择日志等级>，将弹出日志等级复选框以供您查看特定等级的日志信息。",
            children: [{
                type: "step",
                content: [
                    "所有等级：查看所有等级的日志信息。",
                    "致命错误：导致系统不可用的错误。",
                    "紧急错误：必须对其采取紧急措施的错误。",
                    "严重错误：导致系统处于危险状态的错误。",
                    "一般错误：一般性的错误提示。",
                    "警告信息：系统仍然正常运行，但可能存在隐患的提示信息。",
                    "通知信息：正常状态下的重要提示信息。",
                    "信息报告：一般性的提示信息。",
                    "调试信息：调试过程中产生的信息。"
                ]
            }]
        }]
     },
     SYSTEM_LOG_LIST: {
        TITLE: "日志列表",
        CONTENT: [{
            type: "name",
            title: "日志内容",
            content: "每一项日志内容组成格式为“时间+功能模块+日志等级+日志信息”。"
        }, {
            type: "name",
            title: "刷新",
            content: "手动刷新日志内容。"
        }, {
            type: "name",
            title: "全部删除",
            content: "点击<全部删除>将删除路由器中保存的所有日志。"
        }, {
            type: "name",
            title: "导出日志",
            content: "点击<导出日志>按钮，路由器将以文件形式保存当前路由器中所有的日志内容。"
        }]
     },
     DIGNOSTIC: {
        TITLE: "诊断工具",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过诊断工具来检测和诊断当前的网络状况。"
        }, {
            type: "name",
            title: "诊断工具类型",
            content: "用于诊断网络状况的方式。有下面两种：",
            children: [{
                type: "step",
                content: [
                    "PING通信检测。",
                    "路由跟踪检测。"
                ]
            }]
        },{
            type: "name",
            title: "目的IP/域名",
            content: "需要进行Ping通信检测或者路由跟踪检测的主机地址，支持IP地址和域名。"
        }, {
            type: "name",
            title: "出接口",
            content: "需要进行Ping通信检测或者路由跟踪检测的接口。"
        },{
            type: "name",
            title: "PING次数",
            content: "设置Ping通信检测时发送Ping包的数量。"
        }, {
            type: "name",
            title: "PING数据包大小",
            content: "设置Ping通信检测时发送的Ping包的大小。"
        },{
            type: "name",
            title: "路由跟踪最大TTL",
            content: "设置路由跟踪检测发送数据包在网络中的最大转发跳数。"
        }]
     },
     
     PRINTER_SERVER: {
        TITLE: "打印服务器",
        CONTENT: [{
            type: "paragraph",
            content: "通过本页面您可以设置启用/禁用USB网络打印服务器。"
        }]
     },WPORTAL_FUNCTION: {
        TITLE: "功能设置",
        CONTENT: [{
            type: "name",
            title: "状态",
            content: "勾选此项以启用Web认证功能。"
        },{
            type: "name",
            title: "空闲断线",
            content: "输入5-1440分钟来设置空闲断线功能，0表示不开启空闲断线功能。"
        }]
     },
    WPORTAL_PARAMETER: {
        TITLE: "Web认证参数设置",
        CONTENT: [{
            type: "name",
            title: "认证页面",
            content: "选择由系统生成的自定义页面或者由外部的链接进行认证。"
        }, {
            type: "name",
            title: "背景图片",
            content: "用于自定义页面的背景展示图，图片大小限制在200KB以内。"
        }, {
            type: "name",
            title: "欢迎信息",
            content: "显示在自定义认证页面的欢迎信息。"
        }, {
            type: "name",
            title: "版权声明",
            content: "显示在自定义认证页面的版权声明信息。"
        }, {
            type: "name",
            title: "认证URL",
            content: "认证页面选择外部链接时填写，用于认证的URL。"
        }, {
            type: "name",
            title: "认证成功跳转链接",
            content: "认证页面选择外部链接时填写，认证成功后跳转到的链接。"
        }, {
            type: "name",
            title: "认证失败跳转链接",
            content: "认证页面选择外部链接时填写，认证失败后跳转到的链接。"
        }, {
            type: "name",
            title: "认证方式",
            content: "选择认证的方式，有本地认证、radius认证和一键上网可供选择。",
            children:[{
                 type: "step",
                 content:[
                     "本地认证：通过用户管理页面设置的本地用户进行认证",
                     "radius认证：使用外部配置的认证服务器进行认证，如果认证服务器不指定上网时长值，上网时长将设置为默认值30分钟。",
                     "一键上网：通过一键设置通过认证，无需用户名密码。"
                 ]
            }]
        },{
            type: "name",
            title: "到期提醒",
            content: "本地认证方式时，可以设置在用户即将到期时提醒用户。"
        },{
            type: "name",
            title: "开始提醒时间",
            content: "设置帐号到期前几天开始提醒用户。"
        },{
            type: "name",
            title: "提醒方式",
            content: "认证时提醒只在认证成功后提醒用户一次；周期提醒会在开始提醒时间范围内，每隔一段时间提醒用户。"
        },{
            type: "name",
            title: "周期提醒间隔",
            content: "提醒用户认证到期的时间间隔"
        },{
            type: "name",
            title: "提醒页面内容",
            content: "设置提醒页面内容。"
        },{
            type: "name",
            title: "页面预览",
            content: "预览用于提醒用户到期的页面。"
        },{
            type: "name",
            title: "主radius服务器地址",
            content: "选择radius认证时，主radius服务器地址必须填写。"
        },{
            type: "name",
            title: "备用radius服务器地址",
            content: "选择radius认证时，备用的radius服务器地址。"
        },{
            type: "name",
            title: "认证端口",
            content: "用于radius认证的端口号。"
        },{
            type: "name",
            title: "授权共享密钥",
            content: "radius认证授权共享密钥。"
        },{
            type: "name",
            title: "失败发送次数",
            content: "radius认证失败后，重复发送认证请求的次数。"
        },{
            type: "name",
            title: "超时时间",
            content: "radius认证超时时间。"
        },{
            type: "name",
            title: "radius认证方式",
            content: "设置radius认证方式。"
        },{
            type: "name",
            title: "免费上网时长",
            content: "设置一键上网的免费时长，1-1440分钟。"
        },{
             type: "note",
             title: "提示",
             content: [
                 "不能同时开启Web认证和微信连WiFi服务。"
             ]
         }]
     },
     WECHAT_WIFI_FUNCTION: {
        TITLE: "功能设置",
        CONTENT: [{
            type: "name",
            title: "状态",
            content: "勾选此项以启用微信连Wi-Fi功能。"
        },{
            type: "name",
            title: "空闲断线",
            content: "输入5-1440分钟来设置空闲断线功能，0表示不开启空闲断线功能。"
        }]
     },

     WECHAT_WIFI_PARAMETER: {
        TITLE: "微信公众平台参数设置",
        CONTENT: [{
            type: "name",
            title: "SSID",
            content: "无线网络设备的SSID。"
        }, {
            type: "name",
            title: "ShopID",
            content: "商家微信公众平台门店ID。"
        }, {
            type: "name",
            title: "AppID",
            content: "商家微信公众平台账号。"
        }, {
            type: "name",
            title: "Secretkey",
            content: "商家微信工作平台账号的密钥。"
        }, {
            type: "name",
            title: "微信连Wi-Fi设置说明",
            content: "通过该链接您可以看到更详细的设置教程。您需要连接互联网才能查看该教程。"
        }]
     },
     WECHAT_WIFI_PAGE: {
        TITLE: "认证页面设置",
        CONTENT: [{
            type: "name",
            title: "背景图片",
            content: "设置微信认证页面的背景图片。点击<上传>按钮来设置您的自定义背景图片。如不上传，则会使用设备自带的默认背景图片。"
        }, {
            type: "name",
            title: "Logo图片",
            content: "设置微信认证页面的Logo图片。点击<上传>按钮来设置您的自定义Logo图片。点击<删除>按钮将不使用Logo图片。"
        }, {
            type: "name",
            title: "Logo信息",
            content: "设置微信认证页面的Logo信息。Logo信息位于Logo图片的正下方。可以输入1-25个字符。"
         }, {
            type: "name",
            title: "欢迎信息",
            content: "设置微信认证页面的欢迎信息。欢迎信息位于登录按钮的上方。可以输入1-50个字符。"
         }, {
            type: "name",
            title: "登录按钮提示文字",
            content: "设置微信认证页面的登录按钮提示文字。可以输入1-15个字符。"
         }, {
            type: "name",
            title: "版权声明",
            content: "设置微信认证页面的版权声明。版权声明位于认证页面底部。可以输入1-25个字符。"
         }, {
            type: "name",
            title: "页面预览",
            content: "通过点击<预览Portal页面>按钮可以预览设置后的微信认证页面效果。"                                          
        }]
     },
     WECHAT_WIFI_TIME: {
        TITLE: "免费上网时长设置",
        CONTENT: [{
            type: "name",
            title: "免费上网时长",
            content: "设置用户通过认证后能使用网络的时长，可设置最短1分钟，最长1440分钟。"
        }]
     },
     PORTAL_FREE: {
        TITLE: "免认证策略",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面设置和查看免认证策略信息，免认证策略用来配置用户在Portal认证通过前可以免费访问的资源。"
        }, {
            type: "name",
            title: "策略名称",
            content: "设置免认证策略的名称。",
        }, {
            type: "name",
            title: "免认证方式",
            content: "设置免认证策略的方式，可选择五元组和URL两种方式。",
        }, {
            type: "name",
            title: "URL方式",
            content: "设置免认证的目的网络地址。",
        }, {
            type: "name",
            title: "源IP地址范围",
            content: "设置免认证策略的源IP地址和网络掩码。",
        }, {
            type: "name",
            title: "目的IP地址范围",
            content: "设置免认证策略的目的IP地址和网络掩码。",
        }, {
            type: "name",
            title: "源MAC地址",
            content: "设置免认证策略的源MAC地址。",
        }, {
            type: "name",
            title: "源端口范围",
            content: "设置免认证策略的源端口范围。",
        }, {
            type: "name",
            title: "目的端口范围",
            content: "设置免认证策略的目的端口范围。",
        }, {
            type: "name",
            title: "服务协议",
            content: "设置免认证策略的服务协议。",
        }, {
            type: "name",
            title: "备注",
            content: "您可以设置免认证策略的备注，以方便您管理和查找。备注最多支持50个字符。",
        }, {
            type: "name",
            title: "状态",
            content: "您可以勾选该项来启用该免认证策略。"
        }]
     },
     USERMNGR_USER:{
        TITLE: "认证用户规则列表",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来查看认证用户规则。"
        }, {
            type: "name",
            title: "用户类型",
            content: "手动刷新认证用户列表。",
            children:[{
                 type: "step",
                 content:[
                     "正式用户：存留在系统中的正式用户，具有一定的有效期，且可以绑定相应的设备MAC地址。可以记录更多用户的资料信息。",
                     "免费用户：免费用户具有一定的上网时长限制。"
                 ]
            }]
        },{
            type: "name",
            title: "用户名",
            content: "用于认证登录的用户名。"
        }, {
            type: "name",
            title: "密码",
            content: "用户登录所使用的密码。"
        }, {
            type: "name",
            title: "有效期至",
            content: "正式用户的有效期。"
        }, {
            type: "name",
            title: "上网时长",
            content: "免费用户的免费上网时长。"
        }, {
            type: "name",
            title: "允许认证时间段",
            content: "允许用户进行认证的时间。"
        }, {
            type: "name",
            title: "MAC地址绑定方式",
            content: "选择是否绑定MAC地址，以及绑定的方式。",
            children:[{
                 type: "step",
                 content:[
                     "不绑定：不绑定用户的MAC地址。",
                     "静态绑定：绑定一个静态的MAC地址。",
                     "动态绑定：进行动态绑定。"
                 ]
            }]
        }, {
            type: "name",
            title: "同时登录的用户数",
            content: "最多允许同时使用该账号登录的用户数量。"
        }, {
            type: "name",
            title: "上行带宽",
            content: "当前用户允许的上行带宽，以Kbps为单位，0表示不限制。当开启此功能时，系统默认的NAT加速功能将会被关闭，因此转发性能会受到一定程度的影响。"
        }, {
            type: "name",
            title: "下行带宽",
            content: "当前用户允许的下行带宽，以Kbps为单位，0表示不限制。当开启此功能时，系统默认的NAT加速功能将会被关闭，因此转发性能会受到一定程度的影响。"
        }, {
            type: "name",
            title: "姓名",
            content: "可选记录当前用户姓名。"
        }, {
            type: "name",
            title: "电话",
            content: "可选记录当前用户电话。"
        }, {
            type: "name",
            title: "备注",
            content: "可选记录当前用户备注。"
        }, {
            type: "name",
            title: "状态",
            content: "是否启用当前用户规则。"
        }]
     },
     USERMNGR_USER_BK: {
        TITLE: "备份配置信息",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来备份和下载用户配置信息。"
        }, {
            type: "name",
            title: "备份",
            content: "点击<备份>按钮来备份和下载用户配置信息。"
        }]
     },
     USERMNGR_USER_RT: {
        TITLE: "备份配置信息",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来导入和还原用户配置信息。"
        }, {
            type: "name",
            title: "导入",
            content: "点击<导入>按钮来导入用户配置信息。"
        }]
     },
     SESSMNGR_LIST: {
        TITLE: "认证状态",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来查看认证状态。"
        }, {
            type: "name",
            title: "刷新",
            content: "手动刷新认证用户列表。"
        },{
            type: "name",
            title: "下线",
            content: "可实现批量断开用户连接。"
        }, {
            type: "name",
            title: "认证方式",
            content: "用户登录所使用的认证方式。"
        }, {
            type: "name",
            title: "接入时间",
            content: "用户接入时间。"
        }, {
            type: "name",
            title: "IP地址",
            content: "用户的IP地址。"
        }, {
            type: "name",
            title: "设置",
            content: "可断开用户的连接。"
        }, {
            type: "note",
            title: "提示",
            content: "当您希望获取用户的收发包速率、收发报文数量信息时，请您前往运行状态->流量统计->IP流量统计页面启用流量统计功能。"
        }]
     },
     DIA_ENABLE:{
        TITLE: "故障诊断模式",
        CONTENT: [{
            type: "paragraph",
            content: "您可以通过本页面来打开/关闭故障诊断模式。"
        }, {
            type: "name",
            title: "开启诊断模式:",
            content: "点击滑动开关来进行操作，蓝色表示开启诊断模式，灰色表示诊断模式关闭。开启本功能后可以配合技术支持人员对设备进行诊断。"
        }, {
            type: "name",
            title: "导出诊断信息:",
            content: "点击按钮下载基本的诊断信息，将其提供给技术人员以协助您分析和解决问题。"
        }, {
            type: "note",
            title: "注意",
            content: [
                "一般情况下请不要随意开启本功能。",
                "需要诊断时，请先联系技术支持人员，在其协助下打开并使用本功能。"
            ]
        }]

     },


     "" :     ""
    };
})(jQuery);