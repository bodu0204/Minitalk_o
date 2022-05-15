NAME		= Minitalk
ACHIEV0		= client
ACHIEV1		= server
ACHIEV0b	= $(ACHIEV0)_bonus
ACHIEV1b	= $(ACHIEV1)_bonus
CLIENT_d	= client_src/
SERVER_d	= server_src/
SHA256_d	= sha256_src/
CLIENTb_d	= client_src_bonus/
SERVERb_d	= server_src_bonus/
SHA256b_d	= sha256_src_bonus/
CLIENT_src	= client.c 
SERVER_src	= server.c sig_server.c
SHA256_src	= sha256.c sha256_done.c sha256_hash.c sha256_init.c sha256_util.c tool.c
CLIENTb_src	=
SERVERb_src	=
SHA256b_src	=
CLIENT_h	= client.h
SERVER_h	= server.h 
SHA256_h	= sha256.h
CLIENTb_h	=
SERVERb_h	=
SHA256b_h	=
CLIENT_o	= $(CLIENT_src:%.c=%.o) 
SERVER_o	= $(SERVER_src:%.c=%.o) 
SHA256_o	= $(SHA256_src:%.c=%.o) 
CLIENTb_o	= $(CLIENTb_src:%.c=%.o)
SERVERb_o	= $(SERVERb_src:%.c=%.o)
SHA256b_o	= $(SHA256b_src:%.c=%.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I./
PRINTF_GIT	= https://github.com/bodu0204/ftprintf_o.git
PRINTF_od	= ftprintf_o/
PRINTF_d	= libftprintf/
PRINTF_a	= libftprintf.a

all : $(ACHIEV0) $(ACHIEV1)
	
$(NAME) : all

$(ACHIEV0) : $(PRINTF_a) $(CLIENT_d)$(CLIENT_h) $(SHA256_d)$(SHA256_h) $(addprefix $(CLIENT_d),$(CLIENT_o)) $(addprefix $(SHA256_d),$(SHA256_o))
	$(CC) $(CFLAGS) $(addprefix $(CLIENT_d),$(CLIENT_o)) $(addprefix $(SHA256_d),$(SHA256_o)) $(PRINTF_a) -o $(ACHIEV0)

$(ACHIEV1) : $(PRINTF_a) $(SERVER_d)$(SERVER_h) $(SHA256_d)$(SHA256_h) $(addprefix $(SERVER_d),$(SERVER_o)) $(addprefix $(SHA256_d),$(SHA256_o))
	$(CC) $(CFLAGS) $(addprefix $(SERVER_d),$(SERVER_o)) $(addprefix $(SHA256_d),$(SHA256_o)) $(PRINTF_a) -o $(ACHIEV1)

bonus : $(PRINTF_a) $(HEADER_b) $(SRC_b)
	$(CC) $(CFLAGS) $(SRC_b) $(PRINTF_a) -o $(BONUSNAME)

.c.o : 
	$(CC) $(CFLAGS) -c $< -o $(basename $<).o

$(PRINTF_d) :
	rm -rf $(PRINTF_d)
	git clone $(PRINTF_GIT) $(PRINTF_od)
	cd "$(PRINTF_od)" && make file
	mv $(PRINTF_od)$(PRINTF_d) ./
	rm -rf $(PRINTF_od)

$(PRINTF_a) : $(PRINTF_d)
	cd "$(PRINTF_d)" && make bonus
	cp $(PRINTF_d)$(PRINTF_a) ./

clean :
	cd "$(PRINTF_d)" && make clean
	rm -f $(PRINTF_a)

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUSNAME)
	rm -rf $(PRINTF_od)
	cd "$(PRINTF_d)" && make fclean

re : fclean all