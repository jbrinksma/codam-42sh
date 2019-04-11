/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_ushort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/20 12:56:45 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 14:58:08 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_ushort(t_fmt fmt)
{
	int		l;
	char	c;

	c = fmt.conv;
	l = fmt.length;
	if (c == 'o' || c == 'u' || c == 'x' || c == 'X')
	{
		if (l == 'h')
			return (1);
	}
	return (0);
}
