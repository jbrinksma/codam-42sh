/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_get_cmdlst.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/10 12:53:34 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:40:42 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <dirent.h>

int			auto_add_tolst(t_list **matchlst, char *filename)
{
	t_list *new;

	if (auto_check_dups(*matchlst, filename) == true)
		return (FUNCT_SUCCESS);
	new = ft_lstnew(filename, ft_strlen(filename) + 1);
	if (new == NULL)
		return (err_ret(E_ALLOC_STR));
	ft_lstadd(matchlst, new);
	return (FUNCT_SUCCESS);
}

static int	file_exec_check(char *path, char *filename)
{
	int			file_status;
	char		*bin_path;
	int			ret;

	bin_path = ft_joinstrcstr(path, '/', filename);
	if (bin_path == NULL)
		return (err_ret(E_ALLOC_STR));
	file_status = ft_is_regular_file(bin_path);
	if (file_status == -1)
		file_status = false;
	ret = FUNCT_SUCCESS;
	if (file_status == false)
		ret = FUNCT_FAILURE;
	else if (access(bin_path, X_OK) != 0)
		ret = FUNCT_FAILURE;
	ft_strdel(&bin_path);
	return (ret);
}

static int	check_dir(DIR *d, char *match, char *path, t_list **matchlst)
{
	struct dirent	*dir;
	int				match_len;
	int				file_status;

	dir = readdir(d);
	match_len = ft_strlen(match);
	while (dir != NULL)
	{
		if (ft_strnequ(match, dir->d_name, match_len) == true)
		{
			file_status = file_exec_check(path, dir->d_name);
			if (file_status == FUNCT_ERROR)
				return (FUNCT_ERROR);
			if (file_status == FUNCT_SUCCESS &&
				auto_add_tolst(matchlst, dir->d_name) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		dir = readdir(d);
	}
	return (FUNCT_SUCCESS);
}

static int	match_files(char *match, char **paths, t_list **matchlst)
{
	DIR				*dir;
	size_t			i;

	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		dir = opendir(paths[i]);
		if (dir != NULL)
		{
			if (check_dir(dir, match, paths[i], matchlst) == FUNCT_ERROR)
			{
				closedir(dir);
				ft_strarrdel(&paths);
				return (FUNCT_ERROR);
			}
			closedir(dir);
		}
		i++;
	}
	return (FUNCT_SUCCESS);
}

/*
**	auto_get_cmdlst creates a list of matching cmd's with match
**	It first retrieves all directories from the PATH variable
**	It then opens all directories and tries to find matches with match
**	After that it also checks if any builtins match with match
*/

int			auto_get_cmdlst(char *match, t_envlst *envlst, t_list **matchlst)
{
	char			**paths;

	paths = NULL;
	if (tools_get_paths(envlst, &paths) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (match_files(match, paths, matchlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (auto_match_builtins(match, matchlst, ft_strlen(match)) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	ft_strarrdel(&paths);
	return (FUNCT_SUCCESS);
}
