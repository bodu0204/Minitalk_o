#include "server.h"

extern t_cli	g_cli;

void	act(int sig, siginfo_t *info, void *context)
{
	t_req *c;

	g_cli.is_sig++;
	if (g_cli.is_sig != 1 || info->si_pid == g_cli.me)
		return ;
	(void)context;
	c = search_client(info->si_pid);
	if (sig == SIGUSR1)
		c->content[c->use] |= 1U << c->bit;
	c->bit++;
	if (c->bit >= 8)
	{
		c->use++;
		c->bit = 0;
	}
	more_mem(c);
	if (c->use >= HEADER_SIZE)
	{
		if (c->use == *((size_t *)((char *)c->content + SHA256LEN)) && c->bit == 0)
			if (check_hash(c))
				output(c);
	}
}

t_req	*search_client(pid_t	i)
{
	t_req	*r;

	r = g_cli.request;
	while(r)
	{
		if(r->pid == i)
			break ;
		r = r->next;
	}
	if (!r)
		r = mknwereq(i);
	return (r);
}

t_req	*mknwereq(pid_t	i)
{
	t_req	*r;
	t_req	*pre;

	r = calloc(sizeof(t_req), 1);
	if (!r)
		error_exit("malloc error\n");
	r->buf = BUFSIZE;
	r->pid = i;
	r->content = calloc(r->buf, sizeof(char));
	if (!r->content)
		error_exit("malloc error\n");
	if (!g_cli.request)
		g_cli.request = r;
	else
	{
		pre = g_cli.request;
		while (pre->next)
			pre = pre->next;
		pre->next = r;
	}
	return (r);
}

void	output(t_req	*r)
{
	int j;
	t_req	*bf;

	j = 0;
	if (r->use - HEADER_SIZE)
		j = write(STDOUT_FILENO, r->content + HEADER_SIZE, r->use - HEADER_SIZE);
	if (j < 0)
		error_exit(NULL);
	j = r->pid;
	if (g_cli.request == r)
{
		g_cli.request = r->next;
}
	else
	{
		bf = g_cli.request;
		while (bf->next != r)
			bf = bf->next;
		bf->next = r->next;
	}
	free(r->content);
	free(r);
	kill(j, SIGUSR1);
	return ;
}

void	error_exit(char *msg)
{
	t_req	*r;
	t_req	*rr;

	if (msg)
		write(STDOUT_FILENO, msg, strlen(msg));
	r = g_cli.request;
	rr = r->next;
	while (r)
	{
		rr = r->next;
		free(r->content);
		free(r);
		r = rr;
	}
	g_cli.request = NULL;
	return ;
}
