/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_valid_name.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/18 16:31:00 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/07 16:42:59 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool		tools_is_valid_name_char(char c)
{
	return (ft_isalnum(c) == true || ft_strchr("*-_~!@#$%^.,[]+?", c) != NULL);
}

bool		tools_is_valid_name(char *str)
{
	int i;

	if (str == NULL || *str == '\0' || *str == '=')
		return (false);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (tools_is_valid_name_char(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
