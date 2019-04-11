/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_fmt.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/18 12:54:38 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 15:00:53 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	reset_fmt(t_fmt fmt)
{
	int i;

	i = 0;
	while (i < 6)
	{
		fmt.opt[i] = 0;
		i++;
	}
	fmt.width = -1;
	fmt.prec = -1;
	fmt.length = -1;
	fmt.conv = '\0';
	return (fmt);
}
