/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:32:35 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:37:56 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"sha256_bonus.h"

void	sha256(const void *data, size_t len, uint8_t *hash)
{
	t_sha	ctx;

	if (!data || !hash)
		return ;
	sha256_init(&ctx);
	sha256_hash(&ctx, data, len);
	sha256_done(&ctx, hash);
	return ;
}

/*
void showhash(uint8_t *hash);
#include <stdio.h>

int main(void)
{
    char *data = "";
    uint8_t hash[32];
    bzero(hash, sizeof(hash));
    sha256(data, strlen(data), hash);
    showhash(hash);
    return (0);
}

void showhash(uint8_t *hash)
{
    for (size_t i = 0; i < 32; i++){
        printf("%02hhx",hash[i]);
    }
    printf("\n");
    return ;
}
 */
