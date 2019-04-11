/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_double.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 13:50:43 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 15:56:20 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_double(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (l != 'L')
	{
		if (c == 'e' || c == 'E')
			return (1);
		if (c == 'f' || c == 'F')
			return (1);
		if (c == 'g' || c == 'G')
			return (1);
		if (c == 'a' || c == 'A')
			return (1);
	}
	return (0);
}
