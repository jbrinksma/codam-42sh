/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_set_value.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 18:45:30 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/27 15:51:17 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		env_var_set_value(char *var_key, char *var_value, char **vararray)
{
	int		var_len;
	int		env_i;

	var_len = ft_strlen(var_key);
	env_i = 0;
	while (vararray[env_i] != NULL)
	{
		if (ft_strncmp(var_key, vararray[env_i], var_len) == 0 &&
			vararray[env_i][var_len] == '=')
		{
			free(vararray[env_i]);
			vararray[env_i] = env_var_join_key_value(var_key, var_value);
			if (vararray[env_i] == NULL)
				return (FUNCT_ERROR);
			return (FUNCT_SUCCESS);
		}
		env_i++;
	}
	return (FUNCT_FAILURE);
}
