/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryoakira <ryoakira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 08:31:19 by ryoakira          #+#    #+#             */
/*   Updated: 2022/05/20 06:38:43 by ryoakira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# define SHA256LEN 32
# define BUFSIZE 64
# define HEADER_SIZE 40
# define STARTSPEED 4
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

void	send(char *s, size_t l, int	spd);
void	connect(void);
void	readin(size_t	len, t_str	*r);
void	treat_to_send(t_str	*s);
void	sending(t_str	*s);
int		speed(int flag);
int		isnt_correct_num(char *s);
void	msg_exit(char *s);

void	sha256(const void *data, size_t len, uint8_t *hash);

int		ft_isdigit(int	c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
#endif
