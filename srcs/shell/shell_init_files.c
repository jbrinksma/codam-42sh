/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_init_files.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/27 12:39:59 by omulder        #+#    #+#                */
/*   Updated: 2019/07/29 12:33:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		shell_init_files(t_vshdata *vshdata)
{
	char	*homedir;

	homedir = env_getvalue("HOME", vshdata->envlst);
	if (homedir == NULL)
		return (FUNCT_ERROR);
	vshdata->history_file =
	ft_strjoinfree_s2(homedir, ft_strjoin("/", HISTFILENAME));
	vshdata->alias_file =
	ft_strjoinfree_s2(homedir, ft_strjoin("/", ALIASFILENAME));
	if (vshdata->history_file != NULL && vshdata->alias_file != NULL)
		return (FUNCT_SUCCESS);
	return (FUNCT_ERROR);
}
