/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putcharsign.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/12 15:07:22 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:44:58 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putcharsign(int fd, long long c)
{
	char cs;

	cs = (char)c;
	if (cs < 0)
	{
		if (cs < -9)
			pf_putcharsign(fd, (cs / 10) * -1);
		pf_putchar(fd, -(cs % 10) + '0');
	}
	else
	{
		if (cs > 9)
			pf_putcharsign(fd, cs / 10);
		pf_putchar(fd, (cs % 10) + '0');
	}
}
