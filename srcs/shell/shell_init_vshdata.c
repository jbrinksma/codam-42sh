/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_vshdata.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 12:42:44 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/29 11:58:52 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	shell_init_data(t_vshdata *data)
{
	data->curs = shell_init_vshdatacurs();
	data->history = shell_init_vshdatahistory();
	data->line = shell_init_vshdataline();
	data->prompt = shell_init_vshdataprompt();
	data->input = shell_init_vshdatainput();
	data->hashtable = shell_init_vshdatahashtable();
	data->alias = shell_init_vshdataalias();
	data->jobs = shell_init_vshdatajobs();
	data->term = term_init_struct();
	if (data->curs == NULL || data->history == NULL || data->line == NULL ||
		data->prompt == NULL || data->input == NULL || data->hashtable == NULL
		|| data->alias == NULL || data->term == NULL || data->jobs == NULL)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

int			shell_init_term(t_vshdata *data)
{
	free(data->term->old_termios_p);
	free(data->term->termios_p);
	free(data->term);
	data->term = term_prepare(data->envlst);
	data->termcaps = shell_init_vshdatatermcaps();
	if (data->term == NULL || data->termcaps == NULL)
	{
		ft_eprintf(E_TERM_INIT);
		return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

t_vshdata	*shell_init_vshdata(void)
{
	t_vshdata *data;

	data = ft_memalloc(sizeof(t_vshdata));
	g_data = data;
	if (data == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	g_data = data;
	data->envlst = env_getlst();
	if (data->envlst == NULL || shell_init_data(data) == FUNCT_FAILURE)
	{
		ft_eprintf(E_ALLOC_STR);
		return (NULL);
	}
	if (shell_init_files(data) == FUNCT_ERROR
		|| history_get_file_content(data->history) == FUNCT_ERROR
		|| alias_read_file(data) == FUNCT_ERROR
		|| env_add_extern_value(data, "OLDPWD", "") == FUNCT_ERROR)
		return (NULL);
	return (data);
}
