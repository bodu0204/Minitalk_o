/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_done_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:31:58 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:37:05 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"sha256_bonus.h"
void	sha256_done1(t_sha *ctx, uint8_t *hdst);

void	sha256_done(t_sha *ctx, uint8_t *hdst)
{
	size_t	i;

	ctx->buf[ctx->len] = 0x80;
	i = ctx->len + 1;
	while (i < 64)
	{
		ctx->buf[i] = 0x00;
		i++;
	}
	if (ctx->len > 55)
	{
		hash(ctx);
		i = 0;
		while (i < 64)
		{
			ctx->buf[i] = 0x00;
			i++;
		}
	}
	sha256_done1(ctx, hdst);
}

void	sha256_done1(t_sha *ctx, uint8_t *hdst)
{
	size_t	i;

	b32tob8(ctx->bits + 1, ctx->buf + 60);
	b32tob8(ctx->bits, ctx->buf + 56);
	hash(ctx);
	i = 0;
	while (i < 8)
	{
		b32tob8(ctx->hash + i, hdst + (i * 4));
		i++;
	}
}
