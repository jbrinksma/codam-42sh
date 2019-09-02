/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_addvalue.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/30 15:56:30 by omulder        #+#    #+#                */
/*   Updated: 2019/08/19 10:56:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		env_add_extern_value(t_vshdata *data, char *name, char *value)
{
	char		*var;
	int			ret;

	var = ft_strjoinfree_s2(name, ft_strjoin("=", value));
	if (var == NULL)
		return (FUNCT_ERROR);
	ret = builtin_assign(var, data, ENV_EXTERN);
	ft_strdel(&var);
	return (ret);
}
