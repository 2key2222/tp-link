/*
 * Copyright (C) 2016 Marvell
 *
 * Antoine Tenart <antoine.tenart@free-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <crypto/sha.h>
#include <crypto/md5.h>
#include <linux/dmapool.h>

#include "safexcel.h"

struct safexcel_ahash_ctx {
	struct safexcel_context base;
	struct safexcel_crypto_priv *priv;

	u32 alg;
	u32 digest;

	u32 ipad[SHA1_DIGEST_SIZE / sizeof(u32)];
	u32 opad[SHA1_DIGEST_SIZE / sizeof(u32)];
};

/* Ahash structures */
struct safexcel_ahash_req {
	bool last_req;
	bool finish;
	bool hmac;
	bool needs_inv;

	int nents;
	dma_addr_t result_dma;

	u8 state_sz;	/* expected sate size, only set once */
	u32 state[SHA256_DIGEST_SIZE / sizeof(u32)] __aligned(sizeof(u32));

	u64 len;
	u64 processed;

	u8 cache[SHA256_BLOCK_SIZE] __aligned(sizeof(u32));
	u8 cache_next[SHA256_BLOCK_SIZE] __aligned(sizeof(u32));
};

struct safexcel_ahash_export_state {
	u64 len;
	u64 processed;

	u32 state[SHA256_DIGEST_SIZE / sizeof(u32)];
	u8 cache[SHA256_BLOCK_SIZE];
};

static const u8 md5_zero_digest[MD5_DIGEST_SIZE] = {
	0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
	0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e,
};

static const u8 sha1_zero_digest[SHA1_DIGEST_SIZE] = {
	0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55,
	0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09,
};

static const u8 sha224_zero_digest[SHA224_DIGEST_SIZE] = {
	0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b, 0xc9, 0x47,
	0x61, 0x02, 0xbb, 0x28, 0x82, 0x34, 0xc4, 0x15, 0xa2,
	0xb0, 0x1f, 0x82, 0x8e, 0xa6, 0x2a, 0xc5, 0xb3, 0xe4,
	0x2f
};

static const u8 sha256_zero_digest[SHA256_DIGEST_SIZE] = {
	0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a,
	0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24, 0x27, 0xae,
	0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c, 0xa4, 0x95, 0x99,
	0x1b, 0x78, 0x52, 0xb8, 0x55
};

/* Build hash token */
static void safexcel_hash_token(struct safexcel_command_desc *cdesc,
				u32 input_length, u32 result_length)
{
	struct safexcel_token *token =
		(struct safexcel_token *)cdesc->control_data.token;

	token[0].opcode = EIP197_TOKEN_OPCODE_DIRECTION;
	token[0].packet_length = input_length;
	token[0].stat = EIP197_TOKEN_STAT_LAST_HASH;
	token[0].instructions = EIP197_TOKEN_INS_TYPE_HASH;

	token[1].opcode = EIP197_TOKEN_OPCODE_INSERT;
	token[1].packet_length = result_length;
	token[1].stat = EIP197_TOKEN_STAT_LAST_HASH |
			EIP197_TOKEN_STAT_LAST_PACKET;
	token[1].instructions = EIP197_TOKEN_INS_TYPE_OUTPUT |
				EIP197_TOKEN_INS_INSERT_HASH_DIGEST;
}

/* Build hash context control data */
static void safexcel_context_control(struct safexcel_ahash_ctx *ctx,
				     struct safexcel_ahash_req *req,
				     struct safexcel_command_desc *cdesc,
				     unsigned int digestsize,
				     unsigned int blocksize)
{
	int i, ctrl_size;

	cdesc->control_data.control0 |= CONTEXT_CONTROL_TYPE_HASH_OUT;
	cdesc->control_data.control0 |= ctx->alg;
	cdesc->control_data.control0 |= ctx->digest;

	if (ctx->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED) {
		if (req->processed) {
			if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA1)
				ctrl_size = SHA1_DIGEST_SIZE / sizeof(u32);
			else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA224 ||
				 ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA256)
				ctrl_size = SHA256_DIGEST_SIZE / sizeof(u32);
			else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5)
				ctrl_size = MD5_DIGEST_SIZE / sizeof(u32);

			/* last word in context is the number of blocks */
			ctrl_size += 1;
			cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(ctrl_size);
			cdesc->control_data.control1 |= CONTEXT_CONTROL_DIGEST_CNT;
		} else {
			cdesc->control_data.control0 |= CONTEXT_CONTROL_RESTART_HASH;
		}

		if (!req->finish)
			cdesc->control_data.control0 |= CONTEXT_CONTROL_NO_FINISH_HASH;

		/*
		 * Copy the input digest if needed, and setup the context
		 * fields. Do this now as we need it to setup the first command
		 * descriptor.
		 */
		if (req->processed) {
			for (i = 0; i < digestsize / sizeof(u32); i++)
				ctx->base.ctxr->data[i] = cpu_to_le32(req->state[i]);

			if (req->finish)
				ctx->base.ctxr->data[i] = cpu_to_le32(req->processed / blocksize);
		}
	} else if (ctx->digest == CONTEXT_CONTROL_DIGEST_HMAC) {
		cdesc->control_data.control0 |= CONTEXT_CONTROL_SIZE(10);

		memcpy(ctx->base.ctxr->data, ctx->ipad, digestsize);
		memcpy(ctx->base.ctxr->data + digestsize / sizeof(u32),
		       ctx->opad, digestsize);
	}
}

/* Handle a hash result descriptor */
static int safexcel_handle_req_result(struct safexcel_crypto_priv *priv, int ring,
				      struct crypto_async_request *async,
				      bool *should_complete, int *ret)
{
	struct safexcel_result_desc *rdesc;
	struct ahash_request *areq = ahash_request_cast(async);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *sreq = ahash_request_ctx(areq);
	int cache_len;

	*ret = 0;

	spin_lock_bh(&priv->ring[ring].egress_lock);
	rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
	if (IS_ERR(rdesc)) {
		dev_err(priv->dev,
			"hash: result: could not retrieve the result descriptor\n");
		*ret = PTR_ERR(rdesc);
	} else if (rdesc->result_data.error_code) {
		dev_err(priv->dev,
			"hash: result: result descriptor error (%d)\n",
			rdesc->result_data.error_code);
		*ret = -EINVAL;
	}

	safexcel_complete(priv, ring);
	spin_unlock_bh(&priv->ring[ring].egress_lock);

	if (sreq->finish)
		memcpy(areq->result, sreq->state,
		       crypto_ahash_digestsize(ahash));

	if (sreq->nents) {
		dma_unmap_sg(priv->dev, areq->src, sreq->nents, DMA_TO_DEVICE);
		sreq->nents = 0;
	}

	if (sreq->result_dma) {
		dma_unmap_single(priv->dev, sreq->result_dma, sreq->state_sz,
				 DMA_FROM_DEVICE);
		sreq->result_dma = 0;
	}

	safexcel_free_context(priv, async);

	cache_len = sreq->len - sreq->processed;
	if (cache_len)
		memcpy(sreq->cache, sreq->cache_next, cache_len);

	*should_complete = true;

	return 1;
}

/* Send hash command to the engine */
static int safexcel_ahash_send_req(struct crypto_async_request *async, int ring,
				   struct safexcel_request *request,
				   int *commands, int *results)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct safexcel_command_desc *cdesc, *first_cdesc = NULL;
	struct safexcel_result_desc *rdesc;
	struct scatterlist *sg;
	int i, queued, len, cache_len, extra, n_cdesc = 0, ret = 0;

	queued = len = req->len - req->processed;
	if (queued <= crypto_ahash_blocksize(ahash))
		cache_len = queued;
	else
		cache_len = queued - areq->nbytes;

	if (!req->last_req) {
		/* If this is not the last request and the queued data does not
		 * fit into full blocks, cache it for the next send() call.
		 */
		extra = queued & (crypto_ahash_blocksize(ahash) - 1);
		if (!extra)
			/* If this is not the last request and the queued data
			 * is a multiple of a block, cache the last one for now.
			 */
			extra = crypto_ahash_blocksize(ahash);

		if (extra) {
			sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
					   req->cache_next, extra,
					   areq->nbytes - extra);

			queued -= extra;
			len -= extra;

			if (!queued) {
				*commands = 0;
				*results = 0;
				return 0;
			}
		}
	}

	spin_lock_bh(&priv->ring[ring].egress_lock);

	/* Add a command descriptor for the cached data, if any */
	if (cache_len) {
		ctx->base.cache = kzalloc(cache_len, EIP197_GFP_FLAGS(*async));
		if (!ctx->base.cache) {
			ret = -ENOMEM;
			goto unlock;
		}
		memcpy(ctx->base.cache, req->cache, cache_len);
		ctx->base.cache_dma = dma_map_single(priv->dev, ctx->base.cache,
						     cache_len, DMA_TO_DEVICE);
		if (dma_mapping_error(priv->dev, ctx->base.cache_dma)) {
			ret = -EINVAL;
			goto free_cache;
		}

		ctx->base.cache_sz = cache_len;
		first_cdesc = safexcel_add_cdesc(priv, ring, 1,
						 (cache_len == len),
						 ctx->base.cache_dma,
						 cache_len, len,
						 ctx->base.ctxr_dma);
		if (IS_ERR(first_cdesc)) {
			ret = PTR_ERR(first_cdesc);
			goto unmap_cache;
		}
		n_cdesc++;

		queued -= cache_len;
		if (!queued)
			goto send_command;
	}

	/* Now handle the current ahash request buffer(s) */
	req->nents = dma_map_sg(priv->dev, areq->src,
				sg_nents_for_len(areq->src, areq->nbytes),
				DMA_TO_DEVICE);
	if (!req->nents) {
		ret = -ENOMEM;
		goto cdesc_rollback;
	}

	for_each_sg(areq->src, sg, req->nents, i) {
		int sglen = sg_dma_len(sg);

		/* Do not overflow the request */
		if (queued - sglen < 0)
			sglen = queued;

		cdesc = safexcel_add_cdesc(priv, ring, !n_cdesc,
					   !(queued - sglen), sg_dma_address(sg),
					   sglen, len, ctx->base.ctxr_dma);

		if (IS_ERR(cdesc)) {
			ret = PTR_ERR(cdesc);
			goto cdesc_rollback;
		}
		n_cdesc++;

		if (n_cdesc == 1)
			first_cdesc = cdesc;

		queued -= sglen;
		if (!queued)
			break;
	}

send_command:
	/* Setup the context options */
	safexcel_context_control(ctx, req, first_cdesc, req->state_sz,
				 crypto_ahash_blocksize(ahash));

	/* Add the token */
	safexcel_hash_token(first_cdesc, len, req->state_sz);

	req->result_dma = dma_map_single(priv->dev, req->state,
					      req->state_sz, DMA_FROM_DEVICE);
	if (dma_mapping_error(priv->dev, req->result_dma)) {
		ret = -EINVAL;
		goto cdesc_rollback;
	}

	/* Add a result descriptor */
	rdesc = safexcel_add_rdesc(priv, ring, 1, 1, req->result_dma,
				   req->state_sz);
	if (IS_ERR(rdesc)) {
		ret = PTR_ERR(rdesc);
		goto rdesc_rollback;
	}

	request->req = &areq->base;

	list_add_tail(&request->list, &priv->ring[ring].list);

	/* update the ring request count */
	priv->ring[ring].egress_cnt++;

	spin_unlock_bh(&priv->ring[ring].egress_lock);

	req->processed += len;

	*commands = n_cdesc;
	*results = 1;
	return 0;

rdesc_rollback:
	dma_unmap_single(priv->dev, req->result_dma, req->state_sz,
			 DMA_FROM_DEVICE);
	req->result_dma = 0;

cdesc_rollback:
	if (req->nents)
		dma_unmap_sg(priv->dev, areq->src, req->nents, DMA_TO_DEVICE);

	for (i = 0; i < n_cdesc; i++)
		safexcel_ring_rollback_wptr(priv, &priv->ring[ring].cdr);
unmap_cache:
	if (ctx->base.cache_dma) {
		dma_unmap_single(priv->dev, ctx->base.cache_dma,
				 ctx->base.cache_sz, DMA_TO_DEVICE);
		ctx->base.cache_sz = 0;
	}
free_cache:
	kfree(ctx->base.cache);
	ctx->base.cache = NULL;

unlock:
	spin_unlock_bh(&priv->ring[ring].egress_lock);
	return ret;
}

/* Check if the request needs invalidation (context was changed) */
static inline bool safexcel_ahash_needs_inv_get(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	unsigned int state_w_sz = req->state_sz / sizeof(u32);
	int i;

	for (i = 0; i < state_w_sz; i++)
		if (ctx->base.ctxr->data[i] != cpu_to_le32(req->state[i]))
			return true;

	if (ctx->base.ctxr->data[state_w_sz] !=
	    cpu_to_le32(req->processed / crypto_ahash_blocksize(ahash)))
		return true;

	return false;
}

/* Handle a hash invalidation descriptor */
static int safexcel_handle_inv_result(struct safexcel_crypto_priv *priv,
				      int ring,
				      struct crypto_async_request *async,
				      bool *should_complete, int *ret)
{
	struct safexcel_result_desc *rdesc;
	struct ahash_request *areq = ahash_request_cast(async);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(ahash);

	*ret = 0;

	spin_lock_bh(&priv->ring[ring].egress_lock);
	rdesc = safexcel_ring_next_rptr(priv, &priv->ring[ring].rdr);
	if (IS_ERR(rdesc)) {
		dev_err(priv->dev,
			"hash: invalidate: could not retrieve the result descriptor\n");
		*ret = PTR_ERR(rdesc);
	} else if (rdesc->result_data.error_code) {
		dev_err(priv->dev,
			"hash: invalidate: result descriptor error (%d)\n",
			rdesc->result_data.error_code);
		*ret = -EINVAL;
	}

	safexcel_complete(priv, ring);
	spin_unlock_bh(&priv->ring[ring].egress_lock);

	if (ctx->base.exit_inv) {
		dma_pool_free(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);

		*should_complete = true;

		return 1;
	}

	ctx->base.ring = safexcel_select_ring(priv);
	ring = ctx->base.ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	ahash_enqueue_request(&priv->ring[ring].queue, areq);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	*should_complete = false;

	return 1;
}

static int safexcel_handle_result(struct safexcel_crypto_priv *priv, int ring,
				  struct crypto_async_request *async,
				  bool *should_complete, int *ret)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	int err;

	if (req->needs_inv) {
		req->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async,
						 should_complete, ret);
	} else {
		err = safexcel_handle_req_result(priv, ring, async,
						 should_complete, ret);
	}

	return err;
}

/* Send hash invalidation command to the engine */
static int safexcel_ahash_send_inv(struct crypto_async_request *async,
				   int ring, struct safexcel_request *request,
				   int *commands, int *results)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	int ret;

	ret = safexcel_invalidate_cache(async, ctx->priv,
					ctx->base.ctxr_dma, ring, request);
	if (unlikely(ret))
		return ret;

	*commands = 1;
	*results = 1;

	return 0;
}

static int safexcel_ahash_send(struct crypto_async_request *async,
			       int ring, struct safexcel_request *request,
			       int *commands, int *results)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	int ret;

	if (req->needs_inv)
		ret = safexcel_ahash_send_inv(async, ring, request,
					      commands, results);
	else
		ret = safexcel_ahash_send_req(async, ring, request,
					      commands, results);
	return ret;
}

/* Upon context exit, send invalidation command */
static int safexcel_ahash_exit_inv(struct crypto_tfm *tfm)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_crypto_priv *priv = ctx->priv;
	AHASH_REQUEST_ON_STACK(req, __crypto_ahash_cast(tfm));
	struct safexcel_ahash_req *rctx = ahash_request_ctx(req);
	struct safexcel_inv_result result = {};
	int ring = ctx->base.ring;

	/* create invalidation request */
	init_completion(&result.completion);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   safexcel_inv_complete, &result);

	ahash_request_set_tfm(req, __crypto_ahash_cast(tfm));
	ctx = crypto_tfm_ctx(req->base.tfm);
	ctx->base.exit_inv = true;
	rctx->needs_inv = true;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	ahash_enqueue_request(&priv->ring[ring].queue, req);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	wait_for_completion(&result.completion);

	if (result.error) {
		dev_warn(priv->dev, "hash: completion error (%d)\n",
			 result.error);
		return result.error;
	}

	return 0;
}

/* safexcel_ahash_cache: cache data until at least one request can be sent to
 * the engine, aka. when there is at least 1 block size in the pipe.
 */
static int safexcel_ahash_cache(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	int queued, cache_len;

	/* cache_len: everyting accepted by the driver but not sent yet,
	 * tot sz handled by update() - last req sz - tot sz handled by send()
	 */
	cache_len = req->len - areq->nbytes - req->processed;
	/* queued: everything accepted by the driver which will be handled by
	 * the next send() calls.
	 * tot sz handled by update() - tot sz handled by send()
	 */
	queued = req->len - req->processed;

	/*
	 * In case there isn't enough bytes to proceed (less than a
	 * block size), cache the data until we have enough.
	 */
	if (cache_len + areq->nbytes <= crypto_ahash_blocksize(ahash)) {
		sg_pcopy_to_buffer(areq->src, sg_nents(areq->src),
				   req->cache + cache_len,
				   areq->nbytes, 0);
		return areq->nbytes;
	}

	/* We couldn't cache all the data */
	return -E2BIG;
}

static int safexcel_ahash_enqueue(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ret, ring;

	req->needs_inv = false;

	/*
	 * Check if the context exists, if yes:
	 *	- EIP197: check if it needs to be invalidated
	 *	- EIP97: Nothing to be done
	 * If context not exists, allocate it (for both EIP97 & EIP197)
	 * and set the send routine for the new allocated context.
	 * If it's EIP97 with existing context, the send routine is already set.
	 */
	if (ctx->base.ctxr) {
		if (priv->eip_type == EIP197 &&
		    !ctx->base.needs_inv && req->processed &&
		    ctx->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED)
			/* We're still setting needs_inv here, even though it is
			 * cleared right away, because the needs_inv flag can be
			 * set in other functions and we want to keep the same
			 * logic.
			 */
			ctx->base.needs_inv = safexcel_ahash_needs_inv_get(areq);

		if (ctx->base.needs_inv) {
			ctx->base.needs_inv = false;
			req->needs_inv = true;
		}
	} else {
		ctx->base.ring = safexcel_select_ring(priv);
		ctx->base.ctxr = dma_pool_zalloc(priv->context_pool,
						 EIP197_GFP_FLAGS(areq->base),
						 &ctx->base.ctxr_dma);
		if (!ctx->base.ctxr)
			return -ENOMEM;
	}

	ring = ctx->base.ring;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	ret = ahash_enqueue_request(&priv->ring[ring].queue, areq);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	return ret;
}

static int safexcel_ahash_update(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);

	/* If the request is 0 length, do nothing */
	if (!areq->nbytes)
		return 0;

	req->len += areq->nbytes;

	safexcel_ahash_cache(areq);

	/*
	 * We're not doing partial updates when performing an hmac request.
	 * Everything will be handled by the final() call.
	 */
	if (ctx->digest == CONTEXT_CONTROL_DIGEST_HMAC)
		return 0;

	if (req->hmac)
		return safexcel_ahash_enqueue(areq);

	if (!req->last_req &&
	    req->len - req->processed > crypto_ahash_blocksize(ahash))
		return safexcel_ahash_enqueue(areq);

	return 0;
}

static int safexcel_ahash_final(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));

	req->last_req = true;
	req->finish = true;

	/* If we have an overall 0 length request */
	if (!(req->len + areq->nbytes)) {
		if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA1)
			memcpy(areq->result, sha1_zero_digest,
			       SHA1_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA224)
			memcpy(areq->result, sha224_zero_digest,
			       SHA224_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA256)
			memcpy(areq->result, sha256_zero_digest,
			       SHA256_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5)
			memcpy(areq->result, md5_zero_digest,
			       MD5_DIGEST_SIZE);

		return 0;
	}

	return safexcel_ahash_enqueue(areq);
}

static int safexcel_ahash_finup(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	req->last_req = true;
	req->finish = true;

	safexcel_ahash_update(areq);
	return safexcel_ahash_final(areq);
}

static int safexcel_ahash_export(struct ahash_request *areq, void *out)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_export_state *export = out;

	export->len = req->len;
	export->processed = req->processed;

	memcpy(export->state, req->state, req->state_sz);
	memcpy(export->cache, req->cache, crypto_ahash_blocksize(ahash));

	return 0;
}

static int safexcel_ahash_import(struct ahash_request *areq, const void *in)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	const struct safexcel_ahash_export_state *export = in;
	int ret;

	ret = crypto_ahash_init(areq);
	if (ret)
		return ret;

	req->len = export->len;
	req->processed = export->processed;

	memcpy(req->cache, export->cache, crypto_ahash_blocksize(ahash));
	memcpy(req->state, export->state, req->state_sz);

	return 0;
}

static int safexcel_ahash_cra_init(struct crypto_tfm *tfm)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_alg_template *tmpl =
		container_of(__crypto_ahash_alg(tfm->__crt_alg),
			     struct safexcel_alg_template, alg.ahash);

	ctx->priv = tmpl->priv;
	ctx->base.send = safexcel_ahash_send;
	ctx->base.handle_result = safexcel_handle_result;

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct safexcel_ahash_req));
	return 0;
}

static int safexcel_sha1_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = SHA1_H0;
	req->state[1] = SHA1_H1;
	req->state[2] = SHA1_H2;
	req->state[3] = SHA1_H3;
	req->state[4] = SHA1_H4;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA1;
	ctx->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA1_DIGEST_SIZE;

	return 0;
}

static int safexcel_sha1_digest(struct ahash_request *areq)
{
	int ret = safexcel_sha1_init(areq);

	if (ret)
		return ret;

	return safexcel_ahash_finup(areq);
}

static void safexcel_ahash_cra_exit(struct crypto_tfm *tfm)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ret;

	/* context not allocated, skip invalidation */
	if (!ctx->base.ctxr)
		return;

	/*
	 * EIP197 has internal cache which needs to be invalidated
	 * when the context is closed.
	 * dma_pool_free will be called in the invalidation result
	 * handler (different context).
	 * EIP97 doesn't have internal cache, so no need to invalidate
	 * it and we can just release the dma pool.
	 */
	if (priv->eip_type == EIP197) {
		ret = safexcel_ahash_exit_inv(tfm);
		if (ret)
			dev_warn(priv->dev, "hash: invalidation error %d\n", ret);
	} else {
		dma_pool_free(priv->context_pool, ctx->base.ctxr,
			      ctx->base.ctxr_dma);
	}
}

struct safexcel_alg_template safexcel_alg_sha1 = {
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.alg.ahash = {
		.init = safexcel_sha1_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha1_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = {
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = sizeof(struct safexcel_ahash_export_state),
			.base = {
				.cra_name = "sha1",
				.cra_driver_name = "safexcel-sha1",
				.cra_priority = 300,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = sizeof(struct safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_exit = safexcel_ahash_cra_exit,
				.cra_module = THIS_MODULE,
			},
		},
	},
};

static int safexcel_hmac_sha1_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));

	safexcel_sha1_init(areq);
	ctx->digest = CONTEXT_CONTROL_DIGEST_HMAC;
	return 0;
}

static int safexcel_hmac_sha1_digest(struct ahash_request *areq)
{
	int ret = safexcel_hmac_sha1_init(areq);

	if (ret)
		return ret;

	return safexcel_ahash_finup(areq);
}

struct safexcel_ahash_result {
	struct completion completion;
	int error;
};

static void safexcel_ahash_complete(struct crypto_async_request *req, int error)
{
	struct safexcel_ahash_result *result = req->data;

	if (error == -EINPROGRESS)
		return;

	result->error = error;
	complete(&result->completion);
}

static int safexcel_hmac_init_pad(struct ahash_request *areq,
				  unsigned int blocksize, const u8 *key,
				  unsigned int keylen, u8 *ipad, u8 *opad)
{
	struct safexcel_ahash_result result;
	struct scatterlist sg;
	int ret, i;
	u8 *keydup;

	if (keylen <= blocksize) {
		memcpy(ipad, key, keylen);
	} else {
		keydup = kmemdup(key, keylen, GFP_KERNEL);
		if (!keydup)
			return -ENOMEM;

		ahash_request_set_callback(areq, CRYPTO_TFM_REQ_MAY_BACKLOG,
					   safexcel_ahash_complete, &result);
		sg_init_one(&sg, keydup, keylen);
		ahash_request_set_crypt(areq, &sg, ipad, keylen);
		init_completion(&result.completion);

		ret = crypto_ahash_digest(areq);
		if (ret == -EINPROGRESS) {
			wait_for_completion_interruptible(&result.completion);
			ret = result.error;
		}

		/* Avoid leaking */
		memzero_explicit(keydup, keylen);
		kfree(keydup);

		if (ret)
			return ret;

		keylen = crypto_ahash_digestsize(crypto_ahash_reqtfm(areq));
	}

	memset(ipad + keylen, 0, blocksize - keylen);
	memcpy(opad, ipad, blocksize);

	for (i = 0; i < blocksize; i++) {
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	return 0;
}

static int safexcel_hmac_init_iv(struct ahash_request *areq,
				 unsigned int blocksize, u8 *pad, void *state)
{
	struct safexcel_ahash_result result;
	struct safexcel_ahash_req *req;
	struct scatterlist sg;
	int ret;

	ahash_request_set_callback(areq, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   safexcel_ahash_complete, &result);
	sg_init_one(&sg, pad, blocksize);
	ahash_request_set_crypt(areq, &sg, pad, blocksize);
	init_completion(&result.completion);

	ret = crypto_ahash_init(areq);
	if (ret)
		return ret;

	req = ahash_request_ctx(areq);
	req->hmac = true;
	req->last_req = true;

	ret = crypto_ahash_update(areq);
	if (ret && ret != -EINPROGRESS && ret != -EBUSY)
		return ret;

	wait_for_completion_interruptible(&result.completion);
	if (result.error)
		return result.error;

	return crypto_ahash_export(areq, state);
}

static int safexcel_hmac_setkey(const char *alg, const u8 *key,
				unsigned int keylen, void *istate, void *ostate)
{
	struct ahash_request *areq;
	struct crypto_ahash *tfm;
	unsigned int blocksize;
	u8 *ipad, *opad;
	int ret;

	tfm = crypto_alloc_ahash(alg, CRYPTO_ALG_TYPE_AHASH,
				 CRYPTO_ALG_TYPE_AHASH_MASK);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	areq = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!areq) {
		ret = -ENOMEM;
		goto free_ahash;
	}

	crypto_ahash_clear_flags(tfm, ~0);
	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	ipad = kzalloc(2 * blocksize, GFP_KERNEL);
	if (!ipad) {
		ret = -ENOMEM;
		goto free_request;
	}

	opad = ipad + blocksize;

	ret = safexcel_hmac_init_pad(areq, blocksize, key, keylen, ipad, opad);
	if (ret)
		goto free_ipad;

	ret = safexcel_hmac_init_iv(areq, blocksize, ipad, istate);
	if (ret)
		goto free_ipad;

	ret = safexcel_hmac_init_iv(areq, blocksize, opad, ostate);

free_ipad:
	kfree(ipad);
free_request:
	ahash_request_free(areq);
free_ahash:
	crypto_free_ahash(tfm);

	return ret;
}

static int safexcel_hmac_sha1_setkey(struct crypto_ahash *tfm, const u8 *key,
				     unsigned int keylen)
{
	struct safexcel_ahash_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct safexcel_crypto_priv *priv = ctx->priv;
	struct safexcel_ahash_export_state istate, ostate;
	int ret, i;

	ret = safexcel_hmac_setkey("safexcel-sha1", key, keylen, &istate, &ostate);
	if (ret)
		return ret;

	if (priv->eip_type == EIP197 && ctx->base.ctxr) {
		for (i = 0; i < SHA1_DIGEST_SIZE / sizeof(u32); i++) {
			if (ctx->ipad[i] != le32_to_cpu(istate.state[i]) ||
			    ctx->opad[i] != le32_to_cpu(ostate.state[i])) {
				ctx->base.needs_inv = true;
				break;
			}
		}
	}

	memcpy(ctx->ipad, &istate.state, SHA1_DIGEST_SIZE);
	memcpy(ctx->opad, &ostate.state, SHA1_DIGEST_SIZE);

	return 0;
}

struct safexcel_alg_template safexcel_alg_hmac_sha1 = {
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.alg.ahash = {
		.init = safexcel_hmac_sha1_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_hmac_sha1_digest,
		.setkey = safexcel_hmac_sha1_setkey,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = {
			.digestsize = SHA1_DIGEST_SIZE,
			.statesize = sizeof(struct safexcel_ahash_export_state),
			.base = {
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "safexcel-hmac-sha1",
				.cra_priority = 300,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = sizeof(struct safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_exit = safexcel_ahash_cra_exit,
				.cra_module = THIS_MODULE,
			},
		},
	},
};

static int safexcel_sha256_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = SHA256_H0;
	req->state[1] = SHA256_H1;
	req->state[2] = SHA256_H2;
	req->state[3] = SHA256_H3;
	req->state[4] = SHA256_H4;
	req->state[5] = SHA256_H5;
	req->state[6] = SHA256_H6;
	req->state[7] = SHA256_H7;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA256;
	ctx->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;

	return 0;
}

static int safexcel_sha256_digest(struct ahash_request *areq)
{
	int ret = safexcel_sha256_init(areq);

	if (ret)
		return ret;

	return safexcel_ahash_finup(areq);
}

struct safexcel_alg_template safexcel_alg_sha256 = {
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.alg.ahash = {
		.init = safexcel_sha256_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha256_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = {
			.digestsize = SHA256_DIGEST_SIZE,
			.statesize = sizeof(struct safexcel_ahash_export_state),
			.base = {
				.cra_name = "sha256",
				.cra_driver_name = "safexcel-sha256",
				.cra_priority = 300,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = sizeof(struct safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_exit = safexcel_ahash_cra_exit,
				.cra_module = THIS_MODULE,
			},
		},
	},
};

static int safexcel_sha224_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = SHA224_H0;
	req->state[1] = SHA224_H1;
	req->state[2] = SHA224_H2;
	req->state[3] = SHA224_H3;
	req->state[4] = SHA224_H4;
	req->state[5] = SHA224_H5;
	req->state[6] = SHA224_H6;
	req->state[7] = SHA224_H7;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA224;
	ctx->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;

	return 0;
}

static int safexcel_sha224_digest(struct ahash_request *areq)
{
	int ret = safexcel_sha224_init(areq);

	if (ret)
		return ret;

	return safexcel_ahash_finup(areq);
}

struct safexcel_alg_template safexcel_alg_sha224 = {
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.alg.ahash = {
		.init = safexcel_sha224_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_sha224_digest,
		.export = safexcel_ahash_export,
		.import = safexcel_ahash_import,
		.halg = {
			.digestsize = SHA224_DIGEST_SIZE,
			.statesize = sizeof(struct safexcel_ahash_export_state),
			.base = {
				.cra_name = "sha224",
				.cra_driver_name = "safexcel-sha224",
				.cra_priority = 300,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = SHA224_BLOCK_SIZE,
				.cra_ctxsize = sizeof(struct safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_exit = safexcel_ahash_cra_exit,
				.cra_module = THIS_MODULE,
			},
		},
	},
};

static int safexcel_md5_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = MD5_H0;
	req->state[1] = MD5_H1;
	req->state[2] = MD5_H2;
	req->state[3] = MD5_H3;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_MD5;
	ctx->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = MD5_DIGEST_SIZE;

	return 0;
}

static int safexcel_md5_digest(struct ahash_request *areq)
{
	int ret = safexcel_md5_init(areq);

	if (ret)
		return ret;

	return safexcel_ahash_finup(areq);
}

static int safexcel_md5_export(struct ahash_request *areq, void *out)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(areq);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct md5_state *out_state = out;
	int len = req->len;
	int cache_len = do_div(len, crypto_ahash_blocksize(ahash));

	out_state->byte_count = req->len;
	memcpy(out_state->hash, req->state, req->state_sz);
	memset(out_state->block, 0, crypto_ahash_blocksize(ahash));
	memcpy(out_state->block, req->cache, cache_len);

	return 0;
}

static int safexcel_md5_import(struct ahash_request *areq, const void *in)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	const struct md5_state *in_state = in;

	memset(req, 0, sizeof(*req));

	req->len = in_state->byte_count;
	memcpy(req->cache, in_state->block, in_state->byte_count);
	memcpy(req->state, in_state->hash, req->state_sz);

	return 0;
}

struct safexcel_alg_template safexcel_alg_md5 = {
	.type = SAFEXCEL_ALG_TYPE_AHASH,
	.alg.ahash = {
		.init = safexcel_md5_init,
		.update = safexcel_ahash_update,
		.final = safexcel_ahash_final,
		.finup = safexcel_ahash_finup,
		.digest = safexcel_md5_digest,
		.export = safexcel_md5_export,
		.import = safexcel_md5_import,
		.halg = {
			.digestsize = MD5_DIGEST_SIZE,
			.statesize = sizeof(struct md5_state),
			.base = {
				.cra_name = "md5",
				.cra_driver_name = "safexcel-md5",
				.cra_priority = 300,
				.cra_flags = CRYPTO_ALG_ASYNC |
					     CRYPTO_ALG_KERN_DRIVER_ONLY,
				.cra_blocksize = MD5_HMAC_BLOCK_SIZE,
				.cra_ctxsize = sizeof(struct safexcel_ahash_ctx),
				.cra_init = safexcel_ahash_cra_init,
				.cra_exit = safexcel_ahash_cra_exit,
				.cra_module = THIS_MODULE,
			},
		},
	},
};
