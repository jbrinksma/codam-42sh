# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/04/17 14:06:03 by jbrinksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I./ -I./libft/ -I./includes
LIBFT= ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
VPATH = ./srcs
SRCS = main term_init shell_prompt builtin_exit input_read
SRCS := $(SRCS:%=%.c)
OBJECTS = $(SRCS:.c=.o)

all: $(OBJECTS) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(LIB) -o $(NAME) $^
	@echo "[ + ] 21sh has been compiled"

$(OBJECTS): $(SRCS)
	@echo "[...] compiling 21sh"
	@$(CC) $(FLAGS) $(INCLUDES) -c $^

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@rm -f $(OBJECTS)
	@$(MAKE) -C libft clean
	@echo "[ - ] removed object files"
	
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "[ - ] removed binaries"

re: fclean all
