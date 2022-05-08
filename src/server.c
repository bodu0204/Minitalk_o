#include "server.h"
t_req	*g_clients = NULL;

void act(int sig, siginfo_t *info, void *context*)
{
	t_req *c;
	void *p;
	c = search_client(info->si_pid);//この中でフリーしちゃってもいいかも
	if (c == NULL)
	{
		//freeしたい
	}
	if (sig == SIGUSR1)
		c->request[c->len] |= 1U << c->bit;
	c->bit++;
	if (c->bit >= 8)
	{
		c->len++;
		c->bit = 0;
	}
	if (c->len >= c->buf)
	{
		c->buf <<= 1;
		p = calloc(c->buf, sizeof(char));
		if (!p)
		{
			//エラー処理
		}
	}
	

}
