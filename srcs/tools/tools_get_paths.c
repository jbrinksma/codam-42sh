/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_get_paths.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/10 13:04:04 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:41:32 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		tools_get_paths(t_envlst *envlst, char ***paths)
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
