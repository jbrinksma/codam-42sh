/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_type.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/06 13:09:18 by tde-jong       #+#    #+#                */
/*   Updated: 2019/08/08 11:52:46 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	is_builtin(char *name)
{
	if (ft_strequ(name, "echo") || ft_strequ(name, "exit") ||
		ft_strequ(name, "cd") || ft_strequ(name, "export") ||
		ft_strequ(name, "set") || ft_strequ(name, "unset") ||
		ft_strequ(name, "history") || ft_strequ(name, "type") ||
		ft_strequ(name, "alias") || ft_strequ(name, "unalias"))
	{
		ft_printf("%s is a shell builtin\n", name);
		return (true);
	}
	return (false);
}

static bool	is_alias(char *name, t_aliaslst *aliaslst)
{
	char *value;

	value = alias_getvalue(name, aliaslst);
	if (value == NULL)
		return (false);
	ft_printf("%s is an alias for %s\n", name, value);
	return (true);
}

static bool	is_binary(char *name, t_envlst *envlst)
{
	char	*binary;

	binary = NULL;
	if (find_binary(name, envlst, &binary) == FUNCT_SUCCESS && binary != NULL)
	{
		ft_printf("%s is %s\n", name, binary);
		ft_strdel(&binary);
		return (true);
	}
	return (false);
}

static bool	is_executable(char *name)
{
	char	*ret;
	char	*currpath;

	if (ft_strnequ(name, "./", 2) == false &&
		ft_strnequ(name, "../", 3) == false)
		return (false);
	currpath = getcwd(NULL, 0);
	if (currpath == NULL)
	{
		ft_eprintf("vsh: cannot get current working directory\n");
		return (false);
	}
	ret = builtin_cd_create_newpath_wrap(currpath, name);
	ft_strdel(&currpath);
	if (ret == NULL)
		return (false);
	if (access(ret, F_OK) == -1 || access(ret, X_OK) == -1)
		return (false);
	ft_strdel(&ret);
	ft_printf("%s is %s\n", name, name);
	return (true);
}

void		builtin_type(char **args, t_envlst *envlst, t_aliaslst *aliaslst)
{
	size_t	i;

	g_state->exit_code = EXIT_SUCCESS;
	i = 1;
	while (args[i] != NULL)
	{
		if (is_builtin(args[i]) == false &&
			is_alias(args[i], aliaslst) == false &&
			is_binary(args[i], envlst) == false &&
			is_executable(args[i]) == false)
		{
			g_state->exit_code = EXIT_FAILURE;
			ft_eprintf("vsh: type: %s: not found\n", args[i]);
		}
		i++;
	}
}
