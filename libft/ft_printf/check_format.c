/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_format.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 12:01:23 by omulder        #+#    #+#                */
/*   Updated: 2019/02/20 20:54:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	check_format(t_fmt fmt, const char **format, va_list ap)
{
	fmt = find_options(format, fmt);
	fmt = find_width(format, fmt, ap);
	fmt = find_precision(format, fmt, ap);
	fmt = find_length(format, fmt);
	fmt = find_conversion(format, fmt);
	return (fmt);
}
