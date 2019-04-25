# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/09 11:10:43 by omulder        #+#    #+#                 #
#    Updated: 2019/04/25 14:38:12 by mavan-he      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I./includes
FILES = ft_atoi.c ft_itoa.c ft_memalloc.c ft_memdel.c ft_memmove.c \
	ft_putstrarr.c ft_putstrarri.c ft_strdel.c ft_strdup.c ft_strjoin.c \
	ft_strlen.c ft_strnew.c ft_strsub.c ft_strreplace.c ft_isdigit.c \
	ft_isspace.c ft_intlen.c ft_memcpy.c ft_putendl.c ft_putstr.c ft_putnbr.c \
	ft_strcpy.c ft_strcat.c ft_strstr.c ft_putchar.c ft_bzero.c ft_isblank.c \
	ft_strjoinfree.c ft_strcmp.c ft_isprint.c ft_freearray.c ft_arraylen.c \
	ft_strcdup.c ft_strncmp.c
OBJECTS = $(FILES:.c=.o)

all: $(OBJECTS) $(NAME)

$(NAME): $(OBJECTS)
	@$(MAKE) -C ft_printf re
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

$(OBJECTS): $(FILES)
	@$(CC) $(FLAGS) $(INCLUDES) -c $^

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C ft_printf clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ft_printf fclean

re: fclean all
