/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:32:03 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:37:15 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"sha256_bonus.h"
void	hash1(t_sha *ctx, uint32_t *hs);

void	sha256_hash(t_sha *ctx, const void *data, size_t len)
{
	const uint8_t	*bytes;
	size_t			i;

	ctx->bits[0] = (len * 8) / 0x100000000;
	ctx->bits[1] = (len * 8) % 0x100000000;
	bytes = (const uint8_t *)data;
	i = 0;
	while (i < len)
	{
		ctx->buf[ctx->len] = bytes[i];
		ctx->len++;
		i++;
		if (ctx->len == sizeof(ctx->buf))
		{
			hash(ctx);
			ctx->len = 0;
		}
	}
}

void	hash(t_sha *ctx)
{
	uint32_t	hs[8];
	uint32_t	t[2];
	size_t		i;

	ft_memcpy(hs, ctx->hash, sizeof(uint32_t) * 8);
	i = 0;
	while (i < 64)
	{
		ft_memmove(ctx->W, ctx->W + 1, sizeof(uint32_t) * 16);
		if (i < 16)
			b8tob32(ctx->buf + (i * 4), ctx->W + 16);
		else
			ctx->W[16] = G1(ctx->W[14]) + ctx->W[9] + G0(ctx->W[1]) + ctx->W[0];
		t[0] = hs[7] + S1(hs[4]) + Ch(hs[4], hs[5], hs[6]) \
		+ ctx->K[i] + ctx->W[16];
		t[1] = S0(hs[0]) + Ma(hs[0], hs[1], hs[2]);
		ft_memmove(hs + 1, hs, sizeof(uint32_t) * 7);
		hs[4] += t[0];
		hs[0] = t[0] + t[1];
		i++;
	}
	hash1(ctx, hs);
}

void	hash1(t_sha *ctx, uint32_t *hs)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		ctx->hash[i] += hs[i];
		i++;
	}
}
