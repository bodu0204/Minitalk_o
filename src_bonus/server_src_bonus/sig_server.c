#include "server.h"
t_req	*search_client(pid_t	i);
t_req	*mknwereq(pid_t	i);
void more_mem(t_req	*r);
void	output(t_req	*r);
int check_hash(t_req	*r);
void	freeall(void);


extern t_cli	g_cli;

void	act(int sig, siginfo_t *info, void *context)
{
	t_req *c;
	void *p;

	(void)context;
	g_cli.is_sig = 1;
	c = search_client(info->si_pid); //エラーの時この中でフリー exit する
	if (sig == SIGUSR1)
		c->content[c->use] |= 1U << c->bit;
	c->bit++;
	if (c->bit >= 8)
	{
		c->use++;
		c->bit = 0;
	}
	more_mem(c);//エラーの時この中でフリー exit する
	if (c->use == *((size_t *)((char *)c->content + SHA256LEN)))
	{
		if (check_hash(c))
			output(c);// 標準出力 この項目を消す successを返す エラーの時この中でフリー exit する
	}
}

t_req	*search_client(pid_t	i)
{
	t_req	*r;
	char	*cnt;

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

	r = calloc(sizeof(t_req), 1);/*  */
	if (!r)
	{
		write(STDOUT_FILENO, "malloc error\n", 14);
		freeall();/*  */
		exit(1);
	}
	r->buf = BUFSIZE;
	r->pid = i;
	r->content = calloc(r->buf, sizeof(char));/*  */
	if (!r->content)
	{
		write(STDOUT_FILENO, "malloc error\n", 14);
		free(r);
		freeall();/*  */
		exit(1);
	}
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

void more_mem(t_req	*r)
{
	char	*new;
	size_t	l;

	if (r->use + 1  >= r->buf)
	{
		l = r->buf;
		r->buf <<= 1;
		new = calloc(r->buf, sizeof(char));
		if (!new)
		{
		write(STDOUT_FILENO, "malloc error\n", 14);
		freeall();
		exit(1);
		}
		memcpy(new, r->content, l);
		free(r->content);
		r->content = new;
	}
	return ;
}

void	output(t_req	*r)
{
	int j;
	t_req	*bf;

	j = write(STDOUT_FILENO, r->content + HEADER_SIZE, r->use - HEADER_SIZE);
	if (j < 0)
	{
		freeall();/*  */
		exit(1);
	}
	j = r->pid;
	if (g_cli.request == r)
		g_cli.request = r->next;
	else
	{
		bf = g_cli.request;
		while (bf->next != bf)
			bf = bf->next;
		bf->next = r->next;
	}
	free(r);
	kill(j, SIGUSR1);
	return ;
}

int check_hash(t_req	*r)
{
	uint8_t hash[SHA256LEN];

	sha256(r->content + SHA256LEN, r->use - SHA256LEN, hash);
	return (!memcmp(r->content, hash, SHA256LEN));
}

void	freeall(void)
{
	t_req	*r;
	t_req	*rr;

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
