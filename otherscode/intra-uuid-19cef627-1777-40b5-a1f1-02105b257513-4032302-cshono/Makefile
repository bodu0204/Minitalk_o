NAME = minitalk

CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

SRCS_CLIENT = client.c \
			  ft_putstr_fd.c \
			  ft_putnbr_fd.c \
			  ft_putchar_fd.c \
			  ft_strlen.c \
			  ft_atoi.c \


SRCS_SERVER = server.c \
	          ft_putstr_fd.c \
			  ft_putnbr_fd.c \
			  ft_putchar_fd.c \
			  ft_strlen.c \
			  ft_memset.c \

SRCS_CLIENT_BONUS = client_bonus.c \
				    ft_putstr_fd.c \
					ft_putnbr_fd.c \
					ft_putchar_fd.c \
					ft_atoi.c \
					ft_strlen.c \

SRCS_SERVER_BONUS = server_bonus.c \
					ft_putstr_fd.c \
					ft_putnbr_fd.c \
					ft_putchar_fd.c \
					ft_strlen.c \
					ft_memset.c \

OBJS_CLIENT	=			$(SRCS_CLIENT:.c=.o)
OBJS_SERVER	=			$(SRCS_SERVER:.c=.o)
OBJS_CLIENT_BONUS	=	$(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS	=	$(SRCS_SERVER_BONUS:.c=.o)

all :		$(CLIENT) $(SERVER)

$(NAME):	all

$(CLIENT):	$(OBJS_CLIENT)
			@$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

$(SERVER):	$(OBJS_SERVER)
			@$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS):	$(OBJS_CLIENT_BONUS)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_CLIENT_BONUS) -o $(CLIENT_BONUS)

$(SERVER_BONUS):	$(OBJS_SERVER_BONUS)
			@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_SERVER_BONUS) -o $(SERVER_BONUS)

clean:		
			@rm -f $(OBJS_CLIENT)
			@rm -f $(OBJS_SERVER)
			@rm -f $(OBJS_CLIENT_BONUS)
			@rm -f $(OBJS_SERVER_BONUS)
			
fclean:		clean
			@rm -f $(CLIENT)
			@rm -f $(SERVER)
			@rm -f $(CLIENT_BONUS)
			@rm -f $(SERVER_BONUS)

re:			fclean all