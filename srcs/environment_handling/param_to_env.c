/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   param_to_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 18:45:30 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/25 17:08:11 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char		*param_to_env(char *parameter, char **vshenviron)
{
	int		param_len;
	int		env_i;
	int		i;

	param_len = ft_strlen(parameter);
	env_i = 0;
	while (vshenviron[env_i] != NULL)
	{
		if (ft_strncmp(parameter, vshenviron[env_i], param_len) == 0 &&
			vshenviron[env_i][param_len] == '=')
		{
			i = 0;
			while (vshenviron[env_i][i] != '=')
				i++;
			return (&vshenviron[env_i][i + 1]);
		}
		env_i++;
	}
	return (NULL);
}
