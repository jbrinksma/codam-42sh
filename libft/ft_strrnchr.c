/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrnchr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/23 15:38:14 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/26 10:29:19 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrnchr(const char *s, int c, int n)
{
	char *res;

	res = NULL;
	if (s == NULL || n == 0)
		return (res);
	while (*s && n)
	{
		if (*s == (char)c)
			res = (char*)s;
		s++;
		n--;
	}
	if (c == 0)
		return ((char*)s);
	return (res);
}
