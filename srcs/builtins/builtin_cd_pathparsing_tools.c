/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_pathparsing_tools.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/02 14:58:14 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/02 17:48:18 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Returns size of parsed token (`.` or `./`)
*/

static int	cd_stayhere(char *argpath)
{
	if (argpath[1] == '/')
		return (2);
	return (1);
}

/*
**	Subtracts last directory of `newpath`.
**	Returns size of parsed token (`../` or `..`)
*/

static int	cd_gobackone(char **newpath, char *argpath)
{
	int i;

	i = ft_strlen(*newpath);
	if (i > 0)
		i--;
	while ((*newpath)[i] == '/' && i > 0)
	{
		(*newpath)[i] = '\0';
		i--;
	}
	while ((*newpath)[i] != '/' && i > 0)
	{
		(*newpath)[i] = '\0';
		i--;
	}
	if (argpath[2] == '/')
		return (3);
	return (2);
}

/*
**	Adds seperator if necessary, then adds argpath directory.
**	Returns size of parsed token (dirname).
*/

static int	cd_addsymdir(char **newpath, char *argpath)
{
	int i;
	int	arg_i;

	i = ft_strlen(*newpath);
	if (i != 0 && (*newpath)[i - 1] != '/')
	{
		(*newpath)[i] = '/';
		i++;
	}
	arg_i = 0;
	while (argpath[arg_i] != '/' && argpath[arg_i] != '\0')
	{
		(*newpath)[i] = argpath[arg_i];
		i++;
		arg_i++;
	}
	(*newpath)[i] = '\0';
	return (arg_i);
}

/*
**	Safety check to remove any trailing slashes when argpath is completely
**	parsed.
*/

static void	cd_removetrailingslash(char **newpath)
{
	int i;

	i = ft_strlen(*newpath);
	if (i > 0)
		i--;
	while (i > 0 && (*newpath)[i] == '/')
	{
		(*newpath)[i] = '\0';
		i--;
	}
}

/*
**	Parser argpath. Every loop, newpath is altered based on the next
**	token that is received in argpath. A token can be the following regex's:
**	"../?", "./?" and "[DIRCHARS]+/?".
**
**	Any slash in front of the token is removed.
**	KEEP IN MIND: the argpath isn't actually tokenized, this is
**	all based on strcmps.
**
**	If during the loop any sub-newpath does not equal into a valid argument
**	for chdir, FUNCT_FAILURE is returned.
*/

void		builtin_cd_create_newpath(char **newpath, char *argpath)
{
	struct stat	ptr;
	int			i;

	i = 0;
	while (argpath[i] != '\0')
	{
		while (argpath[i] == '/')
			i++;
		#ifdef DEBUG
		ft_printf("CURRENT:\t%s\nTO HANDLE:\t%s\n\n", *newpath, &argpath[i]);
		#endif
		if (argpath[i] != '\0')
		{
			if (ft_strequ(&argpath[i], ".") || ft_strnequ(&argpath[i], "./", 2))
				i += cd_stayhere(&argpath[i]);
			else if (ft_strequ(&argpath[i], "..")
				|| ft_strnequ(&argpath[i], "../", 3))
				i += cd_gobackone(newpath, &argpath[i]);
			else
				i += cd_addsymdir(newpath, &argpath[i]);
		}
		if (stat(*newpath, &ptr) == -1 || S_ISDIR(ptr.st_mode) == false
			|| access(*newpath, R_OK) == -1)
			break ;
	}
	cd_removetrailingslash(newpath);
}
