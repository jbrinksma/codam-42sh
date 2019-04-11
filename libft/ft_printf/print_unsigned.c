/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_unsigned.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 11:17:53 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:43:23 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	typecast(t_fmt fmt, unsigned long long n)
{
	if (is_uchar(fmt))
		return ((unsigned char)n);
	if (is_ushort(fmt))
		return ((unsigned short)n);
	if (is_uint(fmt))
		return ((unsigned int)n);
	if (is_ulong(fmt))
		return ((unsigned long long)n);
	if (is_voidp(fmt))
		return ((unsigned long long)n);
	return ((unsigned long long)n);
}

static t_fmt				set_prec(t_fmt fmt, unsigned long long n, int ilen)
{
	if (is_voidp(fmt))
		fmt.HASH = 1;
	if (fmt.HASH && is_octal(fmt) && fmt.prec < (ilen + 1))
	{
		if (n == 0)
			ilen--;
		fmt.prec = ilen + 1;
	}
	return (fmt);
}

int							print_unsigned(t_fmt fmt, unsigned long long n)
{
	int ilen;
	int oldprec;

	n = (typecast(fmt, n));
	ilen = pf_ulonglen(n, find_base(fmt));
	oldprec = fmt.prec;
	fmt = set_prec(fmt, n, ilen);
	if (fmt.prec > ilen)
		ilen = fmt.prec;
	put_upaddingandsign(fmt, n, ilen, oldprec);
	if (!fmt.MIN && fmt.prec != -1)
		print_padding(fmt.fd, '0', (fmt.prec - pf_ulonglen(n, find_base(fmt))));
	if (fmt.MIN && (n != 0 || is_voidp(fmt)))
		print_prehex(fmt);
	if (fmt.MIN && fmt.prec != -1)
		print_padding(fmt.fd, '0', (fmt.prec - pf_ulonglen(n, find_base(fmt))));
	if (!(fmt.prec == 0 && n == 0))
		pf_putulong_base(fmt.fd, n, find_base(fmt), find_case(fmt));
	put_backpadding(fmt, n, ilen);
	return (printed_uchars(fmt, n));
}
