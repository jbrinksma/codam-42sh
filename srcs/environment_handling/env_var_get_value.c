/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var_get_value.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 18:45:30 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/27 15:51:34 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char		*env_var_get_value(char *var_key, char **vararray)
{
	int		var_len;
	int		env_i;

	var_len = ft_strlen(var_key);
	env_i = 0;
	while (vararray[env_i] != NULL)
	{
		if (ft_strncmp(var_key, vararray[env_i], var_len) == 0 &&
			vararray[env_i][var_len] == '=')
			return (ft_strchr(vararray[env_i], '=') + 1);
		env_i++;
	}
	return (NULL);
}
