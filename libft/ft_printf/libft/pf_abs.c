/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/20 20:30:44 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:19:41 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		pf_abs(long long n)
{
	if (n < 0)
		return (-n);
	return (n);
}
