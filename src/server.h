#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <signal.h>
# define SHA256LEN 32
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
	uint8_t				pid;
	uint8_t				*request;
	size_t				buf;
	size_t				use;
	uint8_t				bit;
	size_t				len;
	struct s_request	next;
}	t_req;

typedef struct s_rtn
{
	size_t	prtl;
	char	*prt;
}	t_rtn;

#endif
