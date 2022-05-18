/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_server_util_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:31:45 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:35:59 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

void	more_mem(t_req	*r)
{
	char	*new;
	size_t	l;

	if (r->use + 1 >= r->buf)
	{
		l = r->buf;
		r->buf <<= 1;
		new = ft_calloc(r->buf, sizeof(char));
		if (!new)
			error_exit("malloc error\n");
		ft_memcpy(new, r->content, l);
		free(r->content);
		r->content = new;
	}
	return ;
}

int	check_hash(t_req	*r)
{
	uint8_t	hash[SHA256LEN];

	sha256(r->content + SHA256LEN, r->use - SHA256LEN, hash);
	return (!ft_memcmp(r->content, hash, SHA256LEN));
}
