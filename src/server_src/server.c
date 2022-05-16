#include "server.h"
#include "debug.h"/* test */
#include <stdio.h>
void	setact(struct sigaction	*a);
void	reserror(struct sigaction	*opn);

t_cli	g_cli = {0};

int main (void)
{
	struct sigaction	opn;

	g_cli.me = getpid();
	setact(&opn);
//TEST
	sigaction(SIGUSR1, &opn, NULL);
	sigaction(SIGUSR2, &opn, NULL);
	printf("PID:%d\n", g_cli.me);
//TEST
	while(1)
	{
//TEST
		while (g_cli.request && !g_cli.is_sig)
		{
t_req *j;
j = g_cli.request;
printf("*");
while (j)
{
printf("->%d", j->pid);
j = j->next;
}TEST
			reserror(&opn);/* 何らかな問題あり 線形リストをうまく扱えていない いや、自分のpidがある */
			sleep(1);
		}
		if(!g_cli.request)
{
//TEST
			pause();
}
		while(g_cli.is_sig)
		{
//TEST
			g_cli.is_sig = 0;
			usleep(10000);
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

void	reserror(struct sigaction	*opn)/*  */
{
	t_req	*c;
	pid_t	i;

	(void)opn;/*  */
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
//TESTn("->pid", i)
	return ;
}
