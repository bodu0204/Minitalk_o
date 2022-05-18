/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:32:50 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:38:15 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"sha256_bonus.h"

uint32_t	rbit(uint32_t x, uint32_t n)
{
	n %= 32;
	return ((x >> n) | (x << (32 - n)));
}

void	b32tob8(uint32_t *src, uint8_t *dst)
{
	dst[0] = (*src >> 24);
	dst[1] = (*src >> 16) & 0xff;
	dst[2] = (*src >> 8) & 0xff;
	dst[3] = *src & 0xff;
	return ;
}

void	b8tob32(uint8_t *src, uint32_t *dst)
{
	*dst = (((uint32_t)src[0]) << 24) | (((uint32_t)src[1]) << 16) \
	 | (((uint32_t)src[2]) << 8) | ((uint32_t)src[3]);
	return ;
}
