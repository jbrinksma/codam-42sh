/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_unsigned.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/11 13:43:34 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 14:36:26 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_unsigned(t_fmt fmt)
{
	char c;

	c = fmt.conv;
	if (c == 'u' || c == 'U')
		return (1);
	if (c == 'o' || c == 'O')
		return (1);
	if (c == 'x' || c == 'X')
		return (1);
	if (c == 'p')
		return (1);
	return (0);
}
