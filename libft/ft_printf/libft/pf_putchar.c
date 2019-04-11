/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putchar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/20 15:14:38 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:28:59 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_putchar(int fd, int c)
{
	char ca;

	ca = (char)c;
	write(fd, &ca, 1);
	return (1);
}
