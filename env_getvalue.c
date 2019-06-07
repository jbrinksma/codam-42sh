/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_getvalue.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/03 18:45:30 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/06 14:52:37 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char		*env_getvalue(char *var_key, t_envlst *envlst)
{
	t_envlst	*probe;
	int			var_len;

	probe = envlst;
	var_len = ft_strlen(var_key);
	while (probe != NULL)
	{
		if (ft_strnequ(var_key, probe->var, var_len) &&
			probe->var[var_len] == '=')
			return (ft_strchr(probe->var, '=') + 1);
		probe = probe->next;
	}
	return (NULL);
}
