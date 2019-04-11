/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_fmt_expo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 15:24:34 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 15:25:13 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	prepare_fmt_exp(t_fmt fmt, t_fmt copy, int ret)
{
	fmt.width = -1;
	fmt.SPACE = 0;
	fmt.MIN = copy.MIN;
	if (fmt.MIN)
		fmt.width = copy.width - ret;
	fmt.PLUS = 0;
	fmt.prec = copy.prec;
	fmt.HASH = 0;
	return (fmt);
}
