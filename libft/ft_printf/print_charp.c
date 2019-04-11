/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_charp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/08 16:14:44 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:40:26 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		put_padding(t_fmt fmt, int slen)
{
	if (!fmt.MIN && (!fmt.ZERO || !(fmt.prec == -1 || fmt.prec == 0)))
		print_padding(fmt.fd, ' ', (fmt.width - slen));
	if (!fmt.MIN && fmt.ZERO)
		print_padding(fmt.fd, '0', (fmt.width - slen));
}

int				print_charp(t_fmt fmt, char *str)
{
	int	slen;

	if (str)
		slen = pf_strlen(str);
	else
		return (print_charp(fmt, "(null)"));
	if (fmt.prec != -1 && fmt.prec < slen)
		slen = fmt.prec;
	put_padding(fmt, slen);
	if (fmt.prec == -1)
		pf_putstr(fmt.fd, str);
	else
		pf_putnstr(fmt.fd, str, fmt.prec);
	if (fmt.MIN)
		print_padding(fmt.fd, ' ', (fmt.width - slen));
	if (fmt.width > slen)
		slen = fmt.width;
	return (slen);
}
