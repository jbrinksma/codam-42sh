/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_tools.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/22 09:18:19 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/06 12:15:52 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Creates a pipe in which the heredoc can be written to
**	and returns its READ-side fd.
*/

int			redir_create_heredoc_fd(char *right_side)
{
	int		pipefds[2];

	g_state->exit_code = EXIT_FATAL;
	if (pipe(pipefds) == -1)
		return (FUNCT_ERROR);
	if (write(pipefds[1], right_side, ft_strlen(right_side)) == -1)
	{
		close(pipefds[0]);
		close(pipefds[1]);
		return (FUNCT_ERROR);
	}
	close(pipefds[1]);
	g_state->exit_code = EXIT_SUCCESS;
	return (pipefds[0]);
}

/*
**	If node->right->left != NULL, it means that the left side
**	of the redirection is explicitly given, and thus (because of our
**	AST structure) the right side of the redirection is then
**	the content of 'node->right->left' instead of 'node->right'.
*/

void		redir_change_if_leftside(t_ast *node, int *left_side_fd,
char **right_side)
{
	if (node->right->left != NULL)
	{
		*left_side_fd = ft_atoi(node->right->value);
		*right_side = node->right->left->value;
	}
}

int			redir_input_closefd(int left_side_fd)
{
	if (close(left_side_fd) == -1)
		return (error_return(FUNCT_ERROR, E_CLOSE, NULL));
	return (FUNCT_SUCCESS);
}

bool		redir_is_open_fd(int fd)
{
	struct stat	buf;

	if (fstat(fd, &buf) == -1)
		return (false);
	return (true);
}
