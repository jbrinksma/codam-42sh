/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_find_file.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/27 12:39:59 by omulder        #+#    #+#                */
/*   Updated: 2019/07/27 12:47:42 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char	*history_find_histfile(t_vshdata *vshdata)
{
	char	*histfile;
	char	*homedir;

	homedir = env_getvalue("HOME", vshdata->envlst);
	if (homedir == NULL)
		return (NULL);
	histfile = ft_strjoinfree_s2(homedir, ft_strjoin("/", HISTFILENAME));
	return (histfile);
}
