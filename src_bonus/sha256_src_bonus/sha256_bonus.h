/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:32:42 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/26 06:39:08 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_BONUS_H
# define SHA256_BONUS_H
# include <stddef.h>
# include <stdint.h>
# define SHA256_SIZE_BYTES 32

enum
{
	_a,
	_b,
	_c,
	_d,
	_e,
	_f,
	_g,
	_h,
};

typedef struct s_sha256_context
{
	uint8_t		buf[64];
	uint32_t	hash[8];
	uint32_t	bits[2];
	size_t		len;
	uint32_t	W[17];
	uint32_t	K[64];
}	t_sha;

void		sha256_init(t_sha *ctx);
void		sha256_hash(t_sha *ctx, const void *data, size_t len);
void		sha256_done(t_sha *ctx, uint8_t *hash);

void		hash(t_sha *ctx);

uint32_t	rbit(uint32_t	x, uint32_t	n);
void		b32tob8(uint32_t	*src, uint8_t	*dst);
void		b8tob32(uint8_t	*src, uint32_t	*dst);

void		sha256(const void *data, size_t len, uint8_t *hash);

uint32_t	Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t	Ma(uint32_t x, uint32_t y, uint32_t z);
uint32_t	S0(uint32_t x);
uint32_t	S1(uint32_t x);
uint32_t	G0(uint32_t x);
uint32_t	G1(uint32_t x);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
#endif
