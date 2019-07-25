/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 15:14:08 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/25 12:58:00 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <fcntl.h>

static int	getvalidfd(int *right_side_fd, char *right_side)
{
	if (tools_is_fdnumstr(right_side) == false)
		return (error_return(FUNCT_ERROR, E_BADRED, right_side));
	*right_side_fd = ft_atoi(right_side);
	if (redir_is_open_fd(*right_side_fd) == false)
		return (error_return(FUNCT_ERROR, E_BADFD, right_side));
	return (FUNCT_SUCCESS);
}

/*
**	Handles `<`, `<<`, and `<&`
*/

int			redir_input(t_ast *node)
{
	char	*right_side;
	int		left_side_fd;
	int		right_side_fd;

	left_side_fd = STDIN_FILENO;
	right_side = node->sibling->value;
	right_side_fd = FD_UNINIT;
	redir_change_if_leftside(node, &left_side_fd, &right_side);
	if (node->type == SLESS)
		right_side_fd = open(right_side, O_RDONLY);
	else if (node->type == DLESS)
		right_side_fd = redir_create_heredoc_fd(right_side);
	else if (ft_strequ(right_side, "-") == true)
		return (redir_input_closefd(left_side_fd));
	else
	{
		if (getvalidfd(&right_side_fd, right_side) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (right_side_fd == -1)
		return (error_return(FUNCT_ERROR, E_OPEN, NULL));
	if (dup2(right_side_fd, left_side_fd) == -1)
		return (error_return(FUNCT_ERROR, E_DUP, NULL));
	close(right_side_fd);
	return (FUNCT_SUCCESS);
}

/*
**	Handles `>`, `>>`, and `>&`
*/

int			redir_output(t_ast *node)
{
	char	*right_side;
	int		left_side_fd;
	int		right_side_fd;

	left_side_fd = STDOUT_FILENO;
	right_side = node->sibling->value;
	right_side_fd = FD_UNINIT;
	redir_change_if_leftside(node, &left_side_fd, &right_side);
	if (node->type == SGREAT)
		right_side_fd = open(right_side, O_WRONLY | O_CREAT | O_TRUNC);
	else if (node->type == DGREAT)
		right_side_fd = open(right_side, O_WRONLY | O_CREAT | O_APPEND);
	else if (ft_strequ(right_side, "-") == true)
		return (redir_input_closefd(left_side_fd));
	else
	{
		if (getvalidfd(&right_side_fd, right_side) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (right_side_fd == -1)
		return (error_return(FUNCT_ERROR, E_OPEN, NULL));
	if (dup2(right_side_fd, left_side_fd) == -1)
		return (error_return(FUNCT_ERROR, E_DUP, NULL));
	close(right_side_fd);
	return (FUNCT_SUCCESS);
}

/*
**	Changes file table based on the redirect given as input.
*/

int			redir(t_ast *node)
{
	int		ret;

	ret = FUNCT_SUCCESS;
	if (node == NULL || tool_is_redirect_tk(node->type) == false)
		return (FUNCT_FAILURE);
	if (node->type == SLESS || node->type == DLESS || node->type == LESSAND)
		ret = redir_input(node);
	if (node->type == SGREAT || node->type == DGREAT || node->type == GREATAND)
		ret = redir_output(node);
	return (ret);
}
