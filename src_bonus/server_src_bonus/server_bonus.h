/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:31:39 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/26 06:38:59 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# define SHA256LEN 32
# define BUFSIZE 64
# define HEADER_SIZE 40

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

int		ft_printf(const char	*fmt, ...);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
#endif
