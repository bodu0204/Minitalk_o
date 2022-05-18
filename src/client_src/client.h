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
	NOSIG,
	SUCCESS,
	FAIL,
	CONNECT,
	GET,
};

typedef struct s_string
{
	char	*s;
	size_t	l;
}	t_str;

typedef struct s_information
{
	int		result;
	pid_t	pid;
}	t_info;

void	sha256(const void *data, size_t len, uint8_t *hash);

int	ft_isdigit(int	c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
