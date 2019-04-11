/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_base.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 15:40:23 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 12:45:51 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_base(t_fmt fmt)
{
	char c;

	c = fmt.conv;
	if (c == 'x' || c == 'X')
		return (16);
	if (c == 'p')
		return (16);
	if (c == 'o' || c == 'O')
		return (8);
	return (10);
}
