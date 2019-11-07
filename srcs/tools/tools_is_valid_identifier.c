/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_valid_identifier.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/18 16:31:00 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/06 13:49:22 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_is_valid_identifier(char *str)
{
	int i;

	if (str == NULL || *str == '\0' || *str == '=')
		return (false);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (tools_is_identifier_char(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
