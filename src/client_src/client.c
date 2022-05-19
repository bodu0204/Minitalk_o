/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 19:52:36 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 20:03:59 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_info	g_;

void	act(int signo)
{
	if (signo == SIGUSR1)
		g_.result = SUCCESS;
	else if (signo == SIGUSR2)
		g_.result = FAIL;
	return ;
}

int	main(int argc, char *argv[])
{
	t_str	s;

	if (argc != 3 || isnt_correct_num(argv[1]))
		msg_exit("not valid args\n");
	g_.result = NOSIG;
	g_.pid = atoi(argv[1]);
	signal(SIGUSR1, act);
	signal(SIGUSR2, act);
	connect();
	s.l = HEADER_SIZE + ft_strlen(argv[2]);
	s.s = malloc(s.l);
	if (!s.s)
		msg_exit("malloc error\n");
	ft_memcpy(s.s + HEADER_SIZE, argv[2], s.l - HEADER_SIZE);
	treat_to_send(&s);
	sending(&s);
	return (0);
}

void	connect(void)
{
	int		spd;
	char	blank[BUFSIZE];
	size_t	i;

	g_.result = NOSIG;
	ft_bzero(blank, BUFSIZE);
	i = HEADER_SIZE;
	ft_memcpy(blank + SHA256LEN, &i, sizeof(size_t));
	sha256(blank + SHA256LEN, sizeof(size_t), (uint8_t *)blank);
	while (g_.result != SUCCESS)
	{
		g_.result = NOSIG;
		spd = speed(CONNECT);
		if (spd < 0)
			msg_exit("connect error\n");
		send(blank, HEADER_SIZE, spd);
		if (g_.result == NOSIG)
			sleep(4);
		if (g_.result == NOSIG)
			msg_exit("connect error\n");
	}
	return ;
}

void	sending(t_str	*s)
{
	int	spd;

	g_.result = NOSIG;
	while (g_.result != SUCCESS)
	{
		g_.result = NOSIG;
		spd = speed(GET);
		if (spd < 0)
		{
			free(s->s);
			msg_exit("sending error\n");
		}
		send(s->s, s->l, spd);
		if (g_.result == NOSIG)
			sleep(4);
		if (g_.result == SUCCESS)
			speed(SUCCESS);
		else
			speed(FAIL);
	}
	free(s->s);
	ft_bzero(s, sizeof(t_str));
	return ;
}

void	send(char *s, size_t l, int	spd)
{
	uint8_t	b;
	size_t	B;

	b = 1U;
	B = 0;
	while (B < l && g_.result != SUCCESS)
	{
		usleep(spd);
		if (s[B] & b)
			kill(g_.pid, SIGUSR1);
		else
			kill(g_.pid, SIGUSR2);
		b <<= 1;
		if (b == 0)
		{
			b = 1U;
			B++;
		}
	}
	return ;
}

/*
int	main(int argc, char *argv[])
{
	t_str	s;

	if (argc != 2 || isnt_correct_num(argv[1]))
		msg_exit("not valid PID\n");
	g_.result = NOSIG;
	g_.pid = atoi(argv[1]);
	signal(SIGUSR1, act);
	signal(SIGUSR2, act);
	connect();
	while (1)
	{
		readin(HEADER_SIZE, &s);
		treat_to_send(&s);
		sending(&s);
	}
	return (0);
}
 */
