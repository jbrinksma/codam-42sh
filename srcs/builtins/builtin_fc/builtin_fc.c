/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 12:23:10 by omulder        #+#    #+#                */
/*   Updated: 2019/10/15 15:17:30 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
** fc [-r][-e editor] [first[last]]
** fc -l[-nr] [first[last]]
** fc -s[old=new][first]
** FLAGS:
** -e [editor] <-- Choose editor, otherwise use FCEDIT or ed
** -l [first[last]] <-- list history
** -n <-- suppress numbers
** -r <-- reverse order of commands listed or edited
** -s [old=new][first]<-- re-execute without editor
*/

static void	free_fcdata(t_fcdata **fc)
{
	ft_strdel(&(*fc)->tmpfile);
	ft_memdel((void**)fc);
}

void		builtin_fc(char **args, t_vshdata *data)
{
	t_fcdata	*fc;

	g_state->exit_code = EXIT_SUCCESS;
	fc = (t_fcdata*)ft_memalloc(sizeof(t_fcdata));
	if (fc == NULL)
		return (err_void_prog_exit(E_N_ALLOC_STR, "fc", EXIT_FAILURE));
	fc_set_default_editor(data, fc);
	if (fc_set_options(args, fc) == FUNCT_FAILURE)
	{
		free_fcdata(&fc);
		g_state->exit_code = EXIT_FAILURE;
		return ;
	}
	if (fc->options & FC_OPT_L)
		fc_list(data->history, fc);
	else if (fc->options & FC_OPT_S)
		fc_substitute(data, data->history, fc);
	else
		fc_edit(data, data->history, fc);
	free_fcdata(&fc);
}
