/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_paddingandsign.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 16:07:28 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:41:52 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		put_paddingandsign(t_fmt fmt, long long num, int ilen)
{
	if (!fmt.MIN && (!fmt.ZERO || fmt.prec != -1))
		print_padding(fmt.fd, ' ', (fmt.width - ilen));
	if (num >= 0 && fmt.SPACE && !fmt.PLUS)
		pf_putchar(fmt.fd, ' ');
	if (num == 0 && fmt.prec == 0 && fmt.width != -1)
		pf_putchar(fmt.fd, ' ');
	if (num >= 0 && fmt.PLUS == 1)
		pf_putchar(fmt.fd, '+');
	if (num < 0 || fmt.PLUS == -1)
		pf_putchar(fmt.fd, '-');
	if (!fmt.MIN && fmt.ZERO && fmt.prec == -1)
		print_padding(fmt.fd, '0', (fmt.width - ilen));
}
