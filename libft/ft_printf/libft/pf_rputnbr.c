/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_rputnbr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 12:12:44 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:32:47 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_rputnbr(int fd, int n)
{
	int len;

	if (n < 0)
	{
		if (n < -9)
			len = (2 + pf_rputnbr(fd, (n / 10) * -1));
		else
			len = 2;
		pf_putchar(fd, -(n % 10) + '0');
	}
	else
	{
		if (n > 9)
			len = (1 + pf_rputnbr(fd, n / 10));
		else
			len = 1;
		pf_putchar(fd, (n % 10) + '0');
	}
	return (len);
}
