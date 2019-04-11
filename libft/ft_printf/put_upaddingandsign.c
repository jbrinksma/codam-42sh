/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_upaddingandsign.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 16:06:31 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:41:58 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_upaddingandsign(t_fmt fmt, unsigned long long num, int ilen, int op)
{
	if (!fmt.MIN && (!fmt.ZERO || (fmt.prec != -1)))
	{
		if (fmt.HASH && is_hex(fmt) && (num != 0 || fmt.conv == 'p'))
		{
			print_padding(fmt.fd, ' ', (fmt.width - ilen) - 2);
			print_prehex(fmt);
		}
		else if (!(fmt.HASH && fmt.ZERO && op == -1))
			print_padding(fmt.fd, ' ', (fmt.width - ilen));
	}
	if (num == 0 && fmt.prec == 0 && fmt.width != -1)
		pf_putchar(fmt.fd, ' ');
	if (!fmt.MIN && fmt.ZERO && fmt.prec == -1)
	{
		if (fmt.HASH && is_hex(fmt) && (num != 0 || fmt.conv == 'p'))
		{
			print_prehex(fmt);
			print_padding(fmt.fd, '0', (fmt.width - ilen) - 2);
		}
		else
			print_padding(fmt.fd, '0', (fmt.width - ilen));
	}
	else if (!fmt.MIN && fmt.ZERO && fmt.HASH && fmt.conv == 'o' && op == -1)
		print_padding(fmt.fd, '0', (fmt.width - ilen));
}
