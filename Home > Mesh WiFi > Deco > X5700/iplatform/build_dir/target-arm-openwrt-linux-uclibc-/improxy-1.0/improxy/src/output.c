/*
 * This file is part of improxy.
 *
 * Copyright (C) 2012 by Haibo Xi <haibbo@gmail.com>
 *
 * The program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * Website: https://github.com/haibbo/improxy
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/if.h>
#include <linux/igmp.h>
#include <netinet/ip.h>

#include <arpa/inet.h>

#include "proxy.h"
#include "data.h"

struct imp_mldv2_query_hdr
{
    struct mld_hdr  mldh;
#if defined(__LITTLE_ENDIAN_BITFIELD)
    uint8_t qrv:3,
            suppress:1,
            resv:4;
#elif defined(__BIG_ENDIAN_BITFIELD)
    uint8_t resv:4,
            suppress:1,
            qrv:3;
#else
#error "Please fix <asm/byteorder.h>"
#endif
    uint8_t qqic;
    uint16_t nsrcs;
    struct in6_addr srcs[0];
};

void send_igmp_mld_query(imp_interface *p_if, im_version version,
    pi_addr *p_dst, pi_addr *p_gp_addr, imp_source* p_sources, int sflag)
{
    int family = 0;
    char *p = NULL;
    int     max_len = 0;

    if(p_if == NULL) {

        IMP_LOG_ERROR("p_if is NULL\n");
        return;
    }
    family = p_if->if_addr.ss.ss_family;


    if(family !=  p_dst->ss.ss_family || (p_gp_addr != NULL &&
        family !=  p_gp_addr->ss.ss_family)) {

        IMP_LOG_ERROR("family don't match, can't send igmp query\n");
        return;
    }

    if(p_if == NULL) {
        IMP_LOG_DEBUG("p_if = NULL\n");
        max_len = MAX_RECV_BUF_LEN;
    }
    else
        max_len = p_if->if_mtu;

    if((p = malloc(max_len)) == NULL){
       IMP_LOG_FATAL("malloc failed\n");
       exit(1);
    }

    bzero(p, max_len);

    if(family == AF_INET) {

        struct igmpv3_query* p_igh;
        struct sockaddr_in din;
        int     igh_len = 0;
        int socket = get_igmp_mld_socket(AF_INET);

        bzero(&din, sizeof(struct sockaddr_in));
        IMP_LOG_DEBUG("src = %s dst = %s \n", imp_pi_ntoa(&p_if->if_addr), imp_pi_ntoa(p_dst));

        max_len -= (sizeof(struct iphdr) + 4);
        IMP_LOG_DEBUG("max_len = %d\n", max_len);

        p_igh = (struct igmpv3_query*)p;

        p_igh->type = IGMP_HOST_MEMBERSHIP_QUERY;

        if(version != IM_IGMPv1)
            p_igh->code = TIMER_QRI * 10; /*10 secs*/;

        if (p_gp_addr != NULL) {

            IMP_LOG_DEBUG("g = %s \n", imp_pi_ntoa(p_gp_addr));
            p_igh->group = p_gp_addr->v4.sin_addr.s_addr;
            p_igh->code = TIMER_LMQI * 10; /*1 sec*/
        }
        p_igh->csum = 0;

        p_igh->qrv  = 2;
        p_igh->qqic = 125;
        p_igh->nsrcs = 0;
        p_igh->suppress = sflag;

        while(p_sources && version == IM_IGMPv3_MLDv2) {

            /* This number is limited by the MTU of the network over which
             * the Query is transmitted.  [RFC 3376 4.1.8]
            */
            if(igh_len > max_len - sizeof(struct in_addr))
                break;

            if(p_sources->src_addr.ss.ss_family == AF_INET) {

                if(imp_source_is_scheduled(p_sources, sflag) == 0) {

                    p_sources = LIST_NEXT(p_sources, link);
                    continue;
                }

                p_igh->srcs[p_igh->nsrcs] = p_sources->src_addr.v4.sin_addr.s_addr;
                p_igh->nsrcs++;
                igh_len += sizeof(int);
            }

            p_sources = LIST_NEXT(p_sources, link);
        }

        p_igh->nsrcs=htons(p_igh->nsrcs);

        if(version == IM_IGMPv3_MLDv2)
            igh_len = sizeof(struct igmpv3_query) + p_igh->nsrcs * sizeof(int);
        else
            igh_len = sizeof(struct igmphdr);

        IMP_LOG_DEBUG("igh_len  = %d\n", igh_len);
        p_igh->csum = in_cusm((unsigned short*)p_igh, igh_len);

        setsockopt(socket, IPPROTO_IP, IP_MULTICAST_IF,
            &p_if->if_addr.v4.sin_addr, sizeof(struct in_addr));

        din.sin_family = AF_INET;
        din.sin_addr.s_addr = p_dst->v4.sin_addr.s_addr;

        if(sendto(socket, p_igh, igh_len, 0, (struct sockaddr*)&din, sizeof(din)) == -1){
            IMP_LOG_ERROR("sendto failed\n");
        }

        free(p);

    }else if(family== AF_INET6) {

        struct imp_mldv2_query_hdr *p_hdr;

        int outif = 0;
        unsigned char rabuf[] = {0x05, 0x02, 0x00, 0x00, 0x01, 0x00};
        struct { struct ip6_hbh p_iph;char buf[sizeof(rabuf)];} hyhoption;
        int p_hdr_len;
        int socket = get_igmp_mld_socket(AF_INET6);

        /*hop-by-hop use 8 bytes*/
        max_len -= (sizeof(struct ip6_hdr) + 8);

        p_hdr = (struct imp_mldv2_query_hdr *)p;
#if 0 /*uClibc Don't support inet6_opt_xxx*/ /*temp solution: hex code*/
        {
            int currentlen = 0;
            char *hhbuf = NULL;
            void *optp= NULL;
            unsigned short val = IP6_ALERT_MLD;

            cmsg->cmsg_type = IPV6_HOPOPTS;
            cmsg->cmsg_level= IPPROTO_IPV6;
            cmsg->cmsg_len = CMSG_LEN(hhlen);
            hhbuf = CMSG_DATA(cmsg);

           if((currentlen = inet6_opt_init(hhbuf, hhlen)) == -1) {
                IMP_LOG_ERROR("inet6_opt_init fail %s\n", strerror(errno));

            }

            IMP_LOG_DEBUG("currentlen = %d\n", currentlen);
            if((currentlen = inet6_opt_append(hhbuf, hhlen, currentlen, IP6OPT_ROUTER_ALERT, 2, 2, &optp)) == -1) {
                IMP_LOG_ERROR("inet6_opt_append fail %s\n", strerror(errno));

            }

            IMP_LOG_DEBUG("currentlen = %d\n", currentlen);
            inet6_opt_set_val(optp, 0, &val, sizeof(val));

            IMP_LOG_DEBUG("currentlen = %d\n", currentlen);
            if((currentlen = inet6_opt_finish(hhbuf, hhlen, currentlen)) == -1) {
                IMP_LOG_ERROR("inet6_opt_finish fail %s\n", strerror(errno));

            }

            IMP_LOG_DEBUG("currentlen = %d\n", currentlen);

        }
#endif

        p_hdr->mldh.mld_type = MLD_LISTENER_QUERY;
        p_hdr->mldh.mld_code = 0;
        p_hdr->mldh.mld_cksum = 0;
        p_hdr->mldh.mld_maxdelay = htons(10000);/*ms 10secs*/
        p_hdr->suppress = sflag;
        p_hdr->qrv      = DEFAULT_RV;
        p_hdr->qqic     = TIMER_QI;
        p_hdr->nsrcs    = 0;

        if (version == IM_IGMPv3_MLDv2)
            p_hdr_len = sizeof(struct imp_mldv2_query_hdr);
        else
            p_hdr_len = sizeof(struct mld_hdr);

        while(p_sources && version == IM_IGMPv3_MLDv2) {

            if(p_hdr_len > max_len - sizeof(struct in6_addr))
                break;

            if(p_sources->src_addr.ss.ss_family == AF_INET6) {

                if(imp_source_is_scheduled(p_sources, sflag) == 0) {

                    p_sources = LIST_NEXT(p_sources, link);
                    continue;
                }

                memcpy(&p_hdr->srcs[p_hdr->nsrcs],
                    &p_sources->src_addr.v6.sin6_addr, sizeof(struct in6_addr));
                p_hdr->nsrcs++;
                p_hdr_len += sizeof(struct in6_addr);
            }

            p_sources = LIST_NEXT(p_sources, link);
       }

       if (p_gp_addr != NULL) {

            memcpy(&p_hdr->mldh.mld_addr, &p_gp_addr->v6.sin6_addr,
                sizeof(struct in6_addr));
            p_hdr->mldh.mld_maxdelay = htons(1000);/*ms 1 secs*/
        }
        p_hdr->mldh.mld_cksum = in_cusm((unsigned short*)p_hdr,
            sizeof(struct imp_mldv2_query_hdr));


        outif = p_if->if_index;
        if( setsockopt(socket, IPPROTO_IPV6, IPV6_MULTICAST_IF,
            &outif, sizeof(outif)) < 0)
            IMP_LOG_ERROR("IPV6_MULTICAST_IF fail %s\n", strerror(errno));

        hyhoption.p_iph.ip6h_len = 0;
        hyhoption.p_iph.ip6h_nxt =  IPPROTO_ICMPV6;
        memcpy(hyhoption.buf, rabuf, sizeof(rabuf));

        if( setsockopt(socket, IPPROTO_IPV6, IPV6_HOPOPTS,
                &hyhoption, sizeof(hyhoption)) < 0)
                IMP_LOG_ERROR("IPV6_HOPOPTS fail %s\n", strerror(errno));

        IMP_LOG_DEBUG("src = %s dst %s\n", imp_pi_ntoa(&p_if->if_addr),
                       imp_pi_ntoa(p_dst));

        if(sendto(socket, p_hdr, p_hdr_len, 0,
            (struct sockaddr*)p_dst, sizeof(struct sockaddr_in6)) == -1){

            IMP_LOG_ERROR("sendto failed");
        }

        free(p);
    }

    return;
}

