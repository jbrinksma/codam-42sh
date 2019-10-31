/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/04 10:16:26 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 09:54:44 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>

static size_t	count_args(t_ast *ast)
{
	t_ast	*probe;
	size_t	i;

	i = 0;
	probe = ast;
	while (probe != NULL && (probe->type == WORD || probe->type == ASSIGN))
	{
		i++;
		probe = probe->left;
	}
	return (i);
}

static char		**create_args(t_ast *ast)
{
	char	**args;
	t_ast	*probe;
	size_t	total_args;
	size_t	i;

	total_args = count_args(ast);
	args = (char**)ft_memalloc(sizeof(char*) * (total_args + 1));
	if (args == NULL)
		return (NULL);
	if (total_args == 0)
		*args = ft_strnew(0);
	i = 0;
	probe = ast;
	while (i < total_args)
	{
		args[i] = ft_strdup(probe->value);
		if (args[i] == NULL)
		{
			ft_strarrdel(&args);
			return (NULL);
		}
		probe = probe->left;
		i++;
	}
	return (args);
}

/*
**	This is used to handle all the redirects and/or assignments in a
**	complete_command
*/

int				exec_assigns(t_ast *ast, t_vshdata *data,
	int env_type)
{
	if (ast == NULL)
		return (FUNCT_FAILURE);
	if (ast->type == ASSIGN)
	{
		if (builtin_assign(ast->value, data, env_type)
		== FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (exec_assigns(ast->left, data, env_type) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int				exec_redirs(t_ast *redirs)
{
	if (redirs == NULL)
		return (FUNCT_FAILURE);
	if (tool_is_redirect_tk(redirs->type))
	{
		if (redir(redirs) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (exec_redirs(redirs->left) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int				exec_command(t_ast *ast, t_vshdata *data)
{
	char	**argv;

	if (expan_handle_variables(ast, data->envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->type == WORD && expan_pathname(ast) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	exec_quote_remove(ast);
	if (ast->type == WORD)
	{
		data->current_redir_and_assign = ast->right;
		argv = create_args(ast);
		if (argv == NULL)
			return (FUNCT_ERROR);
		exec_cmd(argv, data);
	}
	else if (exec_assigns(ast, data, ENV_LOCAL) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
