(function($){

	$.su = $.su || {};   $.su.CHAR = $.su.CHAR||{};
 $.su.CHAR.HELP ={
       IFSTAT :{ 
               TITLE:"Statistics List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the traffic statistics of the interfaces on this page."
                       } ,{                      
                           type: "name",
                           title: "Refresh",
                           content: "Click Refresh to view the latest traffic statistics of the interfaces."
                       } ,{                      
                           type: "name",
                           title: "Sort",
                           content: "Click the header to sort the column in ascending or descending order."
                       }]
},
       IP_STATS_SETTING :{ 
               TITLE:"IP Statistics",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can enable IP Statistics and configure the IP Range to be monitored on this page."
                       } ,{                      
                           type: "name",
                           title: "Enable IP Statistics",
                           content: "Check the box to enable IP Statistics."
                       } ,{                      
                           type: "name",
                           title: "IP Range",
                           content: "Specify the IP range to be monitored in the Statistics List."
                       }]
},
       IP_STATS_LIST :{ 
               TITLE:"Statistics List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the traffic statistics of the monitored IP addresses on this page."
                       } ,{                      
                           type: "name",
                           title: "Refresh",
                           content: "Click Refresh to view the latest traffic statistics of each IP address."
                       } ,{                      
                           type: "name",
                           title: "Sort",
                           content: "Click the header to sort the column in ascending or descending order."
                       }]
},
       INTERFACE_MODE :{ 
               TITLE:"WAN Mode",
               CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "1",
                           content: "Configure physical interface 1 as WAN1."
                       } ,{                      
                           type: "name",
                           title: "2",
                           content: "Configure physical interface 1 and interface 2 as WAN1 and WAN2 respectively."
                       } ,{                      
                           type: "name",
                           title: "3",
                           content: "Configure physical interface 1, interface 2  and interface3 as WAN1, WAN2  and WAN3 respectively."
                       } ,{                      
                           type: "name",
                           title: "4",
                           content: "Configure physical interface 1, interface 2, interface 3 and interface 4 as WAN1, WAN2, WAN3 and WAN4 respectively."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_MODE1 :{ 
               TITLE:"WAN Mode",
               CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "1",
                           content: "Configure physical interface 1 as WAN1."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_MODE2 :{ 
               TITLE:"WAN Mode",
               CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "1",
                           content: "Configure physical interface 1 as WAN1."
                       } ,{                      
                           type: "name",
                           title: "2",
                           content: "Configure physical interface 1 and interface 2 as WAN1 and WAN2 respectively."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_MODE3 :{ 
               TITLE:"WAN Mode",
               CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "1",
                           content: "Configure physical interface 1 as WAN1."
                       } ,{                      
                           type: "name",
                           title: "2",
                           content: "Configure physical interface 1 and interface 2 as WAN1 and WAN2 respectively."
                       } ,{                      
                           type: "name",
                           title: "3",
                           content: "Configure physical interface 1, interface 2  and interface3 as WAN1, WAN2  and WAN3 respectively."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_MODE4 :{ 
               TITLE:"WAN Mode",
               CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "1",
                           content: "Configure physical interface 1 as WAN1."
                       } ,{                      
                           type: "name",
                           title: "2",
                           content: "Configure physical interface 1 and interface 2 as WAN1 and WAN2 respectively."
                       } ,{                      
                           type: "name",
                           title: "3",
                           content: "Configure physical interface 1, interface 2  and interface3 as WAN1, WAN2  and WAN3 respectively."
                       } ,{                      
                           type: "name",
                           title: "4",
                           content: "Configure physical interface 1, interface 2, interface 3 and interface 4 as WAN1, WAN2, WAN3 and WAN4 respectively."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_MODE_SFP :{ 
               TITLE:"WAN Mode",
               CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "SFP WAN",
                           content: "Configure physical SFP interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Configure physical WAN interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "WAN/LAN1",
                           content: "Configure physical WAN/LAN1 interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "WAN/LAN2",
                           content: "Configure physical WAN/LAN2 interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_MODE_NOSFP :{ 
               TITLE:"WAN Mode",
                CONTENT: [{
                           type: "paragraph",
                           content: "Configure the number of WAN ports. When a WAN port is added, the port-related entries are automatically added; when a WAN port is deleted, the port-related entries are automatically deleted."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Configure physical WAN interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "WAN/LAN1",
                           content: "Configure physical WAN/LAN1 interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "WAN/LAN2",
                           content: "Configure physical WAN/LAN2 interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "WAN/LAN3",
                           content: "Configure physical WAN/LAN3 interface as WAN port."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The router will reboot after switching WAN mode. DO NOT operate the device during this process."
                       }]
},
       INTERFACE_WAN :{ 
               TITLE:"Connection Configuration",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the WAN port on this page."
                       } ,{                      
                           type: "name",
                           title: "Connection Type",
                           content: "If your ISP (Intrenet Service Provider) has provided you with a static IP address, select \"Static IP\";</br>If your ISP assigns the IP address automatically, select \"Dynamic IP\";</br>If your ISP has provided the account information for the PPPoE connection, select \"PPPoE\";</br>If your ISP has provided the account information for the L2TP connection, please choose\"L2TP\";</br>If your ISP has provided the account information for the PPTP connection, please choose \"PPTP\";</br>If your ISP has provided the account information for the BigPond connection, please choose \"BigPond\"."
                       } ,{                      
                           type: "name",
                           title: "Username",
                           content: "Enter your username. If you are unsure, please contact your ISP."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Enter your password. If you are unsure, please contact your ISP."
                       } ,{                      
                           type: "name",
                           title: "Connection Mode",
                           content: "You can select the Connection Mode according to your need.</br>Connect Automatically: Select this option to activate the connection automatically when the router reboots or the connection is down. </br>Connect Manually: Select this option to manually activate or terminate the connection by clicking the Connect or Disconnect button. </br> Time-based: During the specified period, the router will automatically activate the connection."
                       } ,{                      
                           type: "name",
                           title: "Host Name",
                           content: "Optional: Enter a name for the router. It is null by default. "
                       } ,{                      
                           type: "name",
                           title: "Upstream/Downstream Bandwidth",
                           content: "Specify the upstream/downstream bandwidth of the interface."
                       } ,{                      
                           type: "name",
                           title: "MTU",
                           content: "MTU (Maximum Transmission Unit) is the maximum data unit transmitted in the physical network. </br>When PPPoE is selected, MTU can be set in the range of 576-1492. The default value is 1492. </br>When Dynamic IP/Static IP/BigPond Cable is selected, MTU can be set in the range of 576-1500. The default value is 1500. </br>When L2TP is selected, MTU can be set in the range of 576-1460. The default value is 1460. </br>When PPTP is selected, MTU can be set in the range of 576-1420. The default value is 1420. "
                       } ,{                      
                           type: "name",
                           title: "Auth. Server",
                           content: "Enter the authenticating server's IP address or hostname."
                       } ,{                      
                           type: "name",
                           title: "Auth. Domain",
                           content: "Enter the server's domain name suffix (based on your location). For example, nsw.bigpond.net.au for NSW/ACT, vic.bigpond.net.au for VIC/TAS/WA/SA/NT, or qld.bigpond.net.au for QLD."
                       } ,{                      
                           type: "name",
                           title: "Service Name",
                           content: "Optional: Enter the Service Name provided by your ISP. It is null by default. "
                       } ,{                      
                           type: "name",
                           title: "Primary/Secondary DNS",
                           content: "Optional: Enter the DNS server's IP address, provided by your ISP. It's null by default."
                       } ,{                      
                           type: "name",
                           title: "Vlan",
                           content: "Specify the VLAN that the WAN port belongs to."
                       } ,{                      
                           type: "name",
                           title: "Get IP using Unicast DHCP",
                           content: "Select this checkbox if your ISP's DHCP server does not support broadcast applications and you cannot get the IP address dynamically."
                       } ,{                      
                           type: "name",
				title: "Secondary Connection",
				children: [{
					type: "step",
					content:[
                "None: Select if no secondary connection is provided. This mode is not available for L2TP/PPTP.",
                "Dynamic IP: Select if the IP address and subnet mask are assigned automatically by the ISP.",
                "Static IP: Select if the IP address and subnet mask are provided by the ISP, and enter this information into the corresponding fields."]
				}]
                       } ,{                      
                           type: "name",
                           title: "VPN Server IP/Domain Name",
                           content: "Enter the VPN server's IP address or domain name provided by your ISP."
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Enter the IP address of the WAN port provided by your ISP."
                       } ,{                      
                           type: "name",
                           title: "Subnet Mask",
                           content: "Enter the subnet mask provided by your ISP."
                       } ,{                      
                           type: "name",
                           title: "Default Gateway",
                           content: "Optional: Enter the IP address of the gateway provided by your ISP. It is null by default."
                       } ,{                      
                           type: "name",
                           title: "Primary/Secondary  DNS",
                           content: "Optional: Enter the DNS server's IP address provided by your ISP. It is null by default."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "name",
                           title: "Connect",
                           content: "Click Connect to activate the connection."
                       } ,{                      
                           type: "name",
                           title: "Disconnect",
                           content: "Click Disconnect to terminate the connection."
                       }]
},
       INTERFACE_WAN_STANDALONE :{ 
               TITLE:"Connection Configuration",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the WAN port on this page."
                       } ,{                      
                           type: "name",
                           title: "Connection Type",
                           content: "If your ISP (Intrenet Service Provider) has provided you with a static IP address, select \"Static IP\";</br>If your ISP assigns the IP address automatically, select \"Dynamic IP\";</br>If your ISP has provided the account information for the PPPoE connection, select \"PPPoE\";</br>If your ISP has provided the account information for the L2TP connection, please choose\"L2TP\";</br>If your ISP has provided the account information for the PPTP connection, please choose \"PPTP\"."
                       } ,{                      
                           type: "name",
                           title: "Username",
                           content: "Enter your username. If you are unsure, please contact your ISP."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Enter your password. If you are unsure, please contact your ISP."
                       } ,{                      
                           type: "name",
                           title: "Connection Mode",
                           content: "You can select the Connection Mode according to your need.</br>Connect Automatically: Select this option to activate the connection automatically when the router reboots or the connection is down. </br>Connect Manually: Select this option to manually activate or terminate the connection by clicking the Connect or Disconnect button. </br> Time-based: During the specified period, the router will automatically activate the connection."
                       } ,{                      
                           type: "name",
                           title: "Host Name",
                           content: "Optional: Enter a name for the router. It is null by default. "
                       } ,{                      
                           type: "name",
                           title: "Upstream/Downstream Bandwidth",
                           content: "Specify the upstream/downstream bandwidth of the interface."
                       } ,{                      
                           type: "name",
                           title: "MTU",
                           content: "MTU (Maximum Transmission Unit) is the maximum data unit transmitted in the physical network. </br>When PPPoE is selected, MTU can be set in the range of 576-1492. The default value is 1492. </br>When Dynamic IP/Static IP is selected, MTU can be set in the range of 576-1500. The default value is 1500. </br>When L2TP is selected, MTU can be set in the range of 576-1460. The default value is 1460. </br>When PPTP is selected, MTU can be set in the range of 576-1420. The default value is 1420. "
                       } ,{                      
                           type: "name",
                           title: "Service Name",
                           content: "Optional: Enter the Service Name provided by your ISP. It is null by default. "
                       } ,{                      
                           type: "name",
                           title: "Primary/Secondary DNS",
                           content: "Optional: Enter the DNS server's IP address, provided by your ISP. It's null by default."
                       } ,{                      
                           type: "name",
                           title: "Vlan",
                           content: "Specify the VLAN that the WAN port belongs to."
                       } ,{                      
                           type: "name",
                           title: "Get IP using Unicast DHCP",
                           content: "Select this checkbox if your ISP's DHCP server does not support broadcast applications and you cannot get the IP address dynamically."
                       } ,{                      
                           type: "name",
				title: "Secondary Connection",
				children: [{
					type: "step",
					content:[
                "None: Select if no secondary connection is provided. This mode is not available for L2TP/PPTP.",
                "Dynamic IP: Select if the IP address and subnet mask are assigned automatically by the ISP.",
                "Static IP: Select if the IP address and subnet mask are provided by the ISP, and enter this information into the corresponding fields."]
				}]
                       } ,{                      
                           type: "name",
                           title: "VPN Server IP/Domain Name",
                           content: "Enter the VPN server's IP address or domain name provided by your ISP."
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Enter the IP address of the WAN port provided by your ISP."
                       } ,{                      
                           type: "name",
                           title: "Subnet Mask",
                           content: "Enter the subnet mask provided by your ISP."
                       } ,{                      
                           type: "name",
                           title: "Default Gateway",
                           content: "Optional: Enter the IP address of the gateway provided by your ISP. It is null by default."
                       } ,{                      
                           type: "name",
                           title: "Primary/Secondary  DNS",
                           content: "Optional: Enter the DNS server's IP address provided by your ISP. It is null by default."
                       } ,{                      
                           type: "name",
                           title: "Save",
                           content: "Click Save to save the settings."
                       } ,{                      
                           type: "name",
                           title: "Connect",
                           content: "Click Connect to activate the connection."
                       } ,{                      
                           type: "name",
                           title: "Disconnect",
                           content: "Click Disconnect to terminate the connection."
                       }]
},
       WAN_STATUS :{ 
               TITLE:"Connection Status",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the connection status of the current WAN port."
                       }]
},
       INTERFACE_LAN :{ 
               TITLE:"LAN",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the parameters of the LAN port on this page."
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Enter the LAN IP address of the router. In the LAN, the default gateway address for all hosts must be the same as this one."
                       } ,{                      
                           type: "name",
                           title: "Subnet Mask",
                           content: "Enter the subnet mask (255.255.255.0 by default). In the LAN, the subnet mask for all hosts must be the same as this one."
                       } ,{                      
                           type: "name",
                           title: "Management Vlan",
                           content: "Only the hosts in this VLAN can manage this router. If not selected, it means all the computers in the LAN can manage this router."
                       }]
},
       INTERFACE_LAN_STANDALONE :{ 
               TITLE:"LAN",
               CONTENT: [{
                           type: "paragraph",
                           content: "When the LAN ports of the router connect to your local network devices, the router functions as the gateway, which allows those devices to connect to the internet."
                       },{
                           type: "name",
                           title: "Settings",
						children: [{                      
                           type: "name",
                           title: "IGMP Proxy",
                           content: "If you want the local network devices to receive multicast data from the internet, check the box to enable IGMP Proxy. This feature is used to detect whether there is any multicast member connected to the LAN ports."
                       } ,{                      
                           type: "name",
                           title: "IGMP Version",
                           content: "Configure the IGMP version as V2 or V3 according to your ISP."
                       } ,{ 
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the network."
                       } ,{  					   
                           type: "name",
                           title: "IP Address",
                           content: "Enter the IP address of the LAN port. To make your local network devices connect to the internet, you need to set the IP address of the LAN port as the default gateway of those devices."
                       } ,{                      
                           type: "name",
                           title: "Subnet Mask",
                           content: "Enter the subnet mask of the LAN port (255.255.255.0 by default). The IP addresses of all devices which connect to the LAN port should be in the same subnet as the IP address of the LAN port."
                       } ,{                      
                           type: "name",
                           title: "Vlan",
                           content: "Specify the VLAN of the LAN port, only the devices in the specified VLAN can access and manage the router."
                       }]},{
                           type: "name",
                           title: "DHCP Server",
						children: [{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable DHCP server."
                       } ,{                      
                           type: "name",
                           title: "Starting IP Address/ Ending IP Address",
                           content: "Enter the starting IP address and ending IP address of the DHCP server’s IP pool. The IP pool defines the range of IP addresses that can be assigned to the clients in the LAN. Note that the starting IP address and ending IP address should be in the same subnet as the IP address of the LAN port."
                       } ,{                      
                           type: "name",
                           title: "Lease Time",
                           content: "Specify the lease time for DHCP clients. Lease time defines how long the clients can use the IP address assigned by the DHCP server. Generally, the client will automatically request the DHCP server for extending the lease time before the lease expired. If the request fails, the client will have to stop using that IP address when the lease finally expired, and try to get a new IP address from another DHCP server."
                       } ,{                      
                           type: "name",
                           title: "Default Gateway",
                           content: "(Optional) Enter the default gateway which is assigned by the DHCP server. It is recommended to enter the IP address of the LAN port."
                       } ,{                      
                           type: "name",
                           title: "Default Domain",
                           content: "(Optional) Enter the domain name of your network."
                       } ,{                      
                           type: "name",
                           title: "Primary/Secondary DNS",
                           content: "(Optional) Enter the DNS server address provided by your ISP. If you are not clear, please consult your ISP."
                       }]},{
                           type: "name",
                           title: "Advanced Settings",
						children: [{                      
                           type: "name",
                           title: "Option60",
                           content: "(Optional) Enter the value for DHCP Option 60. DHCP clients use this field to optionally identify the vendor type and configuration of a DHCP client. Mostly, it is used in the scenario where the APs apply for different IP addresses from different servers according to the needs. For detailed information, please consult the vendor. For TP-Link, this entry should be TP-Link."
                       } ,{                      
                           type: "name",
                           title: "Option66",
                           content: "(Optional) Enter the value for DHCP Option 66. It specifies the TFTP server information and supports a single TFTP server IP address."
                       } ,{                      
                           type: "name",
                           title: "Option138",
                           content: "(Optional) Enter the value for DHCP Option 138. It is used in discovering the devices by the Omada controller."
                       } ,{                      
                           type: "name",
                           title: "Option150",
                           content: "(Optional) Enter the value for DHCP Option 150. It specifies the TFTP server information and supports multiple TFTP server IP addresses."
                       } ,{                      
                           type: "name",
                           title: "Option159",
                           content: "(Optional) Enter the value for DHCP Option 159. This option is used to configure a set of ports bound to a shared IPv4 address."
                       } ,{                      
                           type: "name",
                           title: "Option160",
                           content: "(Optional) Enter the value for DHCP Option 160. This option is used to configure DHCP captive portal."
                       } ,{                      
                           type: "name",
                           title: "Option176",
                           content: "(Optional) Enter the value for DHCP Option 176. This option is used to configure parameters for IP phones."
                       } ,{                      
                           type: "name",
                           title: "Option242",
                           content: "(Optional) Enter the value for DHCP Option 242. This option is used to provide the TMS address automatically."
                       }]}]
},
       DHCP_SERVER_SETTINGS :{ 
               TITLE:"DHCP Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the DHCP server on this page."
                       } ,{                      
                           type: "name",
                           title: "Starting IP Address",
                           content: "Enter the starting IP address to define a range for the DHCP server to assign dynamic IP addresses."
                       } ,{                      
                           type: "name",
                           title: "Ending IP Address",
                           content: "Enter the ending IP address to define a range for the DHCP server to assign dynamic IP addresses. The ending IP address should be greater than the starting IP address."
                       } ,{                      
                           type: "name",
                           title: "Lease Time",
                           content: "Specify the lease duration of the IP address assigned by the DHCP server. "
                       } ,{                      
                           type: "name",
                           title: "Default Gateway",
                           content: "Optional: Enter the Gateway address to be assigned. It is recommended to enter the IP address of the LAN port of the router."
                       } ,{                      
                           type: "name",
                           title: "Default Domain",
                           content: "Optional: Enter the your local domain name."
                       } ,{                      
                           type: "name",
                           title: "Primary/Secondary  DNS",
                           content: "Optional: Enter the DNS server address provided by your ISP. If you are unsure, please consult your ISP."
                       } ,{                      
                           type: "name",
                           title: "Option60",
                           content: "Optional: Enter the information of the vender. For detailed information, please consult the vender. For TP-Link, it's TP-Link."
                       } ,{                      
                           type: "name",
                           title: "Option66",
                           content: "Optional: Enter the TFTP server host name."
                       } ,{                      
                           type: "name",
                           title: "Option138",
                           content: "Optional: Enter the IP address of the AC (Wireless Controller)."
                       } ,{                      
                           type: "name",
                           title: "Option150",
                           content: "Optional: Enter the option 150."
                       } ,{                      
                           type: "name",
                           title: "Option159",
                           content: "Optional: Enter the option 159."
                       } ,{                      
                           type: "name",
                           title: "Option160",
                           content: "Optional: Enter the option 160."
                       } ,{                      
                           type: "name",
                           title: "Option176",
                           content: "Optional: Enter the option 176."
                       } ,{                      
                           type: "name",
                           title: "Option242",
                           content: "Optional: Enter the option 242."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable DHCP server."
                       }]
},
       DHCP_CLIENT_LIST :{ 
               TITLE:"DHCP Client List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of DHCP clients on this page."
                       } ,{                      
                           type: "name",
                           title: "Client Name",
                           content: "Displays the host name of the DHCP client. It should be composed of digits, English letters, dashes and underscores only."
                       } ,{                      
                           type: "name",
                           title: "MAC Address",
                           content: "Displays the MAC address of the DHCP client."
                       } ,{                      
                           type: "name",
                           title: "Assigned IP Address",
                           content: "Displays the IP address assigned to the DHCP client."
                       } ,{                      
                           type: "name",
                           title: "Lease Time",
                           content: "Displays the remaining lease time of the assigned IP address. After the lease expires, the IP address will be re-assigned."
                       }]
},
       DHCP_STATIC :{ 
               TITLE:"Address Reservation",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can reserve an IP address for the specified MAC address on this page. The client with this MAC address will always be assigned this IP address from the DHCP server."
                       } ,{                      
                           type: "name",
                           title: "MAC Address",
                           content: "Enter the MAC address of the host for which the IP address will be reserved."
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Enter the reserved IP address."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the entry. Up to 50 characters can be entered."
                       } ,{                      
                           type: "name",
                           title: "Export to IP-MAC Binding",
                           content: "Export this entry to the IP-MAC Binding list. The IP-MAC Binding list is on Firewall > Anti ARP Spoofing > IP-MAC Binding page."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable this entry."
                       }]
},
       IPTV :{ 
               TITLE:"Settings",
               CONTENT: [{
                           type: "name",
                           title: "IGMP Snooping",
                           content: "Check the box to enable IGMP (Internet Group Management Protocol) Snooping feature."
                       } ,{                      
                           type: "name",
                           title: "IGMP Proxy",
                           content: "Check the box to enable IGMP (Internet Group Management Protocol) Proxy feature."
                       } ,{                      
                           type: "name",
                           title: "IGMP Version",
                           content: "Configure the IGMP Proxy version as V2 or V3 according to your ISP."
                       } ,{                      
                           type: "name",
                           title: "IPTV",
                           content: "Check the box to enable IPTV."
                       } ,{                      
					type: "name",
					title: "Mode",
					content: "Select the appropriate mode according to your ISP. There are two supported IPTV modes:",
					children: [{
						type:"step",
						content: [
							"Bridge",
							"Custom"
						]
					}]
				},{
					type: "name",
					title: "Bridge",
					content:"If no other parameters are required, you can simply select this mode and configure the LAN port features of the router.",
					children:[{
						type: "step",
						content: [
                "Port Mode: Assign your switch ports to function either as the internet supplier or as the IPTV supplier."
						]
					}]
				},
				{
					type: "name",
					title: "Custom",
					content: "Select if your ISP provides the necessary parameters, including Internet/IP-Phone/IPTV VLAN IDs and Priority, and LAN port features.",
					children: [{
						type: "step",
						content:[
							"Internet/IP-Phone/IPTV VLAN ID/Priority: Configure the VLAN IDs and priorities as provided by your ISP.",
							"802.1Q Tag: Select whether to tag the Internet packets with 802.1Q.",
							"IPTV Multicast VLAN ID/Priority: You can enable the IPTV multicast feature as desired, and configure the VLAN ID and Priority according to your ISP.",
                "Port Mode: Assign your switch ports to function as an internet supplier, IP-phone supplier or IPTV supplier."
						]
					}]
				},{
					type:"paragraph",
                           content: "Click Save to save the settings."
				}
			]
		},
       INTERFACE_MAC :{ 
               TITLE:"MAC ",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the MAC address of the router's interfaces."
                       } ,{                      
                           type: "name",
                           title: "Interface Name ",
                           content: "Displays the router's WAN and LAN interfaces."
                       } ,{                      
                           type: "name",
                           title: "Current MAC Address",
                           content: "Displays the MAC address of the corresponding interface."
                       } ,{                      
                           type: "name",
                           title: "Restore Factory MAC ",
                           content: "Click this button to restore the MAC address to the factory default value. Then click Save to save the settings."
                       } ,{                      
                           type: "name",
                           title: "Clone Current PC's MAC ",
                           content: "Click this button to clone the MAC address of the current management host. Then click Save to save the settings."
                       } ,{                      
                           type: "note",
                           title: "Note ",
       content: [ 
                "When cloning curent management host's MAC on the WAN port, the management PC should be connected to the LAN port. ",
                "If the connection type on the WAN port is PPPoE, L2TP or PPTP, changing the MAC address of the WAN port may cause the connection to be terminated (Connect Manually Mode) or re-established (Connect Automatically Mode)."]
	}]
},
       SWITCH_PORT_STATISTICS :{ 
               TITLE:"Statistics List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the detailed traffic information of each port, which facilitates you to monitor the traffic and manage the network effectively."
                       } ,{                      
                           type: "name",
                           title: "Unicast",
                           content: "Displays the number of normal unicast packets received or transmitted on the port."
                       } ,{                      
                           type: "name",
                           title: "Broadcast",
                           content: "Displays the number of normal broadcast packets received or transmitted on the port."
                       } ,{                      
                           type: "name",
                           title: "Pause",
                           content: "Displays the number of flow control frames received or transmitted on the port."
                       } ,{                      
                           type: "name",
                           title: "Mulitcast",
                           content: "Displays the number of normal multicast packets received or transmitted on the port."
                       } ,{                      
                           type: "name",
                           title: "Total",
                           content: "Displays the total bytes of the received or transmitted packets (including error frames)."
                       } ,{                      
                           type: "name",
                           title: "Undersize",
                           content: "Displays the number of received packets which have a length less than 64 bytes (including error frames)."
                       } ,{                      
                           type: "name",
                           title: "Normal",
                           content: "Displays the number of received packets which have length between 64 bytes and the maximum frame length (including error frames)."
                       } ,{                      
                           type: "name",
                           title: "Oversize",
                           content: "Displays the number of received packets that have a length greater than the maximum frame length (including error frames)."
                       } ,{                      
                           type: "name",
                           title: "Refresh",
                           content: "Click Refresh to view the latest traffic statistics of each port."
                       } ,{                      
                           type: "name",
                           title: "Clear",
                           content: "Click Clear to clear all the traffic statistcs."
                       } ,{                      
                           type: "note",
                           title: "Note ",
       content: [ 
                "Error frame: The frames that have a false checksum.",
                "Maximum frame length: The maximum frame length supported by the router. For untagged frames, it's 1518 bytes long; for tagged packets, it's 1522 bytes long."]
	}]
},
       SWITCH_MONITOR_ENABLE :{ 
               TITLE:"Enable Port Mirror",
               CONTENT: [{
                           type: "paragraph",
                           content: "Check the box to enable Port Mirror function. There are three Mirror Modes:",
       children: [{                      
                           type: "step",
       content: [ 
                "Ingress and Egress: Both the incoming and outgoing packets through the mirrored port will be copied to the mirroring port.",
                "Ingress: The packets received by the mirrored port will be copied to the mirroring port.",
                "Egress: The packets sent by the mirrored port will be copied to the mirroring port."]
}]
}]
},
       SWITCH_MONITOR_SETTING :{ 
               TITLE:"Monitor List",
               CONTENT: [{
                           type: "name",
                           title: "Mirroring Port",
                           content: "The packets through the mirrored port will be copied to this port."
                       } ,{                      
                           type: "name",
                           title: "Mirrored Port",
                           content: "The packets through this port will be copied to the mirroring port."
                       } ,{                      
                           type: "note",
                           title: "Note ",
       content: [ 
                "A port cannot be configured as the mirrored port and the mirroring port simultaneously.",
                "Only one port can be configured as the mirroring port."]
}]
},
       SWITCH_PORTLIMIT :{ 
               TITLE:"Rate Control",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can limit the traffic rate for the specific packets on each port to manage the network flow on this page."
                       } ,{                      
                           type: "name",
                           title: "Ingress Limit",
                           content: "Check the box to enable the Ingress Limit feature."
                       } ,{                      
                           type: "name",
                           title: "Ingress Frame Type",
                           content: "Specify the ingress frame type to be limited. It is All Frames by default.",
                           children: [{                      
                           type: "step",
                           content: [ 
                              "All Frames: The ingress rate of all frames is limited.",
                              "Broadcast: The ingress rate of broadcast frames is limited.",
                              "Broadcast and Multicast: The ingress rate of broadcast and multicast frames is limited."]
                           }]
                       } ,{                      
                           type: "name",
                           title: "Ingress Rate(Mbps)",
                           content: "Specify the limit rate for the ingress packets."
                       } ,{                      
                           type: "name",
                           title: "Egress Limit",
                           content: "Check the box to enable Egress Limit feature."
                       } ,{                      
                           type: "name",
                           title: "Egress Rate(Mbps)",
                           content: "Specify the limit rate for the egress packets."
                       }]
},
       SWICH_PARAMETER :{ 
               TITLE:"Port Config",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the basic parameters of the port."
                       } ,{                      
                           type: "name",
                           title: "Flow Control",
                           content: "Check the box to enable Flow Control function for the port."
                       } ,{                      
                           type: "name",
                           title: "Negotiation Mode",
                           content: "Select the Negotiation Mode for the port. You can select Auto (Auto-negoation), or manually select the speed and duplex mode."
                       }]
},
       SWITCH_STATUS :{ 
               TITLE:"Port Status",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the status of each port on this page."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "There are two types of port status:",
       children: [{                      
                           type: "step",
       content: [ 
                "Link Down: The port is not connected.",
                "Link Up: The port is working normally."]
}]
} ,{                      
                           type: "name",
                           title: "Speed(Mbps)",
                           content: "Displays the speed of the port."
                       } ,{                      
                           type: "name",
                           title: "Duplex Mode",
                           content: "Displays the duplex mode, including Full-duplex and Half-duplex."
                       } ,{                      
                           type: "name",
                           title: "Flow Control",
                           content: "Displays if the Flow Control is enabled."
                       }]
},
       VLAN_VLAN_SETTING :{ 
               TITLE:"VLAN Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "By creating VLANs, you can divide the LAN into multiple logical LANs, which lets you flexibly control the communication among the ports."
                       } ,{                      
                           type: "name",
                           title: "VLAN ID",
                           content: "VLAN ID is used to specify the ID of VLAN TAG in IEEE 802.1Q, which identifies the number of VLANs the packets belong to. Ports in the same VLAN can communicate with each other. Ports in different VLANs cannot communicate directly."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the VLAN for easy identification."
                       } ,{                      
                           type: "name",
                           title: "Ports",
                           content: "Specify the port type in the specified VLAN. The ports can be divided into two types: TAG or UNTAG."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for easy management and searching."
                       }]
},
       VLAN_VLAN_SETTING_NO_GENERAL :{ 
               TITLE:"VLAN Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "By creating VLANs, you can divide the LAN into multiple logical LANs, which lets you flexibly control the communication among the ports."
                       } ,{                      
                           type: "name",
                           title: "VLAN ID",
                           content: "VLAN ID is used to specify the ID of VLAN TAG in IEEE 802.1Q, which identifies the number of VLANs the packets belong to. Ports in the same VLAN can communicate with each other. Ports in different VLANs cannot communicate directly."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the VLAN for easy identification."
                       } ,{                      
                           type: "name",
                           title: "Ports",
                           content: "Specify the port type in the specified VLAN. The ports can be divided into two types: TAG or UNTAG."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for easy management and searching."
                       }]
},
       VLAN_VLANLIST :{ 
               TITLE:"VLAN List",
               CONTENT: [{
                           type: "paragraph",
                           content: "View the VLAN information in the list and customize the VLAN settings by pressing the buttons."
                       } ,{                      
                           type: "note",
                           title: "Note",
       content: [ 
                "1. Some VLANs are automatically and randomly referenced by the system, and cannot be edited or deleted. When the WAN mode or IPTV settings are changed, the referenced VLANs may be different.",
                "2. For more VLAN settings, please go to the Ports page."]
}]
},
       VLAN_PORT_SETTING :{ 
               TITLE:"Ports",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can change the PVID on this page according to your network deployment."
                       } ,{                      
                           type: "name",
                           title: "PVID",
                           content: "Specify the PVID for the ports."
                       },{                      
                           type: "name",
                           title: "VLAN",
                           content: "Displays the VLAN(s) the port belongs to."
                       }]
},
       VLAN_PORT_SETTING_NO_GENERAL :{ 
               TITLE:"Ports",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can change the PVID on this page according to your network deployment."
                       } ,{                      
                           type: "name",
                           title: "PVID",
                           content: "Specify the PVID for the ports."
                       },{                      
                           type: "name",
                           title: "VLAN",
                           content: "Displays the VLAN(s) the port belongs to."
                       }]
},
       VLAN_RELATION_TABLE :{ 
               TITLE:"Relations",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the port and its VLAN information on this page."
                       } ,{                      
                           type: "name",
                           title: "VLAN",
                           content: "Displays the VLAN(s) the port belongs to."
                       }]
},
    IPV6_GENERAL: {
      TITLE: "General",
      CONTENT: [{
        type: "name",
        title: "IPv6",
		content: "IPv6 is the next-generation network protocol after IPv4. You can configure IPv6 network for the router if your ISP supports IPv6. IPv6 network won’t cause conflict with your current IPv4 network. Check the box to enable IPv6."
      }]
    },
  	IPV6_LAN: {
			TITLE: "LAN",
			CONTENT: [{
                type: "paragraph",
                content: "Configure IPv6 for the LANs."
            },{
				type: "name",
				title: "Assigned Type",
                content: "Determines the method whereby the router assigns IPv6 addresses to the clients in your local network. Some clients may support only a few of these assigned types, so you should choose it according to the compatibility of clients in your local network."
			},{
				type: "name",
				title: "LAN(VLAN)",
                content: "The name of LAN you have created in Network > LAN."
			},{
				type: "name",
				title: "None",
				content: "Disable IPv6 of the LAN port.",
			},{
				type: "name",
				title: "DHCPv6",
				content: "The router assigns an IPv6 address and other parameters including the DNS server address to each client using DHCPv6.",
				children: [{
					type: "step",
					content: [
						"IPv6 Address: Enter the IPv6 address and prefix length (subnet mask).",
						"DHCP Range: Enter the starting and ending IPv6 address to define a range for the DHCPv6 server to assign dynamic IPv6 addresses.",
						"Lease Time: The duration time in minutes when the assigned IPv6 address remains valid. Either keep the default 1440 minutes or change it if required.",
						"DNS Address: Select a method to configure the DNS server for the LAN. With Auto selected, the DNS server addresses are automatically obtained. With Manual DNS selected, manually enter the primary and secondary DNS server addresses provided by your ISP.",
						"Address: Displays the IPv6 address of the LAN port.",
					]
				}]
			},{
				type: "name",
				title: "SLAAC+Stateless DHCP",
				content: "The router assigns the IPv6 address prefix to each client and the client automatically generates its own IPv6 address. Also, the gateway assigns other parameters including the DNS server address to each client using DHCPv6.",
				children: [{
					type: "step",
					content: [
						"Prefix: Configure the IPv6 address prefix for each client in the local network. With Manual Prefix selected, enter the prefix in the Address Prefix field. With Get from Prefix Delegation selected, select the IPv6 Prefix Delegation WAN port, and enter the IPv6 Prefix ID to get a prefix delegation from the ISP.",
						"Get from Prefix Delegation WAN: Enter the IPv6 Prefix Delegation WAN port and the IPv6 Prefix ID to get a prefix delegation from the ISP.",
						"IPv6 Prefix ID: With Get from Prefix Delegation selected, enter the Prefix ID, which will be added to the prefix to obtain a /64 subnet. The range of IPv6 Prefix ID is determined by Prefix Delegation Size and Prefix Length.",
						"DNS Address: Select a method to configure the DNS server for the LAN. With Auto selected, the DNS server addresses are automatically obtained. With Manual DNS selected, manually enter the primary and secondary DNS server addresses provided by your ISP.",
						"Address: The IPv6 address automatically generated by Prefix.",
					]
				}]
			},{
				type: "name",
				title: "SLAAC+RDNSS",
				content: "The router assigns the IPv6 address prefix to each client and the client automatically generates its own IPv6 address. Also, the gateway assigns other parameters including the DNS server address to each client using the RDNSS option in RA (Router Advertisement).",
				children: [{
					type: "step",
					content: [
						"Prefix: Configure the IPv6 address prefix for each client in the local network. With Manual Prefix selected, enter the prefix in the Address Prefix field. With Get from Prefix Delegation selected, select the IPv6 Prefix Delegation WAN port, and enter the IPv6 Prefix ID to get a prefix delegation from the ISP.",
						"Get from Prefix Delegation WAN: Enter the IPv6 Prefix Delegation WAN port and the IPv6 Prefix ID to get a prefix delegation from the ISP.",
						"IPv6 Prefix ID: With Get from Prefix Delegation selected, enter the Prefix ID, which will be added to the prefix to obtain a /64 subnet. The range of IPv6 Prefix ID is determined by Prefix Delegation Size and Prefix Length.",
						"DNS Address: Select a method to configure the DNS server for the LAN. With Auto selected, the DNS server addresses are automatically obtained. With Manual DNS selected, manually enter the primary and secondary DNS server addresses provided by your ISP.",
						"Address: The IPv6 address automatically generated by Prefix.",
					]
				}]
			},{
				type: "name",
				title: "Pass-Through(Bridge)",
				content: "Select this type if the WAN ports of the gateway use the Pass-Through for IPv6 connections.",
				children: [{
					type: "step",
					content: [
						"IPv6 Passthrough WAN: Select the WAN port using Pass-Through (Bridge) for the IPv6 connection.",
					]
				}]
			},{
				type: "paragraph",
                content: "Click OK to save the settings."
			}]
		},
		IPV6: {
			TITLE: "Internet",
			CONTENT: [{
				type: "name",
        		title: "Internet Connection Type",
				content: "Choose the proper Internet Connection Type according to the requirements of your ISP."
			},{
				type: "name",
				title: "Static IP",
        		content: "Select this type if your ISP provides you with a static IPv6 address.",
        		children: [{
          		type: "step",
          		content: [
            		"IPv6 Address/Prefix Length/Default Gateway/Primary DNS/Secondary DNS: Enter these parameters as provided by the ISP.",
            		/*"MTU Size: The default and typical MTU (Maximum Transmission Unit) size for most Ethernet networks is 1500 Bytes. It is NOT recommended to change the default MTU size unless required by the ISP.",*/
          		]
        	}]
			},{
				type: "name",
				title: "Dynamic IP (SLAAC/DHCPv6)",
        		content: "Select this type if your ISP uses Dynamic IPv6 address assignment, either DHCPv6 or SLAAC+Stateless DHCP.",
        		children: [{
          		type: "step",
          		content: [
            		"IPv6 Address/Primary DNS/Secondary DNS: These parameters are automatically assigned by your ISP.",
                	"Renew: Click this button to get new IPv6 parameters assigned by your ISP.",
            		"Release: Click this button to release all IPv6 addresses assigned by your ISP."
          		]},
          		{
					type: "paragraph",
					content: "Advanced"
				},
          		{
          		type: "step",
          		content: [
            		"Get IPv6 Address: Select the proper method whereby your ISP assigns IPv6 address to your router. <br>Auto: Select Auto to get an IPv6 address automatically. <br>DHCPv6: Your ISP assigns an IPv6 address and other parameters including the DNS server address to your router using DHCPv6. <br>SLAAC+Stateless DHCP: Your ISP assigns the IPv6 address prefix to your router and your router automatically generates its own IPv6 address. Also, your ISP assigns other parameters including the DNS server address to your router using DHCPv6.",
            		"Prefix Delegation: Select Enable to get an address prefix for your LAN port from your ISP, or Disable to designate an address prefix for your LAN port manually. Clients in LAN will get an IPv6 address with this prefix.",
            		"Prefix Delegation Size: With Prefix Delegation enabled, enter the Prefix Delegation Size to determine the length of the address prefix. You can get this value from your ISP.", 
                	"DNS Address: Select whether to get the DNS address dynamically from your ISP or designate the DNS address manually. <br>Get dynamically from ISP: Your ISP assigns an DNS address to your router dynamically. <br>Use the following DNS Addresses: You should manually enter the DNS address provided by your ISP.",
            		"Primary DNS/Secondary DNS: Enter the DNS address manually or display the DNS address which is assigned by your ISP."
          		]}
			]
			},{
				type: "name",
				title: "PPPoE",
        		content: "Select this type if your ISP uses PPPoEv6, and provides a username and password.",
        		children: [
        			{
          			type: "step",
          			content: [
          				"PPPoE same session with IPv4 connection: If this option is enabled, IPv6 uses the same PPPoE session as IPv4.",
            			"Username/Password: Enter these parameters as provided by your ISP.",
            			"IPv6 Address: This address will be automatically assigned by your ISP after you enter the username and password and click Connect."
            		]},
            		{
					type: "paragraph",
					content: "Advanced"
					},
            		{
          			type: "step",
          			content: [
            			"Get IPv6 Address: Select the proper method whereby your ISP assigns IPv6 address to your router. <br>Auto: Select Auto to get an IPv6 address automatically. <br>DHCPv6: Your ISP assigns an IPv6 address and other parameters including the DNS server address to your router using DHCPv6. <br>SLAAC+Stateless DHCP: Your ISP assigns the IPv6 address prefix to your router and your router automatically generates its own IPv6 address. Also, your ISP assigns other parameters including the DNS server address to your router using DHCPv6. <br>Specified by ISP: You should manually enter the IPv6 address provided by your ISP.",
            			"Prefix Delegation: Select Enable to get an address prefix for your LAN port from your ISP, or Disable to designate an address prefix for your LAN port manually.",
            			"Prefix Delegation Size: With Prefix Delegation enabled, enter the Prefix Delegation Size to determine the length of the address prefix. You can get this value from your ISP.", 
                		"DNS Address: Select whether to get the DNS address dynamically from your ISP or designate the DNS address manually. <br>Get dynamically from ISP: Your ISP assigns an DNS address to your router dynamically. <br>Use the following DNS Addresses: You should manually enter the DNS address provided by your ISP.",
                		"Primary DNS/Secondary DNS: Enter the DNS address manually or display the DNS address which is assigned by your ISP.",
                		"Connect: Click this button to connect to the internet.",
                		"Disconnect: Click this button to disconnect from the internet."
          			]}
				]
			},{
				type: "name",
				title: "6to4 Tunnel",
				content: "Select this type if your ISP uses 6to4 deployment for assigning address.",
        		children: [{
          			type: "step",
          			content: [
            			"IPv4 Address/IPv4 Subnet Mask/IPv4 Default Gateway/Tunnel Address: These parameters will be dynamically generated by the IPv4 information of WAN port after you click Connect."
            		]},
            		{
					type: "paragraph",
					content: "Advanced"
					},
            		{
          			type: "step",
          			content: [
            			"Use the following DNS Server: Check the box to manually enter the primary DNS and/or secondary DNS as provided by your ISP.",
                		"Connect: Click this button to connect to the internet.",
                		"Disconnect: Click this button to disconnect from the internet."
          			]}
				]
			},/*{
				type: "title",
				title: "Internet Connection Type: 6RD"
			},{
				type: "name",
				title: "6RD",
				content: "Select this type if your ISP uses 6RD deployment and provides an IPv4 address and IPv6 address prefixes."
			},{
				type: "name",
				title: "Configuration Type",
				content: "Select Auto or Manual for configuring the 6RD channel parameters according to your ISP. If the default parameters below coincide with those provided by your ISP, you can select Auto; otherwise, select Manual and enter the parameters as provided by your ISP."
			},{
				type: "name",
				title: "IPv4 Mask Length/6RD Prefix/6RD Prefix Length/Border Reply IPv4 Address",
				content: "Check if the preset parameters coincide with those provided by your ISP. You can either keep the defaults or manually enter the parameters as provided by your ISP."
			},{
				type: "title",
				title: "Internet Connection Type: DS-Lite"
			},{
				type: "name",
				title: "DS-Lite",
				content: "Select this type if your ISP uses DS-Lite deployment and provides an AFTR domain name or IPv6 address for setting up an IPv4-in-IPv6 tunnel in the IPv6 network to communicate IPv4 traffics or IPv6 traffics in their own respective network."
			},{
				type: "name",
				title: "AFTR Name",
				content: "AFTR is short for Address Family Transition Router. In this field, enter the AFTR domain name or IPv6 address as provided by your ISP."
			},{
				type: "name",
				title: "Secondary Connection",
				content: "Select the secondary connection type as provided by your ISP.",
				children :[ 
				{
					type: "name",
					title: "Dynamic IP",
					content: "Select if your ISP provides Dynamic IP as the secondary connection type and the parameters, IPv6 Address, primary DNS and/or secondary DNS will be automatically assigned by DHCPv6 server from the ISP."
				},
				{
					type: "name",
					title: "Static IP",
					content: "Select if your ISP provides Static IP as the secondary connection type and enter the IPv6 Address, default gateway, primary DNS and/or secondary DNS as provided by your ISP, then configure the MTU size manually (if required) or keep the default value."
				},{
					type: "name",
					title: "PPPoE",
					content: "Select if your ISP provides PPPoE as the secondary connection type and enter the username and password as provided by your ISP. The IPv6 address will be automatically assigned after you click Connect."
				}]
			},*/{
				type: "name",
        		title: "Pass-Through (Bridge)",
				content: "Select this type if your ISP uses Pass-Through (Bridge) network deployment."
			},{
				type: "paragraph",
				content: "No extra parameter is required. Click Save to save the settings."
			}]
		},
       IPGROUP_GROUP_SETTING :{ 
               TITLE:"Group List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can define different address groups on this page."
                       } ,{                      
                           type: "name",
                           title: "Group Name",
                           content: "Specify the name of the address group."
                       } ,{                      
                           type: "name",
                           title: "Address Name",
                           content: "One address group can contain multiple IP addresses. The rule that references the address group will take effect on all the IP addresses contained in the address group."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the address group to facilitate your management. It can be 50 characters at most."
                       } ,{                      
                           type: "note",
                           title: "Note",
       content: [ 
                "The address group that has been referenced by a rule cannot be deleted unless the rule no longer references the address group.",
                "The address group can be null, which means no address entries are contained. The rule that references the address group will not take effect on any IP addresses."]
}]
},
       IPGROUP_ADDRESS_SETTING :{ 
               TITLE:"IP Address List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can define the IP address entry for management on this page."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the address entry."
                       } ,{                      
                           type: "name",
                           title: "IP Address Type",
                           content: "Specify the type of the address entry. There are two types as follows:",
       children: [{                      
                           type: "step",
       content: [ 
                "IP Address Range: Specify a starting IP address and an ending IP address. The rule that references the address group will be applied to the IP address range in the group.",
                "IP Address/Mask: Specify a network address and a subnet mask. The rule that references the address group will be applied to each address entry in the group."]
}]
} ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the IP address entry to facilitate your management. It can be 50 characters at most."
                       }]
},
       TIME_MNGT_SETTING :{ 
               TITLE:"Time Range List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can define the time-range entry for management on this page.<br>The time-range entry can only be applied to the specific days in a week but not a specific date."
                       } ,{                      
                           type: "name",
                           title: "Time Range Name",
                           content: "Specify the name of the time-range entry."
                       } ,{                      
                           type: "name",
                           title: "Time Settings",
                           content: "Specify the time slice contained in the time-range. There are two types:",
       children: [{                      
                           type: "step",
       content: [ 
                "Working Calendar: Select the rectangle displayed on the page to specify the time slice. It can only be accurate to one hour.",
                "Manual: Input the time range and select the effective week  to specify the time slice.  It can be accurate to one minute. At most 12 time slices can be configured in one time range."]
}]
} ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the time range entry to facilitate your management. It can be 32 characters at most."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The time range that has been referenced by a rule cannot be deleted unless the rule no longer references the time range."
                       }]
},
       IP_POOL_LIST :{ 
               TITLE:"VPN IP Pool List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can define the IP address pool entry for management on this page."
                       } ,{                      
                           type: "name",
                           title: "IP Pool Name",
                           content: "Specify the name of the IP Pool."
                       } ,{                      
                           type: "name",
                           title: "Starting IP Address",
                           content: "Specify the starting IP address of the IP Pool."
                       } ,{                      
                           type: "name",
                           title: "Ending IP Address",
                           content: "Specify the ending IP address of the IP Pool."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "The starting IP address should not be greater than the ending IP address. The ranges of IP Pools cannot overlap."
                       }]
},
       SERVICE_TYPE :{ 
               TITLE:"Service Type",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can define the service type entry for management on this page."
                       } ,{                      
                           type: "name",
                           title: "Service Type Name",
                           content: "Specify the name of the service type. The name cannot be same as that of the service type predefined by the system."
                       } ,{                      
                           type: "name",
                           title: "Protocol",
                           content: "Specify the protocol for the service. The system predefined protocols include TCP, UDP, TCP/UDP and ICMP. You can also choose Other and input the protocol  number (0-255)."
                       } ,{                      
                           type: "name",
                           title: "Source Port Range",
                           content: "Specify the source port range for the service. It can be configured only when you choose TCP, UDP or TCP/UDP."
                       } ,{                      
                           type: "name",
                           title: "Destination Port Range",
                           content: "Specify the destination port range for the service. It can be configured only when you choose TCP, UDP or TCP/UDP."
                       } ,{                      
                           type: "name",
                           title: "ICMP",
                           content: "Specify the type and code for ICMP. 255 means all the types/codes are included.  It can be configured only when you choose ICMP."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the service type."
                       }]
},
       NAPT :{ 
               TITLE:"Multi-Nets NAT",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the rules and edit them by clicking the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interface for the rule only when the connection type is Static IP."
                       } ,{                      
                           type: "name",
                           title: "Source IP Range",
                           content: "Specify the source IP range for the rule."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Enable or disable the rule."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the rule entry to facilitate your management."
                       }]
},

       ONE_NAT :{ 
               TITLE:"One-to-One NAT",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the rules and edit them by clicking the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interface for the rule only when the connection type is Static IP."
                       } ,{                      
                           type: "name",
                           title: "Original IP",
                           content: "Specify the original IP address for the rule, which means the device's private IP. The original IP address cannot be the broadcast address, network segment or interface IP. With One-to-One NAT enabled, the original IP will map to the translated IP."
                       } ,{                      
                           type: "name",
                           title: "Translated IP ",
                           content: "Specify the translated IP address for the rule, which means the public IP of device. The translated IP address cannot be the broadcast address, network segment or interface IP. With One-to-One NAT enabled, the original IP will map to the translated IP."
                       } ,{                      
                           type: "name",
                           title: "DMZ Forwarding",
                           content: "Choose to enable DMZ Forwarding. The packets transmitted to the  translated IP address will be forwarded to the host with the original IP address if DMZ Forwarding is enabled. "
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the rule entry to facilitate your management."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       VIRTUAL_SERVER :{ 
               TITLE:"Virtual Server",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the rules and edit them by clicking the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interface for the rule."
                       } ,{                      
                           type: "name",
                           title: "External Port",
                           content: "Enter the service port or port range of the router for external network's access. The ports or port ranges cannot overlap with those of other virtual server rules. "
                       } ,{                      
                           type: "name",
                           title: "Internal Port",
                           content: "Specify the service port of the LAN host which acts as the server."
                       } ,{                      
                           type: "name",
                           title: "Internal Server IP",
                           content: "Enter the IP address of the LAN host which acts as the server. All the requests from the internet to the specified LAN port will be redirected to this host.  "
                       } ,{                      
                           type: "name",
                           title: "Protocol",
                           content: "Specify the protocol used for the entry."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},

       PORT_TRIGGERING :{ 
               TITLE:"Port Triggering",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the rules and edit them by clicking the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interface for the rule."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Trigger Port",
                           content: "Enter the trigger port or port range. Each entry supports at most 5 groups of trigger ports. The ports or port ranges cannot overlap with those of other port triggering rules. "
                       } ,{                      
                           type: "name",
                           title: "Trigger Protocol",
                           content: "Specify the trigger protocol for the trigger port."
                       } ,{                      
                           type: "name",
                           title: "Incoming Port",
                           content: "Enter the incoming port or port range. Each entry supports at most 5 groups of incoming ports. The ports or port ranges cannot overlap with those of other port triggering rules. "
                       } ,{                      
                           type: "name",
                           title: "Incoming Protocol",
                           content: "Specify the incoming protocol for the incoming port."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},

       ALG :{ 
               TITLE:"ALG",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can determine whether to provide ALG(Application Level Gateway) service for FTP, H.323, PPTP, SIP and IPsec to keep these special applications from the effect of NAT service on this page."
                       } ,{                      
                           type: "name",
                           title: "FTP ALG",
                           content: "Check the box to enable FTP ALG."
                       } ,{                      
                           type: "name",
                           title: "H.323 ALG",
                           content: "Check the box to enable H.323 ALG."
                       } ,{                      
                           type: "name",
                           title: "PPTP ALG",
                           content: " Check the box to enable PPTP ALG."
                       } ,{                      
                           type: "name",
                           title: "SIP ALG",
                           content: "Check the box to enable SIP ALG."
                       } ,{                      
                           type: "name",
                           title: "IPsec ALG",
                           content: "Check the box to enable IPsec ALG."
                       }]
},

       NAT_DMZ :{ 
               TITLE:"NAT-DMZ",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the rules and edit them by clicking the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interface for the rule."
                       } ,{                      
                           type: "name",
                           title: "Host IP Address",
                           content: "Specify the host IP address for NAT-DMZ."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       QOS_SETTING :{ 
               TITLE:"Bandwidth Control Config",
               CONTENT: [{
                           type: "paragraph",
                           content: "Check the box to enable Bandwidth Control globally, or you can choose to enable Bandwidth Control when bandwidth usage reaches a specific value."
                       } ,{                      
                           type: "name",
                           title: "Enable Bandwidth Control",
                           content: "Check the box to enable Bandwidth Control globally."
                       } ,{                      
                           type: "name",
                           title: "Enable Bandwidth Control When",
                           content: "With \"Enable Bandwidth Control\" selected, you can specify a percentage, and the Bandwidth Control will take effect only when the bandwidth usage reaches the percentage you specified."
                       }]
},
       QOS_LIST :{ 
               TITLE:"Bandwidth Control Rules List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the rules and edit them by clicking the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Direction",
                           content: "Specify the data stream direction for the rule. "
                       } ,{                      
                           type: "name",
                           title: "Group",
                           content: "Specify the address group for the rule to define the controlled users."
                       } ,{                      
                           type: "name",
                           title: "Maximum Upstream Bandwidth",
                           content: "Specify the Maximum Upstream Bandwidth in Kbps for the rule. "
                       } ,{                      
                           type: "name",
                           title: "Maximum Downstream Bandwidth",
                           content: "Specify the Maximum Downstream Bandwidth in Kbps for the rule. "
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Specify the bandwidth control mode for the address group. Individual means the bandwidth of each user is equal to the current bandwidth of this entry. Shared means the total bandwidth of all controlled IP addresses is equal to the current bandwidth of this entry."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Specify the time for the rule to take effect. Always means it always take effect. The time range referenced here can be created on the Preference > Time Range > Time Range page. "
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the rule."
                       } ,{                      
                           type: "name",
                           title: "ID",
                           content: "Append the rule to the right position to give a priority for the rule."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       SESSIONLIMIT_ENABLE :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "name",
                           title: "Enable Session Limit",
                           content: "Check the box to enable Session Limit."
                       }]
},
       SESSIONLIMIT_LIST :{ 
               TITLE:"Session Limit Rule List",
               CONTENT: [{
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Group",
                           content: "Specify the address group to which the rule will be applied."
                       } ,{                      
                           type: "name",
                           title: "Max Sessions",
                           content: "Specify the max sessions for the controlled users."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       SESSION_LIMITS :{ 
               TITLE:"Session Monitor List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the Session Limit information of hosts configured with Session Limit on this page. Click the Refresh button to get the latest information. "
                       } ,{                      
                           type: "name",
                           title: "IP",
                           content: "Displays the IP address of controlled users."
                       } ,{                      
                           type: "name",
                           title: "Max Sessions",
                           content: "Displays the maximum sessions of controlled users."
                       } ,{                      
                           type: "name",
                           title: "Current Sessions",
                           content: "Displays the current sessions of controlled users."
                       }]
},
       BALANCE_GLOBAL_SETTING :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure Load Balancing on this page."
                       } ,{                      
                           type: "name",
                           title: "Enable Load Balancing",
                           content: "Check the box to enable Load Balancing globally."
                       }]
},
       BALANCE_BASIC_SETTING :{ 
               TITLE:"Basic Settings",
               CONTENT: [{
                           type: "name",
                           title: "Enable Application Optimized Routing",
                           content: "With Application Optimized Routing enabled, the router will consider the source IP address and destination IP address (or destination port) of the packets as a whole and record the WAN port they pass through. Then the packets with the same source IP address and destination IP address (or destination port) will be forwarded to the recorded WAN port. This feature ensures that multi-connected applications work properly.   "
                       } ,{                      
                           type: "name",
                           title: "Enable Bandwidth Based Balance Routing on port(s)",
                           content: "Select the WAN port from the drop-down list to enable Bandwidth Based Balance Routing."
                       }]
},
       LINE_BACKUP_SETTING :{ 
               TITLE:"Link Backup",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the Link Backup function on this page."
                       } ,{                      
                           type: "name",
                           title: "Primary WAN",
                           content: "Specify the primary WAN port."
                       } ,{                      
                           type: "name",
                           title: "Backup WAN",
                           content: "Specify the backup WAN port to back up the traffic for the primary WAN port under the specified condition."
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Specify the mode as Timing or Failover. </br>Timing: Link Backup will be enabled if the specified effective time is reached. All the traffic on the primary WAN will switch to the backup WAN at the beginning of the effective time; the traffic on the backup WAN will switch to the primary WAN at the ending of the effective time. </br>Failover: Specify the premise for Failover Mode. The backup WAN port will be enabled only when the premise is met. "
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Specify the time for the rule to take effect. Always means it always take effect. The time range referenced here can be created on the Preference > Time Range > Time Range page. "
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       LINE_BACKUP_LIST :{ 
               TITLE:"Link Backup Rule List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the link backup rules and edit them by clicking the buttons in the table."
                       }]
},
       ONLINE_SETTING :{ 
               TITLE:"Online Detection",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the detecting mode to detect whether the WAN is online on this page."
                       } ,{                      
                           type: "name",
                           title: "Port",
                           content: "Displays the name of WAN Port."
                       } ,{                      
                           type: "name",
                           title: "Auto",
                           content: "In Auto Mode, the DNS server of the WAN port will be selected as the destination for DNS Lookup to detect whether the WAN is online."
                       } ,{                      
                           type: "name",
                           title: "Manual",
                           content: "In Manual Mode, you can configure the destination IP address for PING and DNS Lookup manually to detect whether the WAN is online."
                       } ,{                      
                           type: "name",
                           title: "Always Online",
                           content: "In Always Online Mode, the status of the port will always be online."
                       } ,{                      
                           type: "name",
                           title: "Ping",
                           content: "With \"Manual Mode\" selected, specify the destination IP for Ping.  The correspoding port will ping the IP address to detect whether the WAN port is online. 0.0.0.0 means Ping detection is disabled.  "
                       } ,{                      
                           type: "name",
                           title: "DNS Lookup",
                           content: "With \"Manual Mode\" selected, specify the IP address of DNS server. The correspoding port will perform the DNS lookup using default domain name to detect whether the WAN port is online. 0.0.0.0 means DNS Lookup is disabled. "
                       }]
},
       POLICY_ROUTING_SETTING :{ 
               TITLE:"Policy Routing",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the policy routing rule for forwarding packets on this page."
                       }]
},
       POLICY_ROUTING_LIST :{ 
               TITLE:"Policy Routing Rule List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the policy routing rules and edit them using the buttons in the table."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the rule."
                       } ,{                      
                           type: "name",
                           title: "Service Type",
                           content: "Specify the service type for the rule. The service type referenced here can be created on the Preferences > Service Type page. "
                       } ,{                      
                           type: "name",
                           title: "Source IP",
                           content: "Specify the IP Group you want to reference.  The IP Group referenced here can be created on the Preferences > IP Group page. "
                       } ,{                      
                           type: "name",
                           title: "Destination IP",
                           content: "Specify the IP Group you want to reference. The IP Group referenced here can be created on the Preferences > IP Group page. "
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Specify the outcoming port for the rule."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Specify the effective time for the rule."
                       } ,{                               
                           type: "name",
                           title: "Mode",
                           content: "Specify the policy routing mode for the rule.",
                           children: [{                      
                              type: "step",
                              content: [ 
                                  "Priority: Priority means that the rule depends on the online detection result. If any WAN port that you specify is online, the rule will take effect. If all the WAN ports that you specify is offline, the rule will not take effect.",
                                  "Only: Only means that the rule always takes effect regardless of the WAN port status or online detection result."]
                            }]
                       } ,{    
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the rule."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       ADVANCED_ROUTING_STATIC_ROUTING :{ 
               TITLE:"Static Route",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the static route entries on this page."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the route entry. The name cannot be same as existing ones."
                       } ,{                      
                           type: "name",
                           title: "Destination IP",
                           content: "Specify the destination IP address the route leads to."
                       } ,{                      
                           type: "name",
                           title: "Subnet Mask",
                           content: "Specify the subnet mask of the destination network."
                       } ,{                      
                           type: "name",
                           title: "Next Hop",
                           content: "Specify the IP address to which the packet should be sent next."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the physical network interface through which this route is accessible."
                       } ,{                      
                           type: "name",
                           title: "Metric",
                           content: "Define the priority of the route. Smaller values represent higher priority. The default value is 0. It is recommended to keep the default value. "
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the rule. It can be 50 characters at most."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       ADVANCED_ROUTING_SYSTEM_ROUTING_TABLE :{ 
               TITLE:"Route Table",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the route table on this page."
                       } ,{                      
                           type: "name",
                           title: "Destination IP",
                           content: "Displays the destination IP address the route leads to."
                       } ,{                      
                           type: "name",
                           title: "Subnet Mask",
                           content: "Displays the subnet mask of the destination network."
                       } ,{                      
                           type: "name",
                           title: "Next Hop",
                           content: "Displays the gateway IP address to which the packet should be sent next."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Displays the physical network interface through which this route is accessible."
                       } ,{                      
                           type: "name",
                           title: "Metric",
                           content: "Displays the metric to reach the destination IP address."
                       }]
},
       IMB_ENABLE :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "name",
                           title: "Enable ARP Spoofing Defense",
                           content: "Check the box to globally enable ARP Spoofing Defense. "
                       } ,{                      
                           type: "name",
                           title: "Permit the packets matching the IP-MAC Binding entries only",
                           content: "With this option enabled, only the packets matching the IP-MAC Binding entries are allowed.<br>Note: This feature can be enabled only when ARP Spoofing Defense is enabled."
                       } ,{                      
                           type: "name",
                           title: "Send GARP packets when ARP attack is detected",
                           content: "With this option enabled, the router will send GARP packets if it receives packets unmatching the IP-MAC Binding entries.<br>Note: This feature can be enabled only when ARP Spoofing Defense is enabled."
                       } ,{                      
                           type: "name",
                           title: "Interval",
                           content: "Specify the time interval for sending GARP packets. The valid values are from 1 to 10000. "
                       }]
},

       IMB_LIST :{ 
               TITLE:"IP-MAC Binding List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the IP-MAC Binding list and configure the current entries."
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Enter the IP address to be bound."
                       } ,{                      
                           type: "name",
                           title: "MAC Address",
                           content: "Enter the MAC address to be bound, in the format xx-xx-xx-xx-xx-xx."
                       // } ,{                      
                       //     type: "name",
                       //     title: "Interface",
                       //     content: "Select the interface on which the IP-MAC entry takes effect."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the entry."
                       } ,{                      
                           type: "name",
                           title: "Export to DHCP Address Reservation",
                           content: "Export the IP-MAC entry to the DHCP Address Reservation list."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the entry to be effective."
                       }]
},
       ARPSCAN_SCAN :{ 
               TITLE:"ARP Scanning",
               CONTENT: [{
	                   type: "paragraph",
                           content: "With ARP Scanning, the router sends ARP request packets with the specified IP field to the hosts. Upon receiving the ARP reply packet, the router can get the IP address, MAC address and connected interface of the host. You can bind these entries conveniently."
                       } ,{                      
                           type: "name",
                           title: "Scanning IP Range",
                           content: "Specify the scanning IP range, and the router will scan and record the entries in the IP address range."
                       } ,{                      
                           type: "name",
                           title: "Scanning Result",
                           content: "The scanning result will be displayed in the table."
                       }]
},
       ARPLIST_SCAN :{ 
               TITLE:"ARP List",
               CONTENT: [{
                           type: "name",
                           title: "ARP List",
                           content: "The ARP entries are displayed in ARP List. You can click the button in Operation column to bind this entry as an IP-MAC Binding entry."
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

        DEFENSE_FLOOD :{ 
               TITLE:"Flood Defense",
               CONTENT: [{
                           type: "name",
                           title: "Multi-connections TCP SYN Flood",
                           content: "With this feature enabled, the router will filter the subsequent TCP SYN packets if the number of this kind of packet reaches the specified threshold. The valid threshold ranges from 100 to 99999."
                       } ,{                      
                           type: "name",
                           title: "Multi-connections UDP Flood",
                           content: "With this feature enabled, the router will filter the subsequent UDP packets if the number of this kind of packet reaches the specified threshold. The valid threshold ranges from 100 to 99999."
                       } ,{                      
                           type: "name",
                           title: "Multi-connections ICMP Flood",
                           content: "With this feature enabled, the router will filter the subsequent ICMP packets if the number of this kind of packet reaches the specified threshold. The valid threshold ranges from 100 to 99999."
                       } ,{                      
                           type: "name",
                           title: "Stationary source TCP SYN Flood",
                           content: "With this feature enabled, the router will filter the subsequent stationary source TCP SYN packets if the number of this kind of packet reaches the specified threshold. The valid threshold ranges from 100 to 99999."
                       } ,{                      
                           type: "name",
                           title: "Stationary source UDP Flood",
                           content: "With this feature enabled, the router will filter the subsequent stationary source UDP SYN packets if the number of this kind of packet reaches the specified threshold. The valid threshold ranges from 100 to 99999."
                       } ,{                      
                           type: "name",
                           title: "Stationary source ICMP Flood",
                           content: "With this feature enabled, the router will filter the subsequent stationary source ICMP SYN packets if the number of this kind of packet reaches the specified threshold. The valid threshold ranges from 100 to 99999."
                       }]
},
       DEFENSE_DOS :{ 
               TITLE:"Packet Anomaly Defense",
               CONTENT: [{
                           type: "name",
                           title: "Block TCP Scan (Stealth FIN/Xmas/Null)",
                           content: "With this option enabled, the router will filter the TCP scan packets of Stealth FIN, Xmas and Null."
                       } ,{                      
                           type: "name",
                           title: "Block Ping of Death",
                           content: "With this option enabled, the router will block Ping of Death attack. Ping of Death attack means that the attacker sends abnormal ping packets larger than 65535 bytes to cause system crash on the target computer."
                       } ,{                      
                           type: "name",
                           title: "Block Large Ping",
                           content: "With this option enabled, the router will block Large Ping attack. Large Ping attack means that the attacker sends multiple ping packets larger than 1500 bytes to cause the system crash on the target computer. We set this limit to 1024 bytes just in case."
                       } ,{                      
                           type: "name",
                           title: "Block Ping from WAN",
                           content: "With this option enabled, the router will block the ICMP request from WAN."
                       } ,{                      
                           type: "name",
                           title: "Block WinNuke attack",
                           content: "With this option enabled, the router will block WinNuke attacks. WinNuke attack refers to a remote denial-of-service attack (DoS) that affects some Windows operating system, such as the Windows 95 and Windows N. The attacker sends a string of OOB (Out of Band) data to the target computer on TCP port 137, 138 or 139, causing system crash or Blue Screen of Death."
                       } ,{                      
                           type: "name",
                           title: "Block TCP packets with both SYN and FIN set",
                           content: "With this option enabled, the router will filter the TCP packets with both SYN Bit and FIN Bit set."
                       } ,{                      
                           type: "name",
                           title: "Block TCP packets with FIN set but without ACK set",
                           content: "With this option enabled, the router will filter the TCP packets with FIN Bit set but without ACK Bit set."
                       } ,{                      
                           type: "name",
                           title: "Block packets with specified IP options",
                           content: "With this option enabled, the router will filter the packets with specified IP options. You can choose the options according to your needs."
                       }]
},
       MAC_FILTERING_SETTING :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "name",
                           title: "Enable MAC Filtering",
                           content: "Check the box to enable MAC Filtering."
                       } ,{                      
                           type: "name",
                           title: "Filtering Mode",
                           content: "Select the filtering mode.<br>Allow packets with the MAC addresses listed below and deny the rest: The packets with the MAC addresses in the Fitering Table will be forwarded and the other packets will be discarded.<br>Deny packets with the MAC addresses listed below and allow the rest: The packets with the MAC addresses in the Fitering Table will be discarded and the other packets will be forwarded."
                       /*} ,{                      
                           type: "step",
                           title: "Example: To forbid the LAN host with MAC address 00-00-11-11-11-F2 to access the internet, you can refer to the following steps:",
       content: [ 
                "1. Click Add to add the MAC address 00-00-11-11-11-F2 to the MAC Filtering Table.",
                "2. Enable MAC Filtering.",
                "3. Select the Filtering Mode as \"Deny packets with the MAC addresses listed below and permit the rest\"."]*/
}]
},
       MAC_FILTERING_LIST :{ 
               TITLE:"MAC Filtering List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the IP-MAC Filtering list or configure the current entries."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify a name for the entry."
                       } ,{                      
                           type: "name",
                           title: "MAC Address",
                           content: "Enter the MAC address in the format xx-xx-xx-xx-xx-xx."
                       }]
},
       ACL_LIST :{ 
               TITLE:"Access Control List",
               CONTENT: [{
                           type: "name",
                           title: "Name",
                           content: "Specify a name for the rule. It can be 50 characters at most. The name of each entry cannot be repeated."
                       } ,{                      
                           type: "name",
                           title: "Policy",
                           content: "Select block or allow the packets matching the rule to access the network."
                       } ,{                      
                           type: "name",
                           title: "Service Type",
                           content: "Select the effective service for the rule. The service referenced here can be created on the Preferences>Service Type page."
                       } ,{                      
                           type: "name",
                           title: "Direction",
                           content: "Select the effective traffic direction for the rule.",
                           children: [{
								type: "step",
								content: [
									"ALL: Match the traffic in any direction.",
									"LAN->WAN: Match the traffic from LAN to WAN.",
									"LAN->LAN: Match the traffic from LAN to LAN.",
									"[WAN] IN: Match the traffic coming in via [WAN].",
									"[VPN] IN: Match the traffic coming in via [VPN]."
								]
							}]
                       } ,{                      
                           type: "name",
                           title: "Source",
                           content: "Select an IP group to specify the source address range for the rule. The IP group referenced here can be created on the Preferences>IP Group page."
                       } ,{                      
                           type: "name",
                           title: "Destination",
                           content: "Select an IP group to specify the destination address range for the rule. The IP group referenced here can be created on the Preferences>IP Group page.",
                           children:[{
                           	type: "note",
							title: "Note",
							content: "If you want to allow/block LAN management traffic, select Me as the Destination."
                           	}]
                       } ,{                      
                           type: "name",
                           title: "Source Network",
                           content: "Select a LAN Network to specify the source network for the rule. The LAN Network referenced here can be created on the Network>LAN page."
                       } ,{                      
                           type: "name",
                           title: "Destination Network",
                           content: "Select a LAN Network to specify the destination network for the rule. The LAN Network referenced here can be created on the Network>LAN page."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Select the effective time for the rule. The effective time referenced here can be created on the Preferences>Time Range page."
                       } ,{                      
                           type: "name",
                           title: "ID",
                           content: "Specify a rule ID. A smaller ID means a higher priority. This value is optional, and the newly added rule without this value configured will get the largest ID among all rules, which means the newly added rule has the lowest priority."
                       }]
},
       APPDIST_SETTING :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "paragraph",
                           content: "With Application Control, you can block the specified users from using the specified applications."
                       } ,{                      
                           type: "name",
                           title: "Enable Application Control",
                           content: "Check the box to enable Application Control."
                       }]
},
       APPDIST_LIST :{ 
               TITLE:"Application Control List",
               CONTENT: [{
                           type: "name",
                           title: "IP Group",
                           content: "Select an IP group for the rule. The IP group referenced here can be created on the Preferences>IP Group page."
                       } ,{                      
                           type: "name",
                           title: "Blacklist",
                           content: "Select one or more applications to be blocked."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Select the effective time for the rule. The effective time referenced here can be created on the Preferences>Time Range page."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the rule."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       WEB_GROUP :{ 
               TITLE:"Web Group",
               CONTENT: [{
                           type: "name",
                           title: "Name",
                           content: "Specify a name for the group. It can be 28 characters at most. The name of each group cannot be repeated."
                       } ,{                      
                           type: "name",
                           title: "Member",
                           content: "Add one or more website members to the group. The format is \"www.tp-link.com\" or \"*.tp-link.com\"., in which \"*\" is a wildcard. Use Enter key, Space key, \",\" or \";\" to divide different websites."
                       } ,{                      
                           type: "name",
                           title: "Clear",
                           content: "Clear all the input contents."
                       } ,{                      
                           type: "name",
                           title: "File Path",
                           content: "Import member list in your TXT file from your host. The format is \"www.tp-link.com\" or \"*.tp-link.com\"., in which \"*\" is a wildcard. Use Enter key, Space key, \",\" or \";\" to divide different websites."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the group. It can be 50 characters at most."
                       }]
},
       WEB_FILTER_ENABLE :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "name",
                           title: "Enable Web Filtering",
                           content: "Check the box to enable Web Filtering."
                       }]
},
       WEB_FILTER :{ 
               TITLE:"Web Filtering List",
               CONTENT: [{
                           type: "name",
                           title: "IP Group",
                           content: "Select an IP group for the rule. The IP group referenced here can be created on the Preferences>IP Group page."
                       } ,{                      
                           type: "name",
                           title: "Policy",
                           content: "Allow or deny the websites matching the rule."
                       } ,{                      
                           type: "name",
                           title: "Web Group",
                           content: "Select a web group for the rule. The web group referenced here can be created on the Behavior Control>Web Filtering>Web Group page."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Select the effective time for the rule. The effective time referenced here can be created on the Preferences>Time Range page."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the group. It can be 50 characters at most."
                       } ,{                      
                           type: "name",
                           title: "ID",
                           content: "Specify a rule ID. A smaller ID means a higher priority. This value is optional, and the newly added rule without this value configured will get the largest ID among all rules, which means the newly added rule has the lowest priority."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       URLFILTER_ENABLE :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "name",
                           title: "Enable URL Filtering",
                           content: "Check the box to enable URL Filtering."
                       }]
},
       URLFILTER_LIST :{ 
               TITLE:"URL Filtering List",
               CONTENT: [{
                           type: "name",
                           title: "IP Group",
                           content: "Select an IP group for the rule. The IP group referenced here can be created on the Preferences>IP Group page."
                       } ,{                      
                           type: "name",
                           title: "Policy",
                           content: "Allow or deny the websites matching the rule."
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Select the filtering mode. <br>Keywords: If a website address contains any keywords, the rule will be applied to this website.<br>URL Path: If a website address is the same as the URL path, the rule will be applied to this website."
                       } ,{                      
                           type: "name",
                           title: "Filtering Content",
                           content: "Add filtering contents. \".\" means that this rule will be applied to any website. For example, if you want to allow website A and deny other websites,  you can add an Allow rule for website A and add a Deny rule for \".\". Note that \".\" rule should have the largest ID number, which means the lowest priority."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Select the effective time for the rule. The effective time referenced here can be created on the Preferences>Time Range page."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the group. It can be 50 characters at most."
                       } ,{                      
                           type: "name",
                           title: "ID",
                           content: "Specify a rule ID. A smaller ID means a higher priority. This value is optional, and the newly added rule without this value configured will get the largest ID among all rules, which means the newly added rule has the lowest priority."
                       }]
},
       WEBSEC_ENABLE :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "name",
                           title: "Enable Web Security",
                           content: "Check the box to enable Web Security."
                       }]
},
       WEBSEC_SETTING :{ 
               TITLE:"Web Security List",
               CONTENT: [{
                           type: "name",
                           title: "IP Group",
                           content: "Select an IP group for the rule. The IP group referenced here can be created on the Preferences>IP Group page."
                       } ,{                      
                           type: "name",
                           title: "Block HTTP Post",
                           content: "With this option enabled, all the http posts will be blocked on the hosts of the selected IP group."
                       } ,{                      
                           type: "name",
                           title: "File Suffix",
                           content: "Enter file suffixes to specify file types. Use Enter key, Space key, \",\" or \";\" to divide different file suffixes. The hosts of the selected IP group cannot download the files of the specified types."
                       } ,{                      
                           type: "name",
                           title: "Effective Time",
                           content: "Select the effective time for the rule. The effective time referenced here can be created on the Preferences>Time Range page."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the group. It can be 50 characters at most."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the rule."
                       }]
},
       APPDIST_DB :{ 
               TITLE:"Application Database Upgrade",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can import a database file to upgrade the application database of the router."
                       } ,{                      
                           type: "name",
                           title: "Current Version",
                           content: "Displays the current database version."
                       } ,{                      
                           type: "name",
                           title: "Database File",
                           content: "Select the database file from your host."
                       }]
},
       IPSEC_TUNNEL_SETTING :{ 
               TITLE:"IPsec Policy",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the IPsec policy on this page. The IPsec policy indicates which IPsec proposal to be applied to the specific data flow. IPsec policy settings include basic settings and advanced settings. Advanced settings are optional."
                       } ,{                      
                           type: "paragraph",
                           title: "Basic Settings",
                           content: "For a newly configured IPsec policy, basic settings are necessary."
                       } ,{                      
                           type: "name",
                           title: "Policy Name",
                           content: "Specify the name of IPsec Policy. It can be 32 characters at most."
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Specify the network mode.",
       children: [{                      
                           type: "step",
       content: [ 
                "LAN-to-LAN: Select this option when a network is connected to the other network.",
                "Client-to-LAN: Select this option when a network is connected to a host."]
}]
} ,{                      
                           type: "name",
                           title: "Remote Gateway",
                           content: "Enter an IP address or a domain name (1 to 255 characters) as the remote gateway when the network mode is  LAN-to-LAN."
                       } ,{                      
                           type: "name",
                           title: "Remote Host",
                           content: "Enter the IP address of the remote host when the network mode is  Client-to-LAN. 0.0.0.0 represents any IP address."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Specify the local WAN port for the policy."
                       } ,{                      
                           type: "name",
                           title: "Local Subnet",
                           content: "Specify the local network to which the policy is applied. It's formed by IP address and subnet mask."
                       } ,{                      
                           type: "name",
                           title: "Remote Subnet",
                           content: "Specify the remote network to which the policy is applied. It's formed by IP address and subnet mask."
                       } ,{                      
                           type: "name",
                           title: "Pre-shared Key",
                           content: "For both peers's authentication, specify the unique pre-shared key for each pair of < WAN, Remote Gateway >."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Choose to enable the IPsec policy."
                       } ,{                      
                           type: "paragraph",
                           title: "Advanced Settings",
                           content: "Advanced settings include phase-1 settings and phase-2 settings.  It is suggested to keep the default advanced settings. You can complete the configuration according to your needs."
                       } ,{                      
                           type: "name",
                           title: "Advanced Settings——Phase-1 Settings",
                           content: "Configure the corresponding parameters for IKEv1 phase-1."
                       } ,{                      
                           type: "name",
                           title: "Proposal",
                           content: "Select the proposal for IKE negotiation phase 1 to specify the encryption algorithm, authentication algorithm and DH group. Up to four proposals can be selected. "
                       } ,{                      
                           type: "name",
                           title: "Exchange Mode",
                           content: "Specify the IKE Exchange Mode as Main Mode or Aggressive Mode. By default, it is Main Mode."
                       } ,{                      
                           type: "name",
                           title: "Negotiation Mode",
                           content: "Specify the IKE Negotiation Mode as Initiator Mode or Responder Mode. Initiator Mode means that the local device initiates a connection to the peer. Responder Mode means that the local device waits for the connection initiated by the peer."
                       } ,{                      
                           type: "name",
                           title: "Local ID Type",
                           content: "Specify the local ID type for IKE negotiation.<br>IP Address: Use an IP address as the ID in IKE negotiation. It is the default type.<br>NAME(FQDN): Use a name as the ID in IKE negotiation."
                       } ,{                      
                           type: "name",
                           title: "Local ID",
                           content: "Enter a name for the local device as the ID in IKE negotiation when the Local ID Type is configured as Name."
                       } ,{                      
                           type: "name",
                           title: "Remote ID Type",
                           content: "Specify the remote ID type for IKE negotiation.<br>IP Address: Use an IP address as the ID in IKE negotiation. It is the default type.<br>NAME(FQDN): Use a name as the ID in IKE negotiation."
                       } ,{                      
                           type: "name",
                           title: "Remote ID",
                           content: "Enter a name of the remote peer as the ID in IKE negotiation when the Remote ID Type is configured as Name."
                       } ,{                      
                           type: "name",
                           title: "SA Lifetime",
                           content: "Specify ISAKMP SA (Security Association) Lifetime in IKE negotiation."
                       } ,{                      
                           type: "name",
                           title: "DPD",
                           content: "Check the box to enable or disable DPD (Dead Peer Detect) function. If enabled, the IKE endpoint can send a DPD request to the peer to inspect whether the IKE peer is alive."
                       } ,{                      
                           type: "name",
                           title: "DPD Interval",
                           content: "If DPD is triggered, specify the interval between sending DPD requests. If the IKE endpoint receives a response from the peer during this interval, it considers the peer alive. If the IKE endpoint does not receive a response during the interval, it considers the peer dead and deletes the SA."
                       } ,{                      
                           type: "name",
                           title: "Advanced Settings——Stage-2 Settings",
                           content: "Configure the corresponding parameters for IKEv1 phase-2."
                       } ,{                      
                           type: "name",
                           title: "Encapsulation Mode",
                           content: "Specify the Encapsulation Mode as Tunnel Mode or Transport Mode. When both ends of the tunnel are hosts, either mode can be choosed. When at least one of the endpoints of a tunnel is a security gateway, such as a router or firewall,  tunnel mode should be chosen. "
                       } ,{                      
                           type: "name",
                           title: "Proposal",
                           content: "Select the proposal for IKE negotiation phase 2 to specify the encryption algorithm, authentication algorithm and protocol. Up to four proposals can be selected."
                       } ,{                      
                           type: "name",
                           title: "PFS",
                           content: "Select the DH group to enable PFS (Perfect Forward Security) for IKE mode to enhance security.  If you select None, it means PFS is disabled."
                       } ,{                      
                           type: "name",
                           title: "SA Lifetime",
                           content: "Specify IPsec SA (Security Association) Lifetime in IKE negotiation."
                       }]
},
       IPSEC_TUNNEL_LISTS :{ 
               TITLE:"IPsec Policy List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the IPsec policy entries and edit them using the buttons in the table."
                       }]
},
       IPSEC_SA :{ 
               TITLE:"IPsec SA List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of the IPsec SA (Security Association) on this page."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Displays the name of the IPsec policy associated with the SA. The name cannot be configured. "
                       } ,{                      
                           type: "name",
                           title: "SPI",
                           content: "Displays the SPI (Security Parameter Index) of the SA, including outgoing SPI and incoming SPI. The SPI of each SA is unique."
                       } ,{                      
                           type: "name",
                           title: "Direction",
                           content: "Displays the direction (in: incoming/out: outgoing) of the SA."
                       } ,{                      
                           type: "name",
                           title: "Tunnel ID",
                           content: "Displays the IP addresses of the local and remote peers."
                       } ,{                      
                           type: "name",
                           title: "Data Flow",
                           content: "Displays the Local Subnet and Remote Subnet/host covered by the SA."
                       } ,{                      
                           type: "name",
                           title: "Protocol",
                           content: "Displays the authentication protocol and encryption protocol used by the SA."
                       } ,{                      
                           type: "name",
                           title: "AH Authentication",
                           content: "Displays the AH authentication algorithm used by the SA."
                       } ,{                      
                           type: "name",
                           title: "ESP Authentication",
                           content: "Displays the ESP authentication algorithm used by the SA."
                       } ,{                      
                           type: "name",
                           title: "ESP Encryption",
                           content: "Displays the ESP encryption algorithm used by the SA."
                       }]
},
       L2TP_SERVER_SET :{ 
               TITLE:"L2TP Server Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the L2TP server on this page."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Specify the WAN port used for L2TP tunnel. "
                       } ,{                      
                           type: "name",
                           title: "IPsec Encryption",
                           content: "Specify whether to enable the encryption for the tunnel. If enabled, the L2TP tunnel will be encrypted by IPsec (L2TP over IPsec). If you choose Auto, the L2TP server will determine whether to encrypt the tunnel automatically."
                       } ,{                      
                           type: "name",
                           title: "Pre-shared Key",
                           content: "Specify the Pre-shared Key for IKE authentication. "
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the L2TP tunnel."
                       }]
},
       L2TP_CLIENT_SET :{ 
               TITLE:"L2TP Client Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the L2TP client on this page."
                       } ,{                      
                           type: "name",
                           title: "Tunnel",
                           content: "Specify the name of L2TP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Specify the account name of L2TP tunnel. It should be configured identically on server and client."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Specify the password of L2TP tunnel. It should be configured identically on server and client."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Specify the WAN port used for L2TP tunnel. "
                       } ,{                      
                           type: "name",
                           title: "Server IP",
                           content: "Specify the IP address or domain name of L2TP server. "
                       } ,{                      
                           type: "name",
                           title: "IPsec Encryption",
                           content: "Specify whether to enable the encryption for the tunnel. If enabled, the L2TP tunnel will be encrypted by IPsec (L2TP over IPsec)."
                       } ,{                      
                           type: "name",
                           title: "Pre-shared Key",
                           content: "Specify the Pre-shared Key for IKE authentication. "
                       } ,{                      
                           type: "name",
                           title: "Remote Subnet",
                           content: "Specify a remote network. (It's always the IP address range of LAN on the remote peer of VPN tunnel.) It's the combination of IP address and subnet mask."
                       } ,{                      
                           type: "name",
                           title: "Upstream Bandwidth",
                           content: "Specify the upstream bandwidth for L2TP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Downstream Bandwidth",
                           content: "Specify the downstream bandwidth for L2TP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Working Mode",
                           content: "Specify the Working Mode as NAT or Routing.<br>NAT: NAT (Network Address Translation) mode allows the device to translate source IP address of L2TP packets to local IP address of L2TP tunnel.<br>Route: Route mode allows the device to forward L2TP packets via routing protocol."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the L2TP tunnel."
                       }]
},
       L2TP_GLOBAL :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure L2TP globally on this page."
                       } ,{                      
                           type: "name",
                           title: "L2TP Hello Interval",
                           content: "Specify the time interval of sending L2TP peer detect packets."
                       } ,{                      
                           type: "name",
                           title: "PPP Hello Interval",
                           content: "Specify the time interval of sending PPP peer detect packets."
                       } ,{                      
                           type: "name",
                           title: "NetBIOS Passthrough",
                           content: "Enable NetBIOS Passthrough function to allow NetBIOS packets to be broadcasted through VPN tunnel."
                       }]/* ,{                      
                           type: "name",
                           title: "VPN-to-Internet",
                           content: "Enable VPN-to-Internet function to allow VPN users to access the internet and VPN networks simultaneously."
                       }]*/
},
       L2TP_TUNNEL :{ 
               TITLE:"Tunnel List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of L2TP tunnel on this page."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Displays the account name of L2TP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Displays whether the device is server or client."
                       } ,{                      
                           type: "name",
                           title: "Tunnel",
                           content: "Displays the name of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "Local IP",
                           content: "Displays the local IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "Remote IP",
                           content: "Displays the remote real IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "Remote Local IP",
                           content: "Displays the remote local IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "DNS",
                           content: "Displays the DNS address of the tunnel."
                       }]
},
       PPTP_SERVER_SET :{ 
               TITLE:"PPTP Server Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the PPTP server on this page."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Specify the WAN port used for the PPTP tunnel. "
                       } ,{                      
                           type: "name",
                           title: "MPPE Encryption",
                           content: "Specify whether to enable the encryption for the tunnel. If enabled, the PPTP tunnel will be encrypted by MPPE."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the PPTP tunnel."
                       }]
},
       PPTP_CLIENT_SET :{ 
               TITLE:"PPTP Client Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the PPTP client on this page."
                       } ,{                      
                           type: "name",
                           title: "Tunnel",
                           content: "Specify the name of PPTP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Specify the account name of PPTP tunnel. It should be configured identically on server and client."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Specify the password of PPTP tunnel. It should be configured identically on server and client."
                       } ,{                      
                           type: "name",
                           title: "WAN",
                           content: "Specify the WAN port used for PPTP tunnel. "
                       } ,{                      
                           type: "name",
                           title: "Server IP",
                           content: "Specify the IP address or domain name of PPTP server. "
                       } ,{                      
                           type: "name",
                           title: "MPPE Encryption",
                           content: "Specify whether to enable the encryption for the tunnel. If enabled, the PPTP tunnel will be encrypted by MPPE."
                       } ,{                      
                           type: "name",
                           title: "Remote Subnet",
                           content: "Specify a remote network. (Generally it's the IP address range of LAN on the remote peer of VPN tunnel.) It's the combination of IP address and subnet mask."
                       } ,{                      
                           type: "name",
                           title: "Upstream Bandwidth",
                           content: "Specify the upstream bandwidth for PPTP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Downstream Bandwidth",
                           content: "Specify the downstream bandwidth for PPTP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Working Mode",
                           content: "Specify the Working Mode as NAT or Route.<br>NAT: NAT (Network Address Translation) mode allows the device to translate source IP address of PPTP packets to local IP address of PPTP tunnel.<br>Route: Route mode allows the device to forward PPTP packets via routing protocol."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable PPTP tunneling."
                       }]
},
       PPTP_GLOBAL :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure PPTP globally on this page."
                       } ,{                      
                           type: "name",
                           title: "PPTP Hello Interval",
                           content: "Specify the time interval for sending PPTP peer detect packets."
                       } ,{                      
                           type: "name",
                           title: "PPP Hello Interval",
                           content: "Specify the time interval of sending PPP peer detect packets."
                       } ,{                      
                           type: "name",
                           title: "NetBIOS Paasthrough",
                           content: "Passthrough function.If enabled,the NetBIOS packet is permitted to broadcast through VPN tunnel."
                       }]/* ,{                      
                           type: "name",
                           title: "VPN-to-Internet",
                           content: "Enable VPN-to-Internet function to allow VPN users to access the internet and VPN networks simultaneously."
                       }]*/
},
       PPTP_TUNNEL :{ 
               TITLE:"Tunnel List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view PPTP tunnel information on this page."
                       } ,{                      
                           type: "name",
                           title: "Account",
                           content: "Displays the account name of the PPTP tunnel."
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Displays whether the device is a server or a client."
                       } ,{                      
                           type: "name",
                           title: "Tunnel",
                           content: "Displays the name of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "Local IP",
                           content: "Displays the local IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "Remote IP",
                           content: "Displays the remote real IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "Remote Local IP",
                           content: "Displays the remote local IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "DNS",
                           content: "Displays the DNS address of the tunnel."
                       }]
},
       VPNUSER :{ 
               TITLE:"VPN User List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the information of L2TP/PPTP users on this page."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Specify the account name used for the VPN tunnel. "
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Specify the password of users."
                       } ,{                      
                           type: "name",
                           title: "Protocol",
                           content: "Specify the protocol for the VPN tunnel.<br>L2TP: Uses L2TP protocol.<br>PPTP: Uses PPTP protocol."
                       } ,{                      
                           type: "name",
                           title: "Local IP Address",
                           content: "Specify the local IP address of the tunnel."
                       } ,{                      
                           type: "name",
                           title: "IP Address Pool",
                           content: "Specify the IP address pool from which the IP address will be assigned to the VPN client. The IP Pool referenced here can be created on the Preferences > IP Pool page. "
                       } ,{                      
                           type: "name",
                           title: "DNS Address",
                           content: "Specify the DNS address to be assigned to the VPN client (8.8.8.8 for example)."
                       } ,{                      
                           type: "name",
                           title: "Network Mode",
                           content: "Specify the network mode. There are two modes:<br>Client-to-LAN: Select this option when the L2TP/PPTP client is a single host.<br>LAN-to-LAN: Select this option when the L2TP/PPTP client is a network. The tunneling request is always initiated by a device."
                       } ,{                      
                           type: "name",
                           title: "Max Connections",
                           content: "Specify the maximum number of connections that the tunnel can support. "
                       } ,{                      
                           type: "name",
                           title: "Remote Subnet",
                           content: "Specify a remote network. (This is the IP address range of the LAN on the remote peer of the L2TP/PPTP tunnel.) It's the combination of IP address and subnet mask."
                       }]
},
       WPORTAL_FUNCTION :{ 
               TITLE:"Settings",
               CONTENT: [{
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable Web Authentication."
                       },{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interface."
                       },{                      
                           type: "name",
                           title: "Idle Timeout",
                           content: "Specify the idle timeout. The client will be disconnected after the specified period (Idle Timeout) of inactivity, and is required to authenticate again."
                       }, {                 
                           type: "name",
                           title: "Portal Authentication Port",
                           content: "Enter the service port for portal authentication. The port number should be different from other servers'. The default setting is 8080."
                       }]
},
       WPORTAL_PARAMETER :{ 
               TITLE:"Authentication Parameters",
               CONTENT: [{
                           type: "name",
                           title: "Authentication Page",
                           content: "Choose whether to use the custom page or the external links for authentication."
                       } ,{                      
                           type: "name",
                           title: "Background Picture",
                           content: "Upload the background picture for the custom page. The picture size cannot exceed 200KB."
                       } ,{                      
                           type: "name",
                           title: "Welcome Information",
                           content: "Enter the welcome information displayed on the custom page."
                       } ,{                      
                           type: "name",
                           title: "Copyright",
                           content: "Enter the copyright information displayed on the custom page."
                       } ,{                      
                           type: "name",
                           title: "Authentication URL",
                           content: "Enter the authentication URL when you choose the the type of authentication page as External Links."
                       } ,{                      
                           type: "name",
                           title: "Success Redirect URL",
                           content: "The browser will redirect to this URL after the authentication succeeds if you select External Links."
                       } ,{                      
                           type: "name",
                           title: "Fail Redirect URL",
                           content: "The browser will redirect to this URL after the authentication fails if you select External Links."
                       } ,{                      
                           type: "name",
                           title: "Authentication Type",
                           content: "Choose the Authentication Type, including Local Authentication, Radius Authentication and Onekey Online. <br>Note: When you choose the Authentication Page as External Links, Onekey Online is not available.",
       children: [{                      
                           type: "step",
       content: [ 
                "Local Authentication: Authentication for users can be configured in the local User Management page.",
                "Radius Authentication: Use an external Radius server to authenticate. The authentication timeout is 30 minutes by default, if not specified by the Radius server.",
                "Onekey Online: Users can pass through authentication directly. No username or password are required."]
}]
} ,{                      
                           type: "name",
                           title: "Expiration Reminder",
                           content: "Remind users that the online time is about to expire in Local Authentication."
                       } ,{                      
                           type: "name",
                           title: "Time to Remind",
                           content: "Specify the number of days before the expiration date to remind users."
                       } ,{                      
                           type: "name",
                           title: "Remind Type",
                           content: "Remind Once: Remind the user only once after the authenticaton succeeded;<br>Remind Periodically: Remind users at specified intervals during the remind period"
                       } ,{                      
                           type: "name",
                           title: "Remind Interval",
                           content: "Specify the interval at which the router reminds users."
                       } ,{                      
                           type: "name",
                           title: "Remind Content",
                           content: "Specify the remind content. The content will be displayed on the Remind page."
                       } ,{                      
                           type: "name",
                           title: "Page Preview",
                           content: "Preview the Remind Page."
                       } ,{                      
                           type: "name",
                           title: "Primary Radius Server",
                           content: "Enter the IP address of the primary Radius server, it is required if you choose Radius Authentication."
                       } ,{                      
                           type: "name",
                           title: "Secondary Radius Server",
                           content: "Enter the IP address of the secondary Radius server. If the primary server is down, the secondary server will be effective."
                       } ,{                      
                           type: "name",
                           title: "Authentication Port",
                           content: "Enter the authentication port number. By default, it is 1812."
                       } ,{                      
                           type: "name",
                           title: "Authorized Share Key",
                           content: "Specify the authorized share key."
                       } ,{                      
                           type: "name",
                           title: "Retry Times",
                           content: "Specify the number of times the router will retry sending authentication requests after the authentication failed. "
                       } ,{                      
                           type: "name",
                           title: "Timeout Interval",
                           content: "Specify the timeout interval that the client can wait before the radius server replies."
                       } ,{                      
                           type: "name",
                           title: "Authentication Method",
                           content: "Specify the Authentication Method."
                       } ,{                      
                           type: "name",
                           title: "Free Authentication Timeout",
                           content: "Specify the free time for Onekey Online. The value ranges from 1 to 1440, and the default value is 60."
                       } /*,{                      
                           type: "note",
                           title: "Note ",
       content: [ 
                "不能同时开启Web认证和微信连WiFi服务。"]
}*/]
},
       PORTAL_FREE :{ 
               TITLE:"Guest Resources",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure and view Guest Resources on this page. Guest Resources is used to provide free resources for users before they pass the portal authentication."
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Specify the name of the resources."
                       } ,{                      
                           type: "name",
                           title: "Type",
                           content: "Specify the Guest Resources type, including Five Tuple Type and URL Type."
                       } ,{                      
                           type: "name",
                           title: "URL Address",
                           content: "Specify the URL address of the websites that can be visited before users pass the authentication."
                       } ,{                      
                           type: "name",
                           title: "Source IP Range",
                           content: "Specify the source IP address range and subnet mask of clients. These clients can visit the specified network resource without any authentication."
                       } ,{                      
                           type: "name",
                           title: "Destination IP Range",
                           content: "Specify the destination IP range and subnet mask of servers. These servers can provide free resources for users."
                       } ,{                      
                           type: "name",
                           title: "Source MAC Address",
                           content: "Specify the source MAC address of clients. These clients can visit the specified network resource without any authentication."
                       } ,{                      
                           type: "name",
                           title: "Source Port Range",
                           content: "Specify the source port range."
                       } ,{                      
                           type: "name",
                           title: "Destination Port Range",
                           content: "Specify the destination port range."
                       } ,{                      
                           type: "name",
                           title: "Protocol",
                           content: "Specify the protocol supported for the Guest Resources."
                       } ,{                      
                           type: "name",
                           title: "Interface Type",
                           content: "Specify the interface supported for the Guest Resources."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Enter a brief description for the Guest Resources entry to make it easier to search for and manage. Up to 50 characters can be entered."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable Guest Resources feature."
                       }]
},
       USERMNGR_USER :{ 
               TITLE:"List of Authenticated User Rule ",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the list of authenticated users on this page."
                       } ,{                      
                           type: "name",
                           title: "User Type",
                           content: "There are two types of authenticated user:",
       children: [{                      
                           type: "step",
       content: [ 
                "Formal User: If you want to provide the user with network service for a long time (in days), you can configure them as formal users.",
                "Free User: If you want to provide the user with network service for a short time (in minutes), you can configure them as free users."]
}]
} ,{                      
                           type: "name",
                           title: "Username",
                           content: "Specify the username. The username should not be the same as the existing ones."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Specify the password."
                       } ,{                      
                           type: "name",
                           title: "Expiration Date",
                           content: "Specify the expiration date for the formal user."
                       } ,{                      
                           type: "name",
                           title: "Authentication Timeout",
                           content: "Specify the authentication timeout for the free user."
                       } ,{                      
                           type: "name",
                           title: "Authentication Peroid",
                           content: "Specify the period during which that the client is allowed to be authenticated. "
                       } ,{                      
                           type: "name",
                           title: "MAC Binding Type",
                           content: "Specify the MAC Binding type. There are three types of MAC Binding: No binding, Static Binding and Dynamic Binding.",
       children: [{                      
                           type: "step",
       content: [ 
                "No Binding: User's MAC address will not be bound.",
                "Static Binding: Manually enter the MAC address of the client to be bound. Only the bound client is able to use the username and password to authenticate.",
                "Dynamic Binding: The MAC address of the first client that passes the authentication will be bound. Only the bound client is able to use the username and password to authenticate."]
}]
} ,{                      
                           type: "name",
                           title: "Maximum Users",
                           content: "Specify the maximum number of users able to use this username and password to authencitate.<br>Note: If the MAC Binding Type is either Static Binding or Dynamic Binding, only one client can use this username and password to authenticate,i.e., the bound client."
                       } ,{                      
                           type: "name",
                           title: "Upstream Bandwidth",
                           content: "Specify the upstream bandwidth for the user. 0 means no limit. "
                       } ,{                      
                           type: "name",
                           title: "Downstream Bandwidth",
                           content: "Specify the downstream bandwidth for the user. 0 means no limit. "
                       } ,{                      
                           type: "name",
                           title: "Name",
                           content: "Optional: Record the user's name."
                       } ,{                      
                           type: "name",
                           title: "Telephone",
                           content: "Optional: Record the user's telephone number."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Optional: Enter a brief description for the user "
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable this entry."
                       }]
},
       USERMNGR_USER_BK :{ 
               TITLE:"Backup",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can backup the user configuration information on this page."
                       } ,{                      
                           type: "name",
                           title: "Backup",
                           content: "Click Backup to back up the user configuration information."
                       }]
},
       USERMNGR_USER_RT :{ 
               TITLE:"Restore",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can restore  the information of user configuration on this page."
                       } ,{                      
                           type: "name",
                           title: "Restore",
                           content: "Click Restore to restore the user configuration."
                       }]
},
       SESSMNGR_LIST :{ 
               TITLE:"Authentication Status",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the status of the authentication on this page."
                       } ,{                      
                           type: "name",
                           title: "Refresh",
                           content: "Refresh the list manually."
                       } ,{                      
                           type: "name",
                           title: "Offline",
                           content: "You can disconnect users in batches."
                       } ,{                      
                           type: "name",
                           title: "Type",
                           content: "Displays the authentication type."
                       } ,{                      
                           type: "name",
                           title: "Starting Time",
                           content: "Displays the Starting Time"
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Displays user's IP address."
                       } ,{                      
                           type: "name",
                           title: "Operation",
                           content: "Disconnect the user."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "If you want to know the packet rate and the total packets sent, please go to Status > Traffic Statistics > IP Statistics page to enable IP Statistics feature."
                      }]
},
       PHDDNS :{ 
               TITLE:"Peanuthull DDNS",
               CONTENT: [{
                           type: "paragraph",
                           content: "DDNS (Dynamic DNS) service is used to assign a fixed domain name to a dynamic WAN IP address, which enables the internet hosts to access the device or the hosts in LAN using the domain name. You can log in to the DDNS server and enable the DDNS service through this page."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Displays the interface for the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Enter the Account Name of your DDNS account."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Enter the password of your DDNS account."
                       } ,{                      
                           type: "name",
                           title: "Update Interval",
                           content: "Select the Update Interval that the device dynamically updates IP addresses for registered domain names."
                       } ,{                    
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Service Status",
                           content: "Displays the current status of DDNS service.",
       children: [{                      
                           type: "step",
       content: [ 
                "Offline: DDNS service is offline.",
                "Connecting: DDNS client is connecting to the server.",
                "Online: DDNS is working normally."]
}]
} ,{
			type: "name",
                           title: "Domain Name",
                           content: "Displays the Domain Names obtained from the DDNS server. Up to 16 domain names can be displayed here."
                },{                      
                           type: "name",
                           title: "Service Type",
                           content: "Displays the DDNS service type, including Professional service and Standard service."
                       }]
},
       CMXDDNS :{ 
               TITLE:"Comexe DDNS",
               CONTENT: [{
                           type: "paragraph",
                           content: "DDNS (Dynamic DNS) service is used to assign a fixed domain name to a dynamic WAN IP address, which enables the internet hosts to access the device or the hosts in LAN using the domain name. You can log in to the DDNS server and enable the DDNS service through this page."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Displays the interface working for the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Enter the Account Name of your DDNS account."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Enter the password of your DDNS account."
                       } ,{     
                           type: "name",
                           title: "Update Interval",
                           content: "Select the Update Interval that the device dynamically updates IP addresses for registered domain names."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Service Status",
                           content: "Displays the current status of DDNS service.",
       children: [{                      
                           type: "step",
       content: [ 
                "Offline: DDNS service is offline.",
                "Connecting: DDNS client is connecting to the server.",
                "Online: DDNS is working normally."]
}]
} ,{                   
                           type: "name",
                           title: "Domain Name",
                           content: "Displays the Domain Names obtained from the DDNS server. Up to 16 domain names can be displayed here."
                       }]
},
       DYNDDNS :{ 
               TITLE:"DynDNS",
               CONTENT: [{
                           type: "paragraph",
                           content: "DDNS (Dynamic DNS) service is used to assign a fixed domain name to a dynamic WAN IP address, which enables the internet hosts to access the device or the hosts in LAN using the domain name. You can log in to the DDNS server and enable the DDNS service through this page."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Displays the interface working for the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Enter the Account Name of your DDNS account."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Enter the password of your DDNS account."
                       } ,{                      
                           type: "name",
                           title: "Update Interval",
                           content: "Select the Update Interval that the device dynamically updates IP addresses for registered domain names."
                       } ,{                    
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the DDNS service."
                       } ,{     
		       type: "name",
                           title: "Service Status",
                           content: "Displays the current status of DDNS service.",
       children: [{                      
                           type: "step",
       content: [ 
                "Offline: DDNS service is offline.",
                "Connecting: DDNS client is connecting to the server.",
                "Online: DDNS is working normally."]
}]
} ,{                                    
                           type: "name",
                           title: "Domain Name",
                           content: "Enter the Domain Name that you registered with your DDNS service provider."
                       }]
},
       NOIPDDNS :{ 
               TITLE:"No-IP DDNS",
               CONTENT: [{
                           type: "paragraph",
                           content: "DDNS (Dynamic DNS) service is used to assign a fixed domain name to a dynamic WAN IP address, which enables the internet hosts to access the device or the hosts in LAN using the domain name. You can log in to the DDNS server and enable the DDNS service through this page."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Displays the interface working for the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Account Name",
                           content: "Enter the Account Name of your DDNS account."
                       } ,{                      
                           type: "name",
                           title: "Password",
                           content: "Enter the password of your DDNS account."
                       } ,{     
                           type: "name",
                           title: "Update Interval",
                           content: "Select the Update Interval that the device dynamically updates IP addresses for registered domain names."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the DDNS service."
                       } ,{                      
                           type: "name",
                           title: "Service Status",
                           content: "Displays the current status of DDNS service.",
       children: [{                      
                           type: "step",
       content: [ 
                "Offline: DDNS service is offline.",
                "Connecting: DDNS client is connecting to the server.",
                "Online: DDNS is working normally."]
}]
} ,{                                
                           type: "name",
                           title: "Domain Name",
                           content: "Enter the Domain Name that you registered with your DDNS service provider."
                       }]
},
       UPNP_SETTING :{ 
               TITLE:"General",
               CONTENT: [{
                           type: "paragraph",
                           content: "UPnP (Universal Plug and Play) function helps the applications and UPNP devices to automatically discover and communicate with each other."
                       } ,{                      
                           type: "name",
                           title: "Enable UPnP",
                           content: "Check the box to enable the UPnP function."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Specify the effective interfaces."
                       }]
},
       UPNP_LIST :{ 
               TITLE:"UPnP Portmap List",
               CONTENT: [{
                           type: "paragraph",
                           content: "The UPnP portmap List displays the rules generated through UPnP protocol."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Displays the description of the application using UPnP protocol."
                       } ,{                      
                           type: "name",
                           title: "Protocol",
                           content: "Displays the protocol type used in the process of UPnP."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Displays the interface used in the process of UPnP."
                       } ,{                      
                           type: "name",
                           title: "IP Address",
                           content: "Displays the IP address of the local host."
                       } ,{                      
                           type: "name",
                           title: "External Port",
                           content: "Displays the external port that is opened for the application by the router."
                       } ,{                      
                           type: "name",
                           title: "Internal Port",
                           content: "Displays the internal port that is opened for the application by the local host."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           children: [{                      
                           type: "step",
                           content: [ 
                              "Enabled: The mapping is active.",
                              "Disabled: The mapping is inactive." ]
                         }]
}]
},
       ADMIN_ACCOUNT :{ 
               TITLE:"Account",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can modify the parameters of the administrator account for login on this page."
                       } ,{                      
                           type: "name",
                           title: "Old Username",
                           content: "Enter the old username."
                       } ,{                      
                           type: "name",
                           title: "Old Password",
                           content: "Enter the old password."
                       } ,{                      
                           type: "name",
                           title: "New Username",
                           content: "Enter a new username for the administrator account. You can use letters, digits and special characters."
                       } ,{                      
                           type: "name",
                           title: "New Password",
                           content: "Enter a new user password  for the account. It is recommended to use a strong password for the security."
                       } ,{                      
                           type: "name",
                           title: "Confirm New Password",
                           content: "Re-enter the password for confirmation."
		       }/*,{
			type: "name",
			title: "密码强度",
			content: "在新密码输入框下的密码强度控件会提示您密码的强度，建议您使用字母、数字及常用符号的组合来提升密码的强度和安全性。"
		 }*/]
},
       REMOTE_MNGT :{ 
               TITLE:"Remote Management",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure to allow the remote host to access the device on this page."
                       } ,{                      
                           type: "name",
                           title: "Subnet/Mask",
                           content: "Enter the Subnet/Mask of the remote host."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Check the box to enable the remote management function for the remote host."
                       } ,{                                 
                           type: "note",
                           title: "Note",
       content: [ 
                "The Remote Management IP should not include LAN IP (including legal LAN IP).",
                "All the remote hosts are allowed to access the device if an entry with subnet 0.0.0.0/0 is added, which may result in illegal attack to the device. "]
}]
},
       ADMIN_CONFIG :{ 
               TITLE:"System Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can modify the server port and session timeout time for login on this page. "
                       } ,{                      
                           type: "name",
                           title: "HTTP Server Port",
                           content: "Enter the http server port for web management. The port number should be different from other servers'. The default setting is 80."
                       } ,{      
                           type: "name",
                           title: "Redirect HTTP to HTTPS",
                           content: "Check the box to enable the function, then you will access to the web by HTTPS protocol."
                       } ,{                 
                           type: "name",
                           title: "HTTPS Server Port",
                           content: "Enter the https server port for web management. The port number should be different from other servers'. The default setting is 443."
                       } ,{                 
                           type: "name",
                           title: "HTTPS Server Status",
                           content: "Check the box to enable HTTPS Server."
                       } ,{                      
                           type: "name",
                           title: "Web Idle Timeout",
                           content: "Enter a session timeout time for the device. The web session will log out for security if there is no operation within the session timeout time. "
                       }]
},
       FACTORY :{ 
               TITLE:"Factory Default Restore",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can restore all the configurations to the factory default settings on this page."
                       } ,{                      
                           type: "name",
                           title: "Factory Defaults",
                           content: "Click Factory Restore to reset the device to the factory default settings."
                       } ,{                      
                           type: "note",
                           title: "Note",
       content: [ 
                "All configurations will be cleared after system reset. Please back up the configurations in advance if needed.",
                "The device will reboot automatically after reset."]
}]
},
       BACKUP_RESTORE :{ 
               TITLE:"Backup & Restore",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can back up and restore the configurations on this page."
                       } ,{                      
                           type: "name",
                           title: "Backup",
                           content: "Click Backup to save your current configuration as a configuration file to the host. It is recommended to back up the configuration before firmware upgrade or configuration modification."
                       } ,{                      
                           type: "name",
                           title: "Restore",
                           content: "Click Restore to import the saved configuration file to your device."
                       } ,{                      
                           type: "note",
                           title: "Note",
       content: [ 
                "If you want to export the configuration file from one device and import it to another device, please make sure the firmware versions of the two devices are same. The large defference of the firmware versions between the two devices may cause the loss of configuration information.",
                "The device will reboot automatically after restoring."]
}]
},
       REBOOT :{ 
               TITLE:"Reboot",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can reboot the device on this page."
                       } ,{                      
                           type: "name",
                           title: "Reboot",
                           content: "Click Reboot to reboot the device."
                       } ,{                      
                           type: "note",
                           title: "Note",
                           content: "DO NOT power off the device during the reboot process."
                       }]
},
       FIRMWARE :{ 
               TITLE:"Firmware Upgrade",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can upgrade the firmware on this page. It is recommended to back up the configurations before upgrading."
                       } ,{                      
                           type: "name",
                           title: "Firmware Version",
                           content: "Displays the current Firmware Version of the device."
                       } ,{                      
                           type: "name",
                           title: "Hardware Version",
                           content: "Displays the current Hardware Version of the device."
                       } ,{                      
                           type: "name",
                           title: "New Firmware File",
                           content: "Click Browse to select a new firmware file to upgrade."
                       } ,{                      
                           type: "note",
                           title: "Tips",
       content: [ 
                "Please don't power off the device or refresh the page while upgrading. The device will automatically reboot after upgrading completes. ",
                "You can visit the official website <a href=\"http:\/\/www.tp-link.com\" target=\"_blank\">www.tp-link.com</a> to obtain the latest firmware."]
} ,{                      
                           type: "note",
                           title: "Note",
       content: [ 
                "DO NOT power off the device during the upgrade process.",
                "The current configurations may be lost after the upgrade completes. It is strongly recommended to back up the configurations in advance."]
}]
},
       SNMP_FUNCTION :{ 
               TITLE:"SNMP",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can specify the parameters of SNMP on this page."
                       } ,{                      
                           type: "name",
                           title: "SNMP",
                           content: "Check Enable to enable the SNMP function."
                       } ,{                      
                           type: "name",
                           title: "Contact",
                           content: "Enter the textual identification of the contact person for this the device, for example, contact or e-mail address."
                       } ,{                      
                           type: "name",
                           title: "Device Name",
                           content: "Enter a name for the device."
                       } ,{                      
                           type: "name",
                           title: "Location",
                           content: "Enter the location of the device. For example, the name can be composed of the building, floor number, and room location."
                       } ,{                      
                           type: "name",
                           title: "Get Community",
                           content: "Specify the community that has read-only access to the device's SNMP information. "
                       } ,{                      
                           type: "name",
                           title: "Get Trusted Host",
                           content: "Enter the IP address that can serve as Get Community to read the SNMP information of this device."
                       } ,{                      
                           type: "name",
                           title: "Set Community",
                           content: "Specify the community who has the read and write right of the device's SNMP information."
                       } ,{                      
                           type: "name",
                           title: "Set Trusted Host",
                           content: "Enter the IP address that can serve as Set Community to read and write the SNMP information of this device."
                       }]
},
		CONTROLLER_SETTINGS :{ 
              	TITLE:"Controller Settings",
              	CONTENT:[{
                           type: "paragraph",
                           content: "You can configure your router to be discovered by Omada Controller on this page, then it can be managed centrally via Omada Controller."
                       	}]
},
		CLOUD_MANAGEMENT :{ 
				TITLE:"Cloud-Based Controller Management",
				CONTENT:[{
							type: "paragraph",
							content: "With this feature, you can configure your router via Omada Cloud-Based Controller. To enjoy centralized management on Omada Cloud-Based Controller, enable Cloud-Based Controller Management and add the router to the controller via its serial number."
						},
						{
							type: "paragraph",
							content: "You can disable this feature if you do not need to manage the router with Omada Cloud-Based Controller."
						},
						{                      
                           type: "name",
                           title: "Connection Status",
                           content: "Displays the status of the connection between the router and Omada Cloud-Based Controller.",
                           children: [{                      
                           		type: "step",
       							content: [ 
                					"Disabled: Cloud-Based Controller Management is disabled.",
                					"Online: The router is connected to Omada Cloud and not managed by the cloud-based controller yet.",
                					"Offline: The router is not connected to Omada Cloud."
                				]
						   }]
                       	},
                       	{                      
                           type: "name",
                           title: "Cloud-Based Controller Management",
                           content: "Enable or disable Omada Cloud-Based Controller Management. With this feature enabled, the router can communicate with Omada Cloud Platform. Then you can add the router to the cloud-based controller via its serial number."
                       	}]
},
	   INFORM_URL :{ 
               	TITLE:"Controller Inform URL",
               	CONTENT:[{
               				type: "paragraph",
                           	content: "With the inform URL or IP address of the controller, the router can be discovered by the controller via this address. This feature is commonly used for the router to be managed by the controller in Layer 3 deployments."
						},
						{
							type: "name",
                           	title: "Inform URL/IP Address",
                           	children: [{
                           		type: "paragraph",
                           		content: "Enter the inform URL or IP address of your controller to tell the router where to discover the controller."
                           	},
                           	{
                           		type: "paragraph",
                           		content: "To get the inform URL of Omada Cloud-Based Controller, click the controller on your Omada Cloud Dashboard to reveal the Properties window, and then go to the Details tab."
                           	}]
						}]
},

       DIGNOSTIC :{ 
               TITLE:"Diagnostics",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can detect the current network connection status by using diagnostic tools on this page. "
                       } ,{                      
                           type: "name",
                           title: "Diagnostic Tool",
                           content: "Select the diagnostic tool to use. There are two types below.",
       children: [{                      
                           type: "step",
       content: [ 
                "Ping: Check the connection by using the ping command.",
                "Traceroute: Check the connection by using the traceroute command."]
}]
} ,{                      
                           type: "name",
                           title: "Destination IP/Domain Name",
                           content: "Enter the IP address or the domain name that you want to ping or tracert."
                       } ,{                      
                           type: "name",
                           title: "Interface",
                           content: "Select the interface that the detection packets sent from."
                       } ,{                      
                           type: "name",
                           title: "Ping Count",
                           content: "Specify the ping count during the ping process."
                       } ,{                      
                           type: "name",
                           title: "Ping Packet Size",
                           content: "Specify the ping packet size during the ping process."
                       } ,{                      
                           type: "name",
                           title: "Traceroute Max TTL",
                           content: "Specify the traceroute max TTL during the traceroute process."
                       }]
},
       DIA_ENABLE :{ 
               TITLE:"Remote Assistance",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can enable/disable the Remote Assistance function or export the diagnostic information on this page."
                       } ,{                      
                           type: "name",
                           title: "Remote Assistance",
                           content: "If you cannot solve your network problem, please try to make contact with technicians. Under the guide of technicians, you can enable the Remote Assistance function to get help."
                       } ,{                      
                           type: "name",
                           title: "Diagnostic Information",
                           content: "Click Export to download a bin-formatted file containing helpful information, and send it to the technicians for help."
                       } ,{                      
                           type: "note",
                           title: "Note",
       content: [ 
                "In general, it is recommended to keep the Remote Assistance function disabled.",
                "Please enable this function with the help of technicians if it is needed."]
}]
},
       TIME_SETTING :{ 
               TITLE:"Time Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view and configure the system time on this page. "
                       } ,{                      
                           type: "name",
                           title: "Current Time",
                           content: "Displays the current system time."
                       } ,{                      
                           type: "name",
                           title: "Time Config",
                           content: "Select one method to configure the system time. There are two methods here: \"Get automatically from the Internet\" and \"Manually\"."
                       } ,{                      
                           type: "name",
                           title: "Get automatically from the Internet",
                           content: "Select to get UTC from the internet.",
       children: [{                      
                           type: "step",
       content: [ 
                "Time Zone: Select the time zone the device is in.",
                "Primary/Secondary NTP Server: Specify the IP address of the NTP server."]
}]
} ,{                      
                           type: "name",
                           title: "Manually",
                           content: "Select to specify the system time manually."
                       } ,{                      
                           type: "name",
                           title: "Synchronize with PC's Clock",
                           content: "Click Synchronize with PC's Clock to obtain the time from the host."
                       }]
},
       DAYLIGHT_SAVING :{ 
               TITLE:"Daylight Saving Time",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure Daylight Saving Time on this page."
                       } ,{                      
                           type: "name",
                           title: "DST Status",
                           content: "Check to enable Daylight Saving Time."
                       } ,{                      
                           type: "name",
                           title: "Predefined Mode",
                           content: "Select a predefined DST configuration.",
       children: [{                      
                           type: "step",
       content: [ 
                "USA: Second Sunday of March at 02:00 ~ First Sunday of November at 02:00.",
                "Europe: Last Sunday of March at 01:00 ~ Last Sunday of October at 01:00.",
                "Australia: First Sunday of October at 02:00 ~ First Sunday of April at 03:00.",
                "New Zealand: Last Sunday of September at 02:00 ~ First Sunday of April at 03:00."]
}]
} ,{                      
                           type: "name",
                           title: "Recurring Mode",
                           content: "Specify the DST configuration in recurring mode. This configuration is recurring in use.",
       children: [{                      
                           type: "step",
       content: [ 
                "Time Offset: Specify the time added in minutes when Daylight Saving Time takes effect.",
                "Starting/Ending Time: Specify starting and ending time of Daylight Saving Time. All times are relative to the local time zone. The starting time is relative to standard time. The ending time is relative to daylight saving time."]
}]
} ,{                      
                           type: "name",
                           title: "Date Mode",
                           content: "Specify the DST configuration in date mode. This configuration is one-off in use.",
       children: [{                      
                           type: "step",
       content: [ 
                "Time Offset: Specify the time added in minutes when Daylight Saving Time takes effect.",
                "Starting/Ending Time: Specify the starting and ending time of Daylight Saving Time. All times are relative to the local time zone. The starting time is relative to standard time. The ending time is relative to daylight saving time."]
}]
}]
},
       SYSTEM_LOG :{ 
               TITLE:"System Log",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the system status on this page."
                       }]
},
       SYSTEM_LOG_SETTING :{ 
               TITLE:"Log Settings",
               CONTENT: [{
                           type: "name",
                           title: "Enable Auto-refresh",
                           content: "Check Enable Auto-refresh and the page will refresh automatically every 10 seconds."
                       } ,{                      
                           type: "name",
                           title: "Severity",
                           content: "Check Severity and specify the importance of the logs you want to view. ",
       children: [{                      
                           type: "step",
       content: [ 
                "ALL Level: Logs of all levels.",
                "EMERGENCY: Errors that render the router unusable, such as hardware errors.",
                "ALERT: Errors that must be resolved immediately, such as flash write errors.",
                "CRITICAL: Errors that put the system at risk, such as a failure to release memory.",
                "ERROR: Generic errors.",
                "WARNING: Warning messages, such as WinNuke attack warnings.",
                "NOTICE: Important notifications, such as IKE policy mismatches.",
                "INFO: Informational messages.",
                "DEBUG: Debug-level notifications, such as when the router receives a DNS packet."]
}]
},{                   
                type: "name",
                title: "Send Log",
                content: "Check the box and specify the server address the log will be sent to."
               }]
},
       SYSTEM_LOG_LIST :{ 
               TITLE:"Log List",
               CONTENT: [{
                           type: "name",
                           title: "Content",
                           content: "Displays the log contents."
                       } ,{                      
                           type: "name",
                           title: "Refresh",
                           content: "Click Refresh to refresh the logs manually."
                       } ,{                      
                           type: "name",
                           title: "Delete All",
                           content: "Click Delete All to delete all logs saved in the device."
                       } ,{                      
                           type: "name",
                           title: "Save Log",
                           content: "Click Save Log and the device will save the current logs as a file to the host."
                       }]
},

       WIRELESS_BASIC :{ 
               TITLE: "Wireless Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "On this page you can configure the basic parameters of the wireless network."
                       } ,{                      
                           type: "name",
                           title: "Wireless",
                           content: "Check the box to enable the wireless function."
                       } ,{                      
                           type: "name",
                           title: "SSID",
                           content: "Specify the name of the wireless network."
                       } ,{                      
                           type: "name",
                           title: "SSID Encoding",
                           content: "Set the SSID Encoding as UTF8 or GBK. Only when the SSID contains Chinese charaters can you configure this parameter."
                       } ,{                      
                           type: "name",
                           title: "AP Isolation",
                           content: "Enable AP Isolation function to isolate wireless stations in your network from each other. Wireless devices will only be able to communicate with the router."
                       } ,{                      
                           type: "name",
                           title: "Hide SSID",
                           content: "Select if you want to hide the network name (SSID) from the wireless clients. When selected, the wireless router will not broadcast the SSID on the air."
                       } ,{                      
                           type: "name",
                           title: "Security",
                           content: "Select one of the following security options.",
            children:[{
                type: "step",
                content:[
                "No Security: Select this option to disable the network security. It is not recommended to choose this option for security.",
                "WPA-PSK/WPA2-PSK (Recommended): Select WPA-PSK/WPA2-PSK as the security option. This option requires a PSK password for authentication and you do not need to configure the authentication server.",
                "WPA/WPA2: Select WPA/WPA2 as the security option. This option requires to configure the Radius Server for authentication.",
                "WEP: Select WPA/WPA2 as the security option. It is based on the IEEE 802.11 standard."
                ]
            }]
        },{
                           type: "name",
                           title: "Authentication Type",
                           content: "Select the authentication type when using WPA-PSK/WPA2-PSK or WPA/WPA2 as the security option. ",
            children:[{
                type:"step",
                content:[
                "For WPA-PSK/WPA2-PSK, there are three authentication types including Automatic, WPA-PSK and WPA2-PSK. It is recommended to choose Automatic for automatically selecting  WPA-PSK or WPA2-PSK according to the wireless station's capability and request.",
                "For WPA/WPA2, there are three authentication types including Automatic, WPA and WPA2. It is recommended to choose Automatic for automatically selecting WPA or WPA2 according to the wireless station's capability and request.",
                "For WEP, there are three authentication types including Automatic,  Open System and Shared Key. It is recommended to choose Automatic for automatically selecting Open System or Shared Key according to the wireless station's capability and request."
                ]
            }]
        },{
                           type: "name",
                           title: "Encryption",
                           content: "Select the encryption algorithm when using WPA-PSK/WPA2-PSK or WPA/WPA2 as the security option. ",
            children:[{
                type:"step",
                content:[
                "For WPA-PSK/WPA2-PSK, there are three encryption algorithms including Automatic, TKIP (Temporal Key Integrity Protocol) and AES (Advanced Encryption Standard). It is recommended to choose Automatic for automatically selecting TKIP or AES according to the wireless station's capability and request.",
                "For WPA/WPA2, there are three encryption algorithms including Automatic, TKIP (Temporal Key Integrity Protocol) and AES (Advanced Encryption Standard). It is recommended to choose Automatic for automatically selecting TKIP or AES according to the wireless station's capability and request."
                ]
            }]
        },{
                           type: "name",
                           title: "PSK Password",
                           content: "Specify a password when you select WPA-PSK/WPA2-PSK as the security option. Please enter 8 to 63 ASCII characters or 8 to 64 hexadecimal characters. "
                       } ,{                      
                           type: "name",
                           title: "RADIUS Server IP",
                           content: "Specify the IP address of the RADIUS Server when you select WPA/WPA2 as the security option."
                       } ,{                      
                           type: "name",
                           title: "RADIUS Port",
                           content: "Specify the port number of the RADIUS Server when you select WPA/WPA2 as the security option."
                       } ,{                      
                           type: "name",
                           title: "RADIUS Password",
                           content: "Specify the password for the RADIUS Server when you select WPA/WPA2 as the security option. Please enter 8 to 63 ASCII characters or 8 to 64 hexadecimal characters. "
                       } ,{                      
                           type: "name",
                           title: "Group Key Update Period",
                           content: "Specify the group key update period in seconds. The period should be 0 or a value more than 30. 0 means no update."
                       } ,{                      
                           type: "name",
                           title: "WEP Key Format",
                           content: "Select Hexadecimal or ASCII as the WEP key format.<br>Hexadecimal format stands for any combination of hexadecimal digits (0-9, a-f, A-F) in the specified length. <br>ASCII format stands for any combination of keyboard characters in the specified length. "
                       } ,{                      
                           type: "name",
                           title: "Key Selected",
                           content: "Select the key to be used according to your actual needs."
                       } ,{                      
                           type: "name",
                           title: "WEP Key",
                           content: "Select which of the four keys will be used and enter the matching WEP key that you create. Make sure these values are identical on all wireless stations in your network.  "
                       } ,{                      
                           type: "name",
                           title: "Key Type",
                           content: "Select the WEP key length (64-bit, 128-bit or 152-bit) for encryption. \"Disable\" means this WEP key entry is invalid.",
            children:[{
                type: "step",
                content:[
                "64-bit: You can enter 10 hexadecimal digits (any combination of 0-9, a-f, A-F, zero key is not promoted) or 5 ASCII characters.",
                "128-bit: You can enter 26 hexadecimal digits (any combination of 0-9, a-f, A-F, zero key is not promoted) or 13 ASCII characters.",
                "152-bit: You can enter 32 hexadecimal digits (any combination of 0-9, a-f, A-F, zero key is not promoted) or 16 ASCII characters."
                ]
            }]
                       }]
    },
    WIRELESS_MSSID: {
        TITLE: "General",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can create and configure multi SSIDs on this page."
                       } ,{                      
                           type: "name",
                           title: "SSID Insulation",
                           content: "Enable or disable the SSID Insulation. If enabled, the hosts accessing to different SSIDs cannot communicate with each other. "
                       }]
    },
    WIRELESS_MSSID_LIST: {
               TITLE:"Multi-SSID List",
               CONTENT: [{
                           type: "name",
                           title: "SSID",
                           content: "Specify the name of the wireless network."
                       } ,{                      
                           type: "name",
                           title: "SSID Encoding",
                           content: "Set the SSID Encoding as UTF8 or GBK. Only when the SSID contains Chinese charaters can you configure this parameter."
                       } ,{                      
                           type: "name",
                           title: "AP Isolation",
                           content: "Enable AP Isolation function to isolate wireless stations in your network from each other. Wireless devices will only be able to communicate with the router."
                       } ,{                      
                           type: "name",
                           title: "Hide SSID",
                           content: "Select if you want to hide the network name (SSID) from the wireless clients. When selected, the wireless router will not broadcast the SSID on the air."
                       } ,{                      
                           type: "name",
                           title: "Security",
                           content: "Select one of the following security options.",
            children:[{
                type: "step",
                content:[
                "No Security: Select this option to disable the network security. It is not recommended to choose this option for security.",
                "WPA-PSK/WPA2-PSK (Recommended): Select WPA-PSK/WPA2-PSK as the security option. This option requires a PSK password for authentication and you do not need to configure the authentication server.",
                "WPA/WPA2: Select WPA/WPA2 as the security option. This option requires to configure the Radius Server for authentication.",
                "WEP: Select WPA/WPA2 as the security option. It is based on the IEEE 802.11 standard."
                ]
            }]
        },{
            type:"name",
                           title: "Authentication Type",
                           content: "Select the authentication type when using WPA-PSK/WPA2-PSK or WPA/WPA2 as the security option. ",
            children:[{
                type:"step",
                content:[
                "For WPA-PSK/WPA2-PSK, there are three authentication types including Automatic, WPA-PSK and WPA2-PSK. It is recommended to choose Automatic for automatically selecting  WPA-PSK or WPA2-PSK according to the wireless station's capability and request.",
                "For WPA/WPA2, there are three authentication types including Automatic, WPA and WPA2. It is recommended to choose Automatic for automatically selecting WPA or WPA2 according to the wireless station's capability and request.",
                "For WEP, there are three authentication types including Automatic,  Open System and Shared Key. It is recommended to choose Automatic for automatically selecting Open System or Shared Key according to the wireless station's capability and request."
                ]
            }]
        },{
            type:"name",
                           title: "Encryption",
                           content: "Select the encryption algorithm when using WPA-PSK/WPA2-PSK or WPA/WPA2 as the security option. ",
            children:[{
                type:"step",
                content:[
                "For WPA-PSK/WPA2-PSK, there are three encryption algorithms including Automatic, TKIP (Temporal Key Integrity Protocol) and AES (Advanced Encryption Standard). It is recommended to choose Automatic for automatically selecting TKIP or AES according to the wireless station's capability and request.",
                "For WPA/WPA2, there are three encryption algorithms including Automatic, TKIP (Temporal Key Integrity Protocol) and AES (Advanced Encryption Standard). It is recommended to choose Automatic for automatically selecting TKIP or AES according to the wireless station's capability and request."
                ]
            }]
        },{
            type: "name",
                           title: "PSK Password",
                           content: "Specify a password when you select WPA-PSK/WPA2-PSK as the security option. Please enter 8 to 63 ASCII characters or 8 to 64 hexadecimal characters. "
                       } ,{                      
                           type: "name",
                           title: "Group Key Update Period",
                           content: "Specify the group key update period in seconds. The period should be 0 or a value more than 30. 0 means no update."
                       } ,{                      
                           type: "name",
                           title: "RADIUS Server IP",
                           content: "Specify the IP address of the RADIUS Server when you select WPA/WPA2 as the security option."
                       } ,{                      
                           type: "name",
                           title: "RADIUS Port",
                           content: "Specify the port number of the RADIUS Server when you select WPA/WPA2 as the security option."
                       } ,{                      
                           type: "name",
                           title: "RADIUS Password",
                           content: "Specify the password for the RADIUS Server when you select WPA/WPA2 as the security option. Please enter 8 to 63 ASCII characters or 8 to 64 hexadecimal characters. "
                       } ,{                      
                           type: "name",
                           title: "WEP Key Format",
                           content: "Select Hexadecimal or ASCII as the WEP key format.<br>Hexadecimal format stands for any combination of hexadecimal digits (0-9, a-f, A-F) in the specified length. <br>ASCII format stands for any combination of keyboard characters in the specified length. "
                       } ,{                      
                           type: "name",
                           title: "Key Selected",
                           content: "Select the key to be used according to your actual needs."
                       } ,{                      
                           type: "name",
                           title: "WEP Key",
                           content: "Select which of the four keys will be used and enter the matching WEP key that you create. Make sure these values are identical on all wireless stations in your network.  "
                       } ,{                      
                           type: "name",
                           title: "Key Type",
                           content: "Select the WEP key length (64-bit, 128-bit or 152-bit) for encryption. \"Disable\" means this WEP key entry is invalid.",
            children:[{
                type: "step",
                content:[
                "64-bit: You can enter 10 hexadecimal digits (any combination of 0-9, a-f, A-F, zero key is not promoted) or 5 ASCII characters.",
                "128-bit: You can enter 26 hexadecimal digits (any combination of 0-9, a-f, A-F, zero key is not promoted) or 13 ASCII characters.",
                "152-bit: You can enter 32 hexadecimal digits (any combination of 0-9, a-f, A-F, zero key is not promoted) or 16 ASCII characters."
                ]
            }]
                       }]
    },
    WIRELESS_WDS: {
               TITLE:"WDS",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the WDS (Wireless Distribution System) Bridging function to extend your wireless network on this page."
                       } ,{                      
                           type: "name",
                           title: "WDS",
                           content: "Check the box to enable WDS function. With this function, the router can bridge two or more WLANs. "
                       } ,{                      
                           type: "name",
                           title: "Scan",
                           content: "Scan the SSID to be bridged and the scanning result will be displayed in the wireless network list. Please try the following:",
       			   children: [{                      
                           	type: "step",
       				content: [ 
                			"Click Scan to search for the wireless network nearby.",
                			"Locate the SSID of the router to be bridged in the Wireless Network List and click Connect.",
                			"Enter the key (wireless password) of the router to be bridged."
				]
			   }]
		       } ,{                      
                           type: "name",
                           title: "SSID (to be bridged)",
                           content: "Enter the network name (SSID) of the router to be bridged."
                       } ,{                      
                           type: "name",
                           title: "MAC Address (to be bridged)",
                           content: "Enter the MAC address of the router to be bridged."
                       } ,{                      
                           type: "name",
                           title: "Security",
                           content: "Select the security option of the router to be bridged.",
            children:[{
                type: "step",
                content:[
                "No Security: Select this option to disable the network security. It is not recommended to choose this option for security.",
                "WEP (ASCII format): Select WEP (ASCII format) as the security option. ASCII format stands for any combination of keyboard characters in the specified length.",
                "WEP (Hexadecimal format): Select WEP (Hexadecimal format) as the security option. Hexadecimal format stands for any combination of hexadecimal digits (0-9, a-f, A-F) in the specified length.",
                "WPA-PSK/WPA2-PSK (Recommended): Select WPA-PSK/WPA2-PSK as the security option. This option requires a PSK password for authentication and you do not need to configure the authentication server."
                ]
            }]
                       } ,{                      
                           type: "name",
                           title: "Key Selected",
                           content: "Select the key according to the WEP Key Index of the AP your router is going to connect to."
                       } ,{                      
                           type: "name",
                           title: "Authentication Type",
                           content: "Specify the authentication type according to the Authentication Type of the AP your router is going to connect to."
                       } ,{                      
                           type: "name",
                           title: "Key",
                           content: "Enter the wireless password if the wireless network to be bridged has a wireless password."
        }]
    },
       WIRELESS_WDS_STATUS :{ 
               TITLE:"WDS Status",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can check the WDS connection status."
                       }]
},
       WIRELESS_ADVANCED :{ 
               TITLE:"Advanced Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the wireless advanced parameters according to your actual needs."
                       } ,{                      
                           type: "name",
                           title: "Channel",
                           content: "Select the frequency to be used. It is recommended to choose automatic. Under automatic mode, the router will choose the best channel automatically. It is not necessary to change the wireless channel unless you notice interference problems with another nearby access point. The channel cannot be configured when the WDS function is enabled."
                       } ,{                      
                           type: "name",
                           title: "Mode",
                           content: "Select the desired wireless mode. It is recommended to keep the default option. Changing the wireless mode may affect the wireless speed. The mode cannot be configured when the WDS function is enabled."
                       } ,{                      
                           type: "name",
                           title: "Channel Width",
                           content: "Select the bandwidth of the wireless channel. The channel width cannot be configured when the WDS function is enabled."
                       } ,{                      
                           type: "name",
                           title: "Transmit Power",
                           content: "Specify the transmit power of router. High is suitable for large wireless coverage or an environment with multi obstacles . Middle is suitable for medium wireless coverage or an environment with fewer obstacles.  Low is suitable for small wireless coverage or an environment without obstacles."
                       } ,{                      
                           type: "name",
                           title: "Beacon Interval",
                           content: "Specify the time interval of the beacons ranging from 40 to 1000 milliseconds. The default value is 100. The beacons are the packets sent by the router to synchronize a wireless network. "
                       } ,{                      
                           type: "name",
            		   title:"RTS Threshold",
                           content: "Specify the RTS (Request to Send) Threshold. If the packet is larger than the specified RTS Threshold size, the router will send RTS frames to a particular receiving station and negotiate the sending of a data frame. The default value is 2346."
                       } ,{                      
                           type: "name",
            		   title:"Fragmentation Threshold",
                           content: "Specify the maximum size determining whether packets will be fragmented. Setting the Fragmentation Threshold too low may result in poor network performance since excessive packets. It is recommended to keep the default value 2346.  "
                       } ,{                      
                           type: "name",
            		   title:"DTIM Interval",
                           content: "Specify the interval of the Delivery Traffic Indication Message (DTIM). You can specify the value between 1-255 Beacon Intervals. The default value is 1."
                       } ,{                      
                           type: "name",
            		   title:"Short GI",
                           content: "It is recommended to enable Short GI for it will increase the data capacity by reducing the guard interval time."
                       } ,{                      
                           type: "name",
                           title: "WMM",
                           content: "WMM (Wi-Fi MultiMedia) can guarantee the packets with high- priority messages transmitted preferentially. It is recommended to enable this function.  This option is unavailable if the mode is selected as 802.11n only or 802.11b/g/n mixed."
        }]
    },
    // WIRELESS_ADVANCED_5G:{
    //     TITLE: "高级设置",
    //     CONTENT:[{
    //         type: "paragraph",
    //         content: "您可以通过本页面进行无线网络的高级设置。"
    //     }, {
    //         type:"name",
    //         title:"信道",
    //         content:"以无线信号作为传输媒体的数据信号传送的通道。如果您选择的是自动，则路由器会自动根据周围的环境选择一个最好的信道，建议使用自动。无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"模式",
    //         content:"路由器工作的无线模式，修改无线模式后会影响路由器的无线速率，建议使用默认设置，无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"频段带宽",
    //         content:"路由器传输无线数据的频段宽度，无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"发射功率",
    //         content:"发射功率分为“高”“中”“低”三个选项，“高”适合大面积或多阻隔覆盖需求，“中”适合中等面积或少阻隔覆盖需求，“低”适合小面积或者无阻隔覆盖需求。"
    //     },{
    //         type:"name",
    //         title:"Beacon时槽",
    //         content:"设置Beacon帧的发包间隔，可以设置为(40～1000)内的值，单位为毫秒(ms)，默认值为100。"
    //     },{
    //         type:"name",
    //         title:"WMM",
    //         content:"启用该选项将使路由器可以处理带有优先级信息的数据包，建议选择此选项。"
    //     }]
    // },
    // WIRELESS_ADVANCED_5G_1:{
    //     TITLE: "高级设置",
    //     CONTENT:[{
    //         type: "paragraph",
    //         content: "您可以通过本页面进行无线网络的高级设置。"
    //     }, {
    //         type:"name",
    //         title:"信道",
    //         content:"以无线信号作为传输媒体的数据信号传送的通道。如果您选择的是自动，则路由器会自动根据周围的环境选择一个最好的信道，建议使用自动。无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"模式",
    //         content:"路由器工作的无线模式，修改无线模式后会影响路由器的无线速率，建议使用默认设置，无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"频段带宽",
    //         content:"路由器传输无线数据的频段宽度，无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"发射功率",
    //         content:"发射功率分为“高”“中”“低”三个选项，“高”适合大面积或多阻隔覆盖需求，“中”适合中等面积或少阻隔覆盖需求，“低”适合小面积或者无阻隔覆盖需求。"
    //     },{
    //         type:"name",
    //         title:"Beacon时槽",
    //         content:"设置Beacon帧的发包间隔，可以设置为(40～1000)内的值，单位为毫秒(ms)，默认值为100。"
    //     },{
    //         type:"name",
    //         title:"WMM",
    //         content:"启用该选项将使路由器可以处理带有优先级信息的数据包，建议选择此选项。"
    //     }]
    // },
    // WIRELESS_ADVANCED_5G_2:{
    //     TITLE: "高级设置",
    //     CONTENT:[{
    //         type: "paragraph",
    //         content: "您可以通过本页面进行无线网络的高级设置。"
    //     }, {
    //         type:"name",
    //         title:"信道",
    //         content:"以无线信号作为传输媒体的数据信号传送的通道。如果您选择的是自动，则路由器会自动根据周围的环境选择一个最好的信道，建议使用自动。无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"模式",
    //         content:"路由器工作的无线模式，修改无线模式后会影响路由器的无线速率，建议使用默认设置，无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"频段带宽",
    //         content:"路由器传输无线数据的频段宽度，无线桥接开启时无法配置。"
    //     },{
    //         type:"name",
    //         title:"发射功率",
    //         content:"发射功率分为“高”“中”“低”三个选项，“高”适合大面积或多阻隔覆盖需求，“中”适合中等面积或少阻隔覆盖需求，“低”适合小面积或者无阻隔覆盖需求。"
    //     },{
    //         type:"name",
    //         title:"Beacon时槽",
    //         content:"设置Beacon帧的发包间隔，可以设置为(40～1000)内的值，单位为毫秒(ms)，默认值为100。"
    //     },{
    //         type:"name",
    //         title:"WMM",
    //         content:"启用该选项将使路由器可以处理带有优先级信息的数据包，建议选择此选项。"
    //     }]
    // },
       WIRELESS_VISITOR :{ 
               TITLE:"Guest Network",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure the parameters of Guest Network on this page."
                       } ,{                      
                           type: "name",
                           title: "Guest Network",
                           content: "Check the box to enable Guest Network."
                       } ,{                      
                           type: "name",
                           title: "SSID",
                           content: "Specify the name of the Guest Network."
                       } ,{                      
                           type: "name",
                           title: "SSID Encoding",
                           content: "Set the SSID Encoding as UTF8 or GBK. Only when the SSID contains Chinese charaters can you configure this parameter."
                       } ,{                      
                           type: "name",
                           title: "Security",
                           content: "Select one of the following security options.",
            children:[{
                type: "step",
                content:[
                "No Security: Select this option to disable the network security. It is not recommended to choose this option for security.",
                "WPA-PSK/WPA-PSK/WPA2-PSK (Recommended): Select WPA-PSK/WPA2-PSK as the security option. This option requires a PSK password for authentication and you do not need to configure the authentication server."
                ]
            }]
                       } ,{                      
                           type: "name",
                           title: "PSK Password",
                           content: "Specify a password when you select WPA-PSK/WPA2-PSK as the security option. Please enter 8 to 63 ASCII characters or 8 to 64 hexadecimal characters. "
                       }]
},
       WIRELESS_VISITOR_ADVANCED :{ 
               TITLE:"Advanced Settings",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can configure advanced parameters for the Guest Network."
                       } ,{                      
                           type: "name",
                           title: "Upstream/Downstream Bandwidth",
                           content: "Specify the maximum upstream/downstream bandwidth in Kbps for the Guest Network. The value should be 100 to 1000000 or 0 and 0 means no limit."
                       } ,{                      
                           type: "name",
                           title: "Maximum number of access devices",
                           content: "Specify the maximum number of wireless devices allowing to access the Guest Network. The number should be 1 to 20."
                       }]
},
       WIRELESS_MACFILTER :{ 
               TITLE:"Wireless MAC Filtering",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can control the wireless access by configuring the Wireless MAC Filtering on this page."
                       } ,{                      
                           type: "name",
                           title: "Wireless MAC Filtering",
                           content: "Check the box to enable Wireless MAC Filtering function."
                       } ,{                      
                           type: "name",
                           title: "SSID",
                           content: "Select an SSID in the drop-down list. The related MAC Address Filtering rules can be applied to the SSID you select. A new SSID can be created on the Wireless > Wireless Settings > Multi-SSID page."
                       } ,{                      
                           type: "name",
                           title: "Filtering Rules",
                           content: "Select the filtering rule.",
            children:[{
                type:"step",
                content:[
                "Blacklist (Deny access of devices): The router will deny the host with the MAC Address in the rule list to access the local wireless network.",
                "Whitelist (Allow access of devices): The router will allow the host with the MAC Address is in the rule list to access the local wireless network."
                ]
            }]
        }]
    },
       WIRELESS_MACFILTER_LIST :{ 
               TITLE:"Rule List",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the MAC Filtering list or configure the current entries."
                       } ,{                      
                           type: "name",
                           title: "MAC Address",
                           content: "Enter the MAC address in the format xx-xx-xx-xx-xx-xx."
                       } ,{                      
                           type: "name",
                           title: "Description",
                           content: "Give a description for the MAC filtering entry. It ranges from 1 to 50 characters."
                       }]
},
       WIRELESS_HOST_STATUS :{ 
               TITLE:"Wireless Host Status",
               CONTENT: [{
                           type: "paragraph",
                           content: "You can view the information of all the hosts connected to the wireless network on this page."
                       } ,{                      
                           type: "name",
                           title: "SSID",
                           content: "Select an SSID, the status of the host in this wireless network will display on the following table. "
                       } ,{                      
                           type: "name",
                           title: "Host Name",
                           content: "Displays the name of the host connected to the router wirelessly. "
                       } ,{                      
                           type: "name",
                           title: "MAC Address",
                           content: "Displays the MAC address of the host connected to the router wirelessly. "
                       } ,{                      
                           type: "name",
                           title: "Host SSID",
                           content: "Displays the name of the SSID to which the host connects."
                       } ,{                      
                           type: "name",
                           title: "Upstream/Downstream Bandwidth (KB/s)",
                           content: "Displays the upstream/downstream bandwidth of the host."
                       } ,{                      
                           type: "name",
                           title: "Status",
                           content: "Displays the status of the wireless connection."
                       }]
},


	//  ISP_ROUTING_SETTING:{
	// 	TITLE: "ISP选路",
	// 	CONTENT: [{
	// 		 type: "paragraph",
	// 		 content: "您可以通过本页面设置进行ISP选路设置，导入ISP数据库。"
	// 	},
	// 	{
	// 		 type: "name",
	// 		 title: "启用ISP地址段选路功能",
	// 		 content: "选中<启用ISP地址段选路功能>，将根据ISP进行选路。"
	// 	}]
	//  },
	//  ISP_IMPORT:{
	// 	TITLE: "导入ISP数据库",
	// 	CONTENT: [{
	// 		 type: "name",
	// 		 title: "导入",
	// 		 content: "可以导入ISP数据库对系统预设的ISP选路进行升级。"
	// 	}]
	//  },

	//  ISP_USER_DEFINE_HELP:{
	// 	TITLE: "用户自定义数据库",
	// 	CONTENT: [
	// 	{
	// 		 type: "name",
	// 		 title: "导入",
	// 		 content: "自定义数据库文件格式为每行由“IP/mask”组成，如“12.12.12.12/24”，总个数不超过2048条。文件格式为txt格式。"
	// 	}]
	//  },

	//  ISP_ROUTING_LIST:{
	// 	TITLE: "选路列表",
	// 	CONTENT: [{
	// 		 type: "paragraph",
	// 		 content: "您可以查看选路条目，还可以通过表格按钮对条目进行操作。"
	// 	},
	// 	{
	// 		 type: "name",
	// 		 title: "接口",
	// 		 content: "选择ISP选路的出接口。"
	// 	 },
	// 	{
	// 		 type: "name",
	// 		 title: "ISP",
	// 		 content: "选择ISP（Internet Service Provider，网络服务提供商）。"
	// 	 }]
	//  },

	// ADVANCED_ROUTING_STATIC_RULE:{
	// 	TITLE: "规则列表",
	// 	CONTENT: [{
	// 		 type: "paragraph",
	// 		 content: "您可以查看路由条目，还可以通过表格按钮对条目进行操作。"
	// 	}
	// 	 ]
	//  },
	 
	//  BWLIST_SETTING:{
	// 	TITLE: "功能设置",
	// 	CONTENT: [{
	// 		 type: "paragraph",
	// 		 content: "您可以通过本页面设置QQ黑白名单。"
	// 	},
	// 	{
	// 		 type: "name",
	// 		 title: "启用QQ黑白名单",
	// 		 content: "选中<启用QQ黑白名单>，将开启该功能。"
	// 	}]
	//  },
	//  BWLIST:{
	// 	TITLE: "规则列表",
	// 	CONTENT: [{
	// 		 type: "name",
	// 		 title: "受控控制组",
	// 		 content: "设置地址组。"
	// 	 },
	// 	 {
	// 		 type: "name",
	// 		 title: "规则类型",
	// 		 content: "设置QQ白名单或QQ黑名单。"
	// 	 },
	// 	{
	// 		 type: "name",
	// 		 title: "QQ号码",
	// 		 content: "设置相应的QQ信息。"
	// 	 },
	// 	 {
	// 		 type: "name",
	// 		 title: "生效时间",
	// 		 content: "选择时间信息，在此时间之内，方可生效。"
	// 	 },
	// 	 {
	// 		 type: "name",
	// 		 title: "备注",
	// 		 content: "设置备注信息。"
	// 	 },
	// 	  {
	// 		 type: "name",
	// 		 title: "状态",
	// 		 content: "设置启用/禁用。"
	// 	 },
	// 	  {
	// 		 type: "name",
	// 		 title: "添加到指定位置",
	// 		 content: "将规则设置到指定的位置。"
	// 	 }]
	//  },
	 
	//  SYSTEM_MODE:{
	// 	TITLE: "System Mode",
	// 	CONTENT: [{
	// 		 type: "paragraph",
	// 		 content: "设置接口模式。"
	// 	},
	// 	{
	// 		 type: "name",
	// 		 title: "Nat",
	// 		 content: "NAT (Network Address Translation) mode allows the device to translate private IP addresses within internal networks to public IP addresses for transport over external networks, such as the Internet. Incoming traffic is translated back for delivery within the internal network."
	// 	},
	// 	{
	// 		 type: "name",
	// 		 title: "Non-Nat",
	// 		 content: "On this mode, the device functions as the traditional Gateway and forwards the packets via routing protocol."
	// 	},
	// 	{
	// 		 type: "name",
	// 		 title: "Classic",
	// 		 content: "It's the combined mode of NAT mode and Routing mode."
	// 	}]
	//  },
	 	
	//  	 	DYN3322DDNS: {
	// 	 TITLE: "3322动态域名",
	// 	 CONTENT: [{
	// 		 type: "paragraph",
	// 		 content: "通过DDNS（Dynamic DNS，动态域名解析服务），您可以将固定域名与动态IP进行绑定，使Internet用户可以通过域名来访问路由器或内网主机。您可以通过本页面登录3322动态域名服务器，开启3322动态域名服务。"
	// 	 },{
	// 		 type: "name",
	// 		 title: "服务接口",
	// 		 content: "3322动态域名服务生效的接口。"
	// 	 },{
	// 		 type: "name",
	// 		 title: "用户名",
	// 		 content: "3322动态域名服务账户的用户名。"
	// 	 },{
	// 		 type: "name",
	// 		 title: "密码",
	// 		 content: "3322动态域名服务账户的密码。"
	// 	 },{
	// 		 type: "name",
	// 		 title: "启用/禁用",
	// 		 content: "选择是否在添加该账户后立即登录3322动态域名服务器，开启动态域名服务。"
	// 	 },{
	// 		 type: "name",
	// 		 title: "域名",
	// 		 content: "从DDNS服务器获取的域名服务列表，最多可以显示16条域名信息。"
	// 	 } ]
	//  },
		
	// 	IPV6_MAC_CLONE: {
	// 		TITLE: "MAC Clone",
	// 		CONTENT: [{
	// 			type: "name",
	// 			title: "Use Default MAC Address",
	// 			content: "Do NOT change the default MAC address of the router, in case the ISP does not bind the assigned IP address to the MAC address."
	// 		},{
	// 			type: "name",
	// 			title: "Use Current Computer MAC Address",
	// 			content: "Select to copy the current MAC address of the computer that is connected to the router, in case the ISP binds the assigned IP address to the computer's MAC address."
	// 		},{
	// 			type: "name",
	// 			title: "Use Custom MAC Address",
	// 			content: "Enter the MAC address manually, in case the ISP binds the assigned IP address to the specific MAC address."
	// 		},{
	// 			type: "paragraph",
	// 			content: "Click Save to save all your settings."
	// 		}]
	// 	},
	 
	//  SWITCH_PORTVLAN:{
	// 	TITLE: "Port VLAN",
	// 	CONTENT: [{
	// 		type: "paragraph",
	// 		content: "您可以通过基于端口的VLAN划分，控制端口之间是否可以进行通信，从而灵活地部署网络环境。"
	// 	 },{
	// 		type: "name",
	// 		title: "网络",
	// 		content: "用于标识各个物理端口此时属于的逻辑网络。"
	// 	 },{
	// 		type: "name",
	// 		title: "VLAN",
	// 		content: "您可以将端口划分入不同的VLAN。"
	// 	 },{
	// 		type: "note",
	// 		title: "提示",
	// 		content: [
	// 			"Port VLAN的划分只能在LAN口中进行。",
	// 			"只有位于同一个Port VLAN中的端口之间才能进行通信，位于不同Port VLAN的端口之间无法进行通信。"
	// 		]
	// 	 }]
	//  },
	 
	//  PRINTER_SERVER: {
	// 	TITLE: "打印服务器",
	// 	CONTENT: [{
	// 		type: "paragraph",
	// 		content: "通过本页面您可以设置启用/禁用USB网络打印服务器。"
	// 	}]
	//  },
	//  WECHAT_WIFI_FUNCTION: {
	// 	TITLE: "功能设置",
	// 	CONTENT: [{
	// 		type: "paragraph",
	// 		content: "您可以通过本页面设置微信连WiFi功能。"
	// 	},
	// 	{
	// 		type: "name",
	// 		title: "状态",
	// 		content: "滑块为灰色表示禁用，滑块为蓝色表示启用。"
	// 	}, {
	// 		type: "name",
	// 		title: "有线端口免认证",
	// 		content: "启用该功能后有线端口直接跳过认证阶段。滑块为灰色表示禁用，滑块为蓝色表示启用。"
	// 	}]
	// },
	//  WECHAT_WIFI_PARAMETER: {
	// 	TITLE: "微信公众平台参数设置",
	// 	CONTENT: [{
	// 		type: "name",
	// 		title: "微信公众平台参数设置",
	// 		content: "设置微信公众平台参数前需先登陆微信公众平台官网注册相关门店，注册成功后，微信公众平台提供一系列参数（SSID、ShopID、AppID、Secretkey），获取到参数后需将相关添加到路由器中，如果之前已经注册成功，只需将微信公众平台参数设置到路由器中。"
	// 	},{
	// 		type: "name",
	// 		title: "SSID",
	// 		content: "设备无线网络的名称。路由器的SSID需与微信公众平台上注册的SSID保存一致。"
	// 	}, {
	// 		type: "name",
	// 		title: "ShopID",
	// 		content: "商家微信公众平台门店ID。"
	// 	}, {
	// 		type: "name",
	// 		title: "AppID",
	// 		content: "商家微信公众平台账号。"
	// 	}, {
	// 		type: "name",
	// 		title: "Secretkey",
	// 		content: "商家微信公众平台账号的密钥。"
	// 	}, {
	// 		type: "name",
	// 		title: "微信连Wi-Fi设置说明",
	// 		content: "通过该链接您可以看到更详细的设置教程。您需要连接互联网才能查看该教程。"
	// 	}]
	//  },
	//  WECHAT_WIFI_PAGE: {
	// 	TITLE: "认证页面设置",
	// 	CONTENT: [{
	// 		type: "name",
	// 		title: "背景图片",
	// 		content: "设置微信认证页面的背景图片。点击<上传>按钮来设置您的自定义背景图片。如不上传，则会使用设备自带的默认背景图片。"
	// 	}, {
	// 		type: "name",
	// 		title: "Logo图片",
	// 		content: "设置微信认证页面的Logo图片。点击<上传>按钮来设置您的自定义Logo图片。点击<删除>按钮将不使用Logo图片。"
	// 	}, {
	// 		type: "name",
	// 		title: "Logo信息",
	// 		content: "设置微信认证页面的Logo信息。Logo信息位于Logo图片的正下方。可以输入1-25个字符。"
	// 	 }, {
	// 		type: "name",
	// 		title: "欢迎信息",
	// 		content: "设置微信认证页面的欢迎信息。欢迎信息位于登录按钮的上方。可以输入1-50个字符。"
	// 	 }, {
	// 		type: "name",
	// 		title: "登录按钮提示文字",
	// 		content: "设置微信认证页面的登录按钮提示文字。可以输入1-15个字符。"
	// 	 }, {
	// 		type: "name",
	// 		title: "版权声明",
	// 		content: "设置微信认证页面的版权声明。版权声明位于认证页面底部。可以输入1-25个字符。"
	// 	 }, {
	// 		type: "name",
	// 		title: "页面预览",
	// 		content: "通过点击<预览Portal页面>按钮可以预览设置后的微信认证页面效果。"                                          
	// 	}]
	//  },
	//  WECHAT_WIFI_TIME: {
	// 	TITLE: "免费上网时长设置",
	// 	CONTENT: [{
	// 		type: "name",
	// 		title: "免费上网时长",
	// 		content: "设置用户通过认证后能使用网络的时长，可设置最短1分钟，最长1440分钟。"
	// 	}]
	//  },

	 "" :     ""
	};
})(jQuery);
