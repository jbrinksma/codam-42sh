/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/04 10:16:26 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/05 09:59:56 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>

static size_t	count_args(t_ast *ast)
{
	t_ast	*probe;
	size_t	i;

	i = 0;
	probe = ast;
	while (probe != NULL)
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

static int		exec_redirs_or_assigns(t_ast *ast, t_vshdata *data,
	int env_type)
{
	if (ast == NULL)
		return (FUNCT_FAILURE);
	if (tool_is_redirect_tk(ast->type) == true)
	{
		if (redir(ast) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else if (ast->type == ASSIGN)
	{
		if (builtin_assign(ast->value, data, env_type)
		== FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (exec_redirs_or_assigns(ast->left, data, env_type) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

/*
**	Exec_command gets executed in this order:
**
**	parameter expansion
**	quote removal
**	set input and output to proper pipes if applicable
**	handle redirects and assignments
**	(if command word):
**		create arguments
**		run command
*/

int				exec_command(t_ast *ast, t_vshdata *data, t_pipes pipes)
{
	char	**command;

	if (expan_handle_variables(ast, data->envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	exec_quote_remove(ast);
	if (redir_handle_pipe(pipes) == FUNCT_ERROR)
		return (return_and_reset_fds(FUNCT_ERROR, data));
	if (ast->type == WORD)
	{
		if (ast->right &&
		exec_redirs_or_assigns(ast->right, data, ENV_TEMP) == FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, data));
		command = create_args(ast);
		if (command == NULL)
			return (return_and_reset_fds(FUNCT_ERROR, data));
		exec_cmd(command, data, pipes);
	}
	else if (ast->type == ASSIGN || tool_is_redirect_tk(ast->type) == true)
	{
		if (exec_redirs_or_assigns(ast, data, ENV_LOCAL) == FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, data));
	}
	return (return_and_reset_fds(FUNCT_SUCCESS, data));
}
