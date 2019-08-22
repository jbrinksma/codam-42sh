/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_error.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 17:54:03 by omulder        #+#    #+#                */
/*   Updated: 2019/08/22 11:06:56 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		cd_alloc_error(void)
{
	ft_eprintf(E_N_ALLOC_STR, "cd");
	return (FUNCT_ERROR);
}

int		cd_print_usage(void)
{
	ft_eprintf(U_CD);
	return (FUNCT_ERROR);
}

int		cd_invalid_option(char c)
{
	ft_eprintf(E_N_P_INV_OPT, "cd", c);
	return (cd_print_usage());
}

int		cd_change_dir_error(char *usedpath, char *argpath, char **newpath,
			char **currpath)
{
	if (usedpath == NULL)
		ft_eprintf(E_CD_CNG_DIR, argpath);
	else if (access(usedpath, F_OK) == -1)
		ft_eprintf(E_CD_NO_SUCH, argpath);
	else if (access(usedpath, R_OK) == -1)
		ft_eprintf(E_N_PER_DEN_P, "cd", argpath);
	else
		ft_eprintf(E_CD_NOT_DIR, argpath);
	ft_strdel(currpath);
	ft_strdel(newpath);
	g_state->exit_code = EXIT_FAILURE;
	return (FUNCT_ERROR);
}
