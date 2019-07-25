/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/07/25 15:51:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

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

static char	**create_args(t_ast *ast)
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

static int	exec_redirs_or_assigns(t_ast *node, t_vshdata *vshdata,
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

static int	redir_save_stdfds(int *stdfds)
{
	STDIN_BAK = dup(STDIN_FILENO);
	if (STDIN_BAK == -1)
		return (FUNCT_ERROR);
	STDOUT_BAK = dup(STDOUT_FILENO);
	if (STDOUT_BAK == -1)
		return (FUNCT_ERROR);
	STDERR_BAK = dup(STDERR_FILENO);
	if (STDERR_BAK == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

static int	redir_reset_stdfds(int *stdfds)
{
	if (dup2(STDIN_BAK, STDIN_FILENO) == -1)
		return (FUNCT_ERROR);
	if (dup2(STDOUT_BAK, STDOUT_FILENO) == -1)
		return (FUNCT_ERROR);
	if (dup2(STDERR_BAK, STDERR_FILENO) == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

/*
**	This function has to prepare the complete_command before
**	execution.
*/

static int	return_and_reset_fds(int retval, int *stdfds)
{
	if (redir_reset_stdfds(stdfds) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (retval);
}

int			exec_complete_command(t_ast *node, t_vshdata *vshdata, int flags)
{
	char	**command;
	int		stdfds[3];

	(void)flags;
	if (redir_save_stdfds(stdfds) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	exec_quote_remove(node);
	if (node->type == WORD)
	{
		if (node->sibling &&
		exec_redirs_or_assigns(node->sibling, vshdata, ENV_TEMP)
		== FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, stdfds));
		command = create_args(node);
		if (command == NULL)
			return (return_and_reset_fds(FUNCT_ERROR, stdfds));
		exec_cmd(command, vshdata);
	}
	else if (node->type == ASSIGN || tool_is_redirect_tk(node->type) == true)
	{
		if (exec_redirs_or_assigns(node, vshdata, ENV_LOCAL)
		== FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, stdfds));
	}
	return (return_and_reset_fds(FUNCT_SUCCESS, stdfds));
}

/*
**	General structure:
**	Read PR.
*/

void		exec_start(t_ast *ast, t_vshdata *vshdata, int flags)
{
	if (ast == NULL)
		return ;
	if (ast->type == PIPE)
		flags &= ~EXEC_PIPE;
	else if (ast->type == BG)
		flags &= ~EXEC_BG;
	else if (ast->type == AND_IF)
		flags &= ~EXEC_AND_IF;
	else if (ast->type == OR_IF)
		flags &= ~EXEC_OR_IF;
	else if (ast->type == SEMICOL)
		flags &= ~EXEC_SEMICOL;
	if (ast->type != WORD && ast->type != ASSIGN &&
	tool_is_redirect_tk(ast->type) == false)
		exec_start(ast->child, vshdata, flags);
	if (ast->type == AND_IF && g_state->exit_code != EXIT_SUCCESS)
		return ;
	else if (ast->type == OR_IF && g_state->exit_code == EXIT_SUCCESS)
		return ;
	else if (ast->type == WORD || ast->type == ASSIGN
	|| tool_is_redirect_tk(ast->type) == true)
	{
		if (exec_complete_command(ast, vshdata, flags)
		== FUNCT_ERROR)
			return ;
	}
	else if (ast->sibling != NULL && (ast->sibling->type == WORD
	|| ast->sibling->type == ASSIGN
	|| tool_is_redirect_tk(ast->sibling->type) == true))
		exec_start(ast->sibling, vshdata, flags);
}
