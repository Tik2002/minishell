RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
RESET	= \033[0;37m
SKY		= \033[1;36m

CC = gcc
SRCSPATH = ./srcs/
LIBFTPATH = ./libft/
LISTPATH = ./list_c/
BS_TREEPATH = ./bs_tree_c/
AS_TREEPATH = ./as_tree_c/
INCLPATH = ./includes/ $(LIBFTPATH) $(LISTPATH)includes/ $(BS_TREEPATH)includes/ $(AS_TREEPATH)includes/ ./readline_local/include/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(SRCSPATH)%.o, $(SRCS))

CFLAGS = -g -Wall -Wextra -Werror $(foreach H, $(INCLPATH), -I$(H))
EXECFLAGS = -g -lreadline -lncurses
#-fsanitize=address
UNAME = $(shell uname -s)
ifeq ($(UNAME), Darwin)
	LREADLINE =  -Lreadline_local/lib -lreadline
else
	LREADLINE = -lreadline
endif

# -g
LIBFT = $(LIBFTPATH)libft.a
LIST = $(LISTPATH)list.a
BS_TREE = $(BS_TREEPATH)bs_tree.a
AS_TREE = $(AS_TREEPATH)as_tree.a
NAME = minishell

all : $(NAME)

#
$(NAME) : $(OBJS) $(LIBFT) $(LIST) $(BS_TREE) $(AS_TREE)
	@$(CC) $^ $(EXECFLAGS) $(LREADLINE) -o $@
	@echo "$(GREEN) Executable file has been created $(RESET)"

$(LIBFT) :
	@make -C $(LIBFTPATH) all
	@echo "$(YELLOW) Libfts object files have been created $(RESET)"

$(LIST) :
	@make -C $(LISTPATH) all
	@echo "$(YELLOW) Lists object files have been created $(RESET)"

$(BS_TREE) :
	@make -C $(BS_TREEPATH) all
	@echo "$(YELLOW) Binary search trees object files have been created $(RESET)"

$(AS_TREE) :
	@make -C $(AS_TREEPATH) all
	@echo "$(YELLOW) Abstract syntax trees object files have been created $(RESET)"

$(SRCSPATH)%.o : $(SRCSPATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW) Object files have been created $(RESET)"

clean :
	@make -C $(LIBFTPATH) clean
	@make -C $(LISTPATH) clean
	@make -C $(BS_TREEPATH) clean
	@make -C $(AS_TREEPATH) clean
	@rm -f $(OBJS)
	@echo "$(RED) Object files have been deleted $(RESET)"

fclean : clean
	@make -C $(LIBFTPATH) fclean
	@make -C $(LISTPATH) fclean
	@make -C $(BS_TREEPATH) fclean
	@make -C $(AS_TREEPATH) fclean
	@rm -f $(NAME)
	@echo "$(RED) Executable file has been deleted $(RESET)"

re : fclean all

config:
	mkdir -p readline_local
	./readline_config.sh readline_local

leaks : all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=.vlgignore ./${NAME}
#
.PHONY : all clean fclean re config
