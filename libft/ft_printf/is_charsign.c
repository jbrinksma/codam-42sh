/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_charsign.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/11 18:50:19 by omulder        #+#    #+#                */
/*   Updated: 2019/02/21 13:33:08 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_charsign(t_fmt fmt)
{
	char	c;
	int		l;

	c = fmt.conv;
	l = fmt.length;
	if (c == 'd' || c == 'i')
	{
		if (l == ('h' + 'h'))
			return (1);
	}
	return (0);
}
