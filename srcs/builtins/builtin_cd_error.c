/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_error.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 17:54:03 by omulder        #+#    #+#                */
/*   Updated: 2019/08/02 17:57:39 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		cd_alloc_error(void)
{
	ft_eprintf("cd: failed to allocate memory\n");
	return (FUNCT_ERROR);
}

int		cd_print_usage(void)
{
	ft_eprintf("cd: usage: cd [-L|-P] [dir]\n");
	return (FUNCT_ERROR);
}

int		cd_invalid_option(char c)
{
	ft_eprintf("vsh: cd: -%c: invalid option\n", c);
	return (cd_print_usage());
}

int		cd_change_dir_error(char *usedpath, char *argpath, char **newpath,
			char **currpath)
{
	ft_putstr_fd("vsh: cd: ", STDERR_FILENO);
	if (usedpath == NULL)
		ft_eprintf("could not get current working directory parsing: %s\n",
			argpath);
	else if (access(usedpath, F_OK) == -1)
		ft_eprintf("no such file or directory: %s\n", argpath);
	else if (access(usedpath, R_OK) == -1)
		ft_eprintf("permission denied: %s\n", argpath);
	else
		ft_eprintf("not a directory: %s\n", argpath);
	ft_strdel(currpath);
	ft_strdel(newpath);
	g_state->exit_code = EXIT_FAILURE;
	return (FUNCT_ERROR);
}
