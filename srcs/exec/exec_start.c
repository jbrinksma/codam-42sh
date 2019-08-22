/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/08/22 11:26:26 by omulder       ########   odam.nl         */
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

static int		exec_redirs_or_assigns(t_ast *ast, t_vshdata *vshdata,
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
		if (builtin_assign(ast->value, vshdata, env_type)
		== FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (exec_redirs_or_assigns(ast->left, vshdata, env_type) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int				exec_command(t_ast *ast, t_vshdata *vshdata, t_pipes pipes)
{
	char	**command;

	if (expan_handle_variables(ast, vshdata->envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	exec_quote_remove(ast);
	if (redir_handle_pipe(pipes) == FUNCT_ERROR)
		return (return_and_reset_fds(FUNCT_ERROR, vshdata));
	if (ast->type == WORD)
	{
		if (ast->right &&
		exec_redirs_or_assigns(ast->right, vshdata, ENV_TEMP) == FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, vshdata));
		command = create_args(ast);
		if (command == NULL)
			return (return_and_reset_fds(FUNCT_ERROR, vshdata));
		exec_cmd(command, vshdata);
	}
	else if (ast->type == ASSIGN || tool_is_redirect_tk(ast->type) == true)
	{
		if (exec_redirs_or_assigns(ast, vshdata, ENV_LOCAL) == FUNCT_ERROR)
			return (return_and_reset_fds(FUNCT_ERROR, vshdata));
	}
	return (return_and_reset_fds(FUNCT_SUCCESS, vshdata));
}

/*
**	Recursively runs commands of the whole pipesequence, and
**	redirects their input and output according to the pipesequence.
**
**	The left of the last pipenode in the pipesequence is the first
**	command in the pipesequence PIPE_START. All other commands will
**	be siblings of pipenodes, and will thus be PIPE_EXTEND.
*/

int				exec_pipe_sequence(t_ast *ast, t_vshdata *vshdata, t_pipes pipes)
{
	t_pipes	childpipes;

	/* Skip this phase if there is no `pipe_sequence` node */
	if (ast->type != PIPE)
		return (exec_command(ast, vshdata, pipes));

	/* create pipe so that childs are properly linked */
	if (pipe(pipes.currentpipe) == -1)
	{
		ft_eprintf(E_NO_PIPE);
		return (FUNCT_ERROR);
	}
	/* Create files if they don't exist yet */
	if (exec_create_files(ast) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	/* always execute a deeper `pipe_sequence` node first */
	if (ast->left->type == PIPE)
	{
		childpipes = pipes;
		childpipes.parentpipe[PIPE_READ] = pipes.currentpipe[PIPE_READ];
		childpipes.parentpipe[PIPE_WRITE] = pipes.currentpipe[PIPE_WRITE];
		if (exec_pipe_sequence(ast->left, vshdata, childpipes) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}

	/* this is the first command node of the pipe sequence */
	if (ast->left->type != PIPE)
	{
		pipes.pipeside = PIPE_START;
		if (exec_command(ast->left, vshdata, pipes) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}

	/* always attempt to close the write end of pipe */
	close(pipes.currentpipe[PIPE_WRITE]);

	/* these are the nodes to be piped towards (and potentially from) */
	pipes.pipeside = PIPE_EXTEND;
	if (exec_command(ast->right, vshdata, pipes) == FUNCT_ERROR)
		return (FUNCT_ERROR);

	/* always attempt to close the read end of pipe */
	close(pipes.currentpipe[PIPE_READ]);
	return (FUNCT_SUCCESS);
}

int				exec_and_or(t_ast *ast, t_vshdata *vshdata)
{
	t_pipes pipes;

	/* init pipes */
	pipes = redir_init_pipestruct();

	/* Skip this phase if no `and_or` node is present */
	if (ast->type != AND_IF && ast->type != OR_IF)
		return (exec_pipe_sequence(ast, vshdata, pipes));

	/* Execute the leftside of `and_or / or_if` node */
	if (exec_and_or(ast->left, vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);

	/* Depending on EXIT status return or continue */
	if (ast->type == AND_IF && g_state->exit_code != EXIT_SUCCESS)
		return (FUNCT_ERROR);
	else if (ast->type == OR_IF && g_state->exit_code == EXIT_SUCCESS)
		return (FUNCT_FAILURE);

	/* Execute the rightside of `and_or / or_if` node  */
	if (exec_and_or(ast->right, vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int				exec_list(t_ast *ast, t_vshdata *vshdata)
{
	/* Skip this phase if no `list` node is present */
	if (ast->type != BG && ast->type != SEMICOL)
		return (exec_and_or(ast, vshdata));

	/* if background token: do optional BG shenanigans */

	/* Execute first list */
	if (exec_and_or(ast->left, vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);

	/* If there are more lists */
	if (ast->right != NULL)
	{
		if (exec_list(ast->right, vshdata) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

int				exec_complete_command(t_ast *ast, t_vshdata *vshdata)
{
	if (ast == NULL)
		return (FUNCT_ERROR);

	/* run list */
	if (exec_list(ast, vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	
	return (FUNCT_SUCCESS);
}
