/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#ifndef _ISISC_NAT_HELPER_H_
#define _ISISC_NAT_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif                          /* __cplusplus */

#include "fal/fal_nat.h"

    sw_error_t nat_helper_init(a_uint32_t dev_id);

    sw_error_t nat_helper_cleanup(a_uint32_t dev_id);

#ifdef IN_NAT_HELPER
#define ISISC_NAT_HELPER_INIT(rv, dev_id) \
    { \
        rv = nat_helper_init(dev_id); \
        SW_OUT_ON_ERROR(rv); \
    }

#define ISISC_NAT_HELPER_CLEANUP(rv, dev_id) \
    { \
        rv = nat_helper_cleanup(dev_id); \
        SW_OUT_ON_ERROR(rv); \
    }
#else
#define ISISC_NAT_HELPER_INIT(rv, dev_id)
#define ISISC_NAT_HELPER_CLEANUP(rv, dev_id)
#endif


#ifdef __cplusplus
}
#endif                          /* __cplusplus */
#endif                          /* _ISISC_NAT_HELPER_H_ */
