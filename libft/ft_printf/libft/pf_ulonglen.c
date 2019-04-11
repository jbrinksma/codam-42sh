/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_ulonglen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/11 12:15:08 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:25:03 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_ulonglen(unsigned long long n, int base)
{
	int					len;

	len = 1;
	if (n != 0)
		len--;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}
