/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/10 20:09:51 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 14:56:20 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_long(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (is_int(fmt))
	{
		if (l == 'l' || l == ('l' + 'l') || l == 'j')
			return (1);
		if (l == 'z')
			return (1);
	}
	if (c == 'D')
		return (1);
	return (0);
}
