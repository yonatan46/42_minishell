# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid Date        by              +#+  #+#    #+#              #
#    Updated: 2023/01/27 15:01:17 by dkaratae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

FILES = 	minishell.c  \
			for_print.c \
			ft_checker_qoutes.c \
			ft_copy_to_struct.c \
			ft_lexer.c \
			ft_redirection_utils.c \
			ft_redirection.c \
			ft_separate_struct.c \
			ft_shell_utils.c \
			ft_space.c \
		
LIBFT = libft/libft.a

CC = gcc -I/usr/local/include 

# CFLAGS = -Wextra -Wall -Werror -g
CFLAGS = -Wextra -Wall -Werror -g -fsanitize=address

OBJS	=	$(FILES:%c=%o)

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L/usr/local/lib -lreadline -o $(NAME)
	
$(LIBFT):
	make -C libft

clean :
	rm -f *.o
	make clean -C libft

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re 


# NAME = minishell

# FILES = minishell.c 

# LIBFT = libft/libft.a

# OBJ = $(FILES:.c=.o)

# CC = gcc  -I/usr/local/include 

# CFLAGS = -Wall -Werror -Wextra 

# all : $(NAME)

# 	%.o : %.c
# 	$(CC) -c  $?

# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -L/usr/local/lib -lreadline -o $(NAME) 

# $(LIBFT):
# 	make -C libft

# clean:
# 	rm -f $(OBJ)
# 	make clean -C libft

# fclean: clean
# 	rm -f $(NAME)
# 	make clean -C libft

# re: fclean all

# .PHONY: all clean fclean re