/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_signed.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 14:06:44 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 14:36:03 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_signed(t_fmt fmt)
{
	char c;

	c = fmt.conv;
	if (c == 'd' || c == 'i' || c == 'D')
		return (1);
	return (0);
}
