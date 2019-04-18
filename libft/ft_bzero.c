/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/11 10:47:29 by mavan-he       #+#    #+#                */
/*   Updated: 2019/04/18 15:12:27 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}
