/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_tools2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/30 10:46:14 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/30 10:49:56 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		redir_save_stdfds(t_vshdata *vshdata)
{
	vshdata->stdfds[STDIN_FILENO] = dup(STDIN_FILENO);
	if (vshdata->stdfds[STDIN_FILENO] == -1)
		return (FUNCT_ERROR);
	vshdata->stdfds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (vshdata->stdfds[STDOUT_FILENO] == -1)
		return (FUNCT_ERROR);
	vshdata->stdfds[STDERR_FILENO] = dup(STDERR_FILENO);
	if (vshdata->stdfds[STDERR_FILENO] == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int		return_and_reset_fds(int retval, t_vshdata *vshdata)
{
	if (redir_reset_stdfds(vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (retval);
}

int		redir_reset_stdfds(t_vshdata *vshdata)
{
	int ret;

	ret = dup2(vshdata->stdfds[STDIN_FILENO], STDIN_FILENO);
	if (ret == -1)
		return (FUNCT_ERROR);
	ret = dup2(vshdata->stdfds[STDOUT_FILENO], STDOUT_FILENO);
	if (ret == -1)
		return (FUNCT_ERROR);
	ret = dup2(vshdata->stdfds[STDERR_FILENO], STDERR_FILENO);
	if (ret == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int		redir_close_saved_stdfds(t_vshdata *vshdata)
{
	if (close(vshdata->stdfds[0]) == -1)
		return (FUNCT_ERROR);
	else if (close(vshdata->stdfds[1]) == -1)
		return (FUNCT_ERROR);
	else if (close(vshdata->stdfds[2]) == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
