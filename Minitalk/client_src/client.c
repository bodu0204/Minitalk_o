#include "client.h"
#include "debug.h"/* test */

void showhash(uint8_t *hash)/* test */
{
    for (size_t i = 0; i < 32; i++){
        printf("%02hhx",hash[i]);
    }
    return ;
}

void	send(pid_t	pid, char *s, size_t l, int	spd);
void	connect(pid_t	pid);
void	readin(size_t	len, t_str	*r);
void	treat_to_send(t_str	*s);
void	sending(pid_t	pid, t_str	*s);
int speed(int flag);

int g_result = NOSIG;

void act(int signo)
{
//TEST
	if (signo == SIGUSR1)
{
TEST
		g_result = SUCCESS;
}
	else if (signo == SIGUSR2)
{
TEST
		g_result = FAIL;
}
	return ;
}

int main (int argc, char *argv[])
{
	pid_t	pid;
	t_str	s;

TESTn("pid", getpid())
	if (argc != 2/*  || isnt_correct_num(argv[2]) */)
	{
		write(STDOUT_FILENO, "Not a valid PID\n", 16);
		return (1);
	}
	pid = atoi(argv[1]);
	signal(SIGUSR1, act);
	signal(SIGUSR2, act);
	connect(pid);
	while (1)
	{
		readin(HEADER_SIZE, &s);
		treat_to_send(&s);
		sending(pid, &s);
	}
	return(0);
}

void	connect(pid_t	pid)
{
	int spd;
	char blank[BUFSIZE];
	size_t	i;

	g_result = NOSIG;
	bzero(blank, BUFSIZE);
	i = HEADER_SIZE;
	memcpy(blank + SHA256LEN, &i, sizeof(size_t));
	sha256(blank + SHA256LEN ,sizeof(size_t) , (uint8_t *)blank);
	while(g_result != SUCCESS)
	{

		g_result = NOSIG;
		spd = speed(CONNECT);
		if (spd < 0)
		{
//TEST
			write(STDOUT_FILENO, "Connect error\n", 14);
			exit(1);
		}
		send(pid, blank, HEADER_SIZE, spd);
		if (g_result == NOSIG)
			sleep(4);
		if (g_result == NOSIG)
		{
//TEST
			write(STDOUT_FILENO, "Connect error\n", 14);
			exit(1);
		}
	}
	return ;
}

void	readin(size_t	len, t_str	*r)
{
	char	s[BUFSIZE];
	ssize_t	i;

	i = read(STDIN_FILENO, s, BUFSIZE);
	if (i < 0)
	{
		write(STDOUT_FILENO, "Read error\n", 11);
		exit(1);
	}
	if (s[i] == '\n')
	{
		r->s = malloc(len + i);
		if (!r->s)
		{
			write(STDOUT_FILENO, "Malloc error\n", 13);
			exit(1);
		}
		r->l = len + i - SHA256LEN;
	}
	else
		readin(len + i, r);
	memcpy(r->s + len, s, i);
	return ;
}

void	treat_to_send(t_str	*s)
{
	memcpy(s->s + SHA256LEN, &s->l, sizeof(size_t));
	sha256(s->s + SHA256LEN, s->l - SHA256LEN, (uint8_t *)(s->s));
	return ;
}

void	sending(pid_t	pid, t_str	*s)
{
	int spd;

	g_result = NOSIG;
	while(g_result != SUCCESS)
	{
		g_result = NOSIG;
		spd = speed(GET);
		if (spd < 0)
		{
			write(STDOUT_FILENO, "sending error\n", 14);
			free (s->s);
			exit(1);
		}
		send(pid, s->s, s->l, spd);
		if (g_result == NOSIG)
			usleep(100000);
		if (g_result == SUCCESS)
			speed(SUCCESS);
		else
			speed(FAIL);
	}
	free(s->s);
	bzero(s, sizeof(t_str));
}

int speed(int flag)
{
	static int base = 0;
	static int type[4];
	static int prev;
	int i;

	if (!base)
	{
		i = 0;
		prev = 1;
		base = 1U;
		while (i < 4)
		{
			type[i] = 2;
			i++;
		}
	}
	if (flag == SUCCESS)
	{
		type[prev]++;
		type[prev] %= 5;
	}
	else if (flag == FAIL)
		type[prev]--;
	else if (flag == CONNECT)
	{
		base <<= 1;
		if (base > 100000)
			return (-1);
		return (base << 1);
	}
	i = 0;
	prev = i;
	while (i < 4)
	{
		if (type[i] > type[prev])
			prev = i;
		i--;
	}
	if (type[prev] < -2)
		return (-1);
	return (base << prev);
}

void	send(pid_t	pid, char *s, size_t l, int	spd)
{
	uint8_t	b;
	size_t	B;

	b = 1U;
	B = 0;
/* showhash((uint8_t *)(s));  */TESTn("spd", spd)
TESTn("l", l)
	while(B < l)
	{
		usleep(spd);
		if (s[B] & b)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		b <<= 1;
		if (b == 0)
		{
			b = 1U;
			B++;
		}
	}
	return ;
}