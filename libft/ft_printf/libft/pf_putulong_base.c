/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putulong_base.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/08 16:36:09 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:32:00 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putulong_base(int fd, unsigned long long n, int base, int up)
{
	const char			upc[] = "0123456789ABCDEF";
	const char			low[] = "0123456789abcdef";
	const char			*ptr;

	if (up)
		ptr = upc;
	else
		ptr = low;
	if (n > (unsigned long long)(base - 1))
		pf_putulong_base(fd, n / base, base, up);
	pf_putchar(fd, ptr[(n % base)]);
}
