/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_hex.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 15:52:31 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 17:01:39 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_hex(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (c == 'x' || c == 'X')
	{
		if (l != 'j')
			return (1);
	}
	if (c == 'p')
	{
		return (1);
	}
	return (0);
}
