/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/22 15:29:52 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSH_H
# define VSH_H
# define DEBUG

/*
**==================================defines=====================================
*/

# define FUNCT_FAILURE 0
# define FUNCT_SUCCESS 1
# define FUNCT_ERROR -1
# define PROG_FAILURE 1
# define PROG_SUCCESS 0
# define E_ALLOC 420
# define E_DUP 100
# define E_OPEN 101
# define E_BADFD 102
# define E_CLOSE 103
# define E_BADRED 104
# define CTRLD -1
# define CR 0

/*
**=================================exit codes====================================
*/

# define EXIT_WRONG_USE 2
# define EXIT_NOTFOUND 127
# define EXIT_FATAL 128

/*
**------------------------------------echo--------------------------------------
*/

# define ECHO_OPT_EL		(1 << 0)
# define ECHO_OPT_EU		(1 << 1)
# define ECHO_OPT_NL		(1 << 2)
# define BS					8
# define ESC				27

/*
**-----------------------------------export-------------------------------------
*/

# define EXP_FLAG_LN	(1 << 0)
# define EXP_FLAG_LP	(1 << 1)

/*
**------------------------------------lexer-------------------------------------
*/

# define CURRENT_CHAR (scanner->str)[scanner->str_index]
# define SCANNER_CHAR scanner.str[scanner.str_index]
# define T_FLAG_HASSPECIAL (1 << 0)
# define T_STATE_SQUOTE (1 << 1)
# define T_STATE_DQUOTE (1 << 2)
# define T_FLAG_HASEQUAL (1 << 3)
# define T_MALLOC_ERROR (1 << 4)

/*
**-----------------------------------executor-----------------------------------
*/

# define EXEC_PIPE (1 << 0)
# define EXEC_BG (1 << 1)
# define EXEC_AND_IF (1 << 2)
# define EXEC_OR_IF (1 << 3)
# define EXEC_SEMICOL (1 << 4)

# define STDIN_BAK stdfds[0]
# define STDOUT_BAK stdfds[1]
# define STDERR_BAK stdfds[2]

/*
**--------------------------------redirections----------------------------------
*/

# define FD_UNINIT -1

/*
**---------------------------------environment----------------------------------
*/


# define ENV_MASK 0xF8
# define ENV_WHITESPACE (1 << 3)
# define ENV_EXTERN (1 << 2)
# define ENV_LOCAL (1 << 1)
# define ENV_TEMP (1 << 0)
# define ENV_HEAD 0

/*
**------------------------------------parser------------------------------------
*/

# define TK_TYPE (*token_lst)->type

/*
**-----------------------------------input--------------------------------------
*/

# define INPUT_NONE			0
# define INPUT_ESC			1
# define INPUT_BRACE		2
# define INPUT_THREE		3
# define INPUT_D_ESC		4
# define INPUT_D_BRACE		5
# define INPUT_D_THREE		6
# define INPUT_BACKSPACE	127

/*
**===============================personal headers===============================
*/

# include "libft.h"
# include "vsh_history.h"

/*
**==================================headers=====================================
*/

# include <stdbool.h>

/*
**	malloc, free, close, fork, execve, exit | getenv
**	access, write, read, getcwd, chdir | isatty ttyname ttyslot write close
**	open
**	opendir readdir closedir
**	stat lstat fstat
**	wait, wait3, wait4, waitpid
**	signal kill
**	****************************************************************************
**	ioctl
**	tcsetattr tcgetattr
**
**	tgetent tgetflag tgetnum tgetstr tgoto tputs
**	open
**
**	read
**	signal
*/

/*
**=================================typedefs====================================
*/

typedef struct	s_term
{
	struct termios	*old_termios_p;
	struct termios	*termios_p;
}				t_term;

/*
**----------------------------------lexer--------------------------------------
*/
/*
**	START,
**	WORD, // bascially any string
**	ASSIGN, WORD=[WORD]
**	IO_NUMBER, // NUM followed by > or <
**	AND_IF, // &&
**	OR_IF, // ||
**	DLESS, // <<
**	DGREAT, // >>
**	SLESS, // <
**	SGREAT, // >
**	LESSAND, // <&
**	GREATAND, // >&
**	BG // & in background
**	PIPE, // |
**	SEMICOL // ;
**	NEWLINE,
**	END,
**	ERROR // malloc fail
*/

typedef enum	e_tokens
{
	ERROR,
	START,
	WORD,
	ASSIGN,
	IO_NUMBER,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	SLESS,
	SGREAT,
	LESSAND,
	GREATAND,
	BG,
	PIPE,
	SEMICOL,
	NEWLINE,
	END
}				t_tokens;

typedef struct	s_tokenlst
{
	t_tokens			type;
	int					flags;
	char				*value;
	struct s_tokenlst	*next;
}				t_tokenlst;

typedef struct	s_scanner
{
	t_tokens	tk_type;
	int			tk_len;
	char		*str;
	int			str_index;
	char		flags;
}				t_scanner;

/*
**----------------------------------parser--------------------------------------
*/

typedef struct	s_ast
{
	t_tokens		type;
	char			flags;
	char			*value;
	struct s_ast	*child;
	struct s_ast	*sibling;
}				t_ast;

/*
**---------------------------------environment----------------------------------
*/

typedef struct	s_envlst
{
	char			*var;
	unsigned char	type;
	struct s_envlst	*next;
}				t_envlst;

char			*env_getvalue(char *var_key, t_envlst *envlst);
char			**env_free_and_return_null(char ***vshenviron);

/* environment branch -jorn */

t_envlst	*env_getlst(void);
void		env_lstaddback(t_envlst **lst, t_envlst *new);
t_envlst	*env_lstnew(char *var, unsigned char type);
char		**env_lsttoarr(t_envlst *lst, unsigned char minimal_type);
int			env_lstlen(t_envlst *lst, unsigned char minimal_type);
void		env_lstdel(t_envlst **envlst);
void   		env_remove_tmp(t_envlst *env);
void		env_sort(t_envlst *head);
void		env_lstadd_to_sortlst(t_envlst *envlst, t_envlst *new);

/*
**----------------------------------terminal------------------------------------
*/

t_term			*term_prepare(t_envlst *lst);
int				term_is_valid(t_envlst *envlst);
t_term			*term_init_struct(void);
int				term_get_attributes(int fd, t_term *term_p);
int				term_set_attributes(t_term *term_p);
int				term_reset(t_term *term_p);
void			term_free_struct(t_term **term_p);

/*
**-----------------------------------input--------------------------------------
*/

int				input_read(char **line);
int				input_is_word_start(char *str, int i1, int i2);
void			input_clear_char_at(char **line, unsigned index);
int				input_parse_escape(char c, int *input_state);
int				input_parse_char(char c, unsigned *index, char **line, int *len_max);
int				input_parse_home(char c, int *input_state, unsigned *index);
int				input_parse_backspace(char c, unsigned *index, char **line);
int				input_parse_end(char c, int *input_state, unsigned *index,
					char **line);
int				input_parse_next(char c, int *input_state, unsigned *index,
					char **line);
int				input_parse_prev(char c, int *input_state, unsigned *index,
					char **line);
int				input_parse_delete(char c, int *input_state, unsigned *index,
					char **line);
int				input_parse_ctrl_d(char c, unsigned *index, char **line);
int				input_parse_ctrl_k(char c, unsigned *index, char **line);
int				input_parse_ctrl_up(char c, int *input_state, unsigned *index,
					char **line);
int				input_parse_ctrl_down(char c, int *input_state, unsigned *index,
					char **line);

/*
**----------------------------------shell---------------------------------------
*/

void			shell_display_prompt(void);
int				shell_dless_read_till_stop(char **heredoc, char *stop);
int				shell_dless_set_tk_val(t_tokenlst *probe, char **heredoc, char *stop);
int				shell_dless_input(t_tokenlst *token_lst);
int				shell_quote_checker(char **line);
char			shell_quote_checker_find_quote(char *line);
int				shell_start(t_envlst *envlst);

/*
**----------------------------------lexer---------------------------------------
*/

int				lexer_tokenlstaddback(t_tokenlst **token_lst, t_tokens type,
					char *value, int flags);
t_tokenlst		*lexer_tokenlstnew(t_tokens type, char *value, int flags);
void			lexer_tokenlstdel(t_tokenlst **token_lst);
void			lexer_tokenlstiter(t_tokenlst *token_lst,
					void (*f)(t_tokenlst *elem));
bool			lexer_is_shellspec(char c);

int				lexer(char **line, t_tokenlst **token_lst);
int				lexer_error(t_tokenlst **token_lst, char **line);
void			lexer_evaluator(t_tokenlst *token_lst);
int				lexer_scanner(char *line, t_tokenlst *token_lst);

void			lexer_change_state(t_scanner *scanner,
					void (*lexer_state_x)(t_scanner *scanner));
void			lexer_state_start(t_scanner *scanner);
void			lexer_state_pipe(t_scanner *scanner);
void			lexer_state_orif(t_scanner *scanner);
void			lexer_state_sgreat(t_scanner *scanner);
void			lexer_state_dgreat(t_scanner *scanner);
void			lexer_state_sless(t_scanner *scanner);
void			lexer_state_dless(t_scanner *scanner);
void			lexer_state_bg(t_scanner *scanner);
void			lexer_state_andif(t_scanner *scanner);
void			lexer_state_semicol(t_scanner *scanner);
void			lexer_state_newline(t_scanner *scanner);
void			lexer_state_squote(t_scanner *scanner);
void			lexer_state_dquote(t_scanner *scanner);
void			lexer_state_dquote_esc(t_scanner *scanner);
void			lexer_state_word(t_scanner *scanner);
void			lexer_state_word_esc(t_scanner *scanner);
void			lexer_state_lessand(t_scanner *scanner);
void			lexer_state_greatand(t_scanner *scanner);
void			lexer_state_ionum(t_scanner *scanner);

/*
**----------------------------------parser--------------------------------------
*/
int				parser_start(t_tokenlst **token_lst, t_ast **ast);
bool			parser_add_astnode(t_tokenlst **token_lst, t_ast **ast);
bool			parser_add_sibling(t_tokenlst **token_lst, t_ast **ast,
				bool (*parse_priority_x)(t_tokenlst **, t_ast **));
t_ast			*parser_new_node(t_tokenlst *token);
bool			parser_command(t_tokenlst **token_lst, t_ast **ast);
char			*parser_return_token_str(t_tokens type);
void			parser_astdel(t_ast **ast);
bool			parser_return_del(t_ast **ast);
bool			parser_io_redirect(t_tokenlst **token_lst, t_ast **ast);
bool			parser_cmd_param(t_tokenlst **token_lst, t_ast **cmd,
				t_ast **last_cmd_arg, t_ast **last_prefix);
bool			parser_cmd_suffix(t_tokenlst **token_lst, t_ast **cmd,
				t_ast **last_cmd_arg, t_ast **last_prefix);

/*
**----------------------------------builtins------------------------------------
*/

void			builtin_exit(char **args, int *exit_code);
void			builtin_echo(char **args, int *exit_code);
char			builtin_echo_set_flags(char **args, int *arg_i);
void			builtin_export(char **args, t_envlst *envlst, int *exit_code);
void			builtin_export_var_to_type(char *varname, t_envlst *envlst, int *exit_code, int type);
void			builtin_export_print(t_envlst *envlst, int flags);
void			builtin_export_args(char **args, t_envlst *envlst, int *exit_code, int i);
int				builtin_assign(char *arg, t_envlst *envlst, int *exit_code, int env_type);
int				builtin_assign_addexist(t_envlst *envlst, char *arg, char *var, int env_type);
int				builtin_assign_addnew(t_envlst *envlst, char *var, int env_type);
void			builtin_set(char **args, t_envlst *envlst, int *exit_code);
void			builtin_unset(char **args, t_envlst *envlst, int *exit_code);

/*
**---------------------------------tools----------------------------------------
*/

bool			tool_is_redirect_tk(t_tokens type);
bool			tools_is_char_escaped(char *line, int i);
int				tools_update_quote_status(char *line, int cur_index,
					char *quote);
bool			tool_is_redirect_tk(t_tokens type);
bool			tools_is_valid_identifier(char *str);
bool			tools_is_fdnumstr(char *str);
bool			tool_has_special(char c);
bool			tool_check_for_whitespace(char *str);

/*
**----------------------------------execution-----------------------------------
*/

void	exec_start(t_ast *ast, t_envlst *envlst, int *exit_code, int flags);
void	exec_cmd(char **args, t_envlst *envlst, int *exit_code);
bool	exec_builtin(char **args, t_envlst *envlst, int *exit_code);
bool	exec_external(char **args, t_envlst *envlst, int *exit_code);
char	*exec_find_binary(char *filename, t_envlst *envlst);
void	exec_quote_remove(t_ast *node);

/*
**------------------------------------redir-------------------------------------
*/

int			redir(t_ast *node, int *exit_code);
int			redir_output(t_ast *node, int *exit_code);
int			redir_input(t_ast *node, int *exit_code);
bool		redir_is_open_fd(int fd);
int			redir_input_closefd(int left_side_fd, int *exit_code);
void		redir_change_if_leftside(t_ast *node, int *left_side_fd,
char **right_side);
int			redir_create_heredoc_fd(char *right_side, int *exit_code);


/*
**--------------------------------error_handling--------------------------------
*/

int			error_return(int ret, int error, int *exit_code, char *opt_str);

/*
**----------------------------------debugging-----------------------------------
*/

void			print_node(t_tokenlst *node);
void			print_tree(t_ast *root);
void			print_token(t_scanner *scanner);
void			print_tree(t_ast *root);

#endif
