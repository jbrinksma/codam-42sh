# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbrinksm <jbrinksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/05/26 18:03:46 by tde-jong      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = vsh
CC = gcc
FLAGS = -Wall -Werror -Wextra -Wunreachable-code
COVERAGE = -coverage
INCLUDES = -I./libft/ -I./includes
LIBFT = ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
CRITERIONINCLUDES = -I$(HOME)/.brew/include
CRITERION = $(CRITERIONINCLUDES) -L$(HOME)/.brew/lib -lcriterion
VPATH = ./test ./libft ./srcs ./srcs/builtins ./srcs/input_handling \
./srcs/term_settings ./srcs/environment_handling ./srcs/shell \
./srcs/tools ./test/parser ./test/tools ./test/builtins \
./test/environment_handling ./srcs/lexer
SRCS = shell_start shell_prompt \
builtin_exit \
input_read input_parse_char input_parse_escape input_parse_home \
input_parse_end input_parse_prev input_parse_next input_parse_backspace \
input_parse_delete input_parse_ctrl_d input_parse_ctrl_k \
input_parse_ctrl_up input_parse_ctrl_down input_is_word_start \
term_prepare term_is_valid term_init_struct term_get_attributes \
term_set_attributes term_reset_attributes term_free_struct \
get_environ_cpy var_get_value var_set_value var_join_key_value var_add_value \
is_char_escaped \
builtin_echo builtin_echo_set_flags \
lexer lexer_utils lexer_debug lexer_evaluator lexer_scanner \
lexer_state_if_else lexer_state_single lexer_state_start lexer_state_strings
TESTS = unit_test
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

test_norm: fclean
	@echo "[ + ] cloning norminette+"
	@git clone https://github.com/thijsdejong/codam-norminette-plus ~/norminette+
	@echo "[...] running norminette+"
	@sh ${TRAVIS_BUILD_DIR}/test/norminette.sh

$(TESTOBJECTS): $(TESTS)
	@$(CC) $(FLAGS) $^ $(INCLUDES) $(CRITERIONINCLUDES) -c

build_test: $(TESTOBJECTS) $(OBJECTS)
	@make re
	@make $(TESTOBJECTS)
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) $(CRITERION) $(LIB) -o vsh_tests

test: build_test
	@./vsh_tests

test_valgrind: build_test
	@valgrind --tool=memcheck --leak-check=full ./vsh_tests

test_coverage: test
	@gcov $(SRCS)

.PHONY: test_norm test_coverage all clean fclean re test $(TESTOBJECTS)
