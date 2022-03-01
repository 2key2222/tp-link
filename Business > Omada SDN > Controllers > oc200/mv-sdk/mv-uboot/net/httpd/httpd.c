#include <common.h>
#include "uip.h"
#include "uip_arp.h"
#include "httpd.h"
#include "fs.h"
#include "fsdata.h"

#define STATE_NONE				0		// empty state (waiting for request...)
#define STATE_FILE_REQUEST		1		// remote host sent GET request
#define STATE_UPLOAD_REQUEST	2		// remote host sent POST request

// ASCII characters
#define ISO_G					0x47	// GET
#define ISO_E					0x45
#define ISO_T					0x54
#define ISO_P					0x50	// POST
#define ISO_O					0x4f
#define ISO_S					0x53
#define ISO_T					0x54
#define ISO_slash				0x2f	// control and other characters
#define ISO_space				0x20
#define ISO_nl					0x0a
#define ISO_cr					0x0d
#define ISO_tab					0x09

// we use this so that we can do without the ctype library
#define is_digit(c)				((c) >= '0' && (c) <= '9')

#define HTTPD_MAC_PATTERN					"XX-XX-XX-XX-XX-XX"
#define HTTPD_MAC_STRING_LEN				17
#define HTTPD_FIRMWARE_VERSION_PATTERN		"X.X.X Build XXXXXXXX Rel.XXXXX"
#define HTTPD_FIRMWARE_VERSION_STRING_LEN	30
#define HTTPD_PRODUCTINFO_PATTERN			"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define HTTPD_PRODUCTINFO_STRING_LEN			32


// debug
//#define DEBUG_UIP

// html files
extern const struct fsdata_file file_index_html;
extern const struct fsdata_file file_logo_png;
extern const struct fsdata_file file_style_css;
extern const struct fsdata_file file_deviceinfo_json;
extern const struct fsdata_file file_result_false_json;
extern const struct fsdata_file file_result_true_json;

unsigned char *http_data_pointer = NULL;
int	http_is_running = 0;
int	http_ready_for_upgrade = 0;
int	http_ready_for_reboot = 0;
int	http_ready_for_poweroff = 0;
int	http_ready_for_xx_delay = 0;

extern u32 net_boot_file_size;
extern int dkmgt_get_firmwareversion(char *frmwareversion, int len);
extern int dkmgt_get_mac(char *macstring, int len);
extern int dkmgt_get_productinfo(char *productinfo, int len);
extern int dkmgt_factory(void);
extern int dkmgt_firmware_check(char* firmware, int firmware_size);
extern int dkmgt_firmware_upgrade(char* firmware, int firmware_size);
extern int board_sys_led(int onoff);
extern int ar8236_down(void);

extern int ctrlc(void);
// extern flash_info_t flash_info[];

// http app state
struct httpd_state *hs;
int upgrade_result = UPGRADE_NOT_BEGIN;


// 0x0D -> CR 0x0A -> LF
static char eol[3] = { 0x0d, 0x0a, 0x00 };
static char eol2[5] = { 0x0d, 0x0a, 0x0d, 0x0a, 0x00 };


// str to int
static int atoi(const char *s){
	int i = 0;

	while(is_digit(*s)){
		i = i * 10 + *(s++) - '0';
	}

	return(i);
}

// print downloading progress
static void httpd_download_progress( void ){
	if ( hs->post_packet_counter_line == 39 ) {
		puts( "\n         " );
		hs->post_packet_counter_line = 0;
	}

	if ( hs->post_packet_counter == 100 ) {
		puts("#");
		hs->post_packet_counter = 0;
		hs->post_packet_counter_line++;
	}

	hs->post_packet_counter++;
}

// http server init
void httpd_init( void ) {
	uip_listen( HTONS( 80 ) );
}

// reset app state
static void httpd_state_reset(void){
	hs->state = STATE_NONE;
	hs->count = 0;
	hs->dataptr = 0;
	hs->upload = 0;
	hs->upload_total = 0;
	hs->data_start_found = 0;
	hs->post_packet_counter = 0;
	hs->post_packet_counter_line = 0;
	if(hs->boundary_value){
		free(hs->boundary_value);
        hs->boundary_value = NULL;
	}
}

// find and get first chunk of data
static int httpd_findandstore_firstchunk(void){
	char *start = NULL;
	char *end = NULL;
//	flash_info_t *info = &flash_info[0];

	if ( !hs->boundary_value ) {
		return -1;
	}

	// chek if we have data in packet
	start = ( char * )strstr( ( char * )uip_appdata, ( char * )hs->boundary_value );

	if ( start ) {

		// ok, we have data in this packet!
		// find upgrade type

		end = ( char * )strstr( ( char * )start, "name=" );

		if ( end == NULL) {

			printf("## Error: input name not found!\n");
			return -1;

		} 

		end = NULL;

		// find start position of the data!
		end = (char *)strstr((char *)start, eol2);

		if(end){

			if((end - (char *)uip_appdata) < uip_len){

				// move pointer over CR LF CR LF
				end += 4;

				// how much data we expect?
				// last part (magic value 6): [CR][LF](boundary length)[-][-][CR][LF]
				hs->upload_total = hs->upload_total - (int)(end - start) - strlen(hs->boundary_value) - 6;

				// We need to check if file which we are going to download
				// has correct size (for every type of upgrade)

				// U-Boot
				/*
				if(hs->upload_total > 0x800000){

					printf("## Error: file too big!\n");
                    upgrade_result = FILE_TOO_LARGE;
					http_upload_failed = 1;
                    return -1;
				}
                */
				printf("Loading: ");
				/* an new upload, reset upgrade_result */
				upgrade_result = UPGRADE_NOT_BEGIN;
				// how much data we are storing now?
				hs->upload = (unsigned int)(uip_len - (end - (char *)uip_appdata));

				memcpy((void *)http_data_pointer, (void *)end, hs->upload);
				http_data_pointer += hs->upload;

				httpd_download_progress();
                return 0;
			}

		} else {
			printf("## Error: couldn't find start of data!\n");
            return -1;
		}

	}
    return -1;
}

// called for http server app
void httpd_appcall(void){
	struct fs_file fsfile;
	unsigned int i;

	switch(uip_conn->lport){

		case HTONS(80):

			// app state
			hs = (struct httpd_state *)(uip_conn->appstate);
			// closed connection
			if(uip_closed()){
				httpd_state_reset();
				uip_close();
				return;
			}
			// aborted connection or time out occured
			
			if(uip_aborted() || uip_timedout()){
				httpd_state_reset();
				printf("abort 1");
				uip_abort();
				return;
			}
			// if we are pooled
			if(uip_poll()){
				if(hs->count++ >= 100){
					httpd_state_reset();
					printf("abort 2");
					uip_abort();
				}
				return;
			}
			else
			{
                hs->count = 0;
			}

			// new connection
			if(uip_connected()){
				httpd_state_reset();
				return;
			}
			// new data in STATE_NONE
			if(uip_newdata() && hs->state == STATE_NONE){
				// GET or POST request?
				if(uip_appdata[0] == ISO_G && uip_appdata[1] == ISO_E && uip_appdata[2] == ISO_T && (uip_appdata[3] == ISO_space || uip_appdata[3] == ISO_tab)){
					hs->state = STATE_FILE_REQUEST;
				} else if(uip_appdata[0] == ISO_P && uip_appdata[1] == ISO_O && uip_appdata[2] == ISO_S && uip_appdata[3] == ISO_T && (uip_appdata[4] == ISO_space || uip_appdata[4] == ISO_tab)){
					hs->state = STATE_UPLOAD_REQUEST;
				}

				// anything else -> abort the connection!
				if(hs->state == STATE_NONE){
					httpd_state_reset();
					printf("abort 3");
					uip_abort();
					return;
				}

				// get file or firmware upload?
				if(hs->state == STATE_FILE_REQUEST){
					// we are looking for GET file name
					for(i = 4; i < 30; i++){
						if(uip_appdata[i] == ISO_space || uip_appdata[i] == ISO_cr || uip_appdata[i] == ISO_nl || uip_appdata[i] == ISO_tab){
							uip_appdata[i] = 0;
							i = 0;
							break;
						}
					}

					if(i != 0){
						printf("## Error: request file name too long!\n");
						//httpd_state_reset();
						//uip_abort();
						//return;
						uip_appdata[i] = 0;
						i = 0;
					}

					//printf("Request for: ");
					//printf("%s\n", &uip_appdata[4]);

					// request for /
					if(uip_appdata[4] == ISO_slash && uip_appdata[5] == 0){
						upgrade_result = UPGRADE_NOT_BEGIN;
						fs_open(file_index_html.name, &fsfile);
					} else if(strncmp((const char *)&uip_appdata[4], "/style.css", strlen("/style.css"))== 0){
						fs_open(file_style_css.name, &fsfile);
					} else if(strncmp((const char *)&uip_appdata[4], "/logo.png", strlen("/logo.png"))== 0){
						fs_open(file_logo_png.name, &fsfile);
					} else if(strncmp((const char *)&uip_appdata[4], "/deviceinfo", strlen("/deviceinfo"))== 0){
						char productinfo[HTTPD_PRODUCTINFO_STRING_LEN+1]={0};
						char macstring[HTTPD_MAC_STRING_LEN+1]={0};
						char firmwareversion[HTTPD_FIRMWARE_VERSION_STRING_LEN+1]={0};
						char *pCurr = NULL;

						fs_open(file_deviceinfo_json.name, &fsfile);

						if (dkmgt_get_productinfo(productinfo, HTTPD_PRODUCTINFO_STRING_LEN+1) < 0 )
						{
							printf("failed to get productinfo\n");
						}
						else
						{
							pCurr = strstr(fsfile.data, HTTPD_PRODUCTINFO_PATTERN);

							if (pCurr)
							{
								int index = 0;
								while ((*pCurr != '"') && (index < HTTPD_PRODUCTINFO_STRING_LEN))
								{
									if (productinfo[index] == 0)
										*pCurr = ' '; /* use space replace it */
									else
										*pCurr = productinfo[index];

									pCurr ++;
									index ++;
								}
							}
						}

						if (dkmgt_get_mac(macstring, HTTPD_MAC_STRING_LEN+1) < 0 )
						{
							printf("failed to get mac\n");
						}
						else
						{
							pCurr = strstr(fsfile.data, HTTPD_MAC_PATTERN);
							if (pCurr)
								memcpy(pCurr, macstring, HTTPD_MAC_STRING_LEN);
						}

						if (dkmgt_get_firmwareversion(firmwareversion, HTTPD_FIRMWARE_VERSION_STRING_LEN+1) < 0 )
						{
							printf("failed to get firmwareversion\n");
						}
						else
						{
							pCurr = strstr(fsfile.data, HTTPD_FIRMWARE_VERSION_PATTERN);
							if (pCurr)
								memcpy(pCurr, firmwareversion, HTTPD_FIRMWARE_VERSION_STRING_LEN);
						}
					} else if(strncmp((const char *)&uip_appdata[4], "/reboot", strlen("/reboot"))== 0){
						fs_open(file_result_true_json.name, &fsfile);

						http_ready_for_reboot = 1;
						http_ready_for_xx_delay = 20;
					} else if(strncmp((const char *)&uip_appdata[4], "/power-off", strlen("/power-off"))== 0){
						fs_open(file_result_true_json.name, &fsfile);

						http_ready_for_poweroff = 1;
						http_ready_for_xx_delay = 20;
					} else if(strncmp((const char *)&uip_appdata[4], "/reset", strlen("/reset"))== 0){
						if (dkmgt_factory() < 0)
							fs_open(file_result_false_json.name, &fsfile);
						else
							fs_open(file_result_true_json.name, &fsfile);

						http_ready_for_reboot = 1;
						http_ready_for_xx_delay = 20;
					} else if(strncmp((const char *)&uip_appdata[4], "/upgrade_result", strlen("/upgrade_result"))== 0){
						if ((upgrade_result != UPGRADE_NOT_BEGIN) && (upgrade_result != UPGRADE_SUCCESS))
						{
							char *pCurr = NULL;
							fs_open(file_result_false_json.name, &fsfile);
							pCurr = strstr(fsfile.data, "error_code");
							if (pCurr)
							{
								pCurr = pCurr + strlen("error_code") + 3; /* 3 = ":" */
								*pCurr = (char)(upgrade_result + 48); /* number to char by ASCII */
							}
						}
						else
							fs_open(file_result_true_json.name, &fsfile);
					} else {
						// check if we have requested file
						if(!fs_open((const char *)&uip_appdata[4], &fsfile)){
							printf("file name is %s, redict to index\n", &uip_appdata[4]);
							fs_open(file_index_html.name, &fsfile);
						}
					}
					
					hs->state = STATE_FILE_REQUEST;
					hs->dataptr = (u8_t *)fsfile.data;
					hs->upload = fsfile.len;
                    //printf("give result.%08x, %08x, %08x\n", &(hs->state), (hs->dataptr), &(hs->upload));
					// send first (and maybe the last) chunk of data
					uip_send(hs->dataptr, (hs->upload > uip_mss() ? uip_mss() : hs->upload));
					return;

				} else if(hs->state == STATE_UPLOAD_REQUEST && upgrade_result != 0){

					char *start = NULL;
					char *end = NULL;
					// end bufor data with NULL
					uip_appdata[uip_len] = '\0';

					/*
					 * We got first packet with POST request
					 *
					 * Some browsers don't include first chunk of data in the first
					 * POST request packet (like Google Chrome, IE and Safari)!
					 * So we must now find two values:
					 * - Content-Length
					 * - boundary
					 * Headers with these values can be in any order!
					 * If we don't find these values in first packet, connection will be aborted!
					 *
					 */

					// Content-Length pos
					start = (char *)strstr((char*)uip_appdata, "Content-Length:");

					if(start){

						start += sizeof("Content-Length:");

						// find end of the line with "Content-Length:"
						end = (char *)strstr(start, eol);

						if(end){

							hs->upload_total = atoi(start);
#ifdef DEBUG_UIP
							printf("Expecting %d bytes in body request message\n", hs->upload_total);
#endif

						} else {
							printf("## Error: couldn't find \"Content-Length\"!\n");
							httpd_state_reset();
							uip_abort();
							return;
						}

					} else {
						printf("## Error: couldn't find \"Content-Length\"!\n");
						httpd_state_reset();
						uip_abort();
						return;
					}

					// we don't support very small files (< 10 KB)
					/*if(hs->upload_total < 10240){
						printf("## Error: request for upload < 10 KB data!\n");
						upgrade_result = FILE_TOO_SMALL;
						httpd_state_reset();
						uip_abort();
						return;
					}*/
					if(hs->upload_total > 272*1024*1024){
						upgrade_result = FILE_TOO_LARGE;
						httpd_state_reset();
						uip_abort();
						return;
					}

					// boundary value
					start = NULL;
					end = NULL;

					start = (char *)strstr((char *)uip_appdata, "boundary=");

					if(start){

						// move pointer over "boundary="
						start += 9;

						// find end of line with boundary value
						end = (char *)strstr((char *)start, eol);

						if(end){

							// malloc space for boundary value + '--' and '\0'
							hs->boundary_value = (char*)malloc(end - start + 3);

							if(hs->boundary_value){

								memcpy(&(hs->boundary_value[2]), start, end - start);

								// add -- at the begin and 0 at the end
								hs->boundary_value[0] = '-';
								hs->boundary_value[1] = '-';
								hs->boundary_value[end - start + 2] = 0;

#ifdef DEBUG_UIP
								printf("Found boundary value: \"%s\"\n", hs->boundary_value);
#endif

							} else {
								printf("## Error: couldn't allocate memory for boundary!\n");
								httpd_state_reset();
								uip_abort();
								return;
							}

						} else {
							printf("## Error: couldn't find boundary!\n");
							httpd_state_reset();
							uip_abort();
							return;
						}

					} else {
						printf("## Error: couldn't find boundary!\n");
						httpd_state_reset();
						uip_abort();
						return;
					}

					/*
					 * OK, if we are here, it means that we found
					 * Content-Length and boundary values in headers
					 *
					 * We can now try to 'allocate memory' and
					 * find beginning of the data in first packet
					 */
					http_data_pointer = (u8_t *)(load_addr);
					printf("load address is %p\n", http_data_pointer);

					if(!http_data_pointer){
						printf("## Error: couldn't allocate RAM for data!\n");
						httpd_state_reset();
						uip_abort();
						return;
					} else {
						printf("Data will be downloaded at %p in RAM\n", http_data_pointer);
					}

					if(httpd_findandstore_firstchunk() == 0){
						hs->data_start_found = 1;
					} else {
						hs->data_start_found = 0;
					}

					return;

				} /* else if(hs->state == STATE_UPLOAD_REQUEST) */

			} /* uip_newdata() && hs->state == STATE_NONE */

			// if we got ACK from remote host
			if(uip_acked()){
				// if we are in STATE_FILE_REQUEST state
				if(hs->state == STATE_FILE_REQUEST){

					// data which we send last time was received (we got ACK)
					// if we send everything last time -> gently close the connection
					if(hs->upload <= uip_mss()){

						// post upload completed?
						if(hs->http_post_done){

							if(!hs->http_upload_failed){
								http_ready_for_upgrade = 1;
							}

							hs->http_post_done = 0;
							hs->http_upload_failed = 0;
						}

						httpd_state_reset();
						uip_close();
						return;
					}

					// otherwise, send another chunk of data
					// last time we sent uip_conn->len size of data
					hs->dataptr += uip_conn->len;
					hs->upload -= uip_conn->len;
					uip_send(hs->dataptr, (hs->upload > uip_mss() ? uip_mss() : hs->upload));
				}

				return;

			}

			// if we need to retransmit
			if(uip_rexmit()){

				// if we are in STATE_FILE_REQUEST state
				if(hs->state == STATE_FILE_REQUEST){
					// send again chunk of data without changing pointer and length of data left to send
					uip_send(hs->dataptr, (hs->upload > uip_mss() ? uip_mss() : hs->upload));
				}

				return;

			}

			// if we got new data frome remote host
			if(uip_newdata()){

				// if we are in STATE_UPLOAD_REQUEST state
				if(hs->state == STATE_UPLOAD_REQUEST && upgrade_result != 0){

					// end bufor data with NULL
					uip_appdata[uip_len] = '\0';

					// do we have to find start of data?
					if(!hs->data_start_found){

						if(httpd_findandstore_firstchunk() != 0){
							printf("## Error: couldn't find start of data in next packet!\n");
							httpd_state_reset();
							uip_abort();
							return;
						} else {
							hs->data_start_found = 1;
						}

						return;
					}

					hs->upload += (unsigned int)uip_len;
					//printf("newdata len : %u(%u)\n", uip_len, http_data_pointer-(u8_t *)(load_addr));
					if(!hs->http_upload_failed){
						memcpy((void *)http_data_pointer, (void *)uip_appdata, uip_len);
						http_data_pointer += uip_len;
					}

					httpd_download_progress();

					// if we have collected all data
					if(hs->upload >= hs->upload_total){

						// end of post upload
						hs->http_post_done = 1;
						net_boot_file_size = (ulong)hs->upload_total;
						printf("\nLoading done. File size is %d bytes\n\n", net_boot_file_size);
						upgrade_result = dkmgt_firmware_check((char *)load_addr, net_boot_file_size);
						http_ready_for_upgrade = 1;
						http_ready_for_xx_delay = 0;

						//fs_open(file_result_true_json.name, &fsfile);
						//hs->state = STATE_FILE_REQUEST;
						//hs->dataptr = (u8_t *)fsfile.data;
						//hs->upload = fsfile.len;
						//uip_send((u8_t *)fsfile.data, (fsfile.len > uip_mss() ? uip_mss() : fsfile.len));

						httpd_state_reset();
						uip_close();
					}

				}

				return;
			}

			break;

		default:
			// we shouldn't get here... we are listening only on port 80
			uip_abort();
			break;
	}
}

/**********************************************************************************
 * HTTPD section
 */

#define BUF	((struct uip_eth_hdr *)&uip_buf[0])

void NetSendHttpd( void ){
	volatile uchar *tmpbuf = net_tx_packet;
	int i;
	for ( i = 0; i < 40 + UIP_LLH_LEN; i++ ) {
		tmpbuf[i] = uip_buf[i];
	}
	for( ; i < uip_len; i++ ) {
		tmpbuf[i] = uip_appdata[ i - 40 - UIP_LLH_LEN ];
	}
	eth_send( net_tx_packet, uip_len );
}

static int arptimer = 0;

void HttpdHandler( void ){
	int i;

	if ( uip_len == 0 ) {
		for ( i = 0; i < UIP_CONNS; i++ ) {
			uip_periodic( i );
			if ( uip_len > 0 ) {
				uip_arp_out();
				NetSendHttpd();
			}
		}
		if ( ++arptimer == 20 ) {
			uip_arp_timer();
			arptimer = 0;
		}
	} else {
		if ( BUF->type == htons( UIP_ETHTYPE_IP ) ) {
			uip_arp_ipin();
			uip_input();
			if ( uip_len > 0 ) {
				uip_arp_out();
				NetSendHttpd();
			}
		} else if ( BUF->type == htons( UIP_ETHTYPE_ARP ) ) {
			uip_arp_arpin();
			if ( uip_len > 0 ) {
				NetSendHttpd();
			}
		}
       // printf("len4 is %d\n", uip_len);
	}

}

// start http daemon
void HttpdStart( void ){
	uip_init();
	httpd_init();
}

void NetReceiveHttpd( volatile uchar * inpkt, int len ) {
	if (len > UIP_BUFSIZE)
		return;

	memcpy( uip_buf, ( const void * )inpkt, len );
	uip_len = len;
	if ( BUF->type == htons( UIP_ETHTYPE_IP ) ) {
		uip_arp_ipin();
		uip_input();
		if ( uip_len > 0 ) {
			uip_arp_out();
			NetSendHttpd();
		}
	} else if( BUF->type == htons( UIP_ETHTYPE_ARP ) ) {
		uip_arp_arpin();
		if ( uip_len > 0 ) {
			NetSendHttpd();
		}
	}
}

/* *************************************
 *
 * HTTP web server for web failsafe mode
 *
 ***************************************/
int NetLoopHttpd( void ){
	//DECLARE_GLOBAL_DATA_PTR;
	int ret = -EINVAL;
	unsigned short int ip[2];
	struct uip_eth_addr eaddr;
	int count = 0;

#if 0
    arp_init();
	if (!net_tx_packet) {
		int	i;
		/*
		 *	Setup packet buffers, aligned correctly.
		 */
		net_tx_packet = &PktBuf[0] + (PKTALIGN - 1);
		net_tx_packet -= (ulong)net_tx_packet % PKTALIGN;
		for (i = 0; i < PKTBUFSRX; i++) {
			NetRxPackets[i] = net_tx_packet + (i+1)*PKTSIZE_ALIGN;
		}
	}
#else
	net_init();
#endif

	for (count = 0; count < 10; count ++)
	{
		board_sys_led(1);
		udelay (200000);
		board_sys_led(0);
		udelay (200000);
	}

	printf("\n NetLoopHttpd ! \n");
	eth_halt();
	eth_set_current();
	ret = eth_init();
	if (ret < 0) {
		eth_halt();
		return ret;
	}

	//memcpy( net_ethaddr, eth_get_dev()->enetaddr, 6 );
	memcpy( eaddr.addr, net_ethaddr, 6);
	#if 0
	eaddr.addr[0] = net_ethaddr[0];
	eaddr.addr[1] = net_ethaddr[1];
	eaddr.addr[2] = net_ethaddr[2];
	eaddr.addr[3] = net_ethaddr[3];
	eaddr.addr[4] = net_ethaddr[4];
	eaddr.addr[5] = net_ethaddr[5];
	#endif
	// set MAC address
	uip_setethaddr( eaddr );

	// set ip and other addresses
	// TODO: do we need this with uIP stack?
	//NetCopyIP( &NetOurIP, &bd->bi_ip_addr );

	net_gateway		= getenv_ip( "gatewayip" );
	net_netmask		= getenv_ip( "netmask" );

    HttpdStart();
    uip_ipaddr(ip, 192,168,0,253);
	uip_sethostaddr(ip); 

	// set network mask (255.255.255.0 -> local network)
	ip[0] = htons( ( ( 0xFFFFFF00 & 0xFFFF0000 ) >> 16 ) );
	ip[1] = htons( ( 0xFFFFFF00 & 0x0000FFFF ) );
	uip_setnetmask( ip );

	// should we also set default router ip address?
	//uip_setdraddr();

	http_is_running = 1;

	// infinite loop
	for ( ; ; ) {

		/*
		 *	Check the ethernet for a new packet.
		 *	The ethernet receive routine will process it.
		 */
		if ( eth_rx() > 0 ) {
			HttpdHandler();
		}

		// if CTRL+C was pressed -> return!
		if ( ctrlc() ) {
			eth_halt();
			eth_set_current();
			eth_init( );


			// reset global variables to default state
			http_is_running = 0;
			http_ready_for_upgrade = 0;
			http_ready_for_reboot = 0;
			http_ready_for_poweroff = 0;
			printf( "\nhttp load aborted!\n\n" );
			return ( -1 );
		}

		if (http_ready_for_reboot) {
			if (http_ready_for_xx_delay > 0)
			{
				http_ready_for_xx_delay--;
				udelay (50000); 			/* wait 50 ms */
				continue;
			}
			puts ("Rebooting (CPU reset) ...\n");
			udelay (50000); 			/* wait 50 ms */

			http_ready_for_reboot = 0;

#ifdef CONFIG_MVEBU_OC300
            do_reset(NULL, 0, 0, NULL);
#else
            disable_interrupts();
            reset_cpu(0);
#endif
		}

		if (http_ready_for_poweroff) {
			if (http_ready_for_xx_delay > 0)
			{
				http_ready_for_xx_delay--;
				udelay (50000); 			/* wait 50 ms */
				continue;
			}
			puts ("Poweroff (power down switch and LED) ...\n");
			http_ready_for_poweroff = 0;

            #ifdef CONFIG_AR8236_SWITCH
			ar8236_down();
            #endif

            #ifdef CONFIG_RTL8367S_SWITCH
			//rtl_switch_down();
            #endif


			board_sys_led(0);
		}

		// until upload is not completed, get back to the start of the loop
		if ( http_ready_for_upgrade ) {
			if (http_ready_for_xx_delay > 0)
			{
				http_ready_for_xx_delay--;
				udelay (50000); 			/* wait 50 ms */
				continue;
			}

			if (upgrade_result == UPGRADE_CHECK_OK)
			{
				// stop eth interface
				eth_halt();
				printf("Firmware begin upgrade\n");

				upgrade_result = dkmgt_firmware_upgrade((char *)load_addr, net_boot_file_size);
				if (upgrade_result == UPGRADE_SUCCESS)
				{
					puts ("Firmware upgrade done, rebooting...\n\n\n");
					udelay (50000); 			/* wait 50 ms */

#ifdef CONFIG_MVEBU_OC300
                    do_reset(NULL, 0, 0, NULL);
#else
                    disable_interrupts();
                    reset_cpu(0);
#endif
				}
			}
			else
			{
				http_ready_for_upgrade = 0;
			}
		}
	}

	// reset global variables to default state
	http_is_running = 0;
	http_ready_for_upgrade = 0;
	net_boot_file_size = 0;

	return( -1 );
}

static int httpd_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	NetLoopHttpd();
	return 0;
}
	

U_BOOT_CMD(
	httpd, CONFIG_SYS_MAXARGS, 1, httpd_cmd,
	"start httpd server for firmware recovery",
	""
);

