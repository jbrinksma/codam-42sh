# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: omulder <omulder@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/10 20:30:07 by jbrinksm       #+#    #+#                 #
#    Updated: 2019/11/07 13:59:26 by omulder       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
CC = gcc
FLAGS = -Wall -Werror -Wextra -Wunreachable-code
INCLUDES = -I./libft/ -I./includes
LIBFT = ./libft/libft.a
LIB = -L./libft/ -lft -ltermcap
OBJDIR = objects/
VPATH = ./libft ./srcs ./srcs/builtins ./srcs/input_handling \
./srcs/term_settings ./srcs/environment_handling ./srcs/shell \
./srcs/tools ./srcs/alias ./test/parser ./test/tools ./test/builtins \
./test/environment_handling ./srcs/lexer ./srcs/parser ./srcs/history \
./srcs/expan ./srcs/autocomplete ./srcs/hashtable ./srcs/signal \
./srcs/exec ./srcs/redir ./srcs/error_handling ./srcs/exec ./includes \
./srcs/builtins/builtin_fc ./srcs/jobs ./srcs/globbing
SRCS = shell_start shell_prompt shell_quote_checker shell_dless_input \
shell_init_files shell_init_vshdata shell_getcurrentdir \
shell_handle_escaped_newlines shell_init_input shell_init_features \
shell_args shell_get_path shell_init_line shell_one_line shell_stdin \
shell_line_splitter shell_lines_exec shell_split_line \
shell_close_quote_and_esc \
input_read input_parse_char input_parse_home \
input_parse_end input_parse_prev input_parse_next input_parse_backspace \
input_parse_delete input_parse_ctrl_c input_parse_ctrl_d input_parse_ctrl_k \
input_parse_ctrl_up input_parse_ctrl_down input_print_str \
input_parse_ctrl_u input_parse_ctrl_y input_resize_window_check \
input_clear_char_at input_read_ansi input_parse_special input_add_chunk \
input_parse_tab input_reset_cursor_pos input_get_curs_row \
input_parse_ctrl_r input_parse_esc input_parse_char_og \
curs_move_n_left_hasnewlines curs_move_n_right_hasnewlines \
term_prepare term_is_valid term_init_struct term_get_attributes \
term_set_attributes term_reset_attributes term_free_struct \
term_disable_isig term_enable_isig \
env_getvalue env_getlst env_lsttoarr env_lstnew env_lstaddback env_lstdel \
env_remove_tmp env_sort env_lstadd_to_sortlst env_addvalue exec_redirs \
exec_assigns \
tools_is_char_escaped tools_is_redirect_tk tools_is_valid_identifier \
tools_is_builtin tools_is_special tools_check_for_special tools_is_fdnumstr \
tools_is_identifier_char tools_check_for_whitespace tools_get_paths \
tools_isprintnotblank tools_contains_quoted_chars \
tools_is_cmd_seperator tools_remove_quotes_etc tools_is_valid_name \
builtin_echo builtin_echo_set_flags builtin_exit builtin_assign \
builtin_export builtin_export_print builtin_set builtin_unset \
builtin_alias builtin_alias_set builtin_alias_lstdel builtin_unalias \
builtin_cd builtin_cd_error builtin_cd_pathparsing \
builtin_cd_pathparsing_tools builtin_cd_changedir \
builtin_type builtin_hash builtin_jobs builtin_fg builtin_bg \
lexer lexer_utils lexer_scanner \
lexer_state_if_else lexer_state_single lexer_state_start lexer_state_strings \
lexer_tokenlstiter \
parser_start parser_utils parser_command parser_error \
parser_astdel \
alias_expansion alias_replace alias_read_file alias_add_expanded \
alias_getvalue \
history_to_file history_get_file_content history_item_helpers history_print \
history_change_line history_index_change history_expansion history_get_line \
history_match_line history_insert_into_line history_helpers history_ctrl_r \
exec_builtin exec_cmd exec_external exec_start exec_find_binary \
exec_quote_remove expan_handle_variables expan_handle_dollar \
exec_create_files exec_command exec_create_process_args \
expan_handle_bracketed_var expan_tilde_expansion exec_validate_binary \
expan_pathname \
redir redir_tools \
hash_ht_insert hash_print hash_reset hash_check \
print_errors print_errors_extended \
auto_get_cmdlst auto_match_builtins auto_get_filelst auto_get_varlst \
auto_find_state auto_start auto_add_match_to_line auto_find_matches \
auto_handle_matchlst auto_small_lst auto_big_lst auto_lst_print \
auto_lst_print_helpers auto_check_dups \
jobs_list_handling jobs_job_utils jobs_find jobs_cont jobs_bg \
jobs_fg jobs_info jobs_mark jobs_processes jobs_status jobs_wait \
jobs_notify jobs_command jobs_launch_forked_job jobs_launch_proc \
jobs_exec_builtin jobs_launch_job \
jobs_finished_job jobs_flush_job jobs_force_job_state jobs_launch_tools \
builtin_fc builtin_fc_options builtin_fc_init builtin_fc_list \
builtin_fc_print_helpers builint_fc_find_index builtin_fc_substitute \
signal_reset \
builtin_fc_edit \
glob_expand_word glob_lexer glob_matchlst_funcs glob_lexer_helpers \
glob_lexer_states glob_matcher glob_helpers glob_dir_match_loop glob_ast_add \
glob_tokenlst_funcs
OBJECTS := $(SRCS:%=$(OBJDIR)%.o)
SRCS := $(SRCS:%=%.c)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJDIR) $(OBJECTS) $(OBJDIR)main.o
	@$(CC) $(FLAGS) $(OBJECTS) $(OBJDIR)main.o $(INCLUDES) $(LIB) \
		-o $(NAME)
	@echo "[ + ] vsh has been compiled"

$(OBJDIR)%.o: %.c vsh.h
	@$(CC) -o $@ $(FLAGS) $< $(INCLUDES) -c

$(LIBFT):
	@$(MAKE) -C libft

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@rm -f $(OBJECTS) $(TESTOBJECTS) $(OBJDIR)main.o
	@$(MAKE) -C libft fclean
	@echo "[ - ] removed object files"

fclean: clean
	@rm -f $(NAME)
	@echo "[ - ] removed binaries"

re: fclean all

.PHONY: all clean fclean re
