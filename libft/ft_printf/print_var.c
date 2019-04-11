/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_var.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 13:52:31 by omulder        #+#    #+#                */
/*   Updated: 2019/02/28 15:57:55 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_var(t_fmt fmt, va_list ap)
{
	if (fmt.conv == '\0')
		return (0);
	if (fmt.conv == '%')
		return (print_char(fmt, '%'));
	if (is_unsigned(fmt))
		return (print_unsigned(fmt, va_arg(ap, unsigned long long)));
	if (is_signed(fmt))
		return (print_signed(fmt, va_arg(ap, long long)));
	if (is_double(fmt))
		return (print_double(fmt, va_arg(ap, double)));
	if (is_ldouble(fmt))
		return (print_ldouble(fmt, va_arg(ap, long double)));
	if (is_char(fmt))
		return (print_char(fmt, va_arg(ap, unsigned int)));
	if (is_charp(fmt))
		return (print_charp(fmt, va_arg(ap, char*)));
	if (is_wcharp(fmt))
		return (print_wcharp(fmt, va_arg(ap, wchar_t*)));
	return (print_char(fmt, fmt.conv));
}
