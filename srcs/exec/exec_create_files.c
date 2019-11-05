/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_create_files.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/06 16:16:21 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/05 15:30:46 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	check_if_directory(char *file)
{
	struct stat statbuf;

	if (stat(file, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_eprintf(E_ISDIR, file);
			g_state->exit_code = EXIT_FAILURE;
			return (FUNCT_ERROR);
		}
	}
	return (FUNCT_SUCCESS);
}

static int	check_if_valid_file(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY | O_CREAT | O_NONBLOCK, REG_PERM);
	if (fd == -1)
	{
		ft_eprintf(E_FAIL_OPEN_P, file);
		g_state->exit_code = EXIT_FAILURE;
		return (FUNCT_ERROR);
	}
	close(fd);
	return (FUNCT_SUCCESS);
}

static int	find_files(t_ast *ast)
{
	char	*file;

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
		if (check_if_valid_file(file) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		if (check_if_directory(file) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

int			exec_create_files(t_ast *ast)
{
	if (find_files(ast) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
