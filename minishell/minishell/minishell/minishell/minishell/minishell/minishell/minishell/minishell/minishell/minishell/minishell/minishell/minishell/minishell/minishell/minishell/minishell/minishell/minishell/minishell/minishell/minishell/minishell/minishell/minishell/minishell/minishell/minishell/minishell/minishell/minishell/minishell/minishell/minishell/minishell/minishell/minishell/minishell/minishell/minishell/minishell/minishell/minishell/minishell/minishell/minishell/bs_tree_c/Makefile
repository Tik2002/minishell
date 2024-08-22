RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
SKY		= \033[1;36m

CC = gcc
SRCSPATH = ./srcs/
LIBFTPATH = ../libft/
INCLPATH = ./includes/ $(LIBFTPATH)
SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(SRCSPATH)%.o, $(SRCS))
CFLAGS = -g -Wall -Wextra -Werror $(foreach H, $(INCLPATH), -I$(H))
NAME = bs_tree.a
LIBFT = $(LIBFTPATH)libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@ar -rcs $@ $^
	@echo "$(GREEN) Binary search trees archive has been created $(RESET)"

$(LIBFT) :
	@make -C $(LIBFTPATH) all
	@echo "$(YELLOW) Libfts object files have been created $(RESET)"

$(SRCSPATH)%.o : $(SRCSPATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW) Binary search trees object files have been created $(RESET)"

clean :
	@make -C $(LIBFTPATH) clean
	@rm -f $(OBJS)
	@echo "$(RED) Binary search trees object files have been deleted $(RESET)"

fclean : clean
	@make -C $(LIBFTPATH) fclean
	@rm -f $(NAME)
	@echo "$(RED) Binary search trees executable file has been deleted $(RESET)"

re : fclean all

.PHONY : all clean fclean re
