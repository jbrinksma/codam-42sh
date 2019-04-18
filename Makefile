# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/04/18 19:10:55 by jbrinksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = vsh
CC = gcc
FLAGS = -Wall -Werror -Wextra
COVERAGE = -coverage
INCLUDES = -I./ -I./libft/ -I./includes -I../includes
LIBFT= ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
VPATH = ./srcs ./test ./libft
SRCS = shell_prompt builtin_exit input_read parser_lexer jornfuckup \
term_prepare term_is_valid term_init_struct term_get_attributes \
term_set_attributes term_reset_attributes term_free_struct 
TESTS = test_main.c
OBJECTS := $(SRCS:%=%.o)
TESTOBJECTS := $(TESTS:%.c=%.o)
SRCS := $(SRCS:%=%.c)

all: $(OBJECTS) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS) main.o
	@$(CC) $(FLAGS) $(COVERAGE) $(INCLUDES) $(LIB) -o $(NAME) $^
	@echo "[ + ] vsh has been compiled"

$(OBJECTS): $(SRCS) main.c
	@$(CC) $(FLAGS) $(COVERAGE) $(INCLUDES) -c $^

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

$(TESTOBJECTS): $(TESTS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $^

test_coverage: $(TESTOBJECTS) $(OBJECTS)
	@ make re
	@ $(CC) $(FLAGS) $(COVERAGE) $(INCLUDES) $(LIB) -o test_coverage $^
	@ ./test_coverage
	@ gcov $(SRCS)

.PHONY: test_norm test_coverage
