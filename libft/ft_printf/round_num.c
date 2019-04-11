/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   round_num.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 15:21:59 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:53 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	round_num(long long num, double expo)
{
	long long cpy;

	cpy = expo * pf_powl(10, 2);
	if (cpy < 0)
		cpy = -cpy;
	if (cpy % 100 > 50)
	{
		if (num > 0)
			return (num + 1);
		else
			return (num - 1);
	}
	return (num);
}
