/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putlong.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/21 14:01:23 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:30:47 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putlong(int fd, long long n)
{
	if (n < 0)
	{
		if (n < -9)
			pf_putlong(fd, (n / 10) * -1);
		pf_putchar(fd, -(n % 10) + '0');
	}
	else
	{
		if (n > 9)
			pf_putlong(fd, n / 10);
		pf_putchar(fd, (n % 10) + '0');
	}
}
