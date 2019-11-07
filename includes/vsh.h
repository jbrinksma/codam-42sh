/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/07 14:26:10 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSH_H
# define VSH_H

# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

# define SHELL				"vsh"
# define SEPERATOR			">"
# define PROMPT_NAME		SHELL " "
# define PROMPT_SEPERATOR	SEPERATOR " "
# define HIST_SRCH_FIRST	"(reverse-i-search)`"
# define HIST_SRCH_LAST		"': "
# define FUNCT_FAILURE 0
# define FUNCT_SUCCESS 1
# define NEW_PROMPT 2
# define FUNCT_ERROR -1
# define PROG_FAILURE 1
# define PROG_SUCCESS 0
# define IR_EOF 3
# define SHELL_BUF			42
# define U_ALIAS			"alias: usage: alias [-p] [name[=value] ... ]\n"
# define U_CD				"cd: usage: cd [-L|-P] [dir]\n"
# define U_EXPORT "export: usage: export [-n] [name[=value] ...] or export -p\n"
# define U_HASH				"hash: usage: hash [-r] [utility ...]\n"
# define U_UNALIAS			"unalias: usage: unalias [-a] name [name ...]\n"
# define U_SET				"set: usage: set\n"
# define E_SYNTAX_P			SHELL ": syntax error near unexpected token '%s'\n"
# define E_P_NOT_VAL_HERE	SHELL ": '%s' is not a valid heredoc delimiter\n"
# define E_P_BAD_FD			SHELL ": %s: bad file descriptor\n"
# define E_BAD_FD			SHELL ": %i: bad file descriptor\n"
# define E_FAIL_DUP_FD		SHELL ": failed to duplicate file descriptor\n"
# define E_FD_CLOSE			SHELL ": failed to close file descriptor\n"
# define E_FD_RESET_STD	   SHELL ": failed to reset standard file descriptors\n"
# define E_NO_PERM_NO_SUCH	SHELL ": no perm / no such file or directory\n"
# define E_NO_SUCH_P		SHELL ": no such file or directory: %s\n"
# define E_P_IS_DIR			SHELL ": %s: is a directory\n"
# define E_P_BAD_SUBS		SHELL ": %.*s: bad substitution\n"
# define E_P_CMD_NOT_FOUND	SHELL ": %s: command not found.\n"
# define E_FAIL_OPEN_P		SHELL ": failed to open/create %s\n"
# define E_FAIL_OPEN		SHELL ": failed to open file\n"
# define E_ISDIR			SHELL ": %s: is a directory\n"
# define E_FAIL_EXEC_P		SHELL ": failed to execute %s\n"
# define E_NO_PIPE			SHELL ": unable to create pipe\n"
# define E_P_BAD_REDIR		SHELL ": %s: bad redirect\n"
# define E_N_P_INV_OPT		SHELL ": %s: -%c: invalid option\n"
# define E_ALLOC_STR		SHELL ": failed to allocate enough memory\n"
# define E_N_ALLOC_STR		SHELL ": %s: failed to allocate enough memory\n"
# define E_N_PER_DEN		SHELL ": %s: permission denied\n"
# define E_N_PER_DEN_P		SHELL ": %s: permission denied: %s\n"
# define E_N_P_NOT_FOUND	SHELL ": %s: %s: not found\n"
# define E_N_P_NUM_REQ		SHELL ": %s: %s: numeric argument required\n"
# define E_N_TOO_MANY		SHELL ": %s: too many arguments\n"
# define E_N_P_NOT_VAL_ID	SHELL ": %s: '%s': not a valid identifier\n"
# define E_N_FAIL_HOME		SHELL ": %s: failed to get home directory\n"
# define E_FAIL_HOME		SHELL ": failed to get home directory\n"
# define E_NOT_CUR_DIR		SHELL ": cannot get current working directory\n"
# define E_NOT_RESET		SHELL ": could not reset terminal settings\n"
# define E_STAT_STR			SHELL ": could not get stat info of file\n"
# define E_STAT_P			SHELL ": could not get stat info of %s\n"
# define E_ALLOC_STR		SHELL ": failed to allocate enough memory\n"
# define E_READ_FILE_STR	SHELL ": failed to read file\n"
# define E_READ_STR			SHELL ": failed to read input\n"
# define E_FORK_STR			SHELL ": fork failed\n"
# define E_HOME_NOTSET_STR 	SHELL ": environment value HOME not set\n"
# define E_HIST_READ_STR 	SHELL ": failed to read history file\n"
# define E_READ_STDIN_STR 	SHELL ": failed to read stdin\n"
# define E_HIST_OPEN_STR 	SHELL ": failed to open / create history file\n"
# define E_ALIAS_OPEN_STR 	SHELL ": failed to open alias file\n"
# define E_ALIAS_READ_STR	SHELL ": failed to read alias file\n"
# define E_ALIAS_INV_NAME	SHELL ": alias: '%.*s': invalid alias name\n"
# define E_CD_CNG_DIR SHELL ": cd: cannot get current working directory: %s\n"
# define E_CD_NO_SUCH		SHELL ": cd: no such file or directory: %s\n"
# define E_CD_NOT_DIR		SHELL ": cd: not a directory: %s\n"
# define E_CD_P_NOT_SET		SHELL ": cd: %s: not set\n"
# define E_TERM_CNT_GET		SHELL ": couldn't get terminal attributes.\n"
# define E_TERM_CNT_SET		SHELL ": couldn't set terminal attributes.\n"
# define E_TERM_NOT_SET		SHELL ": term environment variable not set.\n"
# define E_TERM_DB_NOT_F	SHELL ": terminfo database could not be found.\n"
# define E_TERM_NO_SUCH		SHELL ": no such TERM entry in the database\n"
# define E_STDIN_NOT_TTY	SHELL ": STDIN does not refer to a terminal\n"
# define E_TERM_INIT		SHELL ": term init failed\n"
# define E_BINARY_FILE		SHELL ": cannot execute binary file\n"
# define E_HIST_NOT_FOUND   "\n" SHELL ": !%s: event not found\n"
# define E_HIST_NUM_ERROR   "\n" SHELL ": %.*s: event not found\n"
# define E_BAD_PATTERN		SHELL ": bad pattern: %s\n"
# define E_OPEN_DIR			SHELL ": error opening directory: %s\n"
# define E_INVALID_USER		SHELL ": could not get working directory of: %s\n"
# define E_BG_INV_OPT		SHELL ": bg: %c: invalid option\n"
# define E_BG_USAGE			E_BG_INV_OPT "bg: usage: bg [job_spec ...]\n"
# define E_BG_NO_CUR		"bg: no current job\n"
# define E_BG_JOB_RUN		SHELL ": bg: job %s already running\n"
# define E_FG_INV_OPT		SHELL ": fg: %c: invalid option\n"
# define E_FG_USAGE			E_FG_INV_OPT "fg: usage: fg [job_spec ...]\n"
# define E_FG_NO_CUR		"fg: no current job\n"
# define E_J_I_OPT			SHELL ": jobs: bad option: %c\n"
# define E_JOBS_USAGE		E_J_I_OPT "jobs: usage: jobs [-lp] [job_spec ...]\n"
# define E_JOBS_NO_JOB		"jobs: %s: no such job\n"
# define E_BIN_PROC_LAUNCH	"Error executing %s\n"
# define E_JOB_MARK_SIG		"%d: Terminated by signal %d\n"
# define E_ALLOC 42
# define E_DUP 100
# define E_OPEN 101
# define E_BADFD 102
# define E_CLOSE 103
# define E_BADRED 104
# define CTRLD -1
# define CR 0
# define UNINIT -1
# define RESET_CLEAR_LINE	"\e[2K\e[0E"

/*
**=================================exit codes===================================
*/

# define EXIT_WRONG_USE 2
# define EXIT_NOT_EXECUTABLE 126
# define EXIT_NOTFOUND 127
# define EXIT_FATAL 128

/*
**================================shell colors==================================
*/

# define RESET				"\e[0m"
# define RED				"\e[1;31m"
# define YEL				"\e[1;33m"
# define BLU				"\e[1;36m"
# define WHITE_BG			"\e[47m"
# define BLACK				"\e[30m"
# define WHITE_BG_BLACK		"\e[47;30m"

/*
**------------------------------------shell-------------------------------------
*/

# define SHELL_NON_INTERACT	0
# define SHELL_INTERACT		1

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
**-----------------------------------autocomplete-------------------------------
*/

# define STATE_CMD			(1 << 0)
# define STATE_VAR			(1 << 1)
# define STATE_FILE			(1 << 2)
# define AUTO_NO_MATCHES	(1 << 2)
# define AUTO_ADDED_MATCH	(1 << 3)

/*
**-----------------------------------alias--------------------------------------
*/

# define ALIAS_FLAG_LP		(1 << 0)
# define UNALIAS_FLAG_LA	(2 << 0)
# define ALIASFILENAME		".vsh_alias"
# define ALIAS_MAX	500

/*
**-----------------------------------hash--------------------------------------
*/

# define HT_SIZE			100
# define HT_EMPTY			0
# define HT_HAS_CONTENT		1
# define HASH_LR			(1 << 0)
# define HASH_HIT			1
# define HASH_NO_HIT		0

/*
**-----------------------------------fc-----------------------------------------
*/

# define DEF_FCEDIT			"ed"
# define FC_OPT_E			(1 << 0)
# define FC_OPT_L			(1 << 1)
# define FC_OPT_N			(1 << 2)
# define FC_OPT_R			(1 << 3)
# define FC_OPT_S			(1 << 4)
# define FC_FIRST_NEG		(1 << 5)
# define FC_LAST_NEG		(1 << 6)
# define FC_PRINT_CMD		(1 << 0)
# define FC_SET_HIST		(1 << 1)
# define FC_TMP_FILE		"/tmp/vsh-fc-tmp"
# define U_FC_2				"[-nlr] [first] [last] or fc -s [pat=rep] [cmd]\n"
# define U_FC 				"fc: usage: fc [-e ename] " U_FC_2
# define E_FC_REQARG		SHELL "fc: %s: option requires an argument\n"
# define E_FC_INV_OPT		SHELL ": fc: -%c: invalid option\n"
# define E_FC_OUT_RANGE		SHELL ": fc: history specification out of range\n"
# define E_FC_F_OPEN		SHELL ": fc: failed to open temporary file\n"

/*
**===============================personal headers===============================
*/

# include "libft.h"

/*
**==================================headers=====================================
*/

# include <stdbool.h>

typedef struct	s_fcdata
{
	char	options;
	char	*first;
	char	*last;
	char	*editor;
	char	*replace;
	char	*tmpfile;
	int		fd;
}				t_fcdata;

/*
**-----------------------------------builtin------------------------------------
*/

# define BUILTIN_CD_UL		(1 << 0)
# define BUILTIN_CD_UP		(2 << 0)

/*
**------------------------------------lexer-------------------------------------
*/

# define NO_FLAGS 0
# define CURRENT_CHAR (scanner->str)[scanner->str_index]
# define SCANNER_CHAR scanner.str[scanner.str_index]
# define T_FLAG_HASSPECIAL (1 << 0)
# define T_STATE_SQUOTE (1 << 1)
# define T_STATE_DQUOTE (1 << 2)
# define T_FLAG_ISASSIGN (1 << 3)
# define T_MALLOC_ERROR (1 << 4)
# define T_FLAG_HEREDOC_NOEXP (1 << 5)
# define T_FLAG_ISHEREDOC (1 << 6)

/*
**-----------------------------------executor-----------------------------------
*/

# define EXEC_PIPE (1 << 0)
# define EXEC_BG (1 << 1)
# define EXEC_AND_IF (1 << 2)
# define EXEC_OR_IF (1 << 3)
# define EXEC_SEMICOL (1 << 4)
# define EXEC_WAIT (1 << 5)

/*
**--------------------------------redirections----------------------------------
*/

# define FD_UNINIT				-1
# define REG_PERM				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define SGREAT_OPEN_FLAGS		O_WRONLY | O_CREAT | O_TRUNC
# define DGREAT_OPEN_FLAGS		O_WRONLY | O_CREAT | O_APPEND

/*
**---------------------------------environment----------------------------------
*/

# define ENV_MASK 0xF8
# define ENV_TMP_OVERWRITE (1 << 4)
# define ENV_SPECIAL (1 << 3)
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

# define INPUT_BACKSPACE	127
# define TERMCAPBUFFSIZE 12
# define TC_UP_ARROW "\e[A"
# define TC_CTRL_UP_ARROW "\e[1;5A"
# define TC_DOWN_ARROW "\e[B"
# define TC_CTRL_DOWN_ARROW "\e[1;5B"
# define TC_LEFT_ARROW "\e[D"
# define TC_CTRL_LEFT_ARROW "\e[1;5D"
# define TC_RIGHT_ARROW "\e[C"
# define TC_CTRL_RIGHT_ARROW "\e[1;5C"
# define TC_GETCURSORPOS "\e[6n"
# define TC_HOME "\e[H"
# define TC_END "\e[F"
# define TC_DELETE "\e[3~"
# define CURS_LEFT "\e[D"
# define CURS_RIGHT "\e[C"
# define CURS_UP "\e[A"
# define CURS_DOWN "\e[B"
# define INPUT_CTRL_A '\1'
# define INPUT_CTRL_C '\3'
# define INPUT_CTRL_D '\4'
# define INPUT_CTRL_E '\5'
# define INPUT_CTRL_K '\v'
# define INPUT_TAB '\t'
# define INPUT_CTRL_R 18
# define INPUT_CTRL_U 21
# define INPUT_CTRL_Y 25
# define INPUT_ESC 27
# define TC_MAXRESPONSESIZE 42
# define INPUT_BUF_READ_SIZE 100

/*
**=================================pipe defines=================================
*/

# define PIPE_UNINIT	-42
# define PIPE_START		0
# define PIPE_EXTEND	1
# define PIPE_READ		0
# define PIPE_WRITE		1

/*
**----------------------------------history-------------------------------------
*/

# define POSIX_WRAPPER 	32767
# define DEF_HISTSIZE	500
# define ARROW_UP	    1
# define ARROW_DOWN	    2
# define HISTFILENAME	".vsh_history"
# define HIST_SEPARATE	-1
# define HIST_EXPANDED	(1 << 2)

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
	bool			is_expanded;
	t_tokens		type;
	char			flags;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

/*
**=================================typedefs====================================
*/

typedef struct	s_state
{
	pid_t		pid;
	int			exit_code;
	int			shell_type;
}				t_state;

t_state *g_state;

/*
**---------------------------------environment----------------------------------
*/

typedef struct	s_envlst
{
	char			*var;
	unsigned char	type;
	struct s_envlst	*next;
}				t_envlst;

/*
**-----------------------------------history------------------------------------
*/

typedef struct	s_historyitem
{
	int						number;
	char					*str;
	struct s_historyitem	*prev;
	struct s_historyitem	*next;
}				t_historyitem;

/*
**------------------------------------alias-------------------------------------
*/

typedef struct	s_aliaslst
{
	char				*var;
	struct s_aliaslst	*next;
}				t_aliaslst;

/*
**------------------------------------hashtable---------------------------------
*/

typedef struct	s_ht
{
	char			*key;
	char			*path;
	int				hits;
	struct s_ht		*next;
}				t_ht;

/*
**-----------------------------------term---------------------------------------
*/

typedef struct termios	t_termios;

/*
**-----------------------------------jobs---------------------------------------
*/

# define JOB_EXIT		0
# define JOB_RUNNING	1
# define JOB_SUSPEND	2

# define JOB_OPT_NONE	0
# define JOB_OPT_P		1
# define JOB_OPT_L		2

typedef enum			e_proc_state
{
	PROC_COMPLETED,
	PROC_STOPPED,
	PROC_CONTINUED,
	PROC_RUNNING
}						t_proc_state;

typedef enum			e_andor
{
	ANDOR_NONE,
	ANDOR_AND,
	ANDOR_OR
}						t_andor;

typedef struct	s_proc
{
	pid_t			pid;
	struct s_proc	*next;
	t_proc_state	state;
	int				exit_status;

	char			**env;
	char			**argv;
	char			*binary;

	bool			is_builtin;
	bool			no_cmd;
	t_ast			*redir_and_assign;
	t_ast			*node;
}				t_proc;

typedef struct	s_job
{
	bool			bg;
	pid_t			pgid;
	int				state;
	struct s_job	*next;
	t_andor			andor;
	struct s_job	*child;
	int				job_id;
	int				current;
	char			*command;
	t_proc			*processes;
	t_proc			*last_proc;
}				t_job;

/*
**-----------------------------------vsh_data-----------------------------------
*/

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_datatermcaps
{
	char	*tc_clear_lines_str;
	char	*tc_scroll_down_str;
}				t_datatermcaps;

typedef struct	s_vshdataterm
{
	t_termios	*old_termios_p;
	t_termios	*termios_p;
}				t_vshdataterm;

typedef struct	s_datacurs
{
	t_point	coords;
	int		cur_ws_col;
	int		cur_ws_row;
	int		cur_relative_y;
}				t_datacurs;

typedef struct	s_datahistory
{
	t_historyitem	*head;
	t_historyitem	*tail;
	t_historyitem	*current;
	int				count;
}				t_datahistory;

typedef struct	s_dataline
{
	char		*line;
	char		*line_copy;
	char		*buffer;
	unsigned	buffer_i;
	unsigned	index;
	unsigned	len_max;
	unsigned	len_cur;
}				t_dataline;

typedef struct	s_dataprompt
{
	char	*prompt_name;
	char	*prompt_seperator;
	char	*prompt_addition;
	int		prompt_len;
	int		cur_prompt_type;
}				t_dataprompt;

typedef struct	s_searchhistory
{
	bool			active;
	char			*search_str;
	char			*result_str;
	size_t			result_i;
	size_t			total_len;
	t_historyitem	*current;
}				t_searchhistory;

typedef struct	s_datainput
{
	char			c;
	t_searchhistory	searchhistory;
}				t_datainput;

typedef struct	s_datahashtable
{
	t_ht	*ht[HT_SIZE];
	char	ht_flag;
}				t_datahashtable;

typedef	struct	s_dataalias
{
	t_aliaslst	*aliaslst;
	char		*alias_file;
}				t_dataalias;

typedef struct	s_vshdatajobs
{
	t_job		*joblist;
	int			current_job;
	t_job		*active_job;
}				t_datajobs;

# define EXEC_ISPIPED	(1 << 0)
# define PID_STATE_EXIT		0
# define PID_STATE_RUNNING	1
# define PID_STATE_SUSPEND	2

typedef struct	s_vshdata
{
	t_envlst		*envlst;
	int				term_fd;
	t_vshdataterm	*term;
	t_datacurs		*curs;
	t_datahistory	*history;
	t_dataline		*line;
	t_dataprompt	*prompt;
	t_datainput		*input;
	t_datahashtable	*hashtable;
	t_dataalias		*alias;
	t_datatermcaps	*termcaps;
	t_datajobs		*jobs;
	t_ast			*cur_node;
	int				fc_flags;
	int				exec_flags;
}				t_vshdata;

t_vshdata		*g_data;

typedef enum	e_prompt_type
{
	REGULAR_PROMPT,
	LINECONT_PROMPT,
	QUOTE_PROMPT,
	DQUOTE_PROMPT,
	DLESS_PROMPT,
	HISTSEARCH_PROMPT
}				t_prompt_type;

/*
**----------------------------------autocomplete--------------------------------
*/

typedef struct	s_print
{
	int	row;
	int	length;
	int	coli;
	int	total;
	int	printed;
	int	extra;
	int	col;
	int	left;
}				t_print;

/*
**----------------------------------pipes---------------------------------------
*/

typedef struct	s_pipes
{
	int			pipeside;
	int			parentpipe[2];
	int			currentpipe[2];
}				t_pipes;

/*
**---------------------------------environment----------------------------------
*/

char			*env_getvalue(char *var_key, t_envlst *envlst);
char			**env_free_and_return_null(char ***vshenviron);
t_envlst		*env_getlst(void);
void			env_lstaddback(t_envlst **lst, t_envlst *new);
t_envlst		*env_lstnew(char *var, unsigned char type);
char			**env_lsttoarr(t_envlst *lst);
int				env_lstlen(t_envlst *lst);
void			env_lstdel(t_envlst **envlst);
void			env_remove_tmp(t_envlst *env);
void			env_sort(t_envlst *head);
void			env_lstadd_to_sortlst(t_envlst *envlst, t_envlst *new);
int				env_add_extern_value(t_vshdata *data, char *name, char *value);
int				env_init_envlst(t_vshdata *vshdata);

/*
**----------------------------------terminal------------------------------------
*/

t_vshdataterm	*term_prepare(t_envlst *lst);
int				term_is_valid(t_envlst *envlst);
t_vshdataterm	*term_init_struct(void);
int				term_get_attributes(int fd, t_vshdataterm*term_p);
int				term_set_attributes(t_vshdataterm*term_p);
int				term_reset(t_vshdataterm*term_p);
void			term_free_struct(t_vshdataterm**term_p);
void			term_enable_isig(t_termios *termios_p);
void			term_disable_isig(t_termios *termios_p);

/*
**-----------------------------------input--------------------------------------
*/

int				input_read(t_vshdata *data);
int				input_read_ansi(t_vshdata *data);
int				input_parse_special(t_vshdata *data);
int				input_is_word_start(char *str, int i1, int i2);
void			input_clear_char_at(char **line, unsigned index);
int				input_parse_char(t_vshdata *data);
void			input_print_str(t_vshdata *data, char *str);
int				ft_tputchar(int c);
int				tools_isprintnotblank(int i);
int				input_handle_backspace(t_vshdata *data);
void			input_handle_delete(t_vshdata *data);
void			curs_move_left(t_vshdata *data);
void			curs_move_n_left(t_vshdata *data, size_t n);
void			curs_move_n_left_hasnewlines(t_vshdata *data, size_t n);
void			curs_move_right(t_vshdata *data);
void			curs_move_n_right(t_vshdata *data, size_t n);
void			curs_move_n_right_hasnewlines(t_vshdata *data, size_t n);
void			curs_move_right_at_colmax(t_vshdata *data, int colmax);
void			curs_move_up(t_vshdata *data);
void			curs_move_down(t_vshdata *data);
void			curs_go_home(t_vshdata *data);
void			curs_go_end(t_vshdata *data);
void			curs_move_next_word(t_vshdata *data);
void			curs_move_prev_word(t_vshdata *data);
int				input_parse_ctrl_c(t_vshdata *data);
int				input_parse_ctrl_d(t_vshdata *data);
void			input_parse_ctrl_k(t_vshdata *data);
void			input_parse_ctrl_u(t_vshdata *data);
void			input_parse_ctrl_y(t_vshdata *data);
void			input_parse_tab(t_vshdata *data);
int				input_get_curs_row(void);
void			input_reset_cursor_pos(void);
void			resize_window_check(int sig);
int				input_add_chunk(t_vshdata *data, char *chunk,
				int chunk_len);
int				input_empty_buffer(t_vshdata *data, int n);
int				input_read_from_buffer(t_vshdata *data);
int				input_parse_ctrl_r(t_vshdata *data);
int				input_parse_esc(t_vshdata *data);
int				ctrlr_clear_line(t_vshdata *data);
void			ctrlr_restore_shell(t_vshdata *data);
void			input_print_ctrl_r(t_vshdata *data, char *first, char *second,
				int second_i);
int				input_parse_char_og(t_vshdata *data);

/*
**----------------------------------jobs----------------------------------------
*/

t_job			*jobs_remove_job(t_job **joblist, pid_t pid);
t_job			*jobs_add_job(t_vshdata *data, t_job *job);
t_job			*jobs_new_job(void);
t_job			*jobs_last_child(t_job *job);
void			jobs_flush_job(t_job *job);

void			jobs_continue_job(t_job *job, bool fg);
int				jobs_wait_job(t_job *job, int wait_opt);
void			jobs_bg_job(t_job *job, bool job_continued);
int				jobs_fg_job(t_job *job, bool job_continued);

void			jobs_print_job_info(t_job *job, int options, t_job *joblist);

t_job			*jobs_find_current_job(t_job *joblist);
t_job			*jobs_find_previous_job(t_job *joblist);
t_job			*jobs_find_job(char *job_id, t_job *joblist);

int				jobs_add_process(t_job *job);
int				jobs_exit_status(t_job *job);

int				jobs_stopped_job(t_job *job);
int				jobs_completed_job(t_job *job);
void			jobs_finished_job(t_job *job, bool flush);

void			jobs_notify_pool(void);
void			jobs_update_pool_status(void);

int				jobs_update_job_command(t_job *job, char **av);
void			jobs_flush_process(t_proc *proc);
void			jobs_launch_job(t_job *job);
void			jobs_launch_proc(t_job *job, t_proc *proc,
					int fds[3], int pipes[2]);
void			jobs_exec_builtin(t_proc *proc);
int				jobs_exec_is_single_builtin_proc(t_proc *proc);

void			jobs_force_job_state(t_job *job, t_proc_state state);
void			jobs_launch_cleanup_after_proc(t_proc *proc, int fds[3],
					int pipes[2]);
void			jobs_launch_setup_stds(t_proc *proc, int fds[3], int pipes[2]);
int				jobs_launch_forked_job(t_job *job, int fds[3], int pipes[2]);
int				jobs_mark_process_status(pid_t pid, int status);

/*
**----------------------------------shell---------------------------------------
*/

void			shell_display_prompt(t_vshdata *data, int prompt_type);
int				shell_dless_read_till_stop(char **heredoc, char *stop,
					t_vshdata *data);
int				shell_dless_set_tk_val(t_tokenlst *probe, char **heredoc,
					char *stop, t_vshdata *data);
int				shell_dless_input(t_vshdata *data, t_tokenlst **token_lst);
int				shell_close_unclosed_quotes(t_vshdata *data);
int				shell_init_files(t_vshdata *data);
void			shell_start(t_vshdata *data);
t_vshdata		*shell_init_vshdata(void);
char			*shell_getcurrentdir(char *cwd);
int				shell_close_quote_and_esc(t_vshdata *data);
char			shell_quote_checker_find_quote(char *line);
int				shell_handle_escaped_newlines(t_vshdata *data);
void			shell_get_valid_prompt(t_vshdata *data, int prompt_type);
int				shell_init_term(t_vshdata *data);
void			shell_args(t_vshdata *data, char *filepath);
int				shell_get_path(t_vshdata *data, char *filepath, char **path);
int				shell_init_line(t_vshdata *data, char *filepath);
int				shell_one_line(t_vshdata *data, char *line);
void			shell_stdin(t_vshdata *data);
void			shell_clear_input_data(char **line, t_ast **ast,
				t_tokenlst **token_lst);
char			**shell_line_splitter(t_vshdata *data);
void			shell_lines_exec(t_vshdata *data, char **lines);
int				shell_split_line(char *line, char **lines);

t_datatermcaps	*shell_init_vshdatatermcaps(void);
t_dataalias		*shell_init_vshdataalias(void);
t_datahistory	*shell_init_vshdatahistory(void);
t_datahashtable	*shell_init_vshdatahashtable(void);
t_datainput		*shell_init_vshdatainput(void);
t_dataprompt	*shell_init_vshdataprompt(void);
t_dataline		*shell_init_vshdataline(void);
t_datacurs		*shell_init_vshdatacurs(void);
t_datajobs		*shell_init_vshdatajobs(void);

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
int				lexer_error(char **line);
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
**----------------------------------alias---------------------------------------
*/

int				alias_expansion(t_vshdata *data, t_tokenlst **tokenlst,
				char **expanded_aliases);
int				alias_replace(t_vshdata *data, t_tokenlst *probe, char *alias,
				char **expanded_aliases);
int				alias_error(char **line, t_tokenlst **tokenlst,
				char ***expanded);
int				alias_read_file(t_vshdata *data);
char			**alias_add_expanded(char **expanded, char *alias,
				char *alias_equal);
char			*alias_getvalue(char *var_key, t_aliaslst *aliaslst);

/*
**----------------------------------parser--------------------------------------
*/
int				parser_start(t_tokenlst **token_lst, t_ast **ast);
bool			parser_add_astnode(t_tokenlst **token_lst, t_ast **ast);
bool			parser_add_right(t_tokenlst **token_lst, t_ast **ast,
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

void			builtin_hash(char **args, t_vshdata *data);
void			builtin_exit(char **args, t_vshdata *data);
void			builtin_echo(char **args);
char			builtin_echo_set_flags(char **args, int *arg_i);
void			builtin_export(char **args, t_vshdata *data);
void			builtin_export_var_to_type(char *varname,
				t_envlst *envlst, int type);
void			builtin_export_print(t_envlst *envlst, int flags);
void			builtin_export_args(char **args, t_vshdata *data, int i);
int				builtin_assign(char *arg, t_vshdata *data, int env_type);
int				builtin_assign_addexist(t_envlst *envlst,
				char *var, int env_type);
int				builtin_assign_addnew(t_envlst *envlst,
				char *var, int env_type);
void			builtin_set(char **args, t_envlst *envlst);
void			builtin_unset(char **args, t_envlst *envlst);
void			builtin_alias(char **args, t_aliaslst **aliaslst);
int				builtin_alias_set(char *arg, t_aliaslst **aliaslst);
void			builtin_alias_delnode(t_aliaslst **node);
void			builtin_alias_lstdel(t_aliaslst **lst);
void			builtin_unalias(char **args, t_aliaslst **aliaslst);
void			builtin_type(char **args, t_envlst *envlst,
				t_aliaslst *aliaslst);

void			builtin_jobs(char **args, t_vshdata *data);
int				builtin_jobs_new_current_val(t_job *joblist);

void			builtin_fg(char **args, t_vshdata *data);
void			builtin_bg(char **av, t_vshdata *data);

void			builtin_cd(char **args, t_vshdata *data);
void			builtin_cd_create_newpath(char **newpath, char *argpath);
int				builtin_cd_change_dir(char *argpath, t_vshdata *data,
					char cd_flag, int print);
char			*builtin_cd_create_newpath_wrap(char *currpath, char *argpath);
int				cd_print_usage(void);
int				cd_change_dir_error(char *realpath, char *argpath,
					char **newpath, char **currpath);
int				cd_alloc_error(void);
int				cd_invalid_option(char c);

/*
**----------------------------------builtin-fc----------------------------------
*/

void			builtin_fc(char **args, t_vshdata *data);
void			fc_init_fcdata(t_fcdata **fc);
void			fc_set_default_editor(t_vshdata *data, t_fcdata *fc);
int				fc_set_options(char **args, t_fcdata *fc);
int				fc_option_editor(int i, char **args, t_fcdata *fc);
void			fc_option_list(t_fcdata *fc);
int				fc_option_substitute(int i, char **args, t_fcdata *fc);
void			fc_option_suppress(t_fcdata *fc);
void			fc_option_reverse(t_fcdata *fc);
void			fc_list(t_datahistory *history, t_fcdata *fc);
int				fc_list_print_line(t_historyitem *item, t_fcdata *fc);
void			fc_print_regular(t_historyitem *start, int len, t_fcdata *fc);
void			fc_print_reverse(t_historyitem *start, int len, t_fcdata *fc);
int				fc_find_item(t_datahistory *history, t_fcdata *fc,
				char *str, t_historyitem **item);
void			fc_substitute(t_vshdata *data, t_datahistory *history,
				t_fcdata *fc);
int				fc_get_start(t_datahistory *history, t_fcdata *fc,
				t_historyitem **start, int *len);
void			fc_print(t_fcdata *fc, t_historyitem *start, int len);
void			fc_edit(t_vshdata *data, t_datahistory *history, t_fcdata *fc);

/*
**---------------------------------tools----------------------------------------
*/

bool			tools_is_redirect_tk(t_tokens type);
bool			tools_is_char_escaped(char *line, int i);
bool			tools_is_identifier_char(char c);
bool			tools_is_valid_identifier(char *str);
bool			tools_is_builtin(char *exec_name);
bool			tools_is_fdnumstr(char *str);
bool			tools_is_special(char c);
bool			tools_check_for_special(char *str);
bool			tools_check_for_whitespace(char *str);
int				tools_get_paths(t_envlst *envlst, char ***paths);
void			tools_remove_quotes_etc(char *str, bool is_heredoc);
bool			tools_contains_quoted_chars(char *str);
bool			tools_is_cmd_seperator(t_tokens type);
bool			tools_is_valid_name(char *str);
bool			tools_is_valid_name_char(char c);

/*
**----------------------------------execution-----------------------------------
*/

int				exec_complete_command(t_ast *ast, t_vshdata *data);
int				exec_list(t_ast *ast, t_vshdata *data);
int				exec_and_or(t_ast *ast, t_vshdata *data);
int				exec_pipe_sequence(t_ast *ast, t_vshdata *data);
int				exec_command(t_ast *ast, t_vshdata *g_data);
void			exec_cmd(t_vshdata *data);
bool			exec_builtin(char **args, t_proc *proc);
void			exec_external(char **args, t_vshdata *data, t_proc *proc);
int				exec_find_binary(char *filename, t_vshdata *data,
				char **binary);
int				find_binary(char *filename, t_envlst *envlst, char **binary);
void			exec_quote_remove(t_ast *node);
int				exec_validate_binary(char *binary);
int				exec_create_files(t_ast *ast);
int				exec_redirs(t_ast *redirs);
int				exec_assigns(t_ast *ast, t_vshdata *data, int env_type);
char			**exec_create_process_args(t_ast *ast);
bool			exec_command_contains_only_assign(t_ast *ast);

/*
**-----------------------------------signals------------------------------------
*/

void			signal_reset(void);

/*
**------------------------------------expan-------------------------------------
*/

int				expan_handle_variables(t_ast *node, t_envlst *envlst);
int				expan_handle_bracketed_var(char **value, int *i,
				t_envlst *envlst);
int				expan_handle_dollar(char **value, int *i, t_envlst *envlst);
int				expan_tilde_expansion(t_ast *node, int *i);
int				expan_var_error_print(char *str, int len);
int				expan_pathname(t_ast *ast);

/*
**------------------------------------redir-------------------------------------
*/

int				redir(t_ast *node);
int				redir_output(t_ast *node);
int				redir_input(t_ast *node);
bool			redir_is_open_fd(int fd);
int				redir_input_closefd(int left_side_fd);
void			redir_change_if_leftside(t_ast *node, int *left_side_fd,
					char **right_side);
int				redir_create_heredoc_fd(char *right_side);

t_pipes			redir_init_pipestruct(void);
int				redir_pipe(t_ast *pipe_node);
int				redir_run_pipesequence(t_ast *pipenode, t_vshdata *data,
					t_pipes pipes);
int				redir_handle_pipe(t_pipes pipes);

/*
**------------------------------------history-----------------------------------
*/

int				history_to_file(t_datahistory *history);
int				history_get_file_content(t_datahistory *history);
int				history_get_histsize(void);
void			history_print(t_datahistory *history);
char			*history_get_filename(void);

int				history_add_item(t_datahistory *history, char *line);
void			history_remove_tail(t_datahistory *history);
void			history_remove_head(t_datahistory *history);

int				history_change_line(t_vshdata *data, char arrow);
int				history_index_change_down(t_datahistory *history);
int				history_index_change_up(t_datahistory *history);
int				history_expansion(t_vshdata *data);
char			*history_get_line(t_datahistory *history, char *line, size_t i);
char			*history_match_line(t_datahistory *history,
				char *line, size_t i);
int				history_insert_into_line(char **line,
				char *hist_line, size_t i);
size_t			history_get_match_len(char *line, size_t i);
int				history_count(t_historyitem *start, t_historyitem *end);
void			history_free_item(t_historyitem **item);
int				history_ctrl_r(t_vshdata *data, bool second);

/*
**--------------------------------hashtable-------------------------------------
*/

int				hash_ht_insert(t_vshdata *data, char *key, char *path,
				int count);
void			hash_print(t_ht **ht);
void			hash_reset(t_vshdata *data);
unsigned int	hash_create_hash(char *key);
int				hash_check(t_vshdata *data, char *key, char **binary);

/*
**--------------------------------error_handling--------------------------------
*/

int				error_return(int ret, int error, char *opt_str);
int				err_ret_exit(char *str, int exitcode);
void			err_void_exit(char *str, int exitcode);
int				err_ret(char *str);
void			err_void_prog_exit(char *error, char *prog, int exitcode);
int				err_ret_prog_exit(char *str, char *prog, int exitcode);

/*
**--------------------------------autocomplete----------------------------------
*/

int				auto_get_cmdlst(char *match, t_envlst *envlst,
				t_list **matchlst);
int				auto_add_tolst(t_list **matchlst, char *filename);
int				auto_match_builtins(char *match, t_list **matchlst,
				int match_len);
int				auto_get_filelst(char *match, char **path, t_list **matchlst);
int				auto_get_varlst(char *match, int match_len, t_envlst *envlst,
				t_list **matchlst);
int				auto_find_state(char *line, ssize_t i);
void			auto_start(t_vshdata *data);
int				auto_add_match_to_line(char *match, char *to_add,
				t_vshdata *data);
int				auto_find_matches(t_vshdata *data, char **match,
				t_list **matchlst, int state);
void			auto_lstdel(void *str, size_t size);
int				auto_handle_matchlst(t_vshdata *data, char *match,
				t_list **matchlst);
int				auto_small_lst(char *match, t_list **matchlst,
				t_vshdata *data);
void			auto_lst_print(t_list **matchlst, int lst_len);
int				auto_big_lst(t_list **matchlst, int lst_len);
int				auto_lenname(t_list *matchlst, int length);
int				auto_lst_count(t_list *lst);
void			auto_sort_n(t_list **matchlst);
void			auto_swap_lstitem(t_list **flst, t_list *smal, t_list *prev);
bool			auto_check_dups(t_list *matchlst, char *filename);

/*
**----------------------------------globbing------------------------------------
*/

# define GLOB_CUR_CHAR	(scanner->word[scanner->word_index])
# define GLOB_F_NEG		(1 << 0)

typedef enum	e_globtokens
{
	GLOB_ERROR,
	GLOB_STR,
	GLOB_SLASH,
	GLOB_DOTSLASH,
	GLOB_DOTDOTSLASH,
	GLOB_WILD,
	GLOB_QUEST,
	GLOB_BRACENEG,
	GLOB_BRACEPOS,
}				t_globtokens;

typedef struct	s_globtokenlst
{
	t_globtokens			tk_type;
	char					*word_chunk;
	int						word_len;
	struct s_globtokenlst	*next;
}				t_globtoken;

typedef struct	s_globscanner
{
	t_globtokens			tk_type;
	int						tk_len;
	char					*word;
	int						word_index;
	int						flags;
	char					quote;
}				t_globscanner;

typedef struct	s_globmatchlst
{
	char					*word;
	int						index;
	int						word_len;
	struct s_globmatchlst	*next;
}				t_globmatchlst;

typedef struct	s_glob
{
	t_ast		*expanded;
	int			cwd_len;
}				t_glob;

int				glob_lexer(t_globtoken **lst, char *word);
void			glob_lexer_finish(t_globscanner *scanner, t_globtokens type);
void			glob_lexer_state_start(t_globscanner *scanner);
void			glob_lexer_state_bracket(t_globscanner *scanner);
void			glob_lexer_addchar(t_globscanner *scanner);
void			glob_lexer_changestate(t_globscanner *scanner,
					void (*state)(t_globscanner *scanner));
void			glob_tokenlstadd(t_globtoken **lst, t_globtoken *new);
t_globtoken		*glob_tokenlstnew(char *word_chunk, int type);
void			glob_del_tokenlst(t_globtoken **token);
int				glob_add_scanned_token(t_globtoken **lst,
				t_globscanner *scanner);
int				glob_matcher(t_globtoken *tokenprobe,
				t_globmatchlst match);
int				glob_match_lst_add(t_globmatchlst **lst, char *word);
int				glob_add_dotslash_to_path(t_globtoken **tokenlst, char **path);
void			glob_delmatch(t_globmatchlst **match);
int				glob_dir_match_loop(t_glob *glob_data, t_globtoken *tokenlst,
				char *path);
int				glob_ast_add_left(t_ast **ast, char *value,
				t_tokens type, char flags);
int				glob_keep_dirs(t_globmatchlst **matchlst, char *path);
void			glob_del_matchlst(t_globmatchlst **matchlst);
bool			glob_check_hidden_file(t_globtoken *tokenlst);
int				glob_delmatchlst_ret_err(t_globmatchlst **matchlst);
int				glob_expand_word(t_glob *glob_data, char *word);

/*
**----------------------------------debugging-----------------------------------
*/

void			print_node(t_tokenlst *node);
void			print_tree(t_ast *root);
void			print_token(t_scanner *scanner);
void			print_tree(t_ast *root);
void			print_token_list(t_tokenlst *node);
void			glob_print_tokenlist(t_globtoken *lst);
void			glob_print_matches(t_globmatchlst *lst);
void			glob_print_matchlist(t_globmatchlst *lst);

int				backup_stdfds(void);
int				reset_stdfds(void);

#endif
