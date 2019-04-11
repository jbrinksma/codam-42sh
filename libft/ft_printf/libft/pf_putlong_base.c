/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putlong_base.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/08 16:36:09 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:30:22 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putlong_base(int fd, long long n, int base, int up)
{
	const char			upc[] = "0123456789ABCDEF";
	const char			low[] = "0123456789abcdef";
	const char			*ptr;
	unsigned long long	num;

	if (up)
		ptr = upc;
	else
		ptr = low;
	if (n < 0 && base == 10)
	{
		if (n < -(base - 1))
			pf_putlong_base(fd, (n / base) * -1, base, up);
		pf_putchar(fd, ptr[(-(n % base))]);
	}
	num = (unsigned long long)n;
	if ((n >= 0 && base == 10) || base != 10)
	{
		if (num > (unsigned long long)(base - 1))
			pf_putlong_base(fd, num / base, base, up);
		pf_putchar(fd, ptr[(num % base)]);
	}
}
