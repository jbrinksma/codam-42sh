/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 21:44:34 by omulder        #+#    #+#                */
/*   Updated: 2019/03/13 16:20:14 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_bounds(const char *str, int start, int neg, unsigned long num)
{
	size_t length;

	length = 0;
	while (str[start + length] != '\0' && pf_isdigit(str[start + length]))
		length++;
	if (length > 19 && neg == 1)
		return (-1);
	else if (length > 19)
		return (0);
	return ((int)num * neg);
}

int			pf_atoi(const char *str)
{
	unsigned long	num;
	int				neg;
	int				i;
	int				first;

	i = 0;
	neg = 1;
	while (pf_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!pf_isdigit(str[i]))
		return (0);
	first = i;
	num = (str[i] - '0');
	i++;
	while (pf_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (check_bounds(str, first, neg, num));
}
