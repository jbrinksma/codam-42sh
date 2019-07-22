/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/07/20 16:23:40 by mavan-he      ########   odam.nl         */
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
**	This will edit the I/O table based on the redirect given as input.
**	DOESNT WORK YET
*/

static void exec_redir(t_ast *node, t_envlst *envlst, int *exit_code)
{
	t_ast	*probe;
	char	*left;
	char	*right;

	(void)exit_code;
	(void)envlst;

	probe = node->sibling;
	if (probe->type == WORD)
		left = probe->value;
	else
		left = parser_return_token_str(probe->type);
	probe = node->sibling->child;
	if (probe->type == WORD)
		right = probe->value;
	else
		right = parser_return_token_str(probe->type);
	ft_printf("Redirect: %s > %s\n", left, right);
}

/*
**	This is used to handle all the redirects and/or assignments in a
**	complete_command
*/

static void	exec_redirs_or_assigns(t_ast *node, t_envlst *envlst, int env_type, int *exit_code)
{
	t_ast	*probe;

	probe = node;
	while (probe != NULL)
	{
		if (probe->type == SGREAT)
			exec_redir(probe, envlst, exit_code);
		else if (probe->type == ASSIGN)
			builtin_assign(probe->value, envlst, exit_code, env_type);
		probe = probe->child;
	}
}

/*
**	This function has to prepare the complete_command before
**	execution. Wildcard, quote removal, variables.
*/

static void	exec_complete_command(t_ast *node, t_envlst *envlst, int *exit_code, int flags)
{
	char	**command;

	(void)flags;

	/* Replace wildcards */
	/* Replace variables */

	/* There is atleast one cmd_word in complete_command */
	exec_quote_remove(node);
	if (node->type == WORD)
	{
		if (node->sibling)
			exec_redirs_or_assigns(node->sibling, envlst, ENV_TEMP, exit_code);
		command = create_args(node);
		/* add handling of flag = EXEC_PIPE */
		/* add option for flag = EXEC_BG */
		if (command != NULL)
			exec_cmd(command, envlst, exit_code);
	}

	/* There is no cmd_word in complete_command */
	else if (node->type == ASSIGN || node->type == SGREAT)
		exec_redirs_or_assigns(node, envlst, ENV_LOCAL, exit_code);
}

/*
**	General structure:
**	Read PR.
*/

void		exec_start(t_ast *ast, t_envlst *envlst, int *exit_code, int flags)
{
	if (ast == NULL)
		return ;
	/* Set flags */
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

	/* Goes through the tree to find complete_commands first */
	/* problem if there are no WORD's but only prefix or suffix */
	if (ast->type != WORD && ast->type != ASSIGN && ast->type != SGREAT)
		exec_start(ast->child, envlst, exit_code, flags);
	
	/* Runs after the above exec_start returns or isn't run */
	if (ast->type == AND_IF && *exit_code != EXIT_SUCCESS)
		return ;
	else if (ast->type == OR_IF && *exit_code == EXIT_SUCCESS)
		return ;
	else if (ast->type == WORD || ast->type == ASSIGN || ast->type == SGREAT)
		exec_complete_command(ast, envlst, exit_code, flags);
	else if (ast->sibling != NULL)
		exec_start(ast->sibling, envlst, exit_code, flags);
}
