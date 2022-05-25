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
CLIENT_src	= client.c client_util.c
SERVER_src	= server.c sig_server.c sig_server_util.c
SHA256_src	= sha256.c sha256_done.c sha256_hash.c sha256_init.c sha256_utilA.c sha256_utilB.c tool.c
CLIENTb_src	= client_bonus.c client_util_bonus.c
SERVERb_src	= server_bonus.c sig_server_bonus.c sig_server_util_bonus.c
SHA256b_src	= sha256_bonus.c sha256_done_bonus.c sha256_hash_bonus.c sha256_init_bonus.c sha256_utilA_bonus.c sha256_utilB_bonus.c tool_bonus.c
CLIENT_h	= client.h
SERVER_h	= server.h
SHA256_h	= sha256.h
CLIENTb_h	= client_bonus.h
SERVERb_h	= server_bonus.h
SHA256b_h	= sha256_bonus.h
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

bonus : $(ACHIEV0b) $(ACHIEV1b)

$(ACHIEV0b) : $(PRINTF_a) $(CLIENTb_d)$(CLIENTb_h) $(SHA256b_d)$(SHA256b_h) $(addprefix $(CLIENTb_d),$(CLIENTb_o)) $(addprefix $(SHA256b_d),$(SHA256b_o))
	$(CC) $(CFLAGS) $(addprefix $(CLIENTb_d),$(CLIENTb_o)) $(addprefix $(SHA256b_d),$(SHA256b_o)) $(PRINTF_a) -o $(ACHIEV0b)

$(ACHIEV1b) : $(PRINTF_a) $(SERVERb_d)$(SERVERb_h) $(SHA256b_d)$(SHA256b_h) $(addprefix $(SERVERb_d),$(SERVERb_o)) $(addprefix $(SHA256b_d),$(SHA256b_o))
	$(CC) $(CFLAGS) $(addprefix $(SERVERb_d),$(SERVERb_o)) $(addprefix $(SHA256b_d),$(SHA256b_o)) $(PRINTF_a) -o $(ACHIEV1b)


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
	rm -f $(addprefix $(CLIENT_d),$(CLIENT_o))
	rm -f $(addprefix $(SERVER_d),$(SERVER_o))
	rm -f $(addprefix $(SHA256_d),$(SHA256_o))
	rm -f $(addprefix $(CLIENTb_d),$(CLIENTb_o))
	rm -f $(addprefix $(SERVERb_d),$(SERVERb_o))
	rm -f $(addprefix $(SHA256b_d),$(SHA256b_o))
	rm -f $(PRINTF_a)

fclean : clean
	rm -f $(ACHIEV0)
	rm -f $(ACHIEV1)
	rm -f $(ACHIEV0b)
	rm -f $(ACHIEV1b)
	rm -rf $(PRINTF_od)
	cd "$(PRINTF_d)" && make fclean

re : fclean all
