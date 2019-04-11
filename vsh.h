/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/11 20:17:32 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSH_H
# define VSH_H

/*
**-------------------------------defines----------------------------------------
*/

# define FUNCT_FAILURE 0
# define FUNCT_SUCCESS 1
# define FUNCT_ERROR -1
# define E_ALLOC 420

/*
**-------------------------------personal headers-------------------------------
*/

#include "libft.h"

/*
**----------------------------------headers-------------------------------------
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
**---------------------------------structs--------------------------------------
*/

typedef struct	s_term
{
	struct termios	*old_termios_p;
	struct termios	*termios_p;
}				t_term;

/*
**---------------------------------prototypes-----------------------------------
*/

/*
**	main.c
*/

int		reset_term(t_term *term_p);
void	free_term_p(t_term *term_p);
int		start_shell(t_term *term_p);

/*
**	init_term.c
*/

t_term	*init_term(void);
t_term	*init_term_struct(void);
int		init_term_getent(void);
int		init_term_setattr(t_term *term_p);
t_term	*return_init_term(t_term *term_p, int return_value);

/*
**	prompt.c
*/

void	display_prompt(void);

/*
**	vsh_exit.c
*/

void	vsh_exit(t_term *term_p);

#endif