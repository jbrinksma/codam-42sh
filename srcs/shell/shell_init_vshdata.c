/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_vshdata.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 12:42:44 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/19 11:42:43 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		shell_init_vshdata(t_vshdata *vshdata)
{
	ft_bzero(vshdata, sizeof(t_vshdata));
	vshdata->envlst = env_getlst();
	if (vshdata->envlst == NULL)
		return (err_ret(E_ALLOC_STR));
	vshdata->term = term_prepare(vshdata->envlst);
	if (vshdata->term == NULL)
		return (FUNCT_ERROR);
	if (shell_init_files(vshdata) == FUNCT_ERROR ||
		history_get_file_content(vshdata) == FUNCT_ERROR ||
		alias_read_file(vshdata) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	hash_init(vshdata);
	return (FUNCT_SUCCESS);
}
