/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/01 16:36:22 by omulder        #+#    #+#                */
/*   Updated: 2019/07/23 15:21:22 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int		len;
	t_fmt	fmt;

	len = 0;
	fmt.fd = STDOUT_FILENO;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			fmt = reset_fmt(fmt);
			fmt = check_format(fmt, &format, ap);
			len += print_var(fmt, ap);
		}
		else
		{
			pf_putchar(fmt.fd, *format);
			format++;
			len++;
		}
	}
	va_end(ap);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list ap;
	int		len;
	t_fmt	fmt;

	len = 0;
	fmt.fd = fd;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			fmt = reset_fmt(fmt);
			fmt = check_format(fmt, &format, ap);
			len += print_var(fmt, ap);
		}
		else
		{
			pf_putchar(fd, *format);
			format++;
			len++;
		}
	}
	va_end(ap);
	return (len);
}

int		ft_eprintf(const char *format, ...)
{
	va_list ap;
	int		len;
	t_fmt	fmt;

	len = 0;
	fmt.fd = STDERR_FILENO;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			fmt = reset_fmt(fmt);
			fmt = check_format(fmt, &format, ap);
			len += print_var(fmt, ap);
		}
		else
		{
			pf_putchar(fmt.fd, *format);
			format++;
			len++;
		}
	}
	va_end(ap);
	return (len);
}
