/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_create_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/06 16:16:21 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/22 11:23:37 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	find_files(t_ast *ast)
{
	char	*file;
	int		fd;

	if (ast == NULL)
		return (FUNCT_FAILURE);
	if (find_files(ast->left) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->type == DGREAT || ast->type == SGREAT)
	{
		if (ast->right->type == IO_NUMBER)
			file = ast->right->left->value;
		else
			file = ast->right->value;
		fd = open(file, O_RDONLY | O_CREAT, REG_PERM);
		if (fd == -1)
		{
			ft_eprintf(E_FAIL_OPEN_P, file);
			g_state->exit_code = EXIT_FAILURE;
			return (FUNCT_ERROR);
		}
		close(fd);
	}
	return (FUNCT_SUCCESS);
}

int			exec_create_files(t_ast *ast)
{
	if (ast->left->type != PIPE)
	{
		if (ast->left->type == WORD)
		{
			if (find_files(ast->left->right) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else if (find_files(ast->left) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (ast->right->type == WORD)
	{
		if (find_files(ast->right->right) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else if (find_files(ast->right) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
