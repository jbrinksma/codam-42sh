/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_term.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 10:10:56 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/11 14:22:30 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_term	*init_term_struct(void)
{
	t_term	*term_p;

	term_p = (t_term*)malloc(sizeof(t_term));
	if (!term_p)
		return (NULL);
	term_p->old_termios_p = (struct termios*)malloc(sizeof(struct termios));
	if (!term_p->old_termios_p)
	{
		free(term_p);
		return (NULL);
	}
	term_p->termios_p = (struct termios*)malloc(sizeof(struct termios));
	if (!term_p->termios_p)
	{
		free(term_p->old_termios_p);
		free(term_p);
		return (NULL);
	}
	return (term_p);
}

int		init_term_setattr(t_term *term_p)
{
	int	ret;

	/* Insert: check if it is a valid terminal filed */	
	ret = tcgetattr(STDIN_FILENO, term_p->termios_p);
	if (ret == 0)
	{
		ft_eprintf("Couldn't get terminal attributes.\n");
		return (FUNCT_FAILURE);
	}
	ret = tcgetattr(STDIN_FILENO, term_p->old_termios_p);
	if (ret == 0)
	{
		ft_eprintf("Couldn't get terminal attributes.\n");
		return (FUNCT_FAILURE);
	}
	term_p->termios_p->c_lflag &= ~ICANON;
	term_p->termios_p->c_lflag &= ~ECHO;
	term_p->termios_p->c_cc[VMIN] = 1;
	term_p->termios_p->c_cc[VTIME] = 0;
	/* Is TCSANOW flag correct? */
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->termios_p);
	if (ret == 0)
	{
		ft_eprintf("Couldn't set terminal attributes.\n");
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

int		init_term_getent(void)
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	if (!term_type)
	{
		ft_eprintf("Term env not set.\n");
		return (FUNCT_FAILURE);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		ft_eprintf("Terminfo database could not be found.\n");
	if (ret == 0)
		ft_eprintf("No such TERM entry in the database\n");
	if (ret == -1 || ret == 0)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

t_term	*return_init_term(t_term *term_p, int return_value)
{
	if (return_value == FUNCT_FAILURE)
	{
		free_term_p(term_p);
		return (NULL);
	}
	return (term_p);
}

t_term	*init_term(void)
{
	t_term	*term_p;

	term_p = init_term_struct();
	/* Add specific alloc error here */
	if (!term_p)
		return (return_init_term(NULL, FUNCT_FAILURE));
	if (!init_term_getent())
		return (return_init_term(term_p, FUNCT_FAILURE));
	if (!init_term_setattr(term_p))
		return (return_init_term(term_p, FUNCT_FAILURE));
	return (return_init_term(term_p, FUNCT_SUCCESS));
}
