/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_exec_builtin.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 16:42:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 13:27:13 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			jobs_exec_is_single_builtin_proc(t_proc *proc)
{
	return (proc != NULL && proc->is_builtin == true && proc->next == NULL);
}

static int	cleanup_non_forked_redirs(void)
{
	if (dup2(g_data->stdfds[0], STDIN_FILENO) == -1)
		return (FUNCT_ERROR);
	if (dup2(g_data->stdfds[1], STDOUT_FILENO) == -1)
		return (FUNCT_ERROR);
	if (dup2(g_data->stdfds[2], STDERR_FILENO) == -1)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

static void	jobs_exec_builtin_continued(t_proc *proc)
{
	if (ft_strequ(proc->argv[0], "fc"))
		builtin_fc(proc->argv, g_data);
	else if (ft_strequ(proc->argv[0], "set"))
		builtin_set(proc->argv, g_data->envlst);
	else if (ft_strequ(proc->argv[0], "unset"))
		builtin_unset(proc->argv, g_data->envlst);
	else if (ft_strequ(proc->argv[0], "history"))
		history_print(g_data->history);
	else if (ft_strequ(proc->argv[0], "type"))
		builtin_type(proc->argv, g_data->envlst, g_data->alias->aliaslst);
	else if (ft_strequ(proc->argv[0], "alias"))
		builtin_alias(proc->argv, &g_data->alias->aliaslst);
	else if (ft_strequ(proc->argv[0], "unalias"))
		builtin_unalias(proc->argv, &g_data->alias->aliaslst);
	else if (ft_strequ(proc->argv[0], "jobs"))
		builtin_jobs(proc->argv, g_data);
	else if (ft_strequ(proc->argv[0], "fg"))
		builtin_fg(proc->argv, g_data);
	else if (ft_strequ(proc->argv[0], "bg"))
		builtin_bg(proc->argv, g_data);
	else if (ft_strequ(proc->argv[0], "hash"))
		builtin_hash(proc->argv, g_data);
	else if (ft_strequ(proc->argv[0], "export"))
		builtin_export(proc->argv, g_data);
}

void		jobs_exec_builtin(t_proc *proc)
{
	if (exec_create_files(proc->redir_and_assign) == FUNCT_ERROR ||
		exec_assigns(proc->redir_and_assign, g_data, ENV_TEMP) == FUNCT_ERROR)
		return ;
	if (redir(proc->redir_and_assign) == FUNCT_ERROR)
	{
		g_state->exit_code = EXIT_FAILURE;
		return ;
	}
	if (ft_strequ(proc->argv[0], "echo"))
		builtin_echo(proc->argv);
	else if (ft_strequ(proc->argv[0], "exit"))
		builtin_exit(proc->argv, g_data);
	else if (ft_strequ(proc->argv[0], "cd"))
		builtin_cd(proc->argv, g_data);
	else
		jobs_exec_builtin_continued(proc);
	if (cleanup_non_forked_redirs() == FUNCT_ERROR)
		err_void_exit(E_FD_RESET_STD, EXIT_FAILURE);
}
