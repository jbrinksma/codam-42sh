/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_add_pid_to_pipeseqlist.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 07:59:07 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/05 09:55:44 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Adds pids of a command when it is a part of a pipe sequence. This is done
**	so that we can cancel processes like `base64` in a pipe sequence of
**	`base64 /dev/urandom | head -c 1000`, so that it does not run for infinity.
*/

void		exec_add_pid_to_pipeseqlist(t_vshdata *data, pid_t pid)
{
	t_pipeseqlist	*orig_list;
	bool			is_first_item;

	is_first_item = false;
	if (data->pipeseq != NULL)
	{
		orig_list = data->pipeseq;
		is_first_item = true;
	}
	data->pipeseq = (t_pipeseqlist*)ft_memalloc(sizeof(t_pipeseqlist));
	if (data->pipeseq == NULL)
	{
		ft_eprintf(SHELL ": could not allocate memory to keep track of a pid in"
		" a pipe sequence. You might have to manually cancel some"
		" processes.\n");
		return ;
	}
	data->pipeseq->pid = pid;
	if (is_first_item)
		data->pipeseq->next = orig_list;
}
