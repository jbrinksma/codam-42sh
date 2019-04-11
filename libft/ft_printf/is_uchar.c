/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_uchar.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/20 13:24:39 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 15:06:14 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_uchar(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (c == 'o' || c == 'u' || c == 'x' || c == 'X')
	{
		if (l == ('h' + 'h'))
			return (1);
		return (0);
	}
	return (0);
}
