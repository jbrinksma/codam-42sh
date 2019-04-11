/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_width.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 12:04:30 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:04 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	find_width(const char **format, t_fmt fmt, va_list ap)
{
	while (is_flag(**format))
		(*format)++;
	if ((pf_isdigit(**format) && **format != '0') || **format == '*')
	{
		if (pf_isdigit(**format))
			fmt.width = pf_atoi(*format);
		while (pf_isdigit(**format))
			(*format)++;
		if (**format == '*')
		{
			fmt.width = va_arg(ap, int);
			if (fmt.width < 0)
			{
				fmt.MIN = 1;
				fmt.width = pf_abs(fmt.width);
			}
		}
		while (**format == '*')
			(*format)++;
		if (pf_isdigit(**format) && **format != '0')
			fmt.width = pf_atoi(*format);
		while (pf_isdigit(**format))
			(*format)++;
	}
	return (fmt);
}
