/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_get_filelst.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/11 12:28:38 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/02 17:17:27 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <dirent.h>

/*
** For now we are only using the lstat, not sure if this is the correct one
** but it seems to work
*/

static int	is_dir(char *path, int l)
{
	struct stat buf;

	if (l && lstat(path, &buf) == -1)
		return (0);
	else if (stat(path, &buf) == -1)
		return (0);
	return (S_ISDIR(buf.st_mode));
}

static int	check_and_add_match(t_list **matchlst, char *match, char *name,
char *path)
{
	char	*tmp;

	if (ft_strequ(match, "") == false ||
	(ft_strequ(name, ".") == false &&
	ft_strequ(name, "..") == false))
	{
		tmp = ft_strjoinfree_s1(ft_strjoin(path, "/"), name);
		if (is_dir(tmp, true))
		{
			ft_strdel(&tmp);
			tmp = ft_strjoin(name, "/");
			if (auto_add_tolst(matchlst, tmp) == FUNCT_ERROR)
			{
				ft_strdel(&tmp);
				return (FUNCT_ERROR);
			}
		}
		else
		{
			if (auto_add_tolst(matchlst, name) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		ft_strdel(&tmp);
	}
	return (FUNCT_SUCCESS);
}

static int	check_dir(DIR *d, char *match, t_list **matchlst, char *path)
{
	struct dirent	*dir;
	int				match_len;

	dir = readdir(d);
	match_len = ft_strlen(match);
	while (dir != NULL)
	{
		if (ft_strnequ(match, dir->d_name, match_len) == true)
		{
			if (check_and_add_match(matchlst, match, dir->d_name, path)
			== FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		dir = readdir(d);
	}
	return (FUNCT_SUCCESS);
}

int			auto_get_filelst(char *match, char *path, t_list **matchlst)
{
	DIR				*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		if (check_dir(dir, match, matchlst, path) == FUNCT_ERROR)
		{
			closedir(dir);
			return (FUNCT_ERROR);
		}
		closedir(dir);
	}
	return (FUNCT_SUCCESS);
}
