# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/04/11 10:04:17 by jbrinksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main
SRCS := $(SRCS:%=%.c)

HEADERS = \
			-Ilibft/includes/ \
			-Ilibft/get_next_line/includes/ \
			-Ilibft/ft_printf/includes/ \
			-Iincludes/

LIB = -Llibft/ -lft -ltermcap

GCC = gcc -Wall -Werror -Wextra

$(NAME):
	@make -C libft/
	@$(GCC) $(HEADERS) $(LIB) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	@make clean -C libft/
	@rm -rf *~

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re: fclean all
