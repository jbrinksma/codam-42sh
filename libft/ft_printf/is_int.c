/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_int.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 13:50:19 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 14:22:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_int(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (c == 'd' || c == 'i')
	{
		if (l == -1)
			return (1);
	}
	return (0);
}
