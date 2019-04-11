/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_charp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 13:51:24 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 16:00:02 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_charp(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (c == 's')
	{
		if (l != 'l')
			return (1);
	}
	return (0);
}
