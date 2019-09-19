/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_add_pid_to_pipeseqlist.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 07:59:07 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/16 11:17:21 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

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
		" a pipe sequence. You will have to manually cancel some processes.\n");
		return ;
	}
	data->pipeseq->pid = pid;
	if (is_first_item)
		data->pipeseq->next = orig_list;
}
