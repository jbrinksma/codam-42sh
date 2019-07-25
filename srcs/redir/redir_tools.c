/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_tools.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/22 09:18:19 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/25 12:58:52 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
**	Creates a pipe in which the heredoc can be written to
**	and returns its READ fd.
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
**	If node->sibling->child != NULL, it means that the left side
**	of the redirection is explicitly given, and such the right side
**	of the redirection is then 'node->sibling->child' != NULL instead
**	of 'node->sibling'.
*/

void		redir_change_if_leftside(t_ast *node, int *left_side_fd,
char **right_side)
{
	if (node->sibling->child != NULL)
	{
		*left_side_fd = ft_atoi(node->sibling->value);
		*right_side = node->sibling->child->value;
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
	struct stat buf;

	if (fstat(fd, &buf) == -1)
		return (false);
	return (true);
}
