/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/17 14:29:30 by jbrinksm      ########   odam.nl         */
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
**----------------------------------terminal------------------------------------
*/

/*
**	term_init.c
*/

t_term	*term_init(void);
t_term	*term_init_termstruct(void);
int		term_getent(void);
int		term_setattr(t_term *term_p);
t_term	*term_return(t_term *term_p, int return_value);

/*
**-----------------------------------input--------------------------------------
*/

/*
**	input_read.c
*/

int		input_read(void);
int		input_echo(char *buf);

/*
**----------------------------------shell---------------------------------------
*/

/*
**	shell_prompt.c
*/

void	shell_display_prompt(void);

/*
**----------------------------------bultins-------------------------------------
*/

/*
**	builtin_exit.c
*/

void	builtin_exit(t_term *term_p);

#endif