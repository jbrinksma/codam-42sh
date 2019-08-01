/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_valid_identifier.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/18 16:31:00 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/31 12:27:07 by mavan-he      ########   odam.nl         */
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
		if (tools_isidentifierchar(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
