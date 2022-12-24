# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 12:43:34 by yonamog2          #+#    #+#              #
#    Updated: 2022/12/23 16:32:08 by yonamog2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = minishell.c ft_split.c ft_isprint.c ft_strlen.c ft_strdup.c ft_substr.c 

OBJ = $(FILES:.c=.o)

CC = gcc  -I/usr/local/include 

CFLAGS = -Wall -Werror -Wextra 

all : $(NAME)

%.o : %.c
	$(CC) -c  $?

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L/usr/local/lib -lreadline -o $(NAME) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re