/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_conversion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 12:06:41 by omulder        #+#    #+#                */
/*   Updated: 2019/02/08 13:52:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 'o')
		return (1);
	if (c == 'u' || c == 'x' || c == 'X')
		return (1);
	if (c == 'D' || c == 'O' || c == 'U')
		return (1);
	if (c == 'e' || c == 'E')
		return (1);
	if (c == 'f' || c == 'F')
		return (1);
	if (c == 'g' || c == 'G')
		return (1);
	if (c == 'a' || c == 'A')
		return (1);
	if (c == 'C' || c == 'c')
		return (1);
	if (c == 'S' || c == 's')
		return (1);
	if (c == 'p' || c == 'n')
		return (1);
	if (c == '%')
		return (1);
	return (0);
}
