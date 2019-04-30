/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 16:03:08 by omulder        #+#    #+#                */
/*   Updated: 2019/04/30 11:54:46 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned char		*s;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (d == s)
		return (dst);
	if (d < s)
		dst = ft_memcpy(d, s, len);
	else
	{
		while (len)
		{
			len -= 1;
			d[len] = s[len];
		}
	}
	return (dst);
}
