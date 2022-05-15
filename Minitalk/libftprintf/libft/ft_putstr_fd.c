/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 07:04:27 by blyu              #+#    #+#             */
/*   Updated: 2021/11/11 11:14:16 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>

void	ft_putstr_fd(char	*s, int	fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (*(s + i))
		i++;
	write(fd, s, i);
}
