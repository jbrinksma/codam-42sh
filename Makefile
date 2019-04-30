# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/04/30 12:07:13 by tde-jong      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = vsh
CC = gcc
FLAGS = -Wall -Werror -Wextra -Wunreachable-code
COVERAGE = -coverage
INCLUDES = -I./ -I./libft/ -I./includes -I../includes
LIBFT= ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
VPATH = ./test ./libft ./srcs ./srcs/builtins ./srcs/input_handling \
./srcs/parsing ./srcs/term_settings ./srcs/environment_handling ./srcs/shell \
./srcs/tools ./test/parser ./test/tools ./test/builtins
SRCS = shell_start shell_prompt \
builtin_exit \
input_read \
term_prepare term_is_valid term_init_struct term_get_attributes \
term_set_attributes term_reset_attributes term_free_struct \
get_environ_cpy param_to_env \
parser_lexer parser_split_line_to_commands \
is_char_escaped update_quote_status \
builtin_echo builtin_echo_set_flags
TESTS = test_main \
test_prompt \
test_get_environ_cpy test_param_to_env \
test_term_is_valid test_term_init_struct test_term_free_struct \
test_term_get_attributes \
test_parser_split_line_to_commands \
test_parser_strdup_command_from_line \
test_parser_command_len_from_line \
test_parser_total_commands_from_line \
test_is_char_escaped test_update_quote_status \
test_echo
# test_parser_lexer
OBJECTS := $(SRCS:%=%.o)
TESTOBJECTS := $(TESTS:%=%.o)
SRCS := $(SRCS:%=%.c)
TESTS := $(TESTS:%=%.c)

all: $(OBJECTS) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS) main.o
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) $(LIB) -o $(NAME)
	@echo "[ + ] vsh has been compiled"

$(OBJECTS): $(SRCS) main.c
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) -c

$(LIBFT):
	@$(MAKE) -C libft

clean:
	@rm -f $(OBJECTS) $(TESTOBJECTS) main.o
	@$(MAKE) -C libft clean
	@echo "[ - ] removed object files"
	@rm -f *.gcno
	@rm -f *.gcda

fclean: clean
	@rm -f $(NAME) test_coverage vsh_tests
	@$(MAKE) -C libft fclean
	@echo "[ - ] removed binaries"
	@rm -f *.gcov

re: fclean all

test: $(TESTOBJECTS) $(OBJECTS)
	@make re
	@make $(TESTOBJECTS)
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) $(LIB) -o vsh_tests
	@sh test/local_test.sh

test_norm: fclean
	@echo "[ + ] cloning norminette+"
	@git clone https://github.com/thijsdejong/codam-norminette-plus ~/norminette+
	@echo "[...] running norminette+"
	@sh ${TRAVIS_BUILD_DIR}/test/norminette.sh

$(TESTOBJECTS): $(TESTS)
	@$(CC) $(FLAGS) $^ $(INCLUDES) -c

test_coverage: $(TESTOBJECTS) $(OBJECTS)
	@make re
	@make $(TESTOBJECTS)
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) $(LIB) -o test_coverage
	@./test_coverage
	@gcov $(SRCS)

travis_run:
	@bash ${TRAVIS_BUILD_DIR}/test/travis.sh

travis_linux:
	make test

.PHONY: test_norm test_coverage all clean fclean re test $(TESTOBJECTS)
