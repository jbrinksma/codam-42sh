/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_find_binary.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 15:16:46 by tde-jong       #+#    #+#                */
/*   Updated: 2019/07/30 11:02:55 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <dirent.h>

static char		**get_paths(t_envlst *envlst)
{
	char *paths;

	paths = env_getvalue("PATH", envlst);
	if (paths == NULL || *paths == '\0')
		return (NULL);
	return (ft_strsplit(paths, ':'));
}

static char		*check_dir(DIR *d, char *filename, char *path)
{
	struct dirent	*dir;

	dir = readdir(d);
	while (dir != NULL)
	{
		if (ft_strequ(filename, dir->d_name))
			return (ft_joinstrcstr(path, '/', filename));
		dir = readdir(d);
	}
	return (NULL);
}

char			*exec_find_binary(char *filename, t_vshdata *vshdata)
{
	DIR				*d;
	char			**paths;
	char			*ret;
	size_t			i;

	paths = get_paths(vshdata->envlst);
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		d = opendir(paths[i]);
		if (d != NULL)
		{
			ret = check_dir(d, filename, paths[i]);
			closedir(d);
			if (ret != NULL)
				break ;
		}
		i++;
	}
	ft_strarrdel(&paths);
	return (ret);
}
