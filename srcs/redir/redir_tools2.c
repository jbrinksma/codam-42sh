/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_tools2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/30 10:46:14 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/06 12:18:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Save a duplicate of the terminal pointers.
*/

int		redir_save_stdfds(t_vshdata *data)
{
	data->stdfds[STDIN_FILENO] = dup(STDIN_FILENO);
	if (data->stdfds[STDIN_FILENO] == -1)
		return (FUNCT_ERROR);
	data->stdfds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (data->stdfds[STDOUT_FILENO] == -1)
		return (FUNCT_ERROR);
	data->stdfds[STDERR_FILENO] = dup(STDERR_FILENO);
	if (data->stdfds[STDERR_FILENO] == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int		return_and_reset_fds(int retval, t_vshdata *data)
{
	if (redir_reset_stdfds(data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (retval);
}

/*
**	Reset the standard file descriptors to the terminal pointers.
*/

int		redir_reset_stdfds(t_vshdata *data)
{
	int ret;

	ret = dup2(data->stdfds[STDIN_FILENO], STDIN_FILENO);
	if (ret == -1)
		return (FUNCT_ERROR);
	ret = dup2(data->stdfds[STDOUT_FILENO], STDOUT_FILENO);
	if (ret == -1)
		return (FUNCT_ERROR);
	ret = dup2(data->stdfds[STDERR_FILENO], STDERR_FILENO);
	if (ret == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int		redir_close_saved_stdfds(t_vshdata *data)
{
	if (close(data->stdfds[0]) == -1)
		return (FUNCT_ERROR);
	else if (close(data->stdfds[1]) == -1)
		return (FUNCT_ERROR);
	else if (close(data->stdfds[2]) == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
