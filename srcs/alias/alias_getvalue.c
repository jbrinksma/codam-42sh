/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alias_getvalue.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/06 15:51:20 by tde-jong       #+#    #+#                */
/*   Updated: 2019/08/06 15:54:34 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

char		*alias_getvalue(char *var_key, t_aliaslst *aliaslst)
{
	t_aliaslst	*probe;
	int			var_len;

	probe = aliaslst;
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
