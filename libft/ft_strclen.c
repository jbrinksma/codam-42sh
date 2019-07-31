/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 09:34:22 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/30 17:36:00 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Return length string until 'c' or '\0' is found.
**	This can be used by strncmp to find a match.
*/

int		ft_strclen(const char *arg, char c)
{
	int i;

	i = 0;
	while (arg[i] != c && arg[i] != '\0')
		i++;
	return (i);
}
