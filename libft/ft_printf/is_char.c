/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_char.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 13:51:02 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 16:06:40 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_char(t_fmt fmt)
{
	char	c;

	c = fmt.conv;
	if (c == 'c' || c == 'C')
	{
		return (1);
	}
	return (0);
}
