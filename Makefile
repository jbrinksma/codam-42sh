# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: omulder <omulder@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/04/18 16:50:18 by omulder       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = vsh
CC = gcc
FLAGS = -Wall -Werror -Wextra -coverage
INCLUDES = -I./ -I./libft/ -I./includes -I../includes
LIBFT= ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
VPATH = ./srcs ./test ./libft
SRCS = term_init shell_prompt builtin_exit input_read parser_lexer jornfuckup
TESTS = test_main.c
OBJECTS := $(SRCS:%=%.o)
SRCS := $(SRCS:%=%.c)

all: $(OBJECTS) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS) main.o
	@$(CC) $(FLAGS) $(INCLUDES) $(LIB) -o $(NAME) $^
	@echo "[ + ] vsh has been compiled"

$(OBJECTS): $(SRCS) main.c
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

test_norm:
	@make
	@echo "[ + ] cloning norminette+"
	@git clone https://github.com/thijsdejong/codam-norminette-plus ~/norminette+
	@echo "[ o ] running norminette+"
	@sh ${TRAVIS_BUILD_DIR}/test/norminette.sh

test_coverage: $(TESTS)
	@ make re
	@ $(CC) $(FLAGS) -coverage $(INCLUDES) $(LIB) $(OBJECTS) -o test_coverage $^
	@ ./test_coverage
	@ gcov $(SRCS)

.PHONY: test_norm test_coverage
