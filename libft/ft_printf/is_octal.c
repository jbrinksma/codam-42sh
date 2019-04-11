/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_octal.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 12:42:28 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 14:56:33 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_octal(t_fmt fmt)
{
	char c;

	c = fmt.conv;
	if (c == 'o' || c == 'O')
		return (1);
	return (0);
}
