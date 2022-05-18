#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
#define SHA256LEN 32
#define BUFSIZE 64
#define HEADER_SIZE 40

typedef struct s_request
{
	int					pid;
	char				*content;
	size_t				buf;
	size_t				use;
	unsigned int		bit;
	struct s_request	*next;
}	t_req;

typedef struct s_clients
{
	int					is_sig;
	pid_t				me;
	struct s_request	*request;
}	t_cli;

t_req	*search_client(pid_t	i);
t_req	*mknwereq(pid_t	i);
void	more_mem(t_req	*r);
void	output(t_req	*r);
int		check_hash(t_req	*r);
void	error_exit(char *msg);

void	act(int sig, siginfo_t *info, void *context);

void	sha256(const void *data, size_t len, uint8_t *hash);
#endif
