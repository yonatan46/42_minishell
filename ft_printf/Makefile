# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/20 22:37:44 by yonamog2          #+#    #+#              #
#    Updated: 2022/11/19 17:40:25 by yonamog2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FILES = ft_printf.c ft_printf_deps.c ft_uns_print.c ft_ptr_print.c ft_hex_print.c ft_bzero.c ft_lstnew.c ft_lstmap.c ft_lstiter.c ft_lstclear.c ft_lstdelone.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstadd_front.c ft_itoa.c ft_split.c ft_striteri.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_strmapi.c ft_strtrim.c ft_strjoin.c ft_memcmp.c ft_memchr.c ft_memmove.c ft_strnstr.c ft_strlcat.c ft_strncmp.c ft_strrchr.c ft_strchr.c ft_isalpha.c ft_calloc.c ft_isalnum.c ft_strlcpy.c ft_atoi.c ft_tolower.c ft_toupper.c ft_strdup.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memset.c ft_strlen.c ft_substr.c
OBJ = $(FILES:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rc $@ $?
%.o : %.c
	@$(CC) -c $(CFLAGS) $?
bonus:	$(OBJ)
	@ar -rc $@ $?
clean: 
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME) bonus
re: fclean all bonus

.PHONY: all clean fclean re bonus