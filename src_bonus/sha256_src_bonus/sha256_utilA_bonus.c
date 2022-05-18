/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_utilA_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:32:17 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:37:34 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"sha256_bonus.h"

uint32_t	Ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t	Ma(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	S0(uint32_t x)
{
	return (rbit(x, 2) ^ rbit(x, 13) ^ rbit(x, 22));
}

uint32_t	S1(uint32_t x)
{
	return (rbit(x, 6) ^ rbit(x, 11) ^ rbit(x, 25));
}

uint32_t	G0(uint32_t x)
{
	return (rbit(x, 7) ^ rbit(x, 18) ^ (x >> 3));
}
