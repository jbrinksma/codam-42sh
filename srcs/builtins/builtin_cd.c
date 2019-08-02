/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/30 12:41:21 by omulder        #+#    #+#                */
/*   Updated: 2019/08/02 15:27:59 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**  cd: usage: cd [-L|-P] [dir]
**  TODO:
**	- Handling -L and -P flags when changing dirs.
**	- Parsing -L and -P flags correctly.
**  FUNCTIONALITY:
**  - NO ARGS:
**  	cd to HOME
**  - CD -:
**  	cd to OLDPWD
**  - CD --:
**  	cd to HOME
**  - DISPLAY DIRECTORY:
** 	Only when cd -: Write path to stdout if chdir was succesful.
**  - MORE THAN ONE DIR:
**  	Any additional arguments following directory are ignored.
**  - FLAG P:
**  	Do not follow symbolic links (parse physical address).
**  - RETURN:
**  	0 on success, else -1
**  ERRORS
**  - When OLDPWD is not set
**  - When HOME is not set
**  - When cwd doesn't return correctly.
*/

static int	cd_parse_flags(char **args, char *cd_flag, int *countflags)
{
	int i;
	int j;

	j = 1;
	while (args[j] != NULL && args[j][0] == '-')
	{
		if (args[j][1] == '\0' || ft_strequ(args[j], "--"))
			return (FUNCT_SUCCESS);
		i = 1;
		while (args[j][i] != 0)
		{
			if (args[j][i] == 'P')
				*cd_flag = BUILTIN_CD_UP;
			else if (args[j][i] == 'L')
				*cd_flag = BUILTIN_CD_UL;
			else
				return (cd_invalid_option(args[j][i]));
			i++;
		}
		j++;
	}
	*countflags = j - 1;
	return (FUNCT_SUCCESS);
}

static int	cd_parse_dash(char *newpath, t_envlst *envlst, char cd_flag,
				char *var)
{
	if (newpath == NULL || *newpath == '\0')
	{
		ft_eprintf("vsh: cd: %s: not set\n", var);
		return (FUNCT_ERROR);
	}
	return (builtin_cd_change_dir(newpath, envlst, cd_flag,
		(ft_strequ(var, "HOME") == 1) ? false : true));
}

int			builtin_cd(char **args, t_envlst *envlst)
{
	char	cd_flag;
	char	*newpath;
	int		flags;

	cd_flag = BUILTIN_CD_UL;
	flags = 0;
	if (cd_parse_flags(args, &cd_flag, &flags) == 0)
		return (FUNCT_ERROR);
	if (args[1 + flags] == NULL || ft_strequ(args[1 + flags], "--") == 1)
	{
		newpath = env_getvalue("HOME", envlst);
		return (cd_parse_dash(newpath, envlst, cd_flag, "HOME"));
	}
	if (ft_strequ(args[1 + flags], "-") == 1)
	{
		newpath = env_getvalue("OLDPWD", envlst);
		return (cd_parse_dash(newpath, envlst, cd_flag, "OLDPWD"));
	}
	return (builtin_cd_change_dir(args[1 + flags], envlst, cd_flag, false));
}
