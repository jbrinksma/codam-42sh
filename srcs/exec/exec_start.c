/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:52:22 by omulder        #+#    #+#                */
/*   Updated: 2019/10/05 14:41:06 by jbrinksm      ########   odam.nl         */
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
**	Runs the pipeline from left to right. The first `PIPE` node in the AST is
**	the farmost right `simple_command` in the `pipe sequence`(see GRAMMAR).
**
**	Because of this, we will create all the pipes recursively starting at the
**	top node and working our way down the AST towards the first `simple_command`
**	in the pipe sequence. When we reach this first simple_command, the whole
**	pipeline will have been laid down. Consequently, when we work our way back
**	up in the AST (returning the recursion), we can properly manage the I/O of
**	each simple command in the pipeline before execution (because the pipe fds
**	will already be available in each `t_pipes pipes` struct).
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
