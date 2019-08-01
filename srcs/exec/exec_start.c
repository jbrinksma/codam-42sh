/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/07/31 18:28:09 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static size_t	count_args(t_ast *ast)
{
	t_ast	*probe;
	size_t	i;

	i = 0;
	probe = ast;
	while (probe != NULL)
	{
		i++;
		probe = probe->child;
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
		probe = probe->child;
		i++;
	}
	return (args);
}

/*
**	This is used to handle all the redirects and/or assignments in a
**	complete_command
*/

static int		exec_redirs_or_assigns(t_ast *node, t_vshdata *vshdata,
	int env_type)
{
	t_ast	*probe;

	probe = node;
	while (probe != NULL)
	{
		if (tool_is_redirect_tk(node->type) == true)
		{
			if (redir(probe) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else if (probe->type == ASSIGN)
		{
			if (builtin_assign(node->value, vshdata->envlst, env_type)
			== FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		probe = probe->child;
	}
	return (FUNCT_SUCCESS);
}

/*
**	This function has to prepare the complete_command before
**	execution.
*/

int				exec_complete_command(t_ast *node, t_vshdata *vshdata,
				t_pipes pipes)
{
	char	**command;

	if (exec_handle_variables(node, vshdata->envlst) == FUNCT_ERROR)
		return (g_state->exit_code == EXIT_WRONG_USE ?
		FUNCT_ERROR : error_return(FUNCT_ERROR, E_ALLOC, NULL));
	exec_quote_remove(node);
	if (node->type == WORD)
	{
		redir_handle_pipe(pipes);
		if (node->sibling &&
		exec_redirs_or_assigns(node->sibling, vshdata, ENV_TEMP)
		== FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, vshdata));
		command = create_args(node);
		if (command == NULL)
			return (return_and_reset_fds(FUNCT_ERROR, vshdata));
		exec_cmd(command, vshdata);
	}
	else if (node->type == ASSIGN || tool_is_redirect_tk(node->type) == true)
	{
		redir_handle_pipe(pipes);
		if (exec_redirs_or_assigns(node, vshdata, ENV_LOCAL)
		== FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, vshdata));
	}
	return (return_and_reset_fds(FUNCT_SUCCESS, vshdata));
}

/*
**	General structure:
**	Read PR.
*/

int				exec_start(t_ast *ast, t_vshdata *vshdata, t_pipes pipes)
{
	if (ast == NULL)
		return (FUNCT_ERROR);
	if (ast->type == PIPE)
		return (redir_run_pipesequence(ast, vshdata, pipes));
	if (ast->type != WORD && ast->type != ASSIGN &&
		tool_is_redirect_tk(ast->type) == false &&
		exec_start(ast->child, vshdata, pipes) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->type == AND_IF && g_state->exit_code != EXIT_SUCCESS)
		return (FUNCT_ERROR);
	else if (ast->type == OR_IF && g_state->exit_code == EXIT_SUCCESS)
		return (FUNCT_FAILURE);
	else if (ast->type == WORD || ast->type == ASSIGN
	|| tool_is_redirect_tk(ast->type) == true)
	{
		if (exec_complete_command(ast, vshdata, pipes)
		== FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else if (ast->sibling != NULL
	&& exec_start(ast->sibling, vshdata, pipes) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
