/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_case.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 15:39:57 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 12:44:12 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_case(t_fmt fmt)
{
	char c;

	c = fmt.conv;
	if (c == 'x' || c == 'p')
		return (0);
	return (1);
}
