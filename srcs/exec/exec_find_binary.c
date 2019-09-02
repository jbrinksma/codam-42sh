/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_find_binary.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 15:16:46 by tde-jong       #+#    #+#                */
/*   Updated: 2019/08/22 11:30:40 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <dirent.h>

static int	get_paths(t_envlst *envlst, char ***paths)
{
	char *path_value;

	path_value = env_getvalue("PATH", envlst);
	if (path_value == NULL || *path_value == '\0')
		return (FUNCT_FAILURE);
	*paths = ft_strsplit(path_value, ':');
	if (*paths == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	return (FUNCT_SUCCESS);
}

static int	check_dir(DIR *d, char *filename, char *path, char **binary)
{
	struct dirent	*dir;
	char			file_status;

	dir = readdir(d);
	while (dir != NULL)
	{
		*binary = ft_joinstrcstr(path, '/', filename);
		if (*binary == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		if (ft_strequ(filename, dir->d_name) == true)
		{
			file_status = ft_is_regular_file(*binary);
			if (file_status == true)
				return (FUNCT_SUCCESS);
			ft_strdel(&(*binary));
			if (file_status == -1)
				return (err_ret_exit(E_STAT_STR, EXIT_FAILURE));
			return (FUNCT_SUCCESS);
		}
		else
			ft_strdel(&(*binary));
		dir = readdir(d);
	}
	return (FUNCT_FAILURE);
}

static int	check_paths(char **paths, char *filename, char **binary)
{
	DIR				*dir;
	size_t			i;

	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		dir = opendir(paths[i]);
		if (dir != NULL)
		{
			if (check_dir(dir, filename, paths[i], binary) == FUNCT_ERROR)
			{
				closedir(dir);
				ft_strarrdel(&paths);
				return (FUNCT_ERROR);
			}
			closedir(dir);
			if (*binary != NULL)
				return (FUNCT_SUCCESS);
		}
		i++;
	}
	return (FUNCT_FAILURE);
}

int			find_binary(char *filename, t_envlst *envlst, char **binary)
{
	char			**paths;

	paths = NULL;
	if (get_paths(envlst, &paths) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (check_paths(paths, filename, binary) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	ft_strarrdel(&paths);
	if (*binary == NULL)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}

int			exec_find_binary(char *filename, t_vshdata *data, char **binary)
{
	int		ret;
	char	*bin_dup;

	ret = hash_check(data, filename, binary);
	if (ret == FUNCT_SUCCESS)
		return (FUNCT_SUCCESS);
	if (ret == FUNCT_ERROR)
		return (FUNCT_ERROR);
	ret = find_binary(filename, data->envlst, binary);
	if (ret == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ret == FUNCT_FAILURE)
	{
		ft_eprintf(E_P_CMD_NOT_FOUND, filename);
		return (err_ret_exit(NULL, EXIT_NOTFOUND));
	}
	bin_dup = ft_strdup(*binary);
	if (bin_dup == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	if (hash_ht_insert(data, filename, bin_dup, HASH_HIT) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
