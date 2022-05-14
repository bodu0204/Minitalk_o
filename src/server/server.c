#include "server.h"
#include <stdio.h>
void setact(struct sigaction	*a);
void	reserror(struct sigaction	*opn);

t_cli	g_cli = {0};

int main (void)
{
	struct sigaction	opn;

	printf("PID:%d\n", getpid());
	setact(&opn);
	sigaction(SIGUSR1, &opn, NULL);
	sigaction(SIGUSR2, &opn, NULL);
	while(1)
	{
		while (g_cli.request && !g_cli.is_sig)
		{
			reserror(&opn);
			sleep(1);
		}
		if(!g_cli.request)
			pause();
		while(g_cli.is_sig)
		{
			g_cli.is_sig = 0;
			usleep(100000);
		}
	}
	return (0);
}

void setact(struct sigaction	*a)
{
	sigemptyset(&(a->sa_mask));
	a->sa_flags = SA_SIGINFO;
	a->sa_sigaction = act;
	return ;
}

void	reserror(struct sigaction	*opn)
{
	t_req	*c;
	pid_t	i;

	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
	g_cli.is_sig = 0;
	c = g_cli.request;
	if (!c)
		return ;
	g_cli.request = c->next;
	i = c->pid;
	free(c->content);
	free(c);
	sigaction(SIGUSR1, opn, NULL);
	sigaction(SIGUSR2, opn, NULL);
	kill(SIGUSR2, i);
	return ;
}
