/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_length.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 12:02:41 by omulder        #+#    #+#                */
/*   Updated: 2019/02/18 14:38:51 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt	find_length(const char **format, t_fmt fmt)
{
	while (is_length(**format))
	{
		if (fmt.length == -1)
			fmt.length = **format;
		else if (**format == fmt.length)
			fmt.length += **format;
		else if (fmt.length == 'h' || fmt.length == ('h' + 'h'))
			fmt.length = **format;
		(*format)++;
	}
	return (fmt);
}
