/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:30:59 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 20:12:37 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

extern t_info	g_;

void	readin(size_t	len, t_str	*r)
{
	char	s[BUFSIZE];
	ssize_t	i;

	i = read(STDIN_FILENO, s, BUFSIZE);
	if (i < 0)
		msg_exit("read error\n");
	if (s[i - 1] == '\n')
	{
		r->s = malloc(len + i);
		if (!r->s)
			msg_exit("malloc error\n");
		r->l = len + i;
	}
	else
		readin(len + i, r);
	ft_memcpy(r->s + len, s, i);
	return ;
}

void	treat_to_send(t_str	*s)
{
	ft_memcpy(s->s + SHA256LEN, &s->l, sizeof(size_t));
	sha256(s->s + SHA256LEN, s->l - SHA256LEN, (uint8_t *)(s->s));
	return ;
}

int	isnt_correct_num(char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
	{
		if (!ft_isdigit(s[l]))
			return (1);
		l++;
	}
	if (l > 10)
		return (1);
	else if (l < 10)
		return (0);
	return (ft_memcmp(s, "2147483647", 10) > 0);
}

int	speed(int flag)
{
	static int	base = STARTSPEED;
	static int	error = 0;

	if (flag == SUCCESS)
	{
		if (error > 1)
		{
			base = STARTSPEED;
			connect();
		}
		error = 0;
	}
	else if (flag == FAIL)
		error++;
	else if (flag == CONNECT)
	{
		error = 0;
		base <<= 1;
		if (base > 100000)
			return (-1);
		return (base);
	}
	if (error > 5)
		return (-1);
	return (base << ((error / 2) + 1));
}

void	msg_exit(char *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
	exit (1);
}
