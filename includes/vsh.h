/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 19:36:01 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSH_H
# define VSH_H

/*
**==================================defines=====================================
*/

# define FUNCT_FAILURE 0
# define FUNCT_SUCCESS 1
# define FUNCT_ERROR -1
# define E_ALLOC 420
# define CTRLD -1
# define CR 0

/*
**===============================personal headers===============================
*/

#include "libft.h"

/*
**==================================headers=====================================
*/

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>

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

# include <sys/param.h>

/*
**=================================structs======================================
*/

typedef struct	s_term
{
	struct termios	*old_termios_p;
	struct termios	*termios_p;
}				t_term;

/*
**=================================prototypes===================================
*/

/*
**	main.c
*/

int		term_reset(t_term *term_p);
void	term_free_termp(t_term *term_p);
int		shell_start(void);

/*
**---------------------------------environment----------------------------------
*/

/*
**	get_environ_cpy.c
*/

char	**get_environ_cpy(void);
char	*param_to_env(char *parameter, char **vshenviron);

/*
**----------------------------------terminal------------------------------------
*/

/*
**	term_init.c
*/

t_term	*term_prepare(char **vshenviron);
t_term	*term_return(t_term *term_p, int return_value);
int		term_is_valid(char **vshenviron);
t_term	*term_init_struct(void);
int		term_get_attributes(int fd, t_term *term_p);
int		term_set_attributes(t_term *term_p);
int		term_reset(t_term *term_p);
void	term_free_struct(t_term **term_p);

/*
**-----------------------------------input--------------------------------------
*/

/*
**	input_read.c
*/

int		input_read(char **line);
int		input_echo(char *buf);

/*
**----------------------------------shell---------------------------------------
*/

/*
**	shell_prompt.c
*/

void	shell_display_prompt(void);

/*
**----------------------------------parser--------------------------------------
*/

/*
**	parser_lexer.c
*/

int		parser_lexer(char ****cmd_tab, char *line);

/*
**----------------------------------bultins-------------------------------------
*/

/*
**	builtin_exit.c
*/

void	builtin_exit(t_term *term_p);


/*
**==================================TEST PROTOTYPES=============================
*/

/*
**----------------------------------environment_testers-------------------------
*/

int		test_get_environ_cpy(void);
int		test_param_to_env(void);

/*
**--------------------------------term_testers----------------------------------
*/

int		test_term_is_valid(void);
int		test_term_init_struct(void);
int		test_term_free_struct(void);
int		test_term_get_attributes(void);

/*
**--------------------------------prompt_testers--------------------------------
*/

int		test_prompt(void);

/*
**--------------------------------shell_testers---------------------------------
*/

/*
**---------------------------------input_read_testers---------------------------
*/

#endif
