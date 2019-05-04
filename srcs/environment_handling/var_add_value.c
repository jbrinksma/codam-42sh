/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_add_value.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/03 15:13:44 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/04 13:56:03 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		var_add_value(char *var_key, char *var_value, char ***vararray)
{
	int		ret;
	char	**new_vararray;
	int		i;

	ret = var_set_value(var_key, var_value, *vararray);
	if (ret != FUNCT_FAILURE)
		return (ret == FUNCT_SUCCESS ? FUNCT_SUCCESS : FUNCT_ERROR);
	new_vararray = (char**)ft_memalloc(sizeof(char*) *
	(ft_arraylen(*vararray) + 2));
	if (new_vararray == NULL)
		return (FUNCT_ERROR);
	i = 0;
	while ((*vararray)[i] != NULL)
	{
		new_vararray[i] = (*vararray)[i];
		i++;
	}
	new_vararray[i] = var_join_key_value(var_key, var_value);
	if (new_vararray[i] == NULL)
		return (FUNCT_ERROR);
	i++;
	free(*vararray);
	*vararray = new_vararray;
	return (FUNCT_SUCCESS);
}
