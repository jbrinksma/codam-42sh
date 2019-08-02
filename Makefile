# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: omulder <omulder@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/08/02 15:12:53 by jbrinksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = vsh
CC = gcc
FLAGS = -Wall -Werror -Wextra -Wunreachable-code -g
COVERAGE =
INCLUDES = -I./libft/ -I./includes
LIBFT = ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
CRITERIONINCLUDES = -I$(HOME)/.brew/include
CRITERION = $(CRITERIONINCLUDES) -L$(HOME)/.brew/lib -lcriterion
VPATH = ./test ./libft ./srcs ./srcs/builtins ./srcs/input_handling \
./srcs/term_settings ./srcs/environment_handling ./srcs/shell \
./srcs/tools ./srcs/alias ./test/parser ./test/tools ./test/builtins \
./test/environment_handling ./srcs/lexer ./srcs/parser ./srcs/history \
./srcs/exec ./srcs/redir ./srcs/error_handling ./srcs/exec ./includes
SRCS = shell_start shell_prompt shell_quote_checker shell_dless_input \
shell_init_files shell_init_vshdata shell_getcurrentdir \
shell_handle_escaped_newlines \
input_read input_parse_char input_parse_escape input_parse_home \
input_parse_end input_parse_prev input_parse_next input_parse_backspace \
input_parse_delete input_parse_ctrl_c input_parse_ctrl_d input_parse_ctrl_k \
input_parse_ctrl_up input_parse_ctrl_down input_is_word_start \
term_prepare term_is_valid term_init_struct term_get_attributes \
term_set_attributes term_reset_attributes term_free_struct \
env_getvalue env_getlst env_lsttoarr env_lstnew env_lstaddback env_lstdel \
env_remove_tmp env_sort env_lstadd_to_sortlst env_addvalue \
tools_is_char_escaped tool_is_redirect_tk tools_is_valid_identifier \
tools_is_builtin tool_is_special tool_check_for_special tools_is_fdnumstr \
tools_isidentifierchar tool_check_for_whitespace \
builtin_echo builtin_echo_set_flags builtin_exit builtin_assign \
builtin_export builtin_export_print builtin_set builtin_unset \
builtin_alias builtin_alias_set builtin_alias_lstdel builtin_unalias \
builtin_cd builtin_cd_error builtin_cd_pathparsing \
builtin_cd_pathparsing_tools builtin_cd_changedir \
lexer lexer_utils lexer_debug lexer_evaluator lexer_scanner \
lexer_state_if_else lexer_state_single lexer_state_start lexer_state_strings \
parser_start parser_debug parser_utils parser_command parser_error \
parser_astdel \
alias_expansion alias_replace alias_read_file alias_add_expanded \
history_to_file history_get_file_content history_line_to_array history_print \
history_change_line history_index_change \
exec_builtin exec_cmd exec_external exec_start exec_find_binary \
exec_quote_remove exec_handle_variables exec_handle_dollar \
exec_handle_bracketed_var \
redir_pipe redir redir_tools redir_tools2 \
print_errors
TESTS = unit_test builtin_assign_test
OBJECTS := $(SRCS:%=%.o)
TESTOBJECTS := $(TESTS:%=%.o)
SRCS := $(SRCS:%=%.c)
TESTS := $(TESTS:%=%.c)

all: $(OBJECTS) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS) main.o
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) $(LIB) -o $(NAME)
	@echo "[ + ] vsh has been compiled"

%.o: %.c vsh.h
	@$(CC) -o $@ $(FLAGS) $< $(COVERAGE) $(INCLUDES) -c

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
	@make re COVERAGE=$(COVERAGE)
	@make $(TESTOBJECTS) COVERAGE=$(COVERAGE)
	@$(CC) $(FLAGS) $^ $(COVERAGE) $(INCLUDES) $(CRITERION) $(LIB) -o vsh_tests

test: build_test
	@./vsh_tests

test_valgrind: build_test
	@valgrind --tool=memcheck --leak-check=full ./vsh_tests

test_coverage: COVERAGE = -coverage
test_coverage: test
	@gcov $(SRCS)

.PHONY: test_norm test_coverage all clean fclean re test $(TESTOBJECTS)
