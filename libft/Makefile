# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/09 11:10:43 by omulder        #+#    #+#                 #
#    Updated: 2019/08/29 14:54:04 by jbrinksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra -Wunreachable-code
INCLUDES = -I./includes
FILES = ft_atoi.c ft_itoa.c ft_memalloc.c ft_memdel.c ft_memmove.c \
ft_putstrarr.c ft_putstrarri.c ft_strdel.c ft_strdup.c ft_strjoin.c \
ft_strlen.c ft_strnew.c ft_strsub.c ft_strreplace.c ft_isdigit.c \
ft_isspace.c ft_intlen.c ft_memcpy.c ft_putendl.c ft_putstr.c ft_putnbr.c \
ft_strcpy.c ft_strcat.c ft_strstr.c ft_putchar.c ft_bzero.c ft_isblank.c \
ft_strcmp.c ft_isprint.c ft_strarrdel.c ft_arraylen.c \
ft_strcdup.c ft_strncmp.c ft_strequ.c ft_strnequ.c ft_strncpy.c ft_memset.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstlen.c \
ft_lsttoarray.c ft_lstnew.c ft_lstaddback.c ft_lstadd.c ft_strchr.c \
ft_strsplit.c ft_strjoinchr.c ft_strjoinchrfree.c ft_strndup.c \
ft_lstiter.c ft_lstdel.c ft_lstdelone.c ft_strarradd.c \
ft_joinstrcstr.c ft_chartostr.c ft_joinstrcstr_free_s1.c \
ft_joinstrcstr_free_s2.c ft_joinstrcstr_free_all.c ft_strrnchr.c \
ft_get_next_line.c \
ft_strjoinfree_s1.c ft_strjoinfree_s2.c ft_strjoinfree_all.c \
ft_strclen.c ft_isalpha.c ft_isalnum.c ft_free_return.c ft_is_regular_file.c \
ft_isdir.c ft_aisint.c ft_tputchar.c
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
