/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_special.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 15:22:34 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:34 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_special(t_fmt fmt, double num)
{
	if (num == (1.0 / 0.0))
	{
		fmt.conv = 's';
		if (pf_isupper(fmt.conv))
			return (print_charp(fmt, "INF"));
		return (print_charp(fmt, "inf"));
	}
	else if (num == (-1.0 / 0.0))
	{
		fmt.conv = 's';
		if (pf_isupper(fmt.conv))
			return (print_charp(fmt, "-INF"));
		return (print_charp(fmt, "-inf"));
	}
	else if (num != num)
	{
		fmt.conv = 's';
		if (pf_isupper(fmt.conv))
			return (print_charp(fmt, "NAN"));
		return (print_charp(fmt, "nan"));
	}
	return (0);
}
