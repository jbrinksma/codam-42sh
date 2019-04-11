/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_precision.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 12:03:11 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:04 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	find_precision(const char **format, t_fmt fmt, va_list ap)
{
	if (**format == '.')
	{
		(*format)++;
		if (pf_isdigit(**format))
			fmt.prec = pf_atoi(*format);
		else
			fmt.prec = 0;
		while (pf_isdigit(**format))
			(*format)++;
		if (**format == '*')
		{
			fmt.prec = va_arg(ap, int);
			if (fmt.prec < 0)
				fmt.prec = -1;
			(*format)++;
		}
	}
	return (fmt);
}
