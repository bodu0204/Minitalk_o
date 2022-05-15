PROJECT_NAME	= Minitalk
ACHIEV0			= 
ACHIEV1			= 
ACHIEV0b		= $(ACHIEV0)_bonus
ACHIEV1b		= $(ACHIEV1)_bonus
SRC_PASS		= src/
SRCb_PASS		= src_bonus/
OTHER_PASS		= other/
SUBMIT_d		= $(PROJECT_NAME)/
PRINTF_GIT		= https://github.com/bodu0204/ftprintf_o.git
PRINTF_od		= libftprintf_o/
PRINTF_a		= libftprintf.a
PRINTF_d		= libftprintf/
TEST_d			= test_case_0/
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I./

all : $(NAME)

$(NAME) : file
	cd "$(SUBMIT_d)" && make all
	cp -f $(ACHIEV0) ./
	cp -f $(ACHIEV1) ./

bonus : file
	cd "$(SUBMIT_d)" && make bonus
	cp -f $(ACHIEV0b) ./
	cp -f $(ACHIEV1b) ./

push : fclean
	git add .
	git commit --allow-empty -m "commit form makefile"
	git push

cloneprintf :
	git clone $(PRINTF_GIT) $(PRINTF_od)
	cd "$(PRINTF_od)" && make submit
	rm -rf $(PRINTF_od)

submitfile : push cloneprintf
	mkdir $(SUBMIT_d)
	cp $(SRC_PASS)* $(SUBMIT_d)
	cp $(SRCb_PASS)* $(SUBMIT_d)
	cp $(OTHER_PASS)* $(SUBMIT_d)
	mv $(PRINTF_d) $(SUBMIT_d)

submit : outclean submitfile
	mv $(SUBMIT_d) ../

file : fclean cloneprintf
	mkdir $(SUBMIT_d)
	cp $(SRC_PASS)* $(SUBMIT_d)
	cp $(SRCb_PASS)* $(SUBMIT_d)
	cp $(OTHER_PASS)* $(SUBMIT_d)
	mv $(PRINTF_d) $(SUBMIT_d)

test : submitfile
	cd "$(SUBMIT_d)" && make all
	cd "$(SUBMIT_d)" && make bonus
	mkdir $(TEST_d)
	mv $(SUBMIT_d)$(NAME) $(TEST_d)
	mv $(SUBMIT_d)$(BONUS_NAME) $(TEST_d)
	cp $(STDSRC_PASS)* $(TEST_d)

fclean :
	rm -rf $(SUBMIT_d)
	rm -rf $(PRINTF_d)
	rm -rf $(TEST_d)
	rm -f $(ACHIEV0)
	rm -f $(ACHIEV1)
	rm -f $(ACHIEV0b)
	rm -f $(ACHIEV1b)

outclean :
	rm -rf ../$(SUBMIT_d)

allclean : fclean outclean

re : fclean all