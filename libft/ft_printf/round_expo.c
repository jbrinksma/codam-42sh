/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   round_expo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/28 15:21:12 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:53 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	round_expo(double expo, int prec)
{
	long long cpy;

	cpy = expo * pf_powl(10, prec + 1);
	if (cpy < 0)
		cpy = -cpy;
	if (cpy % 10 >= 5)
	{
		return (pf_abs((cpy / 10) + 1));
	}
	return (pf_abs(cpy / 10));
}
