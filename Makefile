# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/20 22:37:44 by yonamog2          #+#    #+#              #
#    Updated: 2023/02/05 12:52:08 by yonamog2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

.SILENT:

FILES =		ft_expand.c\
			added.c \
			pipex.c \
			ft_red_files.c \
			ft_red_files_util.c \
			ft_builtin.c \
			ft_export.c \
			ft_search.c \
			ft_linkedlist.c \
			minishell.c  \
			for_print.c \
			ft_checker_qoutes.c \
			ft_copy_to_struct.c \
			ft_lexer.c \
			ft_redirection_utils.c \
			ft_redirection.c \
			ft_separate_struct.c \
			ft_shell_utils.c \
			ft_space.c \
			ft_cd.c \
			ft_export_utils.c \
			ft_create_env_list.c \
# FILES = ft_input.c
# FILES = try.c
OBJ = $(FILES:.c=.o)

#for mac
CC = cc  -I/usr/local/Cellar/readline/8.1/include
#for linux
# CC = cc 

CFLAGS = -Wall -Werror -Wextra -g

all : $(NAME)
	tput setaf 3
	echo "🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥\n";
	echo "	██    ██ █ ██    █ █ █████ █   █ █████ █     █";
	echo "	███  ███ █ ███   █ █ █     █   █ █     █     █";
	echo "	█ ████ █ █ █ ██  █ █ █████ █████ ████  █     █";
	echo "	█  ██  █ █ █  ██ █ █     █ █   █ █     █     █";
	echo "	█      █ █ █   ███ █ █████ █   █ █████ █████ █████";
	echo "\n🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥";
	echo "                                                                                              ";
	tput setaf 7
%.o : %.c
	$(CC) -c $(CFLAGS) $?
	
$(NAME): $(OBJ)
	tput setaf 3
	printf "COMPILING!\n"
	tput setaf 7
	cd ft_printf && make
#for mac
	$(CC)  -L /usr/local/Cellar/readline/8.1/lib -lreadline $(OBJ) $(CFLAGS)  ./ft_printf/libft.a -o $(NAME)
# $(CC)  $(OBJ) $(CFLAGS) -L/usr/local/lib -I/usr/local/include -lreadline ./ft_printf/libft.a -o $(NAME)
	tput setaf 3
	printf "done compiling!\n"
	tput setaf 7

clean: 
	tput setaf 1
	printf "Cleaning!\n"
	tput setaf 7
	cd ft_printf && make clean
	rm -f $(OBJ)

fclean: clean
	cd ft_printf && make fclean
	rm -f $(NAME)
	tput setaf 3
	printf "done cleaning!\n"
	tput setaf 7

re: fclean all

.PHONY: all clean fclean re