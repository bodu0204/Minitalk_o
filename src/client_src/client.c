#include "client.h"

void	send(char *s, size_t l, int	spd);
void	connect(void);
void	readin(size_t	len, t_str	*r);
void	treat_to_send(t_str	*s);
void	sending(t_str	*s);
int speed(int flag);
int	isnt_correct_num(char *s);

t_info g_;

void act(int signo)
{
	if (signo == SIGUSR1)
		g_.result = SUCCESS;
	else if (signo == SIGUSR2)
		g_.result = FAIL;
	return ;
}

int main (int argc, char *argv[])
{
	t_str	s;

	if (argc != 2 || isnt_correct_num(argv[1]))
	{
		write(STDOUT_FILENO, "Not a valid PID\n", 16);
		return (1);
	}
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
	return(0);
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

void	connect(void)
{
	int spd;
	char blank[BUFSIZE];
	size_t	i;

	g_.result = NOSIG;
	bzero(blank, BUFSIZE);
	i = HEADER_SIZE;
	memcpy(blank + SHA256LEN, &i, sizeof(size_t));
	sha256(blank + SHA256LEN ,sizeof(size_t) , (uint8_t *)blank);
	while(g_.result != SUCCESS)
	{

		g_.result = NOSIG;
		spd = speed(CONNECT);
		if (spd < 0)
		{
			write(STDOUT_FILENO, "Connect error\n", 14);
			exit(1);
		}
		send(blank, HEADER_SIZE, spd);
		if (g_.result == NOSIG)
			sleep(4);
		if (g_.result == NOSIG)
		{
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
	if (s[i - 1] == '\n')
	{
		r->s = malloc(len + i);
		if (!r->s)
		{
			write(STDOUT_FILENO, "Malloc error\n", 13);
			exit(1);
		}
		r->l = len + i;
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

void	sending(t_str	*s)
{
	int spd;

	g_.result = NOSIG;
	while(g_.result != SUCCESS)
	{
		g_.result = NOSIG;
		spd = speed(GET);
		if (spd < 0)
		{
			write(STDOUT_FILENO, "sending error\n", 14);
			free (s->s);
			exit(1);
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
	bzero(s, sizeof(t_str));
}

int speed(int flag)
{
	static int base = 1;
	static int error = 0;

	if (flag == SUCCESS)
	{
		if (error > 1)
		{
			base = 1;
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
		return(-1);
	return (base << ((error / 2) + 1));
}

void	send(char *s, size_t l, int	spd)
{
	uint8_t	b;
	size_t	B;

	b = 1U;
	B = 0;
	while(B < l && g_.result != SUCCESS)
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
