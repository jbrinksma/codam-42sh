/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_fdnumstr.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 20:18:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/05 09:31:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Check if the string could be a valid file descriptor.
**	(no negative number, digits only)
*/

bool	tools_is_fdnumstr(char *str)
{
	int	i;

	if (str == NULL || *str == '\0')
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
