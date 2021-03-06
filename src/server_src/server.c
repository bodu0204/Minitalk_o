/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:31:31 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/19 08:31:32 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
void	setact(struct sigaction	*a);
void	reserror(void);

t_cli	g_cli = {0};

int	main(void)
{
	struct sigaction	opn;

	g_cli.me = getpid();
	setact(&opn);
	sigaction(SIGUSR1, &opn, NULL);
	sigaction(SIGUSR2, &opn, NULL);
	ft_printf("PID:%d\n", g_cli.me);
	while (1)
	{
		while (g_cli.request && !g_cli.is_sig)
		{
			reserror();
			sleep(1);
		}
		if (!g_cli.request)
			pause();
		while (g_cli.is_sig)
		{
			g_cli.is_sig = 0;
			usleep(10000);
		}
	}
	return (0);
}

void	setact(struct sigaction	*a)
{
	sigemptyset(&(a->sa_mask));
	a->sa_flags = SA_SIGINFO;
	a->sa_sigaction = act;
	return ;
}

void	reserror(void)
{
	t_req	*c;
	pid_t	i;

	g_cli.is_sig = -8;
	c = g_cli.request;
	if (!c)
		return ;
	g_cli.request = c->next;
	i = c->pid;
	free(c->content);
	free(c);
	g_cli.is_sig = 0;
	kill(i, SIGUSR2);
	return ;
}
