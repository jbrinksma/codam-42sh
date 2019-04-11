/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pf_putchar_uni.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 11:27:12 by omulder        #+#    #+#                */
/*   Updated: 2019/03/21 20:28:48 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putmore(int fd, unsigned int c)
{
	unsigned char b;

	if (c > 0x7FF && c <= 0xFFFF)
	{
		b = (0xE0 | (c >> 12));
		write(fd, &b, 1);
		b = (0x80 | ((c >> 6) & 0x3f));
		write(fd, &b, 1);
		b = (0x80 | (c & 0x3F));
		write(fd, &b, 1);
		return (3);
	}
	else if (c > 0xFFFF && c <= 0x001FFFFF)
	{
		b = (0xF0 | (c >> 18));
		write(fd, &b, 1);
		b = (0x80 | ((c >> 12) & 0x3f));
		write(fd, &b, 1);
		b = (0x80 | ((c >> 6) & 0x3f));
		write(fd, &b, 1);
		b = (0x80 | (c & 0x3F));
		write(fd, &b, 1);
		return (4);
	}
	return (1);
}

int			pf_putchar_uni(int fd, unsigned int c)
{
	unsigned char b;

	if (c <= 0x7f)
	{
		write(fd, &c, 1);
		return (1);
	}
	else if (c > 0x7f && c <= 0x7FF)
	{
		b = (0xC0 | (c >> 6));
		write(fd, &b, 1);
		b = (0x80 | (c & 0x3F));
		write(fd, &b, 1);
		return (2);
	}
	return (putmore(fd, c));
}
