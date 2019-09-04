/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/09/04 10:23:58 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int		exec_post_pipe_sequence(t_ast *ast, t_vshdata *data,
				t_pipes pipes)
{
	close(pipes.currentpipe[PIPE_WRITE]);
	pipes.pipeside = PIPE_EXTEND;
	if (exec_command(ast->right, data, pipes) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	close(pipes.currentpipe[PIPE_READ]);
	return (FUNCT_SUCCESS);
}

/*
**	Recursively runs commands of the whole pipesequence, and
**	redirects their input and output according to the pipesequence.
**
**	The left of the last pipenode in the pipesequence is the first
**	command in the pipesequence PIPE_START. All other commands will
**	be siblings of pipenodes, and will thus be PIPE_EXTEND.
*/

int				exec_pipe_sequence(t_ast *ast, t_vshdata *data, t_pipes pipes)
{
	t_pipes	childpipes;

	if (ast->type != PIPE)
		return (exec_command(ast, data, pipes));
	if (pipe(pipes.currentpipe) == -1)
		return (err_ret(E_NO_PIPE));
	if (exec_create_files(ast) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->left->type == PIPE)
	{
		childpipes = pipes;
		childpipes.parentpipe[PIPE_READ] = pipes.currentpipe[PIPE_READ];
		childpipes.parentpipe[PIPE_WRITE] = pipes.currentpipe[PIPE_WRITE];
		if (exec_pipe_sequence(ast->left, data, childpipes) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else
	{
		pipes.pipeside = PIPE_START;
		if (exec_command(ast->left, data, pipes) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (exec_post_pipe_sequence(ast, data, pipes));
}

int				exec_and_or(t_ast *ast, t_vshdata *data)
{
	t_pipes pipes;

	pipes = redir_init_pipestruct();
	if (ast->type != AND_IF && ast->type != OR_IF)
		return (exec_pipe_sequence(ast, data, pipes));
	if (exec_and_or(ast->left, data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->type == AND_IF && g_state->exit_code != EXIT_SUCCESS)
		return (FUNCT_ERROR);
	else if (ast->type == OR_IF && g_state->exit_code == EXIT_SUCCESS)
		return (FUNCT_FAILURE);
	if (exec_and_or(ast->right, data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int				exec_list(t_ast *ast, t_vshdata *data)
{
	if (ast->type != BG && ast->type != SEMICOL)
		return (exec_and_or(ast, data));
	if (exec_and_or(ast->left, data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ast->right != NULL)
	{
		if (exec_list(ast->right, data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

int				exec_complete_command(t_ast *ast, t_vshdata *data)
{
	if (ast == NULL)
		return (FUNCT_ERROR);
	if (exec_list(ast, data) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
