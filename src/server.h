#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# define SHA256LEN 32
# define BUFSIZE 64
# define HEADER_SIZE (sizeof(uint8_t) * SHA256LEN + sizeof(size_t))


enum
{
	LINKING,
	IN_HASH,
	IN_PID,
	IN_HASH,
};


typedef struct s_request
{
	int					pid;
	int					*content;
	size_t				buf;
	size_t				use;
	unsigned int		bit;
	int					status;
	struct s_request	*next;
}	t_req;

typedef struct s_clients
{
	int					is_sig;
	struct s_request	*request;
}	t_cli;

typedef struct s_rtn
{
	size_t	prtl;
	char	*prt;
}	t_rtn;

void	sha256(const void *data, size_t len, uint8_t *hash);
#endif
