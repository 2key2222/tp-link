/**
 * \addtogroup httpd
 * @{
 */

/**
 * \file
 * HTTP server header file.
 * \author Adam Dunkels <adam@dunkels.com>
 */

/*
 * Copyright (c) 2001, Adam Dunkels.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.  
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: httpd.h,v 1.4.2.3 2003/10/06 22:56:44 adam Exp $
 *
 */

#ifndef __HTTPD_H__
#define __HTTPD_H__

void httpd_init(void);
void httpd_appcall(void);

/* UIP_APPCALL: the name of the application function. This function
 must return void and take no arguments (i.e., C type "void
 appfunc(void)"). */
#ifndef UIP_APPCALL
#define UIP_APPCALL		httpd_appcall
#endif

struct httpd_state {
	uint8_t state;
	uint8_t *dataptr;
	uint16_t count;
	unsigned int upload;
	unsigned int upload_total;
	
	int http_post_done;
	int http_upload_failed;
	int data_start_found;
	unsigned char post_packet_counter;
	unsigned char post_packet_counter_line;
	char *boundary_value;
};
/*
char result_head[400] =
{
    "<html>" \
	"<head>" \
		"<meta charset="utf-8">" \
		"<link rel=\"stylesheet\" href=\"style.css\">" \
	"</head>"
}
char result_to_web[6][]
{
    "<p>write flash failed.</p>",
    "upgrade success, please manually reboot your device.",
    "<p>the firmware is too large.</p>",
    "<p>the firmware is too small.</p>",
    "<p>firmware partition is not right</p>",
    "<p>firmware is not for this model.</p>"
}
*/
/* UIP_APPSTATE_SIZE: The size of the application-specific state
 stored in the uip_conn structure. */
#ifndef UIP_APPSTATE_SIZE
#define UIP_APPSTATE_SIZE (sizeof(struct httpd_state))
#endif

//#define FS_STATISTICS 1

extern struct httpd_state *hs;

#endif /* __HTTPD_H__ */
