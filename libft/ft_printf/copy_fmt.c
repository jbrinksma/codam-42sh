/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_fmt.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/26 13:01:25 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:37:56 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	copy_fmt(t_fmt fmt)
{
	int		i;
	t_fmt	copy;

	i = 0;
	while (i < 6)
	{
		copy.opt[i] = fmt.opt[i];
		i++;
	}
	copy.fd = fmt.fd;
	copy.width = fmt.width;
	copy.prec = fmt.prec;
	copy.length = fmt.length;
	copy.conv = fmt.conv;
	return (copy);
}
