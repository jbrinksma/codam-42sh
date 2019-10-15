/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_get_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/15 20:37:03 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/01 12:29:04 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	shell_add_cwd_to_env(t_vshdata *data)
{
	char *path;
	char *cwd;
	char *new_path;

	path = env_getvalue("PATH", data->envlst);
	cwd = getcwd(NULL, 0);
	if (path == NULL || cwd == NULL)
		return (err_ret_exit(E_NOT_CUR_DIR, EXIT_FAILURE));
	new_path = ft_strjoinchr(cwd, ':');
	if (new_path == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	ft_strdel(&cwd);
	cwd = ft_strjoinfree_s2("PATH=", new_path);
	if (cwd == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	new_path = ft_strjoinfree_s1(cwd, path);
	if (new_path == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	if (builtin_assign(new_path, data, ENV_LOCAL) == FUNCT_ERROR)
	{
		ft_strdel(&new_path);
		return (FUNCT_ERROR);
	}
	ft_strdel(&new_path);
	return (FUNCT_SUCCESS);
}

static int	shell_search_env_paths(char *filename,
			t_vshdata *data, char **filepath)
{
	int		ret;

	ret = find_binary(filename, data->envlst, filepath);
	if (ret == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (ret == FUNCT_FAILURE)
	{
		ft_eprintf(E_NO_SUCH_P, filename);
		return (err_ret_exit(NULL, EXIT_NOTFOUND));
	}
	return (FUNCT_SUCCESS);
}

int			shell_get_path(t_vshdata *data, char *filepath, char **path)
{
	if (filepath[0] != '/' && ft_strnequ(filepath, "./", 2) == 0 &&
		ft_strnequ(filepath, "../", 3) == 0)
	{
		if (shell_add_cwd_to_env(data) == FUNCT_ERROR || shell_search_env_paths(
			filepath, data, path) != FUNCT_SUCCESS)
			return (FUNCT_ERROR);
		return (FUNCT_SUCCESS);
	}
	else
	{
		*path = ft_strdup(filepath);
		if (*path == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	}
	return (FUNCT_SUCCESS);
}
