/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 21:44:34 by omulder        #+#    #+#                */
/*   Updated: 2019/02/02 14:00:47 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_bounds(const char *str, int start, int neg, unsigned long num)
{
	size_t length;

	length = 0;
	while (str[start + length] != '\0' && ft_isdigit(str[start + length]))
		length++;
	if (length > 19 && neg == 1)
		return (-1);
	else if (length > 19)
		return (0);
	return ((int)num * neg);
}

int			ft_atoi(const char *str)
{
	unsigned long	num;
	int				neg;
	int				i;
	int				first;

	i = 0;
	neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	first = i;
	num = (str[i] - '0');
	i++;
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (check_bounds(str, first, neg, num));
}
